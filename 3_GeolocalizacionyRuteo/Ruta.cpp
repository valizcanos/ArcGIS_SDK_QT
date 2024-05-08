// Copyright 2024 ESRI
//
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
//
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
//
// See the Sample code usage restrictions document for further information.
//

#include "Ruta.h"

#include "Map.h"
#include "MapQuickView.h"
#include "MapTypes.h"

#include "LocationDisplay.h"
#include "MapViewTypes.h"

//---------------------------------
#include "Point.h"
#include "Viewpoint.h"
#include "SpatialReference.h"
#include <QFuture>
#include "DirectionManeuverListModel.h"
#include "Graphic.h"
#include "GraphicListModel.h"
#include "GraphicsOverlay.h"
#include "GraphicsOverlayListModel.h"
#include "Polyline.h"
#include "RouteTask.h"
#include "RouteResult.h"
#include "RouteParameters.h"
#include "Route.h"
#include "SimpleLineSymbol.h"
#include "SimpleMarkerSymbol.h"
#include "Stop.h"
#include "Symbol.h"
#include "SymbolTypes.h"
#include <QGeoPositionInfoSource>
#include <QList>
#include <QUrl>
#include <QUuid>

#include "ShapefileFeatureTable.h"
#include "FeatureLayer.h"
#include "LayerListModel.h"

//#include "Raster.h"
//#include "RasterLayer.h“

#include "SimpleRenderer.h"
#include "SimpleMarkerSymbol.h"
#include "SymbolTypes.h"

//---------------------------------


using namespace Esri::ArcGISRuntime;

Ruta::Ruta(QObject *parent /* = nullptr */)
    : QObject(parent)
    , m_map(new Map(BasemapStyle::ArcGISStreets, this))
    //---------------------------------
    ,m_currentState(RouteBuilderStatus::NotStarted)
    //---------------------------------
{
    //---------------------------------
    setupRouteTask();
    //---------------------------------
}

Ruta::~Ruta() {}

MapQuickView *Ruta::mapView() const
{
    return m_mapView;
}


void Ruta::CargarCapas()
{

    //const Point center(-75, 5, SpatialReference::wgs84());
    //const Viewpoint viewpoint(center, 100000.0);
    //m_mapView->setViewpointAsync(viewpoint);

    QString shapefilePath = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/data/Col/gadm41_COL_1.shp";
    ShapefileFeatureTable* shapefileFeatureTable  = new ShapefileFeatureTable(shapefilePath, this);
    FeatureLayer* featureLayer = new FeatureLayer(shapefileFeatureTable, this);
    m_map->operationalLayers()->append(featureLayer);

    SimpleRenderer* renderer = new SimpleRenderer(new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor("red"), 10.0), this);
    featureLayer->setRenderer(renderer);


    QString LINEASPath = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/data/Col/CO300023.shp";
    ShapefileFeatureTable* shapeLINEASPathFeatureTable  = new ShapefileFeatureTable(LINEASPath, this);
    FeatureLayer* lINEASLayer = new FeatureLayer(shapeLINEASPathFeatureTable, this);
    m_map->operationalLayers()->append(lINEASLayer);

    SimpleRenderer* renderizar = new SimpleRenderer(new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor("blue"), 10.0), this);
    lINEASLayer->setRenderer(renderizar);


}


void Ruta::localizacion(){
    m_mapView->locationDisplay()->start();
    // center the location display around the device location
    m_mapView->locationDisplay()->setAutoPanMode(LocationDisplayAutoPanMode::Recenter);

    //---------------------------------
    connect(m_mapView, &MapQuickView::mouseClicked, this, [this](QMouseEvent& mouse)
            {
                const Point mapPoint = m_mapView->screenToLocation(mouse.position().x(), mouse.position().y());
                switch (m_currentState)
                {
                case RouteBuilderStatus::NotStarted:
                    resetState();
                    m_currentState = RouteBuilderStatus::SelectedStart;
                    m_startGraphic->setGeometry(mapPoint);
                    break;
                case RouteBuilderStatus::SelectedStart:
                    m_currentState = RouteBuilderStatus::SelectedStartAndEnd;
                    m_endGraphic->setGeometry(mapPoint);
                    findRoute();
                    break;

                case RouteBuilderStatus::SelectedStartAndEnd:
                    // Ignore touches while routing is in progress
                    break;
                }
            });


    m_graphicsOverlay = new GraphicsOverlay(this);
    m_mapView->graphicsOverlays()->append(m_graphicsOverlay);

    SimpleLineSymbol* startOutlineSymbol = new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor("blue"), 2/*width*/, this);
    SimpleMarkerSymbol* startSymbol = new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Diamond, QColor("orange"), 12/*width*/, this);
    startSymbol->setOutline(startOutlineSymbol);
    m_startGraphic = new Graphic(this);
    m_startGraphic->setSymbol(startSymbol);

    SimpleLineSymbol* endOutlineSymbol = new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor("red"), 2/*width*/, this);
    SimpleMarkerSymbol* endSymbol = new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Square, QColor("green"), 12/*width*/, this);
    endSymbol->setOutline(endOutlineSymbol);
    m_endGraphic = new Graphic(this);
    m_endGraphic->setSymbol(endSymbol);

    SimpleLineSymbol* lineSymbol = new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor("blue"), 4/*width*/, this);
    m_lineGraphic = new Graphic(this);
    m_lineGraphic->setSymbol(lineSymbol);

    m_graphicsOverlay->graphics()->append(QList<Graphic*> {m_startGraphic, m_endGraphic, m_lineGraphic});
//---------------------------------




}


//---------------------------------
void Ruta::setupRouteTask()
{
    // create the route task pointing to an online service
    m_routeTask = new RouteTask(QUrl("https://route-api.arcgis.com/arcgis/rest/services/World/Route/NAServer/Route_World"), this);

    // Create the default parameters which will load the route task implicitly.
    m_routeTask->createDefaultParametersAsync().then(this,[this](const RouteParameters& routeParameters)
                                                     {
                                                         // Store the resulting route parameters.
                                                         m_routeParameters = routeParameters;
                                                     });
}
//---------------------------------



//---------------------------------
void Ruta::findRoute()
{
    if (m_routeTask->loadStatus() != LoadStatus::Loaded || m_routeParameters.isEmpty())
        return;

    // Set parameters to return directions.
    m_routeParameters.setReturnDirections(true);

    // Clear previous stops from the parameters.
    m_routeParameters.clearStops();

    // Set the stops to the parameters.
    const Stop stop1(Point(m_startGraphic->geometry()));
    const Stop stop2(Point(m_endGraphic->geometry()));
    m_routeParameters.setStops(QList<Stop> { stop1, stop2 });

    // Solve the route with the parameters.
    m_routeTask->solveRouteAsync(m_routeParameters).then(this,[this](const RouteResult& routeResult)
                                                         {
                                                             // Add the route graphic once the solve completes.
                                                             const Route generatedRoute = routeResult.routes().at(0);
                                                             m_lineGraphic->setGeometry(generatedRoute.routeGeometry());
                                                             m_currentState = RouteBuilderStatus::NotStarted;

                                                             // Set the direction maneuver list model.
                                                             m_directions = generatedRoute.directionManeuvers(this);
                                                             emit directionsChanged();
                                                         });
}
//---------------------------------




//---------------------------------
void Ruta::resetState()
{
    m_startGraphic->setGeometry(Point());
    m_endGraphic->setGeometry(Point());
    m_lineGraphic->setGeometry(Point());
    m_directions = nullptr;
    m_currentState = RouteBuilderStatus::NotStarted;
}
//---------------------------------




// Set the view (created in QML)
void Ruta::setMapView(MapQuickView *mapView)
{
    if (!mapView || mapView == m_mapView) {
        return;
    }

    m_mapView = mapView;
    m_mapView->setMap(m_map);

    localizacion();
    CargarCapas();

    emit mapViewChanged();
}

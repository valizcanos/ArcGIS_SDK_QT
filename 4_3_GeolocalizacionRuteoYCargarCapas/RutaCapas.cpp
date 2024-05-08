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

#include "RutaCapas.h"
#include "Map.h"
#include "MapQuickView.h"
#include "MapTypes.h"

#include "LocationDisplay.h"
#include "MapViewTypes.h"
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
#include "SimpleRenderer.h"
#include "SimpleMarkerSymbol.h"
#include "SymbolTypes.h"


using namespace Esri::ArcGISRuntime;

RutaCapas::RutaCapas(QObject *parent /* = nullptr */)
    : QObject(parent)
    , m_map(new Map(BasemapStyle::ArcGISStreets, this))
    ,m_currentState(RouteBuilderStatus::NotStarted)
{setupRouteTask();}

RutaCapas::~RutaCapas() {}

MapQuickView *RutaCapas::mapView() const
{
    return m_mapView;
}

void RutaCapas::CargarCapas()
{

    //Croquis de Colombia
    QString shapefilePath = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/data/Col/gadm41_COL_1.shp";
    ShapefileFeatureTable* shapefileFeatureTable  = new ShapefileFeatureTable(shapefilePath, this);
    FeatureLayer* featureLayer = new FeatureLayer(shapefileFeatureTable, this);
    m_map->operationalLayers()->append(featureLayer);

    SimpleRenderer* renderer = new SimpleRenderer(new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor("red"), 2.0), this);
    featureLayer->setRenderer(renderer);

    //Ruta BUAARE
    QString shapefileBUAARE = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/data/CartaN/BUAARE.shp";
    ShapefileFeatureTable* BUAAREFeatureTable  = new ShapefileFeatureTable(shapefileBUAARE, this);
    FeatureLayer* BUAARELayer = new FeatureLayer(BUAAREFeatureTable, this);
    m_map->operationalLayers()->append(BUAARELayer);

    SimpleRenderer* renderBUAARE = new SimpleRenderer(new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor("blue"), 2.0), this);
    BUAARELayer->setRenderer(renderBUAARE);

    //Ruta DEPCNT
    QString shapefileDEPCNT = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/data/CartaN/DEPCNT.shp";
    ShapefileFeatureTable* DEPCNTFeatureTable  = new ShapefileFeatureTable(shapefileDEPCNT, this);
    FeatureLayer* DEPCNTLayer = new FeatureLayer(DEPCNTFeatureTable, this);
    m_map->operationalLayers()->append(DEPCNTLayer);

    SimpleRenderer* renderDEPCNT = new SimpleRenderer(new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor("blue"), 2.0), this);
    DEPCNTLayer->setRenderer(renderDEPCNT);


    //Ruta SOUNDG
    QString shapefileSOUNDG = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/data/CartaN/SOUNDG.shp";
    ShapefileFeatureTable* SOUNDGFeatureTable  = new ShapefileFeatureTable(shapefileSOUNDG, this);
    FeatureLayer* SOUNDGLayer = new FeatureLayer(SOUNDGFeatureTable, this);
    m_map->operationalLayers()->append(SOUNDGLayer);

    SimpleRenderer* renderSOUNDG = new SimpleRenderer(new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor("blue"), 2.0), this);
    SOUNDGLayer->setRenderer(renderSOUNDG);

    //Ruta RutaNueva
    QString shapefileRutaNueva = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/data/CartaN/RutaNueva.shp";
    ShapefileFeatureTable* RutaNuevaFeatureTable  = new ShapefileFeatureTable(shapefileRutaNueva, this);
    FeatureLayer* RutaNuevaLayer = new FeatureLayer(RutaNuevaFeatureTable, this);
    m_map->operationalLayers()->append(RutaNuevaLayer);

    SimpleRenderer* renderRutaNueva = new SimpleRenderer(new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Circle, QColor("blue"), 2.0), this);
    RutaNuevaLayer->setRenderer(renderRutaNueva);

}






void RutaCapas::localizacion(){
    m_mapView->locationDisplay()->start();
    // centrar la visualización de ubicación alrededor de la ubicación del dispositivo
    m_mapView->locationDisplay()->setAutoPanMode(LocationDisplayAutoPanMode::Recenter);

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



}

void RutaCapas::setupRouteTask()
{
    // crea la tarea de ruta que apunta a un servicio en línea
    m_routeTask = new RouteTask(QUrl("https://route-api.arcgis.com/arcgis/rest/services/World/Route/NAServer/Route_World"), this);

    // Cree los parámetros predeterminados que cargarán la tarea de ruta implícitamente.
    m_routeTask->createDefaultParametersAsync().then(this,[this](const RouteParameters& routeParameters)
                                                     {
                                                         // Almacene los parámetros de ruta resultantes.
                                                         m_routeParameters = routeParameters;
                                                     });
}


void RutaCapas::findRoute()
{
    if (m_routeTask->loadStatus() != LoadStatus::Loaded || m_routeParameters.isEmpty())
        return;

    // Establezca parámetros para devolver direcciones.
    m_routeParameters.setReturnDirections(true);

    // Borrar paradas anteriores de los parámetros.
    m_routeParameters.clearStops();

    // Establezca las paradas según los parámetros.
    const Stop stop1(Point(m_startGraphic->geometry()));
    const Stop stop2(Point(m_endGraphic->geometry()));
    m_routeParameters.setStops(QList<Stop> { stop1, stop2 });

    // Resuelve la ruta con los parámetros.
    m_routeTask->solveRouteAsync(m_routeParameters).then(this,[this](const RouteResult& routeResult)
                                                         {
                                                             // Agregue el gráfico de ruta una vez que se complete la resolución.
                                                             const Route generatedRoute = routeResult.routes().at(0);
                                                             m_lineGraphic->setGeometry(generatedRoute.routeGeometry());
                                                             m_currentState = RouteBuilderStatus::NotStarted;

                                                             // Establecer el modelo de lista de maniobras de dirección.
                                                             m_directions = generatedRoute.directionManeuvers(this);
                                                             emit directionsChanged();
                                                         });
}


void RutaCapas::resetState()
{
    m_startGraphic->setGeometry(Point());
    m_endGraphic->setGeometry(Point());
    m_lineGraphic->setGeometry(Point());
    m_directions = nullptr;
    m_currentState = RouteBuilderStatus::NotStarted;
}



// Set the view (created in QML)
void RutaCapas::setMapView(MapQuickView *mapView)
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

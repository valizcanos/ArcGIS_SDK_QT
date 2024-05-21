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

#include "MapaDeVistas.h"

#include "Map.h"
#include "MapQuickView.h"
#include "MapTypes.h"

/*Librería para cargar capas vectoriales*/
#include "Point.h"
#include "SpatialReference.h"
#include <QFuture>
#include "Viewpoint.h"
#include "ShapefileFeatureTable.h"
#include "FeatureLayer.h"
#include "LayerListModel.h"
#include "SimpleRenderer.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleLineSymbol.h"
#include "SimpleFillSymbol.h"
#include "SymbolTypes.h"

/*Librerías para poner etquitas a los shp*/
#include "TextSymbol.h"
#include "ArcadeLabelExpression.h"
#include "LabelDefinition.h"
#include "LabelDefinitionListModel.h"

/*Librería para dibujar vectores*/
#include "Graphic.h"
#include "GraphicListModel.h"
#include "GraphicsOverlay.h"
#include "GraphicsOverlayListModel.h"
#include "PolylineBuilder.h"
#include "PolygonBuilder.h"
#include "SimpleFillSymbol.h"
#include "SimpleLineSymbol.h"
#include "SimpleMarkerSymbol.h"
#include "SymbolTypes.h"

/*Librería para mostrar la hora*/
#include<QDateTime>

/*Librerías para cambiar la vista del mapa*/
#include "Point.h"
#include "Viewpoint.h"
#include "SpatialReference.h"
#include "Envelope.h"


using namespace Esri::ArcGISRuntime;

MapaDeVistas::MapaDeVistas(QObject *parent /* = nullptr */)
    : QObject(parent)
    , m_map(new Map(BasemapStyle::ArcGISStreets, this))
{}

MapaDeVistas::~MapaDeVistas() {}

QString MapaDeVistas::tiempo(){
    return QDateTime::currentDateTime().toString("hh:mm:ss");
}

void MapaDeVistas::cambiarVistasQML(QString vista){

    if (vista == "Center")
    {
        Point colA(-76.195681,3.056218, SpatialReference::wgs84());
        m_mapView->setViewpointCenterAsync(colA);
    }
    else if (vista == "Center and scale")
    {
        Point colB(-76.564, 3.677, SpatialReference::wgs84());
        m_mapView->setViewpointCenterAsync(colB, 4000000.0);
    }
    else if (vista == "Geometry")
    {
        Envelope colC(-76.564, 3.056218, -76.195681, 3.677, SpatialReference::wgs84());
        m_mapView->setViewpointGeometryAsync(colC);
    }
    else if (vista == "Geometry and padding")
    {
        Envelope colD(-76.564, 3.056218, -76.195681, 3.677, SpatialReference::wgs84());
        m_mapView->setViewpointGeometryAsync(colD, 200 * screenRatio());
    }
    else if (vista == "Rotation")
    {
        m_rotationValue = (m_rotationValue + 45) % 360;
        m_mapView->setViewpointRotationAsync(m_rotationValue);
    }
    else if (vista == "Scale 1:5,000,000")
    {
        m_mapView->setViewpointScaleAsync(5000000.0);
    }
    else if (vista == "Scale 1:10,000,000")
    {
        m_mapView->setViewpointScaleAsync(10000000.0);
    }
}

void MapaDeVistas::cargarCapas(){

    //Croquis de Colombia --------------------------------------------------------------------------------
    QString shapefilePath = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/ResumerPro/shapes/gadm41_COL_1.shp";
    ShapefileFeatureTable* shapefileFeatureTable  = new ShapefileFeatureTable(shapefilePath, this);
    FeatureLayer* featureLayer = new FeatureLayer(shapefileFeatureTable, this);
    m_map->operationalLayers()->append(featureLayer);
    SimpleRenderer* renderer = new SimpleRenderer(new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor(Qt::blue), 3, this));
    featureLayer->setRenderer(renderer); //Delineado sin relleno
    //SimpleLineSymbol* bordes = new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor(Qt::blue), 3, this);
    //SimpleRenderer* renderer = new SimpleRenderer(new SimpleFillSymbol(SimpleFillSymbolStyle::Solid, QColor(Qt::yellow), bordes, this));
    //featureLayer->setRenderer(renderer); //Delineado con relleno

    //Aeropuerto de Colombia ------------------------------------------------------------------------------
    QString aeropuertoPath = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/ResumerPro/shapes/Aeropuerto_P.shp";
    ShapefileFeatureTable* aeropuertoFeatureTable  = new ShapefileFeatureTable(aeropuertoPath, this);
    FeatureLayer* aeropuertoLayer = new FeatureLayer(aeropuertoFeatureTable, this);
    m_map->operationalLayers()->append(aeropuertoLayer);
    SimpleRenderer* aeropuertoRenderer = new SimpleRenderer(new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Cross, QColor("red"), 10.0, this));
    aeropuertoLayer->setRenderer(aeropuertoRenderer);

    //*******
    aeropuertoLayer->setLabelsEnabled(true);
    TextSymbol* AeropuertosTextSymbol = new TextSymbol(this);
    AeropuertosTextSymbol->setFontFamily("Arial");
    AeropuertosTextSymbol->setFontWeight(FontWeight::Bold);
    AeropuertosTextSymbol->setSize(16);
    AeropuertosTextSymbol->setColor(QColor("blue"));
    AeropuertosTextSymbol->setHaloColor(QColor("white"));
    AeropuertosTextSymbol->setHaloWidth(2);
    ArcadeLabelExpression* AeropuertoLabelExpression  = new ArcadeLabelExpression("$feature.NOMBRE_GEO", this);
    LabelDefinition* AeropuertoLabelDefinition = new LabelDefinition(AeropuertoLabelExpression, AeropuertosTextSymbol, this);
    AeropuertoLabelDefinition->setWhereClause("[SYMBOL] >= 1");
    aeropuertoLayer->labelDefinitions()->append(AeropuertoLabelDefinition);


    //Curvas de nivel de Colombia --------------------------------------------------------------------------
    QString curvasPath = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/ResumerPro/shapes/Curva_Nivel.shp";
    ShapefileFeatureTable* curvasFeatureTable  = new ShapefileFeatureTable(curvasPath, this);
    FeatureLayer* curvasLayer = new FeatureLayer(curvasFeatureTable, this);
    m_map->operationalLayers()->append(curvasLayer);
    SimpleRenderer* curvasRenderer = new SimpleRenderer(new SimpleLineSymbol(SimpleLineSymbolStyle::DashDotDot, QColor(Qt::green), 1, this));
    curvasLayer->setRenderer(curvasRenderer);
}

void MapaDeVistas::createGraphics(GraphicsOverlay *overlay) {
    //Dibujar punto -----------------------------------------------------------------------------------------
    const Point punto(-76.80657463861, 3.0005930608889, SpatialReference::wgs84());
    SimpleLineSymbol* contornoPunto= new SimpleLineSymbol(SimpleLineSymbolStyle::DashDot,QColor("red"),1,this);
    SimpleMarkerSymbol* simboloPunto = new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Triangle,QColor("blue"),20, this);
    simboloPunto -> setOutline(contornoPunto);
    Graphic* graficarPunto = new Graphic(punto,simboloPunto, this);
    overlay ->graphics()->append(graficarPunto);

    //Dibujar polilínea --------------------------------------------------------------------------------------
    PolylineBuilder* polyline_builder = new PolylineBuilder(SpatialReference::wgs84(), this);
    polyline_builder->addPoint(-76.80657463861, 3.0005930608889);
    polyline_builder->addPoint(-76.70657463861, 3.1005930608889);
    polyline_builder->addPoint(-76.60657463861, 3.2005930608889);
    SimpleLineSymbol* line_symbol = new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor(Qt::blue), 3, this);
    Graphic* polyline_graphic = new Graphic(polyline_builder->toGeometry(), line_symbol, this);
    overlay->graphics()->append(polyline_graphic);

    //Dibujar polígono -----------------------------------------------------------------------------------------
    const QList<Point> points = { Point(-76.8190, 3.0138), Point(-76.8068, 3.0216), Point(-76.7914, 3.0164), Point(-76.7960, 3.0086), Point(-76.8086, 3.0035), };
    PolygonBuilder* polygon_builder = new PolygonBuilder(SpatialReference::wgs84(), this);
    polygon_builder->addPoints(points);
    SimpleLineSymbol* polygon_line_symbol = new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor(Qt::blue), 3, this);
    SimpleFillSymbol* fill_symbol = new SimpleFillSymbol(SimpleFillSymbolStyle::Solid, QColor(Qt::yellow), polygon_line_symbol, this);
    Graphic* polygon_graphic = new Graphic(polygon_builder->toGeometry(), fill_symbol, this);
    overlay->graphics()->append(polygon_graphic);
}

MapQuickView *MapaDeVistas::mapView() const
{
    return m_mapView;
}

// Set the view (created in QML)
void MapaDeVistas::setMapView(MapQuickView *mapView)
{
    if (!mapView || mapView == m_mapView) {
        return;
    }

    m_mapView = mapView;
    m_mapView->setMap(m_map);
    cargarCapas();
    GraphicsOverlay* overlay = new GraphicsOverlay(this);
    createGraphics(overlay);
    m_mapView->graphicsOverlays()->append(overlay);
    emit mapViewChanged();
}

double MapaDeVistas::screenRatio() const
{
    const double width = static_cast<double>(m_mapView->width());
    const double height = static_cast<double>(m_mapView->height());
    return height > width ? width / height : height / width;
}

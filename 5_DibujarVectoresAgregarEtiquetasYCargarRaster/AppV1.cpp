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

#include "AppV1.h"

//Librerías incluidas por defecto
#include "Map.h"
#include "MapQuickView.h"
#include "MapTypes.h"

//Librerías empleadas para centrar el mapa base en un lugar determinado
#include "Point.h"
#include "Viewpoint.h"
#include "SpatialReference.h"
#include <QFuture>

//Librerías para crear vectores de tipo punto, linea y polígono
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

//Librerías para cargar archivos vectoriales desde mi computador
#include "ShapefileFeatureTable.h"
#include "FeatureLayer.h"
#include "LayerListModel.h"
#include "SimpleRenderer.h"
#include "SimpleMarkerSymbol.h"
#include "SimpleLineSymbol.h"
#include "SimpleFillSymbol.h"
#include "SymbolTypes.h"

//Librerías para asignar etiquetas a los vectores
#include "TextSymbol.h"
#include "ArcadeLabelExpression.h"
#include "LabelDefinition.h"
#include "LabelDefinitionListModel.h"

//Librerias para cargar archivos tipo Raster desde mi computador
#include "Raster.h"
#include "RasterLayer.h"
#include "LayerListModel.h"
#include "Basemap.h"
#include "ColormapRenderer.h"
QList<QColor> colormap;


using namespace Esri::ArcGISRuntime;

AppV1::AppV1(QObject *parent /* = nullptr */)
    : QObject(parent)
    , m_map(new Map(BasemapStyle::OsmStandard, this))
{}

AppV1::~AppV1() {}

MapQuickView *AppV1::mapView() const
{
    return m_mapView;
}

void AppV1::visualizacion(){

    /*----------------------------------------------------------------------------------------------------*/
    /*Centrar visualización del mapa base en un lugar determinado del planeta*/
    const Point centrar(-74.06,4.65,SpatialReference::wgs84());
    const Viewpoint vista(centrar,100000);
    m_mapView ->setViewpointAsync(vista);

    /*----------------------------------------------------------------------------------------------------*/
    /*Cargar mapa de Colombia, archivo vectorial de tipo polígono*/
    QString rutaColombia = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/ResumerPro/shapes/gadm41_COL_1.shp";
    ShapefileFeatureTable* rutaColombiaFeatureTable  = new ShapefileFeatureTable(rutaColombia, this);
    FeatureLayer* rutaColombiaLayer = new FeatureLayer(rutaColombiaFeatureTable, this);
    m_map->operationalLayers()->append(rutaColombiaLayer);
    //SimpleRenderer* rutaColombiaRenderer = new SimpleRenderer(new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor(Qt::darkGray), 3, this));
    //rutaColombiaLayer->setRenderer(rutaColombiaRenderer); //Delineado sin relleno
    SimpleLineSymbol* rutaColombiaBordes = new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor(Qt::blue), 3, this);
    SimpleRenderer* rutaColombiaRenderer = new SimpleRenderer(new SimpleFillSymbol(SimpleFillSymbolStyle::Solid, QColor(Qt::green), rutaColombiaBordes, this));
    rutaColombiaLayer->setRenderer(rutaColombiaRenderer); //Delineado con relleno

    /*Cargar localización de los aeropuertos de Colombia, archivo vectorial de tipo punto*/
    QString aeropuertoPath = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/ResumerPro/shapes/Aeropuerto_P.shp";
    ShapefileFeatureTable* aeropuertoFeatureTable  = new ShapefileFeatureTable(aeropuertoPath, this);
    FeatureLayer* aeropuertoLayer = new FeatureLayer(aeropuertoFeatureTable, this);
    m_map->operationalLayers()->append(aeropuertoLayer);
    SimpleRenderer* aeropuertoRenderer = new SimpleRenderer(new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::X, QColor("red"), 25.0, this));
    aeropuertoLayer->setRenderer(aeropuertoRenderer);

    /*Cargar curvas de nivel de Colombia, archivo vectorial de tipo línea*/
    QString curvasPath = "D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/ResumerPro/shapes/Curva_Nivel.shp";
    ShapefileFeatureTable* curvasFeatureTable  = new ShapefileFeatureTable(curvasPath, this);
    FeatureLayer* curvasLayer = new FeatureLayer(curvasFeatureTable, this);
    m_map->operationalLayers()->append(curvasLayer);
    SimpleRenderer* curvasRenderer = new SimpleRenderer(new SimpleLineSymbol(SimpleLineSymbolStyle::DashDotDot, QColor(Qt::darkYellow), 1, this));
    curvasLayer->setRenderer(curvasRenderer);

    /*------------------------------------------------------------------------------------------------------------------------------*/
    /*Asignar etiquetas al vector de puntos de la capa Aeropuerto*/
    aeropuertoLayer->setLabelsEnabled(true);
    TextSymbol* AeropuertosTextSymbol = new TextSymbol(this);
    AeropuertosTextSymbol->setFontFamily("Calibri");
    AeropuertosTextSymbol->setFontWeight(FontWeight::Normal);
    AeropuertosTextSymbol->setSize(12);
    AeropuertosTextSymbol->setColor(QColor("blue"));
    AeropuertosTextSymbol->setHaloColor(QColor("lightGray"));
    AeropuertosTextSymbol->setHaloWidth(1);
    ArcadeLabelExpression* AeropuertoLabelExpression  = new ArcadeLabelExpression("$feature.NOMBRE_GEO", this);
    LabelDefinition* AeropuertoLabelDefinition = new LabelDefinition(AeropuertoLabelExpression, AeropuertosTextSymbol, this);
    AeropuertoLabelDefinition->setWhereClause("[SYMBOL] >= 1");
    aeropuertoLayer->labelDefinitions()->append(AeropuertoLabelDefinition);

    /*Asignar etiquetas al vector de lineas de las curvas de nivel*/
    curvasLayer->setLabelsEnabled(true);
    TextSymbol* CurvasTextSymbol = new TextSymbol(this);
    CurvasTextSymbol->setFontFamily("Calibri");
    CurvasTextSymbol->setFontWeight(FontWeight::Normal);
    CurvasTextSymbol->setSize(9);
    CurvasTextSymbol->setColor(QColor("blue"));
    CurvasTextSymbol->setHaloColor(QColor("lightGray"));
    CurvasTextSymbol->setHaloWidth(1);
    ArcadeLabelExpression* CurvasLabelExpression  = new ArcadeLabelExpression("$feature.ALTURA_SOB", this);
    LabelDefinition* CurvasLabelDefinition = new LabelDefinition(CurvasLabelExpression, CurvasTextSymbol, this);
    CurvasLabelDefinition->setWhereClause("[ALTURA_SOB] >= 1000");
    curvasLayer->labelDefinitions()->append(CurvasLabelDefinition);

    /*Asignar etiquetas al vector de polígonos de la capa Colombia*/
    rutaColombiaLayer->setLabelsEnabled(true);
    TextSymbol* ColombiaTextSymbol = new TextSymbol(this);
    ColombiaTextSymbol->setFontFamily("Calibri");
    ColombiaTextSymbol->setFontWeight(FontWeight::Normal);
    ColombiaTextSymbol->setSize(18);
    ColombiaTextSymbol->setColor(QColor("blue"));
    ColombiaTextSymbol->setHaloColor(QColor("lightGray"));
    ColombiaTextSymbol->setHaloWidth(1);
    ArcadeLabelExpression* ColombiaExpression  = new ArcadeLabelExpression("$feature.NAME_1", this);
    LabelDefinition* ColombiaDefinition = new LabelDefinition(ColombiaExpression, ColombiaTextSymbol, this);
    rutaColombiaLayer->labelDefinitions()->append(ColombiaDefinition);
    /*------------------------------------------------------------------------------------------------------------------------------*/
    /*Cargar capa Raster*/
    Raster* raster = new Raster("D:/DOCS/ASIGNATURAS IMPARTIDAS/ArcGIS SDK/ResumerPro/raster/Alturas de California.tif", this);
    RasterLayer* rasterLayer  = new RasterLayer(raster, this);
    colormap << QColor(Qt::red) << QColor(Qt::lightGray) << QColor(Qt::green)<< QColor(Qt::black)<< QColor(Qt::white)<< QColor(Qt::yellow);
    ColormapRenderer* colormapRenderer = new ColormapRenderer(colormap,  this);
    rasterLayer->setRenderer(colormapRenderer);
    //Basemap* basemap = new Basemap(rasterLayer, this);
    //Map* map = new Map(basemap, this);
    //m_mapView->setMap(map);
    m_map->operationalLayers()->append(rasterLayer);
}

void AppV1::crearGraficas(GraphicsOverlay *overlay) {

    const QList<Point> puntosPoligono = { Point(-74.000,4.600), Point(-74.070,4.600), Point(-74.070,4.690), Point(-74.000,4.690) };
    PolygonBuilder* contructorDePoligono = new PolygonBuilder(SpatialReference::wgs84(), this);
    contructorDePoligono->addPoints(puntosPoligono);
    SimpleLineSymbol* contornoPoli = new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor(Qt::blue), 3, this);
    SimpleFillSymbol* rellenoPoli = new SimpleFillSymbol(SimpleFillSymbolStyle::Solid, QColor(Qt::yellow), contornoPoli, this);
    Graphic* polygon_graphic = new Graphic(contructorDePoligono->toGeometry(), rellenoPoli, this);
    overlay->graphics()->append(polygon_graphic);

    const Point punto(-74.06,4.65,SpatialReference::wgs84());
    SimpleLineSymbol* contornoPunto= new SimpleLineSymbol(SimpleLineSymbolStyle::Dot,QColor("red"),1,this);
    SimpleMarkerSymbol* simboloPunto = new SimpleMarkerSymbol(SimpleMarkerSymbolStyle::Diamond,QColor("blue"),15, this);
    simboloPunto -> setOutline(contornoPunto);
    Graphic* graficarPunto = new Graphic(punto,simboloPunto, this);
    overlay ->graphics()->append(graficarPunto);


    PolylineBuilder* construirPoliLinea = new PolylineBuilder(SpatialReference::wgs84(), this);
    construirPoliLinea->addPoint(-74.067,4.657);
    construirPoliLinea->addPoint(-74.076,4.607);
    construirPoliLinea->addPoint(-74.096,4.687);
    construirPoliLinea->addPoint(-74.006,4.699);
    SimpleLineSymbol* simboloDeLinea = new SimpleLineSymbol(SimpleLineSymbolStyle::LongDash, QColor(Qt::blue), 3, this);
    Graphic* graficarPolilinea = new Graphic(construirPoliLinea->toGeometry(), simboloDeLinea, this);
    overlay->graphics()->append(graficarPolilinea);

}


// Set the view (created in QML)
void AppV1::setMapView(MapQuickView *mapView)
{
    if (!mapView || mapView == m_mapView) {
        return;
    }
    m_mapView = mapView;
    m_mapView->setMap(m_map);
    visualizacion();

    GraphicsOverlay* overlay = new GraphicsOverlay(this);
    crearGraficas(overlay);
    m_mapView->graphicsOverlays()->append(overlay);
    emit mapViewChanged();
}

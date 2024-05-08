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

#include "MapaBaseWeb.h"

#include "Map.h"
#include "MapQuickView.h"
#include "MapTypes.h"

/*Librerias incluidas*/

#include "Point.h"
#include "Viewpoint.h"
#include "SpatialReference.h"
#include "Portal.h"
#include "PortalItem.h"
#include "FeatureLayer.h"
#include "LayerListModel.h"
#include <QFuture>

using namespace Esri::ArcGISRuntime;
/*---------------------CONSTRUCTOR------------------------------*/
MapaBaseWeb::MapaBaseWeb(QObject *parent /* = nullptr */)
    : QObject(parent)
    , m_map(new Map(BasemapStyle::ArcGISNavigationNight, this))
{}
/*---------------------DESTRUCTOR------------------------------*/
MapaBaseWeb::~MapaBaseWeb() {}

/*---------------------DECLARACION METODO DE VISTAS QML------------------------------*/
MapQuickView *MapaBaseWeb::mapView() const
{
    return m_mapView;
}


/*---------------------LLAMAMOS A NUESTRO METODO CREADO------------------------------*/

void MapaBaseWeb::configurarVista(){
    const Point center(-76.01,3.01, SpatialReference::wgs84());
    const Viewpoint viewpoint(center, 1000);

    m_mapView -> setViewpointAsync(viewpoint);

    Portal* portal = new Portal(this);

    const QString itemId("67f2e0584b6449c49204a311c831096f");
    PortalItem* portalItem = new PortalItem(portal, itemId, this);

    FeatureLayer* trailheadsLayer = new FeatureLayer(portalItem,0,this);

    m_map -> operationalLayers()-> append(trailheadsLayer);
}


/*---------------------DECLARACION METODO DE VISTAS------------------------------*/
// Set the view (created in QML)
void MapaBaseWeb::setMapView(MapQuickView *mapView)
{
    if (!mapView || mapView == m_mapView) {
        return;
    }

    m_mapView = mapView;
    m_mapView->setMap(m_map);
    configurarVista();
    emit mapViewChanged();
}

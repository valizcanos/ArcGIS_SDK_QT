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

#ifndef RUTACAPAS_H
#define RUTACAPAS_H

namespace Esri::ArcGISRuntime {
class Map;
class MapQuickView;
class Graphic;
class GraphicsOverlay;
class PictureMarkerSymbol;
class RouteTask;




} // namespace Esri::ArcGISRuntime


enum RouteBuilderStatus
{
    NotStarted,
    SelectedStart,
    SelectedStartAndEnd,
};



#include <QObject>

#include "RouteParameters.h"
class QAbstractListModel;
Q_MOC_INCLUDE("QAbstractListModel")
Q_MOC_INCLUDE("MapQuickView.h")

class RutaCapas : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Esri::ArcGISRuntime::MapQuickView *mapView READ mapView WRITE setMapView NOTIFY
                   mapViewChanged)
    Q_PROPERTY(QAbstractListModel* directions MEMBER m_directions NOTIFY directionsChanged)


public:
    explicit RutaCapas(QObject *parent = nullptr);
    ~RutaCapas() override;

signals:
    void mapViewChanged();
    void directionsChanged();


private:
    Esri::ArcGISRuntime::MapQuickView *mapView() const;
    void setMapView(Esri::ArcGISRuntime::MapQuickView *mapView);
    void localizacion();
    void setupRouteTask();
    void findRoute();
    void resetState();
    void CargarCapas();

    Esri::ArcGISRuntime::Map *m_map = nullptr;
    Esri::ArcGISRuntime::MapQuickView *m_mapView = nullptr;

    Esri::ArcGISRuntime::GraphicsOverlay* m_graphicsOverlay = nullptr;
    Esri::ArcGISRuntime::RouteTask* m_routeTask = nullptr;
    Esri::ArcGISRuntime::Graphic* m_startGraphic = nullptr;
    Esri::ArcGISRuntime::Graphic* m_endGraphic = nullptr;
    Esri::ArcGISRuntime::Graphic* m_lineGraphic = nullptr;
    QAbstractListModel* m_directions = nullptr;
    Esri::ArcGISRuntime::RouteParameters m_routeParameters;
    RouteBuilderStatus m_currentState;

};

#endif // RUTACAPAS_H

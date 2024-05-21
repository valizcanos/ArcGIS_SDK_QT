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

#ifndef MAPADEVISTAS_H
#define MAPADEVISTAS_H

namespace Esri::ArcGISRuntime {
class Map;
class MapQuickView;
class GraphicsOverlay; //Clase para dibujar vectores

} // namespace Esri::ArcGISRuntime

#include <QObject>

Q_MOC_INCLUDE("MapQuickView.h")

class MapaDeVistas : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Esri::ArcGISRuntime::MapQuickView *mapView READ mapView WRITE setMapView NOTIFY
                   mapViewChanged)

public:
    explicit MapaDeVistas(QObject *parent = nullptr);
    ~MapaDeVistas() override;
    Q_INVOKABLE QString tiempo();
    Q_INVOKABLE void cambiarVistasQML(QString vista);

signals:
    void mapViewChanged();

private:
    Esri::ArcGISRuntime::MapQuickView *mapView() const;
    void setMapView(Esri::ArcGISRuntime::MapQuickView *mapView);
    void cargarCapas();
    void createGraphics(Esri::ArcGISRuntime::GraphicsOverlay* overlay);
    double screenRatio() const;
    Esri::ArcGISRuntime::Map *m_map = nullptr;
    Esri::ArcGISRuntime::MapQuickView *m_mapView = nullptr;
    int m_rotationValue = 0;

};

#endif // MAPADEVISTAS_H

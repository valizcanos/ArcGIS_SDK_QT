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

#ifndef ADDFEATURESFEATURESERVICE_H
#define ADDFEATURESFEATURESERVICE_H

namespace Esri::ArcGISRuntime {
class FeatureLayer; //Nueva
class Map;
class MapQuickView;
class ServiceFeatureTable; //Nueva
} // namespace Esri::ArcGISRuntime

#include <QObject>

Q_MOC_INCLUDE("MapQuickView.h")

class AddFeaturesFeatureService : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Esri::ArcGISRuntime::MapQuickView *mapView READ mapView WRITE setMapView NOTIFY
                   mapViewChanged)

public:
    explicit AddFeaturesFeatureService(QObject *parent = nullptr);
    ~AddFeaturesFeatureService() override;

    static void init(); //Nueva

signals:
    void mapViewChanged();

private:
    Esri::ArcGISRuntime::MapQuickView *mapView() const;
    void setMapView(Esri::ArcGISRuntime::MapQuickView *mapView);
    void connectSignals();// Nueva
    Esri::ArcGISRuntime::Map *m_map = nullptr;
    Esri::ArcGISRuntime::MapQuickView *m_mapView = nullptr;
    Esri::ArcGISRuntime::FeatureLayer* m_featureLayer = nullptr; // Nueva
    Esri::ArcGISRuntime::ServiceFeatureTable* m_featureTable = nullptr; // Nueva
};

#endif // ADDFEATURESFEATURESERVICE_H

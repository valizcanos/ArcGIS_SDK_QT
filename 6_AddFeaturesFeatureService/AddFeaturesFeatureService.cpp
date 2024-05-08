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

#ifdef PCH_BUILD //Nueva
#include "pch.hpp" //Nueva
#endif // PCH_BUILD


#include "AddFeaturesFeatureService.h"



#include "Map.h"
#include "MapQuickView.h"
#include "MapTypes.h"




#include "Basemap.h" //Nueva
#include "Feature.h"
#include "FeatureEditResult.h"
#include "FeatureLayer.h"
#include "LayerListModel.h"
#include "Point.h"
#include "ServiceFeatureTable.h"
#include "SpatialReference.h"
#include "Viewpoint.h"
#include <QFuture>
#include <QMap>
#include <QMouseEvent>
#include <QUrl>
#include <QUuid>
#include <QVariant> //Nueva

using namespace Esri::ArcGISRuntime;


namespace //Nueva
{
// Convenience RAII struct that deletes all pointers in given container.
struct FeatureListResultLock
{
    FeatureListResultLock(const QList<FeatureEditResult*>& list) : results(list) { }
    ~FeatureListResultLock() { qDeleteAll(results); }
    const QList<FeatureEditResult*>& results;
};
}





AddFeaturesFeatureService::AddFeaturesFeatureService(QObject *parent /* = nullptr */)
    : QObject(parent)
    , m_map(new Map(BasemapStyle::ArcGISStreets, this))
{
    m_map->setInitialViewpoint(Viewpoint(Point(-10800000, 4500000, SpatialReference(102100)), 3e7)); //Nueva

    m_featureTable = new ServiceFeatureTable(QUrl("https://sampleserver6.arcgisonline.com/arcgis/rest/services/DamageAssessment/FeatureServer/0"), this);
    m_featureLayer = new FeatureLayer(m_featureTable, this); //Nueva
    m_map->operationalLayers()->append(m_featureLayer); //Nueva


}





AddFeaturesFeatureService::~AddFeaturesFeatureService() = default; //Nueva solo default


void AddFeaturesFeatureService::init() //Nueva
{
    // Register the map view for QML
    qmlRegisterType<MapQuickView>("Esri.Samples", 1, 0, "MapView");
    qmlRegisterType<AddFeaturesFeatureService>("Esri.Samples", 1, 0, "AddFeaturesFeatureServiceSample");
}





MapQuickView *AddFeaturesFeatureService::mapView() const
{
    return m_mapView;
}

// Set the view (created in QML)
void AddFeaturesFeatureService::setMapView(MapQuickView *mapView)
{
    if (!mapView || mapView == m_mapView) {
        return;
    }

    m_mapView = mapView;
    m_mapView->setMap(m_map);

    emit mapViewChanged();
    connectSignals(); //Nueva
}




void AddFeaturesFeatureService::connectSignals() //Nueva
{
    //! [AddFeaturesFeatureService add at mouse click]
    // connect to the mouse clicked signal on the MapQuickView
    connect(m_mapView, &MapQuickView::mouseClicked, this, [this](QMouseEvent& mouseEvent)
            {
                // obtain the map point
                const double screenX = mouseEvent.position().x();
                const double screenY = mouseEvent.position().y();
                Point newPoint = m_mapView->screenToLocation(screenX, screenY);

                // create the feature attributes
                QMap<QString, QVariant> featureAttributes;
                featureAttributes.insert("typdamage", "Minor");
                featureAttributes.insert("primcause", "Earthquake");

                // create a new feature and add it to the feature table
                Feature* feature = m_featureTable->createFeature(featureAttributes, newPoint, this);
                m_featureTable->addFeatureAsync(feature).then(this, [this]()
                                                              {
                                                                  // if add feature was successful, call apply edits
                                                                  m_featureTable->applyEditsAsync().then(this, [](const QList<FeatureEditResult*>& featureEditResults)
                                                                                                         {
                                                                                                             // Lock is a convenience wrapper that deletes the contents of the list once we leave scope.
                                                                                                             FeatureListResultLock lock(featureEditResults);

                                                                                                             if (lock.results.isEmpty())
                                                                                                                 return;

                                                                                                             // obtain the first item in the list
                                                                                                             FeatureEditResult* featureEditResult = lock.results.first();
                                                                                                             // check if there were errors, and if not, log the new object ID
                                                                                                             if (!featureEditResult->isCompletedWithErrors())
                                                                                                                 qDebug() << "New Object ID is:" << featureEditResult->objectId();
                                                                                                             else
                                                                                                                 qDebug() << "Apply edits error.";
                                                                                                         });
                                                              });
            });
    //! [AddFeaturesFeatureService add at mouse click]
}

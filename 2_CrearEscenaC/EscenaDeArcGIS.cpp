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

#include "EscenaDeArcGIS.h"

//#include "ArcGISTiledElevationSource.h"
//#include "ElevationSourceListModel.h"
//#include "MapTypes.h"
#include "Scene.h"
#include "SceneQuickView.h"
//#include "Surface.h"

#include <QUrl>

using namespace Esri::ArcGISRuntime;

EscenaDeArcGIS::EscenaDeArcGIS(QObject *parent /* = nullptr */)
    : QObject(parent){
    configuracionDeVista();
}

EscenaDeArcGIS::~EscenaDeArcGIS() {}

SceneQuickView *EscenaDeArcGIS::sceneView() const
{
    return m_sceneView;
}

// Set the view (created in QML)
void EscenaDeArcGIS::setSceneView(SceneQuickView *sceneView)
{
    if (!sceneView || sceneView == m_sceneView) {
        return;
    }

    m_sceneView = sceneView;
    m_sceneView->setArcGISScene(m_scene);

    emit sceneViewChanged();
}

void EscenaDeArcGIS::configuracionDeVista(){
    const QString item_id("90e563e4c62543099e4d447a9c20511d");
    const QUrl portal_url(QString("https://www.arcgis.com/sharing/rest/content/items/"+item_id));
    m_scene = new Scene(portal_url);
}

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

#include "MapaDeEscenas.h"

#include "ArcGISTiledElevationSource.h"
#include "ElevationSourceListModel.h"
#include "MapTypes.h"
#include "Scene.h"
#include "SceneQuickView.h"
#include "Surface.h"
#include "Camera.h" // Libreria adicional para trabajar con escenas
#include <QUrl>

using namespace Esri::ArcGISRuntime;

/*---------------------------------------------------------------------------*/
MapaDeEscenas::MapaDeEscenas(QObject *parent /* = nullptr */)
    : QObject(parent)
    , m_scene(new Scene(BasemapStyle::ArcGISImagery, this))
{
    // create a new elevation source from TopoBathy3D rest service
    ArcGISTiledElevationSource *elevationSource
        = new ArcGISTiledElevationSource(QUrl("https://elevation3d.arcgis.com/arcgis/rest/services/"
                                              "WorldElevation3D/TopoBathy3D/ImageServer"),
                                         this);

    // add the elevation source to the scene to display elevation
    m_scene->baseSurface()->elevationSources()->append(elevationSource);
    configuracionDeVistas();
}

/*---------------------------------------------------------------------------*/
MapaDeEscenas::~MapaDeEscenas() {}

/*---------------------------------------------------------------------------*/
SceneQuickView *MapaDeEscenas::sceneView() const
{
    return m_sceneView;
}

/*---------------------------------------------------------------------------*/
// Set the view (created in QML)
void MapaDeEscenas::setSceneView(SceneQuickView *sceneView)
{
    if (!sceneView || sceneView == m_sceneView) {
        return;
    }

    m_sceneView = sceneView;
    m_sceneView->setArcGISScene(m_scene);

    constexpr double latitud = 3.01;
    constexpr double longitud = -76.01;
    constexpr double altura = 50000;
    constexpr double angulo = 90;
    constexpr double pendiente = 0;
    constexpr double giro = 0;

    const Camera sceneCamara(latitud,longitud,altura,angulo,pendiente,giro);

    m_sceneView -> setViewpointCameraAndWait(sceneCamara);

    emit sceneViewChanged();
}

void MapaDeEscenas::configuracionDeVistas(){
    ArcGISTiledElevationSource* elevationSource =
        new ArcGISTiledElevationSource(QUrl("https://elevation3d.arcgis.com/arcgis/rest/services/WorldElevation3D/Terrain3D/ImageServer"), this);

    Surface* elevationSurface = new Surface(this);

    elevationSurface ->elevationSources() -> append(elevationSource);

    elevationSurface->setElevationExaggeration(3.5);

    m_scene-> setBaseSurface(elevationSurface);
};

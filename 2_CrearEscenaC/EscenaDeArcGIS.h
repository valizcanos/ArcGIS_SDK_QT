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

#ifndef ESCENADEARCGIS_H
#define ESCENADEARCGIS_H

namespace Esri::ArcGISRuntime {
class Scene;
class SceneQuickView;
} // namespace Esri::ArcGISRuntime

#include <QObject>

Q_MOC_INCLUDE("SceneQuickView.h")

class EscenaDeArcGIS : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Esri::ArcGISRuntime::SceneQuickView *sceneView READ sceneView WRITE setSceneView
                   NOTIFY sceneViewChanged)

public:
    explicit EscenaDeArcGIS(QObject *parent = nullptr);
    ~EscenaDeArcGIS() override;

signals:
    void sceneViewChanged();

private:
    Esri::ArcGISRuntime::SceneQuickView *sceneView() const;
    void setSceneView(Esri::ArcGISRuntime::SceneQuickView *sceneView);
    void configuracionDeVista();
    Esri::ArcGISRuntime::Scene *m_scene = nullptr;
    Esri::ArcGISRuntime::SceneQuickView *m_sceneView = nullptr;
};

#endif // ESCENADEARCGIS_H

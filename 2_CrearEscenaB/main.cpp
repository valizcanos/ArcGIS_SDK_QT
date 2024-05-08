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

#include "EscenaWeb.h"

#include "ArcGISRuntimeEnvironment.h"
#include "SceneQuickView.h"

#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>

//------------------------------------------------------------------------------

using namespace Esri::ArcGISRuntime;

int main(int argc, char *argv[])
{
#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
    // Linux requires 3.2 OpenGL Context
    // in order to instance 3D symbols
    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    fmt.setVersion(3, 2);
    QSurfaceFormat::setDefaultFormat(fmt);
#endif

    QGuiApplication app(argc, argv);

    // Use of Esri location services, including basemaps and geocoding, requires
    // either an ArcGIS identity or an API key. For more information see
    // https://links.esri.com/arcgis-runtime-security-auth.

    // 1. ArcGIS identity: An ArcGIS named user account that is a member of an
    // organization in ArcGIS Online or ArcGIS Enterprise.

    // 2. API key: A permanent key that gives your application access to Esri
    // location services. Create a new API key or access existing API keys from
    // your ArcGIS for Developers dashboard (https://links.esri.com/arcgis-api-keys).

    const QString apiKey = QString("AAPK1d767ca94cab40c38c6fea6cf92462d0JpfEcsGewRwnT0aXrD1dJrNvO-P0py0KdrB-XAMKHWTtOkxblTgtbDEHlF7JN2n-");
    if (apiKey.isEmpty()) {
        qWarning() << "Use of Esri location services, including basemaps, requires"
                   << "you to authenticate with an ArcGIS identity or set the API Key property.";
    } else {
        ArcGISRuntimeEnvironment::setApiKey(apiKey);
    }

    // Production deployment of applications built with ArcGIS Maps SDK requires you to
    // license ArcGIS Maps SDK functionality. For more information see
    // https://links.esri.com/arcgis-runtime-license-and-deploy.

    // ArcGISRuntimeEnvironment::setLicense("Place license string in here");

    // Register the scene view for QML
    qmlRegisterType<SceneQuickView>("Esri.escenaWeb", 1, 0, "SceneView");

    // Register the EscenaWeb (QQuickItem) for QML
    qmlRegisterType<EscenaWeb>("Esri.escenaWeb", 1, 0, "EscenaWeb");

    // Initialize application view
    QQmlApplicationEngine engine;

    // Add the import Path
    engine.addImportPath(QDir(QCoreApplication::applicationDirPath()).filePath("qml"));

    // Set the source
    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}

//------------------------------------------------------------------------------

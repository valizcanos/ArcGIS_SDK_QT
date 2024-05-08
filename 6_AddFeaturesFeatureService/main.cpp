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

#include "AddFeaturesFeatureService.h"

#include "ArcGISRuntimeEnvironment.h"

#include <QCommandLineParser> //Nueva
#include "MapQuickView.h"

#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>


#ifdef Q_OS_WIN //Nueva
#include <Windows.h> //Nueva
#endif //Nueva


//------------------------------------------------------------------------------

using namespace Esri::ArcGISRuntime;

int main(int argc, char *argv[])
{
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

    // Register the map view for QML
    qmlRegisterType<MapQuickView>("Esri.AddFeaturesFeatureService", 1, 0, "MapView");

    // Register the AddFeaturesFeatureService (QQuickItem) for QML
    qmlRegisterType<AddFeaturesFeatureService>("Esri.AddFeaturesFeatureService",
                                               1,
                                               0,
                                               "AddFeaturesFeatureService");

    // Initialize application view
    QQmlApplicationEngine engine;

    // Add the import Path
    engine.addImportPath(QDir(QCoreApplication::applicationDirPath()).filePath("qml"));

    // Set the source
    engine.load(QUrl("qrc:/qml/main.qml"));

    return app.exec();
}



void setAPIKey(const QGuiApplication& app, QString apiKey) //Nueva
{
    if (apiKey.isEmpty())
    {
        // Try parsing API key from command line argument, which uses the following syntax "-k <apiKey>".
        QCommandLineParser cmdParser;
        QCommandLineOption apiKeyArgument(QStringList{"k", "api"}, "The API Key property used to access Esri location services", "apiKeyInput");
        cmdParser.addOption(apiKeyArgument);
        cmdParser.process(app);

        apiKey = cmdParser.value(apiKeyArgument);

        if (apiKey.isEmpty())
        {
            qWarning() << "Use of Esri location services, including basemaps, requires" <<
                "you to authenticate with an ArcGIS identity or set the API Key property.";
            return;
        }
    }

    Esri::ArcGISRuntime::ArcGISRuntimeEnvironment::setApiKey(apiKey);
}

//------------------------------------------------------------------------------

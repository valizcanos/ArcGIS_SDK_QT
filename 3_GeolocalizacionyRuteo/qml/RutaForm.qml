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

import QtQuick
import QtQuick.Controls
import Esri.Ruta
//---------------------------------
import QtQuick.Shapes
//---------------------------------
Item {

    // Create MapQuickView here, and create its Map etc. in C++ code
    MapView {
        id: view
        anchors.fill: parent
        // set focus to enable keyboard navigation
        focus: true
    }

    // Declare the C++ instance which creates the map etc. and supply the view
    Ruta {
        id: model
        mapView: view
    }



    // Create window for displaying the route directions.
        Rectangle {
            id: directionWindow
            anchors {
                right: parent.right
                top: parent.top
                margins: 5
            }

            radius: 5
            visible: model.directions
            width: Qt.platform.os === "ios" || Qt.platform.os === "android" ? 250 : 350
            height: parent.height / 2
            color: "#FBFBFB"
            clip: true

            ListView {
                id: directionsView
                anchors {
                    fill: parent
                    margins: 5
                }
                header: Component {
                    Text {
                        height: 40
                        text: "Directions:"
                        font.pixelSize: 22
                    }
                }

                // Set the model to the DirectionManeuverListModel returned from the route.
                model: model.directions
                delegate: directionDelegate
            }
        }

        Component {
            id: directionDelegate
            Rectangle {
                id: rect
                width: parent.width
                height: textDirections.height
                color: directionWindow.color

                // separator for directions
                Shape {
                    height: 2
                    ShapePath {
                        strokeWidth: 1
                        strokeColor: "darkgrey"
                        strokeStyle: ShapePath.SolidLine
                        startX: 20; startY: 0
                        PathLine { x: parent.width - 20 ; y: 0 }
                    }
                }

                Text {
                    id: textDirections
                    text: qsTr("%1 (%2 miles)".arg(directionText).arg((length * 0.00062137).toFixed(2)))
                    wrapMode: Text.WordWrap
                    anchors {
                        leftMargin: 5
                        left: parent.left
                        right: parent.right
                    }
                }
            }
        }

}

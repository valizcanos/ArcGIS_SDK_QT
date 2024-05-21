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
import Esri.mapaDeVistas

Item {

    // Create MapQuickView here, and create its Map etc. in C++ code
    MapView {
        id: view
        anchors.fill: parent
        // set focus to enable keyboard navigation
        focus: true

        Timer{
                    running: true
                    repeat: true
                    interval: 1000
                    onTriggered: horaActual.text=model.tiempo()

                }

                Text {
                    id: horaActual
                    color: "#222929"
                    text: qsTr("")
                    font.bold: true
                    font.pointSize: 30
                    styleColor: "#f7f3f3"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    style: Text.Sunken
                    //font.pointSize: 20
                    //anchors.fill: parent
                    font.pixelSize: ApplicationWindow.width/100*4
                    x:610
                    y:20
                }

                MouseArea{
                    anchors.fill: close
                    onClicked: Qt.quit()
                }


                Rectangle{
                    id: rectangulo
                    color: "black"
                    border.color: "white"
                    anchors.fill: close
                }
                Text {
                    id: close
                    color: "#d906e8"
                    text: qsTr("Cerrar")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    x:610
                    y:100
                }

    }

    //Cuadro de opciones
    ComboBox {
                id: comboBoxViewpoint
                anchors {
                    left: parent.left
                    top: parent.top
                    margins: 15
                }

                // Add a background to the ComboBox
                Rectangle {
                    anchors.fill: parent
                    radius: 10
                    // Make the rectangle visible if a dropdown indicator exists
                    // An indicator only exists if a theme is set
                    visible: parent.indicator
                    border.width: 1
                }
                property int bestWidth: implicitWidth
                width: bestWidth + rightPadding + leftPadding + 20
                model: [ "Center", "Center and scale", "Geometry","Geometry and padding", "Rotation","Scale 1:5,000,000",
                    "Scale 1:10,000,000" ]

                onCurrentTextChanged: {
                            // Call C++ invokable function to change the viewpoint
                            model.cambiarVistasQML(comboBoxViewpoint.currentText)}

        }




    // Declare the C++ instance which creates the map etc. and supply the view
    MapaDeVistas {
        id: model
        mapView: view
    }
}

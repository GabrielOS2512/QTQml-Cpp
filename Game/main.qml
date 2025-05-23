﻿import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.3
import GPartida 1.0
import GRodadaModel 1.0

ApplicationWindow {
    id: root
    width: 200; height: 200
    visible: true

    GPartida {
        id: idPartida;
    }
    GRodadaModel {
        id: idRodadaModel;
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Button {
            height: 40
            width: 200
            text: qsTr("Race Game")

            onClicked: {
                var component = Qt.createComponent("RaceGame.qml")
                var window = component.createObject(root, {'width':root.width,
                                                    'height':root.height
                                                    })
                window.show()
            }
        }

        Button {
            height: 40
            width: 200
            text: qsTr("Futebol")

            onClicked: {
                var component = Qt.createComponent("Futebol.qml")
                var window = component.createObject(root)
                window.show()
            }
        }
    }
}

import QtQuick 2.15
import QtQuick.Window 2.15
import "utils/scripts.js" as JS

Window {
    width: 1160
    height: 680
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent
        color: "grey"

        Rectangle {
            id: gamePiece
            anchors.centerIn: parent
            width: 15
            height: 28
            color: "blue"
        }
    }
}

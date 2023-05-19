import QtQuick 2.0

Rectangle {
    id: sprite
    property int morale: 0
    property int atk: 0
    property int def: 0
    property int speed: 0
    property real hp: 0.0
    property alias unit: sprite

    width: 60
    height: 25
    color: "red"
    border.color: "black"

    MouseArea {
        anchors.fill: parent
        drag {
            target: parent
            minimumX: 0
            minimumY: 0
            maximumX: parent.parent.width - parent.width
            maximumY: parent.parent.height - parent.height
            smoothed: true
        }
    }
}

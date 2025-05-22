import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Window 2.3
import 'components'

ApplicationWindow {
    visible: true
    title: qsTr("Futebol")
    color: "blue"
    width: 200; height: 200

    property int currentTick: 0

    Component.onCompleted: {
        idPartida.iniciarPartida();
    }

}

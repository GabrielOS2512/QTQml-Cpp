import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Window 2.3
import QtQuick.Layouts 1.15
import 'components'

ApplicationWindow {
    visible: true
    title: qsTr("Futebol")
    color: "green"
    width: 200; height: 200

    GridView {
        id: grid
        anchors.fill: parent
        cellWidth: 100; cellHeight: 30
        model: ["cruzeiro ", "vasco"]
        delegate: partidaDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }


    Component {
        id: partidaDelegate
        Item {
            width: grid.cellWidth; height: grid.cellHeight
            RowLayout {
                anchors.fill: parent
                spacing: 2
                Rectangle {
                    id: nomeTimeARect
                    Layout.preferredWidth: 40
                    Layout.preferredHeight: 24
                    color: "blue"

                    Text {
                        text: nome
                        color: "white"
                        font.pixelSize: 16
                    }
                }
                Rectangle {
                    id: placarTimeARect
                    Layout.preferredWidth: 10
                    Layout.preferredHeight: 24
                    color: "white"

                    Text {
                        text: nome
                        color: "black"
                        font.pixelSize: 16
                    }
                }

                Text {
                    text: "x"
                }


                Rectangle {
                    id: placarTimeBRect
                    Layout.preferredWidth: 10
                    Layout.preferredHeight: 24
                    color: "white"

                    Text {
                        text: nome
                        color: "black"
                        font.pixelSize: 16
                    }
                }

                Rectangle {
                    id: nomeTimeBRect
                    Layout.preferredWidth: 40
                    Layout.preferredHeight: 24
                    color: "red"

                    Text {
                        text: nome
                        color: "black"
                        font.pixelSize: 16
                    }
                }

            }
        }
    }
}

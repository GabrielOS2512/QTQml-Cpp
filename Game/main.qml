import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Window 2.3
import 'components'

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Race")
    color: "green"
    visibility: Window.Maximized

    property int currentTick: 0

    Item {
        anchors.fill: parent
        focus: true
        Keys.onPressed: {
            if(event.isAutoRepeat) return
            switch(event.key) {
            case Qt.Key_Left:
                car.isLeft = true
                break;
            case Qt.Key_Up:
                car.isUp = true
                break;
            case Qt.Key_Down:
                car.isDown = true
                break;
            case Qt.Key_Right:
                car.isRight = true
                break;
            }
        }
        Keys.onReleased: {
            if(event.isAutoRepeat) return
            switch(event.key) {
            case Qt.Key_Left:
                car.isLeft = false
                break;
            case Qt.Key_Up:
                car.isUp = false
                break;
            case Qt.Key_Down:
                car.isDown = false
                break;
            case Qt.Key_Right:
                car.isRight = false
                break;
            }
        }
    }

    Text {
        z: 100
        x: 0
        y: 0
        text: "Tick: " + currentTick
    }

    Column {
        z: 100
        x: 0
        y: 30
        Label {
            text: "Speed: " +car.speed
        }
        Label {
            text: "Delta: " +car.delta
        }
        Label {
            text:"Fuel: " + ((car.fuel) * 100).toFixed(2) +"%"
        }
        Label {
            text: "Tyres: " + ((car.tyres) * 100).toFixed(2) + "%";
        }
        Label {
            text: "Laps: " + (car.currentLap) + "/12";
            font.bold: true
        }
        Label {
            text: "Lap Time: " + car.lapTime;
            font.bold: true
        }

    }

    function renderTick() {
        currentTick++
        canvas.drawBackgroud()
        car.newPosition()
        car.rotation += car.moveAngle

        const context = canvas.getContext('2d');
        // Get the clicked pixel position
        const x = car.x;
        const y = car.y;

        // Get the color data of the clicked pixel
        const pixelData = context.getImageData(x, y, 2, 6).data;

        // Extract the RGB values
        const red = pixelData[0];
        const green = pixelData[1];
        const blue = pixelData[2];

        // Log the RGB color values
        let colors = red + green + blue

        if (colors > 50) {
            car.colision()
        }
    }

    Canvas {
        id: canvas
        width: parent.width - 100
        height: parent.height
        y:0
        x: 100
        property real positionX: 0
        property real positionY: 0

        function drawBackgroud() {
            const context = canvas.getContext('2d');
            context.drawImage(image.source, positionX, positionY, canvas.width, canvas.height);
        }

        Car {
            id: car
            x: 100
            y: 500
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                rendererTimer.start()
            }
        }
    }

    Timer {
        id: rendererTimer
        interval: 20
        repeat: true
        onTriggered: {
            car.action()
            renderTick()
        }
    }

    Image {
        id: image
        anchors.centerIn: parent
        source: "img/image.png"
        visible: false
    }
}

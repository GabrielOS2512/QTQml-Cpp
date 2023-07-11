import QtQuick 2.0

Rectangle {
    id: car
    color: "transparent"
    width: 16
    height: 28

    /// Speed Properties
    property real speed: 0;
    property real maxSpeed: 6;
    property real minSpeed: -2;
    property real delta: 0; // speed variation
    property real acceleration: 0.001;
    property real maxAcceleration: 0.05;
    property real braking: 0.2;
    /// Stearing
    property real angle: 0;
    property real moveAngle: 0;
    /// Car condition
    property real hp: 100;
    property real tyres: 1.0;
    property real fuel: 0.3;
    /// Time and Lap
    property string lapTime
    property int currentLap: 1

    /// Actions
    property bool isUp: false
    property bool isDown: false
    property bool isRight: false
    property bool isLeft: false
    signal action

    enum TyreType {
        SOFT = 1,
        MEDIUM = 2,
        HARD = 3
    }

    onAction: {
        car.moveAngle = 0
        if(isUp) {
            accelerate()
        }
        if(isDown) {
            breake()
        }
        if(!isUp && !isDown) {
            idle()
        }
        if(isLeft) {
            turn(-1)
        }
        if(isRight) {
            turn(1)
        }
    }

    function accelerate() {
        if (delta < 0)
            delta = 0;

        if (delta > maxAcceleration)
            delta = maxAcceleration
        else
            delta += acceleration

        fuel -= 0.00008
        tyres -= 0.00000
    }

    function breake() {
        if (speed > 0.1) {
            speed -= braking
            tyres -= 0.0003
        } else if (speed < -0.1) {
            speed += braking
            tyres -= 0.0003
        } else
            speed = 0
    }

    function turn(direction) {
        if (speed == 0) {
            moveAngle = 0
        } else if (speed <= 1) {
            moveAngle = 1 * direction
            tyres -= 0.00002
        } else if (speed <= 2) {
            moveAngle = 2 * direction
            tyres -= 0.00003
        } else if (speed <= 3) {
            moveAngle = 3.5 * direction
            tyres -= 0.00005
        } else {
            moveAngle = 3 * direction
            tyres -= 0.0004
        }

        moveAngle = moveAngle * tyres
    }

    function idle() {
        if (speed > 0.5) {
            delta -= 0.004
        }/* else if (speed < -0.1) {
            //speed += 0.01
            delta += 0.01
        }*/ else {
            speed = 0
            delta = 0
        }
    }

    function newPosition() {
        if (delta !== 0)
            speed += delta

        if (speed > maxSpeed) {
            speed = maxSpeed;
        } else if (speed < minSpeed) {
            speed = minSpeed;
        }

        angle += moveAngle * Math.PI / 180;
        x += (speed) * Math.sin(angle);
        y -= (speed) * Math.cos(angle)
    }

    function colision() {
        speed = 1
        delta = 0
    }

    function refuel() {
        fuel = 1.0
    }

    function changeTyres() {
        tyres = 1.0
    }

    function crossedLine() {
        lapTimer.counter = 0
        if(currentLap <= 12)
            currentLap++;
        else
            finished()
    }

    Timer {
        id: lapTimer
        property int counter: 0
        interval: 11; running: true; repeat: true
        onTriggered: {
            counter += 11
            lapTime = new Date(counter).toLocaleTimeString(Qt.locale(), "mm:" + "ss:" + "zzz")
        }
    }

    Image {
        anchors.fill: parent
        source: "../img/cars/car1.png"
    }
}

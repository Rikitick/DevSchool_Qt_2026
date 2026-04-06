import QtQuick 2.15
import QtQuick.Controls

Window {
    id: window
    width: 300
    height: 600
    visible: true
    title: "Snowflakes"

    property bool gameOver: false
    property int sizeBtn: 40
    property int fps: 16
    property int minSpeed: 1
    property int maxSpeed: 3
    property int minAppearance: 100
    property int maxAppearance: 1000


    Item {
        id: area
        Timer {
            interval: minAppearance + Math.random() * (maxAppearance - minAppearance)
            running: true
            repeat: true
            onTriggered: {
                comp.createObject(area, {
                    "x": Math.random() * (window.width - sizeBtn),
                    "y": Math.random() * 100,
                    "speed": minSpeed + Math.random() * maxSpeed,
                })
                interval = minAppearance + Math.random() * (maxAppearance - minAppearance)
            }
        }
    }

    Component {
        id: comp
        Button {
            id: btn
            text: "*"
            width: sizeBtn
            height: sizeBtn

            property double speed: 0.0

            onClicked: btn.destroy()

            Timer {
                interval: fps
                running: true
                repeat: true
                onTriggered: {
                    btn.y += speed

                    if (btn.y + btn.height >= window.height) {
                        color = "red"
                        title = 'you LOSE!!!'
                    }
                }
            }
        }
    }
}

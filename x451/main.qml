import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import "QML/Common"

BaseUI {
    id: mWindow
    width: 800
    height: 480

    Rectangle{
        id:mainContent
        width: 800
        height: 480
        color: "blue"

        Item{
            id:tunerDish
            objectName: "TunerDish"
            anchors.fill: parent
            visible: false
        }

        Item{
            id:homeDish
            objectName: "HomeDish"
            anchors.fill: parent
            visible: false
        }

    }

        states:[
            State {
                name: "Home";
                PropertyChanges { target: homeDish; visible:true }
                PropertyChanges { target: tunerDish; visible:false }
            },
            State {
                name: "Tuner"
                PropertyChanges { target: tunerDish; visible: true }
                PropertyChanges { target: homeDish; visible:false }
            }
        ]

    onDataReceived: {
        cppUIBase.qmlLog("Main onDataReceived: name: " + name + " name:" + data)
    }

}

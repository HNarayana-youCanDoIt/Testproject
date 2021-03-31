import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common/"

BaseUI{
    id:setupMain

    onDataReceived: {
        cppUIBase.qmlLog("SetupMain onDataReceived: name: " + name + " name:" + data)
        if(name == "App_Setup")
        {
            setupMain.state = data
        }
        else
        {
            setupLoader.item.dataReceived(name,data);
        }
    }

    Loader {
        id: setupLoader
        objectName: "SetupLoader"
        anchors.fill: parent
        source:""
    }

    Connections{
        target: setupLoader.item
        ignoreUnknownSignals: true
        onSendData:{
            setupMain.sendData(name,data);
        }
    }

    states: [
        State { name: "SetupMain";   PropertyChanges{ target: setupLoader; source: "qrc:/QML/Setup/SetupScreen.qml"} }
    ]
}

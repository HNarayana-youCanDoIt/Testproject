import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common/"

BaseUI{
    id:startupAnimMain
    state:"StartupAnimMain"
    onDataReceived: {
        cppUIBase.qmlLog("App_StartupANim onDataReceived: name: " + name + " name:" + data)
        if(name == "App_StartupAnim")
        {
            startupAnimMain.state = data
        }
        else
        {
            startupAnimLoader.item.dataReceived(name,data);
        }
    }

    Loader {
        id: startupAnimLoader
        objectName: "StartupAnimLoader"
        anchors.fill: parent
        source:""
    }

    Connections{
        target: startupAnimLoader.item
        ignoreUnknownSignals: true
        onSendData:{
            startupAnimMain.sendData(name,data);
        }
    }

    states: [
        State { name: "StartupAnimMain";                       PropertyChanges{ target: startupAnimLoader; source: "qrc:/QML/StartupAnim/StartupAnimMain.qml"} }
    ]
}

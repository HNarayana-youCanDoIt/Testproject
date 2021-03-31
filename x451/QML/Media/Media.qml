import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common/"

BaseUI{
    id:mediaMain

    onDataReceived: {
        cppUIBase.qmlLog("MediaMain onDataReceived: name: " + name + " name:" + data)
        if(name == "App_Media")
        {
            mediaMain.state = data
        }
        else
        {
            mediaLoader.item.dataReceived(name,data);
        }
    }

    Loader {
        id: mediaLoader
        objectName: "MediaLoader"
        anchors.fill: parent
        source:""
    }

    Connections{
        target: mediaLoader.item
        ignoreUnknownSignals: true
        onSendData:{
            mediaMain.sendData(name,data);
        }
    }

    states: [
        State { name: "MediaMain";   PropertyChanges{ target: mediaLoader; source: "qrc:/QML/Media/MediaScreen.qml"} }
    ]
}

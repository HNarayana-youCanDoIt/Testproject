import QtQuick 2.7
import "../../Common"
import com.harman.qml.popupenums 1.0
import QtGraphicalEffects 1.0

Item {
    id: idNotificationPopupItem
    property var notifyQmlFileName: null

    width: 390
    height: 50

    Connections {
        target: PopupManager
        onSigShowNotificationPopup: {
            cppDrawersApp.qmlLog("HeaderNotificationContainerComponent : SigShowNotificationPopup received")
            notifyQmlFileName = strNotificationQmlFileName
            idNotificationPopupLoader.source = strNotificationQmlFilePath
            PopupManager.bNotificationVisible = true;
        }
    }

    Connections{
        target: PopupManager
        onSigCloseNotificationPopup: {
            cppDrawersApp.qmlLog("HeaderNotificationContainerComponent : SigCloseNotificationPopup received")
            idNotificationPopupLoader.source = ""
            cppIntrospectionAdaptor.invSetPopupChanged("No Popup")
            PopupManager.bNotificationVisible = false;
        }
    }

    Loader{
        id: idNotificationPopupLoader

        anchors {
            fill: parent
            verticalCenter: parent.verticalCenter
        }

        source: ""

        onSourceChanged: {
            cppDrawersApp.qmlLog("HeaderNotificationContainerComponent: idNotificationPopupLoader Source Changed: "+ source)
        }

        onStatusChanged:
        {
            if (idNotificationPopupLoader.status === Loader.Ready) {

                //Set objectName
                idNotificationPopupLoader.item.objectName = notifyQmlFileName
                cppIntrospectionAdaptor.invSetPopupChanged(idNotificationPopupLoader.item.objectName)
            }
        }
    }
}

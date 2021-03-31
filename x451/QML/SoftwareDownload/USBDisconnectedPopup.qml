import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"
import com.harman.qml.thememanager 1.0

NoButtonPopup {
    prPopupTitle: qsTr("Error") + cppThemeMgr.languageChanged
    prPopupText: qsTr("USB Disconnected!") + cppThemeMgr.languageChanged

    onClosed: {
        cppSoftwareUpdateAdaptor.busyIndicatorVisibility = false
        cppSoftwareUpdateApp.raiseSMEvent("activateBack", "usbDisconnect")
    }
}

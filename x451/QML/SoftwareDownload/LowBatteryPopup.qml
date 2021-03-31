import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NoButtonPopup {
    prPopupTitle: qsTr("Warning") + cppThemeMgr.languageChanged
    prPopupText: qsTr("Low Battery!! \nSoftware cannot be Updated.") + cppThemeMgr.languageChanged

    onOpened: {
        cppSoftwareUpdateAdaptor.busyIndicatorVisibility = false
    }
}

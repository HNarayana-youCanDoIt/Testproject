import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NoButtonPopup{
    prPopupTitle: qsTr("Warning") + cppThemeMgr.languageChanged
    prPopupText:  qsTr("Turn IGN OFF to Download Software.") + cppThemeMgr.languageChanged

    onClosed: {
        cppSoftwareUpdateAdaptor.busyIndicatorVisibility = false
    }
}

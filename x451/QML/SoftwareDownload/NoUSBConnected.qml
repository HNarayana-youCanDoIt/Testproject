import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NoButtonPopup{
    prPopupTitle: qsTr("Error") + cppThemeMgr.languageChanged
    prPopupText:  qsTr("No USB Connected.")  + cppThemeMgr.languageChanged

    onClosed: {
        cppSoftwareUpdateAdaptor.busyIndicatorVisibility = false
    }
}

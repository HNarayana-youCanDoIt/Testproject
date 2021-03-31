import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"
import com.harman.qml.thememanager 1.0

NoButtonPopup {
    prPopupTitle: qsTr("Error") + cppThemeMgr.languageChanged
    prPopupText: qsTr("TEXT_SWDL_POPUP_ISO_CORRUPTED_TEXT") + cppThemeMgr.languageChanged

    onOpened: {
        cppSoftwareUpdateAdaptor.busyIndicatorVisibility = false
    }
}

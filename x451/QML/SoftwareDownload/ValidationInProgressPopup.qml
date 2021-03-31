import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"
import "../Common"
import com.harman.qml.thememanager 1.0

NoButtonPopup {

    prPopupTitle: qsTr("Authentication in Progress") + cppThemeMgr.languageChanged

    BusyIndicator {
        visible: true
        anchors {
            top: parent.top
            topMargin: 160
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
    }

    onClosed: {
        cppSoftwareUpdateAdaptor.invShowErrorMessage(0)
    }
}

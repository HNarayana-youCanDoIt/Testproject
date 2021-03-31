import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"
import "../Common"
import com.harman.qml.thememanager 1.0

OneButtonPopup {

    prPopupTitle: qsTr("Software Validation") + cppThemeMgr.languageChanged
    prPopupText: qsTr("Software mismatch in infotainment system is detected. \n Tap OK to update.")
                 + cppThemeMgr.languageChanged
    prBtnText: qsTr("OK") + cppThemeMgr.languageChanged
    prBtnEnable: (cppSoftwareUpdateAdaptor.swUpdateAvailability
                  && (!busyInd.visible))
    BusyIndicator {
        id: busyInd
        scale: 0.5
        visible: !prBtnVisible
        anchors {
            top: parent.top
            left: parent.left
            topMargin: 200
            leftMargin: 225
        }
    }

    onBtnReleased: {
        if (0 === cppSoftwareUpdateAdaptor.invErrorVerMismatchUpdate()) {
            prPopupText = qsTr("Turn IGN OFF and then click OK to Update the Software.") + cppThemeMgr.languageChanged
        } else if(1 === cppSoftwareUpdateAdaptor.invErrorVerMismatchUpdate()){
            prPopupText = qsTr("Low Battery!! \nSoftware cannot be Updated.") + cppThemeMgr.languageChanged
        }
        else{
            prBtnVisible = false
            busyInd.visible = !prBtnVisible
            cppVersionManagerAdaptor.callSwUpdateOnVerMismatch()
        }
    }
}

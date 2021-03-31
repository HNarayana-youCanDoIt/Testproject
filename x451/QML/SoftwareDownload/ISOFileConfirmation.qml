import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0

import "../Common/Popup"


/////////////////////////////////////////////////////////////////////////////////
TwoButtonPopup {

    /**
      * Text to be displayed on Popup
      */
    prPopupText: qsTr("Do you want to start the reflash now?") + cppThemeMgr.languageChanged

    /**
      * Title to be displayed on Popup
      */
    prPopupTitle: cppSoftwareUpdateAdaptor.selectedISOName

    /**
      * Text to be displayed on first button
      */
    prFirstBtnText: qsTr("Yes") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on second button
      */
    prSecondBtnText: qsTr("No") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased: {
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_IMAGE_CONFIRMATION)
        PopupManager.showPopup(PopupEnum.EN_POPUPID_VALIDATION_IN_PROGRESS)
        cppSoftwareUpdateApp.qmlLog("ISOFileConfirmation.qml - Yes btn clicked")
        cppSoftwareUpdateAdaptor.busyIndicatorVisibility = false
        cppSoftwareUpdateAdaptor.requestInstallPackageAttribute(
                    cppSoftwareUpdateAdaptor.selectedISOIndex)
    }

    onSigSecondBtnReleased: {
        cppSoftwareUpdateApp.qmlLog("ISOFileConfirmation.qml - No btn clicked")
        cppSoftwareUpdateAdaptor.busyIndicatorVisibility = false
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_IMAGE_CONFIRMATION)
    }
}

/**
 * @file            DnResetTripBConfirmationPopup.qml
 * @ingroup         QmlPopup
 * @author          Nandkishor Lokhande
 * DnResetTripBConfirmationPopup, a popup can use to ask DriveNext trip B reset confirmation,
 * It has Message field, OK and CANCEL buttons.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import com.harman.qml.driveNextenums 1.0
import "../../Common/Popup"

TwoButtonPopup
{
    /**
      * Message Text to be displayed on Popup
      */
    prPopupText: qsTr("TEXT_DN_POPUP_RESET_TRIP_B_CONFIRMATION") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on first button
      */
    prFirstBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_OK_LABEL") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on second button
      */
    prSecondBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_CANCEL_LABEL") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased:
    {
        cppSetupApp.qmlLog("DriveNext Trip B RESET CONFIRMATION:: OK")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_DN_RESET_TRIP_B_CONFIRMATION)
        cppDriveNextAdaptor.resetDriveNextTrip(DriveNextEnums.DRIVENEXT_TRIP_B)
    }

    onSigSecondBtnReleased:
    {
        cppSetupApp.qmlLog("DriveNext Trip B RESET CONFIRMATION:: Cancel")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_DN_RESET_TRIP_B_CONFIRMATION)
    }
}

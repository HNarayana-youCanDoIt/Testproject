import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../Common/Popup"

TwoButtonPopup
{
    /**
      * Title to be displayed on Popup
      */
    prPopupTitle: qsTr("TEXT_POPUP_DELETE_DEVICE_TITLE") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on Popup
      */
    prPopupText: qsTr("TEXT_POPUP_DELETE_ALL_DEVICES_CONFIRM_MSG") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on first button
      */
    prFirstBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_YES_LABEL") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on second button
      */
    prSecondBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_NO_LABEL") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased:
    {
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_CONFIRMATION)
        PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_DELETING_ALL_DEVICES)
        cppPhoneAdaptor.invDeleteAllDevices()
    }

    onSigSecondBtnReleased:
    {
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_CONFIRMATION)
    }
}


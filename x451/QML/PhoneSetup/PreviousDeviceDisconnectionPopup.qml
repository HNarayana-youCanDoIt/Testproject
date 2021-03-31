import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../Common/Popup"

TwoButtonPopup
{
    /**
      * Text to be displayed on Popup
      */
    prPopupText: qsTr("TEXT_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION").arg(cppUIBase.invTruncateText(cppPhoneAdaptor.connectedDeviceName,20)) + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on first button
      */
    prFirstBtnText: qsTr("TEXT_GLOBAL_PROCEED") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on second button
      */
    prSecondBtnText: qsTr("TEXT_HOME_POPUP_CANCEL_BTN") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased:
    {        
        PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_CONNECTING)
        cppPhoneAdaptor.invStartAllServiceConnection(cppPhoneAdaptor.selItemBtAddr)
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION)
    }

    onSigSecondBtnReleased:
    {
        cppPhoneAdaptor.invResetSelectedItemInfo()
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION)        
    }
}

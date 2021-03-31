import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../Common/Popup"

TwoButtonPopup
{
    /**
      * Title to be displayed on Popup
      */
    // TODO: Popup string id should be added instead of static text.
    prPopupTitle: qsTr("Pass Key:\"%1\"").arg(cppPhoneAdaptor.passKeyPin) + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on Popup
      */
    prPopupText: qsTr("TEXT_PHONE_SETUP_EXTERNAL_PAIRING").arg(cppPhoneAdaptor.passKeyPin).arg(cppUIBase.invTruncateText(cppPhoneAdaptor.selItemName,20)) + cppThemeMgr.languageChanged

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
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_SETUP_EXTERNAL_PAIRING_REQUEST)
        //Show connecting popup
        PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_CONNECTING)
        cppPhoneAdaptor.invBondingReply(true, true)
    }

    onSigSecondBtnReleased:
    {
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_SETUP_EXTERNAL_PAIRING_REQUEST)
        cppPhoneAdaptor.invBondingReply(false, true)
    }
}

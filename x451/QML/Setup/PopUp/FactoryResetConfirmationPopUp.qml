import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../../Common/Popup"

TwoButtonPopup
{
    /**
      * Text to be displayed on Popup
      */
    prPopupText: qsTr("TEXT_SETUP_FACTORY_RESET_CONFIRMATION") + cppThemeMgr.languageChanged


    /**
      * Text to be displayed on first button
      */
    // TODO: Popup string id should be added instead of static text.
    prFirstBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_YES_LABEL") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on second button
      */
    // TODO: Popup string id should be added instead of static text.
    prSecondBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_NO_LABEL") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased:
    {
        cppSetupApp.qmlLog("FACTORY RESET CONFIRMATION:: YES")
        cppSetupAdaptor.factoryResetConfirmClickProcess()
    }

    onSigSecondBtnReleased:
    {
        cppSetupApp.qmlLog("FACTORY RESET CONFIRMATION:: NO")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_SETUP_FACTORY_RESET_CONFIRMATION_STATUS)
    }
}


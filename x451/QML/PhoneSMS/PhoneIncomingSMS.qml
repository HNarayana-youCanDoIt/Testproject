import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import com.harman.qml.thememanager 1.0
import "../Common/Popup"

ThreeButtonPopup {

    Connections
    {
        target: PopupManager
        onSigProcessHKOnPopup: {
            cppUIBase.qmlLog("onSigProcessHKOnPopup : slot called")
            PopupManager.invSetHKHandledStatus(cppPhoneAdaptor.invHandleHardKeys(iKey, iKeyState))
        }
    }

    //Property to hold sms sender name
    property string prSmsSenderName: (cppPhoneAdaptor.smsSenderName != "") ? cppPhoneAdaptor.smsSenderName : cppPhoneAdaptor.smsSenderNumber

    /**
      * Text to be displayed on Popup
      */
    prPopupText: prSmsSenderName + cppThemeMgr.languageChanged

    /**
      * Title to be displayed on Popup
      */
    prPopupTitle: qsTr("TEXT_PHONE_NEW_MESSAGE") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on first button
      */
    prFirstBtnText: qsTr("TEXT_PHONE_SMS_READOUT") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on second button
      */
    prSecondBtnText: qsTr("TEXT_PHONE_CALL") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on third button
      */
    prThirdBtnText: (cppW3WAdaptor.isTextInW3WAddressFormat(cppPhoneAdaptor.smsData) ?
                        qsTr("TEXT_GENERIC_POPUP_BTN_NAVIGATE_LABEL") :
                        qsTr("TEXT_GENERIC_POPUP_BTN_CANCEL_LABEL")) + cppThemeMgr.languageChanged


    //enable call button only when contact number is available
    prSecondBtnEnable: (cppPhoneAdaptor.smsSenderNumber !== "")

    onFirstBtnReleased: {
        cppPhoneApp.qmlLog("PhoneIncomingSMS.qml: onFirstBtnReleased")
        prFirstBtnEnable = false
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_INCOMING_SMS_POPUP)
        cppPhoneAdaptor.invStartSmsReadout()
    }

    onSecondBtnReleased: {
        cppPhoneApp.qmlLog("PhoneIncomingSMS.qml: onSecondBtnReleased")
        prSecondBtnEnable = false
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_INCOMING_SMS_POPUP)
        cppPhoneAdaptor.invDial(cppPhoneAdaptor.smsSenderNumber, cppPhoneAdaptor.smsSenderName)
    }

    onThirdBtnReleased: {
        cppPhoneApp.qmlLog("PhoneIncomingSMS.qml: onThirdBtnReleased")
        prThirdBtnEnable = false
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_INCOMING_SMS_POPUP)

        if(cppW3WAdaptor.isTextInW3WAddressFormat(cppPhoneAdaptor.smsData)) {
             cppPhoneApp.qmlLog("PhoneIncomingSMS.qml: Navigation Initiated")
            cppW3WAdaptor.invInitiateNavigation(cppPhoneAdaptor.smsData)
        }
        else {
            // Do nothing
        }
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import com.harman.qml.thememanager 1.0
import "../Common/Popup"

TwoButtonPopup {

    Connections
    {
        target: PopupManager
        onSigProcessHKOnPopup: {
            cppUIBase.qmlLog("onSigProcessHKOnPopup : slot called")
            PopupManager.invSetHKHandledStatus(cppPhoneAdaptor.invHandleHardKeys(iKey, iKeyState))
        }
    }

    //Property to hold reading sms sender name
    property string prReadingSmsSenderName: (cppPhoneAdaptor.smsSenderName != "") ? cppPhoneAdaptor.readingSMSSenderName : cppPhoneAdaptor.readingSMSSenderNumber

    /**
      * Text to be displayed on Popup
      */
    prPopupText: prReadingSmsSenderName + cppThemeMgr.languageChanged

    /**
      * Title to be displayed on Popup
      */
    prPopupTitle: qsTr("TEXT_PHONE_READING_MESSAGE") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on first button
      */
    prFirstBtnText: qsTr("TEXT_PHONE_CALL") + cppThemeMgr.languageChanged

    //enable call button only when contact number is available
    prFirstBtnEnable: (cppPhoneAdaptor.readingSMSSenderNumber !== "")

    /**
      * Text to be displayed on second button
      */
    prSecondBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_CANCEL_LABEL") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased: {
        cppPhoneApp.qmlLog("PhoneSMSReading.qml: onFirstBtnReleased")
        prFirstBtnEnable = false
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_SMS_READING_POPUP)        
        cppPhoneAdaptor.invDial(cppPhoneAdaptor.readingSMSSenderNumber, cppPhoneAdaptor.readingSMSSenderName)
    }

    onSigSecondBtnReleased: {
        cppPhoneApp.qmlLog("PhoneSMSReading.qml: onSecondBtnReleased")
        prSecondBtnEnable = false
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_PHONE_SMS_READING_POPUP)
        cppPhoneAdaptor.invStopSmsReadout()
    }
}

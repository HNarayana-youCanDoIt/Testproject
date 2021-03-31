import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import QtGraphicalEffects 1.0
import com.harman.qml.hardkeyenum 1.0
import "../../Common"


/*
  Template for Notification Popup with TEXT and one ICON
*/
BasePopupNotification {

    // Property hold the left margin of text field from icon
    property int prLeftMarginFromImage: 3

    // Property hold the max width for dynamic text field
    property int prStaticTextMaxWidth: 134

    // Property hold the max width for static text field
    property int prDynamicTextMaxWidth: 169

    // Property for static text to be set in the popup
    property alias prPopupStaticText: idPopupStaticText.text

    // Property for dynamic text to be set in the popup
    property alias prPopupDynamicText: idPopupDynamicText.text

    // Setting background Height for notification
    prBackgroundHeight: 40

    /**
     * Mouse area to deactivate VR session
     */
    MouseArea{
        anchors.fill: parent
        onPressed: {
            cppUIBase.qmlLog("NotificationPopupWithDynamicText.qml: onPressed event received")
            // Deactivate VR session
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
            // Deactivate phone bt vr
            cppPhoneAdaptor.invReqPhoneBtVrDeactivation()
        }
    }


    /**
      * Image to hold the Icon related to notification popup
      **/
    Image {
        id: idNotificationPopupIcon

        anchors{
            left: parent.left
            leftMargin: 10
            top: parent.top
            topMargin: 5
        }
        source: "qrc:/image/Popup/Popup_Notification_Icon/Popup_Notification_Ico_Bell_n.png"
    }

    /**
     * HBText to hold dynamic text of notification popup
     **/
    HBText {
        id: idPopupDynamicText
        width: 169
        height: 35

        anchors{
            left: idNotificationPopupIcon.right
            verticalCenter: idNotificationPopupIcon.verticalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

        Component.onCompleted: {
            cppTunerApp.qmlLog("idPopupStaticText:  content width right now : " + contentWidth)
            width = (contentWidth >= prDynamicTextMaxWidth) ? prDynamicTextMaxWidth : contentWidth
        }
    }

    /**
     * HBText to hold static text of notification popup
     **/
    HBText {
        id: idPopupStaticText
        width: 134
        height: 35

        anchors{
            left: idPopupDynamicText.right
            verticalCenter: idNotificationPopupIcon.verticalCenter
        }

        elide: HBText.ElideNone

        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignLeft
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

        Component.onCompleted: {
            cppTunerApp.qmlLog("idPopupStaticText:  content width right now : " + contentWidth)
            width = (contentWidth >= prStaticTextMaxWidth) ? prStaticTextMaxWidth : contentWidth
        }
    }
}

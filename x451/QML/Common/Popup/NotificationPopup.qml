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
    id: idNotification

    // Property for text to be set in the popup
    property alias prPopupText: idPopupText.text

    /**
     * Mouse area to deactivate VR session
     */
    MouseArea{
        anchors.fill: parent
        onPressed: {
            cppUIBase.qmlLog("NotificationPopup.qml: onPressed event received")
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
      * HBText to hold title to be displayed on popup
      **/
    HBText {
        id: idPopupText
        width: 340
        height: 35

        anchors{
            left: idNotificationPopupIcon.right
            verticalCenter: idNotificationPopupIcon.verticalCenter
        }

        elide: HBText.ElideRight

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import QtGraphicalEffects 1.0
import "../../Common"

BasePopupNotification{
    id: idNotificationPopupWithTwoImageOneText

    /** Property to set idNotificationImage source */
    property alias prNotificationImage: idNotificationImage.source

    /** Property to set idNotificationText text */
    property alias prNotificationText: idNotificationText.text

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
      * Notification image
      **/
    Image {
        id: idNotificationImage
        anchors {
            left: idNotificationPopupIcon.right
            verticalCenter: idNotificationPopupIcon.verticalCenter
        }
    }

    /**
      * HBText to hold text to be displayed on notification
      **/
    HBText {
        id: idNotificationText
        width: 223
        height: 35

        anchors{
            left: idNotificationImage.right
            leftMargin: 10
            verticalCenter: idNotificationPopupIcon.verticalCenter
        }

        elide: HBText.ElideRight

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
    }
}

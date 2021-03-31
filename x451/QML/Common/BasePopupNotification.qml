import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.hardkeyenum 1.0
import "../Common"


/*
  Base Container for all the notification popups
*/
Item {
    id: idBasePopupNotification

    // Property holds the background width for notification background and as well as mouse area
    property int prBackgroundWidth: 390

    // Property holds the background heigh for notification background and as well as mouse area
    property int prBackgroundHeight: 40

    Image {
        id: idNotificationBackground
        source: "qrc:/image/Popup/PopupBg/Notification_Backgr/Notification_Background_Overlay.png"
        visible: ((cppAndroidAutoAdaptor.androidAutoConnectionStatus && cppAndroidAutoAdaptor.androidAutoProjectionStatus)||
                  (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus && cppAppleCarPlayAdaptor.appleCarPlayProjectionStatus))
    }

    /**
     * Mouse area for notification calls closeOnTouch Method on a touch event over the notification area
     */
    MouseArea{
        height: prBackgroundHeight
        width: prBackgroundWidth
        onPressed: {
            cppUIBase.qmlLog("BasePopup.qml : Notification Area Touched")
            PopupManager.closeOnTouch()
        }
    }
}

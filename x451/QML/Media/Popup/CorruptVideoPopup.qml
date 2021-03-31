import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common/Popup"
import com.harman.qml.mediaenum 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0

TwoButtonPopup {
    prPopupText: qsTr("The Media File is Corrupted or not Supported. Do You Want to Play Another Video?") + cppThemeMgr.languageChanged
    prFirstBtnText: qsTr("Ok") + cppThemeMgr.languageChanged
    prSecondBtnText: qsTr("Next") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased: {
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_USB_CORRUPT_VIDEO)

        /* If all videos are corrupt then USB content type is updated in background */
        if(MediaEnum.CONTENTTYPE_V === MediaAdaptor.usbContentType
                || MediaEnum.CONTENTTYPE_VI === MediaAdaptor.usbContentType
                || MediaEnum.CONTENTTYPE_SV === MediaAdaptor.usbContentType
                || MediaEnum.CONTENTTYPE_SVI === MediaAdaptor.usbContentType)
        {
            //Need to jump directly to Video browse list
            MediaAdaptor.directMediaStateSwitch(MediaEnum.BROWSEITEM_VIDEOS)
        }
        else
        {
            MediaAdaptor.handleAllVideosCorrupt();
        }
    }

    onSigSecondBtnReleased: {
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_USB_CORRUPT_VIDEO)

        /* If all videos are corrupt then USB content type is updated in background */
        if(MediaEnum.CONTENTTYPE_V === MediaAdaptor.usbContentType
                || MediaEnum.CONTENTTYPE_VI === MediaAdaptor.usbContentType
                || MediaEnum.CONTENTTYPE_SV === MediaAdaptor.usbContentType
                || MediaEnum.CONTENTTYPE_SVI === MediaAdaptor.usbContentType)
        {
            MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_RELEASED)
        }
        else
        {
            MediaAdaptor.handleAllVideosCorrupt();
        }

    }
}

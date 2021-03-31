import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common/Popup"
import com.harman.qml.mediaenum 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0
import com.harman.qml.audioenums 1.0

TwoButtonPopup {
    prPopupText: qsTr("No Playable Audio Found.\nDo You Want Browse USB?") + cppThemeMgr.languageChanged
    prFirstBtnText: qsTr("Cancel") + cppThemeMgr.languageChanged
    prSecondBtnText: qsTr("Browse") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased: {
        MediaAdaptor.setNoSongsUSBResponse(false)
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION)
        MediaAdaptor.requestPreviousSource()
    }

    onSigSecondBtnReleased: {
        MediaAdaptor.setNoSongsUSBResponse(true)
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION)
        if(cppVehicleAdaptor.speedLockOutStatus)
        {
            PopupManager.showPopup(PopupEnum.EN_POPUPID_USB_SPEED_LOCKOUT_IMAGES)
            MediaAdaptor.requestPreviousSource()
        }
        else
        {
            MediaAdaptor.directMediaStateSwitch(MediaEnum.BROWSEITEM_PICTURE)
        }
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common/Popup"
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0

TwoButtonPopup {

    prPopupTitle: qsTr("TEXT_W3W_POPUP_AUTO_LAUNCH_PERMISSION_TITLE") + cppThemeMgr.languageChanged
    prPopupText: qsTr("TEXT_W3W_POPUP_AUTO_LAUNCH_PERMISSION_CP") + cppThemeMgr.languageChanged

    prFirstBtnText: qsTr("TEXT_W3W_POPUP_AUTO_LAUNCH_PERMISSION_ALLOW") + cppThemeMgr.languageChanged
    prSecondBtnText: qsTr("TEXT_W3W_POPUP_AUTO_LAUNCH_PERMISSION_DENY") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased: {
        cppW3WApplication.qmlLog("W3WAllowAutoLaunchAAPopup.qml: Allow clicked")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_W3W_ALLOW_AUTOLAUNCH_CP)
        cppAppleCarPlayAdaptor.launchAppleCarPlay()
        cppW3WAdaptor.invSetAutoLaunchPermissionStatusForCP(true)
    }

    onSigSecondBtnReleased: {
        cppW3WApplication.qmlLog("W3WAllowAutoLaunchAAPopup.qml: Deny clicked")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_W3W_ALLOW_AUTOLAUNCH_CP)
    }
}

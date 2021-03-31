import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common/Popup"
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0

OneButtonPopup {

    prPopupTitle: qsTr("TEXT_W3W_POPUP_SHARE_ADDRESS") + cppThemeMgr.languageChanged
    prPopupText: "///" + cppUIBase.invTruncateText(cppW3WAdaptor.selectedW3WAddress, 30)

    prBtnText: qsTr("TEXT_W3W_POPUP_SELECT_CONTACT") + cppThemeMgr.languageChanged

    onBtnReleased: {
        cppW3WApplication.qmlLog("W3WShareAddressPopup.qml: Select Contact clicked")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_W3W_SHARE_ADDRESS)
        cppW3WApplication.raiseSMEvent("LaunchW3WPhoneBrowseScreen", "")
    }
}

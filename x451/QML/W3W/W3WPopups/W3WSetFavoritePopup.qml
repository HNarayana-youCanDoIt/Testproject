import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common/Popup"
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0

TwoButtonPopup {

    prPopupTitle: qsTr("TEXT_W3W_SET_FAVORITE") + cppThemeMgr.languageChanged
    prPopupText: "///" + cppUIBase.invTruncateText(cppW3WAdaptor.selectedW3WAddressForFavorite, 30)

    prFirstBtnText: qsTr("TEXT_W3W_ADD_LABEL") + cppThemeMgr.languageChanged
    prSecondBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_SAVE_LABEL") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased: {
        cppW3WApplication.qmlLog("W3WSetFavoritePopup.qml: Add Label clicked")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_W3W_SET_FAVORITE)
        cppW3WApplication.raiseSMEvent("LaunchW3WEditLabelScreen", "")
    }

    onSigSecondBtnReleased: {
        cppW3WApplication.qmlLog("W3WSetFavoritePopup.qml: Save clicked")
        cppW3WAdaptor.selectedW3WAddressLabelForFavorite = ""
        cppW3WAdaptor.invAddToFavorite()
    }
}

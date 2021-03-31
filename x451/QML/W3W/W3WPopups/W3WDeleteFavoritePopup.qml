import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common/Popup"
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0
import com.harman.qml.w3wenum 1.0

TwoButtonPopup {

    prPopupTitle: qsTr("TEXT_W3W_FAVORITES_TITLE") + cppThemeMgr.languageChanged
    prPopupText: qsTr("TEXT_W3W_POPUP_DELETE_FAVORITE_CONFIRMATION").arg((cppW3WAdaptor.selectedW3WAddressLabelForDelete === "") ?
                                                                               cppUIBase.invTruncateText(cppW3WAdaptor.selectedW3WAddressForDelete, 30) :
                                                                               cppUIBase.invTruncateText(cppW3WAdaptor.selectedW3WAddressLabelForDelete, 30)) + cppThemeMgr.languageChanged

    prFirstBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_YES_LABEL") + cppThemeMgr.languageChanged
    prSecondBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_NO_LABEL") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased: {
        cppW3WApplication.qmlLog("W3WDeleteFavoritePopup.qml: Yes clicked")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_W3W_DELETE_FAVORITE)
        cppW3WAdaptor.invDeleteW3WAddress(W3WEnum.W3W_ADDRESS_TYPE_FAVORITE)
    }

    onSigSecondBtnReleased: {
        cppW3WApplication.qmlLog("W3WDeleteFavoritePopup.qml: No clicked")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_W3W_DELETE_FAVORITE)
    }
}

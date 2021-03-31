import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import "../Common/Popup"

TwoButtonPopup
{
    /**
      * Title to be displayed on Popup
      */
    prPopupTitle: qsTr("TEXT_PHONE_FAVOURITE_TITLE") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on Popup
      */
    prPopupText: qsTr("TEXT_PHONE_BROWSE_FAVOURITE_DELETE_CONFIRMATION").arg(cppPhoneAdaptor.favoriteTogglingContactNumber) + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on first button
      */
    prFirstBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_YES_LABEL") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on second button
      */
    prSecondBtnText: qsTr("TEXT_GENERIC_POPUP_BTN_NO_LABEL") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased:
    {
        PopupManager.forceClosePopup(
                    PopupEnum.EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVE_CONFIRMATION)
        cppPhoneAdaptor.invRemoveFavorite(true)
    }

    onSigSecondBtnReleased:
    {
        PopupManager.forceClosePopup(
                    PopupEnum.EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVE_CONFIRMATION)
        cppPhoneAdaptor.invRemoveFavorite(false)
    }

    onClosed: {
        cppPhoneAdaptor.invRemoveFavorite(false)
    }
}

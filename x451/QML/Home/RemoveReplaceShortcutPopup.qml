import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import com.harman.qml.thememanager 1.0
import "../Home"
import "../Common"
import "../Common/Popup"

ThreeButtonPopup {

    /**
      * Title to be displayed on Popup
      */
    prPopupTitle: qsTr("TEXT_HOME_POPUP_REMOVE_REPLACE_TITLE") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on Popup
      */
    prPopupText: cppHomeAdaptor.invShortcutToEditTitle()

    /**
      * Text to be displayed on first button
      */
    prFirstBtnText: qsTr("TEXT_HOME_POPUP_REPLACE_BTN") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on second button
      */
    prSecondBtnText: qsTr("TEXT_HOME_POPUP_REMOVE_BTN") + cppThemeMgr.languageChanged

    /**
      * Text to be displayed on third button
      */
    prThirdBtnText: qsTr("TEXT_HOME_POPUP_CANCEL_BTN") + cppThemeMgr.languageChanged

    onFirstBtnReleased: {
        cppHomeApplication.qmlLog("RemoveShortcuts.qml: onFirstBtnReleased")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_HOME_EDIT_SHORTCUT)
        cppHomeAdaptor.homeShortcutsList[0].invShortcutClicked(
                    cppHomeAdaptor.shortcutToEdit)
    }

    onSecondBtnReleased: {
        cppHomeApplication.qmlLog("RemoveShortcuts.qml: onSecondBtnReleased")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_HOME_EDIT_SHORTCUT)
        cppHomeAdaptor.invUpdateShortcut(0)
    }

    onThirdBtnReleased: {
        cppHomeApplication.qmlLog("RemoveShortcuts.qml: onThirdBtnReleased")
        PopupManager.forceClosePopup(PopupEnum.EN_POPUPID_HOME_EDIT_SHORTCUT)
    }
}

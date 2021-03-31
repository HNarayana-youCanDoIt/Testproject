import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common/Popup"
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0

TwoButtonPopup {

    prPopupTitle: qsTr("*Clear My sticker") + cppThemeMgr.languageChanged
    prPopupText: qsTr("*Are You Sure You Want To Clear My Sticker Image ?") + cppThemeMgr.languageChanged

    prFirstBtnText: qsTr("*Yes") + cppThemeMgr.languageChanged
    prSecondBtnText: qsTr("*No") + cppThemeMgr.languageChanged

    onSigFirstBtnReleased: {
        cppDoodleApplication.qmlLog("DoodleMyStickerClearPopup.qml: Yes clicked")
    }

    onSigSecondBtnReleased: {
        cppDoodleApplication.qmlLog("DoodleMyStickerClearPopup.qml: No clicked")
    }
}

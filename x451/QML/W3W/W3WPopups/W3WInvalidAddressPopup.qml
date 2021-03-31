import QtQuick 2.7
import "../../Common/Popup"

NoButtonPopup
{
    prPopupTitle: qsTr("TEXT_TITLE_ERROR") + cppThemeMgr.languageChanged
    prPopupText: qsTr("TEXT_W3W_POPUP_INVALID_ADDRESS") + cppThemeMgr.languageChanged
}

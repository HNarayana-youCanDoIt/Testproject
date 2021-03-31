import QtQuick 2.7
import "../../Common/Popup"

NotificationPopup{
    //FixMe: Use QProperty for Device Name here when displaying the same popup for BT
    prPopupText: qsTr("TEXT_SOURCE_NO_PLAYABLE_FILE_FOUND") + cppThemeMgr.languageChanged

}

import QtQuick 2.7
import "../../Common/Popup"

NotificationPopup{
    //FixMe: Need to put device name dynamically here
    prPopupText: qsTr("BT device disconnected") + cppThemeMgr.languageChanged
}

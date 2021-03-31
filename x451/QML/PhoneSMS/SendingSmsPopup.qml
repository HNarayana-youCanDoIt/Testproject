import QtQuick 2.7
import "../Common/Popup"

NotificationPopup
{
    // TODO: Popup string id should be added instead of static text.
    prPopupText: qsTr("TEXT_PHONE_SENDING_MSG") + cppThemeMgr.languageChanged
}

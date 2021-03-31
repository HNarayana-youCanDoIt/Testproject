import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NotificationPopup
{
    // TODO: Popup string id should be added instead of static text.
    prPopupText: qsTr("TEXT_TUNER_ANTENNA_NOT_CONNECTED") + cppThemeMgr.languageChanged
}


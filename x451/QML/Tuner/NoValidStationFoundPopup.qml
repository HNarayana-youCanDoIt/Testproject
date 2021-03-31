import QtQuick 2.7
import "../Common/Popup"

NoButtonPopup
{
    // TODO: Popup string id should be added instead of static text.
    prPopupTitle: qsTr("Error") + cppThemeMgr.languageChanged

    // TODO: Popup string id should be added instead of static text.
    prPopupText: qsTr("No Valid Station Found.") + cppThemeMgr.languageChanged
}

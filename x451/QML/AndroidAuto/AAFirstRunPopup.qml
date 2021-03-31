import QtQuick 2.7
import "../Common/Popup"

NoButtonPopup
{
    prPopupTitle: qsTr("TEXT_GENERIC_POPUP_WARNING_TITLE") + cppThemeMgr.languageChanged

    prPopupText: qsTr("TEXT_POPUP_ANDROIDAUTO_FIRST_RUN") + cppThemeMgr.languageChanged
}

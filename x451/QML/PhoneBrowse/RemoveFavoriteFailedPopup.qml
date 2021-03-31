import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NoButtonPopup
{
    // TODO: Popup string id should be added instead of static text.
    prPopupText: qsTr("TEXT_PHONE_BROWSE_FAILED_TO_REMOVE_FAVOURITE").arg(cppPhoneAdaptor.favoriteTogglingContactNumber) + cppThemeMgr.languageChanged
}

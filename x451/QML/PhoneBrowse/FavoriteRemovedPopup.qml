import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NoButtonPopup
{
    prPopupText: qsTr("TEXT_PHONE_BROWSE_FAVOURITE_REMOVED").arg(cppPhoneAdaptor.favoriteTogglingContactNumber) + cppThemeMgr.languageChanged
}


import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

// TODO : Need to update the popup design and data

NoButtonPopup
{
    prPopupText: cppPhoneAdaptor.favoriteTogglingContactNumber + qsTr("TEXT_PHONE_BROWSE_FAVOURITE_ADDED") + cppThemeMgr.languageChanged
}


import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NoButtonPopup
{
    prPopupText: qsTr("TEXT_PHONE_BROWSE_FAILED_TO_ADD_FAVOURITE").arg(cppPhoneAdaptor.favoriteTogglingContactNumber) + cppThemeMgr.languageChanged
}

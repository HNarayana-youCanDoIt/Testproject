import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NoButtonPopup
{
    prPopupText: qsTr("TEXT_PHONE_SETUP_DEVICE_DISCONNECTING").arg(cppUIBase.invTruncateText(cppPhoneAdaptor.selItemName,20, "")) + cppThemeMgr.languageChanged
}

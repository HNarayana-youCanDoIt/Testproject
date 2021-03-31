import QtQuick 2.7
import "../Common/Popup"

NoButtonPopup
{
    prPopupText: cppUIBase.invTruncateText(cppPhoneAdaptor.connectedDeviceName, 20) + qsTr("TEXT_PHONE_SETUP_A2DP_CONNECTED") + cppThemeMgr.languageChanged
}

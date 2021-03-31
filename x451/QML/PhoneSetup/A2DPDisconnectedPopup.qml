import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NotificationPopup
{
    prPopupText: cppUIBase.invTruncateText(cppPhoneAdaptor.disconnectedDeviceName, 20) + qsTr("TEXT_PHONE_SETUP_A2DP_DISCONNECTED") + cppThemeMgr.languageChanged
}

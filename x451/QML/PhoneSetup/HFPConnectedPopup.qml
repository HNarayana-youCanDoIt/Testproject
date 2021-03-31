import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NotificationPopup
{
    prPopupText: cppPhoneAdaptor.connectedDeviceName + qsTr("TEXT_PHONE_SETUP_HFP_CONNECTED") + cppThemeMgr.languageChanged
}

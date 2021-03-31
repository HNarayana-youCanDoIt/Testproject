import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NotificationPopup
{
    prPopupText: cppPhoneAdaptor.disconnectedDeviceName + qsTr("TEXT_PHONE_SETUP_HFP_DISCONNECTED") + cppThemeMgr.languageChanged
}

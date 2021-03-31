import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NotificationPopupWithDynamicText
{
    prPopupDynamicText: cppPhoneAdaptor.disconnectedDeviceName
    prPopupStaticText: qsTr("TEXT_PHONE_SETUP_DEVICE_DISCONNECTED") + cppThemeMgr.languageChanged

}

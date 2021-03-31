import QtQuick 2.7
import "../Common/Popup"

NotificationPopupWithDynamicText
{
    prPopupDynamicText: cppPhoneAdaptor.deletedDeviceName
    prPopupStaticText: qsTr("TEXT_PHONE_SETUP_DELETE_DEVICES_FAILED") + cppThemeMgr.languageChanged
}

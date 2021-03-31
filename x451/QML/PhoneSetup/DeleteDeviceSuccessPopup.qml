import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/Popup"

NotificationPopupWithDynamicText
{
    prPopupDynamicText: cppPhoneAdaptor.deletedDeviceName
    prPopupStaticText: qsTr("TEXT_PHONE_SETUP_DELETE_DEVICES_SUCCESS") + cppThemeMgr.languageChanged
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import QtGraphicalEffects 1.0
import "../Common/Popup"

HBNotificationPopupWithTwoImageOneText{
    id: idRCAAuxGainNotification

    prNotificationImage: cppRCAAdaptor.strBalanceFaderImageSource

    prNotificationText: qsTr("TEXT_AUDIO_SETTINGS_BALANCE_FADER") + cppThemeMgr.languageChanged
}

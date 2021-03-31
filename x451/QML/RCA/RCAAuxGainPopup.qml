import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import QtGraphicalEffects 1.0
import "../Common/Popup"

HBNotificationPopupWithTwoImageOneText{
    id: idRCAAuxGainNotification

    prNotificationImage: "qrc:/image/RCA/RCA_Ico_Aux_n/Sts_Ico_Aux_n.png"

    prNotificationText: cppRCAAdaptor.strAuxGainText
}

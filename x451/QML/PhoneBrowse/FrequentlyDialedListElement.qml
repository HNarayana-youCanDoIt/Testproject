/* This component contains a Call log list element button. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0


/* Frequently dialed list element derived from generic button */
HBButtonListItem {
    id: idFrequentlyDialedListItem
    /* property phone call type */
    property int prCallType: 0

    /* property contact name*/
    property alias prContactName: idContactName.text

    /* property contact time hh:mm*/
    property alias prCallTime: idCallTime.text

    /* property contact date dd:mm:yyyy*/
    property alias prCallDate: idCallDate.text

    /* Image used to show call type image icon*/
    Image {
        id: idCallTypeImage

        height: 76
        width: 76

        anchors {
            left: parent.left
            verticalCenter: idFrequentlyDialedListItem.verticalCenter
        }
        source: "qrc:/image/PhoneBrowse/Ph_Ico_DialedCall_7in_n/Ph_Ico_DialedCall_n.png"
    }

    /* HBText used to show Contact Name*/
    HBText {
        id: idContactName

        height: 39
        width: 253

        anchors {
            left: parent.left
            leftMargin: 89
            verticalCenter: idFrequentlyDialedListItem.verticalCenter
        }

        horizontalAlignment: HBText.AlignLeft
        verticalAlignment: HBText.AlignVCenter
        fontType: ThemeMgr.FONTTYPE_T35_C3
    }

    /* HBText used to show call Time*/
    HBText {
        id: idCallTime

        height: 21
        width: 120

        anchors {
            left: parent.left
            leftMargin: 361
            top: parent.top
            topMargin: 6
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    /* HBText used to show call Date*/
    HBText {
        id: idCallDate

        height: 29
        width: 120

        anchors {
            left: parent.left
            leftMargin: 361
            top: parent.top
            topMargin: 39
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }
}


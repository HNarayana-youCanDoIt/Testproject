/* This component contains a Call log list element button. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0


/* Call log list element derived from generic button */
// FixMe: [RRahul] [PHONE] need to allign according to X0 design
HBButtonListItem {
    id: idCallLogListItem
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
            verticalCenter: idCallLogListItem.verticalCenter
        }

        visible: (source !== "")
        source: getCallTypeImage(prCallType)
    }

    /* HBText used to show Contact Name*/
    HBText {
        id: idContactName

        height: 39 //------->> orig: 24
        width: 253

        anchors {
            left: parent.left
            leftMargin: 89
            verticalCenter: idCallLogListItem.verticalCenter
        }

        horizontalAlignment: HBText.AlignLeft
        verticalAlignment: HBText.AlignVCenter
        fontType: ThemeMgr.FONTTYPE_T35_C3
    }

    /* HBText used to show call Time*/
    HBText {
        id: idCallTime

        height: 21 //------>> orig: 16
        width: 120

        anchors {
            left: parent.left
            leftMargin: 361
            top: parent.top
            topMargin: 6 //---------->>orig: 10
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    /* HBText used to show call Date*/
    HBText {
        id: idCallDate

        height: 29 //------>> orig: 16
        width: 120

        anchors {
            left: parent.left
            leftMargin: 361
            top: parent.top
            topMargin: 39 //---------->>orig: 50
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }

    // Function return the image path of call type as per the data received from service for the call
    function getCallTypeImage(callType) {
        var imagePath = ""
        switch (callType) {
        case PhoneEnum.CALL_TYPE_INCOMING:
            imagePath = "qrc:/image/PhoneBrowse/Ph_Ico_ReceivedCall_7in_n/Ph_Ico_ReceivedCall_n.png"
            break
        case PhoneEnum.CALL_TYPE_OUTGOING:
            imagePath = "qrc:/image/PhoneBrowse/Ph_Ico_DialedCall_7in_n/Ph_Ico_DialedCall_n.png"
            break
        case PhoneEnum.CALL_TYPE_MISSED:
            imagePath = "qrc:/image/PhoneBrowse/Ph_Ico_MissedCall_7in_n/Ph_Ico_MissedCall_n.png"
            break
        default:
            imagePath = ""
        }
        return imagePath
    }
}


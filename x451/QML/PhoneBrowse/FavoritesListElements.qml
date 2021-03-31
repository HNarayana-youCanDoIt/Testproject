/* This component contains a favourites list element button. */
import QtQuick 2.7
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0
import "../Common"

/* Favourites list element derived from generic button */
HBButtonListItem {
    id: idFavoriteListItem
    /* property contact name*/
    property alias prContactName: idContactName.text

    /* property contact number */
    property alias prContactNumber: idContactNumber.text

    /* property contact number type */
    property alias prContactType: idContactType.text

    /* property hold favorite status of contact */
    property bool prIsFavorite: false

    /* signal to be emitted on favorite clicked */
    signal sigFavoriteBtnReleased

    /* HBText used to show Contact Name*/
    HBText {
        id: idContactName

        height: 39 //------->> orig: 25
        width: 304

        anchors {
            left: parent.left
            leftMargin: 14
            top: parent.top
            topMargin: 2
        }

        horizontalAlignment: HBText.AlignLeft
        verticalAlignment: HBText.AlignVCenter
        fontType: ThemeMgr.FONTTYPE_T35_C3
    }

    /* HBText used to show Contact type*/
    HBText {
        id: idContactType

        height: 21 //------>> orig: 18
        width: 64

        text: prContactType
        elide: Text.ElideNone

        anchors {
            left: parent.left
            leftMargin: 14
            top: parent.top
            topMargin: 44
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        horizontalAlignment: HBText.AlignLeft
        verticalAlignment: HBText.AlignVCenter
    }

    /* HBText used to show Contact Number*/
    HBText {
        id: idContactNumber

        height: 21 //------>> orig: 18
        width: 159

        elide: Text.ElideNone

        anchors {
            left: parent.left
            leftMargin: 100
            top: parent.top
            topMargin: 44
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        horizontalAlignment: HBText.AlignLeft
        verticalAlignment: HBText.AlignVCenter
    }

    /* GenericButton used to show fav button*/
    GenericButton {
        id: idFavoriteIcon

        height: 76
        width: 76

        anchors {
            left: parent.left
            leftMargin: 412
            verticalCenter: idFavoriteListItem.verticalCenter
        }

        enabled: (!cppPhoneAdaptor.isFavoriteToggling)
        visible: (cppPhoneAdaptor.phoneCallState === PhoneEnum.PHONE_CALLSTATE_IDLE)

        defaultImageURL: parent.prIsFavorite ? "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_na.png" : "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_n.png"
        pressedImageURL: "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_nf.png"
        disabledImageURL: parent.prIsFavorite ? "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_nd2.png" : "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_nd.png"

        onReleased: {
            sigFavoriteBtnReleased()
        }
    }
}


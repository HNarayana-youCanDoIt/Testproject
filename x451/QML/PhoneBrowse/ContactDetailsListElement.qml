/* This component contains a favourites list element button. */
import QtQuick 2.7
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0
import "../Common"


/* Favourites list element derived from generic button */
HBButtonListItem {
    id: idContactDetailsListItem

    /* property contact number */
    property alias prContactNumber: idContactNumber.text

    /* property contact number type */
    property alias prContactType: idContactType.text

    /* Property alias for Favourite button */
    property alias prFavoriteButton: idFavoriteButton

    /* property hold favorite status of contact */
    property bool prIsFavorite: false

    /* signal to be emitted on call button pressed */
    signal sigContactDetailCallPressed

    /* signal to be emitted on call clicked */
    signal sigContactDetailCallReleased

    /* signal to be emitted on favorite button pressed */
    signal sigContactDetailFavPressed

    /* signal to be emitted on favorite clicked */
    signal sigContactDetailFavReleased

    /* GenericButton used to show call button*/
    GenericButton {

        height: 76
        width: 76

        anchors {
            left: parent.left
            verticalCenter: idContactDetailsListItem.verticalCenter
        }

        defaultImageURL: "qrc:/image/PhoneBrowse/Ph_Btn_Call_7in_n-assets/Ph_Btn_Call_n.png"
        pressedImageURL: "qrc:/image/PhoneBrowse/Ph_Btn_Call_7in_n-assets/Ph_Btn_Call_nf.png"
        disabledImageURL: "qrc:/image/PhoneBrowse/Ph_Btn_Call_7in_n-assets/Ph_Btn_Call_nd.png"

        onPressed: {
            sigContactDetailCallPressed()
        }

        onReleased: {
            sigContactDetailCallReleased()
        }
    }

    /* HBText used to show Contact Name*/
    HBText {
        id: idContactNumber

        height: 25
        width: 312

        anchors {
            left: parent.left
            leftMargin: 75
            top: parent.top
            topMargin: 8
        }

        horizontalAlignment: HBText.AlignLeft
        verticalAlignment: HBText.AlignVCenter
        fontType: ThemeMgr.FONTTYPE_T35_C3
    }

    /* HBText used to show Contact type*/
    HBText {
        id: idContactType

        height: 18
        width: 312

        elide: Text.ElideNone

        anchors {
            left: idContactNumber.left
            top: parent.top
            topMargin: 47
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        horizontalAlignment: HBText.AlignLeft
        verticalAlignment: HBText.AlignVCenter
    }

    /* GenericButton used to show fav button*/
    GenericButton {
        id: idFavoriteButton

        height: 76
        width: 76

        anchors {
            left: parent.left
            leftMargin: 411
            verticalCenter: idContactDetailsListItem.verticalCenter
        }

        enabled: (!cppPhoneAdaptor.isFavoriteToggling)
        visible: (cppPhoneAdaptor.phoneCallState === PhoneEnum.PHONE_CALLSTATE_IDLE)

        defaultImageURL: parent.prIsFavorite ? "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_na.png" : "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_n.png"
        pressedImageURL: parent.prIsFavorite ? "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_nf.png" : "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_nf.png"
        //Used default Image for disabled image url intentionally to avoid blink when the icon is toggled for enabled property
        disabledImageURL: parent.prIsFavorite ?  "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_na.png" : "qrc:/image/PhoneBrowse/Ph_Ico_AddFavourite_7in_n-assets/Ph_Ico_AddFavourite_n.png"

        onPressed: {
            sigContactDetailFavPressed()
        }

        onReleased: {
            sigContactDetailFavReleased()
        }
    }
}


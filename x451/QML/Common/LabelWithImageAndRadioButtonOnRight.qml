/* This component contains a radio button on right, label and a image on left  */
/* prImageWidth, prImageHeight & image states to be provided as per need, where all this component is used */
import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/"
import com.harman.qml.thememanager 1.0
import QtGraphicalEffects 1.0

/* List Item Button which has a RadioButton and an Image */
HBButtonListItem {
    id: idLabelWithRadioBtnOnRight

    /* Width of Image to be provided */
    property int prImageWidth : 112

    /* Width of Height to be provided */
    property int prImageHeight : 70

    /* color overlay enable property for left image */
    property bool prEnableColorOverlayForLeftImage : false

    /* Variable holds left image overlay color */
    property string prOverlayColor : ""

    /* Path of default state image to be provided */
    property string prDefaultImage : "qrc:/image/Themes/Set_Ico_sColour_7in_n-assets/sLight_patch_color_2_Zen_n.png"

    /* Path of pressed state image to be provided */
    property string prPressedImage : "qrc:/image/Themes/Set_Ico_sColour_7in_n-assets/sLight_patch_color_2_Zen_n.png"

    /* Path of disabled state image to be provided */
    property string prDisabledImage: "qrc:/image/Themes/Set_Ico_sColour_7in_n-assets/sLight_patch_color_2_Zen_n.png"

    /* Width of radio button to be provided */
    property int prRadioBtnWidth: 76

    /* Height of radio button to be provided */
    property int prRadioBtnHeight: 76

    /* Path of selected radio button image to be provided */
    property string prRadioBtnSelectedImage: "qrc:/image/Set_Ico_RadioButton_7in_n-assets/Set_Ico_RadioButton_7in_na.png"

    /* Path of non-selected/default radio button image to be provided */
    property string prRadioBtnDefaultImage: "qrc:/image/Set_Ico_RadioButton_7in_n-assets/Set_Ico_RadioButton_7in_n.png"

    /* Radio button group to be provided */
    property var radioButtonGroup: idRadioButton.ButtonGroup.group

    /* Property for eliding (truncating) the text */
    //property alias prElide: idHBText.ElideNone

    /* Alias provided for radio button control */
    property alias radioButtonChecked: idRadioButton.checked

    /* On click of radio button, this signal gets emitted */
    signal sigRadioBtnCheckedChanged()

    /* This signal gets emitted on onReleased & onPressAndHoldContinue,
       use the property "touchAndHold" to differentiate onReleased & onPressAndHoldContinue */
    signal sigImageClicked()

    /* Removing the GenericButton contentItem and defining our own as per requirement */
    contentItem: Item {


    /* GenericButton used for Image, kept rightside on the delegate */
    GenericButton {
        id : idImageOnLeft
        width: prImageWidth
        height: prImageHeight
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
        }

        defaultImageURL  : prDefaultImage
        pressedImageURL  : prPressedImage
        disabledImageURL : prDisabledImage

        onReleased: {
            sigImageClicked()
        }
        onPressAndHoldContinue: {
            sigImageClicked()
        }
        ColorOverlay {
            id: idColorOverlay
            anchors.fill: parent
            source: parent
            color: prOverlayColor
            visible: prEnableColorOverlayForLeftImage
        }
    }

    /* HBText used to display the label on the listitem */
    HBText {
        id: idHBText
        anchors {
            left: idImageOnLeft.right
        }
        width: 150
        fontType: parent.parent.enabled ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED
        text: parent.parent.text
        height: parent.height
        verticalAlignment: Text.AlignVCenter
    }

    /* Radio button control, kept leftside on the delegate */
    RadioButton {
        id: idRadioButton
        height: prRadioBtnHeight
        width: prRadioBtnWidth
        ButtonGroup.group: radioButtonGroup

        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
        }

        /* Radio button control provides default image and that can be customized according to requirement.
            we can provide different our own custom images in indicator */
        indicator: Image {
            id: idRadioCustomImage
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
            source: idRadioButton.checked ? prRadioBtnSelectedImage : prRadioBtnDefaultImage
        }

        /* On click of radio button, signal gets emitted with the corresponding index */
        onCheckedChanged: {
            if (checked) {
                sigRadioBtnCheckedChanged()
            }
            else{
                //Do Nothing
            }
        }
    }
    }

    onReleased: {
        if (!idRadioButton.checked) {
            idRadioButton.checked = true
        }
    }
}

/* USAGE:
            LabelWithImageAndRadioButtonOnRight {
                text: "listItemNameRole"
                prElide: Text.ElideRight
                radioButtonGroup: Radio btn group name
                radioButtonChecked : listItemCheckedRole
                prDefaultImage : "URL path"
                prPressedImage : "URL path"
                onSigRadioBtnCheckedChanged: {
                    Do your logic
                }
                onSigImageClicked: {
                    Do your logic
                }
            }
*/

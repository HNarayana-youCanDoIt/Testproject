/* This component contains a label with a clickable image */
/* prImageWidth, prImageHeight, prIsImageOnRightSide & image states to be provided as per need, where all this component is used */
import QtQuick 2.7
import "../Common/"
import com.harman.qml.thememanager 1.0

/* Text label which is derived from generic button */
HBButtonListItem {
    id: idLabelWithClickableImage

    property bool prIsImageOnRightSide : true
    property int prImageWidth : 76
    property int prImageHeight : 76
    property string prDefaultImage : "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"
    property string prPressedImage : "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nf.png"
    property string prDisabledImage: "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nd.png"

    /* This signal gets emitted on onReleased & onPressAndHoldContinue,
       use the property touchAndHold to differentiate onReleased & onPressAndHoldContinue */
    signal sigImageClicked()

    contentItem: Item {
        id: name
        HBText {
            id: idHBText
            width: 400
            height: 74

            fontType: parent.enabled ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED
            text: idLabelWithClickableImage.text

            anchors {
                left: parent.left
                leftMargin: (prIsImageOnRightSide) ? 11 : prImageWidth
            }
            verticalAlignment: Text.AlignVCenter
        }

        /* Clickable image, can be placed next/right to text label using the property prIsImageOnRightSide */
        GenericButton {
            id : idImage

            width: prImageWidth
            height: prImageHeight

            anchors {
                right: (prIsImageOnRightSide) ? parent.right : undefined
                left: (prIsImageOnRightSide) ? undefined : parent.left
                verticalCenter: parent.verticalCenter
            }
            defaultImageURL  : prDefaultImage
            pressedImageURL  : prPressedImage
            disabledImageURL : prDisabledImage

            onReleased: {
                sigImageClicked()
            }
        }
    }
}

/* USAGE:
            LabelWithClickableImage {
                text        : "Text"
                prDefaultImage : "Image path to be given"
                prPressedImage : "Image path to be given"
                prDisabledImage: "Image path to be given"
                prImageWidth: 70
                prImageHeight: 70
                prIsImageOnRightSide: false
                onSigImageClicked: {
                   cppUIBase.qmlLog("Do your logic")
                }
                onReleased  : {
                    cppUIBase.qmlLog("Do your logic")
                }
            }
*/

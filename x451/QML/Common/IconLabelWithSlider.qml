/* This component contains a label with a horizontal slider. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "../Common/"
import com.harman.qml.thememanager 1.0

Item {
    id: idIconLabelWithSlider
    /* Left margin of HorizontalSlider */
    property int prHorizontalSliderLeftMargin: 0

    /* Left margin of HorizontalSlider */
    property int prHorizontalSliderTopMargin: 0

    /* This property holds the alias of button list item text*/
    property alias customLabel      : idHBButtonListItem

    /* This property holds the alias of horizontalSlider*/
    property alias horizontalSlider : idHorizontalSlider

    /* This property holds the url of left image of list item*/
    property url prContextualImageSrc: idContextualImage.source

    /* Default image of the list item*/
    Image{
        id:idContextualImage
        source: prContextualImageSrc
        anchors{
            left:parent.left
            leftMargin: -15
        }
    }

    /* Text label which is derived from generic button */
    HBButtonListItem {
        id: idHBButtonListItem

        height: 74
        width: 200

        contentItem: HBText {
            id: idHBText
            anchors.left: parent.left
            anchors.leftMargin: 60
            fontType: ThemeMgr.FONTTYPE_T35_C3
            text: parent.text
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
        enabled: false
    }

    /* Horizontal slider Component with next and previous buttons */
    HorizontalSlider {
        id: idHorizontalSlider
        anchors {
            left: idHBButtonListItem.left
            leftMargin: prHorizontalSliderLeftMargin
            top: parent.top
            topMargin: prHorizontalSliderTopMargin
        }

        prProgressFillItem.width: 0
        prProgressFillItem.height: 0
        prProgressFillItem.anchors.left: undefined

        /* Need to be customized according to requirement in respective qml, default handle is provided */
        slider.handle: Text {
            id: idPopupText
            text: Math.round(idHorizontalSlider.slider.value)
            color: "White"      //FixMe: Need to be changed
            font.pixelSize: 24  //FixMe: Need to be changed
            x: idHorizontalSlider.slider.leftPadding + idHorizontalSlider.slider.visualPosition * (idHorizontalSlider.slider.availableWidth - width)
            y: idHorizontalSlider.slider.topPadding + idHorizontalSlider.slider.availableHeight / 2 - height / 2
        }
    }
}

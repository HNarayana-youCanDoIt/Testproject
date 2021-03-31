/* This component contains a label with a horizontal slider. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "../Common/"
import com.harman.qml.thememanager 1.0

Item {
    id: idLabelWithSlider
    /* Left margin of HorizontalSlider */
    property int prHorizontalSliderLeftMargin: 0

    /* Left margin of HorizontalSlider */
    property int prHorizontalSliderTopMargin: 0

    property alias customLabel      : idHBButtonListItem
    property alias horizontalSlider : idHorizontalSlider

    /*FixMe: Need to find a better way instead of deriving from generic button */
    /* Text label which is derived from generic button */
    HBButtonListItem {
        id: idHBButtonListItem
        height: 74
        width: 430

        //FixMe: Need to un Comment this after getting proper solution
        anchors {
            left: parent.left
            leftMargin: 10
        }

        /* Removing the GenericButton contentItem and defining our own as per requirement */
        contentItem: HBText {
            id: idHBText
            anchors.left: parent.left
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
            //FixMe: Need to un Comment this after getting proper solution
//            fill: idHBButtonListItem
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

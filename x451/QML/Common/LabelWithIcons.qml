/* This component contains a label with a clickable image */

import QtQuick 2.7
import "../Common/"
import com.harman.qml.thememanager 1.0

/* Text label which is derived from generic button */
HBButtonListItem {
    id: idLabelWithIcons

    //Property for text left margin.
    property int prTextLeftMargin: 75 //Default value

    //Property alias provided to change the icon source image.
    property alias prIconImage: idIconImageItem.source

    //property alias provided to change the selected image
    property alias prRightIconImage : idRightIconImage.source

    //property alias provided to change the selected theme color
    property alias prSelectedThemeColor :idRectThemeSelectedColor.color

    //property alias provided to change the fan speed icon image
    property alias prFanSpeedImage: idIconImageFanSpeed.source

    //property alias provided to change the fan speed image visibilty
    property alias prFanSpeedImageVisibilty : idIconImageFanSpeed.visible

    //property alias provided to change the text value
    property alias prFanSpeedValue: idFanSpeedText.text

    //property alias provided to change the fan speed value visibilty
    property alias prFanSpeedValueVisibility: idFanSpeedText.visible

    //property alias to change the temperature value text
    property alias prTemperatureValue: idTemperatureText.text

    //property alias to change the temperature value text visibility
    property alias prTemperatureValueVisibility: idTemperatureText.visible

    //property to set seperator line source value
    property alias prSeperatorLine: idListSeperatorVerticalline2.source

    //property to set seperator line visibilty status
    property alias prSeperatorLineVisibility: idListSeperatorVerticalline2.visible

    //property to set visibility status
    property bool prVisibility: false

    //property to set theme color icon visisbility
    property bool prThemeColorVisibility: true

    //property to set theme sound icon visibilty
    property bool prThemeSoundVisibility: false

    //Property for text font type.
    property int prTextFontType: (enabled) ?  ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED

    //Property for icon left margin.
    property int prIconLeftMargin: 0 //Default value

    contentItem: Item{
        anchors.fill: parent

        /* idTextItem, which provides text for the themes */
        HBText {
            id: idTextItem

            width: 150
            height: 50

            anchors
            {
                left: parent.left
                leftMargin: prTextLeftMargin
                verticalCenter: parent.verticalCenter
            }
            verticalAlignment: Text.AlignVCenter

            text: idLabelWithIcons.text
            fontType: prTextFontType
        }

        /* idIconImageItem, which provides image for theme preset element */
        Image
        {
            id: idIconImageItem
            anchors
            {
                left: parent.left
                leftMargin: prIconLeftMargin
                verticalCenter: parent.verticalCenter
            }

            source: "" //Default value

        }

        /* idIconImageSelected, which provides selected image for theme preset element on changed */
        Image
        {
            id: idRightIconImage
            visible: prThemeSoundVisibility
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 380
            }
            verticalAlignment: Text.AlignVCenter
            source: ""
        }

        Rectangle{
            id:idRectThemeSelectedColor

            width: 99
            height: 39

            anchors
            {
                left: parent.left
                leftMargin: 386
                verticalCenter: parent.verticalCenter
            }

            border.color: "black"
            border.width: 1
            radius: 5

            visible: prThemeColorVisibility
        }

        /* idIconImageFanSpeed, which provides fan speed image */
        Image
        {
            id: idIconImageFanSpeed
            visible: prVisibility
            anchors
            {
                left: parent.left
                leftMargin: 340
                verticalCenter: parent.verticalCenter
            }

            source: ""

        }

        /* idFanSpeedText, which provides fan speed text */
        HBText
        {
            id: idFanSpeedText
            width: 50
            height: 50
            visible: prVisibility
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 385
            }
            verticalAlignment: Text.AlignVCenter
            text: parent.text
            fontType: (enabled) ?  ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
        }

        /* idListSeperatorVerticalline2, which provides vertical seprator line image */
        Image
        {
            id: idListSeperatorVerticalline2
            visible: prVisibility
            anchors
            {
                left: parent.left
                top:parent.top
                topMargin: 18
                leftMargin: 410
            }
            verticalAlignment: Text.AlignVCenter
            source: "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Gfx_ListSeparator_vertical_7in_n-assets/Set_Gfx_ListSeparator_vertical_n.png" //Default value
        }

    /* idTemperatureText, which provides temperature value text */
    HBText
    {
        id: idTemperatureText

        width: 70
        height: 50
        visible: prVisibility
        anchors
        {
            verticalCenter: parent.verticalCenter
            left: idListSeperatorVerticalline2.right
            leftMargin: 10
        }
        verticalAlignment: Text.AlignVCenter
        text: ""
        fontType: (enabled) ?  ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
    }
}
}

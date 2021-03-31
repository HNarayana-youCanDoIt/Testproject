import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0

//Generic button with contentItem as text, icon and button.
ListGenericButton
{
    id: idBtnWithTextIconAndButton

    /** --------PROPERTY FOR TEXT ITEM------------ **/
    //Property for text left margin.
    property int prTextLeftMargin: 14 //Default value

    //Alias for item text.
    property alias prItemText: idTextItem.text

    //Property for text width.
    property int prTextWidth: 382 //Default value

    //Property for text height.
    property int prTextHeight: 39 //Default value ------->> orig: 24

    //Property for text font type.
    property int prTextFontType: ThemeMgr.FONTTYPE_T35_C3

    /*
     * Alias for button. It is used to get the release events of button and to
     * set background images of the item, like default image, pressed image and
     * disabled image.
     */
    property alias prButtonItem: idButtonItem


    contentItem: Item
    {
        id: idBtnContentItem
        anchors.fill: parent

        //Setting HBText property
        HBText
        {
            id: idTextItem
            width: prTextWidth
            height: prTextHeight
            anchors
            {
                left: parent.left
                leftMargin: prTextLeftMargin
                verticalCenter: idBtnContentItem.verticalCenter
            }

            text: ""
            fontType: prTextFontType
            horizontalAlignment: HBText.AlignLeft
            verticalAlignment: HBText.AlignVCenter
        }

        //Setting button property
        GenericButton
        {
            id: idButtonItem
            width: 76
            height: 76
            anchors
            {
                left: parent.left
                leftMargin: 412 //Default value
                verticalCenter: idBtnContentItem.verticalCenter
            }

            defaultImageURL: ""
            pressedImageURL: ""
            disabledImageURL: ""
        }
    }
    pressedImageURL: "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png"
}



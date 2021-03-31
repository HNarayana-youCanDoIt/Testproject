import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0

//Generic button with contentItem as text, icon and button.
ListGenericButton
{
    id: idBtnWithTextIconAndButton

    width: 442
    height: 61

    /** --------PROPERTY FOR TEXT ITEM------------ **/
    //Property for text left margin.
    property int prTextLeftMargin: 11 //Default value

    //Alias for item text.
    property alias prItemText: idTextItem.text

    //Property for text width.
    property int prTextWidth: 246 //Default value

    //Property for text height.
    property int prTextHeight: 23 //Default value

    //Property for text font type.
    property int prTextFontType: ThemeMgr.FONTTYPE_T35_C3

    /** --------PROPERTY FOR ICON ITEM------------ **/
    //Property for icon left margin.
    property int prIconLeftMargin: 264 //Default value

    //Alias for icon source image.
    property alias prIconImage: idIconImageItem.source

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

            onContentHeightChanged: {
                height = contentHeight
            }

            anchors
            {
                left: parent.left
                leftMargin: prTextLeftMargin
                verticalCenter: idBtnContentItem.verticalCenter
            }
            text: ""
            fontType: prTextFontType
        }

        //Setting Image property
        Image
        {
            id: idIconImageItem

            anchors
            {
                left: parent.left
                leftMargin: prIconLeftMargin
                verticalCenter: idBtnContentItem.verticalCenter
            }
            source: "" //Default value
        }

        //Setting button property
        GenericButton
        {
            id: idButtonItem

            width: 70
            height: 70
            anchors
            {
                left: parent.left
                leftMargin: 404 //Default value
                verticalCenter: idBtnContentItem.verticalCenter
            }
            defaultImageURL: "qrc:/image/Set_Ico_Delete/Set_Ico_Delete_n.png"
            pressedImageURL: "qrc:/image/Set_Ico_Delete/Set_Ico_Delete_nf.png"
            disabledImageURL: "qrc:/image/Set_Ico_Delete/Set_Ico_Delete_nd.png"
        }
    }
    pressedImageURL: "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png"
}


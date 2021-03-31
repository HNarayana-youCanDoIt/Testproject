import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0

Item {
    id: idBtnwithIconCmpnt

    width: 610
    height: 68

    /***properties that will be exposed to access the attributes of this Component from outside***/

    /*** Property to whether align the icon on left or right.
    For left and default, its true and for icon on right its false  **/
    property bool isIconOnLeft: true

    /*
     * Property for icon's left margin.
     */
    property int prIconLeftMargin: 32

    /*
     * Property for icon's right margin.
     */
    property int prIconRightMargin: 32

    /*
     * Property for icon's topMargin.
     */
    property int prIconTopMargin: 10

    /*
     * Property for icon's verticalCenter.
     */
    property var prIconVerticalCenter: idBtnContentItem.verticalCenter

    /*
     *  set  text of the Label using this property
     */
    property alias prText: idText.text

    /*
     * Property for text width.
     */
    property alias prTextWidth: idText.width

    /*
     * Property for text height.
     */
    property alias prTextHeight: idText.height

    /*
     * Property for text left margin.
     */
    property int prTextLeftMargin: (isIconOnLeft) ? 48 : 32

    /*
     * Property for verticalCenter of text.
     */
    property var prTextVerticalCenter: idBtnContentItem.verticalCenter

    /*
     * Property for enabled text font type.
     */
    property int prEnabledTextFontType: ThemeMgr.FONTTYPE_T35_C3

    /*
     * Property for disabled text font type.
     */
    property int prDisabledTextFontType: ThemeMgr.FONTTYPE_T35_C3_DISABLED

    /*
     * Property for default image Source of icon.
     */
    property string prDefaultIconImage: ""

    /*
     * Property for pressed image Source of icon.
     */
    property string prPressedIconImage: ""

    /*
     * Property for disabled image Source of icon.
     */
    property string prDisabledIconImage: ""

    /*
     * Alias for button. It is used to get the release events of button and to
     * set background images of the item, like default image, pressed image and
     * disabled image.
     */
    property alias button: idBtnWthIcnAndText

    /*
     * This is mainly a Button with contentItem Icon and Text.
     */
    ListGenericButton {
        id: idBtnWthIcnAndText

        width: parent.width
        height: parent.height

        contentItem: Item {
            id: idBtnContentItem

            anchors.fill: parent

            Image {
                id: idIconImage

                source: idBtnWthIcnAndText.enabled ? (idBtnWthIcnAndText.prPressed ? prPressedIconImage : prDefaultIconImage) : prDisabledIconImage

                /*** Setting the anchors of Icon Image according to the choice given through isIconOnLeft Property  ***/
                anchors {
                    left: (isIconOnLeft) ? parent.left : undefined
                    right: (isIconOnLeft) ? undefined : parent.right
                    leftMargin: (isIconOnLeft) ? prIconLeftMargin : undefined
                    rightMargin: (isIconOnLeft) ? undefined : prIconRightMargin
                    verticalCenter: prIconVerticalCenter
                }
            }

            HBText {
                id: idText

                width: 500
                height: 50

                onContentHeightChanged: {
                    height = contentHeight
                }

                visible: (text !== "")

                text: "Default"

                /*** Setting the anchors of Text according to the choice given through isIconOnLeft Property  ***/
                anchors {
                    left: (isIconOnLeft) ? idIconImage.right : parent.left
                    leftMargin: prTextLeftMargin
                    verticalCenter: prTextVerticalCenter
                }

                fontType: (enabled) ? prEnabledTextFontType : prDisabledTextFontType
            }
        }

        pressedImageURL: "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png"
    }
    /*********************************************************************************************************************


        Example To Use Generic List Item With Icon and Text

        ListItemWithIconComp
        {

            id: idIconWthLabelCompnt
            width: idList.list.contentWidth
            height: 70
            isIconOnLeft:true
            prDefaultIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/MuteUnmuteIcons/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Mute_n.png"
            prPressedIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/MuteUnmuteIcons/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Mute_nf.png"
            prDisabledIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/MuteUnmuteIcons/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Mute_nd.png"

            isIconOnLeft: true

            prIconLeftMargin: 0
            prIconTopMargin: 0

            prTextWidth: 104
            prTextHeight: 19
            prTextLeftMargin: 0

            prText: cppAudioAdaptor.muteActive ? qsTr("Unmute") : qsTr("Mute")
            prTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

            prTextVerticalCenter: prIconVerticalCenter

            button.onReleased: {
                   // Do your work here on button release.
            }
        }
*/
}

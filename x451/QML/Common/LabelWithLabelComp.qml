/* This component contains a Label With Label button. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import com.harman.qml.thememanager 1.0

/* Text label which is derived from generic button */
HBButtonListItem {
    id: idLabelwithLabelButton

    /* Alias provided to assign the Sub-Text of corresponding Main-Text */
    property alias prItemSubText: idItemSubText.text

    /* Alias provided to assign the value of Main text width.*/
    property alias prMainTextWidth: idItemMainText.width

    /* Alias provided to assign the value of Sub text width.*/
    property alias prSubTextWidth: idItemSubText.width

    /* Alias provided to assign the value of Main text font type.*/
    property alias prMainTextFontType: idItemMainText.fontType

    /* Alias provided to assign the value of Sub text font type.*/
    property alias prSubTextFontType: idItemSubText.fontType

    pressedImageURL: enabled ? "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png" : ""

    contentItem: Item {
        anchors.fill: parent
        /* HBText Component which will hold the title of the list item */
        HBText {
            id: idItemMainText

            width: 200
            height: 23

            anchors {
                left: parent.left
                leftMargin: 11
                verticalCenter: parent.verticalCenter
            }

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            text: idLabelwithLabelButton.text
        }

        /* HBText Component which will hold the Sub Text of the list item */
        HBText {
            id: idItemSubText

            width: 200
            height: 23

            anchors {
                right: parent.right
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }

            text: ""

            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter


        }
    }

}

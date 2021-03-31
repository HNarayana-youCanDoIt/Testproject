/* This component contains a text label which is derived from generic button, can be used in the lists like Setup & Engg. menu */
import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common/"
import com.harman.qml.thememanager 1.0


/*
 * Text label which is derived from List generic button, can be used in the
 * lists like Setup & Engg. menu
 */
ListGenericButton {
    contentItem: HBText {
        /**
         * TODO: Currently the font used is not matching with the generic list screen
         * layout as per provided by TML, need to check with TML to provide new FONT or
         * change the existing FONT properties.
         */
        fontType: ThemeMgr.FONTTYPE_T35_C3
        height: 74
        width: 400

        anchors {
            left: parent.left
            leftMargin: 11
        }
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        text: parent.text

        onEnabledChanged: {
            fontType = (enabled) ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED
        }
    }

    pressedImageURL: "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png"
}

/* This component contains a Auto Suggestion list element button. */
import QtQuick 2.7
import QtQuick.Layouts 1.3
import com.harman.qml.thememanager 1.0
import "../../Common"

/* Auto Suggestion list item derived from generic button */
HBButtonListItem {

    /* property for W3W address */
    property alias prAddress: idAddress.text

    /* property for nearest place */
    property alias prNearestPlace: idNearestPlace.text

    /* Property for Flag Image */
    property alias prFlagImage: idFlagImage.source

    ColumnLayout {

        width: parent.width
        height: parent.height

        anchors {
            left: parent.left
            leftMargin: 13
        }

        RowLayout {

            id: idFirstRow

            Image {
                id: idSlashImage

                width: 33
                height: 23

                source: "qrc:/image/W3W/KeyPad/W3W_Marker_Logo-assets/W3W_Marker_Logo.png"
            }

            /* HBText used to show W3W Address */
            HBText {
                id: idAddress
                horizontalAlignment: HBText.AlignLeft
                verticalAlignment: HBText.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
            }
        }

        RowLayout {

            anchors {
                top: idFirstRow.bottom
                topMargin: 5
            }

            Image {
                id: idFlagImage

                width: 32
                height: 24
            }

            /* HBText used to show Nearest Place */
            HBText {
                id: idNearestPlace
                horizontalAlignment: HBText.AlignLeft
                verticalAlignment: HBText.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
            }
        }
    }
}


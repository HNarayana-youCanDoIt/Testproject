/* This component contains a favourites/recent list element */
import QtQuick 2.7
import QtQuick.Layouts 1.3
import com.harman.qml.thememanager 1.0
import "../../Common"

/* Favorite list item derived from generic button */
HBButtonListItem {

    /* property for W3W address */
    property alias prW3WAddress: idW3WAddress.text

    /* property for W3W address  label */
    property alias prW3WAddressLabel: idW3WAddressLabel.text

    /* property for Edit label button for W3W Address */
    property alias prEditLabelButton: idEditLabelButton

    /* property for Delete button for W3W Address */
    property alias prDeleteButton: idDeleteButton

    ColumnLayout {

        width: parent.width
        height: parent.height

        RowLayout {

            anchors {
                top: parent.top
                topMargin: 12
            }

            Image {
                id: idSlashImage

                width: 33
                height: 23

                anchors {
                    left: parent.left
                    leftMargin: 18
                }

                source: "qrc:/image/W3W/KeyPad/W3W_Marker_Logo-assets/W3W_Marker_Logo.png"
            }

            /* HBText used to show W3W Address */
            HBText {
                id: idW3WAddress

                anchors {
                    left: parent.left
                    leftMargin: 60
                }

                horizontalAlignment: HBText.AlignLeft
                verticalAlignment: HBText.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T35_C3
            }

            /* Generic button to show Setup button */
            GenericButton {
                id: idDeleteButton

                anchors {
                    left: parent.left
                    leftMargin: 418
                }
            }
        }

        RowLayout {

            anchors {
                top: parent.top
                topMargin: 75
            }

            /* Generic button to show Setup button */
            GenericButton {
                id: idEditLabelButton

                anchors {
                    left: parent.left
                    leftMargin: -9
                }
            }

            /* HBText used to show Nearest Place */
            HBText {
                id: idW3WAddressLabel

                anchors {
                    left: parent.left
                    leftMargin: 60
                }

                horizontalAlignment: HBText.AlignLeft
                verticalAlignment: HBText.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
            }
        }
    }
}


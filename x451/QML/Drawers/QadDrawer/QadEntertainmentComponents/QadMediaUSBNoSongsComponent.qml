import QtQuick 2.7
import "../../../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: idMediaUSBNoSongsComponent

    anchors.fill: parent

    /*
     * USB source info button, onclick of this HMI needs to
     * launch the USB screen.
     */
    GenericButton {
        id: idSourceInfoButton

        anchors.fill: parent

        contentItem: Item {

            anchors.fill: parent

            /*
             * Image field to show USB source icon.
             */
            Image {
                id: idCurrentEntSourceIcon

                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }

                source: "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_USB_7in_n-assets/Gen_Drawer_Ico_USB_na.png"
            }

            /*
            * Label to show the 'No playable audio files'.
            */
            HBText {
                id: idTxtMetadata

                width: 350
                height: 22

                anchors {
                    left: idCurrentEntSourceIcon.right
                    verticalCenter: parent.verticalCenter
                }

                text: qsTr("No playable audio files") + cppThemeMgr.languageChanged

                elide: Text.ElideRight
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
            }
        }
        onReleased: {
            cppDrawersApp.qmlLog("QadMediaUSBNoSongsComponent.qml: SourceInfo button released.")
            maxDrawerClicked()
            cppAudioAdaptor.switchToActiveEntertainmentSourceScreen()
        }
    }
}

import QtQuick 2.7
import "../../../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: idAUXComponent

    anchors.fill: parent

    /*
     * AUX source info button, onclick of this HMI needs to
     * launch the AUX screen.
     */
    GenericButton {
        id: idSourceInfoButton

        anchors.fill: parent

        contentItem: Item {

            anchors.fill: parent

            /*
             * Image field to show AUX source icon.
             */
            Image {
                id: idCurrentEntSourceIcon

                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }

                source: (enabled
                         ? "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_AUX_7in_n-assets/Gen_Drawer_Ico_AUX_na.png"
                         : "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_AUX_7in_n-assets/Gen_Drawer_Ico_AUX_nd.png")
            }

            /*
            * Label to show the Playing from AUX text.
            */
            HBText {
                id: idTxtMetadata

                width: 200
                height: 22

                anchors {
                    left: idCurrentEntSourceIcon.right
                    verticalCenter: parent.verticalCenter
                }

                text: qsTr("TEXT_SOURCE_AUX_IN_PLAYING") + cppThemeMgr.languageChanged

                elide: Text.ElideRight
                fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
            }
        }
        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadAUXComponent.qml: SourceInfo button released.")
            maxDrawerClicked()
            cppAudioAdaptor.switchToActiveEntertainmentSourceScreen()
        }
    }
}

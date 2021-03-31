import QtQuick 2.7
import "../../../Common"
import QtQuick.Layouts 1.3
import com.harman.qml.mediaenum 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.carplayenums 1.0

Item {
    id: idMediaComponent

    anchors.fill: parent


    /*
     * Current Media source info button, onclick of this HMI needs to
     * launch the Media screen.
     */
    GenericButton {
        id: idSourceInfoButton

        anchors.fill: parent


        contentItem: Item {

            anchors.fill: parent

            /*
             * Image field to show Current media source icon.
             */
            Image {
                id: idCurrentEntSourceIcon

                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }

                source: prActiveEntertainmentSourceIcon
            }

            /*
             * The column to show Song title label and song artist name label.
             */
            ColumnLayout {
                id: idSourceInfoTextColumn

                width: parent.width
                height: 48
                spacing: 10

                anchors {
                    left: parent.left
                    leftMargin: 75
                    verticalCenter: parent.verticalCenter
                }

                /*
                 * Label to show the current playing song title text.
                 */
                HBText {
                    id: idSongTitleText

                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: 22

                    anchors.verticalCenter: (cppAppleCarPlayAdaptor.cpMediaSongArtist === "") ? parent.verticalCenter : undefined

                    text: cppAppleCarPlayAdaptor.cpMediaSongTitle

                    elide: Text.ElideRight
                    fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                }

                /*
                 * Label to show the current playing song artist text.
                 */
                HBText {
                    id: idArtistText

                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: 22

                    text: cppAppleCarPlayAdaptor.cpMediaSongArtist

                    elide: Text.ElideRight
                    fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
                }
            }
        }

        onReleased: {
            cppDrawersApp.qmlLog("QadCPMediaComponent.qml: SourceInfo button released.")
            maxDrawerClicked()
            cppAppleCarPlayAdaptor.setIsCPSwitchable(true)
            cppAppleCarPlayAdaptor.showCPMusicScreen()
        }
    }
}

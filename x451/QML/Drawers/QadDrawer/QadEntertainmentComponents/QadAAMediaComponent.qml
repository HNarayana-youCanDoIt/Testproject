import QtQuick 2.7
import "../../../Common"
import QtQuick.Layouts 1.3
import com.harman.qml.mediaenum 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.androidautoenums 1.0

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

                width: 163
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

                    anchors.verticalCenter: (cppAndroidAutoAdaptor.aaMediaSongArtist === "") ? parent.verticalCenter : undefined

                    text: cppAndroidAutoAdaptor.aaMediaSongTitle

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

                    text: cppAndroidAutoAdaptor.aaMediaSongArtist

                    elide: Text.ElideRight
                    fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
                }
            }
        }

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadAAMediaComponent.qml: SourceInfo button released.")
            maxDrawerClicked()
            cppAndroidAutoAdaptor.setCanSwitchMode(true)
            cppAndroidAutoAdaptor.showAAMusicScreen()
        }
    }

    /*
     * Previous/Reverse button for Media
     */
    GenericButton {
        id: idPrviousButton

        width: 76
        height: parent.height

        anchors {
            left: parent.left
            leftMargin: 279
            verticalCenter: parent.verticalCenter
        }

        defaultImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastRewind_7in_n-assets/Gen_Drawer_Button_Rewind_na.png"
        pressedImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastRewind_7in_n-assets/Gen_Drawer_Button_Rewind_nf.png"
        disabledImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastRewind_7in_n-assets/Gen_Drawer_Button_Rewind_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadAAMediaComponent.qml: Previous Button released.")
            cppAndroidAutoAdaptor.prev()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Play/Pause button
     */
    GenericButton {
        id: idPlayPauseButton

        width: 76
        height: parent.height

        anchors {
            left: parent.left
            leftMargin: 374
            verticalCenter: parent.verticalCenter
        }

        defaultImageURL: (( AndroidAutoEnums.EN_AA_MEDIA_PLAY_STATE_PLAYING ===
                           cppAndroidAutoAdaptor.aaMediaPlayState
                           )
                          ? "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Pause_n.png"
                          : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Play_n.png")
        pressedImageURL: (( AndroidAutoEnums.EN_AA_MEDIA_PLAY_STATE_PLAYING ===
                           cppAndroidAutoAdaptor.aaMediaPlayState
                           )
                          ? "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Pause_nf.png"
                          : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Play_nf.png")
        disabledImageURL: (( AndroidAutoEnums.EN_AA_MEDIA_PLAY_STATE_PLAYING ===
                            cppAndroidAutoAdaptor.aaMediaPlayState
                            )
                           ? "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Pause_nd.png"
                           : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Play_nd.png")

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadAAMediaComponent.qml: PlayPause Button released.")

            cppAndroidAutoAdaptor.togglePlayPause()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Next/Forward button for AndroidAuto Media
     */
    GenericButton {
        id: idNextButton

        width: 76
        height: parent.height

        anchors {
            left: parent.left
            leftMargin: 468
            verticalCenter: parent.verticalCenter
        }

        defaultImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastForward_7in_n-assets/Gen_Drawer_Button_Forward_na.png"
        pressedImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastForward_7in_n-assets/Gen_Drawer_Button_Forward_nf.png"
        disabledImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_FastForward_7in_n-assets/Gen_Drawer_Button_Forward_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadAAMediaComponent.qml: NextButton released.")
            cppAndroidAutoAdaptor.next()
            resetMaxDrawerCloseTimer()

        }
    }
}

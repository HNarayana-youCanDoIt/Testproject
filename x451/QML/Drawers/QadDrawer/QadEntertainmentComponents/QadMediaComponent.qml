import QtQuick 2.7
import "../../../Common"
import QtQuick.Layouts 1.3
import com.harman.qml.mediaenum 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.audioenums 1.0

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

                width: 205//163
                height: 48
                spacing: 10

                anchors {
                    left: idCurrentEntSourceIcon.right
                    verticalCenter: parent.verticalCenter
                }

                /*
                 * Label to show the current playing song title text.
                 */
                HBText {
                    id: idSongTitleText

                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: 22

                    anchors.verticalCenter: (MediaAdaptor.songArtist === "") ? parent.verticalCenter : undefined

                    text: MediaAdaptor.songTitle

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

                    text: MediaAdaptor.songArtist

                    elide: Text.ElideRight
                    fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
                }
            }
        }

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadMediaComponent.qml: SourceInfo button released.")
            maxDrawerClicked()
            cppAudioAdaptor.switchToActiveEntertainmentSourceScreen()
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

        enabled: (AudioEnums.SRC_BT_A2DP1 === cppAudioAdaptor.activeEntSrc) ? MediaAdaptor.isNextPrevSupported : true

        onPressed: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: Previous Button pressed.")
            resetMaxDrawerCloseTimer()
            MediaAdaptor.prev(MediaEnum.EN_BUTTON_STATE_PRESSED)
        }

        onReleased: {
            if(touchAndHold)
            {
                cppDrawersApp.qmlLog(
                            "QadDrawerMaximizedContainer.qml: Previous Button long released.")
                resetMaxDrawerCloseTimer()
                MediaAdaptor.prev(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
            }
            else
            {
                cppDrawersApp.qmlLog(
                            "QadDrawerMaximizedContainer.qml: Previous Button released.")
                resetMaxDrawerCloseTimer()
                MediaAdaptor.prev(MediaEnum.EN_BUTTON_STATE_RELEASED)
            }
        }

        onPressAndHold: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: Previous Button long pressed.")
            resetMaxDrawerCloseTimer()
            MediaAdaptor.prev(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
        }

        onCanceled: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: Previous Button Canceled.")
            resetMaxDrawerCloseTimer()
            MediaAdaptor.prev(MediaEnum.EN_BUTTON_STATE_RELEASED)
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

        defaultImageURL: ((MediaAdaptor.isMediaAudioPlaying)
                          ? "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Pause_n.png"
                          : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Play_n.png")
        pressedImageURL: ((MediaAdaptor.isMediaAudioPlaying)
                          ? "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Pause_nf.png"
                          : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Play_nf.png")
        disabledImageURL: ((MediaAdaptor.isMediaAudioPlaying)
                           ? "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Pause_nd.png"
                           : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Btn_Play_Pause_7in_n-assets/Gen_Drawer_Button_Play_nd.png")

        enabled: (AudioEnums.SRC_BT_A2DP1 === cppAudioAdaptor.activeEntSrc) ? MediaAdaptor.isPlayPauseSupported : true

        //Property to indicate which API was invoked on Press of this button.
        property string prOperationOnPress: ""

        onPressed: {
            cppMediaApp.qmlLog("QadDrawerMaximizedContainer.qml: Play/Pause Btn Pressed!")
            if((MediaAdaptor.isMediaAudioPlaying))
            {
                prOperationOnPress = "pause"
                MediaAdaptor.pause(MediaEnum.EN_BUTTON_STATE_PRESSED)
            }
            else
            {
                prOperationOnPress = "play"
                MediaAdaptor.resume(MediaEnum.EN_BUTTON_STATE_PRESSED)
            }
            resetMaxDrawerCloseTimer()
        }

        onReleased: {
            if(touchAndHold)
            {
                cppMediaApp.qmlLog("QadDrawerMaximizedContainer.qml: Play/Pause Btn Long Released!")

                if("pause" == prOperationOnPress)
                {
                    MediaAdaptor.pause(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                }
                else if("play" == prOperationOnPress)
                {
                    MediaAdaptor.resume(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                }
                else
                {
                    cppMediaApp.qmlLog("QadDrawerMaximizedContainer.qml: prOperationOnPress is NULL")
                }
            }
            else
            {
                cppMediaApp.qmlLog("QadDrawerMaximizedContainer.qml: Play/Pause Btn Released!")

                if("pause" == prOperationOnPress)
                {
                    MediaAdaptor.pause(MediaEnum.EN_BUTTON_STATE_RELEASED)
                }
                else if("play" == prOperationOnPress)
                {
                    MediaAdaptor.resume(MediaEnum.EN_BUTTON_STATE_RELEASED)
                }
                else
                {
                    cppMediaApp.qmlLog("QadDrawerMaximizedContainer.qml: prOperationOnPress is NULL")
                }
            }

            prOperationOnPress = ""
            resetMaxDrawerCloseTimer()
        }

        onPressAndHold: {
            cppMediaApp.qmlLog("QadDrawerMaximizedContainer.qml: Play/Pause Btn Long Pressed!")
            if("pause" == prOperationOnPress)
            {
                MediaAdaptor.pause(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
            }
            else if("play" == prOperationOnPress)
            {
                MediaAdaptor.resume(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
            }
            else
            {
                cppMediaApp.qmlLog("QadDrawerMaximizedContainer.qml: prOperationOnPress is NULL")
            }
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Next/Forward button for Media
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

        enabled: (AudioEnums.SRC_BT_A2DP1 === cppAudioAdaptor.activeEntSrc) ? MediaAdaptor.isNextPrevSupported : true

        onPressed: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: NextButton pressed.")
            resetMaxDrawerCloseTimer()
            MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_PRESSED)
        }

        onReleased: {
            if(touchAndHold)
            {
                cppDrawersApp.qmlLog(
                            "QadDrawerMaximizedContainer.qml: NextButton long released.")
                resetMaxDrawerCloseTimer()
                MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
            }
            else
            {
                cppDrawersApp.qmlLog(
                            "QadDrawerMaximizedContainer.qml: NextButton released.")
                resetMaxDrawerCloseTimer()
                MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_RELEASED)
            }
        }

        onPressAndHold: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: NextButton long pressed.")
            resetMaxDrawerCloseTimer()
            MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
        }

        onCanceled: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: NextButton canceled.")
            resetMaxDrawerCloseTimer()
            MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_RELEASED)
        }
    }
}

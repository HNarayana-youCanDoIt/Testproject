import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.audioenums 1.0
import com.harman.qml.drawersenums 1.0


Item {
    id: idVolumeBarItem

    /*
    Updated logic (16112018):
    1. HMI shall display volume bar if it receives volume notification with prop 'bUserInitiated:true'
    2. HMI shall display Mute status when it receives Mute notification
    3. HMI shall take no action when HU is unmuted. Instead,
        the current displayed bar shall keep on displaying until he pupup bar times out
    */

    property bool prVolumeBarVisibility: ((!cppAudioAdaptor.muteActive && cppAudioAdaptor.volumeUpdatedByUser)
                                              || (prVolumeBarVisibility && !prMuteStatusVisibilty)
                                          || (cppAudioAdaptor.muteActive && cppAudioAdaptor.volumeUpdatedByUser && (0 === cppAudioAdaptor.activeSourceVolume)))

    property bool prMuteStatusVisibilty: ((cppAudioAdaptor.muteActive && cppDrawersAdaptor.showMuteStatus
                                           && !(cppAudioAdaptor.volumeUpdatedByUser && (0 === cppAudioAdaptor.activeSourceVolume)))
                                          || (prMuteStatusVisibilty && !prVolumeBarVisibility))


    width: (prMuteStatusVisibilty ? 160 : 485)
    height: 76

    Image {
        id: idVolumeIcon

        visible: prVolumeBarVisibility

        source: (AudioEnums.EN_VOLUME_UPDATE_GROUP_PROMPT === cppAudioAdaptor.volumeUpdateGroup ||
                 AudioEnums.EN_VOLUME_UPDATE_GROUP_VR === cppAudioAdaptor.volumeUpdateGroup ||
                 AudioEnums.EN_VOLUME_UPDATE_GROUP_TA === cppAudioAdaptor.volumeUpdateGroup)
                ? "qrc:/image/Drawers/NotificationOverlays/Pop_Ico_NotificationVolume_7in_n-assets/Set_Ico_NotificationVolume2_7in_n.png"
                : (AudioEnums.EN_VOLUME_UPDATE_GROUP_PHONE === cppAudioAdaptor.volumeUpdateGroup)
                  ? "qrc:/image/Drawers/NotificationOverlays/Pop_Ico_CallVolume_7in_n-assets/Set_Ico_CallVolume_7in_n.png"
                  : (AudioEnums.EN_VOLUME_UPDATE_GROUP_ENT === cppAudioAdaptor.volumeUpdateGroup)
                    ? "qrc:/image/Drawers/NotificationOverlays/Pop_Ico_MediaVolume_7in_n-assets/Pop_Ico_MediaVolume_n.png"
                    : (AudioEnums.EN_VOLUME_UPDATE_GROUP_PDC_RVC === cppAudioAdaptor.volumeUpdateGroup)
                      ? "qrc:/image/Drawers/NotificationOverlays/Set_Ico_ParkAssist_7in_n-assets/Set_Ico_PDCVolume_7in_na.png"
                      : "qrc:/image/Drawers/NotificationOverlays/Pop_Ico_MediaVolume_7in_n-assets/Pop_Ico_MediaVolume_n.png"
    }

    ProgressBar {
        id: idVolumeProgressBar

        anchors {
            left: idVolumeIcon.right
            leftMargin: -4
        }

        from: 0
        to: 30

        value: cppAudioAdaptor.activeSourceVolume

        visible: prVolumeBarVisibility

        background: Image {
            id: idProgressBarBgImg
            source: "qrc:/image/Drawers/NotificationOverlays/Gen_Gfx_VolumeLargeSlider_7in_n-assets/Gen_Gfx_VolumeLarge_bg_nd.png"
        }
        contentItem: Item {

            /*
                 * This is the item which is used to show the progress.
                 * This will show the progress using the white dots.
                 */
            Item {
                width: idVolumeProgressBar.visualPosition * idProgressBarBgImg.width
                height: parent.height

                clip: true

                Image {
                    id: idProgressBarImg
                    source: "qrc:/image/Drawers/NotificationOverlays/Gen_Gfx_VolumeLargeSlider_7in_n-assets/Gen_Gfx_VolumeLarge_Overlay_na.png"
                }
            }
        }
    }

    /*
     * This text field is used to show the volume current value.
     */
    HBText {
        id: idVolumeValueText

        width: 64
        height: 34

        visible: prVolumeBarVisibility

        anchors {
            left: idVolumeProgressBar.right
            leftMargin: 10
            verticalCenter: idVolumeProgressBar.verticalCenter
        }

        text: idVolumeProgressBar.value

        fontType: ThemeMgr.FONTTYPE_T45_C1_WHITE
    }

    /*
         * If VolumeBar is in slideIn state and user do Mute, the HMI will show
         * Mute Icon on VolumeBar.
         */
    Image{
        id: idMuteIcon

        anchors.verticalCenter: parent.verticalCenter

        visible: prMuteStatusVisibilty
        source: "qrc:/image/Drawers/NotificationOverlays/Popup_Ico_Mute_7in_n.png"
    }

    /*
         * This text field is used to show the Mute text.
         */
    HBText {
        id: idMuteText

        visible: prMuteStatusVisibilty

        width: 120
        height: 22

        anchors{
            left: idMuteIcon.right
            verticalCenter: parent.verticalCenter
        }

        text: qsTr("TEXT_QAD_LABEL_MUTE") + cppThemeMgr.languageChanged

        fontType: ThemeMgr.FONTTYPE_T35_C3
    }
    Component.onCompleted: {
        cppDrawersApp.qmlLog("VolumeNotification.qml: Component.onCompleted")
    }
}

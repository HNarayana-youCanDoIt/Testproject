import QtQuick 2.7
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.audioenums 1.0
import com.harman.qml.phoneenum 1.0
import com.harman.qml.powerenums 1.0

Item {
    id: idActiveEntSourceInfoItem

    /*
     * Binding for MediaOff Info and Unknown Source Info.
     */
    /************************* Binding for Media Info Started. ***********************************/
    Binding{
        target: idTitleText
        property: "text"
        value: ""
        when: ( ((PowerModeEnums.VPM_MEDIA_OFF !== cppPowerModeAdaptor.powerMode) && (AudioEnums.EN_ENT_SOURCE_UNKNOWN === cppAudioAdaptor.activeEntSrc))
               ||(AudioEnums.SRC_HDD === cppAudioAdaptor.activeEntSrc)
               || cppPhoneAdaptor.doesCallExist )
    }

    Binding{
        target: idCurrentEntSourceIcon
        property: "source"
        value: ""
        when: (PowerModeEnums.VPM_MEDIA_OFF === cppPowerModeAdaptor.powerMode
               ||(AudioEnums.SRC_HDD === cppAudioAdaptor.activeEntSrc)
               || AudioEnums.EN_ENT_SOURCE_UNKNOWN === cppAudioAdaptor.activeEntSrc)
    }

    /*
     * Binding for MediaOff mode.
     */
    /************************* Binding for Media Off mode Started. ***********************************/
    Binding{
        target: idTitleText
        property: "text"
        value: qsTr("TEXT_MEDIA_OFF_LABEL") + cppThemeMgr.languageChanged
        when: ((PowerModeEnums.VPM_MEDIA_OFF === cppPowerModeAdaptor.powerMode)
               && (!cppPhoneAdaptor.doesCallExist))
    }

    /****************************************************************************************************/

    /*
     * Binding for Tuner source Info.
     */
    /************************* Binding for Tuner source Info Started. ***********************************/
    Binding{
        target: idTitleText
        property: "text"
        value: cppTunerAdaptor.strBand + " " + cppTunerAdaptor.strFrequency + " " + cppTunerAdaptor.strFrequencyUnit + cppThemeMgr.languageChanged
        when: (((cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_TUNER_FM) ||
              (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_TUNER_AM) ||
              (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_TUNER_DRM)) &&  !cppPhoneAdaptor.doesCallExist)
    }

    Binding{
        target: idCurrentEntSourceIcon
        property: "source"
        value: "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_TunAMFM_7in_n-assets/Gen_Ico_RadioAMFM_n.png"
        when: ((cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_TUNER_FM) ||
              (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_TUNER_AM) ||
              (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_TUNER_DRM))
    }

    /************************* Binding for Tuner source Info end. ***********************************/

    /*
     * Binding for Media source Info.
     */
    /************************* Binding for Media source Info Started. ***********************************/
    Binding{
        target: idTitleText
        property: "text"
        value: MediaAdaptor.songTitle
        when: (((cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_USB1) ||
              (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1) ||
              (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_IPOD)) &&  !cppPhoneAdaptor.doesCallExist)
    }

    Binding{
        target: idCurrentEntSourceIcon
        property: "source"
        value: "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_USB_7in_n-assets/Gen_Ico_USB_n.png"
        when: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_USB1)
    }

    Binding{
        target: idCurrentEntSourceIcon
        property: "source"
        value: "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_BTAudio_n-assets/Sts_Ico_BTAudio_n.png"
        when: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1)
    }

    Binding{
        target: idCurrentEntSourceIcon
        property: "source"
        value: "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_iPod_n-assets/Sts_Ico_iPod_n.png"
        when: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_IPOD)
    }


    /************************* Binding for Media source Info End. ***********************************/


    /*
     * Binding for AUX source Info.
     */
    /************************* Binding for AUX source Info Started. ***********************************/
    Binding{
        target: idTitleText
        property: "text"
        value: qsTr("") + cppThemeMgr.languageChanged
        when: ((cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_AUDIO_AUX) && !cppPhoneAdaptor.doesCallExist)
    }

    Binding{
        target: idCurrentEntSourceIcon
        property: "source"
        value: "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Aux_n-assets/Sts_Ico_Aux_n.png"
        when: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_AUDIO_AUX)
    }

    /************************* Binding for AUX source Info End. ***********************************/

    /*
     * Binding for AndroidAuto Media source Info.
     * ToDo: Need to discuss(Can we show AA media source Info in header status,
     * If it currently playing.) currently showing nothing if AA Media is activated.
     */
    /************************* Binding for AndroidAuto Media source Info Started. ***********************************/
    Binding{
        target: idTitleText
        property: "text"
        value: cppAndroidAutoAdaptor.aaMediaSongTitle
        when: ((cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_GAL_MEDIA) &&  !cppPhoneAdaptor.doesCallExist)
    }

    Binding{
        target: idCurrentEntSourceIcon
        property: "source"
        value: "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_AndroidAuto_7in_n-assets/Sts_Ico_AndroidAuto_n.png"
        when: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_GAL_MEDIA)
    }

    /************************* Binding for AndroidAuto Media source Info End. ***********************************/

    /*
     * Binding for AppleCarPlay Media source Info.
     */
    /************************* Binding for AppleCarPlay Media source Info Started. ***********************************/
    Binding{
        target: idTitleText
        property: "text"
        value: cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus
               ? cppAppleCarPlayAdaptor.cpMediaSongTitle
               : ""
        when: ((cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_CARPLAY_MEDIA) &&  !cppPhoneAdaptor.doesCallExist)
    }

    Binding{
        target: idCurrentEntSourceIcon
        property: "source"
        value: cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus
               ? "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_CarPlay_7in_n-assets/Sts_Ico_CarPlay_n.png"
               : ""
        when: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_CARPLAY_MEDIA)
    }

    /************************* Binding for AppleCarPlay Media source Info End. ***********************************/


    /*
     * Image field to show Current entertainment source icon.
     */
    Image {
        id: idCurrentEntSourceIcon

        visible: !idMutIcon.visible
        width: 60
        height: 40

        anchors {
            left: parent.left
            leftMargin: 5
            top: parent.top
            topMargin: 5
        }

        source: ""
    }

    /*
     * Label to show the current playing song title text.
     */
    HBText {
        id: idTitleText

        width: 144
        height: 18
        visible: !idMuteText.visible

        anchors {
            left: idCurrentEntSourceIcon.right
            verticalCenter: idCurrentEntSourceIcon.verticalCenter
        }

        text: ""

        elide: Text.ElideRight
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
    }

    /*
     *   Mute Icon and Mute text Need to show, When system is in mute state
     *   in Place of Entertainment info.
     */

    /*
     * Image field to show Current entertainment source icon.
     */
    Image {
        id: idMutIcon

        visible: ((((PowerModeEnums.VPM_MEDIA_OFF !== cppPowerModeAdaptor.powerMode) &&
                   (AudioEnums.EN_ENT_SOURCE_UNKNOWN !== cppAudioAdaptor.activeEntSrc)) ||
                    cppPhoneAdaptor.doesCallExist) &&
                    cppAudioAdaptor.muteActive)

        anchors {
            left: parent.left
            leftMargin: 5
            top: parent.top
            topMargin: 5
        }

        source: "qrc:/image/Drawers/HeaderStatusBar/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Mute_n.png"
    }

    /*
     * Text field to show Mute
     */
    HBText{
        id: idMuteText

        width: 144
        height: 18

        visible: idMutIcon.visible

        anchors {
            left: idMutIcon.right
            verticalCenter: idMutIcon.verticalCenter
        }

        text: qsTr("Mute") + cppThemeMgr.languageChanged

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
    }

}

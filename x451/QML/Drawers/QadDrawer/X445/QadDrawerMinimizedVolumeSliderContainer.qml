/* This component contains a QAD volume slider with customized background and handle. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "../../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.powerenums 1.0

Item {
    id: idQADVolumeSliderContainerItem

    /* Property to hold the active source volume from service */
    property int prVolumeSliderValue: cppAudioAdaptor.activeSourceVolume

    property int prMaxVol : 30

    property int prMinVol: 0

    Column {

        spacing: 10

        /* Volume Plus button */
        HBGenericButton {

            width: 72
            height: 72

            anchors.horizontalCenter: parent.horizontalCenter

            defaultImageURL: "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_Volume_plus_n-assets/Gen_Drawer_Ico_Volume_plus_na.png"
            pressedImageURL: "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_Volume_plus_n-assets/Gen_Drawer_Ico_Volume_plus_np.png"
            disabledImageURL: "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_Volume_plus_n-assets/Gen_Drawer_Ico_Volume_plus_nd.png"

            enabled: ( (prVolumeSliderValue < prMaxVol) &&
                       ( (PowerModeEnums.VPM_MEDIA_OFF !== cppPowerModeAdaptor.powerMode) || cppPhoneAdaptor.doesCallExist ))

            onPressed: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml : Volume Plus Button onPressed")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_UP, HardkeyEnum.HKEY_STATE_PRESSED)
            }

            onCanceled: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml : Volume Plus Button onCanceled")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_UP, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onReleased: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml: Volume Plus Button onReleased")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_UP, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onExited: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml: Volume Plus Button onExited")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_UP, HardkeyEnum.HKEY_STATE_RELEASED)
            }
        }

        /* Mute button */
        GenericButton {
            width: 72
            height: 72
            anchors.horizontalCenter: parent.horizontalCenter

            defaultImageURL: cppAudioAdaptor.muteActive ? "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Unmute_7in_n-assets/Gen_Drawer_Ico_Volume_on.png" : "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Volume_off.png"
            pressedImageURL: cppAudioAdaptor.muteActive ? "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Unmute_7in_n-assets/Gen_Drawer_Ico_Volume_on_np.png" : "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Volume_off_np.png"
            disabledImageURL: cppAudioAdaptor.muteActive ? "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Unmute_7in_n-assets/Gen_Drawer_Ico_Volume_on_nd.png" : "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Volume_off_nd.png"

            enabled: ( (PowerModeEnums.VPM_MEDIA_OFF !== cppPowerModeAdaptor.powerMode) || cppPhoneAdaptor.doesCallExist )

            onPressed: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml : Mute Button onPressed")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_MUTE, HardkeyEnum.HKEY_STATE_PRESSED)
            }

            onCanceled: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml : Mute Button onCanceled")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_MUTE, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onReleased: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml: Mute Button onReleased")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_MUTE, HardkeyEnum.HKEY_STATE_RELEASED)
            }
        }

        /* Volume Minus button */
        HBGenericButton {

            width: 72
            height: 72

            anchors.horizontalCenter: parent.horizontalCenter

            defaultImageURL: "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_Volume_minus_n-assets/Gen_Drawer_Ico_Volume_minus_na.png"
            pressedImageURL: "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_Volume_minus_n-assets/Gen_Drawer_Ico_Volume_minus_np.png"
            disabledImageURL: "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_Volume_minus_n-assets/Gen_Drawer_Ico_Volume_minus_nd.png"

            enabled: ( (prVolumeSliderValue > prMinVol) &&
                       ( (PowerModeEnums.VPM_MEDIA_OFF !== cppPowerModeAdaptor.powerMode) || cppPhoneAdaptor.doesCallExist ))

            onPressed: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml : Volume Minus Button onPressed")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_DOWN, HardkeyEnum.HKEY_STATE_PRESSED)
            }

            onCanceled: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml : Volume Minus Button onCanceled")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_DOWN, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onReleased: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml: Volume Minus Button onReleased")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_DOWN, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onExited: {
                cppDrawersApp.qmlLog("QadDrawerMinimizedVolumeSliderContainer.qml: Volume Minus Button onExited")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_DOWN, HardkeyEnum.HKEY_STATE_RELEASED)
            }
        }
    }

}

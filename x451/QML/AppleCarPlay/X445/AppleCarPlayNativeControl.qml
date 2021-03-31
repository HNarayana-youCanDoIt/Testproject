import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.powerenums 1.0
import com.harman.qml.hvacenums 1.0

Item {
    id: idQADVolumeSliderContainerItem

    width: 52
    height: 480
    /* Property to hold the active source volume from service */
    property int prVolumeSliderValue: cppAudioAdaptor.activeSourceVolume

    property int prMaxVol : 30

    property int prMinVol: 0

    // Background image
    BorderImage {
        id: idNativeControlBorderImage
        source: (cppThemeMgr.themeTypeFolderPath + "CarPlay_Gfx_sidepopupbg.png")
        width: 52
        height: 480
        x:0
        y:0
    }

    //HVAC info
    Item {
        id: idClimateInfoItem

        visible: ((cppHVACAdaptor.ccmPresence === HVACEnums.HVAC_CCM_PRESENT) &&
                  (cppPowerModeAdaptor.powerMode !== PowerModeEnums.VPM_ONE_HOUR))

        anchors {
            top: parent.top
            left: parent.left
        }

        /*
         * ClimateStausIcon: This will show the climet status, Like if climate is
         * ON, This will show climate on icon, else climateOff icon.
         */
        Image{
            id: idClimateStatusIcon
            width: 30
            height: 30

            anchors {
                top: parent.top
                left: parent.left
                topMargin: 10
                leftMargin: 12
            }

            source: cppHVACAdaptor.ctrlPanelMode ? "qrc:/image/NativeControlBar/icons/Sts_Ico_HVAC2_n-assets/Sts_Ico_HVAC2_n.png"
                                                 : "qrc:/image/NativeControlBar/icons/Sts_Ico_HVAC2_n-assets/Sts_Ico_HVAC_nd.png"
        }

        // Item to show the temperature details
        Item {
            id: idTempItem

            anchors {
                top: parent.top
                left: parent.left
                topMargin: 60
                leftMargin: 5
            }

            /*
             * TextField to show the temperature.
             */
            HBText{
                id: idTemperatureText

                width: 45
                height: 19

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

                visible: ((cppHVACAdaptor.ctrlPanelMode) && (cppHVACAdaptor.errorStatus !== HVACEnums.HVAC_ERROR))

                /*
                 * The toFixed() method converts a number into a string, keeping a
                 * specified number of decimals.
                 * Here we are showing 1 value after decimal
                 */
                text: ((cppHVACAdaptor.temperature < cppHVACAdaptor.temperatureLowLimit) ?
                           qsTr("LO")
                         : (cppHVACAdaptor.temperature > cppHVACAdaptor.temperatureHighLimit) ?
                               qsTr("HI") : cppHVACAdaptor.temperature.toFixed(1))+ cppThemeMgr.languageChanged

                fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2
            }
        }

        /*
         * This item contains Fan Icon, Fan speed text, Temperature text and °C
         * text. This item is needed because we have to make the visibility of this
         * Item's content item's to false if climate is off.
         */
        Item {
            id: idFanTemperatureDetailsItem
            visible: cppHVACAdaptor.ctrlPanelMode

            width: 49
            height: 30

            anchors {
                top: parent.top
                left: parent.left
                topMargin: 100
                leftMargin: ((cppHVACAdaptor.errorStatus === HVACEnums.HVAC_ERROR) || cppHVACAdaptor.autoMode) ? 0: 7
            }
            /*
            * FanIcon: Image field to show the fan icon.
            */
            Image{
                id: idFanIcon
                visible: (!cppHVACAdaptor.autoMode && (cppHVACAdaptor.errorStatus !== HVACEnums.HVAC_ERROR))
                source: "qrc:/image/NativeControlBar/icons/Sts_Ico_HVACAir2_n-assets/Sts_Ico_HVACAir_n.png"
            }

            /*
            * TextField to show the fan speed.
            */
            HBText{
                id: idFanSpeedText

                width: 19
                height: 19
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideNone
                anchors {
                    left: (cppHVACAdaptor.autoMode || (cppHVACAdaptor.errorStatus === HVACEnums.HVAC_ERROR))
                          ? parent.left : idFanIcon.right
                    verticalCenter: idFanIcon.verticalCenter
                    topMargin: 106
                }

                text: ((cppHVACAdaptor.errorStatus === HVACEnums.HVAC_ERROR) ? qsTr("Error!")
                                                                             : (cppHVACAdaptor.autoMode ?
                                                                                    qsTr("AUTO") :
                                                                                    cppHVACAdaptor.fanSpeed)) + cppThemeMgr.languageChanged

                fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2

            }
        }
    }

    //Volume controls
    Column {

        spacing: 26
        anchors {
            bottom: parent.bottom
            left: parent.left
            bottomMargin: 18
            leftMargin: 5
        }

        /* Volume Plus button */
        HBGenericButton {

            width: 42
            height: 42

            anchors.horizontalCenter: parent.horizontalCenter

            defaultImageURL: "qrc:/image/NativeControlBar/icons/Gen_Drawer_Ico_Volume_plus2_n-assets/Gen_Drawer_Ico_Volume_plus2_n.png"
            pressedImageURL: "qrc:/image/NativeControlBar/icons/Gen_Drawer_Ico_Volume_plus2_n-assets/Gen_Drawer_Ico_Volume_plus2_np.png"
            disabledImageURL: "qrc:/image/NativeControlBar/icons/Gen_Drawer_Ico_Volume_plus2_n-assets/Gen_Drawer_Ico_Volume_plus2_nd.png"

            enabled: ((prVolumeSliderValue < prMaxVol) && (PowerModeEnums.VPM_MEDIA_OFF !== cppPowerModeAdaptor.powerMode))

            onPressed: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml : Volume Plus Button onPressed")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_UP, HardkeyEnum.HKEY_STATE_PRESSED)
            }

            onCanceled: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml : Volume Plus Button onCanceled")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_UP, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onReleased: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml: Volume Plus Button onReleased")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_UP, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onExited: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml: Volume Plus Button onExited")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_UP, HardkeyEnum.HKEY_STATE_RELEASED)
            }
        }

        /* Mute button */
        GenericButton {
            width: 42
            height: 42
            anchors.horizontalCenter: parent.horizontalCenter

            defaultImageURL: cppAudioAdaptor.muteActive ? "qrc:/image/NativeControlBar/icons/Gen_Drawer_Ico_Volume2_on-assets/Gen_Drawer_Ico_Volume2_on_n.png"
                                                        : "qrc:/image/NativeControlBar/icons/Gen_Drawer_Ico_Volume2_on-assets/Gen_Drawer_Ico_Volume2_off_n.png"
            pressedImageURL: cppAudioAdaptor.muteActive ? "qrc:/image/NativeControlBar/icons/Gen_Drawer_Ico_Volume2_on-assets/Gen_Drawer_Ico_Volume2_on_p.png"
                                                        : "qrc:/image/NativeControlBar/icons/Gen_Drawer_Ico_Volume2_on-assets/Gen_Drawer_Ico_Volume2_off_np.png"
            disabledImageURL: cppAudioAdaptor.muteActive ? "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Unmute_7in_n-assets/Gen_Drawer_Ico_Volume_on_nd.png"
                                                         : "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Volume_off_nd.png"

            enabled: PowerModeEnums.VPM_MEDIA_OFF !== cppPowerModeAdaptor.powerMode

            onPressed: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml : Mute Button onPressed")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_MUTE, HardkeyEnum.HKEY_STATE_PRESSED)
            }

            onCanceled: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml : Mute Button onCanceled")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_MUTE, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onReleased: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml: Mute Button onReleased")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_MUTE, HardkeyEnum.HKEY_STATE_RELEASED)
            }
        }

        /* Volume Minus button */
        HBGenericButton {

            width: 42
            height: 42

            anchors.horizontalCenter: parent.horizontalCenter

            defaultImageURL: "qrc:/image/NativeControlBar/icons/Gen_Drawer_Ico_Volume_minus2_n-assets/Gen_Drawer_Ico_Volume_minus2_n.png"
            pressedImageURL: "qrc:/image/NativeControlBar/icons/Gen_Drawer_Ico_Volume_minus2_n-assets/Gen_Drawer_Ico_Volume_minus2_np.png"
            disabledImageURL: "qrc:/image/NativeControlBar/icons/Gen_Drawer_Ico_Volume_minus2_n-assets/Gen_Drawer_Ico_Volume_minus2_nd.png"

            enabled: ((prVolumeSliderValue > prMinVol) && (PowerModeEnums.VPM_MEDIA_OFF !== cppPowerModeAdaptor.powerMode))

            onPressed: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml : Volume Minus Button onPressed")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_DOWN, HardkeyEnum.HKEY_STATE_PRESSED)
            }

            onCanceled: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml : Volume Minus Button onCanceled")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_DOWN, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onReleased: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml: Volume Minus Button onReleased")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_DOWN, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onExited: {
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml: Volume Minus Button onExited")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_VOLUME_DOWN, HardkeyEnum.HKEY_STATE_RELEASED)
            }
        }
    }

    /* The below code is to start the fade out of the native control bar as soon as we get the carplay projection status as false
      But at the momment the below code has no affect since the signal is received at the same time the HMI state and screen is changed */
    Connections {
        target: cppAppleCarPlayAdaptor
        onSigAppleCarPlayProjectionStatusChanged: {
            if(false === cppAppleCarPlayAdaptor.appleCarPlayProjectionStatus) {                                
                cppAppleCarPlayApp.qmlLog("AppleCarPlayNativeControl.qml: fade out animation started")
                idNativeControlItemFadeOutAnimation.start()
            }
        }
    }

    NumberAnimation {
        id: idNativeControlItemFadeOutAnimation
        target: idQADVolumeSliderContainerItem
        property: "opacity"
        from: 1
        to: 0
        duration: 50
        easing.type: Easing.Linear
    }
}

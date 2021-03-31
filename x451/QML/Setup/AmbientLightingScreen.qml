import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common/"
import com.harman.qml.thememanager 1.0
import com.harman.qml.vehicleenums 1.0
import com.harman.qml.popupenums 1.0
import com.harman.qml.powerenums 1.0

BaseUI {
    id:idAmbientLightingScreen

    /*
     * This property is used to check that the
     * ambient light illumination level is updated by user or
     * not. because we have to call service api
     * only if user changes the brightness, at
     * the time of component load the slider position also gets changed.
     * No need to call service api that time.
     */
    property bool isUserInitiated: false

    /* TitleLabel of Setup screen */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_VEHICLE_SETTINGS_AMBIENT_LIGHTING") + cppThemeMgr.languageChanged
    }

    /* Here this connections made to check the current power mode status and on one hour mode
        if user is inside the ambient light screen, switch screen to main setup */
    Connections{
        target: cppPowerModeAdaptor
        onSigPowerModeChanged :{
            if(PowerModeEnums.VPM_ONE_HOUR === cppPowerModeAdaptor.powerMode)
            {
                cppSetupApp.switchScreenToMainSetup()
            }
            else
            {
                //Do nothing
            }
        }
    }

    Connections{
        target: cppVehicleAdaptor

        /* Here this connections made to check the current park lamp status and when park lamp status comes as false
            if user is inside the ambient light screen, switch screen to vehicle setup */
        onSigParkLampStatusChanged :{
            if(!cppVehicleAdaptor.parkLampStatus)
            {
                cppSetupApp.raiseSMEvent("", "Back")
            }
            else
            {
                //Do nothing
            }
        }

        /* If user is inside the ambient light screen and the BCM presence is changed to false, then switch screen to main setup */
        onSigBCMPresenceChanged: {
            if( (false === cppVehicleAdaptor.bCmPresence) )
            {
                cppSetupApp.switchScreenToMainSetup()
            }
            else
            {
                //Do nothing
            }
        }

        /* If user is inside the ambient light screen and the ambient light presence is changed to false, then switch screen to vehicle setup */
        onSigAmbientLightModeIlluOnHuChanged: {
            if( (false === cppVehicleAdaptor.ambientLightModeIlluOnHu) )
            {
                cppSetupApp.switchScreenToVehicleSetup()
            }
            else
            {
                //Do nothing
            }
        }

        /* If user is inside the ambient light screen and the Bcm Ucs state is changed to false, then switch screen to vehicle setup */
        onSigBcmUcsStateChanged: {
            if( (false === cppVehicleAdaptor.bcmUcsState) )
            {
                cppSetupApp.switchScreenToVehicleSetup()
            }
            else
            {
                //Do nothing
            }
        }
    }

    /*
    * Image, which holds the interieor of vehicle
    */
    Image {
        id: idAmbientLightInterior

        anchors {
            left: parent.left
            leftMargin: 237
            top: parent.top
            topMargin: 128
        }

        source: "qrc:/image/Setup/Set_Gfx_MoodlightingInterieur1_7in_n-assets/Set_Gfx_MoodlightingInterieur1_7in_n.png"
    }

    /*
    * Image, which holds the color of front part of interior
    */
    Image {
        id: idAmbientLightFrontColor

        anchors {
            left: parent.left
            leftMargin: 271
            top: parent.top
            topMargin: 147
        }

        visible: (cppVehicleAdaptor.ambientLightMode === VehicleEnums.AMBIENT_LIGHT_ON_MODE)
        source: "qrc:/image/Setup/Set_Gfx_MoodlightingInterieur1_7in_n-assets/Set_Gfx_Moodlighting_BigFrontColour4_7in_na.png"
    }

    /*Note: This code is commented here because in vehicle ambient light will be available in front seat only.*/

    /*
    * Image, which holds the color of rear part of interior
    */
//    Image {
//        id: idAmbientLightRearColor

//        anchors {
//            left: parent.left
//            leftMargin: 340
//            top: parent.top
//            topMargin: 186
//        }

//        visible: (cppVehicleAdaptor.ambientLightMode === VehicleEnums.AMBIENT_LIGHT_ON_MODE)
//        source: "qrc:/image/Setup/Set_Gfx_MoodlightingInterieur1_7in_n-assets/Set_Gfx_Moodlighting_BigRearColour4_7in_na.png"
//    }


    /*
    * HU Brightness control slider.
    */
    HorizontalSlider {
        id: idAmbientLightSlider

        width: 360
        height: 46

        anchors {
            left: parent.left
            leftMargin: 220
            top: parent.top
            topMargin: 357
        }

        prSliderLeftMargin: 0
        prSliderNextBtnLeftMargin: 0
        prSliderPrevBtnLeftMargin: 0

        prMinVal: 1
        prMaxVal: cppVehicleAdaptor.ambLightIllumLevel

        slider.value: cppVehicleAdaptor.ambSelIlluminationLevel

        enabled: ((cppVehicleAdaptor.ambientLightMode === VehicleEnums.AMBIENT_LIGHT_ON_MODE) && (cppVehicleAdaptor.ambLightEnableStatus))

        prProgressFillVisibility: true

        sliderImage.source: "qrc:/image/Drawers/QAD/Maximized/Contents/BrightnesSliderImages/Drw_Gfx_BrightnessSlider_7in_n-assets/Drawer_Gfx_BrightnessSlider_nd.png"


        slider.onPressedChanged: {
            if (!slider.pressed)
            {
                cppSetupApp.qmlLog(
                            "AmbientLightingScreen.qml: Brightness slider onPressedChanged, slider Value: " + Math.round(
                                slider.value))
                isUserInitiated = false
                cppVehicleAdaptor.invSetAmbIlluminationSelUserInitaited(isUserInitiated)
                cppVehicleAdaptor.invSetAmbLightIllumLevel(Math.round(slider.value))
            }
            else
            {
                isUserInitiated = true
                cppVehicleAdaptor.invSetAmbIlluminationSelUserInitaited(isUserInitiated)
            }
        }

        slider.onPositionChanged: {
            cppSetupApp.qmlLog(
                        "AmbientLightingScreen.qml: Brightness slider onPositionChanged, slider Value: " + Math.round(
                            slider.value) + " isUserInitiated " + isUserInitiated)
            if(isUserInitiated)
            {
                cppVehicleAdaptor.setAmbLightillumLevelAttribute(Math.round(slider.value))
            }
            else
            {
                //Do nothing.
            }
        }

        slider.onValueChanged: {
            cppSetupApp.qmlLog(
                        "AmbientLightingScreen.qml: Brightness slider onValueChanged, slider Value: " + Math.round(
                            slider.value))
        }

        /* This signal gets emitted on slider buttons click and we are making API call from here */
        onSigSliderBtnClicked: {
            cppSetupApp.qmlLog(
                        "AmbientLightingScreen.qml: Brightness slider onSigSliderBtnClicked, slider Value: " + Math.round(
                            slider.value) + stepSize)
            cppVehicleAdaptor.setAmbLightillumLevelAttribute(Math.round(slider.value + stepSize))
        }
    }


    RowLayout {
        id:idOnOffBtnRowLayout
        spacing: 12
        anchors{
            left: parent.left
            leftMargin: 285
            top:parent.top
            topMargin: 430
        }

    /**
         * idAmbientLightOnBtn, on clicked Ambient Light will switch on
         */

    GenericButton {
        id: idAmbientLightOnBtn
        width: 112
        height: 47
        defaultImageURL: (cppVehicleAdaptor.ambientLightMode === VehicleEnums.AMBIENT_LIGHT_ON_MODE) ? "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png" : "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"
        pressedImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png"
        disabledImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"

        contentItem:HBText{
            id:idAmbientLightOnText
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
            text: qsTr("On")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        /** here the updateAudioPresetsListIndex called to set the current preset as selected
         * which will highlight the selected preset.
         */
        onReleased: {
            cppSetupApp.qmlLog("AmbientLightingScreen.qml: On btn onReleased: ")
            cppVehicleAdaptor.setAmbLightModeAttribute(VehicleEnums.AMBIENT_LIGHT_ON_MODE)
        }
    }

    /**
         * idAmbientLightOffBtn, on clicked Ambient Light mode will switch off
         */

    GenericButton {
        id: idAmbientLightOffBtn
        width: 112
        height: 47
        defaultImageURL: (cppVehicleAdaptor.ambientLightMode === VehicleEnums.AMBIENT_LIGHT_OFF_MODE) ? "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png" : "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"
        pressedImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png"
        disabledImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"

        contentItem:HBText{
            id:idAmbientLightOffText
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
            text: qsTr("Off")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        /** here the updateAudioPresetsListIndex called to set the current preset as selected
         * which will highlight the selected preset.
         */
        onReleased: {
            cppSetupApp.qmlLog("AmbientLightingScreen.qml: Off btn onReleased")
            cppVehicleAdaptor.setAmbLightModeAttribute(VehicleEnums.AMBIENT_LIGHT_OFF_MODE)
        }
    }
    }
}

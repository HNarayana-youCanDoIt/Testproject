import QtQuick 2.7
import QtQuick.Layouts 1.3
import "../../../Common"
import com.harman.qml.hvacenums 1.0
import com.harman.qml.thememanager 1.0

Item {
    id: idHvacDrawerWithXpressCoolingContainerItem

    /*
     * AirFlow Icon.
     * Display the current Air Vent Mode Icon.
     */
    Image {
        id: idAirFlowIcon
        visible: cppHVACAdaptor.airFlowPresence

        anchors {
            left: parent.left
            leftMargin: 159//257 - 98
            top: parent.top
            topMargin: 21
        }
        source: (HVACEnums.HVAC_DM_CHEST_MODE === cppHVACAdaptor.distributionMode)
                ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Climate_7in_n-assets/Drw_Ico_Climate1_n.png"
                : (HVACEnums.HVAC_DM_CHESTLEG_MODE === cppHVACAdaptor.distributionMode)
                  ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Climate_7in_n-assets/Drw_Ico_Climate2_n.png"
                  : (HVACEnums.HVAC_DM_LEG_MODE === cppHVACAdaptor.distributionMode)
                    ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Climate_7in_n-assets/Drw_Ico_Climate3_n.png"
                    : (HVACEnums.HVAC_DM_LEGDEFROST_MODE === cppHVACAdaptor.distributionMode)
                      ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Climate_7in_n-assets/Drw_Ico_Climate4_n.png"
                      : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Climate_7in_n-assets/Drw_Ico_Climate5_n.png"
    }

    /*
     * Increase button of AirFlow.
     * OnClick: Change Air Vent Mode in the folowing sequence:
     * 1. Chest Mode 2. Chest+Leg Mode 3. Leg Mode
     * 4. Leg +Defrost Mode 5. Defrost Mode
     * and then Loop back to Chest Mode
     */
    GenericButton {
        id: idAirFlowNextButton
        visible: cppHVACAdaptor.airFlowPresence

        width: 76
        height: 76

        anchors {
            left: parent.left
            leftMargin: 355
            top: parent.top
            topMargin: 49
        }

        anchors.verticalCenter: idAirFlowIcon.verticalCenter

        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nf.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainerWithXpressCooling.qml: idAirFlowNextButton released.")
            cppHVACAdaptor.increaseDistributionMode()
            resetMaxDrawerCloseTimer()
        }
    }

    HBText {
        id: idACText
        visible: cppHVACAdaptor.acPresence

        width: 79
        height: 16

        //        x: 564
        //        y: 39

        anchors {
            left: parent.left
            leftMargin: 466 // 564 - 98
            top: parent.top
            topMargin: 44 //39
            //verticalCenter: idAirFlowIcon.verticalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

        text: qsTr("TEXT_HVAC_AC") + cppThemeMgr.languageChanged
    }

    /*
     *  AC ON/OFF button: 2 States: ON OFF
     */
    GenericButton {
        id: idACOnOffButton
        visible: cppHVACAdaptor.acPresence

        width: 76
        height: 76

        //        x: 692
        //        y: 13

        anchors {
            left: parent.left
            leftMargin: 594 // 692 - 98
            top: parent.top
            topMargin: 13
            //verticalCenter: idAirFlowIcon.verticalCenter
        }

        defaultImageURL: cppHVACAdaptor.acMode ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_On_na.png" : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_Off_na.png"
        pressedImageURL: cppHVACAdaptor.acMode ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_On_np.png" : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_Off_np.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainerWithXpressCooling.qml: idACOnOffButton released.")

            cppHVACAdaptor.toggleAcMode()
            resetMaxDrawerCloseTimer()
        }
    }

    HBText {
        id: idEconText
        visible: cppHVACAdaptor.econPresence

        width: 79
        height: 16

        //        x: 564
        //        y: 120

        anchors {
            left: parent.left
            leftMargin: 466 // 564 - 98
            top: parent.top
            topMargin: 125 //120
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        text: qsTr("TEXT_HVAC_ECON") + cppThemeMgr.languageChanged
    }

    // Econimical On / Off
    GenericButton {
        id: idEconOnOffButton
        visible: cppHVACAdaptor.econPresence

        width: 76
        height: 76

        //        x: 692
        //        y: 96

        anchors {
            left: parent.left
            leftMargin: 594 // 692 - 98
            top: parent.top
            topMargin: 96
        }


        defaultImageURL: cppHVACAdaptor.ecoAcMode
                         ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_On_na.png"
                         : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_Off_na.png"
        pressedImageURL: cppHVACAdaptor.ecoAcMode
                         ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_On_nf.png"
                         : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_Off_np.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainerWithXpressCooling.qml: idEconOnOffButton released.")
            cppHVACAdaptor.toggleEcoAcMode()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Button to Decrease the temperature.
     * Decrease the Temperature by 0.5 deg C .
     * Disable at Min Value *Actual change in values will be based on the
     * response received from CCM.
     * 3 States 1. Normal 2. Selected 3. Disabled
     */
    GenericButton {
        id: idTempratureDecreaseButton
        visible: cppHVACAdaptor.temperaturePresence

        width: 76
        height: 76

        //        x: 215
        //        y: 210
        anchors {
            left: parent.left
            leftMargin: 117 // 215 - 98
            top: parent.top
            topMargin: 210
        }

        enabled: (cppHVACAdaptor.temperatureLowLimit <= cppHVACAdaptor.temperature)

        // FixMe: Disbled image is not available, used normal image.
        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nf.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainerWithXpressCooling.qml: idTempratureDecreaseButton released.")
            cppHVACAdaptor.decreaseTemperature()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Temperature indicator icon.
     */
    Image {
        id: idTemperatureIndicatorIcon
        visible: cppHVACAdaptor.temperaturePresence

        width: 76
        height: 76

        //        x: 282
        //         y: 210

        anchors {
            left: parent.left
            leftMargin: 200//184 // 282 - 98
            top: parent.top
            topMargin: 210
        }


        source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Temperature_7in_n-assets/Gen_Drawer_Ico_Temperature_n.png"
    }

    /*
     * Text Field to show the temperature value.
     */
    HBText {
        id: idTemperatureValueText
        visible: cppHVACAdaptor.temperaturePresence

        width: 105
        height: 25

        //        x: 337
        //        y: 236

        anchors {
            left: parent.left
            leftMargin: 267 //239 // 337 - 98
            top: parent.top
            topMargin: 236
        }

        // t35px_c3
        fontType: ThemeMgr.FONTTYPE_T35_C3

        /*
         * The toFixed() method converts a number into a string, keeping a specified number of decimals.
         * Here we are showing 1 value after decimal
         */
        text: (cppHVACAdaptor.temperature.toFixed(1) + qsTr("°C")) + cppThemeMgr.languageChanged
    }

    /*
     * Button to Increase the temperature.
     * Increase the Temperature by 0.5 deg C .
     * Disable at Max Value *Actual change in values will be based on the
     * response received from CCM.
     */
    GenericButton {
        id: idTempratureIncreaseButton
        visible: cppHVACAdaptor.temperaturePresence

        width: 76
        height: 76

        //        x: 434
        //        y: 210

        anchors {
            left: parent.left
            leftMargin: 336 // 434 - 98
            top: parent.top
            topMargin: 210
        }

        enabled: (cppHVACAdaptor.temperatureHighLimit >= cppHVACAdaptor.temperature)

        // FixMe: Disbled image is not available, used normal image.
        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nf.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainerWithXpressCooling.qml: idTempratureIncreaseButton released.")
            cppHVACAdaptor.increaseTemperature()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Text Field to show the Auto text.
     */
    HBText {
        id: idAutoText
        visible: cppHVACAdaptor.autoPresence

        width: 79
        height: 16

        //        x: 288
        //        y: 348

        anchors {
            left: parent.left
            leftMargin: 190 // 288 - 98
            top: parent.top
            topMargin: 359//348
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

        text: qsTr("TEXT_HVAC_AUTO") + cppThemeMgr.languageChanged
    }

    /*
     * Auto On Indicator Icon/Button
     */
    GenericButton {
        id: idAutoOnIndicatorButton
        visible: cppHVACAdaptor.autoPresence

        width: 76
        height: 76

        //        x: 369
        //        y: 323

        anchors {
            left: parent.left
            leftMargin: 271 // 369 - 98
            top: parent.top
            topMargin: 331//323
        }


        defaultImageURL: ( cppHVACAdaptor.autoMode
                          ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Indicator_7in_n-assets/Gen_Drawer_Ico_Indicator_n.png"
                          : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Indicator_7in_n-assets/Gen_Drawer_Ico_Indicator_nd.png" )
        /*
         *  This is commented, because from Now onwards Auto can not be change by HMI side.
         *  Uncomment this code and remove below pressedImageURL, If requirement changes again.
         */
        //pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Indicator_7in_n-assets/Gen_Drawer_Ico_Indicator_nf.png"
        pressedImageURL: ( cppHVACAdaptor.autoMode
                          ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Indicator_7in_n-assets/Gen_Drawer_Ico_Indicator_n.png"
                          : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Indicator_7in_n-assets/Gen_Drawer_Ico_Indicator_nd.png" )
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Indicator_7in_n-assets/Gen_Drawer_Ico_Indicator_nd.png"

        /*
         *  This is commented, because from Now onwards Auto can not be change by HMI side.
         *  Uncomment this code, If requirement changes again.
         */
//        onReleased: {
//            cppDrawersApp.qmlLog(
//                        "HvacDrawerContainer.qml: idAutoOnIndicatorButton released.")
//            /*
//             * HMI can only ON the auto mode, if it is off. HMI can not Off
//             * Auto mode if it is ON.
//             */
//            if (!cppHVACAdaptor.autoMode)
//            {
//                cppHVACAdaptor.setHVACParameter(HVACEnums.HUCCM_AUTO_MODE, 1)
//            }
//            else
//            {
//                // Do nothing.
//            }

//            resetMaxDrawerCloseTimer()
//        }
    }

    /*
     * Button to derease the fan speed.
     * Decrease the Blower Speed by 1.
     * Disable at Min Value *Actual change in values will be based on the
     * response received from CCM.
     */
    GenericButton {
        id: idFanSpeedDecreaseButton
        visible: cppHVACAdaptor.fanPresence

        width: 76
        height: 76

        //        x: 519
        //        y: 210

        anchors {
            left: parent.left
            leftMargin: 421 // 519 - 98
            top: parent.top
            topMargin: 210
        }


        enabled: (cppHVACAdaptor.fanSpeedLowLimit !== cppHVACAdaptor.fanSpeed)

        // FixMe: Disbled image is not available, used normal image.
        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nf.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainerWithXpressCooling.qml: idFanSpeedDecreaseButton released.")
            cppHVACAdaptor.decreaseFanSpeed()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Fan Icon
     */
    Image {
        id: idFanIcon
        visible: cppHVACAdaptor.fanPresence

        width: 76
        height: 76

        //        x: 590
        //        y: 210

        anchors {
            left: parent.left
            leftMargin: 499//492 // 590 - 98
            top: parent.top
            topMargin: 210
        }

        source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Fan_7in_n-assets/Gen_Drawer_Ico_Fan_n.png"
    }

    /*
         * Text Field to show the fan speed.
         */
    HBText {
        id: idFanSpeedValueText
        visible: cppHVACAdaptor.fanPresence

        width: 31
        height: 23


        //        x: 648
        //        y: 238

        anchors {
            left: parent.left
            leftMargin: 573//550 // 648 - 98
            top: parent.top
            topMargin: 238
        }

        // t35px_c3
        fontType: ThemeMgr.FONTTYPE_T35_C3

        text: cppHVACAdaptor.fanSpeed
    }

    /*
     * Button to Increase Fan speed.
     * Increase the Blower Speed by 1.
     * Disable at Max Value *Actual change in values will be based on the
     * response received from CCM.
     */
    GenericButton {
        id: idFanSpeedIncreaseButton
        visible: cppHVACAdaptor.fanPresence

        width: 76
        height: 76

        //        x: 712
        //        y: 210

        anchors {
            left: parent.left
            leftMargin: 614 // 712 - 98
            top: parent.top
            topMargin: 210
        }

        enabled: (cppHVACAdaptor.fanSpeedHighLimit !== cppHVACAdaptor.fanSpeed)

        // FixMe: Disbled image is not available, used normal image.
        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nf.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainerWithXpressCooling.qml: idFanSpeedIncreaseButton released.")
            cppHVACAdaptor.increaseFanSpeed()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Climate in air On / Off: Button
     */
    GenericButton {
        id: idFreshAirButton
        visible: cppHVACAdaptor.freshAirPresence

        width: 76
        height: 76

        //        x: 477
        //        y: 328

        anchors {
            left: parent.left
            leftMargin: 379 // 477 - 98
            top: parent.top
            topMargin: 328
        }

        //FixMe: (OPL)The ClimateRecirculatedAir image is not available so used X0 image for that.
        defaultImageURL: (HVACEnums.HVAC_AIRCIRCULATION_FRESHIR_ON === cppHVACAdaptor.airCirculationMode) ?
                             "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_FreshAir_n.png"
                           : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_RecirculatedAir_n.png"
        pressedImageURL: (HVACEnums.HVAC_AIRCIRCULATION_FRESHIR_ON === cppHVACAdaptor.airCirculationMode) ?
                             "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_FreshAir_nf.png"
                           : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_RecirculatedAir_nf.png"
        disabledImageURL: (HVACEnums.HVAC_AIRCIRCULATION_FRESHIR_ON === cppHVACAdaptor.airCirculationMode) ?
                              "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_FreshAir_nd.png"
                            : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_RecirculatedAir_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainerWithXpressCooling.qml: idFreshAirButton released.")
            cppHVACAdaptor.toggleAirCirculationMode()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Xpress Cool: Button
     */
    GenericButton {
        id: idXpressCoolButton
        visible: cppHVACAdaptor.xpressCoolingPresence

        width: 76
        height: 76

        //        x: 591
        //        y: 330

        anchors {
            left: parent.left
            leftMargin: 493 // 591 - 98
            top: parent.top
            topMargin: 330
        }

        defaultImageURL: cppHVACAdaptor.xpressCoolMode
                         ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_On_n.png"
                         : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_Off_n.png"

        pressedImageURL: cppHVACAdaptor.xpressCoolMode
                         ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_On_np.png"
                         : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_Off_np.png"

        disabledImageURL: cppHVACAdaptor.xpressCoolMode
                          ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_On_nd.png"
                          : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_Off_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainerWithXpressCooling.qml: idXpressCoolButton released.")
            cppHVACAdaptor.invToggleXpressCoolMode()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Max Defrost Mode button: This shows the Status of Max Defrost Mode
     * and also ON/OFF the Max Defrost Mode.
     */
    GenericButton {
        id: idDefrostButton
        visible: cppHVACAdaptor.defrostPresence

        width: 76
        height: 76

        //        x: 706
        //        y: 330

        anchors {
            left: parent.left
            leftMargin: 608 // 706 - 98
            top: parent.top
            topMargin: 330
        }

        defaultImageURL: cppHVACAdaptor.maxDefrostMode
                         ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax_na.png"
                         : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax_n.png"
        pressedImageURL: cppHVACAdaptor.maxDefrostMode
                         ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax_nf.png"
                         : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax_nf.png"

        onReleased: {
            cppDrawersApp.qmlLog("HvacDrawerContainerWithXpressCooling.qml: idDefrostButton released.")

            cppHVACAdaptor.setHVACParameter(HVACEnums.HUCCM_MAX_DEFRST, !cppHVACAdaptor.maxDefrostMode)

            resetMaxDrawerCloseTimer()
        }
    }
}

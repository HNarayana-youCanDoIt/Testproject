import QtQuick 2.7
import QtQuick.Layouts 1.3
import "../../../Common"
import com.harman.qml.hvacenums 1.0
import com.harman.qml.thememanager 1.0

Item {
    id: idHvacDrawerContainerItem
    /*
     * Button to Decrease the temperature.
     * Decrease the Temperature by 0.5 deg C .
     * Disable at Min Value *Actual change in values will be based on the
     * response received from CCM.
     * 3 States 1. Normal 2. Selected 3. Disabled
     */
    GenericButton {
        id: idTempratureDecreaseButton

        width: 76
        height: 76

        //        x: 331
        //        y: 35
        anchors {
            left: parent.left
            leftMargin: 149 // 331 - 182
            top: parent.top
            topMargin: 35
        }

        enabled: (cppHVACAdaptor.temperatureLowLimit < cppHVACAdaptor.temperature)

        // FixMe: Disbled image is not available, used normal image.
        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nf.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainer.qml: idTempratureDecreaseButton released.")
            cppHVACAdaptor.decreaseTemperature()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Temperature indicator icon.
     */
    Image {
        id: idTemperatureIndicatorIcon

        width: 76
        height: 76

        //        x: 392
        //         y: 35

        anchors {
            left: parent.left
            leftMargin: 210 // 392 - 182
            top: parent.top
            topMargin: 35
        }


        source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Temperature_7in_n-assets/Gen_Drawer_Ico_Temperature_n.png"
    }

    /*
     * Text Field to show the temperature value.
     */
    HBText {
        id: idTemperatureValueText

        width: 105
        height: 25

        //        x: 450
        //        y: 60

        anchors {
            left: parent.left
            leftMargin: 268 // 450 - 182
            top: parent.top
            topMargin: 60
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

        width: 76
        height: 76

        //        x: 554
        //        y: 35

        anchors {
            left: parent.left
            leftMargin: 372 // 554 - 182
            top: parent.top
            topMargin: 35
        }

        enabled: (cppHVACAdaptor.temperatureHighLimit > cppHVACAdaptor.temperature)

        // FixMe: Disbled image is not available, used normal image.
        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nf.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainer.qml: idTempratureIncreaseButton released.")
            cppHVACAdaptor.increaseTemperature()
            resetMaxDrawerCloseTimer()
        }
    }

    //! Temperature Separator line image
    Image
    {
        id: idTempSepLineImg

        anchors
        {
            left: parent.left
            leftMargin: 122 //304 - 182
            top: parent.top
            topMargin: 157
        }
        source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Gfx_RightLineSeparatorSingleZone_7in_n/Drw_Gfx_RightLineSeparatorSingleZone_7in_n.png"
    }

    /*
     * AirFlow Icon.
     * Display the current Air Vent Mode Icon.
     */
    Image {
        id: idAirFlowIcon

        //x: 354
        //y: 179

        anchors {
            left: parent.left
            leftMargin: 172 //354 - 182
            top: parent.top
            topMargin: 179
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

        width: 76
        height: 76

        //x: 554
        //y: 188

        anchors {
            left: parent.left
            leftMargin: 372 //554 - 182
            top: parent.top
            topMargin: 188
        }

        anchors.verticalCenter: idAirFlowIcon.verticalCenter

        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nf.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainer.qml: idAirFlowNextButton released.")
            cppHVACAdaptor.increaseDistributionMode()
            resetMaxDrawerCloseTimer()
        }
    }

    //! Air Flow Separator line image
    Image
    {
        id: idAirFlowSepLineImg

        anchors
        {
            left: parent.left
            leftMargin: 122 //304 - 182
            top: parent.top
            topMargin: 297
        }
        source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Gfx_RightLineSeparatorSingleZone_7in_n/Drw_Gfx_RightLineSeparatorSingleZone_7in_n.png"
    }

    /*
     * Button to derease the fan speed.
     * Decrease the Blower Speed by 1.
     * Disable at Min Value *Actual change in values will be based on the
     * response received from CCM.
     */
    GenericButton {
        id: idFanSpeedDecreaseButton

        width: 76
        height: 76

        //        x: 331
        //        y: 331

        anchors {
            left: parent.left
            leftMargin: 149 // 331 - 182
            top: parent.top
            topMargin: 331
        }


        enabled: (cppHVACAdaptor.fanSpeedLowLimit !== cppHVACAdaptor.fanSpeed)

        // FixMe: Disbled image is not available, used normal image.
        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nf.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainer.qml: idFanSpeedDecreaseButton released.")
            cppHVACAdaptor.decreaseFanSpeed()
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Fan Icon
     */
    Image {
        id: idFanIcon

        width: 76
        height: 76

        //        x: 432
        //        y: 330

        anchors {
            left: parent.left
            leftMargin: 250 // 432 - 182
            top: parent.top
            topMargin: 330
        }

        source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_Fan_v2_7in_n-assets/Drw_Ico_Fan_v2_7in_n.png"
    }

    /*
         * Text Field to show the fan speed.
         */
    HBText {
        id: idFanSpeedValueText

        width: 31
        height: 23


        //        x: 491
        //        y: 353

        anchors {
            left: parent.left
            leftMargin: 309 // 491 - 182
            top: parent.top
            topMargin: 353
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

        width: 76
        height: 76

        //        x: 554
        //        y: 329

        anchors {
            left: parent.left
            leftMargin: 372 // 554 - 182
            top: parent.top
            topMargin: 329
        }

        enabled: (cppHVACAdaptor.fanSpeedHighLimit !== cppHVACAdaptor.fanSpeed)

        // FixMe: Disbled image is not available, used normal image.
        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nf.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nd.png"

        onReleased: {
            cppDrawersApp.qmlLog(
                        "HvacDrawerContainer.qml: idFanSpeedIncreaseButton released.")
            cppHVACAdaptor.increaseFanSpeed()
            resetMaxDrawerCloseTimer()
        }
    }

    HvacItemsColumn{
        id: idHvacItemColumn
    }
}

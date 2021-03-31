import QtQuick 2.7
import QtQuick.Layouts 1.3
import "../../../Common"
import com.harman.qml.hvacenums 1.0
import com.harman.qml.thememanager 1.0

Item
{
    id: idHvacDrawerDualZoneContainerItem

    //! Dual zone car icon
    Image
    {
        id: idDualZoneCarIcon

        anchors
        {
            left: parent.left
            leftMargin: 245 //343 - 98
            top: parent.top
            topMargin: 140
        }
        source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_DualZoneCar_7in_n-assets/Drw_Gfx_DualZoneCar_7in_n.png"
    }

    //! SYNC button
    GenericButton
    {
        id: idSyncButton

        width: 76
        height: 76

//        x: 406
//        y: 349

        anchors
        {
            left: parent.left
            leftMargin: 308 // 406 - 98
            top: parent.top
            topMargin: 349
        }

        defaultImageURL: (cppHVACAdaptor.dualMode)
                         ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Btn_Sync_7in_n-assets/Drw_Btn_Sync_7in_On_n.png"
                         : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Btn_Sync_7in_n-assets/Drw_Btn_Sync_7in_Off_n.png"
        pressedImageURL: (cppHVACAdaptor.dualMode)
                         ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Btn_Sync_7in_n-assets/Drw_Btn_Sync_7in_On_np.png"
                         : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Btn_Sync_7in_n-assets/Drw_Btn_Sync_7in_Off_np.png"

        onReleased:
        {
            cppDrawersApp.qmlLog(
                        "HvacDrawerDualZoneContainer.qml: idSyncButton released.")
            cppHVACAdaptor.invToggleDualMode()
            resetMaxDrawerCloseTimer()
        }
    }

    //! Co-Passenger Temprature Up button
    GenericButton
    {
        id: idCoPassengerTempUpButton

        width: 76
        height: 76
        enabled: (cppHVACAdaptor.temperatureHighLimit > cppHVACAdaptor.passengerTemperature)
//        x: 229
//        y: 159

        anchors
        {
            left: parent.left
            leftMargin: 131 // 229 - 98
            top: parent.top
            topMargin: 159
        }

        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_np.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nd.png"

        onReleased:
        {
            cppDrawersApp.qmlLog(
                        "HvacDrawerDualZoneContainer.qml: idCopassengerTempUpButton released.")
            cppHVACAdaptor.invIncreasePassengerTmp()
            resetMaxDrawerCloseTimer()
        }
    }

    //! Co-Passenger Temprature Value
    HBText
    {
        id: idCoPassengerTempVal
        width: 70
        height: 25

//        x: 229
//        y: 247

        anchors
        {
            left: parent.left
            leftMargin: 135 // 233 - 98
            top: parent.top
            topMargin: 247
        }

        text: (cppHVACAdaptor.passengerTemperature.toFixed(1) + qsTr("°C")) + cppThemeMgr.languageChanged
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    //! Co-Passenger Temprature Down button
    GenericButton
    {
        id: idCoPassengerTempDownButton

        width: 76
        height: 76
        enabled: (cppHVACAdaptor.temperatureLowLimit < cppHVACAdaptor.passengerTemperature)
//        x: 229
//        y: 285

        anchors
        {
            left: parent.left
            leftMargin: 131 // 229 - 98
            top: parent.top
            topMargin: 285
        }

        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_np.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nd.png"

        onReleased:
        {
            cppDrawersApp.qmlLog(
                        "HvacDrawerDualZoneContainer.qml: idCoPassengerTempDownButton released.")
            cppHVACAdaptor.invDecreasePassengerTmp()
            resetMaxDrawerCloseTimer()
        }
    }

    //! Driver Temprature Up button
    GenericButton
    {
        id: idDriverTempUpButton

        width: 76
        height: 76
        enabled: (cppHVACAdaptor.temperatureHighLimit > cppHVACAdaptor.driverTemperature)
//        x: 568
//        y: 159

        anchors
        {
            left: parent.left
            leftMargin: 470 // 568 - 98
            top: parent.top
            topMargin: 159
        }

        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_np.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nd.png"

        onReleased:
        {
            cppDrawersApp.qmlLog(
                        "HvacDrawerDualZoneContainer.qml: idDriverTempUpButton released.")
            cppHVACAdaptor.invIncreaseDriverTmp()
            resetMaxDrawerCloseTimer()
        }
    }

    //! Driver Temprature Value
    HBText
    {
        id: idDriverTempVal
        width: 70
        height: 25

//        x: 568
//        y: 247

        anchors
        {
            left: parent.left
            leftMargin: 475 // 573 - 98
            top: parent.top
            topMargin: 247
        }

        text: (cppHVACAdaptor.driverTemperature.toFixed(1)+ qsTr("°C")) + cppThemeMgr.languageChanged
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    //! Driver Temprature Down button
    GenericButton
    {
        id: idDriverTempDownButton

        width: 76
        height: 76
        enabled: (cppHVACAdaptor.temperatureLowLimit < cppHVACAdaptor.driverTemperature)
//        x: 568
//        y: 285

        anchors
        {
            left: parent.left
            leftMargin: 470 // 568 - 98
            top: parent.top
            topMargin: 285
        }

        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_np.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nd.png"

        onReleased:
        {
            cppDrawersApp.qmlLog(
                        "HvacDrawerDualZoneContainer.qml: idDriverTempDownButton released.")
            cppHVACAdaptor.invDecreaseDriverTmp()
            resetMaxDrawerCloseTimer()
        }
    }

    //! Fan Speed minimum button
    GenericButton
    {
        id: idFanSpeedMinButton

        width: 76
        height: 76

//        x: 255
//        y: 72

        anchors
        {
            left: parent.left
            leftMargin: 157 // 255 - 98
            top: parent.top
            topMargin: 72
        }

        enabled: (cppHVACAdaptor.fanSpeedLowLimit !== cppHVACAdaptor.fanSpeed)

        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_Fan_v2_7in_n-assets/Drw_Ico_Fan_v2_7in_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_Fan_v2_7in_n-assets/Drw_Ico_Fan_v2_7in_np.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_Fan_v2_7in_n-assets/Drw_Ico_Fan_v2_7in_nd.png"

        onReleased:
        {
            cppDrawersApp.qmlLog(
                        "HvacDrawerDualZoneContainer.qml: idFanSpeedMinButton released.")
            cppHVACAdaptor.decreaseFanSpeed()
            resetMaxDrawerCloseTimer()
        }
    }    

    //! Fan Speed Image
    Image
    {
        id: idFanSpeedVal

//        x: 311
//        y: 100

        anchors
        {
            left: parent.left
            leftMargin: 213 // 311 - 98
            top: parent.top
            topMargin: 100
        }

        source: cppHVACAdaptor.invGetFanSpeedImage(cppHVACAdaptor.fanSpeed)
    }

    //! Fan Speed maximum button
    GenericButton
    {
        id: idFanSpeedMaxButton

        width: 76
        height: 76

//        x: 566
//        y: 72

        anchors
        {
            left: parent.left
            leftMargin: 468 // 566 - 98
            top: parent.top
            topMargin: 72
        }

        enabled: (cppHVACAdaptor.fanSpeedHighLimit !== cppHVACAdaptor.fanSpeed)

        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_Fan_v3_7in_n-assets/Drw_Ico_Fan_v3_7in_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_Fan_v3_7in_n-assets/Drw_Ico_Fan_v3_7in_np.png"
        disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_Fan_v3_7in_n-assets/Drw_Ico_Fan_v3_7in_nd.png"

        onReleased:
        {
            cppDrawersApp.qmlLog(
                        "HvacDrawerDualZoneContainer.qml: idFanSpeedMaxButton released.")
            cppHVACAdaptor.increaseFanSpeed()
            resetMaxDrawerCloseTimer()
        }
    }

    HvacItemsColumn{
        id: idHvacItemColumn
    }
}

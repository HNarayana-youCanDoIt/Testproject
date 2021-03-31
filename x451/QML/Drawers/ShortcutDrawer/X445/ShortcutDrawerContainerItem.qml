import QtQuick 2.7
import "../../../Common"
import com.harman.qml.drawersenums 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.powerenums 1.0
import com.harman.qml.hvacenums 1.0

Item {
    id: idShortcutDrawerContainerItem

    Column {
        width: 84
        height: parent.height
        anchors.right: parent.right

        /*
         * Media Off button.
         */
        GenericButton {
            id: idMediaOffButton

            width: 84
            height: 84

            defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_power_7in_in-assets/Drw_Ico_power_7in_na.png"
            pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_power_7in_in-assets/Drw_Ico_power_7in_np.png"
            disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_power_7in_in-assets/Drw_Ico_power_7in_nd.png"

            onPressed: {
                cppDrawersApp.qmlLog("ShortcutDrawerContainerItem.qml : Media Off button onPressed")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_POWER, HardkeyEnum.HKEY_STATE_PRESSED)
            }

            onCanceled: {
                cppDrawersApp.qmlLog("ShortcutDrawerContainerItem.qml: Media Off button onCanceled")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_POWER, HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onReleased: {
                cppDrawersApp.qmlLog("ShortcutDrawerContainerItem.qml: Media Off button onReleased")
                cppHardkeyAdaptor.invSendKeyCodeEvent(HardkeyEnum.KEYCODETOUCH_POWER, HardkeyEnum.HKEY_STATE_RELEASED)
            }
        }

        /*
         * Climate button to open HVAC Drawer.
         */
        GenericButton {
            id: idClimateButton

            width: 84
            height: 84

            visible: ((cppHVACAdaptor.ccmPresence === HVACEnums.HVAC_CCM_PRESENT) &&
                      (cppPowerModeAdaptor.powerMode !== PowerModeEnums.VPM_ONE_HOUR))

            /*
             * If climate status is ON and One hour mode is not active, then only
             * It will be enable else disable.
             */
            enabled: ((cppHVACAdaptor.ctrlPanelMode) &&  (PowerModeEnums.VPM_ONE_HOUR !== cppPowerModeAdaptor.powerMode))

            defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_AC_7in_n/Gen_Drawer_Ico_AC_na.png"
            pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_AC_7in_n/Gen_Drawer_Ico_AC_nf.png"
            disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_AC_7in_n/Gen_Drawer_Ico_AC_nd.png"

            onPressed: {
                cppDrawersApp.qmlLog("ShortcutDrawerContainerItem.qml : Climate Button onPressed")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onReleased: {
                cppDrawersApp.qmlLog(
                            "ShortcutDrawerContainerItem.qml: Climate Button Clicked.")
                cppDrawersApp.raiseSMEvent(
                            "ShortcutDrawer",
                            DrawersEnums.SHORTCUT_DRAWER_BUTTON_CLIMATE_ID)
            }
        }

        /*
         * Source button to open Source Drawer.
         */
        GenericButton {
            id: idSourceButton

            width: 84
            height: 84

            defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_Source_7in_n/Gen_Drawer_Ico_Source_na.png"
            pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_Source_7in_n/Gen_Drawer_Ico_Source_nf.png"
            disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_Source_7in_n/Gen_Drawer_Ico_Source_nd.png"
            //prEnableColorOverlay: true

            onPressed: {
                cppDrawersApp.qmlLog("ShortcutDrawerContainerItem.qml : Source Button onPressed")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onReleased: {
                cppDrawersApp.qmlLog(
                            "ShortcutDrawerContainerItem.qml: Source Button Clicked.")
                cppDrawersApp.raiseSMEvent(
                            "ShortcutDrawer",
                            DrawersEnums.SHORTCUT_DRAWER_BUTTON_SOURCE_ID)
            }
        }

        /*
         * Home button to go to home screen.
         */
        GenericButton {
            id: idHomeButton

            width: 84
            height: 84

            enabled: cppDrawersAdaptor.enableHomeButton

            defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_Home_7in_n/Gen_Drawer_Ico_Home_na.png"
            pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_Home_7in_n/Gen_Drawer_Ico_Home_nf.png"
            disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_Home_7in_n/Gen_Drawer_Ico_Home_nd.png"

            onPressed: {
                cppDrawersApp.qmlLog("ShortcutDrawerContainerItem.qml : Home Button onPressed")
                // Deactivate VR session
                cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
            }

            onReleased: {
                cppDrawersApp.qmlLog(
                            "ShortcutDrawerContainerItem.qml: Home Button Clicked.")
                cppDrawersApp.raiseSMEvent(
                            "ShortcutDrawer",
                            DrawersEnums.SHORTCUT_DRAWER_BUTTON_HOME_ID)
            }
        }
    }
}

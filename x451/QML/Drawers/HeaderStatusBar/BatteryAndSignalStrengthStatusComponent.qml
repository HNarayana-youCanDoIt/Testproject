import QtQuick 2.7
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0

Item {
    id: idBatteryAndSignalStrengthStatusItem

    /*
     * Image Field to show battery status of connected phone.
     */
    Image{
        id: idBatteryStatusImage

        visible: (PhoneEnum.BATTERY_CHARGE_UNAVAILABLE !== cppPhoneAdaptor.batteryChargeLevel)

        source: (PhoneEnum.BATTERY_CHARGE_LEVEL_ZERO === cppPhoneAdaptor.batteryChargeLevel) ?
                    "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Bluetooth_battery_7in_n-assets/Gen_Ico_StatusBluetooth_battery_1.png"
                  :(PhoneEnum.BATTERY_CHARGE_LEVEL_ONE === cppPhoneAdaptor.batteryChargeLevel) ?
                        "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Bluetooth_battery_7in_n-assets/Gen_Ico_StatusBluetooth_battery_2.png"
                      : (PhoneEnum.BATTERY_CHARGE_LEVEL_TWO === cppPhoneAdaptor.batteryChargeLevel) ?
                            "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Bluetooth_battery_7in_n-assets/Gen_Ico_StatusBluetooth_battery_3.png"
                          : (PhoneEnum.BATTERY_CHARGE_LEVEL_THREE === cppPhoneAdaptor.batteryChargeLevel) ?
                                "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Bluetooth_battery_7in_n-assets/Gen_Ico_StatusBluetooth_battery_4.png"
                              : (PhoneEnum.BATTERY_CHARGE_LEVEL_FOUR === cppPhoneAdaptor.batteryChargeLevel) ?
                                    "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Bluetooth_battery_7in_n-assets/Gen_Ico_StatusBluetooth_battery_5.png"
                                  : (PhoneEnum.BATTERY_CHARGE_LEVEL_FIVE === cppPhoneAdaptor.batteryChargeLevel) ?
                                        "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Bluetooth_battery_7in_n-assets/Gen_Ico_StatusBluetooth_battery_6.png"
                                        : ""
    }

    /*
     * Image Field to show signal strength of connected phone.
     */
    Image{
        id: idSignalStrengthImage

        anchors{
            left: parent.left
            leftMargin: 40
        }

        visible: (PhoneEnum.SIGNAL_STRENGTH_UNAVAILABLE !== cppPhoneAdaptor.signalStrengthLevel)

        source: (PhoneEnum.SIGNAL_STRENGTH_NO_SIM === cppPhoneAdaptor.signalStrengthLevel) ?
                    "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Reception_7in_n-assets/Sts_Ico_Signal_NoSim.png"
                  :(PhoneEnum.SIGNAL_STRENGTH_LEVEL_ZERO === cppPhoneAdaptor.signalStrengthLevel) ?
                        "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Reception_7in_n-assets/Sts_Ico_Reception.png"
                      :(PhoneEnum.SIGNAL_STRENGTH_LEVEL_ONE === cppPhoneAdaptor.signalStrengthLevel) ?
                            "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Reception_7in_n-assets/Sts_Ico_Reception_1.png"
                          : (PhoneEnum.SIGNAL_STRENGTH_LEVEL_TWO === cppPhoneAdaptor.signalStrengthLevel) ?
                                "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Reception_7in_n-assets/Sts_Ico_Reception_2.png"
                              : (PhoneEnum.SIGNAL_STRENGTH_LEVEL_THREE === cppPhoneAdaptor.signalStrengthLevel) ?
                                    "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Reception_7in_n-assets/Sts_Ico_Reception_3.png"
                                  : (PhoneEnum.SIGNAL_STRENGTH_LEVEL_FOUR === cppPhoneAdaptor.signalStrengthLevel) ?
                                        "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Reception_7in_n-assets/Sts_Ico_Reception_4.png"
                                      : (PhoneEnum.SIGNAL_STRENGTH_LEVEL_FIVE === cppPhoneAdaptor.signalStrengthLevel) ?
                                            "qrc:/image/Drawers/HeaderStatusBar/Sts_Ico_Reception_7in_n-assets/Sts_Ico_Reception5.png"
                                            : ""
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("idBatteryAndSignalStrengthStatusItem onCompleted: batteryChargeLevel: " + cppPhoneAdaptor.batteryChargeLevel + "signalStrengthLevel: " + cppPhoneAdaptor.signalStrengthLevel)
    }

}

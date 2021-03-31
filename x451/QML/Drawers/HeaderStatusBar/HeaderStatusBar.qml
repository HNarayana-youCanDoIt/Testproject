import QtQuick 2.7
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.audioenums 1.0
import com.harman.qml.phoneenum 1.0
import com.harman.qml.powerenums 1.0
import com.harman.qml.hvacenums 1.0

Item {
    id: idHeaderStatusBarItem

    width: parent.width
    height: 50

    anchors{
        top: parent.top
        topMargin: -height
    }

    /*
     * ActiveEntSrcInfoComponent: This component is used to show the source info
     * on header status bar.
     */
    ActiveEntSrcInfoComponent{
        id:idActiveEntSrcItem
        width: 176
        height: parent.height
        visible: (!PopupManager.bNotificationVisible && !cppMediaOffAdaptor.mediaOffScreenStatus)
    }

    /*
     * BatteryAndSignalStrengthStatusComponent: This component is used to show
     * the connected phone's battery status and signal strength on header status.
     */
    BatteryAndSignalStrengthStatusComponent{
        id: idBatterySignalStrengthItem

        visible: (cppPhoneAdaptor.hfpConnectionStatus && !PopupManager.bNotificationVisible)
        width: 80
        height: 40

        anchors {
            left: idActiveEntSrcItem.right
            leftMargin: 50//383
            top: parent.top
            topMargin: 4
        }
    }

    /*
     * Component to show the Time details.
     */
    TimeInfoComponent{
        id: idTimeInfoComponent

        width: 85 // 55 (Time width) + 30 (am/pm width)
        height: 18
        visible: ((PowerModeEnums.VPM_MEDIA_OFF != cppPowerModeAdaptor.powerMode) &&
                 (!PopupManager.bNotificationVisible))

        anchors {
            left: idBatterySignalStrengthItem.right
            //leftMargin: 10//467
            top: parent.top
            topMargin: 16
        }
    }

    ClimateInfoComponent {
        id: idClimateInfoComponent
        width: 170
        height: 40
        visible: ((cppHVACAdaptor.ccmPresence === HVACEnums.HVAC_CCM_PRESENT) &&
                  (cppHVACAdaptor.hvacContainerType !== HVACEnums.EN_CONTAINER_TYPE_DUAL_ZONE) &&
                  (cppPowerModeAdaptor.powerMode !== PowerModeEnums.VPM_ONE_HOUR))

        anchors {
            left: parent.left
            leftMargin: 602
            top: parent.top
            topMargin: 5//-1
        }
    }

    ClimateInfoComponentDualZone {
        id: idClimateInfoComponentDualZone
        width: 230
        height: 40
        visible: ((cppHVACAdaptor.ccmPresence === HVACEnums.HVAC_CCM_PRESENT) &&
                  (cppHVACAdaptor.hvacContainerType === HVACEnums.EN_CONTAINER_TYPE_DUAL_ZONE) &&
                  (cppPowerModeAdaptor.powerMode !== PowerModeEnums.VPM_ONE_HOUR))

        anchors {
            left: parent.left
            leftMargin: 532
            top: parent.top
            topMargin: 5//-1
        }
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("HeaderStatusBar.qml: copomnenet completed.")
    }

}

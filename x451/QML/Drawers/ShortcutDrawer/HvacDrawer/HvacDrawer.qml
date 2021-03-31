import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.powerenums 1.0
import com.harman.qml.hvacenums 1.0

Item {
    id: idHvacDrawerItem

    anchors.fill: parent

    /*
     * property holds the state of drawer.
     */
    property string prHvacDrawerState: cppDrawersAdaptor.hvacDrawerState

    Connections{
        target: cppPowerModeAdaptor

        onSigPowerModeChanged:{
            cppDrawersApp.qmlLog("HvacDrawer.qml: onSigPowerModeChanged. powerMode: " + cppPowerModeAdaptor.powerMode)

            // If HVAC drawer is opened and ONE HOUR mode gets activated, close it.
            if (PowerModeEnums.VPM_ONE_HOUR === cppPowerModeAdaptor.powerMode)
            {
                maxDrawerClicked()
            }
            else
            {
                //Do nothing.
            }
        }
    }

    Connections{
        target: cppHVACAdaptor

        onSigCtrlPanelModeChanged:{
            cppDrawersApp.qmlLog("HvacDrawer.qml: onSigCtrlPanelModeChanged. ctrlPanelMode: " + cppHVACAdaptor.ctrlPanelMode)

            // If HVAC drawer is opened and climate gets off, close it.
            if (!cppHVACAdaptor.ctrlPanelMode)
            {
                maxDrawerClicked()
            }
            else
            {
                //Do nothing.
            }
        }
    }

    /*
     * HVAC drawer dual zone container item.
     */
    HvacDrawerDualZoneContainer
    {
        id: idHvacDrawerDualZoneContainer
        visible: (cppHVACAdaptor.hvacContainerType === HVACEnums.EN_CONTAINER_TYPE_DUAL_ZONE)
        anchors {
            right: parent.right
        }

        width: 702
        height: parent.height
    }

    /*
     * HVAC drawer single zone container item.
     */
    HvacDrawerContainer {
        id: idHvacDrawerContainer
        visible: ((cppHVACAdaptor.hvacContainerType === HVACEnums.EN_CONTAINER_TYPE_SINGLE_ZONE)
                  || (cppHVACAdaptor.hvacContainerType === HVACEnums.EN_CONTAINER_TYPE_SINGLE_ZONE_WITH_XPRESS_COOLING))

        width: 702
        height: parent.height
    }
}

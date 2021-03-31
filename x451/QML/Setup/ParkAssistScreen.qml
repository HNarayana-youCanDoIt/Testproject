import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.setupenums 1.0
import com.harman.qml.parkassistenum 1.0
import "../Common/"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.powerenums 1.0

BaseUI {
    id: idParkAssist

    /*Property to hold the park assist list */
    property alias idParkAssistList: idParkAssistList

    /* Function used to find out the list item type */
    function getDelegate(itemType) {
        switch(itemType) {
        case SetupEnums.SETUP_LIST_ITEM_CHECK_BOX:
            return "SetupDelegates/SetupLabelWithCheckBoxDelegate.qml"
        case SetupEnums.SETUP_LIST_ITEM_DROP_DOWN:
            return "SetupDelegates/SetupLabelWithDropDownDelegate.qml"
        case SetupEnums.SETUP_LIST_ITEM_ICON_SLIDER:
            return "SetupDelegates/SetupLabelWithSliderDelegate.qml"
        case SetupEnums.SETUP_LIST_ITEM_RADIO_BUTTON:
            return "SetupDelegates/SetupParkAssistToneDelegate.qml"
        default:
            cppUIBase.qmlLog("ParkAssistScreen.qml - getDelegate default case, SETUP_LIST_ITEM_LABEL is returned:")
            return undefined
        }
    }

    /* Here this connections made to check the current power mode status and on one hour mode
        if user is inside the vehicle setup switch screen to main setup */
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

    /* If user is inside the Park assist setup and the BCM presence is changed to false, PDC presence is also false, then switch screen to main setup */
    Connections {
        target: cppVehicleAdaptor
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
    }

    /* If user is inside the vehicle setup and the PDC presence is changed to false, BCM presence is also false, then switch screen to main setup */
    Connections {
        target: cppParkAssistAdaptor
        onSigPdcPresenceChanged: {
            if( (false === cppVehicleAdaptor.bCmPresence) && (false === cppParkAssistAdaptor.pdcPresence) )
            {
                cppSetupApp.switchScreenToMainSetup()
            }
            else if( (true === cppVehicleAdaptor.bCmPresence) && (false === cppParkAssistAdaptor.pdcPresence) )
            {
                cppSetupApp.jumpToPreviousScreen()
            }
            else
            {
                //Do nothing
            }
        }
    }

    /* Park assist tone option contains list of radio buttons, to achieve the radio button functionality
        (only one should be checked at a time) ButtonGroup is used */
    ButtonGroup {
        id: idPAToneRadioBtnGroup
    }

    /* Park assist tone option contains list of radio buttons, to achieve the radio button functionality
        (only one should be checked at a time) ButtonGroup is used */
    ButtonGroup {
        id: idPADelayTimerRadioBtnGroup
    }

    /* TitleLabel of Setup screen */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_VEHICLE_SETTINGS_PARK_ASSIST") + cppThemeMgr.languageChanged
    }

    /* Park Assist list is populated using GenericList and Park Assist Model */
    GenericList {
        id: idParkAssistList
        idList.model: cppSetupAdaptor.currentModel
        idList.delegate:
            Loader {
            id: idLoader
            property var parkAssistModel: model
            source: getDelegate(model.listItemTypeRole)
            enabled: model.isListItemEnabledRole
        }
    }

    /**
      * While closing the Park Assist setup screen, all the dropdowns should collapsed and get reset to their closed
      * state
      */
    Component.onDestruction : {
        cppSetupAdaptor.toggleExpandState(cppSetupAdaptor.expandedParkAssistItemIndex, cppSetupAdaptor.expandedParkAssistItemIndex)
    }
}

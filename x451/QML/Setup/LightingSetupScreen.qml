import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.setupenums 1.0
import com.harman.qml.powerenums 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common/"

BaseUI {
    id: idLightingSetup

    //To find out which dropdown is expanded
    property int prCurrentExpandedIndex: -1

    /* TitleLabel of Lighting Setup screen */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_VEHICLE_SETTINGS_LIGHTING") + cppThemeMgr.languageChanged
    }

    /* Here this connections made to check the current power mode status and on one hour mode
        if user is inside the lighting setup switch screen to main setup */
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

    /* Approach lamps option contains list of radio buttons, to achieve the radio button functionality(only one should be checked at a time) ButtonGroup is used */
    ButtonGroup {
        id: idApproachLampsRadioButtonGroup
    }

    /* Function used to find out the list item type */
    function getDelegate(itemType) {
        switch(itemType) {
        case SetupEnums.SETUP_LIST_ITEM_LABEL:
            return "qrc:/QML/Setup/Lighting/AmbientLightDelegate.qml"
        case SetupEnums.SETUP_LIST_ITEM_DROP_DOWN :
            return "qrc:/QML/Setup/Lighting/ApproachLampsDropDownDelegate.qml"
        case SetupEnums.SETUP_LIST_ITEM_RADIO_BUTTON:
            return "qrc:/QML/Setup/Lighting/ApproachLampRadioBtnDelegate.qml"
        case SetupEnums.SETUP_LIST_ITEM_CHECK_BOX:
            return "qrc:/QML/Setup/Lighting/DrlSetup.qml"
        default :
            cppSetupApp.qmlLog(" Invalid list item type, itemType: " + itemType)
            return undefined
        }
    }

    /* Lighting list is populated using GenericList and Lighting list Model */
    GenericList {
        id: idLightingSetupList
        idList.model: cppSetupAdaptor.currentModel
        idList.delegate:
            Loader {
            id: idLoader
            property var lightingSetupModel: model
            source: getDelegate(model.listItemTypeRole)
            enabled: model.isListItemEnabledRole
        }
    }

    /**
      * While closing the Lighting setup screen, all the dropdowns should collapsed and get reset to their closed
      * state
      */
    Component.onDestruction : {
        cppSetupAdaptor.toggleLightingSetupExpandState(cppSetupAdaptor.expandedApproachLampsItemIndex, SetupEnums.SETUP_OPTION_APPROACH_LAMPS)
    }

}

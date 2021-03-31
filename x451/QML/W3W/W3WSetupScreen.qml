import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.w3wenum 1.0
import "../Common"


BaseUI
{
    id: idW3WSetup

    /**
     * This property finds out which dropdown is expanded and closed in W3W Setup screen.
     * So as to change the image icon and its functionality
     */
    property int prCurrentExpandedIndex: -1

    HBTitleWithBackButton
    {
        prTitle: qsTr("TEXT_HOME_SHORTCUT_TITLE_W3W") + cppThemeMgr.languageChanged
    }

    // Generic list object to create W3W setup list
    GenericList
    {
        id: idGenericList
        idList.model: cppW3WAdaptor.w3wSetupListModel
        idList.cacheBuffer: 1000
        idList.delegate:
            Loader{
            id:idLoader
            enabled: model.itemEnabledRole
            source : getDelegate(model.itemTypeRole)
        }
    }

    // Method to get the individual delegate to create the list from the item type passed
    function getDelegate(eItemType)
    {
        cppW3WApplication.qmlLog("getDelegate: " + eItemType)
        switch (eItemType)
        {
        case W3WEnum.ITEM_TYPE_LABEL:
            return "W3WDelegates/W3WSetupLabelDelegate.qml"
        case W3WEnum.ITEM_TYPE_LABEL_WITH_DROPDOWN:
            return "W3WDelegates/W3WSetupLabelWithDropDownDelegate.qml"
        case W3WEnum.ITEM_TYPE_LABEL_WITH_RADIO_BUTTON:
            return "W3WDelegates/W3WSetupLabelWithRadioButtonDelegate.qml"
        case W3WEnum.ITEM_TYPE_LABEL_WITH_CHECKBOX:
            return "W3WDelegates/W3WSetupLabelWithCheckboxDelegate.qml"
        default:
            return undefined
        }
    }

    /* Country Preference option contains list of radio buttons, to achieve the radio button functionality
     * (only one should be checked at a time) ButtonGroup is used
    */
    ButtonGroup {
        id: idW3WCountryPreferenceRadioButtonGroup
    }

    /**
      * While closing the W3W setup screen, all the dropdowns should collapsed and get reset to their closed
      * state
      */
    Component.onDestruction : {
        cppW3WAdaptor.w3wSetupListModel.collapseAutoLaunchPermission()
        cppW3WAdaptor.w3wSetupListModel.collapseCountryPreference()
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.phoneenum 1.0
import "../Common"


/*
 * Points to be captured for Phone Setup flow:
 * 1. Disable all the phone setup items till bluetooth status is not received as TRUE.
 * 2. Disable/Enable all the phone setup items when projection phone is connected/disconnected.
 * 3. On pair new device item selection - If maximum paired device count is reached then show popup.
 * "device limit reached". On timeout of the popup, screen should be switched to paired device screen.
 * 4. On pair new device item selection - If maximum paired device count is not reached then show popup
 * "turn on bluetooth". On timeout of the popup, screen should switch to pair new device screen and start
 * device search.
 * 5. On paired device item selection - screen should switch to paired devices screen.
 * 6. On bluetooth visibility checkbox item selection - set HU discoverable status as true/false based upon current
 * HU discoverable status. The item shall be disabled till the new HU discoverable status is not received from service.
 * Based upon the received HU discoverable status, set the checkbox image.
 */
BaseUI
{
    id: idPhoneSetupMain

    /*
     * This property holds the connection status of andorid auto and carplay. This shall be used to enable or
     * disable the items in the screen. If the projection status property is false then the items in the screen
     * shall be in enable state and if the projection status property is true then the items in the screen shall
     * be in disable state.
     */
    property bool prProjectionStatus: ((cppAndroidAutoAdaptor.androidAutoConnectionStatus) ||
                                       (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus))

    /**
     * This property finds out which dropdown is expanded and closed in Phone Setup Main screen.
     * So as to change the image icon and its functionality
     */
    property int prCurrentExpandedIndex: -1

    /**
     * This property finds out which dropdown is expanded and closed in Configure Auto SMS screen.
     * So as to change the image icon and its functionality
     */
    property int prConfigureSMSExpandedIndex: -1

    // TODO: Language string id should be added instead of static text.
    // Title of phone setup screen.
    HBTitleWithBackButton
    {
        prTitle: qsTr("TEXT_SETTINGS_PHONE_SETUP") + cppThemeMgr.languageChanged
    }

    // Generic list object to create bt setup list
    GenericList
    {
        id: idGenericList
        idList.model: cppPhoneAdaptor.phoneSetupListModel
        idList.cacheBuffer: 1000
        idList.delegate:
            Loader{
            id:idLoader
            enabled: model.itemEnabledRole
            source : getDelegate(model.itemTypeRole)
        }
    }

    // method to get the individual delegate to create the list from the item type passed
    function getDelegate(eItemType)
    {
        cppPhoneApp.qmlLog("getDelegate: " + eItemType)
        switch (eItemType)
        {
        case PhoneEnum.ITEM_TYPE_LABEL:
            return "PhoneSetupDelegates/PhoneSetupLabelDelegate.qml"
        case PhoneEnum.ITEM_TYPE_LABEL_WITH_CHECKBOX:
            return "PhoneSetupDelegates/PhoneSetupBtVisibilityDelegate.qml"
        case PhoneEnum.ITEM_TYPE_LABEL_WITH_DROPDOWN:
            return "PhoneSetupDelegates/PhoneSetupLabelWithDropDownDelegate.qml"
        case PhoneEnum.ITEM_TYPE_LABEL_WITH_RADIO_BUTTON:
            return "PhoneSetupDelegates/PhoneSetupSmsAlertNotificationDelegate.qml"
        case PhoneEnum.ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN:
            return "PhoneSetupDelegates/PhoneSetupConfigureAutoSmsDelegate.qml"
        case PhoneEnum.ITEM_TYPE_LABEL_WITH_EDIT_BUTTON:
            return "PhoneSetupDelegates/PhoneSetupEditSmsDelegate.qml"
        default:
            return undefined
        }
    }

    /* SMS Alert  option contains list of radio buttons, to achieve the radio button functionality
     * (only one should be checked at a time) ButtonGroup is used
    */
    ButtonGroup {
        id: idSMSAlertRadioButtonGroup
    }
    /* Configure Auto SMS option contains list of radio buttons, to achieve the radio button functionality
     * (only one should be checked at a time) ButtonGroup is used
    */
    ButtonGroup {
        id: idSMSConfigureAutoRadioButtonGroup
    }

    /**
      * While closing the BT setup screen, all the dropdowns should collapsed and get reset to their closed
      * state
      */
    Component.onDestruction : {
        cppPhoneAdaptor.phoneSetupListModel.collapseConfigAutoSms()
        cppPhoneAdaptor.phoneSetupListModel.collapseSmsAlertNotification()
    }


}


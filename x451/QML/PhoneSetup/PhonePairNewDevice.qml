import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0
import "../Common"

//TDOD: Update the points to be captured for pairing and connection flow

/*
 * Points to be captured for Pair New Device flow:
 * a. SEARCHING FLOW ------------------
 * 1. Switch back to phone setup screen and stop device search if device search is ongoing when
 * projection phone is connected.
 * 2. Show/Hide "searching" text when device search is started/completed.
 * 3. While device search is ongoing list of devices to seen on the visible view should be 3.
 * 4. When device search completes then the list of devices to be shown on the visible view should be 4.
 * 5. Show popup "Bt devices not found" if no devices are available after searching completes. On timeout
 * of the popup switch to phone setup screen.
 * Append all the searched devices one after another.
 * Stop device search if device search is ongoing and user selects back button.
 * b. PAIRING FLOW ------------------
 * 1. Device selected for pairing and already a device is connected. Show popup "device will be disconnected".
 * User selects "Proceed" option then disable the list and call "startAllServiceConnection" API and close the
 * popup. If user selects "cancel" option then close the popup.
 * 2. "startAllServiceConnection" method call fails then enable the list.
 * 3. Bonding request received from service -
 * (i). Pairing initated from remote phone then show "incoming request" popup. if user selects "Accept" option then
 * show "passkey" popup. If user selects "Reject" option then close the popup and enable the list.
 * (ii). Pairing initiated from HU then show "passkey" popup.
 * 4. Passkey popup - If user selects "Yes" option then close the popup and call API "bondingReply" with "true" param.
 * If user selects "No" option then close the popup and call API "bondingReply" with "false" param.
 * Bonding Status received - If bonding status is received as success then show "Determining bluetooth services" popup,
 * enable the list and continue with connection flow, and if bonding status is received as "faliure" then show
 * "pairing failed" popup and enable the list.
 * c. CONNECTION FLOW - NOT YET STARTED
 */

/*
 * TODO: Flicker(searching text becomes invisible and then screen switching happens) seen sometimes when comming back
 * from pair new device screen to phone setup screen. Need to check.
 */
BaseUI
{
    id: idPhonePairNewDeviceMain

    /*
     * This property holds the connection status of andorid auto and carplay. This shall be used to enable or
     * disable the items in the screen. If the projection status property is false then the items in the screen
     * shall be in enable state and if the projection status property is true then the items in the screen shall
     * be in disable state.
     */
    property bool prProjectionStatus: ((cppAndroidAutoAdaptor.androidAutoConnectionStatus) ||
                                       (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus))
    property bool prDeviceSearchStatus: cppPhoneAdaptor.deviceSearchStatus

    //property to hold bluetooth status oh HU
    property bool prBluetoothStatus: cppPhoneAdaptor.bluetoothStatus

    /**
     * Method to check projection status once component is completed or projection status is changed.
     */
    function checkProjectionStatus()
    {
        /**
         * If projection status is true then switch back to phone setup screen
         * otherwise do not do anything
         */
        if(prProjectionStatus)
        {
            // Switch to phone setup screen if projection phone is connected
            cppPhoneApp.qmlLog("PhonePairNewDevice.qml: projection status is true")
            cppUIBase.raiseSMEvent("back", "")
        }
        else
        {
            cppPhoneApp.qmlLog("PhonePairNewDevice.qml: projection status is false")
        }
    }

    /**
     * Method to check for device search status once component is completed or device search status
     * is changed.
     */
    function checkDeviceSearchStatus()
    {
        /**
         * If device search status is false then set idSelectDeviceToConnect visibility as true and
         * idSearchingItemComponent visibility as false. If the device search status is true the set
         * idSearchingItemComponent visibility as true and idSelectDeviceToConnect visibility as false.
         * Also check if the list is empty then show popup bt devices not found.
         */
        if (prDeviceSearchStatus)
        {
            cppPhoneApp.qmlLog("PhonePairNewDevice.qml: device search status is true")
//            idSearchingItemComponent.visible = true
//            idSelectDeviceToConnect.visible = false
        }
        else
        {
            cppPhoneApp.qmlLog("PhonePairNewDevice.qml: device search status is false")
//            idSelectDeviceToConnect.visible = true
//            idSearchingItemComponent.visible = false
            if (cppPhoneAdaptor.deviceSearchListModel.rowCount() === 0)
            {
                cppPhoneApp.qmlLog("PhonePairNewDevice.qml: device count is 0")
                cppPhoneAdaptor.invShowPopupNoDeviceFound()
            }
            else
            {
                cppPhoneApp.qmlLog("PhonePairNewDevice.qml: device count is not 0")
                idScreenTitle.prTitle = qsTr("TEXT_PHONE_SETUP_SELECT_DEVICE") + cppThemeMgr.languageChanged
            }
        }
    }

    onPrProjectionStatusChanged:
    {
        cppUIBase.qmlLog("PhonePairNewDevice.qml: onPrProjectionStatusChanged")
        // Check for projection status
        checkProjectionStatus();
    }

    onPrDeviceSearchStatusChanged:
    {
        cppUIBase.qmlLog("PhonePairNewDevice.qml: onPrDeviceSearchStatusChanged")
        // Check for device search status
        checkDeviceSearchStatus();
    }

    onPrBluetoothStatusChanged:
    {
        /**
         * If bluetooth status is false then switch back to phone setup screen
         * otherwise do not do anything
         */
        if(!prBluetoothStatus)
        {
            cppPhoneApp.qmlLog("PhonePairNewDevice.qml: bluetooth status is false")
            cppUIBase.raiseSMEvent("back", "")
        }
        else
        {
            cppPhoneApp.qmlLog("PhonePairNewDevice.qml: bluetooth status is true")
        }
    }

    // TODO: Language string id should be added instead of static text.
    // Title of pair new device screen.
    HBTitleWithBackButton
    {
        id: idScreenTitle
        prTitle: qsTr("TEXT_PHONE_SETUP_SEARCHING_DEVICE") + cppThemeMgr.languageChanged
    }

    /** HB text to show "Select device to connect" text **/
//    HBText {
//        id: idSelectDeviceToConnect
//        width: idPairNewDeviceList.idList.width
//        height: (idPairNewDeviceList.prItemHeight - idSearchingItemSeparator.height)
//        anchors
//        {
//            // idSelectDeviceToConnect.X start should be same as idPairNewDeviceList.X start
//            left: idPairNewDeviceList.left
//            leftMargin: 10
//            top: parent.top
//            topMargin: 161
//        }

//        visible: false
//        text: qsTr("TEXT_PHONE_SETUP_SELECT_DEVICE_TO_CONNECT") + cppThemeMgr.languageChanged
//        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
//        verticalAlignment: Text.AlignVCenter
//    }

    HBText
    {
        id: idSearchingItemComponent
        width: idPairNewDeviceList.idList.width
        height: (idPairNewDeviceList.prItemHeight - idSearchingItemSeparator.height)
        anchors
        {
            // idSearchingItemComponent.X start should be same as idPairNewDeviceList.X start
            left: idPairNewDeviceList.left
            leftMargin: 10
            top: parent.top
            topMargin: 161
        }

        //TODO: To be added in language file
        text: qsTr("Connect to \"ConnectNext\" from your Device.") + cppThemeMgr.languageChanged
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        verticalAlignment: Text.AlignVCenter
    }

    ListItemSeparator
    {
        id: idSearchingItemSeparator
        anchors
        {
            left: idPairNewDeviceList.left
            leftMargin: 0
            top: idSearchingItemComponent.bottom
        }
        visible: true
    }

    // Delegate of button list item component
    Component
    {
        id: idPairNewDeviceListItemDelegate
        Column
        {
            HBButtonListItem
            {
                id: idPairNewDeviceListItem
                width: idPairNewDeviceList.idList.width
                height: (idPairNewDeviceList.prItemHeight - idPairNewDeviceListItemSeparator.height)
                text: deviceNameRole
                // Initiate pairing
                onReleased:
                {
                    cppPhoneApp.qmlLog("PhonePairNewDevice.qml: OnReleased for device " + deviceNameRole)
                    cppPhoneAdaptor.invSetSelectedItemInfo(deviceNameRole, deviceAddressRole)
                    /*
                     * If any device is connected then show popup "previous device will be disconnected"
                     * else invoke API startAllServiceConnection
                     */
                    if (cppPhoneAdaptor.deviceConnected)
                    {
                        PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION)
                    }
                    else
                    {
                        PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_CONNECTING)
                        cppPhoneAdaptor.invStartAllServiceConnection(deviceAddressRole)
                    }
                }
            }

            //Handling RRE HK for searched device items in the list
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("PairNewDeviceList: onRotaryUpdate: key state is: " + iKeyState)
                    if((iKeyState === HardkeyEnum.HKEY_STATE_RELEASED) || (iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED))
                    {
                        if(idPairNewDeviceList.idList.currentIndex === index)
                        {
                            cppPhoneApp.qmlLog("PairNewDevice.qml - HBButtonListItem RRE release/longReleae event, itemIndex is: " + index)
                            cppPhoneAdaptor.invSetSelectedItemInfo(deviceNameRole, deviceAddressRole)
                            /*
                             * If any device is connected then show popup "previous device will be disconnected"
                             * else invoke API startAllServiceConnection
                             */
                            if (cppPhoneAdaptor.deviceConnected)
                            {
                                PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION)
                            }
                            else
                            {
                                PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_CONNECTING)
                                cppPhoneAdaptor.invStartAllServiceConnection(deviceAddressRole)
                            }
                        }
                    }
                }
            }

            ListItemSeparator
            {
                id: idPairNewDeviceListItemSeparator
            }
        }
    }

    // Pair new device main list.
    GenericList
    {
        id: idPairNewDeviceList
        rowShownPerPage: 3
        height: (idPairNewDeviceList.prItemHeight * rowShownPerPage)
        anchors
        {
            top: idSearchingItemSeparator.bottom
            topMargin: 0
        }
        prScrollBarTopMargin: -prItemHeight
        idList.model: cppPhoneAdaptor.deviceSearchListModel
        idList.delegate: idPairNewDeviceListItemDelegate
    }

    Connections
    {
        target: cppPhoneAdaptor
        onSigExitPairNewDeviceScreen:
        {
            // If pairing successfull then switch to phone setup screen
            cppUIBase.raiseSMEvent("back", "")
        }
    }

    /*
     * This shall be executed when screen's destrcution begins. At this point we will clear
     * the device search list and shall stop the device search.
     */
    Component.onDestruction:
    {
        cppPhoneApp.qmlLog("PairNewDevice.qml - onDestruction: ")
        cppPhoneAdaptor.invClearDeviceSearchList()
        cppPhoneAdaptor.invStopDeviceSearch()
    }
}

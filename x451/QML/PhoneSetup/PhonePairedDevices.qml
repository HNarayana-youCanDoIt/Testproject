import QtQuick 2.7
import com.harman.qml.popupenums 1.0
import com.harman.qml.phoneenum 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common"

BaseUI
{
    id: idPhonePairedDevicesMain

    /*
     * This property holds the connection status of andorid auto and carplay. This shall be used to enable or
     * disable the items in the screen. If the projection status property is false then the items in the screen
     * shall be in enable state and if the projection status property is true then the items in the screen shall
     * be in disable state.
     */
    property bool prProjectionStatus: ((cppAndroidAutoAdaptor.androidAutoConnectionStatus) ||
                                       (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus))

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
            cppPhoneApp.qmlLog("PhonePairedDevices.qml: projection status is true")
            cppUIBase.raiseSMEvent("back", "")
        }
        else
        {
            cppPhoneApp.qmlLog("PhonePairedDevices.qml: projection status is false")
        }
    }

    // method to get the individual delegate to create the list from the item type passed
    function getDelegate(eItemType)
    {
        switch (eItemType)
        {
        case PhoneEnum.ITEM_TYPE_ICON_WITH_BUTTON:
            return idPairedDevicesListItemDelegate
        case PhoneEnum.ITEM_TYPE_LABEL:
            return idDeleteAllListItemDelegate
        case PhoneEnum.ITEM_TYPE_LABEL_WITH_BUTTON:
            return idPairNewDeviceDelegate
        default:
            return undefined
        }
    }

    onPrProjectionStatusChanged:
    {
        // Check for projection status
        checkProjectionStatus();
    }

    onPrBluetoothStatusChanged:
    {
        /**
         * If bluetooth status is false then switch back to phone setup screen
         * otherwise do not do anything
         */
        if(!prBluetoothStatus)
        {
            cppPhoneApp.qmlLog("PhonePairedDevices.qml: bluetooth status is false")
            cppUIBase.raiseSMEvent("back", "")
        }
        else
        {
            cppPhoneApp.qmlLog("PhonePairedDevices.qml: bluetooth status is true")
        }
    }

    // TODO: Language string id should be added instead of static text.
    // Title of paired devices screen.
    HBTitleWithBackButton
    {
        prTitle: qsTr("TEXT_SETTING_PAIRED_DEVICE_LIST") + cppThemeMgr.languageChanged
    }

    //Delegate for pair new device item
    Component
    {
        id: idPairNewDeviceDelegate
        Column
        {
            ListItemWithIconComp
            {
                id: idPairNewDeviceItem
                width: idPairedDevicesList.idList.width
                height: idPairedDevicesList.prItemHeight - idPairNewDeviceItemSeparator.height
                prIconLeftMargin: -9 //(icon.X - idPairedDevicesList.X)
                prTextWidth: 300
                prTextLeftMargin: 1 //(text.X - (icon.X + icon.width))
                // TODO: Language string id should be added instead of static text.
                prText: qsTr("TEXT_SETTING_PAIR_NEW_DEVICE") + cppThemeMgr.languageChanged
                prDefaultIconImage: "qrc:/image/Gen_Ico_Search_BTAudio_7in_n-assets/Gen_Ico_Search_BTAudio_n.png"
                prPressedIconImage: "qrc:/image/Gen_Ico_Search_BTAudio_7in_n-assets/Gen_Ico_Search_BTAudio_n.png"
                prDisabledIconImage: "qrc:/image/Gen_Ico_Search_BTAudio_7in_n-assets/Gen_Ico_Search_BTAudio_nd.png"

                button.onReleased:
                {
                    cppPhoneApp.qmlLog("PhonePairedDevices.qml: idPairNewDeviceDelegate: OnReleased for pair new device ")
                    cppPhoneAdaptor.invSwitchToPairNewDevice()
                }
            }

            //Handling RRE HK for Pair New Device
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("PairedDeviceList: idPairNewDeviceDelegate: onRotaryUpdate: key state is: " + iKeyState)
                    if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED)
                    {
                        if(idPairedDevicesList.idList.currentIndex === pairedDeviceListModel.index)
                        {
                            cppPhoneApp.qmlLog("PhonePairedDevices.qml - idPairNewDeviceDelegate: HBButtonListItem RRE release/longReleae event, itemIndex is: " + pairedDeviceListModel.index)
                            cppPhoneAdaptor.invSwitchToPairNewDevice()
                        }
                    }
                }
            }

            ListItemSeparator
            {
                id: idPairNewDeviceItemSeparator
            }
        }
    }

    // Delegate of paired devices item component
    Component
    {
        id: idPairedDevicesListItemDelegate
        Column
        {
            ListItemWithIconAndButton
            {
                id: idPairedDevicesListItem
                width: idPairedDevicesList.idList.width
                height: idPairedDevicesList.prItemHeight - idPairedDevicesListItemSeparator.height
                prItemText: pairedDeviceListModel.pairDeviceNameRole
                prIconImage: (pairedDeviceListModel.connectionStatusRole) ? "qrc:/image/Set_Ico_Status/Set_Ico_Connected_n.png" : "qrc:/image/Set_Ico_Status/Set_Ico_Disconnected_nd.png"
                // Initiate connection/disconnection flow
                onReleased:
                {
                    cppPhoneApp.qmlLog("PhonePairedDevices.qml: idPairedDevicesListItemDelegate: OnReleased for device " + pairedDeviceListModel.pairDeviceNameRole)
                    cppPhoneAdaptor.invSetSelectedItemInfo(pairedDeviceListModel.pairDeviceNameRole, pairedDeviceListModel.pairDeviceAddressRole)
                    if(pairedDeviceListModel.connectionStatusRole)
                    {
                        //Initiate device disconnection
                        cppPhoneApp.qmlLog("PhonePairedDevices.qml: Initiating device disconnection")
                        PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_DISCONNECTING)
                        cppPhoneAdaptor.invStartAllServiceDisconnection(pairedDeviceListModel.pairDeviceAddressRole)
                    }
                    else
                    {
                        /* Initiate device connection
                         * If any device is connected then show popup "previous device will be disconnected"
                         * else invoke API startAllServiceConnection
                         */
                        cppPhoneApp.qmlLog("PhonePairedDevices.qml: idPairedDevicesListItemDelegate: Initiating device connection")
                        if (cppPhoneAdaptor.deviceConnected)
                        {
                            PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION)
                        }
                        else
                        {
                            PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_CONNECTING)
                            cppPhoneAdaptor.invStartAllServiceConnection(pairedDeviceListModel.pairDeviceAddressRole)
                        }
                    }
                }

                prButtonItem.onReleased:
                {
                    //Initiate delete flow
                    cppPhoneApp.qmlLog("PhonePairedDevices.qml: idPairedDevicesListItemDelegate: OnReleased for device delete " + pairedDeviceListModel.pairDeviceNameRole)
                    cppPhoneAdaptor.invSetSelectedItemInfo(pairedDeviceListModel.pairDeviceNameRole, pairedDeviceListModel.pairDeviceAddressRole)
                    PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_CONFIRMATION)
                }
            }

            //Handling RRE HK for Paired devices item in the list
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("PhonePairedDevices.qml: idPairedDevicesListItemDelegate: onRotaryUpdate: key state is: " + iKeyState)
                    if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED)
                    {
                        if(idPairedDevicesList.idList.currentIndex === pairedDeviceListModel.index)
                        {
                            cppPhoneApp.qmlLog("PhonePairedDevices.qml - idPairedDevicesListItemDelegate: ListItemWithIconAndButton RRE release/longReleae event, itemIndex is: " + pairedDeviceListModel.index)
                            cppPhoneAdaptor.invSetSelectedItemInfo(pairedDeviceListModel.pairDeviceNameRole, pairedDeviceListModel.pairDeviceAddressRole)
                            if(pairedDeviceListModel.connectionStatusRole)
                            {
                                //Initiate device disconnection
                                cppPhoneApp.qmlLog("PhonePairedDevices.qml: idPairedDevicesListItemDelegate: Initiating device disconnection")
                                PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_DISCONNECTING)
                                cppPhoneAdaptor.invStartAllServiceDisconnection(pairedDeviceListModel.pairDeviceAddressRole)
                            }
                            else
                            {
                                /* Initiate device connection
                                 * If any device is connected then show popup "previous device will be disconnected"
                                 * else invoke API startAllServiceConnection
                                 */
                                cppPhoneApp.qmlLog("PhonePairedDevices.qml: Initiating device connection")
                                if (cppPhoneAdaptor.deviceConnected)
                                {
                                    PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION)
                                }
                                else
                                {
                                    PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_CONNECTING)
                                    cppPhoneAdaptor.invStartAllServiceConnection(pairedDeviceListModel.pairDeviceAddressRole)
                                }
                            }
                        }
                    }
                }
            }

            ListItemSeparator
            {
                id: idPairedDevicesListItemSeparator
            }
        }
    }

    //Delegate for delete all item component
    Component
    {
        id: idDeleteAllListItemDelegate
        Column
        {
            ListItemWithIconAndButton
            {
                id: idDeleteAllItem
                width: idPairedDevicesList.idList.width
                height: idPairedDevicesList.prItemHeight - idDeleteAllItemSeparator.height
                prItemText: qsTr("TEXT_SETTING_DELETE_DEVICES") + cppThemeMgr.languageChanged
                // Initiate delete all
                prButtonItem.defaultImageURL: "qrc:/image/Set_Ico_Delete/Set_Ico_Delete_n.png"
                prButtonItem.pressedImageURL: "qrc:/image/Set_Ico_Delete/Set_Ico_Delete_nf.png"
                prButtonItem.disabledImageURL: "qrc:/image/Set_Ico_Delete/Set_Ico_Delete_nd.png"

                onReleased:
                {
                    cppPhoneApp.qmlLog("PhonePairedDevices.qml: idDeleteAllListItemDelegate: OnReleased for delete all ")
                    PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_CONFIRMATION)
                }

                prButtonItem.onReleased:
                {
                    cppPhoneApp.qmlLog("PhonePairedDevices.qml: idDeleteAllListItemDelegate: OnReleased for delete button ")
                    PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_CONFIRMATION)
                }
            }

            //Handling RRE HK for Delete All
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("PhonePairedDevices.qml: idDeleteAllListItemDelegate: onRotaryUpdate: key state is: " + iKeyState)
                    if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED)
                    {
                        if(idPairedDevicesList.idList.currentIndex === pairedDeviceListModel.index)
                        {
                            cppPhoneApp.qmlLog("PhonePairedDevices.qml - idDeleteAllListItemDelegate: HBButtonListItem RRE release/longReleae event, itemIndex is: " + pairedDeviceListModel.index)
                            PopupManager.showPopup(PopupEnum.EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_CONFIRMATION)
                        }
                    }
                }
            }

            ListItemSeparator
            {
                id: idDeleteAllItemSeparator
            }
        }
    }

    // Paired devices main list
    GenericList
    {
        id: idPairedDevicesList
        idList.model: cppPhoneAdaptor.pairedDeviceListModel
        idList.delegate: Loader
        {
            id:idLoader
            property var pairedDeviceListModel: model
            sourceComponent: getDelegate(pairedDeviceListModel.pairedDeviceItemTypeRole)
        }
        idList.onCountChanged:
        {
            cppPhoneApp.qmlLog("PhonePairedDevices.qml: onCountChanged: rreIndex: " + idPairedDevicesList.prRREIndex + " current list count: " + cppPhoneAdaptor.invGetCurrentListCount() + " previous list count: " + cppPhoneAdaptor.invGetPreviousListCount())
            if(cppPhoneAdaptor.invGetCurrentListCount() !== cppPhoneAdaptor.invGetPreviousListCount())
            {
                //Reset the currentIndex and RREIndex when paired list changes.
                idPairedDevicesList.idList.currentIndex = -1
                idPairedDevicesList.prRREIndex = -1
                cppPhoneApp.qmlLog("onCountChanged: current list count and previous list count not equal")
            }
            else
            {
                //Assign the last saved RREIndex to the currentIndex to highlight the selected index.
                idPairedDevicesList.idList.currentIndex = idPairedDevicesList.prRREIndex
                cppPhoneApp.qmlLog("onCountChanged: current list count and previous list count equal")
            }
        }
    }

    /*
     * This shall be executed when screen's components gets loaded begins. At this point we will check
     * for projection status.
     */
    Component.onCompleted:
    {
        checkProjectionStatus()
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.setupenums 1.0
import com.harman.qml.powerenums 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.hvacenums 1.0
import "../Common/"

BaseUI {
    id:idVehicleSettings

    //To find out which dropdown is expanded
    property int prCurrentExpandedIndex: -1

    /* TitleLabel of Setup screen */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_SETTINGS_VEHICLE_SETUP") + cppThemeMgr.languageChanged
    }

    /** Delegate of Button List Item with Label and CheckBox  **/
    Component {
        id: idBtnListLabelWithCheckBoxDelegate
        Column {
            LabelWithCheckBoxComp {
                id: idLabelWithCheckboxComp
                prCheckBoxRightMargin: 10
                width: idVehicleSetupList.idList.width
                height: idVehicleSetupList.prItemHeight - idSeparator.height
                text: vehicleSettingsModel.listItemNameRole
                prCheckBoxChecked: vehicleSettingsModel.listItemCheckedRole

                onReleased:
                {
                    cppSetupApp.qmlLog("VehicleSettings.qml - Index: onRelesed : "+ vehicleSettingsModel.listItemIndexRole)
                    if(vehicleSettingsModel.listItemIndexRole === SetupEnums.SETUP_SCREEN_SMART_FAN)
                    {
                        cppUIBase.qmlLog("VehicleSetupScreen.qml - Smart Fan:")
                        cppAppleCarPlayAdaptor.setSmartFanState()
                    }
                    else if(vehicleSettingsModel.listItemIndexRole === SetupEnums.SETUP_OPTION_VOICE_ALERT)
                    {
                        cppSetupApp.qmlLog("Set Voice alert : "+ vehicleSettingsModel.listItemIndexRole)
                        cppVoiceAlertsAdaptor.setVoiceAlertSelectionAttribute(!prCheckBoxChecked)
                    }
                    else
                    {
                        cppSetupApp.qmlLog(" idLabelWithCheckboxComp - Index : "+ vehicleSettingsModel.listItemIndexRole)
                    }
                }
            }

            //Handling RRE HK for selecting or deselecting vehicle auto relock
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("VehicleSettingsScreen.qml: onRotaryUpdate: key state is: " + iKeyState +
                                       " idVehicleSetupList.idList.currentIndex "+ idVehicleSetupList.idList.currentIndex +
                                       " vehicleSettingsModel.index " + vehicleSettingsModel.index)
                    cppSetupApp.qmlLog("VehicleSettings.qml - Index: "+ vehicleSettingsModel.listItemIndexRole)
                    if((HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode) &&
                            (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                    {
                        if((idVehicleSetupList.idList.currentIndex === vehicleSettingsModel.index) &&
                                (vehicleSettingsModel.listItemIndexRole === SetupEnums.SETUP_SCREEN_SMART_FAN))
                        {
                            cppUIBase.qmlLog("VehicleSetupScreen.qml - Smart Fan:")
                            cppAppleCarPlayAdaptor.setSmartFanState()
                        }
                        else if((idVehicleSetupList.idList.currentIndex === vehicleSettingsModel.index) &&
                                vehicleSettingsModel.listItemIndexRole === SetupEnums.SETUP_OPTION_VOICE_ALERT)
                        {
                            cppSetupApp.qmlLog("Set Voice alert : "+ vehicleSettingsModel.listItemIndexRole)
                            cppVoiceAlertsAdaptor.setVoiceAlertSelectionAttribute(!idLabelWithCheckboxComp.prCheckBoxChecked)
                        }
                        else
                        {
                            cppSetupApp.qmlLog(" idLabelWithCheckboxComp - Index : "+ vehicleSettingsModel.listItemIndexRole)
                        }
                    }
                    else
                    {
                        cppPhoneApp.qmlLog("VehicleSettingsScreen.qml: onRotaryUpdate: key state is: " + iKeyState)
                    }
                }
            }

            //FixMe: Need to give proper list item separator image as per x451
            ListItemSeparator {
                id:idSeparator
            }
        }
    }

    /** Delegate of Button List Item with Label **/
    Component {
        id: idBtnListWithLabelDelegate
        Column {
            HBButtonListItem {
                id: idLabelComp
                width: idVehicleSetupList.idList.width
                height: idVehicleSetupList.prItemHeight - idSeparator.height
                text: vehicleSettingsModel.listItemNameRole

                onReleased:{
                    //FixME: Call service method to set
                    cppSetupApp.qmlLog("VehicleSetupScreen.qml - index: "+ vehicleSettingsModel.listItemIndexRole)
                    cppSetupApp.raiseSMEvent("VehicleSetup", vehicleSettingsModel.listItemIndexRole)
                }
            }

            Connections {
                target: cppHardkeyAdaptor
                onSigRotaryPressed: {
                    cppSetupApp.qmlLog(
                                "GenericList: onRotaryUpdate: "+iKeyState)
                    if((HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                        HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                    {
                        if(idVehicleSetupList.idList.currentIndex === vehicleSettingsModel.index)
                        {
                            cppSetupApp.qmlLog("VehicleSetupScreen.qml - index: "+ vehicleSettingsModel.listItemIndexRole)
                            cppSetupApp.raiseSMEvent("VehicleSetup", vehicleSettingsModel.listItemIndexRole)
                        }
                    }
                }
            }

            //FixMe: Need to give proper list item separator image as per x451
            ListItemSeparator {
                id:idSeparator
            }
        }
    }

    /* Vehicle settings main list is populated using GenericList and SetupMainModel */
    GenericList {
        id: idVehicleSetupList
        idList.model: cppSetupAdaptor.currentModel
        idList.delegate:Loader {
            id: idLoader
            property var vehicleSettingsModel: model
            sourceComponent: getDelegate(vehicleSettingsModel.listItemTypeRole)
            enabled: vehicleSettingsModel.isListItemEnabledRole
        }
        idList.onModelChanged: {
            idList.currentIndex = -1
        }
    }

    /** getDelegate function will return the type of delegate needed in a list through the
                listItemType Parameter coming from Model  **/
    function getDelegate(ListItemTypeRole) {
        switch (ListItemTypeRole) {
        case SetupEnums.SETUP_LIST_ITEM_CHECK_BOX:
            return idBtnListLabelWithCheckBoxDelegate
        case SetupEnums.SETUP_LIST_ITEM_LABEL:
            return idBtnListWithLabelDelegate
        default:
            return idBtnListWithLabelDelegate
        }
    }
}

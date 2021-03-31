import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.setupenums 1.0
import "../../Common/"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hvacenums 1.0
import com.harman.qml.popupenums 1.0
import "../../Setup/Themes"
import com.harman.qml.hardkeyenum 1.0

Item {
    id: idLabelWithIconsDelegate

    width: idThemeSetupList.width
    height: idThemeSetupList.prItemHeight

    Column {

        LabelWithIcons{
            id: idLabelWithIcons
            height      : idThemeSetupList.prItemHeight - idListItemSeparatorAnim.height
            width       : idThemeSetupList.idList.width
            prIconImage : themeSetupModel.listItemDefaultImageRole
            text        : themeSetupModel.listItemNameRole
            prVisibility: themeSetupModel.listItemClimateIconsVisibilityStatus
            prSelectedThemeColor: colorModeImagesArray[cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].themeColor]
            prRightIconImage: themeSetupModel.listItemSelectedImageRole
            prFanSpeedImage:  themeSetupModel.listItemFanSpeedImageRole
            prFanSpeedImageVisibilty: (cppHVACAdaptor.ccmPresence === HVACEnums.HVAC_CCM_PRESENT) ? ((cppSetupAdaptor.expandThemeItemIndex !== themeSetupModel.index) ? themeSetupModel.listItemFanSpeedImageRole : false) : false
            prFanSpeedValue: cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].fanspeed
            prFanSpeedValueVisibility: (cppHVACAdaptor.ccmPresence === HVACEnums.HVAC_CCM_PRESENT) ? ((cppSetupAdaptor.expandThemeItemIndex !== themeSetupModel.index) ? themeSetupModel.listItemFanSpeedValue : false) : false
            prTemperatureValue: (cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].temperature.toFixed(1) + qsTr("°C") + cppThemeMgr.languageChanged)
            prTemperatureValueVisibility: (cppHVACAdaptor.ccmPresence === HVACEnums.HVAC_CCM_PRESENT) ? ((cppSetupAdaptor.expandThemeItemIndex !== themeSetupModel.index) ? themeSetupModel.listItemTemperatureValue : false) : false
            prSeperatorLine: (cppSetupAdaptor.expandThemeItemIndex !== themeSetupModel.index) ? "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Gfx_ListSeparator_vertical_7in_n-assets/Set_Gfx_ListSeparator_vertical_n.png" : ""
            prThemeColorVisibility: (cppSetupAdaptor.expandThemeItemIndex !== themeSetupModel.index) ? themeSetupModel.listItemThemeColorVisibility : false
            prThemeSoundVisibility: (cppSetupAdaptor.expandThemeItemIndex !== themeSetupModel.index) ? themeSetupModel.listItemThemeSoundVisibility : false

            onReleased  : {
                cppSetupApp.qmlLog("idDelegateDropDown - index: "+ themeSetupModel.index)
                toggleExpandState()
            }

            function toggleExpandState() {
                cppSetupApp.qmlLog("toggleExpandState - index: " + themeSetupModel.index
                                   + " Expand SubItem Index " + cppSetupAdaptor.expandThemeItemIndex)

                if(cppSetupAdaptor.expandThemeItemIndex === themeSetupModel.index)
                {
                    cppSetupAdaptor.collapseThemeItem(themeSetupModel.index)
                }
                else
                {
                    prCurrentExpandedIndex = themeSetupModel.index
                    idThemeSetupList.prSubItemCount = 3
                    cppSetupAdaptor.expandThemeItem(themeSetupModel.index)
                    idThemeSetupList.idList.positionViewAtIndex(themeSetupModel.index, ListView.Beginning)
                }
            }
        }

        ListItemSeparatorAnim{
            id:idListItemSeparatorAnim
            prStartAnim: themeSetupModel.listItemThemeLoadingStatus

            Component.onCompleted: {
                cppSetupApp.qmlLog("Index: "+ themeSetupModel.index + " loading status " + themeSetupModel.listItemThemeLoadingStatus)
            }
        }

    }
    //Handling RRE HK for theme setup items
    Connections
    {
        target: cppHardkeyAdaptor
        onSigRotaryPressed:
        {

            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
            {
                if(idThemeSetupList.idList.currentIndex === index)
                {
                    idLabelWithIcons.toggleExpandState()
                    /**
                      As per the last change we had to use rotary twice to go to the next item . 1st Rotary action will active the
                      RREIndex to the current Top Item and then 2nd rotary to move to the next Item. But now whenever the item will
                      expand, the RREIndex will still be on the currentIndex and in one rotary we will have next Item.
                    **/
                    idThemeSetupList.prRREIndex = idThemeSetupList.idList.currentIndex
                }
                else
                {
                    //Do Nothing
                    cppPhoneApp.qmlLog("Invalid Index Selected")
                }
            }

            else
            {
                //Do Nothing
                cppPhoneApp.qmlLog("Not in Released/LongReleased HardKey State")
            }
        }
    }

    //Connection to handle CCM presence value change
    Connections
    {
        target: cppHVACAdaptor
        onSigCCMPresenceChanged:
        {
            cppPhoneApp.qmlLog("CCM presence value is: " + cppHVACAdaptor.ccmPresence)
            //If CCm is not present then hide fan speed image, fan speed value, temperature value and sperator line image
            if(cppHVACAdaptor.ccmPresence !== HVACEnums.HVAC_CCM_PRESENT)
            {
                idLabelWithIcons.prFanSpeedImageVisibilty = false
                idLabelWithIcons.prFanSpeedValueVisibility = false
                idLabelWithIcons.prTemperatureValueVisibility = false
                idLabelWithIcons.prSeperatorLineVisibility = false
            }
            else
            {
                cppPhoneApp.qmlLog("CCM is present")
            }
        }
    }
}

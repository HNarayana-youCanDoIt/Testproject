import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.setupenums 1.0
import "../Common/"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hvacenums 1.0
import com.harman.qml.popupenums 1.0
import "../Setup/Themes"
import com.harman.qml.powerenums 1.0
import com.harman.qml.hardkeyenum 1.0

BaseUI {
    id: idThemeSetup

    //To find out which dropdown is expanded
    property int prCurrentExpandedIndex: -1

    // This property used to hold the current air flow distribution mode index
    property int prCurrntDistributionModeIndex: cppHVACAdaptor.distributionMode

    //This property used to hold the air flow distribution mode images filled in array
    property var distributionModeImagesArray: [ "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Drw_Ico_Climate2_n.png",
        "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Drw_Ico_Climate1_n.png",
        "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Drw_Ico_Climate3_n.png",
        "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Drw_Ico_Climate4_n.png",
        "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Drw_Ico_Climate5_n.png"
    ]

    property var colorModeImagesArray: ["#2b74c3",
        "#c32b2b",
        //"#2bc393", As per TML, green colour theme should be removed
        "#f7913d",
        "#ac245e"]

    //This property used to hold the fan speed
    property int prFanSpeed: cppHVACAdaptor.fanSpeed

    //This property used to hold the temperature
    property real prTemperature: cppHVACAdaptor.temperature.toFixed(1)

    /*Note:Here we are doing this to show the active theme preset, when user changes theme preset without activating,
           and relaunching the theme settings screen */
    Component.onCompleted: {
        cppSetupAdaptor.initCustomThemeValues()
        idThemePresetsTabView.prCurrIndex = cppSetupAdaptor.curActiveThemePreset
    }

    /* This connections made to when user change any values in climate, color, sound and lighting the theme sholud change to custom mode.
        And accept and reset button visibility handled here*/
    Connections{
        target: cppSetupAdaptor
        onSigPresetSelectionChanged :{
            cppSetupApp.qmlLog(" onSigPresetSelectionChanged -- idThemePresetsTabView.prCurrIndex " + idThemePresetsTabView.prCurrIndex
                               + " cppSetupAdaptor.presetSelection " + cppSetupAdaptor.presetSelection
                               + "Current Active theme preset " + cppSetupAdaptor.curActiveThemePreset)
            idThemePresetsTabView.prCurrIndex =  cppSetupAdaptor.presetSelection
        }
    }

    Connections{
        target: cppHVACAdaptor

        onSigDistributionModeChanged : {
            prCurrntDistributionModeIndex = cppHVACAdaptor.distributionMode
        }
        onSigTemperatureChanged : {
            prTemperature = cppHVACAdaptor.temperature
        }
        onSigFanSpeedChanged : {
            prFanSpeed = cppHVACAdaptor.fanSpeed
        }
    }

    /* Here this connections made to check the current power mode status and on one hour mode
        if user is inside the theme setup switch screen to main setup */
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

    /* Tab view used to show the theme presets where user can change to available theme presets on button press or by scrolling through the presets */
    HBTabBar{
        id:idThemePresetsTabView

        anchors{
            top: parent.top
            topMargin: 50
            left: parent.left
            leftMargin: 166
        }
        prTabViewModel:cppSetupAdaptor.themepresetModel
        prCurrIndex: cppSetupAdaptor.presetSelection

        onSigTabViewCurrentIndexChanged: {
            cppSetupAdaptor.editModeFlag = false

            //Reset the current Index and RREIndex for List
            idThemeSetupList.idList.currentIndex = -1
            idThemeSetupList.prRREIndex = -1

            if(!isMovementByDrag)
            {
                setPositionView();
            }

            if(index != cppSetupAdaptor.presetSelection)
            {
                cppSetupApp.qmlLog(" cppSetupAdaptor.presetSelection " + cppSetupAdaptor.presetSelection + " Current Preset " + cppSetupAdaptor.curActiveThemePreset)
                cppSetupAdaptor.setPresetSelection(idThemePresetsTabView.prCurrIndex)
                cppSetupAdaptor.copyCurrentThemePresetValues(idThemePresetsTabView.prCurrIndex)
            }
            else
            {
                cppSetupApp.qmlLog("ThemeSetupScreen.qml index already active")
            }
            /*Note: Here this method is to collapse drop down item if expanded, on changing theme preset from TabBar */
            cppSetupAdaptor.collapseThemeItem(cppSetupAdaptor.expandThemeItemIndex)
        }
    }

    function getThemeElementToLoad(itemType)
    {
        cppSetupApp.qmlLog(" Load Screen " + itemType)
        switch(itemType) {
        case SetupEnums.SETUP_LIST_ITEM_DROP_DOWN:
            return "qrc:/QML/Setup/Themes/ThemeSetupMainScreen.qml"
        case SetupEnums.SETUP_LIST_ITEM_THEME_CLIMATE:
            return "qrc:/QML/Setup/Themes/ThemesClimateScreen.qml"
        case SetupEnums.SETUP_LIST_ITEM_THEME_COLOR:
            return "qrc:/QML/Setup/Themes/ThemesColorScreen.qml"
        case SetupEnums.SETUP_LIST_ITEM_THEME_LIGHTING:
            return "qrc:/QML/Setup/Themes/ThemeAmbientLightElement.qml"
        case SetupEnums.SETUP_LIST_ITEM_THEME_SOUND:
            return "qrc:/QML/Setup/Themes/ThemesSoundElement.qml"
        default:
        {
            cppSetupApp.qmlLog("ThemeSetupScreen.qml - getDelegate default case ")
            return undefined
        }
        }
    }

    /* Theme setup list is populated using GenericList and Theme setup list Model */
    GenericList {
        id: idThemeSetupList
        idList.model: cppSetupAdaptor.currentModel
        idList.delegate:
            Loader {
            id: idLoader
            property var themeSetupModel: model
            source: getThemeElementToLoad(themeSetupModel.listItemTypeRole)
            enabled: model.isListItemEnabledRole
        }

        Connections
        {
            target : ((idThemeSetupList.idList.currentIndex === (idThemeSetupList.idList.count - 1)) ? cppHardkeyAdaptor : null )
            onSigRotaryUpdate:
            {
                if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState
                        && iKeyCode === HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB)
                {
                    idAcceptSettingsBtn.forceActiveFocus()
                    idThemeSetupList.idList.currentIndex = -1
                }
                else
                {
                    //Do Nothing
                }
            }
        }
    }

    /*
          Accept button to change the selected preset to change the theme.
          */
    GenericButton{
        id: idAcceptSettingsBtn
        width: 76
        height: 76

        anchors{
            left: parent.left
            leftMargin: 340
            top: parent.top
            topMargin: 400
        }

        visible: (cppSetupAdaptor.presetSelection !== cppSetupAdaptor.curActiveThemePreset) || (cppSetupAdaptor.editModeFlag) || (cppSetupAdaptor.currentThemeModified)
        defaultImageURL: "qrc:/image/Setup/Set_Btn_ApplySetting_7in_n-assets/Set_Btn_ApplySetting_n.png"
        pressedImageURL: "qrc:/image/Setup/Set_Btn_ApplySetting_7in_n-assets/Set_Btn_ApplySetting_nf.png"
        disabledImageURL: "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Btn_RefreshSetting_7in_n-assets/Set_Btn_ApplySetting_nd.png"
        onReleased: {
            cppSetupAdaptor.applyTheme(cppSetupAdaptor.editModeFlag, idThemePresetsTabView.prCurrIndex)
            /*Note: Here we ara calling this method to collapse drop down item if expanded, post applying theme. */
            cppSetupAdaptor.collapseThemeItem(cppSetupAdaptor.expandThemeItemIndex)

            //Reset the Current And RREIndex for the list.
            idThemeSetupList.idList.currentIndex = -1
            idThemeSetupList.prRREIndex = -1
            idAcceptSettingsBtn.focus = false
        }

        /* This focus will be visible when accept button gets focus */
        Image {
            id: idAcceptSettingsBtnFocusImage

            anchors.fill: parent
            visible: parent.activeFocus
            source: idAcceptSettingsBtn.pressedImageURL
        }

        Connections
        {
            target : (idAcceptSettingsBtn.activeFocus ? cppHardkeyAdaptor : null )
            onSigRotaryUpdate:
            {
                if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState
                        && iKeyCode === HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB)
                {
                    idThemeSetupList.idList.currentIndex = (idThemeSetupList.idList.count - 1)
                    idThemeSetupList.prRREIndex = (idThemeSetupList.idList.count - 1)
                    idAcceptSettingsBtn.focus = false
                }
                else
                {
                    //Do Nothing.
                }
            }

            onSigRotaryPressed:
            {
                if(HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                        HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState){
                    cppSetupAdaptor.applyTheme(cppSetupAdaptor.editModeFlag, idThemePresetsTabView.prCurrIndex)
                    /*Note: Here we ara calling this method to collapse drop down item if expanded, post applying theme. */
                    cppSetupAdaptor.collapseThemeItem(cppSetupAdaptor.expandThemeItemIndex)

                    //Reset the Current And RREIndex for the list.
                    idThemeSetupList.idList.currentIndex = -1
                    idThemeSetupList.prRREIndex = -1
                    idAcceptSettingsBtn.focus = false

                }
            }
        }
    }
    /**
      * While closing the Theme setup screen, all the dropdowns should collapsed and get reset to their closed
      * state
      */
    Component.onDestruction : {
        cppSetupAdaptor.collapseThemeItem(cppSetupAdaptor.expandThemeItemIndex )
    }
}

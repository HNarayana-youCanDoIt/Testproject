import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.setupenums 1.0
import "../../Common/"
import com.harman.qml.thememanager 1.0

Item {
    id: idClimateSettingsItem

    height: 152
    width: 488
    enabled: true

    /* This Image background image of the drop down */
    BorderImage {
        source: "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Gfx_ListSeparator_PatchClimate_n.png"
        anchors.fill: parent
    }

    /* This image is to show the list item seperator on climate data*/
    Image {
        id: idListItemSepratorImg
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Gfx_ListSeparator_vertical2_n.png"
    }

    /*
         * This Item conatins the details of Fan speed.
         */
    Item {
        id: idFanDetailsRow
        width: 252
        height: 76

        anchors {
            top: parent.top
            topMargin: 36
            left: parent.left
            leftMargin: -7
        }
        /*
             * Button to derease the fan speed.
             */
        GenericButton {
            id: idFanSpeedDecreaseButton

            width: 76
            height: 76

            anchors{
                verticalCenter: parent.verticalCenter
            }

            enabled: ((SetupEnums.THEME_PRESET_USER === cppSetupAdaptor.presetSelection) && (cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].fanspeed > cppHVACAdaptor.fanSpeedLowLimit))

            defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_n.png"
            pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nf.png"
            disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nd.png"

            onReleased: {
                cppSetupApp.qmlLog(
                            "ThemesClimateScreen.qml: idFanSpeedDecreaseButton released." )
                cppSetupAdaptor.editModeFlag = true
                cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].fanspeed = cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].fanspeed - 1
            }
        }

        /*
         * Fan Icon
         */
        Image {
            id: idFanIcon

            anchors {
                left: idFanSpeedDecreaseButton.right
                verticalCenter: parent.verticalCenter
            }

            source: "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Gen_Drawer_Ico_Fan_n.png"
        }

        /*
             * Text Field to show the fan speed.
             */
        HBText {
            id: idFanSpeedValueText
            width: 50
            height: 50
            fontType: (enabled) ?  ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED

            anchors {
                left: idFanIcon.right
                verticalCenter: parent.verticalCenter
            }
            horizontalAlignment: Text.AlignHCenter
            text: cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].fanspeed
        }

        /*
             * Button to Increase Fan speed.
             */
        GenericButton {
            id: idFanSpeedIncreaseButton
            width: 76
            height: 76

            enabled: ((SetupEnums.THEME_PRESET_USER === cppSetupAdaptor.presetSelection) && (cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].fanspeed < cppHVACAdaptor.fanSpeedHighLimit))

            anchors {
                left: idFanSpeedValueText.right
                verticalCenter: parent.verticalCenter
            }

            defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_n.png"
            pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nf.png"
            disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nd.png"

            onReleased: {
                cppSetupApp.qmlLog(
                            "ThemesClimateScreen.qml: idFanSpeedIncreaseButton released.")
                cppSetupAdaptor.editModeFlag = true
                cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].fanspeed = cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].fanspeed + 1
            }
        }
    }

    /*
         * Climate temperature Item, Which contains temprature details.
         */
    Item {
        id: idTempratureDetailsRow
        width: 252
        height: 76

        anchors {
            top: parent.top
            topMargin: 36
            left: parent.left
            leftMargin: 240
        }

        /*
             * Button to Decrease the temperature.
             * Decrease the Temperature by 0.5 deg C.
             */
        GenericButton {
            id: idTempratureDecreaseButton

            width: 76
            height: 76

            anchors{
                verticalCenter: parent.verticalCenter
            }

            enabled: ((SetupEnums.THEME_PRESET_USER === cppSetupAdaptor.presetSelection)
                      && (cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].temperature > cppHVACAdaptor.temperatureLowLimit))

            defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_n.png"
            pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nf.png"
            disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nd.png"

            onReleased: {
                cppSetupApp.qmlLog(
                            "ThemesClimateScreen.qml: idTempratureDecreaseButton released.")
                cppSetupAdaptor.editModeFlag = true
                cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].temperature = cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].temperature - 0.5
            }
        }

        /*
             * Text Field to show the temperature value.
             */
        HBText {
            id: idTemperatureValueText

            width: 100
            height: 76

            fontType: (enabled) ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED

            horizontalAlignment: Text.AlignHCenter

            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }

            text: (cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].temperature.toFixed(1) + qsTr("°C") + cppThemeMgr.languageChanged)
        }

        /*
             * Button to Increase the temperature.
             * Increase the Temperature by 0.5 deg C .
             */
        GenericButton {
            id: idTempratureIncreaseButton

            anchors{
                left: idTemperatureValueText.right
                verticalCenter: parent.verticalCenter
            }

            enabled: ((SetupEnums.THEME_PRESET_USER === cppSetupAdaptor.presetSelection)
                      && (cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].temperature < cppHVACAdaptor.temperatureHighLimit))

            width: 76
            height: 76

            defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_n.png"
            pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nf.png"
            disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nd.png"

            onReleased: {
                cppSetupApp.qmlLog(
                            "ThemesClimateScreen.qml: idTempratureIncreaseButton released.")
                cppSetupAdaptor.editModeFlag = true
                cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].temperature = cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].temperature + 0.5
            }
        }
    }
}


import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.setupenums 1.0
import "../../Common/"
import com.harman.qml.thememanager 1.0

Item {
    id: idColorSettingsItem
    height: 152
    width: 488
    enabled: true

    /*
         * This property is used to check that the
         * brightness level is updated by user or
         * not. because we have to call service api
         * only if user changes the brightness, at
         * the time of component load the slider position also gets changed.
         * No need to call service api that time.
         */
    property bool isUserInitiated: false

    property int iThemeColor: cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].themeColor

    /* This image is used for the background image of the drop down*/
    BorderImage {
        source: "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Gfx_ListSeparator_PatchClimate_n.png"
        anchors.fill: parent
    }

    /*
     * This Item conatins the details of Fan.
     */
    Item {
        id: idColorDetailsItem
        width: 240
        height: 55

        anchors {
            top: parent.top
            topMargin: 35
            left: parent.left
            leftMargin: 140
        }

        /*
         * Button to change the color.
         */
        GenericButton {
            id: idColorChangePrevButton

            width: 70
            height: 70

            anchors.left: parent.left
            anchors.leftMargin: 6

            enabled : (SetupEnums.THEME_PRESET_USER === cppSetupAdaptor.presetSelection)

            defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_n.png"
            pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nf.png"
            disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nd.png"

            onReleased: {
                cppSetupApp.qmlLog("ThemeSetupScreen.qml: idColorChangePrevButton released.")
                cppSetupAdaptor.editModeFlag = true

                // Here we substracted the themecolor to 1 because the theme color value starts from 0
                if(iThemeColor > ThemeMgr.THEME_TYPE_1)
                {
                    iThemeColor =  iThemeColor - 1
                }
                else
                {
                    iThemeColor =  (iThemeColor + (ThemeMgr.THEME_TYPE_MAX - 1))
                }
                cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].themeColor = iThemeColor
            }
        }

        /*
        * Rectangle to change the Color Icon
        */
        Rectangle{
            id:rectThemeColor

            width: 99
            height: 39
            border.color: "black"
            border.width: 1
            radius: 5
            anchors {
                top: parent.top
                topMargin: 15
                left: idColorChangePrevButton.right
                leftMargin: -5
            }
            color: colorModeImagesArray[cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].themeColor]
        }

        /*
        * Button to change the color.
        */
        GenericButton {
            id: idColorChangeNextButton
            width: 70
            height: 70

            anchors {
                left: rectThemeColor.right
                leftMargin: -7
            }

            enabled : (SetupEnums.THEME_PRESET_USER === cppSetupAdaptor.presetSelection )

            defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_n.png"
            pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nf.png"
            disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nd.png"


            onReleased: {
                cppSetupApp.qmlLog("ThemeSetupScreen.qml: idColorChangeNextButton released.")
                cppSetupAdaptor.editModeFlag = true

                // Here we added the themecolor to 1 because the theme color value starts from 0
                if(iThemeColor < ThemeMgr.THEME_TYPE_5)
                {
                    iThemeColor = iThemeColor + 1
                }
                else
                {
                    iThemeColor = (iThemeColor - (ThemeMgr.THEME_TYPE_MAX - 1))
                }
               cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].themeColor = iThemeColor
            }
        }
    }
}

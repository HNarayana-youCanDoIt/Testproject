import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.setupenums 1.0
import com.harman.qml.thememanager 1.0

Item{
    width: idGenericList.width
    height: idGenericList.prItemHeight

    Column {
        LabelWithClickableImage {
            id: idDropDownAndToggleComponent
            width: idGenericList.width
            height: idGenericList.prItemHeight - idCheckboxItemSeparator.height

            prDefaultImage: getDefaultImage()

            prPressedImage: getPressedImage()

            prDisabledImage: getDisabledImage()

            text: itemTextRole

            onSigImageClicked:{
                toggleExpandState()
            }

            enabled: itemEnabledRole

            onReleased:{
                toggleExpandState()
            }

            onEnabledChanged: {
                cppSetupAdaptor.themeSetupWithDriveModeListModel.invCollapseThemesDropdown()
            }

            function getDefaultImage(){
                switch(itemId){
                case SetupEnums.THEME_SETUP_WITH_DRIVE_MODE_CHANGE_THEME_WITH_DRIVE_MODE:
                    // this role is used to check that the item is checked or not
                    if(itemCheckedRole)
                        return "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_On_na.png";
                    else
                        return "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_Off_na.png";

                case SetupEnums.THEME_SETUP_WITH_DRIVE_MODE_THEMES:
                    // this role is used to check that the item is expanded or not
                    if(itemCheckedRole)
                        return "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_n.png";
                    else
                        return "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"
                }
            }

            function getPressedImage(){
                switch(itemId){
                case SetupEnums.THEME_SETUP_WITH_DRIVE_MODE_CHANGE_THEME_WITH_DRIVE_MODE:
                    // this role is used to check that the item is checked or not
                    if(itemCheckedRole)
                        return "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_On_nf.png";
                    else
                        return  "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_Off_np.png";

                case SetupEnums.THEME_SETUP_WITH_DRIVE_MODE_THEMES:
                    // this role is used to check that the item is expanded or not
                    if(itemCheckedRole)
                        return "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nf.png";
                    else
                        return "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nf.png";
                }
            }

            function getDisabledImage(){
                switch(itemId){
                case SetupEnums.THEME_SETUP_WITH_DRIVE_MODE_CHANGE_THEME_WITH_DRIVE_MODE:
                    // this role is used to check that the item is checked or not
                    if(itemCheckedRole)
                        return "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_On_nd.png";
                    else
                        return "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_On_nd.png";

                case SetupEnums.THEME_SETUP_WITH_DRIVE_MODE_THEMES:
                    // this role is used to check that the item is expanded or not
                    if(itemCheckedRole)
                        return "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nd.png";
                    else
                        return "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nd.png";
                }
            }

            function toggleExpandState() {
                cppSetupApp.qmlLog("ThemesToggleAndDropdownDelegate.qml, toggleExpandState, index: "+ itemId)
                if(SetupEnums.THEME_SETUP_WITH_DRIVE_MODE_CHANGE_THEME_WITH_DRIVE_MODE === itemId){
                    cppSetupAdaptor.themeSetupWithDriveModeListModel.invToggleChangeThemeWithDriveMode(itemCheckedRole)
                }
                else if(SetupEnums.THEME_SETUP_WITH_DRIVE_MODE_THEMES === itemId){
                    // this role is used to check that the item is expanded or not
                    if(itemCheckedRole){
                        cppSetupAdaptor.themeSetupWithDriveModeListModel.invCollapseThemesDropdown()
                    }
                    else{
                        cppSetupAdaptor.themeSetupWithDriveModeListModel.invExpandThemesDropdown()
                    }
                }
                else{
                    cppSetupApp.qmlLog("Invalid Option Selected")
                }
            }
        }


        ListItemSeparator{
            id: idCheckboxItemSeparator
        }

        Connections{
            target: cppHardkeyAdaptor
            onSigRotaryPressed: {
                cppSetupApp.qmlLog("ThemesToggleAndDropdownDelegate.qml : right rotary pressed")

                if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode
                   && (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState
                   || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState)){
                    if(idGenericList.idList.currentIndex === index){
                        idDropDownAndToggleComponent.toggleExpandState()
                    }
                }
            }
        }

    }

    Component.onDestruction: {
        if(SetupEnums.THEME_SETUP_WITH_DRIVE_MODE_THEMES === itemId){
            if(itemCheckedRole){
                cppSetupApp.qmlLog("ThemesToggleAndDropdownDelegate.qml : Component.onDestruction")
                cppSetupAdaptor.themeSetupWithDriveModeListModel.invCollapseThemesDropdown()
            }
        }
    }
}

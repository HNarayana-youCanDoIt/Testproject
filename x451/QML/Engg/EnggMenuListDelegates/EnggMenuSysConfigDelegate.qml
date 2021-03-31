import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.enggMenuenums 1.0

/** Delegate of Button List Item with Label and its Value(Label)  **/
Item {
    id: idBtnListSysConfigDelegate
    width: idGenericList.idList.width
    height: idGenericList.prItemHeight

    Column {
        LabelWithLabelComp {
            id: idSysConfigComp
            width: idGenericList.idList.width
            height: (idGenericList.prItemHeight - idSeparator.height)
            prItemSubText: enggMenuItemSubTextRole
            text: enggMenuItemMainTextRole
            prMainTextFontType : ThemeMgr.FONTTYPE_T24_LIGHT_C2
            prSubTextFontType  : ThemeMgr.FONTTYPE_T24_LIGHT_C2
            prMainTextWidth    : 300
            pressedImageURL: (((enggMenuItemIdRole === EnggMenuEnums.ENGG_MENU_ID_ALL_16R_PART_NUMBERS)||
                              (enggMenuItemIdRole === EnggMenuEnums.ENGG_MENU_ID_VC_NUMBER)||
                              (enggMenuItemIdRole === EnggMenuEnums.ENGG_MENU_ID_VIN)) && EnggMenuEnums.ENGG_MENU_SCREEN_SYSTEM_CONFIG)
                             ? "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png"
                             : ""

            onReleased:{
                /**
                  * raiseSMEvent function from the EnggApplication takes the id of the list item
                  * and carries it forward to the next state (if present)according to the model of the screen
                 **/
                cppEnggApplication.raiseSMEvent("EnggMenu", enggMenuItemIdRole)
            }
        }

        ListItemSeparator {
            id:idSeparator
        }


        Connections
        {
            target: cppHardkeyAdaptor

            onSigRotaryPressed :
            {
                if((HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode) &&
                        (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                         HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                {
                    cppEnggApplication.qmlLog("onSigRotaryPressed:: iKeyCode"+ iKeyCode)
                    if(idGenericList.idList.currentIndex === index)
                    {
                        /**
                         *raiseSMEvent function from the EnggApplication takes the id of the list item
                         * and carries it forward to the next state (if present)according to the model of the screen
                        */

                        cppEnggApplication.raiseSMEvent("EnggMenu", enggMenuItemIdRole)
                    }
                }
            }

        }

    }

}

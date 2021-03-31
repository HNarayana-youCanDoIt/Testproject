import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.enggMenuenums 1.0

/** Delegate of Button List Item with Label and its Value(Label)  **/
Item {
    id: idBtnListLabelWithLabelDelegate

    width: idGenericList.idList.width
    height: idGenericList.prItemHeight

    Column {
        LabelWithLabelComp {
            id: idLabelwithLabelComp
            width: idGenericList.idList.width
            height: (idGenericList.prItemHeight - idSeparator.height)
            prMainTextFontType : (EnggMenuEnums.ENGG_MENU_SCREEN_DEBUG_LOG === cppEnggAdaptor.enggMenuCurrentScreen)
                                 ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C2
            prSubTextFontType  : (EnggMenuEnums.ENGG_MENU_SCREEN_DEBUG_LOG === cppEnggAdaptor.enggMenuCurrentScreen)
                                 ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C2
            prItemSubText: enggMenuItemSubTextRole
            text: enggMenuItemMainTextRole
            prMainTextWidth : 300
            /**
                Do not show any focus image when user touches/press any item
              **/
            pressedImageURL: ""

            onReleased:{
                /**
                  * processEnggMenuItemClick function from the EnggAdaptor takes the id of the list item
                  * and carries it forward to process accordingly. This is only applicable for Extract Logs which is present only in
                  Debug Logs
                 **/
                if(EnggMenuEnums.ENGG_MENU_SCREEN_DEBUG_LOG === cppEnggAdaptor.enggMenuCurrentScreen)
                {
                    cppEnggAdaptor.processEnggMenuItemClick(enggMenuItemIdRole)
                }
                else
                {
                    //Do not take any action
                }
            }
        }

        ListItemSeparator {
            id:idSeparator
        }

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
                      * processEnggMenuItemClick function from the EnggAdaptor takes the id of the list item
                      * and carries it forward to process accordingly. This is only applicable for Extract Logs which is present only in
                      * Debug Logs
                    **/
                    if(EnggMenuEnums.ENGG_MENU_SCREEN_DEBUG_LOG === cppEnggAdaptor.enggMenuCurrentScreen)
                    {
                        cppEnggAdaptor.processEnggMenuItemClick(enggMenuItemIdRole)
                    }
                    else
                    {
                        //Do not take any action
                    }
                }
            }
        }

    }
}

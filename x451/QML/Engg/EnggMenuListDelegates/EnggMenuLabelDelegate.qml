import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.hardkeyenum 1.0

/** Delegate of Button List Item with Label **/
Item {
    id: idBtnListWithLabelDelegate

    width: idGenericList.idList.width
    height: idGenericList.prItemHeight

    Column {
        HBButtonListItem {
            id: idLabelComp
            width: idGenericList.idList.width
            height: (idGenericList.prItemHeight - idSeparator.height)
            text: enggMenuItemMainTextRole

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
                    * raiseSMEvent function from the EnggApplication takes the id of the list item
                    * and carries it forward to the next state (if present)according to the model of the screen
                    **/
                    cppEnggApplication.raiseSMEvent("EnggMenu", enggMenuItemIdRole)
                }

            }

        }
    }
}

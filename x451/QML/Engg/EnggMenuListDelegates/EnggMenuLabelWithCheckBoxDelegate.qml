import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.hardkeyenum 1.0

/** Delegate of Button List Item with Label and CheckBox  **/
Item {
    id: idBtnListLabelWithCheckBoxDelegate

    width: idGenericList.idList.width
    height: idGenericList.prItemHeight

    Column {
        LabelWithCheckBoxComp {
            id: idLabelWithCheckboxComp
            width: idGenericList.idList.width
            height: (idGenericList.prItemHeight - idSeparator.height)
            text: enggMenuItemMainTextRole
            prCheckBoxChecked: enggMenuItemStatusRole

            onReleased: {
                /**
                 * toggleEnggCheckbox  function will send the present status of the checkbox and the listItem id to
                 * to take action according to the selected ListItem.
                */
                cppEnggApplication.qmlLog("Label with CheckBox delegate, enggMenuItemIdRole:" + enggMenuItemIdRole)
                cppEnggAdaptor.toggleEnggCheckbox(!prCheckBoxChecked,enggMenuItemIdRole)
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
                 * toggleEnggCheckbox  function will send the present status of the checkbox and the listItem id to
                 * to take action according to the selected ListItem.
                */
                    cppEnggApplication.qmlLog("Label with CheckBox delegate, enggMenuItemIdRole:" + enggMenuItemIdRole)
                    cppEnggAdaptor.toggleEnggCheckbox(!(idLabelWithCheckboxComp.prCheckBoxChecked),enggMenuItemIdRole)
                }
            }
        }

    }
}

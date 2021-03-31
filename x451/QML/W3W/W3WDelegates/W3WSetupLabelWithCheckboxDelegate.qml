import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0

/** Label with CheckBox Delegate ***
  * Delegate containing Label and Checkbox Delegate.
  */

Item
{
    id: idLabelWithCheckBoxComponent
    width: idGenericList.width
    height: idGenericList.prItemHeight

    Column
    {
        LabelWithCheckBoxComp
        {
            id: idLabelWithCheckbox
            width: idGenericList.width
            height: idGenericList.prItemHeight - idCheckboxItemSeparator.height
            text:  itemTextRole
            prCheckBoxChecked:  itemCheckedRole

            onReleased:
            {
                cppW3WApplication.qmlLog("W3WSetupLabelWithCheckboxDelegate.qml - itemId: "+ itemId +" itemTextRole: " + itemTextRole+"
                                                                    itemCheckedRole: " + itemCheckedRole)
                cppW3WAdaptor.invUpdateCheckboxSetting(itemId, !prCheckBoxChecked)
                itemCheckedRole = !prCheckBoxChecked
            }
        }

        ListItemSeparator
        {
            id: idCheckboxItemSeparator
        }
    }

    //Handling RRE HK for bluetooth visibility item
    Connections
    {
        target: cppHardkeyAdaptor
        onSigRotaryPressed:
        {
            cppW3WApplication.qmlLog("GenericList: onRotaryUpdate: idLabelWithCheckBoxComponent: " + iKeyState)
            if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                    || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
            {
                if(idGenericList.idList.currentIndex === index)
                {
                    cppW3WApplication.qmlLog("W3WSetupLabelWithCheckboxDelegate.qml - LabelWithCheckBoxComp RRE release/longRelease
                                                                event, itemIndex is: " + index)
                    cppW3WAdaptor.invUpdateCheckboxSetting(index, !idLabelWithCheckbox.prCheckBoxChecked)
                }
            }
        }
    }
}

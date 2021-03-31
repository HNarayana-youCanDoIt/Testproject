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
                cppPhoneApp.qmlLog("PhoneSetup.qml - LabelWithCheckBoxComp onCompleted event, itemIndex is:" +
                                   itemTypeRole)
                cppPhoneAdaptor.invSetDiscoverableMode(!prCheckBoxChecked)
            }
        }

        //Handling RRE HK for bluetooth visibility item
        Connections
        {
            target: cppHardkeyAdaptor
            onSigRotaryPressed:
            {
                cppPhoneApp.qmlLog("GenericList: onRotaryUpdate: idLabelWithCheckBoxComponent: " + iKeyState)
                if(iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED
                        || iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)
                {
                    if(idGenericList.idList.currentIndex === index)
                    {
                        cppPhoneApp.qmlLog("PhoneSetup.qml - LabelWithCheckBoxComp RRE release/longRelease
                                                                event, itemIndex is: " + index)
                        cppPhoneAdaptor.invSetDiscoverableMode(!itemCheckedRole)
                    }
                }
            }
        }


        ListItemSeparator
        {
            id: idCheckboxItemSeparator
        }
    }
}

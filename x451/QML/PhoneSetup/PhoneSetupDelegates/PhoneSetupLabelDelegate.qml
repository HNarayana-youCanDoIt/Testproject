import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0

/** Label Delegate ***
  * Delegate containing only Label.
  */

Item
{
    id: idLabelDelegate
    width: idGenericList.idList.width
    height: idGenericList.prItemHeight
    Column
    {
        HBButtonListItem
        {
            id: idBtnText
            width: idGenericList.width
            height: idGenericList.prItemHeight - idBtnListItemSeparator.height
            text: itemTextRole
            onReleased:
            {
                cppPhoneApp.qmlLog("PhoneSetup.qml - HBButtonListItem onReleased event, itemId is: " + itemId)
                cppPhoneApp.raiseSMEvent("PhoneSetupPopup", itemId)
            }
        }

        //Handling RRE HK for pair new device item and paired device item
        Connections {
            target: cppHardkeyAdaptor
            onSigRotaryPressed: {
                cppPhoneApp.qmlLog(
                            "GenericList: onRotaryUpdate: idBtnListItemComponent: " + iKeyState)
                //TODO: Need to change magic numbers for keyState comparison to ENUM
                if(HardkeyEnum.HKEY_STATE_LONGPRESSED  === iKeyState
                        || HardkeyEnum.HKEY_STATE_RELEASED === iKeyState)
                {
                    if(idGenericList.idList.currentIndex === index)
                    {
                        cppPhoneApp.qmlLog("PhoneSetup.qml - HBButtonListItem RRE release/longReleae event,
                                            itemIndex is: " + index)
                        cppPhoneApp.raiseSMEvent("PhoneSetupPopup", itemId)
                    }
                    else
                    {
                        //Do Nothing
                    }
                }
                else
                {
                    // Do Nothing
                }
            }
        }

        ListItemSeparator
        {
            id: idBtnListItemSeparator
        }
    }
}



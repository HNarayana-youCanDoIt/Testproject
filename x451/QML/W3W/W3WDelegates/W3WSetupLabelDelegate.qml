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
                cppW3WApplication.qmlLog("W3WSetupLabelDelegate.qml - HBButtonListItem onReleased event, itemId is: " + itemId)
                cppW3WApplication.raiseSMEvent("LaunchW3WAboutScreen", itemId)
            }
        }

        ListItemSeparator
        {
            id: idBtnListItemSeparator
        }

        //Handling RRE HK for pair new device item and paired device item
        Connections {
            target: cppHardkeyAdaptor
            onSigRotaryPressed: {
                cppW3WApplication.qmlLog(
                            "GenericList: onRotaryUpdate: idBtnListItemComponent: " + iKeyState)

                if(HardkeyEnum.HKEY_STATE_LONGPRESSED  === iKeyState
                        || HardkeyEnum.HKEY_STATE_RELEASED === iKeyState)
                {
                    if(idGenericList.idList.currentIndex === index)
                    {
                        cppW3WApplication.qmlLog("W3WSetupLabelDelegate.qml - HBButtonListItem RRE release/longReleae event,
                                            itemIndex is: " + index)
                        cppW3WApplication.raiseSMEvent("LaunchW3WAboutScreen", itemId)
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
    }
}



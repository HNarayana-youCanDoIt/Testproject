/**
 * @file            DoodleSetupLabelDelegate.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * DoodleSetupLabelDelegate, a comopnent can use to show doodle setting element on doodle setting screen,
 * It has Title field to show information.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0

Item
{
    id: idLabelDelegate
    width: idGenericList.idList.width
    height: idGenericList.prItemHeight

    Column {
        enabled: cppDoodleAdaptor.doodleSetupElements[genericListItemTypeRole].enabled

        HBButtonListItem {
            height: idGenericList.prItemHeight - idSeparator.height
            width: idGenericList.idList.width
            text: cppDoodleAdaptor.doodleSetupElements[genericListItemTypeRole].name

            onReleased: {
                cppDoodleApplication.qmlLog("DoodleSetupLabelDelegate.qml onReleased - index: " + index)
                cppDoodleAdaptor.handleDoodleSetupElementTouchEvent(genericListItemTypeRole)
            }
        }
        ListItemSeparator {
            id: idSeparator
        }

        //Handling RRE HK for Delegate
        Connections {
            target: cppHardkeyAdaptor
            onSigRotaryPressed: {
                cppDoodleApplication.qmlLog("DoodleSetupLabelDelegate: onRotaryUpdate: "+iKeyState)
                if((iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED) || (iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)) {
                    if(idGenericList.idList.currentIndex === index) {
                        cppDoodleApplication.qmlLog("DoodleSetupLabelDelegate.qml onSigRotaryPressed - index: " + index)
                        cppDoodleAdaptor.handleDoodleSetupElementTouchEvent(genericListItemTypeRole)

                        idGenericList.prRREIndex = index
                    }
                    else
                    {
                        //Do Nothing! "Invalid option selected"
                    }
                }
                else
                {
                    //Do Nothing! "Not in Released/LongReleased HardKey State"
                }
            }
        }
    }
}

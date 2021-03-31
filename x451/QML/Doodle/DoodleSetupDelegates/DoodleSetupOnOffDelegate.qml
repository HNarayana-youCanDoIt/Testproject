/**
 * @file            DoodleSetupOnOffDelegate.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * DoodleSetupOnOffDelegate, a comopnent can use to show doodle setting element on doodle setting screen,
 * It has Title, On/Off Status Icon field to show information.
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

            //Fix Me add On/Off button image here
            Rectangle {
                id: idOnOffIcon
                height: parent.height/3
                width: height*4
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: 10
                }
                color: cppDoodleAdaptor.doodleSetupElements[genericListItemTypeRole].toggleStatus ? "green" : "red"
            }

            onReleased: {
                cppDoodleApplication.qmlLog("DoodleSetupOnOffDelegate.qml onReleased - index: " + index)
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
                cppDoodleApplication.qmlLog("DoodleSetupOnOffDelegate: onRotaryUpdate: "+iKeyState)
                if((iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED) || (iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)) {
                    if(idGenericList.idList.currentIndex === index) {
                        cppDoodleApplication.qmlLog("DoodleSetupOnOffDelegate.qml onSigRotaryPressed - index: " + index)
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

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0

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

            pressedImageURL: ""

            contentItem: Item {}

            /**
              * Title text field
              */
            HBText {
                anchors {
                    left: parent.left
                    leftMargin: 11
                }
                width: 400
                height: idGenericList.prItemHeight - idSeparator.height

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

                text: cppDriveNextAdaptor.signalsData[enggMenuItemIdRole].enggTitle

                onEnabledChanged: {
                    fontType = (enabled) ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                }
            }

            /**
              * Unit text field
              */
            HBText {
                id: idUnitField

                anchors {
                    right: parent.right
                    rightMargin: 11
                }
                height: idGenericList.prItemHeight - idSeparator.height

                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

                text: cppDriveNextAdaptor.signalsData[enggMenuItemIdRole].enggUnit

                onEnabledChanged: {
                    fontType = (enabled) ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                }
            }

            /**
              * Value text field
              */
            HBText {
                id: idValueField

                anchors {
                    right: idUnitField.left
                    rightMargin: 2
                }
                height: idGenericList.prItemHeight - idSeparator.height

                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

                text: cppDriveNextAdaptor.signalsData[enggMenuItemIdRole].enggValue

                onEnabledChanged: {
                    fontType = (enabled) ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                }
            }

            /**
              * sub Unit text field
              */
            HBText {
                id: idSubUnitField

                anchors {
                    right: idValueField.left
                    rightMargin: 5
                }
                height: idGenericList.prItemHeight - idSeparator.height

                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

                text: cppDriveNextAdaptor.signalsData[enggMenuItemIdRole].enggSubUnit

                onEnabledChanged: {
                    fontType = (enabled) ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                }
            }

            /**
              * sub Value text field
              */
            HBText {
                anchors {
                    right: idSubUnitField.left
                    rightMargin: 2
                }
                height: idGenericList.prItemHeight - idSeparator.height

                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

                text: cppDriveNextAdaptor.signalsData[enggMenuItemIdRole].enggSubValue

                onEnabledChanged: {
                    fontType = (enabled) ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                }
            }

            onReleased: {
                /**
                  * raiseSMEvent function from the EnggApplication takes the id of the list item
                  * and carries it forward to the next state (if present)according to the model of the screen
                 **/
                //For DriveNext Engg Details there is no any requirement to handle inputs hence no flow added here
            }
        }

        ListItemSeparator {
            id:idSeparator
        }
    }

    Connections {
        target: cppHardkeyAdaptor

        onSigRotaryPressed : {
            if((HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode) &&
                    (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                     HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState)) {
                cppEnggApplication.qmlLog("onSigRotaryPressed:: iKeyCode"+ iKeyCode)
                if(idGenericList.idList.currentIndex === index) {
                    /**
                    * raiseSMEvent function from the EnggApplication takes the id of the list item
                    * and carries it forward to the next state (if present)according to the model of the screen
                    **/
                    //For DriveNext Engg Details there is no any requirement to handle inputs hence no flow added here
                }
                else {
                    //Do Nothing!
                }
            } else {
                //Do Nothing!
            }
        }
    }
}

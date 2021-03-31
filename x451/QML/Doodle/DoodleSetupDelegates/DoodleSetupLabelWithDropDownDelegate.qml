/**
 * @file            DoodleSetupLabelWithDropDownDelegate.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * DoodleSetupLabelWithDropDownDelegate, a comopnent can use to show doodle setting element on doodle setting screen,
 * It has Title, Expand/Collapse Icon field to show information.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../../Common"
import com.harman.qml.hardkeyenum 1.0

Item
{
    id: idLabelWithDropDownImageDelegate
    width: idGenericList.idList.width
    height: idGenericList.prItemHeight

    Column {
        enabled: cppDoodleAdaptor.doodleSetupElements[genericListItemTypeRole].enabled

        LabelWithClickableImage {
            height: idGenericList.prItemHeight - idSeparator.height
            width: idGenericList.idList.width
            text: cppDoodleAdaptor.doodleSetupElements[genericListItemTypeRole].name

            prDefaultImage: (cppDoodleAdaptor.doodleSetupExpandedElement === genericListItemTypeRole)
                            ? "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_n.png"
                            : "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_n.png"

            prPressedImage: (cppDoodleAdaptor.doodleSetupExpandedElement === genericListItemTypeRole)
                            ? "qrc:/image/Gen_Ico_SetArrowTop_7in_n-assets/Gen_Ico_SetArrowTop_7in_nf.png"
                            : "qrc:/image/Gen_Ico_SetArrowBottom_7in_n-assets/Gen_Ico_SetArrowBottom_7in_nf.png"

            onSigImageClicked: {
                cppDoodleApplication.qmlLog("DoodleSetupLabelWithDropDownDelegate.qml onSigImageClicked - index: " + index)
                cppDoodleAdaptor.handleDoodleSetupElementTouchEvent(genericListItemTypeRole)
            }

            onReleased: {
                cppDoodleApplication.qmlLog("DoodleSetupLabelWithDropDownDelegate.qml onReleased - index: " + index)
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
                cppDoodleApplication.qmlLog("DoodleSetupLabelWithDropDownDelegate: onRotaryUpdate: "+iKeyState)
                if((iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED) || (iKeyState === HardkeyEnum.HKEY_STATE_RELEASED)) {
                    if(idGenericList.idList.currentIndex === index) {
                        cppDoodleApplication.qmlLog("DoodleSetupLabelWithDropDownDelegate.qml onSigRotaryPressed - index: " + index)
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

import QtQuick 2.7
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.vrenum 1.0
import "../Common"

BaseUI
{
    id: idPickListMain

    Connections
    {
        target: cppVRAdaptor
        onSigSetFocusedItem:
        {
            cppUIBase.qmlLog("onSigSetFocusedItem : slot called")
            if((iLineNo > 0) && (iLineNo <= idPickList.idList.count))
            {
                idPickList.idList.currentIndex = (iLineNo - 1)
                cppVRAdaptor.invSendVRResponse(VREnum.EN_RESPONSE_TYPE_SUCCESS)
            }
            else
            {
                cppVRAdaptor.invSendVRResponse(VREnum.EN_RESPONSE_TYPE_INVALID)
            }
        }
    }

    // TODO: Language string id should be added instead of static text.
    //Title of pair new device screen.
    HBTitleWithBackButton
    {
        prTitle: qsTr("TEXT_VR_PICK_LIST_TITLE_LABEL") + cppThemeMgr.languageChanged
        prBackButtonVisible: false
    }

    // Mouse area to deactivate VR session on background touch
    MouseArea{
        anchors.fill: parent
        onPressed: {
            cppVRApp.qmlLog("PicklistScreen.qml : Pick list screen onPressed")
            // Deactivate VR session
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
        }
    }

    //Delegate of pick list item component
    Component
    {
        id: idPickListListItemDelegate
        Column
        {
            HBButtonListItem
            {
                id: idPickListItem
                width: idPickList.idList.width
                height: (idPickList.prItemHeight - idPickListItemSeparator.height)
                text: vrListItemNameRole
                //Inform VR adaptor that item is selected
                onReleased:
                {
                    cppVRApp.qmlLog("PickListScreen.qml: OnReleased for device " + index)
                    //Incrementing index by 1 as index starts from 1 and in HMI the list index starts from 0
                    cppVRAdaptor.invPickListItemSelected(index + 1)

                }
            }

            //Handling RRE HK for searched device items in the list
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("PickListScreen: onRotaryUpdate: key state is: " + iKeyState)
                    if((iKeyState === HardkeyEnum.HKEY_STATE_RELEASED) || (iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED))
                    {
                        //Inform VR adaptor that item is selected
                        if(idPickList.idList.currentIndex === index)
                        {
                            cppVRApp.qmlLog("PickListScreen.qml: OnReleased for device " + index)
                            //Incrementing index by 1 as index starts from 1 and in HMI the list index starts from 0
                            cppVRAdaptor.invPickListItemSelected(index + 1)
                        }
                    }
                }

                onSigPassHardkeyToOverlay:
                {
                    cppVRApp.qmlLog("VRAnimPopup.qml: onSigPassHardkeyToOverlay: iKeyCode is: " + iKeyCode, " keystate is: ", iKeyState)
                    //Inform VR adaptor to handle hardkey event
                    cppHardkeyAdaptor.invSetHKHandledByOverlayStatus(cppVRAdaptor.invHandleHardKeys(iKeyCode, iKeyState))
                }
            }

            ListItemSeparator
            {
                id: idPickListItemSeparator
            }
        }
    }

    // Pick List.
    GenericList
    {
        id: idPickList
        idList.model: cppVRAdaptor.pickListModel
        idList.delegate: idPickListListItemDelegate
    }
}

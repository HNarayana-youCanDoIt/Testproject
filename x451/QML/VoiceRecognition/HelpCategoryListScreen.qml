import QtQuick 2.7
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.thememanager 1.0
import "../Common"

BaseUI
{
    id: idHelpCategoryListMain

    //Title of VR help category screen.
    HBTitleWithBackButton
    {
        prTitle: qsTr("TEXT_VR_HELP") + cppThemeMgr.languageChanged
        prBackButtonVisible: true
    }

    //Delegate of help category list item component
    Component
    {
        id: idHelpCategoryListItemDelegate
        Column
        {
            HBButtonListItem
            {
                id: idHelpCategoryListItem
                width: idHelpCategoryList.idList.width
                height: (idHelpCategoryList.prItemHeight - idHelpCategoryListItemSeparator.height)
                text: vrHelpTextRole
                //Inform VR adaptor that item is selected
                onReleased:
                {
                    cppVRApp.qmlLog("HelpCategoryListScreen.qml: OnReleased for help category " + index)
                    cppVRAdaptor.invUpdateVRHelpCommandList(index, vrHelpTextRole)
                    cppVRApp.raiseSMEvent("VRHelpCommand", "")
                }
            }

            //Handling RRE HK for vr help category items in the list
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("HelpCategoryListScreen: onRotaryUpdate: key state is: " + iKeyState)
                    if((iKeyState === HardkeyEnum.HKEY_STATE_RELEASED) || (iKeyState === HardkeyEnum.HKEY_STATE_LONGPRESSED))
                    {
                        //Inform VR adaptor that item is selected
                        if(idHelpCategoryList.idList.currentIndex === index)
                        {
                            cppVRApp.qmlLog("HelpCategoryListScreen.qml: OnReleased for help category " + index)
                            cppVRAdaptor.invUpdateVRHelpCommandList(index, vrHelpTextRole)
                            cppVRApp.raiseSMEvent("VRHelpCommand", "")
                        }
                    }
                }
            }

            ListItemSeparator
            {
                id: idHelpCategoryListItemSeparator
            }
        }
    }

    // Help category List.
    GenericList
    {
        id: idHelpCategoryList
        idList.model: cppVRAdaptor.vrHelpCategories
        idList.delegate: idHelpCategoryListItemDelegate
    }
}

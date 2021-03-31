import QtQuick 2.7
import com.harman.qml.thememanager 1.0
import "../Common"
import "../PhoneSetup/PhoneSetupDelegates"

BaseUI
{
    id: idHelpCommandListMain

    //Title of VR help command screen.
    HBTitleWithBackButton
    {
        prTitle: cppVRAdaptor.vrHelpCategoryName + cppThemeMgr.languageChanged
        prBackButtonVisible: true
    }

    Component{
        id: idDelegate
        Column {
            PhoneSetupMessageContentDelegate{
                id: idHelpCommandListItemDelegate
                width : idHelpCommandList.idList.width
                height: ((Math.ceil(prMessageTextHeight/idHelpCommandList.prItemHeight) * idHelpCommandList.prItemHeight)
                         - (idHelpCommandListItemSeparator.height))
                prText : vrHelpTextRole
                prHBText.lineHeight: 1.5
                prEditBtnVisibilityStatus : false
            }


            ListItemSeparator
            {
                id: idHelpCommandListItemSeparator
            }
        }
    }

    // Help command List.
    GenericList
    {
        id: idHelpCommandList
        idList.model: cppVRAdaptor.vrHelpCommands
        idList.delegate: idDelegate
        /*Note : Here cache buffer is used becasue it
                 smoothenes the list on scrolling and reduces the issues of glitching on movement.
                 CacheBuffer has been given 1000 because if list view height is 304 pixels and cachebuffer is set to 1000,
                 then upto 2 delegates above and below the visible area may be created/retained.
                 So the flickering of the list view has been reduced*/
        idList.cacheBuffer: 1000
    }
}

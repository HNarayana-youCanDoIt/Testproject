import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.enggMenuenums 1.0
import "qrc:/QML/Common"

/** QML Screen For all types of list that will come up in Engg Menu Module **/
BaseUI {
    id: idListScreen

    HBTitleWithBackButton {
        id:idTitleWIthBackBtn
        prTitle: qsTr(cppEnggAdaptor.enggMenuScreenTitle) + cppThemeMgr.languageChanged;
    }

    /*
     * Button Group used to group radio buttons created by EnggMenuLabelWithRadioButtonDelegate
     */
    ButtonGroup {
        id: idEnggMenuRadioButtonGroup
    }

    GenericList{
        id: idGenericList

        /*
         * enggMenuCurrentListModel will be setting the model of the
         * present screen
        */

        idList.model: cppEnggAdaptor.enggMenuCurrentListModel
        idList.delegate:
            Loader{
            id:idLoader
            enabled: model.enggMenuItemEnableStatusRole
            source : getDelegate(model.enggMenuItemTypeRole)
        }
        idList.onModelChanged: {
            idList.currentIndex = -1
            prRREIndex= -1
        }
    }

    /*
     * getDelegate function will return the type of delegate needed in a list through the
     * listItemType Parameter coming from Model
    */
    function getDelegate(listItemType) {
        switch (listItemType) {
        case EnggMenuEnums.ENGG_MENU_ITEM_TYPE_LABEL:
            return "EnggMenuListDelegates/EnggMenuLabelDelegate.qml"

        case EnggMenuEnums.ENGG_MENU_ITEM_TYPE_LABEL_WITH_SLIDER:
            return "EnggMenuListDelegates/EnggMenuLabelWithSliderDelegate.qml"

        case EnggMenuEnums.ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL:
            return "EnggMenuListDelegates/EnggMenuLabelWithLabelDelegate.qml"

        case EnggMenuEnums.ENGG_MENU_ITEM_TYPE_LABEL_WITH_CHECKBOX:
            return "EnggMenuListDelegates/EnggMenuLabelWithCheckBoxDelegate.qml"

        case EnggMenuEnums.ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON:
            return "EnggMenuListDelegates/EnggMenuLabelWithRadioButtonDelegate.qml"

        case EnggMenuEnums.ENGG_MENU_ITEM_TYPE_SYS_CONFIG:
            return "EnggMenuListDelegates/EnggMenuSysConfigDelegate.qml"

        case EnggMenuEnums.ENGG_MENU_ITEM_TYPE_TRACK_NAME:
            return "EnggMenuListDelegates/EnggMenuTrackNameDelegate.qml"

        default:
            return "EnggMenuListDelegates/EnggMenuLabelDelegate.qml"
        }
    }
}

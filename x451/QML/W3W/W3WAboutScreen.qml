import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.w3wenum 1.0
import "../Common"


BaseUI
{
    id: idW3WAbout

    /**
     * This property finds out which dropdown is expanded and closed in W3W About screen.
     * So as to change the image icon and its functionality
     */
    property int prCurrentExpandedIndex: -1

    HBTitleWithBackButton
    {
        prTitle: qsTr("TEXT_W3W_ABOUT_TITLE") + cppThemeMgr.languageChanged
    }

    // Generic list object to create W3W setup list
    GenericList
    {
        id: idGenericList
        idList.model: cppW3WAdaptor.w3wAboutListModel
        idList.cacheBuffer: 1000
        idList.delegate:
            Loader{
            id:idLoader
            enabled: model.itemEnabledRole
            source : getDelegate(model.itemTypeRole)
        }
    }

    // Method to get the individual delegate to create the list from the item type passed
    function getDelegate(eItemType)
    {
        cppW3WApplication.qmlLog("getDelegate: " + eItemType)
        switch (eItemType)
        {
        case W3WEnum.ITEM_TYPE_LABEL:
            return "W3WDelegates/W3WAboutLabelDelegate.qml"
        case W3WEnum.ITEM_TYPE_LABEL_WITH_DROPDOWN:
            return "W3WDelegates/W3WAboutLabelWithDropDownDelegate.qml"
        default:
            return undefined
        }
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.setupenums 1.0
import "../Common/"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hvacenums 1.0
import com.harman.qml.popupenums 1.0
import "../Setup/Themes"
import com.harman.qml.powerenums 1.0

BaseUI {
    id: idThemeSetup

    HBTitleWithBackButton{
        prTitle: qsTr("TEXT_SETTINGS_THEMES") + cppThemeMgr.languageChanged
    }


    /* Themes option contains list of radio buttons, to achieve the radio button functionality
     * (only one should be checked at a time) ButtonGroup is used
    */
    ButtonGroup {
        id: idThemesRadioButtonGroup
    }

    // Generic list object to create bt setup list
    GenericList
    {
        id: idGenericList
        idList.model: cppSetupAdaptor.themeSetupWithDriveModeListModel
        idList.delegate:
        Loader {
            id: idLoader
            property var themeSettingsModel: model
            source: getDelegate(model.itemTypeRole)
            enabled: model.itemEnabledRole
        }
    }

    // method to get the individual delegate to create the list from the item type passed
    function getDelegate(eItemType)
    {
        switch (eItemType)
        {
        case SetupEnums.SETUP_LIST_ITEM_DROP_DOWN:
            return "qrc:/QML/Setup/ThemesWithDriveModeDelegates/ThemesToggleAndDropdownDelegate.qml"
        case SetupEnums.SETUP_LIST_ITEM_THEME_RADIO_BUTTON:
            return "qrc:/QML/Setup/ThemesWithDriveModeDelegates/ThemesRadioButtonDelegate.qml"
        default:
            return undefined
        }
    }
}

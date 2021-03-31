import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.setupenums 1.0
import com.harman.qml.powerenums 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common/"

BaseUI {
    id: idDriveNextSetup

    //To find out which dropdown is expanded
    property int prCurrentExpandedIndex: -1

    /* TitleLabel of DriveNext Setup screen */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_HOME_SHORTCUT_TITLE_DriveNext") + cppThemeMgr.languageChanged
    }

    /* Function used to find out the list item type */
    function getDelegate(itemType) {
        switch(itemType) {
        case SetupEnums.SETUP_LIST_ITEM_LABEL:
            return "qrc:/QML/Setup/DriveNext/DriveNextLabelDelegate.qml"
        case SetupEnums.SETUP_LIST_ITEM_DROP_DOWN :
        case SetupEnums.SETUP_LIST_ITEM_RADIO_BUTTON:
        case SetupEnums.SETUP_LIST_ITEM_CHECK_BOX:
        default :
            cppSetupApp.qmlLog(" Invalid list item type, itemType: " + itemType)
            return undefined
        }
    }

    /* DriveNext list is populated using GenericList and DriveNext list Model */
    GenericList {
        id: idDriveNextSetupList
        idList.model: cppSetupAdaptor.currentModel
        idList.delegate:
            Loader {
            id: idLoader
            property var driveNextSetupModel: model
            source: getDelegate(model.listItemTypeRole)
            enabled: model.isListItemEnabledRole
        }
    }
}

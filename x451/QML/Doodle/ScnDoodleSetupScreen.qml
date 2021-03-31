import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.popupenums 1.0
import com.harman.qml.doodleenums 1.0

BaseUI {
    anchors.fill: parent

    property bool prListExpanded: (cppDoodleAdaptor.doodleSetupExpandedElement !== DoodleEnums.DOODLE_SETUP_UNKNOWN)

    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Texts used to show title text for Doodle Setup Screen
     */
    HBTitleWithBackButton {
        prTitle: "*HMI Doodle"//qsTr("TEXT_DOODLE_SETUP_HEADER") + cppThemeMgr.languageChanged
    }

    /*
     * Secondary Title Text layout
     */
    Item
    {
        width: idGenericList.idList.width
        height: idGenericList.prItemHeight

        anchors {
            left: parent.left
            leftMargin: 136
            top: parent.top
            topMargin: 140
        }

        visible: !parent.prListExpanded
        Column {
            Item {
                height: idGenericList.prItemHeight - idSecTitleSeparator.height
                width: idGenericList.idList.width

                HBText {
                    anchors {
                        left: parent.left
                        leftMargin: 11
                        verticalCenter: parent.verticalCenter
                    }
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

                    text: "*Use ConnectNext to Personalize HMI Doodle"//qsTr("TEXT_DOODLE_SETUP_SUB_HEADER") + cppThemeMgr.languageChanged
                }
            }
            ListItemSeparator {
                id: idSecTitleSeparator
            }
        }
    }

    /*
     * Generic list object to create doodle setup list
     */
    GenericList
    {
        id: idGenericList

        idList.model: cppDoodleAdaptor.doodleSetupListModel
        rowShownPerPage:  parent.prListExpanded ? 4 : 3

        height: (prItemHeight * rowShownPerPage)
        anchors {
            left: parent.left
            leftMargin: 136
            top: parent.top
            topMargin: parent.prListExpanded ? 140 : (140 + prItemHeight)
        }

        idList.delegate: Loader {
            id:idLoader
            source : getDelegate(model.genericListItemTypeRole)
        }
    }

    /*
     * method to get the individual delegate to create the list from the item type passed
     */
    function getDelegate(eItemType) {
        cppPhoneApp.qmlLog("getDelegate: " + eItemType)
        switch (eItemType) {
        case DoodleEnums.DOODLE_SETUP_MY_STICKER:
        case DoodleEnums.DOODLE_SETUP_STARTUP_IMAGE:
            cppDoodleApplication.qmlLog("DoodleSetupScreen: DOODLE_SETUP_MY_STICKER: ")
            return "DoodleSetupDelegates/DoodleSetupLabelWithDropDownDelegate.qml"
        case DoodleEnums.DOODLE_SETUP_MY_STICKER_ACTIVATE:
        case DoodleEnums.DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE:
            cppDoodleApplication.qmlLog("DoodleSetupScreen: DOODLE_SETUP_MY_STICKER_ACTIVATE: ")
            return "DoodleSetupDelegates/DoodleSetupOnOffDelegate.qml"
        case DoodleEnums.DOODLE_SETUP_MY_STICKER_PREVIEW:
        case DoodleEnums.DOODLE_SETUP_STARTUP_IMAGE_PREVIEW:
        case DoodleEnums.DOODLE_SETUP_MY_STICKER_CLEAR:
        case DoodleEnums.DOODLE_SETUP_STARTUP_IMAGE_CLEAR:
            cppDoodleApplication.qmlLog("DoodleSetupScreen: DOODLE_SETUP_MY_STICKER_PREVIEW: ")
            return "DoodleSetupDelegates/DoodleSetupLabelDelegate.qml"
        default:
            cppDoodleApplication.qmlLog("DoodleSetupScreen: ????: ")
            return undefined
        }
    }
}

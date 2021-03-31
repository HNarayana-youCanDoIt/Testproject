import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.thememanager 1.0
import com.harman.qml.w3wenum 1.0
import "../Common"

BaseUI {

    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_W3W_RECENT_TITLE") + cppThemeMgr.languageChanged
    }

    /* Message for Empty favorite list */
    ColumnLayout {

        id: idEmptyListComponent
        visible: (idRecentList.idList.count === 0)
        anchors {
            top: parent.top
            topMargin: 227
            horizontalCenter: parent.horizontalCenter
        }

        /* HBText to show "No Recents Found" in this screen */
        HBText {
            anchors.horizontalCenter: parent.horizontalCenter
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T35_C3
            text: qsTr("TEXT_W3W_NO_RECENTS_FOUND") + cppThemeMgr.languageChanged
        }

        /* HBText to show "All your recently navigated addresses \nwill appear here" in this screen */
        HBText {
            anchors.horizontalCenter: parent.horizontalCenter
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
            text: qsTr("TEXT_W3W_RECENTS_DESCRIPTION") + cppThemeMgr.languageChanged
        }
    }

    // Generic list object to create W3W Favorite list
    GenericList {
        id: idRecentList
        idList.model: cppW3WAdaptor.w3wRecentListModel
        visible: (idRecentList.idList.count > 0)
        prItemHeight: 149

        idList.delegate:
            Loader{
            id:idLoader
            source : "W3WDelegates/W3WRecentDelegate.qml"
        }
    }
}

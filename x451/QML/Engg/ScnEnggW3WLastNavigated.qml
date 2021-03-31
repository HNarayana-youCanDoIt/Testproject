import QtQuick 2.7
import QtQuick.Controls 2.2
import "qrc:/QML/Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.enggMenuenums 1.0


/** QML Screen For W3W Last Navigated Address Co-ordinates **/
BaseUI {

    /**
     * Text used to show title text for W3W Last Navigated Address Engg screen
    **/
    HBTitleWithBackButton {
        prTitle: qsTr(cppEnggAdaptor.enggMenuScreenTitle) + cppThemeMgr.languageChanged
    }

    /**
     * Text Component Showing the part number values
    **/
    HBText {
        id: idLatitude

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 150
        }

        text: qsTr("TEXT_ENGG_MENU_W3W_LATITUDE") + Number(cppW3WAdaptor.lastNavigatedLatitude).toFixed(6) + cppThemeMgr.languageChanged
        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignHCenter
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
    }

    /**
     * Text Component Showing the SilverBox version number value
     * This will be visible only when user will enter in a Software part no screen.
    **/
    HBText {
        id: idLongitude

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 200
        }

        text: qsTr("TEXT_ENGG_MENU_W3W_LONGITUDE") + Number(cppW3WAdaptor.lastNavigatedLongitude).toFixed(6) + cppThemeMgr.languageChanged
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
    }
}

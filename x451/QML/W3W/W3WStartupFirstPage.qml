import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import com.harman.qml.w3wenum 1.0
import com.harman.qml.thememanager 1.0
import "../Common"


Item {

    /* Image for W3W Logo */
    Image {
        source: "qrc:/image/W3W/Gen_Gfx_wha3words logo/Gen_Gfx_wha3words-logo.png"
        anchors {
            top: parent.top
            topMargin: 33
            horizontalCenter: parent.horizontalCenter
        }
    }

    /* HBText to show "what3words" in this screen */
    HBText {

        anchors {
            top: parent.top
            topMargin: 154
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T35_C3
        verticalAlignment: Text.AlignVCenter

        text: qsTr("TEXT_HOME_SHORTCUT_TITLE_W3W") + cppThemeMgr.languageChanged
    }

    /* HBText to show description in this screen */
    HBText {

        anchors {
            top: parent.top
            topMargin: 194
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2
        horizontalAlignment: Text.AlignHCenter

        text: qsTr("TEXT_W3W_STARTUP_PAGE1_DESCRIPTION1") + cppThemeMgr.languageChanged
    }

    /* HBText to show description in this screen */
    HBText {

        anchors {
            top: parent.top
            topMargin: 280
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2
        horizontalAlignment: Text.AlignHCenter

        /* Language.csv automatically adds "" for this text (TEXT_W3W_STARTUP_PAGE1_DESCRIPTION2), so using the text directly in code */
        text: qsTr("what3words have assigned each 3m square in the world\na unique 3 word address that are easy to say, share and\nare as accurate as GPS coordinates.") + cppThemeMgr.languageChanged
    }
}

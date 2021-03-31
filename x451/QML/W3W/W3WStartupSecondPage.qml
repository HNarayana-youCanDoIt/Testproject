import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import com.harman.qml.w3wenum 1.0
import com.harman.qml.thememanager 1.0
import "../Common"


Item {

    /* HBText to show "what3words" in this screen */
    HBText {

        anchors {
            top: parent.top
            topMargin: 38
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: Text.AlignHCenter

        text: qsTr("TEXT_HOME_SHORTCUT_TITLE_W3W") + cppThemeMgr.languageChanged
    }

    /* HBText to show "///masterpiece.above.names" in this screen */
    HBText {

        anchors {
            top: parent.top
            topMargin: 110
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: Text.AlignHCenter

        text: qsTr("TEXT_W3W_3WORD_SAMPLE") + cppThemeMgr.languageChanged
    }

    /* HBText to show "Marks exact location to India Gate, Delhi" in this screen */
    HBText {

        anchors {
            top: parent.top
            topMargin: 154
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2
        horizontalAlignment: Text.AlignHCenter

        /* Language.csv automatically adds "" for this text (TEXT_W3W_3WORD_SAMPLE_LOCATION), so using the text directly in code */
        text: qsTr("Marks exact location to India Gate, Delhi") + cppThemeMgr.languageChanged
    }

    /* HBText to show "Explore and find your 3 words address here" in this screen */
    HBText {

        anchors {
            top: parent.top
            topMargin: 214
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2
        horizontalAlignment: Text.AlignHCenter

        text: qsTr("TEXT_W3W_STARTUP_PAGE2_EXPLORE")
              + cppThemeMgr.languageChanged
    }

    /* Image for W3W Barcode */
    Image {
        source: "qrc:/image/W3W/Gen_Gfx_Barcodeurl/Gen_Gfx_Barcodeurl.png"
        anchors {
            top: parent.top
            topMargin: 250
            horizontalCenter: parent.horizontalCenter
        }
    }

    /* HBText to show "https://what3words.com" in this screen */
    HBText {

        anchors {
            top: parent.top
            topMargin: 351
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2
        horizontalAlignment: Text.AlignHCenter

        text: qsTr("TEXT_W3W_URL") + cppThemeMgr.languageChanged
    }
}

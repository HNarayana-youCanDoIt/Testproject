import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0

BaseUI {
    anchors.fill: parent

    HBTitleWithBackButton{
        prTitle: qsTr(MediaAdaptor.activeMediaSrcTitle) + cppThemeMgr.languageChanged
    }

    /* Media Browse button */
    GenericButton {
        //TODO: Need to check about animation on browse button for sync state implementation
        id: idMediaMainBrowseBtn

        //Below positions correspond to positions from Tuner main screen
        anchors {

            left: parent.left
            leftMargin: 495
            top: parent.top
            topMargin: 50
        }

        width: 76
        height: 76

        defaultImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_n.png"
        pressedImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nf.png"
        disabledImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nd.png"

        enabled: true
        onReleased: {
            cppMediaApp.qmlLog("AUX - Media Browse Clicked! - Show AUX In Gain Settings")
            cppMediaApp.raiseSMEvent("Media","Browse")
        }
    }

    /*
    This layout shall display:
    ** Column:
    ** Col 1: Screen Title
    ** Col 2: Aux playing label
    ** Col 3: AUX image
    */
    ColumnLayout {
        id: idMediaAuxScreenCol
        width: parent.width

        anchors
        {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 72
        }

        /* AUX playing text */
        HBText {
            id: idMediaAuxScreenText
            text: qsTr("Playing from AUX")
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 70
            }
        }

        /* AUX Image */
        Image {
            id: idMediaAuxIcon
            source: "qrc:/image/Media/Med_Gfx_AUX/Med_Ico_AUX.png"

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 121
            }

            Layout.preferredWidth: 228
            Layout.preferredHeight: 228
        }
    }

    Connections
    {
        target: cppHardkeyAdaptor
        onSigRotaryPressed:
        {
            if((HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode) && (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
            {
                cppMediaApp.qmlLog("MediaAuxScreen.qml : right rotary pressed")
                cppMediaApp.raiseSMEvent("Media","Browse")
            }
        }
    }
}

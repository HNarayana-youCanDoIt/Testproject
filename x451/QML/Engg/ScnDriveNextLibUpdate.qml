import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.enggMenuenums 1.0

BaseUI {

    /*
     * function to start DriveNext Lib Update
    */
    function startLibUpdate() {
        cppDriveNextApplication.qmlLog("ScnDriveNextLibUpdate.qml startLibUpdate")
        cppEnggApplication.raiseSMEvent("EnggMenu", EnggMenuEnums.ENGG_MENU_ID_DRIVE_NEXT_LIB_UPDATE)
    }

    /*
     * Title text with back button
    */
    HBTitleWithBackButton {
        /**Using QProperty ,changing the title of the List Screen **/
        id: idMainTitle
        prTitle: qsTr(cppEnggAdaptor.enggMenuScreenTitle) + cppThemeMgr.languageChanged;
    }

    /*
     * Version text
    */
    HBText {
        id: idSwVersionText
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: -30
        }
        fontType: ThemeMgr.FONTTYPE_T35_C3
        text: qsTr("TEXT_ENGG_MENU_DN_LIB_VER") + ": " + cppDriveNextAdaptor.libVersion + cppThemeMgr.languageChanged
    }

    /*
     * Update Button to start Lib update
    */
    GenericButton {
        id: idUpdateBtn
        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: 30
        }
        width: 170
        height: 50
        defaultImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"
        pressedImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png"
        disabledImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"
        enabled: cppDriveNextAdaptor.driveNextPresence && (!cppDriveNextAdaptor.updatingLibFile)
        textFontType: enabled ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_BK_C2_DISABLED

        text: qsTr("TEXT_ENGG_MENU_DN_UPDATE_BUTTON") + cppThemeMgr.languageChanged

        background: Image
        {
            id: idUpdateBtnBackground

            anchors.fill: parent
            visible: (source !== "")

            source: (parent.enabled)? ((parent.pressed)? (parent.pressedImageURL): (parent.defaultImageURL)): (parent.disabledImageURL)
        }

        onReleased: {
            cppDriveNextApplication.qmlLog("ScnDriveNextLibUpdate.qml - SW update initiated via touch")
            startLibUpdate()
        }
    }

    /*
     * Busy Indicator to show Update in progress
    */
    BusyIndicator {
        scale: 0.5
        visible: cppDriveNextAdaptor.driveNextPresence && cppDriveNextAdaptor.updatingLibFile
        anchors {
            horizontalCenter: idUpdateBtn.horizontalCenter
            verticalCenter: idUpdateBtn.verticalCenter
        }
    }

    /*
     * Connection to handle button Panel
    */
    Connections {
        target: cppHardkeyAdaptor
        onSigRotaryPressed: {
            cppUIBase.qmlLog("ScnDriveNextLibUpdate.qml: onRotaryUpdate: " + iKeyState)
            if ((iKeyState === 4 || iKeyState === 3) && (idUpdateBtn.enabled)) {
                cppDriveNextApplication.qmlLog("ScnDriveNextLibUpdate.qml - Lib update initiated via rotary")
                startLibUpdate()
            }
        }
    }
}

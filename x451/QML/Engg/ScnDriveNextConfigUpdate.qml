import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.enggMenuenums 1.0

BaseUI {

    /*
     * function to start DriveNext Config Update
    */
    function startConfigUpdate() {
        cppDriveNextApplication.qmlLog("ScnDriveNextConfigUpdate.qml startConfigUpdate")
        cppEnggApplication.raiseSMEvent("EnggMenu", EnggMenuEnums.ENGG_MENU_ID_DRIVE_NEXT_CONFIG_UPDATE)
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
        text: qsTr("TEXT_ENGG_MENU_DN_CONFIG_VER") + ": " + cppDriveNextAdaptor.configVersion + cppThemeMgr.languageChanged
    }

    /*
     * Update Button to start Config update
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
        enabled: cppDriveNextAdaptor.driveNextPresence && (!cppDriveNextAdaptor.updatingConfigFile)
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
            cppDriveNextApplication.qmlLog("ScnDriveNextConfigUpdate.qml - Config update initiated via touch")
            startConfigUpdate()
        }
    }

    /*
     * Busy Indicator to show Update in progress
    */
    BusyIndicator {
        scale: 0.5
        visible: cppDriveNextAdaptor.driveNextPresence && cppDriveNextAdaptor.updatingConfigFile
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
            cppUIBase.qmlLog("ScnDriveNextConfigUpdate.qml: onRotaryUpdate: " + iKeyState)
            if ((iKeyState === 4 || iKeyState === 3) && (idUpdateBtn.enabled)) {
                cppDriveNextApplication.qmlLog("ScnDriveNextConfigUpdate.qml - Config update initiated via rotary")
                startConfigUpdate()
            }
        }
    }
}

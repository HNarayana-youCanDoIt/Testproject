import QtQuick 2.7
import QtQuick.Controls 2.2
import "qrc:/QML/Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.enggMenuenums 1.0


/** QML Screen For Part Number **/
BaseUI {
    id: idPartNumberScreen

    /**
     * Text used to show title text for Engg screen
    **/
    HBTitleWithBackButton {
        id:idTitleWithBackBtn
    }


    /**
     * Text Component Showing the part number values
    **/
    HBText {
        id: idPartNoValueText
        width: 300

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 200
        }

        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignHCenter
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

    }

    /**
     * Text Component Showing the SilverBox version number value
     * This will be visible only when user will enter in a Software part no screen.
    **/
    HBText {
        id: idSbxVersionText

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 150
        }
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        visible: false

    }

    /**
     * Text Component Showing Only the Display manager version number value.
     * This will be visible only when user will enter in a Software part no screen.
    **/

    HBText {
        id: idDmVersionText

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 250
        }

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        visible: false
    }

    Component.onCompleted: {
        switch(cppEnggAdaptor.enggMenuCurrentScreen)
        {
        case EnggMenuEnums.ENGG_MENU_SCREEN_SYSTEM_CONFIG_VIN:
            idTitleWithBackBtn.prTitle = qsTr("TEXT_ENGG_SYS_CONFIG_VIN")+ cppThemeMgr.languageChanged
            idPartNoValueText.text = cppVersionManagerAdaptor.vinInfo
            break;
        case EnggMenuEnums.ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_CONTAINER_PART:
            idTitleWithBackBtn.prTitle = qsTr("TEXT_ENGG_16R_CONTAINER_PART_NUMBER")+ cppThemeMgr.languageChanged
            idPartNoValueText.text =  cppVersionManagerAdaptor.containerPartNo
            break;
        case EnggMenuEnums.ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SILVERBOX_PART:
            idTitleWithBackBtn.prTitle = qsTr("TEXT_ENGG_16R_SILVERBOX_HW_PART_NUMBER")+ cppThemeMgr.languageChanged
            idPartNoValueText.text =  cppVersionManagerAdaptor.silverBoxPartNo
            break;
        case EnggMenuEnums.ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_DISPLAY_PART:
            idTitleWithBackBtn.prTitle = qsTr("TEXT_ENGG_16R_DISPLAY_HW_PART_NUMBER")+ cppThemeMgr.languageChanged
            idPartNoValueText.text =  cppVersionManagerAdaptor.displayHWPartNo
            break;
        case EnggMenuEnums.ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_PARAM_PART:
            idTitleWithBackBtn.prTitle = qsTr("TEXT_ENGG_16R_PARAMETERIZATION_PART_NUMBER")+ cppThemeMgr.languageChanged
            idPartNoValueText.text =  cppVersionManagerAdaptor.parameterizationPartNo
            break;
        case EnggMenuEnums.ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_BUTTON_PANEL:
            idTitleWithBackBtn.prTitle = qsTr("TEXT_ENGG_16R_BUTTON_PANNEL_HW_PART_NUMBER")+ cppThemeMgr.languageChanged
            idPartNoValueText.text = cppVersionManagerAdaptor.buttonPanelPartNo
            break;
        case EnggMenuEnums.ENGG_MENU_SCREEN_SYSTEM_CONFIG_VC_NUMBER:
            idTitleWithBackBtn.prTitle = qsTr("TEXT_ENGG_SYS_CONFIG_VC_NUMBER")+ cppThemeMgr.languageChanged
            idPartNoValueText.text = cppVersionManagerAdaptor.vcInfo
            break;
        case EnggMenuEnums.ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SOFT_PART:
            idTitleWithBackBtn.prTitle = qsTr("TEXT_ENGG_16R_SOFTWARE_PART_NUMBER")+ cppThemeMgr.languageChanged
            idSbxVersionText.visible = true
            idDmVersionText.visible = true
            idPartNoValueText.text = qsTr("TEXT_ENGG_TEST_MODE_SW_PART_NUMBER_LABEL_BP") + ": " + cppVersionManagerAdaptor.btnPanelSoftVersionNo
            idSbxVersionText.text  = qsTr("TEXT_ENGG_TEST_MODE_SW_PART_NUMBER_LABEL_SBX") + ": " + cppVersionManagerAdaptor.socSoftVersionNo
            idDmVersionText.text   = qsTr("TEXT_ENGG_TEST_MODE_SW_PART_NUMBER_LABEL_DM") + ": " + cppVersionManagerAdaptor.displayManagerSoftVersionNo
            break;
        default:
            cppEnggApplication.qmlLog("Invalid Screen, cppEnggAdaptor.enggMenuCurrentScreen :: " + cppEnggAdaptor.enggMenuCurrentScreen);
            break;
        }
    }
}

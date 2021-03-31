import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.drawersenums 1.0
import com.harman.qml.variantcontrolenums 1.0
import com.harman.qml.powerenums 1.0

Item {
    id: idMuteStatusContainer

    /*
     * Preset Setting button to go to preset Settings screen.
     */
    HBButtonWithIconAndText {
        id: idMuteUnmuteButton
        width: ((VariantControlEnum.VIP_DID_HU_HIGH_X451 === cppVariantControlAdaptor.eolVIP_DID)
                || (VariantControlEnum.VIP_DID_HU_HIGH_X445 === cppVariantControlAdaptor.eolVIP_DID)
                || (VariantControlEnum.VIP_DID_HU_NEXON_EV_HIGH === cppVariantControlAdaptor.eolVIP_DID)
                || (VariantControlEnum.VIP_DID_HU_NEXON_MCE === cppVariantControlAdaptor.eolVIP_DID)) ? 162 : 320
        height: parent.height

        anchors.verticalCenter: parent.verticalCenter

        prDefaultIconImage: cppAudioAdaptor.muteActive ? "qrc:/image/Drawers/QAD/Maximized/Contents/MuteUnmuteIcons/Gen_Drawer_Ico_UnMute_n-assets/Gen_Drawer_Ico_UnMute_na.png" : "qrc:/image/Drawers/QAD/Maximized/Contents/MuteUnmuteIcons/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Mute_na.png"
        prPressedIconImage: cppAudioAdaptor.muteActive ? "qrc:/image/Drawers/QAD/Maximized/Contents/MuteUnmuteIcons/Gen_Drawer_Ico_UnMute_n-assets/Gen_Drawer_Ico_UnMute_nf.png" : "qrc:/image/Drawers/QAD/Maximized/Contents/MuteUnmuteIcons/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Mute_nf.png"
        prDisabledIconImage: cppAudioAdaptor.muteActive ? "qrc:/image/Drawers/QAD/Maximized/Contents/MuteUnmuteIcons/Gen_Drawer_Ico_UnMute_n-assets/Gen_Drawer_Ico_UnMute_nd.png" : "qrc:/image/Drawers/QAD/Maximized/Contents/MuteUnmuteIcons/Drw_Ico_Mute_7in_n-assets/Gen_Drawer_Ico_Mute_nd.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 90
        prTextLeftMargin: 0

        prText: cppAudioAdaptor.muteActive ? qsTr("TEXT_PHONE_LABEL_UNMUTE") + cppThemeMgr.languageChanged : qsTr("TEXT_PHONE_LABEL_MUTE") + cppThemeMgr.languageChanged
        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
        prTextVerticalCenter: prIconVerticalCenter

        prIsEnabled: (PowerModeEnums.VPM_MEDIA_OFF !== cppPowerModeAdaptor.powerMode)

        button.onReleased: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: Mute/Unmute button released.")
            cppAudioAdaptor.toggleMute(true)
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * vertical Seprator line to seprate Mute/Unmute info and SettingsPresetButton
     */
    Image {
        id: idSettingsPresetVerticalSepratorLine

        // Show separator for all variant except X104VaVe
        visible: ((VariantControlEnum.VIP_DID_HU_HIGH_X451 === cppVariantControlAdaptor.eolVIP_DID)
	          || (VariantControlEnum.VIP_DID_HU_HIGH_X445 === cppVariantControlAdaptor.eolVIP_DID)
                  || (VariantControlEnum.VIP_DID_HU_NEXON_EV_HIGH === cppVariantControlAdaptor.eolVIP_DID)
                  || (VariantControlEnum.VIP_DID_HU_NEXON_MCE === cppVariantControlAdaptor.eolVIP_DID))

        anchors {
            left: parent.left
            leftMargin: 161
            verticalCenter: parent.verticalCenter
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LineSeparator2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
    }

    /*
     * Preset Setting button to go to preset Settings screen.
     * Open Settings Presets
     */
    HBButtonWithIconAndText {
        id: idSettingsPresetButton

        width: 150
        height: parent.height

        enabled: !cppPhoneAdaptor.doesCallExist

        // Show settings preset button for all variant except X104VaVe
        visible: ((VariantControlEnum.VIP_DID_HU_HIGH_X451 === cppVariantControlAdaptor.eolVIP_DID)
	          || (VariantControlEnum.VIP_DID_HU_HIGH_X445 === cppVariantControlAdaptor.eolVIP_DID)
                  || (VariantControlEnum.VIP_DID_HU_NEXON_EV_HIGH === cppVariantControlAdaptor.eolVIP_DID)
                  || (VariantControlEnum.VIP_DID_HU_NEXON_MCE === cppVariantControlAdaptor.eolVIP_DID))

        anchors {
            left: parent.left
            leftMargin: 170
            verticalCenter: parent.verticalCenter
        }

        prDefaultIconImage: cppSetupAdaptor.activeThemePresetIcon + "a.png"
        prPressedIconImage: cppSetupAdaptor.activeThemePresetIcon + "p.png"
        prDisabledIconImage: cppSetupAdaptor.activeThemePresetIcon + "d.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 100
        prTextLeftMargin: 0
        prText: cppSetupAdaptor.activeThemePresetText
        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
        prTextVerticalCenter: prIconVerticalCenter

        button.onReleased: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: idSettingsPreset button released.")
            maxDrawerClicked()
            cppSetupAdaptor.launchThemeSettings()
        }
    }

    /*
     * vertical Seprator line to seprate SettingsPresetButton and settings button
     */
    Image {
        id: idSettingsButtonVerticalSepratorLine

        anchors {
            left: parent.left
            leftMargin: 325//291
            verticalCenter: parent.verticalCenter
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LineSeparator2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
    }

    /*
     * Settings button to go to settings screen.
     */
    HBButtonWithIconAndText {
        id: idSettingsButton

        width: 134
        height: parent.height

        enabled: !cppPhoneAdaptor.doesCallExist

        anchors {
            left: parent.left
            leftMargin: 330
            verticalCenter: parent.verticalCenter
        }

        prDefaultIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_Settings2_7in_n-assets/Gen_Drawer_Ico_Settings_na.png"
        prPressedIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_Settings2_7in_n-assets/Gen_Drawer_Ico_Settings_nf.png"
        prDisabledIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_Settings2_7in_n-assets/Gen_Drawer_Ico_Settings_nd.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 90
        prTextLeftMargin: 0
        prText: qsTr("TEXT_QAD_SETTINGS") + cppThemeMgr.languageChanged
        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
        prTextVerticalCenter: prIconVerticalCenter

        button.onReleased: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: idSettingsButton button released.")
            maxDrawerClicked()
            cppDrawersApp.raiseSMEvent(
                        "QadDrawer", DrawersEnums.QAD_DRAWER_SETTINGS_BUTTON_ID)
        }
    }

    /*
     * Seprator line to seprate items in QuickAccess Drawer
     */
    Image {
        id: idMuteSepratorLine

        anchors {
            left: parent.left
            bottom: parent.bottom
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LeftLineSeparator_7in_n-assets/Drw_Gfx_LeftLineSeparator_n.png"
    }
}

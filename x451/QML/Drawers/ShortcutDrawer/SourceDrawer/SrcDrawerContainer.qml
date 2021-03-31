import QtQuick 2.7
import QtQuick.Layouts 1.3
import com.harman.qml.thememanager 1.0
import com.harman.qml.audioenums 1.0
import "../../../Common"
import com.harman.qml.popupenums 1.0

Item {
    id: idSourceDrawerContainerItem

    // FM Source Button with text
    HBButtonWithIconAndText {
        id: idFMButton

        width: 151 //76 + 75
        height: 110

        anchors{
            left: parent.left
            leftMargin: 192
        }

        enabled: cppAudioAdaptor.fmSrcStatus

        prDefaultIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/FMIcons/Gen_Drawer_Ico_Radio_na.png"
        prPressedIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/FMIcons/Gen_Drawer_Ico_Radio_nf.png"
        prDisabledIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/FMIcons/Gen_Drawer_Ico_Radio_nd.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 75
        prTextHeight: 16
        prTextLeftMargin: 0

        prText: qsTr("TEXT_TUNER_TITLE_FM") + cppThemeMgr.languageChanged
        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED

        prTextVerticalCenter: prIconVerticalCenter

        button.onReleased: {
            maxDrawerClicked()
            cppAudioAdaptor.setActiveEntSrc(AudioEnums.SRC_TUNER_FM)
        }
    }

    // AM Source Button with text
    HBButtonWithIconAndText {
        id: idAMButton

        width: 151 //76 + 75
        height: 110

       anchors{
            left: parent.left
            leftMargin: 392
        }

        enabled: cppAudioAdaptor.amSrcStatus

        prDefaultIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/FMIcons/Gen_Drawer_Ico_Radio_na.png"
        prPressedIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/FMIcons/Gen_Drawer_Ico_Radio_nf.png"
        prDisabledIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/FMIcons/Gen_Drawer_Ico_Radio_nd.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 75
        prTextHeight: 16
        prTextLeftMargin: 0

        prText: qsTr("TEXT_TUNER_TITLE_AM") + cppThemeMgr.languageChanged
        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED

        prTextVerticalCenter: prIconVerticalCenter

        button.onReleased: {
            maxDrawerClicked()
            cppAudioAdaptor.setActiveEntSrc(AudioEnums.SRC_TUNER_AM)
        }
    }
/*
 * DRM is not supported so commented out the DRM
 */
    // DRM Source Button with text
//    HBButtonWithIconAndText {
//        id: idDRMButton

//        width: 151 //76 (icons width) + 75 (text width)
//        height: 76

//        anchors{
//            left: parent.left
//            /*
//             * In assets the X is given from window's left, and we use the Drawer's
//             * Maximize images X, So subtracting 98, which is the Maximize image X.
//             */
//            leftMargin: 511 //628 - 98
//        }

//        /*
//         * FixMe: This depends on DRM source status, Which is not
//         * available yet.
//         */
//        enabled: false

//        prDefaultIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/FMIcons/Gen_Drawer_Ico_Radio_na.png"
//        prPressedIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/FMIcons/Gen_Drawer_Ico_Radio_nf.png"
//        prDisabledIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/FMIcons/Gen_Drawer_Ico_Radio_nd.png"

//        isIconOnLeft: true

//        prIconLeftMargin: 0
//        prIconTopMargin: 0

//        prTextWidth: 75
//        prTextHeight: 16
//        prTextLeftMargin: 0

//        prText: qsTr("TEXT_TUNER_TITLE_DRM") + cppThemeMgr.languageChanged
//        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
//          prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED

//        prTextVerticalCenter: prIconVerticalCenter

//        button.onReleased: {
//            maxDrawerClicked()
//            cppAudioAdaptor.setActiveEntSrc(AudioEnums.SRC_TUNER_DRM)
//        }
//    }

    // USB Source Button with text
    HBButtonWithIconAndText {
        id: idUSBButton

        width: 151 //76 (icons width) + 75 (text width)
        height: 110

        anchors{
            left: parent.left
            leftMargin: 192
            top: parent.top
            topMargin: 141
        }

        enabled: cppAudioAdaptor.usbSrcStatus

        prDefaultIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/USBIcons/Gen_Drawer_Ico_USB_na.png"
        prPressedIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/USBIcons/Gen_Drawer_Ico_USB_nf.png"
        prDisabledIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/USBIcons/Gen_Drawer_Ico_USB_nd.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 75
        prTextHeight: 16
        prTextLeftMargin: 0

        prText: qsTr("TEXT_HOME_SHORTCUT_TITLE_USB") + cppThemeMgr.languageChanged
        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED

        prTextVerticalCenter: prIconVerticalCenter

        button.onReleased: {
            maxDrawerClicked()
            cppAudioAdaptor.setActiveEntSrc(AudioEnums.SRC_USB1)
        }
    }

    // BtAudio Source Button with text
    HBButtonWithIconAndText {
        id: idBtAudioButton

        width: 151 //76 (icons width) + 75 (text width)
        height: 110

        anchors{
            left: parent.left
            leftMargin: 392
            top: parent.top
            topMargin: 141
        }

        enabled: cppAudioAdaptor.btSrcStatus

        prDefaultIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/BTAudioIcons/Drw_Ico_BTAudio_na.png"
        prPressedIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/BTAudioIcons/Drw_Ico_BTAudio_nf.png"
        prDisabledIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/BTAudioIcons/Drw_Ico_BTAudio_nd.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 100
        prTextHeight: 16
        prTextLeftMargin: 0

        prText: qsTr("TEXT_HOME_SHORTCUT_TITLE_Bluetooth_Audio") + cppThemeMgr.languageChanged
        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED

        prTextVerticalCenter: prIconVerticalCenter

        button.onReleased: {
            maxDrawerClicked()
            cppAudioAdaptor.setActiveEntSrc(AudioEnums.SRC_BT_A2DP1)
        }
    }

    // AUX Source Button with text
    HBButtonWithIconAndText {
        id: idAUXButton

        width: 168 //76 (icons width) + 92 (text width)
        height: 110

        anchors{
            left: parent.left
            leftMargin: 392
            top: parent.top
            topMargin: 282
        }

        visible: ((AudioEnums.AUX_CONNECTED === cppAudioAdaptor.auxConnectionStatus)
                  || (AudioEnums.AUX_ALREADY_CONNECTED === cppAudioAdaptor.auxConnectionStatus))

        enabled: cppAudioAdaptor.auxSrcStatus

        prDefaultIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/AUXIcons/Gen_Drawer_Ico_AUX_na.png"
        prPressedIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/AUXIcons/Gen_Drawer_Ico_AUX_nf.png"
        prDisabledIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/AUXIcons/Gen_Drawer_Ico_AUX_nd.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 75
        prTextHeight: 16
        prTextLeftMargin: 0

        prText: qsTr("TEXT_SOURCE_DRAWER_TITLE_AUX") + cppThemeMgr.languageChanged
        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED

        prTextVerticalCenter: prIconVerticalCenter

        button.onReleased: {
            maxDrawerClicked()
            cppAudioAdaptor.setActiveEntSrc(AudioEnums.SRC_AUDIO_AUX)
        }
    }

    // IPOD Source Button with text
    HBButtonWithIconAndText {
        id: idIPODButton

        width: 151 //76 (icons width) + 75 (text width)
        height: 110

        anchors{
            left: parent.left
            leftMargin: 192
            top: parent.top
            topMargin: 282
        }

        enabled: cppAudioAdaptor.ipodSrcStatus

        prDefaultIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/IPODIcons/Gen_Drawer_Ico_iPOD_na.png"
        prPressedIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/IPODIcons/Gen_Drawer_Ico_iPOD_nf.png"
        prDisabledIconImage: "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/IPODIcons/Gen_Drawer_Ico_iPOD_nd.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 75
        prTextHeight: 16
        prTextLeftMargin: 0

        prText: qsTr("TEXT_HOME_SHORTCUT_TITLE_Ipod") + cppThemeMgr.languageChanged

        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED

        prTextVerticalCenter: prIconVerticalCenter

        button.onReleased: {
            maxDrawerClicked()
            cppAudioAdaptor.setActiveEntSrc(AudioEnums.SRC_IPOD)
        }
    }
}

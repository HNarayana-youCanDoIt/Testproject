import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.setupenums 1.0
import "../../Common/"
import com.harman.qml.thememanager 1.0

Item {
    id: idSoundSettingsItem
    height: 152
    width: 488
    enabled: true

    /* This Image background image of the drop down */
    BorderImage {
        source: "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Gfx_ListSeparator_PatchClimate_n.png"
        anchors.fill: parent
    }

    /*
      * Item contains notification volume text and volume slider
      */
    Item{
        id:idNotificationVolItem

        width: 420
        height: 46

        anchors{
            left: parent.left
            leftMargin: 0
            top: parent.top
            topMargin: 10
        }

        /*
             * Text Field to show the Notification volume label.
             */
        HBText{
            id:idNotificationVolText
            width: 250
            fontType: ThemeMgr.FONTTYPE_T35_C3
            elide: Text.ElideRight
            text: qsTr("TEXT_THEME_NOTIFICATION_VOLUME") + cppThemeMgr.languageChanged
            anchors{
                left: parent.left
                leftMargin: 10
                top: parent.top
                topMargin: 5
            }
        }

        /*
             * Notification volume Icon
             */
        Image {
            id: idNotificationVolIcon
            anchors{
                left: idNotificationVolText.right
                leftMargin: 5
                top: parent.top
                topMargin: -5
            }
            source: "qrc:/image/Themes/Set_Ico_sSound_7in_n-assets/Set_Ico_NotificationVolume_n.png"
        }

        /*
         * Horizontal Slider to show  notification volume
         */
        HorizontalSlider{
            id:idNotificationVolSlider

            width: 120
            height: 40

            prSliderButtonsHeight:0
            prSliderButtonsWidth:0

            anchors{
                left: idNotificationVolIcon.right
                leftMargin: -5
                verticalCenter: idNotificationVolIcon.verticalCenter
            }

            prMinVal: 0
            prMaxVal: 30

            enabled: (SetupEnums.THEME_PRESET_USER === cppSetupAdaptor.presetSelection)

            slider.value: cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].notificationVolume

            slider.anchors{
                left: parent.left
                leftMargin: 0
                rightMargin: 0
            }

            prArrowPrevNormalImage: ""
            prArrowPrevPressedImage: ""
            prArrowPrevDisabledImage: ""
            prArrowNextNormalImage: ""
            prArrowNextPressedImage: ""
            prArrowNextDisabledImage: ""

            prProgressFillVisibility: true
            prHandleDefaultImage: "qrc:/image/AudioPresets/Set_Btn_Circle_7in_n-assets/Gen_Drawer_Button_circle_nf.png"
            prHandlePressedImage: "qrc:/image/AudioPresets/Set_Btn_Circle_7in_n-assets/Gen_Drawer_Button_circle_nf.png"
            prHandleDisabledImage: "qrc:/image/AudioPresets/Set_Btn_Circle_7in_n-assets/Gen_Drawer_Button_circle_n.png"

            sliderImage.source: "qrc:/image/Themes/Set_Ico_sSound_7in_n-assets/Drawer_Gfx_BrightnessSlider_nd.png"


            slider.onPressedChanged: {
                if (!slider.pressed)
                {
                    cppSetupApp.qmlLog("ThemesSoundElement.qml: slider.onPressedChanged." + Math.round(slider.value))
                    cppSetupAdaptor.editModeFlag = true
                    cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].setNotificationVolume(Math.round(slider.value))
                }
                else
                {
                    //Do nothing
                }
            }

            slider.onPositionChanged: {
                cppSetupApp.qmlLog("ThemesSoundElement.qml: slider.onPositionChanged." + Math.round(slider.value))
                cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].setNotificationVolume(Math.round(slider.value))
            }

            slider.onValueChanged: {
                cppSetupApp.qmlLog("ThemesSoundElement.qml: slider.onValueChanged. " + Math.round(slider.value))
                cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].setNotificationVolume(Math.round(slider.value))
            }
        }

        /**
         * text, value of slider on changed
         */
        HBText {
            id: idSliderValueText
            fontType: (enabled) ? ThemeMgr.FONTTYPE_T35_BK_C2 : ThemeMgr.FONTTYPE_T35_BK_C2_DISABLED
            text:  (cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].notificationVolume < 10)
                                                  ? "0" + cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].notificationVolume
                                                  : cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].notificationVolume
            anchors{
                left: idNotificationVolSlider.right
                leftMargin: 10
                verticalCenter: idNotificationVolIcon.verticalCenter
            }
        }
    }


    /*
      * Item contains Audio Presets
      */
    Item {
        id:idAudioPresetsItem
        width: 420
        height: 46

        anchors{
            left: parent.left
            leftMargin: 20
            top: parent.top
            topMargin: 85
        }

        /*
          * text which holds the audio presets label
          */
        HBText{
            id:idAudioPresetsText
            width: 200
            fontType: ThemeMgr.FONTTYPE_T35_C3
            elide: Text.ElideRight
            text: qsTr("TEXT_AUDIO_SETTINGS_AUDIO_PRESETS") + cppThemeMgr.languageChanged
            anchors{
                left: parent.left
                leftMargin: -5
                top: parent.top
                topMargin: 5
            }
        }

        Item {
            id:idPresetsRow
            width: 200
            height: 60

            anchors{
                left: idAudioPresetsText.right
                leftMargin: 65
                top:parent.top
                topMargin: 0
            }

            /* This image is used for the background image of the presets row*/
            BorderImage {
                source: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png"
                anchors.fill: parent
            }


            /*
                 * Button to change the previous Audio preset.
                 */
            GenericButton {
                id: idAudioPresetPrevButton

                width: 70
                height: 70

                anchors {
                    left: parent.left
                    leftMargin: -15
                    verticalCenter: parent.verticalCenter
                }

                enabled: ((SetupEnums.THEME_PRESET_USER === cppSetupAdaptor.presetSelection) && (cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].audioPreset > 0))
                defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_n.png"
                pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nf.png"
                disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowPrev_7in_n-assets/Gen_Drawer_Button_ArrowPreview_nd.png"

                onReleased: {
                    cppSetupApp.qmlLog("ThemesSoundElement.qml: idAudioPresetPrevButton released." )
                    cppSetupAdaptor.editModeFlag = true
                    cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].audioPreset = cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].audioPreset - 1
                }
            }

            /*
              * text, which holds the audio preset name
              */
            HBText{
                id:idAudioPreset

                width: 150
                fontType: ThemeMgr.FONTTYPE_T35_BK_C2
                elide: Text.ElideRight
                text : (cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].invGetThemeAudioPresetText(cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].audioPreset))
                anchors{
                    left: parent.left
                    leftMargin: 25
                    top: parent.top
                    topMargin: 5
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            /*
                 * Button to change the next Audio preset.
                 */
            GenericButton {
                id: idAudioPresetNextButton

                width: 70
                height: 70

                anchors{
                    left: parent.left
                    leftMargin: 145
                    verticalCenter: parent.verticalCenter
                }

                enabled: ((SetupEnums.THEME_PRESET_USER === cppSetupAdaptor.presetSelection) && (cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].audioPreset < 6))

                defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_n.png"
                pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nf.png"
                disabledImageURL: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Gen_Ico_ArrowNext_7in_n-assets/Gen_Drawer_Button_ArrowNext_nd.png"


                onReleased: {
                    cppSetupApp.qmlLog("ThemesSoundElement.qml: idAudioPresetNextButton released." )
                    cppSetupAdaptor.editModeFlag = true
                    cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].audioPreset = cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].audioPreset + 1
                }
            }
        }
    }
}

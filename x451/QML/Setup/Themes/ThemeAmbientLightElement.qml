import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import com.harman.qml.setupenums 1.0
import "../../Common/"
import com.harman.qml.thememanager 1.0

Item {

    id: idAmbientLightSettingsItem
    height: 152
    width: 488

    property bool isUserInitiated: false

    /* This image is used for the background image of the drop down*/
    BorderImage {
        source: "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Gfx_ListSeparator_PatchClimate_n.png"
        anchors.fill: parent
    }

    /*
    * HU Brightness control slider.
    */
    HorizontalSlider {
        id: idAmbientLightSlider

        width: 360
        height: 46

        anchors {
            left: parent.left
            leftMargin: 70
            top: parent.top
            topMargin: 50
        }

        prSliderLeftMargin: 0
        prSliderNextBtnLeftMargin: 0
        prSliderPrevBtnLeftMargin: 0

        prMinVal: 1
        prMaxVal: 5

        enabled: (SetupEnums.THEME_PRESET_USER === cppSetupAdaptor.presetSelection)

        slider.value: cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].themeAmbLightIlluLevel

        sliderImage.source:
            "qrc:/image/Drawers/QAD/Maximized/Contents/BrightnesSliderImages/Drw_Gfx_BrightnessSlider_7in_n-assets/Drawer_Gfx_BrightnessSlider_nd.png"

        prProgressFillVisibility: true

        slider.onPressedChanged: {
            if (!slider.pressed)
            {
                cppSetupApp.qmlLog(
                            "ThemeAmbientLightElement.qml: Brightness slider onPressedChanged, slider Value: " + Math.round(
                                slider.value))
                cppSetupAdaptor.editModeFlag = true
                cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].setThemeAmbLightIlluLevel(Math.round(slider.value))
                isUserInitiated = false
            }
            else
            {
                isUserInitiated = false
            }
        }

        slider.onPositionChanged: {
            cppSetupApp.qmlLog(
                        "ThemeAmbientLightElement.qml: Brightness slider onPositionChanged, slider Value: " + Math.round(
                            slider.value))
            if(isUserInitiated)
            {
                cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].setThemeAmbLightIlluLevel(Math.round(slider.value))
            }
            else
            {
                //Do nothing.
            }
        }

        slider.onValueChanged: {
            cppSetupApp.qmlLog(
                        "ThemeAmbientLightElement.qml: Brightness slider onValueChanged, slider Value: " + Math.round(
                            slider.value))
        }

        /* This signal gets emitted on slider buttons click and we are making API call from here */
        onSigSliderBtnClicked: {
            cppSetupApp.qmlLog(
                        "ThemeAmbientLightElement.qml: Brightness slider onSigSliderBtnClicked, slider Value: " + Math.round(
                              slider.value) + stepSize)
            cppSetupAdaptor.editModeFlag = true
            cppSetupAdaptor.themeElementsList[idThemePresetsTabView.prCurrIndex].setThemeAmbLightIlluLevel(Math.round(slider.value + stepSize))
        }
    }
}

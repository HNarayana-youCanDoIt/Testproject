import QtQuick 2.7
import QtQuick.Controls 2.2
import "qrc:/QML/Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.enggMenuenums 1.0


/*
 *Common QML Screen For Illumination
 * This Screen will be used for both type of Illumination i.e Display as well as Button Panel Illumination
 */
BaseUI {
    id: idIlluminationScreen
    anchors.fill: parent

    /** Text Component Showing the title of the page at the top **/
    HBTitleWithBackButton{
        id:idTitleWithBackBtn
        prTitle: qsTr(cppEnggAdaptor.enggMenuScreenTitle) + cppThemeMgr.languageChanged;
    }

    /** Text Component Showing the current value of Illumination **/
    HBText {
        id: idIlluminationValueText

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 150
        }
        visible: idHorizontalSlider.visible
        text: Math.round(idHorizontalSlider.slider.value)

    }

    /** Generic Slider Customized with the requirement **/
    HorizontalSlider {
        id: idHorizontalSlider
        //[Todo: Height and Width will be changed once requirement is provided.]
        width: 450
        height: 96

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 200
        }

        prMinVal: 20
        prMaxVal: 100

        prSliderLeftMargin: 0
        prSliderNextBtnLeftMargin: 0
        prSliderPrevBtnLeftMargin: 0

        visible: ((EnggMenuEnums.ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION ===  cppEnggAdaptor.enggMenuCurrentScreen) ||
                  (EnggMenuEnums.ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION ===  cppEnggAdaptor.enggMenuCurrentScreen))

        slider.value:(EnggMenuEnums.ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION ===  cppEnggAdaptor.enggMenuCurrentScreen)
                     ?cppDisplayManagerAdaptor.brightNessLevel
                     : ((EnggMenuEnums.ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION ===  cppEnggAdaptor.enggMenuCurrentScreen)
                        ? cppDisplayManagerAdaptor.buttonPanelBrightnessLevel : 0)

        sliderImage.source: "qrc:/image/EnggMenu/Gen_Gfx_SliderLine_n/Gen_Gfx_SliderLine_nd.png"

        prProgressFillVisibility: true

        slider.onPressedChanged:
        {
            if (!slider.pressed)
            {
                if(EnggMenuEnums.ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION ===  cppEnggAdaptor.enggMenuCurrentScreen)
                {
                    cppDisplayManagerAdaptor.reqDisplayBrightnessLevel((Math.round(slider.value)), true)
                }
                else if (EnggMenuEnums.ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION ===  cppEnggAdaptor.enggMenuCurrentScreen)
                {
                    cppDisplayManagerAdaptor.reqButtonPanelBrightnessLevel((Math.round(slider.value)), true)
                }
            }
            else
            {
                //Do nothing.
            }
        }

        slider.onPositionChanged: {

            cppEnggApplication.qmlLog("ScnEnggIllumination.qml: Brightness slider onPositionChanged, slider Value: "
                                      + Math.round(slider.value))

            if(EnggMenuEnums.ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION ===  cppEnggAdaptor.enggMenuCurrentScreen)
                cppDisplayManagerAdaptor.reqDisplayBrightnessLevel((Math.round(slider.value)), false)
            else if (EnggMenuEnums.ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION ===  cppEnggAdaptor.enggMenuCurrentScreen)
                cppDisplayManagerAdaptor.reqButtonPanelBrightnessLevel((Math.round(slider.value)), false)

        }

        slider.onValueChanged: {
            cppEnggApplication.qmlLog("ScnEnggIllumination.qml: Brightness slider value changed, slider Value: "
                                      + Math.round(slider.value))
        }

        /* This signal gets emitted on slider buttons click and we are making API call from here */
        onSigSliderBtnClicked: {
            cppEnggApplication.qmlLog(
                        "ScnEnggIllumination.qml: - Slider Button Clicked, SliderValue: "
                        + (Math.round(slider.value) + stepSize))

            if(cppEnggAdaptor.enggMenuCurrentScreen === EnggMenuEnums.ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION)
                slider.value = (Math.round(slider.value) + stepSize)
            else if(cppEnggAdaptor.enggMenuCurrentScreen === EnggMenuEnums.ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION)
                slider.value = (Math.round(slider.value) + stepSize)
        }

    }
}

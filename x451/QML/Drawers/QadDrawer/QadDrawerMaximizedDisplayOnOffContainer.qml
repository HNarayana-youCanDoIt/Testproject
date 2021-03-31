import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.popupenums 1.0

Item {
    id: idDisplayOnOFFContainer

    /*
     * This property is used to check that the
     * brightness level is updated by user or
     * not. because we have to call service api
     * only if user changes the brightness, at
     * the time of component load the slider position also gets changed.
     * No need to call service api that time.
     */
    property bool isUserInitiated: false

    /*
     * Display ON/OFF button. When the display is OFF tap on display active
     * Area to turn on Display. This will not affect the state of display timer
     * state.
     */
    GenericButton {
        id: idDisplayOnOffButton

        width: 160
        height: parent.height

        enabled: !cppPhoneAdaptor.doesCallExist

        anchors {
            verticalCenter: parent.verticalCenter
        }

        contentItem: Item {

            anchors.fill: parent

            /*
             * Display ON/OFF icon.
             */
            Image {
                id: idDisplayOnOFFIcon

                anchors{
                    verticalCenter: parent.verticalCenter
                }
                source: (enabled
                         ? (idDisplayOnOffButton.pressed
                            ? "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_Display_7in_n-assets/Gen_Drawer_Ico_Display_nf.png"
                            : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_Display_7in_n-assets/Gen_Drawer_Ico_Display_n.png")
                         : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_Display_7in_n-assets/Gen_Drawer_Ico_Display_nd.png")
            }

            Image{
                id: idDisplayOnOffToggleButton

                anchors
                {
                    left: idDisplayOnOFFIcon.right
                    verticalCenter: idDisplayOnOFFIcon.verticalCenter
                }

                source: (enabled
                         ? (idDisplayOnOffButton.pressed
                            ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_Off_np.png"
                            : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_Off_na.png")
                         : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Btn_On_7in_n-assets/Drw_Btn_Off_nd.png")
            }

        }

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadDrawerDisplayOnOffContainer.qml: idDisplayOnOffButton button released.")

            if (!cppDisplayManagerAdaptor.displayOnOffFeatureStatus)
                PopupManager.showPopup(PopupEnum.EN_POPUPID_DISPLAY_OFF_CONFIRMATION)

            resetMaxDrawerCloseTimer()

        }
    }

    /*
     * vertical Seprator line to seprate display Off part and brightness slider.
     */
    Image {
        id: idDisplayOnOFFVerticalSepratorLine

        anchors {
            left: parent.left
            leftMargin: 170
            verticalCenter: parent.verticalCenter
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LineSeparator2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
    }

    /*
     * HU Brightness control slider.
     */
    HorizontalSlider {
        id: idBrightnessSlider

        width: 360
        height: parent.height

        enabled: ( !cppDisplayManagerAdaptor.nightModeStatus )

        anchors {
            left: parent.left
            leftMargin: 184
            verticalCenter: parent.verticalCenter
        }

        prMinVal: 20
        prMaxVal: 100

        slider.value: (cppDisplayManagerAdaptor.nightModeStatus ? 0 : cppDisplayManagerAdaptor.brightNessLevel)

        prSliderLeftMargin: 0
        prSliderNextBtnLeftMargin: 0
        prSliderPrevBtnLeftMargin: 0

        sliderImage.source: "qrc:/image/Drawers/QAD/Maximized/Contents/BrightnesSliderImages/Drw_Gfx_BrightnessSlider_7in_n-assets/Drawer_Gfx_BrightnessSlider_nd.png"

        prProgressFillVisibility: true

        slider.onPressedChanged: {
            if (!slider.pressed)
            {
                cppDisplayManagerAdaptor.reqDisplayBrightnessLevel((Math.round(slider.value)), true)
                isUserInitiated = false
            }
            else
            {
                isUserInitiated = true
            }
        }

        slider.onPositionChanged: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedDisplayOnOffContainer.qml: Brightness slider onPositionChanged, slider Value: " + Math.round(
                            slider.value))
            if (isUserInitiated)
            {
                cppDisplayManagerAdaptor.reqDisplayBrightnessLevel((Math.round(slider.value)), false)
                resetMaxDrawerCloseTimer()
            }
            else
            {
                //Do nothing.
            }
        }

        slider.onValueChanged: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedDisplayOnOffContainer.qml: Brightness slider value changed, slider Value: " + Math.round(
                            slider.value))
        }

        /* This signal gets emitted on slider buttons click and we are making API call from here */
        onSigSliderBtnClicked: {
            cppUIBase.qmlLog(
                        "QadDrawerMaximizedDisplayOnOffContainer.qml: - Slider Button Clicked, SliderValue: "
                        + (Math.round(slider.value) + stepSize))
            cppDisplayManagerAdaptor.reqDisplayBrightnessLevel((Math.round(slider.value + stepSize)), true)
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * vertical Seprator line to seprate display Off part and brightness slider.
     */
    Image {
        id: idBrightnesVerticalSepratorLine

        anchors {
            left: parent.left
            leftMargin: 554
            verticalCenter: parent.verticalCenter
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LineSeparator2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
    }

    /*
     * Parking Lamp Image.
     */
    Image {
        id: idParkingLampImage
        height: parent.height

        visible: cppDisplayManagerAdaptor.nightModeStatus

        anchors {
            left: parent.left
            leftMargin: 568
            verticalCenter: parent.verticalCenter
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_Highbeam_7in_n-assets/Gen_Drawer_Ico_HighBeam_n.png"
    }

    /*
     * Seprator line to seprate items in QuickAccess Drawer
     */
    Image {
        id: idDisplaySepratorLine

        anchors {
            left: parent.left
            bottom: parent.bottom
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LeftLineSeparator_7in_n-assets/Drw_Gfx_LeftLineSeparator_n.png"
    }
}

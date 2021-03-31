/* This component contains a volume slider with customized background and handle. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import com.harman.qml.thememanager 1.0
import QtGraphicalEffects 1.0

Item {

    id: idSliderComponent

    height: idFillImage.height
    width: idFillImage.width

    /* Alias for Volume Slider */
    property alias prVolumeSlider: idSlider

    /* Alias for minimum value of slider */
    property alias prMinVal: idSlider.from

    /* Alias for maximum value of slider */
    property alias prMaxVal: idSlider.to

    /* Alias for stepsize: on click of next/prev btn of slider, how many steps of slider value to be increased/decreased to be provided */
    property alias prSliderStepSize: idSlider.stepSize

    /* Property for Slider's Deafult handle's image */
    property string prHandleDefaultImage:       "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_Volume_slider_n/Gen_Drawer_Ico_Volume_slider_n.png"

    /* Property for Slider's presed handle's image */
    property string prHandlePressedImage:       "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_Volume_slider_n/Gen_Drawer_Ico_Volume_slider_np.png"

    /* Property for Slider's Disabled handle's image */
    property string prHandleDisabledImage:      "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_Volume_slider_n/Gen_Drawer_Ico_Volume_slider_nd.png"

    /* Property for Slider Background image */
    property string prSliderBackgroundImage:    "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Gfx_VolumeLarge_Overlay_n/Gen_Gfx_VolumeLarge_Overlay_n.png"

    /* Property for Slider Fill image */
    property string prSliderFillImage:          "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Gfx_VolumeLarge_Overlay_n/Gen_Gfx_VolumeLarge_Overlay_na.png"

    /* Property for Slider Indicator image */
    property string prSliderIndicatorImage:     "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Gfx_Scrollindicator_7in_n/Gen_Gfx_Scrollindicator_7in_n.png"

    /**
    * slider, Volume slider
    */
    Slider {
        id: idSlider

        width: parent.width
        height: parent.height

        anchors.horizontalCenter: parent.horizontalCenter

        orientation: Qt.Vertical

        from: 0
        to: 30
        stepSize: 1.0
        topPadding: 0
        bottomPadding :0

        //// Removing default handle and background
        background: Item {}
        handle:Item {}

        /**
        * Background image for slider
        */
        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            source: prSliderBackgroundImage
        }

        /**
        * filler image for slider
        */
        Image {
            id: idFillImage
            anchors.horizontalCenter: parent.horizontalCenter
            smooth: true
            visible: false
            source: prSliderFillImage
        }

        /**
        * filler mask for slider
        */
        Item {
            id: idFillerMask
            anchors.fill: idFillImage

            Rectangle {
                width: parent.width
                color: "white"
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    top: parent.top
                    topMargin: (1-idSlider.position) * idFillImage.height
                    bottom: parent.bottom
                    bottomMargin: 0
                }
            }
            smooth: true
            visible: false
        }

        /**
        * filler mask flow
        */
        OpacityMask {
            anchors.fill: idFillImage
            source: idFillImage
            maskSource: idFillerMask
        }

        /**
        * handle for slider
        */
        Item {
            width: 60
            height: 60

            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: idFillImage.bottom
                bottomMargin: idSlider.position * idFillImage.height - height/2
            }

            /**
             * Handler knob icon, volume slider
             */
            Image {

                anchors {
                    centerIn: parent
                }
                source : (idSlider.enabled ? (idSlider.pressed ? prHandlePressedImage : prHandleDefaultImage) : prHandleDisabledImage)

                /**
                 * value text background, Handler knob icon volume slider
                 */
                Image {
                    anchors {
                        left: parent.left
                        leftMargin: 50
                        verticalCenter: parent.verticalCenter
                    }
                    source : prSliderIndicatorImage

                    /**
                     * value text, Handler knob icon volume slider
                     */
                    HBText {
                        anchors {
                            horizontalCenter: parent.horizontalCenter
                            horizontalCenterOffset: 4
                            verticalCenter: parent.verticalCenter
                            verticalCenterOffset: -3
                        }
                        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
                        text: Math.round(idSlider.value)
                    }
                }
            }
        }
    }
}

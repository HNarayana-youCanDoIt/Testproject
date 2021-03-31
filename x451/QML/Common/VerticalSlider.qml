/* This component contains a vertical slider with customized background and handle. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import com.harman.qml.thememanager 1.0

Item {

    id: idSliderComponent
    height: 170
    width: 3

    /* name of the slider */
    property alias prSliderName: idSliderNameText.text

    /* alias name of vertical slider*/
    property alias prVerticalslider: idVerticalSlider

    /* slider value on changed*/
    property alias prSliderValue: idSliderValueText.text

    /* Starting value for slider */
    property int prMinVal: 0

    /* End value for slider */
    property int prMaxVal: 30

    /* Stepsize: on click of next/prev btn of slider, how many steps of slider value to be increased/decreased to be provided */
    property int prSliderStepSize: 1.0

    /* Property for Slider's Deafult handle's image */
    property string prHandleDefaultImage: "qrc:/image/AudioPresets/vertical_slider/Gen_Drawer_Button_circle_n.png"

    /* Property for Slider's presed handle's image */
    property string prHandlePressedImage: "qrc:/image/AudioPresets/vertical_slider/Gen_Drawer_Button_circle_nf.png"

    /* Property for Slider's Disabled handle's image */
    property string prHandleDisabledImage: "qrc:/image/AudioPresets/vertical_slider/Gen_Drawer_Button_circle_nd.png"

    /**
     * column, to arrange the items of slider in column
     */
    Column {
        spacing: 10
        /**
         * text, value of slider on changed
         */
        HBText {
            id: idSliderValueText
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
            text: Math.round(idVerticalSlider.value)
            anchors.horizontalCenter: parent.horizontalCenter
        }

        /**
         * slider, vertical slider to change BMT values
         */
        Slider {
            id: idVerticalSlider

            height: idBgImage.height
            width: 70

            from: prMinVal
            to: prMaxVal

            stepSize: prSliderStepSize

            anchors.horizontalCenter: parent.horizontalCenter

            orientation: Qt.Vertical

            topPadding: 0
            bottomPadding :0

            /**
             * background static image of slider
             */
            background: Image {
                id: idBgImage

                anchors.horizontalCenter: parent.horizontalCenter
                source: "qrc:/image/AudioPresets/vertical_slider/Drawer_Gfx_BrightnessSlider_nd.png"
            }

            /**
             * fill image of slider, on movement of handle the height of the image is getting changed.
             * here height of image is getting varied as per the slider movement which we are calculating with slider visual position and height.
             */
            Item{
                width: idBgImage.width
                height: idVerticalSlider.position * idBgImage.height

                anchors{
                    bottom: idBgImage.bottom
                    left: idBgImage.left
                }
                clip: true

                z : 0
                Image {
                    id: idFillImage
                    source: "qrc:/image/AudioPresets/vertical_slider/Drawer_Gfx_BrightnessSlider_n.png"
                }

            }

            /**
             * background handle of slider, to drag and change the value
             */
            handle:Item {
                id: idSliderHandleItem

                width: idVerticalSlider.width
                height: 18

                /* here Z is set as 1 to make the handle on top of the fill image*/
                z: 1
                anchors{
                    horizontalCenter: parent.horizontalCenter
                    top: idBgImage.top
                    topMargin: (idVerticalSlider.topPadding + ((idVerticalSlider.visualPosition
                                 * (idVerticalSlider.availableHeight - height))))
                }
                Image {
                    id: idSliderhandle
                    anchors.centerIn: idSliderHandleItem
                    source : (idVerticalSlider.enabled ? (idVerticalSlider.pressed ? prHandlePressedImage : prHandleDefaultImage) : prHandleDisabledImage)
                }
            }
        }

        /**
         * text of the slider
         */
        HBText {
            id: idSliderNameText
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}

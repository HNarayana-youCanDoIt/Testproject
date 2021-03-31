/* This component contains a horizontal slider with next & previous buttons. */
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {
    id: idSliderComponent
    width: 347  //FixMe: Need to be changed
    height: 41  //FixMe: Need to be changed

    /* Starting value for slider */
    property int prMinVal         : 0

    /* End value for slider */
    property int prMaxVal         : 30

    /* Stepsize: on click of next/prev btn of slider, how many steps of slider value to be increased/decreased to be provided */
    property int prSliderStepSize : 1

    /* Slider next button left margin to be provided here */
    property int prSliderNextBtnLeftMargin   : 18

    /* Slider prev button left margin to be provided here */
    property int prSliderPrevBtnLeftMargin    : 18

    /* Slider's Left Margin. */
    property int prSliderLeftMargin: 18

    /* Slider buttons height to be provided here */
    property int prSliderButtonsHeight        : 76

    /* Slider buttons width to be provided here */
    property int prSliderButtonsWidth         : 76

    /* slider previous button default image */
    property string prArrowPrevNormalImage    :  "qrc:/image/Drw_Btn_Brightness_7in_n-assets/Gen_Drawer_Btn_Brightness_n.png"

    /* slider previous button clicked image */
    property string prArrowPrevPressedImage   :  "qrc:/image/Drw_Btn_Brightness_7in_n-assets/Gen_Drawer_Btn_Brightness_nf.png"

    /* slider previous button disabled image, when max/min val is reached the corresponding btn should be disabled */
    property string prArrowPrevDisabledImage  :  "qrc:/image/Drw_Btn_Brightness_7in_n-assets/Gen_Drawer_Btn_Brightness_nd.png"

    /* slider next button default image */
    property string prArrowNextNormalImage    :  "qrc:/image/Drw_Btn_Brightness2_7in_n-assets/Gen_Drawer_Brightness_n.png"

    /* slider next button clicked image */
    property string prArrowNextPressedImage   :  "qrc:/image/Drw_Btn_Brightness2_7in_n-assets/Gen_Drawer_Brightness_nf.png"

    /* slider next button disabled image, when max/min val is reached the corresponding btn should be disabled */
    property string prArrowNextDisabledImage  :  "qrc:/image/Drw_Btn_Brightness2_7in_n-assets/Gen_Drawer_Brightness_nd.png"

    /* This signal gets emitted with stepsize value on SliderNextBtn click & -stepsize value on SliderPrevBtn click */
    signal sigSliderBtnClicked(int stepSize)

    property alias sliderPrevBtn : idSliderPrevBtn
    property alias sliderNextBtn : idSliderNextBtn
    property alias slider        : idSlider
    property alias sliderImage   : idSliderImage

    /* Property for Progress Fiil Image Item Visibility */
    property bool  prProgressFillVisibility: false

    /* Property for Slider's Deafult handle's image */
    property string prHandleDefaultImage: "qrc:/image/Drawers/QAD/Maximized/Contents/BrightnesSliderImages/Drw_Btn_Circle_7in_n-assets/Drw_Btn_Circle_n.png"

    /* Property for Slider's presed handle's image */
    property string prHandlePressedImage: "qrc:/image/Drawers/QAD/Maximized/Contents/BrightnesSliderImages/Drw_Btn_Circle_7in_n-assets/Drw_Btn_Circle_nf.png"

    /* Property for Slider's Disabled handle's image */
    property string prHandleDisabledImage: "qrc:/image/Drawers/QAD/Maximized/Contents/BrightnesSliderImages/Drw_Btn_Circle_7in_n-assets/Drw_Btn_Circle_nd.png"

    /* Property for progress bar fill item */
    property alias prProgressFillItem: idProgressFillItem

    /* Previous button of slider */
    ListGenericButton {
        id : idSliderPrevBtn
        width: prSliderButtonsWidth
        height: prSliderButtonsHeight
        anchors {
            left: parent.left
            leftMargin: prSliderPrevBtnLeftMargin
            verticalCenter: parent.verticalCenter
        }
        defaultImageURL     :   prArrowPrevNormalImage
        pressedImageURL     :   prArrowPrevPressedImage
        disabledImageURL    :   prArrowPrevDisabledImage

        onReleased: {
            sigSliderBtnClicked(-prSliderStepSize)
        }
        onPressAndHoldContinue: {
            sigSliderBtnClicked(-prSliderStepSize)
        }
        enabled: (Math.round(idSlider.value) > prMinVal)
    }

    /* Next button of slider */
    ListGenericButton {
        id : idSliderNextBtn

        width: prSliderButtonsWidth
        height: prSliderButtonsHeight

        anchors {
            left: idSlider.right
            leftMargin: prSliderNextBtnLeftMargin
            verticalCenter: parent.verticalCenter
        }

        defaultImageURL     :   prArrowNextNormalImage
        pressedImageURL     :   prArrowNextPressedImage
        disabledImageURL    :   prArrowNextDisabledImage

        onReleased: {
            sigSliderBtnClicked(prSliderStepSize)
        }
        onPressAndHoldContinue: {
            sigSliderBtnClicked(prSliderStepSize)
        }
        enabled: (Math.round(idSlider.value) < prMaxVal)
    }

    /* Slider control, which provides basic slider functionality to be customized accordingly */
    Slider {
        id: idSlider

        from    : prMinVal
        to      : prMaxVal

        stepSize: prSliderStepSize

        leftPadding: 0
        rightPadding: 0

        height: 70
        width: idSliderImage.width

        anchors {
            left: idSliderPrevBtn.right
            leftMargin: prSliderLeftMargin
            verticalCenter: parent.verticalCenter
        }

        background: Image {
            id : idSliderImage
            anchors{
                verticalCenter: idSlider.verticalCenter
                horizontalCenter: idSlider.horizontalCenter
            }
        }

        /**
         * Fill Progress image of slider, on movement of handle the Width of the image is changed.
         */
        Item{
            id: idProgressFillItem

            height: idSliderImage.height
            width: (idSlider.visualPosition * idSliderImage.width)

            anchors{
                left: idSliderImage.left
                verticalCenter: idSlider.verticalCenter
            }

            z: 0

            visible: prProgressFillVisibility

            clip: true

            Rectangle {
                id: idProgressItem

                anchors.fill: parent

                ColorOverlay {
                    id: idPgbColorOverlay
                    anchors.fill: parent
                    source: parent
                    color:  (enabled ? "white" : "#363636")
                }
            }
        }

        /* Handle of slider */
        handle: Item{
            id: idSliderHandleItem

            implicitHeight: idSliderHandle.height
            implicitWidth: 15

            anchors{
                left: idSliderImage.left
                leftMargin: idSlider.leftPadding + idSlider.visualPosition * (idSlider.availableWidth - width)
                verticalCenter: idSliderImage.verticalCenter
            }

            z: 1

            Image {
                id: idSliderHandle

                anchors.centerIn: idSliderHandleItem

                source: (idSlider.enabled ? (idSlider.pressed ? prHandlePressedImage : prHandleDefaultImage) : prHandleDisabledImage)
            }
        }
    }
}

/* EXAMPLE: Creating custom handle
idSlider.handle: Text {
    id: idPopupText
    text: Math.round(idHorizontalSlider.idSlider.value)
    color: "White"
    font.pixelSize: 20
    x: idHorizontalSlider.idSlider.leftPadding + idHorizontalSlider.idSlider.visualPosition * (idHorizontalSlider.idSlider.availableWidth - width)
    y: idHorizontalSlider.idSlider.topPadding + idHorizontalSlider.idSlider.availableHeight / 2 - height / 2
}
*/

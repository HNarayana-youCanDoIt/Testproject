import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"

/** Delegate of Button List Item with Label and Slider  **/
Item {
    id: idBtnListLabelWithSliderDelegate

    width: idGenericList.idList.width
    height: idGenericList.prItemHeight

    /** Delegate of Button List Item with Label and Slider  **/
    Column {
        LabelWithSlider {
            id: idLabelWithSliderComp

            height: (idGenericList.prItemHeight - idSeparator.height)
            width: idGenericList.idList.width

            /* Values for the properties of horizontalslider, next, previous buttons and customLabel is given here */
            customLabel.text: enggMenuItemMainTextRole
            prHorizontalSliderLeftMargin: 272

            horizontalSlider.slider.value: 0
            horizontalSlider.prMinVal: -10
            horizontalSlider.prMaxVal: 10

            horizontalSlider.slider.width: 250 //FixMe: height and width will be changed when assets will be available .
            horizontalSlider.slider.height: 25

            horizontalSlider.sliderImage.source: "qrc:/image/Climate_Gfx_SliderTemp2_n/Climate_Gfx_SliderTemp2_n.png"

            horizontalSlider.prArrowPrevNormalImage: "qrc:/image/Gen_Ico_ArrowPrev2/01_Gen_Ico_ArrowPrev2_n.png"//FixMe: All images to be
            horizontalSlider.prArrowPrevPressedImage: "qrc:/image/Gen_Ico_ArrowPrev2/02_Gen_Ico_ArrowPrev2_np.png"//replaced with new assets
            horizontalSlider.prArrowPrevDisabledImage: "qrc:/image/Gen_Ico_ArrowPrev2/04_Gen_Ico_ArrowPrev2_nd.png"

            horizontalSlider.prArrowNextNormalImage: "qrc:/image/Gen_Ico_ArrowNext2/01_Gen_Ico_ArrowNext2_n.png"
            horizontalSlider.prArrowNextPressedImage: "qrc:/image/Gen_Ico_ArrowNext2/02_Gen_Ico_ArrowNext2_np.png"
            horizontalSlider.prArrowNextDisabledImage: "qrc:/image/Gen_Ico_ArrowNext2/04_Gen_Ico_ArrowNext2_nd.png"

            /**
             * On value change of slider this signal gets emitted, in this we are making API call.
             * The logic here used is we send a request and mark the flag isResponseReceived as false,
             * once we receive the response mark the flag isResponseReceived as true and continues...
             */

            horizontalSlider.slider.onValueChanged: {
                //Adaptor Function call
                idPopupText.text = Math.round(horizontalSlider.slider.value)
            }

            /* Slider handle logic, text is used here as handle */
            horizontalSlider.slider.handle: Text {
                id: idPopupText

                //[Todo:] Will be implemented later. for default value, slider value is assigned i.e 0.
                text: idLabelWithSliderComp.horizontalSlider.slider.value
                color: "white"
                font.pixelSize: 26

                x:( idLabelWithSliderComp.horizontalSlider.slider.leftPadding
                   + (idLabelWithSliderComp.horizontalSlider.slider.visualPosition
                      * (idLabelWithSliderComp.horizontalSlider.slider.availableWidth - width)))
            }

            horizontalSlider.onSigSliderBtnClicked: {
                horizontalSlider.slider.value += stepSize
            }
        }

        ListItemSeparator {
            id:idSeparator
        }
    }
}

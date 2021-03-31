import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.setupenums 1.0
import com.harman.qml.parkassistenum 1.0
import "../../Common/"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0

    /* This component contains label along with a HorizontalSlider and a listItemSeparator image */
Item {

    id: idLabelWithSliderDelegate
    width: idParkAssistList.width
    height: idParkAssistList.prItemHeight

    Column {
        IconLabelWithSlider {

            id: idLabelWithSliderComp
            height               : idParkAssistList.prItemHeight - idSeparator.height
            width                : idParkAssistList.idList.width

            horizontalSlider.sliderPrevBtn.width: 80
            horizontalSlider.sliderPrevBtn.height: 80
            horizontalSlider.sliderNextBtn.width: 80
            horizontalSlider.sliderNextBtn.height: 80

            horizontalSlider.width: 290
            horizontalSlider.height: 40
//            customLabel.width: 190

            prHorizontalSliderLeftMargin: 226
            prContextualImageSrc: parkAssistModel.listItemDefaultImageRole

            prHorizontalSliderTopMargin: 18

            /* Values for the properties of horizontalslider, next, previous buttons and customLabel is given here */
            customLabel.text                          : parkAssistModel.listItemNameRole
            horizontalSlider.slider.value             : parkAssistModel.listItemValueRole
            horizontalSlider.prMinVal                 : parkAssistModel.listItemMinValueRole
            horizontalSlider.prMaxVal                 : parkAssistModel.listItemMaxValueRole
            horizontalSlider.slider.width             : 50
            horizontalSlider.slider.height            : 40
            horizontalSlider.prArrowPrevNormalImage   : "qrc:/image/AudioPresets/Gen_Ico_ArrowPrev_n/Gen_Ico_ArrowPrev_n.png"   //FixMe: All images to be
            horizontalSlider.prArrowPrevPressedImage  : "qrc:/image/AudioPresets/Gen_Ico_ArrowPrev_n/Gen_Ico_ArrowPrev_nf.png"  //replaced with new assets
            horizontalSlider.prArrowPrevDisabledImage : "qrc:/image/AudioPresets/Gen_Ico_ArrowPrev_n/Gen_Ico_ArrowPrev_nd.png"
            horizontalSlider.prArrowNextNormalImage   : "qrc:/image/AudioPresets/Gen_Ico_ArrowNext_n/Gen_Ico_ArrowNext_n.png"
            horizontalSlider.prArrowNextPressedImage  : "qrc:/image/AudioPresets/Gen_Ico_ArrowNext_n/Gen_Ico_ArrowNext_nf.png"
            horizontalSlider.prArrowNextDisabledImage : "qrc:/image/AudioPresets/Gen_Ico_ArrowNext_n/Gen_Ico_ArrowNext_nd.png"
            horizontalSlider.sliderImage.source       : ""

            /* This signal gets emitted on slider buttons click and we are making API call from here */
            horizontalSlider.onSigSliderBtnClicked: {
                cppSetupApp.qmlLog("onSigSliderBtnClicked - API Call, SliderValue: " + (Math.round(horizontalSlider.slider.value) + stepSize) + " Index: " + parkAssistModel.index)
                cppAudioAdaptor.invParkAssistVolume((Math.round(horizontalSlider.slider.value + stepSize)))
            }

            /* Slider handle logic, text is used here as handle */
            horizontalSlider.slider.handle:HBText {
                id: idSliderText
                text: cppAudioAdaptor.convertIntValueFormat(Math.round(idLabelWithSliderComp.horizontalSlider.slider.value))
                font.pixelSize: (enabled) ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED
                anchors.horizontalCenter: parent.horizontalCenter
                x: idLabelWithSliderComp.horizontalSlider.slider.leftPadding + idLabelWithSliderComp.horizontalSlider.slider.visualPosition * (idLabelWithSliderComp.horizontalSlider.slider.availableWidth - width)
                MouseArea{
                    onPositionChanged: mouse.accepted = false
                }
            }


            /* Slider background, image is used here to remove mouse area on slider image */
            horizontalSlider.slider.background: Image{
                MouseArea{
                    anchors.fill: parent
                    onPositionChanged: mouse.accepted = false
                }
            }
        }
        ListItemSeparator {
            id:idSeparator
        }
    }
}

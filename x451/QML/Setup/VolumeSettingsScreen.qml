import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import com.harman.qml.setupenums 1.0
import com.harman.qml.hardkeyenum 1.0
import "../Common/"

BaseUI {
    id:idVolumeSettings

    /* TitleLabel of Setup screen */
    HBTitleWithBackButton {
        prTitle: qsTr("TEXT_SETTINGS_VOLUME_SETUP") + cppThemeMgr.languageChanged
    }

    /** Delegate of Button List Item with Label and CheckBox  **/
    Component {
        id: idBtnListLabelWithCheckBoxDelegate
        Column {
            LabelWithCheckBoxComp {
                id: idLabelWithCheckboxComp
                height: ((idVolumeSetupList.prItemHeight) - (idSeperator.height))
                width: idVolumeSetupList.idList.width
                prCheckBoxRightMargin: 10
                text: setupModel.listItemNameRole
                prCheckBoxChecked: setupModel.listItemCheckedRole

                onReleased:
                {
                    cppAudioAdaptor.setSpeedDependantVolumeAttribute(!prCheckBoxChecked)
                }
            }

            //Handling RRE HK for selecting or deselecting speed dependant volume
            Connections
            {
                target: cppHardkeyAdaptor
                onSigRotaryPressed:
                {
                    cppPhoneApp.qmlLog("VolumeSettingsScreen.qml: onRotaryUpdate: key state is: " + iKeyState)
                    if(iKeyState === HardkeyEnum.HKEY_STATE_RELEASED || iKeyState === HardkeyEnum.HKEY_STATE_LONGRELEASED)
                    {
                        if(idVolumeSetupList.idList.currentIndex === setupModel.index)
                        {
                            cppPhoneApp.qmlLog("VolumeSettingsScreen.qml - HBButtonListItem RRE release/longReleae event, itemIndex is: " + setupModel.index)
                            cppAudioAdaptor.setSpeedDependantVolumeAttribute(!idLabelWithCheckboxComp.prCheckBoxChecked)
                        }
                    }
                }
            }

            //FixMe: Need to give proper list item separator image as per x451
            ListItemSeparator {
                id:idSeperator
            }
        }
    }

    /* Volume settings screen delegate, this component contains label and a listItemSeparator image */
    Component {
        id: idBtnListLabelwithSliderDelegate
        Column {
            LabelWithSlider {
                id: idLabelWithSliderComp
                height               : ((idVolumeSetupList.prItemHeight) - (idSeperator.height))
                width                : idVolumeSetupList.idList.width

                horizontalSlider.sliderPrevBtn.width: 80
                horizontalSlider.sliderPrevBtn.height: 80
                horizontalSlider.sliderNextBtn.width: 80
                horizontalSlider.sliderNextBtn.height: 80

                horizontalSlider.width: 200
                horizontalSlider.height: 40

                prHorizontalSliderLeftMargin: 216

                prHorizontalSliderTopMargin: 18

                /* Values for the properties of horizontalslider, next, previous buttons and customLabel is given here */
                customLabel.text                          : setupModel.listItemNameRole
                horizontalSlider.slider.value             : setupModel.listItemValueRole
                horizontalSlider.prMinVal                 : setupModel.listItemMinValue  //FixMe: Check if get API available for min & max val
                horizontalSlider.prMaxVal                 : setupModel.listItemMaxValue
                horizontalSlider.slider.width             : 50  //FixMe: Move this to base widget after proper asset is received
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
                    cppAudioAdaptor.setVolumeSettingsValues((Math.round(horizontalSlider.slider.value + stepSize)), setupModel.index)
                }

                /* Slider handle logic, text is used here as handle */
                horizontalSlider.slider.handle: HBText {
                    id: idPopupText
                    text: cppAudioAdaptor.convertIntValueFormat(Math.round(idLabelWithSliderComp.horizontalSlider.slider.value))
                    font.pixelSize: (enabled) ? ThemeMgr.FONTTYPE_T35_C3 : ThemeMgr.FONTTYPE_T35_C3_DISABLED
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
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

            //FixMe: Need to give proper list item separator image as per x451
            ListItemSeparator {
                id:idSeperator
            }
        }
    }

    Component{
        id:idBtnListIconLabelWithSliderDelegate

        Column{
            IconLabelWithSlider{
                id:idIconLabelWithSlider

                height               : ((idVolumeSetupList.prItemHeight) - (idSeperator.height))
                width                : idVolumeSetupList.idList.width

                horizontalSlider.sliderPrevBtn.width: 80
                horizontalSlider.sliderPrevBtn.height: 80
                horizontalSlider.sliderNextBtn.width: 80
                horizontalSlider.sliderNextBtn.height: 80

                horizontalSlider.width: 290
                horizontalSlider.height: 40

                prHorizontalSliderLeftMargin: 226
                prContextualImageSrc: setupModel.listItemDefaultImageRole

                prHorizontalSliderTopMargin: 18

                /* Values for the properties of horizontalslider, next, previous buttons and customLabel is given here */
                customLabel.text                          : setupModel.listItemNameRole
                horizontalSlider.slider.value             : setupModel.listItemValueRole
                horizontalSlider.prMinVal                 : setupModel.listItemMinValue  //FixMe: Check if get API available for min & max val
                horizontalSlider.prMaxVal                 : setupModel.listItemMaxValue
                horizontalSlider.slider.width             : 50  //FixMe: Move this to base widget after proper asset is received
                horizontalSlider.slider.height            : 40
                horizontalSlider.prArrowPrevNormalImage   : "qrc:/image/AudioPresets/Gen_Ico_ArrowPrev_n/Gen_Ico_ArrowPrev_n.png"
                horizontalSlider.prArrowPrevPressedImage  : "qrc:/image/AudioPresets/Gen_Ico_ArrowPrev_n/Gen_Ico_ArrowPrev_nf.png"
                horizontalSlider.prArrowPrevDisabledImage : "qrc:/image/AudioPresets/Gen_Ico_ArrowPrev_n/Gen_Ico_ArrowPrev_nd.png"
                horizontalSlider.prArrowNextNormalImage   : "qrc:/image/AudioPresets/Gen_Ico_ArrowNext_n/Gen_Ico_ArrowNext_n.png"
                horizontalSlider.prArrowNextPressedImage  : "qrc:/image/AudioPresets/Gen_Ico_ArrowNext_n/Gen_Ico_ArrowNext_nf.png"
                horizontalSlider.prArrowNextDisabledImage : "qrc:/image/AudioPresets/Gen_Ico_ArrowNext_n/Gen_Ico_ArrowNext_nd.png"
                horizontalSlider.sliderImage.source       : ""

                /* This signal gets emitted on slider buttons click and we are making API call from here */
                horizontalSlider.onSigSliderBtnClicked: {
                    cppAudioAdaptor.setVolumeSettingsValues((Math.round(horizontalSlider.slider.value + stepSize)), setupModel.index)
                }

                /* Slider handle logic, text is used here as handle */
                horizontalSlider.slider.handle: HBText {
                    id: idPopupText
                    text: cppAudioAdaptor.convertIntValueFormat(Math.round(idIconLabelWithSlider.horizontalSlider.slider.value))
                    font.pixelSize: ThemeMgr.FONTTYPE_T35_C3
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    x: idIconLabelWithSlider.horizontalSlider.slider.leftPadding + idIconLabelWithSlider.horizontalSlider.slider.visualPosition * (idIconLabelWithSlider.horizontalSlider.slider.availableWidth - width)
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
                id:idSeperator
            }
        }
    }

    /* Setup main list is populated using GenericList and SetupMainModel */
    GenericList {
        id: idVolumeSetupList
        idList.model: cppSetupAdaptor.currentModel
        idList.delegate:Loader {
            id: idLoader
            property var setupModel: model
            sourceComponent: getDelegate(setupModel.listItemTypeRole)
        }
        idList.onModelChanged: {
            idList.currentIndex = -1
        }
    }

    /** getDelegate function will return the type of delegate needed in a list through the
                listItemType Parameter coming from Model  **/
    function getDelegate(ListItemTypeRole) {
        switch (ListItemTypeRole) {
        case SetupEnums.SETUP_LIST_ITEM_CHECK_BOX:
            return idBtnListLabelWithCheckBoxDelegate
        case SetupEnums.SETUP_LIST_ITEM_SLIDER:
            return idBtnListLabelwithSliderDelegate
        case SetupEnums.SETUP_LIST_ITEM_ICON_SLIDER:
            return idBtnListIconLabelWithSliderDelegate
        default:
            return idBtnListLabelwithSliderDelegate
        }
    }
}

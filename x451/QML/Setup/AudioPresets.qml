import QtQuick 2.7
import QtQuick.Controls.Styles 1.4
import com.harman.qml.setupenums 1.0
import com.harman.qml.thememanager 1.0
import QtQuick.Layouts 1.3
import "../Common/"
import com.harman.qml.popupenums 1.0
import com.harman.qml.audioenums 1.0
import com.harman.qml.hardkeyenum 1.0

BaseUI {
    id: idAudioPresets

    //bassSliderValue - Holds current bass value from service
    property int prBassSliderValue: cppAudioAdaptor.bass

    //midSliderValue - Holds current mid value from service
    property int prMidSliderValue: cppAudioAdaptor.mid

    //trebleSliderValue - Holds current treble value from service
    property int prTrebleSliderValue: cppAudioAdaptor.treble

    //prIsResponseReceived - this preoperty will set true on response recieved from services
    property bool prIsResponseReceived: true

    //prIsPresetUserConfigured - this propery will set true active audio preset is same as configured audio preset
    property bool prIsPresetUserConfigured: (cppAudioAdaptor.activeAudioPreset === cppAudioAdaptor.configuredAudioPreset)

    Connections {
        target: cppAudioAdaptor
        onSigBassChanged: {
            prIsResponseReceived = true
        }
        onSigMidChanged:{
            prIsResponseReceived = true
        }
        onSigTrebleChanged:{
            prIsResponseReceived = true
        }
    }

    /**
     * idAudiopresetandBMTItem, this will have presets and BMT items
     */
    Item {
        id: idAudiopresetandBMTItem
        height: 275
        width: 380

        anchors{
            left: parent.left
            leftMargin: 150
            top: parent.top
            topMargin: 108
        }

        /**
         * idAudioPresetsColumn, column to align the list of presets
         */

        RowLayout {
            id: idAudioPresetsRow
            anchors {
                leftMargin: 10
                top: parent.top
                topMargin: 30
            }

            spacing: 3

            Item {
                id: idPresetsListItem

                anchors{
                    top:parent.top
                    topMargin: 10
                    left: parent.left
                    leftMargin: 50
                }

                /**
                 * idDelegate, This is delagate of the Audio Presets list
                 */
                Component{
                    id: idDelegate
                    Column {
                        ListGenericButton {
                            id: idAudioPresetsListComp
                            width: idAudioPresetList.idList.width
                            height: 50
                            pressedImageURL: "qrc:/image/AudioPresets/AudioPresetsPopupBackground/Gen_Gfx_PopListCursor_7in_n.png"

                            contentItem: HBText {
                                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
                                anchors.centerIn: parent.Center
                                text: listItemNameRole
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }

                            /** here the setConfiguredAudioPreset called to set the current preset as selected
                             * which will highlight the selected preset and call the service method to set preset.
                             */
                            onReleased: {
                                cppSetupApp.qmlLog("AudioPresetsListPopup.qml - index: " + index)
                                cppAudioAdaptor.setConfiguredAudioPreset(index)
                                cppSetupApp.qmlLog("AudioPresets.qml - API Call, index: "+ index + listItemNameRole)
                                cppAudioAdaptor.setAudioPresetAttribute(index)
                            }
                        }

                        Connections {
                            target: cppHardkeyAdaptor
                            onSigRotaryPressed: {
                                cppSetupApp.qmlLog("AudioPresets: onRotaryUpdate: "+iKeyState)
                                if((HardkeyEnum.HKEY_STATE_RELEASED === iKeyState ||
                                    HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
                                {
                                    if(idAudioPresetList.idList.currentIndex === index)
                                    {
                                        idAudioPresetsListComp.released()
                                    }
                                }
                            }
                        }

                        /**
                         * idListItemSepratorImg : Image source of the list item separator
                         */
                        Image {
                            id: idListItemSepratorImg
                            source: "qrc:/image/AudioPresets/AudioPresetsPopupBackground/Set_Gfx_AudioPresetPopSep_7in_n.png"
                            width: 90
                            height: 1
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }

                /**
                  * Text for displaying active Audio Presets
                  **/
                HBText {
                    id: idActiveAudioPresetText

                    width: idAudioPresetList.idList.width
                    height: 50

                    anchors{
                        top: parent.top
                        topMargin: (idAudioPresetList.anchors.topMargin - 57)
                        horizontalCenter: idAudioPresetList.horizontalCenter
                    }

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    text: cppAudioAdaptor.activeAudioPresetName
                    fontType: ThemeMgr.FONTTYPE_T45_C1

                }

                /**
                     * idListItemSepratorImg : Image source of the list item separator
                     */
                Image {
                    id: idListItemSepratorImage
                    source: "qrc:/image/AudioPresets/AudioPresetsPopupBackground/Set_Gfx_AudioPresetPopSep_7in_n.png"
                    width: 90
                    height: 1
                    anchors
                    {
                        left: idActiveAudioPresetText.left
                        leftMargin: 30
                        top: idActiveAudioPresetText.bottom
                        topMargin: 7
                    }
                }

                /**
                 * idAudioPresetList : Generic list of the audio presets
                 */
                GenericList {
                    id: idAudioPresetList
                    width: 166
                    height: 255
                    prScrollBarTrackImageSource : "qrc:/image/AudioPresets/AudioPresetsPopupBackground/Gen_Gfx_ScrollbarBg3_n.png"
                    prScrollBarThumbImageSource : "qrc:/image/AudioPresets/AudioPresetsPopupBackground/Gen_Gfx_Scroller_n.png"
                    prScrollBarLeftMargin : 400

                    anchors{
                        top: parent.top
                        topMargin: 40
                        left: parent.left
                        leftMargin: 230
                    }
                    rowShownPerPage: 5
                    idList.model: cppSetupAdaptor.currentModel
                    idList.delegate: idDelegate

                }

            }

            /**
             * rowlayout, to arrange the BMT sliders in row
             */

            RowLayout{
                id: idBMTRowLayout
                spacing: 80

                anchors {
                    left: parent.left
                    leftMargin:5
                    top: parent.top
                    topMargin: 10
                }

                VerticalSlider {
                    id: idBassSlider
                    prMinVal: -10
                    prMaxVal: 10
                    prVerticalslider.value: prBassSliderValue
                    prSliderName: qsTr("TEXT_AUDIO_SETTING_BASS") + cppThemeMgr.languageChanged

                    /* On value change of slider this signal gets emitted, in this we are making API call.
                       The logic here used is we send a request and mark the flag idresponserecieved as false,
                       once we receive the response mark the flag idresponserecieved as true and continues...*/
                    prVerticalslider.onValueChanged: {
                        cppSetupApp.qmlLog(
                                    "slider Value Changed: " + Math.round(
                                        prVerticalslider.value)
                                    + " prIsResponseReceived: " + prIsResponseReceived)
                        prSliderValue.text = Math.round(prVerticalslider.value)
                        if ((true === prIsResponseReceived) && (Math.round(prVerticalslider.value) !== prBassSliderValue)) {
                            cppAudioAdaptor.setBMTValues(
                                        Math.round(prVerticalslider.value), 0)
                            prIsResponseReceived = false
                        }
                        else {
                            // Do nothing
                        }
                    }
                }

                /**
                 * idMidSlider, slider to change the mid value
                 */
                VerticalSlider {
                    id: idMidSlider
                    prSliderName: qsTr("TEXT_AUDIO_SETTING_MIDDLE") + cppThemeMgr.languageChanged
                    prMinVal: -10
                    prMaxVal: 10
                    prVerticalslider.value: prMidSliderValue
                    /* On value change of slider this signal gets emitted, in this we are making API call.
                       The logic here used is we send a request and mark the flag idresponserecieved as false,
                       once we receive the response mark the flag idresponserecieved as true and continues...*/
                    prVerticalslider.onValueChanged: {
                        cppSetupApp.qmlLog(
                                    "slider Value Changed: " + Math.round(
                                        prVerticalslider.value)
                                    + " prIsResponseReceived: " + prIsResponseReceived)
                        prSliderValue.text = Math.round(prVerticalslider.value)
                        if ((true === prIsResponseReceived) && (Math.round(prVerticalslider.value) !== prMidSliderValue)) {
                            cppAudioAdaptor.setBMTValues(
                                        Math.round(prVerticalslider.value), 1)
                            prIsResponseReceived = false
                        }
                        else {
                            // Do nothing
                        }
                    }
                }

                /**
                 * idTrebleSlider, slider to change the treble value
                 */
                VerticalSlider {
                    id: idTrebleSlider
                    prSliderName: qsTr("TEXT_AUDIO_SETTING_TREBLE") + cppThemeMgr.languageChanged
                    prMinVal: -10
                    prMaxVal: 10
                    prVerticalslider.value: prTrebleSliderValue

                    /* On value change of slider this signal gets emitted, in this we are making API call.
                       The logic here used is we send a request and mark the flag idresponserecieved as false,
                       once we receive the response mark the flag idresponserecieved as true and continues...*/
                    prVerticalslider.onValueChanged: {
                        cppSetupApp.qmlLog(
                                    "slider Value Changed: " + Math.round(
                                        prVerticalslider.value)
                                    + " prIsResponseReceived: " + prIsResponseReceived)
                        prSliderValue.text = Math.round(prVerticalslider.value)
                        if ((true === prIsResponseReceived) && (Math.round(prVerticalslider.value) !== prTrebleSliderValue)) {
                            cppAudioAdaptor.setBMTValues(
                                        Math.round(prVerticalslider.value), 2)
                            prIsResponseReceived = false
                        }
                        else {
                            // Do nothing
                        }
                    }
                }
            }
        }
    }
}

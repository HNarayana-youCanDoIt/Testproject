import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.tunerenums 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import "qrc:/QML/Common"

BaseUI {
    id: idTunerMain
    anchors.fill: parent

    clip: true


    Item {
        id: idTunerScreenItem
        anchors.fill: parent
        state: cppTunerAdaptor.strTunerState
        visible: true//cppTunerAdaptor.bTunerDataAvailableStatus

        /* Text to hold Title of the screen */
        HBTitleWithBackButton {
            id: idTitle
            prTitle: cppTunerAdaptor.strBand
        }

        /* Text to hold tuner ongoing operation or current station name */
        HBText {
            id: idTunerOperationCumStationName

            width: 408
            height: 25

            anchors {
                left: parent.left
                leftMargin: 196
                top: parent.top
                topMargin: 127
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            fontType: ThemeMgr.FONTTYPE_T35_BK_C2
            text: cppTunerAdaptor.strStationName
        }

        /**
    * Item which contains three horizontal components
    *  AutoSeek UP button
    *  AutoSeek Down button
    *  Text field to show current frequency
    **/
        Item {
            id: idFreqAndSeek

            width: 430
            height: 76

            anchors {
                left: parent.left
                leftMargin: 186
                top: parent.top
                topMargin: 138
            }

            /* Button to start tuner autoSeek UP operation */
            ListGenericButton {
                id: idSeekDown

                width: 76
                height: 76

                anchors.left: parent.left

                defaultImageURL: "qrc:/image/Tuner/Tun_Ico_SeekPrevious_7in_n/Gen_Ico_FastRewind_n.png"
                pressedImageURL: "qrc:/image/Tuner/Tun_Ico_SeekPrevious_7in_n/Gen_Ico_FastRewind_nf.png"
                disabledImageURL: "qrc:/image/Tuner/Tun_Ico_SeekPrevious_7in_n/Gen_Ico_FastRewind_nd.png"

                onReleased: {
                    if(!touchAndHold){
                        cppTunerApp.qmlLog("TunerScreen.qml : request autoseek down")
                        cppTunerAdaptor.requestAutoSeekDown()
                    }
                }
                onPressAndHold: {
                    cppTunerApp.qmlLog("TunerScreen.qml : request autoseek down")
                    cppTunerAdaptor.requestAutoSeekDown()
                }
            }

            /* Button to start tuner autoSeek Down operation */
            ListGenericButton {
                id: idSeekUp

                width: 76
                height: 76

                anchors.right: parent.right

                defaultImageURL: "qrc:/image/Tuner/Tun_Ico_SeekNext_7in_n/Gen_Ico_FastForward_n.png"
                pressedImageURL: "qrc:/image/Tuner/Tun_Ico_SeekNext_7in_n/Gen_Ico_FastForward_nf.png"
                disabledImageURL: "qrc:/image/Tuner/Tun_Ico_SeekNext_7in_n/Gen_Ico_FastForward_nd.png"

                onReleased: {
                    if(!touchAndHold){
                        cppTunerApp.qmlLog("TunerScreen.qml : request autoseek up")
                        cppTunerAdaptor.requestAutoSeekUP()
                    }
                }
                onPressAndHold: {
                    cppTunerApp.qmlLog("TunerScreen.qml : request autoseek up")
                    cppTunerAdaptor.requestAutoSeekUP()
                }
            }

            /*
        * Item holds two text component to display complete freq
        *  Text to hold frequency value
        *  Text to hold frequency unit
        */
            Item {
                id: idfreqDisplay

                width: 310
                height: 37

                anchors {
                    horizontalCenter: parent.horizontalCenter
                    top: parent.top
                    topMargin: 20
                }

                /* Text to hold frequency value */
                HBText {
                    id: idFreqText

                    width: 160
                    height: 37

                    anchors.left: parent.left

                    verticalAlignment: HBText.AlignBottom
                    horizontalAlignment: HBText.AlignRight

                    fontType: ThemeMgr.FONTTYPE_T35_C3
                    text: cppTunerAdaptor.strFrequency
                }

                /* Text to hold frequency unit */
                HBText {
                    id: idFreqUnitText

                    width: 146
                    height: 37

                    anchors{
                        right: parent.right
                        top: parent.top
                        topMargin: -3
                    }

                    verticalAlignment: HBText.AlignBottom
                    horizontalAlignment: HBText.AlignLeft

                    fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
                    text: cppTunerAdaptor.strFrequencyUnit
                }
            }
        }

        /*
    * Frequency scale for manual tuning in tuner.
    * Manual frequency bar can touch and drag
    */
        TunerManualSeekBar {
            id: idManualSeekBar

            anchors {
                left: parent.left
                leftMargin: 155
                top: parent.top
                topMargin: 206
            }
        }

        // Preset List to store tuner preset in preset tiles
        TunerPresetList {
            id: idTunerPresetList

            anchors {
                left: parent.left
                leftMargin: 208
                top: parent.top
                topMargin: 397
            }
        }

        /*
    * Preset List naviagtion buttons
    * Preset next arrow button to navigate to preset list's next page
    */
        GenericButton {
            id: idBtnPresetListBrowseLeft

            width: 76
            height: 76

            anchors {
                top: parent.top
                topMargin: 393
                left: parent.left
                leftMargin: 132
            }

            defaultImageURL: "qrc:/image/Tuner/Gen_Ico_ArrowPrev_7in_n/Gen_Ico_ArrowPrev_n.png"
            pressedImageURL: "qrc:/image/Tuner/Gen_Ico_ArrowPrev_7in_n/Gen_Ico_ArrowPrev_nf.png"
            disabledImageURL: "qrc:/image/Tuner/Gen_Ico_ArrowPrev_7in_n/Gen_Ico_ArrowPrev_nd.png"

            enabled: (idTunerPresetList.iPresetListPageIndex > 0) ? true : false

            onReleased: {
                if (idTunerPresetList.iPresetListPageIndex > 0){
                    cppTunerAdaptor.iPresetListPageIndex = idTunerPresetList.iPresetListPageIndex - 1
                }
            }
        }

        /* Preset previous arrow button to navigate to preset list's previous page */
        GenericButton {
            id: idBtnPresetListBrowseRight
            defaultImageURL: "qrc:/image/Tuner/Gen_Ico_ArrowNext_7in_n/Gen_Ico_ArrowNext_n.png"
            pressedImageURL: "qrc:/image/Tuner/Gen_Ico_ArrowNext_7in_n/Gen_Ico_ArrowNext_nf.png"
            disabledImageURL: "qrc:/image/Tuner/Gen_Ico_ArrowNext_7in_n/Gen_Ico_ArrowNext_nd.png"
            width: 76
            height: 76
            enabled: (idTunerPresetList.iPresetListPageIndex
                      < (idTunerPresetList.iPresetListPages - 1)) ? true : false
            anchors {
                top: parent.top
                topMargin: 393
                left: parent.left
                leftMargin: 593
            }
            onReleased: {
                if (idTunerPresetList.iPresetListPageIndex < (idTunerPresetList.iPresetListPages - 1)){
                    cppTunerAdaptor.iPresetListPageIndex = idTunerPresetList.iPresetListPageIndex + 1
                }
            }
        }

        /* tuner browse button to open option screen */
        GenericButton {
            id: idBrowseButton

            width: 76
            height: 76

            anchors {
                left: parent.left
                leftMargin: 519
                top: parent.top
                topMargin: 50
            }

            defaultImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_n.png"
            pressedImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nf.png"
            disabledImageURL: "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nd.png"

            onReleased: {
                //            cppTunerApp.qmlLog("TunerScreen.qml : request Option screen")
                cppTunerApp.raiseSMEvent("tunerApp", TunerEnums.TUNER_SCREEN_OPTION)
            }
        }

        /**
    *   Tuner seek cancel button to stop ongoing scan.
    *   Button position will be same as browse button. Button's default visibility is false and will get visible
    *   when autostore or scan starts.
    **/
        GenericButton {
            id: idSeekCancel

            width: 76
            height: 76

            anchors {
                left: parent.left
                leftMargin: 569
                top: parent.top
                topMargin: 54
            }
            defaultImageURL: "qrc:/image/Tuner/Tun_Ico_Cancel/Tun_Ico_Cancel_n.png"
            pressedImageURL: "qrc:/image/Tuner/Tun_Ico_Cancel/Tun_Ico_Cancel_nf.png"

            visible: false

            onReleased: {
                cppTunerApp.qmlLog("TunerScreen.qml : request stop seek")
                cppTunerAdaptor.stopSeekOnScanAndAutostore()
            }
        }

        /**
    *   Tuner seek cancel button to stop ongoing scan.
    *   Button position will be same as browse button. Button's default visibility is false and will get visible
    *   when autostore or scan starts.
    **/
        GenericButton {
            id: idScanPlay

            width: 76
            height: 76

            anchors {
                left: parent.left
                leftMargin: 569
                top: parent.top
                topMargin: 54
            }
            defaultImageURL: "qrc:/image/Tuner/Tun_Ico_Play_7in_n-assets/Tun_Ico_Play_n.png"
            pressedImageURL: "qrc:/image/Tuner/Tun_Ico_Play_7in_n-assets/Tun_Ico_Play_nf.png"

            visible: false

            onReleased: {
                cppTunerApp.qmlLog("TunerScreen.qml : request play current station")
                cppTunerAdaptor.stopSeek()
            }
        }

        states: [
            State {
                name: "TunerMain"
            },
            State {
                name: "Scan"
                PropertyChanges {
                    target: idTunerOperationCumStationName
                    text: qsTr("TEXT_TUNER_SCAN_PROGRESS") + cppThemeMgr.languageChanged;
                }
                PropertyChanges {
                    target: idBrowseButton
                    visible: false
                }
                PropertyChanges {
                    target: idSeekCancel
                    visible: (cppTunerAdaptor.uiTagId === 0)
                }
                PropertyChanges {
                    target: idScanPlay
                    visible: !(cppTunerAdaptor.uiTagId === 0)
                }
                PropertyChanges {
                    target: idTitle
                    prBackButtonVisible: false
                }
            },
            State {
                name: "Autostore"
                PropertyChanges {
                    target: idTunerOperationCumStationName
                    text: qsTr("TEXT_TUNER_AUTOSTORE_PROGRESS")
                }
                PropertyChanges {
                    target: idBrowseButton
                    visible: false
                }
                PropertyChanges {
                    target: idSeekCancel
                    visible: true
                }
                PropertyChanges {
                    target: idTitle
                    prBackButtonVisible: false
                }
            }
        ]
    }

    Connections{
        target: cppHardkeyAdaptor
        onSigRotaryPressed: {
            cppTunerApp.qmlLog("TunerScreen.qml : right rotary pressed")

            if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode &&
                    (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState)){
                if(TunerEnums.SEEK_NONE === cppTunerAdaptor.eSeekType){
                    cppTunerApp.raiseSMEvent("tunerApp", TunerEnums.TUNER_SCREEN_OPTION)
                }
                else{
                    cppTunerAdaptor.stopSeek()
                }
            }
        }
    }


    Component.onDestruction: {
        cppTunerAdaptor.setTunerQMLStatus(false)
    }


    Component.onCompleted: {
        cppTunerAdaptor.setTunerQMLStatus(true)
    }
}

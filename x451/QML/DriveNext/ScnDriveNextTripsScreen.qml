import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.popupenums 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.driveNextenums 1.0

BaseUI {
    anchors.fill: parent

    /*
     * property to handle rotary events for selected element
     */
    property int prRREElementIndex: 0
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Screen background image
     */
    Image {
        anchors {
            bottom:parent.bottom
            left:parent.left
            leftMargin: 320
        }
        width: 480
        height: 340
        source: "qrc:/image/DriveNext/Gen_Ico_DrivePro_Big_ModeImages_7in_n-assets/Gen_Ico_Car_n.png"
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Swipe View Layout For trip selection
     */
    HBTabBar {
        id: idDriveNextTripsBar
        anchors {
            top: parent.top
            topMargin: 54
            left: parent.left
            leftMargin: 166
        }
        prTabViewModel:cppDriveNextAdaptor.driveNextTripsModel
        prCurrIndex: cppDriveNextAdaptor.currentTripIndex
        property int prTripType: cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripType

        onSigTabViewCurrentIndexChanged: {
            if(!isMovementByDrag) {
                setPositionView();
            }
            cppDriveNextAdaptor.currentTripIndex = prCurrIndex
            //cppDriveNextApplication.raiseSMEvent("ScnDriveNextTripsScreen", index)
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Column layout For trip performance selection
     */
    Column {
        anchors {
            top: parent.top
            topMargin: 150
            left: parent.left
            leftMargin: 377
        }
        spacing: 16

        CmpTripPerformanceButton {
            prTripPerformanceType: 1
            prHighlightedByRRE: (parent.parent.prRREElementIndex === prTripPerformanceType)
        }
        CmpTripPerformanceButton {
            prTripPerformanceType: 2
            prHighlightedByRRE: (parent.parent.prRREElementIndex === prTripPerformanceType)
        }
        CmpTripPerformanceButton {
            prTripPerformanceType: 3
            prHighlightedByRRE: (parent.parent.prRREElementIndex === prTripPerformanceType)
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Image source of the list item horizontal separator
     */
    Image {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top:parent.top
            topMargin: 366
        }
        source: "qrc:/image/AudioPresets/AudioPresetsPopupBackground/Ph_Gfx_BrowsebottomSep_7in_n-assets/Ph_Gfx_BrowsebottomSep_n.png"
    }
    /**
     * Image source of the list item vertical separator
     */
    Image {
        anchors {
            top:parent.top
            topMargin: 171
            left:parent.left
            leftMargin: 349
        }
        width: 1
        height: 140
        source: "qrc:/image/DriveNext/Set_Gfx_ListSeparator_vertical3_7inch_n-assets/Set_Gfx_ListSeparator_vertical3_7inch_n.png"
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Circular progress bar for trip score
     * contains title text, score texts and reset button
     */
    CmpTripProgressCircle {
        anchors {
            top: parent.top
            topMargin: 167
            left: parent.left
            leftMargin: 199
        }
        size: 128
        colorCircle: "#ffb5b5b5"
        colorBackground: "#33ffffff"
        showBackground: true
        lineWidth: 8
        arcBegin: 0
        arcEnd: (cppDriveNextAdaptor.scoreProxyScale > 0)
                ? ((360/cppDriveNextAdaptor.getScoreRange()) * (cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_OVERALL_SCORE]].dnValue))
                : 0

        Item {
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            width : idOverallScore.width + idOverallScoreUnit.width
            /**
             * Score text field
             */
            HBText {
                id : idOverallScore
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                //width: 60
                height: 23
                fontType: ThemeMgr.FONTTYPE_T35_C3
                horizontalAlignment: Text.AlignRight

                text: cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_OVERALL_SCORE]].dnValue
            }

            /**
             * Total score text field
             */
            HBText {
                id : idOverallScoreUnit
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }
                //width: 23
                height: 20
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                horizontalAlignment: Text.AlignLeft

                text: cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_OVERALL_SCORE]].dnUnit
            }
        }
        /**
         * Title text field
         */
        HBText {
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.bottom
                topMargin: 5
            }
            width: 141
            height: 20
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

            visible: ((idDriveNextTripsBar.prCurrIndex != 1) && (idDriveNextTripsBar.prCurrIndex != 2))

            text: cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_OVERALL_SCORE]].dnTitle
        }

        /**
         * Reset button
         */
        GenericButton {
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.bottom
                topMargin: 6
            }
            width: 112
            height: 47

            defaultImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"
            pressedImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_n.png"
            disabledImageURL: "qrc:/image/AudioPresets/Set_GfxBtnBg_7in_n/Set_GfxBtnBg_nd.png"

            visible: ((idDriveNextTripsBar.prTripType === DriveNextEnums.DRIVENEXT_TRIP_A) || (idDriveNextTripsBar.prTripType === DriveNextEnums.DRIVENEXT_TRIP_B))
            enabled: !cppDriveNextAdaptor.resetTripStatus

            text: qsTr("TEXT_DN_TRIP_RESET") + cppThemeMgr.languageChanged

            onReleased: {
                cppDriveNextAdaptor.tryResetDriveNextTrip(idDriveNextTripsBar.prTripType)
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Trip general info field layout
     */
    CmpTripGeneralInfo {
        anchors {
            top: parent.top
            topMargin: 393
            left: parent.left
            leftMargin: 177
        }

        prTitleText:    qsTr(cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_DISTANCE_TRAVELLED]].dnTitle)
        prValueText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_DISTANCE_TRAVELLED]].dnValue
        prUnitText:     cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_DISTANCE_TRAVELLED]].dnUnit
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Trip general info field layout
     */
    CmpTripGeneralInfo {
        anchors {
            top: parent.top
            topMargin: 393
            left: parent.left
            leftMargin: 398
        }

        prTitleText:    qsTr(cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_FUEL_ECONOMY]].dnTitle)
        prValueText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_FUEL_ECONOMY]].dnValue
        prUnitText:     cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_FUEL_ECONOMY]].dnUnit
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * connection to handle RRE events
     */
    Connections {
        target: cppHardkeyAdaptor

        onSigRotaryPressed: {
            cppHomeApplication.qmlLog("ScnDriveNextTripsScreen.qml : right rotary pressed")
            if (prRREElementIndex > 0) {
                if (HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode) {
                    if ((HardkeyEnum.HKEY_STATE_RELEASED === iKeyState) || (HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState)) {
                        cppDriveNextAdaptor.currentPerformanceIndex = prRREElementIndex
                        cppDriveNextApplication.raiseSMEvent("ScnDriveNextTripsScreen", "Details")
                    } else {
                        // do nothing
                    }
                } else {
                    cppHomeApplication.qmlLog("ScnDriveNextTripsScreen.qml : wrong rotary event")
                }
            } else {
                cppHomeApplication.qmlLog("ScnDriveNextTripsScreen.qml : no element selected for rotary even")
            }
        }

        onSigRotaryUpdate: {
            cppHomeApplication.qmlLog("ScnDriveNextTripsScreen.qml : right rotary rotated")
            if (HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB === iKeyCode) {
                if (prRREElementIndex <= 0) {
                    prRREElementIndex = 1
                } else if (HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState) {
                    if (prRREElementIndex > 1) {
                        prRREElementIndex = prRREElementIndex - 1
                    }
                    else {
                        // do nothing
                    }
                } else if (HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState) {
                    if (prRREElementIndex < 3) {
                        prRREElementIndex = prRREElementIndex + 1
                    }
                    else {
                        // do nothing
                    }
                } else {
                    // do nothing
                }
            } else {
                cppHomeApplication.qmlLog("ScnDriveNextTripsScreen.qml : wrong rotary event")
            }
        }
    }
}

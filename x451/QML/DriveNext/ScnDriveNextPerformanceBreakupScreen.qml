import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.driveNextenums 1.0

BaseUI {
    //id: idDriveNextPerformanceBreakupScreen
    anchors.fill: parent

    //property to hold current trip performance breakup type
    //property int prTripPerformanceType: 1
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
        source: (cppDriveNextAdaptor.currentPerformanceIndex === 1) ? "qrc:/image/DriveNext/Gen_Ico_DrivePro_Big_ModeImages_7in_n-assets/Gen_Ico_DriveProEfficiency_n.png" :
                                                                      (cppDriveNextAdaptor.currentPerformanceIndex === 2) ? "qrc:/image/DriveNext/Gen_Ico_DrivePro_Big_ModeImages_7in_n-assets/Gen_Ico_DriveProDriving_n.png" :
                                                                                                                            (cppDriveNextAdaptor.currentPerformanceIndex === 3) ? "qrc:/image/DriveNext/Gen_Ico_DrivePro_Big_ModeImages_7in_n-assets/Gen_Ico_DriveProSafety_n.png" : ""
        visible: (source != "")
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Texts used to show title text for DriveNext Performance Breakup screen
     */
    HBTitleWithBackButton {
        prTitle: ""//qsTr("TEXT_DN_PerformanceBreakupScreen_HEADER") + cppThemeMgr.languageChanged
    }

    /*
     * Custom Texts used to show title text for DriveNext Performance Breakup screen
     */
    HBText {
        anchors {
            top: parent.top
            topMargin: 79
            left: parent.left
            leftMargin: 342
        }
        width: 118
        height: 23
        fontType: ThemeMgr.FONTTYPE_T35_C3
        text: cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripName
    }

    /*
     * Custom Texts used to show title text for DriveNext Performance Breakup screen
     */
    HBText {
        anchors {
            top: parent.top
            topMargin: 122
            left: parent.left
            leftMargin: 283
        }
        width: 227
        height: 20
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        text: qsTr("TEXT_DN_PERFORMANCE_BREAKUP") + cppThemeMgr.languageChanged
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Image source of the list item horizontal separator
     */
    Image {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 152
        }
        source: "qrc:/image/AudioPresets/AudioPresetsPopupBackground/Ph_Gfx_BrowsebottomSep_7in_n-assets/Ph_Gfx_BrowsebottomSep_n.png"
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Performance Rating layout
     * contains Icon image, Title text, Score texts
     */
    Item {
        anchors {
            top: parent.top
            topMargin: 140
            left: parent.left
            leftMargin: 170
        }
        width: 464
        height: 76

        /*
         * Icon image for Performance Rating layout
         */
        Image {
            anchors {
                top: parent.top
                left: parent.left
            }
            width: 76
            height: 76
            source: (cppDriveNextAdaptor.currentPerformanceIndex === 1) ? "qrc:/image/DriveNext/Gen_Ico_DriveProEfficiency_7inch_n-assets/Gen_Ico_DriveProEfficiency_n.png":
                                                                          (cppDriveNextAdaptor.currentPerformanceIndex === 2) ? "qrc:/image/DriveNext/Gen_Ico_DriveProDriving_7inch_n-assets/Gen_Ico_DriveProDriving_n.png":
                                                                                                                                (cppDriveNextAdaptor.currentPerformanceIndex === 3) ?  "qrc:/image/DriveNext/Gen_Ico_DriveProSafety_7inch_n-assets/Gen_Ico_DriveProSafety_n.png": ""
            visible: (source != "")
        }

        /*
         * Title text for Performance Rating layout
         */
        HBText {
            anchors {
                top: parent.top
                topMargin: 26
                left: parent.left
                leftMargin: 73
            }
            width: 150
            height: 23
            fontType: ThemeMgr.FONTTYPE_T35_C3
            text: (cppDriveNextAdaptor.currentPerformanceIndex === 1) ?
                      cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_EFFICIENCY_SCORE]].dnTitle
                    : (cppDriveNextAdaptor.currentPerformanceIndex === 2) ?
                          cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_DRIVING_SCORE]].dnTitle
                        : (cppDriveNextAdaptor.currentPerformanceIndex === 3) ?
                              cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SAFETY_SCORE]].dnTitle
                            : ""
        }

        /*
         * Score texts for Performance Rating layout
         */
        HBText {
            anchors {
                top: parent.top
                topMargin: 32
                right: parent.right
                rightMargin: 45
            }
            width: 21
            height: 20
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
            text: (cppDriveNextAdaptor.currentPerformanceIndex === 1) ?
                      cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_EFFICIENCY_SCORE]].dnUnit
                    : (cppDriveNextAdaptor.currentPerformanceIndex === 2) ?
                          cppDriveNextAdaptor.signalsData[ cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_DRIVING_SCORE]].dnUnit
                        : (cppDriveNextAdaptor.currentPerformanceIndex === 3) ?
                              cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SAFETY_SCORE]].dnUnit
                            : ""
            HBText {
                anchors {
                    top: parent.top
                    topMargin: -5
                    right: parent.left
                }
                width: 70
                height: 23
                fontType: ThemeMgr.FONTTYPE_T35_C3
                horizontalAlignment: Text.AlignRight
                text: (cppDriveNextAdaptor.currentPerformanceIndex === 1) ?
                          cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_EFFICIENCY_SCORE]].dnValue
                        : (cppDriveNextAdaptor.currentPerformanceIndex === 2) ?
                              cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_DRIVING_SCORE]].dnValue
                            : (cppDriveNextAdaptor.currentPerformanceIndex === 3) ?
                                  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SAFETY_SCORE]].dnValue
                                : ""
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Information Layout Line
     */
    Image {
        anchors {
            left: parent.left
            leftMargin: 182
            top: parent.top
            topMargin: 210
        }
        width: 440
        height: 3
        source: "qrc:/image/DriveNext/Gen_Gfx_DriveProSepProgressBar_7inch_n-assets/Gen_Gfx_DriveProSepProgressBar_7inch_n.png"
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Information Layout
     */
    CmpTripPerformanceBreakupInfo {
        prElement01.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_TRIP_DURATION]].dnTitle
        prElement01.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_TRIP_DURATION]].dnValue
        prElement01.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_TRIP_DURATION]].dnUnit
        prElement01.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_TRIP_DURATION]].dnSubValue
        prElement01.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_TRIP_DURATION]].dnSubUnit

        prElement02.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_FUEL_ECONOMY]].dnTitle
        prElement02.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_FUEL_ECONOMY]].dnValue
        prElement02.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_FUEL_ECONOMY]].dnUnit
        prElement02.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_FUEL_ECONOMY]].dnSubValue
        prElement02.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_FUEL_ECONOMY]].dnSubUnit

        prElement03.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_ENG_IDLE_TIME]].dnTitle
        prElement03.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_ENG_IDLE_TIME]].dnValue
        prElement03.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_ENG_IDLE_TIME]].dnUnit
        prElement03.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_ENG_IDLE_TIME]].dnSubValue
        prElement03.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_ENG_IDLE_TIME]].dnSubUnit

        prElement04.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_AVG_SPEED]].dnTitle
        prElement04.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_AVG_SPEED]].dnValue
        prElement04.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_AVG_SPEED]].dnUnit
        prElement04.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_AVG_SPEED]].dnSubValue
        prElement04.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_AVG_SPEED]].dnSubUnit

        visible: (cppDriveNextAdaptor.currentPerformanceIndex === 1)
    }
    CmpTripPerformanceBreakupInfo {
        prElement01.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_TOP_SPEED]].dnTitle
        prElement01.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_TOP_SPEED]].dnValue
        prElement01.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_TOP_SPEED]].dnUnit
        prElement01.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_TOP_SPEED]].dnSubValue
        prElement01.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_TOP_SPEED]].dnSubUnit

        prElement02.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_PROPER_GEAR_UTIL]].dnTitle
        prElement02.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_PROPER_GEAR_UTIL]].dnValue
        prElement02.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_PROPER_GEAR_UTIL]].dnUnit
        prElement02.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_PROPER_GEAR_UTIL]].dnSubValue
        prElement02.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_PROPER_GEAR_UTIL]].dnSubUnit

        prElement03.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_AVG_ACCEL_PEDAL_TRIVAL]].dnTitle
        prElement03.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_AVG_ACCEL_PEDAL_TRIVAL]].dnValue
        prElement03.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_AVG_ACCEL_PEDAL_TRIVAL]].dnUnit
        prElement03.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_AVG_ACCEL_PEDAL_TRIVAL]].dnSubValue
        prElement03.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_AVG_ACCEL_PEDAL_TRIVAL]].dnSubUnit

        prElement04.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_MOST_USED_GEAR]].dnTitle
        prElement04.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_MOST_USED_GEAR]].dnValue
        prElement04.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_MOST_USED_GEAR]].dnUnit
        prElement04.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_MOST_USED_GEAR]].dnSubValue
        prElement04.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_MOST_USED_GEAR]].dnSubUnit

        visible: (cppDriveNextAdaptor.currentPerformanceIndex === 2)
    }
    CmpTripPerformanceBreakupInfo {
        prElement01.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SEATBELT_UTIL]].dnTitle
        prElement01.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SEATBELT_UTIL]].dnValue
        prElement01.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SEATBELT_UTIL]].dnUnit
        prElement01.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SEATBELT_UTIL]].dnSubValue
        prElement01.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SEATBELT_UTIL]].dnSubUnit

        prElement02.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_OVER_SPEEDING]].dnTitle
        prElement02.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_OVER_SPEEDING]].dnValue
        prElement02.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_OVER_SPEEDING]].dnUnit
        prElement02.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_OVER_SPEEDING]].dnSubValue
        prElement02.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_OVER_SPEEDING]].dnSubUnit

        prElement03.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_HARSH_ACCEL]].dnTitle
        prElement03.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_HARSH_ACCEL]].dnValue
        prElement03.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_HARSH_ACCEL]].dnUnit
        prElement03.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_HARSH_ACCEL]].dnSubValue
        prElement03.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_HARSH_ACCEL]].dnSubUnit

        prElement04.prTitleText:    cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_HARSH_BREAK]].dnTitle
        prElement04.prValueText01:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_HARSH_BREAK]].dnValue
        prElement04.prUnitText01:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_HARSH_BREAK]].dnUnit
        prElement04.prValueText02:  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_HARSH_BREAK]].dnSubValue
        prElement04.prUnitText02:   cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_HARSH_BREAK]].dnSubUnit

        visible: (cppDriveNextAdaptor.currentPerformanceIndex === 3)
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * GenericButton is prevoius arrow button, used to swipe left
     */
    GenericButton {

        anchors {
            left: parent.left
            leftMargin: 119
            top: parent.top
            topMargin: 264
        }
        width: 76
        height: 76
        defaultImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowsePreviousArrow_7in_n-assets/Ph_Ico_BrowsePreviousArrow_na.png"
        pressedImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowsePreviousArrow_7in_n-assets/Ph_Ico_BrowsePreviousArrow_np.png"
        disabledImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowsePreviousArrow_7in_n-assets/Ph_Ico_BrowsePreviousArrow_nd.png"

        enabled: (cppDriveNextAdaptor.currentPerformanceIndex > 1)

        onPressed: {
            cppUIBase.qmlLog("ScnDriveNextPerformanceBreakupScreen.qml : BrowsePreviousArrow : onPressed")
        }

        onReleased: {
            cppUIBase.qmlLog("ScnDriveNextPerformanceBreakupScreen.qml : BrowsePreviousArrow : onReleased")
            if (!touchAndHold) {
                moveLeft()
            }
        }

        onPressAndHold: {
            cppUIBase.qmlLog("ScnDriveNextPerformanceBreakupScreen.qml : BrowsePreviousArrow : onPressAndHold")
            moveLeft()
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * GenericButton is next arrow button, used to swipe right
     */
    GenericButton {
        anchors {
            left: parent.left
            leftMargin: 605
            top: parent.top
            topMargin: 264
        }
        width: 76
        height: 76
        defaultImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowseNextArrow_7in_n-assets/Ph_Ico_BrowseNextArrow_na.png"
        pressedImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowseNextArrow_7in_n-assets/Ph_Ico_BrowseNextArrow_np.png"
        disabledImageURL: "qrc:/image/ZenPresets/Ph_Ico_BrowseNextArrow_7in_n-assets/Ph_Ico_BrowseNextArrow_nd.png"

        enabled: (cppDriveNextAdaptor.currentPerformanceIndex < 3)

        onPressed: {
            cppUIBase.qmlLog("ScnDriveNextPerformanceBreakupScreen.qml : BrowseNextArrow : onPressed")
        }

        onReleased: {
            cppUIBase.qmlLog("ScnDriveNextPerformanceBreakupScreen.qml : BrowseNextArrow : onReleased")
            if (!touchAndHold) {
                moveRight()
            }
        }

        onPressAndHold: {
            cppUIBase.qmlLog("ScnDriveNextPerformanceBreakupScreen.qml : BrowseNextArrow : onPressAndHold")
            moveRight()
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * PageIndicator used to show how many data groups are available on DriveNext Performance Breakup screen and which one is on screen
     */
    PageIndicator {
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 19
        }
        spacing: 12
        count: 3
        currentIndex: 0

        delegate: Item {
            width: parent.spacing
            height: parent.spacing
            Image {
                anchors.centerIn: parent
                source: (index === (cppDriveNextAdaptor.currentPerformanceIndex - 1)) ? "qrc:/image/Home/Home_Pagination/Home_pagination_4.png" :  "qrc:/image/Home/Home_Pagination/Home_pagination_3.png"
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * functions to handle left movements
     */
    function moveLeft() {
        if (cppDriveNextAdaptor.currentPerformanceIndex > 1){
            cppDriveNextAdaptor.currentPerformanceIndex = cppDriveNextAdaptor.currentPerformanceIndex - 1
        } else {
            cppDriveNextAdaptor.currentPerformanceIndex = 1
        }
    }

    /**
     * functions to handle right movements
     */
    function moveRight() {
        if (cppDriveNextAdaptor.currentPerformanceIndex < 3){
            cppDriveNextAdaptor.currentPerformanceIndex = cppDriveNextAdaptor.currentPerformanceIndex + 1
        } else {
            cppDriveNextAdaptor.currentPerformanceIndex = 3
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * connection to handle RRE events
     */
    Connections {
        target: cppHardkeyAdaptor

        onSigRotaryUpdate: {
            cppHomeApplication.qmlLog("ScnDriveNextPerformanceBreakupScreen.qml : right rotary rotated")
            if (HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB === iKeyCode) {
                if (HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState) {
                    moveLeft()
                } else if (HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState) {
                    moveRight()
                } else {
                    // do nothing
                }
            } else {
                cppHomeApplication.qmlLog("ScnDriveNextPerformanceBreakupScreen.qml : wrong rotary event")
            }
        }
    }
}

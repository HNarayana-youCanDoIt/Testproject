/**
 * @file            CmpTripPerformanceButton.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * CmpTripPerformanceButton, a comopnent can use to show trip performance breakup information button on DriveNext main screen,
 * It is a button having Icon, Title, ValueScore text fields,
 * All this values are inatialised using value from prTripPerformanceType property.
 * on button input action respective TripPerformanceBreakup screen shall open.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.driveNextenums 1.0

/////////////////////////////////////////////////////////////////////////////////
/**
 * Trip Performance Button
 */
GenericButton {
    width: 241
    height: 55

    property bool prHighlightedByRRE: false // property used to highlight element by RRE event
    property int prTripPerformanceType: 0 // property used to identify trip performance breakup type

    defaultImageURL:  "qrc:/image/DriveNext/Drw_Gfx_rectangel_7in_n-assets/Drw_Gfx_rectangel_7in_n.png"
    disabledImageURL: "qrc:/image/DriveNext/Drw_Gfx_rectangel_7in_n-assets/Drw_Gfx_rectangel_7in_nd.png"
    pressedImageURL:  "qrc:/image/DriveNext/Drw_Gfx_rectangel_7in_n-assets/Drw_Gfx_rectangel_7in_np.png"

    contentItem: Item {} // removed default text to impliment custom text layout

    /////////////////////////////////////////////////////////////////////////////////
    /*
     * removing default background
     */
    background: Item{}

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Icon for Trip Performance Button background
     */
    Image
    {
        id: idButtonBackground
        anchors.fill: parent
        //fillMode: Image.Preserve
        visible: (source !== "")
        source: ((parent.enabled) ? ((parent.prHighlightedByRRE) ? (parent.pressedImageURL) : ((parent.pressed) ? (parent.pressedImageURL) : (parent.defaultImageURL))) : (parent.disabledImageURL))
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Icon for Trip Performance Button Icon
     */
    Image {
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
        }
        width: 56
        height: 56
        source: (prTripPerformanceType === 1) ?
                    "qrc:/image/DriveNext/Gen_Ico_DriveProEfficiency_small_7inch_n-assets/Gen_Ico_DriveProEfficiency_n.png"
                  : (prTripPerformanceType === 2) ?
                        "qrc:/image/DriveNext/Gen_Ico_DriveProDriving_Small_7inch_n-assets/Gen_Ico_DriveProDriving_n.png"
                      : (prTripPerformanceType === 3) ?
                            "qrc:/image/DriveNext/Gen_Ico_DriveProSafety_Small_7inch_n/Gen_Ico_DriveProSafety_Small_7inch_n.png"
                          : ""

        visible: (source !== "")
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Ttile text field for Trip Performance Button
     */
    HBText {
        anchors {
            top: parent.top
            topMargin: 17
            left: parent.left
            leftMargin: 56
        }
        width: 113
        height: 20
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

        text: (prTripPerformanceType === 1) ?
                  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_EFFICIENCY_SCORE]].dnTitle
                : (prTripPerformanceType === 2) ?
                      cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_DRIVING_SCORE]].dnTitle
                    : (prTripPerformanceType === 3) ?
                          cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SAFETY_SCORE]].dnTitle
                        : ""
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * ValueScore text field for Trip Performance Button
     */
    HBText {
        anchors {
            top: parent.top
            topMargin: 17
            right: parent.right
            rightMargin: 8
        }
        width: 23
        height: 20
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED

        text: (prTripPerformanceType === 1) ?
                  cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_EFFICIENCY_SCORE]].dnUnit
                : (prTripPerformanceType === 2) ?
                      cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_DRIVING_SCORE]].dnUnit
                    : (prTripPerformanceType === 3) ?
                          cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SAFETY_SCORE]].dnUnit
                        : ""

        HBText {
            anchors {
                top: parent.top
                topMargin: -4
                right: parent.left
            }
            width: 60
            height: 23
            fontType: ThemeMgr.FONTTYPE_T35_C3
            horizontalAlignment: Text.AlignRight

            text: (prTripPerformanceType === 1) ?
                      cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_EFFICIENCY_SCORE]].dnValue
                    : (prTripPerformanceType === 2) ?
                          cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_DRIVING_SCORE]].dnValue
                        : (prTripPerformanceType === 3) ?
                              cppDriveNextAdaptor.signalsData[cppDriveNextAdaptor.tripsData[cppDriveNextAdaptor.currentTripIndex].tripSignals[DriveNextEnums.DN_TRIP_ELEMENT_SAFETY_SCORE]].dnValue
                            : ""
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Function to handle press and hold action on Trip Performance Button
     */
    onPressAndHold: {
        openPerformanceBreakupScreen()
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Function to handle release action on Trip Performance Button
     */
    onReleased: {
        openPerformanceBreakupScreen()
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Function to open selected Trip Performance Breakup screen
     */
    function openPerformanceBreakupScreen() {
        cppDriveNextAdaptor.currentPerformanceIndex = prTripPerformanceType
        cppDriveNextApplication.raiseSMEvent("ScnDriveNextTripsScreen", "Details")
    }
}

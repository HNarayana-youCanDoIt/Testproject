import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0

BaseUI {
    width: 800
    height: 480
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * GenericButton used to full screen touch input handle
     */
    /*We are setting month -1 since service considers the month from 1(jan = 1) whereas in Date() considers it from 0(jan = 0)*/
    property date prCurrentDate: new Date(cppDateAndTimeAdaptor.year, cppDateAndTimeAdaptor.month,
                                          cppDateAndTimeAdaptor.day, cppDateAndTimeAdaptor.hour,
                                          cppDateAndTimeAdaptor.minute, cppDateAndTimeAdaptor.sec)

    /* Property alias for idMediaOffInfoText1 */
    property alias prMediaOffInfoText1: idMediaOffInfoText1

    /* Property alias for idMediaOffInfoIcon */
    property alias  prMediaOffInfoIcon: idMediaOffInfoIcon

    /* Property alias for idMediaOffInfoText2 */
    property alias prMediaOffInfoText2: idMediaOffInfoText2


    // FixMe: [NK] need to add touch handling flow
    GenericButton {
        anchors {
            fill: parent
        }
        onPressed: {
            cppMediaOffApplication.qmlLog("MediaOff Pressed")
            //cppMediaOffApplication.raiseSMEvent("MediaOffNavigate",0)
        }
        onPressAndHold: {
            cppMediaOffApplication.qmlLog("MediaOff Press and hold")
        }
        onPressAndHoldContinue: {
            cppMediaOffApplication.qmlLog("MediaOff Press and hold continue")
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Clock body layout
     */
    // FixMe: [NK] temprary clock body
    Item {
        property date currentDate
        property int refreshInterval: 100

        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: -10
        }

        /*
         * Clock dial Image
         */
        Image {
            id: idClockDial
            anchors {
                centerIn: parent
                verticalCenterOffset: 10
            }
            source: "qrc:/Assets/MediaOff/Gen_Gfx_WatchFace_n.png" //FixMe: [NK] Dummy Clock Dial Image
        }

        /*
         * Clock Hr Hand layout
         */
        Item {
            id: idClockHrHand
            anchors {
                centerIn: parent
            }
            height: idHrHandImage.height * 2
            rotation: cppDateAndTimeAdaptor.hour * 30.0 + cppDateAndTimeAdaptor.minute * 0.5
            // For debug purpose Hr hand
            /*Rectangle {
                anchors {
                    bottom: idHrHandImage.bottom
                    horizontalCenter: idHrHandImage.horizontalCenter
                }
                color: "gray"
                border.color: "white"
                height: idHrHandImage.height * 0.6
                width: idHrHandImage.width * 1.5
                radius: width / 2
            }*/

            /*
             * Clock Hr Hand Image
             */
            Image {
                id: idHrHandImage
                anchors {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                }
                source: "qrc:/Assets/MediaOff/MediaOff_Gfx_WatchHandHours_n.png"
            }
        }
        /*
         * Clock Min Hand layout
         */
        Item {
            id: idClockMinHand
            anchors {
                centerIn: parent
            }
            height: idMinHandImage.height * 2
            rotation: cppDateAndTimeAdaptor.minute * 6.0 + cppDateAndTimeAdaptor.sec * 0.1
            // For debug purpose min Hand
            /*Rectangle {
                anchors {
                    bottom: idMinHandImage.bottom
                    horizontalCenter: idMinHandImage.horizontalCenter
                }
                color: "gray"
                border.color: "white"
                height: idMinHandImage.height * 0.7
                width: idMinHandImage.width
                radius: width / 2
            }*/

            /*
             * Clock Min Hand Image
             */
            Image {
                id: idMinHandImage
                anchors {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                }
                source: "qrc:/Assets/MediaOff/MediaOff_Gxf_WatchHandMin_n.png"
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * HBText used to show Clock Time
     */
    // FixMe: [NK] temprary text for clock time
    HBText {
        id: idClockTimeText

        fontType: ThemeMgr.FONTTYPE_T45_C1

        anchors {
            bottom: parent.verticalCenter
            bottomMargin: 15
            horizontalCenter: parent.horizontalCenter
        }
        horizontalAlignment: HBText.Center
        verticalAlignment: HBText.Bottom

        text: Qt.formatDateTime(prCurrentDate, "HH:mm")

    }
    HBText {
        id: idClockTimeAMPMText

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

        anchors {
            left: idClockTimeText.right
            leftMargin: 5
            bottom: idClockTimeText.bottom
            bottomMargin: 7
        }

        horizontalAlignment: HBText.Center
        verticalAlignment: HBText.Bottom

        text: cppDateAndTimeAdaptor.is24HrFormatStatus ? "" : cppDateAndTimeAdaptor.amOrPm

    }

    /*
     * HBText used to show Clock Date
     */
    // FixMe: [NK] temprary text for clock time
    HBText {
        id: idClockDateText

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

        anchors {
            top: parent.verticalCenter
            topMargin: -4
            horizontalCenter: parent.horizontalCenter
        }
        horizontalAlignment: HBText.Center
        verticalAlignment: HBText.Top
        text: Qt.formatDateTime(prCurrentDate, "dd MMMM")
    }

    /*
     * HBText used to show Clock Day
     */
    // FixMe: [NK] temprary text for clock time
    HBText {
        id: idClockDayText

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

        anchors {
            top: parent.verticalCenter
            topMargin: 32
            horizontalCenter: parent.horizontalCenter
        }
        horizontalAlignment: HBText.Center
        verticalAlignment: HBText.Top
        text: Qt.formatDateTime(prCurrentDate, "dddd")
    }
    /////////////////////////////////////////////////////////////////////////////////

    /*
     * MediaOFF screen information text & image.
     */
    HBText {
        id: idMediaOffInfoText1
        anchors {
            bottom: parent.bottom
            bottomMargin: 32
            left: parent.left
            leftMargin: 210
        }
        text: qsTr("Press")  + cppThemeMgr.languageChanged
        fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
    }

    Image {
        id: idMediaOffInfoIcon
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_RotaryVolume_7in_n-assets/Drw_Ico_RotaryVolume_7in_na.png"
        anchors {
            left: idMediaOffInfoText1.right
            verticalCenter: idMediaOffInfoText1.verticalCenter
        }
    }

    HBText {
        id: idMediaOffInfoText2
        anchors {
            left: idMediaOffInfoIcon.right
            verticalCenter: idMediaOffInfoText1.verticalCenter
        }
        text: qsTr("to Resume Media Playback.")  + cppThemeMgr.languageChanged
        fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
    }
}

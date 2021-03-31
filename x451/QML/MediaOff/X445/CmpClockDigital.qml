/**
 * @file            CmpClockDigital.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * CmpClockDigital, a component created using CmpClockTemplate to display clock,
 * It digital clock layout.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.maskedMouseArea 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.clockenum 1.0

CmpClockTemplate {
    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Function to check if there is single digit then append 0 at the beginning else return the same number
     */
    function formatNumberLength(num) {
        if (num < 10) {
            num = "0" + num
        }
        return num
    }
    /**
     * Function to update clock information as per time current date values
     */
    function refreshClock() {
        var currentDate = new Date()
        var iHrs = currentDate.getHours()
        var iMins = currentDate.getMinutes()
        var iSecs = currentDate.getSeconds()

        var iHrsIn12 = 0
        if(0 === iHrs) {
            iHrsIn12 = 12
        } else if (iHrs > 12) {
            iHrsIn12 = iHrs - 12
        } else {
            iHrsIn12 = iHrs
        }

        if (cppDateAndTimeAdaptor.is24HrFormatStatus) {
            idClockTimeText.text = formatNumberLength(iHrs) + ":" + formatNumberLength(iMins)
        } else {
            idClockTimeText.text = formatNumberLength(iHrsIn12) + ":" + formatNumberLength(iMins)
        }
        idClockDateText.text = Qt.formatDateTime(currentDate, "MMMM dd, dddd")
    }

    Connections{
        target: cppDrawersAdaptor
        onSigDateTimeRefresh: refreshClock()
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Clock body layout
     */
    Item {
        id: idClockBodyItem

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
            }
            source: cppMediaOffAdaptor.clockInformationList[uId].imageDial
            visible: (source !== "")

            transform: Scale {
                origin.x: width/2
                origin.y: height/2
                xScale: cppUIBase.screenAspectRatio
            }

            /*
             * This masked mouse area used to get touch event inside clock dial
             */
            MaskedMouseArea{
                id: idClockDialMouseArea

                anchors.fill: parent

                alphaThreshold: 0.01
                maskSource: parent.source

                onReleased: {
                    cppUIBase.qmlLog("CmpClockDigital.qml onReleased Uid:" + uId)
                    onClockDialRelease();
                }
            }
        }
        }

        /////////////////////////////////////////////////////////////////////////////////
        /*
         * HBText used to show Clock Time HH:MM
         */
        HBText {
            id: idClockTimeText

            anchors {
                bottom: parent.verticalCenter
                top: idClockDial.top
                topMargin: 26
                horizontalCenter: parent.horizontalCenter
            }

            fontType: ThemeMgr.FONTTYPE_T70_C2_WHITE
            horizontalAlignment: HBText.Center
            verticalAlignment: HBText.Bottom
        }
        /*
         * HBText used to show Clock Time AM/PM
         */
        HBText {
            anchors {                
                left: idClockTimeText.right
                leftMargin: 1
                bottom: idClockTimeText.bottom
                bottomMargin: 14
            }
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
            horizontalAlignment: HBText.Center
            verticalAlignment: HBText.Bottom

            text: cppDateAndTimeAdaptor.is24HrFormatStatus ? "" : cppDateAndTimeAdaptor.amOrPm
        }
        /*
         * HBText used to show Clock Date and Day
         */
        HBText {
            id: idClockDateText

            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

            anchors {
                top: parent.verticalCenter
                bottomMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            horizontalAlignment: HBText.Center
            verticalAlignment: HBText.Bottom
        }

    Component.onCompleted: refreshClock()
}

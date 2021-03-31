/**
 * @file            CmpClockAnalog.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * CmpClockAnalog, a component created using CmpClockTemplate to display clock,
 * It analog clock layout.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.maskedMouseArea 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.clockenum 1.0

CmpClockTemplate {

    //// prEnableHandAnimation is property to toggle hand rotation animations.
    property bool prEnableHandAnimation: false

    //// prHandAnimationTime is property used to change rotation animation duration.
    property int prHandAnimationTime: 0

    //// prHandAnimationType is property used to change rotation animation type.
    property int prHandAnimationType: Easing.Linear

    //// prShadowOffsetX is property used to update shadow positions.
    property double prShadowOffsetX: 7

    //// prShadowOffsetY is property used to update shadow positions.
    property double prShadowOffsetY: 7

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
        if (iHrs > 12) {
            iHrsIn12 = iHrs - 12
        } else if(0 === iHrs) {
            iHrsIn12 = 12
        } else {
            iHrsIn12 = iHrs
        }

        idClockDayText.text = Qt.formatDateTime(currentDate, "MMMM dd, dddd")

        // convert hours value to hour hand rotation
        idHrHandImage.rotation = (iHrsIn12 * 30.0 + iMins * 0.5)
        idHrHandShadowImage.rotation = (iHrsIn12 * 30.0 + iMins * 0.5)

        // convert minutes value to minute hand rotation
        idMinHandImage.rotation = (iMins * 6.0 + iSecs * 0.1)
        idMinHandShadowImage.rotation = (iMins * 6.0 + iSecs * 0.1)

        var iDeltaSec = 0
        if (cppMediaOffAdaptor.clockInformationList[uId].motionType === ClockEnum.MOTION_SMOOTH) {
            prHandAnimationType = Easing.Linear
            if (59 > iSecs) {
                iDeltaSec = 1
            } else {
                iDeltaSec = -iSecs
            }
        } else if (cppMediaOffAdaptor.clockInformationList[uId].motionType === ClockEnum.MOTION_ELASTIC) {
            prHandAnimationType = Easing.OutElastic
        } else if (cppMediaOffAdaptor.clockInformationList[uId].motionType === ClockEnum.MOTION_JUMP) {
            prHandAnimationType = Easing.OutSine
        }

        // convert seconds value to second hand rotation
        idSecHandImage.rotation = ((iSecs + iDeltaSec) * 6.0)
        idSecHandShadowImage.rotation = ((iSecs + iDeltaSec) * 6.0)
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Clock body layout
     */
    Item {
        id: idClockBodyItem

        anchors {
            fill: parent
        }

        transform: Scale {
            origin.x: width/2
            origin.y: height/2
            xScale: cppUIBase.screenAspectRatio
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

            /*
             * This masked mouse area used to get touch event inside clock dial
             */
            MaskedMouseArea{
                id: idClockDialMouseArea

                anchors.fill: parent

                alphaThreshold: 0.01
                maskSource: parent.source

                onReleased: {
                    cppUIBase.qmlLog("CmpClockAnalog.qml onReleased Uid:" + uId)
                    onClockDialRelease();
                }
            }
        }
        /*
         * Clock Hr Hand Shadow Image
         */
        Image {
            id: idHrHandShadowImage
            anchors {
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: prShadowOffsetX * 0.4
                verticalCenter: parent.verticalCenter
                verticalCenterOffset: prShadowOffsetY * 0.4
            }
            source:cppMediaOffAdaptor.clockInformationList[uId].imageHrHandShadow
            visible: (source !== "")
            Behavior on rotation {
                enabled: prEnableHandAnimation
                RotationAnimation { duration: prHandAnimationTime; direction: RotationAnimation.Clockwise; easing.type: prHandAnimationType }
            }
        }
        /*
         * Clock Min Hand Shadow Image
         */
        Image {
            id: idMinHandShadowImage
            anchors {
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: prShadowOffsetX * 0.6
                verticalCenter: parent.verticalCenter
                verticalCenterOffset: prShadowOffsetY * 0.6
            }
            source: cppMediaOffAdaptor.clockInformationList[uId].imageMinHandShadow
            visible: (source !== "")
            Behavior on rotation {
                enabled: prEnableHandAnimation
                RotationAnimation { duration: prHandAnimationTime; direction: RotationAnimation.Clockwise; easing.type: prHandAnimationType }
            }
        }
        /*
         * Clock Sec Hand Shadow Image
         */
        Image {
            id: idSecHandShadowImage
            anchors {
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: prShadowOffsetX * 0.8
                verticalCenter: parent.verticalCenter
                verticalCenterOffset: prShadowOffsetY * 0.8
            }
            source: cppMediaOffAdaptor.clockInformationList[uId].imageSecHandShadow
            visible: (source !== "")
            Behavior on rotation {
                enabled: prEnableHandAnimation
                RotationAnimation { duration: prHandAnimationTime; direction: RotationAnimation.Clockwise; easing.type: prHandAnimationType }
            }
        }
        /*
         * Clock Center round
         */
        Image {
            anchors {
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: prShadowOffsetX
                verticalCenter: parent.verticalCenter
                verticalCenterOffset: prShadowOffsetY
            }
            source: cppMediaOffAdaptor.clockInformationList[uId].imageCenterShadow
            visible: (source !== "")
        }
        /*
         * Clock Hr Hand Image
         */
        Image {
            id: idHrHandImage
            anchors {
                centerIn: parent
            }
            source:cppMediaOffAdaptor.clockInformationList[uId].imageHrHand
            visible: (source !== "")
            Behavior on rotation {
                enabled: prEnableHandAnimation
                RotationAnimation { duration: prHandAnimationTime; direction: RotationAnimation.Clockwise; easing.type: prHandAnimationType }
            }
        }
        /*
         * Clock Min Hand Image
         */
        Image {
            id: idMinHandImage
            anchors {
                centerIn: parent
            }
            source: cppMediaOffAdaptor.clockInformationList[uId].imageMinHand
            visible: (source !== "")
            Behavior on rotation {
                enabled: prEnableHandAnimation
                RotationAnimation { duration: prHandAnimationTime; direction: RotationAnimation.Clockwise; easing.type: prHandAnimationType }
            }
        }
        /*
         * Clock Sec Hand Image
         */
        Image {
            id: idSecHandImage
            anchors {
                centerIn: parent
            }
            source: cppMediaOffAdaptor.clockInformationList[uId].imageSecHand
            visible: (source !== "")
            Behavior on rotation {
                enabled: prEnableHandAnimation
                RotationAnimation { duration: prHandAnimationTime; direction: RotationAnimation.Clockwise; easing.type: prHandAnimationType }
            }
        }
        /*
         * Clock Center round
         */
        Image {
            anchors {
                centerIn: parent
            }
            source: cppMediaOffAdaptor.clockInformationList[uId].imageCenter
            visible: (source !== "")
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * HBText used to show Clock Day
     */
    HBText {
        id: idClockDayText
        anchors {
            top: parent.top
            topMargin: 50
            horizontalCenter: parent.horizontalCenter
        }
        horizontalAlignment: HBText.Center
        verticalAlignment: HBText.Top
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        visible: prShowClockDayText
    }
    /////////////////////////////////////////////////////////////////////////////////
    Connections {
        target: cppDrawersAdaptor
        onSigDateTimeRefresh: refreshClock()
    }
    /////////////////////////////////////////////////////////////////////////////////
    Component.onCompleted: {
        refreshClock()
        if (cppMediaOffAdaptor.clockInformationList[uId].motionType === ClockEnum.MOTION_SWITCH) {
            prEnableHandAnimation = false
        } else {
            prEnableHandAnimation = true
            if (cppMediaOffAdaptor.clockInformationList[uId].motionType === ClockEnum.MOTION_JUMP) {
                prHandAnimationTime = 200
            } else {
                prHandAnimationTime = 1000
            }
        }
    }
}

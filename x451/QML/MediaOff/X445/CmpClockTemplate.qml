/**
 * @file            CmpClockTemplate.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * CmpClockTemplate, a component can use to create clock screens,
 * It has functions to handle touch events.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2

Item {
    //// uId is property to hold clock unique id which is use to display clock layout
    property int uId: index

    //// prShowClockDayText is property used to show clock/day text along with analog ClockEnum
    property bool prShowClockDayText: true

    width: 800
    height: 480

    anchors {
        centerIn: parent.Center
    }

    /**
     * Function to handle clock dial touch press and hold event
     */
    function onClockDialPressAndHold() {
        cppMediaOffApplication.raiseSMEvent("CmpClockTemplate.qml", "onClockDialPressAndHold")
    }

    /**
     * Function to handle clock dial touch release event
     */
    function onClockDialRelease() {
        cppMediaOffApplication.raiseSMEvent("CmpClockTemplate.qml", "onClockDialRelease")
    }
}

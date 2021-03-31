import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import QtGraphicalEffects 1.0

import "../../Common/Popup"
import "../../Common"

//// Doodle My Sticker Icon Sub Element Behavior
BasePopup {

    //// property to handle animation for Icon
    property var prDoodleIconImage: idDoodleIcon

    //// This property holds the height of content item
    contentHeight: height

    //// This property holds the width of content item
    contentWidth: width

    //// Padding is used to set the co-ordinates of Content Item
    topPadding: 0
    leftPadding: 0

    //// contentItem used to maintain doodle icon layout
    contentItem: Item {
        id: idDoodleIcon
    }

    //// This property holds the transition that is applied to the popup item when the popup is opened and enters the screen.
    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: (prIsAnimationRequired) ? 0 : 1
            to: 1
            duration: prShowAnimationDuration
        }

        ScaleAnimator {
            target: prDoodleIconImage
            from: (prIsAnimationRequired) ? 0 : 1
            to: 1
            duration: prShowAnimationDuration
            easing.type: Easing.OutBack
        }

        onRunningChanged: {
            if (!running) {
                cppDrawersApp.qmlLog("base popup enter onRunningChanged end")
                prIsPopupAnimCompleted = true
            } else {
                cppDrawersApp.qmlLog("base popup enter onRunningChanged start")
                prIsPopupAnimCompleted = false
            }
        }
    }

    //// This property holds the transition that is applied to the popup item when the popup is closed and exits the screen.
    exit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1
            to: (prIsAnimationRequired) ? .3 : 1
            duration: prCloseAnimationDuration
        }

        ScaleAnimator {
            target: prDoodleIconImage
            from: 1
            to: (prIsAnimationRequired) ? .3 : 1
            duration: prCloseAnimationDuration
            easing.type: Easing.Linear
        }

        onRunningChanged: {
            if (!running) {
                cppDrawersApp.qmlLog("base popup exit onRunningChanged end")
                sigPopupClosed()
            } else {
                cppDrawersApp.qmlLog("base popup exit onRunningChanged start")
            }
        }
    }
}

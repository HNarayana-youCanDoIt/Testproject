/**
 * @file            CmpTripProgressCircle.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * CmpTripProgressCircle, a comopnent can use to show overall trip rating score on DriveNext main screen,
 * use show a circular filler layout.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: root

    width: size
    height: size

    property int size: 200               // The size of the circle in pixel
    property real arcBegin: 0            // start arc angle in degree
    property real arcEnd: 270            // end arc angle in degree
    property real arcOffset: 0           // rotation
    property bool isPie: false           // paint a pie instead of an arc
    property bool showBackground: false  // a full circle as a background of the arc
    property real lineWidth: 20          // width of the line
    property string colorCircle: "#ffb5b5b5"         // fill color
    property string colorBackground: "#33ffffff"    // background color

    property alias beginAnimation: idAnimationArcBegin.enabled
    property alias endAnimation: idAnimationArcEnd.enabled

    property int animationDuration: 200

    onArcBeginChanged: idCanvas.requestPaint()
    onArcEndChanged: idCanvas.requestPaint()

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Animation for start point value change
     */
    Behavior on arcBegin {
        id: idAnimationArcBegin
        enabled: true
        NumberAnimation {
            duration: root.animationDuration
            easing.type: Easing.InOutCubic
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Animation for end point value change
     */
    Behavior on arcEnd {
        id: idAnimationArcEnd
        enabled: true
        NumberAnimation {
            duration: root.animationDuration
            easing.type: Easing.InOutCubic
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Canvas to draw circular filler
     */
    Canvas {
        id: idCanvas
        anchors.fill: parent
        rotation: -90 + parent.arcOffset

        transform: Scale {
            origin.x: width/2
            origin.y: height/2
            xScale: cppUIBase.screenAspectRatio
        }

        onPaint: {
            var x = width / 2
            var y = height / 2
            var start = Math.PI * (parent.arcBegin / 180)
            var end = Math.PI * (parent.arcEnd / 180)

            var ctx = getContext("2d")
            ctx.reset()

            if (root.isPie) {
                if (root.showBackground) {
                    ctx.beginPath()
                    ctx.fillStyle = root.colorBackground
                    ctx.moveTo(x, y)
                    ctx.arc(x, y, width / 2, 0, Math.PI * 2, false)
                    ctx.lineTo(x, y)
                    ctx.fill()
                }
                ctx.beginPath()
                ctx.fillStyle = root.colorCircle
                ctx.moveTo(x, y)
                ctx.arc(x, y, width / 2, start, end, false)
                ctx.lineTo(x, y)
                ctx.fill()
            } else {
                if (root.showBackground) {
                    ctx.beginPath();
                    ctx.arc(x, y, (width / 2) - parent.lineWidth / 2, 0, Math.PI * 2, false)
                    ctx.lineWidth = root.lineWidth
                    ctx.strokeStyle = root.colorBackground
                    ctx.stroke()
                }
                ctx.beginPath();
                ctx.arc(x, y, (width / 2) - parent.lineWidth / 2, start, end, false)
                ctx.lineWidth = root.lineWidth
                ctx.strokeStyle = root.colorCircle
                ctx.stroke()
            }
        }
    }
}
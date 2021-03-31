import QtQuick 2.0

//Debug purpose rectangle used to mark item area (x,y, width, height) on screen
Rectangle {
    property string prColor : "red"
    anchors.fill: parent
    color: "transparent"
    border.color: prColor
}
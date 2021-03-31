import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.skeletonenums 1.0
import "../Common"

BaseUI {
    anchors.fill: parent

    Label {
        id: idBandText
        x: 222
        width: 300
        height: 38
        text: (SkeletonAdaptor.type === SkeletonEnums.TYPE_DEFAULT) ? "Default" : "Invalid"
        anchors.horizontalCenter: parent.horizontalCenter
        font.weight: Font.Bold
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.topMargin: 75
        font.pixelSize: 22
        color: "white"
    }

    Button {
        text: qsTr("Update value")
        anchors.left: parent.left
        anchors.leftMargin: 350
        anchors.top: parent.top
        anchors.topMargin: 220

        onClicked: {
            SkeletonAdaptor.exampleReq()
        }
    }

    Button {
        text: qsTr("Home")
        anchors.left: parent.left
        anchors.leftMargin: 350
        anchors.top: parent.top
        anchors.topMargin: 350

        onClicked: {
            cppSkeletonApp.raiseSMEvent("Home", "HomeMain")
        }
    }
}

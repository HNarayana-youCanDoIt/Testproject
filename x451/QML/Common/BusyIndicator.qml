import QtQuick 2.2
import QtGraphicalEffects 1.0
import com.harman.qml.thememanager 1.0

Item {
    id: idLoadingComponent

    property alias prLoadingText: idLoadingText.text

    width: 100
    height: 100

    //// Loading fill
    // FixMe: [NK] [QML] fake loading image used need correct assets from TML
    Item {
        id: idAnim

        width: 112
        height: 80

        anchors.centerIn: parent

        smooth: true
        visible: false

        Item {
            anchors.centerIn: parent
            Rectangle {
                width: parent.parent.width
                height: parent.parent.width / 2
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    bottom: parent.top
                }
                color: "white"
            }
            Rectangle {
                width: parent.parent.width / 2
                height: parent.parent.width / 3
                anchors {
                    right: parent.left
                    top: parent.bottom
                }
                color: "grey"
            }

            NumberAnimation on rotation {
                running: idLoadingComponent.visible
                from: 0
                to: 360
                loops: Animation.Infinite
                duration: 1500
            }
        }
    }

    //// Loading logo
    Image {
        id: idLogo

        width: 112
        height: 80

        anchors.centerIn: parent

        smooth: true
        visible: false

        source: "qrc:/image/Common/Loading/Phone_Ico_loading_X451_n.png"
    }

    //// Loading mask
    OpacityMask {
        anchors.fill: idAnim
        source: idAnim
        maskSource: idLogo
    }

    //// Loading text
    HBText {
        id: idLoadingText
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 215
        }
    }
}

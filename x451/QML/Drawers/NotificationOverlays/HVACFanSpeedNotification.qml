import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: idHvacFanBarItem

    width: 200
    height: 76

    Image {
        id: idHvacFanIcon

        anchors {
            top: parent.top
            left: parent.left
        }
        source: "qrc:/image/Drawers/NotificationOverlays/Pop_Ico_FanSpeed_7in_n-assets/Pop_Ico_FanSpeed_n.png"
    }

    ProgressBar {
        id: idHvacFanProgressBar

        from: 0
        to: 7

        value: cppHVACAdaptor.fanSpeed

        anchors {
            left: idHvacFanIcon.right
            leftMargin: -5
            verticalCenter: idHvacFanIcon.verticalCenter
        }

        background: Image {
            id: idProgressBarBgImg
            source: "qrc:/image/Drawers/NotificationOverlays/Gen_Gfx_FanSpeedSlider_7in_n-assets/Gen_Gfx_FanSpeedSlider_nd.png"
        }

        contentItem: Item {

            /*
                 * This is the item which is used to show the progress.
                 * This will show the progress using the white dots.
                 */
            Item {
                id: idProgressBarContentItem

                width: (idHvacFanProgressBar.visualPosition * idProgressBarBgImg.width)
                height: parent.height



                clip: true
                Image {
                    id: idProgressBarImg
                    source: "qrc:/image/Drawers/NotificationOverlays/Gen_Gfx_FanSpeedSlider_7in_n-assets/Gen_Gfx_FanSpeedSlider_Overlay_na.png"
                }
            }
        }

        /*
             * This is the item which is used to show the value of FanSpeed.
             */
        HBText {
            id: idTextFanValue

            width: 43
            height: 34

            anchors {
                left: idHvacFanProgressBar.right
                leftMargin: 10
                verticalCenter: idHvacFanProgressBar.verticalCenter
            }

            text: idHvacFanProgressBar.value
            fontType: ThemeMgr.FONTTYPE_T45_C1_WHITE
        }
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("HvacFanSpeedNotification.qml: Component.onCompleted")
    }
}


import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: idHvacTemperatureBarItem

    width: 450
    height: 76

   Image {
        id: idHvacTemperatureIcon

        anchors {
            top: parent.top
            left: parent.left
        }
        source: "qrc:/image/Drawers/NotificationOverlays/Pop_Ico_Temperature_7in_n-assets/Gen_Drawer_Ico_Temperature_n.png"
    }

    ProgressBar {
        id: idHvacTemperatureProgressBar
        from: cppHVACAdaptor.temperatureLowLimit
        to: cppHVACAdaptor.temperatureHighLimit
        value: cppHVACAdaptor.temperature.toFixed(1)

        anchors {
            left: idHvacTemperatureIcon.right
            leftMargin: -7
            verticalCenter: idHvacTemperatureIcon.verticalCenter
        }

        background: Image {
            id: idProgressBarBgImg
            source: "qrc:/image/Drawers/NotificationOverlays/Gen_Gfx_TemperatureSlider_7in_n-assets/Gen_Gfx_TemperatureSlider_nd.png"
        }

        contentItem: Item {

            /*
                 * This is the item which is used to show the progress.
                 */
            Item {
                id: idProgressBarContentItem

                width: (idHvacTemperatureProgressBar.visualPosition * idProgressBarBgImg.width)
                height: parent.height

                clip: true

                Image {
                    id: idProgressBarImg
                    source: "qrc:/image/Drawers/NotificationOverlays/Gen_Gfx_TemperatureSlider_7in_n-assets/Gen_Gfx_TemperatureSlider_na.png"
                }
            }
        }

        /*
             * This is the item which is used to show the value of temperature.
             */
        HBText {
            id: idTextTemperatureValue

            width: 130
            height: 34

            anchors {
                left: idHvacTemperatureProgressBar.right
                leftMargin: 10
                verticalCenter: idProgressBarBgImg.verticalCenter
            }

            text: (cppHVACAdaptor.temperature.toFixed(1) + qsTr("°C"))+ cppThemeMgr.languageChanged

            fontType: ThemeMgr.FONTTYPE_T35_C3
        }
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("HvacTemperatureOverlay.qml: Component.onCompleted")
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.thememanager 1.0
import QtGraphicalEffects 1.0
import "../Common"

BasePopupNotification{
    id: idRCABMTNotification


    /**
      * Image to hold the Icon related to notification popup
      **/
    Image {
        id: idNotificationPopupIcon

        anchors{
            left: parent.left
            leftMargin: 10
            top: parent.top
            topMargin: 5
        }
        source: "qrc:/image/Popup/Popup_Notification_Icon/Popup_Notification_Ico_Bell_n.png"
    }

    ProgressBar {
        id: idRCABMTProgressBar
        from: -10
        to: 10
        value: cppRCAAdaptor.iBassMidTrebleValue

        anchors{
            left: idNotificationPopupIcon.right
            verticalCenter: idNotificationPopupIcon.verticalCenter
        }

        background: Image {
            id: idProgressBarBgImg
            source: "qrc:/image/RCA/RCA_Ico_BMT_Equilizer_n/Sts_Ico_Equilizer_bg_n.png"
        }

        contentItem: Item {
            anchors.fill: parent

            /*
             * This is the item which is used to show the progress.
             * This will show the progress using the white dots.
             */
            Item {
                id:rightImg
                visible: idRCABMTProgressBar.value > 0 && idRCABMTProgressBar.value <= 10
                width: (idRCABMTProgressBar.value > 0 && idRCABMTProgressBar.value <= 10) ?(idRCABMTProgressBar.value * (idProgressBarBgImg.width/2)/10):idProgressBarBgImg.width/2
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: idProgressBarBgImg.width/2
                clip: true
                Image {
                    source: "qrc:/image/RCA/RCA_Ico_BMT_Equilizer_n/Sts_Equilizer_Overlay_bg_2_n.png"
                }
            }
            Item {
                id:leftImg
                visible: idRCABMTProgressBar.value >= -10 && idRCABMTProgressBar.value < 0
                width: idRCABMTProgressBar.value >= -10 && idRCABMTProgressBar.value < 0 ? (Math.abs(idRCABMTProgressBar.value) * ((idProgressBarBgImg.width/2)/10))  : idProgressBarBgImg.width/2
                height: parent.height
                anchors.right: rightImg.left
                anchors.rightMargin: 1
                clip: true
                Image {
                    id: idProgressBarImg
                    anchors.right: parent.right
                    source: "qrc:/image/RCA/RCA_Ico_BMT_Equilizer_n/Sts_Equilizer_Overlay_bg_1_n.png"
                }
            }
        }
    }

    /**
      * HBText to hold title to be displayed on popup
      **/
    HBText {
        id: idRCABMTText
        width: 223
        height: 19
        anchors{
            left: idRCABMTProgressBar.right
            leftMargin: 10
            verticalCenter: idNotificationPopupIcon.verticalCenter
        }

        elide: HBText.ElideRight

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        text: cppRCAAdaptor.strBassMidTrebleName
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import com.harman.qml.maskedMouseArea 1.0
import com.harman.qml.w3wenum 1.0
import com.harman.qml.thememanager 1.0
import "../Common"


Item {

    /* HBText to show "what3words" in this screen */
    HBText {

        anchors {
            top: parent.top
            topMargin: 38
            horizontalCenter: parent.horizontalCenter
        }

        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: Text.AlignHCenter

        text: qsTr("TEXT_HOME_SHORTCUT_TITLE_W3W") + cppThemeMgr.languageChanged
    }

    /* Image for Play Video Background */
    Image {

        id: idPlayVideoImage

        anchors {
            top: parent.top
            topMargin: 108
            horizontalCenter: parent.horizontalCenter
        }

        source: "qrc:/image/W3W/Gfx_w3w_PlayVideo_n/Gfx_w3w_PlayVideo_n.png"
    }

    /* Mask Image for Play Video Background */
    Image {

        id: idPlayVideoImageMask

        anchors {
            top: parent.top
            topMargin: 108
            horizontalCenter: parent.horizontalCenter
        }

        source: "qrc:/image/W3W/Gfx_w3w_PlayVideo_n/Gfx_w3w_PlayVideo_Mask_n.png"
    }

    OpacityMask {
        anchors.fill: idPlayVideoImage
        source: idPlayVideoImage
        maskSource: idPlayVideoImageMask

        /*
         * This masked mouse area is used to get touch event inside Video thumbnail
         */
        MouseArea{

            anchors.fill: parent

            onReleased: {
                cppUIBase.qmlLog("W3WStartupThirdPage.qml onReleased")
                //Todo[Nishant]: Uncomment below line when W3W Video viewer is implemented
                //cppW3WApplication.raiseSMEvent("LaunchW3WVideoViewerScreen", "")
            }
        }
    }
}

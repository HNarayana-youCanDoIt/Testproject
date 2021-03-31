import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.mediaenum 1.0
import com.harman.qml.audioenums 1.0

BaseUI {
    //FixeMe : Temporary Loading animation. Will be replaced when correct assets are received
    BusyIndicator {
        id: idBusyAnim
        visible: true

        anchors {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
        }
    }

    HBText {
        id: idMediaLoadingTxt
        text: "Reading USB..."
        fontType: ThemeMgr.FONTTYPE_T35_C3

        anchors {
            top: idBusyAnim.bottom
            horizontalCenter: parent.horizontalCenter
        }

        visible: ((AudioEnums.SRC_USB1 === cppAudioAdaptor.activeEntSrc)
                  && (MediaEnum.CONTENTTYPE_U === MediaAdaptor.usbContentType)
                  && (MediaAdaptor.compareMediaOperationState(MediaEnum.MEDIA_OPERATIONSTATE_NONE)))
    }


    Component.onCompleted: {
        if(MediaAdaptor.isNowPlayingDataAvail)
        {
            cppMediaApp.raiseSMEvent("Media","evNowPlayingDataAvailable")
        }
    }
}

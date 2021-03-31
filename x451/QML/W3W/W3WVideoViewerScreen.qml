import QtQuick 2.7
import "../Media"

MediaVideoScreen {

    prVideoScreenTitle.visible: false
    prBrowseBtn.visible: false
    prPreviousBtn.visible: false
    prNextBtn.visible: false

    prCancelBtn.onReleased: {
        cppW3WApplication.qmlLog("W3WVideoViewerScreen.qml : Cancel Button Clicked!")
        cppUIBase.raiseSMEvent("back", "")
        //Switch to Previous Ent.Source when Cancel Button is Relesed
        MediaAdaptor.requestPreviousSource()
    }
}

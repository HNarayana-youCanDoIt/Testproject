import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"

/**
 * Transparent Popup to be displayed over screen when DisplayOff Feature is enabled
 */
BasePopup{
    //No Backgound image required
    prPopupBackground : ""

    /*
     *  Setting height and width of Content item to screen's height and width
     *  This is done to capture touch event on the whole screen.
     */
    contentWidth: 800
    contentHeight: 480

    contentItem: Item{
        anchors.fill: parent

        MouseArea{
            anchors.fill: parent
            //On Press event on Any where on the screen, request to disable DisplayOff Feature
            onPressed: {
                cppDrawersApp.qmlLog("DisplayOffTransparentPopup Pressed.")
                cppDisplayManagerAdaptor.reqDisplayOnOffFeature(false)
            }
        }
    }

    onClosed: {
        cppDrawersApp.qmlLog("DisplayOffTransparentPopup closed.")
        //On Close event of the Popup, request to disable DisplayOff Feature
        cppDisplayManagerAdaptor.reqDisplayOnOffFeature(false)
    }

}

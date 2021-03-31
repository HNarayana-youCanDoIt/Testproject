import QtQuick 2.7
//import "../Drawers/SlideBars"?
import "../Drawers/NotificationOverlays"

/*
 * The volume notification UI window screen which houses the volume overlay
 * It will have the Loader to load the qml files
 */
Item {
    id: idVolNotificationWindow
    objectName: "VolNotificationWindow"
    anchors.fill: parent

    NotificationOverlayLoader{
        anchors.fill: parent
    }

}

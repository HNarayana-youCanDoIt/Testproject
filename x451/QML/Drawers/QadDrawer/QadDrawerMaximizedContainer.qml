import QtQuick 2.7
import "../../Common"
import com.harman.qml.powerenums 1.0

Item {
    id: idQadMaximizeContainer

    /*
     * property holds the state of drawer.
     */
    property string prQadDrawerState: cppDrawersAdaptor.qadDrawerState

    /*
     * System Mute/Unmute button, Mute/Unmute text, Settings shortcut icon and
     * label, Container.
     */
    QadDrawerMaximizedMuteUnMuteContainer {
        id: idQadDrawerMaximizedMuteUnMuteContainer
        width: parent.width
        height: 100

        anchors{
            top: parent.top
            topMargin: 80//70
            left: parent.left
            leftMargin: 10
        }
    }

    /*
     * Display On/Off Container: Which shows Display On/Off Icon, Display toggle
     * button, brightnes slider container.
     */
    QadDrawerMaximizedDisplayOnOffContainer {
        id: idQadDrawerMaximizedDisplayOnOffContainer

        anchors.top: idQadDrawerMaximizedMuteUnMuteContainer.bottom
        width: parent.width
        height: idQadDrawerMaximizedMuteUnMuteContainer.height
    }

    /*
     * Item to show the current active entertainment source Information:
     * Active Source Icon, Active Source Info: like frequency, Song title,
     * next, previous, play/pause buttons.
     */
    QadDrawerMaximizedEntertainmentSourceInfoContainer {
        id: idEntertainmentSourceInfoContainer

        width: parent.width
        height: idQadDrawerMaximizedDisplayOnOffContainer.height

        anchors.top: idQadDrawerMaximizedDisplayOnOffContainer.bottom

        enabled: !cppPhoneAdaptor.doesCallExist
    }

    /*
     * Connected phone info: Connected profile icon, Connected phone name,
     * seprator line, notifications like Missed call.
     */
    QadDrawerMaximizedConnectedPhoneInfoContainer {
        id: idConnectedPhoneInfoContainer

        width: parent.width
        height: idQadDrawerMaximizedDisplayOnOffContainer.height

        anchors.top: idEntertainmentSourceInfoContainer.bottom


        visible: ( !cppAndroidAutoAdaptor.androidAutoConnectionStatus &&
                  !cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus )

        enabled: !cppPhoneAdaptor.doesCallExist
    }

    /*
     * Connected Projection info: icon and Label info: Like if android auto
     * is connected, then Android Auto Icon and if CarPlay is connected carPlay
     * Icon, Apple CarPlay Label and Sub Label with connected phone name.
     */
    QadDrawerMaximizedProjectionInfoContainer {
        id: idProjectionInfoContainer

        anchors.top: idEntertainmentSourceInfoContainer.bottom
        width: parent.width
        height: idQadDrawerMaximizedDisplayOnOffContainer.height

        visible: ( cppAndroidAutoAdaptor.androidAutoConnectionStatus ||
                  cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus )

    }

    /*
     * This Mouse area is used to block the touch during maximize/minimize
     * animation is running.
     */
    MouseArea{
        id: idQADDrawerMouseAreaToBlockTheTouchDuringAnimation

        anchors.fill: parent

        enabled: (prIsQadMinimizeAnimationRunning || prIsQadMaximizeAnimationRunning)

        onClicked: {
            cppDrawersApp.qmlLog("QadDrawerMaximizedContainer.qml: Minimize or Maximize animation is running so No action.")
        }
    }
}

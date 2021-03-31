import QtQuick 2.7
import "../../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.drawersenums 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.powerenums 1.0

Item {
    id: idQADMinimizedContainerItem

    width: (parent ? parent.width : 0)
    height: (parent ? parent.height : 0)

    anchors{
        left: (parent ? parent.left : undefined)
        leftMargin: 770
        top: (parent ? parent.top : undefined)
        topMargin: 70
    }

    Loader {

        anchors {
            left: parent.left
            leftMargin: -3
            top: parent.top
            topMargin: 123
        }

        source: "qrc:/QML/Drawers/QadDrawer/X445/QadDrawerMinimizedVolumeSliderContainer.qml"
    }

    /*
     * Open QAD button to maximize the QAD drawer.
     */
    GenericButton {

        width: 90
        height: 160

        anchors{
            left: parent.left
            leftMargin: 47
            top: parent.top
            topMargin: 247
        }

        defaultImageURL: "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Btn_LeftOpen_SmallDrawer_7in_n-assets/Drw_Btn_LeftOpen_SmallDrawer_7in_na.png"
        pressedImageURL: "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Btn_LeftOpen_SmallDrawer_7in_n-assets/Drw_Btn_LeftOpen_SmallDrawer_7in_nf.png"
        disabledImageURL: "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Btn_LeftOpen_SmallDrawer_7in_n-assets/Drw_Btn_LeftOpen_SmallDrawer_7in_nd.png"

        onPressed: {
            cppDrawersApp.qmlLog("QadDrawerMinimizedContainer.qml: Open QAD Button pressed.")
            cppVRAdaptor.invDeactivateVRSession(HardkeyEnum.HKEY_STATE_RELEASED)
        }

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMinimizedContainer.qml: Open QAD Button released.")
            cppDrawersApp.raiseSMEvent("QadDrawer",
                                       DrawersEnums.QAD_DRAWER_OPEN_BUTTON_ID)
        }

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
            cppDrawersApp.qmlLog("QadDrawerMinimizedContainer.qml: Minimize or Maximize animation is running so No action.")
        }
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog(
                    "QadDrawerMiniMizeContainer.qml: Component.onCompleted:.")
    }
}

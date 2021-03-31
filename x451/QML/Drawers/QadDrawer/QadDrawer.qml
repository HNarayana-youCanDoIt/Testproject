import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.drawersenums 1.0
import com.harman.qml.maskedMouseArea 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.variantcontrolenums 1.0
import "../../Common"

Item {
    id: idQADDrawer

    width: idQadDrawerBgImage.width
    height: parent.height

    anchors {
        left: parent.left
        leftMargin: prInitialLeftMargin
        top: parent.top
    }

    /*
     * Right Margin of drawer when it is in Hidden state.
     */
    property int prInitialLeftMargin: -width

    /*
     * Minimize Left Margin of drawer:
     * Total width of Item - Minimize Items Width -(900 - 120)
     */
    property int prMinimizeLeftMargin: -780

    /*
     * Maximize Left Margin of drawer:
     */
    property int prMaximizeLeftMargin: 0

    /*
     * Minimize Container loader Item width.
     */
    property int prQadDrawerMinimizedContainerLoaderWidth: 120

    /*
     * Minimize Container loader Item Height.
     */
    property int prQadDrawerMinimizedContainerLoaderHeight: 410

    /*
     * The LeftMargin of Background image in Minimized state of drawer.
     */
    property int prQadDrawerBgImageMinimizedLeftMargin: 0

    /*
     * The LeftMargin of Background image in Maximized state of drawer.
     */
    property int prQadDrawerBgImageMaximizedLeftMargin: -156

    /*
     * property holds the status of maximized state.
     */
    property bool prIsQadDrawerMaximizedState: false

    /*
     * property holds the status of maximize animation of QAD.
     */
    property bool prIsQadMaximizeAnimationRunning: false

    /*
     * property holds the status of minimize animation of QAD.
     */
    property bool prIsQadMinimizeAnimationRunning: false

    /* Alias of QAD Minimize Animation. */
    property alias idQadMinimizeAnimation: idQadMinimizeAnimation

    /* Alias of QAD Maximize Animation. */
    property alias idQadMaximizeAnimation: idQadMaximizeAnimation

    /* Alias of QAD container loader. */
    property alias idQadDrawerContainerLoader: idQadDrawerContainerLoader

    /*
     * state of QAD drawer.
     */
    state: cppDrawersAdaptor.qadDrawerState

    onStateChanged: {
        cppDrawersApp.qmlLog("QadDrawer.qml: onStateChanged: state: " + state)
        prIsQadDrawerMaximizedState = (idQADDrawer.state === "Maximized")
    }

    /*
     * Function Which is called Whenever, QadDrawer Maximized Item clicked,
     * means if HMI wants to change the state to Minimize.
     */
    function maxDrawerClicked() {
        cppDrawersApp.qmlLog("QadDrawer.qml: maxDrawerClicked.")
        if (prIsQadDrawerMaximizedState) {
            cppDrawersApp.raiseSMEvent("QadDrawer",
                                       DrawersEnums.QAD_DRAWER_CLOSE_BUTTON_ID)
        } else {


            // Do nothing.
        }
    }

    /*
     * Function Which is called Whenever, QadDrawer Maximized close timer needs
     * to reset
     */
    function resetMaxDrawerCloseTimer(){
        if (prIsQadDrawerMaximizedState) {
            cppDrawersApp.raiseSMEvent("Drawers",
                                       DrawersEnums.DRAWER_COMMON_EVENT_CLOSE_TIMER_RESET)
        } else {
            // Do nothing.
        }
    }

    /*
     * This mouse area will be used to close the drawer if user click outside
     * of the drawer. This will get mouse event only if user touches outside of
     * the Drawer's Image. This happens because of MaskedMouseArea
     */
    MouseArea{
        id: idQadMaxDrawerMouseArea

        anchors.fill: parent

        enabled: (!prIsQadMinimizeAnimationRunning && !prIsQadMaximizeAnimationRunning
                  && prIsQadDrawerMaximizedState)

        onClicked: {
            maxDrawerClicked()
        }
    }

    /*
     * BackGround image of drawer.
     */
    Image {
        id: idQadDrawerBgImage
        source: cppThemeMgr.themeTypeFolderPath + "Qad_Max_Bg.png"

        anchors{
            left: parent.left
            leftMargin: prInitialLeftMargin
        }
    }

    MouseArea {
        id: idQadContainerBackground
        width: 500
        height: 415
        anchors
        {
            top: parent.top
            topMargin: 65
            left: parent.left
        }
    }

    /*
     * This loader loads the Items which HMI needs to show on Minimize/Maximize
     * QAD drawer.
     */
    Loader {
        id: idQadDrawerContainerLoader

        width: (prIsQadDrawerMaximizedState) ? parent.width : prQadDrawerMinimizedContainerLoaderWidth
        height: (prIsQadDrawerMaximizedState) ? parent.height : prQadDrawerMinimizedContainerLoaderHeight

        property bool prbIsMinimizedDrawerPressed: false

        onStatusChanged:
        {
            if (idQadDrawerContainerLoader.status != Loader.Null && idQadDrawerContainerLoader.status === Loader.Ready)
            {
                if (idQadDrawerContainerLoader.source === "qrc:/QML/Drawers/QadDrawer/QadDrawerMinimizedContainer.qml" ||
		        idQadDrawerContainerLoader.source === "qrc:/QML/Drawers/QadDrawer/X445/QadDrawerMinimizedContainer.qml" ||
                        idQadDrawerContainerLoader.source === "")
                {
                    idQadDrawerContainerLoader.item.objectName = "Drawers.qml"
                    cppIntrospectionAdaptor.invSetDrawerChanged(idQadDrawerContainerLoader.item.objectName)
                }
                else
                {
                    idQadDrawerContainerLoader.item.objectName =  cppIntrospectionAdaptor.invExtractFileName(idQadDrawerContainerLoader.source);
                    cppIntrospectionAdaptor.invSetDrawerChanged(idQadDrawerContainerLoader.item.objectName)
                }

                cppDrawersApp.qmlLog("idQadDrawerContainerLoader.item.objectName: " + idQadDrawerContainerLoader.item.objectName)
            }
        }

        source: "qrc:/QML/Drawers/QadDrawer/X445/QadDrawerMinimizedContainer.qml"
    }

    /*
     * Close button Which will close the maximized QAD drawer.
     */
    GenericButton {
        id: idQadDrawerCloseButton

        width: 90
        height: 160

        anchors {
            left: parent.left
            leftMargin: 663
            top: parent.top
            topMargin: 317
        }

        visible: prIsQadDrawerMaximizedState

        enabled: (!prIsQadMinimizeAnimationRunning && !prIsQadMaximizeAnimationRunning)

        opacity: 0

        defaultImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/CloseButtonIcon/Gen_Drawer_Button_Close_n.png"
        pressedImageURL: "qrc:/image/Drawers/QAD/Maximized/Contents/CloseButtonIcon/Gen_Drawer_Button_Close_nf.png"


        onReleased: {
            maxDrawerClicked()
        }
    }

    states: [
        State {
            name: "Minimized"

            PropertyChanges {
                target: idQADDrawer
                anchors.leftMargin: (idShowDrawersWithAnimation.running) ? idQADDrawer.anchors.leftMargin : prMinimizeLeftMargin
            }

            PropertyChanges {
                target: idQadDrawerBgImage
                anchors.leftMargin: prQadDrawerBgImageMinimizedLeftMargin
            }
        },
        State {
            name: "Maximized"

            PropertyChanges {
                target: idQADDrawer
                anchors.leftMargin: prMaximizeLeftMargin
            }

            PropertyChanges {
                target: idQadDrawerBgImage
                anchors.leftMargin: prQadDrawerBgImageMaximizedLeftMargin
            }
        }
    ]

    transitions: [
        Transition {

            from: "Maximized"
            to: "Minimized"

            PropertyAnimation {
                id: idQadMinimizeAnimation

                property: "anchors.leftMargin"
                duration: cppDrawersAdaptor.drawersMaximizeMinimizeAnimationDuration
                easing.type: Easing.OutQuad//Easing.InOutBack
            }

            onRunningChanged: {

                if (!running) {
                    cppDrawersApp.qmlLog("QadDrawer.qml: Qad Drawer's Minimize Animation stopped.")
                    prIsQadMinimizeAnimationRunning = false
                    idQADDrawer.z = 0

                    idQadDrawerContainerLoader.source = "qrc:/QML/Drawers/QadDrawer/X445/QadDrawerMinimizedContainer.qml"

                    if ("HideDrawersWithoutAnimation" === idDrawersMain.state)
                    {
                        idQADDrawer.anchors.leftMargin = prInitialLeftMargin
                    }
                    else
                    {
                        // Do nothing.
                    }
                } else {
                    cppDrawersApp.qmlLog("QadDrawer.qml: Qad Drawer's Minimize Animation started.")
                    prIsQadMinimizeAnimationRunning = true
                    idQadDrawerCloseButton.opacity = 0
                }
            }
        },
        Transition {
            from: "Minimized"
            to: "Maximized"

            PropertyAnimation {
                id: idQadMaximizeAnimation

                property: "anchors.leftMargin"
                duration: cppDrawersAdaptor.drawersMaximizeMinimizeAnimationDuration
                easing.type: Easing.OutQuad
                //easing.type: Easing.InOutBack
            }

            onRunningChanged: {

                if (running) {
                    cppDrawersApp.qmlLog("QadDrawer.qml: Qad Drawer's Maximize Animation started.")
                    prIsQadMaximizeAnimationRunning = true
                    idQADDrawer.z = 1
                    idQadDrawerContainerLoader.source
                            = "qrc:/QML/Drawers/QadDrawer/QadDrawerMaximizedContainer.qml"
                } else {
                    cppDrawersApp.qmlLog("QadDrawer.qml: Qad Drawer's Maximize Animation stoped.")
                    prIsQadMaximizeAnimationRunning = false
                    idQadDrawerCloseButton.opacity = 1
                }
            }
        }
    ]
}

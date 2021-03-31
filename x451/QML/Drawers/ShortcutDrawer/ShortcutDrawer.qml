import QtQuick 2.7
import com.harman.qml.drawersenums 1.0
import "../../Common"
import QtQuick.Particles 2.0
import com.harman.qml.maskedMouseArea 1.0
import com.harman.qml.variantcontrolenums 1.0
import com.harman.qml.hvacenums 1.0


Item {
    id: idShortcutDrawer

    /*
     * This width is calculated because we are creating large Item then the
     * screen, because during bounce animation some blank space seen in right
     * side of screen. so we are adding extra width to this item. like: 800 + 76
     */
    width: (parent.width + prExtraWidthForBounceEffect)
    height: parent.height

    anchors {
        right: parent.right
        rightMargin: prInitialRightMargin
    }

    /*
     * property to hold the extra width which is requierd for bounce iffect.
     */
    property int prExtraWidthForBounceEffect: 56

    /*
     * Right Margin of drawer when it is in Hidden state.
     */
    property int prInitialRightMargin: -width

    /*
     * Minimize right margin of drawer:
     * Total width of Item - Minimize Items Width -(856 - 130)
     */
    property int prMinimizeRightMargin: -726

    /*
     * Maximize right margin of drawer:
     * -extrawidth
     */
    property int prMaximizeRightMargin: -prExtraWidthForBounceEffect

    /*
     * Minimize container loader right margin.
     * Total width of Item - Minimize Items Width (856 - 130)
     */
    property int prMinimizeContainerLoaderRightMargin: 716

    /*
     * Maximized container loader right margin.
     */
    property int prMaximizeContainerLoaderRightMargin: -56

    /*
     * Maximized container loader top margin.
     */
    property int prMaximizeContainerLoaderTopMargin: 0

    /*
     * Minimized container loader top margin.
     */
    property int prMinimizeContainerLoaderTopMargin: 45

    /*
     * Shortcut drawer's minimzed container items width.
     */
    property int prShortcutDrawerMinimizedContainerLoaderWidth: 120

    /*
     * Shortcut drawer's minimzed container items height.
     */
    property int prShortcutDrawerMinimizedContainerLoaderHeight: 435

    /*
     * The rightMargin of Background image in Minimized state of drawer.
     */
    property int prShortcutDrawerBgImageMinimizeRightMargin: prExtraWidthForBounceEffect

    /*
     * The rightMargin of Background image in Maximized state of drawer.
     */
    property int prShortcutDrawerBgImageMaximizeRightMargin: -prExtraWidthForBounceEffect

    /*
     * property holds the state of source drawer.
     */
    property string prSrcDrawerState: cppDrawersAdaptor.srcDrawerState

    /*
     * property holds the state of HVAC drawer.
     */
    property string prHvacDrawerState: cppDrawersAdaptor.hvacDrawerState

    /*
     * property holds the status of maximized state.
     */
    property bool prIsShortcutDrawerMaximizedState: false

    /*
     * property holds the status of maximize animation of Shortcut Drawer.
     */
    property bool prIsShortcutDrawerMaximizeAnimationRunning: false

    /*
     * property holds the status of minimize animation of Shortcut Drawer.
     */
    property bool prIsShortcutDrawerMinimizeAnimationRunning: false

    /* Alias of Shortcut Drawer Minimize Animation. */
    property alias idShortcutMinimizeAnimation: idShortcutMinimizeAnimation

    /* Alias of Shortcut Drawer Maximize Animation. */
    property alias idShortcutMaximizeAnimation: idShortcutMaximizeAnimation

    state: cppDrawersAdaptor.shortcutDrawerState

    onStateChanged: {
        cppDrawersApp.qmlLog(
                    "ShortcutDrawer.qml: onStateChanged: state: " + state)
        prIsShortcutDrawerMaximizedState = (idShortcutDrawer.state === "Maximized")
        if (prIsShortcutDrawerMaximizedState)
        {
            if (prSrcDrawerState === "Maximized") {
                prShortcutDrawerBgImageMaximizeRightMargin = -161
                prMaximizeContainerLoaderRightMargin = -161
            }
            else if (prHvacDrawerState === "Maximized")
            {
                prShortcutDrawerBgImageMaximizeRightMargin = (cppHVACAdaptor.hvacContainerType === HVACEnums.EN_CONTAINER_TYPE_DUAL_ZONE)
                        ? -prExtraWidthForBounceEffect : -125
                prMaximizeContainerLoaderRightMargin = (cppHVACAdaptor.hvacContainerType === HVACEnums.EN_CONTAINER_TYPE_DUAL_ZONE)
                        ? 56 : -125
            }
            else
            {
                // Do nothing.
            }
        }
        else
        {
            // Do nothing.
        }
    }

    Connections
    {
        target: cppHVACAdaptor
        onSigHVACContainerTypeUpdated:
        {
            cppDrawersApp.qmlLog("ShortcutDrawer.qml: onSigHVACContainerTypeUpdated")
            maxDrawerClicked()
        }
    }

    /*
     * Function Which is called Whenever, ShortcutDrawer Maximized Item clicked,
     * means if HMI wants to change the state to Minimize.
     */
    function maxDrawerClicked() {
        cppDrawersApp.qmlLog("ShortcutDrawer.qml: maxDrawerClicked.")
        if (prIsShortcutDrawerMaximizedState) {
            cppDrawersApp.raiseSMEvent(
                        "SourceDrawer",
                        DrawersEnums.SOURCE_DRAWER_CLOSE_BUTTON_ID)
        } else {


            // Do nothing.
        }
    }

    /*
     * Function Which is called Whenever, QadDrawer Maximized close timer needs
     * to reset
     */
    function resetMaxDrawerCloseTimer(){
        if (prIsShortcutDrawerMaximizedState) {
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
        id: idShortcutMaxDrawerMouseArea

        anchors.fill: parent

        enabled: (!prIsShortcutDrawerMaximizeAnimationRunning && !prIsShortcutDrawerMinimizeAnimationRunning
                  && prIsShortcutDrawerMaximizedState)

        onClicked: {
            cppDrawersApp.qmlLog("ShortcutDrawer.qml: Out side Mouse Area clicked.")
            maxDrawerClicked()
        }
    }

    /*
     * BackGround image of drawer.
     */
    Image {
        id: idShortcutDrawerBgImg

        anchors {
            right: parent.right
            rightMargin: prShortcutDrawerBgImageMinimizeRightMargin
        }

        source: cppThemeMgr.themeTypeFolderPath + "Right_Drawer_Max_Bg.png"

        MaskedMouseArea {
            id: idQADDrawerImageMouseArea

            enabled: (!prIsShortcutDrawerMaximizeAnimationRunning && !prIsShortcutDrawerMinimizeAnimationRunning)
            anchors.fill: parent
            alphaThreshold: 0.4
            maskSource: idShortcutDrawerBgImg.source

            onReleased:
            {
                cppDrawersApp.qmlLog("ShortcutDrawer.qml: Masked Mouse Area touch released.")
                //HMI shall close the Source drawer if it is in maximised state
                if (prIsShortcutDrawerMaximizedState)
                {
                    maxDrawerClicked()
                }
                else
                {
                    //Do nothing
                }
            }
        }
    }

    /*
     * This loader loads the Items which HMI needs to show on Minimize/Maximize
     * ShortcutDrawer.
     */
    Loader {
        id: idShortcutDrawerContainerLoader

        width: (prIsShortcutDrawerMaximizedState) ? 800/*parent.width*/ : prShortcutDrawerMinimizedContainerLoaderWidth
        height: (prIsShortcutDrawerMaximizedState) ? parent.height : prShortcutDrawerMinimizedContainerLoaderHeight

        anchors {
            right: parent.right
            rightMargin: prMinimizeContainerLoaderRightMargin
            top: parent.top
            topMargin: prMinimizeContainerLoaderTopMargin
        }

        source: "qrc:/QML/Drawers/ShortcutDrawer/X445/ShortcutDrawerContainerItem.qml"


        onStatusChanged:
        {
            if (idShortcutDrawerContainerLoader.status !== Loader.Null && idShortcutDrawerContainerLoader.status === Loader.Ready)
            {
                if (idShortcutDrawerContainerLoader.source == "qrc:/QML/Drawers/ShortcutDrawer/ShortcutDrawerContainerItem.qml" ||
                        idShortcutDrawerContainerLoader.source == "qrc:/QML/Drawers/ShortcutDrawer/X445/ShortcutDrawerContainerItem.qml" ||
                        idShortcutDrawerContainerLoader.source == "")
                {
                    idShortcutDrawerContainerLoader.item.objectName = "Drawers.qml"
                    cppIntrospectionAdaptor.invSetDrawerChanged(idShortcutDrawerContainerLoader.item.objectName)
                }
                else
                {
                    idShortcutDrawerContainerLoader.item.objectName = cppIntrospectionAdaptor.invExtractFileName(idShortcutDrawerContainerLoader.source);
                    cppIntrospectionAdaptor.invSetDrawerChanged(idShortcutDrawerContainerLoader.item.objectName)
                }
            }
        }
    }

    /*
     * Close button Which will close the maximized Shortcut drawer.
     */
    GenericButton {
        id: idCloseButton

        anchors {
            left: parent.left
            leftMargin: (prSrcDrawerState === "Maximized")
                        ? 201
                        : (cppHVACAdaptor.hvacContainerType !== HVACEnums.EN_CONTAINER_TYPE_DUAL_ZONE)
                          ? 165 : 95
            top: parent.top
            topMargin: 37
        }
        width: 90
        height: 160

        visible: false

        defaultImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Btn_RightClose_7in_n-assets/Gen_Drawer_Button_Close_n.png"
        pressedImageURL: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Btn_RightClose_7in_n-assets/Gen_Drawer_Button_Close_nf.png"


        onReleased: {
            cppDrawersApp.qmlLog("ShortcutDrawer.qml: Close Button Released.")
            maxDrawerClicked()
        }
    }

    states: [
        State {
            name: "Minimized"

            PropertyChanges {
                target: idShortcutDrawer
                anchors.rightMargin: (idShowDrawersWithAnimation.running) ? idShortcutDrawer.anchors.rightMargin : prMinimizeRightMargin
            }

            PropertyChanges {
                target: idShortcutDrawerBgImg
                anchors.rightMargin: prShortcutDrawerBgImageMinimizeRightMargin
            }
        },
        State {
            name: "Maximized"

            PropertyChanges {
                target: idShortcutDrawer
                anchors.rightMargin: prMaximizeRightMargin
            }

            PropertyChanges {
                target: idShortcutDrawerBgImg
                anchors.rightMargin: prShortcutDrawerBgImageMaximizeRightMargin
            }
        }
    ]

    transitions: [
        Transition {

            from: "Maximized"
            to: "Minimized"

            PropertyAnimation {
                id: idShortcutMinimizeAnimation
                property: "anchors.rightMargin"
                duration: cppDrawersAdaptor.drawersMaximizeMinimizeAnimationDuration
                easing.type: Easing.OutQuad//Easing.InOutBack
            }
            onRunningChanged: {

                if (!running) {
                    cppDrawersApp.qmlLog(
                                "ShortcutDrawer.qml: Shortcut Drawer's Minimize Animation stopped.")

                    idShortcutDrawer.z = 0
                    prIsShortcutDrawerMinimizeAnimationRunning = false
                    idShortcutDrawerContainerLoader.source = "qrc:/QML/Drawers/ShortcutDrawer/X445/ShortcutDrawerContainerItem.qml"
                    idShortcutDrawerContainerLoader.anchors.rightMargin
                            = prMinimizeContainerLoaderRightMargin
                    idShortcutDrawerContainerLoader.anchors.topMargin
                            = prMinimizeContainerLoaderTopMargin

                    if ("HideDrawersWithoutAnimation" === idDrawersMain.state || "HideDrawersWithAnimation" === idDrawersMain.state)
                    {
                        idShortcutDrawer.anchors.rightMargin = prInitialRightMargin
                    }
                    else
                    {
                        // Do nothing.
                    }
                } else {
                    cppDrawersApp.qmlLog(
                                "ShortcutDrawer.qml: Shortcut Drawer's Minimize Animation started.")

                    idCloseButton.visible = false
                    prIsShortcutDrawerMinimizeAnimationRunning = true
                }
            }
        },
        Transition {

            from: "Minimized"
            to: "Maximized"

            PropertyAnimation {
                id: idShortcutMaximizeAnimation

                property: "anchors.rightMargin"
                duration: cppDrawersAdaptor.drawersMaximizeMinimizeAnimationDuration
                easing.type: Easing.OutQuad//Easing.InOutBack
            }
            onRunningChanged: {

                if (running) {
                    cppDrawersApp.qmlLog(
                                "ShortcutDrawer.qml: Shortcut Drawer's Maximize Animation started.")

                    idShortcutDrawer.z = 1
                    prIsShortcutDrawerMaximizeAnimationRunning = true
                    if (prSrcDrawerState === "Maximized") {
                        idShortcutDrawerContainerLoader.source
                                = "qrc:/QML/Drawers/ShortcutDrawer/SourceDrawer/SrcDrawer.qml"
                    } else {
                        idShortcutDrawerContainerLoader.source
                                = "qrc:/QML/Drawers/ShortcutDrawer/HvacDrawer/HvacDrawer.qml"
                    }

                    idShortcutDrawerContainerLoader.anchors.rightMargin
                            = prMaximizeContainerLoaderRightMargin
                    idShortcutDrawerContainerLoader.anchors.topMargin
                            = prMaximizeContainerLoaderTopMargin
                } else {
                    cppDrawersApp.qmlLog(
                                "ShortcutDrawer.qml: Shortcut Drawer's Maximize Animation stoped.")
                    prIsShortcutDrawerMaximizeAnimationRunning = false
                    idCloseButton.visible = true
                }
            }
        }
    ]
}

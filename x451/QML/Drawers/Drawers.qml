import QtQuick 2.7
import "HeaderStatusBar"
import "QadDrawer"
import "ShortcutDrawer"
import com.harman.qml.phoneenum 1.0
import com.harman.qml.variantcontrolenums 1.0
import com.harman.qml.powerenums 1.0

Item {
    id: idDrawersMain
    anchors.fill: parent

    state: cppDrawersAdaptor.drawersState

    onStateChanged: {
        cppDrawersApp.qmlLog(
                    "Drawers.qml: Drawer's state changed: state: " + state)

        if (state == "HideDrawersWithAnimation" || state == "HideDrawersWithoutAnimation" || state == "Hidden")
        {
            cppIntrospectionAdaptor.invSetDrawerChanged("No drawers")
        }
        else if(state == "ShowDrawersWithAnimation" || state == "ShowDrawersWithoutAnimation")
        {
            cppIntrospectionAdaptor.invSetDrawerChanged("Drawers.qml")
            idQadDrawer.idQadDrawerContainerLoader.source = "qrc:/QML/Drawers/QadDrawer/X445/QadDrawerMinimizedContainer.qml"
        }
        else
        {
         // do nothing
        }

        if ("HideDrawersWithoutAnimation" === state)
        {
            idQadDrawer.idQadMaximizeAnimation.stop()
            idQadDrawer.idQadMinimizeAnimation.stop()
            idShortcutDrawer.idShortcutMaximizeAnimation.stop()
            idShortcutDrawer.idShortcutMinimizeAnimation.stop()
        }
        else
        {
            // Do nothing.
        }
    }


    /*
     * Maximized Drawer Background overlay: This makes background dim.
     */
    Image {
        id: idMaxDrawerOverlayBgImage

        visible: (
                     (
                         idDrawersMain.state !== "HideDrawersWithAnimation" &&
                         idDrawersMain.state !== "HideDrawersWithoutAnimation"
                         ) &&
                     (
                         idQadDrawer.prIsQadDrawerMaximizedState ||
                         idShortcutDrawer.prIsShortcutDrawerMaximizedState
                         )
                     )
        z: 1

        source: "qrc:/image/Drawers/Gen_Gfx_PopupOverlayBg_7in_n-assets/Gen_Gfx_PopupOverlayBg_n.png"
    }

    /*
     * QAD Drawer (Left Drawer)
     */
    QadDrawer {
        id: idQadDrawer

        visible: ("HideDrawersWithoutAnimation" !== idDrawersMain.state)

        enabled: !(cppPhoneAdaptor.doesCallExist && cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus)
    }

    /*
     * ShortcutDrawer (Right Drawer): This drawer contains, Home Button,
     * Source Button, ParkAssist Button and Climate Button. When user will
     * click on Source button Source maximized drawer will be visible with
     * animation and on click on Climate button, HVAC drawer will be visible
     * with animation.
     */
    ShortcutDrawer {
        id: idShortcutDrawer

        visible: ("HideDrawersWithoutAnimation" !== idDrawersMain.state)

        enabled: !cppPhoneAdaptor.doesCallExist
    }

    /*
     * HeaderStatusBar (Top Status Bar): This will show the informations of system,
     * Like System Time, Current playing source info, temperature, Fan Speed, other
     * notifications etc....
     */
    HeaderStatusBar {
        id: idHeaderStatusBar

        /* Show status bar on screen only when allowStatusBarOnScreen is true */
        visible: cppDrawersAdaptor.allowStatusBarOnScreen
    }

    states: [
        State {
            name: "ShowDrawersWithAnimation"

            PropertyChanges {
                target: idQadDrawer
                anchors.leftMargin: idQadDrawer.prMinimizeLeftMargin
            }
            PropertyChanges {
                target: idShortcutDrawer
                anchors.rightMargin: idShortcutDrawer.prMinimizeRightMargin
            }
            PropertyChanges {
                target: idHeaderStatusBar
                anchors.topMargin: 0
            }
        },
        State {
            name: "ShowDrawersWithoutAnimation"

            PropertyChanges {
                target: idQadDrawer
                anchors.leftMargin: idQadDrawer.prMinimizeLeftMargin
            }
            PropertyChanges {
                target: idShortcutDrawer
                anchors.rightMargin: idShortcutDrawer.prMinimizeRightMargin
            }
            PropertyChanges {
                target: idHeaderStatusBar
                anchors.topMargin: 0
            }
        },
        State {
            name: "HideDrawersWithAnimation"

            PropertyChanges {
                target: idQadDrawer
                anchors.leftMargin: idQadDrawer.prInitialLeftMargin
            }
            PropertyChanges {
                target: idShortcutDrawer
                anchors.rightMargin: idShortcutDrawer.prInitialRightMargin
            }
            PropertyChanges {
                target: idHeaderStatusBar
                /* Do not hide Status bar in Media Off mode */
                anchors.topMargin: ((PowerModeEnums.VPM_MEDIA_OFF === cppPowerModeAdaptor.powerMode) && !(cppParkAssistAdaptor.reverseGearStatus))
                                   ? 0 : -idHeaderStatusBar.height
            }
        },
        State {
            name: "HideDrawersWithoutAnimation"
            PropertyChanges {
                target: idQadDrawer
                anchors.leftMargin: idQadDrawer.prInitialLeftMargin
            }
            PropertyChanges {
                target: idShortcutDrawer
                anchors.rightMargin: idShortcutDrawer.prInitialRightMargin
            }
            PropertyChanges {
                target: idHeaderStatusBar
                anchors.topMargin: ((PowerModeEnums.VPM_MEDIA_OFF === cppPowerModeAdaptor.powerMode) && !(cppParkAssistAdaptor.reverseGearStatus))
                                   ? 0 : -idHeaderStatusBar.height
            }
        }
    ]

    transitions: [
        Transition {
            id: idShowDrawersWithAnimation
            /*
             * ShowDrawers with animation and Hide drawers with animation
             */
            PropertyAnimation {
                property: "anchors.leftMargin"
                duration: cppDrawersAdaptor.drawersShowHideAnimationDuration
            }

            PropertyAnimation {
                property: "anchors.rightMargin"
                duration: cppDrawersAdaptor.drawersShowHideAnimationDuration
            }

            PropertyAnimation {
                property: "anchors.topMargin"
                duration: cppDrawersAdaptor.drawersShowHideAnimationDuration
            }
        },
        Transition {
            from: "ShowDrawersWithAnimation"
            to: "HideDrawersWithoutAnimation"
            PropertyAnimation {
                property: "anchors.leftMargin"
                duration: 0
            }

            PropertyAnimation {
                property: "anchors.rightMargin"
                duration: 0
            }
            PropertyAnimation {
                property: "anchors.topMargin"
                duration: 0
            }
        },
        Transition {
            from: "ShowDrawersWithoutAnimation"
            to: "HideDrawersWithoutAnimation"
            PropertyAnimation {
                property: "anchors.leftMargin"
                duration: 0
            }

            PropertyAnimation {
                property: "anchors.rightMargin"
                duration: 0
            }
            PropertyAnimation {
                property: "anchors.topMargin"
                duration: 0
            }
        },
        Transition {
            from: "Hidden"
            to: "ShowDrawersWithoutAnimation"
            PropertyAnimation {
                property: "anchors.leftMargin"
                duration: 0
            }

            PropertyAnimation {
                property: "anchors.rightMargin"
                duration: 0
            }

            PropertyAnimation {
                property: "anchors.topMargin"
                duration: 0
            }
        },
        Transition {
            from: "HideDrawersWithoutAnimation"
            to: "ShowDrawersWithoutAnimation"
            PropertyAnimation {
                property: "anchors.leftMargin"
                duration: 0
            }

            PropertyAnimation {
                property: "anchors.rightMargin"
                duration: 0
            }

            PropertyAnimation {
                property: "anchors.topMargin"
                duration: 0
            }
        },
        Transition {
        from: "HideDrawersWithAnimation"
        to: "HideDrawersWithoutAnimation"
        PropertyAnimation {
            property: "anchors.leftMargin"
            duration: 0
        }

        PropertyAnimation {
            property: "anchors.rightMargin"
            duration: 0
        }
        PropertyAnimation {
            property: "anchors.topMargin"
            duration: 0
        }
    }
    ]

    Component.onCompleted: {
        cppDrawersApp.qmlLog("Drawers.qml: Drawers component completed.")
    }
}

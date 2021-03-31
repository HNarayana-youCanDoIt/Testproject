import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.clockenum 1.0

BaseUI {
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * SwipeView used to show pages on media Off screen, each page is created from CmpClockLayout.qml
     */
    SwipeView {
        id: idSwipeView
        anchors.fill: parent
        currentIndex: cppMediaOffAdaptor.selectedClockId
        /*
         * Repeater used to control page count
         */
        Repeater {
            model: cppMediaOffAdaptor.clockInformationList.length
            Loader {
                active: true
                source: cppMediaOffAdaptor.clockInformationList[index].layout
            }
        }

        onCurrentIndexChanged: {
            cppMediaOffAdaptor.selectedClockId = currentIndex
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * PageIndicator used to show how many clocks are available on screen and which one is selected
     */
    PageIndicator {
        id: idPageIndicator
        spacing: 12
        count: idSwipeView.count
        currentIndex: idSwipeView.currentIndex
        anchors.bottom: idSwipeView.bottom
        anchors.bottomMargin: 19
        anchors.horizontalCenter: parent.horizontalCenter

        delegate: Item {
            width: parent.spacing
            height: parent.spacing
            Image {
                anchors.centerIn: parent
                source: (index === idSwipeView.currentIndex) ? "qrc:/image/Home/Home_Pagination/Home_pagination_4.png" : "qrc:/image/Home/Home_Pagination/Home_pagination_3.png"
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////

    /*
     * MediaOFF screen information text & image.
     */
    Item {
        id: idMediaOffMessage
        visible: false
        width: idMediaOffInfoText1.width+ idMediaOffInfoIcon.width  + idMediaOffInfoText2.width

        anchors {
            bottom: idPageIndicator.top
            bottomMargin: 15
            horizontalCenter: parent.horizontalCenter
        }


        HBText {
            id: idMediaOffInfoText1
            anchors {
                verticalCenter:  idMediaOffMessage.verticalCenter
                left: parent.Left
            }
            //horizontalAlignment: Text.AlignHCenter
            horizontalAlignment: HBText.Center
            //ToDo: use language file for constant string
            text: qsTr("Tap")  + cppThemeMgr.languageChanged
            fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
        }

        Image {
            id: idMediaOffInfoIcon
            source: "qrc:/image/Drawers/ShortcutDrawer/Icons/Drw_Ico_power_7in_in-assets/Drw_Ico_power_7in_na.png"
            anchors {
                left: idMediaOffInfoText1.right
                leftMargin: -16
                verticalCenter:  idMediaOffMessage.verticalCenter
            }
        }

        HBText {
            id: idMediaOffInfoText2
            anchors {
                left: idMediaOffInfoIcon.right
                leftMargin: -16
                verticalCenter:  idMediaOffMessage.verticalCenter
            }
            //ToDo: use language file for constant string
            text: qsTr("to Resume Media Playback.")  + cppThemeMgr.languageChanged
            fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /**
      * Mouse area that fill the full screen.
      * OnPressed event on anywhere on the screen, Full screen Mode is turned off and Drawers are made visible on the screen
      * Full screen Mode Timer is also restarted
      */
    MouseArea {
        anchors {
            fill: parent
        }
        onPressed: {
            mouse.accepted = false
            idFullScreenModeTimer.restart()
            cppMediaOffAdaptor.invSetDrawersVisibility(true)
            idMediaOffMessage.visible = true
        }
    }

    /* Timer to turn on Full Screen Mode. After 5 seconds, Full Screen Mode will be turned On */
    Timer {
        id: idFullScreenModeTimer
        interval: 5000
        onTriggered: {
            cppMediaOffApplication.qmlLog("ScnMediaOff.qml : Full screen timer triggered")
            cppMediaOffAdaptor.invSetDrawersVisibility(false)
            idMediaOffMessage.visible = false
        }
    }

    Connections{
        target: cppDrawersAdaptor

        onSigHvacDrawerStateChanged: {

            if("Maximized" === cppDrawersAdaptor.hvacDrawerState) {
                cppMediaOffApplication.qmlLog("ScnMediaOff.qml : Full screen timer paused")
                idFullScreenModeTimer.stop()
            }
            else if("Minimized" === cppDrawersAdaptor.hvacDrawerState) {
                cppMediaOffApplication.qmlLog("ScnMediaOff.qml : Full screen timer resumed")
                idFullScreenModeTimer.restart()
            }
            else {
                // do nothing
            }
        }
    }

    Connections
    {
        target : cppHardkeyAdaptor

        onSigRotaryUpdate: {
            cppUIBase.qmlLog("ScnMediaOff.qml: iKeyState: " + iKeyState + " iKeyCode : " + iKeyCode)

            if(HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB === iKeyCode) {
                if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState) {
                    idSwipeView.decrementCurrentIndex()
                } else if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState) {
                    idSwipeView.incrementCurrentIndex()
                }
            }
        }

        onSigRotaryPressed: {
            cppUIBase.qmlLog("ScnMediaOff.qml: onRotaryPressed: "+iKeyState)
            if(HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode) {
                if (HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState) {
                    cppMediaOffApplication.raiseSMEvent("CmpClockTemplate.qml", "onClockDialRelease")
                }
            }
        }
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.homeenum 1.0
import com.harman.qml.hardkeyenum 1.0

BaseUI {
    //id: idMainWindow
    width: 800
    height: 480

    //this property holds RRE slot index of home page
    property int prRRESlotIndex: -1

    /////////////////////////////////////////////////////////////////////////////////
    /*
     * SwipeView used to show pages on home screen, each page is created from /Common/HomePage.qml
     */
    SwipeView {
        id: idSwipeView
        anchors.fill: parent

        currentIndex: cppHomeAdaptor.currentPageIndex

        onCurrentIndexChanged: {
            cppHomeAdaptor.currentPageIndex = currentIndex
        }

        /*
         * Repeater used to control page count
         */
        Repeater {
            model: cppHomeAdaptor.shortcutPages
            Loader {
                active: true
                sourceComponent: HomePage {
                    startIndex: 1 + index * MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE
                }
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////
    /*
     * Text used to show title text for home screen
     */
    HBText {
        id: idTitle

        anchors {
            top: parent.top
            topMargin: 58
            horizontalCenter: parent.horizontalCenter
        }

        horizontalAlignment: Text.AlignHCenter
        fontType: ThemeMgr.FONTTYPE_T45_C1
        text: qsTr("TEXT_HOME_TITLE_LABEL") + cppThemeMgr.languageChanged
    }

    /////////////////////////////////////////////////////////////////////////////////
    /*
     * PageIndicator used to show how many pages are available on home screen and which one is on screen
     */
    PageIndicator {
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
                source: (index === idSwipeView.currentIndex) ? ((index === 0) ? "qrc:/image/Home/Home_Pagination/Home_pagination_2.png" : "qrc:/image/Home/Home_Pagination/Home_pagination_4.png") : ((index === 0) ? "qrc:/image/Home/Home_Pagination/Home_pagination_1.png" : "qrc:/image/Home/Home_Pagination/Home_pagination_3.png")
            }
        }
    }

    Connections {
        target: cppHardkeyAdaptor
        onSigRotaryPressed: {
            cppHomeApplication.qmlLog("ScnHomeMain.qml : right rotary pressed")

            if ((prRRESlotIndex !== -1)
                    && (HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode)) {

                var shortcutId = cppHomeAdaptor.shortcutsId[prRRESlotIndex]

                if (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState) {
                    shortcutClicked(shortcutId)
                } else if (HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState) {
                    shortcutLongPressed(shortcutId)
                }
            }
        }

        onSigRotaryUpdate: {
            cppHomeApplication.qmlLog("ScnHomeMain.qml : right rotary rotated")

            var iNextIndex = -1

            /** iStartSlotIndex holds the slot index of first shortcut on current home page */
            var iStartSlotIndex = (idSwipeView.currentIndex
                                   * MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE) + 1

            if (HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB === iKeyCode) {
                if (prRRESlotIndex === -1) {
                    prRRESlotIndex = iStartSlotIndex
                } else if (HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState) {
                    iNextIndex = prRRESlotIndex - 1
                    if (prRRESlotIndex > 1) {
                        /** below logic is to switch to previous home page if next RRE slot index is on previous home page */
                        if (iNextIndex < iStartSlotIndex) {
                            cppHomeAdaptor.currentPageIndex = idSwipeView.currentIndex - 1
                        }
                        prRRESlotIndex = iNextIndex
                    }
                } else if (HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState) {
                    iNextIndex = prRRESlotIndex + 1
                    if ((cppHomeAdaptor.shortcutsLength > iNextIndex)
                            && (cppHomeAdaptor.shortcutsId[iNextIndex] !== -1)) {
                        /** below logic is to switch to next home page if next RRE slot index is on next home page */
                        if (iNextIndex >= (iStartSlotIndex
                                           + MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE)) {
                            cppHomeAdaptor.currentPageIndex = idSwipeView.currentIndex + 1
                        }
                        prRRESlotIndex = iNextIndex
                    }
                } else {


                    // do nothing
                }
            } else {
                cppHomeApplication.qmlLog(
                            "ScnHomeMain.qml : wrong rotary event")
            }
        }
    }


    // FixMe(RRahul) : Need to move shortcutClicked() and shortcutLongPressed method in homeAdaptor.cpp.
    /*
     * shortcut long pressed handled here
     */
    function shortcutLongPressed(shortcutId) {

        if (prRRESlotIndex <= MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE) {
            if ((HomeEnum.SHORTCUT_ADD_SHORTCUT_ID === shortcutId) || cppHomeAdaptor.invIsFixedShortcut(shortcutId)) {
                //! empty or fixed shortcuts shall act as clicked
                cppHomeAdaptor.homeShortcutsList[shortcutId].invShortcutClicked(prRRESlotIndex)
            }else {
                /** as 0 is unique ID for "add shortcut" icon touch and hold will act as short release event */
                cppHomeAdaptor.invShowUpdateHomeShortcutPopup(prRRESlotIndex)
            }
        } else {
            /** shortcuts available on page other than home page (page which are other than 1st page of home screen) */
            if (cppHomeAdaptor.homeShortcutsList[shortcutId].isActive) {
                cppHomeAdaptor.homeShortcutsList[shortcutId].invShortcutClicked(
                            prRRESlotIndex)
            }
        }
    }


    /*
     * shortcut short click handled here
     */
    function shortcutClicked(shortcutId) {
        if (((HomeEnum.SHORTCUT_BLANK_ID < shortcutId) && (cppHomeAdaptor.homeShortcutsList[shortcutId].isActive))
                || cppHomeAdaptor.invIsFixedShortcut(shortcutId)) {
            cppHomeApplication.qmlLog("Home Shortcut Button:: onClicked " + prRRESlotIndex + ", " + shortcutId + " is valid and active")
            cppHomeAdaptor.homeShortcutsList[shortcutId].invShortcutClicked(prRRESlotIndex)
        }
    }
}

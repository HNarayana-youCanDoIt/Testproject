import QtQuick 2.7
import "../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.homeenum 1.0

MouseArea {
    width: 130
    height: 120

    property string strHomeIconPath: "qrc:/image/Home/"

    //this property holds shortcut slot index for current shortcut
    property int slotIndex: 0

    //this property holds assigned shorucut unique id
    property int shortcutId: (cppHomeAdaptor.shortcutsLength > slotIndex)
                             ? cppHomeAdaptor.shortcutsId[slotIndex] : -1

    //this property holds assigned shorucut active state
    property bool isActive: (HomeEnum.SHORTCUT_BLANK_ID === shortcutId)
                            ? false : cppHomeAdaptor.homeShortcutsList[shortcutId].isActive

    //this property holds assigned shorucut in active icon image
    property string inactiveImageURL: (HomeEnum.SHORTCUT_BLANK_ID === shortcutId)
                                      ? "" : (strHomeIconPath + (cppDisplayManagerAdaptor.nightModeStatus ? "NightMode/" : "DayMode/") + cppHomeAdaptor.homeShortcutsList[shortcutId].iconInactive)

    //set shortcut text using this property
    property string text: (HomeEnum.SHORTCUT_BLANK_ID === shortcutId)
                          ? "" : cppHomeAdaptor.homeShortcutsList[shortcutId].text

    //use to change default image of shortcut
    property string defaultImageURL: (HomeEnum.SHORTCUT_BLANK_ID === shortcutId)
                                     ? "" : (strHomeIconPath + (cppDisplayManagerAdaptor.nightModeStatus ? "NightMode/" : "DayMode/") + cppHomeAdaptor.homeShortcutsList[shortcutId].iconNormal)

    //use to change pressed image of shortcut
    property string pressedImageURL: (HomeEnum.SHORTCUT_BLANK_ID === shortcutId)
                                     ? "" : (strHomeIconPath + (cppDisplayManagerAdaptor.nightModeStatus ? "NightMode/" : "DayMode/") + cppHomeAdaptor.homeShortcutsList[shortcutId].iconPressed)

    //use to change disabled image of shortcut
    property string disabledImageURL: (HomeEnum.SHORTCUT_BLANK_ID === shortcutId)
                                      ? "" : (strHomeIconPath + (cppDisplayManagerAdaptor.nightModeStatus ? "NightMode/" : "DayMode/") + cppHomeAdaptor.homeShortcutsList[shortcutId].iconInactive)

    visible: (defaultImageURL !== "")

    // disable drag functionality on the shortcut buttons
    drag.target: undefined
    drag.axis: Drag.None

    /*
     * RRE focus image
     */
    Image {
        id: idRREFocusImage

        anchors{
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: -10
        }

        visible: (prRRESlotIndex === parent.slotIndex)

        source: "qrc:/image/Home/Home_Ico_RRE_Focus/Home_Ico_RRE_Focus.png"

    }

    /*
     * HBText used to show title text for shortcut
     */
    HBText {
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop
        fontType: (parent.isActive) ? ThemeMgr.FONTTYPE_T24_LIGHT_C2
                                    : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
        wrapMode: Text.WordWrap
        elide: Text.ElideNone
        width: 145
        lineHeight: 0.8

        anchors{
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 91
        }

        visible: (text !== "")
        text: parent.text
    }

    /*
     * Image for shortcut
     */
    Image {
        visible: (source !== "")
        anchors{
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: -10
        }
        source: (parent.enabled) ? ((parent.isActive) ? (parent.pressed
                                                         ? (parent.pressedImageURL) : (parent.defaultImageURL)) : (parent.inactiveImageURL)) : (parent.disabledImageURL)
    }


    // FixMe(RRahul) : Need to move shortcutClicked() and shortcutLongPressed method in homeAdaptor.cpp.
    /*
     * shortcut short click handled here
     */
    function shortcutClicked() {
        cppHomeApplication.qmlLog("Home Shortcut Button:: onPressAndHold " + slotIndex + ", " + shortcutId)
        if (((HomeEnum.SHORTCUT_BLANK_ID < shortcutId) && (isActive)) || cppHomeAdaptor.invIsFixedShortcut(shortcutId)) {
            cppHomeApplication.qmlLog("Home Shortcut Button:: onClicked " + slotIndex + ", " + shortcutId + " is valid and active")
            cppHomeAdaptor.homeShortcutsList[shortcutId].invShortcutClicked(slotIndex)
        }
    }

    /*
     * shortcut long pressed handled here
     */
    function shortcutLongPressed() {
        cppHomeApplication.qmlLog("Home Shortcut Button:: onPressAndHold " + slotIndex + ", " + shortcutId)
        if (slotIndex <= MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE) {
            if ((HomeEnum.SHORTCUT_ADD_SHORTCUT_ID === shortcutId) || cppHomeAdaptor.invIsFixedShortcut(shortcutId)) {
                //! empty or fixed shortcuts shall act as clicked
                cppHomeAdaptor.homeShortcutsList[shortcutId].invShortcutClicked(slotIndex)
            }else {
                /** as 0 is unique ID for "add shortcut" icon touch and hold will act as short release event */
                cppHomeAdaptor.invShowUpdateHomeShortcutPopup(slotIndex)
            }
        } else {
            /** shortcuts available on page other than home page (page which are other than 1st page of home screen) */
            if (isActive) {
                cppHomeAdaptor.homeShortcutsList[shortcutId].invShortcutClicked(
                            slotIndex)
            }
        }
    }

    /*
     * shortcut short press handled here
     */
    onPressed: {
        // Resetting RRE current index to -1.
        prRRESlotIndex = -1
    }

    /*
     * shortcut short click handled here
     */
    onClicked: {
        shortcutClicked()
    }
    /*
     * shortcut long press handled here
     */
    onPressAndHold: {
        shortcutLongPressed()
    }
}

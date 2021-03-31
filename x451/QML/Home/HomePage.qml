import QtQuick 2.7
import "../Common"

Item {

    // this property holds the starting shortcut index for page
    property int startIndex: 1

    /*
     * Grid used to show HomeShortcut in required layout
     */
    Grid {
        anchors.left: parent.left
        anchors.leftMargin: 131
        anchors.top: parent.top
        anchors.topMargin: 140

        width: parent.width + columnSpacing //added spacing to position last column
        height: parent.height + rowSpacing //added spacing to position last row

        columnSpacing: 67
        rowSpacing: 33
        columns: 3

        /*
         * Repeater used to add HomeShortcut in to grid
         */
        Repeater {
            model: MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE
            HomeShortcut {
                slotIndex: parent.parent.startIndex + index
            }
        }
    }
}

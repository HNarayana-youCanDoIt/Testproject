/*
 *  This is a Generic Component, Which provides the functionality related to
 *  List to all other modules. The following functionalities are provided by this
 *  component:
 *  1. It provides the ListView ==> The user of this component needs to assign
 *  a model and a delegate.
 *  2. It also have ScrollBar implementation in it.
 *  3. It also provides one function to show RRE focus. User needs to call that
 *  function and pass the direction of RRE (0 for reverse and 1 for forward).
 */
import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.hardkeyenum 1.0

Item {
    id: idGenericList

    width: 488
    height: 304

    anchors {
        left: parent.left
        leftMargin: 136
        top: parent.top
        topMargin: 140
    }

    /**
      This property is used to change and modify the scrollbar of the Generic List as per requirement.
      **/
    property alias scrollbar: idScrollbar

    /*
    *   Property alias for ListView, the ListView can be accessed using this
    *   property from outside of this qml.
    */
    property alias idList: idListView

    /*
    *   This property is used, to decide that the scrollBar needs to show or
    *   not and the list should be interactive or not. If the list item count
    *   > rowShownPerPage, then ScrollBar will be seen.
    */
    property int rowShownPerPage: 4

    /*
    * This property is used to get the height of individual item in the list.
    */
    property int prItemHeight: 76

    /*
    *   This property is used, as a container, which hold true, if list's
    *   item count is greater than rowShownPerPage or list contentHeight is
    *   greater than the listView height.
    */
    property bool multiPage: false

    /*
     * This property holds the current Top Item index. This is used to allign
     * the top item, when scroll of list stops.
     */
    property int prCurrentTopItemIndex: 0

    /*
     * This property  holds the image path of scroll bar track.
     */
    property alias prScrollBarTrackImageSource:  idScrollTrackImg.source

    /*
     * This property  holds the image path of scroll bar thumb.
     */
    property alias prScrollBarThumbImageSource: idScrollerImage.source

    /*
     * This property  holds the left margin of scroll bar.
     */
    property int prScrollBarLeftMargin: 456

    /*
     * This property  holds the top margin of scroll bar.
     */
    property int prScrollBarTopMargin: 0

    /*
     * This property  holds the sub item count.
     */
    property int prSubItemCount: 0

    /*
     * This property  holds the RRE Index.
     */
    property int prRREIndex: -1

    /*
    *   This property holds the minimum Height of Scroller Thumb.
    *   Because the scrollThumb height changes as per the list count
    *   So this is the minimum height, if scroller thumb height is greater
    *   than this height, then scroller will show a large image and if the
    *   height reaches to this min height, then scroller thumb will show a
    *   a fixed small image.
    */
    property int prScrollThumbMinHeight: 60

    /*
     * This property is for the auto scroll in a list. If a user doesnt want to auto scroll the delgate, then set property to false.
    */
    property bool prEnableAutoScroll: true

    /* Property to hold whether top item index to be set by screen or by generic list */
    property bool prSetTopIndexByScreen: false

    /*
     *  This fuction increase/decrease currentIndex of List, to show the RRE focus.
     *  Like when currentIndex is -1, and HMI gets RRE event for forward
     *  direction, then this function will increase the current index by 1,
     *  and List highlighter will show the RRE focus Image on that Item.
     *  on reverse direction RRE event function will decrease the currentIndex by 1.
     */
    function onRREHardKeyEvent(rreDirection) {
        cppUIBase.qmlLog(
                    "GenericList: onRREHardKeyEvent: rreDirection: " + rreDirection)
        /**
          We must update the rotary, if and only if idList is visible else ignore the rotary operations.
          **/

        if(idListView.visible)
        {
            //Store the RRE index as previous index
            var iPreviousIndex = prRREIndex
            var bEnabledItemFound = false

            /**
              This is implemented because if by any cause if indexAt returns -1 after model change of the list or any cause, then
                whenever user will use rotary it will again search for the current top index of the present list and assign to
                prCurrentTopItemIndex to proceed further.
              **/
            if(prCurrentTopItemIndex === -1)
            {
                prCurrentTopItemIndex = (idListView.indexAt(0, idListView.contentY))
            }
            else
            {
                //Do Need to update prCurrentTopItemIndex
            }

            switch (rreDirection) {
            case HardkeyEnum.HKEY_STATE_ROTATE_LEFT:
                if (-1 <= prRREIndex)
                {
                    /**
                  * Find the previous enabled item in the list, traverese the list till we don't find
                  * the enabled item, once enabled item is found then set bEnabledItemFound as true
                  * and break the loop. If enabled item is not found till end of the list then set
                  * RRE index and current index as previous index.
                  */
                    while(prRREIndex >= -1)
                    {
                        /**
                      * Check if RRE index value is -1 then set the RRE index to the visible page last
                      * item's index otherwise decrement RRE index by 1.
                      */
                        if (prRREIndex === -1)
                        {
                            if (idList.count >= rowShownPerPage)
                            {
                                prRREIndex = (prCurrentTopItemIndex + (rowShownPerPage - 1))
                            }
                            else
                            {
                                prRREIndex = (prCurrentTopItemIndex + (idList.count - 1))
                            }
                        }
                        else
                        {
                            //If RRE index is greater than 0 then only decrement the RRE index by 1
                            if(prRREIndex > 0)
                            {
                                --prRREIndex
                            }
                            else
                            {
                                break
                            }
                        }

                        //Set list current index as RRE index
                        idList.currentIndex = prRREIndex

                        cppUIBase.qmlLog(
                                    "GenericList: current index: " + idList.currentIndex +
                                    ", GenericList: prRREIndex: " + prRREIndex)

                        /**
                          We should only do the operations when the currentItem is not null
                          **/
                        if (idList.currentItem)
                        {
                            cppUIBase.qmlLog(
                                        "GenericList: idList.currentItem " + idList.currentItem +
                                        ", GenericList: idList.currentItem.enabled: " + idList.currentItem.enabled)

                            /**
                        * Check whether the list current item which has RRE focus is enabled
                        * or not. If current item is enabled then set bEnabledItemFound as true
                        */
                            if (idList.currentItem.enabled)
                            {
                                bEnabledItemFound = true
                                break
                            }
                        }
                        else
                        {
                            cppUIBase.qmlLog("GenericList: idList.currentItem is Null ")
                            break
                        }
                    }

                    //Check if bEnabledItemFound is false then set RRE index and current index as previous index.
                    if (!bEnabledItemFound)
                    {
                        prRREIndex = iPreviousIndex
                        idList.currentIndex = iPreviousIndex
                    }

                }
                else
                {
                    // Do nothing
                }

                break
            case HardkeyEnum.HKEY_STATE_ROTATE_RIGHT:
                if (prRREIndex < (idList.count - 1))
                {
                    /**
                  * Find the next enabled item in the list, traverese the list till we don't find
                  * the enabled item, once enabled item is found then set bEnabledItemFound as true
                  * and break the loop. If enabled item is not found till end of the list then set
                  * RRE index and current index as previous index.
                  */
                    while(prRREIndex < (idList.count - 1))
                    {
                        /**
                      * Check if RRE index value is -1 then set the RRE index to the list current
                      * top index otherwise increment RRE index by 1.
                      */
                        if (prRREIndex === -1)
                        {
                            prRREIndex = prCurrentTopItemIndex
                        }
                        else
                        {
                            ++prRREIndex
                        }

                        //Set list current index as RRE index
                        idList.currentIndex = prRREIndex

                        cppUIBase.qmlLog(
                                    "GenericList: current index: " + idList.currentIndex +
                                    ", GenericList: prRREIndex: " + prRREIndex + "prCurrentTopItemIndex: " + prCurrentTopItemIndex)

                        /**
                          We should only do the operations when the currentItem is not null
                          **/
                        if (idList.currentItem)
                        {
                            cppUIBase.qmlLog(
                                        "GenericList: idList.currentItem " + idList.currentItem +
                                        ", GenericList: idList.currentItem.enabled: " + idList.currentItem.enabled)

                            /**
                      * Check whether the list current item which has RRE focus is enabled
                      * or not. If current item is enabled then set bEnabledItemFound as true
                      */
                            if (idList.currentItem.enabled)
                            {
                                bEnabledItemFound = true
                                break
                            }
                        }
                        else
                        {
                            cppUIBase.qmlLog("GenericList: idList.currentItem is Null ")
                            break
                        }
                    }

                    //Check if bEnabledItemFound is false then set RRE index and current index as previous index.
                    if (!bEnabledItemFound)
                    {
                        prRREIndex = iPreviousIndex
                        idList.currentIndex = iPreviousIndex
                    }
                }
                else
                {
                    // Do nothing
                }
                break
            default:
                cppUIBase.qmlLog("GenericList: onRREHardKeyEvent: default case")
                break
            }
        }
        else
        {
            cppUIBase.qmlLog("GenericList.qml:: idListView is not visible.")
        }
    }


    Component {
        id: idHighlightBar
        Item {
            visible: idListView.currentItem.enabled
            width: idListView.width
            height: idListView.currentItem ? idListView.currentItem.height : 0
            y: idListView.currentItem ? idListView.currentItem.y : 0

            Image {
                id: idHighlightImg

                anchors.bottom: parent.bottom
                height: idListView.currentItem.height
                source: idListView.currentItem ? "qrc:/image/Gen_Gfx_ListCursor_7in_n-assets/Gen_Gfx_ListCursor_n.png" : ""
            }
        }
    }

    ListView {
        id: idListView

        orientation: ListView.Vertical
        width: parent.width
        height: parent.height
        focus: true
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        currentIndex: -1
        snapMode: (prEnableAutoScroll ? ListView.SnapToItem : ListView.NoSnap)

        MouseArea{
            anchors.fill: parent

            /*
             * On Touch needs to clear the RRE image.
             */
            onPressed:
            {
                /*
                 * setting this to false, so that delegates can take action on this event.
                 */
                mouse.accepted = false

                // Set current index to clear the RRE focus image.
                idList.currentIndex = -1
                prRREIndex = -1
            }
        }


        /*
        *   Set the highlight delegate. Note we must also set highlightFollowsCurrentItem
        *   to false so the highlight delegate can control how the highlight is moved.
        */
        highlight: idHighlightBar
        highlightFollowsCurrentItem: false

        onCountChanged: {
            cppUIBase.qmlLog("GenericList: Count Changed: " + count)
            multiPage = ((idListView.count > rowShownPerPage) || (idListView.contentHeight > idListView.height))
            idListView.interactive = multiPage
            idScrollbar.visible = multiPage
        }
        onContentHeightChanged: {
            cppUIBase.qmlLog(
                        "GenericList: Content height Changed: " + idListView.contentHeight + idListView.height)
            multiPage = ((idListView.count > rowShownPerPage) || (idListView.contentHeight > idListView.height))
            idListView.interactive = multiPage
            idScrollbar.visible = multiPage
        }

        ScrollBar.vertical: idScrollbar

        onDragEnded: {
            cppUIBase.qmlLog("GenericList.qml: DragEnded:")
            idList.currentIndex = -1
            prRREIndex = -1
        }

        /*
         * onContentYChanged: is used to find the current top item's index, So
         * that we can allign the top item, when scroll stops.
         */
        onContentYChanged: {
            /*
             * Find the top item index.
             */
            prCurrentTopItemIndex = (indexAt(0, contentY))

            /*
             *  If top Item's first half is visible, then show the same item on
             *  top, else show the next Item on top.
             */
            if(prEnableAutoScroll)
            {
                if ((contentY % prItemHeight) > (prItemHeight/2))
                {
                    prCurrentTopItemIndex += 1
                }
                else
                {
                    // Do Nothing.
                }
            }
            else
            {
                //Do Nothing
            }


        }

        Connections {
            target: cppHardkeyAdaptor
            onSigRotaryUpdate: {
                cppUIBase.qmlLog("GenericList: onRotaryUpdate: KeyState: " +iKeyState)

                onRREHardKeyEvent(iKeyState)
            }
        }

        Connections{
            target: cppUIBase

            onSigScreenAboutToLoad :
            {
                cppUIBase.qmlLog("GenericList: onSigNewScreenAboutToLoad:")
                cppUIBase.updateTopIndex(prCurrentTopItemIndex)
            }
        }

        Component.onCompleted: {
            cppPhoneApp.qmlLog("GenericList.qml - top item index is: " + cppUIBase.getListTopItemIndex() + "top index to be set by screen: " + prSetTopIndexByScreen)
            if(!prSetTopIndexByScreen)
            {
                idList.positionViewAtIndex(cppUIBase.getListTopItemIndex(), ListView.Beginning)
            }
            else
            {
                //do nothing
            }
        }
    }

    NumberAnimation { id: idListSnapAnimation; target: idListView; running: false; property: "contentY"; duration: 200 }

    ScrollBar {
        id: idScrollbar

        height: idScrollTrackImg.height
        width: idScrollerImage.width

        anchors {
            top: idGenericList.top
            topMargin: prScrollBarTopMargin
            left: idGenericList.right
        }

        property int prListItemCount: idListView.count + prSubItemCount

        active: true
        /*
         * This is for allign the item completely, when scroll completes.
         * We can not show the half item on top.
         */
        onPressedChanged: {
            cppUIBase.qmlLog("ScrollBar pressed changed: pressed: "
                             + pressed + "prCurrentTopItemIndex: " + prCurrentTopItemIndex)

            if (!pressed && ((prCurrentTopItemIndex != -1)
                             && (idListView.contentY != (idListView.contentHeight - idGenericList.height)))
                    && prEnableAutoScroll)
            {
                idList.currentIndex = -1
                prRREIndex = -1
                idListSnapAnimation.from = idListView.contentY
                idListView.positionViewAtIndex(prCurrentTopItemIndex, ListView.Beginning)
                idListSnapAnimation.to = idListView.contentY

                idListSnapAnimation.start()
            }
            else
            {
                // Do Nothing.
            }
        }

        background: Item {
            id: idScrollbarBgItem

            width: idScrollTrackImg.width
            height: idScrollTrackImg.height

            anchors.horizontalCenter: idScrollbar.horizontalCenter

            Image {
                id: idScrollTrackImg
                source: "qrc:/image/GenericList/Gen_Gfx_ScrollbarBg_n.png"
            }
        }

        contentItem: Rectangle {
            id: idScrollRect

            width: idScrollerImage.width

            color: "transparent"

            anchors.horizontalCenter: idScrollbar.horizontalCenter

            BorderImage {
                id: idScrollerImage

                anchors.top: idScrollRect.top

                border{
                    left: 10
                    top: 10
                    right: 10
                    bottom: 10
                }

                height: ((idScrollRect.height > prScrollThumbMinHeight) ? idScrollRect.height : prScrollThumbMinHeight)

                /*
                *   FixMe: There should be better way to do this.
                *   The problem which was resolved mannualy here is that,
                *   Whenever List count goes so high/Low, the size of
                *   ScrollerThumb of List's ScrollBar is decreased/increased.
                *   If List count goes very high, then scroller thumb size
                *   decreases to very minimum size. So we need to fix the
                *   minimum size of scroller Thumb. So we have used a
                *   Rectangle and inside that rectangle, we used an Image, the
                *   rectangle will be increased or decreased, but Image
                *   will not, So when rectangle's size deceases  to very minimum,
                *   and user scroll to index 0, of list, the image goes to out of
                *   scroll area. So we calculated the topMargin to allign the image
                *   in scrollArea.
                */
                anchors.topMargin: -(idScrollbar.position
                                     / ((idScrollbar.prListItemCount - rowShownPerPage)
                                        / (idScrollbar.prListItemCount))) * (height - idScrollRect.height)

                source: "qrc:/image/GenericList/Gen_Gfx_Scroller_n.png"
            }
        }
    }
}

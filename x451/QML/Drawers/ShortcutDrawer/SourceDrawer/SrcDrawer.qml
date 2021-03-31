import QtQuick 2.7


/*
 * This item is containing source drawer Grid, Which contains all Items need to
 * show on source drawer.
 */
Item {
    id: idSrcDrawerItem

    width:  (parent ? parent.width : 0)
    height: (parent ? parent.height : 0)

    /*
     * property holds the state of drawer.
     */
    property string prSrcDrawerState: cppDrawersAdaptor.srcDrawerState

    Image {
        id: idSepratorLineBgImage
        anchors {
            right: parent.right
            rightMargin: 217
        }
        source: "qrc:/image/Drawers/ShortcutDrawer/Source/BackGround/Wid_Right_Source_LargeDrawer_Divider_7in.png"
    }

    MouseArea {
        id: idSrcContainerBackground
        width: 400
        height: 450
        anchors
        {
            top: parent.top
            left: parent.left
            leftMargin: 180
        }
    }

    /*
     * Source Drawer Container item, Which contains the Source Grid.
     */
    SrcDrawerContainer {
        id: idSrcDrawerContainer

        width: 702
        height: parent.height

        anchors {
            right: parent.right
            rightMargin: 90
            top: parent.top
            topMargin: 33
        }
    }
}

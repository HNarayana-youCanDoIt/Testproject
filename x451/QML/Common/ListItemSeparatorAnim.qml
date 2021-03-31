import QtQuick 2.7

Item {
    width: idListItemSepratorImg.width
    height: idListItemSepratorImg.height

    property alias prStartAnim: idIndicatorLoading.visible

    Image {
        id: idListItemSepratorImg
        source: "qrc:/image/GenericList/Gen_Gfx_ListSeparator_7in_n-assets/Gen_Gfx_ListSeparator_n.png"
    }

    Rectangle{
        id: idIndicatorLoading
        y: -2
        width: 60
        height: idListItemSepratorImg.height + 2

        color: cppThemeMgr.currentThemeColor

        PropertyAnimation on x {
            id: idPositiveAnim
            easing.type: Easing.Linear
            from: 0; to: (parent.width - 60)
            duration: 1500
            //running: false
        }

        PropertyAnimation on x {
            id: idNegativeAnim
            easing.type: Easing.Linear
            from: (parent.width - 60); to:  0
            duration: 1500
            running: false
        }

        onXChanged: {
            if(x===0)
                idPositiveAnim.start()
            else if(x === (parent.width - 60))
                idNegativeAnim.start()

        }

    }
}

/* Note: ListItemSeparatorAnim usage.

    ListItemSeparatorAnim {
        id: idSeparator
        prStartAnim: true/false (to start or stop the animations)
    }
*/


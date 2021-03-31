import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0

/** Delegate of Button List Item with Label and its Value(Label)  **/
Item {
    id: idBtnListTrackNameDelegate
    width: idGenericList.idList.width
    height: idGenericList.prItemHeight

    Column {
        LabelWithLabelComp {
            id: idTrackNameComp
            width: idGenericList.idList.width
            height: (idGenericList.prItemHeight - idSeparator.height)
            prItemSubText: enggMenuItemSubTextRole
            text: enggMenuItemMainTextRole
            prSubTextWidth : 240
            prMainTextFontType : ThemeMgr.FONTTYPE_T24_LIGHT_C2
            prSubTextFontType  : ThemeMgr.FONTTYPE_T24_LIGHT_C2
            /**
                Do not show any focus image when user touches/press any item
              **/
            pressedImageURL: ""
        }

        ListItemSeparator {
            id:idSeparator
        }
    }
}

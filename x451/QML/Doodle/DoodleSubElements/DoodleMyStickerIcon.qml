import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0

//// Doodle My Sticker Icon
DoodleSubElementBehavior {
    prDoodleIconImage: idDoodleMyStickerSubElementLayout.prDoodleIconImage

    //// doodle my sticker layout
    contentItem: Item {
        anchors {
            fill: parent
        }

        DoodleMyStickerSubElementLayout {
            id: idDoodleMyStickerSubElementLayout
            prPopupID: PopupEnum.EN_POPUPID_DOODLE_MYSTICKER_ICON
        }
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0
import com.harman.qml.thememanager 1.0

import "../../Common"

//// Doodle My Sticker Icon Preview
DoodleSubElementBehavior {
    prDoodleIconImage: idDoodleMyStickerSubElementLayout.prDoodleIconImage

    //// doodle my sticker preview layout
    contentItem: Item {
        anchors {
            fill: parent
        }

        //// Text used to show title text
        HBTitleWithBackButton {
            id: idTitleText
            prTitle: "*Preview"//qsTr("TEXT_DOODLE_SETUP_PREVIEW_HEADER") + cppThemeMgr.languageChanged
            prBackButtonVisible: false
        }

        //// Text used to show information text
        HBText {
            anchors {
                top: idTitleText.bottom
                topMargin: -10
                horizontalCenter: parent.horizontalCenter
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontType: ThemeMgr.FONTTYPE_T22_LIGHT_C2

            text: "*Hold and drag Doodle to change its position."//qsTr("TEXT_DOODLE_SETUP_SUB_HEADER") + cppThemeMgr.languageChanged
        }

        DoodleMyStickerSubElementLayout {
            id: idDoodleMyStickerSubElementLayout
            prPopupID: PopupEnum.EN_POPUPID_DOODLE_MYSTICKER_ICON_PREVIEW
        }
    }
}

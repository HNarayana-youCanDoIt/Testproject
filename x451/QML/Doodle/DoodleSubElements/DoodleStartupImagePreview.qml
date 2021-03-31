import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.popupenums 1.0

import "../../Common"

//// Doodle Startup Image Preview
DoodleSubElementBehavior {
    prDoodleIconImage: idDoodleStartupImage

    //// doodle startup image preview layout
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

        //// Layout used to show DoodleStartupImage on Doodle Setup Preview Screen
        Image {
            id: idDoodleStartupImage
            anchors {
                centerIn: parent
            }
            source: cppDoodleAdaptor.startupImageURL
        }
    }
}

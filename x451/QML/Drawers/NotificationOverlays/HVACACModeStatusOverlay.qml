import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: idHVACACModeStatusBarItem

    width: 155
    height: 76

    anchors.centerIn: parent

    Image {
        id: idHvacClimateIcon

        anchors {
            top: parent.top
            left: parent.left
        }
        /*
         * ToDo: (OPL)Image is not correct need Image for slide Bar, Also the
         * Image is not available for Off Mode, used ON Image
         */
        source: cppHVACAdaptor.acMode
                ? "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Popup_Ico_Climate_AC_na.png"
                : "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Pop_Ico_AC_Off_n.png"
    }

    /*
         * This is the item which is used to show the AUTO Mode status.
         */
    HBText {
        id: idTextAutoModeStatus

        width: 140
        height: 34

        anchors {
            left: idHvacClimateIcon.right
            //leftMargin: 10
            verticalCenter: idHvacClimateIcon.verticalCenter
        }

        text: cppHVACAdaptor.acMode ? qsTr("TEXT_HVAC_AC_ON") +
                                      cppThemeMgr.languageChanged :
                                      qsTr("TEXT_HVAC_AC_OFF") +
                                      cppThemeMgr.languageChanged
        fontType: ThemeMgr.FONTTYPE_T35_C3
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("HVACACModeStatusBar.qml: Component.onCompleted")
    }
}

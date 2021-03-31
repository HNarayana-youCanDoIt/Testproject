import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: idHVACEconModeStatusBarItem

    width: 196
    height: 76

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
        source: cppHVACAdaptor.ecoAcMode
                ? "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Popup_Ico_Climate_AC_na.png"
                : "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Pop_Ico_AC_Off_n.png"
    }

    /*
         * This is the item which is used to show the AUTO Mode status.
         */
    HBText {
        id: idTextEconModeStatus

        width: 150
        height: 34

        anchors {
            left: idHvacClimateIcon.right
            //leftMargin: 10
            verticalCenter: idHvacClimateIcon.verticalCenter
        }

        text: cppHVACAdaptor.ecoAcMode ? qsTr("TEXT_HVAC_ECON_ON") +
                                         cppThemeMgr.languageChanged :
                                         qsTr("TEXT_HVAC_ECON_OFF") +
                                         cppThemeMgr.languageChanged
        fontType: ThemeMgr.FONTTYPE_T35_C3
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("HVACEconModeStatusBar.qml: Component.onCompleted")
    }
}

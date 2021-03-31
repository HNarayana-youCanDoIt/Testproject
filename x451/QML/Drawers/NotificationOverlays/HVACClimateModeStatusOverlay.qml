import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: idHVACClimateModeStatusBarItem

    width: 256
    height: 76

    anchors.centerIn: parent

    Image {
        id: idHvacClimateIcon

        anchors {
            top: parent.top
            left: parent.left
        }

        source: "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Pop_Ico_AC_Off_n.png"
    }

    /*
         * This is the item which is used to show the AUTO Mode status.
         */
    HBText {
        id: idTextClimateModeStatus

        width: 180
        height: 34

        anchors {
            left: idHvacClimateIcon.right
            //leftMargin: 10
            verticalCenter: idHvacClimateIcon.verticalCenter
        }

        text: qsTr("TEXT_HVAC_CLIMATE_OFF") + cppThemeMgr.languageChanged
        fontType: ThemeMgr.FONTTYPE_T35_C3
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("HVACClimateModeStatusBar.qml: Component.onCompleted")
    }
}

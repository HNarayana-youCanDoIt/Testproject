import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.thememanager 1.0

Item {
    id: idHVACMaxDefrostStatusBarItem

    width: 270
    height: 76

    Image {
        id: idHvacMaxDefrostIcon

        anchors {
            top: parent.top
            left: parent.left
        }

        source: cppHVACAdaptor.maxDefrostMode
                ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax_na.png"
                : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax_n.png"
    }

    /*
     * This is the item which is used to show the MaxDefrost Mode Mode status.
     */
    HBText {
        width: 190
        height: 34

        anchors {
            left: idHvacMaxDefrostIcon.right
            leftMargin: 10
            verticalCenter: idHvacMaxDefrostIcon.verticalCenter
        }

        text: qsTr("TEXT_HVAC_MAX_DEFROST") + cppThemeMgr.languageChanged

        fontType: ThemeMgr.FONTTYPE_T35_C3
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("HVACMaxDefrostStatusOverlay.qml: Component.onCompleted")
    }
}


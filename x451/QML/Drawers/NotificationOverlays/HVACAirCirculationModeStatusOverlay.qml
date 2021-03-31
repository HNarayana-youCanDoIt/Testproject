import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.hvacenums 1.0

Item {
    id: idHVACAirCirculationModeStatusBarItem

    width: 76
    height: 76

    anchors.centerIn: parent

    Image {
        id: idHvacClimateIcon

        anchors {
            centerIn: parent
        }

        source: (HVACEnums.HVAC_AIRCIRCULATION_FRESHIR_ON ===
                 cppHVACAdaptor.airCirculationMode)
                ? "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Pop_Ico_FreshAir_n.png"
                : "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Pop_Ico_RecirculatedAir_n.png"
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("HVACAirCirculationModeStatusBar.qml: Component.onCompleted")
    }
}

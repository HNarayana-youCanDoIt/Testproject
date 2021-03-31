import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.hvacenums 1.0

Item {
    id: idHVACDistributionModeStatusBarItem

    width: 76
    height: 76

    Image {
        id: idHvacClimateIcon

        anchors {
            centerIn: parent
        }
        /*
             * ToDo: (OPL)Images are not available yet. So using X104 Images.
             */
        source: (HVACEnums.HVAC_DM_CHEST_MODE === cppHVACAdaptor.distributionMode)
                ? "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Popup_Ico_Climate_chest.png"
                : (HVACEnums.HVAC_DM_CHESTLEG_MODE === cppHVACAdaptor.distributionMode)
                  ? "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Popup_Ico_Climate_chest_leg.png"
                  : (HVACEnums.HVAC_DM_LEG_MODE === cppHVACAdaptor.distributionMode)
                    ? "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Popup_Ico_Climate_leg.png"
                    : (HVACEnums.HVAC_DM_LEGDEFROST_MODE === cppHVACAdaptor.distributionMode)
                      ? "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Popup_Ico_Climate_leg_defrost.png"
                      : (HVACEnums.HVAC_DM_DEFROST_MODE === cppHVACAdaptor.distributionMode)
                        ? "qrc:/image/Drawers/NotificationOverlays/Popup_Icon_Climate/Popup_Ico_Climate_defrost.png"
                        : ""
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog("HVACAutoModeStatusBar.qml: Component.onCompleted")
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.powerenums 1.0
import com.harman.qml.popupenums 1.0

ScnTransparent {
    anchors.fill: parent
    Timer {
        id: idTimer
        interval: 10
        onTriggered: {
            cppStartupAnim.qmlLog("StartupAnimMain, timeout triggered")
            if(PowerModeEnums.VPM_ONE_HOUR === cppPowerModeAdaptor.powerMode)
            {
                cppStartupAnim.qmlLog("StartupAnimMain complete, HU in One Hour Mode, showing One hour mode entry popup")
                PopupManager.showPopup(PopupEnum.EN_POPUPID_ONE_HOUR_MODE_ENTRY_POPUP)
            }
            cppStartupAnim.raiseSMEvent("AnimComplete", "HomeMain")
        }
    }

    Component.onCompleted: {
        idTimer.start()
    }
}

import QtQuick 2.7
import "../Common"
import com.harman.qml.parkassistenum 1.0
import com.harman.qml.thememanager 1.0

BaseUI {
    id: id_RVC_Screen

    /* Removing the background image which is set in the BaseUI, to make the RVC screen transparent */
    prBackGroundImage: "qrc:/image/ParkAssist/RVC/Zones/PDC_Gfx_StaticGuide_transparent_n.png"

    /* This function updates the zones info, based on the obstacle distance received from service
     If obstacle is detected in red zone, the zone image starts blinking */
    function fnUpdateZonesInfo(rvcZone) {
        switch (rvcZone) {
        case ParkAssistEnum.RVC_ZONE_GREEN:
            idRvcZoneImage.visible = true
            idZoneTimer.stop()
            break
        case ParkAssistEnum.RVC_ZONE_YELLOW:
            idRvcZoneImage.visible = true
            idZoneTimer.stop()
            break
        case ParkAssistEnum.RVC_ZONE_RED:
            idZoneTimer.start()
            break
        default:
            idZoneTimer.stop()
            idRvcZoneImage.visible = false
            break
        }
    }

    Connections {
        target: cppParkAssistAdaptor

        onSigRvcSensorStateChanged: {
            cppParkAssistApp.qmlLog("RVC_Screen.qml - sigRvcSensorStateChanged: " + cppParkAssistAdaptor.rvcScreenSensorState)
            fnUpdateZonesInfo(cppParkAssistAdaptor.rvcScreenSensorState)
        }
    }

    /**
     * Cancel button - To close the RVC-Screen, if this screen is activated from HMI
     */
    GenericButton {
        id: idCancelBtn
        anchors {
            right: parent.right
            rightMargin: 8
            top:parent.top
            topMargin: 97
        }
        width: 112
        height: 80

        defaultImageURL: "qrc:/image/ParkAssist/RVC/Header/RVC_Ico_Cancel_n/RVC_Ico_Cancel_n.png"
        disabledImageURL: "qrc:/image/ParkAssist/RVC/Header/RVC_Ico_Cancel_n/RVC_Ico_Cancel_nd.png"
        pressedImageURL: "qrc:/image/ParkAssist/RVC/Header/RVC_Ico_Cancel_n/RVC_Ico_Cancel_np.png"

        visible: cppParkAssistAdaptor.isPdcRvcActivatedFromHmi

        onReleased: {
            cppParkAssistApp.qmlLog("RVC_Screen.qml - Cancel button clicked")
            cppParkAssistAdaptor.activatePdcRvc(false)
        }
    }

    /**
     * Dynamic overlay image
     */
    Image {
        id: idDynamicOverlay
        source: cppParkAssistAdaptor.rvcOverlayCurrentImagePath
        visible: (ParkAssistEnum.RVC_OVERLAY_DYNAMIC === cppParkAssistAdaptor.rvcOverlayType)
    }

    /**
     * RVC obstacle distance vary image (Green, Yellow, Red)
     */
    Image {
        id: idRvcZoneImage
        source: cppParkAssistAdaptor.rvcDistanceVaryImagePath
        visible: (ParkAssistEnum.RVC_ZONE_DEFAULT !== cppParkAssistAdaptor.rvcScreenSensorState)
    }

    /**
     * Timer used to blink the corresponding zone, where obstacle is present
     */
    Timer {
        id: idZoneTimer
        interval: 200
        running: false
        repeat: true

        onTriggered: {
            idRvcZoneImage.visible = !idRvcZoneImage.visible
        }
    }

    /**
     * Loader used to load the corresponding header of park assist screen
     */
    Loader {
        id: idParkAssistHeaderLoader
        source: "ParkAssistFaultMessageHeader.qml"
    }

    state: cppParkAssistAdaptor.parkAssistHeaderState

    states: [
        State {
            name: "Fault_Message_Header"
            PropertyChanges {
                target: idParkAssistHeaderLoader
                source: "ParkAssistFaultMessageHeader.qml"
            }
        }
    ]

    Component.onCompleted: {
        cppParkAssistApp.qmlLog("RVC_Screen.qml - Component.onCompleted")
        fnUpdateZonesInfo(cppParkAssistAdaptor.rvcScreenSensorState)
    }
}

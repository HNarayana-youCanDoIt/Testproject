import QtQuick 2.7
import com.harman.qml.drawersenums 1.0
import com.harman.qml.thememanager 1.0
import QtGraphicalEffects 1.0
import com.harman.qml.variantcontrolenums 1.0

Item {
    id: idNotificationLaoderItem

    anchors.fill: parent

    property int prActiveNotification: cppDrawersAdaptor.activeNotification

    onPrActiveNotificationChanged: {
        cppDrawersApp.qmlLog("NotificationLoader.qml: onPrActiveNotificationChanged: prActiveNotification" + prActiveNotification + "idNotificationLaoder.state: " + idNotificationLaoder.state)

        if ("Show" == idNotificationLaoder.state)
        {
            idNotificationLaoder.source = getActiveNotificationSource(prActiveNotification)
        }
        else
        {
            // Do nothing
        }
    }

    function getActiveNotificationSource(activeNotification)
    {
        cppDrawersApp.qmlLog("NotificationLoader.qml: getActiveNotificationSource: activeNotification" + activeNotification)

        var strActiveNotificationSource = ""

        switch(activeNotification)
        {
        case DrawersEnums.EN_NOTIFICATION_TYPE_VOLUME:
            strActiveNotificationSource = "qrc:/QML/Drawers/NotificationOverlays/VolumeOverlay.qml"
            break;
        case DrawersEnums.EN_NOTIFICATION_TYPE_HVAC_FAN:
            strActiveNotificationSource = "qrc:/QML/Drawers/NotificationOverlays/HVACFanSpeedNotification.qml"
            break;
        case DrawersEnums.EN_NOTIFICATION_TYPE_HVAC_AC_MODE_STATUS:
            strActiveNotificationSource = "qrc:/QML/Drawers/NotificationOverlays/HVACACModeStatusOverlay.qml"
            break;
        case DrawersEnums.EN_NOTIFICATION_TYPE_HVAC_AIR_CIRCULATION_MODE_STATUS:
            strActiveNotificationSource = "qrc:/QML/Drawers/NotificationOverlays/HVACAirCirculationModeStatusOverlay.qml"
            break;
        case DrawersEnums.EN_NOTIFICATION_TYPE_HVAC_AUTO_MODE_STATUS:
            strActiveNotificationSource = "qrc:/QML/Drawers/NotificationOverlays/HVACAutoModeStatusOverlay.qml"
            break;
        case DrawersEnums.EN_NOTIFICATION_TYPE_HVAC_CLIMATE_MODE_STATUS:
            strActiveNotificationSource = "qrc:/QML/Drawers/NotificationOverlays/HVACClimateModeStatusOverlay.qml"
            break;
        case DrawersEnums.EN_NOTIFICATION_TYPE_HVAC_DISTRIBUTION_MODE_STATUS:
            strActiveNotificationSource = "qrc:/QML/Drawers/NotificationOverlays/HVACDistributionModeStatusOverlay.qml"
            break;
        case DrawersEnums.EN_NOTIFICATION_TYPE_HVAC_ECON_MODE_STATUS:
            strActiveNotificationSource = "qrc:/QML/Drawers/NotificationOverlays/HVACEconModeStatusOverlay.qml";
            break;
        case DrawersEnums.EN_NOTIFICATION_TYPE_HVAC_MAX_DEFROST_MODE_STATUS:
            strActiveNotificationSource = "qrc:/QML/Drawers/NotificationOverlays/HVACMaxDefrostStatusOverlay.qml"
            break;
        case DrawersEnums.EN_NOTIFICATION_TYPE_HVAC_TEMPERATURE:
            strActiveNotificationSource = "qrc:/QML/Drawers/NotificationOverlays/HVACTemperatureOverlay.qml"
            break;
        default:
            cppDrawersApp.qmlLog("NotificationLoader.qml: getActiveNotificationSource: In default case.")
            break;
        }

        return strActiveNotificationSource;
    }

    Image{
        id: idColorPatchBg

        anchors.centerIn: parent

        visible: idImageBg.visible

        source: "qrc:/image/Drawers/NotificationOverlays/Gen_Gfx_PopupVolumePatch_7in_n-assets/X445/Gen_Gfx_PopupVolumePatch_n.png"
    }

    ColorOverlay {
        id: idBgColorOverlay

        visible: idColorPatchBg.visible

        anchors.fill: idColorPatchBg
        source: idColorPatchBg
        color:  cppThemeMgr.currentThemeColor
    }

    Image{
        id: idImageBg

        anchors.centerIn: parent

        visible: false

        source: "qrc:/image/Drawers/NotificationOverlays/Gen_Gfx_PopupVolumeOverlay_7in_n-assets/Gen_Gfx_PopupVolumeOverlay_n.png"
    }

    /*
     * Notification Loader. This loader loads Volume Notification and HVAC notifications.
     */
    Loader {
        id: idNotificationLaoder

        anchors.centerIn: parent

        source: ""

        state: cppDrawersAdaptor.notificationOverlayState

        onStatusChanged:
        {
            if (idNotificationLaoder.status !== Loader.Null && idNotificationLaoder.status === Loader.Ready)
            {
                cppDrawersApp.qmlLog("idNotificationLaoder.item.objectName: " + idNotificationLaoder.item.objectName)
                idNotificationLaoder.item.objectName =  cppIntrospectionAdaptor.invExtractFileName(idNotificationLaoder.source);
                cppUIBase.qmlLog(" source  " + idNotificationLaoder.item.objectName);
                cppIntrospectionAdaptor.invSetOverlayChanged(idNotificationLaoder.item.objectName)
            }
            else
            {
                if(idNotificationLaoder.status === Loader.Null && idNotificationLaoder.source == "")
                {
                    cppUIBase.qmlLog(" source NO Notification Bar ");
                    cppIntrospectionAdaptor.invSetOverlayChanged("NO Notification Bar")
                }
            }
        }

        onSourceChanged: {
            cppDrawersApp.qmlLog("NotificationLoader.qml: OnSourceChanged: source: " + source)

            if ("" == source)
            {
                idImageBg.visible = false
                cppDrawersAdaptor.activeNotification = DrawersEnums.EN_NOTIFICATION_TYPE_NONE
            }
            else
            {
                idImageBg.visible = true
            }
        }

        onStateChanged: {
            cppDrawersApp.qmlLog("NotificationLoader.qml: OnStateChanged: state: " + state)

            if ("Show" === state)
            {
                if (idNotificationLaoder.status === Loader.Null)
                {
                    cppDrawersApp.qmlLog("NotificationLoader.qml: In Slidein State: NotificationLoader.item is null.")
                    source = getActiveNotificationSource(cppDrawersAdaptor.activeNotification)
                }
            }
            else if ("Hide" === state)
            {
                if (idNotificationLaoder.status !== Loader.Null)
                {
                    source = ""
                }
                else
                {
                    cppDrawersApp.qmlLog("NotificationLoader.qml: In SlideOut State: NotificationLoader.item is already null.")
                }
            }
            else
            {
                cppDrawersApp.qmlLog("NotificationLoader.qml: Wrong state recieved.")
            }
        }
    }
}

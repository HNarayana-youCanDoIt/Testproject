import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common/"
import com.harman.qml.drawersenums 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.audioenums 1.0
import com.harman.qml.mediaenum 1.0
import com.harman.qml.powerenums 1.0
import com.harman.qml.variantcontrolenums 1.0

Item {
    id: idCurrentEntertainmentSourceInfoItem

    /*
     * Property to hold the active entertainment source.
     */
    property int prActiveEntertainmentSource: cppAudioAdaptor.activeEntSrc

    /*
     * Property to hold the now playing metadata type
     */
    property int prNowPlayingMetadataType: MediaAdaptor.nowPlayingMetadata

    /*
     * Property to hold the USB content type
     */
    property int prUSBContentType: MediaAdaptor.usbContentType

    /*
     * Property to hold the active entertainment source icon.
     */
    property string prActiveEntertainmentSourceIcon: ""

    /*
     * Property to hold the PowerMode
     */
    property int prCurrentPowerMode : cppPowerModeAdaptor.powerMode


    onPrCurrentPowerModeChanged: {
        cppDrawersApp.qmlLog("QadDrawerMaximizedContainer.qml: onPrCurrentPowerModeChanged")
        updateEntertainmentInfo()
    }

    onEnabledChanged: {
        updateEntertainmentInfo()
    }

    onPrActiveEntertainmentSourceChanged:
    {
        updateEntertainmentInfo()
    }

    onPrNowPlayingMetadataTypeChanged:
    {
        updateEntertainmentInfo()
    }

    onPrUSBContentTypeChanged:
    {
        updateEntertainmentInfo()
    }

    /*
     * This is done here because, on carplay disconnection Audio Manager is not
     * activating any other music source, if carplay music was playing.
     */
    Connections{
        target: cppAppleCarPlayAdaptor

        onSigAppleCarPlayConnectionStatusChanged:{
            updateEntertainmentInfo()
        }
    }

    Connections{
        target: cppPhoneAdaptor

        onSigPhoneCallStateUpdated:{
                updateEntertainmentInfo()
        }
    }

    /*
     * Function to update the entertainment info.
     */
    function updateEntertainmentInfo() {
        cppDrawersApp.qmlLog(
                    "QadDrawerMaximizedContainer.qml: updateEntertainmentInfo: activeEntSrc: " + cppAudioAdaptor.activeEntSrc +
                    " Current PowerMode: " + cppPowerModeAdaptor.powerMode)
        if(cppPhoneAdaptor.doesCallExist)
        {
            idActiveEntSourceComponentLoader.source = "qrc:/QML/Drawers/QadDrawer/QadEntertainmentComponents/QadActiveCallComponent.qml"
        }
        else if(PowerModeEnums.VPM_MEDIA_OFF !== cppPowerModeAdaptor.powerMode)
        {
            switch (cppAudioAdaptor.activeEntSrc)
            {
            case AudioEnums.SRC_TUNER_FM:
            case AudioEnums.SRC_TUNER_AM:
            case AudioEnums.SRC_TUNER_DRM:
                idActiveEntSourceComponentLoader.source = "qrc:/QML/Drawers/QadDrawer/QadEntertainmentComponents/QadTunerComponent.qml"
                break
            case AudioEnums.SRC_USB1:
                prActiveEntertainmentSourceIcon = idCurrentEntertainmentSourceInfoItem.enabled
                        ?  "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_USB_7in_n-assets/Gen_Drawer_Ico_USB_na.png"
                        : "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_USB_7in_n-assets/Gen_Drawer_Ico_USB_nd.png"

                if((MediaEnum.BROWSEITEM_UNKNOWN === MediaAdaptor.nowPlayingMetadata) &&
                        (MediaEnum.CONTENTTYPE_VI === MediaAdaptor.usbContentType
                         || MediaEnum.CONTENTTYPE_V === MediaAdaptor.usbContentType
                         || MediaEnum.CONTENTTYPE_I === MediaAdaptor.usbContentType
                         || MediaEnum.CONTENTTYPE_E === MediaAdaptor.usbContentType))
                {
                    //USB has only videos and/or images and no video is playing
                    idActiveEntSourceComponentLoader.source = "qrc:/QML/Drawers/QadDrawer/QadEntertainmentComponents/QadMediaUSBNoSongsComponent.qml"
                }
                else
                {
                    idActiveEntSourceComponentLoader.source = "qrc:/QML/Drawers/QadDrawer/QadEntertainmentComponents/QadMediaComponent.qml"
                }

                break;
            case AudioEnums.SRC_BT_A2DP1:
                prActiveEntertainmentSourceIcon = idCurrentEntertainmentSourceInfoItem.enabled
                        ?  "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_BTAudio_7in_n-assets/Gen_Drawer_Ico_BTAudio_na.png"
                        : "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_BTAudio_7in_n-assets/Gen_Drawer_Ico_BTAudio_nd.png"
                idActiveEntSourceComponentLoader.source = "qrc:/QML/Drawers/QadDrawer/QadEntertainmentComponents/QadMediaComponent.qml"
                break
            case AudioEnums.SRC_AUDIO_AUX:
                idActiveEntSourceComponentLoader.width = 430
                idActiveEntSourceComponentLoader.source = "qrc:/QML/Drawers/QadDrawer/QadEntertainmentComponents/QadAUXComponent.qml"
                break
            case AudioEnums.SRC_IPOD:
                prActiveEntertainmentSourceIcon = idCurrentEntertainmentSourceInfoItem.enabled
                        ? "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/IPODIcons/Gen_Drawer_Ico_iPOD_na.png"
                        : "qrc:/image/Drawers/ShortcutDrawer/Source/Contents/IPODIcons/Gen_Drawer_Ico_iPOD_nd.png"
                idActiveEntSourceComponentLoader.source = "qrc:/QML/Drawers/QadDrawer/QadEntertainmentComponents/QadMediaComponent.qml"
                break
            case AudioEnums.SRC_GAL_MEDIA:
                prActiveEntertainmentSourceIcon = idCurrentEntertainmentSourceInfoItem.enabled
                        ? "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_AndroidAuto_7in_n-assets/Gen_Drawer_Ico_AndroidAuto_na.png"
                        : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_AndroidAuto_7in_n-assets/Gen_Drawer_Ico_AndroidAuto_nd.png"
                idActiveEntSourceComponentLoader.source = "qrc:/QML/Drawers/QadDrawer/QadEntertainmentComponents/QadAAMediaComponent.qml"
                break
            case AudioEnums.SRC_CARPLAY_MEDIA:
                idActiveEntSourceComponentLoader.width = 430

                prActiveEntertainmentSourceIcon = (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus
                                                   ? "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_CarPlay_7in_n/Drw_Ico_CarPlay_7in_n.png"
                                                   : "")
                idActiveEntSourceComponentLoader.source = (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus
                                                           ? "qrc:/QML/Drawers/QadDrawer/QadEntertainmentComponents/QadCPMediaComponent.qml"
                                                           : "")
                break
            default:
                prActiveEntertainmentSourceIcon = ""
                idActiveEntSourceComponentLoader.source = ""
                cppDrawersApp.qmlLog(
                            "QadDrawerMaximizedContainer.qml: updateEntertainmentInfo() In default case.")
                break
            }
        }
        else
        {
            idActiveEntSourceComponentLoader.width = 500
            idActiveEntSourceComponentLoader.source = "qrc:/QML/Drawers/QadDrawer/QadEntertainmentComponents/X445/QadMediaOffComponent.qml"
        }
    }

    /*
     * Loader to load current entertainment Component.
     */
    Loader{
        id: idActiveEntSourceComponentLoader

        width: 250
        height: idCurrentEntertainmentSourceInfoItem.height

        source: ""
        onSourceChanged: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: idActiveEntSourceComponentLoader source changed: source:" + source)
        }
    }

    /*
     * vertical Seprator line to seprate cast image and entertainemnt info.
     */
    Image {
        id: idEntertainementVerticalSepratorLine

        asynchronous: true

        anchors {
            left: parent.left
            leftMargin: 554
            verticalCenter: parent.verticalCenter
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LineSeparator2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
    }

    /*
     * Cast Image.
     */
    GenericButton {
        id: idCastButton

        width: 76
        height: parent.height

        visible: (cppVariantControlAdaptor.eolICCastEnabledStatus)


        prEnableColorOverlay: false

        enabled: cppICCastAdaptor.icCastEnableStatus

        anchors {
            left: parent.left
            leftMargin: 568
            verticalCenter: parent.verticalCenter
        }

        defaultImageURL: cppICCastAdaptor.icCastStatus
                         ? "qrc:/image/ICCast/Gen_Ico_Cast_7in_n-assets/Drw_Ico_Cast_B_7in_na.png"
                         : "qrc:/image/ICCast/Gen_Ico_Cast_7in_n-assets/Drw_Ico_Cast_7in_n.png"

        pressedImageURL: cppICCastAdaptor.icCastStatus
                         ? "qrc:/image/ICCast/Gen_Ico_Cast_7in_n-assets/Drw_Ico_Cast_B_7in_np.png"
                         : "qrc:/image/ICCast/Gen_Ico_Cast_7in_n-assets/Drw_Ico_Cast_7in_np.png"
        disabledImageURL: cppICCastAdaptor.icCastStatus
                          ? "qrc:/image/ICCast/Gen_Ico_Cast_7in_n-assets/Drw_Ico_Cast_B_7in_nd.png"
                          : "qrc:/image/ICCast/Gen_Ico_Cast_7in_n-assets/Drw_Ico_Cast_7in_nd.png"

        onReleased:
        {
            cppICCastAdaptor.sendICCastStatus(!cppICCastAdaptor.icCastStatus)
            resetMaxDrawerCloseTimer()
        }
    }

    /*
     * Seprator line to seprate items in QuickAccess Drawer
     */
    Image {
        id: idEntertainmentSepratorLine

        anchors {
            left: parent.left
            bottom: parent.bottom
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LeftLineSeparator_7in_n-assets/Drw_Gfx_LeftLineSeparator_n.png"
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog(
                    "QadDrawerMaximizedContainer.qml: Component completed.")
        updateEntertainmentInfo()
    }
}

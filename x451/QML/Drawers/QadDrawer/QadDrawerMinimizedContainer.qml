import QtQuick 2.7
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.drawersenums 1.0

Item {
    id: idQADMinimizedContainerItem

    width: (parent ? parent.width : 0)
    height: (parent ? parent.height : 0)

    anchors{
        left: (parent ? parent.left : undefined)
        leftMargin: 770
        top: (parent ? parent.top : undefined)
        topMargin: 70
    }

    /*
     *  ImageField to show the setting icon.
     */
    Image{
        id: idSettingIcon

        width: 84
        height: 84

        anchors{
            left: parent.left
            top: parent.top
            topMargin: 141//211-70
        }

        source: ( enabled
                 ? (prbIsMinimizedDrawerPressed ? "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Settings_7in_n-assets/icon_settings_small_nf.png" : "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Settings_7in_n-assets/icon_settings_small_na.png")
                 : "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_Settings_7in_n-assets/icon_settings_small_nd.png" )
    }

    /*
     *  ImageField to show the icon for connection type BT, AndroidAuto,
     *  AppleCarPlay.
     */
    Image{
        id: idConnectedPhoneProfileIcon

        width: 84
        height: 84

        visible: ( !cppAndroidAutoAdaptor.androidAutoConnectionStatus &&
                  !cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus &&
                  cppPhoneAdaptor.deviceConnected )

        anchors{
            left: parent.left
            top: idSettingIcon.bottom
        }

        // ToDo: Need to use disabled images.
        source: /*cppAndroidAutoAdaptor.androidAutoConnectionStatus
                ? "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_AndroidAuto_7in_n-assets/Gen_Drawer_Ico_AndroidAuto_n.png"
                  : cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus
                  ? "qrc:/image/Drawers/QAD/MiniMized/Contents/Gen_Drawer_Ico_Carplay_7in_n-assets/Gen_Drawer_Ico_Carplay_n.png"
                  : */(cppPhoneAdaptor.deviceConnected
                    ? (enabled
                       ? "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_PhoneMusicPaired_7in_n-assets/Drw_Ico_PhoneMusicPaired_na.png"
                       : "qrc:/image/Drawers/QAD/MiniMized/Contents/Drw_Ico_PhoneMusicPaired_7in_n-assets/Drw_Ico_PhoneMusicPaired_nd.png")
                    :"")


    }

    /*
     * TextField to show the connected Phone name:
     * For BT, AndroidAuto, AppleCarPlay.
     */
    HBText{
        id: idConnectedPhoneNameText

        width: 103
        height: 27

        anchors{
            top: parent.top
            topMargin: 311
        }

        property string prDeviceName: cppPhoneAdaptor.connectedDeviceName

        onPrDeviceNameChanged: {
                updateDeviceNameAllignment()
        }

        function updateDeviceNameAllignment()
        {
            cppDrawersApp.qmlLog("QadDrawerMinimizedContainer.qml: updateDeviceName: " + prDeviceName + "length: " + prDeviceName.length)
            if (prDeviceName.length <= 3)
            {
                idConnectedPhoneNameText.anchors.horizontalCenter = idConnectedPhoneProfileIcon.horizontalCenter
                idConnectedPhoneNameText.horizontalAlignment = Text.AlignHCenter
            }
            else
            {
                idConnectedPhoneNameText.anchors.horizontalCenter = undefined
                idConnectedPhoneNameText.width = 90
                idConnectedPhoneNameText.anchors.left = parent.left
                idConnectedPhoneNameText.anchors.leftMargin = 15
                idConnectedPhoneNameText.horizontalAlignment = Text.AlignLeft
            }
        }

        visible: ( !cppAndroidAutoAdaptor.androidAutoConnectionStatus &&
                  !cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus &&
                  cppPhoneAdaptor.deviceConnected )

        text: /*cppAndroidAutoAdaptor.androidAutoConnectionStatus ?
                  cppPhoneAdaptor.connectedDeviceName
                : cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus ?
                     cppAppleCarPlayAdaptor.appleCarPlayDeviceName
                    : */
              cppPhoneAdaptor.deviceConnected ?
                          cppPhoneAdaptor.connectedDeviceName
                        : ""

        fontType: (enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED)

        Component.onCompleted: {
                updateDeviceNameAllignment()
        }
    }

    /*
     * This Mouse area is used to block the touch during maximize/minimize
     * animation is running.
     */
    MouseArea{
        id: idQADDrawerMouseAreaToBlockTheTouchDuringAnimation

        anchors.fill: parent

        enabled: (prIsQadMinimizeAnimationRunning || prIsQadMaximizeAnimationRunning)

        onClicked: {
            cppDrawersApp.qmlLog("QadDrawerMinimizedContainer.qml: Minimize or Maximize animation is running so No action.")
        }
    }

    Component.onCompleted: {
        cppDrawersApp.qmlLog(
                    "QadDrawerMiniMizeContainer.qml: Component.onCompleted:.")
    }
}

import QtQuick 2.7
import "../../Common"
import QtQuick.Controls 2.2
import com.harman.qml.drawersenums 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0

Item {
    id: idConnectedPhoneInfoItem

    /***********************************************************************************************
     *
     * Connected BT Profile info Button: Shows connected BT profile information: like profile icon
     * and device name.
     *
     ***********************************************************************************************/
    GenericButton {
        id: idConnectedPhoneInfoItemButton
        width: 398
        height: parent.height

        contentItem: Item {
            id: idConnectedPhoneInfoItemButtonContentItem
            anchors.fill: parent

            /*
             * Item used to contain all items which HMI needs to
             * show if only one device connected for both A2DP and HFP profile.
             */
            Item {
                id: idOneDeviceConnectedInfoItem
                anchors.fill: parent

                /*
                 * Image field to show Connected profile icon.
                 */
                Image {
                    id: idConnectedProfileIcon

                    visible: cppPhoneAdaptor.deviceConnected

                    anchors {
                        verticalCenter: parent.verticalCenter
                    }
                   source: (enabled
                            ? (idConnectedPhoneInfoItemButton.pressed
                               ? "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_PhoneMusicPaired_7in_n-assets/Drw_Ico_PhoneMusicPaired_np.png"
                               : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_PhoneMusicPaired_7in_n-assets/Drw_Ico_PhoneMusicPaired_na.png")
                            : "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_PhoneMusicPaired_7in_n-assets/Drw_Ico_PhoneMusicPaired_nd.png")
                }

                /*
                 * Label to show the name of device connected for both A2DP and HFP profile.
                 */
                HBText {
                    id: idConnectedPhoneNameLabel

                    width: 300
                    height: 30


                    anchors {
                        left: idConnectedProfileIcon.right
                        leftMargin: (cppPhoneAdaptor.deviceConnected ? -8 : -57)
                        verticalCenter: parent.verticalCenter
                    }

                    text: cppPhoneAdaptor.deviceConnected ? cppPhoneAdaptor.connectedDeviceName : qsTr("TEXT_QAD_NO_DEVICE_CONNECTED") + cppThemeMgr.languageChanged

                    elide: Text.ElideRight

                    fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                }
            }
        }

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadMaximizedContainer.qml: ConnectedPhoneInfoButton Relased.")
            maxDrawerClicked()
            //Switch to paired devices screen.
            cppPhoneAdaptor.invSwitchToPairedDevices()

        }
    }

    /*
     * vertical Seprator line to seprate BT connection status info and notification info
     */
    Image {
        id: idConnectedPhoneInfoItemVerticalSepratorLine

        anchors {
            left: parent.left
            leftMargin: 408
            verticalCenter: parent.verticalCenter
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LineSeparator2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
    }

    /******************** Bt ConnectionProfile information button End ***********************************/

    /***********************************************************************************************
     *
     * Notification Button: Shows Notifications like missed call notification.
     *
     ***********************************************************************************************/
    HBButtonWithIconAndText {
        id: idNotificationInfoButton

        enabled: (cppPhoneAdaptor.invGetMissedCallCount() > 0)

        onPrTextChanged: {
            enabled = (cppPhoneAdaptor.invGetMissedCallCount() > 0)
        }

        width: 250
        height: parent.height

        anchors {
            left: idConnectedPhoneInfoItemVerticalSepratorLine.right
        }

        prDefaultIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_PhoneCall_7in_n-assets/Gen_Drawer_Ico_PhoneCall_n.png"
        prPressedIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_PhoneCall_7in_n-assets/Gen_Drawer_Ico_PhoneCall_nf.png"
        prDisabledIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_PhoneCall_7in_n-assets/Gen_Drawer_Ico_PhoneCall_nd.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 200
        prTextLeftMargin: 0

        prText: cppPhoneAdaptor.phoneNotificationText + cppThemeMgr.languageChanged

        prEnabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        prDisabledTextFontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED

        prTextVerticalCenter: prIconVerticalCenter

        button.onReleased: {
            cppDrawersApp.qmlLog(
                        "QadMaximizedContainer.qml: Notification InfoButton Relased.")
            if (cppPhoneAdaptor.invGetMissedCallCount() > 0)
            {
                cppPhoneAdaptor.invSwitchToPhoneBrowse(PhoneEnum.PHONE_BROWSE_TYPE_CALL_LOGS)
                maxDrawerClicked()
                cppPhoneAdaptor.invResetUnreadMissedCallInfo();
            }
        }
    }

    /*
     * Seprator line to seprate items in QuickAccess Drawer
     */
    Image {
        id: idConnectedPhoneSepratorLine

        anchors {
            left: parent.left
            bottom: parent.bottom
            bottomMargin: -15
            leftMargin: 8
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LeftLineSeparator_7in_n-assets/Drw_Gfx_LeftLineSeparator_n.png"
    }
    /******************** Notification information button End ***********************************/
}

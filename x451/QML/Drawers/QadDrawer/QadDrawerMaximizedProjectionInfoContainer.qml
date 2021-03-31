import QtQuick 2.7
import QtQuick.Controls 2.2
import "../../Common"
import com.harman.qml.drawersenums 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.phoneenum 1.0

Item {
    id: idProjectionInfoItem

    /*
     * This is the button which will contain information about connected projection.
     * Like it will show the icon of projection and text.
     */
    GenericButton {
        id: idProjectionButton

        width: (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus ? 450 : 260)
        height: parent.height

        enabled: (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus ? !cppPhoneAdaptor.doesCallExist : true)

        contentItem: Item {
            id: idProjectionContentItem

            anchors.fill: parent

            Image {
                id: idProjectionIcon

                anchors{
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }

                source: cppAndroidAutoAdaptor.androidAutoConnectionStatus
                        ? (idProjectionButton.pressed
                           ? "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_AndroidAuto_7in_n-assets/Gen_Drawer_Ico_AndroidAuto_np.png"
                           : "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_AndroidAuto_7in_n-assets/Gen_Drawer_Ico_AndroidAuto_n.png")
                          : (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus
                             ? (enabled
                                ? (idProjectionButton.pressed
                                   ? "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_Carplay_76x76_7in_n-assets/Gen_Drawer_Ico_Carplay_np.png"
                                   : "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_Carplay_76x76_7in_n-assets/Gen_Drawer_Ico_Carplay_n.png")
                                : "qrc:/image/Drawers/QAD/Maximized/Contents/Gen_Drawer_Ico_Carplay_76x76_7in_n-assets/Gen_Drawer_Ico_Carplay_nd.png" )
                              : "" )
            }

            /*
             * Column to show Label "Projection name" and Label "Projection info text"
             */
            Column {
                id: idProjectionInfoTextColumn

                width: 125
                height: (idProjectionNameLabel.height + idConnectedLabel.height + spacing)

                spacing: 5

                anchors {
                    left: parent.left
                    leftMargin: 75
                    verticalCenter: parent.verticalCenter
                }

                /*
                 * Label to show the Projection name text like "Android Auto"
                 */
                HBText {
                    id: idProjectionNameLabel

                    width: contentWidth
                    height: 25

                    text: cppAndroidAutoAdaptor.androidAutoConnectionStatus ?
                              qsTr("TEXT_HOME_SHORTCUT_TITLE_AndroidAuto") + cppThemeMgr.languageChanged
                            : cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus ?
                                  qsTr("TEXT_TITLE_CAR_PLAY") + cppThemeMgr.languageChanged
                                : ""

                    elide: Text.ElideNone
                    fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
                }

                /*
                 * Label to show the Projection info text like "Connected"
                 */
                HBText {
                    id: idConnectedLabel

                    width: contentWidth
                    height: 26

                    enabled: parent.enabled

                    text: (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus
                           ? cppAppleCarPlayAdaptor.appleCarPlayDeviceName + " " + qsTr("TEXT_QAD_CONNECTED_LABEL")
                           : qsTr("TEXT_QAD_CONNECTED_LABEL")) + cppThemeMgr.languageChanged

                    fontType: enabled ? ThemeMgr.FONTTYPE_T24_LIGHT_C3 : ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED

                    elide: Text.ElideNone
                }
            }
        }

        onReleased: {
            cppDrawersApp.qmlLog(
                        "QadDrawerMaximizedContainer.qml: Projection Info button released.")
            if (cppAndroidAutoAdaptor.androidAutoConnectionStatus)
            {
                cppAndroidAutoAdaptor.launchAndroidAuto()
            }
            else if (cppAppleCarPlayAdaptor.appleCarPlayConnectionStatus)
            {
                cppAppleCarPlayAdaptor.launchAppleCarPlay()
            }
            else
            {
                //do nothing.
            }

            maxDrawerClicked()
        }
    }

    /*
     * vertical Seprator line to seprate projection info part and brightness slider.
     */
    Image {
        id: idProjectionVerticalSepratorLine

        visible: cppAndroidAutoAdaptor.androidAutoConnectionStatus

        anchors {
            left: parent.left
            leftMargin: 265
            verticalCenter: parent.verticalCenter
        }
        source: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Gfx_LineSeparator2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
    }

    /***********************************************************************************************
     *
     * Notification Button: Shows Notifications, like missed call and new message notification.
     *
     ***********************************************************************************************/

    HBButtonWithIconAndText {
        id: idNotificationInfoButton

        visible: cppAndroidAutoAdaptor.androidAutoConnectionStatus

        enabled: (cppPhoneAdaptor.invGetMissedCallCount() > 0)

        onPrTextChanged: {
            enabled = (cppPhoneAdaptor.invGetMissedCallCount() > 0)
        }

        width: 294
        height: parent.height

        anchors {
            left: parent.left
            leftMargin: 279
            verticalCenter: parent.verticalCenter
        }

        prDefaultIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_PhoneCall_7in_n-assets/Gen_Drawer_Ico_PhoneCall_n.png"
        prPressedIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_PhoneCall_7in_n-assets/Gen_Drawer_Ico_PhoneCall_nf.png"
        prDisabledIconImage: "qrc:/image/Drawers/QAD/Maximized/Contents/Drw_Ico_PhoneCall_7in_n-assets/Gen_Drawer_Ico_PhoneCall_nd.png"

        isIconOnLeft: true

        prIconLeftMargin: 0
        prIconTopMargin: 0

        prTextWidth: 271
        prTextHeight: 19
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
            }
        }
    }
}

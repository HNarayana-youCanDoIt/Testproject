import QtQuick 2.7
import QtQuick.Layouts 1.3
import "../../../Common"
import com.harman.qml.hvacenums 1.0
import com.harman.qml.thememanager 1.0

Item {
    id: idHvacItemsColumn

    //! Coloumn Separator line image
    Image
    {
        id: idColoumnSepLineImg

        anchors
        {
            left: parent.left
            leftMargin: (cppHVACAdaptor.hvacContainerType === HVACEnums.EN_CONTAINER_TYPE_DUAL_ZONE)
                        ? 597 // 695 - 98
                        : 493 // 675 - 182
            top: parent.top
            topMargin: 38
        }
        source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_RightLineSeparator_v1_7in_n-assets/Drw_Gfx_RightLineSeparator_n.png"
    }

    ColumnLayout
    {
        id: idItemColumn
        width: 76
        height: 435 //((image height(76) * 5) + (item distance(11) * 5))

        anchors
        {
            left: parent.left
            leftMargin: (cppHVACAdaptor.hvacContainerType === HVACEnums.EN_CONTAINER_TYPE_DUAL_ZONE)
                        ? 612 // 710 - 98
                        : 517 // 699 - 182
            top: parent.top
            topMargin: 9
        }

        //! AC Item
        Item
        {
            id: idACItem

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 87
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: cppHVACAdaptor.acPresence

            //! AC button
            GenericButton
            {
                id: idACButton
                width: parent.width
                height: parent.height - 11//(item distance)

                defaultImageURL: (cppHVACAdaptor.acMode)
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_AC_v2_7in_n-assets/Drw_Ico_AC_On_v2_7in_n.png"
                                 : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_AC_v2_7in_n-assets/Drw_Ico_AC_Off_v2_7in_n.png"
                pressedImageURL: (cppHVACAdaptor.acMode)
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_AC_v2_7in_n-assets/Drw_Ico_AC_On_v2_7in_np.png"
                                 : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_AC_v2_7in_n-assets/Drw_Ico_AC_Off_v2_7in_np.png"
                disabledImageURL: (cppHVACAdaptor.acMode)
                                  ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_AC_v2_7in_n-assets/Drw_Ico_AC_On_v2_7in_nd.png"
                                  : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_AC_v2_7in_n-assets/Drw_Ico_AC_Off_v2_7in_nd.png"

                onReleased: {
                    cppDrawersApp.qmlLog(
                                "HvacDrawerDualZoneContainer.qml: idACButton onReleased.")
                    cppHVACAdaptor.toggleAcMode()
                    resetMaxDrawerCloseTimer()
                }
            }

            //! AC Seprator line image
            Image
            {
                id: idACSepLineImg
                anchors
                {
                    left: parent.left
                    leftMargin: 2
                    top: idACButton.bottom
                    topMargin: 5
                }
                source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_RightLineSeparator_v2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
            }
        }

        //! Face Leg Item
        Item
        {
            id: idFaceLegItem

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 87
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: ((cppHVACAdaptor.airFlowPresence) && (cppHVACAdaptor.zoneType == HVACEnums.HVAC_DUAL_ZONE))

            //! Face Leg button
            GenericButton
            {
                id: idFaceLegButton
                width: parent.width
                height: parent.height - 11//(item distance)

                defaultImageURL: (HVACEnums.HVAC_DM_CHEST_MODE === cppHVACAdaptor.distributionMode)
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_Face_7in_n.png"
                                 : (HVACEnums.HVAC_DM_CHESTLEG_MODE === cppHVACAdaptor.distributionMode)
                                   ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_FaceLeg_7in_n.png"
                                   : (HVACEnums.HVAC_DM_LEG_MODE === cppHVACAdaptor.distributionMode)
                                     ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_Leg_7in_n.png"
                                     : (HVACEnums.HVAC_DM_LEGDEFROST_MODE === cppHVACAdaptor.distributionMode)
                                       ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_Defrost_Leg_7in_n.png"
                                       : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_DefrostLowMax_7in_n.png"

                pressedImageURL: (HVACEnums.HVAC_DM_CHEST_MODE === cppHVACAdaptor.distributionMode)
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_Face_7in_np.png"
                                 : (HVACEnums.HVAC_DM_CHESTLEG_MODE === cppHVACAdaptor.distributionMode)
                                   ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_FaceLeg_7in_np.png"
                                   : (HVACEnums.HVAC_DM_LEG_MODE === cppHVACAdaptor.distributionMode)
                                     ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_Leg_7in_np.png"
                                     : (HVACEnums.HVAC_DM_LEGDEFROST_MODE === cppHVACAdaptor.distributionMode)
                                       ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_Defrost_Leg_7in_np.png"
                                       : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_DefrostLowMax_7in_np.png"

                disabledImageURL: (HVACEnums.HVAC_DM_CHEST_MODE === cppHVACAdaptor.distributionMode)
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_Face_7in_nd.png"
                                 : (HVACEnums.HVAC_DM_CHESTLEG_MODE === cppHVACAdaptor.distributionMode)
                                   ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_FaceLeg_7in_nd.png"
                                   : (HVACEnums.HVAC_DM_LEG_MODE === cppHVACAdaptor.distributionMode)
                                     ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_Leg_7in_nd.png"
                                     : (HVACEnums.HVAC_DM_LEGDEFROST_MODE === cppHVACAdaptor.distributionMode)
                                       ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_Defrost_Leg_7in_nd.png"
                                       : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_FaceLeg_7in_n-assets/Drw_Ico_DefrostLowMax_7in_nd.png"


                onReleased: {
                    cppDrawersApp.qmlLog(
                                "HvacDrawerDualZoneContainer.qml: idFaceLegButton onReleased.")
                    cppHVACAdaptor.increaseDistributionMode()
                    resetMaxDrawerCloseTimer()
                }
            }

            //! Face Leg Seprator line image
            Image
            {
                id: idFaceLegSepLineImg
                anchors
                {
                    left: parent.left
                    leftMargin: 2
                    top: idFaceLegButton.bottom
                    topMargin: 5
                }
                source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_RightLineSeparator_v2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
            }
        }

        //! Defrost Low Max Item
        Item
        {
            id: idDefrostLowMaxItem

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 87
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: cppHVACAdaptor.defrostPresence

            /*
             * Defrost Low Max button.
             */
            GenericButton
            {
                id: idDefrostLowMaxButton
                width: parent.width
                height: parent.height - 11//(item distance)

                defaultImageURL: cppHVACAdaptor.maxDefrostMode
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax_n.png"
                                 : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax2_n.png"

                pressedImageURL: cppHVACAdaptor.maxDefrostMode
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax_np.png"
                                 : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax2_np.png"

                disabledImageURL: cppHVACAdaptor.maxDefrostMode
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax_nd.png"
                                 : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Ico_DefrostLowMax_7in_n-assets/Gen_Drawer_Ico_DefrostLowMax2_nd.png"


                onReleased: {
                    cppDrawersApp.qmlLog(
                                "HvacDrawerDualZoneContainer.qml: idDefrostLowMaxButton onReleased.")
                    cppHVACAdaptor.setHVACParameter(HVACEnums.HUCCM_MAX_DEFRST, !cppHVACAdaptor.maxDefrostMode)
                    resetMaxDrawerCloseTimer()
                }
            }

            //! Defrost Low Max Seprator line image
            Image
            {
                id: idDefrostLowMaxSepLineImg
                anchors
                {
                    left: parent.left
                    leftMargin: 2
                    top: idDefrostLowMaxButton.bottom
                    topMargin: 5
                }
                source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_RightLineSeparator_v2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
            }
        }

        //! Fresh Air Item
        Item
        {
            id: idFreshAirItem

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 87
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: cppHVACAdaptor.freshAirPresence

            //! Fresh Air button
            GenericButton
            {
                id: idFreshAirButton
                width: parent.width
                height: parent.height - 11//(item distance)

                defaultImageURL: (HVACEnums.HVAC_AIRCIRCULATION_FRESHIR_ON === cppHVACAdaptor.airCirculationMode) ?
                                     "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_FreshAir_n.png"
                                   : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_RecirculatedAir_n.png"
                pressedImageURL: (HVACEnums.HVAC_AIRCIRCULATION_FRESHIR_ON === cppHVACAdaptor.airCirculationMode) ?
                                     "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_FreshAir_nf.png"
                                   : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_RecirculatedAir_nf.png"
                disabledImageURL: (HVACEnums.HVAC_AIRCIRCULATION_FRESHIR_ON === cppHVACAdaptor.airCirculationMode) ?
                                      "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_FreshAir_nd.png"
                                   : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_FreshAir_7in_n-assets/Gen_Drawer_Ico_RecirculatedAir_nd.png"
                onReleased: {
                    cppDrawersApp.qmlLog(
                                "HvacDrawerDualZoneContainer.qml: idFreshAirButton onReleased.")
                    cppHVACAdaptor.toggleAirCirculationMode()
                    resetMaxDrawerCloseTimer()
                }
            }

            //! Fresh Air Seprator line image
            Image
            {
                id: idFreshAirSepLineImg
                anchors
                {
                    left: parent.left
                    leftMargin: 2
                    top: idFreshAirButton.bottom
                    topMargin: 5
                }
                source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_RightLineSeparator_v2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
            }
        }

        //! Xpress Cool Item
        Item
        {
            id: idXpressCoolItem

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 87
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: cppHVACAdaptor.xpressCoolingPresence

            //! Xpress Cool button
            GenericButton
            {
                id: idXpressCoolButton
                width: parent.width
                height: parent.height - 11//(item distance)

                defaultImageURL: cppHVACAdaptor.xpressCoolMode
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_On_n.png"
                                 : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_Off_n.png"

                pressedImageURL: cppHVACAdaptor.xpressCoolMode
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_On_np.png"
                                 : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_Off_np.png"

                disabledImageURL: cppHVACAdaptor.xpressCoolMode
                                  ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_On_nd.png"
                                  : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Xpresscool_7in_n-assets/Gen_Drawer_Ico_XPRESS COOL_Off_nd.png"
                onReleased: {
                    cppDrawersApp.qmlLog(
                                "HvacDrawerDualZoneContainer.qml: idXpressCoolButton onReleased.")
                    cppHVACAdaptor.invToggleXpressCoolMode()
                    resetMaxDrawerCloseTimer()
                }
            }

            //! Xpress Cool Seprator line image
            Image
            {
                id: idXpressCoolSepLineImg
                anchors
                {
                    left: parent.left
                    leftMargin: 2
                    top: idXpressCoolButton.bottom
                    topMargin: 5
                }
                source: "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_RightLineSeparator_v2_7in_n-assets/Gen_Gfx_LineSeparator2_n.png"
            }
        }

        //! Econ Item
        Item
        {
            id: idEconItem

            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 87
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: cppHVACAdaptor.econPresence

            //! Xpress Cool button
            GenericButton
            {
                id: idEconButton
                width: parent.width
                height: parent.height - 11//(item distance)

                defaultImageURL: cppHVACAdaptor.ecoAcMode
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Econ_7in_n-assets/Drw_Ico_Econ_7in_On_n.png"
                                 : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Econ_7in_n-assets/Drw_Ico_Econ_7in_Off_n.png"

                pressedImageURL: cppHVACAdaptor.ecoAcMode
                                 ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Econ_7in_n-assets/Drw_Ico_Econ_7in_On_np.png"
                                 : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Econ_7in_n-assets/Drw_Ico_Econ_7in_Off_np.png"

                disabledImageURL: cppHVACAdaptor.ecoAcMode
                                  ? "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Econ_7in_n-assets/Drw_Ico_Econ_7in_On_nd.png"
                                  : "qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/Drw_Ico_Econ_7in_n-assets/Drw_Ico_Econ_7in_Off_nd.png"
                onReleased: {
                    cppDrawersApp.qmlLog(
                                "HvacDrawerDualZoneContainer.qml: idXpressCoolButton onReleased.")
                    cppHVACAdaptor.toggleEcoAcMode()
                    resetMaxDrawerCloseTimer()
                }
            }
        }
    }
}

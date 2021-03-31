import QtQuick 2.7
import "../../Common"
import com.harman.qml.thememanager 1.0
import com.harman.qml.hvacenums 1.0

Item {
    id: idClimateInfoItem

    /*
     * ClimateStausIcon: This will show the climet status, Like if climate is
     * ON, This will show climate on icon, else climateOff icon.
     */
    Image{
        id: idClimateStatusIcon

        width: 40
        height: 40

        visible: ((cppHVACAdaptor.xpressCoolMode) ?
                      ((cppHVACAdaptor.ctrlPanelMode) ? false : true)
                    : true)

        source: cppHVACAdaptor.ctrlPanelMode ? "qrc:/image/Drawers/HeaderStatusBar/HVAC/Sts_Ico_HVAC_7in_n-assets/Sts_Ico_HVAC_n.png" : "qrc:/image/Drawers/HeaderStatusBar/HVAC/Sts_Ico_HVAC_7in_n-assets/Sts_Ico_HVAC_nd.png"
    }

    /*
     * This item contains Fan Icon, Fan speed text, Temperature text and °C
     * text. This item is needed because we have to make the visibility of this
     * Item's content item's to false if climate is off.
     */
    Item {
        id: idFanTemperatureDetailsItem


        visible: (cppHVACAdaptor.ctrlPanelMode && !cppHVACAdaptor.xpressCoolMode)

        width: 130
        height: 40

        anchors{
            left: idClimateStatusIcon.right
            leftMargin: 9 // 651 (X of idFanTemperatureDetailsItem) - (602 (X of idClimateStatusIcon) + 40 (width of idClimateStatusIcon))
        }

        /*
        * IFanIcon: Image field to show the fan icon.
        */
        Image{
            id: idFanIcon
            visible: (!cppHVACAdaptor.autoMode && (cppHVACAdaptor.errorStatus !== HVACEnums.HVAC_ERROR))
            source: "qrc:/image/Drawers/HeaderStatusBar/HVAC/Sts_Ico_FanSpeed_7in_n-assets/Sts_Ico_FanSpeed_n.png"
        }

        /*
        * TextField to show the fan speed.
        */
        HBText{
            id: idFanSpeedText

            width: (cppHVACAdaptor.autoMode || (cppHVACAdaptor.errorStatus === HVACEnums.HVAC_ERROR))
                   ? 70 : 30
            height: 20

            anchors {
                left: (cppHVACAdaptor.autoMode || (cppHVACAdaptor.errorStatus === HVACEnums.HVAC_ERROR))
                      ? parent.left : idFanIcon.right
                verticalCenter: idFanIcon.verticalCenter
            }

            text: ((cppHVACAdaptor.errorStatus === HVACEnums.HVAC_ERROR) ? qsTr("Error!")
                                              : (cppHVACAdaptor.autoMode ?
                                                     qsTr("AUTO") :
                                                     cppHVACAdaptor.fanSpeed)) + cppThemeMgr.languageChanged

            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2

        }

        /*
         * TextField to show the temperature.
         */
        HBText{
            id: idTemperatureText

            width: 43
            height: 20

            visible: (cppHVACAdaptor.errorStatus !== HVACEnums.HVAC_ERROR)

            anchors {
                left: idFanSpeedText.right
                verticalCenter: parent.verticalCenter
            }

            /*
             * The toFixed() method converts a number into a string, keeping a
             * specified number of decimals.
             * Here we are showing 1 value after decimal
             */
            text: cppHVACAdaptor.temperature.toFixed(1)+ cppThemeMgr.languageChanged

            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        }


        /*
     * TextField to show the DegreeC.
     */
        HBText{
            id: idDegreeCText

            anchors{
                left: idTemperatureText.right
                top: idTemperatureText.top
            }

            visible: (cppHVACAdaptor.errorStatus !== HVACEnums.HVAC_ERROR)

            width: 30
            height: 20

            text: qsTr("°C") + cppThemeMgr.languageChanged

            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        }
    }

    /*
     * Text Field to show climate Off text, when climate is off.
     */
    HBText {
        id: idClimateOffText

        width: 130
        height: 25

        anchors{
            left: idClimateStatusIcon.right
            leftMargin: 6
            verticalCenter: idClimateStatusIcon.verticalCenter

        }

        visible: !cppHVACAdaptor.ctrlPanelMode

        text: qsTr("Climate Off") + cppThemeMgr.languageChanged

        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
    }

    /*
     * XpressCoolItem: This will show the xpress cool status, will be displayed if xpress cooling active.
     */
    Item {
        id: idXpressCoolItem
        visible: (cppHVACAdaptor.xpressCoolMode && cppHVACAdaptor.ctrlPanelMode)

        anchors{
            left: idClimateStatusIcon.left
            top: idClimateStatusIcon.top
        }
        /*
     * XpressCoolStatusIcon: This will be displayed if express cool is active..
     */
        Image{
            id: idXpressCoolStatusIcon

            width: 40
            height: 40

            source: "qrc:/image/Drawers/HeaderStatusBar/HVAC/Sts_Ico_Xpresscool_7in_n/Sts_Ico_Xpresscool_7in_n.png"
        }

        /*
     * Text Field to show xpress cool text, when express cool is active.
     */
        HBText {
            id: idXpressCoolText

            width: 130
            height: 25

            anchors{
                left: idXpressCoolStatusIcon.right
                leftMargin: 6
                verticalCenter: idXpressCoolStatusIcon.verticalCenter

            }

            visible: cppHVACAdaptor.xpressCoolMode

            text: qsTr("Xpress Cool") + cppThemeMgr.languageChanged

            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
        }
    }

}

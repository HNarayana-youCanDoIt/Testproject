/**
 * @file            CmpTripGeneralInfo.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * CmpTripGeneralInfo, a comopnent can use to show general information on DriveNext main screen,
 * It has Title, Value and Unit text fields to show information.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0

Item {
    width: 225
    height: 56

    property alias prTitleText: idTitleText.text // property used to set title text
    property alias prValueText: idValueText.text // property used to set value text
    property alias prUnitText: idUnitText.text // property used to set unit text

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Title text field
     */
    HBText {
        id: idTitleText
        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }
        width: 225
        height: 20
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
        horizontalAlignment: Text.AlignHCenter

        text: "Title"
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Value text field
     */
    HBText {
        id: idValueText
        anchors {
            bottom: parent.bottom
            right: parent.horizontalCenter
            rightMargin: 5
        }
        width: 100
        height: 23
        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: Text.AlignRight

        text: "Value"


        /////////////////////////////////////////////////////////////////////////////////
        /**
         * Unit text field
         */
        HBText {
            id: idUnitText
            anchors {
                bottom: parent.bottom
                left: parent.right
                leftMargin: 10
            }
            width: 100
            height: 20
            fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
            horizontalAlignment: Text.AlignLeft

            text: "Units"
        }
    }
}

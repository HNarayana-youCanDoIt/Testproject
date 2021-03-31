/**
 * @file            CmpTripPerformanceBreakupElement.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * CmpTripPerformanceBreakupElement, a comopnent can use to show trip performance breakup element on trip performance breakup screens,
 * It has Title, Value and Unit text fields to show information.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0

Item {
    width: 400
    height: 56

    property alias prTitleText: idTitleText.text // property used to set title text
    property alias prValueText01: idValueText01.text // property used to set value 1st text
    property alias prUnitText01: idUnitText01.text // property used to set unit 1st text
    property alias prValueText02: idValueText02.text // property used to set value 2nd text
    property alias prUnitText02: idUnitText02.text // property used to set unit 2nd text

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Title text field
     */
    HBText {
        id: idTitleText
        anchors {
            bottom: parent.bottom
            bottomMargin: 18
            left: parent.left
            leftMargin: 12
        }
        width: 250
        height: 20
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3

        text: "Title"
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Unit text field
     */
    HBText {
        id: idUnitText01
        anchors {
            bottom: parent.bottom
            bottomMargin: 18
            right: parent.right
            rightMargin: -14
        }
        height: 20
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
        horizontalAlignment: Text.AlignRight

        text: "Units"
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Value text field
     */
    HBText {
        id: idValueText01
        anchors {
            bottom: parent.bottom
            bottomMargin: 18
            right: idUnitText01.left
        }
        height: 23
        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: Text.AlignRight

        text: "Value"
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Unit text field
     */
    HBText {
        id: idUnitText02
        anchors {
            bottom: parent.bottom
            bottomMargin: 18
            right: idValueText01.left
            rightMargin: 10
        }
        height: 20
        fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3_DISABLED
        horizontalAlignment: Text.AlignRight

        text: "Units"
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * Value text field
     */
    HBText {
        id: idValueText02
        anchors {
            bottom: parent.bottom
            bottomMargin: 18
            right: idUnitText02.left
        }
        height: 23
        fontType: ThemeMgr.FONTTYPE_T35_C3
        horizontalAlignment: Text.AlignRight

        text: "Value"
    }
}

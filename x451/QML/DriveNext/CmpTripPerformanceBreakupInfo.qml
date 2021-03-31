/**
 * @file            CmpTripPerformanceBreakupInfo.qml
 * @ingroup         QmlComponent
 * @author          Nandkishor Lokhande
 * CmpTripPerformanceBreakupInfo, a comopnent can use to show trip performance breakup information on trip performance breakup screens,
 * It has Title, Value and Unit text fields to show information.
 */

import QtQuick 2.7
import QtQuick.Controls 2.2
import "../Common"
import com.harman.qml.thememanager 1.0

/////////////////////////////////////////////////////////////////////////////////
/**
 * Information Layout
 */
Item {
    anchors {
        fill: parent
    }

    /**
     * property used to set elements values
    */
    property alias prElement01: idPerformanceBreakupElement01
    property alias prElement02: idPerformanceBreakupElement02
    property alias prElement03: idPerformanceBreakupElement03
    property alias prElement04: idPerformanceBreakupElement04

    /**
     * Information Layout Background
     */
    Image {
        anchors {
            left: parent.left
            leftMargin: 182
            top: parent.top
            topMargin: 213
        }
        width: 440
        height: 263
        source: "qrc:/image/DriveNext/Gen_Gfx_DriveProBg_7inch_n-assets/Gen_Gfx_DriveProBg_7inch_n.png"

        Column {
            anchors {
                fill: parent
            }

            spacing: 0
            CmpTripPerformanceBreakupElement {
                id: idPerformanceBreakupElement01
            }
            CmpTripPerformanceBreakupElement {
                id: idPerformanceBreakupElement02
            }
            CmpTripPerformanceBreakupElement {
                id: idPerformanceBreakupElement03
            }
            CmpTripPerformanceBreakupElement {
                id: idPerformanceBreakupElement04
            }
        }
    }
}

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import "qrc:/QML/Common"

Item {
    id: idTunerPresetLists

    width: 385
    height: 68
    property int iPresetListPageIndex: cppTunerAdaptor.iPresetListPageIndex
    property int iPresetListPages: 4

    // Preset list color patch background image


    // Preset list color patch background image
    Image {
        id: idColorPatchBackgrond
        anchors.top: parent.top
        source: "qrc:/image/Tuner/Tun_Gfx_PresetBG-assets/Radio_Gfx_Plate_ColourPatch_n.png"
        ColorOverlay {
            id: idPresetButtonColorOverlay
            anchors.fill: parent
            source: parent
            color:  cppThemeMgr.currentThemeColor
        }
    }

    // Preset list background image
    Image {
        id: idPresetListBackground
        anchors{
            top: parent.top
            left: parent.left
            leftMargin: 33
        }

        source: "qrc:/image/Tuner/Tun_Gfx_PresetBG-assets/Tun_Gfx_PresetBG.png"
    }

    Image {
        id: idBackgrondShadow
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 27
        }
        source: "qrc:/image/Tuner/Tun_Gfx_PresetBG-assets/Tun_Gfx_PresetBGShadow_n.png"
    }

    /////////////////////////////////////////////////////////////////////////////////
    /*
     * SwipeView used to show preset list pages, each page is created from /TunerPresetTiles.qml
     */
    SwipeView {
        id: idPresetListSwipeView
        clip: true // fixMe : need to remove clip
        width: 324
        height: 68
        anchors {
            left: parent.left
            leftMargin: 31
        }

        currentIndex: iPresetListPageIndex

        /*
         * Repeater used to create preset list pages
         */
        Repeater {
            id: idPresetListRepeator

            /** We are creating 4 pages of 5 presets each since 20 presets are supported */
            model: iPresetListPages
            delegate: TunerPresetTiles {
                property int presetPageIndex : SwipeView.index
            }
        }

        onCurrentIndexChanged: {
            cppTunerAdaptor.iPresetListPageIndex = currentIndex
        }
    }

    /*
    * FixMe: Need to fix patch
    * To hide the separator in the last preset block we are putting this image over the preset list
    * Below image is right side part of the background image idPresetListBackground
    */
    Image {
        id: idRightSideBackgroundMask
        anchors.left: parent.left
        source: "qrc:/image/Tuner/Tun_Gfx_PresetBG-assets/Radio_Gfx_Plate_Left_n.png"
    }
}

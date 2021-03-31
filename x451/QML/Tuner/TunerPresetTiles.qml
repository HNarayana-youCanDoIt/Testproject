import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.tunerenums 1.0
import com.harman.qml.thememanager 1.0
import "qrc:/QML/Common"

Item {
    id: idPresetList
    width: 325
    height: 61

    /*
     * Property holds the number of preset per preset page
     */
    property int prPresetPerPage: 5

    /*
     * Row used to show preset tiles in required layout
     */
    Row {
        id: idTunertiles

        width: 325
        height: 61
        topPadding: 3

        /*
         * Repeater used to add preset tiles in preset list row
         */
        Repeater {
            id: repeater
            model: prPresetPerPage

            /*
            * Generic button will be used as preset tiles.
            * User can store preset in these tiles using long press.
            * user can select preset tile by clicking.
            */
            GenericButton {
                id: idPresetButton

                height: 61
                width: 65
                prEnableColorOverlay: (tileIndex === cppTunerAdaptor.iActivePresetIndex)

                property int tileIndex: ((prPresetPerPage * presetPageIndex) + index)
                enabled: !((TunerEnums.SEEK_SCAN_UP === cppTunerAdaptor.eSeekType && cppTunerAdaptor.uiTagId === 0) || TunerEnums.SEEK_FULL_AUTOSTORE === cppTunerAdaptor.eSeekType)

                defaultImageURL: (cppTunerAdaptor.liPresetTilesList[tileIndex] === "")
                                 ? "qrc:/image/Tuner/Tun_Ico_AddStation-assets/Tun_Ico_Addstation_na.png"
                                 : ((tileIndex === cppTunerAdaptor.iActivePresetIndex)
                                    ? "qrc:/image/Tuner/Tun_Gfx_RadioTile_n-assets/Gen_Gfx_RadioTile_n.png" : "")
                pressedImageURL: (cppTunerAdaptor.liPresetTilesList[tileIndex] === "")
                                 ? "qrc:/image/Tuner/Tun_Ico_AddStation-assets/Tun_Ico_Addstation_nf.png"
                                 : ((tileIndex === cppTunerAdaptor.iActivePresetIndex)
                                    ? "qrc:/image/Tuner/Tun_Gfx_RadioTile_n-assets/Gen_Gfx_RadioTile_n.png" : "")
                disabledImageURL: (cppTunerAdaptor.liPresetTilesList[tileIndex] === "")
                                  ? "qrc:/image/Tuner/Tun_Ico_AddStation-assets/Tun_Ico_Addstation_nd.png"
                                  : ((tileIndex === cppTunerAdaptor.iActivePresetIndex)
                                     ? "qrc:/image/Tuner/Tun_Gfx_RadioTile_n-assets/Gen_Gfx_RadioTile_n.png" : "")

                text: cppTunerAdaptor.liPresetTilesList[tileIndex]


                contentItem: HBText
                {
                    id: idPresetTileText
                    fontType: (parent.enabled) ? ThemeMgr.FONTTYPE_T24_LIGHT_C2 : ThemeMgr.FONTTYPE_T24_LIGHT_C2_DISABLED
                    visible: (text !== "")

                    anchors{
                        top: parent.top
                        topMargin: 6
                    }

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: parent.text
                    elide: HBText.ElideNone
                }

                /** Button click and longpress handling */
                onReleased:{
                    if(!touchAndHold)
                    {
                        cppTunerApp.qmlLog("TunerScreen.qml : request preset select")
                        cppTunerAdaptor.selectPreset(tileIndex)
                    }
                }

                onPressAndHold:{
                    cppTunerApp.qmlLog("TunerScreen.qml : request preset store")
                    if((TunerEnums.SEEK_AUTOSEEK_UP !== cppTunerAdaptor.eSeekType && TunerEnums.SEEK_AUTOSEEK_DOWN !== cppTunerAdaptor.eSeekType)){
                        cppTunerAdaptor.storePreset(tileIndex)
                    }
                }

                /** Separator image to separate two preset tile */
                Image {
                    id: idTileSeparator

                    anchors {
                        right: parent.right
                        rightMargin: -1
                        verticalCenter: parent.verticalCenter
                    }

                    source: "qrc:/image/Tuner/Gen_Gfx_Divider_n/Gen_Gfx_Divider_n.png"
                }
            }
        }
    }
}

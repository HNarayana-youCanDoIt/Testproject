import QtQuick 2.7
import QtQuick.Controls 2.2
import com.harman.qml.tunerenums 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.popupenums 1.0
import com.harman.qml.diagnosticenums 1.0
import QtGraphicalEffects 1.0
import "qrc:/QML/Common"

Item {
    id: idTunerManualSeekBar
    width: 492
    height: 110

    /** Property holds color code for freq bars */
    readonly property string prFreqBarColorCode: "#696969"

    /** property holds whether the manual scale loading completed or not. */
    property bool prIsManualScaleLoadingComplete: false

    /** property holds type of change by which manaul seek started */
    property int prCurrIndexChangeByType: TunerEnums.CHANGE_INVALID

    /** Property holds tuner's previously played frequency index */
    property int prTunerManualScalePreviousIndex: 0

    /** Property holds tuner's last frequency index for FM */
    readonly property int prFMManualScaleLastIndex: 205

    /** Property holds tuner's first frequency index for FM */
    readonly property int prFMManualScaleFirstIndex: 0

    /**
    * Center line of manual scale is not current index of path view.
    * Difference between manual scale center index and pathview current index is 10.
    * Below property holds that factor.
    */
    property int prManualScaleIndexFactor: 10


    /** Manual seek drag area */
    Rectangle {
        id: idPathViewItem
        width: 492
        height: 110
        color: "transparent"

        /** Delegate for manual scale's pathview */
        Component {
            id: idPathViewDelegate

            /** frequency line item for manual scale consist two lines */
            Item {
                id: idFreqLine
                anchors.top: parent.top
                width: idPathViewItem.width / idPathView.pathItemCount
                height: idPathViewItem.height
                property int freqValue: scaleHandFreqRole

                /** white line in middle of frequency line item */
                Rectangle {
                    id: idWhiteLine
                    width: 6
                    height: scaleHandHeightRole
                    color: prFreqBarColorCode
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        bottom: parent.bottom
                        bottomMargin: 5
                    }
                }
                MouseArea{
                    id: idFreqLineMouseArea
                    anchors.fill: parent
                    onReleased: {
                        cppTunerApp.qmlLog("TunerManualSeek.qml : manual scale mouse area clicked")

                        prCurrIndexChangeByType = TunerEnums.CHANGE_BY_CLICK

                        /*
                         * Center line of manual scale is not the current index of path view but it is caliberated
                         * in such way that it appeares to be the current index of path way.
                         * Difference between manual scale center index and pathview current index is 10.
                         * Below logic is to find the index to be set when user click on any line of manual scale.
                         */
                        /** Property hold the new index to be set for manual scale */
                        var newIndex = index - prManualScaleIndexFactor

                        cppTunerApp.qmlLog("TunerManualSeek.qml : manual scale mouse area clicked and index is " + index + "  " + newIndex)

                        /**
                         * In tuner's FM band frequency range is between 87.5 to 108.0, but for round robin operation for manaul scale
                         * we have 4 we need to add four more frequency line in the end of scale to complete the scale.
                         * So in case of FM band we have 4 extra frequency which user should not select.
                         * Below logic is to set FM max freq or min freq when user select frequency between 108.1 to 108.4
                         */
                        if(TunerEnums.BAND_FM === cppTunerAdaptor.eBandType){
                            if(index > 5 && index < 10){
                                if(idPathView.currentIndex > 195)
                                    idPathView.currentIndex = 0
                                else
                                    idPathView.currentIndex = 205
                            }
                            else{
                                idPathView.currentIndex = newIndex
                            }
                        }
                        else if(idPathView.currentIndex !== newIndex){
                            idPathView.currentIndex = newIndex
                        }
                        else{
                            cppTunerApp.qmlLog("TunerManualSeek.qml : selected is already current index")
                        }
                    }
                }
            }
        }

        /*
         * binding tuner adaptors iManualScaleIndex value with pathview's current index
         */
        Binding {
            target: idPathView
            property: "currentIndex"
            value: cppTunerAdaptor.iManualScaleIndex
        }

        /** Path view for manaul scale to drag or move frequncy line to select frequency */
        PathView {
            id: idPathView

            anchors{
                fill: parent
                left: parent.left
                leftMargin: 33
            }
            enabled: (TunerEnums.SEEK_NONE === cppTunerAdaptor.eSeekType)
            model: cppTunerAdaptor.pTunerManualScaleListModel
            delegate: idPathViewDelegate
            flickDeceleration: 100
            pathItemCount: 20
            cacheItemCount: 10
            maximumFlickVelocity: 200

            /** path for frequency line movement */
            path: Path {
                startX: 39
                startY: 0
                PathLine {
                    x: 386
                    y: 0
                }
            }

            onModelChanged: {
                cppTunerApp.qmlLog("TunerManualSeek.qml : onModelChanged index : " +  cppTunerAdaptor.iManualScaleIndex)
                if(prIsManualScaleLoadingComplete){
                    cppTunerApp.qmlLog("TunerManualSeek.qml : onModelChanged : positionViewAtIndex")
                    positionViewAtIndex(cppTunerAdaptor.iManualScaleIndex, PathView.Beginning)
                }
            }

            onDragStarted: {
                cppTunerApp.qmlLog("TunerManualSeek.qml : onDragStarted")
                cppTunerAdaptor.setManualSeekBlockStatus(false)
            }

            onMovementStarted: {
                cppTunerApp.qmlLog("TunerManualSeek.qml : onMovementStarted")
                prCurrIndexChangeByType = TunerEnums.CHANGE_BY_DRAG
            }
            onMovementEnded: {
                cppTunerApp.qmlLog("TunerManualSeek.qml : onMovementEnded")
                prCurrIndexChangeByType = TunerEnums.CHANGE_INVALID

                /**
                 * In tuner's FM band frequency range is between 87.5 to 108.0, but for round robin operation for manaul scale
                 * we have 4 we need to add four more frequency line in the end of scale to complete the scale.
                 * So in case of FM band we have 4 extra frequency which user should not select.
                 * Below logic is to set FM max freq or min freq when user stop draging manual scale between frequency's 108.1 to 108.4
                 */
                if(TunerEnums.BAND_FM === cppTunerAdaptor.eBandType){
                    if(currentIndex > prFMManualScaleLastIndex){
                        if(prTunerManualScalePreviousIndex === prFMManualScaleLastIndex){
                            prCurrIndexChangeByType = TunerEnums.CHANGE_BY_CLICK
                            currentIndex = 0
                        }
                        else if(prTunerManualScalePreviousIndex === prFMManualScaleFirstIndex){
                            prCurrIndexChangeByType = TunerEnums.CHANGE_BY_CLICK
                            currentIndex = 205
                        }
                    }
                }

                prTunerManualScalePreviousIndex = currentIndex
            }

            onCurrentIndexChanged: {
                cppTunerApp.qmlLog("TunerManualSeek.qml : onCurrentIndexChanged current index : " + currentIndex)

                if ((TunerEnums.CHANGE_INVALID !== prCurrIndexChangeByType) && (TunerEnums.BAND_AM === cppTunerAdaptor.eBandType
                                                                                || currentIndex <= prFMManualScaleLastIndex)){
                    cppTunerApp.qmlLog("TunerManualSeek.qml : onCurrentIndexChanged manual seek request")

                    cppTunerAdaptor.startManualSeek(currentItem.freqValue)

                    if(TunerEnums.CHANGE_BY_DRAG !== prCurrIndexChangeByType){
                        prCurrIndexChangeByType = TunerEnums.CHANGE_INVALID
                    }

                    prTunerManualScalePreviousIndex = currentIndex
                }
                else{
                    cppTunerApp.qmlLog("TunerManualSeek.qml : Index change is due to seek started from service side.")
                }
            }
            Component.onCompleted: {
                cppTunerApp.qmlLog("TunerManualSeek.qml : Component.onCompleted")
                positionViewAtIndex(cppTunerAdaptor.iManualScaleIndex, PathView.Beginning)
                prIsManualScaleLoadingComplete = true
            }
        }

        Image {
            id: idManualScaleMaskOverlay
            anchors.fill: parent
            source: "qrc:/image/Tuner/Tun_Gfx_FrequecyMask-assets/Tun_Gfx_FrequecyMask_Overlay_7in_Bg.png"
        }

        /** Frequency needle image to indicate the current frequency */
        Image {
            id: idManualScaleNeedle
            source: "qrc:/image/Tuner/Tun_Gfx_FrequecyMask-assets/Tun_Gfx_FrequecyCenterNeedle_na.png"
            anchors.fill: parent

            ColorOverlay {
                id: idManualScaleNeedleColorOverlay
                anchors.fill: parent
                source: parent
                color:  cppThemeMgr.currentThemeColor
            }
        }
    }

    Connections{
        target: cppHardkeyAdaptor

        onSigRotaryUpdate: {
            cppTunerApp.qmlLog("TunerManualSeekBar.qml : right rotary rotated")

            cppTunerAdaptor.setManualSeekBlockStatus(false)
            if(TunerEnums.SEEK_NONE === cppTunerAdaptor.eSeekType && cppTunerAdaptor.isTunerAntennaConnected()){
                if(HardkeyEnum.KEYCODEHK_MENUROTARY_KNOB === iKeyCode){
                    if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState){
                        prCurrIndexChangeByType = TunerEnums.CHANGE_BY_ROTARY

                        /**
                         * Setting currentIndex to last index of FM manual scale if the previous index is first and user is rotating
                         * rotary in anti clockwise direction.
                         */
                        if(TunerEnums.BAND_FM === cppTunerAdaptor.eBandType
                                && prFMManualScaleFirstIndex === prTunerManualScalePreviousIndex){
                            idPathView.currentIndex = 205
                        }
                        else{
                            idPathView.currentIndex = idPathView.currentIndex - 1
                        }
                    }
                    else if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState){
                        prCurrIndexChangeByType = TunerEnums.CHANGE_BY_ROTARY

                        /**
                         * Setting currentIndex to first index of FM manual scale if the previous index is last and user is rotating
                         * rotary in clockwise direction.
                         */
                        if(TunerEnums.BAND_FM === cppTunerAdaptor.eBandType
                                && prFMManualScaleLastIndex === prTunerManualScalePreviousIndex){
                            idPathView.currentIndex = 0
                        }
                        else{
                            idPathView.currentIndex = idPathView.currentIndex + 1
                        }
                    }
                    else{
                        cppTunerApp.qmlLog("TunerManualSeek.qml: onSigRotaryUpdate: not a valid iKeyState : " + iKeyState)
                    }
                }
                else{
                    cppTunerApp.qmlLog("TunerManualSeek.qml: onSigRotaryUpdate: not a valid iKeyCode : " + iKeyCode)
                }
            }
            else{
                cppTunerApp.qmlLog("TunerManualSeek.qml : manual seek disabled")
            }

        }
    }

    /**
     * Mouse area will be enabled if the antenna is not connected so that pathview will not get user touch.
     * On press will display antenna not connected popup.
     */
//    MouseArea{
//        id: idManualSeekBarMouseArea
//        anchors.fill: parent
//        enabled: (DiagnosticEnums.CONNECTED !== cppDiagnosticAdaptor.antennaConnectionStatus)
//        onClicked: {
//            cppTunerApp.qmlLog("TunerManualSeek.qml : manual seek disabled, Antenna not connected : " + cppDiagnosticAdaptor.antennaConnectionStatus)
//            cppTunerAdaptor.isTunerAntennaConnected()
//        }
//    }

    Component.onCompleted: {
        cppTunerApp.qmlLog("Component.onCompleted : Current Manual scale index " + idPathView.currentIndex)
        prTunerManualScalePreviousIndex = cppTunerAdaptor.iManualScaleIndex
    }
}

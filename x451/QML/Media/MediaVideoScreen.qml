import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../Common"
import com.harman.qml.mediaenum 1.0
import com.harman.qml.audioenums 1.0
import com.harman.qml.thememanager 1.0
import com.harman.qml.hardkeyenum 1.0
import com.harman.qml.variantcontrolenums 1.0

BaseUI {
    id: idVideoNowPlayingScreen
    anchors.fill: parent

    //Setting transparent background for Video
    prBackGroundImage: ""

    /* Seek time value when slider thumb is pressed and moved */
    property string prSeekTimeValue: ""

    /* full screen time property */
    property bool prFullScreenMode: false

    /* Alias for Video Screen Title */
    property alias prVideoScreenTitle: idVideoScreenTitle

    /* Alias for Cancel Button */
    property alias prCancelBtn: idCancelBtn

    /* Alias for Browse Button */
    property alias prBrowseBtn: idBrowseBtn

    /* Alias for Previous Button */
    property alias prPreviousBtn: idPreviousBtn

    /* Alias for Next Button */
    property alias prNextBtn: idNextBtn

    function browseMedia()
    {
        if(MediaEnum.CONTENTTYPE_V === MediaAdaptor.usbContentType)
        {
            MediaAdaptor.getCategoryRoot(MediaEnum.BROWSEITEM_VIDEOS)
            MediaAdaptor.setMediaDisplayState(MediaEnum.MEDIA_DISPLAYSTATE_BROWSE_CATEGORY)
            cppMediaApp.raiseSMEvent("Media","Browse")
        }
        else
        {
            //Go to Media Browse screen on Release of Browse Button
            cppMediaApp.raiseSMEvent("Media","Browse")
        }
    }

    Connections{
        target: MediaAdaptor
        onSigPlayStateChanged:
        {
            cppMediaApp.qmlLog("MediaVideoScreen.qml: Playstate changed")
            if(MediaEnum.PLAYSTATE_FASTFORWARD === MediaAdaptor.playState
                    || MediaEnum.PLAYSTATE_FASTREVERSE === MediaAdaptor.playState)
            {
                idFullScreenModeTimer.stop()
                prFullScreenMode = false
            }
            else
            {
                idFullScreenModeTimer.start()
            }
        }

        onSigNowPlayingDataAvailUpdated:
        {
            if(MediaEnum.PLAYSTATE_FASTFORWARD === MediaAdaptor.playState
                    || MediaEnum.PLAYSTATE_FASTREVERSE === MediaAdaptor.playState)
            {
                cppMediaApp.qmlLog("MediaVideoScreen.qml: nowPlaying inored as playState is FFwd/FRwd")
            }
            else
            {
                cppMediaApp.qmlLog("MediaVideoScreen.qml: New video started")
                prFullScreenMode = false
                idFullScreenModeTimer.start()
            }
        }
    }

    //Timer to handle Full Screen Mode. After 5 seconds, Full Screen Mode will be turned On
    Timer{
        id: idFullScreenModeTimer
        interval: 5000
        onTriggered: {
            cppMediaApp.qmlLog("Full screen Timer over")
            prFullScreenMode = true
        }
    }

    Image {
        id: idVideoDimImageBg
        source: "qrc:/image/Media/Med_Gfx_VideoViewerDimBg_7in_n-assets/Med_Gfx_VideoViewerDimBg_n.png"
        visible: (!prFullScreenMode)
    }

    /* Video preview item */
    Item {
        id: idVideoPreview

        anchors
        {
            top: parent.top
            topMargin: 210
            left: parent.left
            leftMargin: 83
        }

        Image {
            id: idPreviewbg
            width: 635 //Image provided by TML is stretched, hence need to set width
            source: "qrc:/image/Media/Med_Gfx_NextPreviousVideoInfoBg_7in_n-assets/Med_NextPreviousVideoInfoBg_n.png"
        }

        HBText {
            id: idMediaVideoPreviewTypeTxt
            horizontalAlignment: Text.AlignHCenter
            text: (MediaAdaptor.previewMode === MediaEnum.PREVIEW_MODE_NEXT)
                  ? qsTr("Next") + cppThemeMgr.languageChanged
                  : qsTr("Previous") + cppThemeMgr.languageChanged

            fontType: ThemeMgr.FONTTYPE_T35_C3
            width: 130

            anchors{
                top: parent.top
                topMargin: 15
                left: parent.left
                leftMargin: 5
            }
        }

        Image
        {
            id: idSongPreviewImage

            width: 76
            height: 76

            anchors
            {
                top: parent.top
                topMargin: 0
                left: parent.left
                leftMargin: 119
            }

            source: (MediaAdaptor.previewMode === MediaEnum.PREVIEW_MODE_NEXT)
                    ? "qrc:/image/Media/Med_Ico_NextSong_7in_n-assets/Med_Ico_NextSong_7in_n.png"
                    : "qrc:/image/Media/Med_Ico_PreviousSong_7in_n-assets/Med_Ico_PreviousSong_7in_n.png"
        }

        HBText {
            id: idMediaVideoPreviewTxt
            text: MediaAdaptor.previewText
            fontType: ThemeMgr.FONTTYPE_T35_BK_C2
            width: 419
            elide: Text.ElideRight

            anchors{
                top: parent.top
                topMargin: 15
                left: parent.left
                leftMargin: 203
            }
        }

        visible: (MediaAdaptor.previewMode === MediaEnum.PREVIEW_MODE_NONE) ? false : true
    }

    /**
     * Transparent Button that fill the screen when Full screen mode is on.
     * OnPressed event on anywhere on the Item, Full screen Mode is turned off and Drawers & Media Controls are made visible on the screen
     * Full screen Mode Timer is also restarted
     */
    GenericButton
    {
        id: idFullScreenModeTransparentBtn

        width: 800
        height: 480
        anchors.fill: parent

        onPressed: {
            cppMediaApp.qmlLog("full ScreenMode Transparent btn Pressed")
            prFullScreenMode = false
            idFullScreenModeTimer.restart()
        }

        onPressAndHoldContinue: {
            cppMediaApp.qmlLog("full ScreenMode Transparent btn press and hold continue")
            prFullScreenMode = false
            idFullScreenModeTimer.restart()
        }

    }

    /**
     * Item that is visible when Full screen Mode is Off
     * It contains following items:
     * Video Screen Title
     * Cancel Button
     * Browse Button
     * Media Controls: Play/Pause, Next, Previous
     * Video ProgressBar, PlayTime and TotalTime
     */
    Item{
        id: idVideoNowPlayingScreenContainer
        anchors.fill: parent
        visible: !(prFullScreenMode)

        //Video Main screen Title
        HBText{
            id: idVideoScreenTitle
            width: 419
            height: 31
            anchors{
                top: parent.top
                topMargin: 73
                horizontalCenter: parent.horizontalCenter
            }

            text: MediaAdaptor.songTitle
            horizontalAlignment: Text.AlignHCenter
            fontType: ThemeMgr.FONTTYPE_T45_C1
            elide: Text.ElideRight
        }

        //Cancel Button
        GenericButton{
            id: idCancelBtn
            width: 76
            height: 76
            anchors{
                left: parent.left
                leftMargin: 694
                top: parent.top
                topMargin: 50
            }

            defaultImageURL: "qrc:/image/Media/Media_Ico_Cancel2_7in_n-assets/Media_Ico_Cancel2_n.png"
            pressedImageURL: "qrc:/image/Media/Media_Ico_Cancel2_7in_n-assets/Media_Ico_Cancel2_nf.png"
            disabledImageURL: "qrc:/image/Media/Media_Ico_Cancel2_7in_n-assets/Media_Ico_Cancel2_nd.png"
            //Disabled image not required since this button shall never go to disabled state

            onReleased: {
                cppMediaApp.qmlLog("Cancel Button Clicked!")
                //Switch to Previous Ent.Source when Cancel Button is Relesed
                MediaAdaptor.requestPreviousSource()
            }

            onPressAndHold: {
                //Restart the Full screen Mode Timer
                idFullScreenModeTimer.restart()
            }

            onPressAndHoldContinue: {
                //Restart the Full screen Mode Timer
                idFullScreenModeTimer.restart()
            }
        }

        //Browse Button
        GenericButton{
            id: idBrowseBtn
            width: 76
            height: 76

            anchors{
                left: parent.left
                leftMargin: 619
                top: parent.top
                topMargin: 50
            }

            defaultImageURL: (idMediaBrowseLoadingAnim.visible) ? "" : "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_n.png"
            pressedImageURL: (idMediaBrowseLoadingAnim.visible) ? "" : "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nf.png"
            disabledImageURL: (idMediaBrowseLoadingAnim.visible) ? "" : "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nd.png"

            enabled: (!idMediaBrowseLoadingAnim.visible)

            onReleased:
            {
                cppMediaApp.qmlLog("Browse Btn Clicked!")
                browseMedia()
            }

            onPressAndHold: {
                //Restart the Full screen Mode Timer
                idFullScreenModeTimer.restart()
            }

            onPressAndHoldContinue: {
                //Restart the Full screen Mode Timer
                idFullScreenModeTimer.restart()
            }
        }

        BrowseLoadingAnim
        {
            id: idMediaBrowseLoadingAnim
            anchors{
                horizontalCenter: idBrowseBtn.horizontalCenter
                verticalCenter: idBrowseBtn.verticalCenter
            }

            enabled: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1)
                     ? ((MediaAdaptor.isBrowseSupported)?(MediaAdaptor.btSlotSyncState >= MediaEnum.SYNC_STATE_FILE_PASS) : false )
                     : (MediaAdaptor.usbSlotSyncState >= MediaEnum.SYNC_STATE_FILE_PASS)

            visible: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1)
                     ? ((MediaAdaptor.isBrowseSupported)?(MediaAdaptor.btSlotSyncState < MediaEnum.SYNC_STATE_THUMBNAIL_PASS) : false )
                     : (MediaAdaptor.usbSlotSyncState < MediaEnum.SYNC_STATE_THUMBNAIL_PASS)

            MouseArea
            {
                anchors.fill: parent
                onReleased:
                {
                    cppMediaApp.qmlLog("Browse Btn animation Clicked!")
                    browseMedia()
                }
            }
        }

        //Row that contains- Play/Pause, Next and Previous Buttons
        Row{
            id: idVideoControlsRow
            anchors{
                top: parent.top
                topMargin: 350
                horizontalCenter: parent.horizontalCenter
            }
            spacing: 20


            //Previous button
            ListGenericButton{
                id: idPreviousBtn
                width: 76
                height: 76

                defaultImageURL: "qrc:/image/Media/Med_Btn_FastRewind_7in_n-assets/Med_Btn_FastRewind_n.png"
                pressedImageURL: "qrc:/image/Media/Med_Btn_FastRewind_7in_n-assets/Med_Btn_FastRewind_nf.png"
                disabledImageURL: "qrc:/image/Media/Med_Btn_FastRewind_7in_n-assets/Med_Btn_FastRewind_nd.png"

                onPressed: {
                    cppMediaApp.qmlLog("Prev btn short press")
                    MediaAdaptor.prev(MediaEnum.EN_BUTTON_STATE_PRESSED)

                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()
                }

                onReleased:
                {
                    if(touchAndHold)
                    {
                        if((AudioEnums.SRC_BT_A2DP1 === cppAudioAdaptor.activeEntSrc && MediaAdaptor.isFwdRwdSupported) || (AudioEnums.SRC_BT_A2DP1 !== cppAudioAdaptor.activeEntSrc))
                        {
                            cppMediaApp.qmlLog("Prev btn long release")
                            MediaAdaptor.fastRewind(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                        }
                        else
                        {
                            cppMediaApp.qmlLog("Prev btn long release - ignored")
                        }
                    }
                    else
                    {
                        cppMediaApp.qmlLog("Prev btn short release - Prev song requested")
                        MediaAdaptor.prev(MediaEnum.EN_BUTTON_STATE_RELEASED)
                    }
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()
                }

                onPressAndHold:
                {
                    cppMediaApp.qmlLog("Prev btn long press")
                    MediaAdaptor.fastRewind(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()
                }

                onExited:
                {
                    if(touchAndHold)
                    {
                        cppMediaApp.qmlLog("Prev btn long release cancelled - Resume song requested")
                        MediaAdaptor.fastRewind(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                        //MediaAdaptor.resume()
                    }
                    else
                    {
                        cppMediaApp.qmlLog("Prev btn onExited - Prev song requested")
                        MediaAdaptor.prev(MediaEnum.EN_BUTTON_STATE_RELEASED)
                    }
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()
                }
            }

            //Play/Pause Button
            GenericButton{
                id: idPlayPauseBtn
                width: 76
                height: 76

                defaultImageURL: (MediaAdaptor.isMediaAudioPlaying) ? "qrc:/image/Media/Med_Btn_Pause_7in_n-assets/Med_Btn_Pause_n.png" : "qrc:/image/Media/Med_Btn_Play_7in_n-assets/Med_Btn_Play_n.png"
                pressedImageURL: (MediaAdaptor.isMediaAudioPlaying) ? "qrc:/image/Media/Med_Btn_Pause_7in_n-assets/Med_Btn_Pause_nf.png" : "qrc:/image/Media/Med_Btn_Play_7in_n-assets/Med_Btn_Play_nf.png"
                disabledImageURL: (MediaAdaptor.isMediaAudioPlaying) ? "qrc:/image/Media/Med_Btn_Pause_7in_n-assets/Med_Btn_Pause_nd.png" : "qrc:/image/Media/Med_Btn_Play_7in_n-assets/Med_Btn_Play_nd.png"

                //Property to indicate which API was invoked on Press of this button.
                property string prOperationOnPress: ""

                onPressed: {
                    cppMediaApp.qmlLog("Play/Pause Btn Pressed!")
                    if((MediaAdaptor.isMediaAudioPlaying))
                    {
                        prOperationOnPress = "pause"
                        MediaAdaptor.pause(MediaEnum.EN_BUTTON_STATE_PRESSED)
                    }
                    else
                    {
                        prOperationOnPress = "play"
                        MediaAdaptor.resume(MediaEnum.EN_BUTTON_STATE_PRESSED)
                    }
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()
                }

                onReleased: {
                    if(touchAndHold)
                    {
                        cppMediaApp.qmlLog("Play/Pause Btn Long Released!")

                        if("pause" == prOperationOnPress)
                        {
                            MediaAdaptor.pause(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                        }
                        else if("play" == prOperationOnPress)
                        {
                            MediaAdaptor.resume(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                        }
                        else
                        {
                            cppMediaApp.qmlLog("prOperationOnPress is NULL")
                        }
                    }
                    else
                    {
                        cppMediaApp.qmlLog("Play/Pause Btn Released!")

                        if("pause" == prOperationOnPress)
                        {
                            MediaAdaptor.pause(MediaEnum.EN_BUTTON_STATE_RELEASED)
                        }
                        else if("play" == prOperationOnPress)
                        {
                            MediaAdaptor.resume(MediaEnum.EN_BUTTON_STATE_RELEASED)
                        }
                        else
                        {
                            cppMediaApp.qmlLog("prOperationOnPress is NULL")
                        }
                    }
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()

                    prOperationOnPress = ""
                }

                onPressAndHold: {
                    cppMediaApp.qmlLog("Play/Pause Btn Long Pressed!")
                    if("pause" == prOperationOnPress)
                    {
                        MediaAdaptor.pause(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
                    }
                    else if("play" == prOperationOnPress)
                    {
                        MediaAdaptor.resume(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
                    }
                    else
                    {
                        cppMediaApp.qmlLog("prOperationOnPress is NULL")
                    }
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()

                }

                onPressAndHoldContinue: {
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()
                }
            }

            //Next Button
            ListGenericButton{
                id: idNextBtn
                width: 76
                height: 76
                defaultImageURL: "qrc:/image/Media/Med_Btn_FastForward_7in_n-assets/Med_Btn_FastForward_n.png"
                pressedImageURL: "qrc:/image/Media/Med_Btn_FastForward_7in_n-assets/Med_Btn_FastForward_nf.png"
                disabledImageURL: "qrc:/image/Media/Med_Btn_FastForward_7in_n-assets/Med_Btn_FastForward_nd.png"

                onPressed: {
                    cppMediaApp.qmlLog("Next btn short press")
                    MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_PRESSED)
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()
                }

                onReleased:
                {
                    if(touchAndHold)
                    {
                        if((AudioEnums.SRC_BT_A2DP1 === cppAudioAdaptor.activeEntSrc && MediaAdaptor.isFwdRwdSupported) || (AudioEnums.SRC_BT_A2DP1 !== cppAudioAdaptor.activeEntSrc))
                        {
                            cppMediaApp.qmlLog("Next btn long release - Resume song requested")
                            MediaAdaptor.fastForward(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                        }
                        else
                        {
                            cppMediaApp.qmlLog("Next btn long release - ignored")
                        }
                    }
                    else
                    {
                        cppMediaApp.qmlLog("Next btn short release - Next song requested")
                        MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_RELEASED)
                    }
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()
                }

                onPressAndHold:
                {
                    cppMediaApp.qmlLog("Next btn long press - fast forward song requested")
                    MediaAdaptor.fastForward(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()
                }

                onExited:
                {
                    if(touchAndHold)
                    {
                        cppMediaApp.qmlLog("Next btn long release cancelled - Resume song requested")
                        //MediaAdaptor.resume()
                        MediaAdaptor.fastForward(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                    }
                    else
                    {
                        cppMediaApp.qmlLog("Next btn onExited - Next song requested")
                        MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_RELEASED)
                    }
                    //Restart the Full screen Mode Timer
                    idFullScreenModeTimer.restart()
                }
            }
        }

        //RowLayout that conatins ProgressBar, TotalTime and PlayTime of Current Playing Video
        RowLayout
        {
            id: idMediaMainPgbRow
            width: parent.width

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 294
            }

            /* This shall display play time of the song */
            HBText {
                id: idMediaMainPlayTimeTxt
                text: idMediaSlider.pressed ? prSeekTimeValue : MediaAdaptor.formattedPlayTime
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
                horizontalAlignment: Text.AlignRight
                visible: MediaAdaptor.isPlaytimeReceived

                anchors {
                    left: parent.left
                    leftMargin: 180
                    top: parent.top
                    topMargin: 79
                }
            }

            /* This shall display total duration of the song */
            HBText {
                id: idMediaMainTotalDurationTxt
                text: MediaAdaptor.formattedTotalDuration
                horizontalAlignment: Text.AlignLeft
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C3
                visible: MediaAdaptor.isPlaytimeReceived

                anchors {
                    right: parent.right
                    rightMargin: 180
                    top: parent.top
                    topMargin: 79
                }
            }

            //Progress bar component
            //FixMe: Images supplied by TML are not correct w.r.t alignment and width/height. Need to get correct images from TML. */
            Slider
            {
                id: idMediaSlider

                anchors
                {
                    horizontalCenter: parent.horizontalCenter
                }

                width: idSliderImage.width
                height: idSliderImage.height

                from    : 0
                to      : MediaAdaptor.totalDuration
                stepSize: 1

                /* 'pressed' condition check shall ensure that thumb is not set to value received by service when dragging is in progress */
                value: idMediaSlider.pressed ? idMediaSlider.value : MediaAdaptor.playTime

                background: Image
                {
                    id : idSliderImage
                    source: "qrc:/image/Media/Med_Gfx_Progressbar_bg_7in_n/Gen_Gfx_Progressbar_bg_n.png"
                }

                Image {
                    id: idMediaMainPgbFiller

                    anchors.verticalCenter: idSliderImage.verticalCenter
                    source: "qrc:/image/Media/Med_Gfx_ProgressbarStates_7in_n/Gen_Gfx_Progressbar_Slider_Progress_n.png"

                    //Scale property shall display the actual progress over the pgb background
                    transform: Scale { origin.x: 0; origin.y: 0; xScale: idMediaSlider.visualPosition}

                    visible: MediaAdaptor.isPlaytimeReceived

                    ColorOverlay {
                        id: idMediaPgbColorOverlay
                        anchors.fill: parent
                        source: parent
                        color:  cppThemeMgr.currentThemeColor
                    }
                }

                handle: Item
                {
                    id: idSliderHandleItem

                    anchors.verticalCenter: idSliderImage.verticalCenter
                    x: (idMediaSlider.leftPadding + (idMediaSlider.visualPosition * (idMediaSlider.availableWidth - width)))
                    z: 1

                    Image {
                        id: idSliderHandle
                        anchors.centerIn: idSliderHandleItem
                        source: "qrc:/image/Media/X445/Med_Gfx_ProgressbarPointer_7in_n-assets/Med_Gfx_ProgressbarPointer_n.png"
                    }

                    visible: MediaAdaptor.isPlaytimeReceived
                }

                onPressedChanged:
                {
                    if(!idMediaSlider.pressed) //Updates to service should be sent only when slider is released (instead of on touch)
                    {
                        cppMediaApp.qmlLog("Slider pos requested by user: " + Math.round(idMediaSlider.value))
                        MediaAdaptor.seekToTime(Math.round(idMediaSlider.value))
                    }
                }

                onValueChanged: {

                    if(idMediaSlider.pressed)
                    {
                        //Restart the Full screen Mode Timer
                        idFullScreenModeTimer.restart()

                        prSeekTimeValue = MediaAdaptor.getFormattedTime(Math.round(idMediaSlider.value))
                        cppMediaApp.qmlLog("Slider pressed pos 2 : " + Math.round(idMediaSlider.value))
                    }
                }
            }
        }
    }

    Connections{
        target: cppHardkeyAdaptor
        onSigRotaryPressed:
        {
            if((HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode) && (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
            {
                cppMediaApp.qmlLog("MediaVideoScreen.qml : right rotary pressed")

                if(MediaAdaptor.previewMode === MediaEnum.PREVIEW_MODE_NONE)
                {
                    if(MediaAdaptor.usbSlotSyncState >= MediaEnum.SYNC_STATE_FILE_PASS)
                    {
                        MediaAdaptor.getCategoryRoot(MediaEnum.BROWSEITEM_VIDEOS)
                        MediaAdaptor.setMediaDisplayState(MediaEnum.MEDIA_DISPLAYSTATE_BROWSE_CATEGORY)
                        cppMediaApp.raiseSMEvent("Media","Browse")
                    }
                    else
                    {
                        cppMediaApp.qmlLog("MediaVideoScreen.qml : right rotary pressed ignored Video main screen - sync state issue")
                    }
                }
                else
                {
                    cppMediaApp.qmlLog("MediaScreen.qml : Prev/Next Preview on Display")
                    MediaAdaptor.playPreviewSong();
                }
            }
        }

        onSigRotaryUpdate :
        {
            console.log("onSigRotaryUpdate:: iKeyCode"+ iKeyCode + "iKeyState: "+ iKeyState)

            if(HardkeyEnum.HKEY_STATE_ROTATE_LEFT === iKeyState)
            {
                MediaAdaptor.showSongPreview(MediaEnum.PREVIEW_MODE_PREV)
            }
            else if(HardkeyEnum.HKEY_STATE_ROTATE_RIGHT === iKeyState)
            {
                MediaAdaptor.showSongPreview(MediaEnum.PREVIEW_MODE_NEXT)
            }
            else
            {
                //Do nothing...invalid Rotary update event
            }
        }
    }

    Component.onCompleted: {
        idFullScreenModeTimer.start();
    }
}

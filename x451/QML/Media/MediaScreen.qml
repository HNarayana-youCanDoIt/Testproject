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
    anchors.fill: parent

    /* Default left and right margin value for UI elements on screen */
    property int prDefaultMargin: 170

    /* Default left and right margin value for media control UI elements on screen */
    property int prSpacingMargin: 35

    /* Width of the label boxes displaying the song info text */
    property int prSongInfoWidth: 290

    /* Seek time value when slider thumb is pressed and moved */
    property string prSeekTimeValue: ""

    function browseMedia()
    {
        /*
        * This will update the browse list array based on the latest categories reported by service
        * Not updating the model though to achieve optimization
        */
        MediaAdaptor.updateMediaBrowseList()

        if(cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1)
        {
            MediaAdaptor.getCategoryRoot(MediaEnum.BROWSEITEM_FOLDERS)
        }
        cppMediaApp.qmlLog("Media Browse Clicked!")
        cppMediaApp.raiseSMEvent("Media","Browse")
    }

    /*
    Screen Layout: Screen is divided in 4 rows as below:
    ** 1. Title row
    ** 2. Info row to display Album Art and Song info
    ** 3. Progress bar controls including the playTime info for song
    ** 4. Controls row to display shuffle, repeat/random, play/pause and prev/next buttons
    ** Additionally, screen would display browse and back buttonson top right
    */

    HBTitleWithBackButton{
        prTitle: qsTr(MediaAdaptor.activeMediaSrcTitle) + cppThemeMgr.languageChanged
    }

    /* Media Browse button */
    GenericButton {
        //TODO: Need to check about animation on browse button for sync state implementation
        id: idMediaMainBrowseBtn
        width: 76
        height: 76

        anchors{
            top: parent.top
            topMargin: 50
            left: parent.left
            leftMargin: 519
        }

        defaultImageURL: (idMediaBrowseLoadingAnim.visible) ? "" : "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_n.png"
        pressedImageURL: (idMediaBrowseLoadingAnim.visible) ? "" : "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nf.png"
        disabledImageURL: (idMediaBrowseLoadingAnim.visible) ? "" : "qrc:/image/Tuner/Gen_Ico_Browse/Gen_Ico_Browse_nd.png"

        enabled: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1)
                 ? ((MediaAdaptor.isBrowseSupported)?(!idMediaBrowseLoadingAnim.visible) : false )
                 : (!idMediaBrowseLoadingAnim.visible)

        onReleased:
        {
            cppMediaApp.qmlLog("Browse Btn Clicked!")
            browseMedia()
        }
    }

    BrowseLoadingAnim
    {
        id: idMediaBrowseLoadingAnim
        anchors{
            horizontalCenter: idMediaMainBrowseBtn.horizontalCenter
            verticalCenter: idMediaMainBrowseBtn.verticalCenter
        }

        enabled: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1)
                 ? ((MediaAdaptor.isBrowseSupported)?(MediaAdaptor.btSlotSyncState >= MediaEnum.SYNC_STATE_FILE_PASS) : false )
                 : (MediaAdaptor.usbSlotSyncState >= MediaEnum.SYNC_STATE_FIRST_FILE)

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

    /* Song preview UI elements */
    Image
    {
        id: idSongPreviewImage

        width: 76
        height: 76

        anchors{
            top: parent.top
            topMargin: 170
            left: parent.left
            leftMargin: 284
        }

        source: (MediaAdaptor.previewMode === MediaEnum.PREVIEW_MODE_NEXT)
                ? "qrc:/image/Media/Med_Ico_NextSong_7in_n-assets/Med_Ico_NextSong_7in_n.png"
                : "qrc:/image/Media/Med_Ico_PreviousSong_7in_n-assets/Med_Ico_PreviousSong_7in_n.png"

        visible: (MediaAdaptor.previewMode === MediaEnum.PREVIEW_MODE_NONE) ? false : true
    }

    /* Album of the song */
    HBText {
        id: idMediaMainSongPreviewTxt
        text: MediaAdaptor.previewText
        fontType: ThemeMgr.FONTTYPE_T35_C3
        width: prSongInfoWidth - idSongPreviewImage.width
        elide: Text.ElideRight

        anchors{
            top: parent.top
            topMargin: 185
            left: parent.left
            leftMargin: 360
        }

        visible: (MediaAdaptor.previewMode === MediaEnum.PREVIEW_MODE_NONE) ? false : true
    }

    /*
    This layout shall display:
    ** Row 1: Album Art Image (clickable)
    ** Row 2: Column:
    **       a. Title of the song
    **       b. Artist of the song
    **       c. Album of the song
    */
    RowLayout {
        id: idMediaMainSongInfoRow
        width: parent.width

        anchors {
            top: parent.top
            topMargin: 151
            left: parent.left
            leftMargin: prDefaultMargin
        }

        spacing: 5

        Image {
            id: idMediaMainAlbumArtBtn
            Layout.preferredWidth: 100
            Layout.preferredHeight: 96

            anchors {
                top: parent.top
                left: parent.left
            }

            source: MediaAdaptor.albumArtPath
        }

        ColumnLayout {
            id: idMediaMainSongInfoCol

            anchors {
                top: parent.top
                topMargin: -10
                left: idMediaMainAlbumArtBtn.right
                leftMargin: 32
            }

            /* Title of the song */
            HBText {
                id: idMediaMainSongTitleTxt
                text: MediaAdaptor.songTitle
                fontType: ThemeMgr.FONTTYPE_T35_BK_C2
                Layout.preferredWidth: prSongInfoWidth
                elide: Text.ElideRight
            }

            /* Album of the song */
            HBText {
                id: idMediaMainSongAlbumTxt
                text: MediaAdaptor.songAlbum
                fontType: ThemeMgr.FONTTYPE_T35_C3
                Layout.preferredWidth: prSongInfoWidth
                elide: Text.ElideRight

                anchors {
                    top: idMediaMainSongTitleTxt.bottom
                    topMargin: -4
                }

                visible: (MediaAdaptor.previewMode === MediaEnum.PREVIEW_MODE_NONE) ? true : false
            }

            /* Artist of the song */
            HBText {
                id: idMediaMainSongArtistTxt
                text: MediaAdaptor.songArtist
                fontType: ThemeMgr.FONTTYPE_T24_LIGHT_C2
                Layout.preferredWidth: prSongInfoWidth
                elide: Text.ElideRight

                anchors {
                    top: idMediaMainSongAlbumTxt.bottom
                    topMargin: -3
                }

                visible: (MediaAdaptor.previewMode === MediaEnum.PREVIEW_MODE_NONE) ? true : false
            }
        }
    }

    ColumnLayout {
        id: idMediaMainFolderIconsCol

        anchors {
            top: parent.top
            left: parent.left
            leftMargin: 594
            topMargin: 133
        }

        spacing: 3
        visible: getFolderBtnsVisibility()

        /*
          Note: Folder images provided by TML are not named correctly.
          Please follow the API call to understand the behaviour of btns
          */

        GenericButton {
            id: idMediaFolderUpBtn
            width: 76
            height: 76
            anchors.horizontalCenter: parent.horizontalCenter
            defaultImageURL: "qrc:/image/Media/Med_Ico_FolderPrev_n-assets/Med_Ico_FolderPrev_n.png"
            pressedImageURL: "qrc:/image/Media/Med_Ico_FolderPrev_n-assets/Med_Ico_FolderPrev_nf.png"
            disabledImageURL: "qrc:/image/Media/Med_Ico_FolderPrev_n-assets/Med_Ico_FolderPrev_nd.png"
            visible: true
            enabled: true
            onReleased: {
                cppMediaApp.qmlLog("Folder Next Btn Clicked!")
                MediaAdaptor.nextFolder();
            }
        }

        GenericButton {
            id: idMediaFolderDownBtn
            width: 76
            height: 76
            anchors.horizontalCenter: parent.horizontalCenter
            defaultImageURL: "qrc:/image/Media/Media_Ico_FolderNext_n-assets/Media_Ico_FolderNext_n.png"
            pressedImageURL: "qrc:/image/Media/Media_Ico_FolderNext_n-assets/Media_Ico_FolderNext_nf.png"
            disabledImageURL: "qrc:/image/Media/Media_Ico_FolderNext_n-assets/Media_Ico_FolderNext_nd.png"
            visible: true
            enabled: true
            onReleased: {
                cppMediaApp.qmlLog("Folder Prev Btn Clicked!")
                MediaAdaptor.previousFolder();
            }
        }

        function getFolderBtnsVisibility()
        {
            var bRet = false;
            if(AudioEnums.SRC_USB1 === cppAudioAdaptor.activeEntSrc)
            {
                if((MediaAdaptor.isUSBFolderModePlayBack) && (MediaAdaptor.folderCount > 1))
                {
                    bRet = true;
                }
            }
            return bRet;
        }
    }

    RowLayout
    {
        id: idMediaMainPgbRow
        width: parent.width

        anchors {
            bottom: idMediaMainSongControlsRow.top
            bottomMargin: 23
            left: parent.left
        }

        /* This shall display play time of the song */
        HBText {
            id: idMediaMainPlayTimeTxt
            text: idMediaSlider.pressed ? prSeekTimeValue : MediaAdaptor.formattedPlayTime
            fontType:ThemeMgr.FONTTYPE_T24_LIGHT_C2
            visible: (MediaAdaptor.isPlaytimeReceived)

            anchors {
                left: parent.left
                leftMargin: 170
                bottom: parent.bottom
                bottomMargin: 25
            }
        }

        /* This shall display total duration of the song */
        HBText {
            id: idMediaMainTotalDurationTxt
            text: MediaAdaptor.formattedTotalDuration
            horizontalAlignment: Text.AlignRight
            fontType:  ThemeMgr.FONTTYPE_T24_LIGHT_C3
            visible: (MediaAdaptor.isPlaytimeReceived)

            anchors {
                right: parent.right
                rightMargin: 170
                bottom: parent.bottom
                bottomMargin: 25
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

            enabled: (cppAudioAdaptor.activeEntSrc !== AudioEnums.SRC_BT_A2DP1)

            background: Image
            {
                id : idSliderImage
                source: "qrc:/image/Media/Med_Gfx_Progressbar_bg_7in_n/Gen_Gfx_Progressbar_bg_n.png"
            }

            Image {
                id: idMediaMainPgbFiller

                anchors.verticalCenter: idSliderImage.verticalCenter
                source: "qrc:/image/Media/Med_Gfx_ProgressbarStates_7in_n/Gen_Gfx_Progressbar_Slider_Progress_n.png"
                visible: MediaAdaptor.isPlaytimeReceived

                //Scale property shall display the actual progress over the pgb background
                transform: Scale { origin.x: 0; origin.y: 0; xScale: idMediaSlider.visualPosition}

                ColorOverlay {
                    id: idMediaPgbColorOverlay
                    anchors.fill: parent
                    source: parent
                    color:  cppThemeMgr.currentThemeColor
                }
            }

            handle: Item {
                id: idSliderHandleItem

                anchors.verticalCenter: idSliderImage.verticalCenter
                x: (idMediaSlider.leftPadding + (idMediaSlider.visualPosition * (idMediaSlider.availableWidth - width)))
                z: 1

                Image {
                    id: idSliderHandle
                    anchors.centerIn: idSliderHandleItem
                    source: "qrc:/image/Media/X445/Med_Gfx_ProgressbarPointer_7in_n-assets/Med_Gfx_ProgressbarPointer_n.png"
                    visible: MediaAdaptor.isPlaytimeReceived
                }
            }

            onPressedChanged:
            {
                if(!idMediaSlider.pressed) //Updates to service should be sent only when slider is released (instead of on touch)
                {
                    cppMediaApp.qmlLog("Slider pos requested by user: " + Math.round(idMediaSlider.value))
                    MediaAdaptor.seekToTime(Math.round(idMediaSlider.value))
                }
                else
                {
                    prSeekTimeValue = MediaAdaptor.getFormattedTime(Math.round(idMediaSlider.value))
                }
            }

            onValueChanged: {
                cppMediaApp.qmlLog("Slider pressed pos 1 : " + Math.round(idMediaSlider.pressed))
                if(idMediaSlider.pressed){
                    prSeekTimeValue = MediaAdaptor.getFormattedTime(Math.round(idMediaSlider.value))
                    cppMediaApp.qmlLog("Slider pressed pos 2 : " + Math.round(idMediaSlider.value))
                }
            }
        }
    }

    /*
    This layout shall display:
    ** Play/Pause button at the center of the screen
    ** Prev/FRev song button at the left of the play/Pause button
    ** Next/FFwd song button at the right of the play/Pause button
    ** Shuffle ON/OFF button at the left of the Prev/FRev button
    ** Repeat On/OFF song button at the right of the Next/FFwd button
    */
    RowLayout {
        id: idMediaMainSongControlsRow
        width: parent.width

        anchors {
            bottom: parent.bottom
            bottomMargin: 10
        }


        /* Media Play/Pause button */
        GenericButton {
            id: idMediaMainPlayPauseBtn
            width: 96
            height: 96

            anchors.horizontalCenter: parent.horizontalCenter

            defaultImageURL: (MediaAdaptor.isMediaAudioPlaying) ? "qrc:/image/Media/Med_Btn_Pause_7in_n-assets/Med_Btn_Pause_n.png" : "qrc:/image/Media/Med_Btn_Play_7in_n-assets/Med_Btn_Play_n.png"
            pressedImageURL: (MediaAdaptor.isMediaAudioPlaying) ? "qrc:/image/Media/Med_Btn_Pause_7in_n-assets/Med_Btn_Pause_nf.png" : "qrc:/image/Media/Med_Btn_Play_7in_n-assets/Med_Btn_Play_nf.png"
            disabledImageURL: (MediaAdaptor.isMediaAudioPlaying) ? "qrc:/image/Media/Med_Btn_Pause_7in_n-assets/Med_Btn_Pause_nd.png" : "qrc:/image/Media/Med_Btn_Play_7in_n-assets/Med_Btn_Play_nd.png"

            enabled: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1) ? MediaAdaptor.isPlayPauseSupported : true

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
            }
        }

        /* Media Previous track button */
        ListGenericButton {
            id: idMediaMainPrevBtn
            width: 76
            height: 76

            anchors.right: idMediaMainPlayPauseBtn.left
            anchors.rightMargin: prSpacingMargin

            defaultImageURL: "qrc:/image/Media/Med_Btn_FastRewind_7in_n-assets/Med_Btn_FastRewind_n.png"
            pressedImageURL: "qrc:/image/Media/Med_Btn_FastRewind_7in_n-assets/Med_Btn_FastRewind_nf.png"
            disabledImageURL: "qrc:/image/Media/Med_Btn_FastRewind_7in_n-assets/Med_Btn_FastRewind_nd.png"
            enabled: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1) ? MediaAdaptor.isNextPrevSupported : true

            onPressed: {
                cppMediaApp.qmlLog("Prev btn short press")
                MediaAdaptor.prev(MediaEnum.EN_BUTTON_STATE_PRESSED)
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
            }

            onPressAndHold:
            {
                cppMediaApp.qmlLog("Prev btn long press")
                MediaAdaptor.fastRewind(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
            }

            onExited:
            {
                if(touchAndHold)
                {
                    cppMediaApp.qmlLog("Prev btn long release cancelled - Resume song requested")
                    MediaAdaptor.fastRewind(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                }
                else
                {
                    cppMediaApp.qmlLog("Prev btn onExited - Prev song requested")
                    MediaAdaptor.prev(MediaEnum.EN_BUTTON_STATE_RELEASED)
                }
            }
        }

        /* Media Next track button */
        ListGenericButton {
            id: idMediaMainNextBtn
            width: 76
            height: 76

            anchors.left: idMediaMainPlayPauseBtn.right
            anchors.leftMargin: prSpacingMargin

            defaultImageURL: "qrc:/image/Media/Med_Btn_FastForward_7in_n-assets/Med_Btn_FastForward_n.png"
            pressedImageURL: "qrc:/image/Media/Med_Btn_FastForward_7in_n-assets/Med_Btn_FastForward_nf.png"
            disabledImageURL: "qrc:/image/Media/Med_Btn_FastForward_7in_n-assets/Med_Btn_FastForward_nd.png"
            enabled: (cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1) ? MediaAdaptor.isNextPrevSupported : true

            onPressed: {
                cppMediaApp.qmlLog("Next btn short press")
                MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_PRESSED)
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
            }

            onPressAndHold:
            {
                cppMediaApp.qmlLog("Next btn long press - fast forward song requested")
                MediaAdaptor.fastForward(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
            }

            onExited:
            {
                if(touchAndHold)
                {
                    cppMediaApp.qmlLog("Next btn long release canceled - Resume song requested")
                    MediaAdaptor.fastForward(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                }
                else
                {
                    cppMediaApp.qmlLog("Next btn onExited - Next song requested")
                    MediaAdaptor.next(MediaEnum.EN_BUTTON_STATE_RELEASED)
                }
            }
        }


        /* Media Shuffle ON/OFF button */
        GenericButton {
            id: idMediaMainShuffleBtn
            width: 76
            height: 76

            anchors.right: idMediaMainPrevBtn.left
            anchors.rightMargin: prSpacingMargin

            defaultImageURL: MediaEnum.SHUFFLEMODE_ALL === MediaAdaptor.shuffleMode ? "qrc:/image/Media/Med_Btn_Shuffle_7in_n-assets/Med_Btn_Shuffle_n.png"
                                                                                    : "qrc:/image/Media/Med_Btn_ShuffleOff_7in_n-assets/Med_Btn_ShuffleOff_n.png"
            pressedImageURL: MediaEnum.SHUFFLEMODE_ALL === MediaAdaptor.shuffleMode ? "qrc:/image/Media/Med_Btn_Shuffle_7in_n-assets/Med_Btn_Shuffle_nf.png"
                                                                                    : "qrc:/image/Media/Med_Btn_ShuffleOff_7in_n-assets/Med_Btn_ShuffleOff_nf.png"
            disabledImageURL: MediaEnum.SHUFFLEMODE_ALL === MediaAdaptor.shuffleMode ? "qrc:/image/Media/Med_Btn_Shuffle_7in_n-assets/Med_Btn_Shuffle_nd.png"
                                                                                     : "qrc:/image/Media/Med_Btn_ShuffleOff_7in_n-assets/Med_Btn_ShuffleOff_nd.png"

            enabled: getShuffleAvailability()

            onPressed: {
                cppMediaApp.qmlLog("Shuffle Btn Pressed!")
                MediaAdaptor.toggleShuffleMode(MediaEnum.EN_BUTTON_STATE_PRESSED)
            }

            onReleased: {
                if(touchAndHold)
                {
                    cppMediaApp.qmlLog("Shuffle Btn Long Released!")
                    MediaAdaptor.toggleShuffleMode(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                }
                else
                {
                    cppMediaApp.qmlLog("Shuffle Btn Released!")
                    MediaAdaptor.toggleShuffleMode(MediaEnum.EN_BUTTON_STATE_RELEASED)
                }


                if (MediaAdaptor.shuffleMode === MediaEnum.SHUFFLEMODE_OFF) {
                    cppMediaApp.qmlLog("Shuffle OFF state")
                } else if (MediaAdaptor.shuffleMode === MediaEnum.SHUFFLEMODE_ALL) {
                    cppMediaApp.qmlLog("Shuffle ON state")
                } else {
                    cppMediaApp.qmlLog(
                                "Shuffle ON state" + MediaAdaptor.shuffleMode)
                }
            }

            onPressAndHold: {
                cppMediaApp.qmlLog("Shuffle Btn Long Pressed!")
                MediaAdaptor.toggleShuffleMode(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
            }


            function getShuffleAvailability()
            {
                var bRet = false
                if(cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1)
                {
                    bRet = MediaAdaptor.isRandomSupported
                }
                else if(cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_IPOD)
                {
                    if((MediaAdaptor.nowPlayingMetadata === MediaEnum.BROWSEITEM_AUDIOBOOK) ||
                            (MediaAdaptor.nowPlayingMetadata === MediaEnum.BROWSEITEM_PODCAST) ||
                            (MediaAdaptor.nowPlayingMetadata === MediaEnum.BROWSEITEM_ITUNES_RADIO))
                    {
                        bRet = false
                    }
                    else
                    {
                        bRet = true
                    }
                }
                else
                {
                    bRet = true
                }

                return bRet
            }

        }

        /* Media Repeat button */
        GenericButton {
            //TODO: Implementation for repeat states yet to be implemented
            id: idMediaMainRepeatAllBtn
            width: 76
            height: 76

            anchors.left: idMediaMainNextBtn.right
            anchors.leftMargin: prSpacingMargin

            defaultImageURL: getDefaultImageURL()
            pressedImageURL: getPressedImageURL()

            //If repeat feature is not supported, then always display Repeat_OFF disabled button
            disabledImageURL: (!getRepeatAvailability()) ? "qrc:/image/Media/Med_Btn_Repeat_off_7in_n-assets/Med_Btn_Repeat_off_nd.png" : getDisabledImageURL()
            enabled: getRepeatAvailability()

            onPressed: {
                cppMediaApp.qmlLog("Repeat Btn Pressed!")
                MediaAdaptor.toggleRepeatMode(MediaEnum.EN_BUTTON_STATE_PRESSED)
            }

            onReleased: {
                if(touchAndHold)
                {
                    cppMediaApp.qmlLog("Repeat Btn Long Released!")
                    MediaAdaptor.toggleRepeatMode(MediaEnum.EN_BUTTON_STATE_LONG_RELEASED)
                }
                else
                {
                    cppMediaApp.qmlLog("Repeat Btn Released!")
                    MediaAdaptor.toggleRepeatMode(MediaEnum.EN_BUTTON_STATE_RELEASED)
                }
            }

            onPressAndHold: {
                cppMediaApp.qmlLog("Repeat Btn Long Pressed!")
                MediaAdaptor.toggleRepeatMode(MediaEnum.EN_BUTTON_STATE_LONG_PRESSED)
            }

            function getDefaultImageURL()
            {
                switch(MediaAdaptor.repeatMode)
                {
                case MediaEnum.REPEATMODE_OFF: return "qrc:/image/Media/Med_Btn_Repeat_off_7in_n-assets/Med_Btn_Repeat_off_n.png";

                case MediaEnum.REPEATMODE_ALL: return "qrc:/image/Media/Med_Btn_Repeat_7in_n-assets/Med_Btn_Repeat_n.png";

                case MediaEnum.REPEATMODE_SONG: return "qrc:/image/Media/Med_Btn_RepeatOnce_7in_n-assets/Med_Btn_RepeatOnce_n.png";

                case MediaEnum.REPEATMODE_FOLDER: return "qrc:/image/Media/Med_Btn_Repeat_folder_7in_n-assets/Med_Btn_Repeat_folder_n.png";

                default: return "qrc:/image/Media/Med_Btn_Repeat_off_7in_n-assets/Med_Btn_Repeat_off_n.png";
                }
            }

            function getPressedImageURL()
            {
                switch(MediaAdaptor.repeatMode)
                {
                case MediaEnum.REPEATMODE_OFF: return "qrc:/image/Media/Med_Btn_Repeat_off_7in_n-assets/Med_Btn_Repeat_off_nf.png";

                case MediaEnum.REPEATMODE_ALL: return "qrc:/image/Media/Med_Btn_Repeat_7in_n-assets/Med_Btn_Repeat_nf.png";

                case MediaEnum.REPEATMODE_SONG: return "qrc:/image/Media/Med_Btn_RepeatOnce_7in_n-assets/Med_Btn_RepeatOnce_nf.png";

                case MediaEnum.REPEATMODE_FOLDER: return "qrc:/image/Media/Med_Btn_Repeat_folder_7in_n-assets/Med_Btn_Repeat_folder_nf.png";

                default: return "qrc:/image/Media/Med_Btn_Repeat_7in_n-assets/Med_Btn_Repeat_nf.png";
                }
            }

            function getDisabledImageURL()
            {
                switch(MediaAdaptor.repeatMode)
                {
                case MediaEnum.REPEATMODE_OFF: return "qrc:/image/Media/Med_Btn_Repeat_off_7in_n-assets/Med_Btn_Repeat_off_nd.png";

                case MediaEnum.REPEATMODE_ALL: return "qrc:/image/Media/Med_Btn_Repeat_7in_n-assets/Med_Btn_Repeat_nd.png";

                case MediaEnum.REPEATMODE_SONG: return "qrc:/image/Media/Med_Btn_RepeatOnce_7in_n-assets/Med_Btn_RepeatOnce_nd.png";

                case MediaEnum.REPEATMODE_FOLDER: return "qrc:/image/Media/Med_Btn_Repeat_folder_7in_n-assets/Med_Btn_Repeat_folder_nd.png";

                default: return "qrc:/image/Media/Med_Btn_Repeat_off_7in_n-assets/Med_Btn_Repeat_off_nd.png";
                }
            }

            function getRepeatAvailability()
            {
                var bRet = false
                if(cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_BT_A2DP1)
                {
                    bRet = MediaAdaptor.isRandomSupported
                }
                else if(cppAudioAdaptor.activeEntSrc === AudioEnums.SRC_IPOD)
                {
                    if((MediaAdaptor.nowPlayingMetadata === MediaEnum.BROWSEITEM_AUDIOBOOK) ||
                            (MediaAdaptor.nowPlayingMetadata === MediaEnum.BROWSEITEM_PODCAST) ||
                            (MediaAdaptor.nowPlayingMetadata === MediaEnum.BROWSEITEM_ITUNES_RADIO))
                    {
                        bRet = false
                    }
                    else
                    {
                        bRet = true
                    }
                }
                else
                {
                    bRet = true
                }

                return bRet
            }
        }
    }

    Connections{
        target: cppHardkeyAdaptor
        onSigRotaryPressed: {
            if((HardkeyEnum.KEYCODEHK_MENUROTARY === iKeyCode) && (HardkeyEnum.HKEY_STATE_RELEASED === iKeyState || HardkeyEnum.HKEY_STATE_LONGPRESSED === iKeyState))
            {
                cppMediaApp.qmlLog("MediaScreen.qml : right rotary pressed")

                if(MediaAdaptor.previewMode === MediaEnum.PREVIEW_MODE_NONE)
                {
                    if(AudioEnums.SRC_BT_A2DP1 === cppAudioAdaptor.activeEntSrc)
                    {
                        if (MediaAdaptor.btSlotSyncState >= MediaEnum.SYNC_STATE_FILE_PASS && MediaAdaptor.isBrowseSupported) //&& isBrowsingSupported
                        {
                            //In cas of BT browse, skipping one level of browsing (i.e. Folders) and directly displaying data received from device
                            cppMediaApp.qmlLog("MediaScreen.qml : right rotary pressed - Media browse")
                            browseMedia()
                        }
                        else
                        {
                            //Do nothing
                            cppMediaApp.qmlLog("MediaScreen.qml : right rotary pressed ignored in Media BT main screen")
                        }
                    }
                    else if(MediaAdaptor.usbSlotSyncState >= MediaEnum.SYNC_STATE_FIRST_FILE)
                    {
                        cppMediaApp.qmlLog("MediaScreen.qml : right rotary pressed - Media browse")
                        browseMedia()
                    }
                    else
                    {
                        cppMediaApp.qmlLog("MediaScreen.qml : right rotary pressed ignored in Media USB/IPOD main screen")
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
            cppMediaApp.qmlLog("onSigRotaryUpdate:: iKeyCode"+ iKeyCode + "iKeyState: "+ iKeyState)

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

}

/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaAdaptor.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CMediaAdaptor Adaptor class for Media is a singleton class used to communicate with qml,resources of Media module.
*/
#ifndef CMEDIAADAPTOR_H
#define CMEDIAADAPTOR_H

#include <QObject>
#include <QString>
#include "CFramework.h"
#include "interfaces/IMediaResource.h"
#include "CMediaEnum.h"
#include "CRCAEnums.h"
#include <QList>
#include <QMap>
#include "CAudioAdaptor.h"
#include "CPopupManager.h"
#include "CWindowingHelper.h"

#include "CSetupListModel.h"
#include "CMediaData.h"
#include <QTimer>

class CMediaBrowseCategoryListModel;
class CMediaBrowseListModel;

//Language strings for browse items
const QString  MEDIA_BROWSE_CATEGORY_FOLDERS           = "Folders" ;
const QString  MEDIA_BROWSE_CATEGORY_TRACKS            = "Songs" ;
const QString  MEDIA_BROWSE_CATEGORY_ALBUMS            = "Albums" ;
const QString  MEDIA_BROWSE_CATEGORY_ARTISTS           = "Artists" ;
const QString  MEDIA_BROWSE_CATEGORY_PLAYLIST          = "Playlists" ;
const QString  MEDIA_BROWSE_CATEGORY_GENRES            = "Genres" ;
const QString  MEDIA_BROWSE_CATEGORY_VIDEOS            = "Videos" ;
const QString  MEDIA_BROWSE_CATEGORY_IMAGES            = "Pictures" ;
const QString  MEDIA_BROWSE_CATEGORY_AUDIO_BOOKS       = "Audiobooks" ;
const QString  MEDIA_BROWSE_CATEGORY_PODCASTS          = "Podcasts" ;
const QString  MEDIA_BROWSE_CATEGORY_EPISODES          = "Episode" ;
const QString  MEDIA_BROWSE_CATEGORY_ITUNESRADIO       = "iTunes radio" ;

//Path of images for all supported browse categories across all sources
const QString  MEDIA_BROWSE_IMG_CATEGORY_FOLDERS           = "qrc:/image/Media/Med_Ico_Folder_7in_n-assets/Med_Ico_Folder_7in_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_TRACKS            = "qrc:/image/Media/Med_Ico_AllTracksList_7in_n-assets/Med_Ico_AllTracksList_7in_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_ALBUMS            = "qrc:/image/Media/Med_Ico_Albums_7in_n-assets/Med_Ico_Albums_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_ARTISTS           = "qrc:/image/Media/Med_Ico_Artists_7in_n-assets/Med_Ico_Artists_7in_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_PLAYLIST          = "qrc:/image/Media/Med_Ico_Playlist_7in_n-assets/Med_Ico_Playlist_7in_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_GENRES            = "qrc:/image/Media/Med_Ico_Genre_7in_n-assets/Med_Ico_Genre_7in_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_VIDEOS            = "qrc:/image/Media/Med_Ico_Videos_7in_n-assets/Med_Ico_Videos_7in_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_IMAGES            = "qrc:/image/Media/Med_Ico_Pictures_7in_n-assets/Med_Ico_Pictures_7in_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_AUDIO_BOOKS       = "qrc:/image/Media/Med_Ico_Audiobook_7in_n-assets/Med_Ico_AllTracks_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_PODCASTS          = "qrc:/image/Media/Med_Ico_Podcast_7in_n-assets/Med_Ico_Podcast_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_ITUNESRADIO       = "qrc:/image/Media/Tun_Ico_iTunesRadio_n-assets/Gen_Ico_iTunesRadio_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_EPISODES          = "qrc:/image/Media/Med_Ico_AllTracksList_7in_n-assets/Med_Ico_AllTracksList_7in_n.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_PLAYALL           = "qrc:/image/Media/Med_Ico_PlayAll_7in_n-assets/Med_Ico_PlayAll_7in_n.png" ;

//Path of *disabled* images for all supported browse categories across all sources
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_FOLDERS           = "qrc:/image/Media/Med_Ico_Folder_7in_n-assets/Med_Ico_Folder_7in_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_TRACKS            = "qrc:/image/Media/Med_Ico_AllTracksList_7in_n-assets/Med_Ico_AllTracksList_7in_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_ALBUMS            = "qrc:/image/Media/Med_Ico_Albums_7in_n-assets/Med_Ico_Albums_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_ARTISTS           = "qrc:/image/Media/Med_Ico_Artists_7in_n-assets/Med_Ico_Artists_7in_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_PLAYLIST          = "qrc:/image/Media/Med_Ico_Playlist_7in_n-assets/Med_Ico_Playlist_7in_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_GENRES            = "qrc:/image/Media/Med_Ico_Genre_7in_n-assets/Med_Ico_Genre_7in_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_VIDEOS            = "qrc:/image/Media/Med_Ico_Videos_7in_n-assets/Med_Ico_Videos_7in_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_IMAGES            = "qrc:/image/Media/Med_Ico_Pictures_7in_n-assets/Med_Ico_Pictures_7in_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_AUDIO_BOOKS       = "qrc:/image/Media/Med_Ico_Audiobook_7in_n-assets/Med_Ico_AllTracks_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_PODCASTS          = "qrc:/image/Media/Med_Ico_Podcast_7in_n-assets/Med_Ico_Podcast_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_ITUNESRADIO       = "qrc:/image/Media/Tun_Ico_iTunesRadio_n-assets/Gen_Ico_iTunesRadio_nd.png" ;
const QString  MEDIA_BROWSE_IMG_CATEGORY_DISABLED_EPISODES          = "qrc:/image/Media/Med_Ico_AllTracksList_7in_n-assets/Med_Ico_AllTracksList_7in_nd.png" ;


/**
 * @class CMediaAdaptor
 * @brief Adaptor class for Media is a singleton class used to communicate with qml,resources of Media module.
 */
class CMediaAdaptor : public QObject
{
    Q_OBJECT

    //Define QProperties here

    //Property for song Title
    Q_PROPERTY(QString songTitle READ songTitle NOTIFY sigSongTitleChanged)

    //Property for song Artist
    Q_PROPERTY(QString songArtist READ songArtist NOTIFY sigSongArtistChanged)

    //Property for song Album
    Q_PROPERTY(QString songAlbum READ songAlbum NOTIFY sigSongAlbumChanged)

    //Property for play state
    Q_PROPERTY(CMediaEnum::EMediaPlayStates playState READ playState NOTIFY sigPlayStateChanged)

    //Property to check if media audio is playing or not
    Q_PROPERTY(bool isMediaAudioPlaying READ isMediaAudioPlaying NOTIFY sigIsMediaAudioPlayingChanged)

    //Property for shuffle mode
    Q_PROPERTY(CMediaEnum::EMediaShuffleMode shuffleMode READ shuffleMode NOTIFY sigShuffleModeChanged)

    //Property for repeat state
    Q_PROPERTY(CMediaEnum::EMediaRepeatMode repeatMode READ repeatMode NOTIFY sigRepeatModeChanged)

    //Property for playTime
    Q_PROPERTY(uint playTime READ playTime NOTIFY sigPlayTimeChanged)

    //Property for totalDuration
    Q_PROPERTY(uint totalDuration READ totalDuration NOTIFY sigTotalDurationChanged)

    //Property for formattedPlayTime
    Q_PROPERTY(QString formattedPlayTime READ formattedPlayTime NOTIFY sigFormattedPlayTimeChanged)

    //Property for formattedTotalDuration
    Q_PROPERTY(QString formattedTotalDuration READ formattedTotalDuration NOTIFY sigFormattedTotalDurationChanged)

    //Property for AlbumArt path
    Q_PROPERTY(QString albumArtPath READ albumArtPath NOTIFY sigAlbumArtChanged)

    //Property for total image count
    Q_PROPERTY(int totalImageCount READ totalImageCount NOTIFY sigTotalImageCountChanged)

    //Property for Media Main screen Title
    Q_PROPERTY(QString activeMediaSrcTitle READ activeMediaSrcTitle NOTIFY sigActiveMediaSrcTitleChanged)

    //Property for readyToBrowse event, this shall suggest if the device is browsable or not
    Q_PROPERTY(QString readyToBrowse READ readyToBrowse NOTIFY sigReadyToBrowseChanged)

    //Property for USB slot syncState event, this shall carry the latest syncState for USB slot
    Q_PROPERTY(CMediaEnum::EMediaSyncState usbSlotSyncState READ usbSlotSyncState NOTIFY sigUSBSlotSyncState)

    //Property for BT slot syncState event, this shall carry the latest syncState for BT slot
    Q_PROPERTY(CMediaEnum::EMediaSyncState btSlotSyncState READ btSlotSyncState NOTIFY sigBTSlotSyncState)

    //Property for Media Browse Category List
    Q_PROPERTY(CMediaBrowseCategoryListModel* mediaCategoryListModel READ mediaCategoryListModel CONSTANT)

    //Property for Media Browse List
    Q_PROPERTY(CMediaBrowseListModel* mediaBrowseListModel READ mediaBrowseListModel CONSTANT)

    //Property for Media Aux-In-Gain List
    Q_PROPERTY(CSetupListModel* mediaAuxInGainModel READ mediaAuxInGainModel CONSTANT)

    //Property for Media Aux-In-Gain List
    Q_PROPERTY(CMediaBrowseListModel* imageDataModel READ imageDataModel CONSTANT)

    //Property for Browse category screen Title
    Q_PROPERTY(QString browseCategoryScreenTitle READ browseCategoryScreenTitle NOTIFY sigBrowseCategoryScreenTitleChanged)

    //Property for bool data update event
    Q_PROPERTY(CMediaEnum::EMediaBrowseDataState browseDataState READ browseDataState NOTIFY sigBrowseDataStateUpdated)

    //Property for nowPlayingMetadata update event
    Q_PROPERTY(CMediaEnum::EMediaBrowseItem nowPlayingMetadata READ nowPlayingMetadata NOTIFY sigNowPlayingMetadataChanged)

    //Property for Play/Pause feature Support in connectd BT Device
    Q_PROPERTY(bool isPlayPauseSupported READ isPlayPauseSupported NOTIFY sigIsPlayPauseSupportedChanged)

    //Property for Next/Prev feature Support in connectd BT Device
    Q_PROPERTY(bool isNextPrevSupported READ isNextPrevSupported NOTIFY sigIsNextPrevSupportedChanged)

    //Property for FFwd/FRwd feature Support in connectd BT Device
    Q_PROPERTY(bool isFwdRwdSupported READ isFwdRwdSupported NOTIFY sigIsFwdRwdSupportedChanged)

    //Property for Repeat feature Support in connectd BT Device
    Q_PROPERTY(bool isRepeatSupported READ isRepeatSupported NOTIFY sigIsRepeatSupportedChanged)

    //Property for Random feature Support in connectd BT Device
    Q_PROPERTY(bool isRandomSupported READ isRandomSupported NOTIFY sigIsRandomSupportedChanged)

    //Property for Browsing feature Support in connectd BT Device
    Q_PROPERTY(bool isBrowseSupported READ isBrowseSupported NOTIFY sigIsBrowseSupportedChanged)

    //Property for playtime display on Media main screen
    Q_PROPERTY(bool isPlaytimeReceived READ isPlaytimeReceived NOTIFY sigIsPlaytimeReceivedChanged)

    //Property for folder mode playBack
    Q_PROPERTY(bool isUSBFolderModePlayBack READ isUSBFolderModePlayBack NOTIFY sigUSBPlayBackModeChanged)

    //Property for folder count
    Q_PROPERTY(int folderCount READ folderCount NOTIFY sigFolderCountChanged)

    //Property for preview mode
    Q_PROPERTY(CMediaEnum::EMediaPreviewMode previewMode READ previewMode NOTIFY sigSongPreviewChanged)

    //Property for preview text
    Q_PROPERTY(QString previewText READ previewText NOTIFY sigPreviewTextChanged)

    //Property for content type of USB
    Q_PROPERTY(CMediaEnum::EMediaContentType usbContentType READ usbContentType NOTIFY sigUSBContentTypeChanged)

	//Property for BT Metadata Availability status
    Q_PROPERTY(CMediaEnum::EMediaMetadataAvailabilityStatus btMetadataAvailabilityStatus READ btMetadataAvailabilityStatus NOTIFY sigBTMetadataAvailabilityStatusChanged)

    // Property to hold the List of Image path which will be used in Picture Viewer.
    Q_PROPERTY(QList<QString> pvImageList READ pvImageList NOTIFY sigPvImageListChanged)

private: //declare your const here

    //const variable to specify path for default album art to be shown when song does not has any
    const QString DEFAULT_ALBUM_ART_PATH = "qrc:/image/Media/Med_Ico_CoverDefault/med_Gfx_CoverDefault.png";

public:
    ~CMediaAdaptor();

    /**
     * @brief To get Instance of CMediaAdaptor
     * @param void
     * @return CMediaAdaptor&
     */
    static CMediaAdaptor& getInstance();

    /**
     * @brief requestMediaActivation - Method to request switch to Media source screen
     * @param bScreenSwitchReq - boolean indicating if screen switch is required
     * @return void
     */
    void requestMediaActivation(bool bScreenSwitchReq);

    /**
     * @brief activateUSBSlotDevice - Method to activate media based on content type reported by service
     * @param bScreenSwitchRequired - boolean indicating if screen switch is required
     * @return void
     */
    void activateUSBSlotDevice(bool bScreenSwitchRequired = false);

    /**
     * @brief Returns the value of m_bIsNowPlayingDataAvail. True if available, else false.
     * @param void
     * @return m_bIsNowPlayingDataAvail - bool value indicating availability of nowPlaying data from Media service
     */
    Q_INVOKABLE inline bool isNowPlayingDataAvail() {return m_bIsNowPlayingDataAvail;}

    /**
     * @brief Returns the value of m_eUSBContentType to indicate content type for device connected to USB slot
     * @param void
     * @return m_eUSBContentType - value indicating content type
     */
    Q_INVOKABLE inline CMediaEnum::EMediaContentType getUSBContentType() {return m_eUSBContentType;}    

    /**
     * @brief Method to set the value of NowPlaying Data
     * @param void
     * @return void
     */
    void setNowPlayingData();

    /**
     * @brief onTrackSessionChangedEvent - broadcast from Media service to inform change in track session
     * @brief HMI shall get fetch preview list on this event
     * @return void
     */
    void onTrackSessionChangedEvent();

    /**
     * @brief Method to set the updated path of Album Art
     * @param strAlbumArtPath - path of the album art
     * @return void
     */
    void setAlbumArtData(const QString &strAlbumArtPath);

    /**
     * @brief Method to set the updated value of Audio Bit Rate
     * @param strBitRate - Audio bit rate
     * @return void
     */
    void setBitRateData(const QString &strBitRate);

    /**
     * @brief Method to set the updated value of Audio Sampling Rate
     * @param strSamplingRate - Audio sampling rate
     * @return void
     */
    void setSamplingRateData(const QString &strSamplingRate);

    /**
     * @brief Method to set the updated value of Video test mode parameters
     * @param void
     * @return void
     */
    void setVideoTestModeParameters();

    /**
     * @brief Method to set the updated value of video codec
     * @param strVideoCodec - Video Codec value
     * @return void
     */
    void setVideoCodec(const QString &strVideoCodec);

    /**
     * @brief Method to set the updated value of video resolution
     * @param strVideoResolution - Video resolution value
     * @return void
     */
    void setVideoResolution(const QString &strVideoResolution);

    /**
     * @brief Method to set the updated value of video frame rate
     * @param strVideoFrameRate - Video Frame Rate
     * @return void
     */
    void setVideoFrameRate(const QString &strVideoFrameRate);

    /**
     * @brief setMediaFormat: Method to set the updated value of Media format extracted from Media File Name.
     * @param strFileName - Media File Name.
     * @return void
     */
    void setMediaFormat(const QString &strFileName);

    /**
     * @brief Method to set the updated value of audio codec
     * @param strAudioCodec - Audio Codec value
     * @return void
     */
    void setAudioCodec(const QString &strAudioCodec);

    /**
     * @brief Method to set the updated value of audio sampling rate
     * @param strAudioSamplingRate - audio sampling rate
     * @return void
     */
    void setAudioSamplingRate(const QString &strAudioSamplingRate);

    /**
     * @brief Method to get the value of m_bDefaultAlbumArtDisplayed
     * @param void
     * @return m_bDefaultAlbumArtDisplayed - boolean specifiying if default album art displayed or not
     */
    Q_INVOKABLE bool isDefaultAlbumArtDisplayed() {return m_bDefaultAlbumArtDisplayed;}

    /**
     * @brief Method to get value of m_strSongTitle
     * @param void
     * @return m_strSongTitle - title of the active song
     */
    inline QString songTitle() {return m_strSongTitle;}

    /**
     * @brief Method to get value of m_strSongArtist
     * @param void
     * @return m_strSongArtist - artist of the active song
     */
    inline QString songArtist() {return m_strSongArtist;}

    /**
     * @brief Method to get value of m_strSongAlbum
     * @param void
     * @return m_strSongAlbum - album of the active song
     */
    inline QString songAlbum() {return m_strSongAlbum;}

    /**
     * @brief mediaFormat: Method to get value of m_strMediaFormat
     * @param void
     * @return m_strMediaFormat - Media Format value.
     */
    QString mediaFormat() { return m_strMediaFormat; }

    /**
     * @brief Method to get the value of m_ePlayState
     * @param void
     * @return m_ePlayState - Enum that would tell the current play state
     */
    inline CMediaEnum::EMediaPlayStates playState() {return m_ePlayState;}

    /**
     * @brief Method to get the value of m_eShuffleMode
     * @param void
     * @return m_eShuffleMode - Enum that would tell the current shuffle mode
     */
    inline CMediaEnum::EMediaShuffleMode shuffleMode() {return m_eShuffleMode;}

    /**
     * @brief Method to get the value of repeat mode received by Media service
     * @param void
     * @return m_eRepeatMode - Enum that would tell the current repeat mode
     */
    inline CMediaEnum::EMediaRepeatMode repeatMode() {return m_eRepeatMode;}

    /**
     * @brief Method to get the value of m_uiPlayTime
     * @param void
     * @return m_uiPlayTime - Value of playTime
     */
    inline uint64_t playTime() {return m_uiPlayTime;}

    /**
     * @brief Method to get the value of m_uiTotalDuration
     * @param void
     * @return m_uiTotalDuration - Value of total duration
     */
    inline uint64_t totalDuration() {return m_uiTotalDuration;}

    /**
     * @brief Method to get the value of m_strFormattedPlayTime
     * @param void
     * @return m_strFormattedPlayTime - Formatted value of playTime
     */
    inline QString formattedPlayTime() {return m_strFormattedPlayTime;}

    /**
     * @brief Method to get the value of m_strFormattedTotalDuration
     * @param void
     * @return m_strFormattedTotalDuration - Formatted value of total duration
     */
    inline QString formattedTotalDuration() {return m_strFormattedTotalDuration;}

    /**
     * @brief Method to get the value of m_bIsMediaAudioPlaying
     * @param void
     * @return m_bIsMediaAudioPlaying - bool value indicating if media audio is playing or not
     */
    inline bool isMediaAudioPlaying() {return m_bIsMediaAudioPlaying;}

    /**
     * @brief browseDataState: Method to get the value of m_eMediaBrowseDataState
     * @param void
     * @return m_eMediaBrowseDataState - value indicating state of browsing data
     */
    CMediaEnum::EMediaBrowseDataState browseDataState() {return m_eMediaBrowseDataState;}

    /**
     * @brief setMediaBrowseDataState: Method to set the value of m_eMediaBrowseDataState
     * @param m_eMediaBrowseDataState - value indicating state of browsing data
     * @return void
     */
    void setMediaBrowseDataState(CMediaEnum::EMediaBrowseDataState eMediaBrowseDataState);

    /**
     * @brief Method to get the value of m_bReadyToBrowse
     * @param void
     * @return m_bReadyToBrowse - value indicating if active Media device can be browsed
     */
    inline bool readyToBrowse() {return m_bReadyToBrowse;}

    /**
     * @brief Method to get the value of m_eNowPlayingMetadataType
     * @param void
     * @return m_eNowPlayingMetadataType - metadata value of current playing song
     */
    inline CMediaEnum::EMediaBrowseItem nowPlayingMetadata() {return m_eNowPlayingMetadataType;}

    /**
     * @brief Method to get the value of m_eUSBSyncState
     * @param void
     * @return m_eUSBSyncState - value indicating syncState of device connected to the USB slot
     */
    inline CMediaEnum::EMediaSyncState usbSlotSyncState() {return m_eUSBSyncState;}

    /**
     * @brief Method to get the value of m_eBTSyncState
     * @param void
     * @return m_eBTSyncState - value indicating syncState of device connected to the BT slot
     */
    inline CMediaEnum::EMediaSyncState btSlotSyncState() {return m_eBTSyncState;}

    /**
     * @brief Method to set the value of m_ePlayState
     * @param iPlayState - Value of play state from Media service
     * @return void
     */
    void setPlayState(const int &iPlayState);

    /**
     * @brief Method to set the shuffle mode value received from Media service
     * @param iShuffleMode - Value of shuffle mode
     * @return void
     */
    void setShuffleMode(const int &iShuffleMode);

    /**
     * @brief Method to set the repeat mode value received from Media service
     * @param iRepeatMode - Value of repeat mode
     * @return void
     */
    void setRepeatMode(const int &iRepeatMode);

    /**
     * @brief Method to set the playTime value received from Media service
     * @param uiPlayTime - playTime value received from service
     * @return void
     */
    void setPlayTime(const uint64_t &uiPlayTime);

    /**
     * @brief Method to set the totalDuration value received from Media service
     * @param uiTotalDuration - totalDuration value received from service
     * @return void
     */
    void setTotalDuration(const uint64_t &uiTotalDuration);

    /**
     * @brief setTrackNumber - Method to set the track number value received from Media service
     * @param uiTrackNumber - tarck number value received from service
     * @return void
     */
    void setTrackNumber(const uint64_t &uiTrackNumber);

    /**
     * @brief Method to inform adaptor about updated sync state
     * @param void
     * @return void
     */
    void syncStateUpdated();

    /**
     * @brief Method to inform adaptor about updated content type for USB
     * @param iContentType - content type for USB
     * @return void
     */
    void setContentType(int iContentType);

    /**
     * @brief setUSBPlayBackMode() - Method to inform adaptor about updated play back mode for USB
     * @param int - play back mode for USB
     * @return void
     */
    void setUSBPlayBackMode(int iMediaUSBPlayBackMode);

    /**
     * @brief Method to inform adaptor about updated categories for device connected to USB slot
     * @param void
     * @return void
     */
    void usbCategoriesUpdated();

    /**
     * @brief Method to check if requested category of device connected to USB slot is available for browsing or not
     * @param eBrowseItem - item to be browsed
     * @return bool indicating if the category is available or not
     */
    Q_INVOKABLE bool isUSBDeviceCategoryAvailable(CMediaEnum::EMediaBrowseItem eBrowseItem);

    /**
     * @brief Method to check count for category passed as param for device connected to USB slot
     * @param eBrowseItem - for which count is required
     * @return int - count for items in given category
     */
    Q_INVOKABLE int getUSBDeviceCategoryCount(CMediaEnum::EMediaBrowseItem eBrowseItem);

    /**
     * @brief showSongPreview - Method to show song preiew for prev/next song
     * @param ePreviewMode - preview mode i.e. next/prev
     * @return void
     */
    Q_INVOKABLE void showSongPreview(CMediaEnum::EMediaPreviewMode ePreviewMode);

    /**
     * @brief playPreviewSong - Method to request Media service to play the song displayed in preview mode
     * @param void
     * @return void
     */
    Q_INVOKABLE void playPreviewSong();

    /**
     * @brief requestPreviousSource - Method to switch to previous source from Media
     * @param void
     * @return void
     */
    Q_INVOKABLE void requestPreviousSource();

    /**
     * @brief updateNoSongsUSBResponse - Method to set the value of m_bNoSongsUSBAccepted which shall confirm if user wants to view USB without songs
     * @param bUserResponse - bool indicating user's response
     * @return void
     */
    Q_INVOKABLE void setNoSongsUSBResponse(bool bUserResponse) { m_bNoSongsUSBAccepted = bUserResponse; }

    /**
     * @brief getNoSongsUSBResponse - Method to get the value of m_bNoSongsUSBAccepted which shall confirm if user wants to view USB without songs
     * @param void
     * @return m_bNoSongsUSBAccepted - bool indicating user's response
     */
    Q_INVOKABLE bool getNoSongsUSBResponse() { return m_bNoSongsUSBAccepted; }

    /**
     * @brief getMediaControlsVisibility - Returns true if Media controls should be displayed
     * @param void
     * @return bool
     */
    Q_INVOKABLE bool getMediaControlsVisibility();


    /**
     * @brief getPvCurrentImageIndex - Returns current image index that is set in Image Viewer.
     * @param void
     * @return int: Current Image index
     */
    Q_INVOKABLE int getPvCurrentImageIndex();

    /**
     * @brief setPvCurrentImageIndex - Method to update the current image index to the viewing image index.
     * @param int: Current Image index
     * @return void
     */
    Q_INVOKABLE void setPvCurrentImageIndex(int iIndex);

    /**
     * @brief Method to inform adaptor about updated categories for device connected to BT slot
     * @param void
     * @return void
     */
    void btCategoriesUpdated();

    /**
     * @brief Method to inform Media Adaptor that updated breadcrumb path is received
     * @param strBreadcrumbPath - path to browsing category
     * @return void
     */
    void breadcrumbPathUpdated(const string& strBreadcrumbPath);

    /**
     * @brief Method to inform Media Adaptor to set root level of browse on HMI
     * @param void
     * @return void
     */
    void setRootLevelBrowse();

    /**
     * @brief Method to inform Media Adaptor that corrupt video is accessed
     * @param void
     * @return void
     */
    void corruptVideoAccessed();

    /**
     * @brief Method to inform Media Adaptor to about error of device connected to USB slot
     * @param void
     * @return void
     */
    void usbDeviceError(const int &iUSBDeviceError);

    /**
     * @brief Method to check if requested category of device connected to BT slot is available for browsing or not
     * @param eBrowseItem - item to be browsed
     * @return bool indicating if the category is available or not
     */
    Q_INVOKABLE bool isBTDeviceCategoryAvailable(CMediaEnum::EMediaBrowseItem eBrowseItem);

    /**
     * @brief Method to display popup when selected browse category is empty
     * @param eBrowseItem - empty browse item for which popup is to be displayed
     * @return void
     */
    Q_INVOKABLE void showEmptyCategoryPopup(CMediaEnum::EMediaBrowseItem eBrowseItem);

    /**
     * @brief Method to get value of m_strAlbumArtPath
     * @param void
     * @return m_strAlbumArtPath - path of the album art
     */
    inline QString albumArtPath() {return m_strAlbumArtPath;}

    /**
     * @brief Method to get value of m_strBitRate
     * @param void
     * @return m_strBitRate - Audio bit rate
     */
    QString bitRate() {return m_strBitRate;}

    /**
     * @brief Method to get value of m_strSamplingRate
     * @param void
     * @return m_strSamplingRate - Audio sampling rate
     */
    QString samplingRate() {return m_strSamplingRate;}

    /**
     * @brief Method to get value of m_strVideoCodec
     * @param void
     * @return m_strVideoCodec - Video codec value
     */
    QString videoCodec() {return m_strVideoCodec;}

    /**
     * @brief Method to get value of m_strVideoResolution
     * @param void
     * @return m_strVideoResolution - Video resolution value
     */
    QString videoResolution() {return m_strVideoResolution;}

    /**
     * @brief Method to get value of m_strVideoFrameRate
     * @param void
     * @return m_strVideoFrameRate - Video frame rate value
     */
    QString videoFrameRate() {return m_strVideoFrameRate;}

    /**
     * @brief Method to get value of m_strAudioCodec
     * @param void
     * @return m_strAudioCodec - audio codec of a video
     */
    QString audioCodec() {return m_strAudioCodec;}

    /**
     * @brief Method to get value of m_strAudioSamplingRate
     * @param void
     * @return m_strAudioSamplingRate - audio sampling rate of a video
     */
    QString audioSamplingRate() {return m_strAudioSamplingRate;}

    /**
     * @brief Method to display popup when selected browse category is empty
     * @param iItemFID - File ID of the item
     * @param iMetadataType - Metadata type of the item
     * @param strItemValue - Label of the item
     * @param iFSContentType - folder or playlist type
     * @param iListIndexNo - index no in the list
     * @param bIsVRRequest - bool to indicate if this request is for VR browsing
     * @return void
     */
    Q_INVOKABLE void browseItemClicked(int iItemFID, int iMetadataType, QString strItemValue, int iFSContentType, int iListIndexNo, bool bIsVRRequest = false);

    /**
     * @brief Method to store the image list data from resource
     * @return void
     */
    void storeImageData();

    /**
     * @brief Method to store the browse list data from resource
     * @param iStartIndex - startIndex for which the data is received from Media service
     * @return void
     */
    void storeBrowseData(int iStartIndex);

    /**
     * @brief Method to create an empty list of size - iBrowseCategoryListSize and also initialize windowing
     * @param iBrowseCategoryListSize - size of the list
     * @return void
     */
    void createBrowseList(int iBrowseCategoryListSize);

    /**
     * @brief createNowPlayingList - Method to create an empty list of size - iNowPlayingListSize and also initialize windowing
     * @param iNowPlayingListSize - size of the list
     * @return void
     */
    void createNowPlayingList(int iNowPlayingListSize);

    /**
     * @brief storeNowPlayingData - Method to store/get the now playing data from resource
     * @param void
     * @return void
     */
    void storeNowPlayingList();

    /**
     * @brief Method to execute actions when requested browse item is empty
     * @param void
     * @return void
     */
    void browseItemEmpty();

    /**
     * @brief showStoredBrowseData: Method to execute actions when requested browse item is empty
     * @param void
     * @return void
     */
    void showStoredBrowseData();

    /**
     * @brief Method to return the count of images received
     * @return int: TotalImage count
     */
    int totalImageCount();

    /**
     * @brief Method to return the count of folders received from Media service
     * @return int: Total folder count
     */
    int folderCount() { return m_iUSBFolderCount; }

    /**
    * @brief handleHardKeys Funtion to handle hardkey as per media specifications.
    * @param eKey the key on which the action is triggered.
    * @param eState state of the key on which the action is triggered.
    * @return  true is an action was taken false otherwise.
    */
    bool handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
     * @brief Method to return current value of m_strActiveMediaSrcTitle
     * @param void
     * @return QString - current value of m_strActiveMediaSrcTitle
     */
    inline QString activeMediaSrcTitle() {return m_strActiveMediaSrcTitle;}

    /**
     * @brief Method to return current value of m_strBrowseCategoryScreenTitle
     * @param void
     * @return QString - current value of m_strBrowseCategoryScreenTitle
     */
    inline QString browseCategoryScreenTitle() {return m_strBrowseCategoryScreenTitle;}

    /**
     * @brief Method to get Browse Category List Model
     * @param void
     * @return CMediaBrowseCategoryListModel* - Pointer of class CMediaBrowseCategoryListModel
     */
    inline CMediaBrowseCategoryListModel* mediaCategoryListModel() {return m_pBrowseCategoryList;}

    /**
     * @brief Method to get Browse List Model
     * @param void
     * @return CMediaBrowseListModel* - Pointer of class CMediaBrowseListModel
     */
    inline CMediaBrowseListModel* mediaBrowseListModel() {return m_pBrowseList;}

    /**
     * @brief Method to get AUX-In-Gain List Model
     * @param void
     * @return m_pSetupAUXGainListModel - Pointer of class CSetupListModel
     */
    inline CSetupListModel* mediaAuxInGainModel() {return m_pSetupAUXGainListModel;}

    /**
     * @brief Method to get Image List Model
     * @param void
     * @return m_pImageListModel - Object of Imagedata model class
     */
    inline CMediaBrowseListModel* imageDataModel() {return m_pImageListModel;}

    /**
     * @brief browseSessionCreated: TO be invoked from event handler, used to trigger auto browse related activities.
     * @param void
     * @return void
     */
    void browseSessionCreated();

    /**
     * @brief Method to update the current Browselist screen. To be called when active ent. source is changed
     * @param void
     * @return void
     */
    Q_INVOKABLE void updateMediaBrowseList();

    /**
     * @brief vrBrowseRequest: Method to request data for VR browsing session
     * @param eMediaBrowseItem: Item type to be browsed
     * @param iBrowseItemID: ID of item to be browsed
     * @return EMediaVRBrowseState: Enum to indicate the status of browse request
     */
    CMediaEnum::EMediaVRBrowseState requestVRBrowse(CMediaEnum::EMediaBrowseItem eMediaBrowseItem, int iBrowseItemID);

    /**
     * @brief directMediaStateSwitch - Method to switch directly to Media browse category screen or PV based on browse category
     * @param CMediaEnum::EMediaBrowseItem
     * @return void
     */
    Q_INVOKABLE void directMediaStateSwitch(CMediaEnum::EMediaBrowseItem eMediaBrowseItem);

    /**
     * @brief handleAllVideosCorrupt - Method to decide further actions when all videos are corrupt in USB
     * @param void
     * @return void
     */
    Q_INVOKABLE void handleAllVideosCorrupt();

    /**
     * @brief Method to get dynamic text for popup based on device
     * @param void
     * @return QString -dynamic text to be displayed in the popup
     */
    Q_INVOKABLE QString getEmptyCategoryText();

    /**
     * @brief Method to get dynamic text for popup based on USB device error
     * @param void
     * @return QString - dynamic text to be displayed in the popup
     */
    Q_INVOKABLE QString getStrUSBDeviceErrorPopupText() const;

    /**
     * @brief Method to request browse items for previous level from Media service
     * @param void
     * @return void
     */
    Q_INVOKABLE void goToPreviousLevel();

    /**
     * @brief Method to request browse items from Media service
     * @brief This method shall only fetch first level of browse list
     * @param eMediaBrowseItem - item to be browsed
     * @param bIsVRRequest - bool to indicate if this request is for VR browsing
     * @return void
     */
    Q_INVOKABLE void getCategoryRoot(CMediaEnum::EMediaBrowseItem eMediaBrowseItem, bool bIsVRRequest = false);

    /**
     * @brief Method to process the browse request by user for a particular category
     * @brief This method shall process the request based on active source and fetch browse items
     * @param eMediaBrowseItem - item to be browsed
     * @return void
     */
    Q_INVOKABLE void processBrowseCategoryRequest(CMediaEnum::EMediaBrowseItem eMediaBrowseItem);

    /**
     * @brief Method to add some delay between two run cycles while processing a request to hide drawers
     * @param void
     * @return void
     */
    void processHideDrawersDelay();

    /**
     * @brief cancelFastForward - Method to be invoked only when FFwd is to be cancelled when SW update key is received
     *  Key combination for SW update also includes a LP of Next HK which starts FFwd
     * @param void
     * @return void
     */
    Q_INVOKABLE void cancelFastForward();

    /**
     * @brief Method to update remote Player Capabilities for BT Device connected
     * @param void
     * @return void
     */
    void remotePlayerCapabilitiesUpdate();

    /**
     * @brief Method to get the value of m_bIsPlayPauseSupported
     * @param void
     * @return m_bIsPlayPauseSupported - bool value that tells if Play/Pause feature is supported or not
     */
    inline bool isPlayPauseSupported() {return m_bIsPlayPauseSupported;}

    /**
     * @brief Method to get the value of m_bIsNextPrevSupported
     * @param void
     * @return m_bIsNextPrevSupported - bool value that tells if Next/Prev feature is supported or not
     */
    inline bool isNextPrevSupported() {return m_bIsNextPrevSupported;}

    /**
     * @brief Method to get the value of m_bIsFwdRwdSupported
     * @param void
     * @return m_bIsFwdRwdSupported - bool value that tells if FFwd/FRwd feature is supported or not
     */
    inline bool isFwdRwdSupported() {return m_bIsFwdRwdSupported;}

    /**
     * @brief Method to get the value of m_bIsRepeatSupported
     * @param void
     * @return m_bIsRepeatSupported - bool value that tells if Repeat feature is supported or not
     */
    inline bool isRepeatSupported() {return m_bIsRepeatSupported;}

    /**
     * @brief Method to get the value of m_bIsRandomSupported
     * @param void
     * @return m_bIsRandomSupported - bool value that tells if Random feature is supported or not
     */
    inline bool isRandomSupported() {return m_bIsRandomSupported;}

    /**
     * @brief Method to get the value of m_bIsBrowseSupported
     * @param void
     * @return m_bIsBrowseSupported - bool value that tells if Browsing feature is supported or not
     */
    inline bool isBrowseSupported() {return m_bIsBrowseSupported;}

    /**
     * @brief Method to get the value of m_bShowPlaytime
     * @param void
     * @return m_bShowPlaytime - bool value that tells if playtime is received from service
     */
    inline bool isPlaytimeReceived() {return m_bShowPlaytime;}

    /**
     * @brief Method to set status of m_bShowPlaytime.
     * @param bShowPlaytime - value to be set as m_bShowPlaytime
     * @return void
     */
    void showPlayTime(bool bShowPlaytime);

    /**
     * @brief Method to get the value of m_bIsFolderModePlayBack
     * @param void
     * @return m_bIsFolderModePlayBack - bool value that tells if play back is via folder mode
     */
    inline bool isUSBFolderModePlayBack() {return m_bIsFolderModePlayBack;}
	
	/**
     * @brief Method to get the value of m_eBTMetadataAvailabilityStatus
     * @param void
     * @return m_eBTMetadataAvailabilityStatus - current BT Metadata Availability status
     */
    inline CMediaEnum::EMediaMetadataAvailabilityStatus btMetadataAvailabilityStatus() {return m_eBTMetadataAvailabilityStatus;}
	
	/**
     * @brief Method to set updated value of BT Metadata Availability status
     * @param iMetaDataAvailablityStatus - updated value of BT Metadata Availability status
     * @return void
     */
    void setBTMetadataAvailabilityStatus(int iMetaDataAvailablityStatus);

    /**
     * @brief previewMode - Method to get the value of m_ePreviewMode
     * @param void
     * @return m_ePreviewMode - preview mode value
     */
    CMediaEnum::EMediaPreviewMode previewMode() {return m_ePreviewMode;}

    /**
     * @brief usbContentType - Method to get the value of m_eUSBContentType
     * @param void
     * @return m_eUSBContentType - content type of USB
     */
    CMediaEnum::EMediaContentType usbContentType() {return m_eUSBContentType;}

    /**
     * @brief previewText - Method to get the preview text i.e. prev/next song name
     * @param void
     * @return m_strSongPreviewText - preview text i.e. prev/next song name
     */
    QString previewText() {return m_strSongPreviewText;}

    /**
     * @brief getMediaBrowseItemSelected - Method to get the media browse item selected by user
     * @param void
     * @return EMediaBrowseItem - selected media browse item
     */
    CMediaEnum::EMediaBrowseItem getMediaBrowseItemSelected();

    /**
     * @brief setMediaBrowseItemSelected - Method to set the media browse item selected by user
     * @param eBrowseCategorySelected - selected browse category
     * @return void
     */
    void setMediaBrowseItemSelected(CMediaEnum::EMediaBrowseItem eBrowseCategorySelected);

    /**
     * @brief getMediaDisplayState - Method to get the display state of Media
     * @param void
     * @return EMediaDisplayState - current display state
     */
    CMediaEnum::EMediaDisplayState getMediaDisplayState() const;

    /**
     * @brief setMediaDisplayState - Method to set the display state of Media
     * @param eMediaDisplayState - current display state
     * @return void
     */
    Q_INVOKABLE void setMediaDisplayState(CMediaEnum::EMediaDisplayState eMediaDisplayState);

    /**
     * @brief getMediaOperationState - Method to get the operation state of Media
     * @param void
     * @return EMediaOperationState - current operation state
     */
    CMediaEnum::EMediaOperationState getMediaOperationState() const;

    /**
     * @brief compareMediaOperationState - Returns true if Media operation state is same as input value
     * @param eMediaOperationState - operation state to compare
     * @return bool - result of comparison
     */
    Q_INVOKABLE bool compareMediaOperationState(CMediaEnum::EMediaOperationState eMediaOperationState);

    /**
     * @brief setMediaOperationState - Method to set the operation state of Media
     * @param eMediaOperationState - current operation state
     * @return void
     */
    void setMediaOperationState(CMediaEnum::EMediaOperationState eMediaOperationState);

    /**
     * @brief getMediaCategoryBrowsed - Method to get the media browse item selected by user
     * @param void
     * @return EMediaBrowseItem - category being browsed
     */
    CMediaEnum::EMediaBrowseItem getMediaCategoryBrowsed();

    /**
     * @brief setMediaCategoryBrowsed - Method to set the category being browsed
     * @param m_eMediaCategoryBrowsed - selected browse category
     * @return void
     */
    void setMediaCategoryBrowsed(CMediaEnum::EMediaBrowseItem eMediaCategoryBrowsed);

    /**
     * @brief pvImageList: This function will return the data image list containg image source string.
     * @param void.
     * @return: List of Qstrings containg Image Source Path.
     */
    QList<QString> pvImageList(){ return m_listImageData ; }

    /**
     * @brief getImageTitle: This function will return the image title.
     * @param iPvCurrentIndex: Current index for which image title is needed.
     * @return: Image title for Current index.
     */
    Q_INVOKABLE QString getImageTitle(int iPvCurrentIndex);

    /**
     * @brief updateRvcState provide media pres plugin with the latest reverse gear status
     * @param bRvcStatus, current reverse gear status (engage/disengage) (true/false)
     * @return void
     */
    void updateRvcState(bool bRvcStatus);

    /**
     * @brief handleVideoSurface: This method calls the API of media pres, to show / hide the video surface.
     * @param bVideoSurfaceStatus: true - show video surface, false - hide video surface.
     * @return void.
     */
    void handleVideoSurface(bool bVideoSurfaceStatus);


    /**
     * @brief Method to update index of Now Playing pointer in current Browse category list
     * @param iPrevIndex: Index of item previously highlighted with now playing pointer
     * @param iNewIndex: Index of item to be highlighted with now playing pointer
     * @return void
     */
    void updateNowPlayingPointer(int iPrevIndex, int iNewIndex);

    //API's to be called directly byQML files
    /**
     * @brief Method to be invoked from QML to play the next song
     * @param CMediaEnum::EButtonStates eButtonState - state of next button
     * @return void
     */
    Q_INVOKABLE void next(CMediaEnum::EButtonStates eButtonState);

    /**
     * @brief Method to be invoked from QML to play the previous song
     * @param CMediaEnum::EButtonStates eButtonState - state of prev button
     * @return void
     */
    Q_INVOKABLE void prev(CMediaEnum::EButtonStates eButtonState);

    /**
     * @brief Method to be invoked from QML to resume song
     * @param CMediaEnum::EButtonStates eButtonState - state of resume button
     * @return void
     */
    Q_INVOKABLE void resume(CMediaEnum::EButtonStates eButtonState);

    /**
     * @brief Method to be invoked from QML to pause song
     * @param CMediaEnum::EButtonStates eButtonState - state of pause button
     * @return void
     */
    Q_INVOKABLE void pause(CMediaEnum::EButtonStates eButtonState);

    /**
     * @brief Method to be invoked from QML to fast forward song
     * @param CMediaEnum::EButtonStates eButtonState - state of next button
     * @return void
     */
    Q_INVOKABLE void fastForward(CMediaEnum::EButtonStates eButtonState);

    /**
     * @brief Method to be invoked from QML to fast rewind song
     * @param CMediaEnum::EButtonStates eButtonState - state of prev button
     * @return void
     */
    Q_INVOKABLE void fastRewind(CMediaEnum::EButtonStates eButtonState);

    /**
     * @brief Method to be invoked from QML to resume/pause current song depending on the current play state
     * @param CMediaEnum::EButtonStates eButtonState - state of play/pause button
     * @return void
     */
    Q_INVOKABLE void toggleResumePause(CMediaEnum::EButtonStates eButtonState);

    /**
     * @brief Method to be invoked from QML to toggle the shuffle mode of current track session
     * @param CMediaEnum::EButtonStates eButtonState - state of shuffle button
     * @return void
     */
    Q_INVOKABLE void toggleShuffleMode(CMediaEnum::EButtonStates eButtonState);

    /**
     * @brief Method to be invoked from QML to request the service to seek/jump the song from/to requested time
     * @param uint - time in secs to which seek is requested
     * @return void
     */
    Q_INVOKABLE void seekToTime(uint uiSeekToTime);

    /**
     * @brief Method to be invoked from QML to toggle the repeat mode of current track session
     * @param CMediaEnum::EButtonStates eButtonState - state of repeat button
     * @return void
     */
    Q_INVOKABLE void toggleRepeatMode(CMediaEnum::EButtonStates eButtonState);

    /**
     * @brief Method to format the song playtime and duration in HH:MM:SS format
     * @param uiTimeInSecs-  time in secs which is to be formatted
     * @return QString - formatted time in HH:MM:SS
     */
    Q_INVOKABLE QString getFormattedTime(const uint &uiTimeInSecs);

    /**
     * @brief Method to initiate playback from next folder on USB device
     * @param void
     * @return void
     */
    Q_INVOKABLE void nextFolder();

    /**
     * @brief Method to initiate playback from previous folder on USB device
     * @param void
     * @return void
     */
    Q_INVOKABLE void previousFolder();

    /**
     * @brief	This method will return path to browse category icon based on the Metadata type value provided
     * @param	eBrowseItem - browse item i.e. albums, artists, folders etc
     * @param   bIsEnabled - bool value to fetch the enabled or disabled image
     * @param   iListIndexNo - index of item in the list to decide 'Play All' option
     * @return	void
     */
    Q_INVOKABLE QString getBrowseCategoryImagePath(CMediaEnum::EMediaBrowseItem eBrowseItem, bool bIsEnabled = true);

    /**
     * @brief Method to call requestPage method of Windowing Helper class
     * @param iIndex: item index for which the page request needs to be sent
     * @return void
     */
     Q_INVOKABLE void requestPage(int iIndex);

    /**
     * @brief Method to call resetWindowingParam method of Windowing Helper class which would reset the Windowing Queue and stop fetching data from Service
     * @param void
     * @return void
     */
     void resetWindowing();

     /**
      * @brief emptyListReceived - Method invoked when an empty list is received from Media Service.
      *                            This method would mark the respective page as not requested so that it can be fetched again.
      * @param iStartIndex - startIndex for which the an empty list is received from Media service
      * @return void
      */
     void emptyListReceived(int iStartIndex);

     /**
      * @brief	getMediaVRBrowseState: This method will return of m_eMediaVRBrowseState var
      * @param	void
      * @return	m_eMediaVRBrowseState - var indicating state of VR browse
      */
     CMediaEnum::EMediaVRBrowseState getMediaVRBrowseState();

     /**
      * @brief	setMediaVRBrowseState: This method will set the value of m_eMediaVRBrowseState var
      * @param	eMediaVRBrowseState: value to be set
      * @return	void
      */
     void setMediaVRBrowseState(CMediaEnum::EMediaVRBrowseState eMediaVRBrowseState);

     /**
      * @brief getBreadcrumbPath - Method to get the value of m_strBreadcrumbPath
      * @param void
      * @return QString - current value of m_strBreadcrumbPath
      */
     QString getBreadcrumbPath() {return m_strBreadcrumbPath;}

     /**
      * @brief	processRCARequest: This method will process the request from RCA
      * @param	eRCAActionInitiated: Action initiated from RCA
      * @param uiIntInfo: int data to be passed
      * @return	void
      */
     void processRCARequest(CRCAEnums::ERCAActionInitiated eRCAActionInitiated, uint uiIntInfo);

     /**
      * @brief initBrowse: Method used to initiate browse commands to browse the tracks for sound demo
      * @param void
      * @return void
      */
     void initBrowse(CMediaEnum::EMediaBrowseItem eCategory);

signals:

    /**
     * @brief Signal emitted whenever m_bIsNowPlayingDataAvail is updated
     * @param void
     * @return void
     */
    void sigNowPlayingDataAvailUpdated();

    /**
     * @brief Signal emitted whenever metadata type of now Playing media is changed
     * @param void
     * @return void
     */
    void sigNowPlayingMetadataChanged();

    /**
     * @brief Signal emitted whenever now Playing data is changed
     * @param void
     * @return void
     */
    void sigNowPlayingChanged();

    /**
     * @brief Signal emitted whenever songTitle is updated
     * @param void
     * @return void
     */
    void sigSongTitleChanged();

    /**
     * @brief Signal emitted whenever songArtist is updated
     * @param void
     * @return void
     */
    void sigSongArtistChanged();

    /**
     * @brief Signal emitted whenever songAlbum is updated
     * @param void
     * @return void
     */
    void sigSongAlbumChanged();

    /**
     * @brief sigMediaFormatChanged: Signal emitted whenever mediaFormat is updated
     * @param void
     * @return void
     */
    void sigMediaFormatChanged();

    /**
     * @brief Signal emitted whenever playState is updated
     * @param void
     * @return void
     */
    void sigPlayStateChanged();

    /**
     * @brief Signal emitted whenever shuffle mode is updated
     * @param void
     * @return void
     */
    void sigShuffleModeChanged();

    /**
     * @brief Signal emitted whenever repeat mode is updated
     * @param void
     * @return void
     */
    void sigRepeatModeChanged();

    /**
     * @brief Signal emitted whenever playTime is updated
     * @param void
     * @return void
     */
    void sigPlayTimeChanged();

    /**
     * @brief Signal emitted whenever totalDuration is updated
     * @param void
     * @return void
     */
    void sigTotalDurationChanged();

    /**
     * @param void
     * @return void
     */
    void sigFormattedPlayTimeChanged();

    /**
     * @brief Signal emitted whenever totalDuration is updated with a fomatted value of HH:MM:SS
     * @param void
     * @return void
     */
    void sigFormattedTotalDurationChanged();

    /**
     * @brief Signal emitted whenever AlbumArt for the song is updated
     * @param void
     * @return void
     */
    void sigAlbumArtChanged();

    /**
     * @brief Signal emitted whenever bit rate for Media audio is updated
     * @param void
     * @return void
     */
    void sigBitRateChanged();

    /**
     * @brief Signal emitted whenever sampling rate for Media audio is updated
     * @param void
     * @return void
     */
    void sigSamplingRateChanged();

    /**
     * @brief Signal emitted whenever image count is updated
     * @param void
     * @return void
     */
    void sigTotalImageCountChanged();

    /**
     * @brief Signal emitted whenever current index of image is updated
     * @param void
     * @return void
     */
    void sigImageIndexChanged();

    /**
     * @brief Signal emitted whenever folder count for USB source is updated
     * @param void
     * @return void
     */
    void sigFolderCountChanged();

    /**
     * @brief Signal emitted whenever song preview value is updated
     * @param void
     * @return void
     */
    void sigSongPreviewChanged();

    /**
     * @brief Signal emitted whenever content type value is updated
     * @param void
     * @return void
     */
    void sigUSBContentTypeChanged();

    /**
     * @brief Signal emitted whenever song name to be displayed in preview is updated
     * @param void
     * @return void
     */
    void sigPreviewTextChanged();

    /**
     * @brief Signal emitted whenever m_bIsMediaAudioPlaying value is updated
     * @param void
     * @return void
     */
    void sigIsMediaAudioPlayingChanged();

    /**
     * @brief Signal emitted whenever m_strActiveMediaSrcTitle value is updated
     * @param void
     * @return void
     */
    void sigActiveMediaSrcTitleChanged();

    /**
     * @brief Signal emitted whenever m_bReadyToBrowse value is updated
     * @param void
     * @return void
     */
    void sigReadyToBrowseChanged();

    /**
     * @brief Signal emitted whenever syncState of device connected to USB slot is updated
     * @param void
     * @return void
     */
    void sigUSBSlotSyncState();

    /**
     * @brief Signal emitted whenever syncState of device connected to BT slot is updated
     * @param void
     * @return void
     */
    void sigBTSlotSyncState();

    /**
     * @brief Signal emitted whenever Media Browse Category list is updated is updated.
     * @param void
     * @return void
     */
    void sigMediaCategoryListModel();

    /**
     * @brief Signal emitted whenever Media Browse data state is updated
     * @param void
     * @return void
     */
    void sigBrowseDataStateUpdated();

    /**
     * @brief Signal emitted whenever title for Browse category screenis updated dynamically
     * @param void
     * @return void
     */
    void sigBrowseCategoryScreenTitleChanged();

    /**
     * @brief Signal emitted whenever m_bIsPlayPauseSupported value is updated
     * @param void
     * @return void
     */
    void sigIsPlayPauseSupportedChanged();

    /**
     * @brief Signal emitted whenever m_bIsNextPrevSupported value is updated
     * @param void
     * @return void
     */
    void sigIsNextPrevSupportedChanged();

    /**
     * @brief Signal emitted whenever m_bIsFwdRwdSupported value is updated
     * @param void
     * @return void
     */
    void sigIsFwdRwdSupportedChanged();

    /**
     * @brief Signal emitted whenever m_bIsRepeatSupported value is updated
     * @param void
     * @return void
     */
    void sigIsRepeatSupportedChanged();

    /**
     * @brief Signal emitted whenever m_bIsRandomSupported value is updated
     * @param void
     * @return void
     */
    void sigIsRandomSupportedChanged();

    /**
     * @brief Signal emitted whenever m_bIsBrowseSupported value is updated
     * @param void
     * @return void
     */
    void sigIsBrowseSupportedChanged();

    /**
     * @brief Signal emitted whenever m_bShowPlaytime value is updated
     * @param void
     * @return void
     */
    void sigIsPlaytimeReceivedChanged();

    /**
     * @brief Signal emitted whenever m_eMediaUSBPlayBackMode value is updated
     * @param void
     * @return void
     */
    void sigUSBPlayBackModeChanged();

    /**
     * @brief Signal emitted whenever video codec value is updated
     * @param void
     * @return void
     */
    void sigVideoCodecChanged();

    /**
     * @brief Signal emitted whenever video resolution value is updated
     * @param void
     * @return void
     */
    void sigVideoResolutionChanged();

    /**
     * @brief Signal emitted whenever video frame rate value is updated
     * @param void
     * @return void
     */
    void sigVideoFrameRateChanged();

    /**
     * @brief Signal emitted whenever audio sampling rate of a video is updated
     * @param void
     * @return void
     */
    void sigAudioSamplingRateChanged();

    /**
     * @brief Signal emitted whenever audio codec in a video is updated
     * @param void
     * @return void
     */
    void sigAudioCodecChanged();

    /**
     * @brief Signal emitted whenever m_eBTMetadataAvailabilityStatus value is updated
     * @param void
     * @return void
     */
    void sigBTMetadataAvailabilityStatusChanged();

    /**
     * @brief   sigProcessHideDrawers: This signal will be emitted When Media needs
     *          to hide the drawer, like from Video screen.
     * @param   void.
     * @return  void.
     */
    void sigProcessHideDrawers();

    /**
     * @brief sigPvImageListChanged: This signal will emit when List containing image source path will be changed.
     * @param void.
     * @return void.
     */
    void sigPvImageListChanged();

    /**
     * @brief sigBrowseSessionCreated: Signal to update the creation of browse session to start auto browse.
     * @param void
     * @return void
     */
    void sigBrowseSessionCreated();

    /**
     * @brief sigUpdateNowPlayingPointer: Signal to update the nowplaying pointer.
     * @param iOldIndex: list item index from where the highlight is to be removed.
     * @param iNewIndex: list item index to be highlighted.
     * @return void
     */
    void sigUpdateNowPlayingPointer(int iOldIndex, int iNewIndex);

    /**
     * @brief sigBrowseDataReceived: Signal to update the receival of browse data
     * @param iCategory: Category of data received
     * @return void
     */
    void sigBrowseDataReceived(int iCategory);

  public slots:

    /**
     * @brief	This method shall be invoked when signal sigUSBConnectionStatuschanged shall be emitted. Audio Manager shall send emit this signal when USB is connected or disconnected.
     * @param	void
     * @return	void
     */
    void sltUSBConnectionStatuschanged();

    /**
    * @brief	This method shall be invoked when signal sigIPODConnectionStatuschanged shall be emitted. Audio Manager shall send emit this signal when iPod is connected or disconnected.
    * @param	void
    * @return	void
    */
    void sltIpodConnectionStatuschanged();

    /**
    * @brief	This method shall be invoked when signal sigAUXConnectionStatuschanged shall be emitted. Audio Manager shall send emit this signal when AUX is connected or disconnected.
    * @param	void
    * @return	void
    */
    void sltAUXConnectionStatuschanged();

    /**
    * @brief	This method shall be invoked when signal sigBTSrcStatuschanged shall be emitted. Audio Manager shall send emit this signal when BT Device is connected or disconnected for A2DP.
    * @param	void
    * @return	void
    */
    void sltBTSrcStatuschanged();

    /**
    * @brief This method shall be invoked when signal sigActiveEntSrcChanged is emitted. Audio Manager shall send emit signal whenever Active Entertainment source is updated
    * @param void
    * @param void
    */
    void sltActiveMediaSrcChanged();

    /**
     * @brief Method gets invoked whenever there is a change in AUX gain value
     * @param void
     * @return void
     */
    void sltAuxGainValueChanged();

    /**
     * @brief Method gets invoked whenever there is a change in vehicle speed lockout value
     * @param void
     * @return void
     */
    void sltSpeedLockOutStatusChanged();

    /**
     * @brief sltProcessHideDrawers: This is the slot of signal sigProcessHideDrawers
     *        this function raises the event to state machine to hide the drawers.
     * @param void
     * @return void
     */
    void sltProcessHideDrawers();

    /**
     * @brief Slot to be connected to PopupManager's signal sigPopupResult to handle Popup events
     * @param ePopupId - Id of the Popup
     * @param EPopupPriority - Result of the Popup(Displayed, Closed or Ignored)
     * @param strAdditionalInfo - Additional info (based on reason on which popup is closed)
     */
    void sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo);

    /**
     * @brief Slot to be connected to PowerModeadaptor's signal sigPowerModeChanged to handle actions on power mode change event
     * @param null
     * @return void
     */
    void sltPowerModeChanged();

private slots:

    /**
     * @brief Method gets invoked when the preview timer matures
     * @param void
     * @return void
     */
    void sltPreviewTimeout();

protected:

private:
    /**
     * @brief Method to set value of m_strSongArtist
     * @param strTitle - title of the active song
     * @return void
     */
    void setSongTitle(const QString &strTitle);

    /**
     * @brief Method to set value of m_strSongTitle
     * @param strArtist - artist of the active song
     * @return void
     */
    void setSongArtist(const QString &strArtist);

    /**
     * @brief Method to set value of m_strSongAlbum
     * @param strAlbum - album of the active song
     * @return void
     */
    void setSongAlbum(const QString &strAlbum);

    /**
    * @brief	This method will subscribe for all signals required by MediaAdaptor
    * @param	void
    * @return	void
    */
    void connectSignals();

    /**
     * @brief	This method will flush all the stored data for active Media device
     *           This method is called when Media device is changed for playback
     * @param	void
     * @return	void
     */
    void resetMediaData();

    /**
     * @brief Method to reset Now playing data
     *        This is called when a new song is played from a browse category
     * @param void
     * @return void
     */
    void resetNowPlayingData();

    /**
     * @brief	This method will flush all the stored data for device connected to USB slot
     *           This method is called when USB/IPOD is removed
     * @param	void
     * @return	void
     */
    void resetUSBSlotData();

    /**
     * @brief	This method will flush all the stored data for device connected to BT slot
     *           This method is called when BT device is disconnected
     * @param	void
     * @return	void
     */
    void resetBTSlotData();

    /**
     * @brief	This method will return text value for name of browse category selected by user for browsing
     * @param	eBrowseItem - browse item i.e. albums, artists, folders etc
     * @return	QString - Text value for name of the category
     */
    QString getBrowseCategoryName(CMediaEnum::EMediaBrowseItem eBrowseItem);    

    /**
     * @brief Method to set Media screen title text based on current active Ent. source
     * @param void
     * @return void
     */
    void setMediaScreenTitle();

    /**
     * @brief Callback method to request data for pending pages.
     *        This method shall be called from windowing helper class to fetch data for a page.
     * @param objPageData - @see SPageData
     * @return void
     */
    void requestBrowseDataForPendingPage(SPageData objPageData);

    /**
     * @brief Callback method to request data for pending pages.
     *        This method shall be called from windowing helper class to fetch data for a page.
     * @param objPageData - @see SPageData
     * @return void
     */
    void requestNowPlayingDataForPendingPage(SPageData objPageData);

    /**
     * @brief setFailedRequestStartIndex - Method to set the value of m_iRequestFailedStartIndex
     * @param iStartIndex - value to be set as m_iRequestFailedStartIndex
     * @return void
     */
    inline void setFailedRequestStartIndex(int iStartIndex) {m_iRequestFailedStartIndex = iStartIndex;}

    /**
     * @brief CMediaAdaptor class Constructor
     * @param pParent
     * @return void
     */
    explicit CMediaAdaptor(QObject *pParent = nullptr);

    /**
     * Instance of class CMediaAdaptor
     */
    static CMediaAdaptor* m_pMediaAdaptor;

    /**
     * value to store a bool value
     * True - if NowPlaying Data is available
     * False - if NowPlaying Data is not available
     */
    bool m_bIsNowPlayingDataAvail;

    /**
     * Var to store a browse data state
     **/
    CMediaEnum::EMediaBrowseDataState m_eMediaBrowseDataState;

    /**
     * This will hold the actual metdata type of the media playing currently
     * This is needed in case of some ypes where main screen UI elements are to be shown/hidden
     * for e.g. in case of iTunes Radio, repeat/shuffle buttons should be disabled
     */
    CMediaEnum::EMediaBrowseItem m_eNowPlayingMetadataType;

    /**
     * This will hold the currently Playing song's Title
     */
    QString m_strSongTitle;

    /**
     * This will hold the currently Playing song's Artist
     */
    QString m_strSongArtist;

    /**
     * This will hold the currently Playing song's Album
     */
    QString m_strSongAlbum;

    /**
     * This will hold the current play state of the active song
     */
    CMediaEnum::EMediaPlayStates m_ePlayState;

    /**
     * This will hold the shuffle mode of the active track session
     */
    CMediaEnum::EMediaShuffleMode m_eShuffleMode;

    /**
     * This will hold the repeat mode of the active track session
     */
    CMediaEnum::EMediaRepeatMode m_eRepeatMode;

    /**
     * This will hold the playTime of the current active track
     * This value shall be primarily accessed by the progressbar in the Media main screen
     */
    uint64_t m_uiPlayTime;

    /**
     * This will hold the totalDuration of the current active track
     * This value shall be primarily accessed by the progressbar in the Media main screen
     */
    uint64_t m_uiTotalDuration;

    /**
     * This will hold the formatted playTime of the current active track in HH:MM:SS format
     * This value shall be primarily used to display the play time of active song in the Media main screen
     */
    QString m_strFormattedPlayTime;

    /**
     * This will hold the formatted totalDuration of the current active track in HH:MM:SS format
     * This value shall be primarily used to display the total duration of active song in the Media main screen
     */
    QString m_strFormattedTotalDuration;

    /**
     * This will hold the path to currently Playing song's AlbumArt image
     * albumArt can only be tested on target, it shall not work in simulation
     * Simulation shall always display default album art
     */
    QString m_strAlbumArtPath;

    /**
     * This will hold a boolean value indicating if default album art is displayed
     * By virtue of this property we can choose not to rotate the default album art
     * As per requirement, default album art should not be rotated
     */
    bool m_bDefaultAlbumArtDisplayed;

    /**
     * This will hold a boolean value indicating if current active track is playing or not
     * Value shall be true if the playState is 'Playing'
     * Value shall be false if the plaState is 'Paused'
     * Value shall be unchanged for playStates like 'FastReverse' and 'FastForward'
     */
    bool m_bIsMediaAudioPlaying;

    /**
     * This will hold the active Media Source that shall be displayed as Media Main screen Title
     */
    QString m_strActiveMediaSrcTitle;

    /**
     * This will hold the title for Browse category screen.
     * Title shall be set dynamically based on the user's request to browse specific item.
     */
    QString m_strBrowseCategoryScreenTitle;

    /**
     * This will hold the previous history title for Browse category screen.
     * Title shall be set dynamically based on the user's request to browse specific item.
     */
    QString m_strPrevBrowseCategoryScreenTitle;

    /**
     * This will hold the text value of item that is clicked for browsing by user
     * This value shall be (for now) used when user selects playlist
     * This is hardcoding from HMI since service has lot of efforts to resolve this issue
     * Sometimes service does not sends title in case of playlist and hence this workaround in HMI
     */
    QString m_strItemSelectedText;

    /**
     * This will hold the text to be displayed in empty category popup
     */
    QString m_strEmptyCategoryPopupText;

    /**
     * This will hold the text to be displayed in USB device error popup
     */
    QString m_strUSBDeviceErrorPopupText;

    /**
     * This will hold the boolean value to indicate of browsing is allowed for current active Media device
     */
    bool m_bReadyToBrowse;

    //Framework Reference
    CFramework& mfw;
    // Media Resource
    IMediaResource* m_pMediaResource;

    /**
     * @brief: m_listImageData-  Image source path is saved in this list
     **/
    QList<QString> m_listImageData;

    // Media browse data list will be stored here
    QVariantList m_listBrowseData;

    /**
     * @brief m_iTotalImageCount: To store the total image count
     */
    int m_iTotalImageCount;

    /**
     * @brief m_iCurrentTrackIndex: To store the current playing track index
     * This shall be updated whenever nowPlaying is received
     */
    int m_iCurrentTrackIndex;

    //To store the current playing song index
    int m_iCurrentPreviewIndex;

    //To store the current folder count of audio files for USB source
    int m_iUSBFolderCount;

    //This holds a bool value that tells if Play/Pause feature is supported or not in current BT device connected for Media
    bool m_bIsPlayPauseSupported;

    //This holds a bool value that tells if Next/Prev feature is supported or not in current BT device connected for Media
    bool m_bIsNextPrevSupported;

    //This holds a bool value that tells if fast Fwd/Rwd feature is supported or not in current BT device connected for Media
    bool m_bIsFwdRwdSupported;

    //This holds a bool value that tells if Repeat feature is supported or not in current BT device connected for Media
    bool m_bIsRepeatSupported;

    //This holds a bool value that tells if Random feature is supported or not in current BT device connected for Media
    bool m_bIsRandomSupported;

    //This holds a bool value that tells if Browsing feature is supported or not in current BT device connected for Media
    bool m_bIsBrowseSupported;

    //This holds a bool value that tells if it is folder mode play back for USB device play back
    bool m_bIsFolderModePlayBack;

    //This holds a bool value that tells if playtime is received from Media service
    bool m_bShowPlaytime;

    //This holds a bool value that tells if it prev/next song preview is to be displayed
    CMediaEnum::EMediaPreviewMode m_ePreviewMode;

    //This holds a current display state of Media
    CMediaEnum::EMediaDisplayState m_eMediaDisplayState;

    //This holds a current operation state of Media
    CMediaEnum::EMediaOperationState m_eMediaOperationState;

    //To store the content type for USB
    CMediaEnum::EMediaContentType m_eUSBContentType;

    //To store the playback mode for USB
    CMediaEnum::EMediaUSBPlayBackMode m_eMediaUSBPlayBackMode;

    //To store the sync state for device connected to USB slot
    CMediaEnum::EMediaSyncState m_eUSBSyncState;

    //To store the sync state for device connected to BT slot
    CMediaEnum::EMediaSyncState m_eBTSyncState;

    //Pointer of class CMediaBrowseCategoryListModel
    CMediaBrowseCategoryListModel* m_pBrowseCategoryList;

    //Pointer of class CMediaBrowseListModel
    CMediaBrowseListModel* m_pBrowseList;

    /* Instance of CSetupListModel class, stores data of aux in gain model */
    CSetupListModel* m_pSetupAUXGainListModel;

    /*Instance of Imge data model used to store the list of images*/
    CMediaBrowseListModel* m_pImageListModel;

    //To store the available categories for device connected to USB slot
    QList<int> m_listUSBAvailableCategories;

    //To store the available categories for device connected to BT slot
    QList<int> m_listBTAvailableCategories;

    //To store the available categories for device connected to BT slot
    QList<SBrowseCategoryData> m_listNowPlaying;

    //To store the bit rate info received from Media service
    QString m_strBitRate;

    //To store the sampling rate info received from Media service
    QString m_strSamplingRate;

    //To store the song name to be displayed in preview
    QString m_strSongPreviewText;

    /** Screen timeout timer */
    QTimer m_objPreviewTimer;

    //To store the active audio entertainment source
    CAudioEnums::EAudioEntertainmentSrcs m_eActiveMediaSrc;

    //Windowing helper object to perform task related to windowing
    CWindowingHelper m_objWindowingHelperForBrowse;

    //Windowing helper object to perform task related to windowing specific to getting preview items
    CWindowingHelper m_objWindowingHelperForNowPlayingList;

    //To store current Index of list for which data has been requested
    int m_iCurrentBrowseIndex;

    //To store current Index of NowPlaying list for which data has been requested
    int m_iCurrentNowPlayingIndex;

    //Constant value of Windowing Buffer size
    const int WINDOW_BUFFER_SIZE;

    //This holds a bool value that tells if user confirmed to view Video/Images in USB which has no songs
    bool m_bNoSongsUSBAccepted;

    /** To store the video codec value */
    QString m_strVideoCodec;

    /** To store the video resolution: video height * video width */
    QString m_strVideoResolution;

    /** To store the video frame rate */
    QString m_strVideoFrameRate;

    /**
     * @brief m_strMediaFormat: to store the Media format.
     */
    QString m_strMediaFormat;

    /** To store the audio codec value in the video */
    QString m_strAudioCodec;

    /** To store the audio sampling rate in the video*/
    QString m_strAudioSamplingRate;

    //This holds the value of BT Metadata availabilty status
    CMediaEnum::EMediaMetadataAvailabilityStatus m_eBTMetadataAvailabilityStatus;

    //This holds the value of BT Metadata availabilty status
    CMediaEnum::EMediaBrowseItem m_eMediaBrowseItemSelected;

    //This holds the value of VR browse request status
    CMediaEnum::EMediaVRBrowseState m_eMediaVRBrowseState;

    /*
     * This holds the value of category being browsed
     * This value shall be updated when user selects any category for browsing
     * This value shall be cleared when user exits browsing
     * */
    CMediaEnum::EMediaBrowseItem m_eMediaCategoryBrowsed;

//    /**
//     * @brief m_strImageTitle: This holds the current Image title as per the given index
//     */
//    QString m_strImageTitle;

    /**
     * @brief m_iCurrentImageIndex: This holds the current Image index.
     */
    int m_iCurrentImageIndex;

    //This holds the value of start index of page for which empty list was received from Media service while Browsing. Default value is -1.
    int m_iRequestFailedStartIndex;

    /**
     * @brief m_strBreadcrumbPath - String that would save current BreadcrumbPath received from Media service
     */
    QString m_strBreadcrumbPath;

};

#endif // CMEDIAADAPTOR_H

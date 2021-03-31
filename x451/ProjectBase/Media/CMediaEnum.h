/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaEnum.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CMediaEnum    Class that would contain all the Enums related to Media
*               that would also be registered as a QML type so that these could be used in QML too
*/
#ifndef CMEDIAENUM_H
#define CMEDIAENUM_H
#include <QObject>
#include <QtQml>

/**
 * @class CMediaEnum
 * @brief Class that would contain all the Enums related to Media
 *        that would also be registered as a QML type so that these could be used in QML too
 */
class CMediaEnum : public QObject{

    Q_OBJECT
public:

    //TODO: All enum names to be updated for sake of consistency in naming convention

    /**
     * @enum EMediaPlayStates
     * @brief Enum for play states of an active track
     */
    enum EMediaPlayStates
    {
        PLAYSTATE_PLAYING = 0,
        PLAYSTATE_PAUSED = 1,
        PLAYSTATE_STOPPED = 2,
        PLAYSTATE_FASTFORWARD = 3,
        PLAYSTATE_FASTREVERSE = 4,
        PLAYSTATE_ERROR = 5,
        PLAYSTATE_UNKNOWN = 6
    };
    Q_ENUM(EMediaPlayStates)

    /**
     * @enum EMediaShuffleMode
     * @brief Enum for shuffleMode of track session
     */
    enum EMediaShuffleMode
    {
        SHUFFLEMODE_ALL = 1,
        SHUFFLEMODE_OFF = 2,
        SHUFFLEMODE_UNKNOWN = 64,
    };
    Q_ENUM(EMediaShuffleMode)

    /**
     * @enum EMediaRepeatMode
     * @brief Enum for repeat mode of track session
     */
    enum EMediaRepeatMode
    {
        REPEATMODE_ALL = 1,
        REPEATMODE_OFF = 2,
        REPEATMODE_SONG = 4,
        REPEATMODE_FOLDER = 8,
        REPEAT_UNKNOWN = 128,
    };
    Q_ENUM(EMediaRepeatMode)

    /**
     * @enum EMediaType
     * @brief Enum for current Media Type
     */
    enum EMediaType
    {
        MEDIATYPE_UNKNOWN = 0,
        MEDIATYPE_SONGS = 1,
        MEDIATYPE_VIDEOS = 2,
        MEDIATYPE_IMAGES = 3
    };
    Q_ENUM(EMediaType)

    /**
     * @enum EMediaContentType
     * @brief Enum for Media Content Type - Tells the content types of current media device
     */
    enum EMediaContentType
    {
        CONTENTTYPE_U = 0,  //Unknown
        CONTENTTYPE_E = 1,  //Empty Device
        CONTENTTYPE_S = 2,  //Device with only songs
        CONTENTTYPE_V = 3,  //Device with only videos
        CONTENTTYPE_I = 4,  //Device with only Images
        CONTENTTYPE_SV = 5, //Device with songs and videos
        CONTENTTYPE_SI = 6, //Device with songs and images
        CONTENTTYPE_VI = 7, //Device with videos and images
        CONTENTTYPE_SVI = 8 //Device with songs, videos and images
    };
    Q_ENUM(EMediaContentType)

    /**
     * @enum EMediaBrowseLevel
     * @brief Enum for current Media Browse Level
     */
    enum EMediaBrowseLevel
    {
        BROWSELEVEL_ROOT = 1,
        BROWSELEVEL_CATEGORY = 2,
        BROWSELEVEL_SUBCATEGORY = 3,
    };
    Q_ENUM(EMediaBrowseLevel)

    /**
     * @enum EMediaBrowseItem
     * @brief Enum for current Media Browse Item
     */
    enum EMediaBrowseItem
    {
        BROWSEITEM_UNKNOWN          = -1,
        BROWSEITEM_FOLDERS          = 0,
        BROWSEITEM_SONGS            = 1,
        BROWSEITEM_ALBUMS           = 2,
        BROWSEITEM_ARTISTS          = 3,
        BROWSEITEM_GENRE            = 4,
        BROWSEITEM_PLAYLISTS        = 5,
        BROWSEITEM_PICTURE          = 6,
        BROWSEITEM_VIDEOS           = 7,
        BROWSEITEM_ITUNES_RADIO     = 8,
        BROWSEITEM_AUDIOBOOK        = 9,
        BROWSEITEM_PODCAST          = 10,
        BROWSEITEM_EPISODE          = 11,
        BROWSEITEM_PLAYALL          = 12,
        BROWSEITEM_END              = 13
    };
    Q_ENUM(EMediaBrowseItem)

    /**
     * @enum EMediaSyncState
     * @brief Enum for sync states of Media devices connected to USB and BT slot
     */
    enum EMediaSyncState
    {
        SYNC_STATE_UNKNOWN = 0,
        SYNC_STATE_FIRST_FILE = 1,
        SYNC_STATE_FILE_PASS = 2,
        SYNC_STATE_METADATA_PASS = 3,
        SYNC_STATE_PLAYLIST_PASS = 4,
        SYNC_STATE_THUMBNAIL_PASS = 5,
        SYNC_STATE_GRACENOTE_PASS = 6
    };
    Q_ENUM(EMediaSyncState)

    /**
     * @enum EUSBDeviceError
     * @brief Enum for errors received from Media service for device connected to USB slot
     */
    enum EUSBDeviceError
    {
        USB_DEVICE_NO_ERROR = 0,
        USB_DEVICE_UNSUPPORTED = 1,
        USB_DEVICE_HUB_UNSUPPORTED = 2,
        USB_DEVICE_NO_RESPONSE = 3,
        USB_DEVICE_ERROR_UNKNOWN = 4
    };
    Q_ENUM(EUSBDeviceError)

    /**
     * @enum EMediaUSBPlayBackMode
     * @brief Enum for current Media playback mode
     */
    enum EMediaUSBPlayBackMode
    {
        USB_PLAYBACK_FOLDER_MODE = 0,
        USB_PLAYBACK_TRACK_MODE = 1,
        USB_PLAYBACK_UNKNOWN_MODE = 2,
    };
    Q_ENUM(EMediaUSBPlayBackMode)

    /**
     * @enum EMediaPreviewMode
     * @brief Enum for current Media preview mode
     */
    enum EMediaPreviewMode
    {
        PREVIEW_MODE_NONE = 0,
        PREVIEW_MODE_NEXT = 1,
        PREVIEW_MODE_PREV = 2,
    };
    Q_ENUM(EMediaPreviewMode)

    /**
     * @enum EMediaDisplayState
     * @brief Enum for current Media display state
     */
    enum EMediaDisplayState
    {
        MEDIA_DISPLAYSTATE_NONE = 0,
        MEDIA_DISPLAYSTATE_MAIN,
        MEDIA_DISPLAYSTATE_LOADING,
        MEDIA_DISPLAYSTATE_BROWSE,
        MEDIA_DISPLAYSTATE_BROWSE_CATEGORY,
        MEDIA_DISPLAYSTATE_PICTURES,
        MEDIA_DISPLAYSTATE_AUX,
    };
    Q_ENUM(EMediaDisplayState)

    /**
     * @enum EMediaOperationState
     * @brief Enum for current Media operation state
     */
    enum EMediaOperationState
    {
        MEDIA_OPERATIONSTATE_NONE = 0,
        MEDIA_OPERATIONSTATE_AUDIO,
        MEDIA_OPERATIONSTATE_VIDEO,
        MEDIA_OPERATIONSTATE_NOSONGS,
        MEDIA_OPERATIONSTATE_CORRUPTVIDEO,
    };
    Q_ENUM(EMediaOperationState)

    /**
     * @enum EMediaMetadataAvailabilityStatus
     * @brief Enum for BT Metadata Availability status
     */
    enum EMediaMetadataAvailabilityStatus
    {
        MEDIA_METADATA_STATUS_DEFAULT = 0,
        MEDIA_METADATA_STATUS_NOT_AVAILABLE = 1,
        MEDIA_METADATA_STATUS_AVAILABLE = 2
    };
    Q_ENUM(EMediaMetadataAvailabilityStatus)

    /**
     * @enum EButtonStates
     * @brief Enum for Media Buttons States
     */
    enum EButtonStates{
        EN_BUTTON_STATE_UNKNOWN = 0,
        EN_BUTTON_STATE_PRESSED,
        EN_BUTTON_STATE_LONG_PRESSED,
        EN_BUTTON_STATE_RELEASED,
        EN_BUTTON_STATE_LONG_RELEASED
    };
    Q_ENUM(EButtonStates)

    /**
     * @enum EMediaVRBrowseState
     * @brief Enum for current Media VR browse state
     */
    enum EMediaVRBrowseState
    {
        VR_BROWSE_STATE_NONE        = 0,
        VR_BROWSE_STATE_PROCESSING     ,
        VR_BROWSE_STATE_FAILED         ,
        VR_BROWSE_STATE_SUCCESS        ,
    };
    Q_ENUM(EMediaVRBrowseState)

    /**
     * @enum EMediaBrowseDataState
     * @brief Enum for current Media browse data state
     */
    enum EMediaBrowseDataState
    {
        BROWSEDATA_STATE_NONE         = 0,
        BROWSEDATA_STATE_FETCHING        ,
        BROWSEDATA_STATE_AVAILABLE       ,
        BROWSEDATA_STATE_EMPTY           ,
    };
    Q_ENUM(EMediaBrowseDataState)

    /**
     * @brief Method to register CMediaEnum as a QML type
     * @param void
     * @return void
     */
    static void registerMediaEnumsToQML()
    {
        qmlRegisterType<CMediaEnum>("com.harman.qml.mediaenum",1,0,"MediaEnum");
    }
};
Q_DECLARE_METATYPE(CMediaEnum::EMediaPlayStates)
Q_DECLARE_METATYPE(CMediaEnum::EMediaShuffleMode)
Q_DECLARE_METATYPE(CMediaEnum::EMediaRepeatMode)
Q_DECLARE_METATYPE(CMediaEnum::EMediaType)
Q_DECLARE_METATYPE(CMediaEnum::EMediaContentType)
Q_DECLARE_METATYPE(CMediaEnum::EMediaBrowseLevel)
Q_DECLARE_METATYPE(CMediaEnum::EMediaBrowseItem)
Q_DECLARE_METATYPE(CMediaEnum::EMediaSyncState)
Q_DECLARE_METATYPE(CMediaEnum::EMediaUSBPlayBackMode)
Q_DECLARE_METATYPE(CMediaEnum::EMediaPreviewMode)
Q_DECLARE_METATYPE(CMediaEnum::EMediaDisplayState)
Q_DECLARE_METATYPE(CMediaEnum::EMediaOperationState)
Q_DECLARE_METATYPE(CMediaEnum::EButtonStates)
Q_DECLARE_METATYPE(CMediaEnum::EMediaBrowseDataState)

#endif // CMEDIAENUM_H

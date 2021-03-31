/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaEventProvider.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CMediaEventProvider, Class to send signals to Media Application layer on Media Resource events
*/
#ifndef CMEDIAEVENTPROVIDER_H
#define CMEDIAEVENTPROVIDER_H

#include <QObject>
#include <string>
using namespace std;

/**
 * @class CMediaEventProvider
 * @brief Class to send signals to Media Application layer on Media Resource events
 */
class CMediaEventProvider : public QObject
{
    Q_OBJECT
public:
    CMediaEventProvider(QObject* parent = 0);
    ~CMediaEventProvider();

signals:
    /**
     * @brief Signal to notify CMediaEventHandler that NowPlaying Data has been updated
     * @param void
     * @return void
     */
    void sigNowPlayingDataUpdateEvent();

    /**
     * @brief Signal to notify CMediaEventHandler that track session has been updated
     * @param void
     * @return void
     */
    void sigTrackSessionUpdateEvent();

    /**
     * @brief Signal to notify CMediaEventHandler that Play State for current track has been updated
     * @param iPlayState - play state of the active song
     * @return void
     */
    void sigPlayBackStateUpdateEvent(int iPlayState);

    /**
     *
     * @brief Signal to notify CMediaEventHandler that AlbumArt data has been updated
     * @param string carrying the album art path
     * @return void
     */
    void sigAlbumArtDataUpdateEvent(string);

    /**
     * @brief Signal to notify CMediaEventHandler that shuffle mode has been updated
     * @param int - shuffle mode of the active song
     * @return void
     * shuffle mode should be dispatched as int param
     */
    void sigShuffleModeUpdateEvent(int);

    /**
     * @brief Signal to notify CMediaEventHandler that repeat mode has been updated
     * @param int - repeat mode of the active song
     * @return void
     */
    void sigRepeatModeUpdateEvent(int);

    /**
     * @brief Signal to notify CMediaEventHandler that song playTime has been updated
     * @param uint64_t - playTime on the song
     * @return void
     * playTime should be dispatched as uint64_t param
     */
    void sigPlayTimeUpdateEvent(uint64_t);

    /**
     * @brief Signal to notify CMediaEventHandler that total duration of the song has been updated
     * @param uint64_t - totalDuration of the active song
     * @return void
     */
    void sigTotalDurationUpdateEvent(uint64_t);

    /**
     * @brief Signal to notify CMediaEventHandler that track number of the song has been updated
     * @param uint64_t - Track number of the active song
     * @return void
     */
    void sigTrackNumberUpdateEvent(uint64_t);

    /**
     * Signal to notify CMediaEventHandler that image data has been updated
     */
    void sigImageDataPathUpdateEvent();

    /**
     * Signal to notify CMediaEventHandler that browse data has been updated
     */
    void sigBrowseDataUpdateEvent(int);

    /**
     * Signal to notify CMediaEventHandler that now playing data has been updated
     */
    void sigNowPlayingListUpdateEvent();

    /**
     * Signal to notify CMediaEventHandler that sync state has been updated
     */
    void sigSyncStateUpdateEvent();

    /**
     * @brief Signal to notify CMediaEventHandler that content type has been updated
     * @param int - content type of USB
     * @return void
     */
    void sigContentTypeUpdateEvent(int);

    /**
     * @brief Signal to notify CMediaEventHandler that USB play back mode has been updated
     * @param int - play back mode of USB
     * @return void
     */
    void sigUSBPlayBackModeEvent(int);

    /**
     * Signal to notify CMediaEventHandler that root level browse is to be set in HMI
     */
    void sigSetRootLevelBrowseEvent();

    /**
     * Signal to notify CMediaEventHandler that corrupt video is encountered
     */
    void sigCorruptVideoEvent();

    /**
     * @brief Signal to notify CMediaEventHandler about USB device error
     * @param int - value specifying the device error
     * @return void
     */
    void sigUSBDeviceErrorEvent(int);

    /**
     * @brief Signal to notify CMediaEventHandler that breadcrumb path has been updated
     * @param string - breadcrumb path
     * @return void
     */
    void sigBreadrcrumbPathUpdateEvent(string);

    /**
     * Signal to notify CMediaEventHandler that categories map for device connected to USB slot is updated
     */
    void sigUSBCategoriesUpdateEvent();

    /**
     * Signal to notify CMediaEventHandler that categories map for device connected to BT slot is updated
     */
    void sigBTCategoriesUpdateEvent();

    /**
     * Signal to notify CMediaEventHandler that requested browse item is empty
     */
    void sigBrowseItemEmpty();

    /**
     * @brief to notify CMediaEventHandler that remotePlayerCapabilities have been updated
     * @param void
     * @return void
     */
    void sigRemotePlayerCapabilitiesUpdateEvent();

    /**
     * @brief Signal to notify CMediaEventHandler that Audio Bit Rate data has been updated
     * @param string carrying the bit rate value
     * @return void
     */
    void sigBitRateUpdateEvent(string);

    /**
     *
     * @brief Signal to notify CMediaEventHandler that Audio Sampling Rate data has been updated
     * @param string carrying the sampling rate value
     * @return void
     */
    void sigSamplingRateUpdateEvent(string);

    /**
     * @brief Signal to notify CMediaEventHandler that requested Browse Category list size has been updated
     * @param int - size of browse category list
     * @return void
     */
    void sigRequestedBrowseListSizeUpdateEvent(int);

    /**
     * @brief Signal to notify CMediaEventHandler that requested now playing list size has been updated
     * @param int - size of now playing list
     * @return void
     */
    void sigNowPlayingListSizeUpdateEvent(int);

    /**
     *
     * @brief Signal to notify CMediaEventHandler that Video test mode parameter data has been updated
     * @param void
     * @return void
     */
    void sigVideoTestModeParametersUpdateEvent();

     /** @brief Signal to notify CMediaEventHandler that BT metadata availability staus has been updated
     * @param iMetaDataAvailablityStatus - BT metadata Availability staus
     * @return void
     */
    void sigBTMetaDataAvailabilityStatusUpdateEvent(int);

    /**
     * @brief Signal to notify CMediaEventHandler that Now Playing pointer Index has been updated
     * @param iPrevIndex: Index of item previously highlighted with now playing pointer
     * @param iNewIndex: Index of item to be highlighted with now playing pointer
     * @return void
     */
    void sigUpdateNowPlayingPointer(int,int);

    /**
     * @brief Signal to notify CMediaEventHandler that an empty list is received for startIndex
     * @param iStartIndex - start Index for which empty list was received
     * @return void
     */
    void sigEmptyListReceived(int);

    /**
     * @brief sigBrowseSessionCreated: To notify the browse session creation for the current active source
     * @param void
     * @return void
     */
    void sigBrowseSessionCreated();


public:
    //Functions that would be used by the Resource Layer to indirectly emit signals to the upper layers

    /**
     * @brief Method called from CMediaResourceImpl to emit sigTrackSessionUpdateEvent
     * @param void
     * @return void
     */
    void trackSessionUpdate();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigNowPlayingDataUpdateEvent
     * @param void
     * @return void
     */
    void nowPlayingDataUpdate();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigPlayBackStateUpdateEvent
     * @param iPlayState - play state of the active song
     * @return void
     */
    void playBackStateUpdated(int iPlayState);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigAlbumArtDataUpdateEvent
     * @param strAlbumArtPath - path to album art
     * @return void
     */
    void albumArtUpdate(string strAlbumArtPath);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigAlbumArtDataUpdateEvent
     * @param iShuffleMode - shuffle mode received from service
     * @return void
     */
    void shuffleModeUpdated(int iShuffleMode);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigRepeatModeUpdateEven);
     * @param iRepeatMode - repeat mode received from service
     * @return void
     */
    void repeatModeUpdated(int iRepeatMode);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigPlayTimeUpdateEvent
     * @param uiPlayTime - playTime received from service
     * @return void
     */
    void playTimeUpdated(uint64_t uiPlayTime);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigTotalDurationUpdateEvent
     * @param uiTotalDuration - total duration received from service
     * @return void
     */
    void totalDurationUpdated(uint64_t uiTotalDuration);

    /**
     * @brief trackNumberUpdated - Method called from CMediaResourceImpl to emit sigTrackNumberUpdateEvent
     * @param uiTrackNumber - tarck number received from service
     * @return void
     */
    void trackNumberUpdated(uint64_t uiTrackNumber);    

    /**
     * @brief Method called from CMediaResourceImpl to emit sigImageDataPathUpdateEvent
     * @param void
     * @return void
     */
    void updateImageData();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigBrowseDataUpdateEvent
     * @param iStartIndex - start Index for which data is received from Media Service
     * @return void
     */
    void updateBrowseData(int iStartIndex);

    /**
     * @brief updateNowPlayingList - Method called from CMediaResourceImpl to emit sigNowPlayingListUpdateEvent
     * @param void
     * @return void
     */
    void updateNowPlayingList();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigSyncStateUpdateEvent
     * @param void
     * @return void
     */
    void updateSyncState();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigContentTypeUpdateEvent
     * @param iContentType - content type of USB
     * @return void
     */
    void updateContentType(int iContentType);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigUSBPlayBackModeEvent
     * @param iUSBPlayBackModeEvent - play back mode of USB
     * @return void
     */
    void updateUSBPlayBackMode(int iUSBPlayBackModeEvent);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigUSBCategoriesUpdateEvent()
     * @param void
     * @return void
     */
    void updateUSBCategories();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigBTCategoriesUpdateEvent()
     * @param void
     * @return void
     */
    void updateBTCategories();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigSetRootLevelBrowseEvent();
     * @param void
     * @return void
     */
    void setRootLevelBrowse();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigCorruptVideoEvent();
     * @param void
     * @return void
     */
    void corruptVideoAccessed();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigUSBDeviceErrorEvent()
     * @param int - value specifying the USB device error
     * @return void
     */
    void updateUSBDeviceError(int iUSBDeviceError);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigBreadrcrumbPathUpdateEvent();
     * @param iContentType - content type of USB
     * @return void
     */
    void updateBreadcrumbPath(const string& strBreadcrumbPath);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigBrowseItemEmpty()
     * @param void
     * @return void
     */
    void updateBrowseItemEmpty();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigRemotePlayerCapabilitiesUpdateEvent()
     * @param void
     * @return void
     */
    void updateRemotePlayerCapabilities();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigBitRateUpdateEvent
     * @param strBitRate - Audio bit rate
     * @return void
     */
    void updateBitRate(string strBitRate);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigSamplingRateUpdateEvent
     * @param strSamplingRate - Audio sampling rate
     * @return void
     */
    void updateSamplingRate(string strSamplingRate);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigRequestedBrowseListSizeUpdateEvent
     * @param iBrowseCategoryListSize - size of browse category list
     * @return void
     */
    void updateRequestedBrowseListSize(int iBrowseCategoryListSize);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigNowPlayingListSizeUpdateEvent
     * @param iNowPlayingListSize - size of preview list
     * @return void
     */
    void updateNowPlayingListSize(int iNowPlayingListSize);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigVideoTestModeParametersUpdateEvent()
     * @param void
     * @return void
     */
    void updateVideoTestModeParameters();

    /**
     * @brief Method called from CMediaResourceImpl to emit sigBTMetaDataAvailabilityStatusUpdateEvent
     * @param iMetaDataAvailablityStatus - BT metadata Availability staus
     * @return void
     */
    void updateBTMetaDataAvailabilityStatus(int iMetaDataAvailablityStatus);

    /**
     * @brief Method called from CMediaResourceImpl to emit sigUpdateNowPlayingPointer
     * @param iPrevIndex: Index of item previously highlighted with now playing pointer
     * @param iNewIndex: Index of item to be highlighted with now playing pointer
     * @return void
     */
    void updateNowPlayingPointer(int iPrevIndex,int iNewIndex);

    /**
     * @brief emptyListReceived - Method called from CMediaResourceImpl to emit sigEmptyListReceived
     * @param iStartIndex - start Index for which empty list was received
     * @return void
     */
    void emptyListReceived(int iStartIndex);

    /**
     * @brief updateBrowseSessionCreation: To intimate the upper layers regarding the browse session creation from here on browse activities can be triggered.
     * @param void
     * @return void
     */
    void updateBrowseSessionCreation();
};

#endif // CMEDIAEVENTPROVIDER_H

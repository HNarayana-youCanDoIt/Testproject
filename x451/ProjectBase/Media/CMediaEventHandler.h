/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaEventHandler.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* @class        CMediaEventHandler: Class has the slots for all the Signals sent by CMediaEventHandler
*                                   which informs Media Adaptor about Media Resource Events
*/
#ifndef CMEDIAEVENTHANDLER_H
#define CMEDIAEVENTHANDLER_H

#include <QObject>
#include <string>
using namespace std;

/**
 * @class CMediaEventHandler
 * @brief Class has the slots for all the Signals sent by CMediaEventHandler
 *        which informs Media Adaptor about Media Resource Events
 */
class CMediaEventHandler: public QObject
{
    Q_OBJECT

public:
    CMediaEventHandler(QObject* parent = 0);
    ~CMediaEventHandler();

public slots:
    // Slots that would be invoked on the resource layer events signals
    /**
     * @brief Method to inform Media Adaptor that Now Playing Data is updated
     * @param void
     * @return void
     */
    void sltNowPlayingDataUpdate();

    /**
     * @brief Method to inform Media Adaptor that track session is updated
     * @param void
     * @return void
     */
    void sltTrackSessionUpdate();

    /**
     * @brief Method to inform Media Adaptor that Play State for current track is updated
     * @param iPlayState - New Play state of the track
     * @return void
     */
    void sltPlayBackStateUpdate(int iPlayState);

    /**
     * @brief Method to inform Media Adaptor that Album Art data is updated
     * @param strAlbumArtPath - value for album art path
     * @return void
     */
    void sltAlbumArtDataUpdate(string strAlbumArtPath);

    /**
     * @brief Method to inform Media Adaptor that shuffle mode for current track session is updated
     * @param iShuffleMode - shuffle mode of track session
     * @return void
     */
    void sltShuffleModeUpdate(int iShuffleMode);

    /**
     * @brief Method to inform Media Adaptor that repeat mode for current track session is updated
     * @param iRepeatMode - repeat mode of track session
     * @return void
     */
    void sltRepeatModeUpdate(int iRepeatMode);

    /**
     * @brief Method to inform Media Adaptor that playTime for current track is updated
     * @param uiPlayTime - playTime of current active track
     * @return void
     */
    void sltPlayTimeUpdate(uint64_t uiPlayTime);

    /**
     * @brief Method to inform Media Adaptor that total duration for current track is updated
     * @param uiTotalDuration - totalDuration of current active track
     * @return void
     */
    void sltTotalDuarationUpdate(uint64_t uiTotalDuration);

    /**
     * @brief sltTrackNumberUpdate - Method to inform Media Adaptor that track number for current track is updated
     * @param uiTrackNumber - track number of current active track
     * @return void
     */
    void sltTrackNumberUpdate(uint64_t uiTrackNumber);

    /**
     * @brief Method to inform Media Adaptor that image data is received
     * @param void
     * @return void
     */
    void sltImageDataPathUpdate();

    /**
     * @brief Method to inform Media Adaptor that browse data is received
     * @param iStartIndex - start Index for which data is received from Media Service
     * @return void
     */
    void sltBrowseDataUpdate(int iStartIndex);

    /**
     * @brief sltNowPlayingListUpdate - Method to inform Media Adaptor that now playing data is received
     * @param void
     * @return void
     */
    void sltNowPlayingListUpdate();

    /**
     * @brief Method to inform Media Adaptor that updated sync state is received
     * @param void
     * @return void
     */
    void sltSyncStateUpdate();

    /**
     * @brief Method to inform Media Adaptor that updated content type data is received
     * @param iContentType - type of content for USB
     * @return void
     */
    void sltContentTypeUpdate(int iContentType);

    /**
     * @brief Method to inform Media Adaptor that updated play back mode data is received
     * @param iMediaUSBPlayBackMode - play back mode for USB
     * @return void
     */
    void sltUSBPlayBackModeUpdate(int iMediaUSBPlayBackMode);

    /**
     * @brief Method to inform Media Adaptor that updated catgeories for device connected to USB slot are received
     * @param void
     * @return void
     */
    void sltUSBCategoriesUpdate();

    /**
     * @brief Method to inform Media Adaptor that updated catgeories for device connected to BT slot are received
     * @param void
     * @return void
     */
    void sltBTCategoriesUpdate();

    /**
     * @brief Method to inform Media Adaptor to set root level of browse on HMI
     * @param void
     * @return void
     */
    void sltSetRootLevelBrowse();

    /**
     * @brief Method to inform Media Adaptor that corrupt video is encountered
     * @param void
     * @return void
     */
    void sltCorruptVideoAccessed();

    /**
     * @brief Method to inform Media Adaptor to about error of device connected to USB slot
     * @param int - value specifying the USB device error
     * @return void
     */
    void sltUSBDeviceError(int iUSBDeviceError);

    /**
     * @brief Method to inform Media Adaptor that updated breadcrumb path is received
     * @param strBreadcrumbPath - path to browsing category
     * @return void
     */
    void sltBreadcrumbPathUpdate(const string& strBreadcrumbPath);

    /**
     * @brief Method to inform Media Adaptor that requested browse item is empty
     * @param void
     * @return void
     */
    void sltBrowseItemEmpty();

    /**
     * @brief Method to inform Media Adaptor that remote player capabilities are updated
     * @param void
     * @return void
     */
    void sltRemotePlayerCapabilitiesUpdate();

    /**
     * @brief Method to inform Media Adaptor that Bit Rate data is updated
     * @param strBitRate - Audio bit rate
     * @return void
     */
    void sltBitRateUpdate(string strBitRate);

    /**
     * @brief Method to inform Media Adaptor that Sampling Rate data is updated
     * @param strSamplingRate - Audio sampling rate
     * @return void
     */
    void sltSamplingRateUpdate(string strSamplingRate);

    /**
     * @brief Method to inform Media Adaptor that that requested Browse Category list size has been updated
     *        This method shall call createBrowseList event, which would create an empty list of size iBrowseCategoryListSize
     *        And would initialize Windowing for the list.
     * @param iBrowseCategoryListSize - size of browse category list
     * @return void
     */
    void sltRequestedBrowseListSizeUpdate(int iBrowseCategoryListSize);

    /**
     * @brief Method to inform Media Adaptor that that requested now playing list size has been updated
     *        This method shall call createBrowseList event, which would create an empty list of size iNowPlayingListSize
     *        And would initialize Windowing for the list.
     * @param iNowPlayingListSize - size of now playing list
     * @return void
     */
    void sltNowPlayingListSizeUpdate(int iNowPlayingListSize);

    /**
     * @brief Method to inform Media Adaptor that video test mode data is updated
     * @param void
     * @return void
     */
    void sltVideoTestModeParametersUpdateEvent();

    /**
     * @brief Method to inform Media Adaptor that BT metadata availability staus has been updated
     * @param iMetaDataAvailablityStatus - BT metadata Availability staus
     * @return void
     */
    void sltBTMetaDataAvailabilityStatusUpdate(int iMetaDataAvailablityStatus);

    /**
     * @brief Method to inform Media Adaptor that Now Playing pointer index has been updated
     * @param iPrevIndex: Index of item previously highlighted with now playing pointer
     * @param iNewIndex: Index of item to be highlighted with now playing pointer
     * @return void
     */
    void sltNowPlayingPointerUpdateEvent(int iPrevIndex, int iNextIndex);

    /**
     * @brief sltOnEmptyListReceived - Method to inform Media Adaptor that an empty list is received for startInde
     * @param iStartIndex - start Index for which empty list was received
     * @return void
     */
    void sltOnEmptyListReceived(int iStartIndex);

    /**
     * @brief sltBrowseSessionCreated: Method intimate media adaptor regarding browse session creation.
     * @param void
     * @return void
     */
    void sltBrowseSessionCreated();

private:
    /**
     * @brief Method to connect CMediaEventProvider signals to slots
     * @param void
     * @return void
     */
    void connectSignals();
};

#endif // CMEDIAEVENTHANDLER_H

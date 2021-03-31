/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IMediaResource.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* IMediaResource, an interface for Media Resource Implementaion in HMI.
*/

#ifndef IMEDIARESOURCE_H
#define IMEDIARESOURCE_H

#include <string>
#include "implementations/CMediaResourceData.h"
//Header files related to PresCtrl
#include "v1/com/harman/mmpres/MediaPlayerProxy.hpp"
#include "v1/com/harman/mmpres/MediaManagerProxy.hpp"
#include "v1/com/harman/mmpres/MediaBrowserProxy.hpp"
#include "v1/com/harman/mmpres/MMPresTypes.hpp"
#include "v0/com/harman/mmpresPlugin/mediaPresPluginProxy.hpp"
#include "capi/CAPIClientAbstraction.hpp"
#include "CMediaEnum.h"
using namespace v1::com::harman::mmpres;
using namespace v0::com::harman::mmpresPlugin;
using namespace std;
struct MediaBrowseData;

struct SRemotePlayerSupport;
struct sVideoParameters;

/**
 * @interface IMediaResource
 * @brief     This interface provides functionality that would be implemented to interact
 *            with Media presctrl and also to provide data to Media Adaptor Layer
 */
class IMediaResource
{
public:
    virtual ~IMediaResource() {}

    /*********************************************************
             Request Methods
     *********************************************************/

    //FixMe: API names should be prefixed with 'Req' in method names

    /**
     * @brief Method to get NowPlayingData
     * @param void
     * @return NowPlayingInfo& - now playing info of the song
     */
    virtual const NowPlayingInfo &getNowPlayingData() = 0;

    /**
     * @brief Method to get SRemotePlayerSupport
     * @param void
     * @return SRemotePlayerSupport& - Reference to an object of SRemotePlayerSupport
     */
    virtual const SRemotePlayerSupport &getRemotePlayerCapabilities() = 0;

    /**
     * @brief Method to get the video test mode parameters
     * @param void
     * @return sVideoParameters - Structure conaining the video test mode parameters
     */
    virtual const sVideoParameters &getVideoTestModeParameters() = 0;

    /**
      * @brief Method to get the image data path list
      * @param void
      * @return vector<std::string> - List of image paths returned here
      */
    virtual vector<std::string> &getImageDataList() = 0;

    /**
      * @brief Method to get the Media browse data list from resource
      * @param void
      * @return vector<MediaBrowseData> - List of browse items request from Media service
      */
    virtual vector<MediaBrowseData> &getBrowseDataList() = 0;

    /**
     * @brief Method to get the content type of Media device connected at USB slot
     * @param void
     * @return int - enum value specifying the sync state
     */
    virtual int getUSBSlotSyncState() = 0;

    /**
     * @brief Method to get the content type of Media device connected at BT slot
     * @param void
     * @return int - enum value specifying the sync state
     */
    virtual int getBTSlotSyncState() = 0;

    /**
     * @brief Method to get the available browse categories of Media device connected at BT slot
     * @param void
     * @return int - enum value specifying the sync state
     */
    virtual vector<int> &getBTSlotCategories() = 0;

    /**
     * @brief Method to get the available browse categories of Media device connected at USB slot
     * @param void
     * @return int - enum value specifying the sync state
     */
    virtual vector<int> &getUSBSlotCategories() = 0;

    /**
     * @brief Method to get current Shuffle state
     * @param void
     * @return void
     */
    virtual void getShuffleState() = 0;

    /**
     * @brief Method to get current Repeat state
     * @param void
     * @return void
     */
    virtual void getRepeatState() = 0;

    /**
     * @brief Method to get current USB playback mode
     * @param void
     * @return void
     */
    virtual void getUSBPlaybackMode() = 0;

    /**
     * @brief getDeviceItemsInfoAttribute - Method to get info all available media categories for device connected to USB slot
     * @param void
     * @return void
     */
    virtual void getDeviceItemsInfoAttribute() = 0;

    /**
     * @brief Method to request the service to seek/jump the song from/to requested time
     * @param uint64_t - time in secs to which seek is requested
     * @return void
     */
    virtual void seekToTime(uint64_t uiSeekToTime) = 0;

    /**
     * @brief Method to request the service to play currently paused song
     * @param CMediaEnum::EButtonStates eButtonState - state of resume button
     * @return void
     */
    virtual void resume(CMediaEnum::EButtonStates eButtonState) = 0;

    /**
     * @brief Method to request the service to pause currently playing song
     * @param CMediaEnum::EButtonStates eButtonState - state of pause button
     * @return void
     */
    virtual void pause(CMediaEnum::EButtonStates eButtonState) = 0;

    /**
     * @brief Method to request the service to play previous song
     * @param CMediaEnum::EButtonStates eButtonState - state of prev button
     * @return void
     */
    virtual void prev(CMediaEnum::EButtonStates eButtonState) = 0;

    /**
     * @brief Method to request the service to play next song
     * @param CMediaEnum::EButtonStates eButtonState - state of next button
     * @return void
     */
    virtual void next(CMediaEnum::EButtonStates eButtonState) = 0;

    /**
     * @brief Method to request the service to fast forward active song
     * @param CMediaEnum::EButtonStates eButtonState - state of next button
     * @return void
     */
    virtual void fastForward(CMediaEnum::EButtonStates eButtonState) = 0;

    /**
     * @brief Method to request the service to fast rewind active song
     * @param CMediaEnum::EButtonStates eButtonState - state of prev button
     * @return void
     */
    virtual void fastRewind(CMediaEnum::EButtonStates eButtonState) = 0;

    /**
     * @brief Method to request the service to toggle shuffle mode for current playing category
     * @param CMediaEnum::EButtonStates eButtonState - state of shuffle button
     * @return void
     */
    virtual void toggleShuffle(CMediaEnum::EButtonStates eButtonState) = 0;

    /**
     * @brief Method to request the service to toggle repeat mode for current playing category
     * @param CMediaEnum::EButtonStates eButtonState - state of repeat button
     * @return void
     */
    virtual void toggleRepeat(CMediaEnum::EButtonStates eButtonState) = 0;

    /**
     * @brief Method  to initiate playback from next folder on USB device
     * @param void
     * @return void
     */
    virtual void nextFolder() = 0;

    /**
     * @brief Method to initiate playback from previous folder on USB device
     * @param void
     * @return void
     */
    virtual void previousFolder() = 0;

    /**
     * @brief Method to request Media service to reset itself to the root level of browse for specified category
     * @param iType - metadata type of the song
     * @param bIsVRRequest - bool to indicate if this request is for VR browsing
     * @return void
     */
    virtual void getCategoryRoot(int iType, bool bIsVRRequest = false) = 0;

    /**
     * @brief Method to request Media service to reset itself to the sub level of browse for specified category
     * @brief iQueryType is unused parameter, but required in furture for some other level of browsing
     * @param iFileID - File ID of the item selected
     * @param iMetadataType - Metadatat type of the item selected
     * @param iQueryType - query type for e.g. browse
     * @param bIsVRRequest - bool to indicate if this request is for VR browsing
     * @return void
     */
    virtual void getCategorySubLevel(int iFileID, int iMetadataType, int iQueryType, bool bIsVRRequest = false) = 0;

    /**
     * @brief Method to request Media service to play the song at specified index
     * @param iSongIndex - index of song to be played
     * @param isPreviewReq - bool to indicate if request to play song is via preview feature
     * @return void
     */
    virtual void playSong(int iSongIndex, bool isPreviewReq = false) = 0;

    /**
    * @brief Method to open the media browse session
    * @param void
    * @return void
    */
    virtual void openBrowseSession() = 0;

    /**
    * @brief Method to open the media browse session specific to preview requests
    * @param void
    * @return void
    */
    virtual void openPreviewBrowseSession() = 0;

    /**
     * @brief Method to request Media service to go to the previous level of browsing category
     * @param void
     * @return void
     */
    virtual void goToPreviousLevel() = 0;

    /**
     * @brief Method to request Media service to go to the nowPlaying level of browsing category
     * @param void
     * @return void
     */
    virtual void goToNowPlayingLevel() = 0;

    /**
     * @brief Method to set m_iActiveEntSource. This method is called from MediaAdaptor
     * @param iActiveEntSourceId - int value of active Ent. source
     * @return void
     */
    virtual void setActiveEntSource(int iActiveEntSourceId) = 0;

    /**
     * @brief Request method to fetch items
     * @param iStartIndex - index from which data should be fetched
     * @param iCount - Total number items to be fetched
     * @param isPreviewReq - bool value that indicates if fetchItems is called for NowPlaying Preview list or not
     * @return void
     */
    virtual void fetchItems(uint iStartIndex,uint iCount, bool isPreviewReq = false) = 0;

    /**
     * @brief updateRvcState provide media pres plugin with the latest reverse gear status
     * @param bRvcStatus, current reverse gear status (engage/disengage) (true/false)
     * @return void
     */
    virtual void updateRvcState(bool bRvcStatus) = 0;

    /**
     * @brief getCurrentTrackIndex - Method to get the Index of item to be highlighted in a browse list
     * @param iBrowseSessionId - Current Browse Session Id
     * @param iSessionQueryId - Current Session Query Id
     * @return void
     */
    virtual void getCurrentTrackIndex(uint32_t iBrowseSessionId, uint32_t iSessionQueryId) = 0;

    /**
     * @brief handleVideoSurface: This method sends request to media service to hide or show the video surface.
     * @param bVidSurfaceStatus: true - show video surface, false - hide video surface.
     * @return void.
     */
    virtual void handleVideoSurface(bool bVideoSurfaceStatus) = 0;


private:

    /**
     * @brief Method to get RemotePlayerCapabilities from Media Service
     * @param void
     * @param void
     */
    virtual void getRemotePlayerCapabilitiesValue() = 0;

    /**
     * @brief Method to get SyncState from Media Service
     * @param void
     * @return void
     */
    virtual void getSyncStateValue() = 0;


    /*********************************************************
             CallBack Methods
     *********************************************************/

    /**
     * @brief CallBack Method to update the NowPlayingData
     * @param objData - object containing now playing info of the song
     * @return void
     */
    virtual void onNowPlayingDataCb(MMPresTypes::tNowPlayingInfo objData) = 0;

    /**
     * @brief CallBack Method to update the play state of current song
     * @param ePlayState - play state of the active song
     * @return void
     */
    virtual void onPlaybackStateCb(MMPresTypes::ePlayState ePlayState) = 0;

    /**
     * @brief CallBack Method to update the album art of current song
     * @param eArtWorkAvailabilityStatus - availability of album art for the active song
     * @return void
     */
    virtual void onArtWorkAvailabilityStatusCb(MMPresTypes::eArtWorkAvailabilityStatus eArtWorkAvailabilityStatus) = 0;

    /**
     * @brief CallBack Method to update the playtime of current song
     * @param uiPlayTime - current playtime of the song
     * @return void
     */
    virtual void onPlayTimeCb(uint64_t uiPlayTime) = 0;

    /**
     * @brief CallBack Method to update the total duration of current song
     * @param uiTotalDuration - total duration of the song
     * @return void
     */
    virtual void onTotalPlayDurationCb(uint64_t uiTotalDuration) = 0;

    /**
     * @brief CallBack Method to update the shuffle property of current track session
     * @param eShuffleMode - shuffle mode of current track session
     * @return void
     */
    virtual void onShuffleModeCb(MMPresTypes::eShuffleMode eShuffleMode) = 0;

    /**
     * @brief CallBack Method to update the repeat property of current track session
     * @param eRepeatMode - repeat mode of current track session
     * @return void
     */
    virtual void onRepeatModeCb(MMPresTypes::eRepeatMode eRepeatMode) = 0;

    /**
     * @brief CallBack Method to inform HMI about change in the track state
     * @param trackState - track state of current track session
     * @return void
     */
    virtual void onTrackStateChanged(MMPresTypes::tTrackState eTrackState) = 0;

    /**
     * @brief CallBack Method to update the capabilities of the connected device
     * @param eRepeatMode - repeat mode of current track session
     * @return void
     */
    virtual void onRemotePlayerCapability(MMPresTypes::tRemotePlayerCapability eCapabilityInfo) = 0;

    /**
     * @brief CallBack Method to update the play state of currently playing video
     * @param bStatus - playing status of video i.e. true or false
     * @return void
     */
    virtual void onVideoPlayStatusChanged(bool bStatus) = 0;

    /**
     * @brief CallBack Method to update the sync state of Media service with connected device
     * @param eSyncMap - sync state information of the device
     * @return void
     */
    virtual void onSyncStateChanged(MMPresTypes::SyncMap eSyncMap) = 0;

    /**
     * @brief onBTMetaDataAvailabilityStatusAttributeCb - CallBack Method to update the BTMetadataAvailability status
     * @param mediaPresPlugin::eAvailabilityStatus - metadata availability status
     * @return void
     */
    virtual void onBTMetaDataAvailabilityStatusAttributeCb(mediaPresPlugin::eAvailabilityStatus eMetaDataAvailablityStatus) = 0;

    /**
     * @brief onMediaErrorAttributeCb - CallBack Method to update the onMediaErrorAttributeCb status
     * @param mediaPresPlugin::eAvailabilityStatus - metadata availability status
     * @return void
     */
    virtual void onMediaErrorAttributeCb(mediaPresPlugin::MediaErrorMap mapMediaError) = 0;

    /*********************************************************
             Response CallBack Methods
     *********************************************************/
    /**
     * @brief CallBack to get notified about seekToTime method response
     * @param status - call status of the seekToTime method, whether success or not.
     * @param result - type of the error received after invoking seekToTime method.
     * @return void
     */
    virtual void seekToTimeAsyncCb(const CommonAPI::CallStatus& eStatus, const MMPresTypes::eCallResult& eResult) = 0;

    /**
     * @brief CallBack to get notified about resumeAsync method response
     * @param eStatus - call status of the resumeAsync method, whether success or not.
     * @param eResult - type of the error received after invoking resumeAsync method.
     * @return void
     */
    virtual void resumeAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) = 0;

    /**
     * @brief CallBack to get notified about pauseAsync method response
     * @param eStatus - call status of the pauseAsync method, whether success or not.
     * @param eResult - type of the error received after invoking pauseAsync method.
     * @return void
     */
    virtual void pauseAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) = 0;

    /**
     * @brief CallBack to get notified about nextAsync method response
     * @param eStatus - call status of the nextAsync method, whether success or not.
     * @param eResult - type of the error received after invoking nextAsync method.
     * @return void
     */
    virtual void nextAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) = 0;

    /**
     * @brief CallBack to get notified about fastForwardAsync method response
     * @param eStatus - call status of the fastForwardAsync method, whether success or not.
     * @param eResult - type of the error received after invoking fastForwardAsync method.
     * @return void
     */
    virtual void fastForwardAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) = 0;

    /**
     * @brief CallBack to get notified about fastRewindAsync method response
     * @param eStatus - call status of the fastRewindAsync method, whether success or not.
     * @param eResult - type of the error received after invoking fastRewindAsync method.
     * @return void
     */
    virtual void fastRewindAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) = 0;

    /**
     * @brief CallBack to get notified about previousAsync method response
     * @param eStatus - call status of the previousAsync method, whether success or not.
     * @param eResult - type of the error received after invoking previousAsync method.
     * @return void
     */
    virtual void previousAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) = 0;

    /**
     * @brief CallBack to get notified about setShuffleAsync method response
     * @param eStatus - call status of the setShuffleAsync method, whether success or not.
     * @param eResult - type of the error received after invoking setShuffleAsync method.
     * @return void
     */
    virtual void toggleShuffleAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) = 0;

    /**
     * @brief CallBack to get notified about setRepeatAsync method response
     * @param eStatus - call status of the setRepeatAsync method, whether success or not.
     * @param eResult - type of the error received after invoking setRepeatAsync method.
     * @return void
     */
    virtual void toggleRepeatAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) = 0;

    //FixMe: Album Art path should be sent as std::string to Media adaptor and adaptor should then convert it into QString
    /**
     * @brief CallBack to get notified about response of getAlbumArtPath()
     * @param eStatus - call status of the getAlbumArtPath method, whether success or not.
     * @param strPath - path of the albm art image for active song.
     * @return void
     */
    virtual void getAlbumArtPathAsyncCb(const CommonAPI::CallStatus &eStatus, const std::string &strPath) = 0;

    /**
     * @brief CallBack to get notified about response of playSongAsyncCb()
     * @param eStatus - call status of the getAlbumArtPath method, whether success or not.
     * @param eResult - type of the error received after invoking setRepeatAsync method.
     * @return void
     */
    virtual void playSongAsyncCb(const CommonAPI::CallStatus &status, const MMPresTypes::eCallResult &result) = 0;

    /**
     * @brief CallBack to get notified about response of playSongAsyncCb()
     * @param eStatus - call status of the getAlbumArtPath method, whether success or not.
     * @param eResult - type of the error received after invoking setRepeatAsync method.
     * @param uiNumResults - number of results after this request is procesed.
     * @param uiSessionQueryID - New session query ID after the media pointer is traversed to previous position
     * @param strBreadcrumbPath - New breadcrumb path after the media pointer is traversed to previous position.
     * @return void
     */
    virtual void goToPreviousLevelAsyncCb(const CommonAPI::CallStatus &eStatus, const MMPresTypes::eCallResult &eResult, const uint64_t &uiNumResults, const uint32_t &uiSessionQueryID, const MMPresTypes::ePrevBrowseLevel &ePrevBrowseLevel, const std::string &strBreadcrumbPath) = 0;

    /**
     * @brief CallBack to get notified about response of goToNowPlayingLevelAsyncCb()
     * @param eStatus - call status of the getAlbumArtPath method, whether success or not.
     * @param eResult - type of the error received after invoking setRepeatAsync method.
     * @param uiNumResults - number of results after this request is procesed.
     * @param uiSessionQueryID - New session query ID after the media pointer is traversed to previous position.
     * @param strBreadcrumbPath - New breadcrumb path after the media pointer is traversed to previous position.
     * @return void
     */
    virtual void goToNowPlayingLevelAsyncCb(const CallStatus &eStatus, const MMPresTypes::eCallResult &eResult, const uint64_t &uiNumResults, const uint32_t &uiSessionQueryID, const string &strBreadcrumbpath) = 0;

    /**
     * @brief Callback method to get shuffle attribute
     * @param eStatus -  call status of getShuffleModeAttribute().getValueAsync, whether success or not.
     * @param eShuffleValue - current shuffle mode
     * @return void
     */
    virtual void getShuffleStateCb(const CallStatus &eStatus, MMPresTypes::eShuffleMode eShuffleValue) = 0;

    /**
     * @brief Callback method to get repeat attribute
     * @param eStatus -  call status of getRepeatModeAttribute().getValueAsync, whether success or not.
     * @param eRepeatValue - current repeat mode
     * @return void
     */
    virtual void getRepeatStateCb(const CallStatus &eStatus, MMPresTypes::eRepeatMode eRepeatValue) = 0;

    /**
     * @brief Callback method to get USB playback mode attribute
     * @param eUsbPlaybackMode - current playback mode of USB
     * @return void
     */
    virtual void getUsbPlaybackModeCb(const CallStatus &eStatus, mediaPresPlugin::eUsbPlaybackMode eUsbPlaybackMode) = 0;

    /**
     * @brief getDeviceItemsInfoAttributeCb - Callback method to get info of all available media categories for device connected to USB slot
     * @param eStatus -  call status whether success or not
     * @param sCategoriesInfo - info of all available media categories
     * @return void
     */
    virtual void getDeviceItemsInfoAttributeCb(const CallStatus &eStatus, mediaPresPlugin::sItemsInfo sCategoriesInfo) = 0;

    /**
     * @brief Callback method to get remotePlayerCapabilities attribute
     * @param eStatus -  call status of getRemotePlayerCapabilityAttribute().getValueAsync, whether success or not.
     * @param value - current value of remotePlayerCapability attribute
     * @return void
     */
    virtual void getRemotePlayerCapabilitiesValueCb(const CallStatus &eStatus, MMPresTypes::tRemotePlayerCapability value) = 0;

    /**
     * @brief Callback method to get syncState attribute
     * @param eStatus -  call status of getSyncStatusAttribute().getValueAsync(), whether success or not.
     * @param value - current value of syncState attribute
     * @return void
     */
    virtual void getSyncStateValueCb(const CallStatus &eStatus, MMPresTypes::SyncMap value) = 0;

    /**
     * @brief CallBack to get notified about nextFolderAsync method response
     * @param eStatus -  call status whether success or not.
     * @param eMediaError - Details of media error if any
     * @return void
     */
    virtual void nextFolderAsyncCb(const CallStatus &eStatus, const MMPresTypes::eMediaError &eMediaError) = 0;

    /**
     * @brief CallBack to get notified about previousFolderAsync method response
     * @param eStatus -  call status whether success or not.
     * @param eMediaError - Details of media error if any
     * @return void
     */
    virtual void previousFolderAsyncCb(const CallStatus &eStatus, const MMPresTypes::eMediaError &eMediaError) = 0;

    /**
     * @brief updateRvcStateAsyncCb callback method for updateRvcState call
     * @param eStatus - call status of the setRepeatAsync method, whether success or not.
     * @param eResult - type of the error received after invoking updateRvcState method.
     */
    virtual void updateRvcStateAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult& eResult) = 0;

    /**
     * @brief CallBack Method to get the bit rate for Media audio
     * @param strBitRate - bit rate of Media audio
     * @return void
     */
    virtual void onBitRateAttributeCb(std::string strBitRate) = 0;

    /**
     * @brief CallBack Method to get the sampling rate for Media audio
     * @param strSamplingRate - sampling rate of Media audio
     * @return void
     */
    virtual void onSamplingRateAttributeCb(std::string strSamplingRate) = 0;

    /**
     * @brief onDeviceItemsInfoAttributeCb - CallBack Method to get the count of all media categories for device connected to USB slot
     * @param sCategoriesInfo - info of available media categories
     * @return void
     */
    virtual void onDeviceItemsInfoAttributeCb(mediaPresPlugin::sItemsInfo sCategoriesInfo) = 0;

    /**
     * @brief onVideoTestModeParametersAttributeCb - CallBack Method to get the video test mode parameters
     * @param sVideoParameters - info of video test mode parameters used in test mode
     * @return void
     */
    virtual void onVideoTestModeParametersAttributeCb(mediaPresPlugin::sVideoParameters sVideoTestModeParameters) = 0;


    /**
     * @brief getCurrentTrackIndexAsyncCb - Callback method to get the Index of item to be highlighted in current browse list
     * @param status - call status of the getCurrentTrackIndexAsync method, whether success or not.
     * @param result - type of the error received after invoking getCurrentTrackIndexAsync method.
     * @param iSessionQueryID - Session query Id for which trackId has been received
     * @param bHighlight - bool value if received trackIndex should be highlighted or not
     * @param iTrackIndex - Index of the item to be highlighted
     * @return void
     */
    virtual void getCurrentTrackIndexAsyncCb(const CommonAPI::CallStatus& status, const mediaPresPlugin::eCallResult& result, const uint32_t& iSessionQueryID, const bool& bHighlight, const uint64_t& iTrackIndex) = 0;
};

#endif // IMEDIARESOURCE_H

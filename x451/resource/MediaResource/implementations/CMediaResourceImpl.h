/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaResourceImpl.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CMediaResourceImpl, Resource Implementation for Media.
*/
#ifndef CMEDIARESOURCEIMPL_H
#define CMEDIARESOURCEIMPL_H

#include "interfaces/IMediaResource.h"
#include "CMediaEventProvider.h"

using namespace std;
using namespace v1::com::harman::mmpres;
using namespace v0::com::harman::mmpresPlugin;

/**
 * @class CMediaResourceImpl
 * @brief This class shall implement Media Resource intreface
 */
class CMediaResourceImpl: public IMediaResource
{
public:
    virtual ~CMediaResourceImpl();
    /**
     * @brief Method to get the instance of CMediaEventProvider
     * @param void
     * @return CMediaEventProvider*
     */
    CMediaEventProvider* getMediaEventProvider();

    /**
     * @brief Method to open the media browse session
     * @param void
     * @return void
     */
    void openBrowseSession();

    /**
     * @brief Method to open the media browse session specific to preview requests
     * @param void
     * @return void
     */
    void openPreviewBrowseSession();

    /**
     * @brief Method to set m_iActiveEntSource. This method is called from MediaAdaptor
     * @param iActiveEntSourceId - int value of active Ent. source
     * @return void
     */
    void setActiveEntSource(int iActiveEntSourceId) override {m_iActiveEntSource = iActiveEntSourceId;}


    /*********************************************************
             Request Methods
     *********************************************************/
    void seekToTime(uint64_t uiSeekToTime) override;
    void next(CMediaEnum::EButtonStates eButtonState) override;
    void prev(CMediaEnum::EButtonStates eButtonState) override;
    void resume(CMediaEnum::EButtonStates eButtonState) override;
    void pause(CMediaEnum::EButtonStates eButtonState) override;
    void fastForward(CMediaEnum::EButtonStates eButtonState) override;
    void fastRewind(CMediaEnum::EButtonStates eButtonState) override;
    void toggleShuffle(CMediaEnum::EButtonStates eButtonState) override;
    void toggleRepeat(CMediaEnum::EButtonStates eButtonState) override;
    const NowPlayingInfo &getNowPlayingData() override;
    const SRemotePlayerSupport &getRemotePlayerCapabilities() override;
    vector<std::string> &getImageDataList() override;
    vector<MediaBrowseData> &getBrowseDataList() override;
    int getUSBSlotSyncState() override;
    int getBTSlotSyncState() override;
    vector<int> &getBTSlotCategories() override;
    vector<int> &getUSBSlotCategories() override;
    void getShuffleState() override;
    void getRepeatState() override;
    void nextFolder() override;
    void previousFolder() override;
    void getUSBPlaybackMode() override;
    void getDeviceItemsInfoAttribute() override;
    const sVideoParameters &getVideoTestModeParameters() override;

    void fetchItems(uint iStartIndex,uint iCount, bool isPreviewReq = false) override;
    void updateRvcState(bool bRvcStatus) override;

    void getCurrentTrackIndex(uint32_t iBrowseSessionId, uint32_t iSessionQueryId) override;

    /**
     * @brief handleVideoSurface: This method sends request to media service to hide or show the video surface.
     * @param bVidSurfaceStatus: true - show video surface, false - hide video surface.
     * @return void.
     */
    void handleVideoSurface(bool bVideoSurfaceStatus) override;


private:
    CMediaResourceImpl();

    /**
     * Total number of browse categroies that HMI displays to the user
     * Media service supports some 20 Metadata types but not all are utilized in this project
     */
    const int TOTAL_CATEGORIES;

    /*********************************************************
             Internal Methods
     *********************************************************/
    /**
     * @brief Method to subscribe CallBack methods to events provided by MediaPlayerProxy
     * @param void
     * @return void
     */
    void subscribe();

    /*********************************************************
             broadcast/signals Methods
     *********************************************************/
    /**
     * @brief onTrackSessionChangedEvent - broadcast from Media service to inform change in track session
     * @brief HMI shall get fetch preview list on this event
     * @return void
     */
    void onTrackSessionChangedEvent();

    /*********************************************************
             CallBack Methods
     *********************************************************/
    void onNowPlayingDataCb(MMPresTypes::tNowPlayingInfo objData) override;
    void onPlaybackStateCb(MMPresTypes::ePlayState ePlayState) override;
    void onArtWorkAvailabilityStatusCb(MMPresTypes::eArtWorkAvailabilityStatus eArtWorkAvailabilityStatus) override;
    void onPlayTimeCb(uint64_t uiPlayTime) override;
    void onTotalPlayDurationCb(uint64_t uiTotalDuration) override;
    void onShuffleModeCb(MMPresTypes::eShuffleMode eShuffleMode) override;
    void onRepeatModeCb(MMPresTypes::eRepeatMode eRepeatMode) override;
    void onTrackStateChanged(MMPresTypes::tTrackState eTrackState) override;
    void onRemotePlayerCapability(MMPresTypes::tRemotePlayerCapability eCapabilityInfo) override;
    void onVideoPlayStatusChanged(bool bStatus) override;
    void onSyncStateChanged(MMPresTypes::SyncMap mSyncMap) override;
    void onBitRateAttributeCb(std::string strBitRate) override;
    void onSamplingRateAttributeCb(std::string strSamplingRate) override;
    void onDeviceItemsInfoAttributeCb(mediaPresPlugin::sItemsInfo sCategoriesInfo) override;
    void onVideoTestModeParametersAttributeCb(mediaPresPlugin::sVideoParameters sVideoTestModeParameters) override;
    void onBTMetaDataAvailabilityStatusAttributeCb(mediaPresPlugin::eAvailabilityStatus eMetaDataAvailablityStatus) override;
    void onMediaErrorAttributeCb(mediaPresPlugin::MediaErrorMap mapMediaError) override;
    void getRemotePlayerCapabilitiesValue() override;
    void getSyncStateValue() override;

    /*********************************************************
             Response CallBack Methods
     *********************************************************/
    void resumeAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) override;
    void pauseAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) override;
    void nextAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) override;
    void previousAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) override;
    void fastForwardAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) override;
    void fastRewindAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult) override;
    void getAlbumArtPathAsyncCb(const CommonAPI::CallStatus &eStatus, const std::string &strPath) override;
    void toggleShuffleAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult& eResult) override;
    void toggleRepeatAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult& eResult) override;
    void seekToTimeAsyncCb(const CommonAPI::CallStatus& eStatus, const MMPresTypes::eCallResult &eResult) override;
    void playSongAsyncCb(const CommonAPI::CallStatus &eStatus, const MMPresTypes::eCallResult &eResult) override;
    void goToPreviousLevelAsyncCb(const CommonAPI::CallStatus &eStatus, const MMPresTypes::eCallResult &eResult, const uint64_t &uiNumResults, const uint32_t &uiSessionQueryID, const MMPresTypes::ePrevBrowseLevel &ePrevBrowseLevel, const std::string &strBreadcrumbPath) override;
    void goToNowPlayingLevelAsyncCb(const CallStatus &eStatus, const MMPresTypes::eCallResult &eResult, const uint64_t &uiNumResults, const uint32_t &uiSessionQueryID, const string &strBreadcrumbpath) override;

    void getShuffleStateCb(const CallStatus &eStatus, MMPresTypes::eShuffleMode eShuffleValue) override;
    void getRepeatStateCb(const CallStatus &eStatus, MMPresTypes::eRepeatMode eRepeatValue) override;
    void getUsbPlaybackModeCb(const CallStatus &eStatus, mediaPresPlugin::eUsbPlaybackMode eUsbPlaybackMode) override;
    void getDeviceItemsInfoAttributeCb(const CallStatus &eStatus, mediaPresPlugin::sItemsInfo sCategoriesInfo) override;
    void getRemotePlayerCapabilitiesValueCb(const CallStatus &eStatus, MMPresTypes::tRemotePlayerCapability value) override;
    void getSyncStateValueCb(const CallStatus &eStatus, MMPresTypes::SyncMap value) override;
    void nextFolderAsyncCb(const CommonAPI::CallStatus &eStatus, const MMPresTypes::eMediaError &eMediaError) override;
    void previousFolderAsyncCb(const CallStatus &eStatus, const MMPresTypes::eMediaError &eMediaError) override;
    void updateRvcStateAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult& eResult) override;
    void getCurrentTrackIndexAsyncCb(const CommonAPI::CallStatus& status, const mediaPresPlugin::eCallResult& result, const uint32_t& iSessionQueryID, const bool& bHighlight, const uint64_t& iTrackIndex) override;

    /****** Status Event Listeners ***********/
    void mediaSeriveStatusCb(CommonAPI::AvailabilityStatus eStatus);
    void mediaManagerStatusCb(CommonAPI::AvailabilityStatus eStatus);
    void mediaBrowserStatusCb(CommonAPI::AvailabilityStatus eStatus);
    void mediaPluginStatusCb(CommonAPI::AvailabilityStatus eStatus);
    /****** Status Event Listeners - END ***********/

    /***** Slot info related methods *********/
    /**
     * @brief Method to get the info about all available Media slots
     * @param void
     * @return void
     */
    void getSlots();

    /**
     * @brief Callback method when 'getSlots' API is invoked
     * @param slotList - Info about all Media slots
     * @return void
     */
    void getSlotsAsyncCB(const CommonAPI::CallStatus& eStatus, const MMPresTypes::tSlotList& tSlotList);

    /**
     * @brief CallBack Method when Media slots are updated
     * @param eSlot - info of all the Media slots
     * @return void
     */
    void onSlotUpdate(MMPresTypes::tSlot tSlotUpdates);

    /**
     * @brief CallBack Method on error condition for device connected to USB slot
     * @param eUsbSlotDeviceError - error info for USB slot
     * @return void
     */
    void onUSBDeviceError(mediaPresPlugin::eUsbDeviceError eUsbSlotDeviceError);

    /**
     * @brief CallBack Method on play back mode for device connected to USB slot
     * @param eUsbPlaybackMode - play back mode
     * @return void
     */
    void onUsbPlaybackModeCb(mediaPresPlugin::eUsbPlaybackMode eUsbPlaybackMode);

    /**
     * @brief Method to get the slot Id of active device/source
     * @param void
     * @return int - Id of the slot
     */
    int getActiveSlotId();

    /***** Slot info related methods - END *********/

    /***** Media browse related methods *********/

    void getCategoryRoot(int iType, bool bIsVRRequest) override;
    void getCategorySubLevel(int iFileID, int iMetadataType, int iQueryType, bool bIsVRRequest) override;
    void playSong(int iSongIndex, bool isPreviewReq = false) override;
    void goToPreviousLevel() override;
    void goToNowPlayingLevel() override;

    /**
     * @brief Callback method when browse info is update
     * @param tBrowseCategoryInfoList - info about changes in Media browse data
     * @return void
     */
    void onBrowseCategoryInfoChanged(MMPresTypes::tDeviceBrowseCategoryList tBrowseCategoryInfoList);

    /**
     * @brief Method to parse Media browse categories
     * @param browseCategoryMap - Map of availability of all Media categories
     * @param vectAvailableCategories - vector as per USB/Bt source which shall be updated with availability
     * @return void
     */
    void parseBrowseCategoryMap(const MMPresTypes::BrowseCategoryMap& objBrowseCategoryMap, vector<int> &vectAvailableCategories);

    /**
     * @brief Method to map HMI Metadata enum value with service enum value before invoking the API of Media service
     * @param iMetdataType - metadata type value to be mapped i.e. folders, album, artists etc
     * @return int - value mapped to service enum
     */
    MMPresTypes::eMetadataType encodeMetadataEnum(int iMetdataType);

    /**
     * @brief Method to map Media service enum value with HMI enum value before invoking the API of Media service
     * @param eMetdataType - metadata type value to be mapped i.e. folders, album, artists etc
     * @return int - value mapped to HMI enum
     */
    int decodeMetadataEnum(MMPresTypes::eMetadataType eMetdataType);

    /**
     * @brief Method to map HMI Content Type enum value with service enum value before invoking the API of Media service
     * @param eMetdataType - metadata type value to be mapped i.e. song, video, image etc
     * @return MMPresTypes::eTitleContentType - value mapped to content type enum
     */
    MMPresTypes::eTitleContentType encodeContentTypeEnum(MMPresTypes::eMetadataType eMetdataType);

    /**
     * @brief openBrowseSessionAsyncCb - Medthod to save the session ID from service for Media browsing
     * @param status - status of the request
     * @param sessionId - session ID received from service
     * @param result - result of request i.e. succes/failed etc
     * @return void
     */
    void openBrowseSessionAsyncCb(const CommonAPI::CallStatus&status, const uint32_t&sessionId, const MMPresTypes::eCallResult&result);

    /**
     * @brief openPreviewBrowseSessionAsyncCb - Medthod to save the session ID from service for Media browsing
     * @param status - status of the request
     * @param sessionId - session ID received from service
     * @param result - result of request i.e. succes/failed etc
     * @return void
     */
    void openPreviewBrowseSessionAsyncCb(const CommonAPI::CallStatus& status, const uint32_t& sessionId, const MMPresTypes::eCallResult& result);

    /**
     * @brief onRequestedData - Medthod to process browse/preview list received from service
     * @param sessionId - session ID received from service
     * @param sessionQueryID - session query ID received from service
     * @param status - status of the request
     * @param startIndex - index of 1st item in the list
     * @param itemList - actual list of items
     * @param windowContainsCurrentlyPlayingTrack - bool value indicating presence of nowPlaying item
     * @param itemIndexTobeHighlighted - index of nowPlaying item
     * @param count - total items in the list
     * @return void
     */
    void onRequestedData(uint32_t sessionID, uint32_t sessionQueryID,MMPresTypes::eQueryStatus status, uint64_t startIndex, uint64_t count, MMPresTypes::MetadataItemList itemList, bool windowContainsCurrentlyPlayingTrack, uint64_t itemIndexTobeHighlighted);

    /**
     * @brief fetchRequestedData - Method to get the browse/preview list from service
     * @param status - status of the request
     * @param result - result of request i.e. succes/failed etc
     * @param isPreviewReq - bool value, true if request is for preview session
     * @return void
     */
    virtual void fetchRequestedData(uint32_t sessionQueryId, uint64_t startIndex, uint64_t count, bool isPreviewReq);

    /**
     * @brief fetchRequestedDataAsyncCb - call back for method fetchRequestedData
     * @param status - status of the request
     * @param result - result of request i.e. succes/failed etc
     * @return void
     */
    void fetchRequestedDataAsyncCb(const CommonAPI::CallStatus&status, const MMPresTypes::eCallResult&result);

    /**
     * @brief sessionQueryAsyncCb - call back for method setSessionQueryAsync
     * @param status - status of the request
     * @param result - result of request i.e. succes/failed etc
     * @param numResults - total items availablie in the requested list
     * @param sessionQueryID - session query ID received from service
     * @param breadcrumbpath - path leading to the item in db
     * @return void
     */
    void sessionQueryAsyncCb(const CommonAPI::CallStatus&status, const MMPresTypes::eCallResult&result, const uint64_t&numResults, const uint32_t&sessionQueryID, const std::string&strBreadcrumbpath);

    /**
     * @brief videoSurfaceControlAsyncCb: This is a callback method to the videoSurfaceControlAsync.
     * @param eStatus: API call status, SUCCESS or failure.
     * @param eResult: Call result of media pres, CALLRESULT_OK or fail.
     * @return void.
     */
    void videoSurfaceControlAsyncCb(const CallStatus& eStatus, const mediaPresPlugin::eCallResult& eResult);

    /********************* Media Browse Methods End ************************************/
    /**
     * @brief Method to reset the available categories valuesto default for mentioned slot
     * @param eSlotType - USB or BT slot
     * @return void
     */
    void clearAvailableCategoriesMap(MMPresTypes::eSlotType eSlotType);

    /**
     * @brief Method to update the sync state
     * @param mSyncMap
     * @return void
     */
    void setSyncState(MMPresTypes::SyncMap mSyncMap);

    /**
     * @brief Method to update the RemotePlayerCapabilities
     * @param MMPresTypes::tRemotePlayerCapability
     * @return void
     */
    void setRemotePlayerCapabilities(MMPresTypes::tRemotePlayerCapability eCapabilityInfo);

    /**
     * @brief Method to set shuffle state
     * @param eShuffleMode - current shuffle mode
     * @return void
     */
    void setShuffleState(MMPresTypes::eShuffleMode eShuffleMode);

    /**
     * @brief Method to set repeat state
     * @param eRepeatMode - current repeat mode
     * @return void
     */
    void setRepeatState(MMPresTypes::eRepeatMode eRepeatMode);

    /**
     * @brief Method to set USB playback mode
     * @param eUsbPlaybackMode - current playback mode
     * @return void
     */
    void setUSBPlayBackMode(mediaPresPlugin::eUsbPlaybackMode eUsbPlaybackMode);

    /**
     * @brief setUSBDeviceInfo - Method to set USB device info
     * @param sCategoriesInfo - info of all media categroies
     * @return void
     */
    void setUSBDeviceInfo(mediaPresPlugin::sItemsInfo sCategoriesInfo);

    /**
     * @brief setSessionQueryId - Method to set the value of m_uiSessionQueryId
     * @param uiSessionQueryId - value to be set as m_uiSessionQueryId
     * @return void
     */
    void setSessionQueryId(int iSessionQueryId);

    /**
     * @brief getMediaPressButtonStatusEnum - Method to get mediaPresPlugin::eButtonStatus enum value corresponding to eButtonState
     * @param eButtonState - current button state of media button
     * @return mediaPresPlugin::eButtonStatus enum value corresponding to eButtonState
     */
    mediaPresPlugin::eButtonStatus getMediaPressButtonStatusEnum(CMediaEnum::EButtonStates eButtonState);

private:
    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /*********************************************************
             Properties
     *********************************************************/
    //Instance of CMediaEventProvider to emit signals to the upper layer
    CMediaEventProvider* m_pMediaEventProvider;

    /**
     * MediaPlayerProxy class object to call Media Player Proxy methods
     */
    CAPIClientAbstraction<MediaPlayerProxy> m_pPlayerProxy;

    /**
     * MediaBrowseProxy class object to call Media Browse Proxy methods
     */
    CAPIClientAbstraction<MediaBrowserProxy> m_pBrowserProxy;

    /**
     * MediaPlayerProxy class object to call Media Manager Proxy methods
     */
    CAPIClientAbstraction<MediaManagerProxy> m_pManagerProxy;

    /**
     * MediaPlayerPlugin class object to call Media Plugin Proxy methods
     */
    CAPIClientAbstraction<mediaPresPluginProxy> m_pPluginProxy;

    /**
     * Instance of structure-NowPlayingInfo
     */
    NowPlayingInfo      m_objNowPlayingInfo;

    /**
     * Play state of the active song
     */
    int m_iMediaPlayState;

    /**
     * bool- to check if Media Service is available of not
     */
    bool m_bIsMediaAvailable;

    /**
    * String var to store the album Art path received from Media service
    */
    string m_strAlbumArtPath;

    /**
     * Status of browse session
     */
    bool m_bBrowserAvailable;

    /**
     * Status of plugin availability
     */
    bool m_bPluginAvailable;

    /**
     * Browse session id will be stored here
     */
    int m_iBrowseSessionId;

    /**
     * Preview browse session id will be stored here
     */
    int m_iPreviewBrowseSessionId;

    /**
     * Query session id will be stored here
     */
    int m_iSessionQueryId;

    /**
     * Now Playing Query session id will be stored here
     * This shall be used to distinguish between browse list and nowPlaying list
     */
    int m_iNowPlayingSessionQueryId;

    /**
     * Image paths data list will be stored here
     */
    vector<std::string> m_vectImagesList;

    /**
     * Media browse data list will be stored here
     */
    vector<MediaBrowseData> m_vectBrowseList;

    /**
     * Flag to hold the status of seekToTime request
     * playTime updates would be propagated to adaptor only if this flag is false,
     * else playTime updates shall be supressed in resource layer itself
     * As a fail safe measure, flag is also cleared when nowPlaying data is received
     */
    bool m_bIsSeekRequestInProcess;

    /**
     * Slot ID of connected USB device will be stored here
     */
    int m_iUSBSlotID;

    /**
     * Slot ID of connected BT device will be stored here
     */
    int m_iBTSlotID;

    /**
     * Slot ID of HDD device will be stored here
     */
    int m_iHDDSlotID;

    /**
     * Sync state for device connected to USB slot
     */
    MMPresTypes::eSyncState m_eUSBSlotSyncState;

    /**
     * Sync state for device connected to BT slot
     */
    MMPresTypes::eSyncState m_eBTSlotSyncState;

    /**
     * Vector to store available Media categories for device conected to USB port
     */
    vector<int> m_vectUSBAvailableCategories;

    /**
     * Vector to store available Media categories for device conected via Bluetooth
     */
    vector<int> m_vectBTAvailableCategories;

    /**
     * Object of Struct SRemotePlayerSupport
     */
    SRemotePlayerSupport m_objRemotePlayerCapabilities;

    /**
     * This will hold a bool value for browse feature support in BT device currently connected for Media
     */
    bool m_bIsBTDeviceBrowsable;

    /**
     * This will hold a int value for active Ent. Source. This is updated from Media Adaptor
     */
    int m_iActiveEntSource;

    /**
     * This will hold a int value for major version of profile for BT connected device
     */
    int m_iBTMajorVersion;

    /**
     * This will hold a int value for major version of profile for BT connected device
     */
    int m_iBTMinorVersion;

    /**
     * Object of Struct SRemotePlayerSupport
     */
    sVideoParameters m_objVideoParameters;

    //This will hold the index of item highlighted in current browse category list
    int m_iIndexHighlighted;
};

#endif // CMEDIARESOURCEIMPL_H

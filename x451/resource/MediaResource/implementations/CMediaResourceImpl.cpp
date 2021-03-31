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

#include "CMediaResourceImpl.h"
#include "logging.h"
#include "ResourceMaster.h"
#include "ResourceDeploymentConfig.h"
#include "CMediaResourceData.h"

CMediaResourceImpl::CMediaResourceImpl():
    TOTAL_CATEGORIES(13), //This magic number matches to the enum EMediaBrowse in HMI.
    m_pMediaEventProvider(new CMediaEventProvider()),
    m_pPlayerProxy(ResourceDeploymentConfig::getConfig().m_MediaPlayer_Proxy.domain,ResourceDeploymentConfig::getConfig().m_MediaPlayer_Proxy.instance),
    m_pBrowserProxy(ResourceDeploymentConfig::getConfig().m_Media_Browser.domain,ResourceDeploymentConfig::getConfig().m_Media_Browser.instance),
    m_pManagerProxy(ResourceDeploymentConfig::getConfig().m_Media_Manager.domain,ResourceDeploymentConfig::getConfig().m_Media_Manager.instance),
    m_pPluginProxy(ResourceDeploymentConfig::getConfig().m_MediaPlugin_Proxy.domain,ResourceDeploymentConfig::getConfig().m_MediaPlugin_Proxy.instance),
    m_bIsMediaAvailable(false),
    m_strAlbumArtPath(""),
    m_bBrowserAvailable(false),
    m_bPluginAvailable(false),
    m_iBrowseSessionId(-1),
    m_iPreviewBrowseSessionId(-1),
    m_iSessionQueryId(-1),
    m_iNowPlayingSessionQueryId(-1),
    m_bIsSeekRequestInProcess(false),
    m_iUSBSlotID(-1),
    m_iBTSlotID(-1),
    m_iHDDSlotID(-1),
    m_bIsBTDeviceBrowsable(false),
    m_iActiveEntSource(0),
    m_iIndexHighlighted(-1)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);
    SUBSCRIBE(m_pPlayerProxy, getProxyStatusEvent(), &CMediaResourceImpl::mediaSeriveStatusCb, _1);
    SUBSCRIBE(m_pBrowserProxy,getProxyStatusEvent(),&CMediaResourceImpl::mediaBrowserStatusCb,_1);
    SUBSCRIBE(m_pManagerProxy,getProxyStatusEvent(),&CMediaResourceImpl::mediaManagerStatusCb,_1);
    SUBSCRIBE(m_pPluginProxy,getProxyStatusEvent(),&CMediaResourceImpl::mediaPluginStatusCb,_1);
    m_vectBrowseList.clear();
    m_vectImagesList.clear();

    m_eUSBSlotSyncState = MMPresTypes::eSyncState::STATE_UNKNOWN;
    m_eBTSlotSyncState = MMPresTypes::eSyncState::STATE_UNKNOWN;
    clearAvailableCategoriesMap(MMPresTypes::eSlotType::SLOTTYPE_USB);
    clearAvailableCategoriesMap(MMPresTypes::eSlotType::SLOTTYPE_BLUETOOTH);
}

CMediaResourceImpl::~CMediaResourceImpl()
{
    if(m_pMediaEventProvider)
    {
        delete m_pMediaEventProvider;
        m_pMediaEventProvider = NULL;
    }
}

CMediaEventProvider* CMediaResourceImpl::getMediaEventProvider()
{
    return m_pMediaEventProvider;
}
const NowPlayingInfo &CMediaResourceImpl::getNowPlayingData()
{
    return m_objNowPlayingInfo;
}

const SRemotePlayerSupport &CMediaResourceImpl::getRemotePlayerCapabilities()
{
    return m_objRemotePlayerCapabilities;
}

const sVideoParameters &CMediaResourceImpl::getVideoTestModeParameters()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);
    return m_objVideoParameters;
}

/*********************************************************
         Internal Methods
 *********************************************************/
void CMediaResourceImpl::subscribe()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);
    SUBSCRIBE(m_pPlayerProxy,getNowPlayingDataAttribute().getChangedEvent(), &CMediaResourceImpl::onNowPlayingDataCb,_1);
    SUBSCRIBE(m_pPlayerProxy,getPlayStateAttribute().getChangedEvent(),&CMediaResourceImpl::onPlaybackStateCb,_1);
    SUBSCRIBE(m_pPlayerProxy,getNowPlayingArtworkStatusAttribute().getChangedEvent(),&CMediaResourceImpl::onArtWorkAvailabilityStatusCb,_1);
    SUBSCRIBE(m_pPlayerProxy,getCurrentPlayTimeAttribute().getChangedEvent(),&CMediaResourceImpl::onPlayTimeCb,_1);
    SUBSCRIBE(m_pPlayerProxy,getTotalPlayDurationAttribute().getChangedEvent(),&CMediaResourceImpl::onTotalPlayDurationCb,_1);
    SUBSCRIBE(m_pPlayerProxy,getShuffleModeAttribute().getChangedEvent(),&CMediaResourceImpl::onShuffleModeCb,_1);
    SUBSCRIBE(m_pPlayerProxy,getRepeatModeAttribute().getChangedEvent(),&CMediaResourceImpl::onRepeatModeCb,_1);
    SUBSCRIBE(m_pPlayerProxy,getTrackStateAttribute().getChangedEvent(),&CMediaResourceImpl::onTrackStateChanged,_1);
    SUBSCRIBE(m_pPlayerProxy,getRemotePlayerCapabilityAttribute().getChangedEvent(),&CMediaResourceImpl::onRemotePlayerCapability,_1);
    SUBSCRIBE(m_pPlayerProxy,getVideoPlayStatusAttribute().getChangedEvent(),&CMediaResourceImpl::onVideoPlayStatusChanged,_1);
    SUBSCRIBE(m_pPlayerProxy,getSyncStatusAttribute().getChangedEvent(),&CMediaResourceImpl::onSyncStateChanged,_1);


    /* Browser proxy subscriptions */
    SUBSCRIBE(m_pBrowserProxy,getSessionQueryWindowUpdateSelectiveEvent(),&CMediaResourceImpl::onRequestedData,_1,_2,_3,_4,_5,_6,_7,_8);

    /* Manager proxy subscriptions */
    SUBSCRIBE(m_pManagerProxy,getSlotUpdateEvent(),&CMediaResourceImpl::onSlotUpdate,_1);
    SUBSCRIBE(m_pManagerProxy,getMediaDeviceBrowseCategoryInfoAttribute().getChangedEvent(),&CMediaResourceImpl::onBrowseCategoryInfoChanged,_1);

    /* Plugin proxy subscriptions */
    SUBSCRIBE(m_pPluginProxy,getUsbDeviceErrorAttribute().getChangedEvent(),&CMediaResourceImpl::onUSBDeviceError,_1);
    SUBSCRIBE(m_pPluginProxy,getUsbPlaybackModeAttribute().getChangedEvent(),&CMediaResourceImpl::onUsbPlaybackModeCb,_1);
    SUBSCRIBE(m_pPluginProxy,getBitRateAttribute().getChangedEvent(),&CMediaResourceImpl::onBitRateAttributeCb,_1);
    SUBSCRIBE(m_pPluginProxy,getSamplingRateAttribute().getChangedEvent(),&CMediaResourceImpl::onSamplingRateAttributeCb,_1);
    SUBSCRIBE(m_pPluginProxy,getDeviceItemsInfoAttribute().getChangedEvent(),&CMediaResourceImpl::onDeviceItemsInfoAttributeCb,_1);
    SUBSCRIBE(m_pPluginProxy,getVideoTestModeParametersAttribute().getChangedEvent(),&CMediaResourceImpl::onVideoTestModeParametersAttributeCb,_1);
    SUBSCRIBE(m_pPluginProxy,getBTMetaDataAvailabilityStatusAttribute().getChangedEvent(),&CMediaResourceImpl::onBTMetaDataAvailabilityStatusAttributeCb,_1);
    SUBSCRIBE(m_pPluginProxy,getMediaErrorAttribute().getChangedEvent(),&CMediaResourceImpl::onMediaErrorAttributeCb,_1);
    SUBSCRIBE(m_pPluginProxy,getTrackSessionChangedEvent(),&CMediaResourceImpl::onTrackSessionChangedEvent);
}

/*********************************************************
         broadcast/signals Methods
 *********************************************************/

void CMediaResourceImpl::onTrackSessionChangedEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->trackSessionUpdate();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

/*********************************************************
         CallBack Methods
 *********************************************************/
//Callback function for nowPlaying info updates
void CMediaResourceImpl::onNowPlayingDataCb(MMPresTypes::tNowPlayingInfo objData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);

    m_objNowPlayingInfo.strTitle         = objData.getTitle();
    m_objNowPlayingInfo.strArtist        = objData.getArtist();
    m_objNowPlayingInfo.strAlbum         = objData.getAlbum();
    m_objNowPlayingInfo.iFileID        = objData.getFid();
    m_objNowPlayingInfo.iMediaType     = decodeMetadataEnum(objData.getNowPlayingItemType());
    m_objNowPlayingInfo.strFileName     = objData.getFilename();


    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Title = %s, artist = %s, Album = %s, FileName = %s, Metadata Type = %d",__FUNCTION__,m_objNowPlayingInfo.strTitle.c_str(),
             m_objNowPlayingInfo.strArtist.c_str(),m_objNowPlayingInfo.strAlbum.c_str(),m_objNowPlayingInfo.strFileName.c_str(), static_cast<int>(objData.getNowPlayingItemType()));

    if(m_iSessionQueryId != -1)
    {
        getCurrentTrackIndex(m_iBrowseSessionId,m_iSessionQueryId);
    }
    else
    {
        //Do nothing
    }

    if(m_pMediaEventProvider)
    {
        m_bIsSeekRequestInProcess = false;
        m_pMediaEventProvider->nowPlayingDataUpdate();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::onPlaybackStateCb(MMPresTypes::ePlayState ePlayState)
{
    m_iMediaPlayState = ePlayState.value_;
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s playState: %d",__FUNCTION__,ePlayState.value_);
    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->playBackStateUpdated(m_iMediaPlayState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::mediaSeriveStatusCb( CommonAPI::AvailabilityStatus eStatus )
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(CommonAPI::AvailabilityStatus::AVAILABLE == eStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy available");
        m_bIsMediaAvailable = true;
        subscribe ();
    }
    else
    {
        m_bIsMediaAvailable = false;
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");

    }
}

void CMediaResourceImpl::mediaManagerStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(CommonAPI::AvailabilityStatus::AVAILABLE == eStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Manager available", __FUNCTION__);
        getSlots();
    }
    else
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::onArtWorkAvailabilityStatusCb(MMPresTypes::eArtWorkAvailabilityStatus eArtWorkAvailabilityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s = %d",__FUNCTION__, eArtWorkAvailabilityStatus.value_);

    if((MMPresTypes::eArtWorkAvailabilityStatus::ARTWORK_STATUS_AVAILABLE == eArtWorkAvailabilityStatus) && (m_bIsMediaAvailable))
    {
        LOG_DEBUG(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::onArtWorkAvailabilityStatus() - Album Art is available for song");
        m_pPlayerProxy->getNowPlayingAlbumArtPathAsync(1,std::bind(&CMediaResourceImpl::getAlbumArtPathAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_DEBUG(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::onArtWorkAvailabilityStatus() - Album Art is *not* available for song");
        m_strAlbumArtPath = "";
        if(m_pMediaEventProvider)
        {
            m_pMediaEventProvider->albumArtUpdate(m_strAlbumArtPath);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
        }
    }
}

void CMediaResourceImpl::onPlayTimeCb(uint64_t uiPlayTime)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s playTime received from service = %llu", __FUNCTION__, uiPlayTime);

    if(m_pMediaEventProvider)
    {
        if(!m_bIsSeekRequestInProcess)
        {
            m_pMediaEventProvider->playTimeUpdated(uiPlayTime);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"Seek request in progress, hence playTime from service is ignored");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::onTotalPlayDurationCb(uint64_t uiTotalDuration)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s totalDuration received from service = %llu", __FUNCTION__, uiTotalDuration);

    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->totalDurationUpdated(uiTotalDuration);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::onShuffleModeCb(MMPresTypes::eShuffleMode eShuffleMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s shuffle mode received from service = %d", __FUNCTION__, eShuffleMode.value_);

    setShuffleState(eShuffleMode);
}

void CMediaResourceImpl::onRepeatModeCb(MMPresTypes::eRepeatMode eRepeatMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s repeat mode received from service = %d", __FUNCTION__, eRepeatMode.value_);

    setRepeatState(eRepeatMode);
}

void CMediaResourceImpl::onTrackStateChanged(MMPresTypes::tTrackState eTrackState)
{
    //current track number and total track count should be available here
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->trackNumberUpdated(eTrackState.getCurrentTrack());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::onRemotePlayerCapability(MMPresTypes::tRemotePlayerCapability eCapabilityInfo)
{
    //Device capabilities sould be available here
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    setRemotePlayerCapabilities(eCapabilityInfo);
}

void CMediaResourceImpl::onVideoPlayStatusChanged(bool bStatus)
{
    //Video playing status available here
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    CPP_UNUSED(bStatus);
}

void CMediaResourceImpl::onSyncStateChanged(MMPresTypes::SyncMap mSyncMap)
{
    //sync state of device available here
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    setSyncState(mSyncMap);
}

/*********************************************************
         Request Methods
 *********************************************************/
void CMediaResourceImpl::seekToTime(uint64_t uiSeekToTime)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - seekToTime requested: %llu",__FUNCTION__,uiSeekToTime);

    if(m_bIsMediaAvailable)
    {
        m_bIsSeekRequestInProcess = true;
        m_pPlayerProxy->seekToTimeAsync(uiSeekToTime,std::bind(&CMediaResourceImpl::seekToTimeAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::next(CMediaEnum::EButtonStates eButtonState)
{
    // FixMe: Need to add NULL check for m_pPlayerProxy
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    //FixMe: Need to add ENUMs for step instead of 1
    if(m_bPluginAvailable)
    {
        m_pPluginProxy->nextAsync(1,getMediaPressButtonStatusEnum(eButtonState),std::bind(&CMediaResourceImpl::nextAsyncCb,this,_1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }

}
void CMediaResourceImpl::prev(CMediaEnum::EButtonStates eButtonState)
{
    // FixMe: Need to add NULL check for m_pPlayerProxy
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    //FixMe: Need to add ENUMs for step instead of 1
    if(m_bPluginAvailable)
    {
        m_pPluginProxy->previousAsync(1,getMediaPressButtonStatusEnum(eButtonState),std::bind(&CMediaResourceImpl::previousAsyncCb,this,_1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::resume(CMediaEnum::EButtonStates eButtonState)
{
    // FixMe: Need to add NULL check for m_pPlayerProxy
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(m_bIsMediaAvailable)
    {
        m_pPluginProxy->resumeAsync(getMediaPressButtonStatusEnum(eButtonState),std::bind(&CMediaResourceImpl::previousAsyncCb,this,_1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}
void CMediaResourceImpl::pause(CMediaEnum::EButtonStates eButtonState)
{
    // FixMe: Need to add NULL check for m_pPlayerProxy
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(m_bIsMediaAvailable)
    {
        m_pPluginProxy->pauseAsync(getMediaPressButtonStatusEnum(eButtonState),std::bind(&CMediaResourceImpl::pauseAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::fastForward(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(m_bIsMediaAvailable)
    {
        m_pPluginProxy->fastforwardAsync(getMediaPressButtonStatusEnum(eButtonState),std::bind(&CMediaResourceImpl::fastForwardAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::fastRewind(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(m_bIsMediaAvailable)
    {
        m_pPluginProxy->fastreverseAsync(getMediaPressButtonStatusEnum(eButtonState),std::bind(&CMediaResourceImpl::fastRewindAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::toggleShuffle(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Shuffle mode requested",__FUNCTION__);

    if(m_bPluginAvailable)
    {
        m_pPluginProxy->toggleShuffleAsync(getMediaPressButtonStatusEnum(eButtonState),std::bind(&CMediaResourceImpl::toggleShuffleAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::toggleRepeat(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - repeat mode requested",__FUNCTION__);

    if(m_bPluginAvailable)
    {
        m_pPluginProxy->toggleRepeatAsync(getMediaPressButtonStatusEnum(eButtonState),std::bind(&CMediaResourceImpl::toggleRepeatAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

/*********************************************************
         Response CallBack Methods
 *********************************************************/

void CMediaResourceImpl::resumeAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, result = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult.value_));
}

void CMediaResourceImpl::pauseAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, result = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult.value_));
}

void CMediaResourceImpl::nextAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, result = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult.value_));
}

void CMediaResourceImpl::previousAsyncCb(const CommonAPI::CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, result = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult.value_));
}

void CMediaResourceImpl::fastForwardAsyncCb(const CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, result = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult.value_));
}

void CMediaResourceImpl::fastRewindAsyncCb(const CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, result = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult.value_));
}

void CMediaResourceImpl::getAlbumArtPathAsyncCb(const CommonAPI::CallStatus &eStatus, const string &strPath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(CommonAPI::CallStatus::SUCCESS == eStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"Album art path:  %s",strPath.c_str());

        m_strAlbumArtPath = strPath;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::getAlbumArtPathAsyncCB - Album Art request failed");
        m_strAlbumArtPath = "";
    }


    //Irrespective of request passed/failed, this should be notified to the screen
    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->albumArtUpdate(m_strAlbumArtPath);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

mediaPresPlugin::eButtonStatus CMediaResourceImpl::getMediaPressButtonStatusEnum(CMediaEnum::EButtonStates eButtonState)
{
    mediaPresPlugin::eButtonStatus eButtonStatus;
    switch (eButtonState) {
    case CMediaEnum::EButtonStates::EN_BUTTON_STATE_PRESSED:
        eButtonStatus = mediaPresPlugin::eButtonStatus::BUTTONSTATUS_PRESS;
        break;
    case CMediaEnum::EButtonStates::EN_BUTTON_STATE_RELEASED:
        eButtonStatus = mediaPresPlugin::eButtonStatus::BUTTONSTATUS_RELEASE;
        break;
    case CMediaEnum::EButtonStates::EN_BUTTON_STATE_LONG_PRESSED:
        eButtonStatus = mediaPresPlugin::eButtonStatus::BUTTONSTATUS_LONG_PRESS;
        break;
    case CMediaEnum::EButtonStates::EN_BUTTON_STATE_LONG_RELEASED:
        eButtonStatus = mediaPresPlugin::eButtonStatus::BUTTONSTATUS_LONG_RELEASE;
        break;
    default:
        //eButtonStatus = mediaPresPlugin::eButtonStatus::BUTTONSTATUS_UNKNOWN;
        //Default state is already unknown
        break;
    }

    return eButtonStatus;

}

void CMediaResourceImpl::toggleShuffleAsyncCb(const CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, result = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult.value_));
}

void CMediaResourceImpl::toggleRepeatAsyncCb(const CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, result = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult.value_));
}

void CMediaResourceImpl::seekToTimeAsyncCb(const CallStatus &eStatus, const MMPresTypes::eCallResult &eResult)
{
    m_bIsSeekRequestInProcess = false;
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, result = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult.value_));
}

void CMediaResourceImpl::playSongAsyncCb(const CallStatus &eStatus, const MMPresTypes::eCallResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    CPP_UNUSED(eResult);
    CPP_UNUSED(eStatus);
}

void CMediaResourceImpl::goToPreviousLevelAsyncCb(const CallStatus &status, const MMPresTypes::eCallResult &eResult, const uint64_t &uiNumResults, const uint32_t &uiSessionQueryID, const MMPresTypes::ePrevBrowseLevel &ePrevBrowseLevel, const string &strBreadcrumbPath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - CallStatus:%d eCallResult:%d strBreadcrumbPath:%s",__FUNCTION__,static_cast<int>(status),static_cast<int>(eResult),strBreadcrumbPath.c_str());
    CPP_UNUSED(eResult);

    if(status == CallStatus::SUCCESS)
    {
        if(ePrevBrowseLevel == MMPresTypes::ePrevBrowseLevel::PREVBROWSELEVEL_ROOT)
        {
            //Switch to previous screen
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Root browse level reached", __FUNCTION__);

            //Set current session ID to default
            setSessionQueryId(-1);

            if(m_pMediaEventProvider)
            {
                //This method call is not in use currently.
                m_pMediaEventProvider->setRootLevelBrowse();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Nested browse level", __FUNCTION__);

            if(m_pMediaEventProvider)
            {
                setSessionQueryId(uiSessionQueryID);

                m_pMediaEventProvider->updateBreadcrumbPath(strBreadcrumbPath);
                m_pMediaEventProvider->updateRequestedBrowseListSize(uiNumResults);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
            }
        }
    }
    else
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_MEDIA,"%s - 'goToPreviousLevelAsync' API request failed", __FUNCTION__);
    }
}

void CMediaResourceImpl::goToNowPlayingLevelAsyncCb(const CallStatus &eStatus, const MMPresTypes::eCallResult &eResult, const uint64_t &uiNumResults, const uint32_t &uiSessionQueryID, const string &strBreadcrumbpath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: status = %d, call result = %d, count = %d, sessionQueryID = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult), static_cast<int>(uiNumResults), uiSessionQueryID);

    if((eStatus == CallStatus::SUCCESS) && (MMPresTypes::eCallResult::CALLRESULT_OK == eResult))
    {
        if(uiNumResults > 0)
        {
            m_iNowPlayingSessionQueryId = uiSessionQueryID;

            if(m_pMediaEventProvider)
            {
                m_pMediaEventProvider->updateNowPlayingListSize(uiNumResults);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: - Count is 0 for preview list",__FUNCTION__);
        }
    }

    CPP_UNUSED(strBreadcrumbpath);
}

/*==================== Slot related methods ====================*/

void CMediaResourceImpl::getSlots()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    m_pManagerProxy->getSlotsAsync(std::bind(&CMediaResourceImpl::getSlotsAsyncCB,this, _1,_2));
}

void CMediaResourceImpl::getSlotsAsyncCB(const CallStatus &eStatus, const MMPresTypes::tSlotList &tSlotList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s = %d", __FUNCTION__, static_cast<int>(eStatus));

    if(CallStatus::SUCCESS == eStatus)
    {
        MMPresTypes::tSlotList::const_iterator listItr;

        for(listItr = tSlotList.begin();listItr != tSlotList.end();listItr++)
        {
            if(MMPresTypes::eSlotState::SLOTSTATE_READY == listItr->getSlotState())
            {
                if(MMPresTypes::eSlotType::SLOTTYPE_USB == listItr->getSlotType())
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s USB connected, slot Id = %d", __FUNCTION__, static_cast<int>(listItr->getSlotId()));
                    m_iUSBSlotID = listItr->getSlotId();
                }
                else if(MMPresTypes::eSlotType::SLOTTYPE_BLUETOOTH == listItr->getSlotType())
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s BT connected, slot Id = %d", __FUNCTION__, static_cast<int>(listItr->getSlotId()));
                    m_iBTSlotID = listItr->getSlotId();

                    m_iBTMajorVersion = listItr->getDevice().getBtstatus().getMajorVersion();
                    m_iBTMinorVersion = listItr->getDevice().getBtstatus().getMinorVersion();
                    MMPresTypes::eBTMediaProfile eBtType = listItr->getDevice().getBtstatus().getProfile();

                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  m_iBTMajorVersion=%d, m_iBTMinorVersion=%d, eBtType=%d", __FUNCTION__,m_iBTMajorVersion,m_iBTMinorVersion,static_cast<int>(eBtType));
                    if((1 == m_iBTMajorVersion ) && (3 < m_iBTMinorVersion) && ((MMPresTypes::eBTMediaProfile::AVRCP == eBtType) || (MMPresTypes::eBTMediaProfile::AVRCPA2DP == eBtType)))
                    {
                        m_bIsBTDeviceBrowsable = true;
                    }
                    else
                    {
                        m_bIsBTDeviceBrowsable = false;
                    }
                    getRemotePlayerCapabilitiesValue();
                }
                else if(MMPresTypes::eSlotType::SLOTTYPE_HDD == listItr->getSlotType())
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s HDD connected, slot Id = %d", __FUNCTION__, static_cast<int>(listItr->getSlotId()));
                    m_iHDDSlotID = listItr->getSlotId();
                }
                else
                {
                    //Do nothing
                }
                getSyncStateValue();
            }
        }
    }
    else
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_MEDIA,"%s - 'getSlots' API request failed", __FUNCTION__);
    }
}

void CMediaResourceImpl::onSlotUpdate(MMPresTypes::tSlot tSlotUpdates)
{
    int32_t iSlotType = static_cast<int32_t>(tSlotUpdates.getSlotType());
    int32_t iSlotState = static_cast<int32_t>(tSlotUpdates.getSlotState());

    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s = %d, slotState = %d", __FUNCTION__, iSlotType, iSlotState);

    if(MMPresTypes::eSlotState::SLOTSTATE_READY == iSlotState)
    {
        if(MMPresTypes::eSlotType::SLOTTYPE_USB == iSlotType)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s USB connected, slot Id = %d", __FUNCTION__,static_cast<int>(tSlotUpdates.getSlotId()));
            m_iUSBSlotID = tSlotUpdates.getSlotId();

            //Do nothing....await 'DeviceInfoItemsAttribute'
        }
        else if(MMPresTypes::eSlotType::SLOTTYPE_BLUETOOTH == iSlotType)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s BT media connected, slot Id = %d", __FUNCTION__, static_cast<int>(tSlotUpdates.getSlotId()));
            m_iBTSlotID = tSlotUpdates.getSlotId();

            m_iBTMajorVersion = tSlotUpdates.getDevice().getBtstatus().getMajorVersion();
            m_iBTMinorVersion = tSlotUpdates.getDevice().getBtstatus().getMinorVersion();
            MMPresTypes::eBTMediaProfile eBtType = tSlotUpdates.getDevice().getBtstatus().getProfile();

            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  m_iBTMajorVersion=%d, m_iBTMinorVersion=%d, eBtType=%d", __FUNCTION__,m_iBTMajorVersion,m_iBTMinorVersion,static_cast<int>(eBtType));

            //Browsing shall be supported if BT version is 1.4 and above
            if((1 == m_iBTMajorVersion ) && (3 < m_iBTMinorVersion) && ((MMPresTypes::eBTMediaProfile::AVRCP == eBtType) || (MMPresTypes::eBTMediaProfile::AVRCPA2DP == eBtType)))
            {
                m_bIsBTDeviceBrowsable = true;
            }
            else
            {
                m_bIsBTDeviceBrowsable = false;
            }
            getRemotePlayerCapabilitiesValue();
        }
        else if(MMPresTypes::eSlotType::SLOTTYPE_HDD == tSlotUpdates.getSlotType())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s HDD connected, slot Id = %d", __FUNCTION__, static_cast<int>(tSlotUpdates.getSlotId()));
            m_iHDDSlotID = tSlotUpdates.getSlotId();
        }
        else
        {
            // Do Nothing
        }

        getSyncStateValue();
    }
    else if(MMPresTypes::eSlotState::SLOTSTATE_EJECTED == iSlotState)
    {
        if(MMPresTypes::eSlotType::SLOTTYPE_USB == iSlotType)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s USB disconnected", __FUNCTION__);
            clearAvailableCategoriesMap(MMPresTypes::eSlotType::SLOTTYPE_USB);
        }
        else if(MMPresTypes::eSlotType::SLOTTYPE_BLUETOOTH == iSlotType)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s BT media disconnected", __FUNCTION__);
            clearAvailableCategoriesMap(MMPresTypes::eSlotType::SLOTTYPE_BLUETOOTH);
        }
        else
        {
            //Do nothing
        }
    }
    else
    {
        //Do nothing
    }
}

void CMediaResourceImpl::onUSBDeviceError(mediaPresPlugin::eUsbDeviceError eUsbSlotDeviceError)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s -USB device error: %d",__FUNCTION__, static_cast<int>(eUsbSlotDeviceError));

    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->updateUSBDeviceError(static_cast<int>(eUsbSlotDeviceError));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::onUsbPlaybackModeCb(mediaPresPlugin::eUsbPlaybackMode eUsbPlaybackMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s -USB playback mode: %d",__FUNCTION__, eUsbPlaybackMode.value_);

    setUSBPlayBackMode(eUsbPlaybackMode);
}

void CMediaResourceImpl::onBitRateAttributeCb(string strBitRate)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s - Bit rate: %s",__FUNCTION__, strBitRate.c_str());
    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->updateBitRate(strBitRate);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::onSamplingRateAttributeCb(string strSamplingRate)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s - Sampling rate: %s",__FUNCTION__, strSamplingRate.c_str());
    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->updateSamplingRate(strSamplingRate);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::onDeviceItemsInfoAttributeCb(mediaPresPlugin::sItemsInfo sCategoriesInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    setUSBDeviceInfo(sCategoriesInfo);
}

void CMediaResourceImpl::onVideoTestModeParametersAttributeCb(mediaPresPlugin::sVideoParameters sVideoTestModeParameters)
{
    //Video test mode parameters available here
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);
    m_objVideoParameters.strAudioCodec= sVideoTestModeParameters.getAudioCodec();
    m_objVideoParameters.strAudioSamplingRate = sVideoTestModeParameters.getAudioSamplingRate();
    m_objVideoParameters.strVideoCodec = sVideoTestModeParameters.getVideoCodec();
    m_objVideoParameters.strVideoFrameRate = sVideoTestModeParameters.getVideoFrameRate();
    string strVideoHeight = sVideoTestModeParameters.getVideoResolution().getVideoHeight();
    string strVideoWidth = sVideoTestModeParameters.getVideoResolution().getVideoWidth();
    m_objVideoParameters.strVideoResolution = strVideoHeight + "x" + strVideoWidth;
    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->updateVideoTestModeParameters();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::onBTMetaDataAvailabilityStatusAttributeCb(mediaPresPlugin::eAvailabilityStatus eMetaDataAvailablityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s eMetaDataAvailablityStatus:%d", __FUNCTION__,static_cast<int>(eMetaDataAvailablityStatus));

    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->updateBTMetaDataAvailabilityStatus(static_cast<int>(eMetaDataAvailablityStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::onMediaErrorAttributeCb(mediaPresPlugin::MediaErrorMap mapMediaError)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    for(auto mapIter:mapMediaError)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Media Error code: %d", __FUNCTION__, static_cast<int>(mapIter.second));
        if(mediaPresPlugin::eMediaError::MEDIAERROR_VIDEOCORRUPT == mapIter.second)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - %s", __FUNCTION__, "Corrupt video accessed");

            if(m_pMediaEventProvider)
            {
                m_pMediaEventProvider->corruptVideoAccessed();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
            }
        }
    }
}

int CMediaResourceImpl::getActiveSlotId()
{
    int iRet = 0;
    //FixMe: Currently using Magic Numbers for Ent Sources- USB(55), IPOD(82), BTAudio(65)
    if(m_iActiveEntSource == 55 ||  m_iActiveEntSource == 82)
    {
        iRet = m_iUSBSlotID;
    }
    else if(m_iActiveEntSource == 65)
    {
        iRet = m_iBTSlotID;
    }
    else if(m_iActiveEntSource == 54)
    {
        iRet = m_iHDDSlotID;
    }
    else
    {
        //Do nothing
    }
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s active source: %d slot id: %d",__FUNCTION__, m_iActiveEntSource, iRet);
    return iRet;
}

/*==================== Slot related methods - END ====================*/

/* =========================================== Browse methods start============================================================================ */

void CMediaResourceImpl::onBrowseCategoryInfoChanged(MMPresTypes::tDeviceBrowseCategoryList tBrowseCategoryInfoList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    MMPresTypes::tDeviceBrowseCategoryList::const_iterator listItr;

    for(listItr = tBrowseCategoryInfoList.begin();listItr != tBrowseCategoryInfoList.end();listItr++)
    {
        if(listItr->getSlotId() == m_iUSBSlotID)
        {
            //Do nothing....await 'DeviceItemsInfoAttribute.onChanged()' event

            /*
            parseBrowseCategoryMap(listItr->getCategoryInfo(), m_vectUSBAvailableCategories);
            if(m_pMediaEventProvider)
            {
                m_pMediaEventProvider->updateUSBCategories();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
            }
            */

            /*
            for(int iIndex = 0; iIndex < TOTAL_CATEGORIES; iIndex++)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - iIndex: %d, value: %d",__FUNCTION__, iIndex, static_cast<int>(m_vectUSBAvailableCategories[iIndex]));
            }
            */

        }
        else if(listItr->getSlotId() == m_iBTSlotID)
        {
            parseBrowseCategoryMap(listItr->getCategoryInfo(), m_vectBTAvailableCategories);

            if(m_pMediaEventProvider)
            {
                m_pMediaEventProvider->updateBTCategories();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
            }
        }
        else
        {
            //Do nothing
        }
    }
}

void CMediaResourceImpl::parseBrowseCategoryMap(const MMPresTypes::BrowseCategoryMap &objBrowseCategoryMap, vector<int> &vectAvailableCategories)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);

    for(auto outerIter:objBrowseCategoryMap)
    {
        MMPresTypes::eTitleContentType contentType = outerIter.first;

        if(contentType != MMPresTypes::eTitleContentType::TITLETYPE_UNKNOWN)
        {
            MMPresTypes::MetadataCountMap metadataCountMap = outerIter.second;

            for(auto innerIter:metadataCountMap)
            {
                //innerIter.first - metadata type
                //innerIter.second - value i.e. count of metadata (albums, artists, folders etc)
                vectAvailableCategories[decodeMetadataEnum(innerIter.first)] = innerIter.second;
            }
        }
        else
        {
            //Do nothing
        }
    }
}

MMPresTypes::eMetadataType CMediaResourceImpl::encodeMetadataEnum(int iMetdataType)
{
    /* Map HMI enum to service enum before sending the values
     * enum EMediaBrowseItem
    {
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
        BROWSEITEM_PODCAST          = 10
    };
    */

    switch(iMetdataType)
    {
    case 0:
        return MMPresTypes::eMetadataType::METADATATYPE_FOLDER;
        break;

    case 1: //songs
        return MMPresTypes::eMetadataType::METADATATYPE_TITLE;
        break;

    case 2:
        return MMPresTypes::eMetadataType::METADATATYPE_ALBUM;
        break;

    case 3:
        return MMPresTypes::eMetadataType::METADATATYPE_ARTIST;
        break;

    case 4:
        return MMPresTypes::eMetadataType::METADATATYPE_GENRE;
        break;

    case 5:
        return MMPresTypes::eMetadataType::METADTATATYPE_PLAYLIST;
        break;

    case 6: //pictures
        return MMPresTypes::eMetadataType::METADATATYPE_IMAGE;
        break;

    case 7:
        return MMPresTypes::eMetadataType::METADATATYPE_VIDEO;
        break;

    case 8: //itunes radio
        return MMPresTypes::eMetadataType::METADATATYPE_KEYWORDS;
        break;

    case 9:
        return MMPresTypes::eMetadataType::METADTATATYPE_AUDIOBOOK;
        break;

    case 10:
        return MMPresTypes::eMetadataType::METADTATATYPE_PODCAST;
        break;

    case 11:
        return MMPresTypes::eMetadataType::METADTATATYPE_EPISODE;
        break;

    default:
        LOG_ERROR(Log::e_LOG_CONTEXT_MEDIA,"%s - Wrong metadata type from HMI",__FUNCTION__);
        return MMPresTypes::eMetadataType::METADATATYPE_UNKNOWN;
        break;
    }
}

int CMediaResourceImpl::decodeMetadataEnum(MMPresTypes::eMetadataType eMetdataType)
{
    /* Map HMI enum to service enum before sending the values
     * enum EMediaBrowseItem
    {
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
        BROWSEITEM_PODCAST          = 10
    };
    */

    switch(eMetdataType)
    {
    case MMPresTypes::eMetadataType::METADATATYPE_FOLDER:
        return 0;
        break;

    case MMPresTypes::eMetadataType::METADATATYPE_TITLE: //songs
        return 1;
        break;

    case MMPresTypes::eMetadataType::METADATATYPE_ALBUM:
        return 2;
        break;

    case MMPresTypes::eMetadataType::METADATATYPE_ARTIST:
        return 3;
        break;

    case MMPresTypes::eMetadataType::METADATATYPE_GENRE:
        return 4;
        break;

    case MMPresTypes::eMetadataType::METADTATATYPE_PLAYLIST:
        return 5;
        break;

    case MMPresTypes::eMetadataType::METADATATYPE_IMAGE: //pictures
        return 6;
        break;

    case MMPresTypes::eMetadataType::METADATATYPE_VIDEO:
        return 7;
        break;

    case MMPresTypes::eMetadataType::METADATATYPE_KEYWORDS: //itunes radio
        return 8;
        break;

    case MMPresTypes::eMetadataType::METADTATATYPE_AUDIOBOOK:
        return 9;
        break;

    case MMPresTypes::eMetadataType::METADTATATYPE_PODCAST:
        return 10;
        break;

    case MMPresTypes::eMetadataType::METADTATATYPE_EPISODE:
        return 11;
        break;

    default:
        LOG_ERROR(Log::e_LOG_CONTEXT_MEDIA,"%s - Unused metadata type received from Media service",__FUNCTION__);
        return 1; //songs
        break;
    }
}

MMPresTypes::eTitleContentType CMediaResourceImpl::encodeContentTypeEnum(MMPresTypes::eMetadataType eMetdataType)
{
    switch(eMetdataType)
    {
    case MMPresTypes::eMetadataType::METADATATYPE_VIDEO: //Videos
        return MMPresTypes::eTitleContentType::TITLETYPE_VIDEO;
        break;

    case MMPresTypes::eMetadataType::METADATATYPE_IMAGE:
        return MMPresTypes::eTitleContentType::TITLETYPE_IMAGE;
        break;

    default: //Songs
        return MMPresTypes::eTitleContentType::TITLETYPE_AUDIO;
        break;
    }
}

void CMediaResourceImpl::getCategoryRoot(int iType, bool bIsVRRequest)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    MMPresTypes::eMetadataType resultType = encodeMetadataEnum(iType);
    MMPresTypes::eTitleContentType contentMask = encodeContentTypeEnum(resultType);

    MMPresTypes::eSessionQueryTypes query;
    MMPresTypes::FilterIDMap filterIDs;

    if(bIsVRRequest)
    {
        query = MMPresTypes::eSessionQueryTypes::SESSION_QUERY_VR_BROWSE;
        MMPresTypes::eMetadataType filterIdKey = encodeMetadataEnum(iType);
        filterIDs[filterIdKey] = -1;
    }
    else if(MMPresTypes::eMetadataType::METADATATYPE_FOLDER == resultType)
    {
        //FS_Browse while requesting folders - deafult value is already FS_Browse
        //query = MMPresTypes::eSessionQueryTypes::SESSION_QUERY_FS_BROWSE;
    }
    else
    {
        //Metadata_Browse while requesting anything other than folders
        query = MMPresTypes::eSessionQueryTypes::SESSION_QUERY_METADATA_BROWSE;
    }

    MMPresTypes::FilterMap filters;
    uint32_t metadataAttributes = 0;
    uint32_t metadataCountTypes = 0;
    bool resetPrevious = false;
    bool autoUpdateEnabled = false;

    uint8_t slotId = getActiveSlotId();

    if(m_bBrowserAvailable)
    {
        m_pBrowserProxy->setSessionQueryAsync(m_iBrowseSessionId,slotId,filterIDs,filters,resultType,metadataAttributes,metadataCountTypes,query,resetPrevious,autoUpdateEnabled,contentMask,std::bind(&CMediaResourceImpl::sessionQueryAsyncCb,this, _1,_2,_3,_4,_5));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_bBrowserAvailable is not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::getCategorySubLevel(int iFileID, int iMetadataType, int iQueryType, bool bIsVRRequest)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    MMPresTypes::FilterIDMap filterId;
    MMPresTypes::eMetadataType filterIdKey = encodeMetadataEnum(iMetadataType);
    filterId[filterIdKey] = iFileID;

    MMPresTypes::FilterMap filters;

    MMPresTypes::eMetadataType resultType;
    if(MMPresTypes::eMetadataType::METADATATYPE_GENRE == filterIdKey)
    {
        resultType = MMPresTypes::eMetadataType::METADATATYPE_ARTIST;
    }
    else if(MMPresTypes::eMetadataType::METADATATYPE_ARTIST == filterIdKey)
    {
        resultType = MMPresTypes::eMetadataType::METADATATYPE_ALBUM;
    }
    else if((MMPresTypes::eMetadataType::METADATATYPE_ALBUM  == filterIdKey) || (MMPresTypes::eMetadataType::METADTATATYPE_PLAYLIST == filterIdKey))
    {
        resultType = MMPresTypes::eMetadataType::METADATATYPE_TITLE;
    }
    else if(MMPresTypes::eMetadataType::METADATATYPE_FOLDER == filterIdKey)
    {
        resultType = MMPresTypes::eMetadataType::METADATATYPE_FILE;
    }
    else if(MMPresTypes::eMetadataType::METADTATATYPE_PODCAST == filterIdKey)
    {
        resultType = MMPresTypes::eMetadataType::METADTATATYPE_EPISODE;
    }
    else
    {
        //Do nothing
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Wrong category requested from HMI",__FUNCTION__);
        resultType = MMPresTypes::eMetadataType::METADATATYPE_UNKNOWN;
    }

    uint32_t metadataAttributes = 0;
    uint32_t metadataCountTypes = 0;
    MMPresTypes::eSessionQueryTypes query;

    if(bIsVRRequest)
    {
        query = MMPresTypes::eSessionQueryTypes::SESSION_QUERY_VR_BROWSE;
    }
    else if((MMPresTypes::eMetadataType::METADATATYPE_FOLDER == filterIdKey) || (MMPresTypes::eMetadataType::METADTATATYPE_PLAYLIST == filterIdKey && MMPresTypes::eFileSystemContentType::FS_CONTENT_TYPE_PLAYLIST == iQueryType))
    {
        query = MMPresTypes::eSessionQueryTypes::SESSION_QUERY_FS_BROWSE;
        resultType = MMPresTypes::eMetadataType::METADATATYPE_FILE;
    }
    else
    {
        query = MMPresTypes::eSessionQueryTypes::SESSION_QUERY_METADATA_BROWSE;
    }

    bool resetPrevious = false;
    bool autoUpdateEnabled = false;
    uint32_t contentMask = 1;

    uint8_t slotId = getActiveSlotId();

    if(m_bBrowserAvailable)
    {
        m_pBrowserProxy->setSessionQueryAsync(m_iBrowseSessionId,slotId,filterId,filters,resultType,metadataAttributes,metadataCountTypes,query,resetPrevious,autoUpdateEnabled,contentMask,std::bind(&CMediaResourceImpl::sessionQueryAsyncCb,this, _1,_2,_3,_4,_5));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_bBrowserAvailable is not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::playSong(int iSongIndex, bool isPreviewReq)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    MMPresTypes::FilterIDMap filterId;
    filterId[MMPresTypes::eMetadataType::METADATATYPE_FILE] = iSongIndex;

    uint32_t uiSessionID = (isPreviewReq) ? m_iPreviewBrowseSessionId : m_iBrowseSessionId;

    if(m_bBrowserAvailable)
    {
        m_pBrowserProxy->playSessionAsync(uiSessionID,filterId,std::bind(&CMediaResourceImpl::playSongAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_bBrowserAvailable is not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::goToPreviousLevel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(m_bBrowserAvailable)
    {
        m_pBrowserProxy->gotoPreviousSessionQueryAsync(m_iBrowseSessionId,std::bind(&CMediaResourceImpl::goToPreviousLevelAsyncCb,this, _1,_2,_3,_4,_5,_6));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_bBrowserAvailable is not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::goToNowPlayingLevel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    MMPresTypes::eMetadataType resultType = MMPresTypes::eMetadataType::METADATATYPE_TITLE;
    MMPresTypes::eTitleContentType contentMask = MMPresTypes::eTitleContentType::TITLETYPE_AUDIO;
    MMPresTypes::eSessionQueryTypes query = MMPresTypes::eSessionQueryTypes::SESSION_QUERY_NOWPLAYINGLIST_BROWSE;

    MMPresTypes::FilterIDMap filterIDs;
    MMPresTypes::FilterMap filters;
    uint32_t metadataAttributes = 0;
    uint32_t metadataCountTypes = 0;
    bool resetPrevious = false;
    bool autoUpdateEnabled = false;

    uint8_t slotId = getActiveSlotId();

    if(m_bBrowserAvailable)
    {
        m_pBrowserProxy->setSessionQueryAsync(m_iPreviewBrowseSessionId,slotId,filterIDs,filters,resultType,metadataAttributes,metadataCountTypes,query,resetPrevious,autoUpdateEnabled,contentMask,std::bind(&CMediaResourceImpl::goToNowPlayingLevelAsyncCb,this, _1,_2,_3,_4,_5));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_bBrowserAvailable is not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::mediaBrowserStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(eStatus == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        m_bBrowserAvailable = true;
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"MediaResourceImpl::mediaBrowserStatusCb Browser available");
        openBrowseSession();
        openPreviewBrowseSession();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Media browser is not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::mediaPluginStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(eStatus == CommonAPI::AvailabilityStatus::AVAILABLE)
    {
        m_bPluginAvailable = true;
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Media plugin available", __FUNCTION__);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Media plugin is not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::openBrowseSession()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bBrowserAvailable)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"MediaResourceImpl::openBrowseSession m_bBrowserAvailable");
        m_pBrowserProxy->openSessionAsync(std::bind(&CMediaResourceImpl::openBrowseSessionAsyncCb,this, _1,_2,_3));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_bBrowserAvailable is not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::openBrowseSessionAsyncCb(const CallStatus &status, const uint32_t &sessionId, const MMPresTypes::eCallResult &result)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: status = %d eCallResult = %d",__FUNCTION__,static_cast<int>(status),static_cast<int>(result));

    if((CallStatus::SUCCESS == status) && (MMPresTypes::eCallResult::CALLRESULT_OK == result))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"MediaResourceImpl::openBrowseSessionAsyncCb got sessionId = %d",static_cast<int>(sessionId));
        m_iBrowseSessionId = sessionId;
        if(m_pMediaEventProvider)
        {
            m_pMediaEventProvider->updateBrowseSessionCreation();
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::openBrowseSessionAsyncCb, call status/result is not matched, status: %d, result: %d", static_cast<int>(status), static_cast<int>(result.value_));
    }
}

void CMediaResourceImpl::openPreviewBrowseSession()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bBrowserAvailable)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_bBrowserAvailable", __FUNCTION__);
        m_pBrowserProxy->openSessionAsync(std::bind(&CMediaResourceImpl::openPreviewBrowseSessionAsyncCb,this, _1,_2,_3));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_bBrowserAvailable is not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::openPreviewBrowseSessionAsyncCb(const CallStatus &status, const uint32_t &sessionId, const MMPresTypes::eCallResult &result)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: status = %d eCallResult = %d",__FUNCTION__,static_cast<int>(status),static_cast<int>(result));

    if((CallStatus::SUCCESS == status) && (MMPresTypes::eCallResult::CALLRESULT_OK == result))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - got sessionId = %d", __FUNCTION__, static_cast<int>(sessionId));
        m_iPreviewBrowseSessionId = sessionId;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s, call status/result is not matched, status: %d, result: %d", __FUNCTION__, static_cast<int>(status), static_cast<int>(result.value_));
    }
}

void CMediaResourceImpl::sessionQueryAsyncCb(const CallStatus &status, const MMPresTypes::eCallResult &result, const uint64_t &numResults, const uint32_t &sessionQueryID, const string &strBreadcrumbpath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: status = %d, call result = %d, count = %d",__FUNCTION__, static_cast<int>(status), static_cast<int>(result), static_cast<int>(numResults));

    if((status == CallStatus::SUCCESS) && (MMPresTypes::eCallResult::CALLRESULT_OK == result))
    {
        if(numResults > 0)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: sessionQueryID = %d, breadcrumb path = %s, result count = %d",__FUNCTION__,static_cast<int>(sessionQueryID),strBreadcrumbpath.c_str(),static_cast<int>(numResults));
            setSessionQueryId(sessionQueryID);

            if(m_pMediaEventProvider)
            {
                m_pMediaEventProvider->updateRequestedBrowseListSize(numResults);
                m_pMediaEventProvider->updateBreadcrumbPath(strBreadcrumbpath);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: - Count is 0 for requested list",__FUNCTION__);

            if(m_pMediaEventProvider)
            {
                m_pMediaEventProvider->updateBreadcrumbPath(strBreadcrumbpath);
                m_pMediaEventProvider->updateBrowseItemEmpty();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
            }
        }
    }
}

void CMediaResourceImpl::clearAvailableCategoriesMap(MMPresTypes::eSlotType eSlotType)
{
    /* Below enum is just for reference from ProjectBase
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
   */

    if(MMPresTypes::eSlotType::SLOTTYPE_USB == eSlotType)
    {
        m_vectUSBAvailableCategories.clear();

        for(int iIndex = 0; iIndex < TOTAL_CATEGORIES; iIndex++)
        {
            m_vectUSBAvailableCategories.push_back(-1); //default - not available
        }
    }
    else if(MMPresTypes::eSlotType::SLOTTYPE_BLUETOOTH == eSlotType)
    {
        m_vectBTAvailableCategories.clear();

        for(int iIndex = 0; iIndex < TOTAL_CATEGORIES; iIndex++)
        {
            m_vectBTAvailableCategories.push_back(-1); //default - not available
        }
    }
    else
    {
        //Do nothing
    }
}

void CMediaResourceImpl::setSyncState(MMPresTypes::SyncMap mSyncMap)
{
    for(auto mapIter:mSyncMap)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s slot id = %d | syncState = %d", __FUNCTION__,  mapIter.first, static_cast<int>(mapIter.second));

        if(m_iUSBSlotID == mapIter.first)
        {
            m_eUSBSlotSyncState = mapIter.second;
        }
        else if(m_iBTSlotID == mapIter.first)
        {
            m_eBTSlotSyncState = mapIter.second;
        }
        else
        {
            //Do nothing
        }

        if(m_pMediaEventProvider)
        {
            m_pMediaEventProvider->updateSyncState();
        }
    }
}

void CMediaResourceImpl::setRemotePlayerCapabilities(MMPresTypes::tRemotePlayerCapability eCapabilityInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : slotId:%d | capability:%d",__FUNCTION__,static_cast<int>(eCapabilityInfo.getSlotId()),static_cast<int>(eCapabilityInfo.getCapability()));
    if(m_iBTSlotID == static_cast<int>(eCapabilityInfo.getSlotId()))
    {
        /* Play/Pause and Next/Prev shall be supported by default if BT version is 1.3 and above (irrespective of remote player capab) */

        //Check for Play/Pause Feature
        if((eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_PLAY) != 0 || (eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_PAUSE) != 0 || ((1 == m_iBTMajorVersion ) && (2 < m_iBTMinorVersion)))
        {
            m_objRemotePlayerCapabilities.bIsPlayPauseSupported = true;
        }
        else
        {
            m_objRemotePlayerCapabilities.bIsPlayPauseSupported = false;
        }

        //Check for Next/Prev Feature
        if((eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_NEXT) != 0 || (eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_PREVIOUS) != 0 || ((1 == m_iBTMajorVersion ) && (2 < m_iBTMinorVersion)))
        {
            m_objRemotePlayerCapabilities.bIsNextPrevSupported = true;
        }
        else
        {
            m_objRemotePlayerCapabilities.bIsNextPrevSupported = false;
        }

        //Check for FFwd/FRwd Feature
        if((eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_FASTFORWARD) != 0 || (eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_FASTREWIND) != 0)
        {
            m_objRemotePlayerCapabilities.bIsFwdRwdSupported = true;
        }
        else
        {
            m_objRemotePlayerCapabilities.bIsFwdRwdSupported = false;
        }

        //Check for Random Feature
        if((eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_SHUFFLE) != 0 || (eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_UNSHUFFLE) != 0)
        {
            m_objRemotePlayerCapabilities.bIsRandomSupported = true;
        }
        else
        {
            m_objRemotePlayerCapabilities.bIsRandomSupported = false;
        }

        //Check for Repeat Feature
        if((eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_REPEATOFF) != 0 || (eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_REPEATSINGLE) != 0 || (eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_REPEATALL) != 0)
        {
            m_objRemotePlayerCapabilities.bIsRepeatSupported = true;
        }
        else
        {
            m_objRemotePlayerCapabilities.bIsRepeatSupported = false;
        }

        //Check for Browse feature
        if(((eCapabilityInfo.getCapability() & REMOTEPLAYERCAP_BROWSING) != 0) && m_bIsBTDeviceBrowsable)
        {
            m_objRemotePlayerCapabilities.bIsBrowseSupported = true;
        }
        else
        {
            m_objRemotePlayerCapabilities.bIsBrowseSupported = false;
        }

        m_pMediaEventProvider->updateRemotePlayerCapabilities();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s RemoteCapabitlities received for slot other than BT",__FUNCTION__);
    }
}

void CMediaResourceImpl::getRemotePlayerCapabilitiesValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bIsMediaAvailable)
    {
        m_pPlayerProxy->getRemotePlayerCapabilityAttribute().getValueAsync(std::bind(&CMediaResourceImpl::getRemotePlayerCapabilitiesValueCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::getSyncStateValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bIsMediaAvailable)
    {
        m_pPlayerProxy->getSyncStatusAttribute().getValueAsync(std::bind(&CMediaResourceImpl::getSyncStateValueCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::setShuffleState(MMPresTypes::eShuffleMode eShuffleMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Shuffle Mode = %d", __FUNCTION__, eShuffleMode.value_);

    //TML program only supports ALL and OFF shuffle modes
    if((MMPresTypes::eShuffleMode::SHUFFLE_OFF == eShuffleMode) || (MMPresTypes::eShuffleMode::SHUFFLE_ALL == eShuffleMode))
    {
        if(m_pMediaEventProvider)
        {
            m_pMediaEventProvider->shuffleModeUpdated(eShuffleMode);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
        }
    }
    else
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_MEDIA,"%s - Invalid shuffle mode received from service", __FUNCTION__);
    }
}

void CMediaResourceImpl::setRepeatState(MMPresTypes::eRepeatMode eRepeatMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Repeat Mode = %d", __FUNCTION__, eRepeatMode.value_);

    //TML program supports ALL, OFF, Song and Folder repeat modes
    if((MMPresTypes::eRepeatMode::REPEAT_OFF == eRepeatMode) || (MMPresTypes::eRepeatMode::REPEAT_ALL == eRepeatMode)
            || (MMPresTypes::eRepeatMode::REPEAT_SONG == eRepeatMode) || (MMPresTypes::eRepeatMode::REPEAT_FOLDER == eRepeatMode))
    {
        if(m_pMediaEventProvider)
        {
            m_pMediaEventProvider->repeatModeUpdated((eRepeatMode));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
        }
    }
    else
    {
        LOG_ERROR(Log::e_LOG_CONTEXT_MEDIA,"%s - Invalid repeat mode received from service", __FUNCTION__);
    }
}

void CMediaResourceImpl::setUSBPlayBackMode(mediaPresPlugin::eUsbPlaybackMode eUsbPlaybackMode)
{
    if(m_pMediaEventProvider)
    {
        m_pMediaEventProvider->updateUSBPlayBackMode(static_cast<int>(eUsbPlaybackMode));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
    }
}

void CMediaResourceImpl::setUSBDeviceInfo(mediaPresPlugin::sItemsInfo sCategoriesInfo)
{
    /*
     * This event is only applicable for devices connected to USB slot
    */

    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - USB device info received",__FUNCTION__);

    int iContentType = 1; //Default value - empty device

    int iAudioCount = sCategoriesInfo.getTotalAudioItems();
    int iVideoCount = sCategoriesInfo.getTotalVideoItems();
    int iImagesCount = sCategoriesInfo.getTotalImageItems();

    /* Below enum is just for reference from ProjectBase
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
        BROWSEITEM_END              = 12
    };
   */

    if(iAudioCount < 0)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Default Device Items Info received | AudioCount: %d", __FUNCTION__, iAudioCount);
    }
    else
    {
        /*
         * Set artists, albums and genres to iAudioCount to indicate their availability
         * Service does not sends seperate counts for Artists, Albums and Genres
         */
        m_vectUSBAvailableCategories[1] = iAudioCount;
        m_vectUSBAvailableCategories[2] = iAudioCount;
        m_vectUSBAvailableCategories[3] = iAudioCount;
        m_vectUSBAvailableCategories[4] = iAudioCount;

        //Check Playlists count
        m_vectUSBAvailableCategories[5] = sCategoriesInfo.getTotalPlaylistItems();

        if(m_iActiveEntSource == 55) //USB is 55
        {
            //Check Folders count
            m_vectUSBAvailableCategories[0] = sCategoriesInfo.getTotalFolderItems();

            //Check Images count
            m_vectUSBAvailableCategories[6] = iImagesCount;

            //Check Videos count
            m_vectUSBAvailableCategories[7] = iVideoCount;
        }
        else if(m_iActiveEntSource == 82) //IPOD is 82
        {
            //Check iTunes Radio count
            m_vectUSBAvailableCategories[8] = sCategoriesInfo.getTotalITunesRadioItems();

            //Check Audiobooks count
            m_vectUSBAvailableCategories[9] = sCategoriesInfo.getTotalAudiobookItems();

            //Check Podcast count
            m_vectUSBAvailableCategories[10] = sCategoriesInfo.getTotalPodcastItems();
        }

        if(m_pMediaEventProvider)
        {
            m_pMediaEventProvider->updateUSBCategories();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
        }

        /*
    enum EMediaContentType
    {
        CONTENTTYPE_E = 1,  //Empty Device
        CONTENTTYPE_S = 2,  //Device with only songs
        CONTENTTYPE_V = 3,  //Device with only videos
        CONTENTTYPE_I = 4,  //Device with only Images
        CONTENTTYPE_SV = 5, //Device with songs and videos
        CONTENTTYPE_SI = 6, //Device with songs and images
        CONTENTTYPE_VI = 7, //Device with videos and images
        CONTENTTYPE_SVI = 8 //Device with songs, videos and images
    };
    */

        //Reordered the if checks to ensure high probablity possibilities to be on top
        if((iAudioCount > 0) && (iImagesCount <= 0) && (iVideoCount <= 0))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : USB with only Songs", __FUNCTION__);
            iContentType = 2;
        }
        else if((iAudioCount > 0) && (iImagesCount > 0) && (iVideoCount <= 0))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : USB with Songs and Images", __FUNCTION__);
            iContentType = 6;
        }
        else if((iAudioCount > 0) && (iVideoCount > 0) && (iImagesCount <= 0))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : USB with Songs and Videos", __FUNCTION__);
            iContentType = 5;
        }
        else if((iAudioCount > 0) && (iVideoCount > 0) && (iImagesCount > 0))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : USB with Songs, Videos and Images connected", __FUNCTION__);
            iContentType = 8;
        }
        else if((iImagesCount > 0) && (iVideoCount > 0) && (iAudioCount <= 0))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : USB with Images and Videos", __FUNCTION__);
            iContentType = 7;
        }
        else if((iImagesCount > 0) && (iVideoCount <= 0) && (iAudioCount <= 0))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : USB with only Images", __FUNCTION__);
            iContentType = 4;
        }
        else if((iVideoCount > 0) && (iImagesCount <= 0) && (iAudioCount <= 0))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : USB with only Videos", __FUNCTION__);
            iContentType = 3;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : Empty USB Connected", __FUNCTION__);
            iContentType = 1;
        }


        //Need this log always hence set to WARNING type
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - USB slot content type: %d", __FUNCTION__, iContentType);

        //Send content type to Media adaptor
        if(m_pMediaEventProvider)
        {
            m_pMediaEventProvider->updateContentType(iContentType);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"MediaEventProvider is null");
        }

    }

}

void CMediaResourceImpl::setSessionQueryId(int iSessionQueryId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : iSessionQueryId: %d",__FUNCTION__,iSessionQueryId);
    m_iSessionQueryId = iSessionQueryId;

    //Resetting index to be highlighted
    m_iIndexHighlighted = -1;
}

void CMediaResourceImpl::getCurrentTrackIndex(uint32_t iBrowseSessionId, uint32_t iSessionQueryId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bIsMediaAvailable)
    {
        m_pPluginProxy->getCurrentTrackIndexAsync(iBrowseSessionId,iSessionQueryId,std::bind(&CMediaResourceImpl::getCurrentTrackIndexAsyncCb, this, _1, _2, _3, _4, _5));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: CMediaResourceImpl::mediaSeriveStatusCb Proxy not available",__FUNCTION__);
    }
}

void CMediaResourceImpl::handleVideoSurface(bool bVideoSurfaceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Request - Video surface status: %d", __FUNCTION__, bVideoSurfaceStatus);

    mediaPresPlugin::eVideoSurfaceDisplayStatus eVidSurfaceStatus;

    if(bVideoSurfaceStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Show video surface request sent.", __FUNCTION__);
        eVidSurfaceStatus = mediaPresPlugin::eVideoSurfaceDisplayStatus::VIDEOSURFACE_SHOW;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Hide video surface request sent.", __FUNCTION__);
        //eVidSurfaceStatus = mediaPresPlugin::eVideoSurfaceDisplayStatus::VIDEOSURFACE_HIDE;
        //Default value of the variable is already '_HIDE'
    }

    if(m_bPluginAvailable)
    {
        m_pPluginProxy->videoSurfaceControlAsync(eVidSurfaceStatus, std::bind(&CMediaResourceImpl::videoSurfaceControlAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA, "%s: CMediaResourceImpl::handleVideoSurface, media plugin proxy not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::videoSurfaceControlAsyncCb(const CallStatus& eStatus, const mediaPresPlugin::eCallResult& eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: CallStatus = %d, result = %d", __FUNCTION__, static_cast<int>(eStatus), eResult.value_);
}

void CMediaResourceImpl::getCurrentTrackIndexAsyncCb(const CallStatus &status, const mediaPresPlugin::eCallResult &result, const uint32_t &iSessionQueryID, const bool &bHighlight, const uint64_t &iTrackIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: status:%d, eCallResult:%d, iSessionQueryID:%u, bHighlight:%d, iTrackIndex:%llu",__FUNCTION__,static_cast<int>(status),static_cast<int>(result),iSessionQueryID,bHighlight,iTrackIndex);

    if((CallStatus::SUCCESS == status) && (mediaPresPlugin::eCallResult::CALLRESULT_OK == result))
    {
        int _iSessionQueryID = static_cast<int>(iSessionQueryID);//cast the unsigned int to an int since it may store a -1 value
        if(m_iSessionQueryId == _iSessionQueryID)
        {
            if(m_pMediaEventProvider)
            {
                m_pMediaEventProvider->updateNowPlayingPointer(m_iIndexHighlighted,iTrackIndex-1);
                m_iIndexHighlighted = iTrackIndex-1;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: MediaEventProvider is null",__FUNCTION__);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: sessionQueryID did not match the current m_uiSessionQueryId: %d",__FUNCTION__,m_iSessionQueryId);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: getCurrentTrackIndex request was not successful",__FUNCTION__);
    }
}

void CMediaResourceImpl::getShuffleState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bIsMediaAvailable)
    {
        m_pPlayerProxy->getShuffleModeAttribute().getValueAsync(std::bind(&CMediaResourceImpl::getShuffleStateCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::getRepeatState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bIsMediaAvailable)
    {
        m_pPlayerProxy->getRepeatModeAttribute().getValueAsync(std::bind(&CMediaResourceImpl::getRepeatStateCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::nextFolder()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bIsMediaAvailable)
    {
        m_pPlayerProxy->nextFolderAsync(std::bind(&CMediaResourceImpl::nextFolderAsyncCb,this,_1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::previousFolder()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bIsMediaAvailable)
    {
        m_pPlayerProxy->previousFolderAsync(MMPresTypes::startIndexOption::HEAD,std::bind(&CMediaResourceImpl::previousFolderAsyncCb,this,_1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::getUSBPlaybackMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bPluginAvailable)
    {
        m_pPluginProxy->getUsbPlaybackModeAttribute().getValueAsync(std::bind(&CMediaResourceImpl::getUsbPlaybackModeCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::getDeviceItemsInfoAttribute()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bPluginAvailable)
    {
        m_pPluginProxy->getDeviceItemsInfoAttribute().getValueAsync(std::bind(&CMediaResourceImpl::getDeviceItemsInfoAttributeCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::mediaSeriveStatusCb Proxy not available");
    }
}

void CMediaResourceImpl::getShuffleStateCb(const CallStatus &eStatus, MMPresTypes::eShuffleMode eShuffleValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s callStatus: %d | eShuffleValue: %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eShuffleValue));
    if(eStatus == CallStatus::SUCCESS)
    {
        setShuffleState(eShuffleValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s getShuffleModeAttribute not succesful",__FUNCTION__);
    }
}

void CMediaResourceImpl::getRepeatStateCb(const CallStatus &eStatus, MMPresTypes::eRepeatMode eRepeatValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s callStatus: %d | eShuffleValue: %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eRepeatValue));
    if(eStatus == CallStatus::SUCCESS)
    {
        setRepeatState(eRepeatValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s getRepeatModeAttribute not succesful",__FUNCTION__);
    }
}

void CMediaResourceImpl::getUsbPlaybackModeCb(const CallStatus &eStatus, mediaPresPlugin::eUsbPlaybackMode eUsbPlaybackMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s -USB playback mode: %d",__FUNCTION__, eUsbPlaybackMode.value_);

    if(eStatus == CallStatus::SUCCESS)
    {
        setUSBPlayBackMode(eUsbPlaybackMode);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s getUsbPlaybackModeAttribute call not succesful",__FUNCTION__);
    }
}

void CMediaResourceImpl::getDeviceItemsInfoAttributeCb(const CallStatus &eStatus, mediaPresPlugin::sItemsInfo sCategoriesInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);

    if(eStatus == CallStatus::SUCCESS)
    {
        setUSBDeviceInfo(sCategoriesInfo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s getDeviceItemsInfoAttributeCb call not succesful",__FUNCTION__);
    }
}

void CMediaResourceImpl::getRemotePlayerCapabilitiesValueCb(const CallStatus &eStatus, MMPresTypes::tRemotePlayerCapability value)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s callStatus: %d | Capability: %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(value.getCapability()));
    if(eStatus == CallStatus::SUCCESS)
    {
        setRemotePlayerCapabilities(value);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s getRemotePlayerCapabilityAttribute not succesful",__FUNCTION__);
    }
}

void CMediaResourceImpl::getSyncStateValueCb(const CallStatus &eStatus, MMPresTypes::SyncMap value)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s callStatus: %d",__FUNCTION__,static_cast<int>(eStatus));
    if(eStatus == CallStatus::SUCCESS)
    {
        setSyncState(value);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s getSyncStatusAttribute not succesful",__FUNCTION__);
    }
}

void CMediaResourceImpl::nextFolderAsyncCb(const CallStatus &eStatus, const MMPresTypes::eMediaError &eMediaError)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, mediaError = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eMediaError.value_));
}

void CMediaResourceImpl::previousFolderAsyncCb(const CallStatus &eStatus, const MMPresTypes::eMediaError &eMediaError)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, mediaError = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eMediaError.value_));
}

void CMediaResourceImpl::updateRvcStateAsyncCb(const CallStatus &eStatus, const mediaPresPlugin::eCallResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s status = %d, result = %d",__FUNCTION__,static_cast<int>(eStatus),static_cast<int>(eResult.value_));
}

void CMediaResourceImpl::fetchItems(uint iStartIndex, uint iCount, bool isPreviewReq)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    int uiSessionQueryId = (isPreviewReq) ? m_iNowPlayingSessionQueryId : m_iSessionQueryId;
    fetchRequestedData(uiSessionQueryId, iStartIndex, iCount, isPreviewReq);
}

void CMediaResourceImpl::updateRvcState(bool bRvcStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - rvc status: %d",__FUNCTION__, bRvcStatus);

    if(m_bPluginAvailable)
    {
        m_pPluginProxy->updateRvcStateAsync(bRvcStatus, std::bind(&CMediaResourceImpl::updateRvcStateAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaResourceImpl::updateRvcState media plugin proxy not available");
    }
}

void CMediaResourceImpl::fetchRequestedData(uint32_t sessionQueryId, uint64_t startIndex, uint64_t count, bool isPreviewReq)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_bBrowserAvailable)
    {
        uint32_t uiSessionID = (isPreviewReq) ? m_iPreviewBrowseSessionId : m_iBrowseSessionId;
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: uiSessionID = %d, sessionQueryId = %d ,startIndex = %d,count = %d",__FUNCTION__,static_cast<int>(uiSessionID), static_cast<int>(sessionQueryId),static_cast<int>(startIndex),static_cast<int>(count));
        m_pBrowserProxy->setSessionQueryWindowAsync(uiSessionID,sessionQueryId,startIndex,count,std::bind(&CMediaResourceImpl::fetchRequestedDataAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_bBrowserAvailable is not available", __FUNCTION__);
    }
}

void CMediaResourceImpl::fetchRequestedDataAsyncCb(const CallStatus &status, const MMPresTypes::eCallResult &result)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: status = %d eCallResult=%d",__FUNCTION__,static_cast<int>(status),static_cast<int>(result));
    CPP_UNUSED(result);
}

void CMediaResourceImpl::onRequestedData(uint32_t sessionID, uint32_t sessionQueryID, MMPresTypes::eQueryStatus status, uint64_t startIndex, uint64_t count, MMPresTypes::MetadataItemList itemList, bool windowContainsCurrentlyPlayingTrack, uint64_t itemIndexTobeHighlighted)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: sessionID:%u | sessionQueryID:%u | startIndex:%Iu | count:%Iu | itemIndexTobeHighlighted:%Iu",__FUNCTION__,sessionID,sessionQueryID,startIndex,count,itemIndexTobeHighlighted);

    CPP_UNUSED(status);

    int iSessionID = static_cast<int>(sessionID);//cast the unsigned int to an int since it may store a -1 value
    int iSessionQueryID = static_cast<int>(sessionQueryID);//cast the unsigned int to an int since it may store a -1 value
    //Receieved Browsing Data should only be updated when sessionQueryID(received in the callback) is equal to the current session QueryID(m_uiSessionQueryId).
    if(((iSessionID == m_iBrowseSessionId) && (iSessionQueryID == m_iSessionQueryId)) || ((iSessionID == m_iPreviewBrowseSessionId) && (iSessionQueryID == m_iNowPlayingSessionQueryId)))
    {
        m_vectImagesList.clear();
        m_vectBrowseList.clear();

        MMPresTypes::MetadataItemList::iterator listItr;

        for(listItr = itemList.begin();listItr != itemList.end();listItr++)
        {
            MediaBrowseData objMediaBrowseData;

            objMediaBrowseData.iFileID = static_cast<int>(listItr->getID());
            objMediaBrowseData.strValue = listItr->getValue().c_str();
            objMediaBrowseData.iMetadataType = decodeMetadataEnum(listItr->getItemType());
            objMediaBrowseData.iIndexID = startIndex + (listItr - itemList.begin());
            objMediaBrowseData.iFSContentType = static_cast<int>(listItr->getFolderType());

            if(MMPresTypes::eMetadataType::METADATATYPE_IMAGE == listItr->getItemType())
            {
                MMPresTypes::MetadataStringMap metadataStrMap = listItr->getMetadataMap();
                MMPresTypes::MetadataStringMap::const_iterator mapItr = metadataStrMap.find(MMPresTypes::eMetadataType::METADATATYPE_IMAGE);
                if(mapItr != metadataStrMap.end())
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: imagePath = %s", __FUNCTION__,mapItr->second.c_str());
                    m_vectImagesList.push_back(mapItr->second.c_str());
                }
                else
                {
                    //Do nothing
                }
            }
            else
            {
                m_vectBrowseList.push_back(objMediaBrowseData);
            }
        }

        if((m_pMediaEventProvider) && (m_vectImagesList.size() > 0))
        {
            m_pMediaEventProvider->updateImageData();
        }
        else if((m_pMediaEventProvider))
        {
            if((m_vectBrowseList.size() > 0))
            {
                if((iSessionID == m_iPreviewBrowseSessionId) && (iSessionQueryID == m_iNowPlayingSessionQueryId))
                {
                    m_pMediaEventProvider->updateNowPlayingList();
                }
                else if((iSessionID == m_iBrowseSessionId) && (iSessionQueryID == m_iSessionQueryId))
                {
                    if((windowContainsCurrentlyPlayingTrack))
                    {
                        if((itemIndexTobeHighlighted >= startIndex) && (itemIndexTobeHighlighted < (startIndex + m_vectBrowseList.size())))
                        {
                            /**
                             * @brief iListIndexToBeHighlighted: This local variable holds the index of m_vectBrowseList
                             *                                   that points to the item which is currently Playing. It is used to
                             *                                   set bIsActive of listItem at the respective index to TRUE.
                             */
                            int iListIndexToBeHighlighted = static_cast<int>(itemIndexTobeHighlighted - startIndex);
                            int iBrowseListSize = static_cast<int>(m_vectBrowseList.size());

                            if((iListIndexToBeHighlighted >= 0) && (iListIndexToBeHighlighted < iBrowseListSize))
                            {
                                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Item to be highlighted: Index= %d ItemName= %s", __FUNCTION__, static_cast<int>(itemIndexTobeHighlighted), m_vectBrowseList.at(itemIndexTobeHighlighted-startIndex).strValue.c_str());
                                m_iIndexHighlighted = static_cast<int>(itemIndexTobeHighlighted - 1);
                                m_vectBrowseList.at(iListIndexToBeHighlighted).bIsActive = true;
                            }
                            else
                            {
                                //Do Nothing
                            }

                        }
                        else
                        {
                            //Do Nothing
                        }
                    }
                    m_pMediaEventProvider->updateBrowseData(static_cast<int>(startIndex));
                }
                else
                {
                    //Do Nothing
                }
            }
            else
            {
                m_pMediaEventProvider->emptyListReceived(static_cast<int>(startIndex));
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: Images/Browse data not received from media service or m_pMediaEventProvider is NULL",__FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: sessionQueryID did not match. Data Received Ignored",__FUNCTION__);
    }
}

vector<string> &CMediaResourceImpl::getImageDataList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    return m_vectImagesList;
}

vector<MediaBrowseData> &CMediaResourceImpl::getBrowseDataList()
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    return m_vectBrowseList;
}

int CMediaResourceImpl::getUSBSlotSyncState()
{
    return static_cast<int>(m_eUSBSlotSyncState);
}

int CMediaResourceImpl::getBTSlotSyncState()
{
    return static_cast<int>(m_eBTSlotSyncState);
}

vector<int> &CMediaResourceImpl::getBTSlotCategories()
{
    return m_vectBTAvailableCategories;
}

vector<int> &CMediaResourceImpl::getUSBSlotCategories()
{
    return m_vectUSBAvailableCategories;
}
/* =========================================== Browse methods end ============================================================================ */

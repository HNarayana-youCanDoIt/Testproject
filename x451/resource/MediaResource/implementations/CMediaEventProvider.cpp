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

#include "CMediaEventProvider.h"
#include "logging.h"

CMediaEventProvider::CMediaEventProvider(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
}

CMediaEventProvider::~CMediaEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
}

void CMediaEventProvider::trackSessionUpdate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigTrackSessionUpdateEvent();
}

void CMediaEventProvider::nowPlayingDataUpdate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigNowPlayingDataUpdateEvent();
}

void CMediaEventProvider::playBackStateUpdated(int iPlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigPlayBackStateUpdateEvent(iPlayState);
}

void CMediaEventProvider::albumArtUpdate(string strAlbumArtPath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigAlbumArtDataUpdateEvent(strAlbumArtPath);
}

void CMediaEventProvider::shuffleModeUpdated(int iShuffleMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigShuffleModeUpdateEvent(iShuffleMode);
}

void CMediaEventProvider::repeatModeUpdated(int iRepeatMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigRepeatModeUpdateEvent(iRepeatMode);
}

void CMediaEventProvider::playTimeUpdated(uint64_t uiPlayTime)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigPlayTimeUpdateEvent(uiPlayTime);
}

void CMediaEventProvider::totalDurationUpdated(uint64_t uiTotalDuration)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigTotalDurationUpdateEvent(uiTotalDuration);
}

void CMediaEventProvider::trackNumberUpdated(uint64_t uiTrackNumber)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigTrackNumberUpdateEvent(uiTrackNumber);
}

void CMediaEventProvider::updateImageData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigImageDataPathUpdateEvent();
}

void CMediaEventProvider::updateBrowseData(int iStartIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigBrowseDataUpdateEvent(iStartIndex);
}

void CMediaEventProvider::updateNowPlayingList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigNowPlayingListUpdateEvent();
}

void CMediaEventProvider::updateSyncState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigSyncStateUpdateEvent();
}

void CMediaEventProvider::updateContentType(int iContentType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigContentTypeUpdateEvent(iContentType);
}

void CMediaEventProvider::updateUSBPlayBackMode(int iUSBPlayBackModeEvent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigUSBPlayBackModeEvent(iUSBPlayBackModeEvent);
}

void CMediaEventProvider::updateUSBCategories()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigUSBCategoriesUpdateEvent();
}

void CMediaEventProvider::updateBTCategories()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigBTCategoriesUpdateEvent();
}

void CMediaEventProvider::setRootLevelBrowse()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigSetRootLevelBrowseEvent();
}

void CMediaEventProvider::corruptVideoAccessed()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigCorruptVideoEvent();
}

void CMediaEventProvider::updateUSBDeviceError(int iUSBDeviceError)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigUSBDeviceErrorEvent(iUSBDeviceError);
}

void CMediaEventProvider::updateBreadcrumbPath(const string &strBreadcrumbPath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigBreadrcrumbPathUpdateEvent(strBreadcrumbPath);
}

void CMediaEventProvider::updateBrowseItemEmpty()
{
    emit sigBrowseItemEmpty();
}

void CMediaEventProvider::updateRemotePlayerCapabilities()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigRemotePlayerCapabilitiesUpdateEvent();
}

void CMediaEventProvider::updateBitRate(string strBitRate)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigBitRateUpdateEvent(strBitRate);
}

void CMediaEventProvider::updateSamplingRate(string strSamplingRate)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigSamplingRateUpdateEvent(strSamplingRate);
}

void CMediaEventProvider::updateRequestedBrowseListSize(int iBrowseCategoryListSize)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigRequestedBrowseListSizeUpdateEvent(iBrowseCategoryListSize);
}

void CMediaEventProvider::updateNowPlayingListSize(int iNowPlayingListSize)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigNowPlayingListSizeUpdateEvent(iNowPlayingListSize);
}

void CMediaEventProvider::updateVideoTestModeParameters()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    emit sigVideoTestModeParametersUpdateEvent();
}

void CMediaEventProvider::updateBTMetaDataAvailabilityStatus(int iMetaDataAvailablityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    emit sigBTMetaDataAvailabilityStatusUpdateEvent(iMetaDataAvailablityStatus);
}

void CMediaEventProvider::updateNowPlayingPointer(int iPrevIndex, int iNewIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s iPrevIndex:%d iNewIndex:%d",__FUNCTION__,iPrevIndex,iNewIndex);
    emit sigUpdateNowPlayingPointer(iPrevIndex,iNewIndex);
}

void CMediaEventProvider::emptyListReceived(int iStartIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    emit sigEmptyListReceived(iStartIndex);
}

void CMediaEventProvider::updateBrowseSessionCreation()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    emit sigBrowseSessionCreated();
}

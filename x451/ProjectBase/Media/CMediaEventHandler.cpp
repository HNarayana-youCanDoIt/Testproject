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
* CMediaEventHandler, Class has the slots for all the Signals sent by CMediaEventProvider
*                         which informs Media Adaptor about Media Resource Events
*/

#include "CMediaEventHandler.h"
#include "CHMIMain.h"
#include "CMediaAdaptor.h"
#include "implementations/CMediaResourceImpl.h"
#include "ResourceFactory.hpp"


CMediaEventHandler::CMediaEventHandler(QObject *parent):QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    connectSignals();
}

CMediaEventHandler::~CMediaEventHandler()
{

}

void CMediaEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaResourceImpl* pMediaResource = dynamic_cast<CMediaResourceImpl*>(ResourceFactory::getMediaResource());

    if(pMediaResource)
    {
        CMediaEventProvider* mediaEventProvider = pMediaResource->getMediaEventProvider();
        connect(mediaEventProvider,SIGNAL(sigNowPlayingDataUpdateEvent()),this,SLOT(sltNowPlayingDataUpdate()));
        connect(mediaEventProvider,SIGNAL(sigTrackSessionUpdateEvent()),this,SLOT(sltTrackSessionUpdate()));
        connect(mediaEventProvider,SIGNAL(sigPlayBackStateUpdateEvent(int)),this,SLOT(sltPlayBackStateUpdate(int)));
        connect(mediaEventProvider,SIGNAL(sigAlbumArtDataUpdateEvent(string)),this,SLOT(sltAlbumArtDataUpdate(string)));
        connect(mediaEventProvider,SIGNAL(sigShuffleModeUpdateEvent(int)),this,SLOT(sltShuffleModeUpdate(int)));
        connect(mediaEventProvider,SIGNAL(sigRepeatModeUpdateEvent(int)),this,SLOT(sltRepeatModeUpdate(int)));
        connect(mediaEventProvider,SIGNAL(sigPlayTimeUpdateEvent(uint64_t)),this,SLOT(sltPlayTimeUpdate(uint64_t)));
        connect(mediaEventProvider,SIGNAL(sigTotalDurationUpdateEvent(uint64_t)),this,SLOT(sltTotalDuarationUpdate(uint64_t)));
        connect(mediaEventProvider,SIGNAL(sigTrackNumberUpdateEvent(uint64_t)),this,SLOT(sltTrackNumberUpdate(uint64_t)));
        connect(mediaEventProvider,SIGNAL(sigImageDataPathUpdateEvent()),this,SLOT(sltImageDataPathUpdate()));
        connect(mediaEventProvider,SIGNAL(sigBrowseDataUpdateEvent(int)),this,SLOT(sltBrowseDataUpdate(int)));
        connect(mediaEventProvider,SIGNAL(sigNowPlayingListUpdateEvent()),this,SLOT(sltNowPlayingListUpdate()));
        connect(mediaEventProvider,SIGNAL(sigSyncStateUpdateEvent()),this,SLOT(sltSyncStateUpdate()));
        connect(mediaEventProvider,SIGNAL(sigContentTypeUpdateEvent(int)),this,SLOT(sltContentTypeUpdate(int)));
        connect(mediaEventProvider,SIGNAL(sigUSBCategoriesUpdateEvent()),this,SLOT(sltUSBCategoriesUpdate()));
        connect(mediaEventProvider,SIGNAL(sigBTCategoriesUpdateEvent()),this,SLOT(sltBTCategoriesUpdate()));
        connect(mediaEventProvider,SIGNAL(sigSetRootLevelBrowseEvent()),this,SLOT(sltSetRootLevelBrowse()));
        connect(mediaEventProvider,SIGNAL(sigCorruptVideoEvent()),this,SLOT(sltCorruptVideoAccessed()));
        connect(mediaEventProvider,SIGNAL(sigBreadrcrumbPathUpdateEvent(string)),this,SLOT(sltBreadcrumbPathUpdate(string)));
        connect(mediaEventProvider,SIGNAL(sigBrowseItemEmpty()),this,SLOT(sltBrowseItemEmpty()));
        connect(mediaEventProvider,SIGNAL(sigRemotePlayerCapabilitiesUpdateEvent()),this,SLOT(sltRemotePlayerCapabilitiesUpdate()));
        connect(mediaEventProvider,SIGNAL(sigUSBDeviceErrorEvent(int)),this,SLOT(sltUSBDeviceError(int)));
        connect(mediaEventProvider,SIGNAL(sigUSBPlayBackModeEvent(int)),this,SLOT(sltUSBPlayBackModeUpdate(int)));
        connect(mediaEventProvider,SIGNAL(sigBitRateUpdateEvent(string)),this,SLOT(sltBitRateUpdate(string)));
        connect(mediaEventProvider,SIGNAL(sigSamplingRateUpdateEvent(string)),this,SLOT(sltSamplingRateUpdate(string)));
        connect(mediaEventProvider,SIGNAL(sigRequestedBrowseListSizeUpdateEvent(int)),this,SLOT(sltRequestedBrowseListSizeUpdate(int)));
        connect(mediaEventProvider,SIGNAL(sigNowPlayingListSizeUpdateEvent(int)),this,SLOT(sltNowPlayingListSizeUpdate(int)));
        connect(mediaEventProvider,SIGNAL(sigVideoTestModeParametersUpdateEvent()),this,SLOT(sltVideoTestModeParametersUpdateEvent()));
        connect(mediaEventProvider,SIGNAL(sigBTMetaDataAvailabilityStatusUpdateEvent(int)),this,SLOT(sltBTMetaDataAvailabilityStatusUpdate(int)));
        connect(mediaEventProvider,SIGNAL(sigUpdateNowPlayingPointer(int,int)),this,SLOT(sltNowPlayingPointerUpdateEvent(int,int)));
        connect(mediaEventProvider,SIGNAL(sigEmptyListReceived(int)),this,SLOT(sltOnEmptyListReceived(int)));
        connect(mediaEventProvider,SIGNAL(sigBrowseSessionCreated()),this,SLOT(sltBrowseSessionCreated()));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA, "%s | media Resource is returned NULL from Resource Factory",__FUNCTION__);
    }
}

void CMediaEventHandler::sltNowPlayingDataUpdate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().setNowPlayingData();
}

void CMediaEventHandler::sltTrackSessionUpdate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().onTrackSessionChangedEvent();
}

void CMediaEventHandler::sltPlayBackStateUpdate(int iPlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().setPlayState(iPlayState);
}

void CMediaEventHandler::sltAlbumArtDataUpdate(string strAlbumArtPath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().setAlbumArtData(QString::fromStdString(strAlbumArtPath));
}

void CMediaEventHandler::sltShuffleModeUpdate(int iShuffleMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().setShuffleMode(iShuffleMode);
}

void CMediaEventHandler::sltRepeatModeUpdate(int iRepeatMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().setRepeatMode(iRepeatMode);
}

void CMediaEventHandler::sltPlayTimeUpdate(uint64_t uiPlayTime)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().setPlayTime(uiPlayTime);
}

void CMediaEventHandler::sltTotalDuarationUpdate(uint64_t uiTotalDuration)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().setTotalDuration(uiTotalDuration);
}

void CMediaEventHandler::sltTrackNumberUpdate(uint64_t uiTrackNumber)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().setTrackNumber(uiTrackNumber);
}

void CMediaEventHandler::sltImageDataPathUpdate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().storeImageData();
}

void CMediaEventHandler::sltBrowseDataUpdate(int iStartIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().storeBrowseData(iStartIndex);
}

void CMediaEventHandler::sltNowPlayingListUpdate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    CMediaAdaptor::getInstance().storeNowPlayingList();
}

void CMediaEventHandler::sltSyncStateUpdate()
{
    CMediaAdaptor::getInstance().syncStateUpdated();
}

void CMediaEventHandler::sltContentTypeUpdate(int iContentType)
{
    CMediaAdaptor::getInstance().setContentType(iContentType);
}

void CMediaEventHandler::sltUSBPlayBackModeUpdate(int iMediaUSBPlayBackMode)
{
    CMediaAdaptor::getInstance().setUSBPlayBackMode(iMediaUSBPlayBackMode);
}

void CMediaEventHandler::sltUSBCategoriesUpdate()
{
    CMediaAdaptor::getInstance().usbCategoriesUpdated();
}

void CMediaEventHandler::sltBTCategoriesUpdate()
{
    CMediaAdaptor::getInstance().btCategoriesUpdated();
}

void CMediaEventHandler::sltSetRootLevelBrowse()
{
    CMediaAdaptor::getInstance().setRootLevelBrowse();
}

void CMediaEventHandler::sltCorruptVideoAccessed()
{
    CMediaAdaptor::getInstance().corruptVideoAccessed();
}

void CMediaEventHandler::sltUSBDeviceError(int iUSBDeviceError)
{
    CMediaAdaptor::getInstance().usbDeviceError(iUSBDeviceError);
}

void CMediaEventHandler::sltBreadcrumbPathUpdate(const string &strBreadcrumbPath)
{
    CMediaAdaptor::getInstance().breadcrumbPathUpdated(strBreadcrumbPath);
}

void CMediaEventHandler::sltBrowseItemEmpty()
{
    CMediaAdaptor::getInstance().browseItemEmpty();
}

void CMediaEventHandler::sltRemotePlayerCapabilitiesUpdate()
{
    CMediaAdaptor::getInstance().remotePlayerCapabilitiesUpdate();
}

void CMediaEventHandler::sltBitRateUpdate(string strBitRate)
{
    CMediaAdaptor::getInstance().setBitRateData(QString::fromStdString(strBitRate));
}

void CMediaEventHandler::sltSamplingRateUpdate(string strSamplingRate)
{
    CMediaAdaptor::getInstance().setSamplingRateData(QString::fromStdString(strSamplingRate));
}

void CMediaEventHandler::sltRequestedBrowseListSizeUpdate(int iBrowseCategoryListSize)
{
    CMediaAdaptor::getInstance().createBrowseList(iBrowseCategoryListSize);
}

void CMediaEventHandler::sltNowPlayingListSizeUpdate(int iNowPlayingListSize)
{
    CMediaAdaptor::getInstance().createNowPlayingList(iNowPlayingListSize);
}

void CMediaEventHandler::sltVideoTestModeParametersUpdateEvent()
{
    CMediaAdaptor::getInstance().setVideoTestModeParameters();
}

void CMediaEventHandler::sltBTMetaDataAvailabilityStatusUpdate(int iMetaDataAvailablityStatus)
{
    CMediaAdaptor::getInstance().setBTMetadataAvailabilityStatus(iMetaDataAvailablityStatus);
}

void CMediaEventHandler::sltNowPlayingPointerUpdateEvent(int iPrevIndex, int iNextIndex)
{
    CMediaAdaptor::getInstance().updateNowPlayingPointer(iPrevIndex,iNextIndex);
}

void CMediaEventHandler::sltOnEmptyListReceived(int iStartIndex)
{
    CMediaAdaptor::getInstance().emptyListReceived(iStartIndex);
}

void CMediaEventHandler::sltBrowseSessionCreated()
{
    CMediaAdaptor::getInstance().browseSessionCreated();
}

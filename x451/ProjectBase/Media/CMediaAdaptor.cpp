/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
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

#include "CMediaAdaptor.h"
#include "logging.h"
#include "ResourceFactory.hpp"
#include "HMIIncludes.h"
#include "CMediaBrowseCategoryListModel.h"
#include "CMediaBrowseListModel.h"
#include "CVehicleSettingsAdaptor.h"
#include "CHomeAdaptor.h"
#include "CPowerModeAdaptor.h"
#include "CVRAdaptor.h"
#include "CRCAAdaptor.h"
#include "SoundDemo/CSoundDemoAdaptor.h"

CMediaAdaptor* CMediaAdaptor::m_pMediaAdaptor = nullptr;

CMediaAdaptor::CMediaAdaptor(QObject* parent) : QObject(parent),
    m_bIsNowPlayingDataAvail(false),
    m_ePlayState(CMediaEnum::EMediaPlayStates::PLAYSTATE_UNKNOWN),
    m_eShuffleMode(CMediaEnum::EMediaShuffleMode::SHUFFLEMODE_UNKNOWN),
    m_uiPlayTime(0),
    m_uiTotalDuration(0),
    m_strFormattedPlayTime("00:00"),
    m_strFormattedTotalDuration("00:00"),
    m_strAlbumArtPath(DEFAULT_ALBUM_ART_PATH),
    m_bDefaultAlbumArtDisplayed(true),
    m_strActiveMediaSrcTitle(""),
    mfw(CFramework::getFramework()),
    m_pMediaResource(ResourceFactory::getMediaResource()),
    m_iTotalImageCount(-1),
    m_bIsPlayPauseSupported(false),
    m_bIsNextPrevSupported(false),
    m_bIsFwdRwdSupported(false),
    m_ePreviewMode(CMediaEnum::PREVIEW_MODE_NONE),
    m_pBrowseCategoryList(new CMediaBrowseCategoryListModel(this)),
    m_pBrowseList(new CMediaBrowseListModel(this)),
    m_pSetupAUXGainListModel(new CSetupListModel(this)),
    m_pImageListModel(new CMediaBrowseListModel()),
    m_strBitRate(""),
    m_strSamplingRate(""),
    m_strSongPreviewText(""),
    m_eActiveMediaSrc(CAudioEnums::SRC_ENT_UNKNOWN),
    m_iCurrentBrowseIndex(-1),
    m_iCurrentNowPlayingIndex(-1),
    WINDOW_BUFFER_SIZE(100),
    m_bNoSongsUSBAccepted(false),
    m_strMediaFormat(""),
    m_eBTMetadataAvailabilityStatus(CMediaEnum::EMediaMetadataAvailabilityStatus::MEDIA_METADATA_STATUS_DEFAULT),
    m_iCurrentImageIndex(-1),
    m_iRequestFailedStartIndex(-1),
    m_strBreadcrumbPath("")
{
    mfw.setContextProperty("MediaAdaptor",this);
    CMediaEnum::registerMediaEnumsToQML();
    //Making both Models a qml type so that we can access it's member functions or properties directly in qml
    qmlRegisterUncreatableType<CMediaBrowseCategoryListModel>("com.harman.qml.Media", 1, 0, "CMediaBrowseCategoryListModel", "Cannot create instance of CDeviceSearchListModel in qml");
    qmlRegisterUncreatableType<CMediaBrowseListModel>("com.harman.qml.Media", 1, 0, "CMediaBrowseListModel", "Cannot create instance of CDeviceSearchListModel in qml");
    resetUSBSlotData();
    resetBTSlotData();
    resetMediaData();
    connectSignals();

    if(nullptr != m_pSetupAUXGainListModel)
    {
        m_pSetupAUXGainListModel->addDataToModel(CSetupData("Low",  "", "", CSetupEnums::SETUP_LIST_ITEM_RADIO_BUTTON, true, false, /*Checked/Unchecked*/false, -1, -1, -1, CSetupEnums::SETUP_SCREEN_AUX_IN_GAIN));
        m_pSetupAUXGainListModel->addDataToModel(CSetupData("Mid",  "", "", CSetupEnums::SETUP_LIST_ITEM_RADIO_BUTTON, true, false, /*Checked/Unchecked*/false, -1, -1, -1, CSetupEnums::SETUP_SCREEN_AUX_IN_GAIN));
        m_pSetupAUXGainListModel->addDataToModel(CSetupData("High", "", "", CSetupEnums::SETUP_LIST_ITEM_RADIO_BUTTON, true, false, /*Checked/Unchecked*/true, -1, -1, -1, CSetupEnums::SETUP_SCREEN_AUX_IN_GAIN));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_pSetupAUXGainListModel is NULL",__FUNCTION__);
    }

    if(m_pMediaResource)
    {
        m_pMediaResource->setActiveEntSource(CAudioAdaptor::getInstance()->activeEntSrc());
    }
}

CMediaEnum::EMediaDisplayState CMediaAdaptor::getMediaDisplayState() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Media display state: %d", __FUNCTION__, m_eMediaDisplayState);
    return m_eMediaDisplayState;
}

void CMediaAdaptor::setMediaDisplayState(CMediaEnum::EMediaDisplayState eMediaDisplayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Old display state: %d --> New display state: %d", __FUNCTION__, m_eMediaDisplayState, eMediaDisplayState);
    m_eMediaDisplayState = eMediaDisplayState;
    CHMIMain::getSM()->getSCI_Media()->set_iMediaDisplayState(m_eMediaDisplayState);
}

CMediaEnum::EMediaOperationState CMediaAdaptor::getMediaOperationState() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Media operation state: %d", __FUNCTION__, m_eMediaOperationState);
    return m_eMediaOperationState;
}

bool CMediaAdaptor::compareMediaOperationState(CMediaEnum::EMediaOperationState eMediaOperationState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Media operation state to compare - Current: %d Compare: %d", __FUNCTION__, m_eMediaOperationState, eMediaOperationState);
    return (eMediaOperationState == m_eMediaOperationState);
}

void CMediaAdaptor::setMediaOperationState(CMediaEnum::EMediaOperationState eMediaOperationState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Media operation state: %d", __FUNCTION__, eMediaOperationState);
    m_eMediaOperationState = eMediaOperationState;
    CHMIMain::getSM()->getSCI_Media()->set_iMediaOperationState(m_eMediaOperationState);
}

CMediaEnum::EMediaBrowseItem CMediaAdaptor::getMediaCategoryBrowsed()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Media Category Browsed: %d", __FUNCTION__, m_eMediaCategoryBrowsed);
    return m_eMediaCategoryBrowsed;
}

void CMediaAdaptor::setMediaCategoryBrowsed(CMediaEnum::EMediaBrowseItem eMediaCategoryBrowsed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Media Category Browsed: %d", __FUNCTION__, eMediaCategoryBrowsed);
    m_eMediaCategoryBrowsed = eMediaCategoryBrowsed;
}

CMediaAdaptor::~CMediaAdaptor()
{
    if(m_pMediaAdaptor)
        delete m_pMediaAdaptor;
}

CMediaAdaptor& CMediaAdaptor::getInstance()
{
    //FixMe: Need to return a pointer instead of reference
    if(nullptr == m_pMediaAdaptor)
    {
        m_pMediaAdaptor = new CMediaAdaptor();
    }
    return *m_pMediaAdaptor;
}

void CMediaAdaptor::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigUSBConnectionStatuschanged()), this, SLOT(sltUSBConnectionStatuschanged()));
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigIPODConnectionStatuschanged()), this, SLOT(sltIpodConnectionStatuschanged()));
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigAUXConnectionStatuschanged()), this, SLOT(sltAUXConnectionStatuschanged()));
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigBTSrcStatuschanged()), this, SLOT(sltBTSrcStatuschanged()));
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveEntSrcChanged()),this, SLOT(sltActiveMediaSrcChanged()));
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigAuxGainValueChanged()), this, SLOT(sltAuxGainValueChanged()));
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigSpeedLockOutStatusChanged()), this, SLOT(sltSpeedLockOutStatusChanged()));
    connect(&m_objPreviewTimer, SIGNAL(timeout()), this, SLOT(sltPreviewTimeout()));
    connect(this, SIGNAL(sigProcessHideDrawers()), this, SLOT(sltProcessHideDrawers()), Qt::QueuedConnection);
    connect(&CPowerModeAdaptor::getInstance(), SIGNAL(sigPowerModeChanged()), this, SLOT(sltPowerModeChanged()),Qt::QueuedConnection);
    connect(CPopupManager::getInstance(), SIGNAL(sigPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)), this, SLOT(sltPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)));
}

void CMediaAdaptor::requestMediaActivation(bool bScreenSwitchReq)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: ActiveMediaSrc: %d, bScreenSwitchReq: %d", __FUNCTION__, m_eActiveMediaSrc, bScreenSwitchReq);

    if((CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
            && (!m_bIsNowPlayingDataAvail)
            && (CMediaEnum::CONTENTTYPE_E == m_eUSBContentType
                || CMediaEnum::CONTENTTYPE_I == m_eUSBContentType
                || CMediaEnum::CONTENTTYPE_V == m_eUSBContentType
                || CMediaEnum::CONTENTTYPE_VI == m_eUSBContentType))
    {
        if(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio))
        {
            CHMIMain::getSM()->raise_evMediaActivated();
        }
        activateUSBSlotDevice(bScreenSwitchReq);
    }
    // Check for m_eUSBSyncState to insure that the media is empty, only when sync is completed.
    else if((CAudioEnums::SRC_IPOD == m_eActiveMediaSrc)
            && (CMediaEnum::CONTENTTYPE_E == m_eUSBContentType)
            && (m_eUSBSyncState >= CMediaEnum::SYNC_STATE_THUMBNAIL_PASS))
    {
        //Empty IPOD
        activateUSBSlotDevice(bScreenSwitchReq);
    }
    else if(bScreenSwitchReq)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Switching to Media state, executing choice", __FUNCTION__);
        setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
        CHMIMain::getSM()->raise_evMediaActivated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: Not switching to Media state", __FUNCTION__);
    }
}

void CMediaAdaptor::activateUSBSlotDevice(bool bScreenSwitchRequired)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: bScreenSwitchRequired: %d", __FUNCTION__, bScreenSwitchRequired);
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

    //Fix for ticket 2615762 - HMI to switch to previous source irrespective of nowPlaying data
    // Check for m_eUSBSyncState to insure that the media is empty, only when sync is completed.
    if((CMediaEnum::CONTENTTYPE_E == m_eUSBContentType)
            && (CPopupEnum::EN_POPUPID_USB_CORRUPT_VIDEO != CPopupManager::getInstance()->getCurrentDisplayedPopup())
            && (m_eUSBSyncState >= CMediaEnum::SYNC_STATE_THUMBNAIL_PASS))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Show empty USB/iPOD popup", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_MEDIA_EMPTY_DEVICE_CONNECTED);
        requestPreviousSource();
    }
    else if((CMediaEnum::CONTENTTYPE_V == m_eUSBContentType) || (CMediaEnum::CONTENTTYPE_VI == m_eUSBContentType))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - USB without songs, but videos and or images, connected",__FUNCTION__);
        if(CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
        {
            if(m_bNoSongsUSBAccepted)
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Switching directly to Video browse", __FUNCTION__);
                directMediaStateSwitch(CMediaEnum::BROWSEITEM_VIDEOS);
            }
            else
            {
                if(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Switch to Media loading", __FUNCTION__);
                    setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_LOADING);
                    CHMIMain::getSM()->raise_evMediaActivated();
                }
                else
                {
                    //Do nothing
                }

                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Show Video confirmation popup", __FUNCTION__);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_ONLY_VIDEO_CONFIRMATION);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: Do nothing, USB is not active source yet", __FUNCTION__);
        }
    }
    else if((CMediaEnum::CONTENTTYPE_I == m_eUSBContentType) && (CPopupEnum::EN_POPUPID_USB_CORRUPT_VIDEO != CPopupManager::getInstance()->getCurrentDisplayedPopup()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - USB with only images connected",__FUNCTION__);
        if(CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
        {
            if(m_bNoSongsUSBAccepted)
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Switching directly to Picture Viewer", __FUNCTION__);
                directMediaStateSwitch(CMediaEnum::BROWSEITEM_PICTURE);
            }
            else
            {
                if(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Switch to Media loading", __FUNCTION__);
                    setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_LOADING);
                    CHMIMain::getSM()->raise_evMediaActivated();
                }
                else
                {
                    //Do nothing
                }

                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Show Image confirmation popup", __FUNCTION__);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: Do nothing, USB is not active source yet", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - USB content type: %d", __FUNCTION__, m_eUSBContentType);
        if(bScreenSwitchRequired)
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Screen switch required, raise media activated", __FUNCTION__);
            setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
            CHMIMain::getSM()->raise_evMediaActivated();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Screen switch not required", __FUNCTION__);
        }
    }
}

// Property related functions

void CMediaAdaptor::setSongTitle(const QString &strTitle)
{
    if(strTitle != m_strSongTitle)
    {
        m_strSongTitle = strTitle;
        emit sigSongTitleChanged();
    }
}

void CMediaAdaptor::setSongArtist(const QString &strArtist)
{
    if(strArtist != m_strSongArtist)
    {
        m_strSongArtist = strArtist;
        emit sigSongArtistChanged();
    }
}

void CMediaAdaptor::setSongAlbum(const QString &strAlbum)
{
    if(strAlbum != m_strSongAlbum)
    {
        m_strSongAlbum = strAlbum;
        emit sigSongAlbumChanged();
    }
}

void CMediaAdaptor::syncStateUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);

    if(m_pMediaResource)
    {
        if(m_eUSBSyncState != static_cast<CMediaEnum::EMediaSyncState>(m_pMediaResource->getUSBSlotSyncState()))
        {
            m_eUSBSyncState = static_cast<CMediaEnum::EMediaSyncState>(m_pMediaResource->getUSBSlotSyncState());

            emit sigUSBSlotSyncState();

            if(CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
            {
                if(m_eUSBSyncState >= CMediaEnum::SYNC_STATE_THUMBNAIL_PASS)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ USB - SYNC_STATE_THUMBNAIL_PASS]");
                }
                else if(m_eUSBSyncState >= CMediaEnum::SYNC_STATE_FILE_PASS)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ USB - SYNC_STATE_FILE_PASS]");
                }
                else if(m_eUSBSyncState >= CMediaEnum::SYNC_STATE_FIRST_FILE)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ USB - SYNC_STATE_FIRST_FILE]");
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ USB - SYNC_STATE NOT HANDLED]");
                }
            }

            if(m_eUSBSyncState >= CMediaEnum::SYNC_STATE_THUMBNAIL_PASS)
            {
                if((CAudioEnums::SRC_USB1 == m_eActiveMediaSrc) || (CAudioEnums::SRC_IPOD == m_eActiveMediaSrc))
                {
                    m_pMediaResource->getDeviceItemsInfoAttribute();
                }
            }

            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - USB slot sync state: %d",__FUNCTION__, static_cast<CMediaEnum::EMediaSyncState>(m_eUSBSyncState));
        }

        if(m_eBTSyncState != static_cast<CMediaEnum::EMediaSyncState>(m_pMediaResource->getBTSlotSyncState()))
        {
            m_eBTSyncState = static_cast<CMediaEnum::EMediaSyncState>(m_pMediaResource->getBTSlotSyncState());

            emit sigBTSlotSyncState();

            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - BT slot sync state: %d",__FUNCTION__, static_cast<CMediaEnum::EMediaSyncState>(m_eBTSyncState));
        }
    }
}

void CMediaAdaptor::setContentType(int iContentType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s",__FUNCTION__);

    if(m_eUSBContentType != iContentType)
    {
        m_eUSBContentType = static_cast<CMediaEnum::EMediaContentType>(iContentType);
        emit sigUSBContentTypeChanged();

        //State machine does not takes any action on empty USB content type even if reported
        CHMIMain::getSM()->getSCI_Media()->set_iCurrentContentType(m_eUSBContentType);

        activateUSBSlotDevice();
    }
}

bool CMediaAdaptor::getMediaControlsVisibility()
{
    if((CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
            && (!m_bIsNowPlayingDataAvail)
            && (getNoSongsUSBResponse()))
    {
        //USB with only videos and/or images is connected and no media (video) is playing
        return false;
    }
    else
    {
        return true;
    }
}

int CMediaAdaptor::getPvCurrentImageIndex()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_iCurrentImageIndex: %d", __FUNCTION__, m_iCurrentImageIndex);
    return m_iCurrentImageIndex ;
}

void CMediaAdaptor::setPvCurrentImageIndex(int iIndex)
{
    if((m_pImageListModel)&&
            ((iIndex >= 0) && (m_pImageListModel->rowCount() > iIndex)))
    {
        m_iCurrentImageIndex = iIndex;
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_iCurrentImageIndex: %d", __FUNCTION__, m_iCurrentImageIndex);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_iCurrentImageIndex: %d is invalid.", __FUNCTION__, m_iCurrentImageIndex);
    }
}

void CMediaAdaptor::setUSBPlayBackMode(int iMediaUSBPlayBackMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - USB playBack mode: %d", __FUNCTION__, iMediaUSBPlayBackMode);
    m_eMediaUSBPlayBackMode = static_cast<CMediaEnum::EMediaUSBPlayBackMode>(iMediaUSBPlayBackMode);

    m_bIsFolderModePlayBack = (CMediaEnum::USB_PLAYBACK_FOLDER_MODE == m_eMediaUSBPlayBackMode);
    emit sigUSBPlayBackModeChanged();
}

void CMediaAdaptor::usbCategoriesUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    //Get updated categroies from resource
    if(m_pMediaResource)
    {
        int iSize = static_cast<int>(m_pMediaResource->getUSBSlotCategories().size());
        for(int iIndex = 0; iIndex < iSize; iIndex++)
        {
            m_listUSBAvailableCategories.replace(iIndex, m_pMediaResource->getUSBSlotCategories().at(iIndex));
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Category: %d, count: %d",__FUNCTION__, iIndex, m_listUSBAvailableCategories[iIndex]);
        }

        if((CAudioEnums::SRC_USB1 == CAudioAdaptor::getInstance()->activeEntSrc()) && (getUSBDeviceCategoryCount(CMediaEnum::BROWSEITEM_FOLDERS) != m_iUSBFolderCount))
        {
            m_iUSBFolderCount = getUSBDeviceCategoryCount(CMediaEnum::BROWSEITEM_FOLDERS);
            emit sigFolderCountChanged();
        }
    }
}

bool CMediaAdaptor::isUSBDeviceCategoryAvailable(CMediaEnum::EMediaBrowseItem eBrowseItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s eBrowseItem: %d",__FUNCTION__,eBrowseItem);
    bool bRet = false;
    if(CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
    {
        //Source is USB
        if(CMediaEnum::CONTENTTYPE_V == m_eUSBContentType
                || CMediaEnum::CONTENTTYPE_VI == m_eUSBContentType
                || CMediaEnum::CONTENTTYPE_I == m_eUSBContentType)
        {
            //USB has only videos and/or images

            if(static_cast<int>(eBrowseItem) >= 0 && static_cast<int>(eBrowseItem) < m_listUSBAvailableCategories.size())
            {
                bRet = (m_listUSBAvailableCategories.at(static_cast<int>(eBrowseItem)) > 0);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s eBrowseItem is out of bounds for m_listUSBAvailableCategories",__FUNCTION__);
                bRet = false;
            }

        }
        else
        {
            //USB has songs
            if(CMediaEnum::BROWSEITEM_FOLDERS == eBrowseItem
                    || CMediaEnum::BROWSEITEM_SONGS == eBrowseItem)
            {
                //Folders and songs should always be true
                bRet = true;
            }
            else
            {
                if(static_cast<int>(eBrowseItem) >= 0 && static_cast<int>(eBrowseItem) < m_listUSBAvailableCategories.size())
                {
                    bRet = (m_listUSBAvailableCategories.at(static_cast<int>(eBrowseItem)) > 0);
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s eBrowseItem is out of bounds for m_listUSBAvailableCategories",__FUNCTION__);
                    bRet = false;
                }

            }
        }
    }
    else
    {
        //Source is IPOD
        if(static_cast<int>(eBrowseItem) >= 0 && static_cast<int>(eBrowseItem) < m_listUSBAvailableCategories.size())
        {
            bRet = (m_listUSBAvailableCategories.at(static_cast<int>(eBrowseItem)) > 0);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s eBrowseItem is out of bounds for m_listUSBAvailableCategories",__FUNCTION__);
            bRet = false;
        }
    }

    return bRet;
}

int CMediaAdaptor::getUSBDeviceCategoryCount(CMediaEnum::EMediaBrowseItem eBrowseItem)
{
    int iRet = -1;
    if(static_cast<int>(eBrowseItem) >= 0 && static_cast<int>(eBrowseItem) < m_listUSBAvailableCategories.size())
    {
        iRet = m_listUSBAvailableCategories.at(static_cast<int>(eBrowseItem));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s eBrowseItem:%d is out of bound for m_listUSBAvailableCategories",__FUNCTION__,eBrowseItem);
        //Do Nothing
    }

    return  iRet;

}

void CMediaAdaptor::showSongPreview(CMediaEnum::EMediaPreviewMode ePreviewMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_listNowPlaying.size() > 1)
    {
        if(CMediaEnum::PREVIEW_MODE_NONE == m_ePreviewMode)
        {
            //Need to do this only when Preview request is received for first time
            m_iCurrentPreviewIndex = m_iCurrentTrackIndex - 1; //Preview index is '0' based
        }

        if((CMediaEnum::PREVIEW_MODE_NEXT == ePreviewMode) || (CMediaEnum::PREVIEW_MODE_PREV == ePreviewMode))
        {
            if((CMediaEnum::PREVIEW_MODE_NEXT == ePreviewMode) && (m_iCurrentPreviewIndex >= (m_listNowPlaying.size()-1)))
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Next Preview not displayed since already reached end",__FUNCTION__);
            }
            else if((CMediaEnum::PREVIEW_MODE_PREV == ePreviewMode) && (m_iCurrentPreviewIndex <= 0))
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Prev Preview not displayed since already at start",__FUNCTION__);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - previewIndex: %d, totCount: %d", __FUNCTION__, m_iCurrentPreviewIndex, m_listNowPlaying.size()-1);
                m_iCurrentPreviewIndex = (CMediaEnum::PREVIEW_MODE_NEXT == ePreviewMode) ? (m_iCurrentPreviewIndex + 1) : (m_iCurrentPreviewIndex - 1);

                if((m_iCurrentPreviewIndex >= 0) && (m_iCurrentPreviewIndex < m_listNowPlaying.size()))
                {
                    m_strSongPreviewText = m_listNowPlaying.at(m_iCurrentPreviewIndex).m_strCategoryItemText;
                    m_ePreviewMode = ePreviewMode;
                    emit sigPreviewTextChanged();
                    emit sigSongPreviewChanged();
                }
                else
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - m_iCurrentPreviewIndex out of bounds: %d",__FUNCTION__, m_iCurrentPreviewIndex);
                }
            }

            //If preview is on display then start timer irrespective of user reached start or end of the nowPlaying list
            if((CMediaEnum::PREVIEW_MODE_NEXT == m_ePreviewMode) || (CMediaEnum::PREVIEW_MODE_PREV == m_ePreviewMode))
            {
                m_objPreviewTimer.setSingleShot(true);
                m_objPreviewTimer.setInterval(3000);
                m_objPreviewTimer.start();
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Invalid Preview Mode",__FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Preview not displayed as count less than 2",__FUNCTION__);
    }
}

void CMediaAdaptor::playPreviewSong()
{
    if((m_iCurrentPreviewIndex >= 0) && (m_iCurrentPreviewIndex < m_listNowPlaying.size()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Play song at index: %d", __FUNCTION__, m_listNowPlaying.at(m_iCurrentPreviewIndex).m_iCategoryItemId);
        if(m_pMediaResource)
        {
            m_strSongPreviewText = "";
            m_ePreviewMode = CMediaEnum::PREVIEW_MODE_NONE;
            emit sigPreviewTextChanged();
            emit sigSongPreviewChanged();

            m_pMediaResource->playSong(m_listNowPlaying.at(m_iCurrentPreviewIndex).m_iCategoryItemId, true);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - m_iCurrentPreviewIndex out of bound: %d",__FUNCTION__, m_iCurrentPreviewIndex);
    }
}

void CMediaAdaptor::requestPreviousSource()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - switchToPreviousEntSource invoked from Media",__FUNCTION__);

    //Toggle source to previous
    CAudioAdaptor::getInstance()->switchToPreviousEntSource();
}

void CMediaAdaptor::btCategoriesUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    //Get updated categroies from resource
    if(m_pMediaResource)
    {
        int iSize = static_cast<int>(m_pMediaResource->getBTSlotCategories().size());
        for(int iIndex = 0; iIndex < iSize; iIndex++)
        {
            m_listBTAvailableCategories.replace(iIndex, m_pMediaResource->getBTSlotCategories().at(iIndex));
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Category: %d, count: %d",__FUNCTION__, iIndex, m_listBTAvailableCategories[iIndex]);
        }
    }
}

void CMediaAdaptor::breadcrumbPathUpdated(const string &strBreadcrumbPath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s - strBreadcrumbPath: %s", __FUNCTION__, strBreadcrumbPath.c_str());
    m_strBrowseCategoryScreenTitle = QString::fromStdString(strBreadcrumbPath);

    m_strBreadcrumbPath = QString::fromStdString(strBreadcrumbPath);

    //breadcrumb path format - genres/artists/albums/....Need to extract the last part for HMI to display
    QStringList slSplitList = m_strBrowseCategoryScreenTitle.split("/");
    m_strBrowseCategoryScreenTitle = slSplitList[slSplitList.length() - 1];

    //Hardcoding in HMI because service does not sends title value sometimes
    if((CMediaEnum::BROWSEITEM_PLAYLISTS == getMediaCategoryBrowsed()) && (m_strBrowseCategoryScreenTitle.compare("") == 0))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s - Showing hardcoded title: %s", __FUNCTION__, m_strItemSelectedText.toStdString().c_str());
        m_strBrowseCategoryScreenTitle = m_strItemSelectedText;
    }
    else
    {
        //Do nothing
    }

    /**
     * @note Updating the current Browse level to BROWSELEVEL_CATEGORY when breadcrumb path received from
     *       Media service hase only 2 characters. Eg: "/Songs" or "/Genres"
     */
    if(m_strBreadcrumbPath.split("/").size()<= 2)
    {
        if(CMediaEnum::BROWSEITEM_ITUNES_RADIO == getMediaCategoryBrowsed())
        {
            //Do nothing....no need to capitalize first char for iTunes Radio type
        }
        else
        {
            //Media service gives breadcrumb path in all lower case, hence converting it to camel case below
            m_strBrowseCategoryScreenTitle = m_strBrowseCategoryScreenTitle.left(1).toUpper()+m_strBrowseCategoryScreenTitle.mid(1);
        }

        CHMIMain::getSM()->getSCI_Media()->set_iCurrentBrowseLevel(CMediaEnum::BROWSELEVEL_CATEGORY);
    }

    sigBrowseCategoryScreenTitleChanged();
}

bool CMediaAdaptor::isBTDeviceCategoryAvailable(CMediaEnum::EMediaBrowseItem eBrowseItem)
{
    bool bRet = false;

    if(static_cast<int>(eBrowseItem) >= 0 && static_cast<int>(eBrowseItem) < m_listBTAvailableCategories.size())
    {
        bRet = (m_listBTAvailableCategories.at(static_cast<int>(eBrowseItem)) > 0);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s eBrowseItem:%d is out of bound for m_listBTAvailableCategories",__FUNCTION__,eBrowseItem);
        //Do nothing
    }

    return bRet;

}

void CMediaAdaptor::showEmptyCategoryPopup(CMediaEnum::EMediaBrowseItem eBrowseItem)
{
    //FixMe: Need to put the text from language strings for static text
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Browse category not available: %d", __FUNCTION__, eBrowseItem);
    m_strEmptyCategoryPopupText = "No " + getBrowseCategoryName(eBrowseItem) + " found.";

    //Since browse items are empty on unavailability, this is no more required
    //CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_MEDIA_EMPTY_CATEGORY);
}

QString CMediaAdaptor::getEmptyCategoryText()
{
    QString strEmptyCategoryText = getBrowseCategoryName(getMediaCategoryBrowsed()).append(" Empty.");
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Empty Category Text: %s", __FUNCTION__, strEmptyCategoryText.toStdString().c_str());
    return strEmptyCategoryText;
}

QString CMediaAdaptor::getStrUSBDeviceErrorPopupText() const
{
    return m_strUSBDeviceErrorPopupText;
}

QString CMediaAdaptor::getFormattedTime(const uint &uiTimeInSecs)
{
    ulong ulHours = uiTimeInSecs/60/60;
    ulong ulMinutes = (uiTimeInSecs / 60) % 60;
    ulong ulSeconds = uiTimeInSecs % 60;

    QString strFormattedMinutes = QString::number(ulMinutes);
    if (ulMinutes < 10)
    {
        strFormattedMinutes.prepend("0");
    }

    QString strFormattedSeconds = QString::number(ulSeconds);
    if (ulSeconds < 10)
    {
        strFormattedSeconds.prepend("0");
    }

    QString strFormattedHours = QString::number(ulHours);
    if (ulHours < 10)
    {
        strFormattedHours.prepend("0");
    }

    QString strTime = "";

    if(ulHours > 0 )
    {
        strTime.append(strFormattedHours);
        strTime.append(":");
    }

    strTime.append(strFormattedMinutes);
    strTime.append(":");
    strTime.append(strFormattedSeconds);

    return strTime;
}

void CMediaAdaptor::getCategoryRoot(CMediaEnum::EMediaBrowseItem eMediaBrowseItem, bool bIsVRRequest)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Browse request for: %d",__FUNCTION__, eMediaBrowseItem);

    if(m_pMediaResource)
    {
        setMediaBrowseItemSelected(eMediaBrowseItem);
        setMediaCategoryBrowsed(eMediaBrowseItem);

        m_pBrowseCategoryList->removeRows();
        setMediaBrowseDataState(CMediaEnum::BROWSEDATA_STATE_FETCHING);

        m_strBrowseCategoryScreenTitle = "";
        sigBrowseCategoryScreenTitleChanged();

        CHMIMain::getSM()->getSCI_Media()->set_iCurrentBrowseLevel(CMediaEnum::BROWSELEVEL_CATEGORY);

        m_pMediaResource->getCategoryRoot(static_cast<int>(eMediaBrowseItem), bIsVRRequest);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::processBrowseCategoryRequest(CMediaEnum::EMediaBrowseItem eMediaBrowseItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - %d",__FUNCTION__, eMediaBrowseItem);

    if(CMediaEnum::BROWSEITEM_PICTURE == eMediaBrowseItem)
    {
        if(CVehicleSettingsAdaptor::getInstance()->speedLockOutStatus())
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s : PV speed lockout true - showing lockout popup only", __FUNCTION__);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_SPEED_LOCKOUT_IMAGES);
        }
        else
        {
            setMediaBrowseItemSelected(eMediaBrowseItem);
            setMediaCategoryBrowsed(eMediaBrowseItem);
            CHMIMain::getSM()->getSCI_Media()->raise_evBrowseItemPressed(eMediaBrowseItem);
        }
    }
    else
    {
        getCategoryRoot(eMediaBrowseItem);
        CHMIMain::getSM()->getSCI_Media()->raise_evBrowseItemPressed(eMediaBrowseItem);
    }
}

void CMediaAdaptor::processHideDrawersDelay()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);

    emit sigProcessHideDrawers();
}

void CMediaAdaptor::cancelFastForward()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);

    if(CMediaEnum::PLAYSTATE_FASTFORWARD == m_ePlayState)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Cancelling FFwd on SW Update Key",__FUNCTION__);
        //resume();
        fastForward(CMediaEnum::EN_BUTTON_STATE_LONG_RELEASED);
    }
}

void CMediaAdaptor::nextFolder()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);
    if(m_pMediaResource)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ next folder request]");
        m_pMediaResource->nextFolder();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::previousFolder()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_pMediaResource)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ previous folder request]");
        m_pMediaResource->previousFolder();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::requestPage(int iIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);

    m_objWindowingHelperForBrowse.requestPage(iIndex);
}

void CMediaAdaptor::resetWindowing()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,__FUNCTION__);

    m_iCurrentBrowseIndex = -1;
    m_objWindowingHelperForBrowse.resetWindowingParam();
}

void CMediaAdaptor::browseItemClicked(int iItemFID, int iMetadataType, QString strItemValue, int iFSContentType, int iListIndexNo, bool bIsVRRequest)
{
    CPP_UNUSED(iListIndexNo);
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - itemFID: %d , MetadataType: %d ",__FUNCTION__, iItemFID, iMetadataType);

    //Hardcoding from HMI to save the playlist name (in case service does not sends it)
    m_strItemSelectedText = strItemValue;

    switch(static_cast<CMediaEnum::EMediaBrowseItem>(iMetadataType))
    {
    case CMediaEnum::BROWSEITEM_SONGS:
    case CMediaEnum::BROWSEITEM_AUDIOBOOK:
    case CMediaEnum::BROWSEITEM_ITUNES_RADIO:
    case CMediaEnum::BROWSEITEM_VIDEOS:
    case CMediaEnum::BROWSEITEM_EPISODE:
    case CMediaEnum::BROWSEITEM_PLAYALL:
    {
        //Reset the parameter when any media type is selected
        CHMIMain::getSM()->getSCI_Media()->set_isBrowseCategoryDirectEntry(false);

        //playSong
        if(m_pMediaResource)
        {
            if((CMediaEnum::BROWSEITEM_VIDEOS == static_cast<CMediaEnum::EMediaBrowseItem>(iMetadataType))
                    && (CVehicleSettingsAdaptor::getInstance()->speedLockOutStatus()))
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s : Video speed lockout true - showing lockout popup only", __FUNCTION__);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_SPEED_LOCKOUT_VIDEO);
            }
            else
            {
                //Do not clear nowPlaying data if its not 'Play All' and same song is selected for IPOD/BT
                if((CMediaEnum::BROWSEITEM_PLAYALL != static_cast<CMediaEnum::EMediaBrowseItem>(iMetadataType))
                        && (CAudioEnums::SRC_USB1 != m_eActiveMediaSrc)
                        && (strItemValue == m_strSongTitle))
                {
                    //Do not clear nowPlaying data as user has selected same song for IPOD/BT
                }
                else
                {
                    resetNowPlayingData();
                }

                if(CMediaEnum::BROWSEITEM_VIDEOS == iMetadataType)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "[KPI_MARKER][HMI][ Video PlayBack requested.]");
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "[KPI_MARKER][HMI][ Song PlayBack requested.]");
                }

                setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_LOADING);
                setMediaBrowseItemSelected(static_cast<CMediaEnum::EMediaBrowseItem>(iMetadataType));
                setMediaCategoryBrowsed(static_cast<CMediaEnum::EMediaBrowseItem>(iMetadataType));
                CHMIMain::getSM()->getSCI_Media()->raise_evMediaTypeSelected(iMetadataType);

                m_pMediaResource->playSong(iItemFID);

                m_pBrowseCategoryList->removeRows();
                setMediaBrowseDataState(CMediaEnum::BROWSEDATA_STATE_FETCHING);
            }
        }
    }
        break;

    case CMediaEnum::BROWSEITEM_FOLDERS:
    case CMediaEnum::BROWSEITEM_ALBUMS:
    case CMediaEnum::BROWSEITEM_ARTISTS:
    case CMediaEnum::BROWSEITEM_GENRE:
    case CMediaEnum::BROWSEITEM_PODCAST:
    case CMediaEnum::BROWSEITEM_PLAYLISTS:
    {
        //getCategorySubLevel
        if(m_pMediaResource)
        {
            setMediaBrowseDataState(CMediaEnum::BROWSEDATA_STATE_FETCHING);

            m_strPrevBrowseCategoryScreenTitle = m_strBrowseCategoryScreenTitle;

            if(bIsVRRequest)
            {
                //Back button shall now switch back to previous screen in case of VR browse
                CHMIMain::getSM()->getSCI_Media()->set_iCurrentBrowseLevel(CMediaEnum::BROWSELEVEL_CATEGORY);
            }
            else
            {
                //Back button shall now not switch to previous screen once browse level is set to sub category
                CHMIMain::getSM()->getSCI_Media()->set_iCurrentBrowseLevel(CMediaEnum::BROWSELEVEL_SUBCATEGORY);
            }

            setMediaBrowseItemSelected(static_cast<CMediaEnum::EMediaBrowseItem>(iMetadataType));
            setMediaCategoryBrowsed(static_cast<CMediaEnum::EMediaBrowseItem>(iMetadataType));
            m_pMediaResource->getCategorySubLevel(iItemFID, iMetadataType, iFSContentType, bIsVRRequest);
            CHMIMain::getSM()->getSCI_Media()->raise_evBrowseItemPressed(iMetadataType);
        }
    }
        break;

    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Invalid Metadata type",__FUNCTION__);
    }

    }
}

void CMediaAdaptor::goToPreviousLevel()
{
    if(m_pMediaResource)
    {
        m_pBrowseCategoryList->removeRows();
        setMediaBrowseDataState(CMediaEnum::BROWSEDATA_STATE_FETCHING);

        m_strBrowseCategoryScreenTitle = "";
        sigBrowseCategoryScreenTitleChanged();

        resetWindowing();

        m_pMediaResource->goToPreviousLevel();
    }
}

//Method is currently unused.
void CMediaAdaptor::setRootLevelBrowse()
{
    m_pBrowseCategoryList->removeRows();
    setMediaBrowseDataState(CMediaEnum::BROWSEDATA_STATE_NONE);

    m_strBrowseCategoryScreenTitle = "";


    //Reset Windowing Helper params
    resetWindowing();

    //reset category level
    CHMIMain::getSM()->getSCI_Media()->set_iCurrentBrowseLevel(CMediaEnum::BROWSELEVEL_ROOT);

    if(CAudioEnums::SRC_BT_A2DP1 == CAudioAdaptor::getInstance()->activeEntSrc())
    {
        //Switch to Media Main Screen
        setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_LOADING);
        CHMIMain::getSM()->getSCI_Media()->raise_evMediaTypeSelected(CMediaEnum::BROWSEITEM_SONGS);
    }
    else
    {
        //Switch HMI to browse screen
        CHMIMain::getSM()->raise_evBackPressed();
    }
}

void CMediaAdaptor::corruptVideoAccessed()
{
    resetNowPlayingData();
    if(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain)
            || CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Switch to Media loading", __FUNCTION__);
        setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_LOADING);
        CHMIMain::getSM()->raise_evMediaActivated();
    }
    else
    {
        //Do nothing
    }

    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    setMediaOperationState(CMediaEnum::MEDIA_OPERATIONSTATE_CORRUPTVIDEO);
    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_CORRUPT_VIDEO);
}

void CMediaAdaptor::usbDeviceError(const int &iUSBDeviceError)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(CMediaEnum::USB_DEVICE_UNSUPPORTED == iUSBDeviceError)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show USB Device Error popup - Unsupported Device", __FUNCTION__);
        m_strUSBDeviceErrorPopupText = tr("Unsupported Device");
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_DEVICE_ERROR_CONNECTED);
    }
    else if(CMediaEnum::USB_DEVICE_HUB_UNSUPPORTED == iUSBDeviceError)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show USB Device Error popup - Hub unsupported", __FUNCTION__);
        m_strUSBDeviceErrorPopupText = tr("Hub unsupported");
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_DEVICE_ERROR_CONNECTED);
    }
    else if(CMediaEnum::USB_DEVICE_NO_RESPONSE == iUSBDeviceError)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show USB Device Error popup - Device no response", __FUNCTION__);
        m_strUSBDeviceErrorPopupText = tr("Device no response");
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_DEVICE_ERROR_CONNECTED);
    }
    else if(CMediaEnum::USB_DEVICE_NO_ERROR == iUSBDeviceError)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show USB Device Error popup - No error - popup removed", __FUNCTION__);
        CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_USB_DEVICE_ERROR_CONNECTED);
    }
    else
    {
        //Do nothing
    }
}

void CMediaAdaptor::sltUSBConnectionStatuschanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    setNoSongsUSBResponse(false);

    if (CAudioEnums::USB_CONNECTED == CAudioAdaptor::getInstance()->usbConnectionStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show USB connected popup", __FUNCTION__);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ USB Connected]");
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_CONNECTED);
    }
    else if (CAudioEnums::USB_DISCONNECTED == CAudioAdaptor::getInstance()->usbConnectionStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show USB disconnected popup", __FUNCTION__);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ USB Disconnected]");

        if((CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
                && (CMediaEnum::MEDIA_DISPLAYSTATE_MAIN == getMediaDisplayState())
                && CMediaEnum::MEDIA_OPERATIONSTATE_VIDEO == getMediaOperationState())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Switching to loading state as USB is removed", __FUNCTION__);
            resetNowPlayingData(); //So that SCT shall not enter main state again
            setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_LOADING);
            CHMIMain::getSM()->raise_evMediaActivated();
        }
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_DISCONNECTED);
        resetUSBSlotData();
    }
    else
    {
        //Do Nothing
    }
}

void CMediaAdaptor::sltIpodConnectionStatuschanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if (CAudioEnums::IPOD_CONNECTED == CAudioAdaptor::getInstance()->ipodConnectionStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show Ipod connected popup", __FUNCTION__);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ IPod Connected]");
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_IPOD_CONNECTED);
    }
    else if (CAudioEnums::IPOD_DISCONNECTED == CAudioAdaptor::getInstance()->ipodConnectionStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show Ipod disconnected popup", __FUNCTION__);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ IPod Disconnected]");
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_IPOD_DISCONNECTED);
        resetUSBSlotData();
    }
    else
    {
        //Do Nothing
    }
}

void CMediaAdaptor::sltAUXConnectionStatuschanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if (CAudioEnums::AUX_CONNECTED == CAudioAdaptor::getInstance()->auxConnectionStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show AUX connected popup", __FUNCTION__);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ Aux Connected]");
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AUX_CONNECTED);
    }
    else if (CAudioEnums::AUX_DISCONNECTED == CAudioAdaptor::getInstance()->auxConnectionStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show AUX disconnected popup", __FUNCTION__);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ Aux Disconnected]");
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AUX_DISCONNECTED);
    }
    else
    {
        // Do nothing.
    }
}

void CMediaAdaptor::sltBTSrcStatuschanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    //Media domain to not display any popup for BT connection/disconnection
    //This method can be though utilized in future to handle some cases on BT connection/disconnection

    if(CAudioAdaptor::getInstance()->btSrcStatus())
    {
        //Do nothing
        /*
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show BT connected popup", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_BTAUDIO_CONNECTED);
        */
    }
    else
    {
        /*
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s  - Show BT disconnected popup", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_BTAUDIO_DISCONNECTED);
        */
        resetBTSlotData();
    }
}

void CMediaAdaptor::sltActiveMediaSrcChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_CORRUPT_VIDEO);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_ONLY_VIDEO_CONFIRMATION);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION);

    m_eActiveMediaSrc = CAudioAdaptor::getInstance()->activeEntSrc();

    switch (CAudioAdaptor::getInstance()->activeEntSrc())
    {
    case CAudioEnums::SRC_USB1:
    case CAudioEnums::SRC_AUDIO_AUX:
    case CAudioEnums::SRC_BT_A2DP1:
    case CAudioEnums::SRC_IPOD:
    {
        resetMediaData();
        setMediaScreenTitle();
        updateMediaBrowseList();
        if(m_pMediaResource)
        {
            m_pMediaResource->setActiveEntSource(m_eActiveMediaSrc);

            //Sometimes, SyncState is received before USB activation
            if(m_eUSBSyncState >= CMediaEnum::SYNC_STATE_THUMBNAIL_PASS)
            {
                if((CAudioEnums::SRC_USB1 == m_eActiveMediaSrc) || (CAudioEnums::SRC_IPOD == m_eActiveMediaSrc))
                {
                    m_pMediaResource->getDeviceItemsInfoAttribute();
                }
            }

            if(CAudioEnums::SRC_AUDIO_AUX != m_eActiveMediaSrc)
            {
                m_pMediaResource->getShuffleState();
                m_pMediaResource->getRepeatState();
            }

            if(CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
            {
                m_pMediaResource->getUSBPlaybackMode();
            }
            else
            {
                //Do nothing
                setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
                setMediaOperationState(CMediaEnum::MEDIA_OPERATIONSTATE_NONE);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
        }
        break;
    }

    case CAudioEnums::SRC_ENT_UNKNOWN:
    {
        m_eActiveMediaSrc = CAudioEnums::SRC_ENT_UNKNOWN;
        break;
    }

    case CAudioEnums::SRC_HDD:
    {
        if(m_pMediaResource)
        {
            m_pMediaResource->setActiveEntSource(m_eActiveMediaSrc);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
        }
        break;
    }
    default:
    case CAudioEnums::SRC_TUNER_FM:
    case CAudioEnums::SRC_TUNER_AM:
        setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
        setMediaOperationState(CMediaEnum::MEDIA_OPERATIONSTATE_NONE);
        m_eActiveMediaSrc = CAudioEnums::SRC_ENT_UNKNOWN;
        break;
    }
}

void CMediaAdaptor::resetMediaData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    resetNowPlayingData();
    m_pBrowseCategoryList->removeRows();
    setMediaBrowseDataState(CMediaEnum::BROWSEDATA_STATE_NONE);
    m_eShuffleMode = CMediaEnum::EMediaShuffleMode::SHUFFLEMODE_UNKNOWN;
    m_eRepeatMode  = CMediaEnum::EMediaRepeatMode::REPEAT_UNKNOWN;
    m_ePlayState = CMediaEnum::EMediaPlayStates::PLAYSTATE_UNKNOWN;
    m_eMediaCategoryBrowsed = CMediaEnum::BROWSEITEM_UNKNOWN;
    m_strBrowseCategoryScreenTitle = "";
    m_strActiveMediaSrcTitle = "";
    //TODO: Need to emit signals for all qProps when setting to default values

    //This shall clear the now playing list and reset windowing in progress, if any.
    m_listNowPlaying.clear();
    m_iCurrentNowPlayingIndex = -1;
    m_objWindowingHelperForNowPlayingList.resetWindowingParam();
    setMediaVRBrowseState(CMediaEnum::VR_BROWSE_STATE_NONE);
}

void CMediaAdaptor::resetNowPlayingData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    m_bIsNowPlayingDataAvail = false;
    m_strMediaFormat = "";
    m_eNowPlayingMetadataType = CMediaEnum::BROWSEITEM_UNKNOWN;
    CHMIMain::getSM()->getSCI_Media()->set_isNowPlayingAvailable(m_bIsNowPlayingDataAvail);
    CHMIMain::getSM()->getSCI_Media()->set_iCurrentMediaType(CMediaEnum::MEDIATYPE_UNKNOWN);
    setSongTitle("");
    setSongArtist("");
    setSongAlbum("");
    setPlayTime(0);
    setTotalDuration(0);
    m_bShowPlaytime = false;
    m_strAlbumArtPath = DEFAULT_ALBUM_ART_PATH;
    m_bDefaultAlbumArtDisplayed = true;
}

void CMediaAdaptor::resetUSBSlotData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    //Force close all USB related popups when USB is disconnected
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_CORRUPT_VIDEO);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_ONLY_VIDEO_CONFIRMATION);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION);

    m_eUSBSyncState = CMediaEnum::SYNC_STATE_UNKNOWN;
    m_eUSBContentType = CMediaEnum::CONTENTTYPE_U;
    m_eMediaUSBPlayBackMode = CMediaEnum::USB_PLAYBACK_UNKNOWN_MODE;
    setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
    setMediaOperationState(CMediaEnum::MEDIA_OPERATIONSTATE_NONE);
    m_iUSBFolderCount = 0;
    m_bNoSongsUSBAccepted = false;
    CHMIMain::getSM()->getSCI_Media()->set_iCurrentContentType(CMediaEnum::CONTENTTYPE_U);

    //m_listImageData.clear();
    m_pImageListModel->removeRows();
    m_iTotalImageCount = -1;
    m_iCurrentImageIndex = -1;

    m_listUSBAvailableCategories.clear();
    for(int iIndex = 0; iIndex < CMediaEnum::BROWSEITEM_END; iIndex++)
    {
        m_listUSBAvailableCategories.append(-1);
    }
}

void CMediaAdaptor::resetBTSlotData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    m_eBTSyncState = CMediaEnum::SYNC_STATE_UNKNOWN;

    m_listBTAvailableCategories.clear();
    for(int iIndex = 0; iIndex < CMediaEnum::BROWSEITEM_END; iIndex++)
    {
        m_listBTAvailableCategories.append(-1);
    }
}

QString CMediaAdaptor::getBrowseCategoryImagePath(CMediaEnum::EMediaBrowseItem eBrowseItem, bool bIsEnabled)
{
    if(bIsEnabled)
    {
        switch(eBrowseItem)
        {
        case CMediaEnum::BROWSEITEM_FOLDERS:
            return MEDIA_BROWSE_IMG_CATEGORY_FOLDERS;
            break;

        case CMediaEnum::BROWSEITEM_SONGS:
            return MEDIA_BROWSE_IMG_CATEGORY_TRACKS;
            break;

        case CMediaEnum::BROWSEITEM_ALBUMS:
            return MEDIA_BROWSE_IMG_CATEGORY_ALBUMS;
            break;

        case CMediaEnum::BROWSEITEM_ARTISTS:
            return MEDIA_BROWSE_IMG_CATEGORY_ARTISTS;
            break;

        case CMediaEnum::BROWSEITEM_GENRE:
            return MEDIA_BROWSE_IMG_CATEGORY_GENRES;
            break;

        case CMediaEnum::BROWSEITEM_PLAYLISTS:
            return MEDIA_BROWSE_IMG_CATEGORY_PLAYLIST;
            break;

        case CMediaEnum::BROWSEITEM_PICTURE:
            return MEDIA_BROWSE_IMG_CATEGORY_IMAGES;
            break;

        case CMediaEnum::BROWSEITEM_VIDEOS:
            return MEDIA_BROWSE_IMG_CATEGORY_VIDEOS;
            break;

        case CMediaEnum::BROWSEITEM_ITUNES_RADIO:
            return MEDIA_BROWSE_IMG_CATEGORY_ITUNESRADIO;
            break;

        case CMediaEnum::BROWSEITEM_AUDIOBOOK:
            return MEDIA_BROWSE_IMG_CATEGORY_AUDIO_BOOKS;
            break;

        case CMediaEnum::BROWSEITEM_PODCAST:
            return MEDIA_BROWSE_IMG_CATEGORY_PODCASTS;
            break;

        case CMediaEnum::BROWSEITEM_EPISODE:
            return MEDIA_BROWSE_IMG_CATEGORY_EPISODES;
            break;

        case CMediaEnum::BROWSEITEM_PLAYALL:
            return MEDIA_BROWSE_IMG_CATEGORY_PLAYALL;
            break;

        default:
            return MEDIA_BROWSE_IMG_CATEGORY_TRACKS; //Songs
            break;
        }
    }
    else
    {
        switch(eBrowseItem)
        {
        case CMediaEnum::BROWSEITEM_FOLDERS:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_FOLDERS;
            break;

        case CMediaEnum::BROWSEITEM_SONGS:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_TRACKS;
            break;

        case CMediaEnum::BROWSEITEM_ALBUMS:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_ALBUMS;
            break;

        case CMediaEnum::BROWSEITEM_ARTISTS:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_ARTISTS;
            break;

        case CMediaEnum::BROWSEITEM_GENRE:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_GENRES;
            break;

        case CMediaEnum::BROWSEITEM_PLAYLISTS:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_PLAYLIST;
            break;

        case CMediaEnum::BROWSEITEM_PICTURE:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_IMAGES;
            break;

        case CMediaEnum::BROWSEITEM_VIDEOS:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_VIDEOS;
            break;

        case CMediaEnum::BROWSEITEM_ITUNES_RADIO:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_ITUNESRADIO;
            break;

        case CMediaEnum::BROWSEITEM_AUDIOBOOK:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_AUDIO_BOOKS;
            break;

        case CMediaEnum::BROWSEITEM_PODCAST:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_PODCASTS;
            break;

        case CMediaEnum::BROWSEITEM_EPISODE:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_EPISODES;
            break;

        default:
            return MEDIA_BROWSE_IMG_CATEGORY_DISABLED_TRACKS; //Songs
            break;
        }
    }
}

QString CMediaAdaptor::getBrowseCategoryName(CMediaEnum::EMediaBrowseItem eBrowseItem)
{
    switch(eBrowseItem)
    {
    case CMediaEnum::BROWSEITEM_FOLDERS:
        return MEDIA_BROWSE_CATEGORY_FOLDERS;
        break;

    case CMediaEnum::BROWSEITEM_SONGS:
        return MEDIA_BROWSE_CATEGORY_TRACKS;
        break;

    case CMediaEnum::BROWSEITEM_ALBUMS:
        return MEDIA_BROWSE_CATEGORY_ALBUMS;
        break;

    case CMediaEnum::BROWSEITEM_ARTISTS:
        return MEDIA_BROWSE_CATEGORY_ARTISTS;
        break;

    case CMediaEnum::BROWSEITEM_GENRE:
        return MEDIA_BROWSE_CATEGORY_GENRES;
        break;

    case CMediaEnum::BROWSEITEM_PLAYLISTS:
        return MEDIA_BROWSE_CATEGORY_PLAYLIST;
        break;

    case CMediaEnum::BROWSEITEM_PICTURE:
        return MEDIA_BROWSE_CATEGORY_IMAGES;
        break;

    case CMediaEnum::BROWSEITEM_VIDEOS:
        return MEDIA_BROWSE_CATEGORY_VIDEOS;
        break;

    case CMediaEnum::BROWSEITEM_ITUNES_RADIO:
        return MEDIA_BROWSE_CATEGORY_ITUNESRADIO;
        break;

    case CMediaEnum::BROWSEITEM_AUDIOBOOK:
        return MEDIA_BROWSE_CATEGORY_AUDIO_BOOKS;
        break;

    case CMediaEnum::BROWSEITEM_PODCAST:
        return MEDIA_BROWSE_CATEGORY_PODCASTS;
        break;

    case CMediaEnum::BROWSEITEM_EPISODE:
        return MEDIA_BROWSE_CATEGORY_EPISODES;
        break;

    default:
        return tr("");
        break;
    }
}

void CMediaAdaptor::setMediaScreenTitle()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    switch(m_eActiveMediaSrc)
    {
    case SRC_USB1:
        m_strActiveMediaSrcTitle = "USB";
        break;
    case SRC_AUDIO_AUX:
        m_strActiveMediaSrcTitle = "AUX";
        break;
    case SRC_BT_A2DP1:
        m_strActiveMediaSrcTitle = "BT Audio";
        break;
    case SRC_IPOD:
        m_strActiveMediaSrcTitle = "iPod";
        break;
    default:
        m_strActiveMediaSrcTitle = "";
        break;
    }

    if(m_strActiveMediaSrcTitle != "")
    {
        emit sigActiveMediaSrcTitleChanged();
    }
}

void CMediaAdaptor::requestBrowseDataForPendingPage(SPageData objPageData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_pMediaResource)
    {
        m_pMediaResource->fetchItems((objPageData.m_iPageID + 1),objPageData.m_iPageSize);
        m_iCurrentBrowseIndex = objPageData.m_iPageID;
    }
}

void CMediaAdaptor::requestNowPlayingDataForPendingPage(SPageData objPageData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_pMediaResource)
    {
        m_pMediaResource->fetchItems((objPageData.m_iPageID + 1),objPageData.m_iPageSize, true);
        m_iCurrentNowPlayingIndex = objPageData.m_iPageID;
    }
}

void CMediaAdaptor::initBrowse(CMediaEnum::EMediaBrowseItem eCategory)
{
    if(m_pMediaResource)
    {
        m_pMediaResource->getCategoryRoot(static_cast<int>(eCategory), false);
    }
    else
    {
         LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s MediaResource is not created!",__FUNCTION__);
    }
}

QString CMediaAdaptor::getImageTitle(int iPvCurrentIndex)
{
    QString strImageTitle = "";
    if(m_pImageListModel)
    {
        strImageTitle = m_pImageListModel->getName(iPvCurrentIndex);
        strImageTitle = strImageTitle.mid(strImageTitle.lastIndexOf('/')+1);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Value of iPvCurrentIndex: %d, name: %s", __FUNCTION__, iPvCurrentIndex, strImageTitle.toStdString().c_str());
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Image list not created.", __FUNCTION__);
    }
    return strImageTitle;
}

void CMediaAdaptor::setNowPlayingData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if((m_pMediaResource) && (CAudioEnums::SRC_AUDIO_AUX != m_eActiveMediaSrc))
    {
        setSongTitle(QString::fromStdString(m_pMediaResource->getNowPlayingData().strTitle));
        setSongArtist(QString::fromStdString(m_pMediaResource->getNowPlayingData().strArtist));
        setSongAlbum(QString::fromStdString(m_pMediaResource->getNowPlayingData().strAlbum));
        setMediaFormat(QString::fromStdString(m_pMediaResource->getNowPlayingData().strFileName));

        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Song Title: %s",__FUNCTION__, m_strSongTitle.toStdString().c_str());

        if(CMediaEnum::BROWSEITEM_VIDEOS == static_cast<CMediaEnum::EMediaBrowseItem>(m_pMediaResource->getNowPlayingData().iMediaType))
        {
            CHMIMain::getSM()->getSCI_Media()->set_iCurrentMediaType(CMediaEnum::MEDIATYPE_VIDEOS);
            setMediaOperationState(CMediaEnum::MEDIA_OPERATIONSTATE_VIDEO);
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ Playback Started: Media Type playing: Video ]");
        }
        else
        {
            //Current metadata is not video, so setting it to default i.e. audio
            CHMIMain::getSM()->getSCI_Media()->set_iCurrentMediaType(CMediaEnum::MEDIATYPE_SONGS);
            setMediaOperationState(CMediaEnum::MEDIA_OPERATIONSTATE_AUDIO);
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ Playback Started: Media Type playing: Song ]");
        }

        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s nowPlaying MEdia Type: %d",__FUNCTION__, m_pMediaResource->getNowPlayingData().iMediaType);
        if(static_cast<CMediaEnum::EMediaBrowseItem>(m_pMediaResource->getNowPlayingData().iMediaType) != m_eNowPlayingMetadataType)
        {
            m_eNowPlayingMetadataType = static_cast<CMediaEnum::EMediaBrowseItem>(m_pMediaResource->getNowPlayingData().iMediaType);

            /** To display the speed lockout popup on receiving the nowplaying updates while speed is more than the threshold */
            if((CVehicleSettingsAdaptor::getInstance()->speedLockOutStatus()) &&
                    CMediaEnum::BROWSEITEM_VIDEOS == m_eNowPlayingMetadataType)
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s : Video speed lockout true", __FUNCTION__);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_SPEED_LOCKOUT_VIDEO);
                requestPreviousSource();
            }
            else
            {
                //Do Nothing
            }
            emit sigNowPlayingMetadataChanged();
        }

        m_bIsNowPlayingDataAvail = true;
        emit sigNowPlayingDataAvailUpdated();

        CHMIMain::getSM()->getSCI_Media()->set_isNowPlayingAvailable(m_bIsNowPlayingDataAvail);
        CHMIMain::getSM()->getSCI_Media()->raise_evNowPlayingAvailable();

        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EPopupID::EN_POPUPID_USB_ONLY_VIDEO_CONFIRMATION);
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_CORRUPT_VIDEO);

        emit sigNowPlayingChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::onTrackSessionChangedEvent()
{
    if(m_pMediaResource)
    {
        m_listNowPlaying.clear(); //Clear the list and then fetch new data
        m_pMediaResource->goToNowPlayingLevel();
    }
}

void CMediaAdaptor::setAlbumArtData(const QString &strAlbumArtPath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if("" == strAlbumArtPath)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Album art *not* available for song", __FUNCTION__);
        //Set the default album art if song does not has any album art assigned to it
        m_bDefaultAlbumArtDisplayed = true;
        m_strAlbumArtPath = DEFAULT_ALBUM_ART_PATH;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Album art available for song: %s", __FUNCTION__, strAlbumArtPath.toStdString().c_str());
        //Always display default album art in simulation
#ifdef PLATFORM_WIN32
        m_bDefaultAlbumArtDisplayed = true;
        m_strAlbumArtPath = DEFAULT_ALBUM_ART_PATH;
#else
        //Set the album art received from service
        m_bDefaultAlbumArtDisplayed = false;
        m_strAlbumArtPath = "file://" + strAlbumArtPath;
#endif
    }
    emit sigAlbumArtChanged();
}

void CMediaAdaptor::setBitRateData(const QString &strBitRate)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Bit Rate: %s",__FUNCTION__, strBitRate.toStdString().c_str());
    if(m_strBitRate != strBitRate)
    {
        m_strBitRate = strBitRate;
        emit sigBitRateChanged();
    }
}

void CMediaAdaptor::setSamplingRateData(const QString &strSamplingRate)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Bit Rate: %s",__FUNCTION__, strSamplingRate.toStdString().c_str());
    if(m_strSamplingRate != strSamplingRate)
    {
        m_strSamplingRate = strSamplingRate;
        emit sigSamplingRateChanged();
    }
}

void CMediaAdaptor::setVideoTestModeParameters()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);
    setVideoCodec(QString::fromStdString(m_pMediaResource->getVideoTestModeParameters().strVideoCodec));
    setVideoFrameRate(QString::fromStdString(m_pMediaResource->getVideoTestModeParameters().strVideoFrameRate));
    setVideoResolution(QString::fromStdString(m_pMediaResource->getVideoTestModeParameters().strVideoResolution));
    setAudioCodec(QString::fromStdString(m_pMediaResource->getVideoTestModeParameters().strAudioCodec));
    setAudioSamplingRate(QString::fromStdString(m_pMediaResource->getVideoTestModeParameters().strAudioSamplingRate));
}

void CMediaAdaptor::setVideoCodec(const QString &strVideoCodec)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Video Codec: %s",__FUNCTION__, strVideoCodec.toStdString().c_str());
    if(m_strVideoCodec != strVideoCodec)
    {
        m_strVideoCodec = strVideoCodec;
        emit sigVideoCodecChanged();
    }
}

void CMediaAdaptor::setVideoFrameRate(const QString &strVideoFrameRate)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Video Frame Rate: %s",__FUNCTION__, strVideoFrameRate.toStdString().c_str());
    if(m_strVideoFrameRate != strVideoFrameRate)
    {
        m_strVideoFrameRate = strVideoFrameRate;
        emit sigVideoFrameRateChanged();
    }
}

void CMediaAdaptor::setMediaFormat(const QString &strFileName)
{
    QString strMediaFormat = strFileName.mid(strFileName.lastIndexOf(".") + 1);
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s File Name: %s, Media Format : %s", __FUNCTION__, strFileName.toStdString().c_str(), strMediaFormat.toStdString().c_str());

    if(m_strMediaFormat != strMediaFormat)
    {
        m_strMediaFormat = strMediaFormat;
        emit sigMediaFormatChanged();
    }
}

void CMediaAdaptor::setVideoResolution(const QString &strVideoResolution)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Video Resolution: %s",__FUNCTION__, strVideoResolution.toStdString().c_str());
    if(m_strVideoResolution != strVideoResolution)
    {
        m_strVideoResolution = strVideoResolution;
        emit sigVideoResolutionChanged();
    }
}

void CMediaAdaptor::setAudioCodec(const QString &strAudioCodec)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Audio Codec: %s",__FUNCTION__, strAudioCodec.toStdString().c_str());
    if(m_strAudioCodec != strAudioCodec)
    {
        m_strAudioCodec = strAudioCodec;
        emit sigAudioCodecChanged();
    }
}

void CMediaAdaptor::setAudioSamplingRate(const QString &strAudioSamplingRate)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Audio Sampling Rate: %s",__FUNCTION__, strAudioSamplingRate.toStdString().c_str());
    if(m_strAudioSamplingRate != strAudioSamplingRate)
    {
        m_strAudioSamplingRate = strAudioSamplingRate;
        emit sigAudioSamplingRateChanged();
    }
}

void CMediaAdaptor::setMediaBrowseDataState(CMediaEnum::EMediaBrowseDataState eMediaBrowseDataState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s eMediaBrowseDataState set: %d", __FUNCTION__, eMediaBrowseDataState);
    m_eMediaBrowseDataState = eMediaBrowseDataState;
    emit sigBrowseDataStateUpdated();
}

//Setter functions invoked from CMediaEventHandler
void CMediaAdaptor::setPlayState(const int &iPlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Play state received: %d", __FUNCTION__, iPlayState);
    if(static_cast<CMediaEnum::EMediaPlayStates>(iPlayState) != m_ePlayState)
    {
        m_ePlayState = static_cast<CMediaEnum::EMediaPlayStates>(iPlayState);
        emit sigPlayStateChanged();

        switch(m_ePlayState)
        {
        case CMediaEnum::PLAYSTATE_PAUSED:
        case CMediaEnum::PLAYSTATE_STOPPED:{
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ playback status - paused / stopped ]");
            m_bIsMediaAudioPlaying = false;
            emit sigIsMediaAudioPlayingChanged();
        }
            break;

        case CMediaEnum::PLAYSTATE_PLAYING:{
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ playback status - playing ]");
            m_bIsMediaAudioPlaying = true;
            emit sigIsMediaAudioPlayingChanged();
        }
            break;

        default:{
            //Do nothing...no action to be taken for rest of play states
        }
            break;
        }
    }
}

void CMediaAdaptor::setShuffleMode(const int &iShuffleMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s shuffleMode received as: %d",__FUNCTION__,iShuffleMode);
    if(static_cast<CMediaEnum::EMediaShuffleMode>(iShuffleMode) != m_eShuffleMode)
    {
        m_eShuffleMode = static_cast<CMediaEnum::EMediaShuffleMode>(iShuffleMode);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s shuffleMode received as set in adaptor as : %d",__FUNCTION__,m_eShuffleMode);
        emit sigShuffleModeChanged();
    }
}

void CMediaAdaptor::setRepeatMode(const int &iRepeatMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s repeatMode received as: %d",__FUNCTION__,iRepeatMode);
    if(static_cast<CMediaEnum::EMediaRepeatMode>(iRepeatMode) != m_eRepeatMode)
    {
        m_eRepeatMode = static_cast<CMediaEnum::EMediaRepeatMode>(iRepeatMode);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s repeatMode received in adaptor as : %d",__FUNCTION__,m_eRepeatMode);
        emit sigRepeatModeChanged();
    }
}

void CMediaAdaptor::setPlayTime(const uint64_t &uiPlayTime)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(uiPlayTime != m_uiPlayTime)
    {
        m_uiPlayTime = uiPlayTime;
        m_strFormattedPlayTime = getFormattedTime(uiPlayTime);
        emit sigPlayTimeChanged();
        emit sigFormattedPlayTimeChanged();
    }

    /*Media service sends playtime(0) at the start of any media source
     * and we have to ignore this playtime so a jump is not observed on progressbar
    **/
    if((!m_bShowPlaytime) && (m_bIsNowPlayingDataAvail) && (m_uiTotalDuration > 0))
    {
        showPlayTime(true);
    }
}

void CMediaAdaptor::setTotalDuration(const uint64_t &uiTotalDuration)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(uiTotalDuration != m_uiTotalDuration)
    {
        /**
         * @note: Hiding Play time, Total Duration and Slider handle in Media screen qml when Total duration is received as 0
         */
        if(uiTotalDuration == 0)
        {
            showPlayTime(false);
        }
        m_uiTotalDuration = uiTotalDuration;
        m_strFormattedTotalDuration = getFormattedTime(uiTotalDuration);
        emit sigTotalDurationChanged();
        emit sigFormattedTotalDurationChanged();
    }
}

void CMediaAdaptor::setTrackNumber(const uint64_t &uiTrackNumber)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Track Number playing: %d",__FUNCTION__, static_cast<int>(uiTrackNumber));
    m_iCurrentTrackIndex = static_cast<int>(uiTrackNumber);
}

//Media service API's invoked from HMI
void CMediaAdaptor::next(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: eButtonState: %d", __FUNCTION__,eButtonState);

    if(m_pMediaResource)
    {
        if(CAudioEnums::SRC_AUDIO_AUX == m_eActiveMediaSrc)
        {
            //Do nothing
        }
        else if((CAudioEnums::SRC_BT_A2DP1 == m_eActiveMediaSrc && m_bIsNextPrevSupported) || (CAudioEnums::SRC_BT_A2DP1 != m_eActiveMediaSrc))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ Next track request]");
            m_pMediaResource->next(eButtonState);
        }
        else
        {
            //Do nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::prev(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: eButtonState: %d", __FUNCTION__,eButtonState);

    if(m_pMediaResource)
    {
        if(CAudioEnums::SRC_AUDIO_AUX == m_eActiveMediaSrc)
        {
            //Do nothing
        }
        else if((CAudioEnums::SRC_BT_A2DP1 == m_eActiveMediaSrc && m_bIsNextPrevSupported) || (CAudioEnums::SRC_BT_A2DP1 != m_eActiveMediaSrc))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ Prev track request]");
            m_pMediaResource->prev(eButtonState);
        }
        else
        {
            //Do nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::resume(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: eButtonState: %d", __FUNCTION__,eButtonState);

    if(m_pMediaResource)
    {
        if(CAudioEnums::SRC_AUDIO_AUX == m_eActiveMediaSrc)
        {
            //Do nothing
        }
        else if((CAudioEnums::SRC_BT_A2DP1 == m_eActiveMediaSrc && m_bIsPlayPauseSupported) || (CAudioEnums::SRC_BT_A2DP1 != m_eActiveMediaSrc))
        {
            if((CAudioEnums::SRC_USB1 == m_eActiveMediaSrc) && (CPopupEnum::EN_POPUPID_USB_CORRUPT_VIDEO == CPopupManager::getInstance()->getCurrentDisplayedPopup()))
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - resume ignored as corrupt video poup is active", __FUNCTION__);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ Resume initiated ]");
                m_pMediaResource->resume(eButtonState);
            }
        }
        else
        {
            //Do nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::pause(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: eButtonState: %d", __FUNCTION__,eButtonState);
    if(m_pMediaResource)
    {
        if((CAudioEnums::SRC_BT_A2DP1 == m_eActiveMediaSrc && m_bIsPlayPauseSupported) || (CAudioEnums::SRC_BT_A2DP1 != m_eActiveMediaSrc))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ Pause initiated ]");
            m_pMediaResource->pause(eButtonState);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::fastForward(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: eButtonState: %d", __FUNCTION__,eButtonState);

    if(m_pMediaResource)
    {
        if(CAudioEnums::SRC_AUDIO_AUX == m_eActiveMediaSrc)
        {
            //Do nothing
        }
        else if((CAudioEnums::SRC_BT_A2DP1 == m_eActiveMediaSrc && m_bIsFwdRwdSupported) || (CAudioEnums::SRC_BT_A2DP1 != m_eActiveMediaSrc))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ FastForward initiated ]");
            m_pMediaResource->fastForward(eButtonState);
        }
        else
        {
            //Do nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::fastRewind(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: eButtonState: %d", __FUNCTION__,eButtonState);

    if(m_pMediaResource)
    {
        if(CAudioEnums::SRC_AUDIO_AUX == m_eActiveMediaSrc)
        {
            //Do nothing
        }
        else if((CAudioEnums::SRC_BT_A2DP1 == m_eActiveMediaSrc && m_bIsFwdRwdSupported) || (CAudioEnums::SRC_BT_A2DP1 != m_eActiveMediaSrc))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"[KPI_MARKER][HMI][ FastRewind initiated ]");
            m_pMediaResource->fastRewind(eButtonState);
        }
        else
        {
            //Do nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::toggleResumePause(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: eButtonState: %d", __FUNCTION__,eButtonState);
    if(m_pMediaResource)
    {
        if(m_ePlayState == CMediaEnum::EMediaPlayStates::PLAYSTATE_PLAYING)
        {
            pause(eButtonState);
        }
        else if(m_ePlayState == CMediaEnum::EMediaPlayStates::PLAYSTATE_PAUSED)
        {
            resume(eButtonState);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s | %i play state not handled",__FUNCTION__,m_ePlayState);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::toggleShuffleMode(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: eButtonState: %d", __FUNCTION__,eButtonState);
    if(m_pMediaResource)
    {
        m_pMediaResource->toggleShuffle(eButtonState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::seekToTime(uint uiSeekToTime)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_pMediaResource)
    {
        setPlayTime(uiSeekToTime); //This shall ensure that progress bar thumb does not jumps between previous and new playTime
        m_pMediaResource->seekToTime(uiSeekToTime);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::toggleRepeatMode(CMediaEnum::EButtonStates eButtonState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: eButtonState: %d", __FUNCTION__,eButtonState);
    if(m_pMediaResource)
    {
        m_pMediaResource->toggleRepeat(eButtonState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::updateMediaBrowseList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    m_pBrowseList->removeRows();

    switch(m_eActiveMediaSrc)
    {
    case SRC_USB1:
    {
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_FOLDERS,MEDIA_BROWSE_IMG_CATEGORY_FOLDERS,CMediaEnum::BROWSEITEM_FOLDERS);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_TRACKS,MEDIA_BROWSE_IMG_CATEGORY_TRACKS,CMediaEnum::BROWSEITEM_SONGS);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_ALBUMS,MEDIA_BROWSE_IMG_CATEGORY_ALBUMS,CMediaEnum::BROWSEITEM_ALBUMS);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_PLAYLIST,MEDIA_BROWSE_IMG_CATEGORY_PLAYLIST,CMediaEnum::BROWSEITEM_PLAYLISTS);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_ARTISTS,MEDIA_BROWSE_IMG_CATEGORY_ARTISTS,CMediaEnum::BROWSEITEM_ARTISTS);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_GENRES,MEDIA_BROWSE_IMG_CATEGORY_GENRES,CMediaEnum::BROWSEITEM_GENRE);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_VIDEOS,MEDIA_BROWSE_IMG_CATEGORY_VIDEOS,CMediaEnum::BROWSEITEM_VIDEOS);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_IMAGES,MEDIA_BROWSE_IMG_CATEGORY_IMAGES,CMediaEnum::BROWSEITEM_PICTURE);
    }
        break;
    case SRC_IPOD:
    {
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_ALBUMS,MEDIA_BROWSE_IMG_CATEGORY_ALBUMS,CMediaEnum::BROWSEITEM_ALBUMS);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_TRACKS,MEDIA_BROWSE_IMG_CATEGORY_TRACKS,CMediaEnum::BROWSEITEM_SONGS);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_ARTISTS,MEDIA_BROWSE_IMG_CATEGORY_ARTISTS,CMediaEnum::BROWSEITEM_ARTISTS);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_PLAYLIST,MEDIA_BROWSE_IMG_CATEGORY_PLAYLIST,CMediaEnum::BROWSEITEM_PLAYLISTS);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_GENRES,MEDIA_BROWSE_IMG_CATEGORY_GENRES,CMediaEnum::BROWSEITEM_GENRE);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_AUDIO_BOOKS,MEDIA_BROWSE_IMG_CATEGORY_AUDIO_BOOKS,CMediaEnum::BROWSEITEM_AUDIOBOOK);
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_PODCASTS,MEDIA_BROWSE_IMG_CATEGORY_PODCASTS,CMediaEnum::BROWSEITEM_PODCAST);

        if(isUSBDeviceCategoryAvailable(CMediaEnum::BROWSEITEM_ITUNES_RADIO))
        {
            m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_ITUNESRADIO,MEDIA_BROWSE_IMG_CATEGORY_ITUNESRADIO,CMediaEnum::BROWSEITEM_ITUNES_RADIO);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - iTunes Radio not available",__FUNCTION__);
        }
    }
        break;
    case SRC_BT_A2DP1:
    {
        m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_FOLDERS,MEDIA_BROWSE_IMG_CATEGORY_FOLDERS,CMediaEnum::BROWSEITEM_FOLDERS);
        /*m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_TRACKS,MEDIA_BROWSE_IMG_CATEGORY_TRACKS,CMediaEnum::BROWSEITEM_SONGS);
            m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_ALBUMS,MEDIA_BROWSE_IMG_CATEGORY_ALBUMS,CMediaEnum::BROWSEITEM_ALBUMS);
            m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_ARTISTS,MEDIA_BROWSE_IMG_CATEGORY_ARTISTS,CMediaEnum::BROWSEITEM_ARTISTS);
            m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_PLAYLIST,MEDIA_BROWSE_IMG_CATEGORY_PLAYLIST,CMediaEnum::BROWSEITEM_PLAYLISTS);
            m_pBrowseList->insertRows(MEDIA_BROWSE_CATEGORY_GENRES,MEDIA_BROWSE_IMG_CATEGORY_GENRES,CMediaEnum::BROWSEITEM_GENRE);*/
    }
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s Active Ent. Source neither of 3 - SRC_USB1,SRC_IPOD,SRC_BT_A2DP1",__FUNCTION__);
        break;
    }
}

void CMediaAdaptor::sltAuxGainValueChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(nullptr != m_pSetupAUXGainListModel)
    {
        m_pSetupAUXGainListModel->updateSetupModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE, CAudioAdaptor::getInstance()->auxGainValue(), true, CSetupEnums::SETUP_SCREEN_AUX_IN_GAIN);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s : m_pSetupAUXGainListModel is NULL:", __FUNCTION__);
    }
}

void CMediaAdaptor::sltSpeedLockOutStatusChanged()
{
    if((CAudioEnums::SRC_USB1 == m_eActiveMediaSrc) && (CVehicleSettingsAdaptor::getInstance()->speedLockOutStatus()))
    {
        if(CMediaEnum::BROWSEITEM_VIDEOS == m_eNowPlayingMetadataType)
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s : Video speed lockout true", __FUNCTION__);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_SPEED_LOCKOUT_VIDEO);
            requestPreviousSource();
        }
        else if(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture))
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_SPEED_LOCKOUT_IMAGES);
            if(CMediaEnum::CONTENTTYPE_I == m_eUSBContentType)
            {
                //USB with only images, hence switching to previous source
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s : PV speed lockout true", __FUNCTION__);
                requestPreviousSource();
            }
            else
            {
                //USb has songs and/or videos along with images, hence switching to previous screen
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s : PV speed lockout true - evBack", __FUNCTION__);
                CHMIMain::getSM()->raise_evBackPressed();
            }
        }
    }
}

void CMediaAdaptor::sltProcessHideDrawers()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);

    if (CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo))
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evHideDrawers();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Video State not active, So Drawers will not be hide.", __FUNCTION__);
    }
}

void CMediaAdaptor::sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: ePopupId: %d, ePopupResult: %d", __FUNCTION__, ePopupId, ePopupResult);

    switch(ePopupId)
    {
    case CPopupEnum::EPopupID::EN_POPUPID_USB_CORRUPT_VIDEO:
    {
        if((CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT == ePopupResult)
                || (CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TOUCH == ePopupResult)
                || (CPopupEnum::EN_POPUP_RESULT_IGNORED == ePopupResult)
                || (CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_SUPERSEDE == ePopupResult))
        {
            if(CMediaEnum::CONTENTTYPE_V == m_eUSBContentType || CMediaEnum::CONTENTTYPE_SVI == m_eUSBContentType
                    || CMediaEnum::CONTENTTYPE_VI == m_eUSBContentType || CMediaEnum::CONTENTTYPE_SV == m_eUSBContentType)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Auto next on popup timeout", __FUNCTION__);
                next(CMediaEnum::EN_BUTTON_STATE_RELEASED);
            }
            else
            {
                handleAllVideosCorrupt();
            }
        }
        else if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_HK == ePopupResult)
        {
            if(CMediaEnum::CONTENTTYPE_V == m_eUSBContentType || CMediaEnum::CONTENTTYPE_SVI == m_eUSBContentType
                    || CMediaEnum::CONTENTTYPE_VI == m_eUSBContentType || CMediaEnum::CONTENTTYPE_SV == m_eUSBContentType)
            {
                if((QString::number(CHardKeyEnum::KEYCODEHK_SEEKUP) == strAdditionalInfo) || ((QString::number(CHardKeyEnum::KEYCODESWC_NEXT) == strAdditionalInfo))
                        ||(QString::number(CHardKeyEnum::KEYCODEHK_SEEKDOWN) == strAdditionalInfo) || ((QString::number(CHardKeyEnum::KEYCODESWC_PREV) == strAdditionalInfo)))
                {
                    //Do nothing.
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: No Action taken on Next and Prev Hardkey ", __FUNCTION__);

                }
                else
                {
                    next(CMediaEnum::EN_BUTTON_STATE_RELEASED);
                }
            }
        }
        else
        {
            //Do nothing
        }
    }
        break;

    case CPopupEnum::EPopupID::EN_POPUPID_USB_ONLY_VIDEO_CONFIRMATION:
    case CPopupEnum::EPopupID::EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION:
    {
        if((CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT == ePopupResult)
                || (CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TOUCH == ePopupResult)
                || (CPopupEnum::EN_POPUP_RESULT_IGNORED == ePopupResult)
                || (CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_SUPERSEDE == ePopupResult))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Switch to prev source on popup timeout/soft-touch", __FUNCTION__);
            if((!m_bIsNowPlayingDataAvail) &&
                    (CMediaEnum::MEDIA_DISPLAYSTATE_PICTURES != getMediaDisplayState()))
            {
                requestPreviousSource();
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Not switching to prev source.", __FUNCTION__);
            }
        }
        else if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_HK == ePopupResult)
        {
            if((CHardKeyEnum::KEYCODEHK_FAVORITE == static_cast<CHardKeyEnum::EHardKeys>(strAdditionalInfo.toInt()))
                    && (CHardKeyEnum::FAV_HK_SOURCE == CHomeAdaptor::getInstance().eCurrentFavKeyCode()))
            {
                //Do nothing
            }
            else if(CHardKeyEnum::KEYCODESWC_SOURCE == static_cast<CHardKeyEnum::EHardKeys>(strAdditionalInfo.toInt()))
            {
                //Do nothing
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Switch to prev source on HK action", __FUNCTION__);
                requestPreviousSource();
            }
        }
        else
        {
            //Do nothing
        }
    }
        break;

    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA, "%s: In Default case.", __FUNCTION__);
    }
        break;
    }
}

void CMediaAdaptor::sltPowerModeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(CPowerModeEnums::VPM_EARLY_WAKEUP == CPowerModeAdaptor::getInstance().getPowerModeStatus()
            || CPowerModeEnums::VPM_MEDIA_OFF == CPowerModeAdaptor::getInstance().getPowerModeStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Reset noSongsUSBResponse",__FUNCTION__);
        setNoSongsUSBResponse(false);
    }
}

void CMediaAdaptor::sltPreviewTimeout()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    m_strSongPreviewText = "";
    m_ePreviewMode = CMediaEnum::PREVIEW_MODE_NONE;
    emit sigPreviewTextChanged();
    emit sigSongPreviewChanged();
}

void CMediaAdaptor::remotePlayerCapabilitiesUpdate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_pMediaResource)
    {
        if(m_pMediaResource->getRemotePlayerCapabilities().bIsPlayPauseSupported != m_bIsPlayPauseSupported)
        {
            m_bIsPlayPauseSupported = m_pMediaResource->getRemotePlayerCapabilities().bIsPlayPauseSupported;
            emit sigIsPlayPauseSupportedChanged();
        }

        if(m_pMediaResource->getRemotePlayerCapabilities().bIsNextPrevSupported != m_bIsNextPrevSupported)
        {
            m_bIsNextPrevSupported = m_pMediaResource->getRemotePlayerCapabilities().bIsNextPrevSupported;
            emit sigIsNextPrevSupportedChanged();
        }

        if(m_pMediaResource->getRemotePlayerCapabilities().bIsRandomSupported != m_bIsRandomSupported)
        {
            m_bIsRandomSupported = m_pMediaResource->getRemotePlayerCapabilities().bIsRandomSupported;
            emit sigIsRandomSupportedChanged();
        }

        if(m_pMediaResource->getRemotePlayerCapabilities().bIsRepeatSupported != m_bIsRepeatSupported)
        {
            m_bIsRepeatSupported = m_pMediaResource->getRemotePlayerCapabilities().bIsRepeatSupported;
            emit sigIsRepeatSupportedChanged();
        }

        if(m_pMediaResource->getRemotePlayerCapabilities().bIsBrowseSupported != m_bIsBrowseSupported)
        {
            m_bIsBrowseSupported = m_pMediaResource->getRemotePlayerCapabilities().bIsBrowseSupported;
            emit sigIsBrowseSupportedChanged();
        }

        if(m_pMediaResource->getRemotePlayerCapabilities().bIsFwdRwdSupported != m_bIsFwdRwdSupported)
        {
            m_bIsFwdRwdSupported = m_pMediaResource->getRemotePlayerCapabilities().bIsFwdRwdSupported;
            emit sigIsFwdRwdSupportedChanged();
        }

        //Need below logs for debugging purposes
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - PlayPause supported: %d", __FUNCTION__, m_bIsPlayPauseSupported);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - NextPrev supported: %d", __FUNCTION__, m_bIsNextPrevSupported);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - FwdRwd supported: %d", __FUNCTION__, m_bIsFwdRwdSupported);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Shuffle supported: %d", __FUNCTION__, m_bIsRandomSupported);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Repeat supported: %d", __FUNCTION__, m_bIsRepeatSupported);
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - BT Browsing supported: %d", __FUNCTION__, m_bIsBrowseSupported);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - m_pMediaResource is null",__FUNCTION__);
    }
}

void CMediaAdaptor::showPlayTime(bool bShowPlaytime)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s bShowPlaytime: %d",__FUNCTION__,bShowPlaytime);

    if(m_bShowPlaytime != bShowPlaytime)
    {
        m_bShowPlaytime = bShowPlaytime;
        emit sigIsPlaytimeReceivedChanged();
    }
}

void CMediaAdaptor::setBTMetadataAvailabilityStatus(int iMetaDataAvailablityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s iMetaDataAvailablityStatus: %d",__FUNCTION__,iMetaDataAvailablityStatus);
    if(iMetaDataAvailablityStatus != m_eBTMetadataAvailabilityStatus)
    {
        m_eBTMetadataAvailabilityStatus = static_cast<CMediaEnum::EMediaMetadataAvailabilityStatus>(iMetaDataAvailablityStatus);
        //emit sigBTMetadataAvailabilityStatusChanged(); //Disabling qProp as it is no more required

        if(CMediaEnum::MEDIA_METADATA_STATUS_NOT_AVAILABLE == m_eBTMetadataAvailabilityStatus)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - HMI to display - playing from phone",__FUNCTION__);
            //Setting empty now playing values so that screen transition happens
            setSongTitle("Play from Phone");
            setSongArtist("");
            setSongAlbum("");

            CHMIMain::getSM()->getSCI_Media()->set_iCurrentMediaType(CMediaEnum::MEDIATYPE_SONGS);
            m_eNowPlayingMetadataType = CMediaEnum::BROWSEITEM_SONGS;
            emit sigNowPlayingMetadataChanged();

            m_bIsNowPlayingDataAvail = true;
            CHMIMain::getSM()->getSCI_Media()->set_isNowPlayingAvailable(m_bIsNowPlayingDataAvail);
            CHMIMain::getSM()->getSCI_Media()->raise_evNowPlayingAvailable();
        }
        else
        {
            //Do nothing....nowPlaying is expected from service
        }
    }
}

CMediaEnum::EMediaBrowseItem CMediaAdaptor::getMediaBrowseItemSelected()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s m_eMediaBrowseItemSelected: %d", __FUNCTION__, m_eMediaBrowseItemSelected);
    return m_eMediaBrowseItemSelected;
}

void CMediaAdaptor::setMediaBrowseItemSelected(CMediaEnum::EMediaBrowseItem eBrowseCategorySelected)
{
    m_eMediaBrowseItemSelected = eBrowseCategorySelected;
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s m_eMediaBrowseItemSelected: %d", __FUNCTION__, m_eMediaBrowseItemSelected);
}

void CMediaAdaptor::updateRvcState(bool bRvcStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s rvcStatus: %d", __FUNCTION__, bRvcStatus);
    if(m_pMediaResource)
    {
        m_pMediaResource->updateRvcState(bRvcStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"CMediaAdaptor::m_pMediaResource is null");
    }
}

void CMediaAdaptor::updateNowPlayingPointer(int iPrevIndex, int iNewIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s iPrevIndex: %d iNewIndex: %d", __FUNCTION__, iPrevIndex,iNewIndex);

    SBrowseCategoryData objBrowseData;

    objBrowseData = m_pBrowseCategoryList->getBrowseDataFromIndex(iPrevIndex);
    objBrowseData.m_bIsActive = false;
    if(m_pBrowseCategoryList)
    {
        m_pBrowseCategoryList->updateBrowseList(iPrevIndex,objBrowseData);
    }

    objBrowseData = m_pBrowseCategoryList->getBrowseDataFromIndex(iNewIndex);
    objBrowseData.m_bIsActive = true;
    if(m_pBrowseCategoryList)
    {
        m_pBrowseCategoryList->updateBrowseList(iNewIndex,objBrowseData);
    }

    emit sigUpdateNowPlayingPointer(iPrevIndex, iNewIndex);
}

void CMediaAdaptor::handleVideoSurface(bool bVideoSurfaceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s: Video surface status: %d", __FUNCTION__, bVideoSurfaceStatus);

    if(m_pMediaResource)
    {
        m_pMediaResource->handleVideoSurface(bVideoSurfaceStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA, "%s: CMediaAdaptor::handleVideoSurface, m_pMediaResource is null", __FUNCTION__);
    }
}


void CMediaAdaptor::storeImageData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if((m_pMediaResource) && (m_pImageListModel) && (m_pImageListModel->rowCount() != static_cast<int>(m_pMediaResource->getImageDataList().size())))
    {
        m_listImageData.clear();
        QString strImagePath="";
        m_pImageListModel->removeRows();
        int iSize = static_cast<int>(m_pMediaResource->getImageDataList().size());
        for(int iIndex = 0; iIndex < iSize; iIndex++)
        {
            strImagePath = "file://" + QString::fromStdString(m_pMediaResource->getImageDataList().at(iIndex));
            //m_listImageData.append("file://" + QString::fromStdString(m_pMediaResource->getImageDataList().at(iIndex)));
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - %s",__FUNCTION__, strImagePath.toStdString().c_str() );
            m_pImageListModel->insertRows("",strImagePath,CMediaEnum::BROWSEITEM_PICTURE);
        }

        m_iTotalImageCount = m_pImageListModel->rowCount();

        //Below conditions are specifically for TSR image viewer feature
        if((-1 == m_iCurrentImageIndex) || (m_iCurrentImageIndex > m_iTotalImageCount))
        {
            m_iCurrentImageIndex = 0;
        }
        else
        {
            //Do nothing
        }

        emit sigTotalImageCountChanged();
        emit sigPvImageListChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - m_pMediaResource is null",__FUNCTION__);
    }
}

void CMediaAdaptor::storeBrowseData(int iStartIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : iStartIndex: %d", __FUNCTION__,iStartIndex);
    m_iCurrentBrowseIndex = iStartIndex-1;
    if(m_pMediaResource)
    {
        int iSize = static_cast<int>(m_pMediaResource->getBrowseDataList().size());
        SBrowseCategoryData objBrowseData;

        if(iSize > 0)
        {
            if(CMediaEnum::BROWSEITEM_FOLDERS == static_cast<CMediaEnum::EMediaBrowseItem>(m_pMediaResource->getBrowseDataList().at(0).iMetadataType))
            {
                for(int iIndex = 0; iIndex < iSize; iIndex++)
                {
                    objBrowseData.m_iCategoryItemId = m_pMediaResource->getBrowseDataList().at(iIndex).iFileID;
                    objBrowseData.m_eCategoryItemType = static_cast<CMediaEnum::EMediaBrowseItem>(m_pMediaResource->getBrowseDataList().at(iIndex).iMetadataType);
                    objBrowseData.m_strCategoryItemText = QString::fromStdString(m_pMediaResource->getBrowseDataList().at(iIndex).strValue);
                    objBrowseData.m_strCategoryImage = getBrowseCategoryImagePath(static_cast<CMediaEnum::EMediaBrowseItem>(m_pMediaResource->getBrowseDataList().at(iIndex).iMetadataType), true);
                    objBrowseData.m_bIsActive = m_pMediaResource->getBrowseDataList().at(iIndex).bIsActive;
                    objBrowseData.m_iFSContentType = m_pMediaResource->getBrowseDataList().at(iIndex).iFSContentType;

                    if(m_pBrowseCategoryList)
                    {
                        m_pBrowseCategoryList->updateBrowseList(iIndex+m_iCurrentBrowseIndex,objBrowseData);
                    }

                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_strCategoryItemText - %s",__FUNCTION__, objBrowseData.m_strCategoryItemText.toStdString().c_str());
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_iCategoryItemId - %d",__FUNCTION__, objBrowseData.m_iCategoryItemId);
                }
            }
            else
            {
                CMediaEnum::EMediaBrowseItem eCategoryItemType = static_cast<CMediaEnum::EMediaBrowseItem>(m_pMediaResource->getBrowseDataList().at(0).iMetadataType);
                QString strCategoryImage;
                int iFSContentType = m_pMediaResource->getBrowseDataList().at(0).iFSContentType;

                if((0 == m_iCurrentBrowseIndex)
                        && (CMediaEnum::BROWSEITEM_ALBUMS == eCategoryItemType
                            || CMediaEnum::BROWSEITEM_ARTISTS == eCategoryItemType
                            || CMediaEnum::BROWSEITEM_GENRE == eCategoryItemType))
                {
                    //Adding play all item to the list
                    objBrowseData.m_iCategoryItemId = m_pMediaResource->getBrowseDataList().at(0).iFileID;
                    objBrowseData.m_eCategoryItemType = CMediaEnum::BROWSEITEM_PLAYALL;
                    objBrowseData.m_strCategoryItemText = QString::fromStdString(m_pMediaResource->getBrowseDataList().at(0).strValue);
                    objBrowseData.m_strCategoryImage = getBrowseCategoryImagePath(CMediaEnum::BROWSEITEM_PLAYALL);
                    objBrowseData.m_bIsActive = m_pMediaResource->getBrowseDataList().at(0).bIsActive;
                    objBrowseData.m_iFSContentType = iFSContentType;

                    if(m_pBrowseCategoryList)
                    {
                        m_pBrowseCategoryList->updateBrowseList(0,objBrowseData);
                    }

                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_strCategoryItemText - %s",__FUNCTION__, objBrowseData.m_strCategoryItemText.toStdString().c_str());
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_iCategoryItemId - %d",__FUNCTION__, objBrowseData.m_iCategoryItemId);
                }
                else
                {
                    //Do nothing
                }

                //Reset the values as the list is of same type
                strCategoryImage = getBrowseCategoryImagePath(eCategoryItemType, true);

                int iStartIndex = (CMediaEnum::BROWSEITEM_PLAYALL == objBrowseData.m_eCategoryItemType) ? 1 : 0;
                for(int iIndex = iStartIndex; iIndex < iSize; iIndex++)
                {
                    objBrowseData.m_iCategoryItemId = m_pMediaResource->getBrowseDataList().at(iIndex).iFileID;
                    objBrowseData.m_eCategoryItemType = eCategoryItemType;
                    objBrowseData.m_strCategoryItemText = QString::fromStdString(m_pMediaResource->getBrowseDataList().at(iIndex).strValue);
                    objBrowseData.m_strCategoryImage = strCategoryImage;
                    objBrowseData.m_bIsActive = m_pMediaResource->getBrowseDataList().at(iIndex).bIsActive;
                    objBrowseData.m_iFSContentType = iFSContentType;

                    if(m_pBrowseCategoryList)
                    {
                        m_pBrowseCategoryList->updateBrowseList(iIndex+m_iCurrentBrowseIndex,objBrowseData);
                    }

                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_strCategoryItemText - %s",__FUNCTION__, objBrowseData.m_strCategoryItemText.toStdString().c_str());
                    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - m_iCategoryItemId - %d",__FUNCTION__, objBrowseData.m_iCategoryItemId);
                }

                emit sigBrowseDataReceived(static_cast<int>(eCategoryItemType));
            }
        }

        if( CMediaEnum::BROWSEDATA_STATE_AVAILABLE != m_eMediaBrowseDataState)
        {
            setMediaBrowseDataState(CMediaEnum::BROWSEDATA_STATE_AVAILABLE);
        }

        if(CMediaEnum::VR_BROWSE_STATE_PROCESSING == getMediaVRBrowseState())
        {
            CVRAdaptor::getInstance()->mediaVRBrowseReqStatus(CMediaEnum::VR_BROWSE_STATE_SUCCESS);
            setMediaVRBrowseState(CMediaEnum::VR_BROWSE_STATE_NONE);
        }
        else
        {
            //Do nothing
        }

        if(m_iRequestFailedStartIndex != -1)
        {
            requestPage(m_iRequestFailedStartIndex-1);
            setFailedRequestStartIndex(-1);
        }
        else
        {
            m_objWindowingHelperForBrowse.requestNextPage(m_iCurrentBrowseIndex);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - m_pMediaResource is null",__FUNCTION__);
    }
}

void CMediaAdaptor::emptyListReceived(int iStartIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : iStartIndex: %d", __FUNCTION__,iStartIndex);
    m_objWindowingHelperForBrowse.requestFailed(iStartIndex-1);

    setFailedRequestStartIndex(iStartIndex);
}

void CMediaAdaptor::createBrowseList(int iBrowseCategoryListSize)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    m_pBrowseCategoryList->removeRows();
    for(int iIndex = 0; iIndex < iBrowseCategoryListSize; iIndex++)
    {
        SBrowseCategoryData objBrowseData;

        if(m_pBrowseCategoryList)
        {
            m_pBrowseCategoryList->insertRows(objBrowseData);
        }
    }

    m_objWindowingHelperForBrowse.resetWindowingParam();

    /**
     * @note WINDOW_BUFFER_SIZE value is currently set to 100.
     *       This could be changed in future depending on the list response experience.
     */
    m_objWindowingHelperForBrowse.initializeWindowingParam(std::bind(&CMediaAdaptor::requestBrowseDataForPendingPage,this,_1),WINDOW_BUFFER_SIZE,iBrowseCategoryListSize);
}

void CMediaAdaptor::createNowPlayingList(int iNowPlayingListSize)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Total preview items: %d",__FUNCTION__, iNowPlayingListSize);
    m_listNowPlaying.clear();
    m_iCurrentNowPlayingIndex = -1;
    for(int iIndex = 0; iIndex < iNowPlayingListSize; iIndex++)
    {
        //Creating empty list for now
        SBrowseCategoryData objPreviewData;
        m_listNowPlaying.append(objPreviewData);
    }

    m_objWindowingHelperForNowPlayingList.resetWindowingParam();

    /**
     * @note WINDOW_BUFFER_SIZE value is currently set to 100.
     *       This could be changed in future depending on the list response experience.
     */
    m_objWindowingHelperForNowPlayingList.initializeWindowingParam(std::bind(&CMediaAdaptor::requestNowPlayingDataForPendingPage,this,_1),WINDOW_BUFFER_SIZE,iNowPlayingListSize);

}


void CMediaAdaptor::storeNowPlayingList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    if(m_pMediaResource)
    {
        const vector<MediaBrowseData> &vecBrowseData = m_pMediaResource->getBrowseDataList();
        int iSize = static_cast<int>(vecBrowseData.size());
        for(int iIndex = 0; iIndex < iSize; iIndex++)
        {
            int iActualIndex = iIndex + m_iCurrentNowPlayingIndex;
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - %d",__FUNCTION__, iActualIndex);
            if((iActualIndex >= 0) && (iActualIndex < m_listNowPlaying.size()) )
            {
                m_listNowPlaying[iActualIndex].m_iCategoryItemId = vecBrowseData.at(iIndex).iFileID;
                m_listNowPlaying[iActualIndex].m_strCategoryItemText = QString::fromStdString(vecBrowseData.at(iIndex).strValue);
                m_listNowPlaying[iActualIndex].m_bIsActive = vecBrowseData.at(iIndex).bIsActive;
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: Index: %d, Title: %s", __FUNCTION__, iActualIndex, m_listNowPlaying[iActualIndex].m_strCategoryItemText.toStdString().c_str());
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Index out of bounds %d",__FUNCTION__, iActualIndex);
            }
        }

        m_objWindowingHelperForNowPlayingList.requestNextPage(m_iCurrentNowPlayingIndex);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - m_pMediaResource is null",__FUNCTION__);
    }
}

void CMediaAdaptor::browseItemEmpty()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(CMediaEnum::VR_BROWSE_STATE_PROCESSING == getMediaVRBrowseState())
    {
        CVRAdaptor::getInstance()->mediaVRBrowseReqStatus(CMediaEnum::VR_BROWSE_STATE_FAILED);
        setMediaVRBrowseState(CMediaEnum::VR_BROWSE_STATE_NONE);
    }
    else
    {
        //Do nothing
    }

    //Show popup for item whose count is received as 0
    if(CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
    {
        if(m_eUSBSyncState < CMediaEnum::SYNC_STATE_FILE_PASS)
        {
            m_strEmptyCategoryPopupText = "Sync in progress, please wait!";
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_MEDIA_EMPTY_CATEGORY);
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s: Sync in progress popup displayed", __FUNCTION__);
        }
        else
        {
            setMediaBrowseDataState(CMediaEnum::BROWSEDATA_STATE_EMPTY);
        }
    }
    else
    {
        setMediaBrowseDataState(CMediaEnum::BROWSEDATA_STATE_EMPTY);
    }
}

void CMediaAdaptor::showStoredBrowseData()
{
    m_strBrowseCategoryScreenTitle = m_strPrevBrowseCategoryScreenTitle;
    sigBrowseCategoryScreenTitleChanged();

    setMediaBrowseDataState(CMediaEnum::BROWSEDATA_STATE_AVAILABLE);
}

int CMediaAdaptor::totalImageCount()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);
    return m_iTotalImageCount;
}

bool CMediaAdaptor::handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s keycode: %d, keyState: %d",__FUNCTION__, static_cast<int>(eKey), static_cast<int>(eKeyState));
    bool bRes = false;
    switch(eKey)
    {
    case EHardKeys::KEYCODEHK_SEEKUP:
    {
        if(CHardKeyEnum::EHardKeyState::HKEY_STATE_RELEASED == eKeyState)
        {
            next(CMediaEnum::EN_BUTTON_STATE_RELEASED);
        }
        else if(CHardKeyEnum::EHardKeyState::HKEY_STATE_PRESSED == eKeyState)
        {
            next(CMediaEnum::EN_BUTTON_STATE_PRESSED);
        }
        else if(CHardKeyEnum::EHardKeyState::HKEY_STATE_LONGPRESSED == eKeyState)
        {
            fastForward(CMediaEnum::EN_BUTTON_STATE_LONG_PRESSED);
        }
        else if(CHardKeyEnum::EHardKeyState::HKEY_STATE_LONGRELEASED == eKeyState)
        {
            /*
             * This check cannot be added in the resume() func because resume is a common function for play/pause also
            and we cannot differentiate if thsi resume was called after releasing the Next HK/SWC
            */
            if((CAudioEnums::SRC_BT_A2DP1 == m_eActiveMediaSrc && m_bIsFwdRwdSupported) || (CAudioEnums::SRC_BT_A2DP1 != m_eActiveMediaSrc))
            {
                fastForward(CMediaEnum::EN_BUTTON_STATE_LONG_RELEASED);
                //resume();
            }
        }
        else
        {
            //Do Nothing.
        }
        bRes = true;
    }
        break;
    case EHardKeys::KEYCODEHK_SEEKDOWN:
    {
        if(CHardKeyEnum::EHardKeyState::HKEY_STATE_RELEASED == eKeyState)
        {
            prev(CMediaEnum::EN_BUTTON_STATE_RELEASED);
        }
        else if(CHardKeyEnum::EHardKeyState::HKEY_STATE_PRESSED == eKeyState)
        {
            prev(CMediaEnum::EN_BUTTON_STATE_PRESSED);
        }
        else if(CHardKeyEnum::EHardKeyState::HKEY_STATE_LONGPRESSED == eKeyState)
        {
            fastRewind(CMediaEnum::EN_BUTTON_STATE_LONG_PRESSED);
        }
        else if(CHardKeyEnum::EHardKeyState::HKEY_STATE_LONGRELEASED == eKeyState)
        {
            /*
             * This check cannot be added in the resume() func because resume is a common function for play/pause also
            and we cannot differentiate if thsi resume was called after releasing the Next HK/SWC
            */
            if((CAudioEnums::SRC_BT_A2DP1 == m_eActiveMediaSrc && m_bIsFwdRwdSupported) || (CAudioEnums::SRC_BT_A2DP1 != m_eActiveMediaSrc))
            {
                fastRewind(CMediaEnum::EN_BUTTON_STATE_LONG_RELEASED);
                //resume();
            }
        }
        else
        {
            //Do Nothing
        }
        bRes = true;
    }
        break;
    case EHardKeys::KEYCODESWC_NEXT:
    {
        if((CHardKeyEnum::EHardKeyState::HKEY_STATE_RELEASED == eKeyState))
        {
            next(CMediaEnum::EN_BUTTON_STATE_RELEASED);
        }
        else if((CHardKeyEnum::EHardKeyState::HKEY_STATE_PRESSED == eKeyState))
        {
            next(CMediaEnum::EN_BUTTON_STATE_PRESSED);
        }
        else if((CHardKeyEnum::EHardKeyState::HKEY_STATE_LONGPRESSED == eKeyState))
        {
            if(CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
            {
                if(m_bIsNowPlayingDataAvail)
                {
                    if((m_bIsFolderModePlayBack) && (getUSBDeviceCategoryCount(CMediaEnum::BROWSEITEM_FOLDERS) > 1))
                    {
                        nextFolder();
                    }
                    else
                    {
                        fastForward(CMediaEnum::EN_BUTTON_STATE_LONG_PRESSED);
                    }
                }
                else
                {
                    //Do nothing
                }
            }
            else
            {
                fastForward(CMediaEnum::EN_BUTTON_STATE_LONG_PRESSED);
            }
        }
        else if((CHardKeyEnum::EHardKeyState::HKEY_STATE_LONGRELEASED == eKeyState))
        {
            if(CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
            {
                if(m_bIsNowPlayingDataAvail)
                {
                    if((m_bIsFolderModePlayBack) && (getUSBDeviceCategoryCount(CMediaEnum::BROWSEITEM_FOLDERS) > 1))
                    {
                        //Do Nothing
                    }
                    else
                    {
                        fastForward(CMediaEnum::EN_BUTTON_STATE_LONG_RELEASED);
                    }
                }
                else
                {
                    //Do nothing
                }
            }
            else
            {
                /*
                 * This check cannot be added in the resume() func because resume is a common function for play/pause also
                and we cannot differentiate if thsi resume was called after releasing the Next HK/SWC
                */
                if((CAudioEnums::SRC_BT_A2DP1 == m_eActiveMediaSrc && m_bIsFwdRwdSupported) || (CAudioEnums::SRC_BT_A2DP1 != m_eActiveMediaSrc))
                {
                    fastForward(CMediaEnum::EN_BUTTON_STATE_LONG_RELEASED);
                }
            }
        }
        else
        {
            //Do nothing
        }
    }
        break;
    case EHardKeys::KEYCODESWC_PREV:
    {
        if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState))
        {
            prev(CMediaEnum::EN_BUTTON_STATE_RELEASED);
        }
        else if((CHardKeyEnum::HKEY_STATE_PRESSED == eKeyState))
        {
            prev(CMediaEnum::EN_BUTTON_STATE_PRESSED);
        }
        else if((CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
        {
            if(CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
            {
                if(m_bIsNowPlayingDataAvail)
                {
                    if((m_bIsFolderModePlayBack) && (getUSBDeviceCategoryCount(CMediaEnum::BROWSEITEM_FOLDERS) > 1))
                    {
                        previousFolder();
                    }
                    else
                    {
                        fastRewind(CMediaEnum::EN_BUTTON_STATE_LONG_PRESSED);
                    }
                }
                else
                {
                    //Do nothing
                }
            }
            else
            {
                fastRewind(CMediaEnum::EN_BUTTON_STATE_LONG_PRESSED);
            }
        }
        else if((CHardKeyEnum::HKEY_STATE_LONGRELEASED == eKeyState))
        {
            if(CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
            {
                if((m_bIsNowPlayingDataAvail))
                {
                    if((m_bIsFolderModePlayBack) && (getUSBDeviceCategoryCount(CMediaEnum::BROWSEITEM_FOLDERS) > 1))
                    {
                        //Do nothing
                    }
                    else
                    {
                        fastRewind(CMediaEnum::EN_BUTTON_STATE_LONG_RELEASED);
                    }
                }
                else
                {
                    //Do nothing
                }
            }
            else
            {
                /*
                 * This check cannot be added in the resume() func because resume is a common function for play/pause also
                and we cannot differentiate if thsi resume was called after releasing the Next HK/SWC
                */
                if((CAudioEnums::SRC_BT_A2DP1 == m_eActiveMediaSrc && m_bIsFwdRwdSupported) || (CAudioEnums::SRC_BT_A2DP1 != m_eActiveMediaSrc))
                {
                    fastRewind(CMediaEnum::EN_BUTTON_STATE_LONG_RELEASED);
                }
            }
        }
        else
        {
            //Do nothing
        }
    }
        break;

    default:
        //bRes = false;
        //bRes is already defined false
        break;
    }

    return bRes;
}

void CMediaAdaptor::browseSessionCreated()
{
    emit sigBrowseSessionCreated();
}

CMediaEnum::EMediaVRBrowseState CMediaAdaptor::getMediaVRBrowseState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - VR browse state: %d",__FUNCTION__, m_eMediaVRBrowseState);
    return m_eMediaVRBrowseState;
}

void CMediaAdaptor::setMediaVRBrowseState(CMediaEnum::EMediaVRBrowseState eMediaVRBrowseState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - VR browse state: %d",__FUNCTION__, eMediaVRBrowseState);
    m_eMediaVRBrowseState = eMediaVRBrowseState;
}

void CMediaAdaptor::processRCARequest(CRCAEnums::ERCAActionInitiated eRCAActionInitiated, uint uiIntInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(CRCAEnums::RCA_PICTURE_SELECTED == eRCAActionInitiated)
    {
        //Since a direct switch is required, never invoke processBrowseCategoryRequest()
        if(CVehicleSettingsAdaptor::getInstance()->speedLockOutStatus())
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s : PV speed lockout true - showing lockout popup only", __FUNCTION__);
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_SPEED_LOCKOUT_IMAGES);
        }
        else
        {
            m_iCurrentImageIndex = (uiIntInfo - 1); //RCA data is not 0 index based, hence decrementing the value by 1

            if(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaPicture))
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Picture Viewer already open, switching to index: %d", __FUNCTION__, m_iCurrentImageIndex);
                emit sigImageIndexChanged();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Switching directly to Picture Viewer for index: %d", __FUNCTION__, m_iCurrentImageIndex);
                directMediaStateSwitch(CMediaEnum::BROWSEITEM_PICTURE);
            }
        }

        //Clear the RCA bit
        CRCAAdaptor::getInstance()->clearRCAAction(CRCAEnums::RCA_PICTURE_SELECTED);
    }
    else
    {
        //Do nothing
    }
}

CMediaEnum::EMediaVRBrowseState CMediaAdaptor::requestVRBrowse(CMediaEnum::EMediaBrowseItem eMediaBrowseItem, int iBrowseItemID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - VR browse request for type: %d and ID: %d",__FUNCTION__, eMediaBrowseItem, iBrowseItemID);

    setMediaVRBrowseState(CMediaEnum::VR_BROWSE_STATE_PROCESSING);
    if(-1 == iBrowseItemID)
    {
        getCategoryRoot(eMediaBrowseItem, true);
    }
    else
    {
        browseItemClicked(iBrowseItemID, eMediaBrowseItem, "Browse", 1, 1, true);
    }

    setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_BROWSE_CATEGORY);
    CHMIMain::getSM()->raise_evMediaActivated();

    return getMediaVRBrowseState();
}

void CMediaAdaptor::directMediaStateSwitch(CMediaEnum::EMediaBrowseItem eMediaBrowseItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if(CMediaEnum::MEDIA_OPERATIONSTATE_CORRUPTVIDEO != getMediaOperationState())
    {
        if(CMediaEnum::CONTENTTYPE_I == m_eUSBContentType
                || CMediaEnum::CONTENTTYPE_V == m_eUSBContentType
                || CMediaEnum::CONTENTTYPE_VI == m_eUSBContentType)
        {
            setMediaOperationState(CMediaEnum::MEDIA_OPERATIONSTATE_NOSONGS);
        }
    }

    if(CMediaEnum::BROWSEITEM_VIDEOS == eMediaBrowseItem)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Switching directly to Video browse", __FUNCTION__);
        getCategoryRoot(CMediaEnum::BROWSEITEM_VIDEOS);
        setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_BROWSE_CATEGORY);
        CHMIMain::getSM()->raise_evMediaActivated();
    }
    else if(CMediaEnum::BROWSEITEM_PICTURE == eMediaBrowseItem)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s - Switching directly to Picture Viewer", __FUNCTION__);
        setMediaBrowseItemSelected(eMediaBrowseItem);
        setMediaCategoryBrowsed(eMediaBrowseItem);
        setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_PICTURES);
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION);
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_ONLY_VIDEO_CONFIRMATION);
        CHMIMain::getSM()->raise_evMediaActivated();
    }
}

void CMediaAdaptor::handleAllVideosCorrupt()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s",__FUNCTION__);

    if((CAudioEnums::CAudioEnums::SRC_USB1 == m_eActiveMediaSrc) && (CMediaEnum::CONTENTTYPE_E == m_eUSBContentType))
    {
        //Show empty USB popup
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Show empty USB popup", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_MEDIA_EMPTY_DEVICE_CONNECTED);
        requestPreviousSource();
    }
    else if((CAudioEnums::CAudioEnums::SRC_USB1 == m_eActiveMediaSrc) && (CMediaEnum::CONTENTTYPE_I == m_eUSBContentType))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - Show Image confirmation popup", __FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION);
    }
    else
    {
        if(CAudioEnums::CAudioEnums::SRC_USB1 == m_eActiveMediaSrc)
        {
            //All videos are corrupt and USB is not having images nor it is empty (might have songs)
            requestPreviousSource();
        }
        else
        {
            //Do nothing
        }
    }
}

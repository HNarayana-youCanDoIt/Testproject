/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaSM.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CMediaSM      Class to implement Media SCT Interface
*/

#include "CMediaSM.h"
#include "CMediaAdaptor.h"
#include "CVehicleSettingsAdaptor.h"
#include "CParkAssistAdaptor.h"
#include "CPowerModeAdaptor.h"
#include "CRCAAdaptor.h"

CMediaSM::CMediaSM(CMediaApplication& mediaApp):mMediaApp(mediaApp)
{

}
CMediaSM::~CMediaSM()
{

}

////////////////////////////////////
// StateMachine related functions //
////////////////////////////////////

void CMediaSM::enterMedia()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);

    /*
     * Only videos USB --> Browse screen (videos) --> Activate PDC/RVC -->  Deactivate PDC/RVC
     * In above scenario, SCT switches to history i.e. Media state and raised evMediaActivated
     * Below code shall force browse category screen to be displayed with list of videos
     * */
    if((CAudioEnums::SRC_USB1 == CAudioAdaptor::getInstance()->activeEntSrc())
            && (CMediaEnum::CONTENTTYPE_V == CMediaAdaptor::getInstance().getUSBContentType()
                || CMediaEnum::CONTENTTYPE_VI == CMediaAdaptor::getInstance().getUSBContentType())
            && (CMediaEnum::MEDIA_DISPLAYSTATE_PICTURES != CMediaAdaptor::getInstance().getMediaDisplayState())
            && (CMediaAdaptor::getInstance().getNoSongsUSBResponse())
            && (CMediaEnum::MEDIA_OPERATIONSTATE_VIDEO != CMediaAdaptor::getInstance().getMediaOperationState())
            && (CMediaEnum::MEDIA_OPERATIONSTATE_CORRUPTVIDEO != CMediaAdaptor::getInstance().getMediaOperationState()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - USB activation going in bad state, recovery initiated", __FUNCTION__);
        CMediaAdaptor::getInstance().directMediaStateSwitch(CMediaEnum::BROWSEITEM_VIDEOS);
    }
    else
    {
        //Do nothing
    }
}

void CMediaSM::exitMedia()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);
    CFramework::getFramework().clearScreenHistoryStack();

    /*
     * Requirement: IF PV is on display and user switches to PDC/RVC or active call and returns to media,
       then PV should be displayed again
     * Hence, display state PV is saved whenever USB is active or unknown ENT source is active
     * */
    if(CAudioEnums::SRC_USB1 == CAudioAdaptor::getInstance()->activeEntSrc()
            || CAudioEnums::SRC_IPOD == CAudioAdaptor::getInstance()->activeEntSrc()
            || CAudioEnums::SRC_ENT_UNKNOWN == CAudioAdaptor::getInstance()->activeEntSrc())
    {
        if(CMediaEnum::MEDIA_DISPLAYSTATE_PICTURES == CMediaAdaptor::getInstance().getMediaDisplayState()
                || CMediaEnum::MEDIA_OPERATIONSTATE_CORRUPTVIDEO == CMediaAdaptor::getInstance().getMediaOperationState()
                || CMediaEnum::VR_BROWSE_STATE_PROCESSING == CMediaAdaptor::getInstance().getMediaVRBrowseState())
        {
            //Do nothing...save the state as it is
        }
        else
        {
            CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
        }
    }
    else
    {
        CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
    }
}
//=================================================================

void CMediaSM::enterMediaLoadingScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);
    CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_LOADING);
    mMediaApp.loadScreen("qrc:/QML/Media/MediaLoadingScreen.qml");
}

void CMediaSM::exitMediaLoadingScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);
}
//=================================================================

void CMediaSM::enterMediaMainScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);
    CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_MAIN);
    mMediaApp.loadScreen("qrc:/QML/Media/MediaScreen.qml");
}

void CMediaSM::exitMediaMainScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);
}
//=================================================================

void CMediaSM::enterMediaVideoViewerScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);    
    CMediaAdaptor::getInstance().processHideDrawersDelay();
    CDrawersAdaptor::getInstance()->setShowMuteStatus(true);
    CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_MAIN);
    mMediaApp.loadScreen("qrc:/QML/Media/MediaVideoScreen.qml");
    CMediaAdaptor::getInstance().handleVideoSurface(true);
}

void CMediaSM::exitMediaVideoViewerScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s",__FUNCTION__);
    emit CDrawersAdaptor::getInstance()->sigChangeMuteStatusOnScreenExit();
    CMediaAdaptor::getInstance().handleVideoSurface(false);
}

//=================================================================

void CMediaSM::enterMediaBrowseMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);
    CRCAAdaptor::getInstance()->setHMIMediaBrowseStatus(true);
}

void CMediaSM::exitMediaBrowseMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s",__FUNCTION__);
    CRCAAdaptor::getInstance()->setHMIMediaBrowseStatus(false);
    CMediaAdaptor::getInstance().setMediaCategoryBrowsed(CMediaEnum::BROWSEITEM_UNKNOWN);
    CFramework::getFramework().clearScreenHistoryStack();

    /*
     * Below code handles following scenarios:
     * 1. Only videos USB --> Browse screen (videos) --> User clicks back without selecting any video
     * 2. Corrupt video state --> Browse screen (videos) --> User clicks back without selecting any video
     * Note: Power mode is checked because ENT source is USB even when media OFF is activated
     * */
    if((CAudioEnums::SRC_USB1 == CAudioAdaptor::getInstance()->activeEntSrc())
            && (CAudioEnums::EN_SOURCE_STATE_SUSPENDED != CAudioAdaptor::getInstance()->getSourceState(CAudioEnums::EN_ENT_SOURCE_USB1))
            && (!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus())
            && (CPowerModeEnums::VPM_ACTIVE == CPowerModeAdaptor::getInstance().getPowerModeStatus()
                || CPowerModeEnums::VPM_ONE_HOUR == CPowerModeAdaptor::getInstance().getPowerModeStatus()))
    {
        if(CMediaEnum::BROWSEITEM_UNKNOWN == CMediaAdaptor::getInstance().getMediaBrowseItemSelected())
        {
            if(CMediaEnum::MEDIA_OPERATIONSTATE_NOSONGS == CMediaAdaptor::getInstance().getMediaOperationState()
                    && !CMediaAdaptor::getInstance().isNowPlayingDataAvail())
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s - OPERATIONSTATE_NOSONGS: Exiting USB browse without selecting any media - requestPreviousSource",__FUNCTION__);
                CMediaAdaptor::getInstance().requestPreviousSource();
            }
            else if(CMediaEnum::MEDIA_OPERATIONSTATE_CORRUPTVIDEO == CMediaAdaptor::getInstance().getMediaOperationState())
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s - OPERATIONSTATE_CORRUPTVIDEO: Exiting video browse without selecting any media - next() invoked",__FUNCTION__);
                CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
                CMediaAdaptor::getInstance().next(CMediaEnum::EN_BUTTON_STATE_RELEASED);
            }
            else if(CMediaEnum::VR_BROWSE_STATE_PROCESSING == CMediaAdaptor::getInstance().getMediaVRBrowseState())
            {
                //do nothing
            }
            else
            {
                CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
            }
        }
        else
        {
            if(CMediaEnum::MEDIA_OPERATIONSTATE_CORRUPTVIDEO == CMediaAdaptor::getInstance().getMediaOperationState()
                    || CMediaEnum::VR_BROWSE_STATE_PROCESSING == CMediaAdaptor::getInstance().getMediaVRBrowseState())
            {
                //do nothing
            }
            else
            {
                CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
            }

        }
    }
    else
    {
        //Do nothing
    }

}

//=================================================================

void CMediaSM::enterMediaBrowseScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s",__FUNCTION__);
    CMediaAdaptor::getInstance().setMediaBrowseItemSelected(CMediaEnum::BROWSEITEM_UNKNOWN);
    CHMIMain::getSM()->getSCI_Media()->set_iCurrentBrowseLevel(CMediaEnum::BROWSELEVEL_ROOT);
    CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_BROWSE);
    mMediaApp.loadScreen("qrc:/QML/Media/MediaBrowseScreen.qml");
}

void CMediaSM::exitMediaBrowseScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);
}

//=================================================================

void CMediaSM::enterMediaBrowseCategoryScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);

    CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_BROWSE_CATEGORY);
    CMediaAdaptor::getInstance().setMediaBrowseItemSelected(CMediaEnum::BROWSEITEM_UNKNOWN);

    if(CFramework::getFramework().getIsBackPressed())
    {
        if(CMediaEnum::BROWSEDATA_STATE_EMPTY == CMediaAdaptor::getInstance().browseDataState())
        {
            CMediaAdaptor::getInstance().showStoredBrowseData();
        }
        else if(CHMIMain::getSM()->getSCI_Media()->get_iCurrentBrowseLevel() == CMediaEnum::BROWSELEVEL_SUBCATEGORY)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s - goToPreviousLevel()", __FUNCTION__);
            CMediaAdaptor::getInstance().goToPreviousLevel();
        }
        else
        {
            //Do nothing
        }
    }
    mMediaApp.loadScreen("qrc:/QML/Media/MediaBrowseCategory.qml");
}

void CMediaSM::exitMediaBrowseCategoryScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s - Current browse level - %d",__FUNCTION__, CHMIMain::getSM()->getSCI_Media()->get_iCurrentBrowseLevel());
    CMediaAdaptor::getInstance().resetWindowing();

    if((CAudioEnums::SRC_BT_A2DP1 == CAudioAdaptor::getInstance()->activeEntSrc())
            && (CHMIMain::getSM()->getSCI_Media()->get_iCurrentBrowseLevel() <= 2))
    {
        CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_LOADING);
    }
    else
    {
        //Do nothing
    }
}
//=================================================================

void CMediaSM::enterMediaPictureViewerScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s",__FUNCTION__);
    CDrawersAdaptor::getInstance()->setShowMuteStatus(true);
    CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_PICTURES);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_USB_ONLY_VIDEO_CONFIRMATION);
    mMediaApp.loadScreen("qrc:/QML/Media/MediaPictureViewerScreen.qml");
}

void CMediaSM::exitMediaPictureViewerScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s", __FUNCTION__);
    emit CDrawersAdaptor::getInstance()->sigChangeMuteStatusOnScreenExit();
}

void CMediaSM::enterMediaAuxScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s", __FUNCTION__);
    CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_AUX);
    mMediaApp.loadScreen("qrc:/QML/Media/MediaAUXScreen.qml");
}

void CMediaSM::exitMediaAuxScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s",__FUNCTION__);
}

void CMediaSM::enterAUXInGainScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s",__FUNCTION__);
    mMediaApp.loadScreen("qrc:/QML/Media/MediaAuxGainScreen.qml");
}

void CMediaSM::exitAUXInGainScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s",__FUNCTION__);
}
//=================================================================


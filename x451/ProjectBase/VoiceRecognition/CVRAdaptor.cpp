/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CVRAdaptor.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CVRAdaptor class
 */

#include "CVRAdaptor.h"
#include "CVRStubResource.h"
#include "ResourceFactory.hpp"
#include "CPhoneAdaptor.h"
#include "CAndroidAutoAdaptor.h"
#include "CAppleCarPlayAdaptor.h"
#include "CMediaAdaptor.h"
#include "CAudioAdaptor.h"
#include "CDiagnosticAdaptor.h"
#include "CPowerModeAdaptor.h"
#include "CMediaAdaptor.h"
#include "CHomeAdaptor.h"
#include "CParkAssistAdaptor.h"
#include "logging.h"
#include "CHVACAdaptor.h"

CVRAdaptor* CVRAdaptor::m_pVRAdaptor = nullptr;

CVRAdaptor::CVRAdaptor(QObject *pParent)
    : QObject(pParent),
      m_objFramework(CFramework::getFramework()),
      m_eVRState(CVREnum::EN_VR_STATE_NONE),
      m_bVRSessionStatus(false),
      m_strVRHelpCategoryName(""),
      m_bVRHelpFileReadStatus(false),
      m_bIsVRAvailable(false),
      m_bTeleprompterListStatus(false),
      m_iMediaFilterType(-1),
      m_iMediaFilterId(-1),
      m_bIsVROverlayDisplaying(false),
      m_bHideVROverlayTimerStatus(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    m_objFramework.setContextProperty("cppVRAdaptor", this);
    CVREnum::registerVREnumsToQML();
    setRequestState(CVREnum::EN_NO_REQUEST);
    m_objVRHelpCommands.clear();
    m_objVRHelpCommandsNoFATC.clear();
    m_objVRHelpCategoryListModel.removeRows();
    m_objVRHelpCategoryListModelNoFATC.removeRows();
    m_objVRHelpCommandListModel.removeRows();
    m_objVRHelpCommandListModelNoFATC.removeRows();
    m_objTeleprompterListModel.removeRows();

    parseVRHelpCommands("/mnt/data/VR/dialogManager/dialog/text/VR_HelpTexts.xml", m_objVRHelpCategoryListModel, m_objVRHelpCommands);
    initMainVRCommandsList(m_listMainVRCommands, m_objVRHelpCommands);

    parseVRHelpCommands("/mnt/data/VR/dialogManager/dialog/text/VR_HelpTexts_No_HVAC.xml", m_objVRHelpCategoryListModelNoFATC, m_objVRHelpCommandsNoFATC);
    initMainVRCommandsList(m_listMainVRCommandsNoFATC, m_objVRHelpCommandsNoFATC);

    connect(CAudioAdaptor::getInstance(), SIGNAL(sigSourceStateInfoUpdated(int,int)), this, SLOT(sltSourceStateInfoUpdated(int, int)), Qt::QueuedConnection);
}

CVRAdaptor::~CVRAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
}

CVRAdaptor* CVRAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if (!m_pVRAdaptor)
    {
        m_pVRAdaptor = new CVRAdaptor();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR instance already created", __FUNCTION__);
    }
    return m_pVRAdaptor;
}

void CVRAdaptor::activateVRSession(CHardKeyEnum::EHardKeyState eKeyState, EVRScreenID eScreenID)
{
    if (
#ifndef TATA_X445
        (!CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus()) &&
        (!CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus()) &&
        (CPowerModeEnums::VPM_MEDIA_OFF != CPowerModeAdaptor::getInstance().getPowerModeStatus()) &&
#endif
        (!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()) &&
        (!CPhoneAdaptor::getInstance()->doesCallExist()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: hard key state is: %d", __FUNCTION__, eKeyState);
        if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState ) || (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState ))
        {
            if(ResourceFactory::getVRStubResource())
            {
                if((CDiagnosticAdaptor::getInstance()) && (CDiagnosticAdaptor::getInstance()->micConnectionStatus() != CDiagnosticEnum::CONNECTED))
                {
                    //Mic is not connected
                    CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
                    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_MIC_NOT_AVAILABLE_POPUP);
                }
                else
                {
                    //Mic is connected
                }

                //If vr is available then only activate VR session otherwise show popup, vr is not available
                if(m_bIsVRAvailable)
                {
                    //If keystate received is long press and vr session is active then we need to deactivate it else always activate VR
                    if((CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState) && m_bVRSessionStatus)
                    {
                        ResourceFactory::getVRStubResource()->deactivateVRSession();
                    }
                    else
                    {
                        ResourceFactory::getVRStubResource()->activateVRSession(eKeyState, eScreenID);
                    }
                }
                else
                {
                    //VR is not available
                    CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
                    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_VR_NOT_AVAILABLE_POPUP);
                }
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR resource stub not created", __FUNCTION__);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: hard key state not handled", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: AA phone or carplay phone is connected, not activating VR", __FUNCTION__);
    }
}

bool CVRAdaptor::invDeactivateVRSession(CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: hard key state is: %d", __FUNCTION__, eKeyState);
    bool bRet = false;
    if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState ) || (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState ))
    {
        if(m_bVRSessionStatus)
        {
            if(ResourceFactory::getVRStubResource())
            {
                ResourceFactory::getVRStubResource()->deactivateVRSession();
                bRet = true;
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR resource stub not created", __FUNCTION__);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR session is not active", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: hard key state not handled", __FUNCTION__);
    }
    return bRet;
}

bool CVRAdaptor::invHandleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: eKey is: %d, eKeyState is: %d", __FUNCTION__, eKey, eKeyState);
    bool bHardkeyHandledCompletely = false;

    /*
     * If VR overlay is displaying and user Rotate or Press Menu Rotary, then we have
     * to not take any action, So returning true, So that no action will be taken in background.
     */
    if (isVROverlayDisplaying()
            && ((CHardKeyEnum::KEYCODEHK_MENUROTARY_KNOB == eKey)
                                    || (CHardKeyEnum::KEYCODEHK_MENUROTARY == eKey)))
    {
        bHardkeyHandledCompletely = true;
    }
    else if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) || (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
    {
        switch(eKey)
        {
        case CHardKeyEnum::KEYCODEHK_HOME:
        case CHardKeyEnum::KEYCODEHK_PHONE:
        case CHardKeyEnum::KEYCODEHK_SOFTWARE_UPDATE:
        case CHardKeyEnum::KEYCODEHK_ENGGMENU:
        case CHardKeyEnum::KEYCODEHK_VOLROTARY:
        case CHardKeyEnum::KEYCODESWC_SOURCE:
        case CHardKeyEnum::KEYCODESWC_REJECT_MUTE:
            invDeactivateVRSession(eKeyState);
            break;

        case CHardKeyEnum::KEYCODEHK_BACK:
        {
            invDeactivateVRSession(eKeyState);
            bHardkeyHandledCompletely = true;
        }
            break;

        case CHardKeyEnum::KEYCODEHK_SEEKUP:
        case CHardKeyEnum::KEYCODEHK_SEEKDOWN:
        case CHardKeyEnum::KEYCODESWC_NEXT:
        case CHardKeyEnum::KEYCODESWC_PREV:
            bHardkeyHandledCompletely = true;
            break;

        case CHardKeyEnum::KEYCODEHK_FAVORITE:
        {
            if(CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState)
            {
                invDeactivateVRSession(eKeyState);
            }
            else if (CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState)
            {
                CHardKeyEnum::EFavKeyCode eFavKeyCode = CHomeAdaptor::getInstance().eCurrentFavKeyCode();
                switch(eFavKeyCode)
                {
                case CHardKeyEnum::FAV_HK:
                case CHardKeyEnum::FAV_HK_SOURCE:
                case CHardKeyEnum::FAV_HK_PARK_ASSIST:
                case CHardKeyEnum::FAV_HK_AUDIO_SETUP:
                case CHardKeyEnum::FAV_HK_FAVOURITES:
                case CHardKeyEnum::FAV_HK_NAVIGATION:
                case CHardKeyEnum::FAV_HK_MOODLIGHTING:
                case CHardKeyEnum::FAV_HK_ANDROIDAUTO:
                case CHardKeyEnum::FAV_HK_CARPLAY:
                {
                    invDeactivateVRSession(eKeyState);
                }
                    break;
                case CHardKeyEnum::FAV_HK_CONTACTS:
                case CHardKeyEnum::FAV_HK_VOICE_COMMAND:
                default:
                {
                    //Do Nothing!
                }
                    break;
                }
            }
            else
            {
                //do nothing
            }
        }
            break;

        default:
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: hard key not handled: %d", __FUNCTION__, eKey);
            break;
        }
    }
    else
    {
        //do nothing
    }
    return bHardkeyHandledCompletely;
}

void CVRAdaptor::setScreen(const QString &strScreenName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: screen name is: %s", __FUNCTION__, strScreenName.toStdString().c_str());

    EResponseType eResponseType = EN_RESPONSE_TYPE_INVALID;

    if(strScreenName == SET_SCREEN_PHONE)
    {
        if(CPhoneAdaptor::getInstance())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: switching to call logs screen", __FUNCTION__);

            /* In case VR is launched on Projection screen,
             * then requestNative needs to be called if screen switch heppens through VR,
             * applicable for Android Auto */
            CAndroidAutoAdaptor::getInstance()->requestNative();

            CPhoneAdaptor::getInstance()->invSwitchToPhoneBrowse(CPhoneEnum::PHONE_BROWSE_TYPE_CALL_LOGS);
            eResponseType = EN_RESPONSE_TYPE_SUCCESS;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: Phone adaptor is not created", __FUNCTION__);
            eResponseType = EN_RESPONSE_TYPE_FAILURE;
        }
    }
    else if(strScreenName == SET_SCREEN_PAIRED_PHONES)
    {
        if(((CAndroidAutoAdaptor::getInstance()) && (!CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus())) &&
                    ((CAppleCarPlayAdaptor::getInstance()) && (!CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus())))
        {
            if(CPhoneAdaptor::getInstance())
            {
                LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: switching to paired devices", __FUNCTION__);
                CPhoneAdaptor::getInstance()->invSwitchToPairedDevices();
                eResponseType = EN_RESPONSE_TYPE_SUCCESS;
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: Phone adaptor is not created", __FUNCTION__);
                eResponseType = EN_RESPONSE_TYPE_FAILURE;
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: projection phone connected", __FUNCTION__);
            eResponseType = EN_RESPONSE_TYPE_PROJECTION_MODE;
        }
    }
    else if(strScreenName == SET_SCREEN_CLIMATE)
    {
        /* In case VR is launched on Projection screen,
         * then requestNative needs to be called if screen switch heppens through VR,
         * Applicalbe for Android Auto and Carplay */
        CAppleCarPlayAdaptor::getInstance()->requestNative();
        CAndroidAutoAdaptor::getInstance()->requestNative();

        CHMIMain::getSM()->getSCI_Drawers()->raise_evMaximizeHVACDrawer();
        eResponseType = EN_RESPONSE_TYPE_SUCCESS;
    }
    else if(strScreenName == SET_SCREEN_MEDIA_FOLDERS)
    {
        CMediaAdaptor::getInstance().requestVRBrowse(CMediaEnum::EMediaBrowseItem::BROWSEITEM_FOLDERS, -1);
        eResponseType = EN_RESPONSE_TYPE_SUCCESS;
    }
    else if(strScreenName == SET_SCREEN_MEDIA)
    {        
        if(CAudioAdaptor::getInstance())
        {
            //Play the source from Media category and switch to Media screen
            CAudioAdaptor::getInstance()->playFromSourceGroup(CAudioEnums::EAudioSourceCategory::SOURCE_CATEGORY_MEDIA, true);
            eResponseType = EN_RESPONSE_TYPE_SUCCESS;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: audio adaptor is not created", __FUNCTION__);
            eResponseType = EN_RESPONSE_TYPE_FAILURE;
        }
    }
    else if(strScreenName == SET_SCREEN_TUNER)
    {
        if(CAudioAdaptor::getInstance())
        {
            /* In case VR is launched on Projection screen,
             * then requestNative needs to be called if screen switch heppens through VR
             * Applicalbe for Android Auto and Carplay */
            CAppleCarPlayAdaptor::getInstance()->requestNative();
            CAndroidAutoAdaptor::getInstance()->requestNative();

            //Play the source from Tuner category and switch to Tuner screen
            CAudioAdaptor::getInstance()->playFromSourceGroup(CAudioEnums::EAudioSourceCategory::SOURCE_CATEGORY_TUNER, true);
            eResponseType = EN_RESPONSE_TYPE_SUCCESS;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: audio adaptor is not created", __FUNCTION__);
            eResponseType = EN_RESPONSE_TYPE_FAILURE;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: screen name not handled", __FUNCTION__);
        eResponseType = EN_RESPONSE_TYPE_INVALID;
    }

    if(ResourceFactory::getVRStubResource())
    {
        ResourceFactory::getVRStubResource()->sendVRResponse(eResponseType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR resource stub not created", __FUNCTION__);
    }
}

void CVRAdaptor::showContact(const QString &strDatabaseType, int iContactId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Database type is: %s, Contact id is: %d", __FUNCTION__, strDatabaseType.toStdString().c_str(), iContactId);
    EResponseType eResponseType = EN_RESPONSE_TYPE_INVALID;

    if((strDatabaseType == "pb") && (iContactId > 0))
    {
        if(CPhoneAdaptor::getInstance())
        {
            /* In case VR is launched on Projection screen,
             * then requestNative needs to be called if screen switch heppens through VR
             * Applicalbe for Android Auto */
            CAndroidAutoAdaptor::getInstance()->requestNative();

            //Close VR animation overlay before showing the picklist
            showHideVROverlay(false);
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: switching to contact details screen", __FUNCTION__);
            CPhoneAdaptor::getInstance()->switchToContactDetails(iContactId);
            //TODO: The response needs to only be sent back after we get the contact details data in Phone Adaptor
            eResponseType = EN_RESPONSE_TYPE_SUCCESS;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: Phone adaptor is not created", __FUNCTION__);
            eResponseType = EN_RESPONSE_TYPE_FAILURE;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Invalid database type or invalid contact id", __FUNCTION__);
        eResponseType = EN_RESPONSE_TYPE_INVALID;
    }

    if(ResourceFactory::getVRStubResource())
    {
        ResourceFactory::getVRStubResource()->sendVRResponse(eResponseType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR resource stub not created", __FUNCTION__);
    }
}

void CVRAdaptor::showTeleprompterList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    m_objTeleprompterListModel.removeRows();
    m_objTeleprompterListModel.insertRows(ResourceFactory::getVRStubResource()->getVRStubResourceImpl()->getTeleprompterList());
    setTeleprompterListStatus(true);
//    CPopupEnum::EPopupApplicableContext eCurrentHMIContext = static_cast<CPopupEnum::EPopupApplicableContext>(CHMIMain::getSM()->getDefaultSCI()->get_iCurrentHMIContext());

//    if(eCurrentHMIContext == CPopupEnum::EPopupApplicableContext::EN_HMI_VR_PICKLIST_CONTEXT)
//    {
//        //Show teleprompter list popup
//        //TODO: THe flow shall be added once new popup layout is ready from Milind
//    }
//    else
//    {
//        //Update VR animation popup with teleprompter list data
//        setTeleprompterListStatus(true);
//    }
}

void CVRAdaptor::setTeleprompterListStatus(bool bTeleprompterListStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: bTeleprompterListStatus is: %d", __FUNCTION__, bTeleprompterListStatus);
    if(m_bTeleprompterListStatus != bTeleprompterListStatus)
    {
        m_bTeleprompterListStatus = bTeleprompterListStatus;
        emit sigTeleprompterListStatusChanged();
    }
}

void CVRAdaptor::sltSourceStateInfoUpdated(int iSourceId, int iSourceState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: source id is: %d, source state is: %d, m_eVRRequestState is: %d", __FUNCTION__, iSourceId, iSourceState, m_eVRRequestState);
    CAudioEnums::ESourceId eSourceId        = static_cast<CAudioEnums::ESourceId>(iSourceId);
    CAudioEnums::ESourceState eSourceState  = static_cast<CAudioEnums::ESourceState>(iSourceState);
    switch(eSourceId)
    {
    case CAudioEnums::ESourceId::EN_ENT_SOURCE_USB1:
    case CAudioEnums::ESourceId::EN_ENT_SOURCE_IPOD:
    {
        switch(eSourceState)
        {
        case CAudioEnums::EN_SOURCE_STATE_SUSPENDED:
        case CAudioEnums::EN_SOURCE_STATE_CONNECTED:
        {
            //Source state is either connected or suspended and request state is EN_REQUEST_MEDIA_FILTER_LIST_SHOW then request for VR browse
            if(CVREnum::EN_REQUEST_MEDIA_FILTER_LIST_SHOW == m_eVRRequestState)
            {
                requestVRBrowse();
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: VR request state is not EN_REQUEST_MEDIA_FILTER_LIST_SHOW", __FUNCTION__);
            }
        }
            break;

        default:
            break;
        }
    }
        break;

    default:
        break;
    }
}

void CVRAdaptor::showHideVROverlay(bool bShowVROverLay)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: bShowVROverLay: %d", __FUNCTION__, bShowVROverLay);

    if (m_bIsVROverlayDisplaying != bShowVROverLay)
    {
        m_bIsVROverlayDisplaying = bShowVROverLay;
        emit sigShowHideVROverlay(bShowVROverLay);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Values are same. So no Action", __FUNCTION__);
    }
}

void CVRAdaptor::showPickList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    //set teleprompter list status as false
    setTeleprompterListStatus(false);
    //Close VR animation overlay before showing the picklist
    showHideVROverlay(false);
    m_objPickListModel.removeRows();
    m_objPickListModel.insertRows(ResourceFactory::getVRStubResource()->getVRStubResourceImpl()->getPickList());
    CHMIMain::getSM()->getSCI_Vr()->raise_evShowPicklist();
}

void CVRAdaptor::hidePickList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR session status is: %d, pdcRvcScreenStatus is: %d",
             __FUNCTION__, m_bVRSessionStatus, CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus());
    if(!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus())
    {
        if(m_bVRSessionStatus)
        {
            showHideVROverlay(true);
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: PDC/RVC is active, do not show VR overlay", __FUNCTION__);
    }
    CHMIMain::getSM()->getSCI_Vr()->raise_evHidePicklist();
}

void CVRAdaptor::setFocusedItem(int iLineNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Line number is: %d", __FUNCTION__, iLineNo);
    sigSetFocusedItem(iLineNo);
}

//TODO: need to implement this method once gets confirmation from the VR service about the multiple category issue
void CVRAdaptor::focusSelectedCategory(const QString &strCategory)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Category is: %s", __FUNCTION__, strCategory.toStdString().c_str());
    if(CPhoneAdaptor::getInstance()->selectContactDetailsCategory(strCategory))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Category available", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Category not available in contact details", __FUNCTION__);
    }
}

void CVRAdaptor::mediaFilterListShow(int32_t iMediaFilterType, int64_t iMediaFilterId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: iMediaFilterType is: %d, iMediaFilterId: %lld", __FUNCTION__, iMediaFilterType, iMediaFilterId);
    setRequestState(CVREnum::EN_REQUEST_MEDIA_FILTER_LIST_SHOW);
    m_iMediaFilterType  = iMediaFilterType;
    m_iMediaFilterId    = iMediaFilterId;
    if((CAudioEnums::EAudioEntertainmentSrcs::SRC_USB1 == CAudioAdaptor::getInstance()->activeEntSrc()) ||
       (CAudioEnums::EAudioEntertainmentSrcs::SRC_IPOD == CAudioAdaptor::getInstance()->activeEntSrc()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: USB or IPOD is the active entertainment source", __FUNCTION__);
        requestVRBrowse();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: USB or IPOD is not the active entertainment source", __FUNCTION__);        
        if((CAudioEnums::EUsbConnectionStatus::USB_CONNECTED == CAudioAdaptor::getInstance()->usbConnectionStatus()) ||
           (CAudioEnums::EUsbConnectionStatus::USB_ALREADY_CONNECTED == CAudioAdaptor::getInstance()->usbConnectionStatus()))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: USB is connected", __FUNCTION__);
            CAudioAdaptor::getInstance()->setActiveEntSrc(CAudioEnums::SRC_USB1);
        }
        else if((CAudioEnums::EIpodConnectionStatus::IPOD_CONNECTED == CAudioAdaptor::getInstance()->ipodConnectionStatus()) ||
                (CAudioEnums::EIpodConnectionStatus::IPOD_ALREADY_CONNECTED == CAudioAdaptor::getInstance()->ipodConnectionStatus()))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: IPOD is connected", __FUNCTION__);
            CAudioAdaptor::getInstance()->setActiveEntSrc(CAudioEnums::SRC_IPOD);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: Neither USB is connected nor IPOD is connected", __FUNCTION__);
            setRequestState(CVREnum::EN_NO_REQUEST);
            m_iMediaFilterType  = -1;
            m_iMediaFilterId    = -1;
            ResourceFactory::getVRStubResource()->sendVRResponse(EN_RESPONSE_TYPE_INVALID);
        }
    }
}

void CVRAdaptor::onVRStateChange(int iVRState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR state is: %d", __FUNCTION__, iVRState);
    CVREnum::EVRState eVRState = static_cast<CVREnum::EVRState>(iVRState);
    if(m_eVRState != eVRState)
    {        
        switch(eVRState)
        {
        case CVREnum::EN_VR_STATE_SESSION_BEGIN:
        {
            m_eVRState = eVRState;
            m_bVRSessionStatus = true;
            setTeleprompterListStatus(false);
            showHideVROverlay(true);
            emit sigVRStateUpdated();
        }
            break;
        case CVREnum::EN_VR_STATE_LISTENING:
        case CVREnum::EN_VR_STATE_ACCEPTING:
        case CVREnum::EN_VR_STATE_PROCESSING:
        case CVREnum::EN_VR_STATE_PROMPTING:
        {
            m_eVRState = eVRState;
            //CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_VR_ANIMATION_POPUP);
            emit sigVRStateUpdated();
        }
            break;
        case CVREnum::EN_VR_STATE_SESSION_END:
        {
            if(m_bHideVROverlayTimerStatus)
            {
                /* To avoid the flicker of Home screen in VR Overlay -> Projection screen transition */
                LOG_INFO(Log::e_LOG_CONTEXT_VR, "Timer invoked for sltHideVROverlayOnSessionEnd to hide VR overlay");
                QTimer::singleShot(500, this, SLOT(sltHideVROverlayOnSessionEnd()));
            }
            else
            {
                /* Projection phone is not connected, directly hide VR overlay */
                hideVROverlayOnSessionEnd();
            }
        }
            break;
        default:
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR state unchanged", __FUNCTION__);
    }
}

void CVRAdaptor::sltHideVROverlayOnSessionEnd()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    hideVROverlayOnSessionEnd();
}

void CVRAdaptor::hideVROverlayOnSessionEnd()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    m_eVRState = CVREnum::EN_VR_STATE_SESSION_END;
    m_bVRSessionStatus = false;
    m_strVRHelpCategoryName = "";
    setHideVROverlayTimerStatus(false);
    emit sigVRStateUpdated();
    setTeleprompterListStatus(false);
    showHideVROverlay(false);
    CHMIMain::getSM()->getSCI_Vr()->raise_evHidePicklist();
}

void CVRAdaptor::setHideVROverlayTimerStatus(bool bHideVROverlayTimerStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: bHideVROverlayTimerStatus is: %d", __FUNCTION__, bHideVROverlayTimerStatus);
    if(m_bHideVROverlayTimerStatus != bHideVROverlayTimerStatus)
    {
        m_bHideVROverlayTimerStatus = bHideVROverlayTimerStatus;
    }
}

void CVRAdaptor::mediaVRBrowseReqStatus(CMediaEnum::EMediaVRBrowseState eMediaVRBrowseState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: eMediaVRBrowseState is: %d", __FUNCTION__, eMediaVRBrowseState);
    EResponseType eResponseType = EN_RESPONSE_TYPE_INVALID;
    switch(eMediaVRBrowseState)
    {
    case CMediaEnum::VR_BROWSE_STATE_SUCCESS:
        eResponseType = EN_RESPONSE_TYPE_SUCCESS;
        break;

    case CMediaEnum::VR_BROWSE_STATE_FAILED:
        eResponseType = EN_RESPONSE_TYPE_FAILURE;
        break;

    default:
        //do nothing
        break;
    }

    if(ResourceFactory::getVRStubResource())
    {
        ResourceFactory::getVRStubResource()->sendVRResponse(eResponseType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR resource stub not created", __FUNCTION__);
    }
}

void CVRAdaptor::onVRDialogStateChange(int iVRDialogState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR dialog state is: %d", __FUNCTION__, iVRDialogState);
    //m_bVRSessionStatus = (static_cast<CVREnum::EVRDialogState>(iVRDialogState) == CVREnum::EN_VR_DIALOG_STATE_ACTIVE);
}

void CVRAdaptor::onVRAvailableStatus(bool bVRAvailabilityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR availibility status is: %d", __FUNCTION__, bVRAvailabilityStatus);
    if(m_bIsVRAvailable != bVRAvailabilityStatus)
    {
        m_bIsVRAvailable = bVRAvailabilityStatus;
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_VR_NOT_AVAILABLE_POPUP);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR available status not changed", __FUNCTION__);
    }
}

void CVRAdaptor::onVRProxyAvailableStatus(bool bVRProxyAvailabilityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR proxy availibility status is: %d", __FUNCTION__, bVRProxyAvailabilityStatus);
    if(!bVRProxyAvailabilityStatus)
    {
        onVRStateChange(CVREnum::EN_VR_STATE_SESSION_END);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR proxy is available", __FUNCTION__);
    }
}


void CVRAdaptor::invPickListItemSelected(int iLineNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Line number is: %d", __FUNCTION__, iLineNo);
    if(ResourceFactory::getVRStubResource())
    {
        ResourceFactory::getVRStubResource()->listItemSelected(iLineNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR resource stub not created", __FUNCTION__);
    }
}

void CVRAdaptor::invSendVRResponse(CVREnum::EResponseType eResponseType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR response type is: %d", __FUNCTION__, eResponseType);
    if(ResourceFactory::getVRStubResource())
    {
        ResourceFactory::getVRStubResource()->sendVRResponse(static_cast<EResponseType>(eResponseType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR resource stub not created", __FUNCTION__);
    }
}

QAbstractListModel *CVRAdaptor::vrHelpCommands()
{
    QAbstractListModel* listModel = ((CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT) &&
                                     (CPowerModeAdaptor::getInstance().getPowerModeStatus() != CPowerModeEnums::VPM_ONE_HOUR)) ? &m_objVRHelpCommandListModel: &m_objVRHelpCommandListModelNoFATC;
    return listModel;
}

QAbstractListModel *CVRAdaptor::vrHelpCategories()
{
    QAbstractListModel* listModel = ((CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT) &&
                                     (CPowerModeAdaptor::getInstance().getPowerModeStatus() != CPowerModeEnums::VPM_ONE_HOUR)) ? &m_objVRHelpCategoryListModel: &m_objVRHelpCategoryListModelNoFATC;
    return listModel;
}

QStringList CVRAdaptor::mainVRCommands()
{
    QStringList strList = ((CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT) &&
                           (CPowerModeAdaptor::getInstance().getPowerModeStatus() != CPowerModeEnums::VPM_ONE_HOUR)) ? m_listMainVRCommands : m_listMainVRCommandsNoFATC;
   return strList;
}

void CVRAdaptor::initMainVRCommandsList(QStringList &lstCommands, SVRHelpCommands objCommands)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    lstCommands.clear();

    if(objCommands.m_mapVRHelpCommands.count(CVREnum::EN_VR_MAIN_CATEGORY) > 0)
    {
        lstCommands = objCommands.m_mapVRHelpCommands.at(CVREnum::EN_VR_MAIN_CATEGORY).m_listCommandText;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR Main command type not found in the map", __FUNCTION__);
    }
}

void CVRAdaptor::invUpdateVRHelpCommandList(int iVRHelpCommandType, QString strVRHelpCategoryName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    CVREnum::EVRHelpCategoryType eVRHelpCategoryType = static_cast<CVREnum::EVRHelpCategoryType>(iVRHelpCommandType);

    SVRHelpCommands objCmds = ((CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT) &&
                               (CPowerModeAdaptor::getInstance().getPowerModeStatus() != CPowerModeEnums::VPM_ONE_HOUR)) ? m_objVRHelpCommands : m_objVRHelpCommandsNoFATC;

    CVRHelpCommandListModel& objCmdListModel = ((CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT) &&
                                                (CPowerModeAdaptor::getInstance().getPowerModeStatus() != CPowerModeEnums::VPM_ONE_HOUR)) ? m_objVRHelpCommandListModel : m_objVRHelpCommandListModelNoFATC;

    if(objCmds.m_mapVRHelpCommands.count(eVRHelpCategoryType) > 0)
    {
        m_strVRHelpCategoryName = strVRHelpCategoryName;
        objCmdListModel.removeRows();
        objCmdListModel.insertRows(objCmds.m_mapVRHelpCommands.at(eVRHelpCategoryType).m_listCommandText);
        emit sigVRHelpCommandsUpdated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR command type not found in the map", __FUNCTION__);
    }
}

void CVRAdaptor::parseVRHelpCommands(QString strFile, CVRHelpCommandListModel& objCommandList, SVRHelpCommands &objCommands)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    //QString strVRHelpFilePath = "/mnt/data/VR/dialogManager/dialog/text/VR_HelpTexts.xml";

//    QString strVRHelpFilePath = qGuiApp->applicationDirPath();
//    strVRHelpFilePath.append("/VR_HelpTexts.xml");
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR help file path is: %s", __FUNCTION__, strFile.toStdString().c_str());
    QFile objVRHelpFile(strFile);

    if(!objVRHelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Could not open VR Help file", __FUNCTION__);
        m_bVRHelpFileReadStatus = false;
    }
    else
    {
        m_bVRHelpFileReadStatus = true;
        QXmlStreamReader objReader(&objVRHelpFile);
        QStringList listVRHelpCategory;
        listVRHelpCategory.clear();
        while((!objReader.atEnd()) && (!objReader.hasError()))
        {
            if(objReader.name() == "domainBtnCode")
            {
                foreach(const QXmlStreamAttribute &objAttributes, objReader.attributes())
                {
                    if (objAttributes.name().toString() == "text")
                    {
                        QString strValue = objAttributes.value().toString();
                        if(strValue == "Main Commands")
                        {
                            listVRHelpCategory.append(strValue);
                            parseCommands(objReader, CVREnum::EN_VR_MAIN_CATEGORY, objCommands);
                        }
                        else if(strValue == "Phone Commands")
                        {
                            listVRHelpCategory.append(strValue);
                            parseCommands(objReader, CVREnum::EN_VR_PHONE_CATEGORY, objCommands);
                        }
                        else if(strValue == "Media Commands")
                        {
                            listVRHelpCategory.append(strValue);
                            parseCommands(objReader, CVREnum::EN_VR_MEDIA_CATEGORY, objCommands);
                        }
                        else if(strValue == "Radio Commands")
                        {
                            listVRHelpCategory.append(strValue);
                            parseCommands(objReader, CVREnum::EN_VR_RADIO_CATEGORY, objCommands);
                        }
                        else if(strValue == "Climate Commands")
                        {
                            listVRHelpCategory.append(strValue);
                            parseCommands(objReader, CVREnum::EN_VR_CLIMATE_CATEGORY, objCommands);
                        }
                        else
                        {
                            //Attribute value not handled
                        }
                    }
                    else
                    {
                        //Atrribute not handled
                    }
                }
            }
            else
            {
                //Element/Node not handled
            }

            objReader.readNext();
        }

        //m_objVRHelpCategoryListModel.insertRows(listVRHelpCategory);
        objCommandList.insertRows(listVRHelpCategory);
        objVRHelpFile.close();
    }
}

void CVRAdaptor::parseCommands(QXmlStreamReader &objReader, CVREnum::EVRHelpCategoryType eCategoryType, SVRHelpCommands &objCommands)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    SVRCommandCategory objVRHelpMainCategory;
    objVRHelpMainCategory.clear();
    while(!((objReader.tokenType() == QXmlStreamReader::EndElement) && (objReader.name() == "domainBtnCode")))
    {
        if(objReader.name().toString() == "cmdText")
        {
            objVRHelpMainCategory.m_listCommandText.append(objReader.readElementText());
        }
        else if(objReader.name().toString() == "cmdPrompt")
        {
            objVRHelpMainCategory.m_listCommandPrompt.append(objReader.readElementText());
        }
        else
        {
            //do nothing
        }
        objReader.readNext();
    }
    //m_objVRHelpCommands.m_mapVRHelpCommands.insert({eCategoryType, objVRHelpMainCategory});
    objCommands.m_mapVRHelpCommands.insert({eCategoryType, objVRHelpMainCategory});
}

void CVRAdaptor::setRequestState(CVREnum::EVRRequestState eVRRequestState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Current VR request state is: %d, Incoming VR request state is: %d", __FUNCTION__, m_eVRRequestState, eVRRequestState);
    m_eVRRequestState = eVRRequestState;
}

void CVRAdaptor::requestVRBrowse()
{
    CMediaEnum::EMediaVRBrowseState eMediaVRBrowseState = CMediaAdaptor::getInstance().requestVRBrowse(static_cast<CMediaEnum::EMediaBrowseItem>(m_iMediaFilterType), m_iMediaFilterId);
    //Reset request state, vr filter type and filter id after requesting browse to media adaptor
    setRequestState(CVREnum::EN_NO_REQUEST);
    m_iMediaFilterType  = -1;
    m_iMediaFilterId    = -1;
    if(eMediaVRBrowseState == CMediaEnum::EMediaVRBrowseState::VR_BROWSE_STATE_FAILED)
    {
        if(ResourceFactory::getVRStubResource())
        {
            ResourceFactory::getVRStubResource()->sendVRResponse(EN_RESPONSE_TYPE_FAILURE);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR resource stub not created", __FUNCTION__);
        }
    }
    else
    {
        //Do nothing
    }
}

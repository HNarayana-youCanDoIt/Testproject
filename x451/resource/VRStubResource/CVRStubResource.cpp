/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRStubResource.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CVRStubResource class
 */

#include "CVRStubResource.h"
#include <CommonAPI/CommonAPI.hpp>
#include "logging.h"

CVRStubResource::CVRStubResource()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    /*
     * create the runtime
     */
    shared_ptr<CommonAPI::Runtime> pRunTime = CommonAPI::Runtime::get();
    if(pRunTime)
    {
        string strDomain = "local";
        string strConnectionInstance = "dbusconnection";
        string strInstanceName = "HMIService.vrInstance";
        m_pVRStubResourceImpl = make_shared<CVRStubResourceImpl>();
        bool bStatus = pRunTime->registerService(strDomain, strInstanceName, m_pVRStubResourceImpl, strConnectionInstance);
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: status of vr stub register is: %d", __FUNCTION__, bStatus);
    }
    else
    {
        // Error: could not load runtime
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: Could not load runtime", __FUNCTION__);
    }
}

CVRStubResource::~CVRStubResource()
{
    //TODO: need to unregister service
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
}

void CVRStubResource::activateVRSession(int iKeyState, EVRScreenID eScreenId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: hard key state: %d screen Id: %d", __FUNCTION__, iKeyState, static_cast<int>(eScreenId));
    EHardKeyState eKeyState = static_cast<EHardKeyState>(iKeyState);
    if(m_pVRStubResourceImpl)
    {
        m_pVRStubResourceImpl->fireActivateVREvent(getVRKeyState(eKeyState) , getVRScreenName(eScreenId));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR stub not created", __FUNCTION__);
    }
}

void CVRStubResource::deactivateVRSession()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(m_pVRStubResourceImpl)
    {
        m_pVRStubResourceImpl->fireCancelVREvent();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR stub not created", __FUNCTION__);
    }
}

void CVRStubResource::listItemSelected(int32_t iLineNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: line number is: %d", __FUNCTION__, iLineNo);
    if(m_pVRStubResourceImpl)
    {
        m_pVRStubResourceImpl->fireListItemTouchEvent(iLineNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR stub not created", __FUNCTION__);
    }
}

void CVRStubResource::sendVRResponse(EResponseType eResponseType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: response type is: %d", __FUNCTION__, static_cast<int>(eResponseType));
    if(m_pVRStubResourceImpl)
    {
        m_pVRStubResourceImpl->sendVRResponse(eResponseType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: VR stub not created", __FUNCTION__);
    }
}

hmiVRTypes::EKeyState CVRStubResource::getVRKeyState(EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: hard key state is: %d", __FUNCTION__, static_cast<int>(eKeyState));
    hmiVRTypes::EKeyState eVRKeyState = hmiVRTypes::EKeyState::EN_KEY_SHORT_RELEASE;
    switch(eKeyState)
    {
    case HKEY_STATE_LONGPRESSED:
        eVRKeyState = hmiVRTypes::EKeyState::EN_KEY_LONG_PRESS;
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: wrong hard key state received", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: vr key state is: %d", __FUNCTION__, eVRKeyState.value_);
    return eVRKeyState;
}

hmiVRTypes::EScreenName CVRStubResource::getVRScreenName(EVRScreenID eScreenId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Screen id: %d", __FUNCTION__, static_cast<int>(eScreenId));
    hmiVRTypes::EScreenName eVRScreenName = hmiVRTypes::EScreenName::EN_SCREEN_DEFAULT;
    switch(eScreenId)
    {
    case EN_SCREEN_DEFAULT:
        eVRScreenName = hmiVRTypes::EScreenName::EN_SCREEN_DEFAULT;
        break;

    case EN_SCREEN_W3W:
        eVRScreenName = hmiVRTypes::EScreenName::EN_SCREEN_W3W;
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: wrong Screen id", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR Screen name: %d", __FUNCTION__, eVRScreenName.value_);
    return eVRScreenName;
}

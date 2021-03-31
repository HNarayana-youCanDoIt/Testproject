/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
***************************************************************
*/
/**
* @file         CVRProxyResImpl.cpp
* @ingroup      HMIComponent
* @author       Rahul Singh Parihar
* @brief        CVRProxyResImpl will be an interface to communicate to VR service
* and to pass on the information to upper layers.
*/

#include <ResourceDeploymentConfig.h>
#include <ResourceMaster.h>
#include "CVRProxyResImpl.h"
#include "logging.h"

CVRProxyResImpl::CVRProxyResImpl()
    : m_objVRProxy(ResourceDeploymentConfig::getConfig().m_VR_Proxy.domain,
                   ResourceDeploymentConfig::getConfig().m_VR_Proxy.instance),
      m_pVRProxyEventProvider(new CVRProxyEventProvider()),
      m_bIsVRProxyAvailable(false),
      m_eVRState(UISSTypes::eVRStateEnum::E_VRStateNone),
      m_eVRDialogState(UISSTypes::eVRDialogActive::E_VR_DIALOG_INACTIVE)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    subscribeVRProxyCb();
}

CVRProxyResImpl::~CVRProxyResImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    delete m_pVRProxyEventProvider;
    m_pVRProxyEventProvider = nullptr;
}

CVRProxyEventProvider* CVRProxyResImpl::getVRProxyEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    return m_pVRProxyEventProvider;
}

void CVRProxyResImpl::onVRProxyStatusCb(AvailabilityStatus eAvailabilityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(AvailabilityStatus::AVAILABLE == eAvailabilityStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR,"%s, VR proxy status is TRUE", __FUNCTION__);
        m_bIsVRProxyAvailable = true;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s, VR proxy status is FALSE", __FUNCTION__);
        m_bIsVRProxyAvailable = false;
    }

    if(m_pVRProxyEventProvider)
    {
        m_pVRProxyEventProvider->updateVRProxyAvailableStatus(m_bIsVRProxyAvailable);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s, Event provider not created", __FUNCTION__);
    }
}

void CVRProxyResImpl::onVRStateAttributeCb(UISSTypes::eVRStateEnum eVRState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR state is: %d", __FUNCTION__, eVRState.value_);
    m_eVRState = eVRState;
    if(m_pVRProxyEventProvider)
    {
        m_pVRProxyEventProvider->updateVRStateChangeStatus(eVRState.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s, Event provider not created", __FUNCTION__);
    }
}

void CVRProxyResImpl::onVRDialogStateAttributeCb(UISSTypes::eVRDialogActive eVRDialogState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR dialog state is: %d", __FUNCTION__, eVRDialogState.value_);
    m_eVRDialogState = eVRDialogState;
    if(m_pVRProxyEventProvider)
    {
        m_pVRProxyEventProvider->updateVRDialogStateChangeStatus(eVRDialogState.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s, Event provider not created", __FUNCTION__);
    }
}

void CVRProxyResImpl::onVRAvailableStateAttributeCb(UISSTypes::sVRAvailable objVRAvailableState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR available status is: %d", __FUNCTION__, objVRAvailableState.getAvailableState());
    if(m_pVRProxyEventProvider)
    {
        m_pVRProxyEventProvider->updateVRAvailableStatus(objVRAvailableState.getAvailableState());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s, Event provider not created", __FUNCTION__);
    }
}

void CVRProxyResImpl::subscribeVRProxyCb()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    SUBSCRIBE(m_objVRProxy, getProxyStatusEvent(),                                  &CVRProxyResImpl::onVRProxyStatusCb,            _1 );
    SUBSCRIBE(m_objVRProxy, getVoiceRecognitionStateAttribute().getChangedEvent(),  &CVRProxyResImpl::onVRStateAttributeCb,          _1 );
    SUBSCRIBE(m_objVRProxy, getVrDialogActiveStateAttribute().getChangedEvent(),    &CVRProxyResImpl::onVRDialogStateAttributeCb,    _1 );
    SUBSCRIBE(m_objVRProxy, getVrAvailableStateAttribute().getChangedEvent(),       &CVRProxyResImpl::onVRAvailableStateAttributeCb, _1 );
}

/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CRCAResourceImpl.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* CRCAResourceImpl, Resource Implementation for the RCA module. Implements the IRCAResource interface
*/

#include "CRCAResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"

CRCAResourceImpl::CRCAResourceImpl():
    m_pRCAEventProvider(new CRCAEventProvider())
  , m_RCAProxy(ResourceDeploymentConfig::getConfig().m_RCA_Proxy.domain,ResourceDeploymentConfig::getConfig().m_RCA_Proxy.instance)
  , m_bRCAProxyAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    SUBSCRIBE(m_RCAProxy, getProxyStatusEvent(), &CRCAResourceImpl::rcaProxyStatusCb, _1);
}

CRCAResourceImpl::~CRCAResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);

    if (m_pRCAEventProvider)
    {
        delete m_pRCAEventProvider;
        m_pRCAEventProvider = nullptr;
    }
}

CRCAEventProvider* CRCAResourceImpl::getRCAEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    return m_pRCAEventProvider;
}

void CRCAResourceImpl::rcaProxyStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s, RCA proxy status : %d", __FUNCTION__, static_cast<int>(eStatus));

    if(CommonAPI::AvailabilityStatus::AVAILABLE == eStatus)
    {
        m_bRCAProxyAvailable = true;
        subscribeToRCAProxy();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s, RCA service NOT AVAILABLE",__FUNCTION__);
        m_bRCAProxyAvailable = false;
    }
}

void CRCAResourceImpl::subscribeToRCAProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    SUBSCRIBE(m_RCAProxy, getActionInitiatedFromTSREvent(), &CRCAResourceImpl::onRCAActionInitiatedCb, _1, _2)
}

void CRCAResourceImpl::onRCAActionInitiatedCb(const RCAServiceTypes::eActionInitiated eRCAActionInitiated, uint16_t uiIntInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s, RCA action initiated: %d, Int Data: %d",__FUNCTION__,static_cast<int>(eRCAActionInitiated), uiIntInfo);
    // Call event provider to propogate the enum and value to the upper layer
    if(m_pRCAEventProvider)
    {
        m_pRCAEventProvider->rcaActionUpdate(eRCAActionInitiated.value_, uiIntInfo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"RCA event provider is NULL");
    }
}

void CRCAResourceImpl::setHMIMediaBrowseStatusAsyncReq(bool bIsHMIInBrowseState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s, HMI Browse Status: %d",__FUNCTION__,bIsHMIInBrowseState);

    if(m_bRCAProxyAvailable)
    {
        m_RCAProxy->setHMIBrowseStatusAsync(bIsHMIInBrowseState, std::bind(&CRCAResourceImpl::setHMIMediaBrowseStatusAsyncCb,this, _1));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, RCA service NOT AVAILABLE",__FUNCTION__);
    }
}

void CRCAResourceImpl::setHMIMediaBrowseStatusAsyncCb(const CommonAPI::CallStatus& eCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s, call status: %d",__FUNCTION__, static_cast<int>(eCallStatus));
}

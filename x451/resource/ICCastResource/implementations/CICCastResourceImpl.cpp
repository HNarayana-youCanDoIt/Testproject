/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CICCastResourceImpl.h
* @ingroup      HMIComponent
* @author       Rahul Balyan
* IICCastResource, Resource Implementation for the IC Cast module. Implements the IICCastResource interface
*/

#include "CICCastResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"

CICCastResourceImpl::CICCastResourceImpl():
    m_pICCastEventProvider(new CICCastEventProvider()),
    m_ICCastProxy(ResourceDeploymentConfig::getConfig().m_ICCast_Proxy.domain,ResourceDeploymentConfig::getConfig().m_ICCast_Proxy.instance),
    m_bICCastProxyAvailable(false),
    m_bICCastValue(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);
    SUBSCRIBE(m_ICCastProxy, getProxyStatusEvent(), &CICCastResourceImpl::icCastProxyStatusCb, _1);
}

CICCastResourceImpl::~CICCastResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);

    if (m_pICCastEventProvider)
    {
        delete m_pICCastEventProvider;
        m_pICCastEventProvider = nullptr;
    }
}

CICCastEventProvider* CICCastResourceImpl::getICCastEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);
    return m_pICCastEventProvider;
}

void CICCastResourceImpl::subscribeToICCastProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);
}

IcRenderPresTypes::eIcRenderCallState CICCastResourceImpl::getICRenderCallState(EICRenderPhoneCallState ePhoneCallState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: ePhoneCallState is: %d", __FUNCTION__, ePhoneCallState);

    IcRenderPresTypes::eIcRenderCallState objIcRenderCallState = IcRenderPresTypes::eIcRenderCallState::ICRENDER_NO_PHONE_CALL;
    switch(ePhoneCallState)
    {
    case EN_ICRENDER_STATE_INCOMING_CALL:
        objIcRenderCallState = IcRenderPresTypes::eIcRenderCallState::ICRENDER_INCOMING_CALL;
        break;
    case EN_ICRENDER_STATE_OUTGOING_CALL:
        objIcRenderCallState = IcRenderPresTypes::eIcRenderCallState::ICRENDER_OUTGOING_CALL;
        break;
    case EN_ICRENDER_STATE_ACTIVE_CALL:
        objIcRenderCallState = IcRenderPresTypes::eIcRenderCallState::ICRENDER_ACTIVE_CALL;
        break;
    case EN_ICRENDER_STATE_ACTIVE_CONF_CALL:
        objIcRenderCallState = IcRenderPresTypes::eIcRenderCallState::ICRENDER_ACTIVE_CONF_CALL;
        break;
    case EN_ICRENDER_STATE_CALL_ONHOLD:
        objIcRenderCallState = IcRenderPresTypes::eIcRenderCallState::ICRENDER_CALL_ONHOLD;
        break;
    case EN_ICRENDER_STATE_CALL_ENDED:
        objIcRenderCallState = IcRenderPresTypes::eIcRenderCallState::ICRENDER_CALL_ENDED;
        break;
    case EN_ICRENDER_STATE_INVALID_CALL_STATE:
        objIcRenderCallState = IcRenderPresTypes::eIcRenderCallState::ICRENDER_INVALID_CALL_STATE;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for ic render call state passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "IcRenderPresTypes::eIcRenderCallState type is: %d", objIcRenderCallState.value_);
    return objIcRenderCallState;
}

void CICCastResourceImpl::icCastProxyStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s, ICCast proxy status : %d", __FUNCTION__, static_cast<int>(eStatus));

    if(CommonAPI::AvailabilityStatus::AVAILABLE == eStatus)
    {
        m_bICCastProxyAvailable = true;
        subscribeToICCastProxy();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ICCAST,"%s, ICCast service NOT AVAILABLE",__FUNCTION__);
        m_bICCastProxyAvailable = false;
    }
    if(m_pICCastEventProvider)
    {
        m_pICCastEventProvider->updateIcProxyAvailability(m_bICCastProxyAvailable);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ICCAST,"%s, m_pICCastEventProvider not available", __FUNCTION__);
    }
}

void CICCastResourceImpl::setIcRenderPhoneCallStateAsyncReq(EICRenderPhoneCallState ePhoneCallState, const string& strContactNameNum, int8_t cCallId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s, eICRenderCallState is: %d, strContactNameNum is: %s, cCallId is: %d", __FUNCTION__,
             ePhoneCallState, strContactNameNum.c_str(), cCallId);

    if(m_bICCastProxyAvailable)
    {
        m_ICCastProxy->setIcRenderPhoneCallStateAsync(getICRenderCallState(ePhoneCallState), strContactNameNum, cCallId,
                                                      std::bind(&CICCastResourceImpl::setIcRenderPhoneCallStateAsyncReqCb,
                                                                this, _1));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ICCAST,"%s, IC cast proxy not available",__FUNCTION__);
    }
}

void CICCastResourceImpl::setIcRenderSmsIndicationAsyncReq(bool bSmsIndicationFlag, const string &strContactNameNum)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s, bSmsIndicationFlag is: %d, strContactNameNum is: %s", __FUNCTION__,
             bSmsIndicationFlag, strContactNameNum.c_str());

    if(m_bICCastProxyAvailable)
    {
        m_ICCastProxy->setIcRenderSmsRxIndicationAsync(bSmsIndicationFlag, strContactNameNum,
                                                       std::bind(&CICCastResourceImpl::setIcRenderSmsIndicationAsyncReqCb,
                                                                 this, _1));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ICCAST,"%s, IC cast proxy not available",__FUNCTION__);
    }
}

void CICCastResourceImpl::setIcRenderPhoneCallStateAsyncReqCb(const CallStatus& eCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s, eCallStatus is: %d", __FUNCTION__, static_cast<int>(eCallStatus));
}

void CICCastResourceImpl::setIcRenderSmsIndicationAsyncReqCb(const CallStatus& eCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s, eCallStatus is: %d", __FUNCTION__, static_cast<int>(eCallStatus));
}

void CICCastResourceImpl::setIcRenderCastAsyncReq(int iICCastTypeEnum, const bool bICCastStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s, eICCastTypeEnum is: %d, bICCastOnOffValue is: %d", __FUNCTION__,
             iICCastTypeEnum, bICCastStatus);

    if(m_bICCastProxyAvailable)
    {
        IcRenderPresTypes::eIcRenderCast eICCastRenderCastValue = static_cast<IcRenderPresTypes::eIcRenderCast::Literal>(iICCastTypeEnum);
        m_ICCastProxy->setIcRenderCastAsync(eICCastRenderCastValue, !(bICCastStatus),
                                            std::bind(&CICCastResourceImpl::setIcRenderCastAsyncReqCb,
                                                      this, _1));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ICCAST,"%s, IC cast proxy not available", __FUNCTION__);
    }

}

void CICCastResourceImpl::setIcRenderCastAsyncReqCb(const CallStatus &eCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s, eCallStatus is: %d", __FUNCTION__, static_cast<int>(eCallStatus));
    if(m_pICCastEventProvider)
    {
        m_pICCastEventProvider->updateIcRenderCastAsyncReqCb(static_cast<int>(eCallStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ICCAST,"%s, m_pICCastEventProvider not available", __FUNCTION__);
    }

}

void CICCastResourceImpl::getIcRenderCastAsync(int iIcRenderCastComponent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s, iIcRenderCastComponent is: %d", __FUNCTION__, iIcRenderCastComponent);

    if(m_bICCastProxyAvailable)
    {
        IcRenderPresTypes::eIcRenderCast eIcRenderCast_enum = static_cast<IcRenderPresTypes::eIcRenderCast::Literal> (iIcRenderCastComponent);
        m_ICCastProxy->getIcRenderCastAsync(eIcRenderCast_enum, std::bind(&CICCastResourceImpl::getIcRenderCastAsyncReqCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ICCAST,"%s, IC cast proxy not available", __FUNCTION__);
    }
}

void CICCastResourceImpl::getIcRenderCastAsyncReqCb(const CallStatus &eCallStatus, bool bIcCastValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s, eCallStatus is: %d | bIcCastValue = %d ", __FUNCTION__, static_cast<int>(eCallStatus), bIcCastValue);
    if(m_pICCastEventProvider)
    {
        if(CallStatus::SUCCESS == eCallStatus)
        {
            m_bICCastValue = bIcCastValue;
            m_pICCastEventProvider->updateIcCastValue(!bIcCastValue);
        }
        else
        {
            //Do Nothing.
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ICCAST,"%s, m_pICCastEventProvider not available", __FUNCTION__);
    }

}

void CICCastResourceImpl::setIcColorTheme(int iCurrentThemeType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s iCurrentThemeType: %d", __FUNCTION__, iCurrentThemeType);
    if(m_bICCastProxyAvailable)
    {
        IcRenderPresTypes::eIcColorStatus_enum eIcCastTheme = static_cast<IcRenderPresTypes::eIcColorStatus_enum::Literal>(iCurrentThemeType);
        m_ICCastProxy->setIcColorThemeAsync(eIcCastTheme, std::bind(&CICCastResourceImpl::setIcColorThemeCb, this, _1));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ICCAST,"%s, IC cast proxy not available", __FUNCTION__);
    }
}

void CICCastResourceImpl::setIcColorThemeCb(const CallStatus &eCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s, eCallStatus is: %d", __FUNCTION__, static_cast<int>(eCallStatus));
}

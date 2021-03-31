/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDiagnosticResourceImpl.cpp
* @ingroup      HMIComponent
* @author       Manali Patil
* CDiagnosticResourceImpl, Resource Implementation for DiagnosticHandler
*/

#include "CDiagnosticResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"


CDiagnosticResourceImpl::CDiagnosticResourceImpl():
    m_pDiagnosticEventProvider(new CDiagnosticEventProvider()),
    m_DiagnosticProxy(ResourceDeploymentConfig::getConfig().m_Diagnostic_Proxy.domain,ResourceDeploymentConfig::getConfig().m_Diagnostic_Proxy.instance),
    m_iAmFmConnectionStatusValue(-1),
    m_iSwcConnectionStatusValue(-1),
    m_iMicConnectionStatusValue(-1)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    subscribeDiagnosticProxy();
}

void CDiagnosticResourceImpl::subscribeDiagnosticProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    SUBSCRIBE(m_DiagnosticProxy, getProxyStatusEvent(), &CDiagnosticResourceImpl::diagnosticStatusCb,_1);
}

CDiagnosticResourceImpl::~CDiagnosticResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    if (m_pDiagnosticEventProvider)
    {
        delete m_pDiagnosticEventProvider;
    }
}

CDiagnosticEventProvider* CDiagnosticResourceImpl::getDiagnosticEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    return m_pDiagnosticEventProvider;
}

void CDiagnosticResourceImpl::diagnosticStatusCb(CommonAPI::AvailabilityStatus eAvailabilityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);

    if(CommonAPI::AvailabilityStatus::AVAILABLE == eAvailabilityStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: Diagnostic status is available.", __FUNCTION__);
        SUBSCRIBE(m_DiagnosticProxy, getDiagAmFmAntennaStatusAttribute().getChangedEvent(), &CDiagnosticResourceImpl::getDiagAmFmAntennaStatusCb, _1 );
        SUBSCRIBE(m_DiagnosticProxy, getDiagSWCStatusAttribute().getChangedEvent(), &CDiagnosticResourceImpl::getDiagSWCStatusCb, _1 );
        SUBSCRIBE(m_DiagnosticProxy, getDiagMICStatusAttribute().getChangedEvent(), &CDiagnosticResourceImpl::getDiagMICStatusCb, _1 );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: Diagnostic status is not available: %d", __FUNCTION__, static_cast<int>(eAvailabilityStatus));
    }
}

void CDiagnosticResourceImpl::getDiagAmFmAntennaStatusCb(const diagTypedefs::eDiagConnectionState & eAntennaConnectionState)
{
    m_iAmFmConnectionStatusValue = static_cast<int> (eAntennaConnectionState);
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: Antenna status: %d", __FUNCTION__, m_iAmFmConnectionStatusValue);
    if(m_pDiagnosticEventProvider)
    {
        m_pDiagnosticEventProvider->updateAntennaConnectionStatus(m_iAmFmConnectionStatusValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: m_pDiagnosticEventProvider is NULL ", __FUNCTION__);
    }
}

void CDiagnosticResourceImpl::getDiagSWCStatusCb(const diagTypedefs::eDiagConnectionState & eSWCConnectionState)
{
    m_iSwcConnectionStatusValue = static_cast<int> (eSWCConnectionState);
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: SWC status: %d", __FUNCTION__, m_iSwcConnectionStatusValue);
    if(m_pDiagnosticEventProvider)
    {
        m_pDiagnosticEventProvider->updateSWCConnectionState(m_iSwcConnectionStatusValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: m_pDiagnosticEventProvider is NULL ", __FUNCTION__);
    }

}

void CDiagnosticResourceImpl::getDiagMICStatusCb(const diagTypedefs::eDiagConnectionState & eMicConnectionState)
{
    m_iMicConnectionStatusValue = static_cast<int> (eMicConnectionState);
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: MIC status: %d", __FUNCTION__, m_iMicConnectionStatusValue);
    if(m_pDiagnosticEventProvider)
    {
        m_pDiagnosticEventProvider->updateMICConnectionStatus(m_iMicConnectionStatusValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: m_pDiagnosticEventProvider is NULL ", __FUNCTION__);
    }
}

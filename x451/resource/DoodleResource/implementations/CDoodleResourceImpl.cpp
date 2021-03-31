/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDoodleResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * CDoodleResourceImpl, Resource Implementation for Doodle.
 */
//________________________________________________________________________________________________
#include "CDoodleResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"

#include <iomanip>
#include <sstream>

//________________________________________________________________________________________________
CDoodleResourceImpl::CDoodleResourceImpl():
    //m_objDoodleProxy(ResourceDeploymentConfig::getConfig().m_Doodle_Proxy.domain, ResourceDeploymentConfig::getConfig().m_Doodle_Proxy.instance),
    m_pEventProvider(new CDoodleEventProvider()),
    m_bProxyAvailability(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    subscribeDoodleProxy();
}
//________________________________________________________________________________________________
CDoodleResourceImpl::~CDoodleResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);

    unSubscribeDoodleProxy();
}
//________________________________________________________________________________________________
CDoodleEventProvider *CDoodleResourceImpl::getEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    return m_pEventProvider;
}
//________________________________________________________________________________________________
void CDoodleResourceImpl::subscribeDoodleProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    //SUBSCRIBE(m_objDoodleProxy, getProxyStatusEvent(), &CDoodleResourceImpl::DoodleProxyStatusCb, _1);
}
//________________________________________________________________________________________________
void CDoodleResourceImpl::unSubscribeDoodleProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
bool CDoodleResourceImpl::getProxyAvailabilityStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s m_bProxyAvailability %d", __FUNCTION__, m_bProxyAvailability);
    return m_bProxyAvailability;
}
//________________________________________________________________________________________________
void CDoodleResourceImpl::doodleProxyStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, Doodle service status : %d", __FUNCTION__, static_cast<int>(eStatus));
    m_bProxyAvailability = (CommonAPI::AvailabilityStatus::AVAILABLE == eStatus);
    if(m_pEventProvider)
    {
        m_pEventProvider->onProxyStatusChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s m_pEventProvider not available", __FUNCTION__);
    }
}
//________________________________________________________________________________________________

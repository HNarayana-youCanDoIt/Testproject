/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDisplayManagerResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         Contain implementation of all the methods declared in
 *                CDisplayManagerResourceImpl class
 */

#include "CDisplayManagerResourceImpl.h"
#include "CDisplayManagerEventProvider.h"
#include <ResourceDeploymentConfig.h>
#include <ResourceMaster.h>
#include "logging.h"

CDisplayManagerResourceImpl::CDisplayManagerResourceImpl()
    : m_pDisplayManagerEventProvider(new CDisplayManagerEventProvider()),
      m_objDisplayManagerProxy(ResourceDeploymentConfig::getConfig().m_DisplayManager_Proxy.domain,
                               ResourceDeploymentConfig::getConfig().m_DisplayManager_Proxy.instance),
      m_bIsDisplayManagerProxyAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);
    SUBSCRIBE(m_objDisplayManagerProxy, getProxyStatusEvent(),
              &CDisplayManagerResourceImpl::displayManagerStatusCb, _1);
    subscribeDisplayManagerCb();
}

CDisplayManagerResourceImpl::~CDisplayManagerResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);
    if (m_pDisplayManagerEventProvider)
    {
        delete m_pDisplayManagerEventProvider;
        m_pDisplayManagerEventProvider = NULL;
    }
}

CDisplayManagerEventProvider* CDisplayManagerResourceImpl::getDisplayManagerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);
    return m_pDisplayManagerEventProvider;
}

/******************************************************//**
 * @category REQUEST METHODS
 *******************************************************/

void CDisplayManagerResourceImpl::setDisplayOnOffFeatureAsyncReq(bool bDisplayStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);
    if(m_bIsDisplayManagerProxyAvailable)
    {
        m_objDisplayManagerProxy->setDisplayOnOffFeatureAsync(bDisplayStatus,
                                                              std::bind(&CDisplayManagerResourceImpl::setDisplayOnOffFeatureAsyncCb,
                                                                        this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL,"Display manager proxy not available");
    }
}

void CDisplayManagerResourceImpl::setDisplayBrightnessLevelAsyncReq(int16_t iBrightnessLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);

    if(m_bIsDisplayManagerProxyAvailable)
    {
        m_objDisplayManagerProxy->setDisplayBrightnessLevelAsync(iBrightnessLevel,
                                                                 std::bind(&CDisplayManagerResourceImpl::setDisplayBrightnessLevelAsyncCb,
                                                                           this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL,"Display manager proxy not available");
    }
}

void CDisplayManagerResourceImpl::setButtonPanelBrightnessLevelAsyncReq(int16_t iBrightnessLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);

    if(m_bIsDisplayManagerProxyAvailable)
    {
        m_objDisplayManagerProxy->setButtonPanelBrightnessAsync(iBrightnessLevel,
                                                                std::bind(&CDisplayManagerResourceImpl::setButtonPanelBrightnessLevelAsyncCb,
                                                                          this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL,"Display manager proxy not available");
    }
}

void CDisplayManagerResourceImpl::getDisplayBrightnessLevelAsyncReq()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);

    if(m_bIsDisplayManagerProxyAvailable)
    {
        m_objDisplayManagerProxy->getDisplayBrightnessLevelAsync(std::bind(&CDisplayManagerResourceImpl::getDisplayBrightnessLevelAsyncCb,
                                                                           this, _1, _2, _3));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL,"Display manager proxy not available");
    }

}


void CDisplayManagerResourceImpl::getButtonPanelBrightnessLevelAsyncReq()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);

    if(m_bIsDisplayManagerProxyAvailable)
    {
        m_objDisplayManagerProxy->getButtonPanelBrightnessLevelAsync(std::bind(&CDisplayManagerResourceImpl::getButtonPanelBrightnessLevelAsyncCb,
                                                                               this, _1, _2, _3));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "Display manager proxy not available");
    }
}


/******************************************************//**
 * @category CALLBACK METHODS
 *******************************************************/

void CDisplayManagerResourceImpl::displayManagerStatusCb(CommonAPI::AvailabilityStatus eStatus)
{
    if(eStatus == CommonAPI::AvailabilityStatus::AVAILABLE)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL," %s: Display Manager Proxy available.", __FUNCTION__);
        m_bIsDisplayManagerProxyAvailable = true;

        /* Get brightness level. whenever proxy gets available */
        getDisplayBrightnessLevelAsyncReq();

        /* Get Button panel brightness level. whenever proxy gets available */
        getButtonPanelBrightnessLevelAsyncReq();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL,"%s: Display Manager Proxy not available.", __FUNCTION__);
        m_bIsDisplayManagerProxyAvailable = false;
    }
}

/********************************************//**
 * @category RESPONSE CALLBACK METHODS
 ************************************************/

void CDisplayManagerResourceImpl::setDisplayOnOffFeatureAsyncCb(const CallStatus &eCallStatus, const DisplayMgrEventTypes::DmErrorStatus &eErrorStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);

    Q_UNUSED(eCallStatus)
    Q_UNUSED(eErrorStatus)
}

void CDisplayManagerResourceImpl::setDisplayBrightnessLevelAsyncCb(const CallStatus &eCallStatus, const DisplayMgrEventTypes::DmErrorStatus &eErrorStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);

    Q_UNUSED(eCallStatus)

    if ( (DisplayMgrEventTypes::DmErrorStatus::DmErrorStatus_Ok == eErrorStatus) && m_pDisplayManagerEventProvider )
    {
        m_pDisplayManagerEventProvider->updateBrightnessLevelResponse();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: m_pDisplayManagerEventProvider is NULL or eErrorStatus: %d", __FUNCTION__, eErrorStatus.value_);
    }

}

void CDisplayManagerResourceImpl::getDisplayBrightnessLevelAsyncCb(const CallStatus &eCallStatus, const int16_t &iBrightnessLevel, const DisplayMgrEventTypes::DmErrorStatus &eErrorStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);

    Q_UNUSED(eCallStatus)

    if( (DisplayMgrEventTypes::DmErrorStatus::DmErrorStatus_Ok == eErrorStatus) && m_pDisplayManagerEventProvider )
    {
        m_pDisplayManagerEventProvider->updateBrightnessLevel(iBrightnessLevel);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: m_pDisplayManagerEventProvider is NULL or error occured: eErrorStatus: %d", __FUNCTION__, eErrorStatus.value_);
    }

}

void CDisplayManagerResourceImpl::setButtonPanelBrightnessLevelAsyncCb(const CallStatus &eCallStatus, const DisplayMgrEventTypes::DmErrorStatus &eErrorStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);

    Q_UNUSED(eCallStatus)

    if ( (DisplayMgrEventTypes::DmErrorStatus::DmErrorStatus_Ok == eErrorStatus) && m_pDisplayManagerEventProvider )
    {
        m_pDisplayManagerEventProvider->updateButtonPanelBrightnessLevelResponse ();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: m_pDisplayManagerEventProvider is NULL or eErrorStatus: %d", __FUNCTION__, eErrorStatus.value_);
    }
}

void CDisplayManagerResourceImpl::getButtonPanelBrightnessLevelAsyncCb(const CallStatus &eCallStatus, const int16_t &iBrightnessLevel, const DisplayMgrEventTypes::DmErrorStatus &eErrorStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);

    Q_UNUSED(eCallStatus)

    if( (DisplayMgrEventTypes::DmErrorStatus::DmErrorStatus_Ok == eErrorStatus) && m_pDisplayManagerEventProvider )
    {
        m_pDisplayManagerEventProvider->updateButtonPanelBrightnessLevel(iBrightnessLevel);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: m_pDisplayManagerEventProvider is NULL or error occured: eErrorStatus: %d", __FUNCTION__, eErrorStatus.value_);
    }
}

void CDisplayManagerResourceImpl::onDisplayOnOffFeatureStatusCb(int32_t iDisplayOnOffFeatureStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iDisplayOnOffFeatureStatus: %d", __FUNCTION__, iDisplayOnOffFeatureStatus);

    if (m_pDisplayManagerEventProvider)
    {
        m_pDisplayManagerEventProvider->updateDisplayOnOffFeatureStatus(iDisplayOnOffFeatureStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: m_pDisplayManagerEventProvider is NULL", __FUNCTION__);
    }

}

void CDisplayManagerResourceImpl::onNightModeStatusCb(int32_t iNightModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iNightModeStatus: %d", __FUNCTION__, iNightModeStatus);

    if (m_pDisplayManagerEventProvider)
    {
        m_pDisplayManagerEventProvider->updateNightModeStatus(iNightModeStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: m_pDisplayManagerEventProvider is NULL", __FUNCTION__);
    }
}

/******************************************************//**
 * @category INTERNAL METHODS
 *******************************************************/

void CDisplayManagerResourceImpl::subscribeDisplayManagerCb()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s", __FUNCTION__);

    SUBSCRIBE(m_objDisplayManagerProxy, getDisplayOnOffStatusAttribute().getChangedEvent(), &CDisplayManagerResourceImpl::onDisplayOnOffFeatureStatusCb, _1);
    SUBSCRIBE(m_objDisplayManagerProxy, getDayNightModeStatusAttribute().getChangedEvent(), &CDisplayManagerResourceImpl::onNightModeStatusCb, _1);
}

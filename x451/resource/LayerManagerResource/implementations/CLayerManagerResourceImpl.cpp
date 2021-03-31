/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CLayerManagerResourceImpl.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CLayerManagerResourceImpl, Resource Implementation for Layer manager.
*/

#include "CLayerManagerResourceImpl.h"
#include "logging.h"
#include "ResourceMaster.h"
#include "ResourceDeploymentConfig.h"

const std::string VIDEO_SURFACE_ID = "videos"; // Need to decide video surface name once video playback is implemented
const std::string VOICE_ALERT_NOTIFICATION_SURFACE_ID = "voice-alert-hmi-notifications";
const std::string VOL_NOTIFICATION_SURFACE_ID = "vol-hmi-notifications";
const std::string HMI_SURFACE_ID = "hmi_main";

CLayerManagerResourceImpl::CLayerManagerResourceImpl():   
    m_bLayerManagerAvailable(false)
  , m_pLayerManagerEventProvider(new CLayerManagerEventProvider())
  , m_pLayerManagerProxy(ResourceDeploymentConfig::getConfig().m_LayerManager_Proxy.domain,ResourceDeploymentConfig::getConfig().m_LayerManager_Proxy.instance)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);
    subscribe();
}

CLayerManagerResourceImpl::~CLayerManagerResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);

    CommonAPI::CallStatus status;
    m_pLayerManagerProxy->subscribeProps(LayerManagerTypes::tObjectType::TYPE_LAYER, "notifications-vol", LayerManagerTypes::tPropertyType::PROPERTY_VISIBILITY, false, status);

    // Removes all event / property subscription for a client, as recommended by Layer manager documentation
    m_pLayerManagerProxy->unsubscribeAllAsync();
}

void CLayerManagerResourceImpl::subscribe()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
    SUBSCRIBE(m_pLayerManagerProxy,getProxyStatusEvent(),&CLayerManagerResourceImpl::layerManagerServiceStatusCb,_1)
}

void CLayerManagerResourceImpl::layerManagerServiceStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s, status: %d",__FUNCTION__,static_cast<int>(eStatus));

    if( CommonAPI::AvailabilityStatus::AVAILABLE == eStatus)
    {
        m_bLayerManagerAvailable = true;

        CommonAPI::CallStatus status;
        m_pLayerManagerProxy->subscribeProps(LayerManagerTypes::tObjectType::TYPE_LAYER, "notifications-vol", LayerManagerTypes::tPropertyType::PROPERTY_VISIBILITY, true, status);
        SUBSCRIBE(m_pLayerManagerProxy, getPropertyUpdateSelectiveEvent(), &CLayerManagerResourceImpl::onPropertyUpdateEventCb, _1);
    }
    else
    {
        m_bLayerManagerAvailable = false;
        LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"Layer manager Proxy not available");
    }
}

/******************* HVAC Notification surface ********************/

void CLayerManagerResourceImpl::showVoiceAlertNotificationSurface()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);

    if(m_bLayerManagerAvailable)
    {
        m_pLayerManagerProxy->showSurfaceAsync(VOICE_ALERT_NOTIFICATION_SURFACE_ID, false, std::bind(&CLayerManagerResourceImpl::showHVACNotificationSurfaceAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "Layer manager Proxy not available");
    }
}

void CLayerManagerResourceImpl::showHVACNotificationSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s, status = %d, result = %d", __FUNCTION__, static_cast<int>(eCallStatus), static_cast<int>(eResult));

    if (CallStatus::SUCCESS == eCallStatus)
    {
        // Inform notification surface show was successful
        if (m_pLayerManagerEventProvider)
        {
            m_pLayerManagerEventProvider->onShowNotificationSurfaceResult(static_cast<int>(eResult));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s, LayerManagerEventProvide is null", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, hideVoiceAlertNotificationSurface is not succesful.", __FUNCTION__);
    }

}

void CLayerManagerResourceImpl::hideVoiceAlertNotificationSurface()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);

    if(m_bLayerManagerAvailable)
    {
        m_pLayerManagerProxy->hideSurfaceAsync(VOICE_ALERT_NOTIFICATION_SURFACE_ID, std::bind(&CLayerManagerResourceImpl::hideHVACNotificationSurfaceAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"Layer manager Proxy not available");
    }
}

void CLayerManagerResourceImpl::hideHVACNotificationSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, status = %d, result = %d",__FUNCTION__, static_cast<int>(eCallStatus),static_cast<int>(eResult));

    if (CallStatus::SUCCESS == eCallStatus)
    {
        // Inform notification surface hide was successful
        if (m_pLayerManagerEventProvider)
        {
            m_pLayerManagerEventProvider->onHideNotificationSurfaceResult(static_cast<int>(eResult));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, LayerManagerEventProvide is null",__FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, hideVoiceAlertNotificationSurface is not succesful.", __FUNCTION__);
    }
}
/******************* End HVAC Notification surface ********************/

/******************* Volume Notification surface ********************/
void CLayerManagerResourceImpl::showVolNotificationSurface()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);

    if(m_bLayerManagerAvailable)
    {
        m_pLayerManagerProxy->showSurfaceAsync(VOL_NOTIFICATION_SURFACE_ID, false, std::bind(&CLayerManagerResourceImpl::showVolNotificationSurfaceAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"Layer manager Proxy not available");
    }
}

void CLayerManagerResourceImpl::showVolNotificationSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s, status = %d, result = %d", __FUNCTION__, static_cast<int>(eCallStatus), static_cast<int>(eResult));

    if (CallStatus::SUCCESS == eCallStatus)
    {
        // Inform notification surface show was successful
        if (m_pLayerManagerEventProvider)
        {
            m_pLayerManagerEventProvider->onShowNotificationSurfaceResult(static_cast<int>(eResult));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, LayerManagerEventProvide is null", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, showVolNotificationSurface is not succesful.", __FUNCTION__);
    }
}

void CLayerManagerResourceImpl::hideVolNotificationSurface()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);

    if(m_bLayerManagerAvailable)
    {
        m_pLayerManagerProxy->hideSurfaceAsync(VOL_NOTIFICATION_SURFACE_ID,std::bind(&CLayerManagerResourceImpl::hideVolNotificationSurfaceAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"Layer manager Proxy not available");
    }
}

void CLayerManagerResourceImpl::onPropertyUpdateEventCb(LayerManagerTypes::tProperty property)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, notification layer is top layer: %d", __FUNCTION__, static_cast<int>(property.getData().get<bool>()));

    bool bNotificationLayerVisibilityState = false;

    if(property.getPropertyType() == LayerManagerTypes::tPropertyType::PROPERTY_VISIBILITY)
    {
        if(property.getData().get<bool>())
        {
            bNotificationLayerVisibilityState = true;
        }
        else
        {
            //Do nothing
        }
        if (m_pLayerManagerEventProvider)
            m_pLayerManagerEventProvider->onNotificationLayerVisibilityState(bNotificationLayerVisibilityState);
        else
            LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, LayerManagerEventProvider is null",__FUNCTION__);
    }
    else
    {
        // Do nothing
    }
}

void CLayerManagerResourceImpl::hideVolNotificationSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, status = %d, result = %d", __FUNCTION__, static_cast<int>(eCallStatus), static_cast<int>(eResult));

    if (CallStatus::SUCCESS == eCallStatus)
    {
        // Inform notification surface hide was successful
        if (m_pLayerManagerEventProvider)
        {
            m_pLayerManagerEventProvider->onHideNotificationSurfaceResult(static_cast<int>(eResult));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, LayerManagerEventProvide is null", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, hideVolNotificationSurface is not succesful.", __FUNCTION__);
    }
}
/******************* End volume Notification surface ********************/


/******************* Generic surface ********************/
void CLayerManagerResourceImpl::showSurface(std::string strSurfaceName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);

    if(m_bLayerManagerAvailable)
    {
        m_pLayerManagerProxy->showSurfaceAsync(strSurfaceName,false,std::bind(&CLayerManagerResourceImpl::showSurfaceAsyncCb, this, _1,_2));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"Layer manager Proxy not available");
    }
}

void CLayerManagerResourceImpl::showSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, status = %d, result = %d",__FUNCTION__, static_cast<int>(eCallStatus), static_cast<int>(eResult));

    if (CallStatus::SUCCESS == eCallStatus)
    {
        if (m_pLayerManagerEventProvider)
        {
            m_pLayerManagerEventProvider->onShowSurfaceResult(static_cast<int>(eResult));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, LayerManagerEventProvide is null", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, showSurface is not succesful.", __FUNCTION__);
    }
}

void CLayerManagerResourceImpl::hideSurface(std::string strSurfaceName)
{

    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
    if(m_bLayerManagerAvailable)
    {
        m_pLayerManagerProxy->hideSurfaceAsync(strSurfaceName,std::bind(&CLayerManagerResourceImpl::hideSurfaceAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"Layer manager Proxy not available");
    }
}

void CLayerManagerResourceImpl::hideSurfaceAsyncCb(const CallStatus &eCallStatus, const LayerManagerTypes::tResult &eResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, status = %d, result = %d",__FUNCTION__, static_cast<int>(eCallStatus),static_cast<int>(eResult));

    if (CallStatus::SUCCESS == eCallStatus)
    {
        if (m_pLayerManagerEventProvider)
        {
            m_pLayerManagerEventProvider->onHideSurfaceResult(static_cast<int>(eResult));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, LayerManagerEventProvide is null",__FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, hideSurface is not succesful.", __FUNCTION__);
    }
}

/******************* End Generic surface ********************/

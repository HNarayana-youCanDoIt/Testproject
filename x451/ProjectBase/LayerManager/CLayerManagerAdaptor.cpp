/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CLayerManagerAdaptor.h
 * @ingroup         HMIComponent
 * @author          Mohit Rajani
 * CLayerManagerAdaptor, an Adaptor for LayerManager module,
 * CLayerManagerAdaptor used to communicate between QML and Resource Layer.
 */


#include "CLayerManagerAdaptor.h"
#include "ResourceFactory.hpp"
#include "LayerManagerResource/interfaces/ILayerManagerResource.h"
#include "HMIIncludes.h"
#include <CFramework.h>
#include "AndroidAuto/CAndroidAutoAdaptor.h"
#include "CarPlay/CAppleCarPlayAdaptor.h"

const std::string VOICE_ALERT_NOTIFICATION_SURFACE_ID = "voice-alert-hmi-notifications";
const std::string VOL_NOTIFICATION_SURFACE_ID = "vol-hmi-notifications";
const std::string HMI_SURFACE_ID = "hmi_main";
const std::string AA_SURFFACE_ID = "android_surface";
const std::string CP_SURFFACE_ID = "carplay_surface";

CLayerManagerAdaptor* CLayerManagerAdaptor::m_pLayerManagerAdaptor = nullptr;

CLayerManagerAdaptor::CLayerManagerAdaptor(QObject *parent) : QObject(parent)
  , m_pLayerManagerResource(ResourceFactory::getLayerManagerResource())
  , m_bNotificationLayerVisibilityState(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppLayerManagerAdaptor", this);
    CLayerManagerEnums::registerLayerManagerEnumsToQML();
    // Connect to projection adaptors, so that when project owner is HU we show hmi surface
    connect(CAndroidAutoAdaptor::getInstance(), SIGNAL(sigAndroidAutoProjectionStatusChanged(bool)), this, SLOT(sltProjectionOwnerChanged()));
    connect(CAppleCarPlayAdaptor::getInstance(),SIGNAL(sigAppleCarPlayProjectionStatusChanged(bool)),this,SLOT(sltProjectionOwnerChanged()));
}

CLayerManagerAdaptor::~CLayerManagerAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
    m_pLayerManagerAdaptor = nullptr;
}

void CLayerManagerAdaptor::showScene(CLayerManagerEnums::ESurfaceType eSurfaceType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, surfaceType: %d", __FUNCTION__, eSurfaceType);

    if(m_pLayerManagerResource)
    {
        switch(eSurfaceType)
        {
        case CLayerManagerEnums::SURFACE_HMI:
            m_pLayerManagerResource->showSurface(HMI_SURFACE_ID);
            break;
        case CLayerManagerEnums::SURFACE_HVAC_NOTIFICATIONS:
            m_pLayerManagerResource->showVoiceAlertNotificationSurface();
            break;
        case CLayerManagerEnums::SURFACE_VOL_NOTIFICATION:
            m_pLayerManagerResource->showVolNotificationSurface();
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, surfaceType: %d not supported", __FUNCTION__, eSurfaceType);
            break;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, resource is NULL", __FUNCTION__);
    }
}

void CLayerManagerAdaptor::hideScene(CLayerManagerEnums::ESurfaceType eSurfaceType)
{   
    if(m_pLayerManagerResource)
    {
        switch(eSurfaceType)
        {
        case CLayerManagerEnums::SURFACE_HVAC_NOTIFICATIONS:
            m_pLayerManagerResource->hideVoiceAlertNotificationSurface();
            break;
        case CLayerManagerEnums::SURFACE_VOL_NOTIFICATION:
            m_pLayerManagerResource->hideVolNotificationSurface();
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, surfaceType: %d not supported", __FUNCTION__, eSurfaceType);
            break;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, resource is NULL", __FUNCTION__);
    }
}

CLayerManagerAdaptor* CLayerManagerAdaptor::getInstance()
{
    if(nullptr == m_pLayerManagerAdaptor)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
        m_pLayerManagerAdaptor = new CLayerManagerAdaptor();
    }
    return m_pLayerManagerAdaptor;
}

/******** Notification Start ***********/

void CLayerManagerAdaptor::showVoiceAlertNotificationSurface()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);

    if(m_pLayerManagerResource)
    {
        m_pLayerManagerResource->showVoiceAlertNotificationSurface();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, resource is NULL", __FUNCTION__);
    }
}

void CLayerManagerAdaptor::hideVoiceAlertNotificationSurface()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);

    if(m_pLayerManagerResource)
    {
        m_pLayerManagerResource->hideVoiceAlertNotificationSurface();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s, resource is NULL", __FUNCTION__);
    }
}

void CLayerManagerAdaptor::showVolNotificationSurface()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);

    if(m_pLayerManagerResource)
    {
        m_pLayerManagerResource->showVolNotificationSurface();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s, resource is NULL", __FUNCTION__);
    }
}

void CLayerManagerAdaptor::hideVolNotificationSurface()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);

    if(m_pLayerManagerResource)
    {
        m_pLayerManagerResource->hideVolNotificationSurface();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s, resource is NULL", __FUNCTION__);
    }
}

void CLayerManagerAdaptor::onShowNotificationSurfaceResult(int iResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, result: %d", __FUNCTION__, iResult);
    emit sigShowNotificationSurfaceResult(iResult);
}

void CLayerManagerAdaptor::onHideNotificationSurfaceResult(int iResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, result: %d", __FUNCTION__, iResult);
    emit sigHideNotificationSurfaceResult(iResult);
}
/******** Notification End ***********/

/******** Surface Start ***********/
void CLayerManagerAdaptor::showSurface(QString strSurfaceName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
    if(m_pLayerManagerResource)
        m_pLayerManagerResource->showSurface(strSurfaceName.toStdString());
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, resource is NULL", __FUNCTION__);
}

void CLayerManagerAdaptor::hideSurface(QString strSurfaceName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
    if(m_pLayerManagerResource)
        m_pLayerManagerResource->hideSurface(strSurfaceName.toStdString());
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, resource is NULL", __FUNCTION__);
}

void CLayerManagerAdaptor::onShowSurfaceResult(int iResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, result: %d", __FUNCTION__, iResult);
    emit sigShowSurfaceResult(iResult);
}

void CLayerManagerAdaptor::onHideSurfaceResult(int iResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, result: %d", __FUNCTION__, iResult);
    emit sigHideSurfaceResult(iResult);
}

void CLayerManagerAdaptor::onNotificationLayerVisibiltyState(bool bVisibilityState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, state: %d ", __FUNCTION__, bVisibilityState);

    if (bVisibilityState != m_bNotificationLayerVisibilityState)
    {
        m_bNotificationLayerVisibilityState = bVisibilityState;
        emit sigNotificationLayerVisibilityState(m_bNotificationLayerVisibilityState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, state is same: %d", __FUNCTION__, bVisibilityState);
    }
}

bool CLayerManagerAdaptor::getNotificationLayerVisibiltyState()
{
    return m_bNotificationLayerVisibilityState;
}

/******** Surface End ***********/


void CLayerManagerAdaptor::sltProjectionOwnerChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, AA status: %d, CarPlay Status: %d", __FUNCTION__,
             CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus(),
             CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus());


    if (m_pLayerManagerResource)
    {
        //Projections has stopped due to requestNative or cable disconnection, hence call to show HMI surface
        if ((false == CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus())
                && (false == CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus()))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, calling showSurface on HMI", __FUNCTION__);
            // Since there is no active projection ongoing show HMI surface
            m_pLayerManagerResource->showSurface(HMI_SURFACE_ID);
        }
        else
        {
            //Do nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, resource is NULL", __FUNCTION__);
    }
}

/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CLayerManagerEventProvider.cpp
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CLayerManagerEventProvider, propogates LayerManager service events to the upper layers
*/

#include "CLayerManagerEventProvider.h"
#include "logging.h"

CLayerManagerEventProvider::CLayerManagerEventProvider(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
}

CLayerManagerEventProvider::~CLayerManagerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
}

void CLayerManagerEventProvider::onShowNotificationSurfaceResult(int result)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, result = %d",__FUNCTION__,result);
    emit sigShowNotificationSurfaceResult(result);
}

void CLayerManagerEventProvider::onHideNotificationSurfaceResult(int result)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, result = %d",__FUNCTION__,result);
    emit sigHideNotificationSurfaceResult(result);
}

void CLayerManagerEventProvider::onShowSurfaceResult(int result)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, result = %d",__FUNCTION__,result);
    emit sigShowSurfaceResult(result);
}

void CLayerManagerEventProvider::onHideSurfaceResult(int result)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, result = %d",__FUNCTION__,result);
    emit sigHideSurfaceResult(result);
}

void CLayerManagerEventProvider::onNotificationLayerVisibilityState(bool bVisibilityState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s, state: %d ", __FUNCTION__, bVisibilityState);
    emit sigNotificationLayerVisibilityState(bVisibilityState);
}

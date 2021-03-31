/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CLayerManagerEventHandler.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* @class        CLayerManagerEventHandler: Class acts as the event handler for all the signals/events sent by CLayerManagerEventProvider
* which informs LayerManager Adaptor about LayerManager resource events
*/

#include "CLayerManagerEventHandler.h"
#include "CLayerManagerAdaptor.h"
#include "HMIIncludes.h"
#include "LayerManagerResource/implementations/CLayerManagerResourceImpl.h"
#include <ResourceFactory.hpp>
#include "LayerManager/CLayerManagerEnums.h"

using namespace v0::com::harman::dcif;

CLayerManagerEventHandler::CLayerManagerEventHandler(QObject *parent) : QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);
    CLayerManagerAdaptor::getInstance();
    connectSignals();
}


CLayerManagerEventHandler::~CLayerManagerEventHandler()
{

}

void CLayerManagerEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s", __FUNCTION__);

    CLayerManagerResourceImpl* pLayerManagerResource = static_cast<CLayerManagerResourceImpl*>(ResourceFactory::getLayerManagerResource());

    if (pLayerManagerResource)
    {
        // make the signal and slot connection
        CLayerManagerEventProvider* pLayerManagerEventProvider = pLayerManagerResource->getLayerManagerEventProvider();

        if (pLayerManagerEventProvider)
        {
            //Notification
            connect(pLayerManagerEventProvider, &CLayerManagerEventProvider::sigShowNotificationSurfaceResult, this, &CLayerManagerEventHandler::sltShowNotificationSurfaceResult,Qt::QueuedConnection);
            connect(pLayerManagerEventProvider, &CLayerManagerEventProvider::sigHideNotificationSurfaceResult, this, &CLayerManagerEventHandler::sltHideNotificationSurfaceResult,Qt::QueuedConnection);
            connect(pLayerManagerEventProvider, &CLayerManagerEventProvider::sigNotificationLayerVisibilityState, this, &CLayerManagerEventHandler::sltNotificationLayerVisibilityState,Qt::QueuedConnection);

            // Surface (generic call)
            connect(pLayerManagerEventProvider, &CLayerManagerEventProvider::sigShowSurfaceResult, this, &CLayerManagerEventHandler::sltShowSurfaceResult,Qt::QueuedConnection);
            connect(pLayerManagerEventProvider, &CLayerManagerEventProvider::sigHideSurfaceResult, this, &CLayerManagerEventHandler::sltHideSurfaceResult,Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER, "pLayerManagerEventProvider is NULL");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER, "Resource returned as null from ResourceFactory");
    }

}

//Notification
void CLayerManagerEventHandler::sltShowNotificationSurfaceResult(int iResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s : result: %d", __FUNCTION__, iResult);

    if (CLayerManagerAdaptor::getInstance())
    {
        CLayerManagerAdaptor::getInstance()->onShowNotificationSurfaceResult(iResult);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER, "Layer manager adaptor is null");
    }
}

void CLayerManagerEventHandler::sltHideNotificationSurfaceResult(int iResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s : result: %d", __FUNCTION__, iResult);

    if (CLayerManagerAdaptor::getInstance())
    {
        CLayerManagerAdaptor::getInstance()->onHideNotificationSurfaceResult(iResult);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER, "Layer manager adaptor is null");
    }
}

void CLayerManagerEventHandler::sltNotificationLayerVisibilityState(bool bVisibilityState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s, state: %d ",__FUNCTION__,bVisibilityState);

    if (CLayerManagerAdaptor::getInstance())
    {
        CLayerManagerAdaptor::getInstance()->onNotificationLayerVisibiltyState(bVisibilityState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER,"Layer manager adaptor is null");
    }
}

//Surface
void CLayerManagerEventHandler::sltShowSurfaceResult(int iResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s : result: %d", __FUNCTION__, iResult);

    if (CLayerManagerAdaptor::getInstance())
    {
        CLayerManagerAdaptor::getInstance()->onShowSurfaceResult(iResult);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER, "Layer manager adaptor is null");
    }
}

void CLayerManagerEventHandler::sltHideSurfaceResult(int iResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER, "%s : result: %d", __FUNCTION__, iResult);

    if (CLayerManagerAdaptor::getInstance())
    {
        CLayerManagerAdaptor::getInstance()->onHideSurfaceResult(iResult);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_LAYER_MANAGER, "Layer manager adaptor is null");
    }
}

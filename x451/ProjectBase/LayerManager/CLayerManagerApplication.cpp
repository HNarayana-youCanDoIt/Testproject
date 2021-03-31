/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CLayerManagerApplication.cpp
 * @ingroup         HMIComponent
 * @author          Mohit Rajani
 * CLayerManagerApplication, an Application for LayerManager module,
 * CLayerManagerApplication act as creator calls for the adaptor and event handler
 */

#include "CLayerManagerApplication.h"
#include "CLayerManagerAdaptor.h"
#include "CLayerManagerEventHandler.h"

CLayerManagerApplication::CLayerManagerApplication(QObject* parent): QObject(parent)
  ,m_pLayerManagerAdaptor(CLayerManagerAdaptor::getInstance())
  ,m_pLayerManagerEventHandler(new CLayerManagerEventHandler())
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
}

CLayerManagerApplication::~CLayerManagerApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_LAYER_MANAGER,"%s", __FUNCTION__);
    if (m_pLayerManagerEventHandler)
    {
        delete m_pLayerManagerEventHandler;
    }
}

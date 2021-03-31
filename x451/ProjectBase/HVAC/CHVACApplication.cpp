/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHVACApplication.cpp
 * @ingroup         HMIComponent
 * @author          Mohit Rajani
 * CHVACApplication, an Application for HVAC (ccm) module,
 * CHVACApplication act as creator calls for the adaptor and event handler
 */

#include "CHVACApplication.h"
#include "CHVACAdaptor.h"
#include "CHVACEventHandler.h"

CHVACApplication::CHVACApplication(QObject* parent): QObject(parent)
  ,m_pHVACAdaptor(CHVACAdaptor::getInstance())
  ,m_pHVACEventHandler(new CHVACEventHandler())
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s", __FUNCTION__);
}

CHVACApplication::~CHVACApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s", __FUNCTION__);
    if (m_pHVACEventHandler)
    {
        delete m_pHVACEventHandler;
    }
}

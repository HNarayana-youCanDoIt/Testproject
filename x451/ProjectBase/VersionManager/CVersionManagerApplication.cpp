/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CVersionManagerApplication.cpp
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CVersionManagerApplication, an Application for Version Manager module,
 * CVersionManagerApplication act as mediator between QML and Statemachine.
 */

#include "CVersionManagerApplication.h"
#include "CVersionManagerAdaptor.h"
#include "CVersionManagerEventHandler.h"

CVersionManagerApplication::CVersionManagerApplication(QObject* parent): QObject(parent)
  ,m_pVersionManagerEventHandler(new CVersionManagerEventHandler())
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppVersionManagerApp",this);
    CVersionManagerAdaptor::getInstance();
}

CVersionManagerApplication::~CVersionManagerApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    if (m_pVersionManagerEventHandler)
    {
        delete m_pVersionManagerEventHandler;
    }
}

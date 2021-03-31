/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CRCAApplication.cpp
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CRCAApplication, an Application for RCA module,
 * CRCAApplication act as creator calls for the adaptor and event handler
 */

#include "CRCAApplication.h"
#include "CRCAAdaptor.h"
#include "CRCAEventHandler.h"

CRCAApplication::CRCAApplication(QObject* pParent): QObject(pParent)
  ,m_pRCAAdaptor(CRCAAdaptor::getInstance())
  ,m_pRCAEventHandler(new CRCAEventHandler())
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
}

CRCAApplication::~CRCAApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    if (m_pRCAEventHandler)
    {
        delete m_pRCAEventHandler;
        m_pRCAEventHandler = NULL;
    }
}

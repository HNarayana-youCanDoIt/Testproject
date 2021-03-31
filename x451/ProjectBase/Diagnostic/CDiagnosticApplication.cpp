/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDiagnosticApplication.cpp
 * @ingroup         HMIComponent
 * @author          Manali Patil
 * CDiagnosticApplication, an Application for Diagnostic module,
 * CDiagnosticApplication act as mediator between QML and Statemachine.
 */

#include "CDiagnosticApplication.h"
#include "CDiagnosticAdaptor.h"
#include "CDiagnosticEventHandler.h"

CDiagnosticApplication::CDiagnosticApplication(QObject* pParent): QObject(pParent)
    ,m_pDiagnosticEventHandler(new CDiagnosticEventHandler())
{
    CDiagnosticAdaptor::getInstance();
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
}

CDiagnosticApplication::~CDiagnosticApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    if (m_pDiagnosticEventHandler)
    {
        delete m_pDiagnosticEventHandler;
    }
}

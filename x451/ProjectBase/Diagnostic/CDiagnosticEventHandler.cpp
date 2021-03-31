/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDiagnosticEventHandler.cpp
* @ingroup      HMIComponent
* @author       Manali Patil
* @class        CDiagnosticEventHandler: Class has the slots for all the Signals sent by CDiagnosticEventHandler
*                                   which informs Diagnostic Adaptor about Diagnostic Resource Events
*/

#include "CDiagnosticEventHandler.h"
#include "CDiagnosticAdaptor.h"
#include "HMIIncludes.h"
#include "DiagnosticResource/implementations/CDiagnosticResourceImpl.h"
#include <ResourceFactory.hpp>

CDiagnosticEventHandler::CDiagnosticEventHandler(QObject *pParent) : QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    connectSignals();
}

CDiagnosticEventHandler::~CDiagnosticEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
}

void CDiagnosticEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    CDiagnosticResourceImpl* pDiagnosticResource = static_cast<CDiagnosticResourceImpl*>(ResourceFactory::getDiagnosticResource());
    if (pDiagnosticResource)
    {
        CDiagnosticEventProvider* pDiagnosticEventProvider = pDiagnosticResource->getDiagnosticEventProvider();
        // make the signal and slot connection
        if(pDiagnosticEventProvider)
        {
            connect(pDiagnosticEventProvider, SIGNAL(sigUpdateAntennaConnectionStatus(int)), this, SLOT(sltUpdateAntennaConnectionStatus(int)),Qt::QueuedConnection);
            connect(pDiagnosticEventProvider, SIGNAL(sigUpdateSWCConnectionState(int))    , this, SLOT(sltUpdateSWCConnectionState(int))    ,Qt::QueuedConnection);
            connect(pDiagnosticEventProvider, SIGNAL(sigUpdateMICConnectionStatus(int))    , this, SLOT(sltUpdateMICConnectionStatus(int))    ,Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"pDiagnosticEventProvider is NULL");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"Resource returns as null from ResourceFactory");
    }
}

void CDiagnosticEventHandler::sltUpdateAntennaConnectionStatus(int iAntennaConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    if(CDiagnosticAdaptor::getInstance())
    {
        CDiagnosticAdaptor::getInstance()->setAntennaConnectionStatus(static_cast<CDiagnosticEnum::EConnectionStatus> (iAntennaConnectionStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: CDiagnosticAdaptor::getInstance() is NULL", __FUNCTION__);
    }
}

void CDiagnosticEventHandler::sltUpdateSWCConnectionState(int iSWCConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    if(CDiagnosticAdaptor::getInstance())
    {
        CDiagnosticAdaptor::getInstance()->setSWCConnectionStatus(static_cast<CDiagnosticEnum::EConnectionStatus> (iSWCConnectionStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: CDiagnosticAdaptor::getInstance() is NULL", __FUNCTION__);
    }
}

void CDiagnosticEventHandler::sltUpdateMICConnectionStatus(int iMICConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    if(CDiagnosticAdaptor::getInstance())
    {
        CDiagnosticAdaptor::getInstance()->setMICConnectionStatus(static_cast<CDiagnosticEnum::EConnectionStatus> (iMICConnectionStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DIAGNOSTIC,"%s: CDiagnosticAdaptor::getInstance() is NULL", __FUNCTION__);
    }
}

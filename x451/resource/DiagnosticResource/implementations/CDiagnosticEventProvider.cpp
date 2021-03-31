/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDiagnosticEventProvider.cpp
* @ingroup      HMIComponent
* @author       Manali Patil
* CDiagnosticEventProvider, Class to send signals to DiagnosticHandler on Diagnostic Resource events
*/


#include "CDiagnosticEventProvider.h"
#include "logging.h"

CDiagnosticEventProvider::CDiagnosticEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
}

CDiagnosticEventProvider::~CDiagnosticEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
}

void CDiagnosticEventProvider::updateAntennaConnectionStatus(int iAntennaStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    emit sigUpdateAntennaConnectionStatus(iAntennaStatus);
}

void CDiagnosticEventProvider::updateSWCConnectionState(int iSWCStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    emit sigUpdateSWCConnectionState(iSWCStatus);
}

void CDiagnosticEventProvider::updateMICConnectionStatus(int iMICStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    emit sigUpdateMICConnectionStatus(iMICStatus);
}

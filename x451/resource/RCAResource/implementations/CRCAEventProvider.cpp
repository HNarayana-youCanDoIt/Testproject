/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CRCAEventProvider.cpp
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* CRCAEventProvider, class to propogate events for resource layer to the RCA Application layer
*/

#include "CRCAEventProvider.h"
#include "logging.h"

CRCAEventProvider::CRCAEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
}

CRCAEventProvider::~CRCAEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
}

void CRCAEventProvider::rcaActionUpdate(int iRCAActionInitiated, uint uiIntInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    emit sigRCAActionUpdate(iRCAActionInitiated, uiIntInfo);
}

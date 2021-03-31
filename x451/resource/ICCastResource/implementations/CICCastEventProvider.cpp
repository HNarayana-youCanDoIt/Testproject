/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CICCastEventProvider.h
* @ingroup      HMIComponent
* @author       Rahul Balyan
* CICastEventProvider, class to propogate events for resource layer to the ICCast Application layer
*/

#include "CICCastEventProvider.h"
#include "logging.h"

CICCastEventProvider::CICCastEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);
}

CICCastEventProvider::~CICCastEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);
}

void CICCastEventProvider::updateIcRenderCastAsyncReqCb(int iICCastResponseCbValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: iICCastResponseCbValue: %d", __FUNCTION__, iICCastResponseCbValue);
    emit sigUpdateIcRenderCastAsyncReqCb(iICCastResponseCbValue);

}

void CICCastEventProvider::updateIcProxyAvailability(bool bIcProxyAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: bIcProxyAvailability: %d", __FUNCTION__, bIcProxyAvailability);
    emit sigUpdateIcProxyAvailability(bIcProxyAvailability);
}

void CICCastEventProvider::updateIcCastValue(bool bIcCastValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: bIcCastValue: %d", __FUNCTION__, bIcCastValue);
    emit sigUpdateIcCastValue(bIcCastValue);
}

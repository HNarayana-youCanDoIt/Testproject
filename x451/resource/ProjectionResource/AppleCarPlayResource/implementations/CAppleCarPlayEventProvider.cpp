/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlayEventProvider.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CAppleCarPlayEventProvider, Class to send signals to AppleCarPlay Application
* layer on AppleCarPlay Resource events
*/

#include "CAppleCarPlayEventProvider.h"
#include "logging.h"

CAppleCarPlayEventProvider::CAppleCarPlayEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
}

CAppleCarPlayEventProvider::~CAppleCarPlayEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
}

void CAppleCarPlayEventProvider::updateAppleCarPlayConnectionStatus(bool bAppleCarPlayConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    emit sigUpdateAppleCarPlayConnectionStatus(bAppleCarPlayConnectionStatus);
}

void CAppleCarPlayEventProvider::updateAppleCarPlayProjectionStatus(bool bAppleCarPlayProjectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    emit sigUpdateAppleCarPlayProjectionStatus(bAppleCarPlayProjectionStatus);
}

void CAppleCarPlayEventProvider::updateAppleCarPlayPhoneStatus(bool bAppleCarPlayPhoneStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    emit sigUpdateAppleCarPlayPhoneStatus(bAppleCarPlayPhoneStatus);
}

void CAppleCarPlayEventProvider::updateCarPlaySiriStatus(bool bCarPlaySiriStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    emit sigUpdateCarPlaySiriStatus(bCarPlaySiriStatus);
}

void CAppleCarPlayEventProvider::updateAppleCarPlayDeviceName(const string &strAppleCarPlayDeviceName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    emit sigUpdateAppleCarPlayDeviceName(QString::fromStdString(strAppleCarPlayDeviceName));
}

void CAppleCarPlayEventProvider::updateAppleCarPlayRemoteUIStatus(bool bAppleCarPlayRemoteUIStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    emit sigUpdateAppleCarPlayRemoteUIStatus(bAppleCarPlayRemoteUIStatus);
}

void CAppleCarPlayEventProvider::updateCPNowPlayingInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    emit sigUpdateCPMediaNowPlayingInfo();
}

void CAppleCarPlayEventProvider::updateSmartFanState(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s, Smart Fan state : %d", __FUNCTION__, bValue);
    emit sigUpdateSmartFanState(bValue);
}

void CAppleCarPlayEventProvider::updateCPProxyStatus(bool bCPProxyStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bCPProxyStatus: %d", __FUNCTION__, bCPProxyStatus);
    emit sigUpdateCPProxyStatus(bCPProxyStatus);
}

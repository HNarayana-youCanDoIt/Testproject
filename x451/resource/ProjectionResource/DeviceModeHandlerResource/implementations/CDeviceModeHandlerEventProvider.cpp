/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDeviceModeHandlerEventProvider.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CDeviceModeHandlerEventProvider, Class to send signals to DeviceModeHandler
* Application layer on DeviceModeHandler Resource events
*/

#include "CDeviceModeHandlerEventProvider.h"
#include "logging.h"

CDeviceModeHandlerEventProvider::CDeviceModeHandlerEventProvider(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,__FUNCTION__);
}

CDeviceModeHandlerEventProvider::~CDeviceModeHandlerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,__FUNCTION__);
}

void CDeviceModeHandlerEventProvider::updateAAConnectionStatus(bool bAAConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s : bAAConnectionStatus: %d", __FUNCTION__, bAAConnectionStatus);
    emit sigUpdateAAConnectionStatus(bAAConnectionStatus);
}

void CDeviceModeHandlerEventProvider::updateAABondingReqStatus(bool bAABondingReqStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    emit sigUpdateAABondingReqStatus(bAABondingReqStatus);
}

void CDeviceModeHandlerEventProvider::updateCarPlayConnectionStatus(bool bCarPlayConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s : bCarPlayConnectionStatus: %d", __FUNCTION__, bCarPlayConnectionStatus);
    emit sigUpdateCarPlayConnectionStatus(bCarPlayConnectionStatus);
}

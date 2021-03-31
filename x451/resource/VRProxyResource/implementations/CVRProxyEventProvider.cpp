/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
* @file          CVRProxyEventProvider.cpp
* @ingroup       HMIComponent
* @author        Rahul Singh Parihar
* @brief         Contain implementation of all the methods declared in
*                CVRProxyEventProvider class
*/

#include "CVRProxyEventProvider.h"
#include "logging.h"

CVRProxyEventProvider::CVRProxyEventProvider(QObject *pParent)
    : QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
}

CVRProxyEventProvider::~CVRProxyEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
}

/************************************************************************//**
 * @category    METHODS
 ************************************************************************/
void CVRProxyEventProvider::updateVRStateChangeStatus(int iVRState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigVRStateChange(iVRState);
}

void CVRProxyEventProvider::updateVRDialogStateChangeStatus(int iVRDialogState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigVRDialogStateChange(iVRDialogState);
}

void CVRProxyEventProvider::updateVRAvailableStatus(bool bVRAvailableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigVRAvailableStatus(bVRAvailableStatus);
}

void CVRProxyEventProvider::updateVRProxyAvailableStatus(bool bVRProxyAvailableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigVRProxyAvailableStatus(bVRProxyAvailableStatus);
}

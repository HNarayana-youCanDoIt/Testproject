/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CEnggMenuEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CEnggMenuEventProvider class, The class will emit the signal
 * from Resource Layer to application Layer
 *
**/

#include "CEnggMenuEventProvider.h"
#include "logging.h"

CEnggMenuEventProvider::CEnggMenuEventProvider(QObject *pParent):
    QObject(pParent)
{

    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}



CEnggMenuEventProvider::~CEnggMenuEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}



void CEnggMenuEventProvider::updateDebugsLogCheckStatus(bool bDebugsLogStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s: bDebugsLogStatus: %d", __FUNCTION__, bDebugsLogStatus);
    emit sigUpdateDebugsLogCheckStatus(bDebugsLogStatus);
}

void CEnggMenuEventProvider::UpdateIpTypeStatus(int iIpStatusCb, int iIpTypeCb)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    emit  sigUpdateIpTypeStatus(iIpStatusCb, iIpTypeCb) ;
}

void CEnggMenuEventProvider::UpdateTestAutomationLaunchStatus(int iTestAutomationStatusCb, int iTestAutomationValueCb)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    emit  sigUpdateTestAutomation(iTestAutomationStatusCb, iTestAutomationValueCb) ;
}

void CEnggMenuEventProvider::updatefactoryResetWaitingStatus(bool bFactoryResetWaitingStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bFactoryResetWaitingStatus: %d" ,__FUNCTION__,bFactoryResetWaitingStatus);
    emit sigUpdateFactoryResetWaitingStatus(bFactoryResetWaitingStatus);
}

void CEnggMenuEventProvider::updateFactoryResetCompletionStatus(bool bFactoryResetCompletionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bFactoryResetCompletionStatus: %d" ,__FUNCTION__,bFactoryResetCompletionStatus);
    emit sigUpdateFactoryResetCompleteStatus(bFactoryResetCompletionStatus);

}

void CEnggMenuEventProvider::updateDeviceModeStatus(int iDeviceModeStatus, int iDeviceType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iDeviceModeStatus: %d, iDeviceType: %d" ,__FUNCTION__, iDeviceModeStatus, iDeviceType);
    emit sigUpdateDeviceModeStatus(iDeviceModeStatus, iDeviceType);

}

void CEnggMenuEventProvider::updateEnggProxyAvailabilityToHMI(bool bIsEnggMenuProxyAvailable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bIsEnggMenuProxyAvailable: %d", __FUNCTION__, bIsEnggMenuProxyAvailable);
    emit sigUpdateEnggProxyAvailabilityToHMI(bIsEnggMenuProxyAvailable);
}

void CEnggMenuEventProvider::updateExtractLogsStatus(int iExtractLogsProcessStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iExtractLogsProcessStatus: %d", __FUNCTION__, iExtractLogsProcessStatus);
    emit sigUpdateExtractLogsStatus(iExtractLogsProcessStatus);
}

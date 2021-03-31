/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggEventHandler.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande,Rajat Gupta
 * CEnggEventHandler, an Resource handler for Engineering module,
 * CEnggEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#include <CHMIMain.h>
#include <ResourceFactory.hpp>

#include "CEnggApplication.h"
#include "CEnggAdaptor.h"
#include "CEnggSM.h"
#include "CEnggEventHandler.h"
#include "EnggMenuResource/implementations/CEnggMenuResourceImpl.h"

//////////////////////////////////////////////////////////////////
// DataEventHandler related functions
//////////////////////////////////////////////////////////////////
CEnggEventHandler::CEnggEventHandler(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    connectSignals();
}



CEnggEventHandler::~CEnggEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}

void CEnggEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CEnggMenuResourceImpl* pEnggMenuResource = dynamic_cast<CEnggMenuResourceImpl*>(ResourceFactory::getEnggMenuResource());

    if(pEnggMenuResource)
    {
        CEnggMenuEventProvider* pEnggMenuEventProvider = pEnggMenuResource->getEnggMenuDataEventProvider();
        if(pEnggMenuEventProvider)
        {
            connect(pEnggMenuEventProvider, SIGNAL(sigUpdateDebugsLogCheckStatus(bool)),this,SLOT(sltUpdateDebugsLogCheckStatus(bool)), Qt::QueuedConnection);
            connect(pEnggMenuEventProvider, SIGNAL(sigUpdateIpTypeStatus(int,int)),this,SLOT(sltUpdateIpTypeStatus(int,int)), Qt::QueuedConnection);
            connect(pEnggMenuEventProvider, SIGNAL(sigUpdateTestAutomation(int,int)),this,SLOT(sltUpdateTestAutomationStatus(int,int)), Qt::QueuedConnection);
            connect(pEnggMenuEventProvider, SIGNAL(sigUpdateFactoryResetWaitingStatus(bool)),this,SLOT(sltUpdateFactoryResetWaitingStatus(bool)), Qt::QueuedConnection);
            connect(pEnggMenuEventProvider, SIGNAL(sigUpdateFactoryResetCompleteStatus(bool)),this,SLOT(sltUpdateFactoryResetCompletionStatus(bool)), Qt::QueuedConnection);
            connect(pEnggMenuEventProvider, SIGNAL(sigUpdateDeviceModeStatus(int, int)),this,SLOT(sltUpdateDeviceModeStatus(int, int)), Qt::QueuedConnection);
            connect(pEnggMenuEventProvider, SIGNAL(sigUpdateEnggProxyAvailabilityToHMI(bool)), this, SLOT(sltUpdateEnggProxyAvailabilityToHMI(bool)), Qt::QueuedConnection);
            connect(pEnggMenuEventProvider, SIGNAL(sigUpdateExtractLogsStatus(int)), this, SLOT(sltUpdateExtractLogsStatus(int)), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA, "%s: pEnggMenuEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA, "%s: EnggMenu Resource is returned NULL from Resource Factory", __FUNCTION__);
    }
}

void CEnggEventHandler::sltUpdateDebugsLogCheckStatus(bool bDebugsLogStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s : bDebugsLogStatus: %d", __FUNCTION__, bDebugsLogStatus);
    CEnggAdaptor::getInstance()->setDebugsLogCheckStatus(bDebugsLogStatus);
}

void CEnggEventHandler::sltUpdateIpTypeStatus(int iIpStatusCb, int iIpTypeCb)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s : iIpStatusCb: %d ,iIpTypeCb : %d ", __FUNCTION__, iIpStatusCb, iIpTypeCb);
    CEnggAdaptor::getInstance()->setIpTypeStatus(iIpStatusCb, iIpTypeCb);
}

void CEnggEventHandler::sltUpdateTestAutomationStatus(int iTestAutomationStatusCb, int iTestAutomationValueCb)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s : iTestAutomationStatusCb: %d ,iTestAutomationValueCb : %d ", __FUNCTION__, iTestAutomationStatusCb, iTestAutomationValueCb);
    CEnggAdaptor::getInstance()->setEnggMenuTestAutomationStatus(iTestAutomationStatusCb, iTestAutomationValueCb);
}

void CEnggEventHandler::sltUpdateFactoryResetWaitingStatus(bool bFactoryResetWaitingStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CEnggAdaptor::getInstance()->setFactoryResetWaitingStatus(bFactoryResetWaitingStatus);
}

void CEnggEventHandler::sltUpdateFactoryResetCompletionStatus(bool bFactoryResetCompletionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CEnggAdaptor::getInstance()->setFactoryResetCompletionStatus(bFactoryResetCompletionStatus);
}

void CEnggEventHandler::sltUpdateDeviceModeStatus(int iDeviceModeStatus, int iDeviceType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iDeviceModeStatus: %d, iDeviceType: %d", __FUNCTION__, iDeviceModeStatus, iDeviceType);
    CEnggAdaptor::getInstance()->setDeviceModeStatus(iDeviceModeStatus, iDeviceType );
}

void CEnggEventHandler::sltUpdateEnggProxyAvailabilityToHMI(bool bIsEnggMenuProxyAvailable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bIsEnggMenuProxyAvailable: %d", __FUNCTION__, bIsEnggMenuProxyAvailable);
    CEnggAdaptor::getInstance()->updateEnggMenuParametersOnProxyAvailability(bIsEnggMenuProxyAvailable);
}

void CEnggEventHandler::sltUpdateExtractLogsStatus(int iExtractLogsProcessStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iExtractLogsProcessStatus: %d", __FUNCTION__, iExtractLogsProcessStatus);
    CEnggAdaptor::getInstance()->setExtractLogsStatus(static_cast<CEnggMenuEnum::EEnggMenuExtractLogsStatus>(iExtractLogsProcessStatus));
}

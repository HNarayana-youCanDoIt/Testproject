/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CEnggMenuResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CEnggMenuResourceImpl class, The class that will implement the
 *  resources from proxy side to this Resource layer and then further
 *
 *
**/

#include "CEnggMenuResourceImpl.h"
#include "logging.h"
#include <ResourceMaster.h>
#include "ResourceDeploymentConfig.h"
#include "ProjectBase/HMIApplication/CHMIApplication.h"
#include <cstring>
#include <string>

CEnggMenuResourceImpl::CEnggMenuResourceImpl():
    m_pEnggMenuEventProvider(new CEnggMenuEventProvider())
  ,m_pEnggMenuPressCtrlProxy(ResourceDeploymentConfig::getConfig().m_EnggMenu_Proxy.domain,ResourceDeploymentConfig::getConfig().m_EnggMenu_Proxy.instance)
  ,m_bIsEnggServiceAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    SUBSCRIBE(m_pEnggMenuPressCtrlProxy, getProxyStatusEvent(), &CEnggMenuResourceImpl::enggMenuServiceStatusCb,_1);
}



CEnggMenuResourceImpl::~CEnggMenuResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if(m_pEnggMenuEventProvider)
    {
        delete m_pEnggMenuEventProvider;
        m_pEnggMenuEventProvider = NULL;
    }

}



CEnggMenuEventProvider *CEnggMenuResourceImpl::getEnggMenuDataEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    return m_pEnggMenuEventProvider;
}



void CEnggMenuResourceImpl::subscribe()
{
    //Todo: Here the Proxies will be subscribed whichever will be used in EnggMenu
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    SUBSCRIBE(m_pEnggMenuPressCtrlProxy,getFactoryResetCompleteEvent(),&CEnggMenuResourceImpl::getFactoryResetCompleteEventCb,_1)

}



void CEnggMenuResourceImpl::enggMenuServiceStatusCb(CommonAPI::AvailabilityStatus eStatus)
{

    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: eStatus: %d", __FUNCTION__, static_cast<int> (eStatus));
    if(CommonAPI::AvailabilityStatus::AVAILABLE ==  eStatus )
    {
        m_bIsEnggServiceAvailable = true;
        subscribe();
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"EnggMenu Service Available");
    }
    else
    {
        m_bIsEnggServiceAvailable = false;
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"EnggMenu Service Not Available");
    }

    updateEnggProxyAvailabilityToHMI(m_bIsEnggServiceAvailable);

}

void CEnggMenuResourceImpl::getFactoryResetCompleteEventCb(bool bResetFactoryCompleteStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bResetFactoryCompleteStatus: %d", __FUNCTION__,bResetFactoryCompleteStatus);
    if(m_pEnggMenuEventProvider)
    {
        if( bResetFactoryCompleteStatus )
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: SUCCESS bResetFactoryCompleteStatus SUCCESS", __FUNCTION__);
            m_pEnggMenuEventProvider->updateFactoryResetCompletionStatus(bResetFactoryCompleteStatus);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: SUCCESS bResetFactoryCompleteStatus FAILURE", __FUNCTION__);
            m_pEnggMenuEventProvider->updateFactoryResetCompletionStatus(bResetFactoryCompleteStatus);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU,"EnggMenuEventProvider is null");
    }

}

void CEnggMenuResourceImpl::startLoggingAsyncCb(const CommonAPI::CallStatus &eCallStatus , const EnggMenuTypes::retStatus &eReturnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s, eCallStatus :%d, eReturnStatus : %d", __FUNCTION__, static_cast<int>(eCallStatus), static_cast<int>(eReturnStatus));
    if(m_pEnggMenuEventProvider)
    {
        m_pEnggMenuEventProvider->updateDebugsLogCheckStatus((EnggMenuTypes::retStatus::SUCCESS == eReturnStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU,"EnggMenuEventProvider is Null");
    }

}

void CEnggMenuResourceImpl::stopLoggingAsyncCb(const CommonAPI::CallStatus &eCallStatus , const EnggMenuTypes::retStatus &eReturnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s, eCallStatus :%d, eReturnStatus : %d", __FUNCTION__, static_cast<int>(eCallStatus), static_cast<int>(eReturnStatus));
    if(m_pEnggMenuEventProvider)
    {
        m_pEnggMenuEventProvider->updateDebugsLogCheckStatus(!(EnggMenuTypes::retStatus::SUCCESS == eReturnStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU,"%s EnggMenuEventProvider is Null", __FUNCTION__);
    }
}



void CEnggMenuResourceImpl::setSystemStaticIpAddressCb(const CallStatus &callStatus, const EnggMenuTypes::retStatus &returnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: callStatus %d ,returnStatus  %d", __FUNCTION__, static_cast<int> (callStatus), static_cast<int> (returnStatus));
    if(m_pEnggMenuEventProvider)
    {
        m_pEnggMenuEventProvider->UpdateIpTypeStatus(static_cast<int> (returnStatus) , EIpType::IP_STATIC);
    }

    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: EnggMenuEventProvider is null", __FUNCTION__);
    }
}



void CEnggMenuResourceImpl::setSystemDynamicIpAddressCb(const CallStatus &callStatus, const EnggMenuTypes::retStatus &returnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: callStatus %d, returnStatus: %d", __FUNCTION__, static_cast<int> (callStatus), static_cast<int> (returnStatus));
    if(m_pEnggMenuEventProvider)
    {
        m_pEnggMenuEventProvider->UpdateIpTypeStatus(static_cast<int> (returnStatus) , EIpType::IP_DYNAMIC);
    }

    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU,"%s EnggMenuEventProvider is null", __FUNCTION__);
    }
}



void CEnggMenuResourceImpl::testAutomationStartServiceCb(const CallStatus &status, const EnggMenuTypes::retStatus &returnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: status : %d, returnStatus %d", __FUNCTION__, static_cast<int> (status), static_cast<int> (returnStatus));
    if(m_pEnggMenuEventProvider)
    {
        if( EnggMenuTypes::retStatus::SUCCESS == returnStatus)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: testAutomationStartServiceCb Status ::SUCCESS ", __FUNCTION__);
            m_pEnggMenuEventProvider->UpdateTestAutomationLaunchStatus(static_cast<int> (returnStatus), EResourceTestAutomationStatus::TEST_AUTOMATION_ENABLE);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: testAutomationStartServiceCb Status ::FAILURE ", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU,"%s EnggMenuEventProvider is null", __FUNCTION__);
    }
}



void CEnggMenuResourceImpl::testAutomationStopServiceCb(const CallStatus &status, const EnggMenuTypes::retStatus &returnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: status : %d, returnStatus %d", __FUNCTION__, static_cast<int> (status), static_cast<int> (returnStatus));
    if(m_pEnggMenuEventProvider)
    {
        if(EnggMenuTypes::retStatus::SUCCESS == returnStatus)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: testAutomationStopServiceCb Status ::SUCCESS ", __FUNCTION__);
            m_pEnggMenuEventProvider->UpdateTestAutomationLaunchStatus(static_cast<int> (returnStatus), EResourceTestAutomationStatus::TEST_AUTOMATION_DISABLE);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: testAutomationStopServiceCb Status ::FAILURE ", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: EnggMenuEventProvider is null", __FUNCTION__);
    }
}

void CEnggMenuResourceImpl::factoryResetCb(const CallStatus& callStatus, const EnggMenuTypes::retStatus &returnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: status %d, returnStatus: %d", __FUNCTION__, static_cast<int> (callStatus), static_cast<int> (returnStatus));
    if(m_pEnggMenuEventProvider)
    {
        if(EnggMenuTypes::retStatus::SUCCESS == returnStatus)
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: CALLBACK SUCCESS ", __FUNCTION__);
            m_pEnggMenuEventProvider->updatefactoryResetWaitingStatus(true);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: CALLBACK FAILURE ", __FUNCTION__);
            m_pEnggMenuEventProvider->updatefactoryResetWaitingStatus(false);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: EnggMenuEventProvider is null", __FUNCTION__);
    }
}

void CEnggMenuResourceImpl::setDeviceModeCb(const CallStatus &callStatus, const EnggMenuTypes::modeType & modeType, const EnggMenuTypes::deviceModeStatus &deviceModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: status: %d, modeType: %d, deviceModeStatus: %d ", __FUNCTION__, static_cast<int> (callStatus), static_cast<int> (modeType), static_cast<int> (deviceModeStatus));
    if(m_pEnggMenuEventProvider)
    {
        m_pEnggMenuEventProvider->updateDeviceModeStatus(static_cast<int> (deviceModeStatus), static_cast<int> (modeType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: EnggMenuEventProvider is null", __FUNCTION__);
    }
}


void CEnggMenuResourceImpl::startDebugLogsService()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_bIsEnggServiceAvailable: %d", __FUNCTION__, m_bIsEnggServiceAvailable);
    if(m_bIsEnggServiceAvailable)
    {
       m_pEnggMenuPressCtrlProxy->startSystemLoggingAsync(std::bind(&CEnggMenuResourceImpl::startLoggingAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU,"%s: EnggService is not Available.", __FUNCTION__);
    }
}



void CEnggMenuResourceImpl::stopDebugLogsService()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s: m_bIsEnggServiceAvailable: %d", __FUNCTION__, m_bIsEnggServiceAvailable);

    if(m_bIsEnggServiceAvailable)
    {
       m_pEnggMenuPressCtrlProxy->stopSystemLoggingAsync(std::bind(&CEnggMenuResourceImpl::stopLoggingAsyncCb, this, _1, _2));
    }
	else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU,"%s: EnggService is not Available.", __FUNCTION__);
    }
}

void CEnggMenuResourceImpl::extractDebugLogs()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s: m_bIsEnggServiceAvailable: %d", __FUNCTION__, m_bIsEnggServiceAvailable);

    if(m_bIsEnggServiceAvailable)
    {
        CommonAPI::CallInfo callInfo;
        callInfo.timeout_ = 60000;
        m_pEnggMenuPressCtrlProxy->extractLogsAsync(std::bind(&CEnggMenuResourceImpl::extractLogsAsyncCb, this, _1, _2), &callInfo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU,"%s: EnggService is not Available.", __FUNCTION__);
    }
}


void CEnggMenuResourceImpl::setSystemIpAddress(bool bIPType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_bIsEnggServiceAvailable:: %d", __FUNCTION__,m_bIsEnggServiceAvailable);
    if(m_bIsEnggServiceAvailable)
    {
        if(bIPType)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bIpType:Static IP set: %d", __FUNCTION__,bIPType);
            m_pEnggMenuPressCtrlProxy->setSystemIPAsync(EnggMenuTypes::ipType_enum::IP_STATIC, std::bind(&CEnggMenuResourceImpl::setSystemStaticIpAddressCb,this,_1,_2));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bIpType:Dynamic IP set: %d", __FUNCTION__,bIPType);
            m_pEnggMenuPressCtrlProxy->setSystemIPAsync(EnggMenuTypes::ipType_enum::IP_DYNAMIC, std::bind(&CEnggMenuResourceImpl::setSystemDynamicIpAddressCb,this,_1,_2));
        }
    }
}



void CEnggMenuResourceImpl::testAutomationToggleService(bool bIsTestAutomationEnable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_bIsEnggServiceAvailable:: %d", __FUNCTION__,m_bIsEnggServiceAvailable);
    if(m_bIsEnggServiceAvailable)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_bIsEnggServiceAvailable:: AVAILABLE", __FUNCTION__);
        if(bIsTestAutomationEnable)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_bIsEnggServiceAvailable: %d ,bIsTestAutomationEnable: ENABLE %d", __FUNCTION__,m_bIsEnggServiceAvailable,bIsTestAutomationEnable);
            m_pEnggMenuPressCtrlProxy->testAutomationLaunchAsync(bIsTestAutomationEnable,std::bind(&CEnggMenuResourceImpl::testAutomationStartServiceCb,this,_1,_2));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_bIsEnggServiceAvailable: %d ,bIsTestAutomationEnable: DISABLE %d", __FUNCTION__,m_bIsEnggServiceAvailable,bIsTestAutomationEnable);
            m_pEnggMenuPressCtrlProxy->testAutomationLaunchAsync(bIsTestAutomationEnable,std::bind(&CEnggMenuResourceImpl::testAutomationStopServiceCb,this,_1,_2));
        }
    }
}

void CEnggMenuResourceImpl::startFactoryReset()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_bIsEnggServiceAvailable: %d ", __FUNCTION__,m_bIsEnggServiceAvailable);
    if(m_bIsEnggServiceAvailable)
    {
        m_pEnggMenuPressCtrlProxy->performFactoryResetAsync(std::bind(&CEnggMenuResourceImpl::factoryResetCb,this,_1,_2));
    }
}

void CEnggMenuResourceImpl::setDeviceMode(bool bDeviceMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_bIsEnggServiceAvailable: %d", __FUNCTION__, m_bIsEnggServiceAvailable);
    if(m_bIsEnggServiceAvailable)
    {
        if(bDeviceMode)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_bIsEnggServiceAvailable: %d ,MODE: DEVICE_MODE %d", __FUNCTION__, m_bIsEnggServiceAvailable, bDeviceMode);
            m_pEnggMenuPressCtrlProxy->setDeviceModeAsync(EnggMenuTypes::modeType::DEVICE_MODE, std::bind(&CEnggMenuResourceImpl::setDeviceModeCb ,this, _1, _2, _3));

        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_bIsEnggServiceAvailable: %d ,MODE: HOST_MODE %d", __FUNCTION__, m_bIsEnggServiceAvailable, bDeviceMode);
            m_pEnggMenuPressCtrlProxy->setDeviceModeAsync(EnggMenuTypes::modeType::HOST_MODE, std::bind(&CEnggMenuResourceImpl::setDeviceModeCb, this, _1, _2, _3));
        }
    }
}

void CEnggMenuResourceImpl::updateEnggProxyAvailabilityToHMI(bool bIsEnggMenuProxyAvailable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bIsEnggMenuProxyAvailable: %d", __FUNCTION__, bIsEnggMenuProxyAvailable);

    if(m_pEnggMenuEventProvider)
    {
        m_pEnggMenuEventProvider->updateEnggProxyAvailabilityToHMI(bIsEnggMenuProxyAvailable);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: EnggMenuEventProvider is null", __FUNCTION__);
    }
}


void CEnggMenuResourceImpl::extractLogsAsyncCb(const CallStatus &eCallStatus, const EnggMenuTypes::extractLogsError_enum &eExtractLogsProcessStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: CallStatus: %d, ExtractLogsProcessStatus: %d", __FUNCTION__, static_cast<int>(eCallStatus), static_cast<int>(eExtractLogsProcessStatus));
    if(m_pEnggMenuEventProvider)
    {
        m_pEnggMenuEventProvider->updateExtractLogsStatus(static_cast<int>(eExtractLogsProcessStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU,"%s EnggMenuEventProvider is null", __FUNCTION__);
    }
}

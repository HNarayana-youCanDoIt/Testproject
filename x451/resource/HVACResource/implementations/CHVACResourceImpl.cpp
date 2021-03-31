/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHVACResourceImpl.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CHVACResourceImpl, Resource Implementation for the HVAC module. Implements the IHVACResource interface
*/

#include "CHVACResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"

CHVACResourceImpl::CHVACResourceImpl():
    m_pHVACEventProvider(new CHVACEventProvider())
  , m_ccmHuProxy(ResourceDeploymentConfig::getConfig().m_CcmHu_Proxy.domain,ResourceDeploymentConfig::getConfig().m_CcmHu_Proxy.instance)
  , m_bCcmHuAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);
    SUBSCRIBE(m_ccmHuProxy,getProxyStatusEvent(),&CHVACResourceImpl::ccmHuStatusEventCb,_1);
    subscribeToCcmHuProxy();
}

void CHVACResourceImpl::subscribeToCcmHuProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);
    SUBSCRIBE(m_ccmHuProxy, getCcmHuAttribute().getChangedEvent(), &CHVACResourceImpl::asyncCcmHuParameterCb, _1)
    SUBSCRIBE(m_ccmHuProxy, getCcmHuUserInterventionFlagAttribute().getChangedEvent(), &CHVACResourceImpl::ccmHuUserInterventionFlagAttributeCb, _1);
}

CHVACResourceImpl::~CHVACResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);

    if (m_pHVACEventProvider)
        delete m_pHVACEventProvider;
}

CHVACEventProvider* CHVACResourceImpl::getHVACEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);
    return m_pHVACEventProvider;
}

void CHVACResourceImpl::ccmHuStatusEventCb(AvailabilityStatus status)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);

    if(status == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        m_bCcmHuAvailable = true;
        getCcmInfo();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, ccmHu service NOT AVAILABLE",__FUNCTION__);
        m_bCcmHuAvailable = false;
    }
}

void CHVACResourceImpl::huCcm_req(CcmPresTypes::eHuCcmParam eCcmHuParam, const uint16_t uiValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, param: %d, value: %d",__FUNCTION__,static_cast<int>(eCcmHuParam),uiValue);

    if(m_bCcmHuAvailable)
    {
        m_ccmHuProxy->huCcm_reqAsync(eCcmHuParam, uiValue, std::bind(&CHVACResourceImpl::asyncCcmHuReqCb,this, _1));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, ccmHu service NOT AVAILABLE",__FUNCTION__);
    }
}
void CHVACResourceImpl::getCcmInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s",__FUNCTION__);

    if(m_bCcmHuAvailable)
    {
        m_ccmHuProxy->getCcmInfoAsync(std::bind(&CHVACResourceImpl::asyncGetCcmInfoCb,this, _1, _2));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, ccmHu service NOT AVAILABLE",__FUNCTION__);
    }
}

void CHVACResourceImpl::asyncGetCcmInfoCb(const CommonAPI::CallStatus& status, const CcmPresTypes::CcmInfo& CcmDetails )
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: call status is: %d, bCcmAirconCtrl is: %d, bCcmAutoMode is: %d, iCcmDistribMode is: %d, bCcmDualMode is: %d, bCcmEconMode is: %d, bCcmErrStatus is: %d, iCcmFanSpeed is: %d, iCcmFreshairRecirc is: %d, iCcmHifanspdConfig is: %d, iCcmHitempConfig is: %d, bCcmHVACCtrl is: %d, iCcmLowfanspdConfig is: %d, iCcmLowtempConfig is: %d, bCcmMaxDefrst is: %d, bCccmRearDefog is: %d, iCcmTempChange is: %d, iCcmPresence is: %d, iCcmEconConfig: %d, iCcmExpCoolConfig: %d, bCcmExpCoolStatus: %d, iCcmPassengerTemprature: %d, iCcmDriverTemprature: %d, iVariantType: %d",
             __FUNCTION__, static_cast<int>(status), CcmDetails.getCcmAirconCtrl(), CcmDetails.getCcmAutoMode(), CcmDetails.getCcmDistribMode(),
             CcmDetails.getCcmDualMode(), CcmDetails.getCcmEconMode(), CcmDetails.getCcmErrStatus(), CcmDetails.getCcmFanSpeed(),
             CcmDetails.getCcmFreshairRecirc(), CcmDetails.getCcmHifanspdConfig(), CcmDetails.getCcmHitempConfig(),
             CcmDetails.getCcmHVACCtrl(), CcmDetails.getCcmLowfanspdConfig(), CcmDetails.getCcmLowtempConfig(), CcmDetails.getCcmMaxDefrst(),
             CcmDetails.getCcmRearDefog(), CcmDetails.getCcmTempChange(), CcmDetails.getCcmPresence(), static_cast<int>(CcmDetails.getCcmEconConfig()),
             static_cast<int>(CcmDetails.getCcmExpCoolConfig()), CcmDetails.getCcmExpCoolSts(), static_cast<int>(CcmDetails.getCcmTemPass()),
             static_cast<int>(CcmDetails.getCcmTempDrvr()), static_cast<int>(CcmDetails.getCcmVariantType()));

    if(CommonAPI::CallStatus::SUCCESS == status)
    {

        // Call event provider to propogate the structure to the upper layer
        if(m_pHVACEventProvider)
        {
            m_objSHVACParamValues.bCcmAirconCtrl= CcmDetails.getCcmAirconCtrl();
            m_objSHVACParamValues.bCcmAutoMode = CcmDetails.getCcmAutoMode();
            m_objSHVACParamValues.iCcmDistribMode = static_cast<int>(CcmDetails.getCcmDistribMode());
            m_objSHVACParamValues.bCcmDualMode = CcmDetails.getCcmDualMode();
            m_objSHVACParamValues.bCcmEconMode = CcmDetails.getCcmEconMode();
            m_objSHVACParamValues.bCcmErrStatus = CcmDetails.getCcmErrStatus();
            m_objSHVACParamValues.iCcmFanSpeed = static_cast<int>(CcmDetails.getCcmFanSpeed());
            m_objSHVACParamValues.iCcmFreshairRecirc = static_cast<int>(CcmDetails.getCcmFreshairRecirc());
            m_objSHVACParamValues.iCcmHifanspdConfig = static_cast<int>(CcmDetails.getCcmHifanspdConfig());
            m_objSHVACParamValues.iCcmHitempConfig = static_cast<int>(CcmDetails.getCcmHitempConfig());
            m_objSHVACParamValues.bCcmHVACCtrl= CcmDetails.getCcmHVACCtrl();
            m_objSHVACParamValues.iCcmLowfanspdConfig = static_cast<int>(CcmDetails.getCcmLowfanspdConfig());
            m_objSHVACParamValues.iCcmLowtempConfig = static_cast<int>(CcmDetails.getCcmLowtempConfig());
            m_objSHVACParamValues.bCcmMaxDefrst = CcmDetails.getCcmMaxDefrst();
            m_objSHVACParamValues.bCccmRearDefog = CcmDetails.getCcmRearDefog();
            m_objSHVACParamValues.iCcmTempChange = static_cast<int>(CcmDetails.getCcmTempChange());
            m_objSHVACParamValues.iCcmPresence = static_cast<int>(CcmDetails.getCcmPresence());
            m_objSHVACParamValues.iCcmEconConfig = static_cast<int>(CcmDetails.getCcmEconConfig());
            m_objSHVACParamValues.iCcmExpCoolConfig = static_cast<int>(CcmDetails.getCcmExpCoolConfig());
            m_objSHVACParamValues.bCcmExpCoolStatus = CcmDetails.getCcmExpCoolSts();
            m_objSHVACParamValues.iCcmPassengerTemprature = static_cast<int>(CcmDetails.getCcmTemPass());
            m_objSHVACParamValues.iCcmDriverTemprature = static_cast<int>(CcmDetails.getCcmTempDrvr());
            m_objSHVACParamValues.iVariantType = static_cast<int>(CcmDetails.getCcmVariantType());
            m_pHVACEventProvider->HVACInfoReceived();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"HVAC event provider is NULL");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"HVAC asyncGetCcmInfoCb callback is not successful");
    }
}

void CHVACResourceImpl::ccmHuUserInterventionFlagAttributeCb(uint8_t ucHuCcmParam)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, HU CCM param is: %d", __FUNCTION__, ucHuCcmParam);
    if(m_pHVACEventProvider)
    {
        m_pHVACEventProvider->ccmUserInterventionParamChanged(ucHuCcmParam);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"HVAC event provider is NULL");
    }
}

void CHVACResourceImpl::asyncCcmHuReqCb(const CommonAPI::CallStatus& callStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, call status: %d",__FUNCTION__, static_cast<int>(callStatus));
}

void CHVACResourceImpl::asyncCcmHuParameterCb(const CcmPresTypes::tCcmHu ccmHuAttributeStruct)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, param: %d, value: %d",__FUNCTION__,static_cast<int>(ccmHuAttributeStruct.getCcmHu_enum()),static_cast<int>(ccmHuAttributeStruct.getCcmHu_value()));
    // Call event provider to propogate the enum and value to the upper layer
    if(m_pHVACEventProvider)
    {
        m_pHVACEventProvider->HVACParamUpdate(ccmHuAttributeStruct.getCcmHu_enum(),ccmHuAttributeStruct.getCcmHu_value());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"HVAC event provider is NULL");
    }
}

SHVACParamValues CHVACResourceImpl::fetchHVACInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SYSTEM, __FUNCTION__);
    return m_objSHVACParamValues;
}

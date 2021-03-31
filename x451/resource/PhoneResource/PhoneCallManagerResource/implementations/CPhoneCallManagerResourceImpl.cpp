/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneCallManagerResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CPhoneCallManagerResourceImpl class
 */

#include "CPhoneCallManagerResourceImpl.h"
#include <ResourceDeploymentConfig.h>
#include <ResourceMaster.h>
#include "logging.h"

CPhoneCallManagerResourceImpl::CPhoneCallManagerResourceImpl()
    : m_pPhoneCallMgrEventProvider(new CPhoneCallManagerEventProvider()),
      m_objCallManagerProxy(ResourceDeploymentConfig::getConfig().m_PhoneCallManager_Proxy.domain,
                            ResourceDeploymentConfig::getConfig().m_PhoneCallManager_Proxy.instance),
      m_bIsCallManagerProxyAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectCallDurationList.clear();
    m_vectHfModeStatusList.clear();
    m_vectSignalChargeInfoList.clear();
    m_vectNetworkOperatorInfoList.clear();
    m_vectHfpSupportedFeatureInfoList.clear();
    m_vectCallStateInfoList.clear();
    m_vectPhoneBTVrModeStatusList.clear();
    subscribeCallManagerCb();
}

CPhoneCallManagerResourceImpl::~CPhoneCallManagerResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if (m_pPhoneCallMgrEventProvider)
    {
        delete m_pPhoneCallMgrEventProvider;
        m_pPhoneCallMgrEventProvider = NULL;
    }
}

CPhoneCallManagerEventProvider* CPhoneCallManagerResourceImpl::getPhoneCallManagerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_pPhoneCallMgrEventProvider;
}

/******************************************************//**
 * @category REQUEST METHODS
 *******************************************************/
void CPhoneCallManagerResourceImpl::acceptIncomingCallAsyncReq(const string& strBtAddr, bool bAcceptInHandsetMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->acceptIncomingCallAsync(strBtAddr, bAcceptInHandsetMode,
                                                       std::bind(&CPhoneCallManagerResourceImpl::acceptIncomingCallAsyncCb,
                                                                 this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::rejectIncomingCallAsyncReq(const string& strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->rejectIncomingCallAsync(strBtAddr,
                                                       std::bind(&CPhoneCallManagerResourceImpl::rejectIncomingCallAsyncCb,
                                                                 this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::dialAsyncReq(const string& strBtAddr, const string& strNumber, const string& strContactName,
                                                 const string& strImageUrl, EContactNumTeleType eTelphoneType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->dialAsync(strBtAddr, strNumber, strContactName, strImageUrl, getContactTelephoneType(eTelphoneType),
                                         std::bind(&CPhoneCallManagerResourceImpl::dialAsyncCb,
                                                   this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::conferenceCallAsyncReq(const string& strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->conferenceCallAsync(strBtAddr,
                                                   std::bind(&CPhoneCallManagerResourceImpl::conferenceCallAsyncCb,
                                                             this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::swapCallsAsyncReq(const string& strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->swapCallsAsync(strBtAddr,
                                              std::bind(&CPhoneCallManagerResourceImpl::swapCallsAsyncCb,
                                                        this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::resumeHeldCallAsyncReq(const string& strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->resumeHeldCallAsync(strBtAddr,
                                                   std::bind(&CPhoneCallManagerResourceImpl::resumeHeldCallAsyncCb,
                                                             this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::holdActiveCallAsyncReq(const string& strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->holdActiveCallAsync(strBtAddr,
                                                   std::bind(&CPhoneCallManagerResourceImpl::holdActiveCallAsyncCb,
                                                             this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::endCallAsyncReq(const string& strBtAddr, int iCallId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->endCallAsync(strBtAddr, iCallId,
                                            std::bind(&CPhoneCallManagerResourceImpl::endCallAsyncCb,
                                                      this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::endActiveCallAsyncReq(const string& strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->endActiveCallAsync(strBtAddr,
                                                  std::bind(&CPhoneCallManagerResourceImpl::endActiveCallAsyncCb,
                                                            this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::endAllCallsAsyncReq(const string& strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->endAllCallsAsync(strBtAddr,
                                                std::bind(&CPhoneCallManagerResourceImpl::endAllCallsAsyncCb,
                                                          this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::sendDtmfToneAsyncReq(const string& strBtAddr, const string& strDtmfTone)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->sendDtmfToneAsync(strBtAddr, strDtmfTone,
                                                 std::bind(&CPhoneCallManagerResourceImpl::sendDtmfToneAsyncCb,
                                                           this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::setHfModeAsyncReq(const string& strBtAddr, bool bHfMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->setHfModeAsync(strBtAddr, bHfMode,
                                              std::bind(&CPhoneCallManagerResourceImpl::setHfModeAsyncCb,
                                                        this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::setPhoneBtVrModeAsyncReq(const string &strBtAddr, bool bPhoneBtVrMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: strBtAddr: %s, bPhoneBtVrMode: %d", __FUNCTION__, strBtAddr.c_str(), bPhoneBtVrMode);
    if(m_bIsCallManagerProxyAvailable)
    {
        m_objCallManagerProxy->setVRModeAsync(strBtAddr, bPhoneBtVrMode,
                                              std::bind(&CPhoneCallManagerResourceImpl::setVrModeAsyncCb,
                                                        this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
    }
}


/******************************************************//**
 * @category CALLBACK METHODS
 *******************************************************/
void CPhoneCallManagerResourceImpl::callManagerStatusCb(CommonAPI::AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(eStatus == CommonAPI::AvailabilityStatus::AVAILABLE)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy available", __FUNCTION__);
        m_bIsCallManagerProxyAvailable = true;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager proxy not available", __FUNCTION__);
        m_bIsCallManagerProxyAvailable = false;
    }
}

void CPhoneCallManagerResourceImpl::callStateInfoCb(BTPresTypes::callstateInfoList vectCallStateInfoList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectCallStateInfoList.clear();
    unsigned int uiSize = static_cast<unsigned int>(vectCallStateInfoList.size());
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: call state info list size: %d", __FUNCTION__, uiSize);
    for(unsigned int uiIndex = 0; uiIndex < uiSize; uiIndex++)
    {
        if(m_vectCallStateInfoList.empty())
        {
            SCallStateInfoList objCallStateInfoList;
            objCallStateInfoList.m_strDeviceBtAddr = vectCallStateInfoList.at(uiIndex).getDeviceAddress();
            addCallStateInfo(objCallStateInfoList, vectCallStateInfoList.at(uiIndex));
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: deviceBtAddress: %s", __FUNCTION__,
                     vectCallStateInfoList.at(uiIndex).getDeviceAddress().c_str());
            m_vectCallStateInfoList.push_back(objCallStateInfoList);
        }
        else
        {
            unsigned int uiCallStateListSize = static_cast<unsigned int>(m_vectCallStateInfoList.size());
            bool bCallStateInfoAdded = false;
            for(unsigned int uiCallStateListIndex = 0; uiCallStateListIndex < uiCallStateListSize; uiCallStateListIndex++)
            {
                if(vectCallStateInfoList.at(uiIndex).getDeviceAddress().compare(m_vectCallStateInfoList.at(uiCallStateListIndex).m_strDeviceBtAddr) == 0)
                {
                    addCallStateInfo(m_vectCallStateInfoList[uiCallStateListIndex], vectCallStateInfoList.at(uiIndex));
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: deviceBtAddress: %s", __FUNCTION__,
                             vectCallStateInfoList.at(uiIndex).getDeviceAddress().c_str());
                    bCallStateInfoAdded = true;
                    break;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call state bt address not found in call state info list", __FUNCTION__);
                }
            }
            if(!bCallStateInfoAdded)
            {
                SCallStateInfoList objCallStateInfoList;
                objCallStateInfoList.m_strDeviceBtAddr      = vectCallStateInfoList.at(uiIndex).getDeviceAddress();
                addCallStateInfo(objCallStateInfoList, vectCallStateInfoList.at(uiIndex));
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: deviceBtAddress: %s", __FUNCTION__,
                         vectCallStateInfoList.at(uiIndex).getDeviceAddress().c_str());
                m_vectCallStateInfoList.push_back(objCallStateInfoList);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call state info already added in call state info list", __FUNCTION__);
            }
        }
    }


    generateHMICallState();

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: update call state info to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->callStateInfoReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::hfFeaturesListCb(BTPresTypes::hfpSupportedFeaturesList vectHFPSupportedFeatureList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectHfpSupportedFeatureInfoList.clear();
    unsigned int uiSize = static_cast<unsigned int>(vectHFPSupportedFeatureList.size());
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: hfp supported feature list size: %d", __FUNCTION__, uiSize);
    for(unsigned int uiIndex = 0; uiIndex < uiSize; uiIndex++)
    {
        SHfpSupportedFeatures objHfpSupportedFeature;
        objHfpSupportedFeature.m_strDeviceBtAddr = vectHFPSupportedFeatureList.at(uiIndex).getDeviceAddress();
        for (auto& hfpSupportedFeatureMap: vectHFPSupportedFeatureList.at(uiIndex).getHfpFeatures())
        {
            objHfpSupportedFeature.m_mapSupportedFeatures.insert({getPhoneSupportedFeature(hfpSupportedFeatureMap.first.value_), hfpSupportedFeatureMap.second});
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: hfpFeature: %d, isSupported: %d", __FUNCTION__,
                     hfpSupportedFeatureMap.first.value_, hfpSupportedFeatureMap.second);
        }

        m_vectHfpSupportedFeatureInfoList.push_back(objHfpSupportedFeature);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: deviceBtAddress: %s", __FUNCTION__,
                 vectHFPSupportedFeatureList.at(uiIndex).getDeviceAddress().c_str());
    }

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: update hf feature list info to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->hfFeaturesListReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::operatorInfoListCb(BTPresTypes::networkOperatorInfoList vectNetworkOperatorInfoList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectNetworkOperatorInfoList.clear();
    unsigned int uiSize = static_cast<unsigned int>(vectNetworkOperatorInfoList.size());
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: network operator info list size: %d", __FUNCTION__, uiSize);
    for(unsigned int uiIndex = 0; uiIndex < uiSize; uiIndex++)
    {
        SNetworkOperatorInfo objNewtorkOperatorInfo;
        objNewtorkOperatorInfo.m_ePhoneNetworkRegState   = getPhoneNetworkRegState(vectNetworkOperatorInfoList.at(uiIndex).getNetworkRegistrationState().value_);
        objNewtorkOperatorInfo.m_bNetworkAvailability    = vectNetworkOperatorInfoList.at(uiIndex).getNetworkAvailability();
        objNewtorkOperatorInfo.m_strDeviceBtAddr         = vectNetworkOperatorInfoList.at(uiIndex).getDeviceAddress();
        objNewtorkOperatorInfo.m_strSubscriberNumber     = vectNetworkOperatorInfoList.at(uiIndex).getSubscriberNumber();
        objNewtorkOperatorInfo.m_strOperatorName         = vectNetworkOperatorInfoList.at(uiIndex).getOperatorName();
        objNewtorkOperatorInfo.m_ePhoneOperatorMode      = getPhoneOperatorMode(vectNetworkOperatorInfoList.at(uiIndex).getOperatorMode().value_);
        m_vectNetworkOperatorInfoList.push_back(objNewtorkOperatorInfo);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: phoneNetworkRegistryState: %d, networkAvailable: %d, deviceBtAddress: %s, subscriberNumber: %s, operatorName: %s, phoneOperatorMode: %d",
                 __FUNCTION__, vectNetworkOperatorInfoList.at(uiIndex).getNetworkRegistrationState().value_, vectNetworkOperatorInfoList.at(uiIndex).getNetworkAvailability(),
                 vectNetworkOperatorInfoList.at(uiIndex).getDeviceAddress().c_str(), vectNetworkOperatorInfoList.at(uiIndex).getSubscriberNumber().c_str(),
                 vectNetworkOperatorInfoList.at(uiIndex).getOperatorName().c_str(), vectNetworkOperatorInfoList.at(uiIndex).getOperatorMode().value_);
    }

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: update operator info list info to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->operatorInfoListReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::rssiChargeInfoListCb(BTPresTypes::signalChargeInfoList vectSignalChargeInfoList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectSignalChargeInfoList.clear();
    unsigned int uiSize = static_cast<unsigned int>(vectSignalChargeInfoList.size());
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: signal charge info list size: %d", __FUNCTION__, uiSize);
    for(unsigned int uiIndex = 0; uiIndex < uiSize; uiIndex++)
    {
        SSignalChargeInfo objSignalChargeInfo;
        objSignalChargeInfo.m_strDeviceBtAddr       = vectSignalChargeInfoList.at(uiIndex).getDeviceAddress();
        objSignalChargeInfo.m_eSignalLevel          = getSignalLevel(vectSignalChargeInfoList.at(uiIndex).getSignalQuality().value_);
        objSignalChargeInfo.m_eBatteryChargeLevel   = getBatteryChargeLevel(vectSignalChargeInfoList.at(uiIndex).getBatteryCharge().value_);
        m_vectSignalChargeInfoList.push_back(objSignalChargeInfo);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: deviceBtAddress: %s, signalLevel: %d, batteryChargeLevel: %d", __FUNCTION__,
                 vectSignalChargeInfoList.at(uiIndex).getDeviceAddress().c_str(), vectSignalChargeInfoList.at(uiIndex).getSignalQuality().value_,
                 vectSignalChargeInfoList.at(uiIndex).getBatteryCharge().value_);
    }

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: update rssi charge info list info to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->rssiChargeInfoListReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::hfModeCb(BTPresTypes::hfModeStatusList vectHFModeStatusList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectHfModeStatusList.clear();
    unsigned int uiSize = static_cast<unsigned int>(vectHFModeStatusList.size());
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: hf mode status info list size: %d", __FUNCTION__, uiSize);
    for(unsigned int uiIndex = 0; uiIndex < uiSize; uiIndex++)
    {
        SHfModeStatus objHfModeStatus;
        objHfModeStatus.m_strDeviceBtAddr   = vectHFModeStatusList.at(uiIndex).getDeviceAddress();
        objHfModeStatus.m_eCallAudioStatus  = getCallAudioStatus(vectHFModeStatusList.at(uiIndex).getStatus().value_);
        m_vectHfModeStatusList.push_back(objHfModeStatus);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: deviceBtAddress: %s, callAudioStatus: %d", __FUNCTION__,
                 vectHFModeStatusList.at(uiIndex).getDeviceAddress().c_str(), vectHFModeStatusList.at(uiIndex).getStatus().value_);
    }

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: update hf mode status info to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->hfModeStatusReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::callDurationCb(BTPresTypes::callDurationList vectCallDurationList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectCallDurationList.clear();
    unsigned int uiSize = static_cast<unsigned int>(vectCallDurationList.size());
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: call duration list size: %d", __FUNCTION__, uiSize);
    for(unsigned int uiIndex = 0; uiIndex < uiSize; uiIndex++)
    {
        SCallDuration objCallDuration;
        objCallDuration.m_strDeviceBtAddr   = vectCallDurationList.at(uiIndex).getDeviceAddress();
        objCallDuration.m_iCallId           = vectCallDurationList.at(uiIndex).getCallId();
        objCallDuration.m_uiCallDuration    = vectCallDurationList.at(uiIndex).getDuration();
        m_vectCallDurationList.push_back(objCallDuration);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: deviceBtAddress: %s, callId: %d, callDuration: %d", __FUNCTION__,
                 vectCallDurationList.at(uiIndex).getDeviceAddress().c_str(), vectCallDurationList.at(uiIndex).getCallId(),
                 vectCallDurationList.at(uiIndex).getDuration());
    }

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: update call duration info to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->callDurationReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::phoneVRModeCb(BTPresTypes::vrModeStatusList vectPhoneBtVrModeStatusList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectPhoneBTVrModeStatusList.clear();
    unsigned int uiSize = static_cast<unsigned int>(vectPhoneBtVrModeStatusList.size());
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone bt vr mode status list size: %d", __FUNCTION__, uiSize);
    for(unsigned int uiIndex = 0; uiIndex < uiSize; uiIndex++)
    {
        SPhoneBTVrModeStatus objPhoneBtVrModeStatus;
        objPhoneBtVrModeStatus.m_strDeviceBtAddr        = vectPhoneBtVrModeStatusList.at(uiIndex).getDeviceAddress();
        objPhoneBtVrModeStatus.m_bPhoneBtVrModeStatus   = vectPhoneBtVrModeStatusList.at(uiIndex).getStatus();
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: deviceBtAddress: %s, phoneBtVrModeStatus: %d", __FUNCTION__,
                 vectPhoneBtVrModeStatusList.at(uiIndex).getDeviceAddress().c_str(), vectPhoneBtVrModeStatusList.at(uiIndex).getStatus());
        m_vectPhoneBTVrModeStatusList.push_back(objPhoneBtVrModeStatus);
    }

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: update phone bt vr mode status to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->phoneBtVrModeStatusReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}


/********************************************//**
 * @category RESPONSE CALLBACK METHODS
 ************************************************/
void CPhoneCallManagerResourceImpl::acceptIncomingCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify acceptIncomingCallAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->acceptIncomingCallAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                              getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::rejectIncomingCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify rejectIncomingCallAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->rejectIncomingCallAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                              getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::dialAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify dialAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->dialAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::conferenceCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify conferenceCallAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->conferenceCallAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                          getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::swapCallsAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify swapCallsAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->swapCallsAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                     getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::resumeHeldCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify resumeHeldCallAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->resumeHeldCallAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                          getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::holdActiveCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify holdActiveCallAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->holdActiveCallAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                          getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::endCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify endCallAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->endCallAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                   getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::endActiveCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify endActiveCallAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->endActiveCallAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                         getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::endAllCallsAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify endAllCallsAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->endAllCallsAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                       getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::sendDtmfToneAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify sendDtmfToneAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->sendDtmfToneAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                        getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::setHfModeAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: notify setHfModeAsync method call status is received to phone application layer", __FUNCTION__);
        m_pPhoneCallMgrEventProvider->setHfModeAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                     getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

void CPhoneCallManagerResourceImpl::setVrModeAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);
    // Propagate the information to the phone application layer
    if (m_pPhoneCallMgrEventProvider)
    {
        m_pPhoneCallMgrEventProvider->setVrModeAsyncMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                     getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s: call manager data event provider object not created", __FUNCTION__);
    }
}

/******************************************************//**
 * @category INTERNAL METHODS
 *******************************************************/
void CPhoneCallManagerResourceImpl::subscribeCallManagerCb()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    SUBSCRIBE(m_objCallManagerProxy, getProxyStatusEvent(),                                 &CPhoneCallManagerResourceImpl::callManagerStatusCb,    _1);
    SUBSCRIBE(m_objCallManagerProxy, getCallStateInfoAttribute().getChangedEvent(),         &CPhoneCallManagerResourceImpl::callStateInfoCb,        _1);
    SUBSCRIBE(m_objCallManagerProxy, getHfFeaturesListAttribute().getChangedEvent(),        &CPhoneCallManagerResourceImpl::hfFeaturesListCb,       _1);
    SUBSCRIBE(m_objCallManagerProxy, getOperatorInfoListAttribute().getChangedEvent(),      &CPhoneCallManagerResourceImpl::operatorInfoListCb,     _1);
    SUBSCRIBE(m_objCallManagerProxy, getRssiChargeInfoListAttribute().getChangedEvent(),    &CPhoneCallManagerResourceImpl::rssiChargeInfoListCb,   _1);
    SUBSCRIBE(m_objCallManagerProxy, getHfModeAttribute().getChangedEvent(),                &CPhoneCallManagerResourceImpl::hfModeCb,               _1);
    SUBSCRIBE(m_objCallManagerProxy, getCallDurationAttribute().getChangedEvent(),          &CPhoneCallManagerResourceImpl::callDurationCb,         _1);
    SUBSCRIBE(m_objCallManagerProxy, getVrModeAttribute().getChangedEvent(),                &CPhoneCallManagerResourceImpl::phoneVRModeCb,          _1);
}

BTPresTypes::eTelType CPhoneCallManagerResourceImpl::getContactTelephoneType(EContactNumTeleType eContactNumTeleType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    BTPresTypes::eTelType objTelephoneType = BTPresTypes::eTelType::CONTACT_TEL_TYPE_OTHER;
    switch(eContactNumTeleType)
    {
    case CONTACT_NUM_TELEPHONE_TYPE_MOBILE:
        objTelephoneType = BTPresTypes::eTelType::CONTACT_TEL_TYPE_CELL;
        break;
    case CONTACT_NUM_TELEPHONE_TYPE_HOME:
        objTelephoneType = BTPresTypes::eTelType::CONTACT_TEL_TYPE_HOME;
        break;
    case CONTACT_NUM_TELEPHONE_TYPE_WORK:
        objTelephoneType = BTPresTypes::eTelType::CONTACT_TEL_TYPE_WORK;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for contact telephone type passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: telephone type is: %d", __FUNCTION__, objTelephoneType.value_);
    return objTelephoneType;
}

EContactNumTeleType CPhoneCallManagerResourceImpl::getContactTelephoneType(int iContactNumTeleType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    EContactNumTeleType eContactNumTeleType = CONTACT_NUM_TELEPHONE_TYPE_DEFAULT;
    switch(iContactNumTeleType)
    {
    case BTPresTypes::eTelType::CONTACT_TEL_TYPE_CELL:
        eContactNumTeleType = CONTACT_NUM_TELEPHONE_TYPE_MOBILE;
        break;
    case BTPresTypes::eTelType::CONTACT_TEL_TYPE_HOME:
        eContactNumTeleType = CONTACT_NUM_TELEPHONE_TYPE_HOME;
        break;
    case BTPresTypes::eTelType::CONTACT_TEL_TYPE_WORK:
        eContactNumTeleType = CONTACT_NUM_TELEPHONE_TYPE_WORK;
        break;
    case BTPresTypes::eTelType::CONTACT_TEL_TYPE_OTHER:
        eContactNumTeleType = CONTACT_NUM_TELEPHONE_TYPE_OTHER;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for contact number telephone type passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: contact number telephone type is: %d", __FUNCTION__, eContactNumTeleType);
    return eContactNumTeleType;
}

ECallState CPhoneCallManagerResourceImpl::getCallState(int iCallState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    ECallState eCallState = CALL_STATE_IDLE;
    switch(iCallState)
    {
    case BTPresTypes::eCallState::CALL_STATE_ACTIVE:
        eCallState = CALL_STATE_ACTIVE;
        break;
    case BTPresTypes::eCallState::CALL_STATE_ON_HOLD:
        eCallState = CALL_STATE_ON_HOLD;
        break;
    case BTPresTypes::eCallState::CALL_STATE_TERMINATED:
        eCallState = CALL_STATE_TERMINATED;
        break;
    case BTPresTypes::eCallState::CALL_STATE_DIALING:
        eCallState = CALL_STATE_DIALING;
        break;
    case BTPresTypes::eCallState::CALL_STATE_RINGING:
        eCallState = CALL_STATE_RINGING;
        break;
    case BTPresTypes::eCallState::CALL_STATE_ALERTING:
        eCallState = CALL_STATE_ALERTING;
        break;
    case BTPresTypes::eCallState::CALL_STATE_WAITING:
        eCallState = CALL_STATE_WAITING;
        break;
    case BTPresTypes::eCallState::CALL_STATE_IGNORED:
        eCallState = CALL_STATE_IGNORED;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for call state passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call state is: %d", __FUNCTION__, eCallState);
    return eCallState;
}

ECallDirection CPhoneCallManagerResourceImpl::getCallDirection(int iCallDirection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    ECallDirection eCallDirection = CALL_DIRECTION_UNKNOWN;
    switch(iCallDirection)
    {
    case BTPresTypes::eDirection::DIRECTION_INCOMING:
        eCallDirection = CALL_DIRECTION_INCOMING;
        break;
    case BTPresTypes::eDirection::DIRECTION_OUTGOING:
        eCallDirection = CALL_DIRECTION_OUTGOING;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for call direction passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call direction is: %d", __FUNCTION__, eCallDirection);
    return eCallDirection;
}

ECallAudioStatus CPhoneCallManagerResourceImpl::getCallAudioStatus(int iCallAudioStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    ECallAudioStatus eCallAudioStatus = CALL_AUDIOSTATUS_DEFAULT;
    switch(iCallAudioStatus)
    {
    case BTPresTypes::eAudioStatus::SCO_CONNECTED:
        eCallAudioStatus = CALL_AUDIOSTATUS_CONNECTED;
        break;
    case BTPresTypes::eAudioStatus::SCO_DISCONNECTED:
        eCallAudioStatus = CALL_AUDIOSTATUS_DISCONNECTED;
        break;
    case BTPresTypes::eAudioStatus::SCO_ERROR:
        eCallAudioStatus = CALL_AUDIOSTATUS_ERROR;
        break;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for call audio status passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call audio status is: %d", __FUNCTION__, eCallAudioStatus);
    return eCallAudioStatus;
}

ESignalLevel CPhoneCallManagerResourceImpl::getSignalLevel(int iSignalLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    ESignalLevel eSignalLevel = SIGNAL_LEVEL_INVALID;
    switch(iSignalLevel)
    {
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_0_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_0_PERCENT;
        break;
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_10_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_10_PERCENT;
        break;
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_20_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_20_PERCENT;
        break;
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_30_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_30_PERCENT;
        break;
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_40_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_40_PERCENT;
        break;
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_50_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_50_PERCENT;
        break;
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_60_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_60_PERCENT;
        break;
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_70_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_70_PERCENT;
        break;
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_80_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_80_PERCENT;
        break;
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_90_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_90_PERCENT;
        break;
    case BTPresTypes::eRssiLevel::RSSI_LEVEL_100_PERCENT:
        eSignalLevel = SIGNAL_LEVEL_100_PERCENT;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for signal level passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: signal level is: %d", __FUNCTION__, eSignalLevel);
    return eSignalLevel;
}

EBatteryChargeLevel CPhoneCallManagerResourceImpl::getBatteryChargeLevel(int iBatteryChargeLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    EBatteryChargeLevel eBatteryChargeLevel = BATTERY_CHARGE_LEVEL_INVALID;
    switch(iBatteryChargeLevel)
    {
    case BTPresTypes::eBatteryChargeLevel::BATTERY_CHARGE_0_PERCENT:
        eBatteryChargeLevel = BATTERY_CHARGE_LEVEL_0_PERCENT;
        break;
    case BTPresTypes::eBatteryChargeLevel::BATTERY_CHARGE_20_PERCENT:
        eBatteryChargeLevel = BATTERY_CHARGE_LEVEL_20_PERCENT;
        break;
    case BTPresTypes::eBatteryChargeLevel::BATTERY_CHARGE_40_PERCENT:
        eBatteryChargeLevel = BATTERY_CHARGE_LEVEL_40_PERCENT;
        break;
    case BTPresTypes::eBatteryChargeLevel::BATTERY_CHARGE_60_PERCENT:
        eBatteryChargeLevel = BATTERY_CHARGE_LEVEL_60_PERCENT;
        break;
    case BTPresTypes::eBatteryChargeLevel::BATTERY_CHARGE_80_PERCENT:
        eBatteryChargeLevel = BATTERY_CHARGE_LEVEL_80_PERCENT;
        break;
    case BTPresTypes::eBatteryChargeLevel::BATTERY_CHARGE_100_PERCENT:
        eBatteryChargeLevel = BATTERY_CHARGE_LEVEL_100_PERCENT;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for battery charge level passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: battery charge level is: %d", __FUNCTION__, eBatteryChargeLevel);
    return eBatteryChargeLevel;
}

EPhoneNetworkRegState CPhoneCallManagerResourceImpl::getPhoneNetworkRegState(int iPhoneNetworkRegState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    EPhoneNetworkRegState ePhoneNetworkRegState = PHONE_NETWORK_REGSTATE_UNKNOWN;
    switch(iPhoneNetworkRegState)
    {
    case BTPresTypes::eNetworkRegState::PHONE_REGSTATE_NOT_REGISTERED:
        ePhoneNetworkRegState = PHONE_NETWORK_REGSTATE_NOT_REGISTERED;
        break;
    case BTPresTypes::eNetworkRegState::PHONE_REGSTATE_HOME:
        ePhoneNetworkRegState = PHONE_NETWORK_REGSTATE_HOME;
        break;
    case BTPresTypes::eNetworkRegState::PHONE_REGSTATE_SEARCHING:
        ePhoneNetworkRegState = PHONE_NETWORK_REGSTATE_SEARCHING;
        break;
    case BTPresTypes::eNetworkRegState::PHONE_REGSTATE_DENIED:
        ePhoneNetworkRegState = PHONE_NETWORK_REGSTATE_DENIED;
        break;
    case BTPresTypes::eNetworkRegState::PHONE_REGSTATE_ROAMING:
        ePhoneNetworkRegState = PHONE_NETWORK_REGSTATE_ROAMING;
        break;
    case BTPresTypes::eNetworkRegState::PHONE_REGSTATE_OPERATOR_DENIED:
        ePhoneNetworkRegState = PHONE_NETWORK_REGSTATE_OPERATOR_DENIED;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for phone network registry state passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone network registry state is: %d", __FUNCTION__, ePhoneNetworkRegState);
    return ePhoneNetworkRegState;
}

EPhoneOperatorMode CPhoneCallManagerResourceImpl::getPhoneOperatorMode(int iPhoneOperatorMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    EPhoneOperatorMode ePhoneOperatorMode = PHONE_OPERATOR_MODE_UNKNOWN;
    switch(iPhoneOperatorMode)
    {
    case BTPresTypes::eOperatorMode::OPERATOR_MODE_AUTO:
        ePhoneOperatorMode = PHONE_OPERATOR_MODE_AUTO;
        break;
    case BTPresTypes::eOperatorMode::OPERATOR_MODE_MANUAL:
        ePhoneOperatorMode = PHONE_OPERATOR_MODE_MANUAL;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for phone operator mode passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone operator mode is: %d", __FUNCTION__, ePhoneOperatorMode);
    return ePhoneOperatorMode;
}

EPhoneSupportedFeatures CPhoneCallManagerResourceImpl::getPhoneSupportedFeature(int iPhoneSupportedFeature)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    EPhoneSupportedFeatures ePhoneSupportedFeature = PHONE_FEATURE_NONE;
    switch(iPhoneSupportedFeature)
    {
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_REJECT:
        ePhoneSupportedFeature = PHONE_FEATURE_REJECT;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_REPLACE:
        ePhoneSupportedFeature = PHONE_FEATURE_REPLACE;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_SWAP:
        ePhoneSupportedFeature = PHONE_FEATURE_SWAP;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_HANGUP_ENH:
        ePhoneSupportedFeature = PHONE_FEATURE_HANGUP_ENH;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_SELECT:
        ePhoneSupportedFeature = PHONE_FEATURE_SELECT;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_CONFERENCE:
        ePhoneSupportedFeature = PHONE_FEATURE_CONFERENCE;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_CALLTRANSFER:
        ePhoneSupportedFeature = PHONE_FEATURE_CALLTRANSFER;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_CALLSTATUS_ENH:
        ePhoneSupportedFeature = PHONE_FEATURE_CALLSTATUS_ENH;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_RESP_AND_HOLD:
        ePhoneSupportedFeature = PHONE_FEATURE_RESP_AND_HOLD;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_INBAND:
        ePhoneSupportedFeature = PHONE_FEATURE_INBAND;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_VR:
        ePhoneSupportedFeature = PHONE_FEATURE_VR;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_AUDIO_ENH:
        ePhoneSupportedFeature = PHONE_FEATURE_AUDIO_ENH;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_SIRI:
        ePhoneSupportedFeature = PHONE_FEATURE_SIRI;
        break;
    case BTPresTypes::eSupportedFeature::PHONE_FEATURE_GOOGLE_NOW:
        ePhoneSupportedFeature = PHONE_FEATURE_GOOGLE_NOW;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for phone supported feature passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: phone supported feature is: %d", __FUNCTION__, ePhoneSupportedFeature);
    return ePhoneSupportedFeature;
}

EMethodCallStatus CPhoneCallManagerResourceImpl::getMethodCallStatus(CallStatus eCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    EMethodCallStatus eMethodCallStatus = METHOD_CALL_STATUS_DEFAULT;
    switch(eCallStatus)
    {
    case CallStatus::SUCCESS:
        eMethodCallStatus = METHOD_CALL_STATUS_SUCCESS;
        break;
    case CallStatus::OUT_OF_MEMORY:
        eMethodCallStatus = METHOD_CALL_STATUS_OUT_OF_MEMORY;
        break;
    case CallStatus::NOT_AVAILABLE:
        eMethodCallStatus = METHOD_CALL_STATUS_NOT_AVAILABLE;
        break;
    case CallStatus::CONNECTION_FAILED:
        eMethodCallStatus = METHOD_CALL_STATUS_CONNECTION_FAILED;
        break;
    case CallStatus::REMOTE_ERROR:
        eMethodCallStatus = METHOD_CALL_STATUS_REMOTE_ERROR;
        break;
    case CallStatus::UNKNOWN:
        eMethodCallStatus = METHOD_CALL_STATUS_UNKNOWN;
        break;
    case CallStatus::INVALID_VALUE:
        eMethodCallStatus = METHOD_CALL_STATUS_INVALID_VALUE;
        break;
    case CallStatus::SUBSCRIPTION_REFUSED:
        eMethodCallStatus = METHOD_CALL_STATUS_SUBSCRIPTION_REFUSED;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for call status passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call status is: %d", __FUNCTION__, eMethodCallStatus);
    return eMethodCallStatus;
}

EMethodCallErrorType CPhoneCallManagerResourceImpl::getMethodCallErrorType(int iErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    EMethodCallErrorType eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_DEFAULT;
    switch(iErrorType)
    {
    case BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_SUCCESS;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_PENDING:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_PENDING;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_API_NOT_SUPPORTED:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_API_NOT_SUPPORTED;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_BAD_PARAMETER:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_BAD_PARAMETER;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_DEVICE_REMOVED:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_DEVICE_REMOVED;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_SYNC_NOT_COMPLETED:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_SYNC_NOT_COMPLETED;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_FAILURE:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_FAILURE;
        break;
    case BTPresTypes::eErrorType::ERROR_EXCEEDED_MAX_ENTRY_LIMIT:
        eMethodCallErrorType = METHOD_CALL_ERROR_EXCEEDED_MAX_ENTRY_LIMIT;
        break;
    case BTPresTypes::eErrorType::ERROR_EXCEEDED_MAX_CHARACTER_LIMIT:
        eMethodCallErrorType = METHOD_CALL_ERROR_EXCEEDED_MAX_CHARACTER_LIMIT;
        break;
    case BTPresTypes::eErrorType::ERROR_REASON_NO_NETWORK_SERVICE:
        eMethodCallErrorType = METHOD_CALL_ERROR_REASON_NO_NETWORK_SERVICE;
        break;
    case BTPresTypes::eErrorType::ERROR_REASON_NETWORK_NOT_ALLOWED:
        eMethodCallErrorType = METHOD_CALL_ERROR_REASON_NETWORK_NOT_ALLOWED;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: wrong value for method call error type passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: method call error type is: %d", __FUNCTION__, eMethodCallErrorType);
    return eMethodCallErrorType;
}

void CPhoneCallManagerResourceImpl::generateHMICallState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(!m_vectCallStateInfoList.empty())
    {
        unsigned int uiCallStateInfoListSize = static_cast<unsigned int>(m_vectCallStateInfoList.size());
        for(unsigned int uiCallStateInfoListIndex = 0; uiCallStateInfoListIndex < uiCallStateInfoListSize; uiCallStateInfoListIndex++)
        {
            unsigned int uiSize = static_cast<unsigned int>(m_vectCallStateInfoList.at(uiCallStateInfoListIndex).m_vectCallStateInfo.size());
            EHMICallState& eHMICallState = m_vectCallStateInfoList.at(uiCallStateInfoListIndex).m_eHMICallState;
            SCallStateInfoList& objCallStateInfoList = m_vectCallStateInfoList.at(uiCallStateInfoListIndex);
            if((uiSize - getCallStateCount(objCallStateInfoList, CALL_STATE_TERMINATED)) == 1)
            {
                /*
                 * If there is only one call in the call state list and the state of the call is CALL_STATE_RINGING,
                 * then consider HMI call state as HMI_CALLSTATE_INCOMING_CALL
                 */
                if(getCallStateCount(objCallStateInfoList, CALL_STATE_RINGING) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_INCOMING_CALL;
                }
                /*
                 * If there is only one call in the call state list and the state of the call is CALL_STATE_ACTIVE,
                 * then consider HMI call state as HMI_CALLSTATE_ACTIVE_CALL
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_ACTIVE) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_ACTIVE_CALL;
                }
                /*
                 * If there is only one call in the call state list and the state of the call is CALL_STATE_ON_HOLD,
                 * then consider HMI call state as HMI_CALLSTATE_HELD_CALL
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_ON_HOLD) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_HELD_CALL;
                }
                /*
                 * If there is only one call in the call state list and the state of the call is CALL_STATE_DIALING,
                 * then consider HMI call state as HMI_CALLSTATE_DIALING
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_DIALING) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_DIALING;
                }
                /*
                 * If there is only one call in the call state list and the state of the call is CALL_STATE_ALERTING,
                 * then consider HMI call state as HMI_CALLSTATE_ALERTING
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_ALERTING) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_ALERTING;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: invalid single call condition", __FUNCTION__);
                }
            }
            /*
             * If there is more than one call in the call state list which has same call state,
             * then consider it as conference call
             */
            else if(getCallStateCount(objCallStateInfoList, CALL_STATE_ACTIVE) > 1 )
            {
                /*
                 * If the call state info list size after removing the calls which has call state as CALL_STATE_TERMINATED
                 * is equal to the calls having call state as CALL_STATE_ACTIVE, then consider HMI call state
                 * as HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE
                 */
                if((uiSize - getCallStateCount(objCallStateInfoList, CALL_STATE_TERMINATED)) == getCallStateCount(objCallStateInfoList, CALL_STATE_ACTIVE))
                {
                    eHMICallState = HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE;
                }
                /*
                 * If there is more than one call in the call state list which has call state as CALL_STATE_ACTIVE
                 * and any one call which has call state as CALL_STATE_ON_HOLD, then consider it
                 * as HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_HELD_CALL
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_ON_HOLD) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_HELD_CALL;
                }
                /*
                 * If there is more than one call in the call state list which has call state as CALL_STATE_ACTIVE
                 * and any one call which has call state as CALL_STATE_WAITING, then consider it
                 * as HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_WAITING) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL;
                }
                /*
                 * If there is more than one call in the call state list which has call state as CALL_STATE_ACTIVE
                 * and any one call which has call state as CALL_STATE_DIALING, then consider it
                 * as HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_DIALING
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_DIALING) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_DIALING;
                }
                /*
                 * If there is more than one call in the call state list which has call state as CALL_STATE_ACTIVE
                 * and any one call which has call state as CALL_STATE_ALERTING, then consider it
                 * as HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_ALERTING
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_ALERTING) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_ALERTING;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: invalid conference active call condition", __FUNCTION__);
                }
            }
            /*
             * If there is more than one call in the call state list which has same call state,
             * then consider it as conference call
             */
            else if(getCallStateCount(objCallStateInfoList, CALL_STATE_ON_HOLD) > 1 )
            {
                /*
                 * If the call state info list size after removing the calls which has call state as CALL_STATE_TERMINATED
                 * is equal to the calls having call state as CALL_STATE_ON_HOLD, then consider HMI call state
                 * as HMI_CALLSTATE_CONFERENCE_ONHOLD
                 */
                if((uiSize - getCallStateCount(objCallStateInfoList, CALL_STATE_TERMINATED)) == getCallStateCount(objCallStateInfoList, CALL_STATE_ON_HOLD))
                {
                    eHMICallState = HMI_CALLSTATE_CONFERENCE_ONHOLD;
                }
                /*
                 * If there is more than one call in the call state list which has call state as CALL_STATE_ON_HOLD
                 * and any one call which has call state as CALL_STATE_ACTIVE, then consider it
                 * as HMI_CALLSTATE_ACTIVE_CALL_AND_CONFERENCE_ONHOLD
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_ACTIVE) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_ACTIVE_CALL_AND_CONFERENCE_ONHOLD;
                }
                /*
                 * If there is more than one call in the call state list which has call state as CALL_STATE_ON_HOLD
                 * and any one call which has call state as CALL_STATE_WAITING, then consider it
                 * as HMI_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_WAITING) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL;
                }
                /*
                 * If there is more than one call in the call state list which has call state as CALL_STATE_ON_HOLD
                 * and any one call which has call state as CALL_STATE_DIALING, then consider it
                 * as HMI_CALLSTATE_CONFERENCE_ONHOLD_AND_DIALING
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_DIALING) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_CONFERENCE_ONHOLD_AND_DIALING;
                }
                /*
                 * If there is more than one call in the call state list which has call state as CALL_STATE_ON_HOLD
                 * and any one call which has call state as CALL_STATE_ALERTING, then consider it
                 * as HMI_CALLSTATE_CONFERENCE_ONHOLD_AND_ALERTING
                 */
                else if(getCallStateCount(objCallStateInfoList, CALL_STATE_ALERTING) == 1)
                {
                    eHMICallState = HMI_CALLSTATE_CONFERENCE_ONHOLD_AND_ALERTING;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: invalid conference onhold call condition", __FUNCTION__);
                }
            }
            /*
             * If the call state info list size after removing the calls which has call state as CALL_STATE_TERMINATED
             * is equal to 2, then consider that there are only two calls remaining.
             */
            else if((uiSize - getCallStateCount(objCallStateInfoList, CALL_STATE_TERMINATED)) == 2)
            {
                /*
                 * If the call state info list has one call which has call state as CALL_STATE_ACTIVE
                 * and another call which has call state as CALL_STATE_WAITING, then consider it
                 * as HMI_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL
                 */
                if((getCallStateCount(objCallStateInfoList, CALL_STATE_ACTIVE) == 1) && (getCallStateCount(objCallStateInfoList, CALL_STATE_WAITING) == 1))
                {
                    eHMICallState = HMI_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL;
                }
                /*
                 * If the call state info list has one call which has call state as CALL_STATE_ON_HOLD
                 * and another call which has call state as CALL_STATE_WAITING, then consider it
                 * as HMI_CALLSTATE_HELD_CALL_AND_INCOMING_CALL
                 */
                else if((getCallStateCount(objCallStateInfoList, CALL_STATE_ON_HOLD) == 1) && (getCallStateCount(objCallStateInfoList, CALL_STATE_WAITING) == 1))
                {
                    eHMICallState = HMI_CALLSTATE_HELD_CALL_AND_INCOMING_CALL;
                }
                /*
                 * If the call state info list has one call which has call state as CALL_STATE_ACTIVE
                 * and another call which has call state as CALL_STATE_ON_HOLD, then consider it
                 * as HMI_CALLSTATE_ACTIVE_CALL_AND_HELD_CALL
                 */
                else if((getCallStateCount(objCallStateInfoList, CALL_STATE_ACTIVE) == 1) && (getCallStateCount(objCallStateInfoList, CALL_STATE_ON_HOLD) == 1))
                {
                    eHMICallState = HMI_CALLSTATE_ACTIVE_CALL_AND_HELD_CALL;
                }
                /*
                 * If the call state info list has one call which has call state as CALL_STATE_ACTIVE
                 * and another call which has call state as CALL_STATE_DIALING, then consider it
                 * as HMI_CALLSTATE_ACTIVE_CALL_AND_DIALING
                 */
                else if((getCallStateCount(objCallStateInfoList, CALL_STATE_ACTIVE) == 1) && (getCallStateCount(objCallStateInfoList, CALL_STATE_DIALING) == 1))
                {
                    eHMICallState = HMI_CALLSTATE_ACTIVE_CALL_AND_DIALING;
                }
                /*
                 * If the call state info list has one call which has call state as CALL_STATE_ACTIVE
                 * and another call which has call state as CALL_STATE_ALERTING, then consider it
                 * as HMI_CALLSTATE_ACTIVE_CALL_AND_ALERTING
                 */
                else if((getCallStateCount(objCallStateInfoList, CALL_STATE_ACTIVE) == 1) && (getCallStateCount(objCallStateInfoList, CALL_STATE_ALERTING) == 1))
                {
                    eHMICallState = HMI_CALLSTATE_ACTIVE_CALL_AND_ALERTING;
                }
                /*
                 * If the call state info list has one call which has call state as CALL_STATE_ON_HOLD
                 * and another call which has call state as CALL_STATE_DIALING, then consider it
                 * as HMI_CALLSTATE_HELD_CALL_AND_DIALING
                 */
                else if((getCallStateCount(objCallStateInfoList, CALL_STATE_ON_HOLD) == 1) && (getCallStateCount(objCallStateInfoList, CALL_STATE_DIALING) == 1))
                {
                    eHMICallState = HMI_CALLSTATE_HELD_CALL_AND_DIALING;
                }
                /*
                 * If the call state info list has one call which has call state as CALL_STATE_ON_HOLD
                 * and another call which has call state as CALL_STATE_ALERTING, then consider it
                 * as HMI_CALLSTATE_HELD_CALL_AND_ALERTING
                 */
                else if((getCallStateCount(objCallStateInfoList, CALL_STATE_ON_HOLD) == 1) && (getCallStateCount(objCallStateInfoList, CALL_STATE_ALERTING) == 1))
                {
                    eHMICallState = HMI_CALLSTATE_HELD_CALL_AND_ALERTING;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: invalid multi-party call condition", __FUNCTION__);
                }
            }
            /*
             * If the call state info list size is equal to the calls having call state as CALL_STATE_TERMINATED,
             * then consider HMI call state as HMI_CALLSTATE_CONFERENCE_ONHOLD
             */
            else if(getCallStateCount(objCallStateInfoList, CALL_STATE_TERMINATED) == uiSize)
            {
                eHMICallState = HMI_CALLSTATE_ALL_CALLS_TERMINATED;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: invalid condition", __FUNCTION__);
            }

            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: hmiCallState: %d", __FUNCTION__, eHMICallState);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: call state info list is empty", __FUNCTION__);
    }
}

unsigned int CPhoneCallManagerResourceImpl::getCallStateCount(SCallStateInfoList& objCallStateInfoList, ECallState eCallState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    unsigned int uiCallStateCount = 0;
    unsigned int uiSize = static_cast<unsigned int>(objCallStateInfoList.m_vectCallStateInfo.size());
    //Get the call count which has call state same as the call state passed.
    for(unsigned int iIndex = 0; iIndex < uiSize; iIndex++)
    {
        if(objCallStateInfoList.m_vectCallStateInfo.at(iIndex).m_eCallState == eCallState)
            uiCallStateCount++;
    }

    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: callState: %d, count: %d", __FUNCTION__, eCallState, uiCallStateCount);
    return uiCallStateCount;
}

void CPhoneCallManagerResourceImpl::addCallStateInfo(SCallStateInfoList& objCallStateInfoList, BTPresTypes::callStateInfo& objCallState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    SCallStateInfo objCallStateInfo;
    objCallStateInfo.m_iCallId                  = objCallState.getCallId();
    objCallStateInfo.m_eCallState               = getCallState(objCallState.getCstate().value_);
    objCallStateInfo.m_strContactNumber         = objCallState.getNumber();
    objCallStateInfo.m_strContactName           = (objCallState.getName() == EMPTY_NAME_FOR_CONTACT) ? "" : objCallState.getName();
    objCallStateInfo.m_strContactImageUrl       = objCallState.getImageUrl();
    objCallStateInfo.m_eContactNumTeleType      = getContactTelephoneType(objCallState.getNumType().value_);
    objCallStateInfo.m_uiContactId              = objCallState.getMappedContactId();
    objCallStateInfo.m_eCallDirection           = getCallDirection(objCallState.getDirection().value_);
    objCallStateInfoList.m_vectCallStateInfo.push_back(objCallStateInfo);

    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: callId: %d, callState: %d, contactNumber: %s, contactName: %s, contactImageUrl: %s, contactNumTeleType: %d, contactId: %d, callDirection: %d",
             __FUNCTION__, objCallState.getCallId(), objCallState.getCstate().value_, objCallState.getNumber().c_str(), objCallState.getName().c_str(),
             objCallState.getImageUrl().c_str(), objCallState.getNumType().value_, objCallState.getMappedContactId(), objCallState.getDirection().value_);

}

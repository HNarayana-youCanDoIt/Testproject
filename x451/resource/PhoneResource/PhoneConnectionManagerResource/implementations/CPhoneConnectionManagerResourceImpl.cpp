/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneConnectionManagerResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CPhoneConnectionManagerResourceImpl class
 */

#include "CPhoneConnectionManagerResourceImpl.h"
#include "CPhoneConnectionManagerEventProvider.h"
#include <ResourceDeploymentConfig.h>
#include <ResourceMaster.h>
#include "logging.h"

CPhoneConnectionManagerResourceImpl::CPhoneConnectionManagerResourceImpl()
    :  MAX_DEVICES(30),
      DEVICE_SEARCH_TIMEOUT(40),
      m_pPhoneConnMgrEventProvider(new CPhoneConnectionManagerEventProvider()),
      m_objConnectionManagerProxy(ResourceDeploymentConfig::getConfig().m_PhoneConnectionManager_Proxy.domain,
                                ResourceDeploymentConfig::getConfig().m_PhoneConnectionManager_Proxy.instance),
      m_bIsConnectionManagerProxyAvailable(false),
      m_bIsBtAvailable(false),
      m_strPassKeyPin(""),
      m_bDeviceSearchStatus(false),
      m_bHUDiscoverableStatus(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    m_vectDeviceSearchList.clear();
    m_vectBondedDeviceList.clear();
    m_vectConnectedDeviceList.clear();
    subscribeConnectionManagerCb();
}

CPhoneConnectionManagerResourceImpl::~CPhoneConnectionManagerResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if (m_pPhoneConnMgrEventProvider)
    {
        delete m_pPhoneConnMgrEventProvider;
        m_pPhoneConnMgrEventProvider = NULL;
    }
}

CPhoneConnectionManagerEventProvider* CPhoneConnectionManagerResourceImpl::getPhoneConnectionManagerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    return m_pPhoneConnMgrEventProvider;
}

/******************************************************//**
 * @category REQUEST METHODS
 *******************************************************/
void CPhoneConnectionManagerResourceImpl::setDiscoverableModeAsyncReq(bool bEnable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        m_objConnectionManagerProxy->setDiscoverableModeAsync(bEnable,
                                                            std::bind(&CPhoneConnectionManagerResourceImpl::setDiscoverableModeAsyncCb,
                                                                      this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::startDeviceSearchAsyncReq()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        m_objConnectionManagerProxy->startDeviceSearchAsync(MAX_DEVICES, DEVICE_SEARCH_TIMEOUT,
                                                          std::bind(&CPhoneConnectionManagerResourceImpl::startDeviceSearchAsyncCb,
                                                                    this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::stopDeviceSearchAsyncReq()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        m_objConnectionManagerProxy->stopDeviceSearchAsync(std::bind(&CPhoneConnectionManagerResourceImpl::stopDeviceSearchAsyncCb,
                                                                   this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::startAllServiceConnectionAsyncReq(string strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);
        BTPresTypes::arSupportedProfile arySupportedProfiles;
        arySupportedProfiles.push_back(static_cast<BTPresTypes::eSupportedProfile::Literal>(BTPresTypes::eSupportedProfile::PROFILE_HFPGW));
        arySupportedProfiles.push_back(static_cast<BTPresTypes::eSupportedProfile::Literal>(BTPresTypes::eSupportedProfile::PROFILE_A2DP));
        m_objConnectionManagerProxy->startServiceConnectionAsync(strBtAddr, arySupportedProfiles, "",
                                                                 std::bind(&CPhoneConnectionManagerResourceImpl::startAllServiceConnectionAsyncCb, this, _1, _2),
                                                                 &objCallInfoData);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::startServiceConnectionAsyncReq(string strBtAddr, ESupportedProfile eProfileType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);
        m_objConnectionManagerProxy->startServiceConnectionAsync(strBtAddr, getProfileType(eProfileType), "", "",
                                                                 std::bind(&CPhoneConnectionManagerResourceImpl::startServiceConnectionAsyncCb, this, _1, _2),
                                                                 &objCallInfoData);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::bondingReplyAsyncReq(string strBtAddr, bool bAccepted, bool bSecureBonding)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        BTPresTypes::eBondingType eType = BTPresTypes::eBondingType::BONDING_STANDARD;
        if(bSecureBonding)
        {
            eType = BTPresTypes::eBondingType::BONDING_SECURE;
        }
        else
        {
            //do nothing
        }
        m_objConnectionManagerProxy->bondingReplyAsync(strBtAddr, bAccepted, true, eType,
                                                     std::bind(&CPhoneConnectionManagerResourceImpl::bondingReplyAsyncCb,
                                                               this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::deleteDeviceAsyncReq(string strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        m_objConnectionManagerProxy->deleteDeviceAsync(strBtAddr, std::bind(&CPhoneConnectionManagerResourceImpl::deleteDeviceAsyncCb,
                                                                          this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::deleteAllDevicesAsyncReq()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);
        m_objConnectionManagerProxy->deleteAllDevicesAsync(std::bind(&CPhoneConnectionManagerResourceImpl::deleteAllDevicesAsyncCb, this, _1, _2),
                                                           &objCallInfoData);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::startAllServiceDisconnectionAsyncReq(string strBtAddr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);
        BTPresTypes::arSupportedProfile arySupportedProfiles;
        arySupportedProfiles.push_back(static_cast<BTPresTypes::eSupportedProfile::Literal>(BTPresTypes::eSupportedProfile::PROFILE_HFPGW));
        arySupportedProfiles.push_back(static_cast<BTPresTypes::eSupportedProfile::Literal>(BTPresTypes::eSupportedProfile::PROFILE_A2DP));
        m_objConnectionManagerProxy->startServiceDisconnectionAsync(strBtAddr, arySupportedProfiles,
                                                                    std::bind(&CPhoneConnectionManagerResourceImpl::startAllServiceDisconnectionAsyncCb, this, _1, _2),
                                                                    &objCallInfoData);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::startServiceDisconnectionAsyncReq(string strBtAddr, ESupportedProfile eProfileType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);
        m_objConnectionManagerProxy->startServiceDisconnectionAsync(strBtAddr, getProfileType(eProfileType),
                                                                    std::bind(&CPhoneConnectionManagerResourceImpl::startServiceDisconnectionAsyncCb, this,_1,_2),
                                                                    &objCallInfoData);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::setBluetoothStatusAsyncReq(bool bEnable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(m_bIsConnectionManagerProxyAvailable)
    {
        m_objConnectionManagerProxy->setBluetoothStatusAsync(bEnable, std::bind(&CPhoneConnectionManagerResourceImpl::setBluetoothStatusAsyncCb,
                                                                                this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}

void CPhoneConnectionManagerResourceImpl::getOldestConnectedDeviceAsyncReq()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    if(m_bIsConnectionManagerProxyAvailable)
    {
        m_objConnectionManagerProxy->getOldestConnectedDevAsync(std::bind(&CPhoneConnectionManagerResourceImpl::getOldestConnectedDeviceAsyncCb,
                                                                                this, _1, _2, _3));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Connection manager proxy not available");
    }
}


/******************************************************//**
 * @category CALLBACK METHODS
 *******************************************************/
void CPhoneConnectionManagerResourceImpl::connectionManagerStatusCb(CommonAPI::AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    if(eStatus == CommonAPI::AvailabilityStatus::AVAILABLE)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"Proxy available");
        m_bIsConnectionManagerProxyAvailable = true;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"Proxy not available");
        m_bIsConnectionManagerProxyAvailable = false;
    }
}

void CPhoneConnectionManagerResourceImpl::bluetoothStatusCb(BTPresTypes::eBluetoothStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, eStatus = %d", __FUNCTION__, static_cast<int>(eStatus));
    if(eStatus == BTPresTypes::eBluetoothStatus::BTSTATE_ON)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, bluetooth is ON", __FUNCTION__);
        m_bIsBtAvailable = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, bluetooth is OFF", __FUNCTION__);
        m_bIsBtAvailable = false;
    }

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"update bluetooth status to upper layer");
        m_pPhoneConnMgrEventProvider->updateBluetoothStatus(m_bIsBtAvailable);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::passKeyPinCb(string strPassKey)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    m_strPassKeyPin = strPassKey;
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "passkey pin is: %s", m_strPassKeyPin.c_str());

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"update pass key to upper layer");
        m_pPhoneConnMgrEventProvider->updatePassKey(m_strPassKeyPin);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::deviceSearchStatusCB(bool bDeviceSearchStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    m_bDeviceSearchStatus = bDeviceSearchStatus;
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "device search status is: %d", m_bDeviceSearchStatus);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"update device search status to upper layer");
        m_pPhoneConnMgrEventProvider->updateDeviceSearchStatus(m_bDeviceSearchStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::discoverableStatusCb(bool bDiscoverableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    m_bHUDiscoverableStatus = bDiscoverableStatus;
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "HU discoverable status is: %d", m_bHUDiscoverableStatus);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"update HU discoverable status to upper layer");
        m_pPhoneConnMgrEventProvider->updateDiscoverableStatus(m_bHUDiscoverableStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::deviceSearchResultCb(BTPresTypes::tDeviceSearchEntryList vectSearchedDevices)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    m_vectDeviceSearchList.clear();
    int iSize = static_cast<int>(vectSearchedDevices.size());
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"device search list size: %d", iSize);
    for(int iIndex = 0; iIndex < iSize; iIndex++)
    {
        SSearchDeviceInfo objDeviceInfo;
        objDeviceInfo.m_strDeviceName      = vectSearchedDevices.at(iIndex).getDeviceName();
        objDeviceInfo.m_strDeviceBtAddr    = vectSearchedDevices.at(iIndex).getDeviceAddr();
        objDeviceInfo.m_eDeviceClass       = getDeviceClass(vectSearchedDevices.at(iIndex).getDeviceClass().value_);
        objDeviceInfo.m_bDeviceConnected   = vectSearchedDevices.at(iIndex).getConnected();
        objDeviceInfo.m_bDevicePaired      = vectSearchedDevices.at(iIndex).getPaired();
        m_vectDeviceSearchList.push_back(objDeviceInfo);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"deviceName: %s, deviceAddress: %s, deviceClass: %d, connected: %d, paired: %d", vectSearchedDevices.at(iIndex).getDeviceName().c_str(),
                 vectSearchedDevices.at(iIndex).getDeviceAddr().c_str(), vectSearchedDevices.at(iIndex).getDeviceClass().value_, vectSearchedDevices.at(iIndex).getConnected(),
                 vectSearchedDevices.at(iIndex).getPaired());
    }

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify device search result is received to upper layer");
        m_pPhoneConnMgrEventProvider->deviceSearchResultReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::bondedDeviceListCb(BTPresTypes::bondedDevList vectBondedDeviceList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    m_vectBondedDeviceList.clear();
    parseDeviceList(vectBondedDeviceList, m_vectBondedDeviceList);

    // Propagate the information to the phone adaptor layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify bonded device list is received to upper layer");
        m_pPhoneConnMgrEventProvider->bondedDeviceListReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::connectedDeviceListCb(BTPresTypes::bondedDevList vectConnectedDeviceList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectConnectedDeviceList.clear();
    parseDeviceList(vectConnectedDeviceList, m_vectConnectedDeviceList);

    // Propagate the information to the phone adaptor layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify connected device list is received to upper layer");
        m_pPhoneConnMgrEventProvider->connectedDeviceListReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::bondingStatusCb(string strBtAddr, string strDeviceName, BTPresTypes::ePairingStatus ePairingStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    m_objDeviceBondingStatus.clear();
    m_objDeviceBondingStatus.m_strDeviceBtAddr      = strBtAddr;
    m_objDeviceBondingStatus.m_strDeviceName        = strDeviceName;
    m_objDeviceBondingStatus.m_ePairingStatus       = getDevicePairingStatus(ePairingStatus.value_);
    m_objDeviceBondingStatus.m_bPairingSuccessful   = (ePairingStatus.value_ == ePairingStatus.Literal::PAIRING_SUCCESS);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"deviceAddr: %s, deviceName: %s, pairingStatus: %d, pairingSuccessful: %d", strBtAddr.c_str(),
             strDeviceName.c_str(), ePairingStatus.value_, m_objDeviceBondingStatus.m_bPairingSuccessful);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify bonding status is received to upper layer");
        m_pPhoneConnMgrEventProvider->bondingStatusReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::bondingRequestCb(string strBtAddr, string strDeviceName, BTPresTypes::eBondingType eBondingType, string strPin)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    m_objBondingRequest.clear();
    m_objBondingRequest.m_strDeviceBtAddr   = strBtAddr;
    m_objBondingRequest.m_strDeviceName     = strDeviceName;
    m_objBondingRequest.m_strPasskey        = strPin;
    m_objBondingRequest.m_eBondingType      = getDeviceBondingType(eBondingType.value_);
    m_objBondingRequest.m_bSecureBonding    = (eBondingType.value_ == eBondingType.Literal::BONDING_SECURE);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"deviceAddr: %s, deviceName: %s, passKey: %s, bondingType: %d, secureBonding: %d", strBtAddr.c_str(),
             strDeviceName.c_str(), strPin.c_str(), eBondingType.value_, m_objBondingRequest.m_bSecureBonding);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"CPhoneConnectionManagerResourceImpl::bondingRequestCb: notify bonding request is received to upper layer");
        m_pPhoneConnMgrEventProvider->bondingRequestReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::serviceConnectionStatusCb(string strBtAddr, string strDeviceName, BTPresTypes::eSupportedProfile eSupportedProfile, BTPresTypes::eConnectionStatus eConnectionStatus, BTPresTypes::eServiceConnectDisconnectReason eServiceConnectDisconnectReason)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    m_objServiceConnectionStatus.clear();
    m_objServiceConnectionStatus.m_strDeviceBtAddr                  = strBtAddr;
    m_objServiceConnectionStatus.m_strDeviceName                    = strDeviceName;
    m_objServiceConnectionStatus.m_eSupportedProfile                = getProfileType(eSupportedProfile.value_);
    m_objServiceConnectionStatus.m_eConnectionStatus                = getServiceConnectionStatus(eConnectionStatus.value_);
    m_objServiceConnectionStatus.m_bConnectionSuccessful            = (eConnectionStatus.value_ == eConnectionStatus.Literal::SERVICE_CONNECTED);
    m_objServiceConnectionStatus.m_bDisconnectionSuccessful         = (eConnectionStatus.value_ == eConnectionStatus.Literal::SERVICE_DISCONNECTED);
    m_objServiceConnectionStatus.m_eServiceConnectDisconnectReason  = getServiceConnectDisconnectReason(eServiceConnectDisconnectReason.value_);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"deviceAddr: %s, deviceName: %s, profileName: %d, connectionStatus: %d, connectionSuccessful: %d, disconnectionSuccessful: %d, serviceConnectDisconnectReason: %d",
             strBtAddr.c_str(), strDeviceName.c_str(), eSupportedProfile.value_, eConnectionStatus.value_,
             m_objServiceConnectionStatus.m_bConnectionSuccessful, m_objServiceConnectionStatus.m_bDisconnectionSuccessful, eServiceConnectDisconnectReason.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify service connection status is received to upper layer");
        m_pPhoneConnMgrEventProvider->serviceConnectionStatusReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::deviceDeletedCb(string strBtAddr, string strDeviceName, BTPresTypes::eDeviceDeletedReason eDeviceDeleteReason)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    m_objDeviceDeleted.clear();
    m_objDeviceDeleted.m_strDeviceBtAddr        = strBtAddr;
    m_objDeviceDeleted.m_strDeviceName          = strDeviceName;
    m_objDeviceDeleted.m_eDeviceDeleteReason    = getDeviceDeletedReason(eDeviceDeleteReason.value_);
    m_objDeviceDeleted.m_bUserRequested         = (eDeviceDeleteReason.value_ == eDeviceDeleteReason.Literal::DEVICE_DELETED_REASON_USER_REQUESTED);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"deviceAddr: %s, deviceName: %s, deviceDeleteReason: %d, userRequested: %d", strBtAddr.c_str(),
             strDeviceName.c_str(), eDeviceDeleteReason.value_, m_objDeviceDeleted.m_bUserRequested);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify device deleted is received to upper layer");
        m_pPhoneConnMgrEventProvider->deviceDeletedReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}


/********************************************//**
 * @category RESPONSE CALLBACK METHODS
 ************************************************/
void CPhoneConnectionManagerResourceImpl::setDiscoverableModeAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify setDiscoverableMode method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->setDiscoverableModeMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                          getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::startDeviceSearchAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify startDeviceSearch method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->startDeviceSearchMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                        getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::stopDeviceSearchAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify stopDeviceSearch method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->stopDeviceSearchMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                       getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::startAllServiceConnectionAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify startAllServiceConnection method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->startAllServiceConnectionMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                                getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::startServiceConnectionAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, CallStatus: %d, ErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify startServiceConnection method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->startServiceConnectionMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                             getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::bondingReplyAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"CallStatus: %d, ErrorType: %d", static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify bondingReply method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->bondingReplyMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                   getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::deleteDeviceAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"CallStatus: %d, ErrorType: %d", static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify deleteDevice method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->deleteDeviceMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                   getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::deleteAllDevicesAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"CallStatus: %d, ErrorType: %d", static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify deleteAllDevices method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->deleteAllDevicesMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                       getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::startAllServiceDisconnectionAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"CallStatus: %d, ErrorType: %d", static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify startAllServiceDisconnection method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->startAllServiceDisconnectionMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                                   getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::startServiceDisconnectionAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"CallStatus: %d, ErrorType: %d", static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify startServiceDisconnection method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->startServiceDisconnectionMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                                getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::setBluetoothStatusAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"CallStatus: %d, ErrorType: %d", static_cast<int>(eCallStatus), eErrorType.value_);

    // Propagate the information to the phone application layer
    if (m_pPhoneConnMgrEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"notify setBluetoothStatus method call status is received to upper layer");
        m_pPhoneConnMgrEventProvider->setBluetoothStatusMethodCallStatus(getMethodCallStatus(eCallStatus),
                                                                         getMethodCallErrorType(eErrorType.value_));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CPhoneConnectionManagerResourceImpl::getOldestConnectedDeviceAsyncCb(const CallStatus &eCallStatus,
                                                                          const BTPresTypes::eErrorType &eErrorType,
                                                                          const BTPresTypes::deviceInfo &objDeviceInfo
                                                                          )
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: CallStatus: %d, ErrorType: %d, deviceName: %s, deviceAddress: %s",
             __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_, objDeviceInfo.getName().c_str(),
             objDeviceInfo.getAddress().c_str());

    if (m_pPhoneConnMgrEventProvider)
    {
        m_pPhoneConnMgrEventProvider->updateOldestConnectedtDeviceInfo(objDeviceInfo.getName(), objDeviceInfo.getAddress());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "data event provider object not created");
    }

}


/******************************************************//**
 * @category INTERNAL METHODS
 *******************************************************/
void CPhoneConnectionManagerResourceImpl::subscribeConnectionManagerCb()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    SUBSCRIBE(m_objConnectionManagerProxy, getProxyStatusEvent(),                               &CPhoneConnectionManagerResourceImpl::connectionManagerStatusCb,    _1);
    SUBSCRIBE(m_objConnectionManagerProxy, getBtStateAttribute().getChangedEvent(),             &CPhoneConnectionManagerResourceImpl::bluetoothStatusCb,            _1);
    SUBSCRIBE(m_objConnectionManagerProxy, getPassKeyPinAttribute().getChangedEvent(),          &CPhoneConnectionManagerResourceImpl::passKeyPinCb,                 _1);
    SUBSCRIBE(m_objConnectionManagerProxy, getDeviceSearchStatusAttribute().getChangedEvent(),  &CPhoneConnectionManagerResourceImpl::deviceSearchStatusCB,         _1);
    SUBSCRIBE(m_objConnectionManagerProxy, getDiscoverableStatusAttribute().getChangedEvent(),  &CPhoneConnectionManagerResourceImpl::discoverableStatusCb,         _1);
    SUBSCRIBE(m_objConnectionManagerProxy, getDevSearchResultsAttribute().getChangedEvent(),    &CPhoneConnectionManagerResourceImpl::deviceSearchResultCb,         _1);
    SUBSCRIBE(m_objConnectionManagerProxy, getDevListAttribute().getChangedEvent(),             &CPhoneConnectionManagerResourceImpl::bondedDeviceListCb,           _1);
//    SUBSCRIBE(m_objConnectionManagerProxy, getConnectedDevListAttribute().getChangedEvent(),  &CPhoneConnectionManagerResourceImpl::connectedDeviceListCb,        _1);
    SUBSCRIBE(m_objConnectionManagerProxy, getBondingStatusEvent(),                             &CPhoneConnectionManagerResourceImpl::bondingStatusCb,              _1, _2, _3);
    SUBSCRIBE(m_objConnectionManagerProxy, getBondingRequestEvent(),                            &CPhoneConnectionManagerResourceImpl::bondingRequestCb,             _1, _2, _3, _4);
    SUBSCRIBE(m_objConnectionManagerProxy, getServiceConnectionStatusEvent(),                   &CPhoneConnectionManagerResourceImpl::serviceConnectionStatusCb,    _1, _2, _3, _4, _5);
    SUBSCRIBE(m_objConnectionManagerProxy, getDeviceDeletedEvent(),                             &CPhoneConnectionManagerResourceImpl::deviceDeletedCb,              _1, _2, _3);
}

EMethodCallStatus CPhoneConnectionManagerResourceImpl::getMethodCallStatus(CallStatus eCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
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
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for call status passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "method call status is: %d", eMethodCallStatus);
    return eMethodCallStatus;
}

EMethodCallErrorType CPhoneConnectionManagerResourceImpl::getMethodCallErrorType(int iErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
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
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for method call error type passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "method call error type is: %d", eMethodCallErrorType);
    return eMethodCallErrorType;
}

EDeviceClass CPhoneConnectionManagerResourceImpl::getDeviceClass(int iDeviceClass)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    EDeviceClass eDeviceClass = DEVICE_CLASS_DEFAULT;
    switch(iDeviceClass)
    {
    case BTPresTypes::eCOD::CLASS_COMPUTER:
        eDeviceClass = DEVICE_CLASS_COMPUTER;
        break;
    case BTPresTypes::eCOD::CLASS_PHONE:
        eDeviceClass = DEVICE_CLASS_PHONE;
        break;
    case BTPresTypes::eCOD::CLASS_AUDIO_VIDEO:
        eDeviceClass = DEVICE_CLASS_AUDIO_VIDEO;
        break;
    case BTPresTypes::eCOD::CLASS_WEARABLE:
        eDeviceClass = DEVICE_CLASS_WEARABLE;
        break;
    case BTPresTypes::eCOD::CLASS_OTHERS:
        eDeviceClass = DEVICE_CLASS_OTHERS;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for class of device passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "call of device is is: %d", eDeviceClass);
    return eDeviceClass;
}

ESupportedProfile CPhoneConnectionManagerResourceImpl::getProfileType(int iProfile)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    ESupportedProfile eProfileType = PROFILE_TYPE_DEFAULT;
    switch(iProfile)
    {
    case BTPresTypes::eSupportedProfile::PROFILE_HFPGW:
        eProfileType = PROFILE_TYPE_HFPGW;
        break;
    case BTPresTypes::eSupportedProfile::PROFILE_A2DP:
        eProfileType = PROFILE_TYPE_A2DP;
        break;
    case BTPresTypes::eSupportedProfile::PROFILE_AVRCP:
        eProfileType = PROFILE_TYPE_AVRCP;
        break;
    case BTPresTypes::eSupportedProfile::PROFILE_SPP:
        eProfileType = PROFILE_TYPE_SPP;
        break;
    case BTPresTypes::eSupportedProfile::PROFILE_PAN:
        eProfileType = PROFILE_TYPE_PAN;
        break;
    case BTPresTypes::eSupportedProfile::PROFILE_PBAP:
        eProfileType = PROFILE_TYPE_PBAP;
        break;
    case BTPresTypes::eSupportedProfile::PROFILE_MAP:
        eProfileType = PROFILE_TYPE_MAP;
        break;
    case BTPresTypes::eSupportedProfile::PROFILE_UNKNOWN:
        eProfileType = PROFILE_TYPE_UNKNOWN;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for supported profile passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "profile type is: %d", eProfileType);
    return eProfileType;
}

BTPresTypes::eSupportedProfile CPhoneConnectionManagerResourceImpl::getProfileType(ESupportedProfile eProfileType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    BTPresTypes::eSupportedProfile objSupportedProfile = BTPresTypes::eSupportedProfile::PROFILE_UNKNOWN;
    switch(eProfileType)
    {
    case PROFILE_TYPE_HFPGW:
        objSupportedProfile = BTPresTypes::eSupportedProfile::PROFILE_HFPGW;
        break;
    case PROFILE_TYPE_A2DP:
        objSupportedProfile = BTPresTypes::eSupportedProfile::PROFILE_A2DP;
        break;
    case PROFILE_TYPE_AVRCP:
        objSupportedProfile = BTPresTypes::eSupportedProfile::PROFILE_AVRCP;
        break;
    case PROFILE_TYPE_SPP:
        objSupportedProfile = BTPresTypes::eSupportedProfile::PROFILE_SPP;
        break;
    case PROFILE_TYPE_PAN:
        objSupportedProfile = BTPresTypes::eSupportedProfile::PROFILE_PAN;
        break;
    case PROFILE_TYPE_PBAP:
        objSupportedProfile = BTPresTypes::eSupportedProfile::PROFILE_PBAP;
        break;
    case PROFILE_TYPE_MAP:
        objSupportedProfile = BTPresTypes::eSupportedProfile::PROFILE_MAP;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for supported profile passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "profile type is: %d", objSupportedProfile.value_);
    return objSupportedProfile;
}

EConnectionStatus CPhoneConnectionManagerResourceImpl::getServiceConnectionStatus(int iConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    EConnectionStatus eConnectionStatus = CONNECTION_STATUS_DEFAULT;
    switch(iConnectionStatus)
    {
    case BTPresTypes::eConnectionStatus::SERVICE_CONNECTED:
        eConnectionStatus = CONNECTION_STATUS_CONNECTED;
        break;
    case BTPresTypes::eConnectionStatus::SERVICE_CONNECTING:
        eConnectionStatus = CONNECTION_STATUS_CONNECTING;
        break;
    case BTPresTypes::eConnectionStatus::SERVICE_DISCONNECTING:
        eConnectionStatus = CONNECTION_STATUS_DISCONNECTING;
        break;
    case BTPresTypes::eConnectionStatus::SERVICE_DISCONNECTED:
        eConnectionStatus = CONNECTION_STATUS_DISCONNECTED;
        break;
    case BTPresTypes::eConnectionStatus::SERVICE_CONNECTERROR:
        eConnectionStatus = CONNECTION_STATUS_CONNECTERROR;
        break;
    case BTPresTypes::eConnectionStatus::SERVICE_NOT_SUPPORTED:
        eConnectionStatus = CONNECTION_STATUS_NOT_SUPPORTED;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for connection status passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "connection status is: %d", eConnectionStatus);
    return eConnectionStatus;
}

EPairingStatus CPhoneConnectionManagerResourceImpl::getDevicePairingStatus(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    EPairingStatus ePairingStatus = PAIRING_STATUS_DEFAULT;
    switch(iStatus)
    {
    case BTPresTypes::ePairingStatus::PAIRING_SUCCESS:
        ePairingStatus = PAIRING_STATUS_SUCCESS;
        break;
    case BTPresTypes::ePairingStatus::PAIRING_FAILURE:
        ePairingStatus = PAIRING_STATUS_FAILURE;
        break;
    case BTPresTypes::ePairingStatus::PAIRING_DISCOVERABLE:
        ePairingStatus = PAIRING_STATUS_DISCOVERABLE;
        break;
    case BTPresTypes::ePairingStatus::PAIRING_NOT_DISCOVERABLE:
        ePairingStatus = PAIRING_STATUS_NOT_DISCOVERABLE;
        break;
    case BTPresTypes::ePairingStatus::PAIRING_FAILED_NO_USER_ACTION_FROM_HU:
        ePairingStatus = PAIRING_STATUS_FAILED_NO_USER_ACTION_FROM_HU;
        break;
    case BTPresTypes::ePairingStatus::INCOMPATIBLE_REMOTE_DEVICE:
        ePairingStatus = PAIRING_STATUS_INCOMPATIBLE_REMOTE_DEVICE;
        break;
    case BTPresTypes::ePairingStatus::UNRESPONSIVE_DEVICE:
        ePairingStatus = PAIRING_STATUS_UNRESPONSIVE_DEVICE;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for pairing status passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, pairing status is: %d", __FUNCTION__, ePairingStatus);
    return ePairingStatus;
}

EBondingType CPhoneConnectionManagerResourceImpl::getDeviceBondingType(int iBondingType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    EBondingType eDeviceBondingType = BONDING_TYPE_DEAFULT;
    switch(iBondingType)
    {
    case BTPresTypes::eBondingType::BONDING_STANDARD:
        eDeviceBondingType = BONDING_TYPE_STANDARD;
        break;
    case BTPresTypes::eBondingType::BONDING_SECURE:
        eDeviceBondingType = BONDING_TYPE_SECURE;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for bonding type passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "bonding type is: %d", eDeviceBondingType);
    return eDeviceBondingType;
}

EServiceConnectDisconnectReason CPhoneConnectionManagerResourceImpl::getServiceConnectDisconnectReason(int iReason)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    EServiceConnectDisconnectReason eServiceConnectDisconnectReason = SERVICE_CONNECT_DISCONNECT_DEFAULT;
    switch(iReason)
    {
    case BTPresTypes::eServiceConnectDisconnectReason::SERVICE_CONNECTED_HEADUNIT_INITIATED:
        eServiceConnectDisconnectReason = SERVICE_CONNECTED_HEADUNIT_INITIATED;
        break;
    case BTPresTypes::eServiceConnectDisconnectReason::SERVICE_CONNECTED_PHONE_INITIATED:
        eServiceConnectDisconnectReason = SERVICE_CONNECTED_PHONE_INITIATED;
        break;
    case BTPresTypes::eServiceConnectDisconnectReason::SERVICE_CONNECTED_AUTO_CONNECTION:
        eServiceConnectDisconnectReason = SERVICE_CONNECTED_AUTO_CONNECTION;
        break;
    case BTPresTypes::eServiceConnectDisconnectReason::SERVICE_DISCONNECTED_HEADUNIT_INITIATED:
        eServiceConnectDisconnectReason = SERVICE_DISCONNECTED_HEADUNIT_INITIATED;
        break;
    case BTPresTypes::eServiceConnectDisconnectReason::SERVICE_DISCONNECTED_PHONE_INITIATED:
        eServiceConnectDisconnectReason = SERVICE_DISCONNECTED_PHONE_INITIATED;
        break;
    case BTPresTypes::eServiceConnectDisconnectReason::SERVICE_DISCONNECTED_LINK_LOSS:
        eServiceConnectDisconnectReason = SERVICE_DISCONNECTED_LINK_LOSS;
        break;
    case BTPresTypes::eServiceConnectDisconnectReason::SERVICE_CONNECT_ERROR_PAGE_TIMEOUT:
        eServiceConnectDisconnectReason = SERVICE_CONNECT_ERROR_PAGE_TIMEOUT;
        break;
    case BTPresTypes::eServiceConnectDisconnectReason::SERVICE_CONNECT_ERROR_USER_REJECTED:
        eServiceConnectDisconnectReason = SERVICE_CONNECT_ERROR_USER_REJECTED;
        break;
    case BTPresTypes::eServiceConnectDisconnectReason::SERVICE_DISCONNECTED_DEVICE_DISCONNECTED:
        eServiceConnectDisconnectReason = SERVICE_DISCONNECTED_DEVICE_DISCONNECTED;
        break;
    case BTPresTypes::eServiceConnectDisconnectReason::SERVICE_DISCONNECTED_NEW_CONNECTION_REQUEST:
        eServiceConnectDisconnectReason = SERVICE_DISCONNECTED_NEW_CONNECTION_REQUEST;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for service connection disconnection reason passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "service connection disconnection reason is: %d", eServiceConnectDisconnectReason);
    return eServiceConnectDisconnectReason;
}

EDeviceDeletedReason CPhoneConnectionManagerResourceImpl::getDeviceDeletedReason(int iReason)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s", __FUNCTION__);
    EDeviceDeletedReason eDeviceDeletedReason = DEVICE_DELETED_REASON_DEFAULT;
    switch(iReason)
    {
    case BTPresTypes::eDeviceDeletedReason::DEVICE_DELETED_REASON_MISSING_KEY:
        eDeviceDeletedReason = DEVICE_DELETED_REASON_MISSING_KEY;
        break;
    case BTPresTypes::eDeviceDeletedReason::DEVICE_DELETED_REASON_USER_REQUESTED:
        eDeviceDeletedReason = DEVICE_DELETED_REASON_USER_REQUESTED;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value for device deleted reason passed");
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "device deleted reason is: %d", eDeviceDeletedReason);
    return eDeviceDeletedReason;
}

void CPhoneConnectionManagerResourceImpl::parseDeviceList(BTPresTypes::bondedDevList& vectDeviceList, vector<SBondedDeviceInfo>& vectDeviceInfo)
{
    int iSize = static_cast<int>(vectDeviceList.size());
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"bonded device list size: %d", iSize);
    for(int iIndex = 0; iIndex < iSize; iIndex++)
    {
        SBondedDeviceInfo objBondedDeviceInfo;
        objBondedDeviceInfo.m_strDeviceName     = vectDeviceList.at(iIndex).getDevName();
        objBondedDeviceInfo.m_strDeviceBtAddr   = vectDeviceList.at(iIndex).getBtAddress();
        objBondedDeviceInfo.m_uiIndex           = vectDeviceList.at(iIndex).getIndex();
        objBondedDeviceInfo.m_eDeviceClass      = getDeviceClass(vectDeviceList.at(iIndex).getDeviceClass().value_);
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"deviceName: %s, deviceAddress: %s, deviceClass: %d, deviceIndex: %d", vectDeviceList.at(iIndex).getDevName().c_str(),
                 vectDeviceList.at(iIndex).getBtAddress().c_str(), vectDeviceList.at(iIndex).getDeviceClass().value_, vectDeviceList.at(iIndex).getIndex());

        BTPresTypes::profileInfoList vectProfileList    = vectDeviceList.at(iIndex).getProfileList();
        int iProfileListSize                            = static_cast<int>(vectProfileList.size());
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"profile list size: %d", iProfileListSize);

        for(int iProfileIndex = 0; iProfileIndex < iProfileListSize; iProfileIndex++)
        {
            SProfileInfo objProfileInfo;

            objProfileInfo.m_uiMajorVersion = vectProfileList.at(iProfileIndex).getMajorNum();
            objProfileInfo.m_uiMinorVersion = vectProfileList.at(iProfileIndex).getMinorNum();
            ESupportedProfile eProfileType  = PROFILE_TYPE_DEFAULT;
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"majorNum: %d, minorNum: %d", objProfileInfo.m_uiMajorVersion, objProfileInfo.m_uiMinorVersion);

            for (auto& connectionStateMap: vectProfileList.at(iProfileIndex).getService())
            {
                eProfileType                        = getProfileType(connectionStateMap.first.value_);
                objProfileInfo.m_eConnectionStatus  = getServiceConnectionStatus(connectionStateMap.second.value_);
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"profileType: %d, serviceConnectionStatus: %d", connectionStateMap.first.value_, connectionStateMap.second.value_);
            }
            //const ESupportedProfile eTemp = eProfileType;
            objBondedDeviceInfo.m_mapProfileInfoList.insert({eProfileType, objProfileInfo});
        }

        vectDeviceInfo.push_back(objBondedDeviceInfo);
    }
}

/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneEventHandler.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the slots and methods declared in
 *                CPhoneEventHandler class
 */

#include "CPhoneEventHandler.h"
#include "ResourceFactory.hpp"
#include "logging.h"
#include "CPhoneAdaptor.h"
#include "implementations/CPhoneConnectionManagerResourceImpl.h"
#include "implementations/CPhoneCallManagerResourceImpl.h"
#include "implementations/CPhonePIMDBResourceImpl.h"
#include "implementations/CBtPluginResourceImpl.h"

CPhoneEventHandler::CPhoneEventHandler(QObject* pParent): QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    connectConnectionManagerSignals();
    connectCallManagerSignals();
    connectPimDbSignals();
    connectBtPluginSignals();
}

CPhoneEventHandler::~CPhoneEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    disconnectConnectionManagerSignals();
    disconnectCallManagerSignals();
    disconnectPimDbSignals();
    disconnectBtPluginSignals();
}

/******************************************************//**
 * @category    CONNECTION MANAGER SLOTS
 *******************************************************/
void CPhoneEventHandler::sltUpdateBluetoothStatus(bool bIsBtAvailable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateBluetoothStatus(bIsBtAvailable);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltUpdatePassKey(const string &strPassKey)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updatePassKey(strPassKey);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltUpdateDeviceSearchStatus(bool bDeviceSearchStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateDeviceSearchStatus(bDeviceSearchStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltUpdateDiscoverableStatus(bool bDiscoverableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateHUDiscoverableStatus(bDiscoverableStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltDeviceSearchResultReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateDeviceSearchResult();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltBondedDeviceListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateBondedDeviceList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltConnectedDeviceListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateConnectedDeviceList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltBondingStatusReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateBondingStatus();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltBondingRequestReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateBondingRequest();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltServiceConnectionStatusReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateServiceConnectionStatus();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltDeviceDeletedReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateDeviceDeletedStatus();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltSetDiscoverableModeMethodCallStatus(int iMethodCallStatus,
                                                                int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateSetDiscoverableModeMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                                static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltStartDeviceSearchMethodCallStatus(int iMethodCallStatus,
                                                              int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateStartDeviceSearchMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                              static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltStopDeviceSearchMethodCallStatus(int iMethodCallStatus,
                                                             int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateStopDeviceSearchMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                             static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltStartAllServiceConnectionMethodCallStatus(int iMethodCallStatus,
                                                                      int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateStartAllServiceConnectionMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                                      static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltStartServiceConnectionMethodCallStatus(int iMethodCallStatus,
                                                                   int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateStartServiceConnectionMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                                   static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltBondingReplyMethodCallStatus(int iMethodCallStatus,
                                                         int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateBondingReplyMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                         static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltDeleteDeviceMethodCallStatus(int iMethodCallStatus,
                                                         int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateDeleteDeviceMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                         static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltDeleteAllDevicesMethodCallStatus(int iMethodCallStatus,
                                                             int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateDeleteAllDevicesMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                             static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltStartAllServiceDisconnectionMethodCallStatus(int iMethodCallStatus,
                                                                         int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateStartAllServiceDisconnectionMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                                         static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltStartServiceDisconnectionMethodCallStatus(int iMethodCallStatus,
                                                                      int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateStartServiceDisconnectionMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                                      static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltSetBluetoothMethodStatusCallStatus(int iMethodCallStatus,
                                                               int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateSetBluetoothStatusMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                               static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltUpdateOldestConnectedDeviceInfo(const QString &strDeviceName, const QString &strDeviceAddress)
{
   LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

   if(CPhoneAdaptor::getInstance())
   {
       CPhoneAdaptor::getInstance()->updateOldestConnectedDeviceInfo(strDeviceName, strDeviceAddress);
   }
   else
   {
       LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
   }
}

/******************************************************//**
 * @category    CALL MANAGER SLOTS
 *******************************************************/
void CPhoneEventHandler::sltCallStateInfoReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->callStateInfoUpdated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltHfFeaturesListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateHfFeatures();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltOperatorInfoListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateOperatorInfoList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltRssiChargeInfoListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateRssiChargeInfo();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltHfModeStatusReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateHfModeStatus();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltCallDurationReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateCallDuration();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltPhoneBtVrModeStatusReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updatePhoneBtVrModeStatus();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltAcceptIncomingCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateAcceptIncomingCallAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                                    static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltRejectIncomingCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateRejectIncomingCallAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                                    static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltSendSMSAsyncMethodCallStatus(bool bIsSucessful)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateSendSMSAsyncMethodCallStatus(bIsSucessful);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltDialAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateDialAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                      static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltConferenceCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateConferenceCallAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                                static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltSwapCallsAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateSwapCallsAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                           static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltResumeHeldCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateResumeHeldCallAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                                static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltHoldActiveCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateHoldActiveCallAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                                static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltEndCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateEndCallAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                         static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltEndActiveCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateEndActiveCallAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                               static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltEndAllCallsAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateEndAllCallsAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                             static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltSendDtmfToneAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateSendDtmfToneAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                              static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltSetHfModeAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateSetHfModeAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                           static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltSetVRModeAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateSetVRModeAsyncMethodCallStatus(static_cast<EMethodCallStatus>(iMethodCallStatus),
                                                                           static_cast<EMethodCallErrorType>(iMethodCallErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

/****************************************************//**
 * @category    PHONE PIMDB SLOTS
 *****************************************************/
void CPhoneEventHandler::sltPimDbServiceAvailableStatusChanged(bool bPimDbServiceAvailableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, bPimDbServiceAvailableStatus = %d", __FUNCTION__, bPimDbServiceAvailableStatus);
    CPhoneAdaptor::getInstance()->pimDbServiceAvailableStatusChanged(bPimDbServiceAvailableStatus);
}

void CPhoneEventHandler::sltPimDbSessionClosedSelectiveEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->resetPimdbProperties();
}

void CPhoneEventHandler::sltCallLogStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s status : %d", __FUNCTION__, static_cast<int>(iStatus));
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->changePimDbCallListSyncState(static_cast<CPhoneEnum::EPhoneSyncStatus>(iStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltContactStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s status : %d", __FUNCTION__, static_cast<int>(iStatus));
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->changePimDbContactListSyncState(static_cast<CPhoneEnum::EPhoneSyncStatus>(iStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltContactDetailStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s status : %d", __FUNCTION__, static_cast<int>(iStatus));
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->changePimDbContactDetailSyncState(static_cast<CPhoneEnum::EPhoneSyncStatus>(iStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltFavoriteStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s status : %d", __FUNCTION__, static_cast<int>(iStatus));
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->changePimDbFavouriteListSyncState(static_cast<CPhoneEnum::EPhoneSyncStatus>(iStatus));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltFrequentlyDialedStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s status : %d", __FUNCTION__, static_cast<int>(iStatus));
    CPhoneAdaptor::getInstance()->changePimDbFrequentlyDialedListSyncState(static_cast<CPhoneEnum::EPhoneSyncStatus>(iStatus));
}

void CPhoneEventHandler::sltCallLogUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->pimDbCallListUpdated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltContactUpdated(unsigned short usStartIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->pimDbContactListUpdated(usStartIndex);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltContactDetailUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->pimDbContactDetailListUpdated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltFavoriteUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->pimDbFavouriteListUpdated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltFrequentlyDialedListUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    CPhoneAdaptor::getInstance()->pimDbFrequentlyDialedListUpdated();
}

void CPhoneEventHandler::sltAddContactToFavouriteComplete(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->pimDbSetAsFavoriteOperationResult(bStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltRemoveContactFromFavouriteComplete(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->pimDbRemoveAsFavoriteOperationResult(bStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltMessageNotificationEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->newMessageNotification();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltIsSendingSMSAllowedPermissionChanged(bool bIsSendingSMSAllowed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->setIsSendingSMSAllowed(bIsSendingSMSAllowed);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltUnreadMissedCallEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateUnreadMissedCallStatus();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

void CPhoneEventHandler::sltGetSmsSupportedFeatureEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateGetSmsSupportedFeature();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

/******************************************************************//**
 * @category    BT PRESS PLUGIN SLOTS
 *******************************************************************/
void CPhoneEventHandler::sltTTSPlayStateStatus(int iTTSPlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->updateTTSPlayStateStatus(iTTSPlayState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phone adaptor object not created", __FUNCTION__);
    }
}

/******************************************************//**
 * @category    INTERNAL METHODS
 *******************************************************/
void CPhoneEventHandler::connectConnectionManagerSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneConnectionManagerResourceImpl* pPhConnMgrResource = dynamic_cast<CPhoneConnectionManagerResourceImpl*>(ResourceFactory::getPhoneConnectionManagerResource());

    if(pPhConnMgrResource)
    {
        CPhoneConnectionManagerEventProvider* pPhConnMgrEventProvider = pPhConnMgrResource->getPhoneConnectionManagerEventProvider();
        connect(pPhConnMgrEventProvider, SIGNAL(sigUpdateBluetoothStatus(bool)),                                        this, SLOT(sltUpdateBluetoothStatus(bool)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigUpdateDeviceSearchStatus(bool)),                                     this, SLOT(sltUpdateDeviceSearchStatus(bool)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigUpdateDiscoverableStatus(bool)),                                     this, SLOT(sltUpdateDiscoverableStatus(bool)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigDeviceSearchResultReceived()),                                       this, SLOT(sltDeviceSearchResultReceived()));
        connect(pPhConnMgrEventProvider, SIGNAL(sigBondedDeviceListReceived()),                                         this, SLOT(sltBondedDeviceListReceived()));
        connect(pPhConnMgrEventProvider, SIGNAL(sigConnectedDeviceListReceived()),                                      this, SLOT(sltConnectedDeviceListReceived()));
        connect(pPhConnMgrEventProvider, SIGNAL(sigBondingStatusReceived()),                                            this, SLOT(sltBondingStatusReceived()));
        connect(pPhConnMgrEventProvider, SIGNAL(sigBondingRequestReceived()),                                           this, SLOT(sltBondingRequestReceived()));
        connect(pPhConnMgrEventProvider, SIGNAL(sigServiceConnectionStatusReceived()),                                  this, SLOT(sltServiceConnectionStatusReceived()));
        connect(pPhConnMgrEventProvider, SIGNAL(sigDeviceDeletedReceived()),                                            this, SLOT(sltDeviceDeletedReceived()));
        connect(pPhConnMgrEventProvider, SIGNAL(sigSetDiscoverableModeMethodCallStatus(int, int)),                      this, SLOT(sltSetDiscoverableModeMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigStartDeviceSearchMethodCallStatus(int, int)),                        this, SLOT(sltStartDeviceSearchMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigStopDeviceSearchMethodCallStatus(int, int)),                         this, SLOT(sltStopDeviceSearchMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigStartAllServiceConnectionMethodCallStatus(int, int)),                this, SLOT(sltStartAllServiceConnectionMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigStartServiceConnectionMethodCallStatus(int, int)),                   this, SLOT(sltStartServiceConnectionMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigBondingReplyMethodCallStatus(int, int)),                             this, SLOT(sltBondingReplyMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigDeleteDeviceMethodCallStatus(int, int)),                             this, SLOT(sltDeleteDeviceMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigDeleteAllDevicesMethodCallStatus(int, int)),                         this, SLOT(sltDeleteAllDevicesMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigStartAllServiceDisconnectionMethodCallStatus(int, int)),             this, SLOT(sltStartAllServiceDisconnectionMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigStartServiceDisconnectionMethodCallStatus(int, int)),                this, SLOT(sltStartServiceDisconnectionMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigSetBluetoothStatusMethodCallStatus(int, int)),                       this, SLOT(sltSetBluetoothMethodStatusCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhConnMgrEventProvider, SIGNAL(sigUpdateOldestConnetedDeviceInfo(const QString &, const QString &)),   this, SLOT(sltUpdateOldestConnectedDeviceInfo(const QString &, const QString &)), Qt::QueuedConnection);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Phone connection manager resource not created");
    }
}

void CPhoneEventHandler::disconnectConnectionManagerSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneConnectionManagerResourceImpl* pPhConnMgrResource = dynamic_cast<CPhoneConnectionManagerResourceImpl*>(ResourceFactory::getPhoneConnectionManagerResource());

    if(pPhConnMgrResource)
    {
        CPhoneConnectionManagerEventProvider* pPhConnMgrEventProvider = pPhConnMgrResource->getPhoneConnectionManagerEventProvider();
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigUpdateBluetoothStatus(bool)),                            this, SLOT(sltUpdateBluetoothStatus(bool)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigUpdatePassKey(const string&)),                           this, SLOT(sltUpdatePassKey(const string&)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigUpdateDeviceSearchStatus(bool)),                         this, SLOT(sltUpdateDeviceSearchStatus(bool)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigUpdateDiscoverableStatus(bool)),                         this, SLOT(sltUpdateDiscoverableStatus(bool)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigDeviceSearchResultReceived()),                           this, SLOT(sltDeviceSearchResultReceived()));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigBondedDeviceListReceived()),                             this, SLOT(sltBondedDeviceListReceived()));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigBondingStatusReceived()),                                this, SLOT(sltBondingStatusReceived()));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigBondingRequestReceived()),                               this, SLOT(sltBondingRequestReceived()));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigServiceConnectionStatusReceived()),                      this, SLOT(sltServiceConnectionStatusReceived()));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigDeviceDeletedReceived()),                                this, SLOT(sltDeviceDeletedReceived()));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigSetDiscoverableModeMethodCallStatus(int, int)),          this, SLOT(sltSetDiscoverableModeMethodCallStatus(int, int)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigStartDeviceSearchMethodCallStatus(int, int)),            this, SLOT(sltStartDeviceSearchMethodCallStatus(int, int)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigStopDeviceSearchMethodCallStatus(int, int)),             this, SLOT(sltStopDeviceSearchMethodCallStatus(int, int)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigStartAllServiceConnectionMethodCallStatus(int, int)),    this, SLOT(sltStartAllServiceConnectionMethodCallStatus(int, int)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigStartServiceConnectionMethodCallStatus(int, int)),       this, SLOT(sltStartServiceConnectionMethodCallStatus(int, int)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigBondingReplyMethodCallStatus(int, int)),                 this, SLOT(sltBondingReplyMethodCallStatus(int, int)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigDeleteDeviceMethodCallStatus(int, int)),                 this, SLOT(sltDeleteDeviceMethodCallStatus(int, int)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigDeleteAllDevicesMethodCallStatus(int, int)),             this, SLOT(sltDeleteAllDevicesMethodCallStatus(int, int)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigStartAllServiceDisconnectionMethodCallStatus(int, int)), this, SLOT(sltStartAllServiceDisconnectionMethodCallStatus(int, int)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigStartServiceDisconnectionMethodCallStatus(int, int)),    this, SLOT(sltStartServiceDisconnectionMethodCallStatus(int, int)));
        disconnect(pPhConnMgrEventProvider, SIGNAL(sigSetBluetoothStatusMethodCallStatus(int, int)),           this, SLOT(sltSetBluetoothMethodStatusCallStatus(int, int)));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Phone connection manager resource not created");
    }
}

void CPhoneEventHandler::connectCallManagerSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneCallManagerResourceImpl* pPhCallMgrResource = dynamic_cast<CPhoneCallManagerResourceImpl*>(ResourceFactory::getPhoneCallManagerResource());

    if(pPhCallMgrResource)
    {
        CPhoneCallManagerEventProvider* pPhCallMgrEventProvider = pPhCallMgrResource->getPhoneCallManagerEventProvider();
        connect(pPhCallMgrEventProvider, SIGNAL(sigCallStateInfoReceived()),                            this, SLOT(sltCallStateInfoReceived()));
        connect(pPhCallMgrEventProvider, SIGNAL(sigHfFeaturesListReceived()),                           this, SLOT(sltHfFeaturesListReceived()));
        connect(pPhCallMgrEventProvider, SIGNAL(sigOperatorInfoListReceived()),                         this, SLOT(sltOperatorInfoListReceived()));
        connect(pPhCallMgrEventProvider, SIGNAL(sigRssiChargeInfoListReceived()),                       this, SLOT(sltRssiChargeInfoListReceived()));
        connect(pPhCallMgrEventProvider, SIGNAL(sigHfModeStatusReceived()),                             this, SLOT(sltHfModeStatusReceived()));
        connect(pPhCallMgrEventProvider, SIGNAL(sigCallDurationReceived()),                             this, SLOT(sltCallDurationReceived()));
        connect(pPhCallMgrEventProvider, SIGNAL(sigPhoneBtVrModeStatusReceived()),                      this, SLOT(sltPhoneBtVrModeStatusReceived()));
        connect(pPhCallMgrEventProvider, SIGNAL(sigAcceptIncomingCallAsyncMethodCallStatus(int, int)),  this, SLOT(sltAcceptIncomingCallAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigRejectIncomingCallAsyncMethodCallStatus(int, int)),  this, SLOT(sltRejectIncomingCallAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigDialAsyncMethodCallStatus(int, int)),                this, SLOT(sltDialAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigConferenceCallAsyncMethodCallStatus(int, int)),      this, SLOT(sltConferenceCallAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigSwapCallsAsyncMethodCallStatus(int, int)),           this, SLOT(sltSwapCallsAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigResumeHeldCallAsyncMethodCallStatus(int, int)),      this, SLOT(sltResumeHeldCallAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigHoldActiveCallAsyncMethodCallStatus(int, int)),      this, SLOT(sltHoldActiveCallAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigEndCallAsyncMethodCallStatus(int, int)),             this, SLOT(sltEndCallAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigEndActiveCallAsyncMethodCallStatus(int, int)),       this, SLOT(sltEndActiveCallAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigEndAllCallsAsyncMethodCallStatus(int, int)),         this, SLOT(sltEndAllCallsAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigSendDtmfToneAsyncMethodCallStatus(int, int)),        this, SLOT(sltSendDtmfToneAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigSetHfModeAsyncMethodCallStatus(int, int)),           this, SLOT(sltSetHfModeAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
        connect(pPhCallMgrEventProvider, SIGNAL(sigSetVrModeAsyncMethodCallStatus(int,int)),            this, SLOT(sltSetVRModeAsyncMethodCallStatus(int, int)), Qt::QueuedConnection);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Phone call manager resource not created");
    }
}

void CPhoneEventHandler::disconnectCallManagerSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneCallManagerResourceImpl* pPhCallMgrResource = dynamic_cast<CPhoneCallManagerResourceImpl*>(ResourceFactory::getPhoneCallManagerResource());

    if(pPhCallMgrResource)
    {
        CPhoneCallManagerEventProvider* pPhCallMgrEventProvider = pPhCallMgrResource->getPhoneCallManagerEventProvider();
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigCallStateInfoReceived()),                            this, SLOT(sltCallStateInfoReceived()));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigHfFeaturesListReceived()),                           this, SLOT(sltHfFeaturesListReceived()));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigOperatorInfoListReceived()),                         this, SLOT(sltOperatorInfoListReceived()));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigRssiChargeInfoListReceived()),                       this, SLOT(sltRssiChargeInfoListReceived()));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigHfModeStatusReceived()),                             this, SLOT(sltHfModeStatusReceived()));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigCallDurationReceived()),                             this, SLOT(sltCallDurationReceived()));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigPhoneBtVrModeStatusReceived()),                      this, SLOT(sltPhoneBtVrModeStatusReceived()));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigAcceptIncomingCallAsyncMethodCallStatus(int, int)),  this, SLOT(sltAcceptIncomingCallAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigRejectIncomingCallAsyncMethodCallStatus(int, int)),  this, SLOT(sltRejectIncomingCallAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigDialAsyncMethodCallStatus(int, int)),                this, SLOT(sltDialAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigConferenceCallAsyncMethodCallStatus(int, int)),      this, SLOT(sltConferenceCallAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigSwapCallsAsyncMethodCallStatus(int, int)),           this, SLOT(sltSwapCallsAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigResumeHeldCallAsyncMethodCallStatus(int, int)),      this, SLOT(sltResumeHeldCallAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigHoldActiveCallAsyncMethodCallStatus(int, int)),      this, SLOT(sltHoldActiveCallAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigEndCallAsyncMethodCallStatus(int, int)),             this, SLOT(sltEndCallAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigEndActiveCallAsyncMethodCallStatus(int, int)),       this, SLOT(sltEndActiveCallAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigEndAllCallsAsyncMethodCallStatus(int, int)),         this, SLOT(sltEndAllCallsAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigSendDtmfToneAsyncMethodCallStatus(int, int)),        this, SLOT(sltSendDtmfToneAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigSetHfModeAsyncMethodCallStatus(int, int)),           this, SLOT(sltSetHfModeAsyncMethodCallStatus(int, int)));
        disconnect(pPhCallMgrEventProvider, SIGNAL(sigSetVrModeAsyncMethodCallStatus(int,int)),            this, SLOT(sltSetVRModeAsyncMethodCallStatus(int, int)));

    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Phone call manager resource not created");
    }
}

void CPhoneEventHandler::connectPimDbSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhonePIMDBResourceImpl* pPhPimDbResource = dynamic_cast<CPhonePIMDBResourceImpl*>(ResourceFactory::getPhonePIMDBResource());

    if(pPhPimDbResource)
    {
        CPhonePIMDBEventProvider* pPhPimDbEventProvider = pPhPimDbResource->getPhonePimDbEventProvider();
        connect(pPhPimDbEventProvider, SIGNAL(sigCallLogStatusChanged(int)),                          this, SLOT(sltCallLogStatusChanged(int)), Qt::QueuedConnection);
        connect(pPhPimDbEventProvider, SIGNAL(sigSessionClosedSelectiveEvent()),                      this, SLOT(sltPimDbSessionClosedSelectiveEvent()), Qt::QueuedConnection);
		connect(pPhPimDbEventProvider, SIGNAL(sigPimDbServiceAvailableStatusChanged(bool)),           this, SLOT(sltPimDbServiceAvailableStatusChanged(bool)), Qt::QueuedConnection);
        connect(pPhPimDbEventProvider, SIGNAL(sigContactStatusChanged(int)),                          this, SLOT(sltContactStatusChanged(int)), Qt::QueuedConnection);
        connect(pPhPimDbEventProvider, SIGNAL(sigContactDetailStatusChanged(int)),                    this, SLOT(sltContactDetailStatusChanged(int)), Qt::QueuedConnection);
        connect(pPhPimDbEventProvider, SIGNAL(sigFavoriteStatusChanged(int)),                         this, SLOT(sltFavoriteStatusChanged(int)), Qt::QueuedConnection);
        connect(pPhPimDbEventProvider, SIGNAL(sigFrequenltDialedStatusChanged(int)),                  this, SLOT(sltFrequentlyDialedStatusChanged(int)), Qt::QueuedConnection);
        connect(pPhPimDbEventProvider, SIGNAL(sigCallLogUpdated()),                                   this, SLOT(sltCallLogUpdated()));
        connect(pPhPimDbEventProvider, SIGNAL(sigContactUpdated(unsigned short)),                     this, SLOT(sltContactUpdated(unsigned short)));
        connect(pPhPimDbEventProvider, SIGNAL(sigContactDetailUpdated()),                             this, SLOT(sltContactDetailUpdated()));
        connect(pPhPimDbEventProvider, SIGNAL(sigFavoriteUpdated()),                                  this, SLOT(sltFavoriteUpdated()));
        connect(pPhPimDbEventProvider, SIGNAL(sigFrequentlyDialedListUpdated()),                      this, SLOT(sltFrequentlyDialedListUpdated()));
        connect(pPhPimDbEventProvider, SIGNAL(sigMessageNotificationEvent()),                         this, SLOT(sltMessageNotificationEvent()));
        connect(pPhPimDbEventProvider, SIGNAL(sigIsSendingSMSAllowedAttributeChanged(bool)),          this, SLOT(sltIsSendingSMSAllowedPermissionChanged(bool)), Qt::QueuedConnection);
        connect(pPhPimDbEventProvider, SIGNAL(sigAddContactToFavouriteComplete(bool)),                this, SLOT(sltAddContactToFavouriteComplete(bool)), Qt::QueuedConnection);
        connect(pPhPimDbEventProvider, SIGNAL(sigRemoveContactFromFavouriteComplete(bool)),           this, SLOT(sltRemoveContactFromFavouriteComplete(bool)), Qt::QueuedConnection);
        connect(pPhPimDbEventProvider, SIGNAL(sigSendSMSAsyncMethodCallStatus(bool)),                 this, SLOT(sltSendSMSAsyncMethodCallStatus(bool)), Qt::QueuedConnection);
        connect(pPhPimDbEventProvider, SIGNAL(sigUnreadMissedCallEvent()),                            this, SLOT(sltUnreadMissedCallEvent()));
        connect(pPhPimDbEventProvider, SIGNAL(sigGetSmsSupportedFeature()),                           this, SLOT(sltGetSmsSupportedFeatureEvent()));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
    }
}

void CPhoneEventHandler::disconnectPimDbSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhonePIMDBResourceImpl* pPhPimDbResource = dynamic_cast<CPhonePIMDBResourceImpl*>(ResourceFactory::getPhonePIMDBResource());

    if(pPhPimDbResource)
    {
        CPhonePIMDBEventProvider* pPhPimDbEventProvider = pPhPimDbResource->getPhonePimDbEventProvider();
		disconnect(pPhPimDbEventProvider, SIGNAL(sigPimDbServiceAvailableStatusChanged(bool)),           this, SLOT(sltPimDbServiceAvailableStatusChanged(bool)));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigCallLogStatusChanged(int)),                          this, SLOT(sltCallLogStatusChanged(int)));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigContactStatusChanged(int)),                          this, SLOT(sltContactStatusChanged(int)));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigContactDetailStatusChanged(int)),                    this, SLOT(sltContactDetailStatusChanged(int)));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigFavoriteStatusChanged(int)),                         this, SLOT(sltFavoriteStatusChanged(int)));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigCallLogUpdated()),                                   this, SLOT(sltCallLogUpdated()));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigContactUpdated(unsigned short)),                     this, SLOT(sltContactUpdated(unsigned short)));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigContactDetailUpdated()),                             this, SLOT(sltContactDetailUpdated()));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigFavoriteUpdated()),                                  this, SLOT(sltFavoriteUpdated()));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigMessageNotificationEvent()),                         this, SLOT(sltMessageNotificationEvent()));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigIsSendingSMSAllowedAttributeChanged(bool)),          this, SLOT(sltIsSendingSMSAllowedPermissionChanged(bool)));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigAddContactToFavouriteComplete(bool)),                this, SLOT(sltAddContactToFavouriteComplete(bool)));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigRemoveContactFromFavouriteComplete(bool)),           this, SLOT(sltRemoveContactFromFavouriteComplete(bool)));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigSendSMSAsyncMethodCallStatus(bool)),                 this, SLOT(sltSendSMSAsyncMethodCallStatus(bool)));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigUnreadMissedCallEvent()),                            this, SLOT(sltUnreadMissedCallEvent()));
        disconnect(pPhPimDbEventProvider, SIGNAL(sigGetSmsSupportedFeature()),                            this, SLOT(sltGetSmsSupportedFeatureEvent()));

    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "PimDb resource object not created");
    }
}

void CPhoneEventHandler::connectBtPluginSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CBtPluginResourceImpl* pBtPluginResource = dynamic_cast<CBtPluginResourceImpl*>(ResourceFactory::getBtPluginResource());

    if(pBtPluginResource)
    {
        CBtPluginEventProvider* pBtPluginEventProvider = pBtPluginResource->getBtPluginEventProvider();
        connect(pBtPluginEventProvider, SIGNAL(sigTTSPlayStateStatus(int)), this, SLOT(sltTTSPlayStateStatus(int)), Qt::QueuedConnection);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Bt plugin resource object not created");
    }
}

void CPhoneEventHandler::disconnectBtPluginSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CBtPluginResourceImpl* pBtPluginResource = dynamic_cast<CBtPluginResourceImpl*>(ResourceFactory::getBtPluginResource());

    if(pBtPluginResource)
    {
        CBtPluginEventProvider* pBtPluginEventProvider = pBtPluginResource->getBtPluginEventProvider();
        disconnect(pBtPluginEventProvider, SIGNAL(sigTTSPlayStateStatus(int)), this, SLOT(sltTTSPlayStateStatus(int)));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "Bt plugin resource object not created");
    }
}


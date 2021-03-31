/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneConnectionManagerDataEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CPhoneConnectionManagerDataEventProvider class
 */

#include "CPhoneConnectionManagerEventProvider.h"
#include "logging.h"

/* TODO: Create different methods for each response received from proxy for the proxy API's invoked,
 * currently only one method is created to update application layer. This will not work.
 */

CPhoneConnectionManagerEventProvider::CPhoneConnectionManagerEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
}

CPhoneConnectionManagerEventProvider::~CPhoneConnectionManagerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
}

/************************************************************************//**
 * @category    METHODS
 ************************************************************************/
void CPhoneConnectionManagerEventProvider::updateBluetoothStatus(bool bIsBtAvailable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigUpdateBluetoothStatus(bIsBtAvailable);
}

void CPhoneConnectionManagerEventProvider::updatePassKey(const string& strPassKey)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigUpdatePassKey(strPassKey);
}

void CPhoneConnectionManagerEventProvider::updateDeviceSearchStatus(bool bDeviceSearchStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigUpdateDeviceSearchStatus(bDeviceSearchStatus);
}

void CPhoneConnectionManagerEventProvider::updateDiscoverableStatus(bool bDiscoverableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigUpdateDiscoverableStatus(bDiscoverableStatus);
}

void CPhoneConnectionManagerEventProvider::deviceSearchResultReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigDeviceSearchResultReceived();
}

void CPhoneConnectionManagerEventProvider::bondedDeviceListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigBondedDeviceListReceived();
}

void CPhoneConnectionManagerEventProvider::connectedDeviceListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigConnectedDeviceListReceived();
}

void CPhoneConnectionManagerEventProvider::bondingStatusReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigBondingStatusReceived();
}

void CPhoneConnectionManagerEventProvider::bondingRequestReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigBondingRequestReceived();
}

void CPhoneConnectionManagerEventProvider::serviceConnectionStatusReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigServiceConnectionStatusReceived();
}

void CPhoneConnectionManagerEventProvider::deviceDeletedReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigDeviceDeletedReceived();
}

void CPhoneConnectionManagerEventProvider::setDiscoverableModeMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                               EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSetDiscoverableModeMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::startDeviceSearchMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                             EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigStartDeviceSearchMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::stopDeviceSearchMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                            EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigStopDeviceSearchMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::startAllServiceConnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                                     EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigStartAllServiceConnectionMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::startServiceConnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                                  EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigStartServiceConnectionMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::bondingReplyMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                        EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigBondingReplyMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::deleteDeviceMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                        EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigDeleteDeviceMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::deleteAllDevicesMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                            EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigDeleteAllDevicesMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::startAllServiceDisconnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                                        EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigStartAllServiceDisconnectionMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::startServiceDisconnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                                     EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigStartServiceDisconnectionMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::setBluetoothStatusMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                              EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSetBluetoothStatusMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneConnectionManagerEventProvider::updateOldestConnectedtDeviceInfo(string strDeviceName, string strDeviceAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigUpdateOldestConnetedDeviceInfo(QString::fromStdString(strDeviceName), QString::fromStdString(strDeviceAddress));
}

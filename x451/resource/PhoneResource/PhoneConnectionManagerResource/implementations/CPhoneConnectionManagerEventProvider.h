/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneConnectionManagerEventProvider.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPhoneConnectionManagerEventProvider class that shall publish events
 * whenever HMI PhoneConnectionManagerResource layer receive some response or callbacks from BtResource proxy.
 */

#ifndef CPHONECONNECTIONMANAGEREVENTPROVIDER_H
#define CPHONECONNECTIONMANAGEREVENTPROVIDER_H

#include <QObject>
#include <string>
#include "PhoneResource/CPhoneResourceEnums.h"
using namespace std;

/*!
 * @class CPhoneConnectionManagerDataEventProvider
 * @brief This class shall publish events whenever HMI PhoneConnectionManagerResource layer receive
 * some response or callbacks from BtResource proxy.
 */
class CPhoneConnectionManagerEventProvider: public QObject
{
    Q_OBJECT

public:
    CPhoneConnectionManagerEventProvider(QObject* pParent = 0);
    ~CPhoneConnectionManagerEventProvider();

signals:
    /******************************************************//**
     * @category SIGNALS
     * @brief Signals that shall be emitted to the application layer
     *******************************************************/

    /*!
     * @brief   Signal that shall be emited to notify updated bluetooth status.
     * @param   bIsBtAvailable - status of the bluetooth whether enable or not.
     * @return  void.
     */
    void sigUpdateBluetoothStatus(bool bIsBtAvailable);

    /*!
     * @brief   Signal that shall be emited to notify updated passkey.
     * @param   strPassKey - passkey generated at time of pairing with a new device.
     * @return  void.
     */
    void sigUpdatePassKey(const string &strPassKey);

    /*!
     * @brief   Signal that shall be emited to notify updated device search status.
     * @param   bDeviceSearchStatus - Device search status whether started or stopped.
     * @return  void.
     */
    void sigUpdateDeviceSearchStatus(bool bDeviceSearchStatus);

    /*!
     * @brief   Signal that shall be emited to notify updated HU discoverable status.
     * @param   bDiscoverableStatus - HU discoverable status whether discoverable or not.
     * @return  void.
     */
    void sigUpdateDiscoverableStatus(bool bDiscoverableStatus);

    /*!
     * @brief   Signal that shall be emited to notify device search result is received.
     * @param   void.
     * @return  void.
     */
    void sigDeviceSearchResultReceived();

    /*!
     * @brief   Signal that shall be emited to notify bonded device list is received.
     * @param   void.
     * @return  void.
     */
    void sigBondedDeviceListReceived();

    /*!
     * @brief   sigConnectedDeviceListReceived: Signal that shall be emited to notify connected
     *          device list is received.
     * @param   void.
     * @return  void.
     */
    void sigConnectedDeviceListReceived();

    /*!
     * @brief   Signal that shall be emited to notify bonding status is received.
     * @param   void.
     * @return  void.
     */
    void sigBondingStatusReceived();

    /*!
     * @brief   Signal that shall be emited to notify bonding request is received.
     * @param   void.
     * @return  void.
     */
    void sigBondingRequestReceived();

    /*!
     * @brief   Signal that shall be emited to notify service connection status is received.
     * @param   void.
     * @return  void.
     */
    void sigServiceConnectionStatusReceived();

    /*!
     * @brief   Signal that shall be emited to notify device deleted is received.
     * @param   void.
     * @return  void.
     */
    void sigDeviceDeletedReceived();

    /*!
     * @brief   Signal that shall be emited to notify setDiscoverableMode method call
     *          status is received.
     * @param   void.
     * @return  void.
     */
    void sigSetDiscoverableModeMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   Signal that shall be emited to notify startDeviceSearch method call
     *          status is received.
     * @param   iMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void sigStartDeviceSearchMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   Signal that shall be emited to notify stopDeviceSearch method call
     *          status is received.
     * @param   iMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void sigStopDeviceSearchMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   Signal that shall be emited to notify startAllServiceConnection method call
     *          status is received.
     * @param   iMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void sigStartAllServiceConnectionMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   Signal that shall be emited to notify startServiceConnection method call
     *          status is received.
     * @param   iMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void sigStartServiceConnectionMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   Signal that shall be emited to notify bondingReply method call
     *          status is received.
     * @param   iMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void sigBondingReplyMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   Signal that shall be emited to notify deleteDevice method call
     *          status is received.
     * @param   iMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void sigDeleteDeviceMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   Signal that shall be emited to notify deleteAllDevices method call
     *          status is received.
     * @param   iMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void sigDeleteAllDevicesMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   Signal that shall be emited to notify startAllServiceDisconnection method call
     *          status is received.
     * @param   iMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void sigStartAllServiceDisconnectionMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   Signal that shall be emited to notify startServiceDisconnection method call
     *          status is received.
     * @param   iMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void sigStartServiceDisconnectionMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   Signal that shall be emited to notify setBluetooth method call
     *          status is received.
     * @param   iMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void sigSetBluetoothStatusMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /**
     * @brief   sigUpdateOldestConnetedDeviceInfo: Signal that shall be emitted to notify Oldest
     *          Connected device info to Phone adaptor.
     * @param   strDeviceName: Device name.
     * @param   strDeviceAddress: Device address.
     * @return  void.
     */
    void sigUpdateOldestConnetedDeviceInfo(const QString &strDeviceName, const QString &strDeviceAddress);


public:
    /************************************************************************//**
     * @category    METHODS
     * @brief       Methods that would be used by the PhoneConnectionManagerResource
     * layer to indirectly emit signals to the phone application layer
     ************************************************************************/

    /*!
     * @brief   Method to inform phone application layer regarding the availability of bluetooth.
     * @param   bIsBtAvailable - status of the bluetooth whether enable or not.
     * @return  void.
     */
    void updateBluetoothStatus(bool bIsBtAvailable);

    /*!
     * @brief   Method to inform phone application layer regarding updated passkey.
     * @param   strPassKey - passkey generated at time of pairing with a new device.
     * @return  void.
     */
    void updatePassKey(const string &strPassKey);

    /*!
     * @brief   Method to inform phone application layer regarding device search status.
     * @param   bDeviceSearchStatus - Device search status whether started or stopped.
     * @return  void.
     */
    void updateDeviceSearchStatus(bool bDeviceSearchStatus);

    /*!
     * @brief   Method to inform phone application layer regarding HU discoverable status.
     * @param   bDiscoverableStatus - HU discoverable status whether discoverable or not.
     * @return  void.
     */
    void updateDiscoverableStatus(bool bDiscoverableStatus);

    /*!
     * @brief   Method to inform phone application layer regarding device search result.
     * @param   void.
     * @return  void.
     */
    void deviceSearchResultReceived();

    /*!
     * @brief   Method to inform phone application layer regarding bonded device list.
     * @param   void.
     * @return  void.
     */
    void bondedDeviceListReceived();

    /*!
     * @brief   connectedDeviceListReceived: Method to inform phone adaptor layer regarding
     *          connected device list.
     * @param   void.
     * @return  void.
     */
    void connectedDeviceListReceived();

    /*!
     * @brief   Method to inform phone application layer regarding bonding status.
     * @param   void.
     * @return  void.
     */
    void bondingStatusReceived();

    /*!
     * @brief   Method to inform phone application layer regarding bonding request.
     * @param   void.
     * @return  void.
     */
    void bondingRequestReceived();

    /*!
     * @brief   Method to inform phone application layer regarding service connection status.
     * @param   void.
     * @return  void.
     */
    void serviceConnectionStatusReceived();

    /*!
     * @brief   Method to inform phone application layer regarding device deleted.
     * @param   void.
     * @return  void.
     */
    void deviceDeletedReceived();

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of setDiscoverableMode.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void setDiscoverableModeMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                             EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of startDeviceSearch.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void startDeviceSearchMethodCallStatus(EMethodCallStatus eMethodCallStatus, EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of stopDeviceSearch.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void stopDeviceSearchMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                          EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of startAllServiceConnection.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void startAllServiceConnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                   EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of startServiceConnection.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void startServiceConnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of bondingReply.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void bondingReplyMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                      EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of deleteDevice.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void deleteDeviceMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                      EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of deleteAllDevices.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void deleteAllDevicesMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                          EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of startAllServiceDisconnection.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void startAllServiceDisconnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                      EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of startServiceDisconnection.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void startServiceDisconnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                   EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform phone application layer regarding method call status
     *          of setBluetoothStatus.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void setBluetoothStatusMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                            EMethodCallErrorType eMethodCallErrorType);

    /**
     * @brief   updateOldestConnectedtDeviceInfo: Method to inform phone application
     *          layer for Oldest Connected device information.
     * @param   strDeviceName: Device name.
     * @param   strDeviceAddress: Device Address.
     */
    void updateOldestConnectedtDeviceInfo(string strDeviceName, string strDeviceAddress);
};

#endif // CPHONECONNECTIONMANAGEREVENTPROVIDER_H

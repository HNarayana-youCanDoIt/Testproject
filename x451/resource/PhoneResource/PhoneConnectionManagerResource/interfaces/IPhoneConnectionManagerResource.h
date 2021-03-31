/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          IPhoneConnectionManagerResource.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains IPhoneConnectionManagerResource interface that provides abstract methods to communicate
 * with the ConnectionManager proxy directly which shall be implemented by resource implementation class.
 */

#ifndef PHONECONNECTIONMANAGERRESOURCE_H
#define PHONECONNECTIONMANAGERRESOURCE_H

#include <string>
#include <vector>

//!Include the headers related to ConnectionManagerPresCtrl
#include "v7/com/harman/btpres/BTPresTypes.hpp"
#include "v2/com/harman/btpres/ConnectionManagerProxy.hpp"
#include "PhoneResource/CPhoneResourceEnums.h"

using namespace v2::com::harman::btpres;
using namespace v7::com::harman::btpres;
using namespace std;

/*!
 * @interface IPhoneConnectionManagerResource
 * @brief This interfaces provides abstract methods to communicate with the
 * ConnectionManager proxy directly which shall be implemented by resource
 * implementation class.
 */
class IPhoneConnectionManagerResource
{
public:
    virtual ~IPhoneConnectionManagerResource(){}

    /********************************************//**
     * @category REQUEST METHODS
     ************************************************/

    /*!
     * @brief   Method to inform connection manager proxy to enable (or) disable
     *          discoverable mode.
     * @param   bEnable - value can be true(enable) or false(disable).
     * @return  void.
     */
    virtual void setDiscoverableModeAsyncReq(bool bEnable) = 0;

    /*!
     * @brief   Method to inform connection manager proxy to start device search.
     * @param   void.
     * @return  void.
     */
    virtual void startDeviceSearchAsyncReq() = 0;

    /*!
     * @brief   Method to inform connection manager proxy to stop device search.
     * @param   void.
     * @return  void.
     */
    virtual void stopDeviceSearchAsyncReq() = 0;

    /*!
     * @brief   Method to inform connection manager proxy to start service connection
     *          of all supported profiles for a device.
     * @param   strBtAddr - bt address of the device for which service connection
     *                      needs to be started.
     * @return  void.
     */
    virtual void startAllServiceConnectionAsyncReq(string strBtAddr) = 0;

    /*!
     * @brief   Method to inform connection manager proxy to start service connection
     *          of a specific profile for a device.
     * @param   strBtAddr - bt address of the device.
     * @param   eProfileType - profile for which service connection needs to be started.
     * @return  void.
     */
    virtual void startServiceConnectionAsyncReq(string strBtAddr, ESupportedProfile eProfileType) = 0;

    /*!
     * @brief   Method to inform connection manager proxy to start (or) stop bonding process.
     * @param   strBtAddr - bt address of the device.
     * @param   bAccepted - authentication request accepted or declined.
     * @param   bSecureBonding - secure bonding or not, true(secure) or false(standard).
     * @return  void.
     */
    virtual void bondingReplyAsyncReq(string strBtAddr, bool bAccepted, bool bSecureBonding) = 0;

    /*!
     * @brief   Method to inform connection manager proxy to delete the paired device.
     * @param   strBtAddr - bt address of the device.
     * @return  void.
     */
    virtual void deleteDeviceAsyncReq(string strBtAddr) = 0;

    /*!
     * @brief   Method to inform connection manager proxy to delete all the paired devices.
     * @param   void.
     * @return  void.
     */
    virtual void deleteAllDevicesAsyncReq() = 0;

    /*!
     * @brief   Method to inform connection manager proxy to start service disconnection
     *          of all supported profiles for a device.
     * @param   strBtAddr - bt address of the device for which service disconnection
     *                      needs to be started.
     * @return  void.
     */
    virtual void startAllServiceDisconnectionAsyncReq(string strBtAddr) = 0;

    /*!
     * @brief   Method to inform connection manager proxy to start service disconnection
     *          of a specific profile for a device.
     * @param   strBtAddr - bt address of the device.
     * @param   eProfileType - profile for which service disconnection needs to be started.
     * @return  void.
     */
    virtual void startServiceDisconnectionAsyncReq(string strBtAddr, ESupportedProfile eProfileType) = 0;

    /*!
     * @brief   Method to inform connection manager proxy to enable or disable bluetooth
     * @param   bEnable - value can be true(enable) or false(disable).
     * @return  void.
     */
    virtual void setBluetoothStatusAsyncReq(bool bEnable) = 0;

    /**
     * @brief   getOldestConnectedDeviceAsyncReq: This function is used to get the
     *          oldest connected device information from connection manager pres.
     * @param   void.
     * @return  void.
     */
    virtual void getOldestConnectedDeviceAsyncReq() = 0;

private:
    /********************************************//**
     * @category CALLBACK METHODS
     ************************************************/

    /*!
     * @brief   Callback to get notified about the avalability status of the ConnectionManager proxy.
     * @param   eStatus - status of ConnectionManager proxy whether available or not.
     * @return  void.
     */
    virtual void connectionManagerStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;

    /*!
     * @brief   Callback to get notified about the current status of bluetooth.
     * @param   eStatus - status of the bluetooth whether on or off.
     * @return  void.
     */
    virtual void bluetoothStatusCb(BTPresTypes::eBluetoothStatus eStatus) = 0;

    /*!
     * @brief   Callback to get notified about the generated passkey at time of external pairing with a new device.
     * @param   strPassKey - passkey generated at time of pairing with a new device.
     * @return  void.
     */
    virtual void passKeyPinCb(string strPassKey) = 0;

    /*!
     * @brief   Callback to get notified about the status of device search.
     * @param   bDeviceSearchStatus - Device search status whether started or stopped.
     * @return  void.
     */
    virtual void deviceSearchStatusCB(bool bDeviceSearchStatus) = 0;

    /*!
     * @brief   Callback to get notified about HU discoverable status.
     * @param   bDiscoverableStatus - HU discoverable status whether discoverable or not.
     * @return  void.
     */
    virtual void discoverableStatusCb(bool bDiscoverableStatus) = 0;

    /*!
     * @brief   Callback to get notified about the list of devices while device search is in progress.
     * @param   vectSearchedDevices - vector of devices found while search is ongoing.
     * @return  void.
     */
    virtual void deviceSearchResultCb(BTPresTypes::tDeviceSearchEntryList vectSearchedDevices) = 0;

    /*!
     * @brief   bondedDeviceListCb: Callback to get notified about the bonded device list.
     * @param   vectBondedDeviceList - vector of devices paired to HU.
     * @return  void.
     */
    virtual void bondedDeviceListCb(BTPresTypes::bondedDevList vectBondedDeviceList) = 0;

    /*!
     * @brief   connectedDeviceListCb: Callback to get notified about the connected device list.
     * @param   vectConnectedDeviceList: vector of devices connected to HU.
     * @return  void.
     */
    virtual void connectedDeviceListCb(BTPresTypes::bondedDevList vectConnectedDeviceList) = 0;

    /*!
     * @brief   Callback to get notified about the pairing status of the device.
     * @param   strBtAddr         - bt address of the device.
     * @param   strDeviceName     - name of the device.
     * @param   ePairingStatus    - pairing status whether successful or failure.
     * @return  void.
     */
    virtual void bondingStatusCb(string strBtAddr, string strDeviceName, BTPresTypes::ePairingStatus ePairingStatus) = 0;

    /*!
     * @brief   Callback to get notified about the bonding request at time of paring initiated from HU for a new device.
     * @param   strBtAddr         - bt address of the device.
     * @param   strDeviceName     - name of the device.
     * @param   eBondingType      - bonding type.
     * @param   strPin            - passkey pin
     * @return  void.
     */
    virtual void bondingRequestCb(string strBtAddr, string strDeviceName, BTPresTypes::eBondingType eBondingType, string strPin) = 0;

    /*!
     * @brief   Callback to get notified about the connection status of a device whether connected or disconnected.
     * @param   strBtAddr                         - bt address of the device.
     * @param   strDeviceName                     - name of the device.
     * @param   eSupportedProfile                 - supported profile list by the device.
     * @param   eConnectionStatus                 - connection status of the device whether connected or disconnected.
     * @param   eServiceConnectDisconnectReason   - reason for connection or disconnection.
     * @return  void.
     */
    virtual void serviceConnectionStatusCb(string strBtAddr, string strDeviceName, BTPresTypes::eSupportedProfile eSupportedProfile,
                                             BTPresTypes::eConnectionStatus eConnectionStatus,
                                             BTPresTypes::eServiceConnectDisconnectReason eServiceConnectDisconnectReason) = 0;

    /*!
     * @brief   Callback to get notified whenever any device gets deleted or unpaired externally.
     * @param   strBtAddr             - bt address of the device.
     * @param   strDeviceName         - name of the device.
     * @param   eDeviceDeleteReason   - reason for device deletion i.e. deletion due to missing key (or)
     *                                deletion due to user action.
     * @return  void.
     */
    virtual void deviceDeletedCb(string strBtAddr, string strDeviceName, BTPresTypes::eDeviceDeletedReason eDeviceDeleteReason) = 0;

    /********************************************//**
     * @category RESPONSE CALLBACK METHODS
     ************************************************/

    /*!
     * @brief   Callback to get notified about setDiscoverableModeAsync method response.
     * @param   eCallStatus   - call status of the setDiscoverableModeAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking setDiscoverableModeAsync method.
     * @return  void.
     */
    virtual void setDiscoverableModeAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Callback to get notified about startDeviceSearchAsync method response.
     * @param   eCallStatus   - call status of the startDeviceSearchAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking startDeviceSearchAsync method.
     * @return  void.
     */
    virtual void startDeviceSearchAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Callback to get notified about stopDeviceSearchAsync method response.
     * @param   eCallStatus   - call status of the stopDeviceSearchAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking stopDeviceSearchAsync method.
     * @return  void.
     */
    virtual void stopDeviceSearchAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Callback to get notified about startAllServiceConnectionAsync method response.
     * @param   eCallStatus   - call status of the startAllServiceConnectionAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking startAllServiceConnectionAsync method.
     * @return  void.
     */
    virtual void startAllServiceConnectionAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Callback to get notified about startServiceConnectionAsync method response.
     * @param   eCallStatus   - call status of the startServiceConnectionAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking startServiceConnectionAsync method.
     * @return  void.
     */
    virtual void startServiceConnectionAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Callback to get notified about bondingReplyAsync method response.
     * @param   eCallStatus   - call status of the bondingReplyAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking bondingReplyAsync method.
     * @return  void.
     */
    virtual void bondingReplyAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Callback to get notified about deleteDeviceAsync method response.
     * @param   eCallStatus   - call status of the deleteDeviceAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking deleteDeviceAsync method.
     * @return  void.
     */
    virtual void deleteDeviceAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Callback to get notified about deleteAllDevicesAsync method response.
     * @param   eCallStatus   - call status of the deleteAllDevicesAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking deleteAllDevicesAsync method.
     * @return  void.
     */
    virtual void deleteAllDevicesAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Callback to get notified about startAllServiceDisconnectionAsync method response.
     * @param   eCallStatus   - call status of the startAllServiceDisconnectionAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking startAllServiceDisconnectionAsync method.
     * @return  void.
     */
    virtual void startAllServiceDisconnectionAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Callback to get notified about startServiceDisconnectionAsync method response.
     * @param   eCallStatus   - call status of the startServiceDisconnectionAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking startServiceDisconnectionAsync method.
     * @return  void.
     */
    virtual void startServiceDisconnectionAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Callback to get notified about setBluetoothStatusAsync method response.
     * @param   eCallStatus   - call status of the setBluetoothStatusAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking setBluetoothStatusAsync method.
     * @return  void.
     */
    virtual void setBluetoothStatusAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /**
     * @brief   getOldestConnectedDeviceAsyncCb: Callback to get notified about
     *          getOldestConnectedDeviceAsync method response.
     * @param   eCallStatus   - call status of the getOldestConnectedDeviceAsync method, whether success or not.
     * @param   eErrorType    - type of the error received after invoking getOldestConnectedDeviceAsync method.
     * @param   objDeviceInfo - object of deviceInfo structure, it contains name and bt address of the oldest device connected.
     */
    virtual void getOldestConnectedDeviceAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType,
                                                 const BTPresTypes::deviceInfo& objDeviceInfo) = 0;
};
#endif // PHONECONNECTIONMANAGERRESOURCE_H

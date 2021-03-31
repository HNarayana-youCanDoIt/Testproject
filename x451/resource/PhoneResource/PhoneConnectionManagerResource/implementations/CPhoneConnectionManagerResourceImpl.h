/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneConnectionManagerResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPhoneConnectionManagerResourceImpl class that shall implement the
 * PhoneConnectionManagerResource interface and is a mediator between lower layer(press control)
 * and upper layer(application).
 */

#ifndef CPHONECONNECTIONMANAGERRESOURCEIMPL_H
#define CPHONECONNECTIONMANAGERRESOURCEIMPL_H

#include <capi/CAPIClientAbstraction.hpp>
#include "interfaces/IPhoneConnectionManagerResource.h"
#include "PhoneResource/CPhoneResourceData.h"
#include "CPhoneConnectionManagerEventProvider.h"

/*!
 * @class CPhoneConnectionManagerResourceImpl
 * @brief This is a singleton class that shall implement the PhoneConnectionManagerResource interface
 * and is a mediator between lower layer(press control) and upper layer(application).
 */

class CPhoneConnectionManagerResourceImpl: public IPhoneConnectionManagerResource
{
/********************************************//**
 * @category CONSTANTS
 ************************************************/
private:
    const uint32_t MAX_DEVICES;
    const uint32_t DEVICE_SEARCH_TIMEOUT;

/********************************************//**
 * @category METHODS
 ************************************************/
public:
    virtual ~CPhoneConnectionManagerResourceImpl();

    /*!
     * @brief   Method to get the instance of CPhoneConnectionManagerDataEventProvider class.
     * @param   void.
     * @return  pointer to the object of CPhoneConnectionManagerDataEventProvider class.
     */
    CPhoneConnectionManagerEventProvider* getPhoneConnectionManagerEventProvider();

    /******************************************************//**
     * @category    REQUEST
     * @brief       Overide the PhoneConnectionManagerResource functions
     * that shall be used by the Phone adapter layer to propagate
     * the calls.
     *******************************************************/
    void setDiscoverableModeAsyncReq(bool bEnable) override;
    void startDeviceSearchAsyncReq() override;
    void stopDeviceSearchAsyncReq() override;
    void startAllServiceConnectionAsyncReq(string strBtAddr) override;
    void startServiceConnectionAsyncReq(string strBtAddr, ESupportedProfile eProfileType) override;
    void bondingReplyAsyncReq(string strBtAddr, bool bAccepted, bool bSecureBonding) override;
    void deleteDeviceAsyncReq(string strBtAddr) override;
    void deleteAllDevicesAsyncReq() override;
    void startAllServiceDisconnectionAsyncReq(string strBtAddr) override;
    void startServiceDisconnectionAsyncReq(string strBtAddr, ESupportedProfile eProfileType) override;
    void setBluetoothStatusAsyncReq(bool bEnable) override;
    void getOldestConnectedDeviceAsyncReq() override;

    /******************************************************//**
     * @category GETTERS
     *******************************************************/

    /*!
     * @brief   Method to get Bluetooth status.
     * @param   void.
     * @return  const bool bluetooth is ON or OFF.
     */
    bool  getBluetoothStatus() { return m_bIsBtAvailable; }

    /*!
     * @brief   Method to get device search list.
     * @param   void.
     * @return  const reference vector of SDeviceInfo structure's instance.
     */
    const vector<SSearchDeviceInfo>&  getDeviceSearchList() { return m_vectDeviceSearchList; }

    /*!
     * @brief   Method to get bonded device list.
     * @param   void.
     * @return  const reference vector of SBondedDeviceInfo structure's instance.
     */
    const vector<SBondedDeviceInfo>& getBondedDeviceList(){ return m_vectBondedDeviceList; }

    /*!
     * @brief   getConnectedDeviceList: Method to get connected device list.
     * @param   void.
     * @return  const reference vector of SBondedDeviceInfo structure's instance.
     */
    const vector<SBondedDeviceInfo>& getConnectedDeviceList(){ return m_vectConnectedDeviceList; }

    /*!
     * @brief   Method to get device bonding status information.
     * @param   void.
     * @return  const reference instance of SDeviceBondingStatus structure.
     */
    const SDeviceBondingStatus& getDeviceBondingStatus(){ return m_objDeviceBondingStatus; }

    /*!
     * @brief   Method to get bonding request information.
     * @param   void.
     * @return  const reference instance of SBondingRequest structure.
     */
    const SBondingRequest& getBondingRequest(){ return m_objBondingRequest; }

    /*!
     * @brief   Method to get service connection status information.
     * @param   void.
     * @return  const reference instance of SServiceConnectionStatus structure.
     */
    const SServiceConnectionStatus& getServiceConnectionStatus(){ return m_objServiceConnectionStatus; }

    /*!
     * @brief   Method to get device deleted information.
     * @param   void.
     * @return  const reference instance of SDeviceDeleted structure.
     */
    const SDeviceDeleted& getDeviceDeleted(){ return m_objDeviceDeleted; }

private:
    /*!
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;
    CPhoneConnectionManagerResourceImpl();

    /******************************************************//**
     * @category CALLBACK
     *******************************************************/
    void connectionManagerStatusCb( CommonAPI::AvailabilityStatus eStatus ) override;
    void bluetoothStatusCb(BTPresTypes::eBluetoothStatus eStatus) override;
    void passKeyPinCb(string strPassKey) override;
    void deviceSearchStatusCB(bool bDeviceSearchStatus) override;
    void discoverableStatusCb(bool bDiscoverableStatus) override;
    void deviceSearchResultCb(BTPresTypes::tDeviceSearchEntryList vectSearchedDevices) override;
    void bondedDeviceListCb(BTPresTypes::bondedDevList vectBondedDeviceList) override;
    void connectedDeviceListCb(BTPresTypes::bondedDevList vectConnectedDeviceList) override;
    void bondingStatusCb(string strBtAddr, string strDeviceName, BTPresTypes::ePairingStatus ePairingStatus) override;
    void bondingRequestCb(string strBtAddr, string strDeviceName, BTPresTypes::eBondingType eBondingType, string strPin) override;
    void serviceConnectionStatusCb(string strBtAddr, string strDeviceName, BTPresTypes::eSupportedProfile eSupportedProfile,
                                     BTPresTypes::eConnectionStatus eConnectionStatus, BTPresTypes::eServiceConnectDisconnectReason eServiceConnectDisconnectReason) override;
    void deviceDeletedCb(string strBtAddr, string strDeviceName, BTPresTypes::eDeviceDeletedReason eDeviceDeleteReason) override;

    /********************************************//**
     * @category RESPONSE
     ************************************************/
    void setDiscoverableModeAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void startDeviceSearchAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void stopDeviceSearchAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void startAllServiceConnectionAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void startServiceConnectionAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void bondingReplyAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void deleteDeviceAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void deleteAllDevicesAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void startAllServiceDisconnectionAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void startServiceDisconnectionAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void setBluetoothStatusAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void getOldestConnectedDeviceAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType,
                                                     const BTPresTypes::deviceInfo& objDeviceInfo) override;


    /******************************************************//**
     * @category INTERNAL METHODS
     *******************************************************/
    /*!
     * @brief   Internal method to subscribe all the callback methods.
     * @param   void.
     * @return  void.
     */
    void subscribeConnectionManagerCb();

    /*!
     * @brief   Internal method to map BTPress method call status enums to connection manager resource's method
     *          call status enums. The mapped enums shall be used by the phone application layer and the class itself.
     * @param   eCallStatus - BTPress method call status enum value.
     * @return  connection manager resource's method call status enum.
     */
    EMethodCallStatus getMethodCallStatus(CallStatus eCallStatus);

    /*!
     * @brief   Internal method to map BTPress method call error type enums to connection manager resource's
     *          method call error type enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iErrorType - BTPress method call error type enum value.
     * @return  connection manager resource's method call error type enum value.
     */
    EMethodCallErrorType getMethodCallErrorType(int iErrorType);

    /*!
     * @brief   Internal method to map BTPress device class enums to connection manager resource's device class enums.
     *          The mapped enums shall be used by the phone application layer and the class itself.
     * @param   iDeviceClass - BTPress device class enum value.
     * @return  connection manager resource's device class enum value.
     */
    EDeviceClass getDeviceClass(int iDeviceClass);

    /*!
     * @brief   Internal method to map BTPress supportedprofile enums to connection manager resource's supported
     *          profile enums. The mapped enums shall be used by the phone application layer and the class itself.
     * @param   iProfile - BTPress supported profile enum value.
     * @return  connection manager resource's supported profile enum value.
     */
    ESupportedProfile getProfileType(int iProfile);

    /*!
     * @brief   Internal method to map BTPress service connection status enums to connection manager resource's
     *          service connection status enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iConnectionStatus - BTPress service connection status enum value.
     * @return  connection manager resource's service connection status enum value.
     */
    EConnectionStatus getServiceConnectionStatus(int iConnectionStatus);

    /*!
     * @brief   Internal method to map BTPress device pairing status enums to connection manager resource's
     *          device pairing status enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iStatus - BTPress device pairing status enum value.
     * @return  connection manager resource's device pairing status enum value.
     */
    EPairingStatus getDevicePairingStatus(int iStatus);

    /*!
     * @brief   Internal method to map BTPress device bonding type enums to connection manager resource's
     *          device bonding type enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iBondingType - BTPress device bonding type enum value.
     * @return  connection manager resource's device bonding type enum value.
     */
    EBondingType getDeviceBondingType(int iBondingType);

    /*!
     * @brief   Internal method to map BTPress service connect disconnect reason enums to connection manager resource's
     *          service connect disconnect reason enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iReason - BTPress service connect disconnect reason enum value.
     * @return  connection manager resource's service connect disconnect reason enum value.
     */
    EServiceConnectDisconnectReason getServiceConnectDisconnectReason(int iReason);

    /*!
     * @brief   Internal method to map BTPress device deleted reason enums to connection manager resource's device deleted
     *          reason enums. The mapped enums shall be used by the phone application layer and the class itself.
     * @param   iReason - BTPress device deleted reason enum value.
     * @return  connection manager resource's device deleted reason enum value.
     */
    EDeviceDeletedReason getDeviceDeletedReason(int iReason);

    /*!
     * @brief   Internal method to map connection manager resource's supported
     *          profile enums to BTPress supportedprofile enums. The mapped enums shall be used by the class itself.
     * @param   eProfileType - Connection manager resource's supported profile enum value.
     * @return  BTPress supported profile enum value.
     */
    BTPresTypes::eSupportedProfile getProfileType(ESupportedProfile eProfileType);

    /**
     * @brief   parseDeviceList: Method to parse device list received from bt press and store
     *          the information.
     * @param   vectDeviceList: list of devices paired/connected received from bt press.
     * @param   vectDeviceInfo: list of paired/connected device information to be stored from
     *          the data received from bt press.
     * @return  void.
     */
    void parseDeviceList(BTPresTypes::bondedDevList& vectDeviceList, vector<SBondedDeviceInfo>& vectDeviceInfo);

/******************************************************//**
 * @category PROPERTIES
 *******************************************************/
private:
    /*!
     * @brief Pointer of CPhoneConnectionManagerDataEventProvider class to
     * emit signals to the phone application layer.
     */
    CPhoneConnectionManagerEventProvider*           m_pPhoneConnMgrEventProvider;
    /*!
     * @brief Instance of ConnectionManagerProxy class to communicate with
     * bt press control layer.
     */
    CAPIClientAbstraction<ConnectionManagerProxy>   m_objConnectionManagerProxy;
    //! Flag to maintain connection manager proxy availability status
    bool                                            m_bIsConnectionManagerProxyAvailable;
    //! Flag to maintain availability status of bluetooth */
    bool                                            m_bIsBtAvailable;
    //! Contains passkey pin
    string                                          m_strPassKeyPin;
    //! Flag to maintain status of device search
    bool                                            m_bDeviceSearchStatus;
    //! Flag to main device discoverable status of HU
    bool                                            m_bHUDiscoverableStatus;
    //! List of searched devices
    vector<SSearchDeviceInfo>                       m_vectDeviceSearchList;
    //! List of paired/bonded devices
    vector<SBondedDeviceInfo>                       m_vectBondedDeviceList;
    //! List of connected devices
    vector<SBondedDeviceInfo>                       m_vectConnectedDeviceList;
    //! Data object that shall hold the data received for device bonding status
    SDeviceBondingStatus                            m_objDeviceBondingStatus;
    //! Data object that shall hold the data received for bonding request
    SBondingRequest                                 m_objBondingRequest;
    //! Data object that shall hold the data received for service connection status
    SServiceConnectionStatus                        m_objServiceConnectionStatus;
    //! Data object that shall hold the data received for device deleted
    SDeviceDeleted                                  m_objDeviceDeleted;
};

#endif // CPHONECONNECTIONMANAGERRESOURCEIMPL_H

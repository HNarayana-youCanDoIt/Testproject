/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneEventHandler.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPhoneEventHandler class that implements the slot for the signals
 * emited by phone resource layer to inform phone adaptor regarding the updates in phone resource layer.
 */

#ifndef CPHONEEVENTHANDLER_H
#define CPHONEEVENTHANDLER_H

#include <QObject>
#include <string>
#include <PhoneResource/CPhoneResourceEnums.h>

using namespace std;

/*!
 * @class CPhoneEventHandler
 * @brief This class implements the slot for the signals emited by phone resource layer to inform
 * phone adaptor regarding the updates in phone resource layer.
 */
class CPhoneEventHandler: public QObject
{
    Q_OBJECT
public:
    CPhoneEventHandler(QObject* pParent = 0);
    ~CPhoneEventHandler();

private slots:
    /******************************************************//**
     * @category    CONNECTION MANAGER SLOTS
     * @brief       Slots for the signals emitted by phone connection
     *              manager resource
     *******************************************************/

    /*!
     * @brief   sltUpdateBluetoothStatus: Method to notify phone adaptor regarding update in bluetooth
     *          status.
     * @param   bIsBtAvailable - status of the bluetooth whether enable or not.
     * @return  void.
     */
    void sltUpdateBluetoothStatus(bool bIsBtAvailable);

    /*!
     * @brief   sltUpdatePassKey: Method to notify phone adaptor regarding updated passkey.
     * @param   strPassKey - passkey generated at time of pairing with a new device.
     * @return  void.
     */
    void sltUpdatePassKey(const string &strPassKey);

    /*!
     * @brief   sltUpdateDeviceSearchStatus: Method to notify phone adaptor regarding updated device
     *          search status.
     * @param   bDeviceSearchStatus - Device search status whether started or stopped.
     * @return  void.
     */
    void sltUpdateDeviceSearchStatus(bool bDeviceSearchStatus);

    /*!
     * @brief   sltUpdateDiscoverableStatus: Method to notify phone adaptor regarding updated
     *          HU discoverable status.
     * @param   bDiscoverableStatus - HU discoverable status whether discoverable or not.
     * @return  void.
     */
    void sltUpdateDiscoverableStatus(bool bDiscoverableStatus);

    /*!
     * @brief   sltDeviceSearchResultReceived: Method to notify phone adaptor regarding device
     *          search result received.
     * @param   void.
     * @return  void.
     */
    void sltDeviceSearchResultReceived();

    /*!
     * @brief   sltBondedDeviceListReceived: Method to notify phone adaptor regarding bonded device
     *          list received.
     * @param   void.
     * @return  void.
     */
    void sltBondedDeviceListReceived();

    /*!
     * @brief   sltConnectedDeviceListReceived: Method to notify phone adaptor regarding
     *          connected device list received.
     * @param   void.
     * @return  void.
     */
    void sltConnectedDeviceListReceived();

    /*!
     * @brief   sltBondingStatusReceived: Method to notify phone adaptor regarding bonding status
     *          received.
     * @param   void.
     * @return  void.
     */
    void sltBondingStatusReceived();

    /*!
     * @brief   sltBondingRequestReceived: Method to notify phone adaptor regarding bonding request
     *          received.
     * @param   void.
     * @return  void.
     */
    void sltBondingRequestReceived();

    /*!
     * @brief   sltServiceConnectionStatusReceived: Method to notify phone adaptor regarding service
     *          connection status received.
     * @param   void.
     * @return  void.
     */
    void sltServiceConnectionStatusReceived();

    /*!
     * @brief   sltDeviceDeletedReceived: Method to notify phone adaptor regarding device deleted
     *          received.
     * @param   void.
     * @return  void.
     */
    void sltDeviceDeletedReceived();

    /*!
     * @brief   sltUpdateOldestConnectedDeviceInfo: Method to update oldest connected device info.
     * @param   strDeviceName: Device Name.
     * @param   strDeviceAddress: Device Address.
     * @return  void.
     */
    void sltUpdateOldestConnectedDeviceInfo(const QString &strDeviceName, const QString &strDeviceAddress);

    /*!
     * @brief   sltSetDiscoverableModeMethodCallStatus: Method to notify phone adaptor regarding
     *          setDiscoverableMode method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltSetDiscoverableModeMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltStartDeviceSearchMethodCallStatus: Method to notify phone adaptor regarding
     *          startDeviceSearch method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltStartDeviceSearchMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltStopDeviceSearchMethodCallStatus: Method to notify phone adaptor regarding
     *          stopDeviceSearch method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltStopDeviceSearchMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltStartAllServiceConnectionMethodCallStatus: Method to notify phone adaptor regarding
     *          startAllServiceConnection method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltStartAllServiceConnectionMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltStartServiceConnectionMethodCallStatus: Method to notify phone adaptor regarding
     *          startServiceConnection method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltStartServiceConnectionMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltBondingReplyMethodCallStatus: Method to notify phone adaptor regarding bondingReply method
     *          call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltBondingReplyMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltDeleteDeviceMethodCallStatus: Method to notify phone adaptor regarding
     *          deleteDevice method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltDeleteDeviceMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltDeleteAllDevicesMethodCallStatus: Method to notify phone adaptor regarding
     *          deleteAllDevices method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltDeleteAllDevicesMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltStartAllServiceDisconnectionMethodCallStatus: Method to notify phone adaptor regarding
     *          startAllServiceDisconnection method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltStartAllServiceDisconnectionMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltStartServiceDisconnectionMethodCallStatus: Method to notify phone adaptor regarding
     *          startServiceDisconnection method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltStartServiceDisconnectionMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltSetBluetoothMethodStatusCallStatus: Method to notify phone adaptor regarding
     *          setBluetoothStatus method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltSetBluetoothMethodStatusCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /******************************************************//**
     * @category    CALL MANAGER SLOTS
     * @brief       Slots for the signals emitted by phone call
     *              manager resource
     *******************************************************/
    /*!
     * @brief   sltCallStateInfoReceived: Method to notify phone adaptor regarding call state info received.
     * @param   void.
     * @return  void.
     */
    void sltCallStateInfoReceived();

    /*!
     * @brief   sltHfFeaturesListReceived: Method to notify phone adaptor regarding HF feature list received.
     * @param   void.
     * @return  void.
     */
    void sltHfFeaturesListReceived();

    /*!
     * @brief   sltOperatorInfoListReceived: Method to notify phone adaptor regarding operator info list received.
     * @param   void.
     * @return  void.
     */
    void sltOperatorInfoListReceived();

    /*!
     * @brief   sltRssiChargeInfoListReceived: Method to notify phone adaptor regarding Rssi charge info list received.
     * @param   void.
     * @return  void.
     */
    void sltRssiChargeInfoListReceived();

    /*!
     * @brief   sltHfModeStatusReceived: Method to notify phone adaptor regarding HF mode status received.
     * @param   void.
     * @return  void.
     */
    void sltHfModeStatusReceived();

    /*!
     * @brief   sltCallDurationReceived: Method to notify phone adaptor regarding call duration received.
     * @param   void.
     * @return  void.
     */
    void sltCallDurationReceived();

    /*!
     * @brief   sltPhoneBtVrModeStatusReceived: Method to notify phone adaptor regarding
     *          phone bt vr mode status received.
     * @param   void.
     * @return  void.
     */
    void sltPhoneBtVrModeStatusReceived();

    /*!
     * @brief   sltAcceptIncomingCallAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          acceptIncomingCallAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltAcceptIncomingCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltRejectIncomingCallAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          rejectIncomingCallAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltRejectIncomingCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltSendSMSAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          SendSMSAsync method call status received.
     * @param   bIsSucessful: request completed sucessfully
     * @return  void.
     */
    void sltSendSMSAsyncMethodCallStatus(bool bIsSucessful);

    /*!
     * @brief   sltDialAsyncMethodCallStatus: Method to notify phone adaptor regarding dialAsync
     *          method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltDialAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltConferenceCallAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          conferenceCallAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltConferenceCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltSwapCallsAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          swapCallsAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltSwapCallsAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltResumeHeldCallAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          resumeHeldCallAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltResumeHeldCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltHoldActiveCallAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          holdActiveCallAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltHoldActiveCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltEndCallAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          endCallAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltEndCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltEndActiveCallAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          endActiveCallAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltEndActiveCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltEndAllCallsAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          endAllCallsAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltEndAllCallsAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltSendDtmfToneAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          sendDtmfToneAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltSendDtmfToneAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltSetHfModeAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          setHfModeAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltSetHfModeAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sltSetVRModeAsyncMethodCallStatus: Method to notify phone adaptor regarding
     *          setVRModeAsync method call status received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sltSetVRModeAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /******************************************************************//**
     * @category    PHONE PIMDB SLOTS
     * @brief       Slots for the signals emitted by phone pimdb resource
     *              manager resource
     *******************************************************************/
    /*!
     * @brief   sltPimDbServiceAvailableStatusChanged: Method get notify PimDb Service Available
     *          Status Changed.
     * @param   bPimDbServiceAvailableStatus: PimDb Service Availability Status
     * @return  void.
     */
    void sltPimDbServiceAvailableStatusChanged(bool bPimDbServiceAvailableStatus);

    /*!
     * @brief   sltPimDbSessionClosedSelectiveEvent: Method get notify PimDb Session Closed
     *          Selective Event.
     * @param   void.
     * @return  void.
     */
    void sltPimDbSessionClosedSelectiveEvent();

    /*!
     * @brief   sltCallLogStatusChanged: Method get notify call log list status changed
     * @param   iStatus: Call Log Status
     * @return  void.
     */
    void sltCallLogStatusChanged(int iStatus);

    /*!
     * @brief   sltContactStatusChanged: Method get notify contact list status changed
     * @param   iStatus: Contact Status
     * @return  void.
     */
    void sltContactStatusChanged(int iStatus);

    /*!
     * @brief   sltContactDetailStatusChanged: Method get notify contact Detail list status changed
     * @param   iStatus: Contact Detail Status
     * @return  void.
     */
    void sltContactDetailStatusChanged(int iStatus);

    /*!
     * @brief   sltFavoriteStatusChanged: Method get notify Favorite contact list status changed
     * @param   iStatus: Favorite Status
     * @return  void.
     */
    void sltFavoriteStatusChanged(int iStatus);

    /*!
     * @brief   sltFrequentlyDialedStatusChanged: Method get notify frequently dialed list status changed.
     * @param   iStatus: Frequently dialed list sync status.
     * @return  void.
     */
    void sltFrequentlyDialedStatusChanged(int iStatus);

    /*!
     * @brief   sltCallLogUpdated: Method get notify contact log list updated
     * @param   void.
     * @return  void.
     */
    void sltCallLogUpdated();

    /*!
     * @brief   sltContactUpdated: Method get notify contact list updated
     * @param   usStartIndex: start index of the contact data list received.
     * @return  void.
     */
    void sltContactUpdated(unsigned short usStartIndex);

    /*!
     * @brief   sltContactDetailUpdated: Method get notify contact detail list updated
     * @param   void.
     * @return  void.
     */
    void sltContactDetailUpdated();

    /*!
     * @brief   sltFavoriteUpdated: Method get notify favorite contact list updated
     * @param   void.
     * @return  void.
     */
    void sltFavoriteUpdated();

    /*!
     * @brief   sltFrequentlyDialedListUpdated: Method get notify frequently dialed list updated.
     * @param   void.
     * @return  void.
     */
    void sltFrequentlyDialedListUpdated();

    /*!
     * @brief   sltAddContactToFavouriteComplete: Method get notify Add Contact To Favourite Complete
     * @param   bStatus: true if favorite is added, false otherwise
     * @return  void.
     */
    void sltAddContactToFavouriteComplete(bool bStatus);

    /*!
     * @brief   sltRemoveContactFromFavouriteComplete: Method get notify Remove Contact From Favourite
     *          Complete
     * @param   bStatus: true if favorite is removed, false otherwise
     * @return  void.
     */
    void sltRemoveContactFromFavouriteComplete(bool bStatus);

    /*!
     * @brief   sltMessageNotificationEvent: Method get notify new SMS recieved
     * @param   void.
     * @return  void.
     */
    void sltMessageNotificationEvent();

    /*!
     * @brief   sltIsSendingSMSAllowedPermissionChanged: Method get notify new Send SMS permission
     *          change recieved
     * @param   bIsSendingSMSAllowed: bool can send SMS.
     * @return  void.
     */
    void sltIsSendingSMSAllowedPermissionChanged(bool bIsSendingSMSAllowed);

    /*!
     * @brief   sltUnreadMissedCallEvent: Method to get unread missed call data
     * @param   void
     * @return  void.
     */
    void sltUnreadMissedCallEvent();

    /*!
     * @brief   sltGetSmsSupportedFeatureEvent: Method to get sms supported feature data
     * @param   void
     * @return  void.
     */
    void sltGetSmsSupportedFeatureEvent();

    /******************************************************************//**
     * @category    BT PRESS PLUGIN SLOTS
     * @brief       Slots for the signals emitted by bt plugin resource
     *******************************************************************/
    /**
     * @brief   sltTTSPlayStateStatus: Method to notify phone adaptor regarding
     *          TTS playstate status received.
     * @param   iTTSPlayState: current playstate of TTS.
     * @return  void.
     */
    void sltTTSPlayStateStatus(int iTTSPlayState);


private:
    /******************************************************//**
     * @category    INTERNAL METHODS
     *******************************************************/

    /*!
     * @brief   connectConnectionManagerSignals: Method to connect signals provided by
     *          CPhoneConnectionManagerEventProvider class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void connectConnectionManagerSignals();

    /*!
     * @brief   disconnectConnectionManagerSignals: Method to disconnect signals provided by
     *          CPhoneConnectionManagerEventProvider class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void disconnectConnectionManagerSignals();

    /*!
     * @brief   connectCallManagerSignals: Method to connect signals provided by
     *          CPhoneCallManagerEventProvider class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void connectCallManagerSignals();

    /*!
     * @brief   disconnectCallManagerSignals: Method to disconnect signals provided by
     *          CPhoneCallManagerEventProvider class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void disconnectCallManagerSignals();

    /*!
     * @brief   connectPimDbSignals: Method to connect signals provided by CPhonePIMDBEventProvider
     *          class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void connectPimDbSignals();

    /*!
     * @brief   disconnectPimDbSignals: Method to disconnect signals provided by CPhonePIMDBEventProvider
     *          class with the internal slots.
     * @param   void.
     * @return  void.
     */

    void disconnectPimDbSignals();

    /*!
     * @brief   connectBtPluginSignals: Method to connect signals provided by CBtPluginEventProvider
     *          class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void connectBtPluginSignals();

    /*!
     * @brief   disconnectBtPluginSignals: Method to disconnect signals provided by CBtPluginEventProvider
     *          class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void disconnectBtPluginSignals();

private:
};

#endif // CPHONEEVENTHANDLER_H

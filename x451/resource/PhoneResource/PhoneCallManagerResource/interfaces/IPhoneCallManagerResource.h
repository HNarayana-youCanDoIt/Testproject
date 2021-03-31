/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          IPhoneCallManagerResource.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains IPhoneCallManagerResource interface that provides abstract methods to communicate
 * with the CallManager proxy directly which shall be implemented by resource implementation class.
 */

#ifndef IPHONECALLMANAGERRESOURCE_H
#define IPHONECALLMANAGERRESOURCE_H

#include <string>
#include <vector>

//!Include the headers related to CallManagerPresCtrl
#include "v7/com/harman/btpres/BTPresTypes.hpp"
#include "v1/com/harman/btpres/CallManagerProxy.hpp"
#include "PhoneResource/CPhoneResourceEnums.h"

using namespace v1::com::harman::btpres;
using namespace v7::com::harman::btpres;
using namespace std;

/*!
 * @interface IPhoneCallManagerResource
 * @brief This interfaces provides abstract methods to communicate with the CallManager proxy directly which
 * shall be implemented by resource implementation class.
 */
class IPhoneCallManagerResource
{
public:
    virtual ~IPhoneCallManagerResource(){}

    /********************************************//**
     * @category REQUEST METHODS
     ************************************************/

    /*!
     * @brief   acceptIncomingCallAsyncReq: Method to inform call manager proxy to accept the incoming call from HU.
     * @param   strBtAddr: bt address of the connected phone.
     * @param   bAcceptInHandsetMode: flag indicates whether the call has to be transferred to handset mode.
     * @return  void.
     */
    virtual void acceptIncomingCallAsyncReq(const string& strBtAddr, bool bAcceptInHandsetMode = false) = 0;

    /*!
     * @brief   rejectIncomingCallAsyncReq: Method to inform call manager proxy to reject the incoming call from HU.
     * @param   strBtAddr: bt address of the connected phone.
     * @return  void.
     */
    virtual void rejectIncomingCallAsyncReq(const string& strBtAddr) = 0;

    /*!
     * @brief   dialAsyncReq: Method to inform call manager proxy to initate a call from HU.
     * @param   strBtAddr: bt address of the connected phone.
     * @param   strNumber: phone number to be dialled.
     * @param   strContactName: name of the contact if available.
     * @param   strImageUrl: image url of the contact if available.
     * @param   eTelphoneType: telephone type of the number(mobile/home/work/other).
     * @return  void.
     */
    virtual void dialAsyncReq(const string& strBtAddr, const string& strNumber, const string& strContactName,
                              const string& strImageUrl, EContactNumTeleType eTelphoneType) = 0;

    /*!
     * @brief   conferenceCallAsyncReq: Method to inform call manager proxy to put the calls in conference/merge two calls from HU.
     * @param   strBtAddr: bt address of the connected phone.
     * @return  void.
     */
    virtual void conferenceCallAsyncReq(const string& strBtAddr) = 0;

    /*!
     * @brief   swapCallsAsyncReq: Method to inform call manager proxy to swap the active call with held call from HU.
     * @param   strBtAddr: bt address of the connected phone.
     * @return  void.
     */
    virtual void swapCallsAsyncReq(const string& strBtAddr) = 0;

    /*!
     * @brief   resumeHeldCallAsyncReq: Method to inform call manager proxy to activate/resume the held call from HU.
     * @param   strBtAddr: bt address of the connected phone.
     * @return  void.
     */
    virtual void resumeHeldCallAsyncReq(const string& strBtAddr) = 0;

    /*!
     * @brief   holdActiveCallAsyncReq: Method to inform call manager proxy to put the current active call on hold from HU.
     * @param   strBtAddr: bt address of the connected phone.
     * @return  void.
     */
    virtual void holdActiveCallAsyncReq(const string& strBtAddr) = 0;

    /*!
     * @brief   endCallAsyncReq: Method to inform call manager proxy to end the call for passed call id from HU.
     * @param   strBtAddr: bt address of the connected phone.
     * @param   iCallId: call id of the phone call to be ended.
     * @return  void.
     */
    virtual void endCallAsyncReq(const string& strBtAddr, int iCallId) = 0;

    /*!
     * @brief   endActiveCallAsyncReq: Method to inform call manager proxy to end the current active call from HU.
     * @param   strBtAddr: bt address of the connected phone.
     * @return  void.
     */
    virtual void endActiveCallAsyncReq(const string& strBtAddr) = 0;

    /*!
     * @brief   endAllCallsAsyncReq: Method to inform call manager proxy to end all available calls from HU.
     * @param   strBtAddr: bt address of the connected phone.
     * @return  void.
     */
    virtual void endAllCallsAsyncReq(const string& strBtAddr) = 0;

    /*!
     * @brief   sendDtmfToneAsyncReq: Method to inform call manager proxy to send DTMF tone from HU to phone.
     * @param   strBtAddr: bt address of the connected phone.
     * @param   strDtmfTone: dtmf tone to be sent to phone.
     * @return  void.
     */
    virtual void sendDtmfToneAsyncReq(const string& strBtAddr, const string& strDtmfTone) = 0;

    /*!
     * @brief   setHfModeAsyncReq: Method to inform call manager proxy to transfer call audio from handsfree to handset mode
     *          and vice versa.
     * @param   strBtAddr: bt address of the connected phone.
     * @param   bHfMode: mode requested from HMI whether to set handset mode or handsfree mode .
     * @return  void.
     */
    virtual void setHfModeAsyncReq(const string& strBtAddr, bool bHfMode) = 0;

    /*!
     * @brief   setPhoneBtVrModeAsyncReq: Method to inform call manager proxy to activate/deactivate phone bt vr mode from head unit.
     * @param   strBtAddr: bt address of the connected phone.
     * @param   bPhoneBtVrMode: mode requested from HMI whether to activate/deactivate phone bt vr mode.
     * @return  void.
     */
    virtual void setPhoneBtVrModeAsyncReq(const string& strBtAddr, bool bPhoneBtVrMode) = 0;

private:
    /********************************************//**
     * @category CALLBACK METHODS
     ************************************************/

    /*!
     * @brief   callManagerStatusCb: Callback to get notified about the avalability status of the CallManager proxy.
     * @param   eStatus: status of CallManager proxy whether available or not.
     * @return  void.
     */
    virtual void callManagerStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;

    /*!
     * @brief   callStateInfoCb: Callback to get notified about the call state information of the connected phone.
     * @param   vectCallStateInfoList: vector of call details information.
     * @return  void.
     */
    virtual void callStateInfoCb(BTPresTypes::callstateInfoList vectCallStateInfoList) = 0;

    /*!
     * @brief   hfFeaturesListCb: Callback to get notified about the HFP profile supported features of the connected phone.
     * @param   vectHFPSupportedFeatureList: vector of HFP profile supported features.
     * @return  void.
     */
    virtual void hfFeaturesListCb(BTPresTypes::hfpSupportedFeaturesList vectHFPSupportedFeatureList) = 0;

    /*!
     * @brief   operatorInfoListCb: Callback to get notified about the network operator information of the connected phone.
     * @param   vectNetworkOperatorInfoList: vector of network operator information.
     * @return  void.
     */
    virtual void operatorInfoListCb(BTPresTypes::networkOperatorInfoList vectNetworkOperatorInfoList) = 0;

    /*!
     * @brief   rssiChargeInfoListCb: Callback to get notified about the network signal and battery charge level information of the
     *          connected phone.
     * @param   vectSignalChargeInfoList: vector of network signal and battery charge level information.
     * @return  void.
     */
    virtual void rssiChargeInfoListCb(BTPresTypes::signalChargeInfoList vectSignalChargeInfoList) = 0;

    /*!
     * @brief   hfModeCb: Callback to get notified about the handsfree mode status of the connected phone.
     * @param   vectHFModeStatusList: vector of handsfree mode status information.
     * @return  void.
     */
    virtual void hfModeCb(BTPresTypes::hfModeStatusList vectHFModeStatusList) = 0;

    /*!
     * @brief   callDurationCb: Callback to get notified about the call duration information of current call(active/conference).
     * @param   vectCallDurationList: vector of call duration information.
     * @return  void.
     */
    virtual void callDurationCb(BTPresTypes::callDurationList vectCallDurationList) = 0;

    /*!
     * @brief   phoneVRModeCb: Callback to get notified about the phone bt vr mode status whether ative or not.
     * @param   vectPhoneBtVrModeStatusList: vector of phone bt vr mode status information.
     * @return  void.
     */
    virtual void phoneVRModeCb(BTPresTypes::vrModeStatusList vectPhoneBtVrModeStatusList) = 0;

    /********************************************//**
     * @category RESPONSE CALLBACK METHODS
     ************************************************/

    /*!
     * @brief   acceptIncomingCallAsyncCb: Callback to get notified about acceptIncomingCallAsync method response.
     * @param   eCallStatus: call status of the acceptIncomingCallAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking acceptIncomingCallAsync method.
     * @return  void.
     */
    virtual void acceptIncomingCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   rejectIncomingCallAsyncCb: Callback to get notified about rejectIncomingCallAsync method response.
     * @param   eCallStatus: call status of the rejectIncomingCallAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking rejectIncomingCallAsync method.
     * @return  void.
     */
    virtual void rejectIncomingCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   dialAsyncCb: Callback to get notified about dialAsync method response.
     * @param   eCallStatus: call status of the dialAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking dialAsync method.
     * @return  void.
     */
    virtual void dialAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   conferenceCallAsyncCb: Callback to get notified about conferenceCallAsync method response.
     * @param   eCallStatus: call status of the conferenceCallAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking conferenceCallAsync method.
     * @return  void.
     */
    virtual void conferenceCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   swapCallsAsyncCb: Callback to get notified about swapCallsAsync method response.
     * @param   eCallStatus: call status of the swapCallsAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking swapCallsAsync method.
     * @return  void.
     */
    virtual void swapCallsAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   resumeHeldCallAsyncCb: Callback to get notified about resumeHeldCallAsync method response.
     * @param   eCallStatus: call status of the resumeHeldCallAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking resumeHeldCallAsync method.
     * @return  void.
     */
    virtual void resumeHeldCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   holdActiveCallAsyncCb: Callback to get notified about holdActiveCallAsync method response.
     * @param   eCallStatus: call status of the holdActiveCallAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking holdActiveCallAsync method.
     * @return  void.
     */
    virtual void holdActiveCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   endCallAsyncCb: Callback to get notified about endCallAsync method response.
     * @param   eCallStatus: call status of the endCallAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking endCallAsync method.
     * @return  void.
     */
    virtual void endCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   endActiveCallAsyncCb: Callback to get notified about endActiveCallAsync method response.
     * @param   eCallStatus: call status of the endActiveCallAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking endActiveCallAsync method.
     * @return  void.
     */
    virtual void endActiveCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   endAllCallsAsyncCb: Callback to get notified about endAllCallsAsync method response.
     * @param   eCallStatus: call status of the endAllCallsAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking endAllCallsAsync method.
     * @return  void.
     */
    virtual void endAllCallsAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   sendDtmfToneAsyncCb: Callback to get notified about sendDtmfToneAsync method response.
     * @param   eCallStatus: call status of the sendDtmfToneAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking sendDtmfToneAsync method.
     * @return  void.
     */
    virtual void sendDtmfToneAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   setHfModeAsyncCb: Callback to get notified about setHfModeAsync method response.
     * @param   eCallStatus: call status of the setHfModeAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking setHfModeAsync method.
     * @return  void.
     */
    virtual void setHfModeAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   setVrModeAsyncCb: Callback to get notified about setVRModeAsync method response.
     * @param   eCallStatus: call status of the setHfModeAsync method, whether success or not.
     * @param   eErrorType: type of the error received after invoking setHfModeAsync method.
     * @return  void.
     */
    virtual void setVrModeAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) = 0;
};

#endif // IPHONECALLMANAGERRESOURCE_H

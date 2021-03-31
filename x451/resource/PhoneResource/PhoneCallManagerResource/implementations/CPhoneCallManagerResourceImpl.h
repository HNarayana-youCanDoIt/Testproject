/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneCallManagerResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPhoneCallManagerResourceImpl class that shall implement the
 * PhoneCallManagerResource interface and is a mediator between lower layer(bt press control)
 * and upper layer(phone application).
 */

#ifndef CPHONECALLMANAGERRESOURCEIMPL_H
#define CPHONECALLMANAGERRESOURCEIMPL_H

#include <capi/CAPIClientAbstraction.hpp>
#include "interfaces/IPhoneCallManagerResource.h"
#include "CPhoneCallManagerEventProvider.h"
#include "PhoneResource/CPhoneResourceData.h"

/*!
 * @class CPhoneConnectionManagerResourceImpl
 * @brief This is a singleton class that shall implement the PhoneCallManagerResource interface and is a mediator between
 * lower layer(bt press control) and upper layer(phone application).
 */
class CPhoneCallManagerResourceImpl: public IPhoneCallManagerResource
{
/********************************************//**
 * @category CONSTANTS
 ************************************************/
public:

    const string EMPTY_NAME_FOR_CONTACT = "Empty Name For HMI";

/********************************************//**
 * @category METHODS
 ************************************************/
public:
    /*!
     * @brief   getPhoneCallManagerEventProvider: Method to get the instance of CPhoneCallManagerEventProvider class.
     * @param   void.
     * @return  pointer to the object of CPhoneCallManagerEventProvider class.
     */
    CPhoneCallManagerEventProvider* getPhoneCallManagerEventProvider();

    /******************************************************//**
     * @category    REQUEST
     * @brief       Overide the PhoneCallManagerResource functions
     * that shall be used by the Phone adapter layer to propagate
     * the calls.
     *******************************************************/
    void acceptIncomingCallAsyncReq(const string& strBtAddr, bool bAcceptInHandsetMode = false) override;
    void rejectIncomingCallAsyncReq(const string& strBtAddr) override;
    void dialAsyncReq(const string& strBtAddr, const string& strNumber, const string& strContactName,
                      const string& strImageUrl, EContactNumTeleType eTelphoneType) override;
    void conferenceCallAsyncReq(const string& strBtAddr) override;
    void swapCallsAsyncReq(const string& strBtAddr) override;
    void resumeHeldCallAsyncReq(const string& strBtAddr) override;
    void holdActiveCallAsyncReq(const string& strBtAddr) override;
    void endCallAsyncReq(const string& strBtAddr, int iCallId) override;
    void endActiveCallAsyncReq(const string& strBtAddr) override;
    void endAllCallsAsyncReq(const string& strBtAddr) override;
    void sendDtmfToneAsyncReq(const string& strBtAddr, const string& strDtmfTone) override;
    void setHfModeAsyncReq(const string& strBtAddr, bool bHfMode) override;
    void setPhoneBtVrModeAsyncReq(const string& strBtAddr, bool bPhoneBtVrMode) override;

    /******************************************************//**
     * @category GETTERS
     *******************************************************/
    /*!
     * @brief   getCallDurationList: Method to get call duration of active call for connected devices.
     * @param   void.
     * @return  const reference vector of SCallDuration structure's instance.
     */
    const vector<SCallDuration>&  getCallDurationList() { return m_vectCallDurationList; }

    /*!
     * @brief   getHfModeStatusList: Method to get handsfree mode status of active call for connected devices.
     * @param   void.
     * @return  const reference vector of SHfModeStatus structure's instance.
     */
    const vector<SHfModeStatus>&  getHfModeStatusList() { return m_vectHfModeStatusList; }

    /*!
     * @brief   getSignalChargeInfoList: Method to get signal charge(battery charge & signal strength) info of
     *          connected devices for hfp profile.
     * @param   void.
     * @return  const reference vector of SSignalChargeInfo structure's instance.
     */
    const vector<SSignalChargeInfo>&  getSignalChargeInfoList() { return m_vectSignalChargeInfoList; }

    /*!
     * @brief   getNetworkOperatorInfoList: Method to get network operator info of connected devices for hfp profile.
     * @param   void.
     * @return  const reference vector of SNetworkOperatorInfo structure's instance.
     */
    const vector<SNetworkOperatorInfo>&  getNetworkOperatorInfoList() { return m_vectNetworkOperatorInfoList; }

    /*!
     * @brief   getHfpSupportedFeatureList: Method to get hfp supported features info of connected devices for hfp profile.
     * @param   void.
     * @return  const reference vector of SHfpSupportedFeatures structure's instance.
     */
    const vector<SHfpSupportedFeatures>&  getHfpSupportedFeatureList() { return m_vectHfpSupportedFeatureInfoList; }

    /*!
     * @brief   getCallStateInfoList: Method to get call state info list of connected devices.
     * @param   void.
     * @return  const reference vector of SCallStateInfoList structure.
     */
    const vector<SCallStateInfoList>&  getCallStateInfoList() { return m_vectCallStateInfoList; }

    /*!
     * @brief   getPhonebtVrModeStatusList: Method to get phone bt vr mode status info list of connected devices.
     * @param   void.
     * @return  const reference vector of SPhoneBTVrModeStatus structure.
     */
    const vector<SPhoneBTVrModeStatus>&  getPhonebtVrModeStatusList() { return m_vectPhoneBTVrModeStatusList; }

private:
    /*!
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;
    CPhoneCallManagerResourceImpl();
    virtual ~CPhoneCallManagerResourceImpl();

    /******************************************************//**
     * @category CALLBACK
     *******************************************************/
    void callManagerStatusCb(CommonAPI::AvailabilityStatus eStatus) override;
    void callStateInfoCb(BTPresTypes::callstateInfoList vectCallStateInfoList) override;
    void hfFeaturesListCb(BTPresTypes::hfpSupportedFeaturesList vectHFPSupportedFeatureList) override;
    void operatorInfoListCb(BTPresTypes::networkOperatorInfoList vectNetworkOperatorInfoList) override;
    void rssiChargeInfoListCb(BTPresTypes::signalChargeInfoList vectSignalChargeInfoList) override;
    void hfModeCb(BTPresTypes::hfModeStatusList vectHFModeStatusList) override;
    void callDurationCb(BTPresTypes::callDurationList vectCallDurationList) override;
    void phoneVRModeCb(BTPresTypes::vrModeStatusList vectPhoneBtVrModeStatusList) override;

    /********************************************//**
     * @category RESPONSE
     ************************************************/
    void acceptIncomingCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void rejectIncomingCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void dialAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void conferenceCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void swapCallsAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void resumeHeldCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void holdActiveCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void endCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void endActiveCallAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void endAllCallsAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void sendDtmfToneAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void setHfModeAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;
    void setVrModeAsyncCb(const CommonAPI::CallStatus& eCallStatus, const BTPresTypes::eErrorType& eErrorType) override;

    /******************************************************//**
     * @category INTERNAL METHODS
     *******************************************************/
    /*!
     * @brief   Internal method to subscribe all the callback methods.
     * @param   void.
     * @return  void.
     */
    void subscribeCallManagerCb();

    /*!
     * @brief   getContactTelephoneType: Internal method to map call manager resource's contact telephone type enums
     *          to BTPress telephone Type enums. The mapped enums shall be used by the class itself.
     * @param   eTelephoneType: Call manager resource's contact telephone enum value.
     * @return  BTPress telephone type enum value.
     */
    BTPresTypes::eTelType getContactTelephoneType(EContactNumTeleType eContactNumTeleType);

    /*!
     * @brief   getContactTelephoneType: Internal method to map BTPress telephone Type enums to call manager resource's method
     *          contact number telephone type enums. The mapped enums shall be used by the phone
     *          application layer and the class itself.
     * @param   iContactNumTeleType: BTPress telephone Type enum value.
     * @return  call manager resource's contact number telephone type enum.
     */
    EContactNumTeleType getContactTelephoneType(int iContactNumTeleType);

    /*!
     * @brief   getMethodCallStatus: Internal method to map BTPress method call status enums to call manager resource's method
     *          call status enums. The mapped enums shall be used by the phone application layer and the class itself.
     * @param   eCallStatus: BTPress method call status enum value.
     * @return  call manager resource's method call status enum.
     */
    EMethodCallStatus getMethodCallStatus(CallStatus eCallStatus);

    /*!
     * @brief   getMethodCallErrorType: Internal method to map BTPress method call error type enums to call manager resource's
     *          method call error type enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iErrorType: BTPress method call error type enum value.
     * @return  call manager resource's method call error type enum value.
     */
    EMethodCallErrorType getMethodCallErrorType(int iErrorType);

    /*!
     * @brief   getCallState: Internal method to map BTPress call state enums to call manager resource's
     *          call state enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iCallState: BTPress call state enum value.
     * @return  call manager resource's call state enum value.
     */
    ECallState getCallState(int iCallState);

    /*!
     * @brief   getCallDirection: Internal method to map BTPress call direction enums to call manager resource's
     *          call direction enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iCallDirection: BTPress call direction enum value.
     * @return  call manager resource's call direction enum value.
     */
    ECallDirection getCallDirection(int iCallDirection);

    /*!
     * @brief   getCallAudioStatus: Internal method to map BTPress call audio status enums to call manager resource's
     *          call audio status enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iCallAudioStatus: BTPress call audio status enum value.
     * @return  call manager resource's call audio status enum value.
     */
    ECallAudioStatus getCallAudioStatus(int iCallAudioStatus);

    /*!
     * @brief   getSignalLevel: Internal method to map BTPress signal level enums to call manager resource's
     *          signal level enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iSignalLevel: BTPress signal level enum value.
     * @return  call manager resource's signal level enum value.
     */
    ESignalLevel getSignalLevel(int iSignalLevel);

    /*!
     * @brief   getBatteryChargeLevel: Internal method to map BTPress battery charge level enums to call manager resource's
     *          battery charge level enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iBatteryChargeLevel: BTPress battery charge level enum value.
     * @return  call manager resource's battery charge level enum value.
     */
    EBatteryChargeLevel getBatteryChargeLevel(int iBatteryChargeLevel);

    /*!
     * @brief   getPhoneNetworkRegState: Internal method to map BTPress phone network registry state enums to call manager resource's
     *          phone network registry state enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iPhoneNetworkRegState: BTPress phone network registry state enum value.
     * @return  call manager resource's phone network registry state enum value.
     */
    EPhoneNetworkRegState getPhoneNetworkRegState(int iPhoneNetworkRegState);

    /*!
     * @brief   getPhoneOperatorMode: Internal method to map BTPress phone operator mode enums to call manager resource's
     *          phone operator mode enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iPhoneOperatorMode: BTPress phone operator mode enum value.
     * @return  call manager resource's phone operator mode enum value.
     */
    EPhoneOperatorMode getPhoneOperatorMode(int iPhoneOperatorMode);

    /*!
     * @brief   getPhoneSupportedFeature: Internal method to map BTPress phone supported features enums to call manager resource's
     *          phone supported features enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iPhoneSupportedFeature: BTPress phone supported features enum value.
     * @return  call manager resource's phone supported features enum value.
     */
    EPhoneSupportedFeatures getPhoneSupportedFeature(int iPhoneSupportedFeature);

    /*!
     * @brief   generateHMICallState: Internal method to generate HMI call state based upon the call state information received
     *          from call manager proxy.
     * @param   void.
     * @return  void.
     */
    void generateHMICallState();

    /*!
     * @brief   getCallStateCount: Internal method to find the number of occurenecs of the call state in callStateInfoList.
     * @param   objCallStateInfoList: reference of call state info list object.
     * @param   eCallState: resource call state enum mapped with callstate enum of BtPress.
     * @return  count of ocurreneces of the call state in callStateInfoList.
     */
    unsigned int getCallStateCount(SCallStateInfoList &objCallStateInfoList, ECallState eCallState);

    /*!
     * @brief   addCallStateInfo: Internal method to add call state information in call state info list.
     * @param   objCallStateInfoList: reference of call state info list object.
     * @param   objCallState: reference of call state info object.
     * @return  void.
     */
    void addCallStateInfo(SCallStateInfoList& objCallStateInfoList, BTPresTypes::callStateInfo &objCallState);


/******************************************************//**
 * @category PROPERTIES
 *******************************************************/
private:
    //!Pointer of CPhoneCallManagerEventProvider class to emit signals to the phone application layer.
    CPhoneCallManagerEventProvider*             m_pPhoneCallMgrEventProvider;
    //!Instance of CallManagerProxy class to communicate with bt press control layer.
    CAPIClientAbstraction<CallManagerProxy>     m_objCallManagerProxy;
    //!Flag to maintain connection manager proxy availability status.
    bool                                        m_bIsCallManagerProxyAvailable;
    //!List of call duration of active call for connected devices.
    vector<SCallDuration>                       m_vectCallDurationList;
    //!List of handsfree mode status of active call for connected devices.
    vector<SHfModeStatus>                       m_vectHfModeStatusList;
    //!List of signal charge(battery charge & signal strength) info of connected devices for hfp profile.
    vector<SSignalChargeInfo>                   m_vectSignalChargeInfoList;
    //!List of network operator info of connected devices for hfp profile.
    vector<SNetworkOperatorInfo>                m_vectNetworkOperatorInfoList;
    //!List of hfp supported features info of connected devices for hfp profile.
    vector<SHfpSupportedFeatures>               m_vectHfpSupportedFeatureInfoList;
    //!Vector of call state info list structure.
    vector<SCallStateInfoList>                  m_vectCallStateInfoList;
    //!Vector of Phone Bt VR mode status list structure.
    vector<SPhoneBTVrModeStatus>                m_vectPhoneBTVrModeStatusList;
};

#endif // CPHONECALLMANAGERRESOURCEIMPL_H

/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
/**
 * description: This new interface is an extension of existing CallManager interface. 	This new
 *   interface is added to provide a common interface which will handles various
 *   	voice call scenarios from different modules like BT, Carplay etc.
 */
#ifndef V1_COM_HARMAN_BTPRES_Call_Manager_V2_PROXY_BASE_HPP_
#define V1_COM_HARMAN_BTPRES_Call_Manager_V2_PROXY_BASE_HPP_

#include <v1/com/harman/btpres/CallManagerV2.hpp>


#include <v7/com/harman/btpres/BTPresTypes.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <cstdint>
#include <string>
#include <vector>

#include <CommonAPI/Attribute.hpp>
#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace com {
namespace harman {
namespace btpres {

class CallManagerV2ProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::ObservableReadonlyAttribute<::v7::com::harman::btpres::BTPresTypes::networkOperatorList> NetworkoperatorAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v7::com::harman::btpres::BTPresTypes::signalChargeList> SignalChargeAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v7::com::harman::btpres::BTPresTypes::hfpFeatureList> HandsfreeFeaturesAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v7::com::harman::btpres::BTPresTypes::modeStatusList> HandsfreeModeStatusAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v7::com::harman::btpres::BTPresTypes::modeStatusList> AudioModeStatusAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v7::com::harman::btpres::BTPresTypes::modeStatusList> VrModeStatusAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v7::com::harman::btpres::BTPresTypes::callStateList> CallStatesAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v7::com::harman::btpres::BTPresTypes::callsDurationList> CallDurationsAttribute;

    typedef std::function<void(const CommonAPI::CallStatus&, const ::v7::com::harman::btpres::BTPresTypes::eErrorType&)> ControlVoiceCallAsyncCallback;

    /**
     * description: broadcast phone network operator information to registered clients
     */
    virtual NetworkoperatorAttribute& getNetworkoperatorAttribute() = 0;
    /**
     * description: broadcast signal and charge levels to registered clients
     */
    virtual SignalChargeAttribute& getSignalChargeAttribute() = 0;
    /**
     * description: broadcast Handsfree supported features to registered clients
     */
    virtual HandsfreeFeaturesAttribute& getHandsfreeFeaturesAttribute() = 0;
    /**
     * description: broadcast HF mode status to registered clients
     */
    virtual HandsfreeModeStatusAttribute& getHandsfreeModeStatusAttribute() = 0;
    /**
     * description: broadcast SCO audio status to registered clients
     */
    virtual AudioModeStatusAttribute& getAudioModeStatusAttribute() = 0;
    /**
     * description: broadcast VR status to registered clients
     */
    virtual VrModeStatusAttribute& getVrModeStatusAttribute() = 0;
    /**
     * description: broadcast callstate status to registered clients
     */
    virtual CallStatesAttribute& getCallStatesAttribute() = 0;
    /**
     * description: broadcast call duration to registered clients
     */
    virtual CallDurationsAttribute& getCallDurationsAttribute() = 0;


    /**
     * description: Clients should use this API to control voice calls from different modules
     * param: actionType (ePhoneCallActionType): Actions like Accept, Reject, EndCall etc.
     * param: callerInfo (sVoiceCallInfo)		 : contains caller informations like number,
     *   contactName etc. 		returns: errorCode (eErrorType)	: API execution output
     */
    virtual void controlVoiceCall(const ::v7::com::harman::btpres::BTPresTypes::ePhoneCallActionType &_actionType, const ::v7::com::harman::btpres::BTPresTypes::sVoiceCallInfo &_callerInfo, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> controlVoiceCallAsync(const ::v7::com::harman::btpres::BTPresTypes::ePhoneCallActionType &_actionType, const ::v7::com::harman::btpres::BTPresTypes::sVoiceCallInfo &_callerInfo, ControlVoiceCallAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace btpres
} // namespace harman
} // namespace com
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_COM_HARMAN_BTPRES_Call_Manager_V2_PROXY_BASE_HPP_

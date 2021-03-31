/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V1_COM_HARMAN_PRES_IAP2_Handler_PROXY_BASE_HPP_
#define V1_COM_HARMAN_PRES_IAP2_Handler_PROXY_BASE_HPP_

#include <v1/com/harman/pres/IAP2Handler.hpp>


#include <v1/com/harman/pres/devprestypes.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <cstdint>
#include <vector>

#include <CommonAPI/Event.hpp>
#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace com {
namespace harman {
namespace pres {

class IAP2HandlerProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::Event<
        ::v1::com::harman::pres::devprestypes::eIAP2Transport, std::vector<::v1::com::harman::pres::devprestypes::eIAP2Mode>, std::string, uint8_t, std::string
    > IAP2StartedEvent;
    typedef CommonAPI::Event<
        std::string
    > IAP2StoppedEvent;

    typedef std::function<void(const CommonAPI::CallStatus&, const ::v1::com::harman::pres::devprestypes::eAcknowledgement&)> StartIAP2AsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const ::v1::com::harman::pres::devprestypes::eAcknowledgement&)> StopIAP2AsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const ::v1::com::harman::pres::devprestypes::vIAP2Info&)> GetIAP2StartedAsyncCallback;


    /**
     * description: This broadcast notifies dbus instanceName of IAP2 launched. 		 		"devicepath"
     *   is only applicable for USB_HOST, BT & WIFI transports. 		"deviceId" is only
     *   applicable for USB_HOST & USB_DEVICE.
     */
    virtual IAP2StartedEvent& getIAP2StartedEvent() = 0;
    /**
     * description: This broadcast notifies dbus instanceName of IAP2 terminated. 	
     *   		"instanceName" : dbus instanceName of IAP2 driver terminated.
     */
    virtual IAP2StoppedEvent& getIAP2StoppedEvent() = 0;

    /**
     * description: This method to be called to start IAP2 driver. 	 		This is to be called for
     *   transport over BT & WIFI.  		For USB_HOST & USB_DEVICE transports,
     *   devPresCntrl itself starts IAP2 driver. 		 		dbus instanceName of launched
     *   IAP2 driver can be found with broadcast "IAP2Started".
     */
    virtual void startIAP2(const ::v1::com::harman::pres::devprestypes::eIAP2Transport &_transport, const std::vector<::v1::com::harman::pres::devprestypes::eIAP2Mode> &_modes, const std::string &_devicePath, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::pres::devprestypes::eAcknowledgement &_ackStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> startIAP2Async(const ::v1::com::harman::pres::devprestypes::eIAP2Transport &_transport, const std::vector<::v1::com::harman::pres::devprestypes::eIAP2Mode> &_modes, const std::string &_devicePath, StartIAP2AsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: This method to be called to stop IAP2 driver. 	 		"instanceName" : dbus
     *   instanceName of IAP2 driver to be terminated.
     */
    virtual void stopIAP2(const std::string &_instanceName, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::pres::devprestypes::eAcknowledgement &_ackStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> stopIAP2Async(const std::string &_instanceName, StopIAP2AsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: This getter notifies dbus instanceName of IAP2 currently launched. 
     *   	"devicepath" is only applicable for USB_HOST, BT & WIFI transports.
     *   	"deviceId" is only applicable for USB_HOST & USB_DEVICE.  	instanceName and
     *   devicePath will be null if iap2 is not active
     */
    virtual void getIAP2Started(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::pres::devprestypes::vIAP2Info &_iap2StackInfo, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> getIAP2StartedAsync(GetIAP2StartedAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace pres
} // namespace harman
} // namespace com
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_COM_HARMAN_PRES_IAP2_Handler_PROXY_BASE_HPP_

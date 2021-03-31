/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V0_COM_HARMAN_KEYPRES_Key_Pres_Plugin_PROXY_BASE_HPP_
#define V0_COM_HARMAN_KEYPRES_Key_Pres_Plugin_PROXY_BASE_HPP_

#include <v0/com/harman/keypres/KeyPresPlugin.hpp>



#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <cstdint>
#include <vector>

#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace com {
namespace harman {
namespace keypres {

class KeyPresPluginProxyBase
    : virtual public CommonAPI::Proxy {
public:

    typedef std::function<void(const CommonAPI::CallStatus&, const KeyPresPlugin::eCallResult&)> SendSliderStateAsyncCallback;



    /**
     * description: This method will send the keycode received from HMI 	Input :  KeyCodeID,
     *   KeyState
     */
    /**
     * @invariant Fire And Forget
     */
    virtual void sendKeyCode(const KeyPresPlugin::eKeyCodeId &_keyCode, const KeyPresPlugin::eKeyState &_keystate, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * description: This method will send the the volume slider state 	Input :  KeyCodeID,
     *   KeyState, steps 	Output : result
     */
    virtual void sendSliderState(const KeyPresPlugin::eKeyCodeId &_keyCode, const KeyPresPlugin::eKeyState &_keystate, const int16_t &_steps, CommonAPI::CallStatus &_internalCallStatus, KeyPresPlugin::eCallResult &_result, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> sendSliderStateAsync(const KeyPresPlugin::eKeyCodeId &_keyCode, const KeyPresPlugin::eKeyState &_keystate, const int16_t &_steps, SendSliderStateAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace keypres
} // namespace harman
} // namespace com
} // namespace v0


// Compatibility
namespace v0_1 = v0;

#endif // V0_COM_HARMAN_KEYPRES_Key_Pres_Plugin_PROXY_BASE_HPP_

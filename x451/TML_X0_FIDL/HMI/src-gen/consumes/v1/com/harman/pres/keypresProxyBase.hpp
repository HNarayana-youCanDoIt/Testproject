/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V1_COM_HARMAN_PRES_keypres_PROXY_BASE_HPP_
#define V1_COM_HARMAN_PRES_keypres_PROXY_BASE_HPP_

#include <v1/com/harman/pres/keypres.hpp>


#include <v1/com/harman/pres/keyprestypes.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <cstdint>
#include <string>
#include <vector>

#include <CommonAPI/Event.hpp>
#include <CommonAPI/SelectiveEvent.hpp>
#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace com {
namespace harman {
namespace pres {

class keypresProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::SelectiveEvent<std::shared_ptr<::v1::com::harman::pres::keyprestypes::tKey>> KeyEventSelectiveEvent;



    /**
     * description: brodcast publishing a keystate
     */
    virtual KeyEventSelectiveEvent& getKeyEventSelectiveEvent() = 0;

    /**
     * description: method to subscribe to keys and some states of the same 		Client can provide a
     *   list of tKeyStates which contains ids and corresponding states 		To subsribe
     *   to all states , pass an empty array to tKeyStates::keyStates 		Subscibing to
     *   only interested states is strongly recommended 		Note: In case client wants
     *   states of all available buttons , pass an empty array of tKeyStates
     */
    /**
     * @invariant Fire And Forget
     */
    virtual void subscribeKeys(const std::vector<::v1::com::harman::pres::keyprestypes::tKeyStates> &_keys, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * description: method to subscribe to keys and some states of the same with a priority
     *   		Client can provide a list of tKeyStates which contains ids and corresponding
     *   states 		To subsribe to all states , pass an empty array to
     *   tKeyStates::keyStates 		Subscibing to only interested states is strongly
     *   recommended 		Project team should first decide on a priority matrix and enable
     *   the same in cfg  		Note: In case client wants states of all available buttons
     *   , pass an empty array of tKeyStates
     */
    /**
     * @invariant Fire And Forget
     */
    virtual void subscribeKeys(const std::vector<::v1::com::harman::pres::keyprestypes::tKeyPriority> &_keys, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * description: method to unsubscribe to some or all keys 		To unsubscribe few keys , mention
     *   the key ids 		To unsubscribe to all keys , pass on an empty list, Pres will
     *   remove the client id for  		previously subscribed keys by the client
     */
    /**
     * @invariant Fire And Forget
     */
    virtual void unSubscribeKeys(const std::vector<uint16_t> &_keyIds, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * description: method to get/release exclusive focus to the keys 		keyIds - array of key ids
     *   		focus - exclusive client if true 				key events (subscribed states) will be
     *   published only to the requesting client  				broadcast to self and other
     *   clients already registered if false 		NOTE : If a client is not previously
     *   registered as a subscriber to a keyid and yet a keyid is passed here , 		then
     *   request for the particular keyid will be ignored , other key requests will be
     *   honored
     */
    /**
     * @invariant Fire And Forget
     */
    virtual void setExclusiveFocus(const std::vector<uint16_t> &_keyIds, const bool &_focus, CommonAPI::CallStatus &_internalCallStatus) = 0;
    /**
     * description: method to get/release exclusive focus to the keys along with states 		This
     *   interface doesnt require a client to first register to a key unlike the above
     *   API 		keyStates - array of key states 		focus - exclusive client if true
     *   				key events (subscribed states) will be published only to the requesting
     *   client  				broadcast to self and other clients already registered if false
     */
    /**
     * @invariant Fire And Forget
     */
    virtual void setExclusiveFocus(const std::vector<::v1::com::harman::pres::keyprestypes::tKeyStates> &_keyStates, const bool &_focus, CommonAPI::CallStatus &_internalCallStatus) = 0;
};

} // namespace pres
} // namespace harman
} // namespace com
} // namespace v1


// Compatibility
namespace v1_1 = v1;

#endif // V1_COM_HARMAN_PRES_keypres_PROXY_BASE_HPP_

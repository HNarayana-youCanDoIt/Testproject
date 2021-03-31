/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V1_COM_HARMAN_MMPRES_Media_Settings_PROXY_BASE_HPP_
#define V1_COM_HARMAN_MMPRES_Media_Settings_PROXY_BASE_HPP_

#include <v1/com/harman/mmpres/MediaSettings.hpp>


#include <v1/com/harman/mmpres/MMPresTypes.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <cstdint>
#include <vector>

#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace com {
namespace harman {
namespace mmpres {

class MediaSettingsProxyBase
    : virtual public CommonAPI::Proxy {
public:

    typedef std::function<void(const CommonAPI::CallStatus&, const ::v1::com::harman::mmpres::MMPresTypes::eCallResult&)> MasterMediaResetAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const ::v1::com::harman::mmpres::MMPresTypes::eCallResult&)> ResetMediaIndexAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const ::v1::com::harman::mmpres::MMPresTypes::eMediaError&)> UpdateIndexAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const ::v1::com::harman::mmpres::MMPresTypes::eCallResult&)> SetSubtitleAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const ::v1::com::harman::mmpres::MMPresTypes::eMediaError&)> SetDisplayWindowAsyncCallback;



    /**
     * description: reset all the Media related settings to the default.  		e: error code.
     */
    virtual void masterMediaReset(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::mmpres::MMPresTypes::eCallResult &_e, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> masterMediaResetAsync(MasterMediaResetAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: removes the database file of specified device on device ejection.
     * param: slotId: the specified slot id         returns:	  eCallResult:	Result of the API
     *   call
     */
    virtual void resetMediaIndex(const uint8_t &_slotId, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::mmpres::MMPresTypes::eCallResult &_e, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> resetMediaIndexAsync(const uint8_t &_slotId, ResetMediaIndexAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: Updates the index of a device
     * param: slotId: the specified slot id         returns:	  e:	Result of the API call
     */
    virtual void updateIndex(const uint8_t &_slotId, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::mmpres::MMPresTypes::eMediaError &_e, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> updateIndexAsync(const uint8_t &_slotId, UpdateIndexAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: Set Subtitle ON or OFF
     * param: dispSubtitle - eSubtitleStatus:ON is to enable Subtitle, eSubtitleStatus:OFF is
     *   to disable subtitle
     */
    virtual void setSubtitle(const ::v1::com::harman::mmpres::MMPresTypes::eSubtitleStatus &_dispSubtitle, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::mmpres::MMPresTypes::eCallResult &_result, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> setSubtitleAsync(const ::v1::com::harman::mmpres::MMPresTypes::eSubtitleStatus &_dispSubtitle, SetSubtitleAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: Set the display window coordinates of video playback
     * param: isFullscreen True is to enable fullscreen, false is to disable fullscreen and
     *   manually assign by screeenDimension                 screeenDimension  Screen
     *   coordinates
     */
    virtual void setDisplayWindow(const bool &_isFullscreen, const ::v1::com::harman::mmpres::MMPresTypes::tScreen &_screeenDimension, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::mmpres::MMPresTypes::eMediaError &_e, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> setDisplayWindowAsync(const bool &_isFullscreen, const ::v1::com::harman::mmpres::MMPresTypes::tScreen &_screeenDimension, SetDisplayWindowAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace mmpres
} // namespace harman
} // namespace com
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_COM_HARMAN_MMPRES_Media_Settings_PROXY_BASE_HPP_

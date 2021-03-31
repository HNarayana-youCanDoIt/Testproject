/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V0_COM_HARMAN_DCIF_Ccm_Hu_PROXY_BASE_HPP_
#define V0_COM_HARMAN_DCIF_Ccm_Hu_PROXY_BASE_HPP_

#include <v0/com/harman/dcif/CcmHu.hpp>


#include <v0/com/harman/dcif/CcmPresTypes.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <cstdint>
#include <vector>

#include <CommonAPI/Attribute.hpp>
#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace com {
namespace harman {
namespace dcif {

class CcmHuProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::ObservableReadonlyAttribute<::v0::com::harman::dcif::CcmPresTypes::tCcmHu> CcmHuAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<uint8_t> CcmHuUserInterventionFlagAttribute;

    typedef std::function<void(const CommonAPI::CallStatus&)> HuCcm_reqAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&, const ::v0::com::harman::dcif::CcmPresTypes::CcmInfo&)> GetCcmInfoAsyncCallback;

    virtual CcmHuAttribute& getCcmHuAttribute() = 0;
    virtual CcmHuUserInterventionFlagAttribute& getCcmHuUserInterventionFlagAttribute() = 0;


    virtual void huCcm_req(const ::v0::com::harman::dcif::CcmPresTypes::eHuCcmParam &_huCcm_enum, const uint16_t &_huCcm_value, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> huCcm_reqAsync(const ::v0::com::harman::dcif::CcmPresTypes::eHuCcmParam &_huCcm_enum, const uint16_t &_huCcm_value, HuCcm_reqAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual void getCcmInfo(CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::CcmPresTypes::CcmInfo &_ccmInfo, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> getCcmInfoAsync(GetCcmInfoAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace dcif
} // namespace harman
} // namespace com
} // namespace v0


// Compatibility
namespace v0_1 = v0;

#endif // V0_COM_HARMAN_DCIF_Ccm_Hu_PROXY_BASE_HPP_

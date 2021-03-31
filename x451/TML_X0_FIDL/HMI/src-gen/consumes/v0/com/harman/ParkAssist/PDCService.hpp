/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V0_COM_HARMAN_PARKASSIST_PDC_SERVICE_HPP_
#define V0_COM_HARMAN_PARKASSIST_PDC_SERVICE_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Types.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace com {
namespace harman {
namespace ParkAssist {

class PDCService {
public:
    virtual ~PDCService() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
};

const char* PDCService::getInterface() {
    return ("com.harman.ParkAssist.PDCService");
}

CommonAPI::Version PDCService::getInterfaceVersion() {
    return CommonAPI::Version(0, 1);
}


} // namespace ParkAssist
} // namespace harman
} // namespace com
} // namespace v0

namespace CommonAPI {
}


// Compatibility
namespace v0_1 = v0;

#endif // V0_COM_HARMAN_PARKASSIST_PDC_SERVICE_HPP_

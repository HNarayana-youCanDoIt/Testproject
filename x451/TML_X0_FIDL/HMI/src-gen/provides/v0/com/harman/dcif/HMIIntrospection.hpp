/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
/**
 * description: The HMI Service is responsible for providing the information to its consumers
 *   about the screen changes in HMI      and the information about the components
 *   present in the screen           Version: 1.0     Reason:         - Initial
 *   Version     Changes:         1. readonly attributes: topScreen         2.
 *   methods: inspectScreen         3. signal : screenChange
 * author: Gaurav Garg
 */
#ifndef V0_COM_HARMAN_DCIF_HMI_INTROSPECTION_HPP_
#define V0_COM_HARMAN_DCIF_HMI_INTROSPECTION_HPP_




#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Types.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v0 {
namespace com {
namespace harman {
namespace dcif {

class HMIIntrospection {
public:
    virtual ~HMIIntrospection() { }

    static inline const char* getInterface();
    static inline CommonAPI::Version getInterfaceVersion();
};

const char* HMIIntrospection::getInterface() {
    return ("com.harman.dcif.HMIIntrospection");
}

CommonAPI::Version HMIIntrospection::getInterfaceVersion() {
    return CommonAPI::Version(0, 1);
}


} // namespace dcif
} // namespace harman
} // namespace com
} // namespace v0

namespace CommonAPI {
}


// Compatibility
namespace v0_1 = v0;

#endif // V0_COM_HARMAN_DCIF_HMI_INTROSPECTION_HPP_

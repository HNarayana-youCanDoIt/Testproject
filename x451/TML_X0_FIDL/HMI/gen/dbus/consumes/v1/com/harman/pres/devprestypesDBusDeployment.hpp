/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/

#ifndef V1_COM_HARMAN_PRES_DEVPRESTYPES_DBUS_DEPLOYMENT_HPP_
#define V1_COM_HARMAN_PRES_DEVPRESTYPES_DBUS_DEPLOYMENT_HPP_

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/DBus/DBusDeployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace com {
namespace harman {
namespace pres {
namespace devprestypes_ {

// typecollection-specific deployment types
typedef CommonAPI::EmptyDeployment eModeNameDeployment_t;

typedef CommonAPI::EmptyDeployment eModeStatusDeployment_t;

typedef CommonAPI::EmptyDeployment eDeviceTypeDeployment_t;

typedef CommonAPI::EmptyDeployment eAcknowledgementDeployment_t;

typedef CommonAPI::EmptyDeployment eRequestStatusDeployment_t;

typedef CommonAPI::EmptyDeployment eErrorStatusDeployment_t;

typedef CommonAPI::EmptyDeployment eDeviceFilterDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::EmptyDeployment
> sConflictModeDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> sModeInfoDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::ArrayDeployment<
        CommonAPI::DBus::StructDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment
        >
    >
> sDeviceInfoDeployment_t;

typedef CommonAPI::EmptyDeployment eIAP2TransportDeployment_t;

typedef CommonAPI::EmptyDeployment eIAP2ModeDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> sPrefByDevTypeDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::EmptyDeployment
> sPrefByDevNameDeployment_t;

typedef CommonAPI::DBus::ArrayDeployment<
    CommonAPI::DBus::StructDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StringDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::ArrayDeployment<
            CommonAPI::DBus::StructDeployment<
                CommonAPI::EmptyDeployment,
                CommonAPI::EmptyDeployment,
                CommonAPI::EmptyDeployment
            >
        >
    >
> vDeviceInfoDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::ArrayDeployment<
        CommonAPI::EmptyDeployment
    >,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment
> sIAP2InfoDeployment_t;

typedef CommonAPI::DBus::ArrayDeployment<
    CommonAPI::DBus::StructDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::ArrayDeployment<
            CommonAPI::EmptyDeployment
        >,
        CommonAPI::DBus::StringDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StringDeployment
    >
> vIAP2InfoDeployment_t;


// typecollection-specific deployments

} // namespace devprestypes_
} // namespace pres
} // namespace harman
} // namespace com
} // namespace v1

#endif // V1_COM_HARMAN_PRES_DEVPRESTYPES_DBUS_DEPLOYMENT_HPP_

/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/

#ifndef V3_COM_HARMAN_AUDIO_AUDIOPRESCTRL_AUDIO_PRES_CTRL_TYPES_DBUS_DEPLOYMENT_HPP_
#define V3_COM_HARMAN_AUDIO_AUDIOPRESCTRL_AUDIO_PRES_CTRL_TYPES_DBUS_DEPLOYMENT_HPP_

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/DBus/DBusDeployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v3 {
namespace com {
namespace harman {
namespace audio {
namespace audioPresCtrl {
namespace audioPresCtrlTypes_ {

// typecollection-specific deployment types
typedef CommonAPI::EmptyDeployment SourceIdDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StructDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StringDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StringDeployment
    >
> mEntSrcsInfoDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> mBeepStatusDeployment_t;

typedef CommonAPI::EmptyDeployment eAudioPresErrorsDeployment_t;

typedef CommonAPI::EmptyDeployment eEntertainmentSrcsDeployment_t;

typedef CommonAPI::EmptyDeployment eInterruptSrcsDeployment_t;

typedef CommonAPI::EmptyDeployment eSourceAvailablityDeployment_t;

typedef CommonAPI::EmptyDeployment eEntSourceTypeDeployment_t;

typedef CommonAPI::EmptyDeployment eToggleDirectionDeployment_t;

typedef CommonAPI::EmptyDeployment eUserOptionDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> sSourceTypeDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> sSourceVolumeDeployment_t;

typedef CommonAPI::EmptyDeployment eSampleRateTypeDeployment_t;

typedef CommonAPI::DBus::ArrayDeployment<
    CommonAPI::DBus::StringDeployment
> ListItemsDeployment_t;

typedef CommonAPI::EmptyDeployment eAudioAttributeDeployment_t;

typedef CommonAPI::EmptyDeployment eResetTypeDeployment_t;

typedef CommonAPI::EmptyDeployment eDiagModeTypeDeployment_t;

typedef CommonAPI::EmptyDeployment eDiagSpeakerMaskDeployment_t;

typedef CommonAPI::EmptyDeployment eOccupancyModeTypeDeployment_t;

typedef CommonAPI::EmptyDeployment eVolumeGroupDeployment_t;

typedef CommonAPI::DBus::VariantDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::MapDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment
    >,
    CommonAPI::EmptyDeployment
> uAttributeValueDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::VariantDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StringDeployment,
        CommonAPI::MapDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment
        >,
        CommonAPI::EmptyDeployment
    >
> mAttributeDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment
> sSourceInfoDeployment_t;


// typecollection-specific deployments

} // namespace audioPresCtrlTypes_
} // namespace audioPresCtrl
} // namespace audio
} // namespace harman
} // namespace com
} // namespace v3

#endif // V3_COM_HARMAN_AUDIO_AUDIOPRESCTRL_AUDIO_PRES_CTRL_TYPES_DBUS_DEPLOYMENT_HPP_

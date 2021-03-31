/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/

#ifndef V1_COM_HARMAN_MMPRES_MM_PRES_TYPES_DBUS_DEPLOYMENT_HPP_
#define V1_COM_HARMAN_MMPRES_MM_PRES_TYPES_DBUS_DEPLOYMENT_HPP_

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif
#include <CommonAPI/DBus/DBusDeployment.hpp>
#undef COMMONAPI_INTERNAL_COMPILATION

namespace v1 {
namespace com {
namespace harman {
namespace mmpres {
namespace MMPresTypes_ {

// typecollection-specific deployment types
typedef CommonAPI::EmptyDeployment eSlotTypeDeployment_t;

typedef CommonAPI::EmptyDeployment eFileSystemContentTypeDeployment_t;

typedef CommonAPI::EmptyDeployment eDeviceTypeDeployment_t;

typedef CommonAPI::EmptyDeployment eDeviceCapabilitiesDeployment_t;

typedef CommonAPI::EmptyDeployment eRemotePlayerCapabilityDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> tRemotePlayerCapabilityDeployment_t;

typedef CommonAPI::EmptyDeployment eRepeatModeDeployment_t;

typedef CommonAPI::EmptyDeployment eShuffleModeDeployment_t;

typedef CommonAPI::EmptyDeployment eSlotStateDeployment_t;

typedef CommonAPI::EmptyDeployment eSyncStateDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> SyncMapDeployment_t;

typedef CommonAPI::EmptyDeployment eTitleContentTypeDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> ContentInfoMapDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::MapDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment
    >,
    CommonAPI::DBus::StructDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment
    >
> tDeviceDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::MapDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment
    >
> BrowseCategoryMapDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::MapDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::MapDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment
        >
    >
> tDeviceBrowseCategoryInfoDeployment_t;

typedef CommonAPI::DBus::ArrayDeployment<
    CommonAPI::DBus::StructDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::MapDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::MapDeployment<
                CommonAPI::EmptyDeployment,
                CommonAPI::EmptyDeployment
            >
        >
    >
> tDeviceBrowseCategoryListDeployment_t;

typedef CommonAPI::EmptyDeployment eBTMediaProfileDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> tBTStatusDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment
> tAdditionalDeviceInfoDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StructDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StringDeployment,
        CommonAPI::MapDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment
        >,
        CommonAPI::DBus::StructDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment
        >
    >
> tSlotDeployment_t;

typedef CommonAPI::DBus::ArrayDeployment<
    CommonAPI::DBus::StructDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StructDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment,
            CommonAPI::DBus::StringDeployment,
            CommonAPI::MapDeployment<
                CommonAPI::EmptyDeployment,
                CommonAPI::EmptyDeployment
            >,
            CommonAPI::DBus::StructDeployment<
                CommonAPI::EmptyDeployment,
                CommonAPI::EmptyDeployment,
                CommonAPI::EmptyDeployment
            >
        >
    >
> tSlotListDeployment_t;

typedef CommonAPI::EmptyDeployment eMetadataTypeDeployment_t;

typedef CommonAPI::EmptyDeployment eFilterTypeDeployment_t;

typedef CommonAPI::EmptyDeployment ePrevBrowseLevelDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> FilterIDMapDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment
> FilterMapDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment
> MetadataStringMapDeployment_t;

typedef CommonAPI::EmptyDeployment eSessionQueryTypesDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> MetadataCountMapDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::MapDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment
    >,
    CommonAPI::MapDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StringDeployment
    >,
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment
> tMetadataItemDeployment_t;

typedef CommonAPI::DBus::ArrayDeployment<
    CommonAPI::DBus::StructDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StringDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::MapDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment
        >,
        CommonAPI::MapDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::DBus::StringDeployment
        >,
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StringDeployment,
        CommonAPI::DBus::StringDeployment,
        CommonAPI::DBus::StringDeployment
    >
> MetadataItemListDeployment_t;

typedef CommonAPI::EmptyDeployment eMediaErrorDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> MediaErrorMapDeployment_t;

typedef CommonAPI::EmptyDeployment eCallResultDeployment_t;

typedef CommonAPI::EmptyDeployment ePlayStateDeployment_t;

typedef CommonAPI::EmptyDeployment eScanStatusDeployment_t;

typedef CommonAPI::EmptyDeployment eTrackSeekSpeedDeployment_t;

typedef CommonAPI::EmptyDeployment ePlaybackSpeedDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> tTrackStateDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::DBus::StringDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> tNowPlayingInfoDeployment_t;

typedef CommonAPI::EmptyDeployment eArtWorkAvailabilityStatusDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StringDeployment
> tArtWorkImagePropertyDeployment_t;

typedef CommonAPI::EmptyDeployment tArtWorkImagePositionTypeDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::StructDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StringDeployment
    >
> tArtWorkArtImageDeployment_t;

typedef CommonAPI::DBus::ArrayDeployment<
    CommonAPI::DBus::StructDeployment<
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::EmptyDeployment,
        CommonAPI::DBus::StructDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment,
            CommonAPI::DBus::StringDeployment
        >
    >
> artWorkImageInfoDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::DBus::ArrayDeployment<
        CommonAPI::DBus::StructDeployment<
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment,
            CommonAPI::EmptyDeployment,
            CommonAPI::DBus::StructDeployment<
                CommonAPI::EmptyDeployment,
                CommonAPI::EmptyDeployment,
                CommonAPI::EmptyDeployment,
                CommonAPI::DBus::StringDeployment
            >
        >
    >
> tAlbumArtInformationDeployment_t;

typedef CommonAPI::DBus::StructDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> tScreenDeployment_t;

typedef CommonAPI::EmptyDeployment eSubtitleStatusDeployment_t;

typedef CommonAPI::EmptyDeployment eQueryStatusDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> SyncProgressMapDeployment_t;

typedef CommonAPI::MapDeployment<
    CommonAPI::EmptyDeployment,
    CommonAPI::EmptyDeployment
> isPlayableItemAvailableMapDeployment_t;

typedef CommonAPI::EmptyDeployment databaseErrorDeployment_t;

typedef CommonAPI::EmptyDeployment startIndexOptionDeployment_t;


// typecollection-specific deployments

} // namespace MMPresTypes_
} // namespace mmpres
} // namespace harman
} // namespace com
} // namespace v1

#endif // V1_COM_HARMAN_MMPRES_MM_PRES_TYPES_DBUS_DEPLOYMENT_HPP_

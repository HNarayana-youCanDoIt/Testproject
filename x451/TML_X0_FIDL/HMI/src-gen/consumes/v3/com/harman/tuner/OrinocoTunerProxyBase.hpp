/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
/**
 * description: Orinoco specific tuner interface. This interface is a facade to a bunch of
 *   plattform interfaces in order to provide a simplified access to tuner data and
 *   functionality.
 * author: Harman, CoC Tuner, Dirk Engel (c) copyright 2016
 */
#ifndef V3_COM_HARMAN_TUNER_Orinoco_Tuner_PROXY_BASE_HPP_
#define V3_COM_HARMAN_TUNER_Orinoco_Tuner_PROXY_BASE_HPP_

#include <v3/com/harman/tuner/OrinocoTuner.hpp>


#include <v3/com/harman/tuner/OrinocoTunerTypes.hpp>

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
#include <CommonAPI/Event.hpp>
#include <CommonAPI/Proxy.hpp>
#include <functional>
#include <future>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace v3 {
namespace com {
namespace harman {
namespace tuner {

class OrinocoTunerProxyBase
    : virtual public CommonAPI::Proxy {
public:
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::CurrentStationListSortingMode> StationListSortingModeAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::AudioStationUpdateMode> AudioStationUpdateModeAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::AudioCurrentStation> AudioCurrentStationAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::AudioStationList> AudioStationListAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::StationList> AudioPresetListAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::AnnouncementStatus> AnnouncementCurrentStatusAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::AmFmRegionInfo> AmfmControlRegionInfoAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::CurrentSwitchState> AmfmControlAfSwitchAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::CurrentSwitchState> AmfmControlRegSwitchAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::CurrentAmFmHdBallgameMode> AmfmControlHdBallgameModeAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::CurrentAmFmHdMode> AmfmControlHdModeAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::DabRegionInfo> DabControlRegionInfoAttribute;
    typedef CommonAPI::ObservableReadonlyAttribute<::v3::com::harman::tuner::OrinocoTunerTypes::CurrentSwitchState> DabControlFollowingSwitchAttribute;
    typedef CommonAPI::Event<
        ::v3::com::harman::tuner::OrinocoTunerTypes::CurrentStation
    > StationCurrentStationEvent;
    typedef CommonAPI::Event<
        ::v3::com::harman::tuner::OrinocoTunerTypes::StationList
    > StationStationListEvent;
    typedef CommonAPI::Event<
        ::v3::com::harman::tuner::OrinocoTunerTypes::ProcessedMethod, uint32_t, ::v3::com::harman::tuner::OrinocoTunerTypes::Result
    > MethodProcessedEvent;

    typedef std::function<void(const CommonAPI::CallStatus&)> StationSelectStationAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> StationStorePresetAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> StationDeletePresetAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> AudioSetStationUpdateModeAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> AnnouncementSetConfigurationAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> AnnouncementAbortAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> AmfmControlSetAfSwitchAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> AmfmControlSetRegSwitchAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> AmfmControlSetHdModeAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> AmfmControlSetHdBallgameModeAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> DabControlSetFollowingSwitchAsyncCallback;
    typedef std::function<void(const CommonAPI::CallStatus&)> ForceBroadcastUpdateAsyncCallback;

    /**
     * description: The sorting mode used for station lists (except from type LIST_PRESET)
     */
    virtual StationListSortingModeAttribute& getStationListSortingModeAttribute() = 0;
    /**
     * description: The the station update mode for the current active tuner audio source.
     */
    virtual AudioStationUpdateModeAttribute& getAudioStationUpdateModeAttribute() = 0;
    /**
     * description: The current active tuner source and station.
     */
    virtual AudioCurrentStationAttribute& getAudioCurrentStationAttribute() = 0;
    /**
     * description: The station list of the current tuner audio source
     */
    virtual AudioStationListAttribute& getAudioStationListAttribute() = 0;
    /**
     * description: The preset list of the current tuner audio source (content depends on
     *   configuration: mixed mode or dedicated)
     */
    virtual AudioPresetListAttribute& getAudioPresetListAttribute() = 0;
    /**
     * description: All available information about the current settings and state of
     *   announcements. Announcement monitoring can be activated/deactivated by
     *   "announcementSetConfiguration". An active announcement can be aborted by
     *   "announcementAbort".
     */
    virtual AnnouncementCurrentStatusAttribute& getAnnouncementCurrentStatusAttribute() = 0;
    /**
     * description: The AM/FM region code and waveband information
     */
    virtual AmfmControlRegionInfoAttribute& getAmfmControlRegionInfoAttribute() = 0;
    /**
     * description: The current state of the alternative frequency (AF) switch. The switch can be
     *   controlled by the request "amfmControlSetAfSwitch".
     */
    virtual AmfmControlAfSwitchAttribute& getAmfmControlAfSwitchAttribute() = 0;
    /**
     * description: The current state of the regionalization (REG) switch. The switch can be
     *   controlled by the request "amfmControlSetRegSwitch".
     */
    virtual AmfmControlRegSwitchAttribute& getAmfmControlRegSwitchAttribute() = 0;
    /**
     * description: The current state of the HD ballgame mode switch. The switch can be controlled
     *   by the request "amfmControlSetHdBallgameMode".
     */
    virtual AmfmControlHdBallgameModeAttribute& getAmfmControlHdBallgameModeAttribute() = 0;
    /**
     * description: The current HD mode. The switch can be controlled by the request
     *   "amfmControlSetHdMode".
     */
    virtual AmfmControlHdModeAttribute& getAmfmControlHdModeAttribute() = 0;
    /**
     * description: The DAB region code
     */
    virtual DabControlRegionInfoAttribute& getDabControlRegionInfoAttribute() = 0;
    /**
     * description: The current state of the DAB/FM service following switch (DAB/DAB cannot be
     *   disabled via this interface). The switch can be controlled by the request
     *   "dabControlSetFollowingSwitch".
     */
    virtual DabControlFollowingSwitchAttribute& getDabControlFollowingSwitchAttribute() = 0;

    /**
     * description: Current station update. Updates of different source might happen in parallel
     *   (not only for the current audio source). If FM, for example, is the active
     *   audio source according to attribute "audioCurrentSource" this is also the
     *   currently active tuner station which is audible.
     */
    virtual StationCurrentStationEvent& getStationCurrentStationEvent() = 0;
    /**
     * description: List update. Check "stationList.source" and "stationList.listType" to
     *   distinguish between different lists.
     */
    virtual StationStationListEvent& getStationStationListEvent() = 0;
    /**
     * description: Optional: Asynchronous method response (will be called after all necessary
     *   action is done to fulfill a specific request call).     Usually, the handle of
     *   the request that caused a change of an attribute is updated within the
     *   attribute. But in case of multiple clients or if many calls are done in quick
     *   succession only the last request will lead to the final state and will be
     *   visible in the attribute.    However, by using this callback you'll be
     *   informed about each processed request even if it's result will have no actual
     *   effect because of overwriting (last wins strategy).
     */
    virtual MethodProcessedEvent& getMethodProcessedEvent() = 0;

    /**
     * description: Any manipulation of the current station: Selection by list / direct frequency
     *   tuning / preset selection / starting a search run. As result the information
     *   "stationCurrentStation" is updated with the given handle.
     */
    virtual void stationSelectStation(const ::v3::com::harman::tuner::OrinocoTunerTypes::StationSelector &_stationSelector, const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> stationSelectStationAsync(const ::v3::com::harman::tuner::OrinocoTunerTypes::StationSelector &_stationSelector, const uint32_t &_handle, StationSelectStationAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: Store the given station in corresponding preset list (depends on project
     *   configuration wether there is ony list per source or one common list) and
     *   assign the given preset number for later recalls (via "stationStartTune").   
     *   As result the corresponding information "stationStationList" is updated with
     *   the given handle.
     */
    virtual void stationStorePreset(const ::v3::com::harman::tuner::OrinocoTunerTypes::StationSelector &_stationSelector, const uint32_t &_preset, const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> stationStorePresetAsync(const ::v3::com::harman::tuner::OrinocoTunerTypes::StationSelector &_stationSelector, const uint32_t &_preset, const uint32_t &_handle, StationStorePresetAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: Remove given preset number from corresponding preset list.     As result the
     *   corresponding information "stationStationList" is updated with the given handle
     */
    virtual void stationDeletePreset(const uint32_t &_preset, const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> stationDeletePresetAsync(const uint32_t &_preset, const uint32_t &_handle, StationDeletePresetAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: Customize the content and updates of current station and station list
     */
    virtual void audioSetStationUpdateMode(const ::v3::com::harman::tuner::OrinocoTunerTypes::StationUpdateMode &_updateMode, const bool &_enable, const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> audioSetStationUpdateModeAsync(const ::v3::com::harman::tuner::OrinocoTunerTypes::StationUpdateMode &_updateMode, const bool &_enable, const uint32_t &_handle, AudioSetStationUpdateModeAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: Enable/disable the announcement monitoring for FM and DAB.    As result the
     *   attribute "announcementCurrentStatus" is updated with the given handle
     */
    virtual void announcementSetConfiguration(const ::v3::com::harman::tuner::OrinocoTunerTypes::AnnouncementConfiguration &_configuration, const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> announcementSetConfigurationAsync(const ::v3::com::harman::tuner::OrinocoTunerTypes::AnnouncementConfiguration &_configuration, const uint32_t &_handle, AnnouncementSetConfigurationAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: Abort an active announcement. As a result the attribute
     *   "announcementCurrentStatus" is updated with the given handle.
     */
    virtual void announcementAbort(const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> announcementAbortAsync(const uint32_t &_handle, AnnouncementAbortAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: [AM/FM only] Set the desired RDS alternative frequency (AF) state. As result
     *   the attribute "amfmControlAfSwitch" is updated.
     */
    virtual void amfmControlSetAfSwitch(const bool &_enable, const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> amfmControlSetAfSwitchAsync(const bool &_enable, const uint32_t &_handle, AmfmControlSetAfSwitchAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: [AM/FM only] Set the desired RDS regionalisation (REG) state. As result the
     *   attribute "amfmControlRegSwitch" is updated.
     */
    virtual void amfmControlSetRegSwitch(const bool &_enable, const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> amfmControlSetRegSwitchAsync(const bool &_enable, const uint32_t &_handle, AmfmControlSetRegSwitchAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: [AM/FM only] Set the desired HD mode. As result the attribute
     *   "amfmControlHdMode" is updated.
     */
    virtual void amfmControlSetHdMode(const ::v3::com::harman::tuner::OrinocoTunerTypes::AmFmHdMode &_hdMode, const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> amfmControlSetHdModeAsync(const ::v3::com::harman::tuner::OrinocoTunerTypes::AmFmHdMode &_hdMode, const uint32_t &_handle, AmfmControlSetHdModeAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: [AM/FM only] Set the desired HD ballgame mode. As result the attribute
     *   "amfmControlHdBallgameMode" is updated.
     */
    virtual void amfmControlSetHdBallgameMode(const ::v3::com::harman::tuner::OrinocoTunerTypes::AmFmHdBallgameMode &_hdBallgameMode, const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> amfmControlSetHdBallgameModeAsync(const ::v3::com::harman::tuner::OrinocoTunerTypes::AmFmHdBallgameMode &_hdBallgameMode, const uint32_t &_handle, AmfmControlSetHdBallgameModeAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: Set the desired service following at the FollowingMaster. As result the
     *   attribute "dabControlFollowingSwitch" is updated with the given handle.   
     *   Note: This switch only affects DAB/FM linking, DAB/DAB is always on
     */
    virtual void dabControlSetFollowingSwitch(const bool &_enable, const uint32_t &_handle, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> dabControlSetFollowingSwitchAsync(const bool &_enable, const uint32_t &_handle, DabControlSetFollowingSwitchAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
    /**
     * description: Request initial broadcast update at startup (stationCurrentStation,
     *   stationStationList) in order to force an "on change" update.
     */
    virtual void forceBroadcastUpdate(CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info = nullptr) = 0;
    virtual std::future<CommonAPI::CallStatus> forceBroadcastUpdateAsync(ForceBroadcastUpdateAsyncCallback _callback = nullptr, const CommonAPI::CallInfo *_info = nullptr) = 0;
};

} // namespace tuner
} // namespace harman
} // namespace com
} // namespace v3


// Compatibility
namespace v3_0 = v3;

#endif // V3_COM_HARMAN_TUNER_Orinoco_Tuner_PROXY_BASE_HPP_

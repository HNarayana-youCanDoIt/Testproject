/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V0_COM_HARMAN_DCIF_Engg_Menu_Pres_Ctrl_DBUS_PROXY_HPP_
#define V0_COM_HARMAN_DCIF_Engg_Menu_Pres_Ctrl_DBUS_PROXY_HPP_

#include <v0/com/harman/dcif/EnggMenuPresCtrlProxyBase.hpp>
#include "v0/com/harman/dcif/EnggMenuPresCtrlDBusDeployment.hpp"

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/DBus/DBusAddress.hpp>
#include <CommonAPI/DBus/DBusFactory.hpp>
#include <CommonAPI/DBus/DBusProxy.hpp>
#include <CommonAPI/DBus/DBusAddressTranslator.hpp>
#include <CommonAPI/DBus/DBusAttribute.hpp>
#include <CommonAPI/DBus/DBusEvent.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

#include <string>

namespace v0 {
namespace com {
namespace harman {
namespace dcif {

class EnggMenuPresCtrlDBusProxy
    : virtual public EnggMenuPresCtrlProxyBase, 
      virtual public CommonAPI::DBus::DBusProxy {
public:
    EnggMenuPresCtrlDBusProxy(
        const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection);

    virtual ~EnggMenuPresCtrlDBusProxy() { }

    virtual LogStatusAttribute& getLogStatusAttribute();
    virtual TunerDataAttribute& getTunerDataAttribute();
    virtual MediaDataAttribute& getMediaDataAttribute();

    virtual FactoryResetCompleteEvent& getFactoryResetCompleteEvent();

    /**
     * description: method to start logging of DBUS,DLT RAM and CPU Measurement logs 		DBUS_LOGS =
     *   0 		DLT_LOGS = 1 		CPU_MEASUREMENT_LOGS = 2 		RAM_MEASUREMENT_LOGS = 3
     */
    virtual void startLogging(const ::v0::com::harman::dcif::EnggMenuTypes::logType &_typeOfLogs, CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::logType &_activeLogType, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> startLoggingAsync(const ::v0::com::harman::dcif::EnggMenuTypes::logType &_typeOfLogs, StartLoggingAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to start logging of DBUS,DLT RAM and CPU Measurement logs
     */
    virtual void startSystemLogging(CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> startSystemLoggingAsync(StartSystemLoggingAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to stop logging of DBUS,DLT RAM and CPU Measurement logs
     */
    virtual void stopSystemLogging(CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> stopSystemLoggingAsync(StopSystemLoggingAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    virtual void extractLogs(CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::extractLogsError_enum &_logError, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> extractLogsAsync(ExtractLogsAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to stop logging of DBUS,DLT RAM and CPU Measurement logs 		DBUS_LOGS = 0
     *   		DLT_LOGS = 1 		CPU_MEASUREMENT_LOGS = 2 		RAM_MEASUREMENT_LOGS = 3
     */
    virtual void stopLogging(const ::v0::com::harman::dcif::EnggMenuTypes::logType &_typeOfLogs, CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::logType &_activeLogType, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> stopLoggingAsync(const ::v0::com::harman::dcif::EnggMenuTypes::logType &_typeOfLogs, StopLoggingAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to set Display Brightness
     */
    virtual void setDisplayBrightness(const uint16_t &_brightnessValue, CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setDisplayBrightnessAsync(const uint16_t &_brightnessValue, SetDisplayBrightnessAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to read Display Brightness
     */
    virtual void getDisplayBrightness(CommonAPI::CallStatus &_internalCallStatus, uint16_t &_brightnessValue, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> getDisplayBrightnessAsync(GetDisplayBrightnessAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to set Button Panel Brightness
     */
    virtual void setButtonPanelBrightness(const uint16_t &_brightnessValue, CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setButtonPanelBrightnessAsync(const uint16_t &_brightnessValue, SetButtonPanelBrightnessAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to read Button Panel Brightness
     */
    virtual void getButtonPanelBrightness(CommonAPI::CallStatus &_internalCallStatus, uint16_t &_brightnessValue, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> getButtonPanelBrightnessAsync(GetButtonPanelBrightnessAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to read media type
     */
    virtual void getMediaType(CommonAPI::CallStatus &_internalCallStatus, std::string &_mediaType, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> getMediaTypeAsync(GetMediaTypeAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to read track name
     */
    virtual void getTrackName(CommonAPI::CallStatus &_internalCallStatus, std::string &_trackName, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> getTrackNameAsync(GetTrackNameAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to launch/stop test automation service
     */
    virtual void testAutomationLaunch(const bool &_isEnable, CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> testAutomationLaunchAsync(const bool &_isEnable, TestAutomationLaunchAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to set the system IP- Static/Dynamic
     */
    virtual void setSystemIP(const ::v0::com::harman::dcif::EnggMenuTypes::ipType_enum &_typeOfIP, CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setSystemIPAsync(const ::v0::com::harman::dcif::EnggMenuTypes::ipType_enum &_typeOfIP, SetSystemIPAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to read the  		tuner data.
     */
    virtual void getTunerData(CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::tunerInfo &_tunerData, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> getTunerDataAsync(GetTunerDataAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to read the media data.
     */
    virtual void getMediaData(CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::mediaInfo &_mediaData, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> getMediaDataAsync(GetMediaDataAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Perform factory reset of peristent data, media,  	tuner and bluetooth data   
     *   	- Key Pres 	- Mute audio sources 	- clear media data 	- reset persistency
     *   data 	- Disconnect the bluetooth device and delete the paired device list 	-
     *   Vehicle Settings reset
     */
    virtual void performFactoryReset(CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> performFactoryResetAsync(PerformFactoryResetAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method to turn on device mode.
     */
    virtual void setDeviceMode(const ::v0::com::harman::dcif::EnggMenuTypes::modeType &_typeOfMode, CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::modeType &_activatedMode, ::v0::com::harman::dcif::EnggMenuTypes::deviceModeStatus &_dmStatus, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setDeviceModeAsync(const ::v0::com::harman::dcif::EnggMenuTypes::modeType &_typeOfMode, SetDeviceModeAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Method to update the Mihup configuration file from the USB
     */
    virtual void updateMihupLib(CommonAPI::CallStatus &_internalCallStatus, ::v0::com::harman::dcif::EnggMenuTypes::retStatus &_status, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> updateMihupLibAsync(UpdateMihupLibAsyncCallback _callback, const CommonAPI::CallInfo *_info);


    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

private:
   
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<LogStatusAttribute, ::v0::com::harman::dcif::EnggMenuTypes_::loggingStatusDeployment_t>> logStatus_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<TunerDataAttribute, ::v0::com::harman::dcif::EnggMenuTypes_::tunerInfoDeployment_t>> tunerData_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<MediaDataAttribute, ::v0::com::harman::dcif::EnggMenuTypes_::mediaInfoDeployment_t>> mediaData_;

    CommonAPI::DBus::DBusEvent<FactoryResetCompleteEvent, CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment>> factoryResetComplete_;

};

} // namespace dcif
} // namespace harman
} // namespace com
} // namespace v0

#endif // V0_COM_HARMAN_DCIF_Engg_Menu_Pres_Ctrl_DBUS_PROXY_HPP_


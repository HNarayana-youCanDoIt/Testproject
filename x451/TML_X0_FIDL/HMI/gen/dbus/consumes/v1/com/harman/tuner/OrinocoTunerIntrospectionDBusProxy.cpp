/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
/**
 * description: Orinoco specific tuner introspection interface. This interface is a facade to a
 *   bunch of platform     interfaces in order to provide a simplified access to
 *   tuner diagnosis/engineering data and functionality.
 * author: Harman, CoC Tuner, Dirk Engel (c) copyright 2016
 */
#include <v1/com/harman/tuner/OrinocoTunerIntrospectionDBusProxy.hpp>

namespace v1 {
namespace com {
namespace harman {
namespace tuner {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createOrinocoTunerIntrospectionDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection) {
	return std::make_shared<OrinocoTunerIntrospectionDBusProxy>(_address, _connection);
}

INITIALIZER(registerOrinocoTunerIntrospectionDBusProxy) {
     CommonAPI::DBus::Factory::get()->registerProxyCreateMethod(
		OrinocoTunerIntrospection::getInterface(),
		&createOrinocoTunerIntrospectionDBusProxy);
}

OrinocoTunerIntrospectionDBusProxy::OrinocoTunerIntrospectionDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection)
	:	CommonAPI::DBus::DBusProxy(_address, _connection)
,		powerSync_(*this, "onPowerSyncAttributeChanged", "au", "getPowerSyncAttribute", static_cast<::v3::com::harman::tuner::OrinocoTunerTypes_::UInt32sDeployment_t*>(nullptr)),
		antennaInfos_(*this, "onAntennaInfosAttributeChanged", "a(siii)", "getAntennaInfosAttribute", static_cast<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes_::AntennaInfosDeployment_t*>(nullptr)),
		devicesInIntrospectionMode_(*this, "onDevicesInIntrospectionModeAttributeChanged", "i", "getDevicesInIntrospectionModeAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		versionInfos_(*this, "onVersionInfosAttributeChanged", "a(is)", "getVersionInfosAttribute", static_cast<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes_::VersionInfosDeployment_t*>(nullptr)),
		activeErrors_(*this, "onActiveErrorsAttributeChanged", "ai", "getActiveErrorsAttribute", static_cast<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes_::ErrorElementsDeployment_t*>(nullptr))
,		factoryReset_(*this, "factoryReset", "i", std::make_tuple(static_cast<CommonAPI::EmptyDeployment*>(nullptr))),
		qualityMonitor_(*this, "qualityMonitor", "a(uuusysqyn)a(iuydduqyuqbbbsun)a((ddd)(yiiiiyy)(uiii)(yyyq))", std::make_tuple(static_cast<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes_::QualityAmFmsDeployment_t*>(nullptr), static_cast<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes_::QualityDabsDeployment_t*>(nullptr), static_cast<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes_::QualityDrmsDeployment_t*>(nullptr)))
{
}

      OrinocoTunerIntrospectionDBusProxy::PowerSyncAttribute& OrinocoTunerIntrospectionDBusProxy::getPowerSyncAttribute() {
          return powerSync_;
      }
      OrinocoTunerIntrospectionDBusProxy::AntennaInfosAttribute& OrinocoTunerIntrospectionDBusProxy::getAntennaInfosAttribute() {
          return antennaInfos_;
      }
      OrinocoTunerIntrospectionDBusProxy::DevicesInIntrospectionModeAttribute& OrinocoTunerIntrospectionDBusProxy::getDevicesInIntrospectionModeAttribute() {
          return devicesInIntrospectionMode_;
      }
      OrinocoTunerIntrospectionDBusProxy::VersionInfosAttribute& OrinocoTunerIntrospectionDBusProxy::getVersionInfosAttribute() {
          return versionInfos_;
      }
      OrinocoTunerIntrospectionDBusProxy::ActiveErrorsAttribute& OrinocoTunerIntrospectionDBusProxy::getActiveErrorsAttribute() {
          return activeErrors_;
      }

OrinocoTunerIntrospectionDBusProxy::FactoryResetEvent& OrinocoTunerIntrospectionDBusProxy::getFactoryResetEvent() {
    return factoryReset_;
}
OrinocoTunerIntrospectionDBusProxy::QualityMonitorEvent& OrinocoTunerIntrospectionDBusProxy::getQualityMonitorEvent() {
    return qualityMonitor_;
}
    
    /**
     * description: Perform factory reset of peristent data, broadcast factoryReset will be called
     *   when done
     */
    void OrinocoTunerIntrospectionDBusProxy::performFactoryReset(const ::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::FactoryResetMode &_factoryResetMode, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::FactoryResetMode, CommonAPI::EmptyDeployment> deploy_factoryResetMode(_factoryResetMode, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::FactoryResetMode, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            >
        	>::callMethodWithReply(
        *this,
        "performFactoryReset",
        "i",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_factoryResetMode,
_internalCallStatus);
}
    std::future<CommonAPI::CallStatus> OrinocoTunerIntrospectionDBusProxy::performFactoryResetAsync(const ::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::FactoryResetMode &_factoryResetMode, PerformFactoryResetAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::FactoryResetMode, CommonAPI::EmptyDeployment> deploy_factoryResetMode(_factoryResetMode, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::FactoryResetMode, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            >
        	>::callMethodAsync(
        *this,
        "performFactoryReset",
        "i",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_factoryResetMode,
        [_callback] (CommonAPI::CallStatus _internalCallStatus) {
        	if (_callback)
        		_callback(_internalCallStatus);
        },
        std::make_tuple());
    }
    /**
     * description: Disable/enable antenna power supply. After toggling the power supply the
     *   corresponding "antennaInfo"        entry will change
     */
    void OrinocoTunerIntrospectionDBusProxy::switchAntennaPowerSupply(const std::string &_name, const bool &_enable, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> deploy_name(_name, static_cast<CommonAPI::DBus::StringDeployment*>(nullptr));
        CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> deploy_enable(_enable, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment >,
            CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            >
        	>::callMethodWithReply(
        *this,
        "switchAntennaPowerSupply",
        "sb",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_name, deploy_enable,
_internalCallStatus);
}
    std::future<CommonAPI::CallStatus> OrinocoTunerIntrospectionDBusProxy::switchAntennaPowerSupplyAsync(const std::string &_name, const bool &_enable, SwitchAntennaPowerSupplyAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> deploy_name(_name, static_cast<CommonAPI::DBus::StringDeployment*>(nullptr));
        CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> deploy_enable(_enable, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment >,
            CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            >
        	>::callMethodAsync(
        *this,
        "switchAntennaPowerSupply",
        "sb",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_name, deploy_enable,
        [_callback] (CommonAPI::CallStatus _internalCallStatus) {
        	if (_callback)
        		_callback(_internalCallStatus);
        },
        std::make_tuple());
    }
    /**
     * description: Enable introspection mode        CAUTION: The introspection mode can lead to
     *   unexspected behavior and reduced functionality, don't forget to disable again!
     */
    void OrinocoTunerIntrospectionDBusProxy::switchIntrospectionMode(const ::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device &_device, const bool &_enable, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment> deploy_device(_device, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> deploy_enable(_enable, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment >,
            CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            >
        	>::callMethodWithReply(
        *this,
        "switchIntrospectionMode",
        "ib",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_device, deploy_enable,
_internalCallStatus);
}
    std::future<CommonAPI::CallStatus> OrinocoTunerIntrospectionDBusProxy::switchIntrospectionModeAsync(const ::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device &_device, const bool &_enable, SwitchIntrospectionModeAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment> deploy_device(_device, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> deploy_enable(_enable, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment >,
            CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            >
        	>::callMethodAsync(
        *this,
        "switchIntrospectionMode",
        "ib",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_device, deploy_enable,
        [_callback] (CommonAPI::CallStatus _internalCallStatus) {
        	if (_callback)
        		_callback(_internalCallStatus);
        },
        std::make_tuple());
    }
    /**
     * description: 
     */
    void OrinocoTunerIntrospectionDBusProxy::tune(const ::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device &_device, const uint8_t &_deviceInstance, const uint32_t &_frequency, const std::string &_frequencyLabel, const bool &_automaticServiceSelection, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment> deploy_device(_device, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<uint8_t, CommonAPI::EmptyDeployment> deploy_deviceInstance(_deviceInstance, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<uint32_t, CommonAPI::EmptyDeployment> deploy_frequency(_frequency, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> deploy_frequencyLabel(_frequencyLabel, static_cast<CommonAPI::DBus::StringDeployment*>(nullptr));
        CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> deploy_automaticServiceSelection(_automaticServiceSelection, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment >,
            CommonAPI::Deployable<uint8_t, CommonAPI::EmptyDeployment >,
            CommonAPI::Deployable<uint32_t, CommonAPI::EmptyDeployment >,
            CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment >,
            CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            >
        	>::callMethodWithReply(
        *this,
        "tune",
        "iyusb",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_device, deploy_deviceInstance, deploy_frequency, deploy_frequencyLabel, deploy_automaticServiceSelection,
_internalCallStatus);
}
    std::future<CommonAPI::CallStatus> OrinocoTunerIntrospectionDBusProxy::tuneAsync(const ::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device &_device, const uint8_t &_deviceInstance, const uint32_t &_frequency, const std::string &_frequencyLabel, const bool &_automaticServiceSelection, TuneAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment> deploy_device(_device, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<uint8_t, CommonAPI::EmptyDeployment> deploy_deviceInstance(_deviceInstance, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<uint32_t, CommonAPI::EmptyDeployment> deploy_frequency(_frequency, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment> deploy_frequencyLabel(_frequencyLabel, static_cast<CommonAPI::DBus::StringDeployment*>(nullptr));
        CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> deploy_automaticServiceSelection(_automaticServiceSelection, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment >,
            CommonAPI::Deployable<uint8_t, CommonAPI::EmptyDeployment >,
            CommonAPI::Deployable<uint32_t, CommonAPI::EmptyDeployment >,
            CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment >,
            CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            >
        	>::callMethodAsync(
        *this,
        "tune",
        "iyusb",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_device, deploy_deviceInstance, deploy_frequency, deploy_frequencyLabel, deploy_automaticServiceSelection,
        [_callback] (CommonAPI::CallStatus _internalCallStatus) {
        	if (_callback)
        		_callback(_internalCallStatus);
        },
        std::make_tuple());
    }
    /**
     * description: Start/stop sending the quality values for a specific device incl. cyclic
     *   updates (via qualityMonitor).
     */
    void OrinocoTunerIntrospectionDBusProxy::controlQualityMonitor(const ::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device &_device, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment> deploy_device(_device, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            >
        	>::callMethodWithReply(
        *this,
        "controlQualityMonitor",
        "i",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_device,
_internalCallStatus);
}
    std::future<CommonAPI::CallStatus> OrinocoTunerIntrospectionDBusProxy::controlQualityMonitorAsync(const ::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device &_device, ControlQualityMonitorAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment> deploy_device(_device, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::tuner::OrinocoTunerIntrospectionTypes::Device, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            >
        	>::callMethodAsync(
        *this,
        "controlQualityMonitor",
        "i",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_device,
        [_callback] (CommonAPI::CallStatus _internalCallStatus) {
        	if (_callback)
        		_callback(_internalCallStatus);
        },
        std::make_tuple());
    }


void OrinocoTunerIntrospectionDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
          ownVersionMajor = 1;
          ownVersionMinor = 0;
      }

      } // namespace tuner
      } // namespace harman
      } // namespace com
      } // namespace v1

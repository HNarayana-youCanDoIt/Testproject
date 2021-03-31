/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#include <v0/com/harman/VoiceAlert/VoiceAlertServiceDBusProxy.hpp>

namespace v0 {
namespace com {
namespace harman {
namespace VoiceAlert {

std::shared_ptr<CommonAPI::DBus::DBusProxy> createVoiceAlertServiceDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection) {
	return std::make_shared<VoiceAlertServiceDBusProxy>(_address, _connection);
}

INITIALIZER(registerVoiceAlertServiceDBusProxy) {
     CommonAPI::DBus::Factory::get()->registerProxyCreateMethod(
		VoiceAlertService::getInterface(),
		&createVoiceAlertServiceDBusProxy);
}

VoiceAlertServiceDBusProxy::VoiceAlertServiceDBusProxy(
	const CommonAPI::DBus::DBusAddress &_address,
	const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection)
	:	CommonAPI::DBus::DBusProxy(_address, _connection)
,		curDriveModeSig_(*this, "onCurDriveModeSigAttributeChanged", "i", "getCurDriveModeSigAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		huAlertState_(*this, "onHuAlertStateAttributeChanged", "i", "getHuAlertStateAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		huAlertHMISelection_(*this, "onHuAlertHMISelectionAttributeChanged", "setHuAlertHMISelectionAttribute", "i", "getHuAlertHMISelectionAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		huInfoFeaturePresence_(*this, "onHuInfoFeaturePresenceAttributeChanged", "i", "getHuInfoFeaturePresenceAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		huAlertStatus_(*this, "onHuAlertStatusAttributeChanged", "i", "getHuAlertStatusAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		vasStatus_(*this, "onVasStatusAttributeChanged", "b", "getVasStatusAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr)),
		huAlertStateMce_(*this, "onHuAlertStateMceAttributeChanged", "i", "getHuAlertStateMceAttribute", static_cast<CommonAPI::EmptyDeployment*>(nullptr))
{
}

      VoiceAlertServiceDBusProxy::CurDriveModeSigAttribute& VoiceAlertServiceDBusProxy::getCurDriveModeSigAttribute() {
          return curDriveModeSig_;
      }
      VoiceAlertServiceDBusProxy::HuAlertStateAttribute& VoiceAlertServiceDBusProxy::getHuAlertStateAttribute() {
          return huAlertState_;
      }
      VoiceAlertServiceDBusProxy::HuAlertHMISelectionAttribute& VoiceAlertServiceDBusProxy::getHuAlertHMISelectionAttribute() {
          return huAlertHMISelection_;
      }
      VoiceAlertServiceDBusProxy::HuInfoFeaturePresenceAttribute& VoiceAlertServiceDBusProxy::getHuInfoFeaturePresenceAttribute() {
          return huInfoFeaturePresence_;
      }
      VoiceAlertServiceDBusProxy::HuAlertStatusAttribute& VoiceAlertServiceDBusProxy::getHuAlertStatusAttribute() {
          return huAlertStatus_;
      }
      VoiceAlertServiceDBusProxy::VasStatusAttribute& VoiceAlertServiceDBusProxy::getVasStatusAttribute() {
          return vasStatus_;
      }
      VoiceAlertServiceDBusProxy::HuAlertStateMceAttribute& VoiceAlertServiceDBusProxy::getHuAlertStateMceAttribute() {
          return huAlertStateMce_;
      }

    
    void VoiceAlertServiceDBusProxy::setHuHMISelection(const ::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum &_huTypeofAlert, const bool &_alertStatus, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum &_huAlertType, bool &_status, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum, CommonAPI::EmptyDeployment> deploy_huTypeofAlert(_huTypeofAlert, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> deploy_alertStatus(_alertStatus, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum, CommonAPI::EmptyDeployment> deploy_huAlertType(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> deploy_status(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum, CommonAPI::EmptyDeployment >,
            CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum,CommonAPI::EmptyDeployment>,
            CommonAPI::Deployable<bool,CommonAPI::EmptyDeployment>
            >
        	>::callMethodWithReply(
        *this,
        "setHuHMISelection",
        "ib",
(_info ? _info : &CommonAPI::DBus::defaultCallInfo),
deploy_huTypeofAlert, deploy_alertStatus,
_internalCallStatus,
deploy_huAlertType, deploy_status);
_huAlertType = deploy_huAlertType.getValue();
_status = deploy_status.getValue();
}
    std::future<CommonAPI::CallStatus> VoiceAlertServiceDBusProxy::setHuHMISelectionAsync(const ::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum &_huTypeofAlert, const bool &_alertStatus, SetHuHMISelectionAsyncCallback _callback, const CommonAPI::CallInfo *_info) {
        CommonAPI::Deployable<::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum, CommonAPI::EmptyDeployment> deploy_huTypeofAlert(_huTypeofAlert, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> deploy_alertStatus(_alertStatus, static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum, CommonAPI::EmptyDeployment> deploy_huAlertType(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> deploy_status(static_cast<CommonAPI::EmptyDeployment*>(nullptr));
        return CommonAPI::DBus::DBusProxyHelper<
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum, CommonAPI::EmptyDeployment >,
            CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment >
            >,
            CommonAPI::DBus::DBusSerializableArguments<
            CommonAPI::Deployable<::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum,CommonAPI::EmptyDeployment>,
            CommonAPI::Deployable<bool,CommonAPI::EmptyDeployment>
            >
        	>::callMethodAsync(
        *this,
        "setHuHMISelection",
        "ib",
        (_info ? _info : &CommonAPI::DBus::defaultCallInfo),
        deploy_huTypeofAlert, deploy_alertStatus,
        [_callback] (CommonAPI::CallStatus _internalCallStatus, CommonAPI::Deployable<::v1::com::harman::VoiceAlert::VoiceAlertType::HuHMISelection_enum, CommonAPI::EmptyDeployment> _huAlertType, CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment> _status) {
        	if (_callback)
        		_callback(_internalCallStatus, _huAlertType.getValue(), _status.getValue());
        },
        std::make_tuple(deploy_huAlertType, deploy_status));
    }


void VoiceAlertServiceDBusProxy::getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const {
          ownVersionMajor = 0;
          ownVersionMinor = 1;
      }

      } // namespace VoiceAlert
      } // namespace harman
      } // namespace com
      } // namespace v0

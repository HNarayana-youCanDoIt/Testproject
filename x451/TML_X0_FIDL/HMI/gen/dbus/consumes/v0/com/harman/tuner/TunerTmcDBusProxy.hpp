/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
/**
 * description: Tuner TMC interface.
 * author: Harman, CoC Tuner, Dirk Engel (c) copyright 2017
 */
#ifndef V0_COM_HARMAN_TUNER_Tuner_Tmc_DBUS_PROXY_HPP_
#define V0_COM_HARMAN_TUNER_Tuner_Tmc_DBUS_PROXY_HPP_

#include <v0/com/harman/tuner/TunerTmcProxyBase.hpp>
#include "v0/com/harman/tuner/TunerTmcDBusDeployment.hpp"

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
namespace tuner {

class TunerTmcDBusProxy
    : virtual public TunerTmcProxyBase, 
      virtual public CommonAPI::DBus::DBusProxy {
public:
    TunerTmcDBusProxy(
        const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection);

    virtual ~TunerTmcDBusProxy() { }

    virtual StatusAttribute& getStatusAttribute();
    virtual DetailedStatusAttribute& getDetailedStatusAttribute();
    virtual ServicesAttribute& getServicesAttribute();
    virtual FiltersAttribute& getFiltersAttribute();

    virtual DataEvent& getDataEvent();

    /**
     * description: Disable/enable TMC and set update rate (SDARS counter and time)
     */
    virtual void setUpdateRate(const ::v0::com::harman::tuner::TunerTmcTypes::DeviceType &_device, const uint16_t &_maxDropCounter, const uint16_t &_maxDropTime, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setUpdateRateAsync(const ::v0::com::harman::tuner::TunerTmcTypes::DeviceType &_device, const uint16_t &_maxDropCounter, const uint16_t &_maxDropTime, SetUpdateRateAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Set filter for TMC data selection.
     */
    virtual void setFilter(const ::v0::com::harman::tuner::TunerTmcTypes::Filter &_filter, CommonAPI::CallStatus &_internalCallStatus, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setFilterAsync(const ::v0::com::harman::tuner::TunerTmcTypes::Filter &_filter, SetFilterAsyncCallback _callback, const CommonAPI::CallInfo *_info);


    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

private:
   
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<StatusAttribute, ::v0::com::harman::tuner::TunerTmcTypes_::StatusDeployment_t>> status_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<DetailedStatusAttribute, ::v0::com::harman::tuner::TunerTmcTypes_::DetailedStatusDeployment_t>> detailedStatus_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<ServicesAttribute, ::v0::com::harman::tuner::TunerTmcTypes_::ServicesDeployment_t>> services_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<FiltersAttribute, ::v0::com::harman::tuner::TunerTmcTypes_::FiltersDeployment_t>> filters_;

    CommonAPI::DBus::DBusEvent<DataEvent, CommonAPI::Deployable<::v0::com::harman::tuner::TunerTmcTypes::DeviceType, CommonAPI::EmptyDeployment>, CommonAPI::Deployable<uint32_t, CommonAPI::EmptyDeployment>, CommonAPI::Deployable<uint16_t, CommonAPI::EmptyDeployment>, CommonAPI::Deployable<uint8_t, CommonAPI::EmptyDeployment>, CommonAPI::Deployable<CommonAPI::ByteBuffer, CommonAPI::EmptyDeployment>> data_;

};

} // namespace tuner
} // namespace harman
} // namespace com
} // namespace v0

#endif // V0_COM_HARMAN_TUNER_Tuner_Tmc_DBUS_PROXY_HPP_


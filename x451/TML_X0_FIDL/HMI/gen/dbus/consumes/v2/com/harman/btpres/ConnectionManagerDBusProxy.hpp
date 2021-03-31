/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
#ifndef V2_COM_HARMAN_BTPRES_Connection_Manager_DBUS_PROXY_HPP_
#define V2_COM_HARMAN_BTPRES_Connection_Manager_DBUS_PROXY_HPP_

#include <v2/com/harman/btpres/ConnectionManagerProxyBase.hpp>
#include "v2/com/harman/btpres/ConnectionManagerDBusDeployment.hpp"

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

namespace v2 {
namespace com {
namespace harman {
namespace btpres {

class ConnectionManagerDBusProxy
    : virtual public ConnectionManagerProxyBase, 
      virtual public CommonAPI::DBus::DBusProxy {
public:
    ConnectionManagerDBusProxy(
        const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection);

    virtual ~ConnectionManagerDBusProxy() { }

    virtual BtStateAttribute& getBtStateAttribute();
    virtual LocalDevAddrAttribute& getLocalDevAddrAttribute();
    virtual LocalDevNameAttribute& getLocalDevNameAttribute();
    virtual PassKeyPinAttribute& getPassKeyPinAttribute();
    virtual DeviceSearchStatusAttribute& getDeviceSearchStatusAttribute();
    virtual DiscoverableStatusAttribute& getDiscoverableStatusAttribute();
    virtual DiscoveryTimeoutAttribute& getDiscoveryTimeoutAttribute();
    virtual DevSearchResultsAttribute& getDevSearchResultsAttribute();
    virtual DevListAttribute& getDevListAttribute();
    virtual ConnectedDevListAttribute& getConnectedDevListAttribute();
    virtual NetIfStatusAttribute& getNetIfStatusAttribute();
    virtual UnstableDevsAttribute& getUnstableDevsAttribute();
    virtual PrimaryDeviceAttribute& getPrimaryDeviceAttribute();
    virtual DnDStatusAttribute& getDnDStatusAttribute();
    virtual DndInfoAttribute& getDndInfoAttribute();
    virtual SocialModeStatusAttribute& getSocialModeStatusAttribute();

    virtual BondingRequestEvent& getBondingRequestEvent();
    virtual ServiceConnectionRequestEvent& getServiceConnectionRequestEvent();
    virtual ServiceConnectionStatusEvent& getServiceConnectionStatusEvent();
    virtual DeviceDeletedEvent& getDeviceDeletedEvent();
    virtual ReconnectionFailedEvent& getReconnectionFailedEvent();
    virtual BondingStatusEvent& getBondingStatusEvent();
    virtual TonePlayStateEvent& getTonePlayStateEvent();

    /**
     * description: Used to start device search on head unit
     * param: maxDevice (UInt32)       : max limit for found devices
     * param: timeout (UInt32)         : time limit for device search operation         
     *   returns: errorCode (eErrorType) : error code
     */
    virtual void startDeviceSearch(const uint32_t &_maxDevice, const uint32_t &_timeout, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> startDeviceSearchAsync(const uint32_t &_maxDevice, const uint32_t &_timeout, StartDeviceSearchAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to stop device search on head unit
     * param: none          returns: error code (eErrorType) : error code
     */
    virtual void stopDeviceSearch(CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> stopDeviceSearchAsync(StopDeviceSearchAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to send secure Bonding reply
     * param: inAddress (string)       : phone BT address
     * param: accept (boolean)         : accepting authentication request
     * param: trusted (boolean)        : making device trusted means service won't send
     *   connection request for each connect attempt
     * param: type (eBondingType)      : Bonding type, standard or secure bonding         
     *   returns: errorCode (eErrorType) : error code
     */
    virtual void bondingReply(const std::string &_inAddress, const bool &_accept, const bool &_trusted, const ::v7::com::harman::btpres::BTPresTypes::eBondingType &_type, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> bondingReplyAsync(const std::string &_inAddress, const bool &_accept, const bool &_trusted, const ::v7::com::harman::btpres::BTPresTypes::eBondingType &_type, BondingReplyAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to delete device from paired device list
     * param: inAddress (string)      : phone BT address          returns: errorCode
     *   (eErrorType): error code
     */
    virtual void deleteDevice(const std::string &_inAddress, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> deleteDeviceAsync(const std::string &_inAddress, DeleteDeviceAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to delete all device in paired device list
     * param: none          returns: errorCode (eErrorType) : error code
     */
    virtual void deleteAllDevices(CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> deleteAllDevicesAsync(DeleteAllDevicesAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to initate profile connection with device         version 1.0
     * param: inAddress (string)       : phone BT address
     * param: service (eSupportedProfile) : profile name
     * param: instanceName (string)    : containing the phone instance
     * param: replaceAddr (string)     : containing the replacement address for which the
     *   connection will be replaced          returns: errorCode (eErrorType) : error
     *   code
     */
    virtual void startServiceConnection(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::eSupportedProfile &_service, const std::string &_instanceName, const std::string &_replaceAddr, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> startServiceConnectionAsync(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::eSupportedProfile &_service, const std::string &_instanceName, const std::string &_replaceAddr, StartServiceConnectionAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to initate multiple profile connection with device         version 2.0
     * param: inAddress (string)                       : phone BT address
     * param: ProfileList (arSupportedProfile)         : profile name list
     * param: replaceAddr (string)                     : containing the replacement address
     *   for which the connection will be replaced          returns: errorCode
     *   (eErrorType) : error code
     */
    virtual void startServiceConnection(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::arSupportedProfile &_ProfileList, const std::string &_replaceAddr, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> startServiceConnectionAsync(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::arSupportedProfile &_ProfileList, const std::string &_replaceAddr, StartServiceConnectionAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to allows the existance of the service connection to this device and
     *   service.
     * param: inAddress (string)           : phone BT address
     * param: service (eSupportedProfile)  : profile name
     * param: allow (Boolean)              : containing the value true for allow, or false
     *   for reject          returns: errorCode (eErrorType)      : error code
     */
    virtual void allowServiceConnection(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::eSupportedProfile &_service, const bool &_allow, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> allowServiceConnectionAsync(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::eSupportedProfile &_service, const bool &_allow, AllowServiceConnectionAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to initate the disconnection with connected service i.e. HFP and A2DP
     * param: inAddress (string)                  : phone BT address
     * param: service (eSupportedProfile)         : profile name          returns: errorCode
     *   error code (eErrorType)  : error code
     */
    virtual void startServiceDisconnection(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::eSupportedProfile &_service, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> startServiceDisconnectionAsync(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::eSupportedProfile &_service, StartServiceDisconnectionAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to initate the disconnection with connected service i.e. HFP and A2DP
     * param: inAddress (string)                  : phone BT address
     * param: ProfileList (arSupportedProfile)         : profile name list          returns:
     *   errorCode error code (eErrorType)  : error code
     */
    virtual void startServiceDisconnection(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::arSupportedProfile &_ProfileList, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> startServiceDisconnectionAsync(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::arSupportedProfile &_ProfileList, StartServiceDisconnectionAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This method should be called by clients in order to reply to the incoming
     *   service                         connection request from a remote device as
     *   indicated by the signal 'serviceConnectionRequest'.                        
     *   The reply can be to accept or reject incoming service connection request.
     * param: inAddress (string)              : phone BT address
     * param: service (eSupportedProfile)     : profile name
     * param: accept (boolean)                : containing the value true for allow, or false
     *   for reject
     * param: instanceName (string)           : containing the instance name of the device   
     *         returns: errorCode (eErrorType)         : error code
     */
    virtual void serviceConnectionReply(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::eSupportedProfile &_service, const bool &_accept, const std::string &_instanceName, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> serviceConnectionReplyAsync(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::eSupportedProfile &_service, const bool &_accept, const std::string &_instanceName, ServiceConnectionReplyAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to initiate the reconnection to previously connected device
     * param: None          returns: errorCode error code (eErrorType) : error code
     */
    virtual void startReconnect(CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> startReconnectAsync(StartReconnectAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This method should be called to get oldest connected device
     * param: None          returns: oldestDevInfo (oldestDevInfo)     : Oldest device name
     *   and address         returns: errorCode error code (eErrorType) : error code
     */
    virtual void getOldestConnectedDev(CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, ::v7::com::harman::btpres::BTPresTypes::deviceInfo &_oldestDevInfo, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> getOldestConnectedDevAsync(GetOldestConnectedDevAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This method used to change name of bonded device.
     * param: inAddress  (string)     : contains the BD address.
     * param: name (string)           : Device name          returns: errorCode(eErrorType) 
     *   : error code
     */
    virtual void renameBondedDevice(const std::string &_inAddress, const std::string &_name, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> renameBondedDeviceAsync(const std::string &_inAddress, const std::string &_name, RenameBondedDeviceAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This method used to change local name of head unit.
     * param: name (string)           : Device name          returns: errorCode(eErrorType) 
     *   : error code
     */
    virtual void renameLocalDevice(const std::string &_name, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> renameLocalDeviceAsync(const std::string &_name, RenameLocalDeviceAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to set bluetooth on or off
     * param: status (boolean)       : set true or false          returns: error
     *   code(eErrorType) : error code
     */
    virtual void setBluetoothStatus(const bool &_status, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setBluetoothStatusAsync(const bool &_status, SetBluetoothStatusAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Used to enable or disable discoverable mode
     * param: enabled (boolean)       : set true or false          returns: errorCode
     *   (eErrorType) : error code
     */
    virtual void setDiscoverableMode(const bool &_enabled, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setDiscoverableModeAsync(const bool &_enabled, SetDiscoverableModeAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This method used to pin information for head unit.
     * param: passkey (string)          : set the default pin for legacy devices         
     *   returns:  error code (eErrorType) : error code
     */
    virtual void setPin(const std::string &_passkey, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setPinAsync(const std::string &_passkey, SetPinAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: It will set a device as primary
     * param: inAddress  (string)     : contains the BD address.          returns:  error
     *   code (eErrorType) : error code
     */
    virtual void setPrimaryDevice(const std::string &_inAddress, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> setPrimaryDeviceAsync(const std::string &_inAddress, SetPrimaryDeviceAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This API is used for set and get phone specific properties like PhoneBook    
     *   Auto Download is enabled or disables, set specific ringtone, call volume etc.
     *   These property values     will to set for all the paired phones.
     * param: inAddress  (string)     : contains the BD address.
     * param: type (eSettingsOperation) : Operations like GET or SET
     * param: setProperty (eSettingsProperty) : Property like PhoneBook AutoDowload, sorting
     *   order etc
     * param: setValue (settingsValues) : value of the selected property          returns: 
     *   error code (eErrorType) : error code         returns: outAddress  (string)    
     *   : contains the BD address.         returns: getProperty (eSettingsProperty) :
     *   Property like PhoneBook AutoDowload, sorting order etc         returns:
     *   getValue (settingsValues) : value of the selected property
     */
    virtual void PhoneSettings(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::eSettingsOperation &_type, const ::v7::com::harman::btpres::BTPresTypes::eSettingsProperty &_setProperty, const ::v7::com::harman::btpres::BTPresTypes::settingsValues &_setValue, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, std::string &_outAddress, ::v7::com::harman::btpres::BTPresTypes::eSettingsProperty &_getProperty, ::v7::com::harman::btpres::BTPresTypes::settingsValues &_getValue, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> PhoneSettingsAsync(const std::string &_inAddress, const ::v7::com::harman::btpres::BTPresTypes::eSettingsOperation &_type, const ::v7::com::harman::btpres::BTPresTypes::eSettingsProperty &_setProperty, const ::v7::com::harman::btpres::BTPresTypes::settingsValues &_setValue, PhoneSettingsAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This API is used to enable or disable Do Not Disturb for a specific device.    
     *   When this is enabled incoming call to that device will be rejected and also
     *   SMS notification     alerts will be disabled.
     * param: device  (dontDisturbDeviceInfo) : contains the BD address and DnD status to be
     *   set.          returns:  error code (eErrorType)       : error code            
     *        This API will be deprecated once all client move to DontDisturbExtended
     *   API
     */
    virtual void DontDisturb(const ::v7::com::harman::btpres::BTPresTypes::dontDisturbDeviceInfo &_device, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> DontDisturbAsync(const ::v7::com::harman::btpres::BTPresTypes::dontDisturbDeviceInfo &_device, DontDisturbAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This API is used to enable or disable Do Not Disturb.      This method should
     *   be called with eDndType , which contains different type of dnd .      when
     *   clients wants to enable phone specific dnd then dnd type should be DND_PHONE  
     *      Whne clents wants to enable dnd for somplete HU then dnd type should be
     *   DND_HU      Whne clents wants to disable audio handling for the BTPRES then
     *   dnd type should be DND_DISABLE_AUDIO.
     * param: device  (extendedDnd) : different type of DND mode       returns:  error code
     *   (eErrorType)       : error code
     */
    virtual void DontDisturbExtended(const ::v7::com::harman::btpres::BTPresTypes::extendedDnd &_dndMode, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> DontDisturbExtendedAsync(const ::v7::com::harman::btpres::BTPresTypes::extendedDnd &_dndMode, DontDisturbExtendedAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This will update the position of the device in devList(Bonded Device List)
     *   attribute.For example     device with index 1 will be at top of the devList.
     * param: address  (string)   : Address of the device
     * param: index  (UInt16)     : New index(position) for the device          returns: 
     *   error code (eErrorType) : error code
     */
    virtual void SetFavoriteDevice(const std::string &_address, const uint16_t &_index, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> SetFavoriteDeviceAsync(const std::string &_address, const uint16_t &_index, SetFavoriteDeviceAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This will be used to play the HU ringtone
     * param: toneID    : Tone ID which HMI want to play          returns:  error code
     *   (eErrorType) : error code
     */
    virtual void play(const ::v7::com::harman::btpres::BTPresTypes::uToneID &_toneID, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> playAsync(const ::v7::com::harman::btpres::BTPresTypes::uToneID &_toneID, PlayAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This will be used to stop the HU ringtone playback started by previous method
     * param: toneID    : Tone ID which is currently playing          returns:  error code
     *   (eErrorType) : error code
     */
    virtual void stop(const ::v7::com::harman::btpres::BTPresTypes::uToneID &_ringID, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> stopAsync(const ::v7::com::harman::btpres::BTPresTypes::uToneID &_ringID, StopAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This can be used by the clients to get bonded device details like manufacturer,
     *   model,                       software version, profileinfo etc.
     * param: address  (string)   : Address of the device          returns:  error code
     *   (eErrorType) : error code         returns:  device (deviceDetails) : This
     *   contains details like BD Address, Name,                   manufacturer, model,
     *   software version, profileinfo etc.
     */
    virtual void getBondedDeviceDetails(const std::string &_address, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, ::v7::com::harman::btpres::BTPresTypes::deviceDetails &_device, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> getBondedDeviceDetailsAsync(const std::string &_address, GetBondedDeviceDetailsAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This will be used to reset profile / profiles to default value.
     * param: type (factroyResetType)	: Type of reset can be user or system level            
     *                                 USER: Should set current user settings to
     *   default value                                           SYSTEM: Should set all
     *   profiles settings to default value          returns:  error code (eErrorType)
     *   : error code
     */
    virtual void factoryReset(const ::v7::com::harman::btpres::BTPresTypes::factroyResetType &_type, CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::eErrorType &_errorCode, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> factoryResetAsync(const ::v7::com::harman::btpres::BTPresTypes::factroyResetType &_type, FactoryResetAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: This will be used to get the radio strength of Bluetooth device connected to HU.
     */
    virtual void getRadioStrength(CommonAPI::CallStatus &_internalCallStatus, ::v7::com::harman::btpres::BTPresTypes::radioStrengthInfoList &_radioStrengthList, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> getRadioStrengthAsync(GetRadioStrengthAsyncCallback _callback, const CommonAPI::CallInfo *_info);


    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

private:
   
    class DBusbtState_Attribute : public CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<BtStateAttribute>> {
    public:
    template <typename... _A>
    	DBusbtState_Attribute(DBusProxy &_proxy,
    		_A ... arguments)
    		: CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<BtStateAttribute>>(
    			_proxy, arguments...) {}
    };
    DBusbtState_Attribute btState_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<LocalDevAddrAttribute, CommonAPI::DBus::StringDeployment>> localDevAddr_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<LocalDevNameAttribute, CommonAPI::DBus::StringDeployment>> localDevName_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<PassKeyPinAttribute, CommonAPI::DBus::StringDeployment>> passKeyPin_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<DeviceSearchStatusAttribute>> deviceSearchStatus_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<DiscoverableStatusAttribute>> discoverableStatus_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<DiscoveryTimeoutAttribute>> discoveryTimeout_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<DevSearchResultsAttribute, ::v7::com::harman::btpres::BTPresTypes_::tDeviceSearchEntryListDeployment_t>> devSearchResults_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<DevListAttribute, ::v7::com::harman::btpres::BTPresTypes_::bondedDevListDeployment_t>> devList_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<ConnectedDevListAttribute, ::v7::com::harman::btpres::BTPresTypes_::bondedDevListDeployment_t>> connectedDevList_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<NetIfStatusAttribute, ::v7::com::harman::btpres::BTPresTypes_::networkIfStatusDeployment_t>> netIfStatus_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<UnstableDevsAttribute, ::v7::com::harman::btpres::BTPresTypes_::unstableDeviceInfoListDeployment_t>> unstableDevs_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<PrimaryDeviceAttribute, CommonAPI::DBus::StringDeployment>> primaryDevice_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<DnDStatusAttribute, ::v7::com::harman::btpres::BTPresTypes_::dontDisturbDeviceInfoDeployment_t>> dnDStatus_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<DndInfoAttribute, ::v7::com::harman::btpres::BTPresTypes_::extendedDndDeployment_t>> dndInfo_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<SocialModeStatusAttribute>> socialModeStatus_;

    CommonAPI::DBus::DBusEvent<BondingRequestEvent, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>, CommonAPI::Deployable<::v7::com::harman::btpres::BTPresTypes::eBondingType, CommonAPI::EmptyDeployment>, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>> bondingRequest_;
    CommonAPI::DBus::DBusEvent<ServiceConnectionRequestEvent, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>, CommonAPI::Deployable<::v7::com::harman::btpres::BTPresTypes::eSupportedProfile, CommonAPI::EmptyDeployment>> serviceConnectionRequest_;
    CommonAPI::DBus::DBusEvent<ServiceConnectionStatusEvent, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>, CommonAPI::Deployable<::v7::com::harman::btpres::BTPresTypes::eSupportedProfile, CommonAPI::EmptyDeployment>, CommonAPI::Deployable<::v7::com::harman::btpres::BTPresTypes::eConnectionStatus, CommonAPI::EmptyDeployment>, CommonAPI::Deployable<::v7::com::harman::btpres::BTPresTypes::eServiceConnectDisconnectReason, CommonAPI::EmptyDeployment>> serviceConnectionStatus_;
    CommonAPI::DBus::DBusEvent<DeviceDeletedEvent, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>, CommonAPI::Deployable<::v7::com::harman::btpres::BTPresTypes::eDeviceDeletedReason, CommonAPI::EmptyDeployment>> deviceDeleted_;
    CommonAPI::DBus::DBusEvent<ReconnectionFailedEvent, CommonAPI::Deployable<::v7::com::harman::btpres::BTPresTypes::deviceInfo, ::v7::com::harman::btpres::BTPresTypes_::deviceInfoDeployment_t>> reconnectionFailed_;
    CommonAPI::DBus::DBusEvent<BondingStatusEvent, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>, CommonAPI::Deployable<::v7::com::harman::btpres::BTPresTypes::ePairingStatus, CommonAPI::EmptyDeployment>> bondingStatus_;
    CommonAPI::DBus::DBusEvent<TonePlayStateEvent, CommonAPI::Deployable<::v7::com::harman::btpres::BTPresTypes::uToneID, ::v7::com::harman::btpres::BTPresTypes_::uToneIDDeployment_t>, CommonAPI::Deployable<bool, CommonAPI::EmptyDeployment>> tonePlayState_;

};

} // namespace btpres
} // namespace harman
} // namespace com
} // namespace v2

#endif // V2_COM_HARMAN_BTPRES_Connection_Manager_DBUS_PROXY_HPP_


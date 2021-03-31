/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.
* Used org.franca.core 0.9.1.201412191134.
*
* generated by DCIF CodeGen Version: R2_v2.1.0
* generated on: Wed Oct 30 12:44:55 IST 2019
*/
/**
 * description: Provides interface to control the Software Update flow and to access the states
 *   and progress during the update process
 * author: Bharath Upadhya
 */
#ifndef V1_COM_HARMAN_SWDL_Software_Update_DBUS_PROXY_HPP_
#define V1_COM_HARMAN_SWDL_Software_Update_DBUS_PROXY_HPP_

#include <v1/com/harman/swdl/SoftwareUpdateProxyBase.hpp>
#include "v1/com/harman/swdl/SoftwareUpdateDBusDeployment.hpp"

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

namespace v1 {
namespace com {
namespace harman {
namespace swdl {

class SoftwareUpdateDBusProxy
    : virtual public SoftwareUpdateProxyBase, 
      virtual public CommonAPI::DBus::DBusProxy {
public:
    SoftwareUpdateDBusProxy(
        const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection);

    virtual ~SoftwareUpdateDBusProxy() { }

    virtual SoftwareAvailableForDownloadAttrAttribute& getSoftwareAvailableForDownloadAttrAttribute();
    virtual SoftwareAvailableForInstallAttrAttribute& getSoftwareAvailableForInstallAttrAttribute();
    virtual InstallProgressAttribute& getInstallProgressAttribute();
    virtual DownloadProgressAttribute& getDownloadProgressAttribute();
    virtual ActivationResultAttribute& getActivationResultAttribute();
    virtual LastUpdateSearchTimeAttribute& getLastUpdateSearchTimeAttribute();
    virtual LastUpdateInstallTimeAttribute& getLastUpdateInstallTimeAttribute();
    virtual StatusAttribute& getStatusAttribute();
    virtual AutoDownloadAttribute& getAutoDownloadAttribute();
    virtual AutoDownloadSizeLimitAttribute& getAutoDownloadSizeLimitAttribute();
    virtual AutoInstallAttribute& getAutoInstallAttribute();
    virtual AutoSearchAttribute& getAutoSearchAttribute();
    virtual AutoSearchIntervalAttribute& getAutoSearchIntervalAttribute();
    virtual AllowVersionDowngradeAttribute& getAllowVersionDowngradeAttribute();

    virtual SoftwareAvailableForDownloadEvent& getSoftwareAvailableForDownloadEvent();
    virtual SoftwareAvailableForInstallEvent& getSoftwareAvailableForInstallEvent();
    virtual SoftwareUpdateStatusEvent& getSoftwareUpdateStatusEvent();

    /**
     * description: Trigger to search for any software updates available for download and install
     *   from the available sources.                        e.g check for updates from
     *   OTA server or update packages within connected mass storage devices etc
     */
    virtual void CheckForUpdates(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, ::v1::com::harman::swdl::SoftwareUpdateTypes::tUpdateSearchResult &_checkResult, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> CheckForUpdatesAsync(CheckForUpdatesAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Trigger to search for specific update package via its name and matching hash in
     *   a source (e.g. Mass Storage Device)                          Parameters:
     */
    virtual void CheckPackageForUpdate(const std::string &_packageName, const ::v1::com::harman::swdl::SoftwareUpdateTypes::tHashValue &_hash, const ::v1::com::harman::swdl::SoftwareUpdateTypes::eUpdateSource &_source, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, ::v1::com::harman::swdl::SoftwareUpdateTypes::tUpdateSearchResult &_checkResult, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> CheckPackageForUpdateAsync(const std::string &_packageName, const ::v1::com::harman::swdl::SoftwareUpdateTypes::tHashValue &_hash, const ::v1::com::harman::swdl::SoftwareUpdateTypes::eUpdateSource &_source, CheckPackageForUpdateAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Trigger to perform a possible download action on newly available software.
     */
    virtual void RequestDownload(const ::v1::com::harman::swdl::SoftwareUpdateTypes::eRequestDownload &_requestDownload, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> RequestDownloadAsync(const ::v1::com::harman::swdl::SoftwareUpdateTypes::eRequestDownload &_requestDownload, RequestDownloadAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Trigger to perform a possible installation action on newly available software  
     *                         (Note : Package might be already downloaded from
     *   external sources to the internal device cache or ready for installation from
     *   external source)
     */
    virtual void RequestInstall(const ::v1::com::harman::swdl::SoftwareUpdateTypes::eRequestInstall &_installPackage, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> RequestInstallAsync(const ::v1::com::harman::swdl::SoftwareUpdateTypes::eRequestInstall &_installPackage, RequestInstallAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Method interface to request installation of the specific package located at a
     *   path specified via argument
     */
    virtual void RequestDownloadPackage(const ::v1::com::harman::swdl::SoftwareUpdateTypes::tPackageDetails &_downloadPackage, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> RequestDownloadPackageAsync(const ::v1::com::harman::swdl::SoftwareUpdateTypes::tPackageDetails &_downloadPackage, RequestDownloadPackageAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Method interface to request installation of the specific package located at a
     *   path specified via argument
     */
    virtual void RequestInstallPackage(const ::v1::com::harman::swdl::SoftwareUpdateTypes::tPackageDetails &_installPackage, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> RequestInstallPackageAsync(const ::v1::com::harman::swdl::SoftwareUpdateTypes::tPackageDetails &_installPackage, RequestInstallPackageAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: To cancel the download which is already started.         Deprecated for future
     *   use , Instead use RequestDownload(CANCEL_DOWNLOAD)
     */
    virtual void CancelDownload(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> CancelDownloadAsync(CancelDownloadAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: To cancel the installation which is already in progress.         Deprecated for
     *   future use , Instead use RequestInstall(CANCEL_INSTALLATION)
     */
    virtual void CancelInstall(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> CancelInstallAsync(CancelInstallAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: To enable or disable automatic download of the package from external source
     *   (e.g. OTA server or Mass storage device) in to the device cached.
     */
    virtual void SetAutomaticDownload(const bool &_enableAutoDownload, const uint32_t &_autoDownloadLimit, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> SetAutomaticDownloadAsync(const bool &_enableAutoDownload, const uint32_t &_autoDownloadLimit, SetAutomaticDownloadAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: To get the current enable/disable status for automatic download.
     */
    virtual void GetAutomaticDownloadStatus(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, bool &_enableAutoDownload, uint32_t &_autoDownloadLimit, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> GetAutomaticDownloadStatusAsync(GetAutomaticDownloadStatusAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: Request for activation of recently installed software ;                        
     *   Installation complete is notified via states INSTALLATION_COMPLETE or
     *   READY_FOR_ACTIVATION                        Post this API trigger , system
     *   will be restarted to new lifecycle to effect the new software
     */
    virtual void ActivateSoftware(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> ActivateSoftwareAsync(ActivateSoftwareAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: To completely disable the software update feature. When the update is disbaled,
     *                           software update process will neither check for any
     *   updates on its own not process any APIs to serach for updates.
     */
    virtual void DisableSoftwareUpdate(const bool &_disable, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> DisableSoftwareUpdateAsync(const bool &_disable, DisableSoftwareUpdateAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: retrieve if software update service is currently enabled or disabled
     */
    virtual void GetDisableSoftwareUpdate(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, bool &_disable, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> GetDisableSoftwareUpdateAsync(GetDisableSoftwareUpdateAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: To abort any on going search for updates.
     */
    virtual void AbortSearch(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> AbortSearchAsync(AbortSearchAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: To enable / disable automatic installation of the available/downloaded package
     *   without the confirmation from the client .
     */
    virtual void SetAutomaticInstallation(const bool &_enable, CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> SetAutomaticInstallationAsync(const bool &_enable, SetAutomaticInstallationAsyncCallback _callback, const CommonAPI::CallInfo *_info);
    /**
     * description: method trigger to reset the Software update states back to idle along with
     *   resetting the settings back to default.                        Clears any
     *   internal cache/status informations. If service is already in installation
     *   stage , request will not be processed
     */
    virtual void RequestFactoryReset(CommonAPI::CallStatus &_internalCallStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes::eMethodResult &_error, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> RequestFactoryResetAsync(RequestFactoryResetAsyncCallback _callback, const CommonAPI::CallInfo *_info);


    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

private:
   
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<SoftwareAvailableForDownloadAttrAttribute, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tPackageListDeployment_t>> softwareAvailableForDownloadAttr_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<SoftwareAvailableForInstallAttrAttribute, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tPackageListDeployment_t>> softwareAvailableForInstallAttr_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<InstallProgressAttribute, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tInstallProgressDeployment_t>> installProgress_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<DownloadProgressAttribute, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tDownloadProgressDeployment_t>> downloadProgress_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<ActivationResultAttribute, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tActivationResultDeployment_t>> activationResult_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<LastUpdateSearchTimeAttribute, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tTimeDeployment_t>> lastUpdateSearchTime_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<LastUpdateInstallTimeAttribute, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tTimeDeployment_t>> lastUpdateInstallTime_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusReadonlyAttribute<StatusAttribute, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tStatusDeployment_t>> status_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<AutoDownloadAttribute>> autoDownload_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<AutoDownloadSizeLimitAttribute>> autoDownloadSizeLimit_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<AutoInstallAttribute>> autoInstall_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<AutoSearchAttribute>> autoSearch_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<AutoSearchIntervalAttribute>> autoSearchInterval_;
    CommonAPI::DBus::DBusObservableAttribute<CommonAPI::DBus::DBusAttribute<AllowVersionDowngradeAttribute>> allowVersionDowngrade_;

    CommonAPI::DBus::DBusEvent<SoftwareAvailableForDownloadEvent, CommonAPI::Deployable<::v1::com::harman::swdl::SoftwareUpdateTypes::tPackageDetails, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tPackageDetailsDeployment_t>> softwareAvailableForDownload_;
    CommonAPI::DBus::DBusEvent<SoftwareAvailableForInstallEvent, CommonAPI::Deployable<::v1::com::harman::swdl::SoftwareUpdateTypes::tPackageDetails, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tPackageDetailsDeployment_t>> softwareAvailableForInstall_;
    CommonAPI::DBus::DBusEvent<SoftwareUpdateStatusEvent, CommonAPI::Deployable<::v1::com::harman::swdl::SoftwareUpdateTypes::tStatus, ::v1::com::harman::swdl::SoftwareUpdateTypes_::tStatusDeployment_t>, CommonAPI::Deployable<::v1::com::harman::swdl::SoftwareUpdateTypes::eUpdateSource, CommonAPI::EmptyDeployment>> softwareUpdateStatus_;

};

} // namespace swdl
} // namespace harman
} // namespace com
} // namespace v1

#endif // V1_COM_HARMAN_SWDL_Software_Update_DBUS_PROXY_HPP_


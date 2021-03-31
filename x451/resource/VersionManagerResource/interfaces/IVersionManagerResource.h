/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IVersionManagerResource.h
* @ingroup      HMIComponent
* @author       Rajat Gupta
* IVersionManagerResource, an interface for Version Manager Resource Implementaion in HMI
*/

#ifndef IVERSIONMANAGERRESOURCE_H
#define IVERSIONMANAGERRESOURCE_H

#include <capi/CAPIClientAbstraction.hpp>
#include "v0/com/harman/dcif/VersionManagerService_TATAProxy.hpp"
#include "v0/com/harman/dcif/versionmanagertypes_tata.hpp"
#include "v0/com/harman/dcif/VersionManagerService_TATA.hpp"
#include "CVersionManagerEnums.h"

using namespace v0::com::harman::dcif ;
/**
*   @brief The IVersionManagerResource class
*   This interfaces provides functionality which interacts with the below PresCtrl or Resource proxy directly.
*   It also provides functionality via which data can be provided to the upper layer.
*/
class IVersionManagerResource
{
public:
    virtual ~IVersionManagerResource(){}

    /*****  Request METHODS  ****************************/

    /**
    * @brief	This method will return SVersionInformation structure reuested by adaptor.
    * @param	void
    * @return	SVersionInformation : structure which contains SVersionInformation from VersionManager service.
    */
    virtual CVersionManagerEnums::SVersionInformation fetchVersionInfo() = 0;

    /*****  CALL BACK METHODS  ****************************/
    /**
    * @brief	onVersionMismatchEventStatusCb, This is a callback method for version manager mismatch status event.
    * @param	status: version manager mismatch status
    * @return	void
    */
    virtual void onVersionMismatchEventStatusCb(versionmanagertypes_tata::VersionMismatchDetails_e eMismatchType) = 0;

    /**
    * @brief	versionManagerStatusCb, This is a callback method for version manager proxy status event.
    * @param	status: version manager proxy status available or not
    * @return	void
    */
    virtual void versionManagerStatusCb(CommonAPI::AvailabilityStatus status) = 0;

    /**
    * @brief	get16RPartNumberAsyncCb, This is a callback method, which gets invoked on calling the API get16RPartNumberAsyncCb.
    * @param	status : The status of the get16RPartNumberAsyncCb API call.
    * @param	16RPartInfo : PartNumberInfo details structure
    * @return	void
    */
    virtual void get16RPartNumberAsyncCb(const CommonAPI::CallStatus& status, const versionmanagertypes_tata::_16RPartDetails_t &t_16RpartInfo) = 0;

    /**
    * @brief	getVersionDetailsAsyncCb, This is a callback method, which gets invoked on calling the API get16RPartNumberAsyncCb.
    * @param	status : The status of the get16RPartNumberAsyncCb API call.
    * @param	16RPartInfo : PartNumberInfo details structure
    * @return	void
    */
    virtual void getVersionDetailsAsyncCb(const CommonAPI::CallStatus& status, const versionmanagertypes_tata::versionInfo_t &t_versionInfo) = 0;

    /**
    * @brief	getPowerModeCfgTypeAsyncCb, This is a callback method, which gets invoked on calling the API getPowerModeCfgTypeAsync.
    * @param	status : The status of the getPowerModeCfgTypeAsyncCb API call.
    * @param	objPowerModeConfigInfo : object of PowerModeInfo detail structure
    * @return	void
    */
    virtual void getPowerModeCfgTypeAsyncCb(const CommonAPI::CallStatus& status, const versionmanagertypes_tata::_16RPartDetails_t& objPowerModeConfigInfo) = 0;

};

#endif // IVERSIONMANAGERRESOURCE_H

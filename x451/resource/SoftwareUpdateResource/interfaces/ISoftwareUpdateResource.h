/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         ISoftwareUpdateResource.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* ISoftwareUpdateResource, an interface for Software Update Resource Implementaion in HMI
*/

#ifndef ISOFTWAREUPDATERESOURCE_H
#define ISOFTWAREUPDATERESOURCE_H

#include <QVariant>
#include <string>
#include <QString>
#include <QObject>
#include "implementations/CSoftwareUpdateEnumsResource.h"
#include "v1/com/harman/swdl/SoftwareUpdateProxy.hpp"
#include "v1/com/harman/swdl/SoftwareUpdateTypes.hpp"
#include <capi/CAPIClientAbstraction.hpp>

using namespace std;
using namespace v1::com::harman::swdl;

/**
*   @brief The ISoftwareUpdateResource class
*   This interfaces provides functionality which interacts with the below PresCtrl or Resource proxy directly.
*   It also provides functionality via which data can be provided to the upper layer.
*/
class ISoftwareUpdateResource
{
public:
    virtual ~ISoftwareUpdateResource(){}

    /*****  Request METHODS  ****************************/

    /**
    * @brief	This pure virtual function is used by UI Layer to check whether there is any update available for software update.
    *           This will invoke the Service method, the response of which will be triggered in async function passed as argument.
    *           And, response will consist of list of ISO files or any error.
    * @param    void
    * @return	void
    */
    virtual void checkForUpdate()= 0;

    /**
    * @brief	This pure virtual function is used by UI Layer to get the package details for software update
    *           which is recieved as part of response of checkForUpdate()
    * @param    void
    * @return	SUpdateSearchResult : Software Update package data which will consist of package name and other attributes
    */
    virtual std::list<SUpdateSearchResult> getPackageDetails()=0;

    /**
    * @brief	This pure virtual function is used by UI Layer to request the start of the software installation
    *           after selecting the software update image. After calling the method,
    *           system will start update in emergency mode
    * @param    int index of the list item to install
    * @return	void
    */
    virtual void requestSWUpdate(int index) =0;

    /**
    * @brief	cancelUpdate This method will abort the Update if it is in progress
    * @param	eCancelType: It tells which API to be invoked for aborting the update
    * @return	void
    */
    virtual void cancelUpdate(ESoftwareUpdateCancelType eCancelType) = 0;

    /**
    * @brief	This method will request the installation of the Update if it is in version mismatch state
    * @param	uiMismatchType: type of version mismatch
    * @return	void
    */
    virtual void reqInstallVerMismatch(uint uiMismatchType) = 0;


    /*****  CALL BACK METHODS  ****************************/

    /**
    * @brief	This function is call back method to get Software Availability For Install, response from softwareupdatepresctrlproxy received here.
    * @param    SoftwareUpdateTypes::tPackageDetails: software update package list details
    * @return	void
    */
    virtual void onSWAvailable(SoftwareUpdateTypes::tPackageList) =0;

    /**
    * @brief	This function is call back method to check for updates, response from softwareupdatepresctrlproxy received here.
    * @param    const CommonAPI::CallStatus& : API call response status
    *           const SoftwareUpdateTypes::eMethodResult& : API call result
    *           const SoftwareUpdateTypes::tUpdateSearchResult& : Result data
    * @return	void
    */
    virtual void asyncCbCheckForUpdate(const CommonAPI::CallStatus&, const SoftwareUpdateTypes::eMethodResult& mResult, const SoftwareUpdateTypes::tUpdateSearchResult& searchResult)=0;

    /**
     * @brief	This function is call back method to get indication of current state of the Software update flow , response from softwareupdatepresctrlproxy received here.
     * @param    status: Software package update status.
     * @param    eUpdateSource: Software package update source.
     * @return	void
     */
     virtual void onSoftwareUpdateStatus(SoftwareUpdateTypes::tStatus status, SoftwareUpdateTypes::eUpdateSource eUpdateSource) =0;

    /**
    * @brief	This function is used to get the software update availibility status
    * @param    CommonAPI::AvailabilityStatus : Software Update availibility status
    * @return	void
    */
    virtual void statusEventListnerSoftwareUpdate(CommonAPI::AvailabilityStatus status) =0;

    /**
    * @brief	This function is call back method to cancel the update in progress
    * @param    const CommonAPI::CallStatus& : API call response status
    * @return	void
    */
    virtual void CancelUpdateAsyncCb(const CommonAPI::CallStatus& status) = 0;

    /**
    * @brief	This function is call back method to decline the update in progress
    * @param    const CommonAPI::CallStatus& : API call response status
    * @return	void
    */
    virtual void DeclineUpdateAsyncCb(const CommonAPI::CallStatus& status) = 0;

    /**
    * @brief	InstallPackageVerMismatchAsyncCb: This is a callback method, which gets invoked on calling the API requestInstallAsync.
    * @param	status : The status of the API call.
    * @return	void
    */
    virtual void InstallPackageVerMismatchAsyncCb(const CommonAPI::CallStatus& status) =0;

};

#endif // ISOFTWAREUPDATERESOURCE_H




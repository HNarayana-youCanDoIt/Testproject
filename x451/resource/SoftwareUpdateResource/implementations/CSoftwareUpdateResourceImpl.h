/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CSoftwareUpdateResourceImpl.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* CSoftwareUpdateResourceImpl, Resource Implementation for Software Update
*/
#ifndef CSOFTWAREUPDATERESOURCEIMPL_H
#define CSOFTWAREUPDATERESOURCEIMPL_H

#include <memory>
#include "resource/SoftwareUpdateResource/interfaces/ISoftwareUpdateResource.h"
#include "CSoftwareUpdateEventProvider.h"
#include "CSoftwareUpdateEnumsResource.h"
#include "Test/SoftwareUpdate/CSoftwareUpdateResourceImplTest.h"

using namespace std;
using namespace v1::com::harman::swdl;

/***************************************************************//**
 * @category CONSTANTS
 ***************************************************************/
const int SW_CHECKFORUPDATE_CAPI_TIMEOUT  = 45000;

/**
 * @brief The CSoftwareUpdateResourceImpl class is Resource Implementation for Software Update
 */
class CSoftwareUpdateResourceImpl: public ISoftwareUpdateResource
{
public:

    /**
    * @brief	CSoftwareUpdateResourceImpl Destructor
    * @param	void
    * @return	None
    */
    virtual ~CSoftwareUpdateResourceImpl();

    FRIEND_TEST(CSoftwareUpdateResourceImplTest, CheckSoftwareUpdateResourceImpInitializedVariables);
    FRIEND_TEST(CSoftwareUpdateResourceImplTest, CheckForStatusEventListnerSoftwareUpdate);
    FRIEND_TEST(CSoftwareUpdateResourceImplTest, CheckForOnSWAvailable);
    FRIEND_TEST(CSoftwareUpdateResourceImplTest, CodeCoverage);
    FRIEND_TEST(CSoftwareUpdateResourceImplTest, CodeCoverage2);




    /**
    * @brief	getSoftwareUpdateEventProvider This function is returns the pointer to CSoftwareUpdateEventProvider
    * @param    void
    * @return	CSoftwareUpdateEventProvider* : Pointer to CSoftwareUpdateEventProvider instance
    */
    CSoftwareUpdateEventProvider* getSoftwareUpdateEventProvider();

    /**
    * @brief	checkForUpdate This pure virtual function is used by UI Layer to check whether there is any update available for software update.
    *           This will invoke the Service method, the response of which will be triggered in async function passed as argument.
    *           And, response will consist of list of ISO files or any error.
    * @param    void
    * @return	void
    */
    void checkForUpdate() override;

    /**
    * @brief	getPackageDetails This pure virtual function is used by UI Layer to get the package details for software update
    *           which is recieved as part of response of checkForUpdate()
    * @param    void
    * @return	SUpdateSearchResult : Software Update package data which will consist of package name and other attributes
    */
    std::list<SUpdateSearchResult> getPackageDetails() override;

    /**
    * @brief	cancelUpdate This method will abort the Update if it is in progress
    * @param	eCancelType: It tells which API to be invoked for aborting the update
    * @return	void
    */
    void cancelUpdate(ESoftwareUpdateCancelType eCancelType) override;

    /**
    * @brief	reqInstallVerMismatch This method will request the installation of the Update if it is in version mismatch state
    * @param	uint
    * @return	void
    */
    void reqInstallVerMismatch(uint uiMismatchType) override;

public:

    static const char* SBX_VERSION;

private:

    /**
    * @brief	CSoftwareUpdateResourceImpl Constructor
    * @param	void
    * @return	void
    */
    CSoftwareUpdateResourceImpl();

    friend class CSoftwareUpdateResourceImplTest;
    /**
    * @brief	onSoftwareUpdateStatus onSoftwareUpdateStatus This function is call back method to get indication of current state of the update flow along with
     *          notification of process flow.
    * @param    status: Software package update status.
    * @param    eUpdateSource: Software package update source.
    * @return	void
    */
    void onSoftwareUpdateStatus(SoftwareUpdateTypes::tStatus status, SoftwareUpdateTypes::eUpdateSource eUpdateSource) override ;

    /**
    * @brief	onSWAvailable This function is call back method to get Software Availability For Install, response from softwareupdatepresctrlproxy received here.
    * @param    SoftwareUpdateTypes::tPackageList : software update package list details
    * @return	void
    */
    void onSWAvailable(SoftwareUpdateTypes::tPackageList packageList) override ;

    /**
    * @brief	asyncCbCheckForUpdate This function is call back method to check for updates, response from softwareupdatepresctrlproxy received here.
    * @param    const CommonAPI::CallStatus& : API call response status
    *           const SoftwareUpdateTypes::eMethodResult& : API call result
    *           const SoftwareUpdateTypes::tUpdateSearchResult& : Result data
    * @return	void
    */
    void asyncCbCheckForUpdate(const CommonAPI::CallStatus&, const SoftwareUpdateTypes::eMethodResult& mResult, const SoftwareUpdateTypes::tUpdateSearchResult& searchResult) override ;

    /**
    * @brief	CancelUpdateAsyncCb This function is call back method to cancel the update in progress
    * @param    const CommonAPI::CallStatus& : eCallStatus API call response status
    * @return	void
    */
    void CancelUpdateAsyncCb(const CommonAPI::CallStatus& eCallStatus) override ;

    /**
    * @brief	DeclineUpdateAsyncCb This function is call back method to decline the update in progress
    * @param    const CommonAPI::CallStatus& :eCallStatus API call response status
    * @return	void
    */
    void DeclineUpdateAsyncCb(const CommonAPI::CallStatus& eCallStatus) override ;

    /**
    * @brief	requestSWUpdate This pure virtual function is used by UI Layer to request the start of the software installation
    *           after selecting the software update image. After calling the method,
    *           system will start update in emergency mode
    * @param    int index of the list item to install
    * @return	void
    */
    void requestSWUpdate(int index) override ;


    /**
    * @brief	statusEventListnerSoftwareUpdate This function is used to get the software update availibility status
    * @param    CommonAPI::AvailabilityStatus : Software Update availibility status
    * @return	void
    */
    void statusEventListnerSoftwareUpdate(CommonAPI::AvailabilityStatus status) override;

    /**
    * @brief	InstallPackageVerMismatchAsyncCb: This is a callback method, which gets invoked on calling the API requestInstallAsync.
    * @param	status : The status of the API call.
    * @return	void
    */
    void InstallPackageVerMismatchAsyncCb(const CommonAPI::CallStatus& status) override;

private:

    friend class ResourceFactory;

    /**
    * @brief	subscribeSoftwareUpdateProxy This function subscribes to the service of software update service
    * @param    void
    * @return	void
    */
    void subscribeSoftwareUpdateProxy();

    /**
    * @brief	fillDetails This function is used to unpack the response recieved as part of the call to CheckForUpdatesAsync()
    * @param    SoftwareUpdateTypes::tPackageList : Response data recieved as part of the call to CheckForUpdatesAsync()
    * @return	void
    */
    void fillDetails(SoftwareUpdateTypes::tPackageList packageList);

    /* Instance of the CSoftwareUpdateEventProvider to emit signals to the upper layer */
    CSoftwareUpdateEventProvider* m_pSoftwareUpdateEventProvider;

    /* SoftwareUpdateProxy class object to call Software Update proxy methods */
    CAPIClientAbstraction<SoftwareUpdateProxy> m_SoftwareUpdateProxy;

    /* Bool memeber for Software Update Service availibility */
    bool m_bSoftwareUpdateAvailable;

    /* string member that holds value for name of package to install for BP_DM version mismatch  */
    const string  m_strBP_DM_VerMismatchFileName  = "X451H_DM_BP.sqfs";

    /* string member that holds value for name of package to install for BP version mismatch  */
    const string  m_strBP_VerMismatchFileName  = "X451H_BP.sqfs";

    /* string member that holds value for name of package to install for DM version mismatch  */
    const string  m_strDM_VerMismatchFileName  = "X451H_DM.sqfs";

    /* string member that holds value for path of package to install for BP_DM version mismatch  */
    const string  m_strBP_DM_VerMismatchFilePath  = "/mnt/swdl/X451H_DM_BP.sqfs";

    /* string member that holds value for path of package to install for BP version mismatch  */
    const string  m_strBP_VerMismatchFilePath  = "/mnt/swdl/X451H_BP.sqfs";

    /* string member that holds value for path of package to install for DM version mismatch  */
    const string  m_strDM_VerMismatchFilePath  = "/mnt/swdl/X451H_DM.sqfs";

    /* To store the result of Software Update service response */
    std::list<SUpdateSearchResult> m_updateDetailsList;

    SoftwareUpdateTypes::tPackageList mSWImageList;
};

#endif //CSWUPDATERESOURCEIMPL_H

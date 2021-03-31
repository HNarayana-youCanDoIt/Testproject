/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVersionManagerResourceImpl.h
* @ingroup      HMIComponent
* @author       Rajat Gupta
* CVersionManagerResourceImpl, Resource Implementation for Version Manager
*/
#ifndef CVERSIONMANAGERRESOURCEIMPL_H
#define CVERSIONMANAGERRESOURCEIMPL_H

#include "resource/VersionManagerResource/interfaces/IVersionManagerResource.h"
#include "CVersionManagerEventProvider.h"
#include "CVersionManagerEnums.h"
#include "Test/VersionManager/CVersionManagerResourceImplTest.h"

using namespace std;

/**
 * @brief The CVersionManagerResourceImpl class is Resource Implementation for Version Manager
 */
class CVersionManagerResourceImpl: public IVersionManagerResource
{
public:

    /**
    * @brief	CVersionManagerResourceImpl, Constructor
    * @param	void.
    * @return	void.
    */
    CVersionManagerResourceImpl();
    /**
    * @brief	Destructor, ~CVersionManagerResourceImpl
    * @param	void
    * @return	void.
    */
    virtual ~CVersionManagerResourceImpl();

    /**
    * @brief	getVersionManagerEventProvider, This function  returns the pointer to CVersionManagerEventProvider
    * @param    void
    * @return	CVersionManagerEventProvider* : Pointer to CVersionManagerEventProvider instance
    */
    CVersionManagerEventProvider* getVersionManagerEventProvider();
    FRIEND_TEST(CVersionManagerResourceImplTest, CheckVersionManagerResourceImpInitializedVariables);
    FRIEND_TEST(CVersionManagerResourceImplTest, CheckForGetterOfVersionDetailsAsyncCb);
    FRIEND_TEST(CVersionManagerResourceImplTest, CheckForCodeCoverageWithOtherFunctions2);
    FRIEND_TEST(CVersionManagerResourceImplTest, CheckForCodeCoverageWithOtherFunctions);



private:


    /**
    * @brief	versionManagerStatusCb, This is a callback method for version manager proxy status event.
    * @param	status: version manager proxy status available or not
    * @return	void
    */
    void versionManagerStatusCb(CommonAPI::AvailabilityStatus status) override;

    /**
    * @brief	onVersionMismatchEventStatusCb, This is a callback method for version manager mismatch status event.
    * @param	status: version manager mismatch status
    * @return	void
    */
    void onVersionMismatchEventStatusCb(versionmanagertypes_tata::VersionMismatchDetails_e eMismatchType) override;

    /**
    * @brief	get16RPartNumberAsyncCb, This is a callback method, which gets invoked on calling the API get16RPartNumberAsyncCb.
    * @param	status : The status of the get16RPartNumberAsyncCb API call.
    * @param	16RPartInfo : PartNumberInfo details structure
    * @return	void
    */
    void get16RPartNumberAsyncCb(const CommonAPI::CallStatus& status, const versionmanagertypes_tata::_16RPartDetails_t &t_16RpartInfo) override;

    /**
    * @brief	getVersionDetailsAsyncCb, This is a callback method, which gets invoked on calling the API get16RPartNumberAsyncCb.
    * @param	status : The status of the get16RPartNumberAsyncCb API call.
    * @param	16RPartInfo : PartNumberInfo details structure
    * @return	void
    */
    void getVersionDetailsAsyncCb(const CommonAPI::CallStatus& status, const versionmanagertypes_tata::versionInfo_t &t_versionInfo) override;


    /**
    * @brief	This method will return SVersionInformation structure.
    * @param	void
    * @return	SVersionInformation : structure which contains SVersionInformation from VersionManager service.
    */
    CVersionManagerEnums::SVersionInformation fetchVersionInfo() override;

    /**
    * @brief	This is a callback method, which gets invoked on calling the API getPowerModeCfgTypeAsync.
    * @param	eCallstatus : The status of the getPowerModeCfgTypeAsyncCb API call.
    * @param	objPowerModeConfigInfo : PowerModeInfo details structure
    * @return	void
    */
    void getPowerModeCfgTypeAsyncCb(const CommonAPI::CallStatus& eCallstatus, const versionmanagertypes_tata::_16RPartDetails_t& objPowerModeConfigInfo) override;

private:

    friend class ResourceFactory;

    /**
    * @brief	subscribeVersionManagerProxy, This function subscribes to the service of version manager service
    * @param    void
    * @return	void
    */
    void subscribeVersionManagerProxy();

    /** SVersionInformation structure variable, which holds the version info data */
     CVersionManagerEnums::SVersionInformation m_sVersionInfo;

    /**
     * @brief m_pVersionManagerEventProvider: Instance of the CVersionManagerEventProvider to emit signals to the upper layer
     */
    CVersionManagerEventProvider* m_pVersionManagerEventProvider;

    /**
     * @brief m_VersionManagerProxy : VersionManagerProxy class object to call version manager proxy methods
     */
    CAPIClientAbstraction<VersionManagerService_TATAProxy> m_VersionManagerProxy;

    /**
     * @brief VEHICLE_ID_NUMBER : string to hold  verhicle id no
     */
    const string VEHICLE_ID_NUMBER;

    /**
     * @brief VEHICLE_CFG_INFO : string to hold  verhicle config info no
     */
    const string VEHICLE_CFG_INFO_NUMBER;

    /**
     * @brief BUTTON_PANEL_16R_NUMBER_ECU_HW : string to hold  button panel string
     */
    const string BUTTON_PANEL_16R_NUMBER_ECU_HW;

    /**
     * @brief DISPLAY_16R_NUMBER_ECU_HW : string to hold  display 16R number string
     */
    const string DISPLAY_16R_NUMBER_ECU_HW;

    /**
     * @brief PARAMETERIZATION_PART_NUMBER : string to hold  parameterization part no
     */
    const string PARAMETERIZATION_PART_NUMBER;

    /**
     * @brief SILVERBOX_HARDWARE_PART_NUMBER : string to hold  silverbox part no string
     */
    const string SILVERBOX_HARDWARE_PART_NUMBER;

    /**
     * @brief CONTAINER_PART_NUMBER : string to hold container part no string
     */
    const string CONTAINER_PART_NUMBER;

    /**
     * @brief SOC : string to hold  SOC string
     */
    const string SOC;

    /**
     * @brief BUTTON_PANEL : Vstring to hold  button panel string
     */
    const string BUTTON_PANEL;

    /**
     * @brief DISPLAY : Vstring to hold  Display string
     */
    const string DISPLAY;

    /**
     * @brief VERSION_DETAILS_TIMEOUT : Dbus Timeout for Version details CallBack
     */
    const int VERSION_DETAILS_TIMEOUT;

};

#endif //CVERSIONMANAGERRESOURCEIMPL_H

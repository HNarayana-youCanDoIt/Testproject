/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CEnggMenuResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CEnggMenuResourceImpl class, The class that will implement the
 *  resources from proxy side to this Resource layer and then further
 *
 *
**/

#ifndef CENGGMENURESOURCEIMPL_H
#define CENGGMENURESOURCEIMPL_H
#include "interfaces/IEnggMenuResource.h"
#include "CEnggMenuEventProvider.h"
#include "interfaces/CDataEnggMenu.h"
#include <QObject>

using namespace std;
using namespace v0::com::harman::dcif;

/**
 * @brief:CEnggMenuResourceImpl class, The class that will implement the
 *  resources from proxy side to this Resource layer and then further
* */

class CEnggMenuResourceImpl:public QObject,public IEnggMenuResource
{
    Q_OBJECT
public:
    /**
    * @brief	CEnggMenuResourceImpl::~CEnggMenuResourceImpl Destructor for class CEnggMenuResourceImpl
    * @param	void
    * @return	void
    **/

    virtual ~CEnggMenuResourceImpl();
    /**
    * @brief	CEnggMenuResourceImpl::getEnggMenuDataEventProvider. Getter Function to get the pointer for getEnggMenuDataEventProvider
    * @param	void
    * @return	void
    **/

    CEnggMenuEventProvider* getEnggMenuDataEventProvider();


    /*********************************************************
                        CallBack Methods
     *********************************************************/
    /**
    * @brief	CEnggMenuResourceImpl::enggMenuServiceStatusCb,This function ensures the availability of EnggMenu service
    * @param	AvailabilityStatus eStatus, this provides the enum carrying the info whether the service is available,not known or unavailable.
    * @return	void
    **/
    void enggMenuServiceStatusCb( CommonAPI::AvailabilityStatus eStatus) override;

    /**
    * @brief	IEnggMenuResource::getFactoryResetCompleteEventCb,This callback function will be triggered whenever there is a signal emitted from service side
    * of completing factory reset
    * @param	bResetFactoryCompleteStatus , this provides the status of event completion/failure
    * @return	void
    **/
    void getFactoryResetCompleteEventCb( bool bResetFactoryCompleteStatus) override;


    /*********************************************************
                         Request Methods
     *********************************************************/
    /**
    * @brief	CEnggMenuResourceImpl::startDebugLogsService,This function starts Debug logs
    * @param	void
    * @return	void
    **/
    void startDebugLogsService() override ;
    //_____________________________________________________________________________________________________________________________________________________________

    /**
    * @brief	CEnggMenuResourceImpl::stopDebugLogsService,This function stops Debug logs
    * @param	void
    * @return	void
    **/
    void stopDebugLogsService()  override ;
    //_____________________________________________________________________________________________________________________________________________________________
     /**
     * @brief	CEnggMenuResourceImpl::extractDebugLogs,This function calls the pres's api to extract the Debug Logs to USB.
     * @param	void
     * @return	void
     **/
     void extractDebugLogs()    override;
	//_____________________________________________________________________________________________________________________________________________________________

    /**
    * @brief	CEnggMenuResourceImpl::setSystemIpAddress,This function will set the system IP.
    * @param	bool bIPType: Checkbox Status whether we have to set Static Ip or Dynamic IP.
    * @return	void
    **/

    void setSystemIpAddress(bool bIPType) override ;
    //_____________________________________________________________________________________________________________________________________________________________

    /**
     * @brief	IEnggMenuResource::testAutomationToggleService,This function starts/stop Test Automation service.
     * @param	bIsTestAutomationEnable,holds the status of test automation checkbox.
     * @return	void
     **/
    void testAutomationToggleService(bool bIsTestAutomationEnable) override;
    //_____________________________________________________________________________________________________________________________________________________________


    /**
    * @brief	IEnggMenuResource::startFactoryReset,This function performs factory reset task
    * @param	void
    * @return	void
    **/
    void startFactoryReset() override;
    //_____________________________________________________________________________________________________________________________________________________________

    /**
    * @brief	IEnggMenuResource::setDeviceMode,This function performs device mode task
    * @param	bDeviceMode: contains device mode option
    * @return	void
    **/
    void setDeviceMode(bool bDeviceMode) override;


    /*********************************************************
                     Response CallBack Methods
     *********************************************************/

    /**
      * @brief CallBack to get notified about startLoggingAsync method response
      * @param eCallStatus - call status of the startLoggingAsync method, whether success or not.
      * @param eReturnStatus - type of the error received after invoking startLoggingAsync method.
      * @return void
      */
      void startLoggingAsyncCb(const CommonAPI::CallStatus &eCallStatus, const EnggMenuTypes::retStatus &eReturnStatus) override;
    //_____________________________________________________________________________________________________________________________________________________________

    /**
      * @brief CallBack to get notified about stopLoggingAsync method response
      * @param eCallStatus - call status of the stopLoggingAsync method, whether success or not.
      * @param eReturnStatus - type of the error received after invoking stopLoggingAsync method.
      * @return void
      */
      void stopLoggingAsyncCb(const CommonAPI::CallStatus &eCallStatus, const EnggMenuTypes::retStatus &eReturnStatus) override;
    //_____________________________________________________________________________________________________________________________________________________________



    /**
      * @brief CallBack to get notified about setSystemIpAddress method response
      * @param callStatus - call status of the setSystemIpAddress method, whether success or not.
      * @param result - type of the error received after invoking setSystemIpAddress method.
      * @return void
      */
    void setSystemStaticIpAddressCb(const CommonAPI::CallStatus &callStatus,const EnggMenuTypes::retStatus &returnStatus) override;
    //_____________________________________________________________________________________________________________________________________________________________

    /**
       * @brief CallBack to get notified about setSystemDynamicIpAddress method response
       * @param status - call status of the setSystemDynamicIpAddress method, whether success or not.
       * @param result - type of the error received after invoking setSystemDynamicIpAddress method.
       * @return void
       */
    void setSystemDynamicIpAddressCb(const CommonAPI::CallStatus &callStatus, const EnggMenuTypes::retStatus&returnStatus) override;
    //_____________________________________________________________________________________________________________________________________________________________


    /**
       * @brief CallBack to get notified about testAutomationToggleService method response
       * @param callStatus - call status of the testAutomationToggleService method, whether success or not.
       * @param result - type of the error received after invoking testAutomationToggleService method.
       * @return void
       */
    void testAutomationStartServiceCb(const CommonAPI::CallStatus &callStatus , const EnggMenuTypes::retStatus &returnStatus) override;
    //_____________________________________________________________________________________________________________________________________________________________

    /**
       * @brief CallBack to get notified about testAutomationStopService method response
       * @param status - call status of the testAutomationStopService method, whether success or not.
       * @param result - type of the error received after invoking testAutomationStopService method.
       * @return void
       */
    void testAutomationStopServiceCb(const CommonAPI::CallStatus&status,const EnggMenuTypes::retStatus&returnStatus) override;
    //_____________________________________________________________________________________________________________________________________________________________

    /**
       * @brief CallBack to get notified about startFactoryReset method response
       * @param status - call status of the startFactoryReset method, whether success or not.
       * @param result - type of the error received after invoking startFactoryReset method.
       * @return void
       */
    void factoryResetCb(const CommonAPI::CallStatus& callStatus, const EnggMenuTypes::retStatus& returnStatus) override;
    //_____________________________________________________________________________________________________________________________________________________________

    /**
     * @brief CallBack to get notified about setDeviceMode method response
     * @param callStatus - call status of the setDeviceMode method, whether success or not.
     * @param modeType - type of mode activated.
     * @param deviceModeStatus - device mode status.
     */
    void setDeviceModeCb(const CommonAPI::CallStatus& callStatus, const EnggMenuTypes::modeType& modeType, const EnggMenuTypes::deviceModeStatus& deviceModeStatus) override;
	
    /**
     * @brief extractLogsAsyncCb: callback function for extractLogsAsync reques function.
     * @param eCallStatus: call status of the extractLogsAsync method, whether success or not.
     * @param eExtractLogsProcessStatus: Status while extracting logs. Like usb not connected, usb is full or success.
     */
    void extractLogsAsyncCb(const CallStatus &eCallStatus, const EnggMenuTypes::extractLogsError_enum &eExtractLogsProcessStatus) override;


private:

    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /**
    * @brief	CEnggMenuResourceImpl::CEnggMenuResourceImpl Constructor for class CEnggMenuResourceImpl
    * @param	void
    * @return	void
    **/

    CEnggMenuResourceImpl();
    /*********************************************************
                        Internal Methods
     *********************************************************/

    /**
    * @brief	CEnggMenuResourceImpl::subscribe . This Function will subscribe the EnggMenuPresCtrlProxy Proxy to the
    *           function in CEnggMenuResourceImpl class.
    * @param	void
    * @return	void
    **/

    void subscribe();

    /**
     * @brief	updateEnggProxyAvailabilityToHMI: This function is to update the engg proxy availability status to HMI.
     * @param   bIsEnggMenuProxyAvailable: status whether EnggMenu Proxy is available.
     * @return	void.
     */
    void updateEnggProxyAvailabilityToHMI(bool bIsEnggMenuProxyAvailable);

    /**
     * @brief m_pEnggMenuEventProvider: Pointer of the CEnggMenuEventProvider class to access the functions that
     * will emit the signals on value change
     */
    CEnggMenuEventProvider* m_pEnggMenuEventProvider;

    /**
     * @brief m_pEnggMenuPressCtrlProxy: Proxy Declaration
     */
    CAPIClientAbstraction<EnggMenuPresCtrlProxy> m_pEnggMenuPressCtrlProxy;

    /**
     * @brief m_bIsEnggServiceAvailable: boolean variable to check if the EnggService is available or not.
     */
    bool m_bIsEnggServiceAvailable;
};

#endif // CENGGMENURESOURCEIMPL_H

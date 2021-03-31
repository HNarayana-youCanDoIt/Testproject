/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file   IEnggMenuResource.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 *  This interface file provides functionality which interacts with the below PresCtrl or Resource proxy directly.
 It also provides functionality via which data can be provided to the upper layer.
 It also propagates various events (Hard key, VR, etc) to the upper layers. This is done via Qt Signals
**/

#ifndef IENGGMENURESOURCE_H
#define IENGGMENURESOURCE_H
#include <string>
#include <QString>
#include "interfaces/CDataEnggMenu.h"

#include "v0/com/harman/dcif/EnggMenuTypes.hpp"
#include "v0/com/harman/dcif/EnggMenuPresCtrl.hpp"
#include "v0/com/harman/dcif/EnggMenuPresCtrlProxy.hpp"
#include "v0/com/harman/dcif/EnggMenuPresCtrlProxyBase.hpp"
#include <capi/CAPIClientAbstraction.hpp>
using namespace std;
using namespace v0::com::harman::dcif;



/** @brief:
* * IEnggMenuResource class, This interface provides functionality which interacts with the below PresCtrl or Resource proxy directly.
 It also provides functionality via which data can be provided to the upper layer.
 It also propagates various events (Hard key, VR, etc) to the upper layers. This is done via Qt Signals
**/

class IEnggMenuResource
{
public:
    /**
    * @brief	IEnggMenuResource::~IEnggMenuResource Destructor for  class IEnggMenuResource.
    * @param	void
    * @return	void
    **/
    virtual ~IEnggMenuResource() {}


    /*********************************************************
                         Request Methods
     *********************************************************/

    /**
    * @brief	IEnggMenuResource::startDebugLogsService,This function starts the logs
    * @param	void
    * @return	void
    **/
    virtual void startDebugLogsService() = 0;
    //________________________________________________________________________________________________
    /**
    * @brief	IEnggMenuResource::stopDebugLogsService,This function stops the logs
    * @param	void
    * @return	void
    **/
    virtual void stopDebugLogsService() = 0;
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggMenuResourceImpl::extractDebugLogs,This function calls the pres's api to extract the Debug Logs to USB.
    * @param	void
    * @return	void
    **/
    virtual void extractDebugLogs() = 0;

    /**
    * @brief	IEnggMenuResource::setSystemIpAddress,This function will set the type of IP of System.
    * @param	bool bIPType: Checkbox status whether we have to set static Ip or Dynamic IP.
    * @return	void
    **/
    virtual void setSystemIpAddress(bool bIPType) = 0;
    //________________________________________________________________________________________________

    /**
    * @brief	IEnggMenuResource::testAutomationToggleService,This function starts/stop Test Automation service.
    * @param	void
    * @return	void
    **/
    virtual void testAutomationToggleService(bool bIsTestAutomationEnable) = 0;
    //________________________________________________________________________________________________

    /**
    * @brief	IEnggMenuResource::startFactoryReset,This function performs factory reset task
    * @param	void
    * @return	void
    **/
    virtual void startFactoryReset() = 0;

    //________________________________________________________________________________________________

    /**
    * @brief	IEnggMenuResource::setDeviceMode,This function sets the system mode i.e Device mode or Host Mode.
    * @param	bDeviceMode: contains device mode option
    * @return	void
    **/
    virtual void setDeviceMode(bool bDeviceMode) = 0;


private:

    /*********************************************************
                        CallBack Methods
     *********************************************************/
    /**
    * @brief	IEnggMenuResource::enggMenuServiceStatusCb,This function ensures the availability of EnggMenu service
    * @param	AvailabilityStatus eStatus, this provides the enum carrying the info whether the service is available,not known or unavailable.
    * @return	void
    **/
    virtual void enggMenuServiceStatusCb(CommonAPI::AvailabilityStatus eStatus) = 0;
    //________________________________________________________________________________________________

    /**
    * @brief	IEnggMenuResource::getFactoryResetCompleteEventCb,This callback function will be triggered whenever there is a signal emitted from service side
    * of completing factory reset
    * @param	bResetFactoryCompleteStatus , this provides the status of event completion/failure
    * @return	void
    **/
    virtual void getFactoryResetCompleteEventCb(bool bResetFactoryCompleteStatus) = 0;



    /*********************************************************
                     Response CallBack Methods
     *********************************************************/

    /**
     * @brief CallBack to get notified about startLoggingAsync method response
     * @param eCallStatus - call status of the startLoggingAsync method, whether success or not.
     * @param eReturnStatus - type of the error received after invoking startLoggingAsync method.
     * @return void
     */
    virtual void startLoggingAsyncCb(const CommonAPI::CallStatus &eCallStatus, const EnggMenuTypes::retStatus &eReturnStatus) = 0;
    //_____________________________________________________________________________________________________________________________________________________________


    /**
     * @brief CallBack to get notified about stopLoggingAsync method response
     * @param eCallStatus - call status of the stopLoggingAsync method, whether success or not.
     * @param eReturnStatus - type of the error received after invoking stopLoggingAsync method.
     * @return void
     */
    virtual void stopLoggingAsyncCb(const CommonAPI::CallStatus &eCallStatus, const EnggMenuTypes::retStatus &eReturnStatus) = 0;
    //_____________________________________________________________________________________________________________________________________________________________


    /**
     * @brief CallBack to get notified about setSystemStaticIpAddress method response
     * @param status - call status of the setSystemStaticIpAddress method, whether success or not.
     * @param returnStatus - type of the error received after invoking setSystemStaticIpAddress method.
     * @return void
     */
    virtual void setSystemStaticIpAddressCb(const CommonAPI::CallStatus&status,const ::v0::com::harman::dcif::EnggMenuTypes::retStatus&returnStatus) = 0;
    //_____________________________________________________________________________________________________________________________________________________________


    /**
     * @brief CallBack to get notified about setSystemDynamicIpAddress method response
     * @param status - call status of the setSystemDynamicIpAddress method, whether success or not.
     * @param returnStatus - type of the error received after invoking setSystemDynamicIpAddress method.
     * @return void
     */
    virtual void setSystemDynamicIpAddressCb(const CommonAPI::CallStatus&status,const ::v0::com::harman::dcif::EnggMenuTypes::retStatus&returnStatus) = 0;
    //_____________________________________________________________________________________________________________________________________________________________


    /**
     * @brief CallBack to get notified about testAutomationToggleService method response
     * @param status - call status of the testAutomationToggleService method, whether success or not.
     * @param returnStatus - type of the error received after invoking testAutomationToggleService method.
     * @return void
     */
    virtual void testAutomationStartServiceCb(const CommonAPI::CallStatus&status,const ::v0::com::harman::dcif::EnggMenuTypes::retStatus&returnStatus) = 0;
    //_____________________________________________________________________________________________________________________________________________________________

    /**
     * @brief CallBack to get notified about testAutomationStopService method response
     * @param status - call status of the testAutomationStopService method, whether success or not.
     * @param returnStatus - type of the error received after invoking testAutomationStopService method.
     * @return void
     */
    virtual void testAutomationStopServiceCb(const CommonAPI::CallStatus&status,const ::v0::com::harman::dcif::EnggMenuTypes::retStatus&returnStatus) = 0;
    //_____________________________________________________________________________________________________________________________________________________________


    /**
     * @brief CallBack to get notified about startFactoryReset method response
     * @param status - call status of the startFactoryReset method, whether success or not.
     * @param result - type of the error received after invoking startFactoryReset method.
     * @return void
     */
    virtual void factoryResetCb(const CommonAPI::CallStatus& status,const EnggMenuTypes::retStatus& returnStatus) = 0;

    //________________________________________________________________________________________________

    /**
     * @brief CallBack to get notified about setDeviceMode method response
     * @param status - call status of the setDeviceMode method, whether success or not.
     * @param modeType - type of mode activated.
     * @param deviceModeStatus - device mode status.
     */
    virtual void setDeviceModeCb(const CommonAPI::CallStatus& status, const EnggMenuTypes::modeType& modeType, const EnggMenuTypes::deviceModeStatus& deviceModeStatus ) = 0;

    /**
     * @brief extractLogsAsyncCb: callback function for extractLogsAsync reques function.
     * @param eCallStatus: call status of the extractLogsAsync method, whether success or not.
     * @param eExtractLogsProcessStatus: Status while extracting logs. Like usb not connected, usb is full or success.
     */
    virtual void extractLogsAsyncCb(const CallStatus &eCallStatus, const EnggMenuTypes::extractLogsError_enum &eExtractLogsProcessStatus) = 0;


};
#endif // IENGGMENURESOURCE_H


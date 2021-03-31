/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggEventHandler.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande,Rajat Gupta
 * CEnggEventHandler, an Resource handler for Engineering module,
 * CEnggEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#ifndef CENGGEVENTHANDLER_H
#define CENGGEVENTHANDLER_H

#include <QObject>

class CEnggApplication;
class CEnggAdaptor;
class CEnggSM;

/**
 * @brief
 * CEnggEventHandler, an Resource handler for Engineering module,
 * It act as mediator between adaptor and resource manager,
 * This listens signals raised by the resource layer provider class,
 * It has the implementation of the corresponding slots.
 */
class CEnggEventHandler: public QObject
{
    Q_OBJECT
public:
    /**
    * @brief	CEnggEventHandler::CEnggEventHandler constructor for data handler class CEnggEventHandler.
    * @param	pParent: Parent class pointer.
    * @return	void.
    **/
    CEnggEventHandler(QObject* pParent = 0);
    //________________________________________________________________________________________________
    /**
    * @brief	CEnggEventHandler::~CEnggEventHandler is destructor of data handler class CEnggEventHandler
    * @param	void.
    * @return	void.
    **/
    ~CEnggEventHandler();
    //________________________________________________________________________________________________
public slots:
    // Declare the slots that would be invoked on the resource layer events signals___________________________________________

    /**
    * @brief	CEnggEventHandler::sltUpdateDebugsLogCheckStatus is a slot which will be evoked when the signal will be emitted.
    * @param	bDebugsLogStatus: DebugsLog check/uncheck status.
    * @return	void.
    **/

    void sltUpdateDebugsLogCheckStatus(bool bDebugsLogStatus);
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggEventHandler::sltUpdateIpTypeStatus is a slot which will be evoked when the signal will be emitted.
    * @param	iIpStatusCb, This will give the info regarding the UpdateIpTypeStatus Status.
    * @param.   iIpTypeCb, this will tell about the IP Type which is enabled
    * @return	void.
    **/

    void sltUpdateIpTypeStatus(int iIpStatusCb, int iIpTypeCb);
    //________________________________________________________________________________________________


    /**
    * @brief	CEnggEventHandler::sltUpdateTestAutomationStatus is a slot which will be evoked when the signal will be emitted.
    * @param	iTestAutomationStatusCb, This will give the info regarding the test automation Status.
    * @param	iTestAutomationValueCb, This will give the info regarding the value of  automation value ie. enable/disable.
    * @return	void.
    **/

    void sltUpdateTestAutomationStatus(int iTestAutomationStatusCb, int iTestAutomationValueCb);
    //________________________________________________________________________________________________


    /**
    * @brief	CEnggEventHandler::sltUpdateFactoryResetWaitingStatus is a slot which will be evoked when the signal will be emitted.
    * @param	bool bStatus: contains the status of factory reset callback
    * @return	void.
    **/

    void sltUpdateFactoryResetWaitingStatus(bool bFactoryResetWaitingStatus);
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggEventHandler::sltUpdateFactoryResetCompletionStatus is a slot which will be evoked when the signal will be emitted.
    * @param	bool bFactoryResetCompletionStatus: contains the status of factory reset completion callback
    * @return	void.
    **/

    void sltUpdateFactoryResetCompletionStatus(bool bFactoryResetCompletionStatus);
    //________________________________________________________________________________________________

    /**
    * @brief	CEnggEventHandler::sltUpdateDeviceModeStatus, evoked when the device mode callback signal will be emitted.
    * @param	iDeviceModeStatus:  status of device mode callback
    * @param	iDeviceType:  type of mode which has been activated
    * @return	void.
    **/

    void sltUpdateDeviceModeStatus(int iDeviceModeStatus, int iDeviceType);
    //________________________________________________________________________________________________

    /**
     * @brief	sltUpdateFactoryResetCompletionStatus: This slot is to update the engg proxy availability status to HMI.
     * @param   bIsEnggMenuProxyAvailable: Holds status whether Engg Proxy is available or not.
     * @return	void.
     */
    void sltUpdateEnggProxyAvailabilityToHMI(bool bIsEnggMenuProxyAvailable);
	//________________________________________________________________________________________________
	
    /**
     * @brief	sltUpdateExtractLogsStatus: This slot is to update the extract logs to usb status.
     * @param   int iExtractLogsProcessStatus: This will give the info regarding the extract Logs status(SUCCESS = 0,USB_NOT_CONNECTED = 1,
     *          LOGGING_NOT_ENABLED = 2,USB_DEVICE_FULL=3)
     * @return	void.
     */
    void sltUpdateExtractLogsStatus(int iExtractLogsProcessStatus);
    //________________________________________________________________________________________________

private:
    /**
     * @brief connectSignals: Function which will connect all the signals to the slot coming from Resource Layer.
     * @param void.
     * @return void.
     */
    void connectSignals();
    //________________________________________________________________________________________________
};

#endif // CENGGEVENTHANDLER_H

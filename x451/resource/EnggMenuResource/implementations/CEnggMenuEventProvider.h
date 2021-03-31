/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CEnggMenuEventProvider.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CEnggMenuEventProvider class, The class will emit the signal
 * from Resource Layer to application Layer
 *
**/


#ifndef CENGGMENUEVENTPROVIDER_H
#define CENGGMENUEVENTPROVIDER_H
#include <QObject>
#include <string.h>
#include <interfaces/CDataEnggMenu.h>

/** @brief: CEnggMenuEventProvider class, The class will emit the signal
 * from Resource Layer to application Layer
**/

class CEnggMenuEventProvider: public QObject
{
    Q_OBJECT
public:
    /**
    * @brief	CEnggMenuEventProvider::CEnggMenuEventProvider Constructor for class CEnggMenuEventProvider
    * @param	pParent: Parent class pointer.
    * @return	void
    **/
    CEnggMenuEventProvider(QObject* pParent = 0);

    /**
    * @brief	CEnggMenuEventProvider::~CEnggMenuEventProvider Destructor for class CEnggMenuEventProvider
    * @param	void
    * @return	void
    **/
    ~CEnggMenuEventProvider();

signals:

    /**
     * @brief sigUpdateDebugsLogCheckStatus: signal to emit when the DebugLog Status will change to Enable status
     * @param bDebugsLogStatus: Debugslog check/uncheck status
     * @return	void
     */
    void sigUpdateDebugsLogCheckStatus(bool bDebugsLogStatus);

    /**
     * @brief sigUpdateIpTypeStatus: signal to emit when the IP type gets change.
     * @param iIpStatusCb: contains IP Callback status
     * @param iIpTypeCb: Type of IP in a callback.
     */
    void sigUpdateIpTypeStatus(int  iIpStatusCb , int iIpTypeCb);

    /**
     * @brief sigUpdateTestAutomation: signal to emit when the test automation gets toggle.
     * @param iTestAutomationStatusCb: Function call back status.
     * @param iTestAutomationValueCb: Test Automation Value .
     */
    void sigUpdateTestAutomation(int  iTestAutomationStatusCb, int iTestAutomationValueCb);

    /**
     * @brief sigUpdateFactoryResetWaitingStatus: signal to emit when the factory reset status will be given by service
     * @param bFactoryResetWaitingStatus: Factory reset Waiting Status
     */
    void sigUpdateFactoryResetWaitingStatus(bool bFactoryResetWaitingStatus);

    /**
     * @brief sigUpdateFactoryResetCompleteStatus: signal to emit when the factory reset is completed
     * @param bFactoryResetCompletionStatus: contains the info of factory reswet completion status.
     */
    void sigUpdateFactoryResetCompleteStatus(bool bFactoryResetCompletionStatus);

    /**
     * @brief sigUpdateDeviceModeStatus: Signal to update the Device Mode status to adaptor layer
     * @param iDeviceModeStatus : device Mode status.
     * @param iDeviceType : Type of mode activated. ie. Device mode/Host Mode.
     */
    void sigUpdateDeviceModeStatus(int iDeviceModeStatus, int iDeviceType);

    /**
     * @brief	sigUpdateEnggProxyAvailabilityToHMI: This signal is to update the engg proxy availability status to HMI.
     * @param   bIsEnggMenuProxyAvailable: Holds status whether Engg Proxy is available or not.
     * @return	void.
     */
    void sigUpdateEnggProxyAvailabilityToHMI(bool bIsEnggMenuProxyAvailable);

    /**
    * @brief	This signal is to update the extract logs return status
    * @param	int iExtractLogsProcessStatus: SUCCESS = 0,USB_NOT_CONNECTED = 1,LOGGING_NOT_ENABLED = 2,USB_DEVICE_FULL=3
    * @return	void
    **/
    void sigUpdateExtractLogsStatus(int iExtractLogsProcessStatus);

public:

    /**
    * @brief	CEnggMenuEventProvider::updateDebugsLogCheckStatus.This function will be used by
    * the Resource Layer to emit signals to the upper layers
    * @param	bDebugsLogStatus: DebugLogs Check/uncheck status.S
    * @return	void
    **/
    void updateDebugsLogCheckStatus(bool bDebugsLogStatus);

    /**
    * @brief	CEnggMenuEventProvider::UpdateIpTypeStatus.This function will be used by
    * the Resource Layer to emit signals to the upper layers
    * @param	iIpStatusCb, This will give the info regarding the status of Ip change callback
    * @param.   iIpTypeCb, this will give the info about the type of ip
    * @return	void
    **/

    void UpdateIpTypeStatus(int iIpStatusCb, int iIpTypeCb);

    /**
    * @brief	CEnggMenuEventProvider::UpdateTestAutomationLaunchStatus.This function will be used by
    * the Resource Layer to emit signals to the upper layers
    * @param	iTestAutomationStatusCb, This will give the info regarding the status of Test automation callback
    * @param    iTestAutomationValueCb,  this will give the info about the value of TestAutomation i.e active or inactive
    * @return	void
    **/

    void UpdateTestAutomationLaunchStatus(int iTestAutomationStatusCb, int iTestAutomationValueCb);

    /**
    * @brief	CEnggMenuEventProvider::updatefactoryResetWaitingStatus.This function will be used by
    * the Resource Layer to emit signals to the upper layers
    * @param	bool bFactoryResetWaitingStatus, This will give the info regarding the factory reset  Status.
    * @return	void
    **/

    void updatefactoryResetWaitingStatus(bool bFactoryResetWaitingStatus);

    /**
    * @brief	CEnggMenuEventProvider::updateFactoryResetCompletionStatus.This function will be used by
    * the Resource Layer to emit signals to the upper layers
    * @param	bool bFactoryResetCompletionStatus, This will give the info regarding the factory reset completion Status.
    * @return	void
    **/

    void updateFactoryResetCompletionStatus(bool bFactoryResetCompletionStatus);

    /**
    * @brief	CEnggMenuEventProvider: updateDeviceModeStatus, updates the callback status and device type of device Mode.
    * @param	iDeviceModeStatus: status of device mode callback
    * @param	iDeviceType: type of device mode.
    * @return	void
    **/

    void updateDeviceModeStatus(int iDeviceModeStatus, int iDeviceType);

    /**
     * @brief	updateEnggProxyAvailabilityToHMI: This function is to update the engg proxy availability status to HMI.
     * @param   bIsEnggMenuProxyAvailable: Holds status whether Engg Proxy is available or not.
     * @return	void.
     */
    void updateEnggProxyAvailabilityToHMI(bool bIsEnggMenuProxyAvailable);
	
    /**
     * @brief	CEnggMenuEventProvider::updateExtractLogsStatus.This function will be used by
     *          the Resource Layer to emit signals to the upper layers.
     * @param	iExtractLogsProcessStatus, This will give the info regarding the extract Logs status(SUCCESS = 0,USB_NOT_CONNECTED = 1,
     *          LOGGING_NOT_ENABLED = 2,USB_DEVICE_FULL=3)
     * @return	void
     **/
    void updateExtractLogsStatus(int iExtractLogsProcessStatus);
};

#endif // CENGGMENUEVENTPROVIDER_H





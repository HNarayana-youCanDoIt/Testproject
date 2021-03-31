/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
***************************************************************
*/
/**
* @file         CVRProxyEventProvider.h
* @ingroup      HMIComponent
* @author       Rahul Singh Parihar
* @brief        CVRProxyEventProvider class to send signals to adaptor layer on
* voice recognition updates
*/

#ifndef CVRPROXYEVENTPROVIDER_H
#define CVRPROXYEVENTPROVIDER_H

#include <QObject>

class CVRProxyEventProvider: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief   CVRProxyEventProvider - Constructor of CVRProxyEventProvider class.
     * @param   pParent - parent class pointer
     * @return  NA
     */
    CVRProxyEventProvider(QObject* pParent = 0);

    /**
     * @brief   ~CVRProxyEventProvider - Destructor of CVRProxyEventProvider class
     * @param   void.
     * @return  void.
     */
    ~CVRProxyEventProvider();

signals:
    /******************************************************//**
     * @category SIGNALS
     * @brief Signals that shall be emitted to the adaptor layer
     *******************************************************/

    /**
     * @brief   sigVRStateChange - Signal that shall be emited to notify
     *          VR state change.
     * @param   iVRState - current state of voice recognition.
     * @return  void.
     */
    void sigVRStateChange(int iVRState);

    /**
     * @brief   sigVRDialogStateChange - Signal that shall be emited to notify
     *          VR dialog state change.
     * @param   iVRDialogState - current dialog state of voice recognition.
     * @return  void.
     */
    void sigVRDialogStateChange(int iVRDialogState);

    /**
     * @brief   sigVRAvailableStatus - Signal that shall be emited to notify
     *          VR available status.
     * @param   bVRAvailableState - status of VR availibility, whether available or not.
     * @return  void.
     */
    void sigVRAvailableStatus(bool bVRAvailableStatus);

    /**
     * @brief   sigVRProxyAvailableStatus - Signal that shall be emited to notify
     *          VR proxy available status.
     * @param   bVRProxyAvailableStatus - status of VR proxy availibility, whether available or not.
     * @return  void.
     */
    void sigVRProxyAvailableStatus(bool bVRProxyAvailableStatus);

public:
    /************************************************************************//**
     * @category    METHODS
     * @brief       Methods that would be used by the VRProxyResource layer to
     * emit signals to the VR adaptor layer
     ************************************************************************/

    /**
     * @brief   updateVRStateChangeStatus - Method to inform VR adaptor layer regarding
     *          VR state change status.
     * @param   iVRState - current state of voice recognition.
     * @return  void.
     */
    void updateVRStateChangeStatus(int iVRState);

    /**
     * @brief   updateVRDialogStateChangeStatus - Method to inform VR adaptor layer regarding
     *          VR dialog state change status.
     * @param   iVRDialogState - current dialog state of voice recognition.
     * @return  void.
     */
    void updateVRDialogStateChangeStatus(int iVRDialogState);

    /**
     * @brief   updateVRAvailableStatus - Method to inform VR adaptor layer regarding
     *          VR available status.
     * @param   bVRAvailableStatus - status of VR availibility, whether available or not.
     * @return  void.
     */
    void updateVRAvailableStatus(bool bVRAvailableStatus);

    /**
     * @brief   updateVRProxyAvailableStatus - Method to inform VR adaptor layer regarding
     *          VR proxy available status.
     * @param   bVRProxyAvailableStatus - status of VR proxy availibility, whether available or not.
     * @return  void.
     */
    void updateVRProxyAvailableStatus(bool bVRProxyAvailableStatus);
};

#endif // CVRPROXYEVENTPROVIDER_H

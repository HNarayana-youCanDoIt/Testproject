/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDeviceModeHandlerEventProvider.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CDeviceModeHandlerEventProvider, Class to send signals to DeviceModeHandler
* Application layer on DeviceModeHandler Resource events
*/
#ifndef CDEVICEMODEHANDLEREVENTPROVIDER_H
#define CDEVICEMODEHANDLEREVENTPROVIDER_H

#include <QObject>

/**
 * @class CDeviceModeHandlerEventProvider
 * @brief Class to send signals to DeviceModeHandler Application layer
 *        on DeviceModeHandler Resource events
 */
class CDeviceModeHandlerEventProvider : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief   CDeviceModeHandlerEventProvider: constructor of
     *          CDeviceModeHandlerEventProvider
     * @param   parent class pointer.
     * @return  NA
     */
    CDeviceModeHandlerEventProvider(QObject* parent = 0);

    /**
     * @brief   ~CDeviceModeHandlerEventProvider: Destructor of
     *          CDeviceModeHandlerEventProvider
     * @param   NA.
     * @return  NA
     */
    ~CDeviceModeHandlerEventProvider();

signals:
    /**
     * @brief   sigUpdateAAConnectionStatus: Signal to notify the Adaptor layer
     *          for the change of AndroidAuto connection status.
     * @param   bAAConnectionStatus: Android Auto connection status.
     * @return  void.
     */
    void sigUpdateAAConnectionStatus(bool bAAConnectionStatus);

    /**
     * @brief   sigUpdateAABondingReqStatus: Signal to notify the Adaptor layer
     *          for the change of AndroidAuto bond req status.
     * @param   bAABondReqStatus: Android Auto bond req status.
     * @return  void.
     */
    void sigUpdateAABondingReqStatus(bool bAABondReqStatus);


    /**
     * @brief   sigUpdateCarPlayConnectionStatus: Signal to notify the Adaptor
     *          layer for the change of CarPlay connection status.
     * @param   bCarPlayConnectionStatus: CarPlay connection status.
     * @return  void.
     */
    void sigUpdateCarPlayConnectionStatus(bool bCarPlayConnectionStatus);

public:

    /**
     * @brief   updateAAConnectionStatus: This function is called from Resource
     *          implimentation, to inform the adaptor layer about the connection
     *          status update of Android Auto. This function emmits the signal
     *          sigUpdateAAConnectionStatus, to update the Adaptor layer.
     * @param   bAAConnectionStatus: connection status of Android Auto.
     * @return  void.
     */
    void updateAAConnectionStatus(bool bAAConnectionStatus);

    /**
     * @brief   updateAABondingReqStatus: This function is called from Resource
     *          implimentation, to inform the adaptor layer about the bonding request
     *          status update of Android Auto. This function emmits the signal
     *          sigUpdateAABondingReqStatus, to update the Adaptor layer.
     * @param   bAAConnectionStatus: connection status of Android Auto.
     * @return  void.
     */
    void updateAABondingReqStatus(bool bAABondingReqStatus);

    /**
     * @brief   updateCarPlayConnectionStatus: This function is called from
     *          Resource implimentation, to inform the adaptor layer about the
     *          connection status update of Android Auto. This function emmits
     *          the signal sigUpdateCarPlayConnectionStatus, to update the
     *          Adaptor layer.
     * @param   bCarPlayConnectionStatus: connection status of CarPlay.
     * @return  void
     */
    void updateCarPlayConnectionStatus(bool bCarPlayConnectionStatus);

};

#endif // CDEVICEMODEHANDLEREVENTPROVIDER_H

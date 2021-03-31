/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CAndroidAutoEventHandler.h
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         This file contains CAndroidAutoEventHandler class that
 *                implements the slot for the signals emited by AndroidAuto
 *                resource layer to inform AndroidAuto adaptor regarding the
 *                updates in AndroidAuto resource layer.
 */

#ifndef CANDROIDAUTOEVENTHANDLER_H
#define CANDROIDAUTOEVENTHANDLER_H

#include <QObject>

/*!
 * @class CAndroidAutoEventHandler
 * @brief This class implements the slot for the signals emited by AndroidAuto
 *        resource layer to inform AndroidAuto adaptor regarding the updates
 *        in AndroidAuto resource layer.
 */
class CAndroidAutoEventHandler: public QObject
{
    Q_OBJECT
public:
    /*!
     * @brief   Constructor of CAndroidAutoEventHandler
     * @param   pParent: parent class pointer.
     * @return  void.
     */
    CAndroidAutoEventHandler(QObject* pParent = 0);

    /*!
     * @brief   Destructor of CAndroidAutoEventHandler
     * @param   void.
     * @return  void.
     */
    ~CAndroidAutoEventHandler();

private slots:
    /********************************************************************//**
     * @category    ANDROID AUTO EVENT HANDLER SLOTS
     * @brief       Slots for the signals emitted by AndroidAuto resource
     *********************************************************************/

    /*!
     * @brief   Method to notify AndroidAuto adaptor regarding update of
     *          AndroidAuto Connection status.
     * @param   bAAConnectionStatus: true if connected else false.
     * @return  void.
     */
    void sltUpdateAndroidAutoConnectionStatus(bool bAAConnectionStatus);


    /*!
     * @brief   Method to notify AndroidAuto adaptor regarding update of
     *          AndroidAuto bond req status.
     * @param   bAABondReqStatus: true if connected else false.
     * @return  void.
     */
    void sltUpdateAndroidAutoBondReqStatus(bool bAABondReqStatus);


    /**
     * @brief   Method to show Android Auto first run popup.
     */
    void sltShowFirstRunPopup();

    /**
     * @brief   sltUpdateAAMediaMetaData: The slot for sigUpdateAAMediaMetaData,
     *          to update AA media meta data in AndroidAuto Adaptor.
     * @param   void.
     * @return  void.
     */
    void sltUpdateAAMediaMetaData();

    /**
     * @brief   sltUpdateAAMediaPlayState: The slot for sigUpdateAAMediaPlayState,
     *          to update AAMedia playState in AndroidAuto Adaptor.
     * @param   usAAMediaPlayState: AAMediaPlayState.
     * @return  void.
     */
    void sltUpdateAAMediaPlayState(ushort usAAMediaPlayState);

    /**
     * @brief   sltUpdateAAProjectionStatus: The slot for
     *          sigUpdateAAProjectionStatus, to update AAProjectionStatus
     *          in AndroidAuto Adaptor.
     * @param   bAAProjectionStatus: AAProjectionStatus, true if projected
     *          else false.
     * @return  void.
     */
    void sltUpdateAAProjectionStatus(bool bAAProjectionStatus);

    /**
     * @brief   sltUpdateOKGoogleStatus: The slot for
     *          sigUpdateOKGoogleStatus, to update OKGoogle Status
     *          in AndroidAuto Adaptor.
     * @param   bOKGoogleStatus: OKGoogle Status, true if active
     *          else false.
     * @return  void.
     */
    void sltUpdateOKGoogleStatus(bool bOKGoogleStatus);

    /**
     * @brief   sltUpdateAANaviStatus: The slot for
     *          sigUpdateAANaviStatus, to update AndroidAuto Navigation Status
     *          in AndroidAuto Adaptor.
     * @param   bAANaviStatus: AndroidAuto Navigation Status, true if active
     *          else false.
     * @return  void.
     */
    void sltUpdateAANaviStatus(bool bAANaviStatus);

    /**
     * @brief   sltUpdateAASessionDetails: The slot for
     *          sigUpdateAASessionDetails, to update AndroidAuto session details
     *          in AndroidAuto Adaptor.
     * @param   void.
     * @return  void.
     */
    void sltUpdateAASessionDetails();

    /**
     * @brief   sltUpdateAANaviTurnEventDetails: This function is called, Whenever
     *          AA Navigation details received from resource layer.
     * @param   void.
     * @return  void.
     */
    void sltUpdateAANaviTurnEventDetails();

    /**
     * @brief   sltUpdateAANaviDistanceDetails: This function is called, Whenever
     *          AA Navigation distance received from resource layer.
     * @param   void.
     * @return  void.
     */
    void sltUpdateAANaviDistanceDetails();

private:
    /******************************************************//**
     * @category    INTERNAL METHODS
     *******************************************************/

    /*!
     * @brief   Method to connect signals provided by CDeviceModeHandlerEventProvider
     *          class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void connectDeviceModeHandlerEventProviderSignals();

    /*!
     * @brief   Method to disconnect signals provided by
     *          CDeviceModeHandlerEventProvider class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void disconnectDeviceModeHandlerEventProviderSignals();

    /*!
     * @brief   Method to connect signals provided by CAndroidAutoEventProvider
     *          class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void connectAndroidAutoEventProviderSignals();

    /*!
     * @brief   Method to disconnect signals provided by
     *          CAndroidAutoEventProvider class with the internal slots.
     * @param   void.
     * @return  void.
     */
    void disconnectAndroidAutoEventProviderSignals();

private:

};

#endif // CANDROIDAUTOEVENTHANDLER_H

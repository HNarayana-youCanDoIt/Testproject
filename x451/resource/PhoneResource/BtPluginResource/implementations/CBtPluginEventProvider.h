/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CBtPluginEventProvider.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CBtPluginEventProvider class that shall publish events
 * whenever HMI BtPluginResource layer receive some response or callbacks from BtPlugin proxy.
 */

#ifndef CBTPLUGINEVENTPROVIDER_H
#define CBTPLUGINEVENTPROVIDER_H

#include <QObject>
#include "PhoneResource/CPhoneResourceEnums.h"

/*!
 * @class CBtPluginEventProvider
 */
class CBtPluginEventProvider: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief   CBtPluginEventProvider - Constructor of CBtPluginEventProvider class.
     * @param   pParent - parent class pointer
     * @return  NA
     */
    CBtPluginEventProvider(QObject* pParent = 0);

    /**
     * @brief   ~CBtPluginEventProvider - Destructor of CBtPluginEventProvider class
     * @param   void.
     * @return  void.
     */
    ~CBtPluginEventProvider();

signals:
    /******************************************************//**
     * @category SIGNALS
     * @brief Signals that shall be emitted to the adaptor layer
     *******************************************************/

    /**
     * @brief   sigStartTTSPlayAsyncMethodCallStatus - Signal that shall be emited to notify
     *          TTS playstate status.
     * @param   iTTSPlayState - current playstate of TTS.
     * @return  void.
     */
    void sigTTSPlayStateStatus(int iTTSPlayState);

public:
    /************************************************************************//**
     * @category    METHODS
     * @brief       Methods that would be used by the BtPluginResource layer to
     * emit signals to the phone adaptor layer
     ************************************************************************/

    /*!
     * @brief   updateTTSPlayStateStatus - Method to inform phone adaptor layer regarding
     *          TTS playstate status.
     * @param   iTTSPlayState - current playstate of TTS.
     * @return  void.
     */
    void updateTTSPlayStateStatus(int iTTSPlayState);
};

#endif // CBTPLUGINEVENTPROVIDER_H

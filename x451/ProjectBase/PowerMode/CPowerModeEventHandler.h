/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CPowerModeEventHandler.h
 * @ingroup         HMIComponent
 * @author          Prashantkumar Raut
 * CPowerModeEventHandler - This class has the slots for all the Signals sent by CPowerModeEventProvider
 * which informs PowerMode Adaptor about PowerMode Resource Events
 */

#ifndef CPOWERMODEEVENTHANDLER_H
#define CPOWERMODEEVENTHANDLER_H

#include <QObject>
#include "CPowerModeEnums.h"

class CPowerModeAdaptor;

/**
 * @brief CPowerModeEventHandler - This class has the slots for all the Signals sent by CPowerModeEventProvider
 * which informs PowerMode Adaptor about PowerMode Resource Events
 */
class CPowerModeEventHandler: public QObject
{
    Q_OBJECT
public:
    /**
    * @brief	CPowerModeEventHandler::CPowerModeEventHandler constructor for data handler class CPowerModeEventHandler.
    * @param	QObject.
    * @return	NA.
    **/
    CPowerModeEventHandler(QObject* parent = 0);

    /**
    * @brief	CPowerModeEventHandler::~CPowerModeEventHandler is destructor of data handler class CPowerModeEventHandler
    * @param	NA.
    * @return	NA.
    **/
    ~CPowerModeEventHandler();

public slots:
    /**
    * @brief	CPowerModeEventHandler::sltPowerModeEvent is slot to get Power event change call back from resource
    * @param	string.
    * @return	void.
    **/
    void sltPowerModeEvent(QString m_mode);

    /**
     * @brief sltNSMNodeStateEvent, slot to get nsm node state change call back from resource
     * @param nsmNodeState
     * @return void
     */
    void sltNSMNodeStateEvent(int iNsmNodeState);

    /**
     * @brief sltUpdateOneHourExpiryState: Slot to get the state of one hour expiry.
     * @param bOneHourExpiryState: State of one hour expiry active or not.
     * @return void.
     */
    void sltUpdateOneHourExpiryState(bool bOneHourExpiryState);

private:
    /**
    * @brief	CPowerModeEventHandler::connectSignals is used to connect slot(s) with respective signals from resource
    * @param	void.
    * @return	void.
    **/
    void connectSignals();

    /**
     * member variable for storing the power mode received from the service in the class
     */
    CPowerModeEnums::eVehiclePowerModes m_ePowerMode;
};

#endif // CPOWERMODEEVENTHANDLER_H

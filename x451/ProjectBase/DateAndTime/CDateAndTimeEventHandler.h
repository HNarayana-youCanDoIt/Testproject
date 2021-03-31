/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CDateAndTimeEventHandler.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * This class is to handle DateAndTime settings and DateAndTime Control events.
 */
#ifndef CDATEANDTIMEEVENTHANDLER_H
#define CDATEANDTIMEEVENTHANDLER_H

#include <QObject>
#include "StateMachine_TML_HMI_SM.h"
#include "DateAndTime/CDateAndTimeAdaptor.h"

/**
 * @brief The CDateAndTimeEventHandler class: This class is to handle DateAndTime settings events.
 *          DateAndTime resource event provider will emit signals and those will be handled here.
 */
class CDateAndTimeEventHandler: public QObject
{
    Q_OBJECT

public:
    CDateAndTimeEventHandler(QObject* parent = 0);
    ~CDateAndTimeEventHandler();

public slots:

    /**
    * @brief	This function will update current date and time status received from Time Manager Resource layer.
    * @param	bDateAndTimeStatus: bDateAndTimeStatus value whether service function calling  was success or failure.
    * @return	void
    */
    void sltUpdateDateAndTimeStatusCb(bool bDateAndTimeStatus);
    /**
     * @brief   sltUpdateTimeFormatStatus: Updates the time format status in adaptor received from resource.
     * @param   iTimeFormat: contains time format, 1 - 12 hr, 2 - 24 hr.
     * @return	void.
     */
    void sltUpdateTimeFormatStatus(int iTimeFormat);

    /**
     * @brief   sltUpdateTimeFormatCbStatus: Updates the time format cb status received from resource.
     * @param   iCallStatus: time format callback status.
     * @param   bTimeFormatCbStatus: time format response callback status.
     * @return	void.
     */
    void sltUpdateTimeFormatCbStatus(int iCallStatus, bool bTimeFormatCbStatus);

private:
    /**
    * @brief	This function will connect signals and slots.
    * @param	void
    * @return	void
    */
    void connectSignals();

    /**
    * @brief	This function will disconnect signals and slots.
    * @param	void
    * @return	void
    */
    void disConnectSignals();
};

#endif // CDateAndTimeEventHandler_H

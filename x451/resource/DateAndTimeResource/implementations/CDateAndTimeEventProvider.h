/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CDateAndTimeEventProvider.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CDateAndTimeEventProvider, Class to send signals to DateAndTime Application layer on DateAndTime Resource events
 */

#ifndef CDATEANDTIMEEVENTPROVIDER_H
#define CDATEANDTIMEEVENTPROVIDER_H

#include <QObject>
#include <string>
#include "DateAndTimeResource/interfaces/CDataTimeManagerResource.h"
using namespace std;

class CDateAndTimeEventProvider: public QObject
{
    Q_OBJECT

public:
    CDateAndTimeEventProvider(QObject* pParent = 0);
    ~CDateAndTimeEventProvider();

signals:

    /**
     * @brief sigUpdateDateAndTimeStatusCb : This signal gets emitted when date and time attribute gets change and cb gives
     * the status of change
     * @param bDateAndTimeStatus: bDateAndTimeStatus will give the status of the callback
     * @return	void.
     */
    void sigUpdateDateAndTimeStatusCb(bool bDateAndTimeStatus);

    /**
     * @brief   sigUpdateTimeFormatStatus: This signal gets emitted on time format status change.
     * @param   iTimeFormat: contains time format, 1 - 12 hr, 2 - 24 hr.
     * @return  void.
     */
    void sigUpdateTimeFormatStatus(int iTimeFormat);

    /**
     * @brief   sigUpdateTimeFormatCbStatus: Updates the time format cb status received from resource.
     * @param   iCallStatus: time format callback status.
     * @param   bTimeFormatCbStatus: time format response callback status.
     * @return	void.
     */
    void sigUpdateTimeFormatCbStatus(int iCallStatus, bool bTimeFormatCbStatus);

public:
    /**
    * @brief	This function is called from resource layer when there is a callback from TimeManager side after setting date and time.
    * @param	bDateAndTimeStatus: bDateAndTimeStatus will give the status of the callback
    * @return	void.
    */
    void updateDateAndTimeStatusCb(bool bDateAndTimeStatus);

    /**
     * @brief   updateTimeFormatStatus: Updates the time format status in adaptor received from resource.
     * @param   iTimeFormat: contains time format, 1 - 12 hr, 2 - 24 hr.
     * @return  void.
     */
    void updateTimeFormatStatus(int iTimeFormat);

    /**
     * @brief   updateTimeFormatCbStatus: Updates the time format cb status received from resource.
     * @param   iCallStatus: time format callback status.
     * @param   bTimeFormatCbStatus: time format response callback status.
     * @return	void.
     */
    void updateTimeFormatCbStatus(int iCallStatus, bool bTimeFormatCbStatus);

};

#endif // CDateAndTimeEventProvider_H

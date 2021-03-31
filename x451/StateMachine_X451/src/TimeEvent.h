/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         TimeEvent.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* TimeEvent     Class implements QTimer and sends timeout() signal when a timer is timed out
*               which helps in carrying out Timer events in StateChart
*/

#ifndef TIMEEVENT_H_
#define TIMEEVENT_H_

#include <QObject>
#include <QTimer>
#include "sc_types.h"

/**
 * @class TimeEvent
 * @brief Class implements QTimer and sends timeout() signal when a timer is timed out
 */
class TimeEvent: public QObject {

Q_OBJECT

public:
    TimeEvent(sc_eventid eventId, sc_integer time_ms, sc_boolean periodic);
    virtual ~TimeEvent();

public slots:
    /**
     * @brief This slot is called when timeout() signal of a timer(QTimer) is received
     * @param void
     * @return void
     */
    void sltTimeout();

signals:
    /**
     * @brief This signal is emitted when a timer(QTimer Instance) is timed out
     * @param eventId - Timer event Id
     * @return void
     */
    void sigTimeout(const sc_eventid eventId);

private:
    /** Id of Time Event **/
    sc_eventid m_eventId;

    /** Qtimer Instance **/
    QTimer *m_pTimer;
};

#endif /* TIMEEVENT_H_ */

/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         TimeEvent.cpp
* @ingroup      HMIComponent
* @author       Rahul Madan
* TimeEvent     Class implements QTimer and sends timeout() signal when a timer is timed out
*               which helps in carrying out Timer events in StateChart
*/

#include "TimeEvent.h"
#include "logging.h"

TimeEvent::TimeEvent(sc_eventid eventId, sc_integer time_ms, sc_boolean periodic) :
        QObject()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SYSTEM,"%s event:%Id time:%d",__FUNCTION__,eventId,time_ms);
    m_pTimer = new QTimer();
    m_eventId = eventId;
    m_pTimer->setSingleShot(!periodic);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(sltTimeout()));
    m_pTimer->start(time_ms);

}

void TimeEvent::sltTimeout()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SYSTEM,"%s event:%Id",__FUNCTION__,m_eventId);
    emit sigTimeout(m_eventId);
}

TimeEvent::~TimeEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SYSTEM,__FUNCTION__);
    if(m_pTimer)
    {
        disconnect(m_pTimer, SIGNAL(timeout()), this, SLOT(sltTimeout()));
        m_pTimer->stop();
        delete m_pTimer;
        m_pTimer = nullptr;
    }
}

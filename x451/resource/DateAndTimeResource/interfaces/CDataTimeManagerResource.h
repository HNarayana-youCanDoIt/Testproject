#ifndef CDATATIMEMANAGERENUMS_H
#define CDATATIMEMANAGERENUMS_H


struct SSystemTimeData {

    SSystemTimeData(): m_iSec(0),m_iMinute(0),m_iHour(0),m_iDay(0),m_iWeek(0),m_iMonth(0),m_iYear(0)
    {
    }
    SSystemTimeData(const int &_sec, const int &_minute, const int &_hour, const int &_week, const int &_Day, const int &_month, const int &_Year)
        : m_iSec(_sec),m_iMinute(_minute),m_iHour(_hour),m_iDay(_Day),m_iWeek(_week),m_iMonth(_month),m_iYear(_Year)
    {
    }

    int m_iSec   ;
    int m_iMinute;
    int m_iHour  ;
    int m_iDay   ;
    int m_iWeek  ;
    int m_iMonth ;
    int m_iYear  ;
};

#endif // CDATATIMEMANAGERENUMS_H

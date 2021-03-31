/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CDateAndTimeAdaptor.h
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * This class is to handle Date and Time settings and its functionality.
 */
#ifndef CDATEANDTIMEADAPTOR_H
#define CDATEANDTIMEADAPTOR_H

#include "QObject"
#include "logging.h"
#include "CFramework.h"
#include "DateAndTimeResource/interfaces/IDateAndTimeResource.h"
#include "DateAndTimeResource/implementations/CDateAndTimeResourceImpl.h"

/**
 * @brief The CDateAndTimeAdaptor class: This class contains methods to handle Date and Time related functionality
 *          like Date, Month, Hour, Minute eddtc.
 */
class CDateAndTimeAdaptor : public QObject
{
    Q_OBJECT

    // to get current hour value
    Q_PROPERTY(int hour     READ hour    WRITE setHour    NOTIFY sigHourChanged)

    // to get current minute value.
    Q_PROPERTY(int minute      READ minute     WRITE setMinute     NOTIFY sigMinuteChanged)

    // to get current sec value
    Q_PROPERTY(int sec     READ sec    WRITE setSec    NOTIFY sigSecChanged)

    // to get current day value.
    Q_PROPERTY(int day   READ day  WRITE setDay  NOTIFY sigDayChanged)

    // to get current month value.
    Q_PROPERTY(int month  READ month WRITE setMonth NOTIFY sigMonthChanged)

    //to get current year value.
    Q_PROPERTY(int year    READ year   WRITE setYear   NOTIFY sigYearChanged)

    //to get current AM/PM value.
    Q_PROPERTY(QString amOrPm    READ amOrPm   WRITE setAmOrPm   NOTIFY sigAmOrPmChanged)

    // to get current 24Hr checkbox status.
    Q_PROPERTY(bool is24HrFormatStatus   READ is24HrFormatStatus  WRITE setIs24HrFormatStatus NOTIFY sigIs24HrFormatStatusChanged)

    // to get the model for days for a particular year and month.
    Q_PROPERTY(int totalDays   READ totalDays  WRITE setTotalDaysStatus NOTIFY sigTotalDaysStatusChanged)

    // to get the enable status for 24Hr checkbox used in Date and time screen.
    Q_PROPERTY(bool timeFormatChangeReqStatus  READ timeFormatChangeReqStatus WRITE setTimeFormatChangeReqStatus NOTIFY sigTimeFormatChangeReqStatusChanged)


public:
    ~CDateAndTimeAdaptor();

    /**
    * @brief	This function will return hour value.
    * @param	void.
    * @return	hour: hour value
    */
    int hour();

    /**
    * @brief	This function will return minute value.
    * @param	void.
    * @return	minute: minute value
    */
    int minute();

    /**
        * @brief	This function will return sec value.
        * @param	void.
        * @return	sec: sec value
        */
    int sec();

    /**
    * @brief	This function will return day value.
    * @param	void.
    * @return	day: day value
    */
    int day();

    /**
    * @brief	This function will return month value.
    * @param	void.
    * @return	month: month value
    */
    int month();

    /**
    * @brief	This function will return year value.
    * @param	void.
    * @return	year: year value
    */
    int year();

    /**
    * @brief	This function will return AM/PM value.
    * @param	void.
    * @return	amOrPm: amOrPm value
    */
    QString amOrPm();

    /**
    * @brief	This function will return checkbox status of 24Hr format.
    * @param	void.
    * @return	It will return true when 24hr Checkbox status will be true else false.
    */
    bool is24HrFormatStatus();

    /**
    * @brief	This function will return total number of days.
    * @param	void.
    * @return	number of days present in a particular month of that year.
    */
    int totalDays();

    /**
    * @brief	This function get the instance of adaptor class.
    * @param	void.
    * @return   pointer
    */
    static CDateAndTimeAdaptor *getInstance();

    /**
    * @brief	This function will set hour value.
    * @param	iHour:  will set hour value.
    * @return	void
    */
    void setHour(int iHour);

    /**
    * @brief	This function will set minute value.
    * @param	iMinute will set minute value.
    * @return	void
    */
    void setMinute(int iMinute);

    /**
    * @brief	This function will set sec value.
    * @param	iSec will set sec value.
    * @return	void
    */
    void setSec(int iSec);

    /**
    * @brief	This function will set day value.
    * @param	iDay will set day value.
    * @return	void
    */
    void setDay(int iDay);

    /**
    * @brief	This function will set month value.
    * @param	iMonth will set month value.
    * @return	void
    */
    void setMonth(int iMonth);

    /**
    * @brief	This function will set year value.
    * @param	iYear will set year value.
    * @return	void
    */
    void setYear(int iYear);

    /**
    * @brief	This function will set AM/PM value.
    * @param	setAmOrPm will set AM/PM value.
    * @return	void
    */
    void setAmOrPm(const QString &strAmOrPm);

    /**
    * @brief	setIs24HrFormatStatus: This function will set the 24hr checkbox check/uncheck status.
    * @param	b24HrCheckboxStatus: will set 24hr format checkbox value.
    * @return	void
    */
    void setIs24HrFormatStatus(bool b24HrCheckboxStatus);

    /**
    * @brief	This function will set the no of days in a given month and year.
    * @param	iTotalDays will set the no of days.
    * @return	void
    */
    void setTotalDaysStatus(int iTotalDays);

    /**
    * @brief	This function will update date and time whenver qmlrelated to date and time will be loaded.
    * @param	void
    * @return	void
    */
    void updateDateAndTimeUI();

    /**
    * @brief	This function will set date and time property which is provided to qml.
    * @param	bDateAndTimeStatus, contains the status of callback
    * @return	void
    */
    void updateDateAndTimeResp(bool bDateAndTimeStatus);

    /**
     * @brief   updateTimeFormatStatus: Updates the time format status in adaptor received from resource.
     * @param   iTimeFormat: contains time format, 1 - 12 hr, 2 - 24 hr.
     * @return	void.
     */
    void updateTimeFormatStatus(int iTimeFormat);


    /**
    * @brief	invSetTimeFormat: This function will send the status of 24hr checkbox status to service.
    * @param	b24HrCheckboxStatus: value of 24hr format checkbox value.
    * @return	void
    */
    Q_INVOKABLE void invSetTimeFormat(bool b24HrCheckboxStatus);

    /**
    * @brief	timeFormatChangeReqStatus: Tihs will set the 24hr checkbox enable status.
    * @param	void.
    * @return	returns the checkbox enable/disable status.
    */
    bool timeFormatChangeReqStatus() { return m_bTimeFormatReqStatus; }

    /**
     * @brief setTimeFormatChangeReqStatus: sets the updated enable status value for 24hr checkbox.
     * @param bTimeFormatReqStatus: the updated value of the checkbox enable status.
     * @return	void
     */
    void setTimeFormatChangeReqStatus(bool bTimeFormatReqStatus);

    /**
     * @brief   updateTimeFormatChangeReqStatus: Updates the time format cb status received from resource.
     * @param   iCallStatus: time format callback status.
     * @param   bTimeFormatCbStatus: time format response callback status.
     * @return	void.
     */
    void updateTimeFormatChangeReqStatus(int iCallStatus, bool bTimeFormatCbStatus);

protected:
    /**
    * @brief	This function will set date and time from the qml to service.
    * @param
    * int iMin: contains the selected min,
    * int iHour:contains the selected hour,
    * int iDay:contains the selected day,
    * int iMonth:contains the selected month,
    * int iYear:contains the selected year,
    * QString amOrPm:contains the selected AM or PM,
    * int iSec:contains the selected sec
    * @return	void
    */
    Q_INVOKABLE void setDateAndTime(int iMin, int iHour, int iDay, int iMonth, int iYear, QString amOrPm, int iSec);

    /**
     * @brief	This function will validate and return the no of days on the given year and month.
     * @param	iMonth: contains the selected month from the tumbler,iYear :contains the selected year from the tumbler
     * @return	no of days in that particular year and month
     */
    Q_INVOKABLE int validateTotalDays(int iMonth,int iYear);

signals:
    /**
    * @brief	This signal will emit hour value whenever hour gets changed.
    * @param	void.
    * @return	void
    */
    void sigHourChanged();

    /**
    * @brief	This signal will emit minute value whenever minute gets changed.
    * @param	void.
    * @return	void
    */
    void sigMinuteChanged();

    /**
    * @brief	This signal will emit sec value whenever sec gets changed.
    * @param	void.
    * @return	void
    */
    void sigSecChanged();

    /**
    * @brief	This signal will emit day value whenever day gets changed.
    * @param	void.
    * @return	void
    */
    void sigDayChanged();

    /**
    * @brief	This signal will emit month value whenever month gets changed.
    * @param	void.
    * @return	void
    */
    void sigMonthChanged();

    /**
    * @brief	This signal will emit year value whenever year gets changed.
    * @param	void.
    * @return	void
    */
    void sigYearChanged();

    /**
    * @brief	This signal will emit AM/PM value whenever it gets changed.
    * @param	void.
    * @return	void
    */
    void sigAmOrPmChanged();

    /**
    * @brief	This signal will emit checkbox status value whenever its gets changed.
    * @param	void.
    * @return	void
    */
    void sigIs24HrFormatStatusChanged();

    /**
    * @brief	This signal will emit whenever no of days get change
    * @param	void.
    * @return	void
    */
    void sigTotalDaysStatusChanged();

    /**
    * @brief	sigTimeFormatChangeReqStatusChanged: This signal will emit whenever 24HR Checkbox Enable Status gets changed.
    * @param	void.
    * @return	void
    */
    void sigTimeFormatChangeReqStatusChanged();

private:

    /**
     * @brief CDateAndTimeAdaptor class Constructor
     * @param pParent
     * @return void
     */
    explicit CDateAndTimeAdaptor(QObject *parent = nullptr);

    /* Instance of class CDateAndTimeAdaptor */
    static CDateAndTimeAdaptor* m_pDateAndTimeAdaptor;

    /* Instance of class IDateAndTimeResource */
    IDateAndTimeResource* m_pDateAndTimeResource;

    /* This variable holds the hour value */
    int m_iHour;

    /* This variable holds the minute value */
    int m_iMinute;

    /* This variable holds the sec value */
    int m_iSec;

    /* This variable holds the day value */
    int m_iDay;

    /* This variable holds the month value */
    int m_iMonth;

    /* This variable holds the year value */
    int m_iYear;

    /* This variable holds the Am/Pm value */
    QString m_strAmorPm;

    /**
     * @brief m_bIs24HrFormatSelected: This variable holds the 24Hr Format check/uncheck status
     */
    bool m_bIs24HrFormatSelected;

    /* This variable holds the total days value */
    int m_iTotalDays;

    /**
     * @brief m_bTimeFormatReqStatus: variable to hold the value for d24hr checkbox enable status.
     */
    bool m_bTimeFormatReqStatus;

};

#endif // CDATEANDTIMEADAPTOR_H

/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CDateAndTimeAdaptor.cpp
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * This class is to handle DateAndTime settings and DateAndTime Controls functionality.
 */
#include "CDateAndTimeAdaptor.h"
#include "ResourceFactory.hpp"
#include "Setup/SetupDef.h"
#include "CHMIMain.h"
#include "CPersistencyAdaptor.h"
#include "resource/DateAndTimeResource/interfaces/CDataTimeManagerResource.h"
#include "CDateAndTimeEnums.h"

CDateAndTimeAdaptor* CDateAndTimeAdaptor::m_pDateAndTimeAdaptor = nullptr;

CDateAndTimeAdaptor::CDateAndTimeAdaptor(QObject *parent):
    QObject(parent),
    m_pDateAndTimeResource(ResourceFactory::getDateAndTimeResource()),
    m_iHour(1),
    m_iMinute(1),
    m_iSec(1),
    m_iDay(1),
    m_iMonth(1),
    m_iYear(2018),
    m_strAmorPm("AM"),
    m_bIs24HrFormatSelected(false),
    m_iTotalDays(30),
    m_bTimeFormatReqStatus(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    CDateAndTimeEnums::registerDateAndTimeEnumsToQML();
    updateDateAndTimeUI();
    CFramework::getFramework().setContextProperty("cppDateAndTimeAdaptor", this);
}

CDateAndTimeAdaptor::~CDateAndTimeAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    if(m_pDateAndTimeAdaptor)
    {
        delete m_pDateAndTimeAdaptor;
        m_pDateAndTimeAdaptor = nullptr;
    }
}

CDateAndTimeAdaptor* CDateAndTimeAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    if(nullptr == m_pDateAndTimeAdaptor)
    {
        m_pDateAndTimeAdaptor = new CDateAndTimeAdaptor();
    }
    return m_pDateAndTimeAdaptor;
}

int CDateAndTimeAdaptor::hour()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_iHour;
}

void CDateAndTimeAdaptor::setHour(int iHour)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set -HOUR :%d", __FUNCTION__, iHour);
    if(iHour != m_iHour)
    {
        m_iHour = iHour;
        emit sigHourChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

int CDateAndTimeAdaptor::minute()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_iMinute;
}

void CDateAndTimeAdaptor::setMinute(int iMinute)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - MINUTE :%d", __FUNCTION__, iMinute);
    if(iMinute != m_iMinute)
    {
        m_iMinute = iMinute;
        emit sigMinuteChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

int CDateAndTimeAdaptor::sec()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_iSec;
}

void CDateAndTimeAdaptor::setSec(int iSec)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - SECOND :%d", __FUNCTION__, iSec);
    if(iSec != m_iSec)
    {
        m_iSec = iSec;
        emit sigSecChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

int CDateAndTimeAdaptor::day()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_iDay;
}

void CDateAndTimeAdaptor::setDay(int iDay)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - DAY :%d", __FUNCTION__, iDay);
    if(iDay != m_iDay)
    {
        m_iDay = iDay;
        emit sigDayChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

int CDateAndTimeAdaptor::month()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_iMonth;
}

void CDateAndTimeAdaptor::setMonth(int iMonth)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - MONTH :%d", __FUNCTION__, iMonth);
    if(iMonth != m_iMonth)
    {
        m_iMonth = iMonth;
        emit sigMonthChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

int CDateAndTimeAdaptor::year()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_iYear;
}

QString CDateAndTimeAdaptor::amOrPm()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_strAmorPm;
}

bool CDateAndTimeAdaptor::is24HrFormatStatus()
{
    return m_bIs24HrFormatSelected;
}

int CDateAndTimeAdaptor::totalDays()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_iTotalDays;

}

void CDateAndTimeAdaptor::setYear(int iYear)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - YEAR :%d", __FUNCTION__, iYear);
    if(iYear != m_iYear)
    {
        m_iYear = iYear;
        emit sigYearChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

void CDateAndTimeAdaptor::setAmOrPm(const QString &strAmOrPm)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - AM/PM :%s", __FUNCTION__, strAmOrPm.toStdString ().c_str ());
    if(strAmOrPm != m_strAmorPm)
    {
        m_strAmorPm = strAmOrPm;
        emit sigAmOrPmChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

void CDateAndTimeAdaptor::invSetTimeFormat(bool b24HrCheckboxStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - 24Hr Checkbox Status :%d", __FUNCTION__, b24HrCheckboxStatus);
    //Disable the Checkbox when user clicks on it and make it enable on the service response.
    setTimeFormatChangeReqStatus(false);
    CDateAndTimeResourceImpl* pDateAndTimeResource = dynamic_cast<CDateAndTimeResourceImpl*>(ResourceFactory::getDateAndTimeResource());
    if(pDateAndTimeResource)
    {
        pDateAndTimeResource->setTimeFormat(b24HrCheckboxStatus);
    }
    else
    {
        //Do nothing
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Date and time resource is null", __FUNCTION__);
    }
}

void CDateAndTimeAdaptor::setIs24HrFormatStatus(bool b24HrCheckboxStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - 24Hr Checkbox Status :%d", __FUNCTION__, b24HrCheckboxStatus);
    if(b24HrCheckboxStatus != m_bIs24HrFormatSelected)
    {
        m_bIs24HrFormatSelected = b24HrCheckboxStatus;
        updateDateAndTimeUI();
        emit sigIs24HrFormatStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

void CDateAndTimeAdaptor::setTimeFormatChangeReqStatus(bool bTimeFormatReqStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Total days :%d", __FUNCTION__, bTimeFormatReqStatus);
    if(bTimeFormatReqStatus != m_bTimeFormatReqStatus)
    {
        m_bTimeFormatReqStatus = bTimeFormatReqStatus;
        emit sigTimeFormatChangeReqStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }

}

void CDateAndTimeAdaptor::updateTimeFormatChangeReqStatus(int iCallStatus, bool bTimeFormatCbStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Time format Call Status %d, Response Status: %d", __FUNCTION__, iCallStatus, bTimeFormatCbStatus);
    CDateAndTimeEnums::ECallStatus eCallStatus =  static_cast<CDateAndTimeEnums::ECallStatus>(iCallStatus);

     if((CDateAndTimeEnums::SUCCESS != eCallStatus) || (!bTimeFormatCbStatus))
     {
         setTimeFormatChangeReqStatus(true);
     }
     else
     {
         //Do Nothing.
     }

}

void CDateAndTimeAdaptor::setTotalDaysStatus(int iTotalDays)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Total days :%d", __FUNCTION__, iTotalDays);
    if(iTotalDays != m_iTotalDays)
    {
        m_iTotalDays = iTotalDays;
        emit sigTotalDaysStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }

}

void CDateAndTimeAdaptor::updateDateAndTimeResp(bool bDateAndTimeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    if(bDateAndTimeStatus)
    {
        updateDateAndTimeUI();
    }
    else
    {

        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s DateAndTime Setter Callback FAILURE", __FUNCTION__);
    }
}

void CDateAndTimeAdaptor::updateTimeFormatStatus(int iTimeFormat)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);

    CDateAndTimeEnums::ETimeFormat eTimeFormatStatus = static_cast<CDateAndTimeEnums::ETimeFormat>(iTimeFormat);
    //Enable the 24Hr Format checkbox
    setTimeFormatChangeReqStatus(true);
    if(CDateAndTimeEnums::TIME_FORMAT_12_HR == eTimeFormatStatus)
    {
        setIs24HrFormatStatus(false);
    }
    else if(CDateAndTimeEnums::TIME_FORMAT_24_HR == eTimeFormatStatus)
    {
        setIs24HrFormatStatus(true);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS, "%s: Invalid time format received: %d", __FUNCTION__, eTimeFormatStatus);
    }
}

int CDateAndTimeAdaptor::validateTotalDays(int m_iMonth, int m_iYear)
{
    //leap year condition, if month is 2
    if( m_iMonth == 2)
    {
        if((m_iYear%400==0) || (m_iYear%4==0 && m_iYear%100!=0))
            return 29;
        else
            return 28;
    }
    //months which has 31 days
    else if(m_iMonth == 1 || m_iMonth == 3 || m_iMonth == 5 || m_iMonth == 7 || m_iMonth == 8
            ||m_iMonth == 10 || m_iMonth==12)
        return 31;
    else
        return 30;
}

void CDateAndTimeAdaptor::updateDateAndTimeUI()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    CDateAndTimeResourceImpl *pDateAndTimeResourceImpl = dynamic_cast<CDateAndTimeResourceImpl*> (m_pDateAndTimeResource);
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);

    if(pDateAndTimeResourceImpl)
    {
        if(m_bIs24HrFormatSelected)
        {
            setHour(pDateAndTimeResourceImpl->getSystemTimeData().m_iHour);
            setAmOrPm(((pDateAndTimeResourceImpl->getSystemTimeData().m_iHour) >= 12) ? "PM" :"AM");
        }

        else
        {
            int iHourAt12 = pDateAndTimeResourceImpl->getSystemTimeData().m_iHour;
            setHour(((iHourAt12 % 12) == 0) ? 12 : (iHourAt12 % 12));
            setAmOrPm(( iHourAt12 >= 12) ? "PM" :"AM");
        }
        setMinute(pDateAndTimeResourceImpl->getSystemTimeData().m_iMinute);
        setSec(pDateAndTimeResourceImpl->getSystemTimeData().m_iSec);
        setDay(pDateAndTimeResourceImpl->getSystemTimeData().m_iDay);
        setMonth(pDateAndTimeResourceImpl->getSystemTimeData().m_iMonth);
        setYear(pDateAndTimeResourceImpl->getSystemTimeData().m_iYear);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: pDateAndTimeResourceImpl is NULL", __FUNCTION__);
    }
}

void CDateAndTimeAdaptor::setDateAndTime(int iMin, int iHour, int iDay, int iMonth, int iYear, QString amOrPm, int iSec)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    SSystemTimeData objTimeData;
    objTimeData.m_iDay = iDay;
    objTimeData.m_iMonth = iMonth - 1;
    objTimeData.m_iYear = iYear;
    objTimeData.m_iMinute = iMin;
    objTimeData.m_iSec = iSec;
    if(is24HrFormatStatus() == true)
    {
        objTimeData.m_iHour = iHour;
    }
    else{
        objTimeData.m_iHour = (amOrPm == "PM") ? ((iHour % 12) +12) : (iHour % 12);
    }

    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, setDateAndTime From HMI Minute :%d, Hour :%d,Day :%d,Month :%d,Year :%d",
             __FUNCTION__, objTimeData.m_iMinute, objTimeData.m_iHour, objTimeData.m_iDay, objTimeData.m_iMonth, objTimeData.m_iYear);

    if(m_pDateAndTimeResource){
        m_pDateAndTimeResource->setSystemTime(objTimeData);
    }
}




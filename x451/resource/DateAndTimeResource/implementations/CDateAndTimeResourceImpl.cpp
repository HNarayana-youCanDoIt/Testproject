/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDateAndTimeResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CDateAndTimeResourceImpl, Resource Implementation for Date and Time.
 */
#include "CDateAndTimeResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"
#include "CDateAndTimeEventProvider.h"

CDateAndTimeResourceImpl::CDateAndTimeResourceImpl():
    m_pDateAndTimeEventProvider(new CDateAndTimeEventProvider()),
    m_pDateAndTimeProxy(ResourceDeploymentConfig::getConfig().m_TimeManager_Proxy.domain,ResourceDeploymentConfig::getConfig().m_TimeManager_Proxy.instance)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    SUBSCRIBE(m_pDateAndTimeProxy,getProxyStatusEvent(),&CDateAndTimeResourceImpl::timeManagerServiceStatusCb,_1);
}

void CDateAndTimeResourceImpl::subscribeDateAndTimeProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    SUBSCRIBE(m_pDateAndTimeProxy,getSystemTimeWithTz24HrAttribute().getChangedEvent(),&CDateAndTimeResourceImpl::getSystemTimeWithTz24HrAttributeCb,_1);
    /** Time format attribute */
    SUBSCRIBE(m_pDateAndTimeProxy, getTimeFormatAttribute().getChangedEvent(), &CDateAndTimeResourceImpl::onGetTimeFormatAttributeCb, _1);

}

CDateAndTimeResourceImpl::~CDateAndTimeResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    if(m_pDateAndTimeEventProvider){
        delete m_pDateAndTimeEventProvider;
        m_pDateAndTimeEventProvider = nullptr;
    }
}

void CDateAndTimeResourceImpl::timeManagerServiceStatusCb(AvailabilityStatus eStatus)
{
    if(CommonAPI::AvailabilityStatus::AVAILABLE ==  eStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, :AVAILABLE", __FUNCTION__);
        m_bIsDateAndTimeServiceAvailable = true;
        subscribeDateAndTimeProxy();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, :NOT AVAILABLE", __FUNCTION__);
        m_bIsDateAndTimeServiceAvailable = false;
    }
}

void CDateAndTimeResourceImpl::getSystemTimeWithTz24HrAttributeCb(const timeManagerServiceTypes::systemTime &sSystemTime)
{
    m_objSystemTimeData.m_iSec = sSystemTime.getSec();
    m_objSystemTimeData.m_iMinute = sSystemTime.getMinute();
    m_objSystemTimeData.m_iHour = sSystemTime.getHour();
    m_objSystemTimeData.m_iDay = sSystemTime.getDay();
    m_objSystemTimeData.m_iMonth = sSystemTime.getMonth();
    m_objSystemTimeData.m_iWeek = sSystemTime.getWeek();
    m_objSystemTimeData.m_iYear = sSystemTime.getYear();
    m_pDateAndTimeEventProvider->updateDateAndTimeStatusCb(true);

    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, DateAndTime Values From Service Side Minute :%d, Hour :%d,Day :%d,Month :%d,Year :%d",
             __FUNCTION__, m_objSystemTimeData.m_iMinute, m_objSystemTimeData.m_iHour, m_objSystemTimeData.m_iDay, m_objSystemTimeData.m_iMonth, m_objSystemTimeData.m_iYear);
}

void CDateAndTimeResourceImpl::setSystemTimeCb(const CallStatus &callStatus, const bool &callBackStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, callStatus;%d, callBackStatus:%d", __FUNCTION__, static_cast<int>(callStatus), callBackStatus);
    m_pDateAndTimeEventProvider->updateDateAndTimeStatusCb(callBackStatus);
}


CDateAndTimeEventProvider *CDateAndTimeResourceImpl::getDateAndTimeEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_pDateAndTimeEventProvider;
}

void CDateAndTimeResourceImpl::setSystemTime(const SSystemTimeData &sSystemDateTime)
{
    timeManagerServiceTypes::systemTime objNewSystemTimeData;
    objNewSystemTimeData.setDay(sSystemDateTime.m_iDay);
    objNewSystemTimeData.setMonth(sSystemDateTime.m_iMonth);
    objNewSystemTimeData.setYear(sSystemDateTime.m_iYear);
    objNewSystemTimeData.setHour(sSystemDateTime.m_iHour);
    objNewSystemTimeData.setMinute(sSystemDateTime.m_iMinute);
    objNewSystemTimeData.setSec(0);
    objNewSystemTimeData.setPeriod(timeManagerServiceTypes::TM_TimePeriod::TM_PERIOD_NONE); /** Requesting in 24 hr format */

    if(m_bIsDateAndTimeServiceAvailable)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,m_bIsDateAndTimeServiceAvailable :: AVAILABLE ",__FUNCTION__);
        m_pDateAndTimeProxy->updateSourceTime_wellFormedAsync(objNewSystemTimeData,"com.harman.capi.source", std::bind(&CDateAndTimeResourceImpl::setSystemTimeCb,this,_1,_2));
    }

    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,m_bIsDateAndTimeServiceAvailable ::NOT AVAILABLE ",__FUNCTION__);
    }
}

void CDateAndTimeResourceImpl::onGetTimeFormatAttributeCb(timeManagerServiceTypes::TM_Format eTimeFormat)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Response(attribute) - eTimeFormat: %d", __FUNCTION__, eTimeFormat.value_);

    if(m_pDateAndTimeEventProvider)
    {
        m_pDateAndTimeEventProvider->updateTimeFormatStatus(eTimeFormat.value_);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: m_pDateAndTimeEventProvider is NULL", __FUNCTION__);
    }
}

void CDateAndTimeResourceImpl::setTimeFormat(bool bIs24HrTimeFormat)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Request - bIs24HrTimeFormat: %d", __FUNCTION__, bIs24HrTimeFormat);

    timeManagerServiceTypes::TM_Format eTimeFormat = timeManagerServiceTypes::TM_Format::TM_FORMAT_12_HR;
    if(bIs24HrTimeFormat)
    {
        eTimeFormat = timeManagerServiceTypes::TM_Format::TM_FORMAT_24_HR;
    }
    else
    {
        //do nothing
    }

    if(m_bIsDateAndTimeServiceAvailable)
    {
        m_pDateAndTimeProxy->setTimeFormatAsync("com.harman.capi.source", eTimeFormat, std::bind(&CDateAndTimeResourceImpl::setTimeFormatCb, this, _1, _2));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Time manager service is not available", __FUNCTION__);
    }
}

void CDateAndTimeResourceImpl::setTimeFormatCb(const CallStatus& callStatus, const bool& callBackStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: callStatus: %d, callBackStatus: %d", __FUNCTION__, static_cast<int>(callStatus), static_cast<int>(callBackStatus));

    if(m_pDateAndTimeEventProvider)
    {
            m_pDateAndTimeEventProvider->updateTimeFormatCbStatus(static_cast<int>(callStatus), callBackStatus);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: m_pDateAndTimeEventProvider is NULL", __FUNCTION__);
    }
}



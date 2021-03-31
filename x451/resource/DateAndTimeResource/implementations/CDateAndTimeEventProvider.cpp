/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDateAndTimeEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CDateAndTimeEventProvider, Class to send signals to DateAndTime Application layer on DateAndTime Resource events
 */
#include "CDateAndTimeEventProvider.h"
#include "logging.h"

CDateAndTimeEventProvider::CDateAndTimeEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
}

CDateAndTimeEventProvider::~CDateAndTimeEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
}

void CDateAndTimeEventProvider::updateDateAndTimeStatusCb(bool bDateAndTimeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    emit sigUpdateDateAndTimeStatusCb(bDateAndTimeStatus);
}

void CDateAndTimeEventProvider::updateTimeFormatStatus(int iTimeFormat)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Time format: %d", __FUNCTION__, iTimeFormat);
    emit sigUpdateTimeFormatStatus(iTimeFormat);
}

void CDateAndTimeEventProvider::updateTimeFormatCbStatus(int iCallStatus, bool bTimeFormatCbStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Time format: %d", __FUNCTION__, bTimeFormatCbStatus);
    emit sigUpdateTimeFormatCbStatus(iCallStatus, bTimeFormatCbStatus);

}

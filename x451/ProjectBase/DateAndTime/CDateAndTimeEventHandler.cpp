/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CDateAndTimeEventHandler.cpp
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * This class is to handle Date and Time settings.
 */
#include "CDateAndTimeEventHandler.h"
#include "DateAndTimeResource/implementations/CDateAndTimeResourceImpl.h"
#include <ResourceFactory.hpp>
#include "CHMIMain.h"
#include "implementations/CDateAndTimeEventProvider.h"

CDateAndTimeEventHandler::CDateAndTimeEventHandler(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);

    connectSignals();
}

CDateAndTimeEventHandler::~CDateAndTimeEventHandler()
{
    disConnectSignals();
}

void CDateAndTimeEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    CDateAndTimeResourceImpl* pDateAndTimeResource = dynamic_cast<CDateAndTimeResourceImpl*>(ResourceFactory::getDateAndTimeResource());
    if(pDateAndTimeResource)
    {
        CDateAndTimeEventProvider* pDateAndTimeEventProvider = pDateAndTimeResource->getDateAndTimeEventProvider();

        if (pDateAndTimeEventProvider)
        {
            connect(pDateAndTimeEventProvider, SIGNAL(sigUpdateDateAndTimeStatusCb(bool)), this, SLOT(sltUpdateDateAndTimeStatusCb(bool)));
            connect(pDateAndTimeEventProvider, SIGNAL(sigUpdateTimeFormatStatus(int)), this, SLOT(sltUpdateTimeFormatStatus(int)), Qt::QueuedConnection);
            connect(pDateAndTimeEventProvider, SIGNAL(sigUpdateTimeFormatCbStatus(int, bool)), this, SLOT(sltUpdateTimeFormatCbStatus(int, bool)), Qt::QueuedConnection);

        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"pDateAndTimeEventProvider is NULL");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"Resource returns as null from ResourceFactory");
    }
}

void CDateAndTimeEventHandler::disConnectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    CDateAndTimeResourceImpl* pDateAndTimeResource = dynamic_cast<CDateAndTimeResourceImpl*>(ResourceFactory::getDateAndTimeResource());
    if(pDateAndTimeResource)
    {
        CDateAndTimeEventProvider* pDateAndTimeEventProvider = pDateAndTimeResource->getDateAndTimeEventProvider();

        if (pDateAndTimeEventProvider)
        {
            disconnect(pDateAndTimeEventProvider, SIGNAL(sigUpdateDateAndTimeStatusCb(bool)), this, SLOT(sltUpdateDateAndTimeStatusCb(bool)));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"pDateAndTimeEventProvider is NULL");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"Resource returns as null from ResourceFactory");
    }

}

void CDateAndTimeEventHandler::sltUpdateDateAndTimeStatusCb(bool bDateAndTimeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Set Date and Time callback status:: %d" ,__FUNCTION__, bDateAndTimeStatus);
    CDateAndTimeAdaptor::getInstance()->updateDateAndTimeResp(bDateAndTimeStatus);
}

void CDateAndTimeEventHandler::sltUpdateTimeFormatStatus(int iTimeFormat)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Time format: %d", __FUNCTION__, iTimeFormat);

    CDateAndTimeAdaptor::getInstance()->updateTimeFormatStatus(iTimeFormat);
}

void CDateAndTimeEventHandler::sltUpdateTimeFormatCbStatus(int iCallStatus, bool bTimeFormatCbStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Time format Cb Status: %d", __FUNCTION__, bTimeFormatCbStatus);

    if(CDateAndTimeAdaptor::getInstance())
    {
        CDateAndTimeAdaptor::getInstance()->updateTimeFormatChangeReqStatus(iCallStatus, bTimeFormatCbStatus);
    }
    else
    {
        //Do Nothing.
    }
}

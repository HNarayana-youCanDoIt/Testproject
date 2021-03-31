/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CICCastEventHandler.h
* @ingroup      HMIComponent
* @author       Rajat Gupta
* CICCastEventHandler, Class has the slots for all the Signals sent by CICCastEventProvider
*                         which informs IC Cast Adaptor about IC Cast Resource Events
*/

#include "CICCastEventHandler.h"
#include "CHMIMain.h"
#include "CICCastAdaptor.h"
#include "implementations/CICCastResourceImpl.h"
#include "ResourceFactory.hpp"

CICCastEventHandler::CICCastEventHandler(QObject *parent):QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST,__FUNCTION__);
    connectSignals();
}

CICCastEventHandler::~CICCastEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST,__FUNCTION__);
}

void CICCastEventHandler::sltUpdateIcRenderCastAsyncReqCb(int iCallbackStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST,"%s, iCallbackStatus: %d", __FUNCTION__, iCallbackStatus);
    CICCastAdaptor::getInstance()->updateICCastStatus(iCallbackStatus);
}

void CICCastEventHandler::sltUpdateIcProxyAvailability(bool bIcProxyAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST,"%s, bIcProxyAvailability: %d", __FUNCTION__, bIcProxyAvailability);
    CICCastAdaptor::getInstance()->updateOnProxyAvailability(bIcProxyAvailability);
}

void CICCastEventHandler::sltUpdateIcCastValue(bool bIcCastValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST,"%s, bIcCastVlaue: %d", __FUNCTION__, bIcCastValue);
    CICCastAdaptor::getInstance()->setICCastStatus(bIcCastValue);
}


void CICCastEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, __FUNCTION__);
    CICCastResourceImpl* pICCastResource = dynamic_cast<CICCastResourceImpl*>(ResourceFactory::getICCastResource());

    if(pICCastResource)
    {
        CICCastEventProvider* pICCastEventProvider = pICCastResource->getICCastEventProvider();
        if(pICCastEventProvider)
        {
            connect(pICCastEventProvider,SIGNAL(sigUpdateIcRenderCastAsyncReqCb(int)),this,SLOT(sltUpdateIcRenderCastAsyncReqCb(int)),Qt::QueuedConnection);
            connect(pICCastEventProvider,SIGNAL(sigUpdateIcProxyAvailability(bool)),this,SLOT(sltUpdateIcProxyAvailability(bool)), Qt::QueuedConnection);
            connect(pICCastEventProvider,SIGNAL(sigUpdateIcCastValue(bool)),this,SLOT(sltUpdateIcCastValue(bool)),Qt::QueuedConnection);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ICCAST,"%s, pICCastEventProvider is null", __FUNCTION__);
        }

    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ICCAST, "%s | ICCast Resource is returned NULL from Resource Factory",__FUNCTION__);
    }
}

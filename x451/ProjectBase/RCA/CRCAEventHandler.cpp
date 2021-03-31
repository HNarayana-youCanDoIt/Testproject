/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CRCAEventHandler.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* @class        CRCAEventHandler: Class acts as the event handler for all the signals/events sent by CRCAEventProvider
* which informs RCA Adaptor about RCA resource events
*/

#include "CRCAEventHandler.h"
#include "CRCAAdaptor.h"
#include "HMIIncludes.h"
#include "RCAResource/implementations/CRCAResourceImpl.h"
#include <ResourceFactory.hpp>
#include "CRCAEnums.h"
#include "CDisplayManagerAdaptor.h"

using namespace v0::com::harman::dcif;

CRCAEventHandler::CRCAEventHandler(QObject *pParent) : QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    connectSignals();
}

CRCAEventHandler::~CRCAEventHandler()
{
}

void CRCAEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    CRCAResourceImpl* pRCAResource = dynamic_cast<CRCAResourceImpl*>(ResourceFactory::getRCAResource());
    if (pRCAResource)
    {
        // make the signal and slot connection
        CRCAEventProvider* pRCAEventProvider = pRCAResource->getRCAEventProvider();
        if(pRCAEventProvider)
        {
            connect( pRCAEventProvider, &CRCAEventProvider::sigRCAActionUpdate, this, &CRCAEventHandler::sltRCAActionUpdate, Qt::QueuedConnection);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"Resource returned as null from ResourceFactory");
    }
}

void CRCAEventHandler::sltRCAActionUpdate(int iRCAActionInitiated, uint uiIntInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);

    /* If display is off and user initiates RCA action, Display must be wakeup */
    CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);

    if(CRCAAdaptor::getInstance())
    {
        CRCAAdaptor::getInstance()->setRCAActionsInitiated(static_cast<CRCAEnums::ERCAActionInitiated>(iRCAActionInitiated), uiIntInfo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"HVAC adpator is NULL");
    }
}

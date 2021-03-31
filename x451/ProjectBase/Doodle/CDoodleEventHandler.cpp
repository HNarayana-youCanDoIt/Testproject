/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDoodleEventHandler.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleEventHandler, a Resource handler for Doodle module,
 * CDoodleEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#include <CHMIMain.h>
#include <ResourceFactory.hpp>

#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"
#include "CDoodleSM.h"
#include "CDoodleEventHandler.h"

#include "implementations/CDoodleResourceImpl.h"

///////////////////////////////////////////////////////////////////////////////
// DataEventHandler related functions
///////////////////////////////////////////////////////////////////////////////
CDoodleEventHandler::CDoodleEventHandler(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    connectSignals();
}
//____________________________________________________________________________
CDoodleEventHandler::~CDoodleEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    disconnectSignals();
}
//____________________________________________________________________________
void CDoodleEventHandler::slotProxyStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    if (CDoodleApplication::getDoodleAdaptor())
    {
        CDoodleApplication::getDoodleAdaptor()->updateDoodleProxyPresence();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s: DoodleAdaptor not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDoodleEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    CDoodleResourceImpl* pResource = dynamic_cast<CDoodleResourceImpl*>(ResourceFactory::getDoodleResource());
    if(pResource)
    {
        CDoodleEventProvider * pEventProvider = pResource->getEventProvider();
        if(pEventProvider)
        {
            connect(pEventProvider, SIGNAL(sigProxyStatusChanged()),this, SLOT(slotProxyStatusChanged()), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s: CDoodleEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s: Doodle Resource is returned NULL from Resource Factory", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CDoodleEventHandler::disconnectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    CDoodleResourceImpl* pResource = dynamic_cast<CDoodleResourceImpl*>(ResourceFactory::getDoodleResource());
    if(pResource)
    {
        CDoodleEventProvider * pEventProvider = pResource->getEventProvider();
        if(pEventProvider)
        {
            disconnect(pEventProvider, SIGNAL(sigProxyStatusChanged()),this, SLOT(slotProxyStatusChanged()));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s: CDoodleEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s: Doodle Resource is returned NULL from Resource Factory", __FUNCTION__);
    }
}

/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CMediaOffEventHandler.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CMediaOffEventHandler, a Resource handler for Media Off module,
 * CMediaOffEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#include <CHMIMain.h>
#include <ResourceFactory.hpp>

#include "CMediaOffApplication.h"
#include "CMediaOffAdaptor.h"
#include "CMediaOffSM.h"
#include "CMediaOffEventHandler.h"

//////////////////////////////////////////////////////////////////
// Event Handler related functions
//////////////////////////////////////////////////////////////////
CMediaOffEventHandler::CMediaOffEventHandler(QObject *parent): QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
    connectSignals();
}
//________________________________________________________________________________________________
CMediaOffEventHandler::~CMediaOffEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
}
//________________________________________________________________________________________________
void CMediaOffEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
}
//________________________________________________________________________________________________

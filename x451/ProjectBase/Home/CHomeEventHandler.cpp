/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHomeEventHandler.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CHomeEventHandler, a Resource handler for Home module,
 * CHomeEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#include <CHMIMain.h>
#include <ResourceFactory.hpp>

#include "CHomeApplication.h"
#include "CHomeAdaptor.h"
#include "CHomeSM.h"
#include "CHomeEventHandler.h"

//////////////////////////////////////////////////////////////////
// DataEventHandler related functions
//////////////////////////////////////////////////////////////////
CHomeEventHandler::CHomeEventHandler(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    connectSignals();
}

CHomeEventHandler::~CHomeEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
}

void CHomeEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
}
/*
void CHomeEventHandler::sltHardKeyEvent(int eventType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, eventType : %d ", __FUNCTION__, eventType);
}*/
/*
void CHomeEventHandler::sltUpdateDataType(int type)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, type : %d ",  __FUNCTION__, type);
}*/

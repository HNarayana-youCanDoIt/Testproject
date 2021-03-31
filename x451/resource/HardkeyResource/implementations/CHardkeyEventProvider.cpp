/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardkeyEventProvider.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CHardkeyEventProvider, Class to send signals to HardkeyHandler on KeyPress Resource events
*/

#include "CHardkeyEventProvider.h"
#include "logging.h"

CHardkeyEventProvider::CHardkeyEventProvider(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
}

CHardkeyEventProvider::~CHardkeyEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
}

void CHardkeyEventProvider::onKeyEvent(EHardKeys eKey, EHardKeyState eState )
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s : key:- %d : state: %d",__FUNCTION__, eKey, eState);
    emit sigHardKeyEvent(eKey,eState);
}

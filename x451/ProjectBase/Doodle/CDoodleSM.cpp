/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDoodleSM.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleSM, a State machine handler for Doodle module,
 * CDoodleSM inherits SCI_Doodle_OCB to handle state-machine events.
 */

#include "HMIIncludes.h"

#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"
#include "CDoodleSM.h"
#include "CDoodleEventHandler.h"

///////////////////////////////////////////////////////////////////////////////
// CDoodleSM related functions
///////////////////////////////////////////////////////////////////////////////
CDoodleSM::CDoodleSM(CDoodleApplication& DoodleApp):
    mDoodleApp(DoodleApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_DoodleSetup_OCB(this);
}
//____________________________________________________________________________
CDoodleSM::~CDoodleSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////
// StateMachine related functions
///////////////////////////////////////////////////////////////////////////////

void CDoodleSM::enterDoodleSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    if (CDoodleApplication::getDoodleAdaptor())
    {
        CDoodleApplication::getDoodleAdaptor()->initDoodleSetupList();
    }
}
//____________________________________________________________________________
void CDoodleSM::exitDoodleSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    if (CDoodleApplication::getDoodleAdaptor())
    {
        CDoodleApplication::getDoodleAdaptor()->resetDoodleSetupList();
    }
}
//____________________________________________________________________________
void CDoodleSM::enterDoodleSetupScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    mDoodleApp.loadScreen("qrc:/QML/Doodle/ScnDoodleSetupScreen.qml");
}
//____________________________________________________________________________
void CDoodleSM::exitDoodleSetupScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
}
//____________________________________________________________________________

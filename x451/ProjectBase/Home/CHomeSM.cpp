/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHomeSM.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CHomeSM, a State machine handler for Home module,
 * CHomeSM inherits SCI_Home_OCB to handle statemachine events.
 */

#include "HMIIncludes.h"

#include "CHomeApplication.h"
#include "CHomeAdaptor.h"
#include "CHomeSM.h"
#include "CHomeEventHandler.h"
#include "CAudioAdaptor.h"
#include "ParkAssist/CParkAssistAdaptor.h"

#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"

CHomeSM::CHomeSM(CHomeApplication& homeApp):
    mHomeApp(homeApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_Home_OCB(this);
}

CHomeSM::~CHomeSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
}

//////////////////////////////////////////////////////////////////
// StateMachine related functions
//////////////////////////////////////////////////////////////////
void CHomeSM::enterHome()//state machine callback for entering home module
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);

    CDrawersAdaptor::getInstance()->setAllowStatusBarOnScreen(true);
}
void CHomeSM::exitHome()//state machine callback for exiting home module
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    CFramework::getFramework().clearScreenHistoryStack();
}
//____________________________________________________________________________
void CHomeSM::enterHomeScreenMain()//state machine callback for entering home main screen
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);

    CHomeAdaptor::getInstance().setOnHomeScreen(true);
    mHomeApp.loadScreen("qrc:/QML/Home/ScnHomeMain.qml");

    if (CDoodleApplication::getDoodleAdaptor())
    {
        CDoodleApplication::getDoodleAdaptor()->setAllowDoodleOnScreen(true);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HOME, "%s CDoodleAdaptor object not available", __FUNCTION__);
    }
}
void CHomeSM::exitHomeScreenMain()//state machine callback for exiting home main screen
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);

    CHomeAdaptor::getInstance().setOnHomeScreen(false);

    if (CDoodleApplication::getDoodleAdaptor())
    {
        CDoodleApplication::getDoodleAdaptor()->setAllowDoodleOnScreen(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HOME, "%s CDoodleAdaptor object not available", __FUNCTION__);
    }
}
//____________________________________________________________________________
void CHomeSM::enterHomeScreenUpdateShortcuts()//state machine callback for entering home update screen
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    mHomeApp.loadScreen("qrc:/QML/Home/ScnHomeUpdateShortcuts.qml");
    CHomeAdaptor::getInstance().initUnusedShortcutsList();
}
void CHomeSM::exitHomeScreenUpdateShortcuts()//state machine callback for exiting home update screen
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
}
//____________________________________________________________________________
void CHomeSM::enterConfigureFavHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    mHomeApp.loadScreen("qrc:/QML/Home/ScnConfigureFavKey.qml");
}

void CHomeSM::exitConfigureFavHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
}
//____________________________________________________________________________

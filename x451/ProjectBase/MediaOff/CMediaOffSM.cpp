/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CMediaOffSM.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CMediaOffSM, a State machine handler for Media Off module,
 * CMediaOffSM inherits SCI_MediaOff_OCB to handle statemachine events.
 */

#include "HMIIncludes.h"

#include "CMediaOffApplication.h"
#include "CMediaOffAdaptor.h"
#include "CMediaOffSM.h"
#include "CMediaOffEventHandler.h"
#include "ParkAssist/CParkAssistAdaptor.h"
#include "Persistency/CPersistencyAdaptor.h"
#include "VariantControl/CVariantControlAdaptor.h"

#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"

//________________________________________________________________________________________________
CMediaOffSM::CMediaOffSM(CMediaOffApplication& mediaOffApp):
    mMediaOffApp(mediaOffApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_MediaOff_OCB(this);
}
CMediaOffSM::~CMediaOffSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
//////////////////////////////////////////////////////////////////
// StateMachine related functions
//////////////////////////////////////////////////////////////////
void CMediaOffSM::enterMediaOff()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);

    CDrawersAdaptor::getInstance()->setAllowStatusBarOnScreen(true);

    // Inform RVCApp hmi is up and running
    CParkAssistAdaptor::getInstance()->setHmiNotificationAttribute(true);
    CMediaOffAdaptor::getInstance().setMediaOffScreenStatus(true);

}
void CMediaOffSM::exitMediaOff()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);
    CFramework::getFramework().clearScreenHistoryStack();
    CMediaOffAdaptor::getInstance().setMediaOffScreenStatus(false);
}

void CMediaOffSM::enterMediaOffScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);
    CMediaOffAdaptor::getInstance().setSelectedClockId(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SELECTED_CLOCK_ID));
    mMediaOffApp.loadScreen("qrc:/QML/MediaOff/X445/ScnMediaOff.qml");

    if (CDoodleApplication::getDoodleAdaptor())
    {
        CDoodleApplication::getDoodleAdaptor()->setAllowDoodleOnScreen(true);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s CDoodleAdaptor object not available", __FUNCTION__);
    }
}

void CMediaOffSM::exitMediaOffScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_SELECTED_CLOCK_ID, CMediaOffAdaptor::getInstance().selectedClockId());
    mMediaOffApp.loadScreen("qrc:/QML/Setup/GeneralSetupSetDateAndTime.qml");

    if (CDoodleApplication::getDoodleAdaptor())
    {
        CDoodleApplication::getDoodleAdaptor()->setAllowDoodleOnScreen(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s CDoodleAdaptor object not available", __FUNCTION__);
    }
}

void CMediaOffSM::enterMediaOffSetDateScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);
    mMediaOffApp.loadScreen("qrc:/QML/Setup/GeneralSetupSetDateAndTime.qml");
}

void CMediaOffSM::exitMediaOffSetDateScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________

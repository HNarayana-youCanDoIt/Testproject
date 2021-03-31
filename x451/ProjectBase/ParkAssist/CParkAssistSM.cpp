/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistSM.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CParkAssistSM.cpp, park assist module state machine source file, contains all the state machine callbacks of the module park assist.
 */

#include "CParkAssistSM.h"
#include "CParkAssistAdaptor.h"
#include "CAudioAdaptor.h"
#include "CDisplayManagerAdaptor.h"
#include "CMediaAdaptor.h"
#include "CLayerManagerAdaptor.h"
#include "CAndroidAutoAdaptor.h"
#include "CAppleCarPlayAdaptor.h"
#include "CPhoneAdaptor.h"
#include "CVRAdaptor.h"

CParkAssistSM::CParkAssistSM(CParkAssistApplication& parkAssistApp):
    mParkAssistApp(parkAssistApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_ParkAssit_OCB(this);
}

CParkAssistSM::~CParkAssistSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);
}

void CParkAssistSM::enterParkAssist()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);

    //Deactivate Native VR
    CVRAdaptor::getInstance()->invDeactivateVRSession();

    //Deactivate Phone Bt VR
    CPhoneAdaptor::getInstance()->invReqPhoneBtVrDeactivation();

    // Set audio state ON
    CAudioAdaptor::getInstance()->setAudioOff(false);

    /** Making the display to ON, if it is in OFF state while entering into PDC-RVC screen */
    CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);

    mParkAssistApp.displayScreenPdcRvc();

    if ((true == CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus())
            || (true == CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus()))
    {
        //Getting the HMI to the topmost layer, when projections are connected
        CLayerManagerAdaptor::getInstance()->showScene(CLayerManagerEnums::SURFACE_HMI);
    }

    //Setting rvcstate to media for hiding video surface if video is playing
    CMediaAdaptor::getInstance().updateRvcState(true);

}

void CParkAssistSM::exitParkAssist()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);
    CDrawersAdaptor::getInstance()->setActiveNotification(CDrawersEnums::EN_NOTIFICATION_TYPE_NONE);
    CParkAssistAdaptor::getInstance()->updateRvcState();
    CFramework::getFramework().clearScreenHistoryStack();
}

void CParkAssistSM::enterParkAssistMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);
}

void CParkAssistSM::exitParkAssistMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);
}

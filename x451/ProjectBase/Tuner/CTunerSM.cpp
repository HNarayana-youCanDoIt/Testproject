/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CTunerSM.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * CTunerSM,   The class is child of state machine tuner module's class and will override all the parent class methods.
 * These method will get invoked when particular state gets activated.
**/

#include "CTunerSM.h"
#include "CTunerAdaptor.h"
#include "CTunerEnums.h"

CTunerSM::CTunerSM(CTunerApplication& tunerApp):mTunerApp(tunerApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}
CTunerSM::~CTunerSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}



void CTunerSM::enterTuner()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}

void CTunerSM::exitTuner()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CFramework::getFramework().clearScreenHistoryStack();
}

void CTunerSM::enterTunerMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);

    CTunerAdaptor::getInstance()->selectPresetListPageIndex();
    if(!CTunerAdaptor::getInstance()->isTunerAntennaConnected())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s, Tuner antenna not connected", __FUNCTION__);
    }
    mTunerApp.loadScreen("qrc:/QML/Tuner/TunerScreen.qml");
}

void CTunerSM::exitTunerMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->handleStopSeek();
}

void CTunerSM::enterTunerDefault()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setTunerState("TunerMain");
}

void CTunerSM::exitTunerDefault()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}

void CTunerSM::enterTunerOption()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    mTunerApp.loadScreen("qrc:/QML/Tuner/TunerOptionScreen.qml");
}

void CTunerSM::exitTunerOption()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}

void CTunerSM::enterTunerScan()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setTunerState("Scan");
}

void CTunerSM::exitTunerScan()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}

void CTunerSM::enterTunerAutoSeekUp()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setTunerState("TunerMain");
}

void CTunerSM::exitTunerAutoSeekUp()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->handleStopSeek();
}

void CTunerSM::enterTunerAutoSeekDown()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setTunerState("TunerMain");
}

void CTunerSM::exitTunerAutoSeekDown()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->handleStopSeek();
}

void CTunerSM::enterTunerAutoStore()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CTunerAdaptor::getInstance()->setTunerState("Autostore");
}

void CTunerSM::exitTunerAutoStore()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}

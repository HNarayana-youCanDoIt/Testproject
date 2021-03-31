/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlayApplication.cpp
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition of all functions of CAppleCarPlaySM class of
* AppleCarPlay.
*/

#include "CAppleCarPlaySM.h"
#include "CAppleCarPlayAdaptor.h"
#include "CAppleCarPlayApplication.h"
#include "CVRAdaptor.h"

CAppleCarPlaySM::CAppleCarPlaySM(const CAppleCarPlayApplication *pAppleCarPlayApp):
    m_pAppleCarPlayApp(pAppleCarPlayApp)
{
    CHMIMain::getSM()->setSCI_CarPlay_OCB(this);
}

CAppleCarPlaySM::~CAppleCarPlaySM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
}

void CAppleCarPlaySM::enterCarPlay()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    if (m_pAppleCarPlayApp)
    {
        CDrawersAdaptor::getInstance()->setShowMuteStatus(true);
        // Default HMI is set to x445
        (const_cast<CAppleCarPlayApplication *> (m_pAppleCarPlayApp))->loadScreen("qrc:/QML/AppleCarPlay/X445/AppleCarPlayNativeControl.qml");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAppleCarPlayApp is NULL",
                 __FUNCTION__);
    }
}

void CAppleCarPlaySM::exitCarPlay()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    emit CDrawersAdaptor::getInstance()->sigChangeMuteStatusOnScreenExit();

    if(CVRAdaptor::getInstance())
    {
        /* If VR session gets active during active Projection, then timer is needed to remove the
         * VR Overlay to avoid the flicker in VR Overlay -> Projection transition after VR session ends
         */
        if(CVRAdaptor::getInstance()->invGetVRSessionStatus())
        {
            CVRAdaptor::getInstance()->setHideVROverlayTimerStatus(true);
        }
        else
        {
            CVRAdaptor::getInstance()->setHideVROverlayTimerStatus(false);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: VR adaptor is NULL",__FUNCTION__);
    }

    CFramework::getFramework().clearScreenHistoryStack();
}

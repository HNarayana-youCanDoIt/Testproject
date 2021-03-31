/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoApplication.cpp
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition of all functions of CAndroidAutoSM class of
* AndroidAuto.
*/

#include "CAndroidAutoSM.h"
#include "CAndroidAutoAdaptor.h"
#include "CAndroidAutoApplication.h"
#include "CParkAssistAdaptor.h"
#include "CVRAdaptor.h"

CAndroidAutoSM::CAndroidAutoSM(const CAndroidAutoApplication *pAndroidAutoApp):
    m_pAndroidAutoApp(pAndroidAutoApp)
{
    CHMIMain::getSM()->setSCI_AndroidAuto_OCB(this);
}

CAndroidAutoSM::~CAndroidAutoSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
}

void CAndroidAutoSM::enterAndroidAuto()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_pAndroidAutoApp && CAndroidAutoAdaptor::getInstance())
    {
        CDrawersAdaptor::getInstance()->setShowMuteStatus(true);
        (const_cast<CAndroidAutoApplication *> (m_pAndroidAutoApp))->loadScreen(
                    "qrc:/QML/Common/ScnTransparent.qml");

        CAndroidAutoAdaptor::getInstance()->setAATransientState(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAndroidAutoApp is NULL",
                 __FUNCTION__);
    }
}

void CAndroidAutoSM::exitAndroidAuto()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    emit CDrawersAdaptor::getInstance()->sigChangeMuteStatusOnScreenExit();

    if(CParkAssistAdaptor::getInstance())
    {
        if(CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus())
        {
            CAndroidAutoAdaptor::getInstance()->setAATransientState(true);
        }
        else
        {
            CAndroidAutoAdaptor::getInstance()->setAATransientState(false);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: park assist adaptor is NULL",
                 __FUNCTION__);
    }

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

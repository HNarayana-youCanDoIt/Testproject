/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoEventProvider.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CAndroidAutoEventProvider, Class to send signals to AndroidAuto Application
* layer on AndroidAuto Resource events
*/

#include "CAndroidAutoEventProvider.h"
#include "logging.h"

CAndroidAutoEventProvider::CAndroidAutoEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,__FUNCTION__);
}

CAndroidAutoEventProvider::~CAndroidAutoEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,__FUNCTION__);
}

void CAndroidAutoEventProvider::updateAAFirstRunConnectionStatus()
{
   LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,__FUNCTION__);
   emit sigShowFirstRunPopup();
}

void CAndroidAutoEventProvider::updateAAMediaPlayState(ushort usAAMediaPlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: usAAMediaPlayState: %u",
             __FUNCTION__, usAAMediaPlayState);

    emit sigUpdateAAMediaPlayState(usAAMediaPlayState);
}

void CAndroidAutoEventProvider::updateAAProjectionStatus(bool bAAProjectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bAAProjectionState: %d", __FUNCTION__, bAAProjectionState);

    emit sigUpdateAAProjectionStatus(bAAProjectionState);
}

void CAndroidAutoEventProvider::updateOKGoogleStatus(bool bOKGoogleStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bOKGoogleStatus: %d", __FUNCTION__, bOKGoogleStatus);

    emit sigUpdateOKGoogleStatus(bOKGoogleStatus);
}

void CAndroidAutoEventProvider::updateAANaviStatus(bool bAANaviStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bAANaviStatus: %d", __FUNCTION__, bAANaviStatus);

    emit sigUpdateAANaviStatus(bAANaviStatus);
}

void CAndroidAutoEventProvider::updateAAMediaMetaData()
{
   LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

   emit sigUpdateAAMediaMetaData();
}

void CAndroidAutoEventProvider::updateAASessionDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    emit sigUpdateAASessionDetails();
}

void CAndroidAutoEventProvider::updateAANaviTurnEventDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    emit sigUpdateAANaviTurnEventDetails();
}

void CAndroidAutoEventProvider::updateAANaviTurnDistanceDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    emit sigUpdateAANaviDistanceDetails();
}

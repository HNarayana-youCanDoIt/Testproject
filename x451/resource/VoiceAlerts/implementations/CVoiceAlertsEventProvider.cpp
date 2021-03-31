/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CVoiceAlertsEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Guru Alingal
 * CVehicleSettingsEventProvider, Class to send signals to setup Application layer on vehicle Resource events
 */

#include "logging.h"
#include "CVoiceAlertsEventProvider.h"

CVoiceAlertsEventProvider::CVoiceAlertsEventProvider(QObject *pParent) :
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s",__FUNCTION__);
}

CVoiceAlertsEventProvider::~CVoiceAlertsEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s",__FUNCTION__);
}

void CVoiceAlertsEventProvider::updateVasStatus(bool bStatus)
{
    emit sigVASStatus(bStatus);
}

void CVoiceAlertsEventProvider::updateHuAlertStatus(int iAlertStaus)
{
    emit sigHuAlertStatus(iAlertStaus);
}

void CVoiceAlertsEventProvider::updateHuInfoFeaturePresence(int iPresence)
{
    emit sigHuInfoFeaturePresence(iPresence);
}

void CVoiceAlertsEventProvider::updateHuAlertHMISelection(int iHMISelection)
{
    emit sigHuAlertHMISelection(iHMISelection);
}

void CVoiceAlertsEventProvider::updateCurDriveMode(int iDriveMode)
{
    emit sigCurDriveMode(iDriveMode);
}

void CVoiceAlertsEventProvider::updateHuAlertState(int iAlert)
{
    emit sigHuAlertState(iAlert);
}

void CVoiceAlertsEventProvider::updateHuAlertMceState(int iMceAlert)
{
    emit sigHuAlertMceState(iMceAlert);
}


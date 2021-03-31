/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CParkAssistEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CParkAssistEventProvider, Class to send signals to setup Application layer on park assist Resource events
 */

#include "logging.h"
#include "CParkAssistEventProvider.h"

CParkAssistEventProvider::CParkAssistEventProvider(QObject *pParent) :
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,__FUNCTION__);
}

CParkAssistEventProvider::~CParkAssistEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,__FUNCTION__);
}

void CParkAssistEventProvider::updateParkAssistDelayTimer(int iPdcDelayTimer)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, PDC Delay Timer : %d", __FUNCTION__, iPdcDelayTimer);
    emit sigUpdateParkAssistDelayTimer(iPdcDelayTimer);
}

void CParkAssistEventProvider::updateParkAssistRearTone(int iPdcRearTone)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, PDC Tone : %d", __FUNCTION__, iPdcRearTone);
    emit sigUpdateParkAssistRearTone(iPdcRearTone);
}

void CParkAssistEventProvider::updateScreenPDC_RVCStatus(bool bReverseGearStatus, bool bActivationStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Reverse gear status: %d, Activation status from HMI: %d",
             __FUNCTION__, bReverseGearStatus, bActivationStatus);

    emit sigScreenPDC_RVCStatus(bReverseGearStatus, bActivationStatus);
}

void CParkAssistEventProvider::updateParkAssistVariantType(int iParkAssistVariantType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssist Variant Type: %d", __FUNCTION__, iParkAssistVariantType);

    emit sigParkAssistVariantType(iParkAssistVariantType);
}

void CParkAssistEventProvider::updatePdcScreenSensorState(int iPdcSensorState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC Sensor state: %d", __FUNCTION__, iPdcSensorState);

    emit sigPdcScreenSensorState(iPdcSensorState);
}

void CParkAssistEventProvider::updateRvcScreenSensorState(int iRvcSensorState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC Sensor state: %d", __FUNCTION__, iRvcSensorState);

    emit sigRvcScreenSensorState(iRvcSensorState);
}

void CParkAssistEventProvider::updatePdcFault(int iPdcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC Fault: %d", __FUNCTION__, iPdcFault);

    emit sigPdcFault(iPdcFault);
}

void CParkAssistEventProvider::updateRvcFault(int iRvcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC Fault: %d", __FUNCTION__, iRvcFault);

    emit sigRvcFault(iRvcFault);
}

void CParkAssistEventProvider::updatePdcRvcFault(int iPdcRvcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC+RVC Fault: %d", __FUNCTION__, iPdcRvcFault);

    emit sigPdcRvcFault(iPdcRvcFault);
}

void CParkAssistEventProvider::updateRvcOverlayType(int iRvcOverlayType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC Overlay Type: %d", __FUNCTION__, iRvcOverlayType);

    emit sigRvcOverlayType(iRvcOverlayType);
}

void CParkAssistEventProvider::updateRvcOverlayDirection(int iOverlayDirection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC Overlay Direction: %d", __FUNCTION__, iOverlayDirection);

    emit sigRvcOverlayDirection(iOverlayDirection);
}

void CParkAssistEventProvider::updateRvcOverlayAngle(double dOverlayAngle)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC Overlay Angle: %f", __FUNCTION__, dOverlayAngle);

    emit sigRvcOverlayAngle(dOverlayAngle);
}

void CParkAssistEventProvider::updateParkAssistStatusToHMI()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, __FUNCTION__);

    emit sigParkAssistStatusToHMI();
}

void CParkAssistEventProvider::updatePdcPresence(bool bPdcPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC Presence : %d", __FUNCTION__, bPdcPresence);

    emit sigPdcPresence(bPdcPresence);
}

void CParkAssistEventProvider::updatePdcSettingsStatus(bool bErrorStatus, int iErrorId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Error status : %d, Error Id : %d ", __FUNCTION__, bErrorStatus, iErrorId);

    emit sigPdcSettingsStatus(bErrorStatus, iErrorId);
}

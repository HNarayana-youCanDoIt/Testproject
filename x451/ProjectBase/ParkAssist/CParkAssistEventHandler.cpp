/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistEventHandler.cpp
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * This class is to handle Park assist events.
 */

#include "CParkAssistEventHandler.h"
#include "ParkAssistResource/implementations/CParkAssistResourceImpl.h"
#include <ResourceFactory.hpp>
#include "CHMIMain.h"
#include "CParkAssistAdaptor.h"

CParkAssistEventHandler::CParkAssistEventHandler(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST," %s, CParkAssistEventHandler Constructor ", __FUNCTION__);
    connectSignals();
}

CParkAssistEventHandler::~CParkAssistEventHandler()
{

}

void CParkAssistEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,__FUNCTION__);
    CParkAssistResourceImpl* pParkAssistResource = static_cast<CParkAssistResourceImpl*>(ResourceFactory::getParkAssistResource());
    if(pParkAssistResource)
    {
        CParkAssistEventProvider* pParkAssistEventProvider = pParkAssistResource->getParkAssistEventProvider();
        connect(pParkAssistEventProvider, SIGNAL(sigUpdateParkAssistDelayTimer(int)), this, SLOT(sltUpdateParkAssistDelayTimer(int)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigUpdateParkAssistRearTone(int)), this, SLOT(sltUpdateParkAssistRearTone(int)), Qt::QueuedConnection);

        connect(pParkAssistEventProvider, SIGNAL(sigParkAssistStatusToHMI()), this, SLOT(sltParkAssistStatusToHMI()), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigScreenPDC_RVCStatus(bool, bool)), this, SLOT(sltUpdateScreenPDC_RVCStatus(bool, bool)));
        connect(pParkAssistEventProvider, SIGNAL(sigParkAssistVariantType(int)), this, SLOT(sltParkAssistVariantType(int)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigPdcScreenSensorState(int)), this, SLOT(sltPdcScreenSensorState(int)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigRvcScreenSensorState(int)), this, SLOT(sltRvcScreenSensorState(int)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigPdcFault(int)), this, SLOT(sltPdcFault(int)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigRvcFault(int)), this, SLOT(sltRvcFault(int)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigPdcRvcFault(int)), this, SLOT(sltPdcRvcFault(int)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigRvcOverlayType(int)), this, SLOT(sltRvcOverlayType(int)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigRvcOverlayDirection(int)), this, SLOT(sltRvcOverlayDirection(int)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigRvcOverlayAngle(double)), this, SLOT(sltRvcOverlayAngle(double)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigPdcPresence(bool)), this, SLOT(sltPdcPresence(bool)), Qt::QueuedConnection);
        connect(pParkAssistEventProvider, SIGNAL(sigPdcSettingsStatus(bool, int)), this, SLOT(sltPdcSettingsStatus(bool, int)), Qt::QueuedConnection);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist Resource is returned NULL from Resource Factory", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltUpdateParkAssistDelayTimer(int iParkAssistDelayTimer)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, pdc delay timer : %d ",__FUNCTION__, iParkAssistDelayTimer);
    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setParkAssistDelayTimer(iParkAssistDelayTimer);
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltUpdateParkAssistRearTone(int iParkAssistRearTone)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s, park assist tone : %d ",__FUNCTION__, iParkAssistRearTone);
    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setParkAssistRearTone(iParkAssistRearTone);
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltUpdateScreenPDC_RVCStatus(bool bReverseGearStatus, bool bActivationStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: Reverse gear status: %d, Activation status from HMI: %d",
                 __FUNCTION__, bReverseGearStatus, bActivationStatus);

    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setReverseGearStatus(bReverseGearStatus, bActivationStatus);
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltParkAssistVariantType(int iParkAssistVariantType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: ParkAssist Variant Type: %d", __FUNCTION__, iParkAssistVariantType);

    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setParkAssistVariant(static_cast<CParkAssistEnum::EParkAssistVariantType>(iParkAssistVariantType));
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltPdcScreenSensorState(int iPdcSensorState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC Sensor state: %d", __FUNCTION__, iPdcSensorState);

    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setPdcScreenSensorState(iPdcSensorState);
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltRvcScreenSensorState(int iRvcSensorState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC Sensor state: %d", __FUNCTION__, iRvcSensorState);

    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setRvcScreenSensorState(iRvcSensorState);
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltPdcFault(int iPdcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC Fault: %d", __FUNCTION__, iPdcFault);

    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setPdcFault(static_cast<CParkAssistEnum::EPdcFaults>(iPdcFault));
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltRvcFault(int iRvcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC Fault: %d", __FUNCTION__, iRvcFault);
    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setRvcFault(static_cast<CParkAssistEnum::ERvcFaults>(iRvcFault));
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltPdcRvcFault(int iPdcRvcFault)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC+RVC Fault: %d", __FUNCTION__, iPdcRvcFault);
    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setPdcRvcFault(static_cast<CParkAssistEnum::EPdcRvcFaults>(iPdcRvcFault));
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltRvcOverlayType(int iRvcOverlayType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC Overlay Type: %d", __FUNCTION__, iRvcOverlayType);
    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setRvcOverlayType(static_cast<CParkAssistEnum::ERvcOverlays>(iRvcOverlayType));
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltRvcOverlayDirection(int iOverlayDirection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC Overlay Direction: %d", __FUNCTION__, iOverlayDirection);
    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setRvcOverlayDirection(static_cast<CParkAssistEnum::ERvcOverlayDirection>(iOverlayDirection));
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltRvcOverlayAngle(double dOverlayAngle)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: RVC Overlay Angle: %f", __FUNCTION__, dOverlayAngle);
    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setRvcOverlayAngle(dOverlayAngle);
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltParkAssistStatusToHMI()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, __FUNCTION__);
    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setParkAssistProxyStatus(true);
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltPdcPresence(bool bPdcPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC Presence: %d", __FUNCTION__, bPdcPresence);

    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setPdcPresence(bPdcPresence);
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

void CParkAssistEventHandler::sltPdcSettingsStatus(bool bErrorStatus, int iErrorId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: PDC Settings errot status : %d, Error Id : %d ", __FUNCTION__, bErrorStatus, iErrorId);

    if(CParkAssistAdaptor::getInstance())
    {
        CParkAssistAdaptor::getInstance()->setPdcSettingsStatus(bErrorStatus, iErrorId);
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PARKASSIST, "%s, parkassist adaptor is not available", __FUNCTION__);
    }
}

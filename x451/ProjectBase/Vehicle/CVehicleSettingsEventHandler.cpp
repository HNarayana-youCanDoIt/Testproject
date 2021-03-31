/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CVehicleSettingsEventHandler.cpp
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * This class is to handle vehicle events.
 */

#include "CVehicleSettingsEventHandler.h"
#include "implementations/CVehicleResourceImpl.h"
#include "ResourceFactory.hpp"
#include "CHMIMain.h"
#include "CVehicleSettingsAdaptor.h"

CVehicleSettingsEventHandler::CVehicleSettingsEventHandler(QObject *parent) :
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s", __FUNCTION__);
    connectSignals();
}

CVehicleSettingsEventHandler::~CVehicleSettingsEventHandler()
{

}

void CVehicleSettingsEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s", __FUNCTION__);
    CVehicleResourceImpl* pVehicleResource = dynamic_cast<CVehicleResourceImpl*>(ResourceFactory::getVehicleResource());
    if(pVehicleResource)
    {
        CVehicleSettingsEventProvider* pVehicleEventProvider = pVehicleResource->getVehicleEventProvider();
        if(pVehicleEventProvider)
        {
            connect(pVehicleEventProvider, SIGNAL(sigUpdateApproachLampsValue(int)), this, SLOT(sltUpdateApproachLampsValue(int)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateVehicleAutoRelockStatus(bool)), this, SLOT(sltUpdateVehicleAutoRelockStatus(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateBCMPresenceStatus(bool)), this, SLOT(sltUpdateBCMPresenceStatus(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateVehicleSpeedValue(float)), this, SLOT(sltUpdateVehicleSpeedValue(float)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateAmbLightModeValue(int)), this, SLOT(sltUpdateAmbLightModeValue(int)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateAmbLightIllumLevelValue(int)), this, SLOT(sltUpdateAmbLightIllumLevelValue(int)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateAmbientLightModeIlluOnHuValue(bool)), this, SLOT(sltUpdateAmbientLightModeIlluOnHuStatus(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateAmbLightIlluSelLevelValue(int)), this, SLOT(sltUpdateAmbLightIlluSelLevelValue(int)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateParkLampStatus(bool)), this, SLOT(sltUpdateParkLampStatus(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateSpeedLockOutStatus(bool)), this, SLOT(sltUpdateSpeedLockOutStatus(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateVehiAutoRelockPresenceStatus(bool)), this, SLOT(sltUpdateVehiAutoRelockPresenceStatus(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateApproachLampsPresenceStatus(bool)), this, SLOT(sltUpdateApproachLampsPresenceStatus(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateBcmUcsState(bool)), this, SLOT(sltUpdateBcmUcsState(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateAntitheftFeaturePresenceStatus(bool)), this, SLOT(sltUpdateAntitheftFeaturePresenceStatus(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateBCmAntitheftKeyConfirmationValue(bool)), this, SLOT(sltUpdateBCmAntitheftKeyConfirmationValue(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigVehicleSettingChangeError()), this, SLOT(sltVehicleSettingChangeError()), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigBcmDrlSelectionState(bool)), this, SLOT(sltBcmDrlSelectionState(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateBcmDrlFeaturePresenceStatus(bool)), this, SLOT(sltUpdateBcmDrlFeaturePresenceStatus(bool)), Qt::QueuedConnection);
            connect(pVehicleEventProvider, SIGNAL(sigUpdateAmbLightSelIllumLevelResponse()), this, SLOT(sltUpdateAmbLightSelIllumLevelResponse()), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"pVehicleEventProvider is NULL.");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE, "%s, vehicle Resource is returned NULL from Resource Factory", __FUNCTION__);
    }
}

void CVehicleSettingsEventHandler::sltUpdateApproachLampsValue(int iAppraochLampsValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Appraoch Lamps : %d ",__FUNCTION__, iAppraochLampsValue);
    CVehicleSettingsAdaptor::getInstance()->setAppraochLamps(iAppraochLampsValue);
}

void CVehicleSettingsEventHandler::sltUpdateVehicleAutoRelockStatus(bool bAutoRelockStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Auto Relock : %d ",__FUNCTION__, bAutoRelockStatus);
    CVehicleSettingsAdaptor::getInstance()->setVehicleAutoRelock(bAutoRelockStatus);
}

void CVehicleSettingsEventHandler::sltUpdateBCMPresenceStatus(bool bBCmPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, BCM Presence : %d ",__FUNCTION__, bBCmPresence);
    CVehicleSettingsAdaptor::getInstance()->setBCMPresence(bBCmPresence);
}

void CVehicleSettingsEventHandler::sltUpdateVehicleSpeedValue(float fVehicleSpeed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Vehicle Speed : %f ",__FUNCTION__, fVehicleSpeed);
    CVehicleSettingsAdaptor::getInstance()->setVehicleSpeed(fVehicleSpeed);
}

void CVehicleSettingsEventHandler::sltUpdateAmbLightModeValue(int iAmbLightMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient Light Mode : %d ",__FUNCTION__, iAmbLightMode);
    CVehicleSettingsAdaptor::getInstance()->setAmbLightMode(static_cast<CVehicleEnums::EAmbientLightMode>(iAmbLightMode));
}

void CVehicleSettingsEventHandler::sltUpdateAmbLightIllumLevelValue(int iAmbLightIlluLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient Light possible illumination level : %d ",__FUNCTION__, iAmbLightIlluLevel);
    CVehicleSettingsAdaptor::getInstance()->setAmbLightIllumLevel(iAmbLightIlluLevel);
}

void CVehicleSettingsEventHandler::sltUpdateAmbientLightModeIlluOnHuStatus(bool bAmbientLightModeIlluOnHu)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient Light illumination On HU : %d ",__FUNCTION__, bAmbientLightModeIlluOnHu);
    CVehicleSettingsAdaptor::getInstance()->setAmbientLightModeIlluOnHu(bAmbientLightModeIlluOnHu);
}

void CVehicleSettingsEventHandler::sltUpdateAmbLightIlluSelLevelValue(int iAmbSelIlluLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient Light Selected illumination level On HU : %d ",__FUNCTION__, iAmbSelIlluLevel);
    CVehicleSettingsAdaptor::getInstance()->setAmbLightIlluSelLevelValue(iAmbSelIlluLevel);
    CVehicleSettingsAdaptor::getInstance()->updateAmbLightSelIllumLevelResponseRecv();
}

void CVehicleSettingsEventHandler::sltUpdateParkLampStatus(bool bParkLampStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Park lamp status : %d ",__FUNCTION__, bParkLampStatus);
    CVehicleSettingsAdaptor::getInstance()->setParkLampStatus(bParkLampStatus);
}

void CVehicleSettingsEventHandler::sltUpdateVehiAutoRelockPresenceStatus(bool bVehiAutoRelockPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Vehicle auto relock presence : %d ",__FUNCTION__, bVehiAutoRelockPresence);
    CVehicleSettingsAdaptor::getInstance()->setVehicleAutoRelockPresence(bVehiAutoRelockPresence);
}

void CVehicleSettingsEventHandler::sltUpdateApproachLampsPresenceStatus(bool bApproachLampsPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Approach lamps presence : %d ",__FUNCTION__, bApproachLampsPresence);
    CVehicleSettingsAdaptor::getInstance()->setAppraochLampsPresence(bApproachLampsPresence);
}

void CVehicleSettingsEventHandler::sltUpdateBcmUcsState(bool bBcmUcsState)
{
   LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, BcmUcs state : %d ",__FUNCTION__, bBcmUcsState);
   CVehicleSettingsAdaptor::getInstance()->setBcmUcsState(bBcmUcsState);
}

void CVehicleSettingsEventHandler::sltUpdateSpeedLockOutStatus(bool bSpeedLockOutStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: bSpeedLockOutStatus: %d", __FUNCTION__, bSpeedLockOutStatus);
    CVehicleSettingsAdaptor::getInstance()->setSpeedLockOutStatus(bSpeedLockOutStatus);
}

void CVehicleSettingsEventHandler::sltUpdateAntitheftFeaturePresenceStatus(bool bIsAntitheftFeatureEnabled)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s, bIsAntitheftFeatureEnabled : %d ", __FUNCTION__, bIsAntitheftFeatureEnabled);
    CVehicleSettingsAdaptor::getInstance()->updateAntitheftFeaturePresenceStatus(bIsAntitheftFeatureEnabled);
}

void CVehicleSettingsEventHandler::sltUpdateBCmAntitheftKeyConfirmationValue(bool bIsAntitheftKeyConfirmed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s, bIsAntitheftKeyConfirmed : %d ", __FUNCTION__, bIsAntitheftKeyConfirmed);
    CVehicleSettingsAdaptor::getInstance()->updateBCmAntitheftKeyConfirmationValue(bIsAntitheftKeyConfirmed);
}

void CVehicleSettingsEventHandler::sltVehicleSettingChangeError()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);

    CVehicleSettingsAdaptor::getInstance()->updateVehicleSettingChangeError();
}

void CVehicleSettingsEventHandler::sltBcmDrlSelectionState(bool bDrlMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);

    CVehicleSettingsAdaptor::getInstance()->updateBcmDrlSelectionState(bDrlMode);
}

void CVehicleSettingsEventHandler::sltUpdateBcmDrlFeaturePresenceStatus(bool bIsDrlFeatureEnabled)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s bIsDrlFeatureEnabled : %d", __FUNCTION__, bIsDrlFeatureEnabled);
    CVehicleSettingsAdaptor::getInstance()->UpdateBcmDrlFeaturePresenceStatus(bIsDrlFeatureEnabled);
}

void CVehicleSettingsEventHandler::sltUpdateAmbLightSelIllumLevelResponse()
{
   LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s ", __FUNCTION__);
}

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
 * CVehicleSettingsEventProvider, Class to send signals to setup Application layer on vehicle Resource events
 */

#include "logging.h"
#include "CVehicleSettingsEventProvider.h"

CVehicleSettingsEventProvider::CVehicleSettingsEventProvider(QObject *pParent) :
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s",__FUNCTION__);
}

CVehicleSettingsEventProvider::~CVehicleSettingsEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s",__FUNCTION__);
}

void CVehicleSettingsEventProvider::updateApproachLampsValue(qint16 iAppraochLamps)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, appraoch lamp value : %d", __FUNCTION__, iAppraochLamps);
    emit sigUpdateApproachLampsValue(iAppraochLamps);
}

void CVehicleSettingsEventProvider::updateVehicleAutoRelockStatus(bool bAutoRelockStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Auto Relock status : %d", __FUNCTION__, bAutoRelockStatus);
    emit sigUpdateVehicleAutoRelockStatus(bAutoRelockStatus);
}

void CVehicleSettingsEventProvider::updateBCMPresenceStatus(bool bBCmPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, BCM Presence status : %d", __FUNCTION__, bBCmPresenceStatus);
    emit sigUpdateBCMPresenceStatus(bBCmPresenceStatus);
}

void CVehicleSettingsEventProvider::updateVehiAutoRelockPresenceStatus(bool bVehiAutoRelockPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, BCM Presence status : %d", __FUNCTION__, bVehiAutoRelockPresence);
    emit sigUpdateVehiAutoRelockPresenceStatus(bVehiAutoRelockPresence);
}

void CVehicleSettingsEventProvider::updateVehicleSpeedValue(float fVehicleSpeed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Vehicle speed : %f", __FUNCTION__, fVehicleSpeed);
    emit sigUpdateVehicleSpeedValue(fVehicleSpeed);
}

void CVehicleSettingsEventProvider::updateAmbLightModeValue(int iAmbLightMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient Light mode : %d", __FUNCTION__, iAmbLightMode);
    emit sigUpdateAmbLightModeValue(iAmbLightMode);
}

void CVehicleSettingsEventProvider::updateAmbLightIllumLevelValue(int iAmbLightIllumLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient Light illumination levels : %d", __FUNCTION__, iAmbLightIllumLevel);
    emit sigUpdateAmbLightIllumLevelValue(iAmbLightIllumLevel);
}

void CVehicleSettingsEventProvider::updateAmbientLightModeIlluOnHuValue(bool bAmbientLightModeIlluOnHu)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient Light on HU : %d", __FUNCTION__, bAmbientLightModeIlluOnHu);
    emit sigUpdateAmbientLightModeIlluOnHuValue(bAmbientLightModeIlluOnHu);
}

void CVehicleSettingsEventProvider::updateAmbLightIlluSelLevelOnHuValue(int16_t iAmbSelIlluLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient Light selected Illu Level on HU : %d", __FUNCTION__, iAmbSelIlluLevel);
    emit sigUpdateAmbLightIlluSelLevelValue(iAmbSelIlluLevel);
}

void CVehicleSettingsEventProvider::updateParkLampStatus(bool bParkLampStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Park lamp status : %d", __FUNCTION__, bParkLampStatus);
    emit sigUpdateParkLampStatus(bParkLampStatus);
}

void CVehicleSettingsEventProvider::updateSpeedLockOutStatus(bool bSpeedLockOutStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: bSpeedLockOutStatus: %d", __FUNCTION__, bSpeedLockOutStatus);
    emit sigUpdateSpeedLockOutStatus(bSpeedLockOutStatus);
}

void CVehicleSettingsEventProvider::updateApproachLampsPresenceStatus(bool bApproachLampsPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: Approach lamps status: %d", __FUNCTION__, bApproachLampsPresence);
    emit sigUpdateApproachLampsPresenceStatus(bApproachLampsPresence);
}

void CVehicleSettingsEventProvider::updateBcmUcsState(bool bBcmUcsState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: Bcm Ucs state: %d", __FUNCTION__, bBcmUcsState);
    emit sigUpdateBcmUcsState(bBcmUcsState);
}

void CVehicleSettingsEventProvider::updateAntitheftFeaturePresenceStatus(bool bIsAntitheftFeatureEnabled)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: bIsAntitheftFeatureEnabled: %d", __FUNCTION__, bIsAntitheftFeatureEnabled);
    emit sigUpdateAntitheftFeaturePresenceStatus(bIsAntitheftFeatureEnabled);

}

void CVehicleSettingsEventProvider::updateBCmAntitheftKeyConfirmationValue(bool bIsAntitheftKeyConfirmed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: bIsAntitheftKeyConfirmed: %d", __FUNCTION__, bIsAntitheftKeyConfirmed);
    emit sigUpdateBCmAntitheftKeyConfirmationValue(bIsAntitheftKeyConfirmed);

}

void CVehicleSettingsEventProvider::updateVehicleSettingChangeError()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);
    emit sigVehicleSettingChangeError();
}

void CVehicleSettingsEventProvider::updateBcmDrlSelectionState(bool bDrlMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);
    emit sigBcmDrlSelectionState(bDrlMode);
}

void CVehicleSettingsEventProvider::updateBcmDrlFeaturePresenceStatus(bool bIsDrlFeatureEnabled)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);
    emit sigUpdateBcmDrlFeaturePresenceStatus(bIsDrlFeatureEnabled);
}

void CVehicleSettingsEventProvider::updateAmbLightSelIllumLevelResponse()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);
    emit sigUpdateAmbLightSelIllumLevelResponse();
}



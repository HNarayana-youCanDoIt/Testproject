/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CVehicleResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CVehicleResourceImpl, Resource Implementation for Audio.
 */

#include "CVehicleResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"
#include "CVehicleEnums.h"

CVehicleResourceImpl::CVehicleResourceImpl():
    m_pVehicleEventProvider(new CVehicleSettingsEventProvider()),
    m_objVehicleServiceProxy(ResourceDeploymentConfig::getConfig().m_VehicleSettingsService_Proxy.domain, ResourceDeploymentConfig::getConfig().m_VehicleSettingsService_Proxy.instance),
    m_bVehicleSettingAvailable(false),
    m_bIsBCmAntitheftFeatureEnabled(false),
    m_bIsBCmAntitheftKeyConfirmed(false),
    m_iAmbSelIlluLevel(-1)

{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s",__FUNCTION__);
    SUBSCRIBE(m_objVehicleServiceProxy,getProxyStatusEvent(),&CVehicleResourceImpl::vehicleSettingsSeriveStatusCb,_1)
}

void CVehicleResourceImpl::subscribeVehicleSettingsProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s",__FUNCTION__);
    SUBSCRIBE(m_objVehicleServiceProxy, getApproachLampValueEvent(), &CVehicleResourceImpl::onApproachLampValueCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getAutoRelockfunctionEvent(), &CVehicleResourceImpl::onVehicleAutoRelockValueCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getBCmPresenceAttribute().getChangedEvent(), &CVehicleResourceImpl::onBCmPresenceAttributeCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getVehicleSpeedAttribute().getChangedEvent(), &CVehicleResourceImpl::onVehicleSpeedAttributeCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getAmbLightModeEvent(), &CVehicleResourceImpl::onAmbLightModeAttributeCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getAmbLightIllumPossibleLevelsEvent(), &CVehicleResourceImpl::onAmbLightIllumPossibleLevelsCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getAmbientLightModeIlluOnHuAttribute().getChangedEvent(), &CVehicleResourceImpl::onAmbientLightModeIlluOnHuCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getAmbientLightIllumSelLevelsEvent(), &CVehicleResourceImpl::onAmbientLightIllumSelLevelOnHuCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getParkLampStatusAttribute().getChangedEvent(), &CVehicleResourceImpl::onParkLampStatusCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getSpeedLockOutEvent(), &CVehicleResourceImpl::onSpeedLockOutEventCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getBCmUcsStateAttribute().getChangedEvent(), &CVehicleResourceImpl::onBcmUcsStateAttributeCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getBCmAutoRelockStateAttribute().getChangedEvent(), &CVehicleResourceImpl::onVehiAutoRelockPresenceAttributeCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getBCmApproachLampStateAttribute().getChangedEvent(), &CVehicleResourceImpl::onApproachLampsPresenceAttributeCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getBCmAntitheftFeatureStateAttribute().getChangedEvent(), &CVehicleResourceImpl::onAntitheftFeaturePresenceAttributeCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getBCmAntitheftKeyConfirmationAttribute().getChangedEvent(), &CVehicleResourceImpl::onBCmAntitheftKeyConfirmationValueCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getBCmDRLStateAttribute().getChangedEvent(), &CVehicleResourceImpl::onBcmDrlFeaturePresenceAtrributeCb, _1);
    SUBSCRIBE(m_objVehicleServiceProxy, getDrlActiveSignalValEvent(), &CVehicleResourceImpl::onBcmDrlSelectionStateValueCb, _1);


    /** BCM settings error */
    SUBSCRIBE(m_objVehicleServiceProxy, getHuBCmRequestErrorEvent(), &CVehicleResourceImpl::onGetHuBcmRequestErrorEventCb, _1);
}


CVehicleResourceImpl::~CVehicleResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s",__FUNCTION__);
}

CVehicleSettingsEventProvider *CVehicleResourceImpl::getVehicleEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s",__FUNCTION__);
    return m_pVehicleEventProvider;
}

void CVehicleResourceImpl::vehicleSettingsSeriveStatusCb(CommonAPI::AvailabilityStatus eStatus)
{
    if(CommonAPI::AvailabilityStatus::AVAILABLE ==  eStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, :true", __FUNCTION__);
        m_bVehicleSettingAvailable = true;
        subscribeVehicleSettingsProxy();
        getBCMPresence();
        //To get the value of Vehicle auto relock
        getVehicleAutoRelockValue();
        //To get the value of Approach Lamps
        getApproachLampValue();
        //To get the value of Ambient light mode
        getAmbLightMode();
        //To get the value of Ambient light illumination maximum level
        getAmbLightIllumPossibleLevel();
        //To get the value of selected illumination level
        getAmbLightIllumSelLevel();
        //To get the value of DRL selection state
        getBcmDrlActiveSignalVal();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, :false", __FUNCTION__);
        m_bVehicleSettingAvailable = false;
    }
}

void CVehicleResourceImpl::setApproachLamps(int16_t iApproachLampsValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s: Request - ApprachLamps: %d", __FUNCTION__, iApproachLampsValue);

    if(m_bVehicleSettingAvailable)
    {
        m_objVehicleServiceProxy->setValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::USER_CUSTOMIZATION_SETTINGS, VehicleSettingsTypeCollection::settingsAttribute_enum::UCS_APPROACH_LAMP_VALUE, iApproachLampsValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::setVehicleAutoRelock(bool bVehicleAutoRelock)
{
    if(m_bVehicleSettingAvailable)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s: Request - Vehicle Auto Relock: %d, Vehicle service :%d ", __FUNCTION__, bVehicleAutoRelock, m_bVehicleSettingAvailable);
        m_objVehicleServiceProxy->setValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::USER_CUSTOMIZATION_SETTINGS, VehicleSettingsTypeCollection::settingsAttribute_enum::UCS_AUTO_RELOCK_FUNCTION, bVehicleAutoRelock);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onApproachLampValueCb(int16_t iApproachLampValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Appraoch Lamp : %d ",__FUNCTION__, iApproachLampValue);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateApproachLampsValue(iApproachLampValue);
    }
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"VehicleEventProvider is null");
}

void CVehicleResourceImpl::getApproachLampValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Approach Lamps value",__FUNCTION__);
    if(m_bVehicleSettingAvailable)
    {
        m_objVehicleServiceProxy->getValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::USER_CUSTOMIZATION_SETTINGS, VehicleSettingsTypeCollection::settingsAttribute_enum::UCS_APPROACH_LAMP_VALUE, std::bind(&CVehicleResourceImpl::setApproachLampsAsyncCbResp,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::getAmbLightMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Ambient Light Mode ", __FUNCTION__);
    if(m_bVehicleSettingAvailable)
    {
        m_objVehicleServiceProxy->getValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::AMBIENT_LIGHT_SETTINGS,
                                                VehicleSettingsTypeCollection::settingsAttribute_enum::AMBIENT_MODE_SETTINGS,
                                                std::bind(&CVehicleResourceImpl::onAmbLightModeAsyncCbResp,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }

}

void CVehicleResourceImpl::getAmbLightIllumPossibleLevel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Ambient Light Illumination Possible level ", __FUNCTION__);
    if(m_bVehicleSettingAvailable)
    {
        m_objVehicleServiceProxy->getValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::AMBIENT_LIGHT_SETTINGS,
                                                VehicleSettingsTypeCollection::settingsAttribute_enum::AMBIENT_ILLUMINATION_POSSIBLE_LEVELS,
                                                std::bind(&CVehicleResourceImpl::onAmbLightIllumPossibleLevelAsyncCbResp,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::getAmbLightIllumSelLevel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Ambient Light selected Illumination level ", __FUNCTION__);
    if(m_bVehicleSettingAvailable)
    {
        m_objVehicleServiceProxy->getValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::AMBIENT_LIGHT_SETTINGS,
                                                VehicleSettingsTypeCollection::settingsAttribute_enum::AMBIENT_ILLUMINATION_SEL_ACTIVE_VAL,
                                                std::bind(&CVehicleResourceImpl::onAmbLightIllumSelLevelAsyncCbResp,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::setBcmDrlSelectionState(bool bDrlActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s set - Drl Mode : %d", __FUNCTION__, bDrlActiveStatus);
    if(m_bVehicleSettingAvailable)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s: Request - DRL Mode: %d, Vehicle service :%d ", __FUNCTION__, bDrlActiveStatus, m_bVehicleSettingAvailable);
        m_objVehicleServiceProxy->setValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::USER_CUSTOMIZATION_SETTINGS, VehicleSettingsTypeCollection::settingsAttribute_enum::UCS_BCM_DRL_ACTIVE_SIGNAL_VAL, bDrlActiveStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::getBcmDrlActiveSignalVal()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - DRL selection value ", __FUNCTION__);
    if(m_bVehicleSettingAvailable)
    {
        m_objVehicleServiceProxy->getValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::USER_CUSTOMIZATION_SETTINGS, VehicleSettingsTypeCollection::settingsAttribute_enum::UCS_BCM_DRL_ACTIVE_SIGNAL_VAL, std::bind(&CVehicleResourceImpl::onBcmDrlActiveSignalValAsyncCbResp,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onBcmDrlActiveSignalValAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue)
{
    CPP_UNUSED(eReturnValue);
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, BcmDrl CB status",__FUNCTION__);
    if(CommonAPI::CallStatus::SUCCESS == callStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, false", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onBcmDrlSelectionStateValueCb(bool bDrlMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Drl Value : %d ",__FUNCTION__, bDrlMode);
    m_bBcmDrlSelectionStatus = bDrlMode;
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateBcmDrlSelectionState(bDrlMode);
    }
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"VehicleEventProvider is null");
}

bool CVehicleResourceImpl::getBcmDrlFeaturePresenceStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);
    return m_bBcmDrlFeatureStatus;
}

bool CVehicleResourceImpl::getBcmDrlSelectionState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);
    return m_bBcmDrlSelectionStatus;
}

void CVehicleResourceImpl::onBcmDrlFeaturePresenceAtrributeCb(bool bIsDrlFeatureEnabled)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Drl feature presence : %d ",__FUNCTION__, bIsDrlFeatureEnabled);
    m_bBcmDrlFeatureStatus = bIsDrlFeatureEnabled;
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateBcmDrlFeaturePresenceStatus(bIsDrlFeatureEnabled);
    }
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"VehicleEventProvider is null");
}

void CVehicleResourceImpl::getBCMPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - BCM Presence ", __FUNCTION__);
    if(m_bVehicleSettingAvailable)
    {
        m_objVehicleServiceProxy->getBCmPresenceAttribute().getValueAsync(std::bind(&CVehicleResourceImpl::getBCMPresenceAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onBCmPresenceAttributeCb(bool bBCmPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - BCM Presence : %d ", __FUNCTION__, bBCmPresence);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateBCMPresenceStatus(bBCmPresence);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onVehiAutoRelockPresenceAttributeCb(bool bVehiAutoRelockPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Vehicle auto relock Presence : %d ", __FUNCTION__, bVehiAutoRelockPresence);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateVehiAutoRelockPresenceStatus(bVehiAutoRelockPresence);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onApproachLampsPresenceAttributeCb(bool bApproachLampsPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Approach Lamps Presence : %d ", __FUNCTION__, bApproachLampsPresence);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateApproachLampsPresenceStatus(bApproachLampsPresence);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onBcmUcsStateAttributeCb(bool bBcmUcsState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Bcm Ucs state : %d ", __FUNCTION__, bBcmUcsState);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateBcmUcsState(bBcmUcsState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onVehicleSpeedAttributeCb(float fVehicleSpeed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Vehicle Speed : %f ", __FUNCTION__, fVehicleSpeed);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateVehicleSpeedValue(fVehicleSpeed);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onAmbLightModeAttributeCb(int16_t iAmbLightMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Ambient Light Mode: %d ", __FUNCTION__, iAmbLightMode);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateAmbLightModeValue(iAmbLightMode);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onAmbLightIllumPossibleLevelsCb(int16_t iAmbLightIllumPossibleLevels)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Ambient Light illumination possible levels: %d ", __FUNCTION__, iAmbLightIllumPossibleLevels);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateAmbLightIllumLevelValue(iAmbLightIllumPossibleLevels);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onAmbientLightModeIlluOnHuCb(bool bAmbientLightModeIlluOnHu)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Ambient Light availability on HU: %d ", __FUNCTION__, bAmbientLightModeIlluOnHu);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateAmbientLightModeIlluOnHuValue(bAmbientLightModeIlluOnHu);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onAmbientLightIllumSelLevelOnHuCb(int16_t iAmbSelIlluLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Ambient Light illumination Selected level on HU: %d ", __FUNCTION__, iAmbSelIlluLevel);
    m_iAmbSelIlluLevel = iAmbSelIlluLevel;
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateAmbLightIlluSelLevelOnHuValue(m_iAmbSelIlluLevel);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

int CVehicleResourceImpl::getAmbSelIlluminationLevel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);
    return  m_iAmbSelIlluLevel;
}

void CVehicleResourceImpl::onParkLampStatusCb(bool bParkLampStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get Park Lamp status: %d ", __FUNCTION__,bParkLampStatus);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateParkLampStatus(bParkLampStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::setApproachLampsAsyncCbResp(const CallStatus &status, VehicleSettingsTypeCollection::retStatus_enum eReturnValue)
{
    CPP_UNUSED(eReturnValue);
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Approach Lamps CB status",__FUNCTION__);
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, false", __FUNCTION__);
    }
}

void CVehicleResourceImpl::getBCMPresenceAsyncCb(const CallStatus &status, bool bBCmPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, BCM Presence CB status %d",__FUNCTION__, bBCmPresence);
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, true", __FUNCTION__);
        m_pVehicleEventProvider->updateBCMPresenceStatus(bBCmPresence);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, false", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onAmbLightModeAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient light mode CB status %d",__FUNCTION__, static_cast<int>(eReturnValue));
    if(CommonAPI::CallStatus::SUCCESS == callStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, false", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onAmbLightIllumPossibleLevelAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue)
{
    CPP_UNUSED(eReturnValue);
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient light illumination possible level CB status",__FUNCTION__);
    if(CommonAPI::CallStatus::SUCCESS == callStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, false", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onAmbLightIllumSelLevelAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue)
{
    CPP_UNUSED(eReturnValue);
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Ambient light illumination selected level CB status",__FUNCTION__);
    if(CommonAPI::CallStatus::SUCCESS == callStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, false", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onVehicleAutoRelockValueCb(bool bAutoRelockStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Vehicle Auto Relock : %d ",__FUNCTION__, bAutoRelockStatus);
    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateVehicleAutoRelockStatus(bAutoRelockStatus);
    }
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"VehicleEventProvider is null");
}

void CVehicleResourceImpl::getVehicleAutoRelockValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s get - Auto Relock value, Vehicle settings proxy %d",__FUNCTION__ , m_bVehicleSettingAvailable);

    if(m_bVehicleSettingAvailable)
    {
        m_objVehicleServiceProxy->getValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::USER_CUSTOMIZATION_SETTINGS, VehicleSettingsTypeCollection::settingsAttribute_enum::UCS_AUTO_RELOCK_FUNCTION, std::bind(&CVehicleResourceImpl::setVehicleAutoRelockAsyncCbResp,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::setAmbLightMode(int16_t iAmbLightMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s Request - Ambient light mode %d",__FUNCTION__ , iAmbLightMode);
    if(m_bVehicleSettingAvailable)
    {
        m_objVehicleServiceProxy->setValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::AMBIENT_LIGHT_SETTINGS, VehicleSettingsTypeCollection::settingsAttribute_enum::AMBIENT_MODE_SETTINGS, iAmbLightMode);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::setAmbLightIllumLevel(int16_t iAmbLightIllumLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s Request - Ambient light illumination level %d",__FUNCTION__ , iAmbLightIllumLevel);
    if(m_bVehicleSettingAvailable)
    {
        m_objVehicleServiceProxy->setValueAsync(VehicleSettingsTypeCollection::vehicleSettingsTypes_enum::AMBIENT_LIGHT_SETTINGS,
                                                VehicleSettingsTypeCollection::settingsAttribute_enum::AMBIENT_ILLUMINATION_SEL_ACTIVE_VAL,
                                                iAmbLightIllumLevel,
                                                std::bind(&CVehicleResourceImpl::setAmbLightIllumLevelAsyncCb,
                                                          this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE,"%s, VehicleSettings Proxy not available", __FUNCTION__);
    }
}

void CVehicleResourceImpl::setAmbLightIllumLevelAsyncCb(const CallStatus &eCallStatus, VehicleSettingsTypeCollection::retStatus_enum eErrorStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE," %s ",__FUNCTION__ );
    Q_UNUSED(eCallStatus)

    if ( (VehicleSettingsTypeCollection::retStatus_enum::SUCCESS == eErrorStatus) && m_pVehicleEventProvider )
    {
        m_pVehicleEventProvider->updateAmbLightSelIllumLevelResponse();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE, "%s: m_pVehicleEventProvider is NULL or eErrorStatus: %d", __FUNCTION__, eErrorStatus.value_);
    }
}

void CVehicleResourceImpl::setVehicleAutoRelockAsyncCbResp(const CallStatus &callStatus, VehicleSettingsTypeCollection::retStatus_enum eReturnValue)
{
    CPP_UNUSED(eReturnValue);
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, Vehicle auto relock CB status",__FUNCTION__);
    if(CommonAPI::CallStatus::SUCCESS == callStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE,"%s, false", __FUNCTION__);
    }
}

void CVehicleResourceImpl::onSpeedLockOutEventCb(bool bSpeedLockOutStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: bSpeedLockOutStatus: %d", __FUNCTION__, bSpeedLockOutStatus);

    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateSpeedLockOutStatus(bSpeedLockOutStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE, "%s: VehicleEventProvider is NULL", __FUNCTION__);
    }

}

void CVehicleResourceImpl::onAntitheftFeaturePresenceAttributeCb(bool bIsAntitheftFeatureEnabled)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: bIsAntitheftFeatureEnabled: %d", __FUNCTION__, bIsAntitheftFeatureEnabled);

    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateAntitheftFeaturePresenceStatus(bIsAntitheftFeatureEnabled);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE, "%s: VehicleEventProvider is NULL", __FUNCTION__);
    }

}

void CVehicleResourceImpl::onBCmAntitheftKeyConfirmationValueCb(int iAntitheftKeyConfirmationValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: iAntitheftKeyConfirmationValue: %d", __FUNCTION__, iAntitheftKeyConfirmationValue);

    if(m_pVehicleEventProvider)
    {
        m_pVehicleEventProvider->updateBCmAntitheftKeyConfirmationValue(iAntitheftKeyConfirmationValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE, "%s: VehicleEventProvider is NULL", __FUNCTION__);
    }

}

bool CVehicleResourceImpl::getBCmAntitheftFeaturePresenceValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);
    return m_bIsBCmAntitheftFeatureEnabled ;
}

bool CVehicleResourceImpl::getBCmAntitheftKeyConfirmationValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s", __FUNCTION__);
    return m_bIsBCmAntitheftKeyConfirmed ;
}

void CVehicleResourceImpl::onGetHuBcmRequestErrorEventCb(VehicleSettingsTypeCollection::retStatus_enum eBcmRequestStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: Response - eBcmRequestStatus: %d", __FUNCTION__, eBcmRequestStatus.value_);

    if(VehicleSettingsTypeCollection::retStatus_enum::FAILURE == eBcmRequestStatus.value_)
    {
        if(m_pVehicleEventProvider)
        {
            m_pVehicleEventProvider->updateVehicleSettingChangeError();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VEHICLE, "%s: VehicleEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        //Success case, no action
    }
}

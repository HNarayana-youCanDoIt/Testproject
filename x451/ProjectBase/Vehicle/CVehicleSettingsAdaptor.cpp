/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CVehicleSettingsAdaptor.cpp
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * This class is to handle vehicle functionality.
 */

#include "CVehicleSettingsAdaptor.h"
#include "ResourceFactory.hpp"

CVehicleSettingsAdaptor* CVehicleSettingsAdaptor::m_pVehicleAdaptor = nullptr;

CVehicleSettingsAdaptor::CVehicleSettingsAdaptor(QObject *parent):
    QObject(parent),
    m_pVehicleResource(ResourceFactory::getVehicleResource()),
    m_iApproachLamps(-1),
    m_bVehicleAutoRelock(false),
    m_bBCmPresence(false),
    m_fVehicleSpeed(-1),
    m_eAmbientLightMode(CVehicleEnums::AMBIENT_LIGHT_OFF_MODE),
    m_iAmbLightIllumLevel(5),
    m_bAmbientLightModeIlluOnHu(false),    
    m_iAmbSelIlluLevel(ResourceFactory::getVehicleResource()->getAmbSelIlluminationLevel()),
    m_iLastAmbLightIllumLevel(ResourceFactory::getVehicleResource()->getAmbSelIlluminationLevel()),
    m_bParkLampStatus(false),
    m_bSpeedLockOutStatus(false),
    m_bVehiAutoRelockPresence(false),
    m_bAppraochLampsPresence(false),
    m_bAmbientLightAvailableStatus(false),
    m_bBcmUcsState(false),
    m_bBcmAntitheftFeatureStatus(ResourceFactory::getVehicleResource()->getBCmAntitheftFeaturePresenceValue()),
    m_bBCmAntitheftKeyConfirmationStatus(ResourceFactory::getVehicleResource()->getBCmAntitheftKeyConfirmationValue()),
    m_bBcmDrlSelectionStatus(ResourceFactory::getVehicleResource()->getBcmDrlSelectionState()),
    m_bAmbLightEnableStatus(true),
    m_bBcmDrlFeatureStatus(ResourceFactory::getVehicleResource()->getBcmDrlFeaturePresenceStatus()),
    m_bIsAmbLightSelIlluLevelRespRecv(true),
    m_iAmbLightIllumReqValue(-1),
    m_bIsAmbIlluminationSelUserInitaited(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    CVehicleEnums::registerVehicleEnumsToQML();
    CFramework::getFramework().setContextProperty("cppVehicleAdaptor", this);
    // Filling the approach lamps indexe's & vaule's map
    m_mapApproachLamps.clear();
    m_mapApproachLamps.insert(CVehicleEnums::VEHICLE_APPROACH_LAMPS_ZERO_INDEX, CVehicleEnums::VEHICLE_APPROACH_LAMPS_ZERO_INDEX_VALUE);
    m_mapApproachLamps.insert(CVehicleEnums::VEHICLE_APPROACH_LAMPS_ONE_INDEX, CVehicleEnums::VEHICLE_APPROACH_LAMPS_ONE_INDEX_VALUE);
    m_mapApproachLamps.insert(CVehicleEnums::VEHICLE_APPROACH_LAMPS_TWO_INDEX, CVehicleEnums::VEHICLE_APPROACH_LAMPS_TWO_INDEX_VALUE);
    connect(CPopupManager::getInstance(),SIGNAL(sigPopupResult(CPopupEnum::EPopupID,CPopupEnum::EPopupResult, QString)),this,SLOT(sltPopupResult(CPopupEnum::EPopupID,CPopupEnum::EPopupResult, QString)));
}

CVehicleSettingsAdaptor::~CVehicleSettingsAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    m_mapApproachLamps.clear();
    if(m_pVehicleAdaptor)
    {
        delete m_pVehicleAdaptor;
        m_pVehicleAdaptor = nullptr;
    }
}

CVehicleSettingsAdaptor *CVehicleSettingsAdaptor::getInstance()
{
    if(nullptr == m_pVehicleAdaptor)
    {
        m_pVehicleAdaptor = new CVehicleSettingsAdaptor();
    }
    return m_pVehicleAdaptor;
}

void CVehicleSettingsAdaptor::invSetAmbLightEnableStatus(bool bIsEnable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: bIsEnable: %d", __FUNCTION__, bIsEnable);
    if(bIsEnable != m_bAmbLightEnableStatus)
    {
        m_bAmbLightEnableStatus = bIsEnable;
        emit sigAmbLightEnableStatusChanged();
    }
    else
    {
        //do nothing
    }
}

/* get, set methods - start */

int CVehicleSettingsAdaptor::approachLamps()
{
    /* Passing the value to the map so that we can get key,
            if value is not found in the map it returns VEHICLE_APPROACH_LAMPS_DEFAULT_INDEX */
    return m_mapApproachLamps.key(static_cast<CVehicleEnums::EVehicleApproachLampsValues>(m_iApproachLamps), CVehicleEnums::VEHICLE_APPROACH_LAMPS_DEFAULT_INDEX);
}

void CVehicleSettingsAdaptor::setAppraochLamps(int iApproachLamps)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Apprach Lamps :%d", __FUNCTION__, iApproachLamps);
    m_iApproachLamps = iApproachLamps;
    emit sigAppraochLampsChanged();
}

bool CVehicleSettingsAdaptor::vehicleAutoRelock()
{
    return m_bVehicleAutoRelock;
}

void CVehicleSettingsAdaptor::setVehicleAutoRelock(bool bAutoRelockStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Auto Relock :%d", __FUNCTION__, bAutoRelockStatus);
    if(bAutoRelockStatus != m_bVehicleAutoRelock)
    {
        m_bVehicleAutoRelock = bAutoRelockStatus;
        emit sigVehicleAutoRelockChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

void CVehicleSettingsAdaptor::setAmbientLightAvailableStatus(bool bAmbientLightAvailableStatus)
{
    if(bAmbientLightAvailableStatus != m_bAmbientLightAvailableStatus)
    {
        m_bAmbientLightAvailableStatus = bAmbientLightAvailableStatus;
        emit sigAmbientLightAvailableStatusChanged();
    }
}

void CVehicleSettingsAdaptor::setBCMPresence(bool bBCmPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - BCM Presence :%d", __FUNCTION__, bBCmPresence);
    if(bBCmPresence != m_bBCmPresence)
    {
        m_bBCmPresence = bBCmPresence;
        updateAmbientLightAvailability();
        emit sigBCMPresenceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

void CVehicleSettingsAdaptor::setVehicleSpeed(float fVehicleSpeed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Vehicle Speed :%f", __FUNCTION__, fVehicleSpeed);
    if(fVehicleSpeed != m_fVehicleSpeed)
    {
        m_fVehicleSpeed = fVehicleSpeed;
        emit sigVehicleSpeedChanged();
    }
}

void CVehicleSettingsAdaptor::setAmbLightMode(CVehicleEnums::EAmbientLightMode eAmbLightMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Ambient light mode :%d", __FUNCTION__, eAmbLightMode);
    m_eAmbientLightMode = eAmbLightMode;
    emit sigAmbientLightModeChanged();
}

void CVehicleSettingsAdaptor::setAmbLightIllumLevel(int iAmbLightIllumLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Ambient light illumination level :%d", __FUNCTION__, iAmbLightIllumLevel);
    m_iAmbLightIllumLevel = iAmbLightIllumLevel;
    emit sigAmbLightIllumLevelChanged();
}

void CVehicleSettingsAdaptor::setAmbientLightModeIlluOnHu(bool bAmbientLightModeIlluOnHu)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Ambient light illumination On HU :%d", __FUNCTION__, bAmbientLightModeIlluOnHu);
    m_bAmbientLightModeIlluOnHu = bAmbientLightModeIlluOnHu;
    updateAmbientLightAvailability();
    emit sigAmbientLightModeIlluOnHuChanged();
}

void CVehicleSettingsAdaptor::setAmbLightIlluSelLevelValue(int iAmbSelIlluLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Ambient light Selected illumination level On HU : %d, m_bIsAmbIlluminationSelUserInitaited: %d", __FUNCTION__, iAmbSelIlluLevel, m_bIsAmbIlluminationSelUserInitaited);

    //If ambient light illumination changes are not user initated then only update the illumintation level for the UI update
    if(!m_bIsAmbIlluminationSelUserInitaited)
    {
        m_iAmbSelIlluLevel = iAmbSelIlluLevel;
        emit sigAmbLightIlluSelLevelChanged();
    }
    else
    {
        //do nothing
    }

    //Set the last illumination level value
    m_iLastAmbLightIllumLevel = iAmbSelIlluLevel;
}

void CVehicleSettingsAdaptor::updateAmbLightSelIllumLevelResponseRecv()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s m_bIsAmbLightSelIlluLevelRespRecv : %d, m_iAmbLightIllumReqValue : %d",
             __FUNCTION__, m_bIsAmbLightSelIlluLevelRespRecv, m_iAmbLightIllumReqValue);
    m_bIsAmbLightSelIlluLevelRespRecv = true;

    /*Note : Here this logic is used to hanlde the request to service call on release so that request to service wont miss */
    if(m_iAmbLightIllumReqValue != -1)
    {
        setAmbLightillumLevelAttribute(m_iAmbLightIllumReqValue);
        m_iAmbLightIllumReqValue = -1;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s InValid request of m_iAmbLightIllumReqValue : %d",
                 __FUNCTION__, m_iAmbLightIllumReqValue);
    }

}

void CVehicleSettingsAdaptor::setAmbLightillumLevelAttribute(int iAmbLightillumLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Ambient light illumination level :%d", __FUNCTION__, iAmbLightillumLevel);
    if(m_pVehicleResource)
    {
        m_iAmbLightIllumReqValue = iAmbLightillumLevel;
        if(m_bIsAmbLightSelIlluLevelRespRecv && (iAmbLightillumLevel != m_iAmbSelIlluLevel))
        {
            m_pVehicleResource->setAmbLightIllumLevel(iAmbLightillumLevel);
            m_bIsAmbLightSelIlluLevelRespRecv = false;
            m_iAmbLightIllumReqValue = -1;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same :%d", __FUNCTION__, iAmbLightillumLevel);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s, Vehicle Resource is null", __FUNCTION__);
    }
}

void CVehicleSettingsAdaptor::invSetAmbLightIllumLevel(int iAmbLightIllumLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_iLastAmbLightIllumLevel: %d, iAmbLightIllumLevel :%d", __FUNCTION__, m_iLastAmbLightIllumLevel, iAmbLightIllumLevel);
    if(m_iLastAmbLightIllumLevel != iAmbLightIllumLevel)
    {
        ResourceFactory::getVehicleResource()->setAmbLightIllumLevel(iAmbLightIllumLevel);
        m_bIsAmbLightSelIlluLevelRespRecv = false;
        m_iAmbLightIllumReqValue = -1;
    }
    else
    {
        //Set the illumination level and emit the signal so that qml can read the values again.
        m_iAmbSelIlluLevel = m_iLastAmbLightIllumLevel;
        emit sigAmbLightIlluSelLevelChanged();
    }
}

void CVehicleSettingsAdaptor::setParkLampStatus(bool bParkLampStatus)
{
    if(bParkLampStatus != m_bParkLampStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Park lamp status :%d", __FUNCTION__, bParkLampStatus);
        m_bParkLampStatus = bParkLampStatus;
        emit sigParkLampStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

void CVehicleSettingsAdaptor::setVehicleAutoRelockPresence(bool bVehiAutoRelockPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Vehicle Auto Re-lock Presence :%d", __FUNCTION__, bVehiAutoRelockPresence);
    if(bVehiAutoRelockPresence !=m_bVehiAutoRelockPresence)
    {
        m_bVehiAutoRelockPresence = bVehiAutoRelockPresence;
        emit sigVehiAutoRelockPresenceChanged();
    }
}

void CVehicleSettingsAdaptor::setAppraochLampsPresence(bool bAppraochLampsPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Approach lamps Presence :%d", __FUNCTION__, bAppraochLampsPresence);
    if(bAppraochLampsPresence != m_bAppraochLampsPresence)
    {
        m_bAppraochLampsPresence = bAppraochLampsPresence;
        emit sigAppraochLampsPresenceChanged();
    }
}

void CVehicleSettingsAdaptor::setBcmUcsState(bool bBcmUcsState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Bcm Ucs State :%d", __FUNCTION__, bBcmUcsState);
    if(bBcmUcsState != m_bBcmUcsState)
    {
        m_bBcmUcsState = bBcmUcsState;
        updateAmbientLightAvailability();
        emit sigBcmUcsStateChanged();
    }
}

void CVehicleSettingsAdaptor::updateAmbientLightAvailability()
{
    bool bStatus = (m_bBCmPresence && m_bBcmUcsState && m_bAmbientLightModeIlluOnHu);
    setAmbientLightAvailableStatus(bStatus);
}

void CVehicleSettingsAdaptor::updateAntitheftFeaturePresenceStatus(bool bIsAntitheftFeatureEnabled)
{
    if(bIsAntitheftFeatureEnabled != m_bBcmAntitheftFeatureStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - Antitheft Feature status :%d", __FUNCTION__, bIsAntitheftFeatureEnabled);
        m_bBcmAntitheftFeatureStatus = bIsAntitheftFeatureEnabled;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

void CVehicleSettingsAdaptor::updateBCmAntitheftKeyConfirmationValue(bool bIsAntitheftKeyConfirmed)
{
    if(bIsAntitheftKeyConfirmed != m_bBCmAntitheftKeyConfirmationStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s set -Antitheft Key Confirmation status :%d", __FUNCTION__, bIsAntitheftKeyConfirmed);
        m_bBCmAntitheftKeyConfirmationStatus = bIsAntitheftKeyConfirmed;

        if(m_bBcmAntitheftFeatureStatus)
        {
            if(m_bBCmAntitheftKeyConfirmationStatus)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Key Verification has been success.", __FUNCTION__);
            }
            else
            {
                //Show Authentication Failed Popup.
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Key Verification has been failed. Show Popup", __FUNCTION__);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_VEHICLE_ANTITHEFT_AUTHENTICATION_FAILED_POPUP);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: AntiTheft Feature is Disabled", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s Values are same", __FUNCTION__);
    }
}

void CVehicleSettingsAdaptor::updateVehicleSettingChangeError()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_VEHICLE_SETTING_CANNOT_UPDATE_POPUP);
    //If response is not received and we get error then only disable ambient light slider and set the value.
    if(!m_bIsAmbLightSelIlluLevelRespRecv)
    {
        //Disable ambient light component
        invSetAmbLightEnableStatus(false);
        //Set the illumination level to last illumination value and emit the signal so that qml can read the values again.
        m_iAmbSelIlluLevel = m_iLastAmbLightIllumLevel;
        emit sigAmbLightIlluSelLevelChanged();
    }
}

void CVehicleSettingsAdaptor::invSetAmbIlluminationSelUserInitaited(bool bUserInitated)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: bUserInitated is: %d", __FUNCTION__, bUserInitated);
    m_bIsAmbIlluminationSelUserInitaited = bUserInitated;
}

void CVehicleSettingsAdaptor::UpdateBcmDrlFeaturePresenceStatus(bool bIsDrlFeatureEnabled)
{
    if(bIsDrlFeatureEnabled != m_bBcmDrlFeatureStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s set - DRL Feature status :%d", __FUNCTION__, bIsDrlFeatureEnabled);
        m_bBcmDrlFeatureStatus = bIsDrlFeatureEnabled;
        emit sigBcmDrlFeaturePresenceStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

void CVehicleSettingsAdaptor::updateBcmDrlSelectionState(bool bDrlStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: bDrlStatus: %d", __FUNCTION__, bDrlStatus);

    if(bDrlStatus != m_bBcmDrlSelectionStatus)
    {
        m_bBcmDrlSelectionStatus = bDrlStatus;
        emit sigBcmDrlSelectionStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: Values are same", __FUNCTION__);
    }
}

/* get, set methods - end */

/* Vehicle resource implementor methods - start */

void CVehicleSettingsAdaptor::setApproachLampsAttribute(int iApproachLampsIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Approach Lamps :%d", __FUNCTION__, iApproachLampsIndex);

    if(approachLamps() != iApproachLampsIndex)
    {
        CVehicleEnums::EVehicleApproachLampsIndex eVehicleApproachLampsIndex = static_cast<CVehicleEnums::EVehicleApproachLampsIndex>(iApproachLampsIndex);
        if(m_mapApproachLamps.contains(eVehicleApproachLampsIndex))
        {
            ResourceFactory::getVehicleResource()->setApproachLamps(m_mapApproachLamps[eVehicleApproachLampsIndex]);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: m_mapApproachLamps doesn't contains approach lamps index: %d", __FUNCTION__, eVehicleApproachLampsIndex);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Approach lamps request received for the value which is already set: %d", __FUNCTION__, iApproachLampsIndex);
    }

}

void CVehicleSettingsAdaptor::setVehicleAutoRelockAttribute(bool bAutoRelock)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Vehicle Auto Relock :%d", __FUNCTION__, bAutoRelock);
    if(m_pVehicleResource)
    {
        m_pVehicleResource->setVehicleAutoRelock(bAutoRelock);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s, Vehicle Resource is null", __FUNCTION__);
    }
}

void CVehicleSettingsAdaptor::setAmbLightModeAttribute(int iAmbLightMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Ambient light mode :%d", __FUNCTION__, iAmbLightMode);
    /*FixMe: Need to do debounce logic here, so that multiple request to set value can be minimized */
    if(m_pVehicleResource)
    {
        if(iAmbLightMode != m_eAmbientLightMode)
        {
            m_pVehicleResource->setAmbLightMode(iAmbLightMode);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same :%d", __FUNCTION__, iAmbLightMode);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s, Vehicle Resource is null", __FUNCTION__);
    }
}

void CVehicleSettingsAdaptor::setBcmDrlSelectionAttribute(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Drl value :%d", __FUNCTION__, bValue);
    if(m_pVehicleResource)
    {
        m_pVehicleResource->setBcmDrlSelectionState(bValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s, Vehicle Resource is null", __FUNCTION__);
    }
}

void CVehicleSettingsAdaptor::sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s: ePopupId: %d | ePopupResult: %d | strAdditionalInfo: %s", __FUNCTION__,
             ePopupId, ePopupResult, strAdditionalInfo.toStdString().c_str());

    switch(ePopupId)
    {
    case CPopupEnum::EPopupID::EN_POPUPID_SETUP_VEHICLE_SETTING_CANNOT_UPDATE_POPUP:
    {
        if(CPopupEnum::EN_POPUP_RESULT_DISPLAYED != ePopupResult)
        {
            //Set enable status of ambient light component to true if the popup is closed
            invSetAmbLightEnableStatus(true);
        }

    }
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "Invalid popup id");
        break;
    }
}

void CVehicleSettingsAdaptor::setSpeedLockOutStatus(bool bSpeedLockOutStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: bSpeedLockOutStatus: %d", __FUNCTION__, bSpeedLockOutStatus);

    if(bSpeedLockOutStatus != m_bSpeedLockOutStatus)
    {
        m_bSpeedLockOutStatus = bSpeedLockOutStatus;
        emit sigSpeedLockOutStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VEHICLE, "%s: m_bSpeedLockOutStatus Values are same", __FUNCTION__);
    }
}


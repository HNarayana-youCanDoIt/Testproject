/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHVACAdaptor.h
 * @ingroup         HMIComponent
 * @author          Mohit Rajani
 * CHVACAdaptor, an Adaptor for HVAC module,
 * CHVACAdaptor used to communicate between QML and Resource Layer.
 */


#include "CHVACAdaptor.h"
#include "ResourceFactory.hpp"
#include "HVACResource/interfaces/IHVACResource.h"
#include "HMIIncludes.h"
#include <CFramework.h>

CHVACAdaptor* CHVACAdaptor::m_pHVACAdaptor = nullptr;

CHVACAdaptor::CHVACAdaptor(QObject *parent) : QObject(parent)
  , m_pHVACResource(ResourceFactory::getHVACResource())
  , m_uiACMode(0)
  , m_bXpressCoolMode(false)
  , m_uiEcoACMode(0)
  , m_uiAutoMode(0)
  , m_uiCtrlPanelMode(0)
  , m_uiMaxDefrostMode(0)
  , m_eAirRecirculationMode(CHVACEnums::HVAC_AIRCIRCULATION_UNKNOWN)
  , m_eDistributionMode(CHVACEnums::HVAC_DM_MIN_LIMIT)
  , m_uiFanSpeed(0)
  , m_bDualMode(false)
  , m_fTemperature(16)
  , m_uiRearDefog(0)
  , m_uiErrorStatus(0)
  , m_uiFanSpeedLowLimit(0)
  , m_uiFanSpeedHighLimit(7)
  , m_fTemperatureLowLimit(16)
  , m_fTemperatureHighLimit(30)
  , m_eCCMPresence(CHVACEnums::HVAC_CCM_UNKNOWN)
  , m_eHvacZoneType(CHVACEnums::HVAC_UNKNOWN_ZONE)
  , m_bAirFlowPresenceStatus(true)
  , m_bACPresenceStatus(true)
  , m_bEconPresenceStatus(false)
  , m_bTemperaturePresenceStatus(true)
  , m_bAutoPresenceStatus(true)
  , m_bFanPresenceStatus(true)
  , m_bFreshAirPresenceStatus(true)
  , m_bXpressCoolingPresenceStatus(false)
  , m_bDefrostPresenceStatus(true)
  , m_eHvacContainerType(CHVACEnums::EN_CONTAINER_TYPE_NONE)
  , m_fDriverTemperature(16)
  , m_fPassengerTemperature(16)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppHVACAdaptor", this);
    CHVACEnums::registerHVACEnumsToQML();
    insertFanSpeedImages();
}

CHVACAdaptor::~CHVACAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, __FUNCTION__);
    m_pHVACAdaptor = nullptr;
}

CHVACAdaptor* CHVACAdaptor::getInstance()
{
    if(nullptr == m_pHVACAdaptor)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC, __FUNCTION__);
        m_pHVACAdaptor = new CHVACAdaptor();
    }
    return m_pHVACAdaptor;
}

void CHVACAdaptor::callToResourceLayer(
        CHVACEnums::EHVACParamEnums eParameterEnum ,
        quint16 uiValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, param: %d, value: %u", __FUNCTION__,
             eParameterEnum, uiValue);

    if (m_pHVACResource)
    {
        m_pHVACResource->huCcm_req(static_cast<CcmPresTypes::eHuCcmParam::Literal>
                                   (eParameterEnum),static_cast<uint16_t>(uiValue));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"%s, HVAC resource is NULL", __FUNCTION__);
    }

}

float CHVACAdaptor::getTemperatureVal(int iTemperature)
{
    // Temperature sent from the resource ranges from 160 to 300 hence dividing by 10
    float fTempValue = static_cast<float>(iTemperature) / static_cast<float>(TEMPERATURE_DIVISOR_MULTI);

    if (fTempValue < m_fTemperatureLowLimit)
    {
        fTempValue = m_fTemperatureLowLimit - TEMPERATURE_STEP_SIZE;
    }
    else if (fTempValue > m_fTemperatureHighLimit)
    {
        fTempValue = m_fTemperatureHighLimit + TEMPERATURE_STEP_SIZE;
    }
    else
    {
        //Do nothing.
    }

    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s:fTempValue:  %lf",  __FUNCTION__, static_cast<double> (fTempValue));
    return fTempValue;
}

void CHVACAdaptor::insertFanSpeedImages()
{
    m_listFanSpeedImages.clear();
    m_listFanSpeedImages.append("qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_FanSpeed_7in_n-assets/Drw_Gfx_FanSpeed1_7in_n.png");
    m_listFanSpeedImages.append("qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_FanSpeed_7in_n-assets/Drw_Gfx_FanSpeed2_7in_n.png");
    m_listFanSpeedImages.append("qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_FanSpeed_7in_n-assets/Drw_Gfx_FanSpeed3_7in_n.png");
    m_listFanSpeedImages.append("qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_FanSpeed_7in_n-assets/Drw_Gfx_FanSpeed4_7in_n.png");
    m_listFanSpeedImages.append("qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_FanSpeed_7in_n-assets/Drw_Gfx_FanSpeed5_7in_n.png");
    m_listFanSpeedImages.append("qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_FanSpeed_7in_n-assets/Drw_Gfx_FanSpeed6_7in_n.png");
    m_listFanSpeedImages.append("qrc:/image/Drawers/ShortcutDrawer/HVAC/Maximized/Contents/dual_zone/Drw_Gfx_FanSpeed_7in_n-assets/Drw_Gfx_FanSpeed7_7in_n.png");
}

void CHVACAdaptor::fetchHVACvalues()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s",__FUNCTION__);

    SHVACParamValues sHVACInfo;
    if(nullptr != m_pHVACResource)
    {
        sHVACInfo = m_pHVACResource->fetchHVACInfo();
        setCCMPresence(static_cast<CHVACEnums::EHVACCCMPresence>(sHVACInfo.iCcmPresence));
        setAcMode(static_cast<int>(sHVACInfo.bCcmAirconCtrl));
        setAutoMode(static_cast<int>(sHVACInfo.bCcmAutoMode));
        setDistributionMode(sHVACInfo.iCcmDistribMode);
        setDualMode(static_cast<int>(sHVACInfo.bCcmDualMode));
        setEcoAcMode(static_cast<int>(sHVACInfo.bCcmEconMode));
        setErrorStatus(static_cast<int>(sHVACInfo.bCcmErrStatus));
        setFanSpeed(sHVACInfo.iCcmFanSpeed);
        setAirCirculationMode(sHVACInfo.iCcmFreshairRecirc);
        setFanSpeedHighLimit(sHVACInfo.iCcmHifanspdConfig);
        setTemepratureHighLimit(sHVACInfo.iCcmHitempConfig);
        setCtrlPanelMode(static_cast<int>(sHVACInfo.bCcmHVACCtrl));
        setFanSpeedLowLimit(sHVACInfo.iCcmLowfanspdConfig);
        setTemepratureLowLimit(sHVACInfo.iCcmLowtempConfig);
        setMaxDefrostMode(static_cast<int>(sHVACInfo.bCcmMaxDefrst));
        setRearDefog(static_cast<int>(sHVACInfo.bCccmRearDefog));
        setTemperatureValue(sHVACInfo.iCcmTempChange);
        setEconPresenceStatus(sHVACInfo.iCcmEconConfig == 0);
        setXpressCoolingPresenceStatus(sHVACInfo.iCcmExpCoolConfig != 0);
        setXpressCoolMode(sHVACInfo.bCcmExpCoolStatus);
        setPassengerTemperature(sHVACInfo.iCcmPassengerTemprature);
        setDriverTemperature(sHVACInfo.iCcmDriverTemprature);
        setHvacZoneType(static_cast<CHVACEnums::EHVACZoneType>(sHVACInfo.iVariantType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC, "%s: m_pHVACResource is NULL.", __FUNCTION__);
    }
}

void CHVACAdaptor::setCCMPresenceStatus(quint16 uiCCMPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s, uiCCMPresenceStatus: %u", __FUNCTION__, uiCCMPresenceStatus);

    setCCMPresence(static_cast<CHVACEnums::EHVACCCMPresence>(uiCCMPresenceStatus));

    // 0 means ccm is present
    if ((0 == uiCCMPresenceStatus) && m_pHVACResource)
    {
        m_pHVACResource->getCcmInfo();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: CCM is not present.", __FUNCTION__);
    }
}

void CHVACAdaptor::setHvacZoneType(CHVACEnums::EHVACZoneType eZoneType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: zone type is: %d.", __FUNCTION__, eZoneType);
    if(eZoneType != m_eHvacZoneType)
    {
        m_eHvacZoneType = eZoneType;
        //Emit signal
        emit sigZoneTypeUpdated();
        //Update HVAC container type based upon the zone type received.
        updateHVACContainerType();
    }
}

void CHVACAdaptor::setAirFlowPresenceStatus(bool bPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: presence status is: %d.", __FUNCTION__, bPresenceStatus);
    m_bAirFlowPresenceStatus = bPresenceStatus;
    //Emit signal
    emit sigAirFlowPresenceUpdated();
}

void CHVACAdaptor::setACPresenceStatus(bool bPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: presence status is: %d.", __FUNCTION__, bPresenceStatus);
    m_bACPresenceStatus = bPresenceStatus;
    //Emit signal
    emit sigACPresenceUpdated();
}

void CHVACAdaptor::setEconPresenceStatus(bool bPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: bPresenceStatus: %d, m_bEconPresenceStatus: %d", __FUNCTION__, bPresenceStatus, m_bEconPresenceStatus);
    if(m_bEconPresenceStatus != bPresenceStatus)
    {
        m_bEconPresenceStatus = bPresenceStatus;
        //Emit signal
        emit sigEconPresenceUpdated();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setTemperaturePresnceStatus(bool bPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: presence status is: %d.", __FUNCTION__, bPresenceStatus);
    m_bTemperaturePresenceStatus = bPresenceStatus;
    //Emit signal
    emit sigTemperaturePresenceUpdated();
}

void CHVACAdaptor::setAutoPresenceStatus(bool bPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: presence status is: %d.", __FUNCTION__, bPresenceStatus);
    m_bAutoPresenceStatus = bPresenceStatus;
    //Emit signal
    emit sigAutoPresenceUpdated();
}

void CHVACAdaptor::setFanPresenceStatus(bool bPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: presence status is: %d.", __FUNCTION__, bPresenceStatus);
    m_bFanPresenceStatus = bPresenceStatus;
    //Emit signal
    emit sigFanPresenceUpdated();
}

void CHVACAdaptor::setFreshAirPresenceStatus(bool bPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: presence status is: %d.", __FUNCTION__, bPresenceStatus);
    m_bFreshAirPresenceStatus = bPresenceStatus;
    //Emit signal
    emit sigFreshAirPresenceUpdated();
}

void CHVACAdaptor::setXpressCoolingPresenceStatus(bool bPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: bPresenceStatus: %d, m_bXpressCoolingPresenceStatus: %d", __FUNCTION__, bPresenceStatus, m_bXpressCoolingPresenceStatus);
    if(m_bXpressCoolingPresenceStatus != bPresenceStatus)
    {
        m_bXpressCoolingPresenceStatus = bPresenceStatus;
        //Emit signal
        emit sigXpressCoolingPresenceUpdated();
        //Update HVAC container type based upon the zone type received.
        updateHVACContainerType();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setDefrostPresenceStatus(bool bPresenceStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: presence status is: %d.", __FUNCTION__, bPresenceStatus);
    m_bDefrostPresenceStatus = bPresenceStatus;
    //Emit signal
    emit sigDefrostPresenceUpdated();
}

CHVACEnums::EHVACCCMPresence CHVACAdaptor::ccmPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: CCM presence value is: %d", __FUNCTION__, m_eCCMPresence);
    return m_eCCMPresence;
}

CHVACEnums::EHVACZoneType CHVACAdaptor::zoneType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: zone type is: %d", __FUNCTION__, m_eHvacZoneType);
    return m_eHvacZoneType;
}

CHVACEnums::EHVACContainerType CHVACAdaptor::hvacContainerType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: hvac container type is: %d", __FUNCTION__, m_eHvacContainerType);
    return m_eHvacContainerType;
}

bool CHVACAdaptor::airFlowPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: air flow presence value is: %d", __FUNCTION__, m_bAirFlowPresenceStatus);
    return m_bAirFlowPresenceStatus;
}

bool CHVACAdaptor::acPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: ac presence value is: %d", __FUNCTION__, m_bACPresenceStatus);
    return m_bACPresenceStatus;
}

bool CHVACAdaptor::econPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: econ presence value is: %d", __FUNCTION__, m_bEconPresenceStatus);
    return m_bEconPresenceStatus;
}

bool CHVACAdaptor::temperaturePresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: temperature presence value is: %d", __FUNCTION__, m_bTemperaturePresenceStatus);
    return m_bTemperaturePresenceStatus;
}

bool CHVACAdaptor::autoPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: auto presence value is: %d", __FUNCTION__, m_bAutoPresenceStatus);
    return m_bAutoPresenceStatus;
}

bool CHVACAdaptor::fanPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: fan presence value is: %d", __FUNCTION__, m_bFanPresenceStatus);
    return m_bFanPresenceStatus;
}

bool CHVACAdaptor::freshAirPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: fresh air presence value is: %d", __FUNCTION__, m_bFreshAirPresenceStatus);
    return m_bFreshAirPresenceStatus;
}

bool CHVACAdaptor::xpressCoolingPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: xpress cooling presence value is: %d", __FUNCTION__, m_bXpressCoolingPresenceStatus);
    return m_bXpressCoolingPresenceStatus;
}

bool CHVACAdaptor::defrostPresence()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: defrost presence value is: %d", __FUNCTION__, m_bDefrostPresenceStatus);
    return m_bDefrostPresenceStatus;
}

void CHVACAdaptor::setHVACParameter(CHVACEnums::EHVACParamEnums eHVACParam ,
                                    quint16 uiValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, param: %d, value: %u", __FUNCTION__,
             eHVACParam, uiValue);

    switch(eHVACParam)
    {
    case CHVACEnums::HUCCM_AIRCON_CTRL:
    case CHVACEnums::HUCCM_ECON_MODE:
    case CHVACEnums::HUCCM_AUTO_MODE:
    case CHVACEnums::HUCCM_HVAC_CTRL:
    case CHVACEnums::HUCCM_MAX_DEFRST:
    case CHVACEnums::HUCCM_FRESHAIR_RECIRC:
    case CHVACEnums::HUCCM_DISTRIB_MODE:
    case CHVACEnums::HUCCM_DUAL_MODE:
    case CHVACEnums::HUCCM_REAR_DEFOG:
    case CHVACEnums::CCM_ERR_STATUS:
    case CHVACEnums::HUCCM_FAN_SPEED:
    case CHVACEnums::HUCCM_TEMP_CHANGE:
        /*
         * ToDo: Need to add error handling. Require more details on how
         * this would be implemented by the ccm service. Once the service is
         * implemented we would update this
         */
        callToResourceLayer(eHVACParam,uiValue);
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, unknow param: %d, value: %u",
                 __FUNCTION__, eHVACParam, uiValue);
    }

}

void CHVACAdaptor::toggleAcMode()
{
    quint16 uiAcMode = !m_uiACMode;
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, set Ac mode: %u", __FUNCTION__,
             uiAcMode);
    callToResourceLayer(CHVACEnums::HUCCM_AIRCON_CTRL, uiAcMode);
}

void CHVACAdaptor::invToggleXpressCoolMode()
{
    quint16 uiXpressCoolMode = static_cast<quint16>(!m_bXpressCoolMode);
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, m_bXpressCoolMode: %d, uiXpressCoolMode: %u",
             __FUNCTION__, m_bXpressCoolMode, uiXpressCoolMode);
    callToResourceLayer(CHVACEnums::HUCCM_EXPCOOL_STATUS, uiXpressCoolMode);
}

void CHVACAdaptor::invToggleDualMode()
{
    quint16 uiDualMode = static_cast<quint16>(!m_bDualMode);
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, m_bDualMode: %d, uiDualMode: %u",
             __FUNCTION__, m_bDualMode, uiDualMode);
    callToResourceLayer(CHVACEnums::HUCCM_DUAL_MODE, uiDualMode);
}

void CHVACAdaptor::invDecreasePassengerTmp()
{
    float fPassengerTmp = m_fPassengerTemperature - TEMPERATURE_STEP_SIZE;

    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, m_fPassengerTemperature: %lf, fPassengerTmp: %lf", __FUNCTION__,
             static_cast<double> (m_fPassengerTemperature), static_cast<double> (fPassengerTmp));

    /*
     * Temperature that needs to be sent to resource ranges from 160 to 300
     * hence multiplying by 10.
     */
    callToResourceLayer(CHVACEnums::HUCCM_TEMP_PASS, static_cast<quint16>
                        (fPassengerTmp * TEMPERATURE_DIVISOR_MULTI));
}

void CHVACAdaptor::invIncreasePassengerTmp()
{
    float fPassengerTmp = m_fPassengerTemperature + TEMPERATURE_STEP_SIZE;

    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, m_fPassengerTemperature: %lf, fPassengerTmp: %lf", __FUNCTION__,
             static_cast<double> (m_fPassengerTemperature), static_cast<double> (fPassengerTmp));

    /*
     * Temperature that needs to be sent to resource ranges from 160 to 300
     * hence multiplying by 10
     */
    callToResourceLayer(CHVACEnums::HUCCM_TEMP_PASS, static_cast<quint16>
                        (fPassengerTmp * TEMPERATURE_DIVISOR_MULTI));
}

void CHVACAdaptor::invDecreaseDriverTmp()
{
    float fDriverTmp = m_fDriverTemperature - TEMPERATURE_STEP_SIZE;

    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, m_fDriverTemperature: %lf, fDriverTmp: %lf", __FUNCTION__,
             static_cast<double> (m_fDriverTemperature), static_cast<double> (fDriverTmp));

    /*
     * Temperature that needs to be sent to resource ranges from 160 to 300
     * hence multiplying by 10
     */
    callToResourceLayer(CHVACEnums::HUCCM_TEMP_DRVR, static_cast<quint16>
                        (fDriverTmp * TEMPERATURE_DIVISOR_MULTI));
}

void CHVACAdaptor::invIncreaseDriverTmp()
{
    float fDriverTmp = m_fDriverTemperature + TEMPERATURE_STEP_SIZE;

    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, m_fDriverTemperature: %lf, fDriverTmp: %lf", __FUNCTION__,
             static_cast<double> (m_fDriverTemperature), static_cast<double> (fDriverTmp));

    /*
     * Temperature that needs to be sent to resource ranges from 160 to 300
     * hence multiplying by 10
     */
    callToResourceLayer(CHVACEnums::HUCCM_TEMP_DRVR, static_cast<quint16>
                        (fDriverTmp * TEMPERATURE_DIVISOR_MULTI));
}

void CHVACAdaptor::toggleEcoAcMode()
{
    quint16 uiEcoAcMode = !m_uiEcoACMode;
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, set Eco Ac mode: %u", __FUNCTION__,
             uiEcoAcMode);
    callToResourceLayer(CHVACEnums::HUCCM_ECON_MODE, uiEcoAcMode);
}

void CHVACAdaptor::decreaseTemperature()
{
    float fTemperature = m_fTemperature - TEMPERATURE_STEP_SIZE;

    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, set Temperature: %lf", __FUNCTION__,
             static_cast<double> (fTemperature));

    /*
     * Temperature that needs to be sent to resource ranges from 160 to 300
     * hence multiplying by 10.
     */
    callToResourceLayer(CHVACEnums::HUCCM_TEMP_CHANGE, static_cast<quint16>
                        (fTemperature * TEMPERATURE_DIVISOR_MULTI));
}

void CHVACAdaptor::increaseTemperature()
{
    float fTemperature = m_fTemperature + TEMPERATURE_STEP_SIZE;
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, set Temperature: %lf", __FUNCTION__,
             static_cast<double> (fTemperature));

    /*
     * Temperature that needs to be sent to resource ranges from 160 to 300
     * hence multiplying by 10
     */
    callToResourceLayer(CHVACEnums::HUCCM_TEMP_CHANGE, static_cast<quint16>
                        (fTemperature * TEMPERATURE_DIVISOR_MULTI));
}

void CHVACAdaptor::decreaseFanSpeed()
{
    quint16 uiFanSpeed = m_uiFanSpeed - FAN_SPEED_STEP_SIZE;

    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, Set Fan speed: %u",
             __FUNCTION__,uiFanSpeed);

    if ((m_uiFanSpeedLowLimit <= uiFanSpeed) && (m_uiFanSpeedHighLimit >= uiFanSpeed))
    {
        callToResourceLayer(CHVACEnums::HUCCM_FAN_SPEED, uiFanSpeed);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"Fan speed not in range: %u", uiFanSpeed);
    }

}

void CHVACAdaptor::increaseFanSpeed()
{    
    quint16 uiFanSpeed = m_uiFanSpeed + FAN_SPEED_STEP_SIZE;

    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, Set Fan speed: %u",
             __FUNCTION__,uiFanSpeed);

    if ((m_uiFanSpeedLowLimit <= uiFanSpeed) && (m_uiFanSpeedHighLimit >= uiFanSpeed))
    {
        callToResourceLayer(CHVACEnums::HUCCM_FAN_SPEED, uiFanSpeed);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"Fan speed not in range: %u", uiFanSpeed);
    }
}

void CHVACAdaptor::increaseDistributionMode()
{
    CHVACEnums::EHVACDistributionMode eDistributionMode =
            static_cast<CHVACEnums::EHVACDistributionMode>
            (m_eDistributionMode + DISTRIBUTION_MODE_STEP_SIZE);

    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, increase distributionMode: %u",
             __FUNCTION__,eDistributionMode);
    if (CHVACEnums::HVAC_DM_MAX_LIMIT == eDistributionMode)
    {
        // Once the max limit is reached we need to loop back to chest mode
        eDistributionMode = CHVACEnums::HVAC_DM_CHEST_MODE;
    }

    callToResourceLayer(CHVACEnums::HUCCM_DISTRIB_MODE, eDistributionMode);
}

QString CHVACAdaptor::invGetFanSpeedImage(quint16 uiFanSpeed)
{
    QString strFanSpeedImg = "";
    if((uiFanSpeed > 0) && (uiFanSpeed <= m_listFanSpeedImages.size()))
    {
        strFanSpeedImg = m_listFanSpeedImages.at(uiFanSpeed - 1);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"%s, fan speed out of bound", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiFanSpeed: %u, strFanSpeedImg: %s", __FUNCTION__, uiFanSpeed, strFanSpeedImg.toStdString().c_str());
    return strFanSpeedImg;
}

void CHVACAdaptor::toggleAirCirculationMode()
{
    CHVACEnums::EHVACAirCirculationModes eAirCirculationMode = m_eAirRecirculationMode;

    switch(m_eAirRecirculationMode)
    {
    case CHVACEnums::HVAC_AIRCIRCULATION_UNKNOWN:
    case CHVACEnums::HVAC_AIRCIRCULATION_RECIRCULATION_ON:
        eAirCirculationMode = CHVACEnums::HVAC_AIRCIRCULATION_FRESHIR_ON;
        break;
    case CHVACEnums::HVAC_AIRCIRCULATION_FRESHIR_ON:
        eAirCirculationMode = CHVACEnums::HVAC_AIRCIRCULATION_RECIRCULATION_ON;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, air circulation mode invalid: %d",
                 __FUNCTION__, m_eAirRecirculationMode);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, set air circulation mode: %d",
             __FUNCTION__, eAirCirculationMode);
    callToResourceLayer(CHVACEnums::HUCCM_FRESHAIR_RECIRC, static_cast<quint16>
                        (eAirCirculationMode));
}

void CHVACAdaptor::updateHVACContainerType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s", __FUNCTION__);
    CHVACEnums::EHVACContainerType eHvacContainerType = CHVACEnums::EN_CONTAINER_TYPE_NONE;
    if(CHVACEnums::HVAC_DUAL_ZONE == zoneType())
    {
        eHvacContainerType = CHVACEnums::EN_CONTAINER_TYPE_DUAL_ZONE;
    }
    else if(CHVACEnums::HVAC_SINGLE_ZONE == zoneType())
    {
        if(xpressCoolingPresence())
        {
            eHvacContainerType = CHVACEnums::EN_CONTAINER_TYPE_SINGLE_ZONE_WITH_XPRESS_COOLING;
        }
        else
        {
            eHvacContainerType = CHVACEnums::EN_CONTAINER_TYPE_SINGLE_ZONE;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: Zone type not handled", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: eHvacContainerType is: %d, m_eHvacContainerType is: %d", __FUNCTION__,
             eHvacContainerType, m_eHvacContainerType);
    if(m_eHvacContainerType != eHvacContainerType)
    {
        m_eHvacContainerType = eHvacContainerType;
        emit sigHVACContainerTypeUpdated();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setAcMode(quint16 uiAcMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiAcMode: %u", __FUNCTION__,uiAcMode);

    if( m_uiACMode != uiAcMode )
    {
        m_uiACMode = uiAcMode;
        emit sigAcModeChanged();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setXpressCoolMode(bool bXpressCoolMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, bXpressCoolMode: %d, m_bXpressCoolMode: %d", __FUNCTION__, bXpressCoolMode, m_bXpressCoolMode);
    if(m_bXpressCoolMode != bXpressCoolMode)
    {
        m_bXpressCoolMode = bXpressCoolMode;
        emit sigXpressCoolModeChanged();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setEcoAcMode(quint16 uiEcoAcMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiEcoAcMode: %u", __FUNCTION__,uiEcoAcMode);

    if( m_uiEcoACMode != uiEcoAcMode)
    {
        m_uiEcoACMode = uiEcoAcMode;
        emit sigEcoAcModeChanged();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setAutoMode(quint16 uiAutoMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiAutoMode: %u", __FUNCTION__,uiAutoMode);

    if( m_uiAutoMode != uiAutoMode )
    {
        m_uiAutoMode = uiAutoMode;
        emit sigAutoModeChanged();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setCtrlPanelMode(quint16 uiCtrlPanelMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiCtrlPanelMode: %u", __FUNCTION__,uiCtrlPanelMode);

    if( m_uiCtrlPanelMode != uiCtrlPanelMode )
    {
        m_uiCtrlPanelMode = uiCtrlPanelMode;
        emit sigCtrlPanelModeChanged();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setMaxDefrostMode(quint16 uiMaxDefrostMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiMaxDefrostMode: %u", __FUNCTION__,uiMaxDefrostMode);

    if( m_uiMaxDefrostMode != uiMaxDefrostMode )
    {
        m_uiMaxDefrostMode = uiMaxDefrostMode;
        emit sigMaxDefrostModeChanged();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setAirCirculationMode(quint16 uiAirCirculationMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s air circulation mode: %d", __FUNCTION__,uiAirCirculationMode);

    if (CHVACEnums::HVAC_AIRCIRCULATION_RECIRCULATION_ON == uiAirCirculationMode ||
            CHVACEnums::HVAC_AIRCIRCULATION_FRESHIR_ON == uiAirCirculationMode)
    {
        if( m_eAirRecirculationMode != uiAirCirculationMode )
        {
            m_eAirRecirculationMode = static_cast<CHVACEnums::EHVACAirCirculationModes> (uiAirCirculationMode);
            emit sigAirCirculationModeChanged();
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, air circulation mode"
                                         " invalid: %d", __FUNCTION__,
                 uiAirCirculationMode);
    }
}

void CHVACAdaptor::setDistributionMode(quint16 uiDistributionMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiDistributionMode: %u", __FUNCTION__,uiDistributionMode);

    if( m_eDistributionMode != uiDistributionMode )
    {
        m_eDistributionMode = static_cast<CHVACEnums::EHVACDistributionMode>(uiDistributionMode);
        emit sigDistributionModeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: Distribution Mode is same as"
                                          " requested.", __FUNCTION__);
    }
}

void CHVACAdaptor::setFanSpeed(quint16 uiFanSpeed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiFanSpeed: %u", __FUNCTION__,uiFanSpeed);

    if( (m_uiFanSpeed != uiFanSpeed) && (uiFanSpeed <= m_uiFanSpeedHighLimit)
            && (uiFanSpeed >= m_uiFanSpeedLowLimit) )
    {
        m_uiFanSpeed = uiFanSpeed;
        emit sigFanSpeedChanged();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setDualMode(bool bDualMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiDualMode: %u", __FUNCTION__,bDualMode);

    if( m_bDualMode != bDualMode )
    {
        m_bDualMode = bDualMode;
        emit sigDualModeChanged();
    }
}

void CHVACAdaptor::setTemperature(float fTemperature)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: %lf",  __FUNCTION__, static_cast<double> (fTemperature));

    if ( m_fTemperature != fTemperature )
    {
        m_fTemperature = fTemperature;
        emit sigTemperatureChanged();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setTemperatureValue(quint16 uiTemperature)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiTemperature: %u", __FUNCTION__,uiTemperature);
    float fTempValue = getTemperatureVal(static_cast<int> (uiTemperature));
    setTemperature(fTempValue);
}

void CHVACAdaptor::setRearDefog(quint16 uiRearDefog)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiRearDefog: %u", __FUNCTION__,uiRearDefog);

    if( m_uiRearDefog != uiRearDefog )
    {
        m_uiRearDefog = uiRearDefog;
        emit sigRearDefogChanged();
    }
}

void CHVACAdaptor::setFanSpeedLowLimit(quint16 uiFanSpeedLowLimit)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiFanSpeedLowLimit: %u", __FUNCTION__,uiFanSpeedLowLimit);

    if( m_uiFanSpeedLowLimit != uiFanSpeedLowLimit )
    {
        m_uiFanSpeedLowLimit = uiFanSpeedLowLimit;
        emit sigFanSpeedLowLimitChanged();
    }
}

void CHVACAdaptor::setFanSpeedHighLimit(quint16 uiFanSpeedHighLimit)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiFanSpeedHighLimit: %u", __FUNCTION__,uiFanSpeedHighLimit);

    if( m_uiFanSpeedHighLimit != uiFanSpeedHighLimit )
    {
        m_uiFanSpeedHighLimit = uiFanSpeedHighLimit;
        emit sigFanSpeedHighLimitChanged();
    }
}

void CHVACAdaptor::setTemepratureLowLimit(quint16 uiTemperatureLowLimit)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiTemperatureLowLimit: %u", __FUNCTION__,uiTemperatureLowLimit);


    uiTemperatureLowLimit = uiTemperatureLowLimit / TEMPERATURE_DIVISOR_MULTI;
    if( m_fTemperatureLowLimit != uiTemperatureLowLimit )
    {
        m_fTemperatureLowLimit = uiTemperatureLowLimit;
        emit sigTemperatureLowLimitChanged();
    }
}

void CHVACAdaptor::setTemepratureHighLimit(quint16 uiTemperatureHighLimit)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiTemperatureHighLimit: %u", __FUNCTION__,uiTemperatureHighLimit);


    uiTemperatureHighLimit = uiTemperatureHighLimit / TEMPERATURE_DIVISOR_MULTI;

    if( m_fTemperatureHighLimit != uiTemperatureHighLimit )
    {
        m_fTemperatureHighLimit = uiTemperatureHighLimit;
        emit sigTemperatureHighLimitChanged();
    }
}

void CHVACAdaptor::setErrorStatus(quint16 uiErrorStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, uiErrorStatus: %u", __FUNCTION__,uiErrorStatus);
    if( m_uiErrorStatus != uiErrorStatus )
    {
        m_uiErrorStatus = uiErrorStatus;
        emit sigErrorStatusChanged();
    }

    /* CCM service sends uiErrorStatus as HVAC_ERROR_SETTING_NOT_UPDATED to show the Settings cannot be updated popup */
    if( CHVACEnums::HVAC_ERROR_SETTING_NOT_UPDATED == uiErrorStatus )
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_VEHICLE_SETTING_CANNOT_UPDATE_POPUP);
    }
}

void CHVACAdaptor::setCCMPresence(CHVACEnums::EHVACCCMPresence eCCMPresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: CCMPresence: %d", __FUNCTION__, eCCMPresence);

    if(m_eCCMPresence != eCCMPresence)
    {
        m_eCCMPresence = eCCMPresence;
        emit sigCCMPresenceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: CCM presence value is same as previous: %d", __FUNCTION__, m_eCCMPresence);
    }
}

void CHVACAdaptor::ccmUserInterventionParamChanged(int iHuCcmParam)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s: HU CCM param is: %d", __FUNCTION__, iHuCcmParam);
    emit sigCcmUserInterventionParamChanged(iHuCcmParam);
}

void CHVACAdaptor::setPassengerTemperature(int iPassengerTemp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, iPassengerTemp: %d", __FUNCTION__, iPassengerTemp);
    float fPassengerTempValue = getTemperatureVal(iPassengerTemp);
    if ( m_fPassengerTemperature != fPassengerTempValue )
    {
        m_fPassengerTemperature = fPassengerTempValue;
        emit sigPassengerTempChanged();
    }
    else
    {
        //do nothing
    }
}

void CHVACAdaptor::setDriverTemperature(int iDriverTemp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s, iDriverTemp: %d", __FUNCTION__, iDriverTemp);
    float fDriverTempValue = getTemperatureVal(iDriverTemp);
    if ( m_fDriverTemperature != fDriverTempValue )
    {
        m_fDriverTemperature = fDriverTempValue;
        emit sigDriverTempChanged();
    }
    else
    {
        //do nothing
    }
}

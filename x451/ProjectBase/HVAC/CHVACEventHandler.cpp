/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHVACEventHandler.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* @class        CHVACEventHandler: Class acts as the event handler for all the signals/events sent by CHVACEventProvider
* which informs HVAC Adaptor about HVAC resource events
*/

#include "CHVACEventHandler.h"
#include "CHVACAdaptor.h"
#include "HMIIncludes.h"
#include "HVACResource/implementations/CHVACResourceImpl.h"
#include <ResourceFactory.hpp>
#include "HVAC/CHVACEnums.h"
#include "CDisplayManagerAdaptor.h"

using namespace v0::com::harman::dcif;

CHVACEventHandler::CHVACEventHandler(QObject *parent) : QObject(parent),
    m_pHVACAdaptor(CHVACAdaptor::getInstance())
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);
    connectSignals();
}

void CHVACEventHandler::sltHVACParamUpdate(int eParameterEnum , const uint16_t& uiValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);

    /* If display is off and user change's the climate, Display must be wakeup */
    CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);

    if(m_pHVACAdaptor)
    {
        switch(eParameterEnum)
        {
        // All adaptor function calls to set value for the provided parameter
        case CHVACEnums::HUCCM_AIRCON_CTRL:
            m_pHVACAdaptor->setAcMode(uiValue);
            break;
        case CHVACEnums::HUCCM_ECON_MODE:
            m_pHVACAdaptor->setEcoAcMode(uiValue);
            break;
        case CHVACEnums::HUCCM_AUTO_MODE:
            m_pHVACAdaptor->setAutoMode(uiValue);
            break;
        case CHVACEnums::HUCCM_HVAC_CTRL:
            m_pHVACAdaptor->setCtrlPanelMode(uiValue);
            break;
        case CHVACEnums::HUCCM_MAX_DEFRST:
            m_pHVACAdaptor->setMaxDefrostMode(uiValue);
            break;
        case CHVACEnums::HUCCM_FRESHAIR_RECIRC:
            m_pHVACAdaptor->setAirCirculationMode(uiValue);
            break;
        case CHVACEnums::HUCCM_DISTRIB_MODE:
            m_pHVACAdaptor->setDistributionMode(uiValue);
            break;
        case CHVACEnums::HUCCM_FAN_SPEED:
            m_pHVACAdaptor->setFanSpeed(uiValue);
            break;
        case CHVACEnums::HUCCM_DUAL_MODE:
            m_pHVACAdaptor->setDualMode(uiValue != 0);
            break;
        case CHVACEnums::HUCCM_TEMP_CHANGE:
            m_pHVACAdaptor->setTemperatureValue(uiValue);
            break;
        case CHVACEnums::HUCCM_REAR_DEFOG:
            m_pHVACAdaptor->setRearDefog(uiValue);
            break;
        case CHVACEnums::CCM_ERR_STATUS:
            m_pHVACAdaptor->setErrorStatus(uiValue);
            break;
        case CHVACEnums::CCM_LOWFANSPD_CONFIG:
            m_pHVACAdaptor->setFanSpeedLowLimit(uiValue);
            break;
        case CHVACEnums::CCM_HIFANSPD_CONFIG:
            m_pHVACAdaptor->setFanSpeedHighLimit(uiValue);
            break;
        case CHVACEnums::CCM_LOWTEMP_CONFIG:
            m_pHVACAdaptor->setTemepratureLowLimit(uiValue);
            break;
        case CHVACEnums::CCM_HITEMP_CONFIG:
            m_pHVACAdaptor->setTemepratureHighLimit(uiValue);
            break;
        case CHVACEnums::CCM_PRESENCE:
            m_pHVACAdaptor->setCCMPresenceStatus(uiValue);
            break;
        case CHVACEnums::CCM_ECON_CONFIG:
            m_pHVACAdaptor->setEconPresenceStatus(uiValue == 0);
            break;
        case CHVACEnums::CCM_EXPCOOL_CONFIG:
            m_pHVACAdaptor->setXpressCoolingPresenceStatus(uiValue != 0);
            break;
        case CHVACEnums::HUCCM_EXPCOOL_STATUS:
            m_pHVACAdaptor->setXpressCoolMode(uiValue != 0);
            break;
        case CHVACEnums::HUCCM_TEMP_PASS:
            m_pHVACAdaptor->setPassengerTemperature(static_cast<int>(uiValue));
            break;
        case CHVACEnums::HUCCM_TEMP_DRVR:
            m_pHVACAdaptor->setDriverTemperature(static_cast<int>(uiValue));
            break;
        case CHVACEnums::CCM_VARIANT_TYPE:
            m_pHVACAdaptor->setHvacZoneType(static_cast<CHVACEnums::EHVACZoneType>(uiValue));
            break;
        default:
            LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"%s, unhandled HVAC parameter %d",__FUNCTION__, eParameterEnum);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"HVAC adpator is NULL");
    }
}

CHVACEventHandler::~CHVACEventHandler()
{

}

void CHVACEventHandler::sltHVACInfoReceived()
{
    if(m_pHVACAdaptor)
    {
        m_pHVACAdaptor->fetchHVACvalues();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"HVAC adpator is NULL");
    }
}

void CHVACEventHandler::sltCcmUserInterventionParamChanged(uint8_t ucHuCcmParam)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC, "%s", __FUNCTION__);
    CHVACAdaptor::getInstance()->ccmUserInterventionParamChanged(static_cast<int>(ucHuCcmParam));
}

void CHVACEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);
    CHVACResourceImpl* hvacResource = static_cast<CHVACResourceImpl*>(ResourceFactory::getHVACResource());
    if (hvacResource)
    {
        // make the signal and slot connection
        CHVACEventProvider* hvacEventProvider = hvacResource->getHVACEventProvider();
        if(hvacEventProvider)
		{
            connect(hvacEventProvider, &CHVACEventProvider::sigHVACParamUpdate,                 this, &CHVACEventHandler::sltHVACParamUpdate);
            connect(hvacEventProvider, &CHVACEventProvider::sigHVACInfoReceived,                this, &CHVACEventHandler::sltHVACInfoReceived);
            connect(hvacEventProvider, &CHVACEventProvider::sigCcmUserInterventionParamChanged, this, &CHVACEventHandler::sltCcmUserInterventionParamChanged);
		}
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"Resource returned as null from ResourceFactory");
    }

}

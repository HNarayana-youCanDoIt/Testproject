/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHVACEventProvider.cpp
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CHVACEventProvider, class to propogate events for resource layer to the HVAC Application layer
*/

#include "CHVACEventProvider.h"
#include "logging.h"

CHVACEventProvider::CHVACEventProvider(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);
}

CHVACEventProvider::~CHVACEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);
}

void CHVACEventProvider::HVACInfoReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);
    emit sigHVACInfoReceived();
}

void CHVACEventProvider::ccmUserInterventionParamChanged(uint8_t ucHuCcmParam)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s", __FUNCTION__);
    emit sigCcmUserInterventionParamChanged(ucHuCcmParam);
}

void CHVACEventProvider::HVACParamUpdate(const CcmPresTypes::eHuCcmParam& eParameterEnum , const uint16_t& uiValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HVAC,__FUNCTION__);
    emit sigHVACParamUpdate((int)eParameterEnum, uiValue);
}

/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CPowerModeEventHandler.cpp
 * @ingroup         HMIComponent
 * @author          Prashantkumar Raut
 * CPowerModeEventHandler - This class has the slots for all the Signals sent by CPowerModeEventProvider
 * which informs PowerMode Adaptor about PowerMode Resource Events
 */

#include <CHMIMain.h>
#include <ResourceFactory.hpp>
#include "CPowerModeAdaptor.h"
#include "CPowerModeEventHandler.h"
#include "CPowerModeEnums.h"
#include "PowerModeResource/implementations/CPowerModeResourceImpl.h"

CPowerModeEventHandler::CPowerModeEventHandler(QObject *parent) : QObject(parent), m_ePowerMode( CPowerModeEnums::VPM_UNKNOWN)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
    connectSignals();
}

CPowerModeEventHandler::~CPowerModeEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
}

void CPowerModeEventHandler::sltPowerModeEvent(QString m_mode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s : power mode : %s ", __FUNCTION__,m_mode.toStdString().c_str() );
    CPowerModeAdaptor::getInstance().sltPowerModeEvent(m_mode);
}

void CPowerModeEventHandler::sltNSMNodeStateEvent(int iNsmNodeState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s : nsm node state : %d ", __FUNCTION__, iNsmNodeState);
    CPowerModeAdaptor::getInstance().sltNSMNodeStateEvent(iNsmNodeState);
}

void CPowerModeEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
    CPowerModeResourceImpl* powerModeResource = static_cast<CPowerModeResourceImpl*>(ResourceFactory::getPowerModeResource());
    if (powerModeResource)
    {
        CPowerModeEventProvider* powerModeEventProvider = powerModeResource->getPowerModeEventProvider();
        connect(powerModeEventProvider, SIGNAL(sigUpdatePowerMode(QString)), this, SLOT(sltPowerModeEvent(QString)), Qt::QueuedConnection);
        connect(powerModeEventProvider, SIGNAL(sigUpdateNSMNodeState(int)),this , SLOT(sltNSMNodeStateEvent(int)), Qt::QueuedConnection);
        connect(powerModeEventProvider, SIGNAL(sigUpdateOneHourExpiryState(bool)), this, SLOT(sltUpdateOneHourExpiryState(bool)), Qt::QueuedConnection);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"powerModeResource null");
    }
}

void CPowerModeEventHandler::sltUpdateOneHourExpiryState(bool bOneHourExpiryState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: bOneHourExpiryState: %d", __FUNCTION__, bOneHourExpiryState);
    CPowerModeAdaptor::getInstance().updateOneHourExpiryState(bOneHourExpiryState);
}

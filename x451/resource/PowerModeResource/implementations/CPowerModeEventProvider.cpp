/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CPowerModeEventProvider.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CPowerModeEventProvider, Class to send signals to PowerMode on NSMPress Resource events
*/

#include "CPowerModeEventProvider.h"
#include "logging.h"
#include "qdebug.h"

CPowerModeEventProvider::CPowerModeEventProvider(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
}

CPowerModeEventProvider::~CPowerModeEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
}


void CPowerModeEventProvider::updatePowerMode(std::string  m_strMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,__FUNCTION__);
    emit sigUpdatePowerMode(QString::fromStdString(m_strMode));
}

void CPowerModeEventProvider::updateNSMNodeState(int iNsmNodeState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE,"%s",__FUNCTION__);
    emit sigUpdateNSMNodeState(iNsmNodeState);
}

void CPowerModeEventProvider::updateOneHourExpiryState(bool bOneHourExpiryState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POWER_MODE, "%s: bOneHourExpiryState: %d", __FUNCTION__, bOneHourExpiryState);
    emit sigUpdateOneHourExpiryState(bOneHourExpiryState);
}

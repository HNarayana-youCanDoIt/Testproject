/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CSoftwareUpdateEventProvider.cpp
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* CSoftwareUpdateEventProvider, Class to send signals to SoftwareUpdateHandler on Software Update Resource events
*/


#include "CSoftwareUpdateEventProvider.h"
#include "logging.h"

CSoftwareUpdateEventProvider::CSoftwareUpdateEventProvider(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
}

CSoftwareUpdateEventProvider::~CSoftwareUpdateEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
}

void CSoftwareUpdateEventProvider::updateSwAvailabilityStatus(bool swUpdateAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    emit sigSWUpdateAvailable(swUpdateAvailability);
}

void CSoftwareUpdateEventProvider::updateSoftware()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    emit sigUpdateSoftware();
}

void CSoftwareUpdateEventProvider::updateError(uint type)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    emit sigUpdateError(type);
}

void CSoftwareUpdateEventProvider::updateSwAvailability(uint type)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    emit sigUpdateSwAvailability(type);
}

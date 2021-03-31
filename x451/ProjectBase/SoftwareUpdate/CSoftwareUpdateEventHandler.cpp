/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CSoftwareUpdateEventHandler.cpp
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* @class        CSoftwareUpdateEventHandler: Class has the slots for all the Signals sent by CSoftwareUpdateEventHandler
*                                   which informs Software Update Adaptor about Software Update Resource Events
*/

#include "CSoftwareUpdateEventHandler.h"
#include "CSoftwareUpdateAdaptor.h"
#include "HMIIncludes.h"
#include "SoftwareUpdateResource/implementations/CSoftwareUpdateResourceImpl.h"
#include <ResourceFactory.hpp>

CSoftwareUpdateEventHandler::CSoftwareUpdateEventHandler(QObject *parent) : QObject(parent),
    m_pSoftwareUpdateAdaptor(CSoftwareUpdateAdaptor::getInstance())
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    connectSignals();
}

void CSoftwareUpdateEventHandler::sltSWUpdateAvailable(bool swUpdateAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    if(m_pSoftwareUpdateAdaptor)
    {
        m_pSoftwareUpdateAdaptor->setSwUpdateAvailability(swUpdateAvailability);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_pSoftwareUpdateAdaptor is null");
    }
}

void CSoftwareUpdateEventHandler::sltUpdateSoftware()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    if(m_pSoftwareUpdateAdaptor)
    {
        m_pSoftwareUpdateAdaptor->swISOListReceived();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_pSoftwareUpdateAdaptor is null");
    }

    CHMIMain::getSM()->getSCI_SoftwareUpdate()->raise_evSoftwareSelectActivated();
}

void CSoftwareUpdateEventHandler::sltUpdateError(uint uiSwUpdateError)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    if(m_pSoftwareUpdateAdaptor)
    {
        m_pSoftwareUpdateAdaptor->invShowErrorMessage(uiSwUpdateError);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_pSoftwareUpdateAdaptor is null");
    }
}

void CSoftwareUpdateEventHandler::sltUpdateSwAvailability(uint uiSwAvailabilityType )
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    if(m_pSoftwareUpdateAdaptor)
    {
        m_pSoftwareUpdateAdaptor->showAvailabilityErrorMessage(uiSwAvailabilityType );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_pSoftwareUpdateAdaptor is null");
    }
}
CSoftwareUpdateEventHandler::~CSoftwareUpdateEventHandler()
{
}

void CSoftwareUpdateEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    CSoftwareUpdateResourceImpl* swUpdateResource = static_cast<CSoftwareUpdateResourceImpl*>(ResourceFactory::getSoftwareUpdateResource());
    if (swUpdateResource)
    {
        // make the signal and slot connection
        CSoftwareUpdateEventProvider* swUpdateEventProvider = swUpdateResource->getSoftwareUpdateEventProvider();
        connect(swUpdateEventProvider, SIGNAL(sigSWUpdateAvailable(bool)), this, SLOT(sltSWUpdateAvailable(bool)));
        connect(swUpdateEventProvider, SIGNAL(sigUpdateSoftware()), this, SLOT(sltUpdateSoftware()));
        connect(swUpdateEventProvider, SIGNAL(sigUpdateError(uint)), this, SLOT(sltUpdateError(uint)));
        connect(swUpdateEventProvider, SIGNAL(sigUpdateSwAvailability(uint)), this, SLOT(sltUpdateSwAvailability(uint)));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"Resource returns as null from ResourceFactory");
    }

}

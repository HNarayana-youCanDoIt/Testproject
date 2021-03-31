/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDiagnosticAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Manali Patil
 * CDiagnosticAdaptor, an Adaptor for Diagnostic module,
 * CDiagnosticAdaptor used to communicate between QML and Resource Layer.
 */

#include "CDiagnosticAdaptor.h"
#include "ResourceFactory.hpp"
#include "DiagnosticResource/interfaces/IDiagnosticResource.h"
#include "HMIIncludes.h"
#include <CFramework.h>
#include <list>

CDiagnosticAdaptor* CDiagnosticAdaptor::m_pDiagnosticAdaptor = nullptr;


CDiagnosticAdaptor::CDiagnosticAdaptor(QObject *pParent) : QObject(pParent)
  , m_pDiagnosticResource(ResourceFactory::getDiagnosticResource())
  , m_eAntennaConnectionStatus(CDiagnosticEnum::INVALID)
  , m_eSWCConnectionStatus(CDiagnosticEnum::INVALID)
  , m_eMICConnectionStatus(CDiagnosticEnum::INVALID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppDiagnosticAdaptor", this);
    CDiagnosticEnum::registerDiagnosticEnumsToQML();
    if(m_pDiagnosticResource)
    {
        setAntennaConnectionStatus(static_cast<CDiagnosticEnum::EConnectionStatus>(m_pDiagnosticResource->getDiagAmFmAntennaConnectionStatusValue()));
        setMICConnectionStatus(static_cast<CDiagnosticEnum::EConnectionStatus>(m_pDiagnosticResource->getDiagMICConnectionStatusValue()));
        setSWCConnectionStatus(static_cast<CDiagnosticEnum::EConnectionStatus>(m_pDiagnosticResource->getDiagSWCConnectionStatusValue()));
    }
}

CDiagnosticAdaptor::~CDiagnosticAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);

    if(m_pDiagnosticAdaptor)
    {
        delete m_pDiagnosticAdaptor;
        m_pDiagnosticAdaptor = nullptr;
    }
}

CDiagnosticAdaptor* CDiagnosticAdaptor::getInstance()
{
    if(nullptr == m_pDiagnosticAdaptor)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, __FUNCTION__);
        m_pDiagnosticAdaptor = new CDiagnosticAdaptor();
    }
    return m_pDiagnosticAdaptor;
}

void CDiagnosticAdaptor::setAntennaConnectionStatus(CDiagnosticEnum::EConnectionStatus eAntennaConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    if(m_eAntennaConnectionStatus != eAntennaConnectionStatus)
    {
        m_eAntennaConnectionStatus = eAntennaConnectionStatus;
        emit sigAntennaConnectionStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC,"m_eAntennaConnectionStatus unchanged");
    }
}

void CDiagnosticAdaptor::setSWCConnectionStatus(CDiagnosticEnum::EConnectionStatus eSWCConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    if(m_eSWCConnectionStatus != eSWCConnectionStatus)
    {
        m_eSWCConnectionStatus = eSWCConnectionStatus;
        emit sigSWCConnectionStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC,"m_eSWCConnectionStatus unchanged");
    }
}

void CDiagnosticAdaptor::setMICConnectionStatus(CDiagnosticEnum::EConnectionStatus eMICConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    if(m_eMICConnectionStatus != eMICConnectionStatus)
    {
        m_eMICConnectionStatus = eMICConnectionStatus;
        emit sigMICConnectionStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC,"m_eMICConnectionStatus unchanged");
    }
}

CDiagnosticEnum::EConnectionStatus CDiagnosticAdaptor::antennaConnectionStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    return m_eAntennaConnectionStatus;
}

CDiagnosticEnum::EConnectionStatus CDiagnosticAdaptor::swcConnectionStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    return m_eSWCConnectionStatus;
}

CDiagnosticEnum::EConnectionStatus CDiagnosticAdaptor::micConnectionStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DIAGNOSTIC, "%s", __FUNCTION__);
    return m_eMICConnectionStatus;
}

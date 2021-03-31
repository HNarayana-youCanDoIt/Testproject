/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDriveNextApplication.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextApplication, an Application for DriveNext module,
 * CDriveNextApplication act as mediator between QML and State-machine.
 */

#include "HMIIncludes.h"
#include "logging.h"
#include "ResourceFactory.hpp"

#include "CDriveNextApplication.h"
#include "CDriveNextAdaptor.h"
#include "CDriveNextSM.h"
#include "CDriveNextEventHandler.h"


CDriveNextApplication* CDriveNextApplication::m_pInstance = nullptr;
///////////////////////////////////////////////////////////////////////////////
// DriveNext related functions
///////////////////////////////////////////////////////////////////////////////
CDriveNextApplication::CDriveNextApplication(QQuickItem* parent)
    :CBaseApplication(parent)
    ,m_spDriveNextAdaptor(QSharedPointer<CDriveNextAdaptor>(new CDriveNextAdaptor()))
    ,mpDriveNextDataEventHandler(new CDriveNextEventHandler())
    ,mpDriveNextSM(new CDriveNextSM(*this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    mfw.setContextProperty("cppDriveNextApplication",this);
    m_pInstance = this;
}
//____________________________________________________________________________
CDriveNextApplication::~CDriveNextApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    if (m_spDriveNextAdaptor)
    {
        m_spDriveNextAdaptor.reset();
        m_spDriveNextAdaptor = nullptr;
    }
    else
    {
        //// Do Nothing
    }

    if (mpDriveNextDataEventHandler)
    {
        delete mpDriveNextDataEventHandler;
        mpDriveNextDataEventHandler = nullptr;
    }
    else
    {
        //// Do Nothing
    }

    if (mpDriveNextSM)
    {
        delete mpDriveNextSM;
        mpDriveNextSM = nullptr;
    }
    else
    {
        //// Do Nothing
    }
    m_pInstance = nullptr;
}
//____________________________________________________________________________
CDriveNextAdaptor* CDriveNextApplication::getDriveNextAdaptor()
{
    CDriveNextAdaptor* _instanceForAdaptor =nullptr;
    if (nullptr != m_pInstance)
    {
        if (m_pInstance->m_spDriveNextAdaptor)
        {
            _instanceForAdaptor = m_pInstance->m_spDriveNextAdaptor.data();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s m_spDriveNextAdaptor not holding any reference", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s CDriveNextApplication not created", __FUNCTION__);
    }
    return _instanceForAdaptor;
}
///////////////////////////////////////////////////////////////////////////////
// CBaseApplication related functions
///////////////////////////////////////////////////////////////////////////////
void CDriveNextApplication::onCreated(QQuickItem *rootObject)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);
    Q_UNUSED(rootObject);
}
//____________________________________________________________________________
void CDriveNextApplication::raiseSMEvent(const QString & name,const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, name=%s , data=%s", __FUNCTION__, name.toStdString().c_str(), data.toString().toStdString().c_str());

    if ("ScnDriveNextTripsScreen" == name)
    {
        if ("Details" == data)
        {
            CHMIMain::getSM()->getSCI_DriveNext()->raise_evDriveNextDetailsActivated();
        }
        else
        {
            ////handle other Trip Screen events
        }
    }
    else if ("ScnDriveNextPerformanceBreakupScreen" == name)
    {
        ////handle Performance Breakup Screen events
    }
    else
    {
        ////handle other screen events
    }
}
//____________________________________________________________________________

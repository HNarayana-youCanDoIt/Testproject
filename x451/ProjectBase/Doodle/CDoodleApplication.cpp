/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDoodleApplication.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleApplication, an Application for Doodle module,
 * CDoodleApplication act as mediator between QML and State-machine.
 */

#include "HMIIncludes.h"
#include "logging.h"
#include "ResourceFactory.hpp"

#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"
#include "CDoodleSM.h"
#include "CDoodleEventHandler.h"


CDoodleApplication* CDoodleApplication::m_pInstance = nullptr;
///////////////////////////////////////////////////////////////////////////////
// Doodle related functions
///////////////////////////////////////////////////////////////////////////////
CDoodleApplication::CDoodleApplication(QQuickItem* parent)
    :CBaseApplication(parent)
    ,m_spDoodleAdaptor(QSharedPointer<CDoodleAdaptor>(new CDoodleAdaptor()))
    ,mpDoodleDataEventHandler(new CDoodleEventHandler())
    ,mpDoodleSM(new CDoodleSM(*this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    mfw.setContextProperty("cppDoodleApplication", this);
    m_pInstance = this;
}
//____________________________________________________________________________
CDoodleApplication::~CDoodleApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    if (m_spDoodleAdaptor)
    {
        m_spDoodleAdaptor.reset();
        m_spDoodleAdaptor = nullptr;
    }
    else
    {
        //// Do Nothing
    }

    if (mpDoodleDataEventHandler)
    {
        delete mpDoodleDataEventHandler;
        mpDoodleDataEventHandler = nullptr;
    }
    else
    {
        //// Do Nothing
    }

    if (mpDoodleSM)
    {
        delete mpDoodleSM;
        mpDoodleSM = nullptr;
    }
    else
    {
        //// Do Nothing
    }
    m_pInstance = nullptr;
}
//____________________________________________________________________________
CDoodleAdaptor* CDoodleApplication::getDoodleAdaptor()
{
    CDoodleAdaptor* _instanceForAdaptor =nullptr;
    if (nullptr != m_pInstance)
    {
        if (m_pInstance->m_spDoodleAdaptor)
        {
            _instanceForAdaptor = m_pInstance->m_spDoodleAdaptor.data();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s m_spDoodleAdaptor not holding any reference", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DOODLE, "%s CDoodleApplication not created", __FUNCTION__);
    }
    return _instanceForAdaptor;
}
///////////////////////////////////////////////////////////////////////////////
// CBaseApplication related functions
///////////////////////////////////////////////////////////////////////////////
void CDoodleApplication::onCreated(QQuickItem *rootObject)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    Q_UNUSED(rootObject);
}
//____________________________________________________________________________
void CDoodleApplication::raiseSMEvent(const QString & name,const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s, name=%s , data=%s", __FUNCTION__, name.toStdString().data(), data.toString().toStdString().data());
}
//____________________________________________________________________________

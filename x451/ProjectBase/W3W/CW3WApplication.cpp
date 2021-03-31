/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CW3WApplication.cpp
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CW3WApplication, an Application for W3W module,
 * CW3WApplication act as mediator between QML and State-machine.
 */

#include "HMIIncludes.h"
#include "logging.h"
#include "ResourceFactory.hpp"

#include "CW3WApplication.h"
#include "CW3WAdaptor.h"
#include "CW3WSM.h"
#include "CW3WEventHandler.h"


CW3WApplication* CW3WApplication::m_pInstance = nullptr;

CW3WApplication::CW3WApplication(QQuickItem* parent)
    :CBaseApplication(parent)
    ,m_spW3WAdaptor(QSharedPointer<CW3WAdaptor>(new CW3WAdaptor()))
    ,mpW3WDataEventHandler(new CW3WEventHandler())
    ,mpW3WSM(new CW3WSM(*this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    mfw.setContextProperty("cppW3WApplication",this);
    m_pInstance = this;
}

CW3WApplication::~CW3WApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    if (m_spW3WAdaptor)
    {
        m_spW3WAdaptor.reset();
        m_spW3WAdaptor = nullptr;
    }
    else
    {
        // Do Nothing
    }

    if (mpW3WDataEventHandler)
    {
        delete mpW3WDataEventHandler;
        mpW3WDataEventHandler = nullptr;
    }
    else
    {
        // Do Nothing
    }

    if (mpW3WSM)
    {
        delete mpW3WSM;
        mpW3WSM = nullptr;
    }
    else
    {
        // Do Nothing
    }
    m_pInstance = nullptr;
}

CW3WAdaptor* CW3WApplication::getW3WAdaptor()
{
    CW3WAdaptor* _instanceForAdaptor =nullptr;
    if (nullptr != m_pInstance)
    {
        if (m_pInstance->m_spW3WAdaptor)
        {
            _instanceForAdaptor = m_pInstance->m_spW3WAdaptor.data();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_W3W, "%s m_spW3WAdaptor not holding any reference", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_W3W, "%s CW3WApplication not created", __FUNCTION__);
    }
    return _instanceForAdaptor;
}

void CW3WApplication::onCreated(QQuickItem *rootObject)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    Q_UNUSED(rootObject);
}

void CW3WApplication::raiseSMEvent(const QString & name,const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, name=%s , data=%s", __FUNCTION__, name.toStdString().c_str(), data.toString().toStdString().c_str());

    if ("LaunchW3WAddressSuggestionScreen" == name)
    {
        CHMIMain::getSM()->getSCI_W3w()->raise_evW3WAddressSuggestionActivated();
    }
    else if ("LaunchW3WPhoneBrowseScreen" == name)
    {
        CHMIMain::getSM()->getSCI_W3w()->raise_evW3WPhoneBrowseActivated();
    }
    else if ("LaunchW3WFavoritesScreen" == name)
    {
        CHMIMain::getSM()->getSCI_W3w()->raise_evW3WFavoritesActivated();
    }
    else if ("LaunchW3WRecentScreen" == name)
    {
        CHMIMain::getSM()->getSCI_W3w()->raise_evW3WRecentActivated();
    }
    else if ("LaunchW3WSetupScreen" == name)
    {
        CHMIMain::getSM()->getSCI_W3w()->raise_evW3WSetupActivated();
    }
    else if ("LaunchW3WAboutScreen" == name)
    {
        CHMIMain::getSM()->getSCI_W3w()->raise_evW3WAboutActivated();
    }
    else if ("LaunchW3WEditLabelScreen" == name)
    {
        CHMIMain::getSM()->getSCI_W3w()->raise_evW3WEditLabelActivated();
    }
    else if ("LaunchW3WVideoViewerScreen" == name)
    {
        CHMIMain::getSM()->getSCI_W3w()->raise_evW3WVideoViewerActivated();
    }
    else
    {
        //Do nothing
    }
}

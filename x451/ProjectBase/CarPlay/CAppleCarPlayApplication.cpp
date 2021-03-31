/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlayApplication.cpp
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition of all functions of CAppleCarPlayApplication
* class of AppleCarPlay.
*/

#include "CAppleCarPlayApplication.h"
#include "CAppleCarPlaySM.h"
#include "CAppleCarPlayAdaptor.h"
#include "CAudioAdaptor.h"
#include "CAppleCarPlayEventHandler.h"

CAppleCarPlayApplication::CAppleCarPlayApplication(QQuickItem *pParent)
    : CBaseApplication(pParent),
      m_pAppleCarPlaySM(new CAppleCarPlaySM(this)),
      m_pAppleCarPlayEventHandler(new CAppleCarPlayEventHandler(this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, __FUNCTION__);

    mfw.setContextProperty("cppAppleCarPlayApp",this);
}

CAppleCarPlayApplication::~CAppleCarPlayApplication()
{
    if (m_pAppleCarPlaySM)
    {
        delete m_pAppleCarPlaySM;
        m_pAppleCarPlaySM = nullptr;
    }
}

void CAppleCarPlayApplication::onCreated(QQuickItem *pRootObject)
{
    Q_UNUSED(pRootObject)
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CAppleCarPlayApplication::raiseSMEvent(const QString &name, const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: name: %s , data: %d", __FUNCTION__, name.toStdString().c_str(), data.toInt());
}

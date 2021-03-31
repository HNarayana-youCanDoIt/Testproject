/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoApplication.cpp
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition of all functions of CAndroidAutoApplication
* class of AndroidAuto.
*/

#include "CAndroidAutoApplication.h"
#include "CAndroidAutoSM.h"
#include "CAndroidAutoAdaptor.h"
#include "CAudioAdaptor.h"
#include "CAndroidAutoEventHandler.h"

CAndroidAutoApplication::CAndroidAutoApplication(QQuickItem *pParent)
    : CBaseApplication(pParent),
      m_pAndroidAutoSM(new CAndroidAutoSM(this)),
      m_pAndroidAutoEventHandler(new CAndroidAutoEventHandler(this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, __FUNCTION__);

    mfw.setContextProperty("cppAndroidAutoApp",this);
}

CAndroidAutoApplication::~CAndroidAutoApplication()
{
    if (m_pAndroidAutoSM)
    {
        delete m_pAndroidAutoSM;
        m_pAndroidAutoSM = nullptr;
    }
}

void CAndroidAutoApplication::onCreated(QQuickItem *pRootObject)
{
    Q_UNUSED(pRootObject)
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CAndroidAutoApplication::raiseSMEvent(const QString &name, const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: name: %s , data: %d", __FUNCTION__, name.toStdString().c_str(), data.toInt());
}

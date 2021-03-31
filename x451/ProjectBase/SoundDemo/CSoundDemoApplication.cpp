/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          SoundDemoApplication.h
 * @ingroup       HMIComponent
 * @author        Guru Alingal
 * @brief         This file contains SoundDemoApplication class that act as a mediator between QML and state machine.
 */


#include "CSoundDemoApplication.h"
#include "CSoundDemoSM.h"
#include "CSoundDemoAdaptor.h"
#include "logging.h"

CSoundDemoApplication::CSoundDemoApplication(QQuickItem *pParent)
    : CBaseApplication(pParent),
      m_pSoundDemoSM(new CSoundDemoSM(this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    mfw.setContextProperty("cppSoundDemoApp", this);
    mfw.setContextProperty("cppSoundDemoAdaptor", CSoundDemoAdaptor::getInstance());
}

CSoundDemoApplication::~CSoundDemoApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);

    if(m_pSoundDemoSM)
    {
        delete m_pSoundDemoSM;
        m_pSoundDemoSM = nullptr;
    }
}

void CSoundDemoApplication::qmlLog(QString strLog)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO,"QML_LOG: %s", strLog.toUtf8().data());
}

void CSoundDemoApplication::onCreated(QQuickItem* pRootObject)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    Q_UNUSED(pRootObject);
}

void CSoundDemoApplication::loadScreen(QString strQmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s: qml file path is - %s", __FUNCTION__, strQmlFilePath.toStdString().c_str());
    CBaseApplication::loadScreen(strQmlFilePath);
}

void CSoundDemoApplication::raiseSMEvent(const QString& strName, const QVariant& objData)
{
    Q_UNUSED(objData);
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s: name is: %s", __FUNCTION__, strName.toStdString().c_str());

    CBaseApplication::raiseSMEvent(strName, objData);
}

void CSoundDemoApplication::handleFailSafeScenario()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    QTimer::singleShot(50, this, SLOT(sltProcessAutoBack()));
}

void CSoundDemoApplication::sltProcessAutoBack()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__)
    CHMIMain::getSM()->raise_evBackPressed();
}


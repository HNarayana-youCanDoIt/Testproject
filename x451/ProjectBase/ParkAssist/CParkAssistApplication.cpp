/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistApplication.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CParkAssistApplication.h, park assist module application source file, contains all the functionality related to park assist module
 *          creates instances for CParkAssistEventHandler & CParkAssistSM and raises events SM
 */

#include "CParkAssistApplication.h"
#include "CParkAssistSM.h"
#include "ParkAssist/CParkAssistAdaptor.h"
#include "ParkAssist/CParkAssistEventHandler.h"

CParkAssistApplication::CParkAssistApplication(QQuickItem* parent)
    :CBaseApplication(parent),
      m_pParkAssistSM(new CParkAssistSM(*this)),
      m_pParkAssistAdaptor(CParkAssistAdaptor::getInstance()),
      m_pParkAssistEventHandler(new CParkAssistEventHandler())
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);
    mfw.setContextProperty("cppParkAssistApp",this);
}

CParkAssistApplication::~CParkAssistApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);

    if (m_pParkAssistSM)
    {
        delete m_pParkAssistSM;
        m_pParkAssistSM = nullptr;
    }
    if (m_pParkAssistEventHandler)
    {
        delete m_pParkAssistEventHandler;
        m_pParkAssistEventHandler = nullptr;
    }
}

void CParkAssistApplication::onCreated(QQuickItem *rootObject)
{
    Q_UNUSED(rootObject);
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s", __FUNCTION__);
}

void CParkAssistApplication::displayScreenPdcRvc()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s", __FUNCTION__);

    if( (CParkAssistEnum::PARK_ASSIST_VARIANT_PDC_RVC == CParkAssistAdaptor::getInstance()->parkAssistVariant()) ||
            (CParkAssistEnum::PARK_ASSIST_VARIANT_RVC == CParkAssistAdaptor::getInstance()->parkAssistVariant()) )   /** PDC+RVC & RVC */
    {
        loadScreen("qrc:/QML/ParkAssist/RVCScreen.qml");
        /* The delay is introduced to have a seamless transition from fb0 to fb1. The timer value was finalized after proper testing */
        QTimer::singleShot(200,this,SLOT(sltSetHMINotification()));
    }
    else if(CParkAssistEnum::PARK_ASSIST_VARIANT_PDC == CParkAssistAdaptor::getInstance()->parkAssistVariant())  /** PDC */
    {
        loadScreen("qrc:/QML/ParkAssist/PDCScreen.qml");
        /* The delay is introduced to have a seamless transition from fb0 to fb1. The timer value was finalized after proper testing */
        QTimer::singleShot(200,this,SLOT(sltSetHMINotification()));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST, "%s: In else, Park assist variant: %d", __FUNCTION__, CParkAssistAdaptor::getInstance()->parkAssistVariant());
    }
}

void CParkAssistApplication::sltSetHMINotification()
{
    // Inform RVCApp hmi is up and running
    LOG_INFO(Log::e_LOG_CONTEXT_PARKASSIST,"%s", __FUNCTION__);
    CParkAssistAdaptor::getInstance()->setHmiNotificationAttribute(true);
}

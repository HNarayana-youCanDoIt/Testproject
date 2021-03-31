/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CTunerApplication.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * CTunerApplication, This is an Application class for tuner module which communicates with project framework.
 * It also load tuner module's QML.
**/

#include "CTunerApplication.h"
#include "CTunerAdaptor.h"
#include "CTunerEventHandler.h"
#include "CTunerSM.h"
#include "HMIIncludes.h"

CTunerApplication::CTunerApplication(QQuickItem* parent)
    :CBaseApplication(parent),
      m_pTunerAdaptor(CTunerAdaptor::getInstance()),
      m_pTunerSM(new CTunerSM(*this)),
      m_pTunerEventHandler(new CTunerEventHandler())
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "TunerBaseScreen::TunerBaseScreen");
    CHMIMain::getSM()->setSCI_Tuner_OCB(m_pTunerSM);
    mfw.setContextProperty("cppTunerApp",this);
}

CTunerApplication::~CTunerApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    if(m_pTunerEventHandler)
        delete m_pTunerEventHandler;
    if(m_pTunerSM)
        delete m_pTunerSM;
}

void CTunerApplication::onCreated(QQuickItem *rootObject)
{
    Q_UNUSED(rootObject);
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
}

void CTunerApplication::loadScreen(QString qmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    CBaseApplication::loadScreen(qmlFilePath);
}

void CTunerApplication::raiseSMEvent(const QString & name,const QVariant & data)
{
    Q_UNUSED(name);
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER, "%s", __FUNCTION__);
    if(CTunerEnums::TUNER_SCREEN_OPTION == data)
    {
        CHMIMain::getSM()->getSCI_Tuner()->raise_evTunerOptionScreen();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, incorrect data : %d", __FUNCTION__, data.toInt());
    }
}

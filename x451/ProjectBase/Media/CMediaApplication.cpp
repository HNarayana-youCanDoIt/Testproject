/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaApplication.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CMediaApplication, Class to load Media QML files
*/

#include "CMediaApplication.h"
#include "CMediaSM.h"
#include "CMediaEventHandler.h"
#include "CMediaAdaptor.h"
#include "HMIIncludes.h"

CMediaApplication::CMediaApplication(QQuickItem* parent)
    :CBaseApplication(parent),
      mMediaAdaptor(CMediaAdaptor::getInstance()),
      m_pMediaSM(new CMediaSM(*this)),
      m_pMediaEventHandler(new CMediaEventHandler())
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    CHMIMain::getSM()->setSCI_Media_OCB(m_pMediaSM);
    mfw.setContextProperty("cppMediaApp",this);
}

CMediaApplication::~CMediaApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    if (m_pMediaEventHandler)
        delete m_pMediaEventHandler;
    if (m_pMediaSM)
        delete m_pMediaSM;
}

void CMediaApplication::onCreated(QQuickItem *rootObject)
{
    Q_UNUSED(rootObject);
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
}

void CMediaApplication::loadScreen(QString qmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN,__FUNCTION__);
    CBaseApplication::loadScreen(qmlFilePath);
}

void CMediaApplication::raiseSMEvent(const QString & name,const QVariant & data)
{
    Q_UNUSED(name);
    //FixMe: Use Enums insted of Strings in data
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    if(data == "Browse")
    {
        CHMIMain::getSM()->getSCI_Media()->raise_evMediaBrowse();
    }
    else if(data == "Back")
    {
        CHMIMain::getSM()->raise_evBackPressed();
    }
    else if(data == "evNowPlayingDataAvailable")
    {
        CHMIMain::getSM()->getSCI_Media()->raise_evNowPlayingAvailable();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, "%s - Request to raise SM event not handled",__FUNCTION__);
    }
}


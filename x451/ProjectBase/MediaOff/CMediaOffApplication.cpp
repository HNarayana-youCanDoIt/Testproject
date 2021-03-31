/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CMediaOffApplication.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CMediaOffApplication, an Application for Media Off module,
 * CMediaOffApplication act as mediator between QML and Statemachine.
 */

#include "HMIIncludes.h"
#include "logging.h"
#include "ResourceFactory.hpp"

#include "CMediaOffApplication.h"
#include "CMediaOffAdaptor.h"
#include "CMediaOffSM.h"
#include "CMediaOffEventHandler.h"

///////////////////////////////////////////////////////////////////////////////
// MediaOff related functions
///////////////////////////////////////////////////////////////////////////////
CMediaOffApplication::CMediaOffApplication(QQuickItem* parent)
    :CBaseApplication(parent),
      mMediaOffAdaptor(CMediaOffAdaptor::getInstance()),
      mpMediaOffEventHandler(new CMediaOffEventHandler()),
      mpMediaOffSM(new CMediaOffSM(*this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
    mfw.setContextProperty("cppMediaOffApplication",this);
}
//____________________________________________________________________________
CMediaOffApplication::~CMediaOffApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
    if (mpMediaOffEventHandler)
    {
        delete mpMediaOffEventHandler;
        mpMediaOffEventHandler = null;
    }
    if (mpMediaOffSM)
    {
        delete mpMediaOffSM;
        mpMediaOffSM = null;
    }
}
///////////////////////////////////////////////////////////////////////////////
// CBaseApplication related functions
///////////////////////////////////////////////////////////////////////////////
void CMediaOffApplication::onCreated(QQuickItem *rootObject)
{
    Q_UNUSED(rootObject);
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
}
//____________________________________________________________________________
void CMediaOffApplication::raiseSMEvent(const QString & name,const QVariant & data)
{
    Q_UNUSED(name);
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF,__FUNCTION__);
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA_OFF, "CMediaOffApplication::raiseSMEvent %s", data.toString().toStdString().data() );
    if("MediaOffNavigate" == name)
    {
        switch (data.toInt())// FixMe: [NK] test purpose, shall be removed
        {
        case 0:
        {
            CHMIMain::getSM()->raise_evHomeActivated();
        }
            break;
        }
    }
    else if ("CmpClockTemplate.qml" == name)
    {
        if (("onClockDialRelease" == data.toString()) || ("onClockDialPressAndHold" == data.toString()))
        {
            CHMIMain::getSM()->getSCI_MediaOff()->raise_evMediaOffSetDate();
        }
        else
        {
            ////Do Nothing
        }
    }
    else
    {
        ////Do Nothing
    }
}
//____________________________________________________________________________

/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHomeApplication.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CHomeApplication, an Application for Home module,
 * CHomeApplication act as mediator between QML and Statemachine.
 */

#include "HMIIncludes.h"
#include "logging.h"
#include "ResourceFactory.hpp"

#include "CHomeApplication.h"
#include "CHomeAdaptor.h"
#include "CHomeSM.h"
#include "CHomeEventHandler.h"


///////////////////////////////////////////////////////////////////////////////
// Home related functions
///////////////////////////////////////////////////////////////////////////////
CHomeApplication::CHomeApplication(QQuickItem* parent)
    :CBaseApplication(parent),
      mHomeAdaptor(CHomeAdaptor::getInstance()),
      mpHomeDataEventHandler(new CHomeEventHandler()),
      mpHomeSM(new CHomeSM(*this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    mfw.setContextProperty("cppHomeApplication",this);

    // Doing this in-order to prefetch the qml during application startup
    mfw.getQMLScreen("qrc:/QML/Home/ScnHomeMain.qml",NULL);
}
//____________________________________________________________________________
CHomeApplication::~CHomeApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    if (mpHomeDataEventHandler)
    {
        delete mpHomeDataEventHandler;
    }
    if (mpHomeSM)
    {
        delete mpHomeSM;
    }
}
///////////////////////////////////////////////////////////////////////////////
// CBaseApplication related functions
///////////////////////////////////////////////////////////////////////////////
void CHomeApplication::onCreated(QQuickItem *rootObject)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    Q_UNUSED(rootObject);
}
//____________________________________________________________________________
void CHomeApplication::raiseSMEvent(const QString & name,const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s: name: %s , data: %d", __FUNCTION__, name.toStdString().c_str(), data.toInt());
    Q_UNUSED(data);
    if ("BackToHome" == name)
    {
            CHMIMain::getSM()->raise_evHomeActivated();
    }
}
//____________________________________________________________________________

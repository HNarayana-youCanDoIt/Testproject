/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDoodleEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * CDoodleEventProvider, This class propagates service signals to application layer.
 */
//________________________________________________________________________________________________
#include "logging.h"
#include "CDoodleEventProvider.h"

//________________________________________________________________________________________________
CDoodleEventProvider::CDoodleEventProvider(QObject *pParent) :
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
CDoodleEventProvider::~CDoodleEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CDoodleEventProvider::onProxyStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DOODLE, "%s", __FUNCTION__);
    emit sigProxyStatusChanged();
}
//________________________________________________________________________________________________

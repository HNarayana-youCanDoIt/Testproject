
/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionEventHandler.cpp
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionEventHandler: Class acts as the event handler for all the signals/events sent by CIntrospectionEventProvider
* which informs Introspection Adaptor about Introspection resource events
*/

#include "CIntrospectionEventHandler.h"
#include "HMIIncludes.h"
#include "IntrospectionStubResource/CIntrospectionStubResource.h"
#include <ResourceFactory.hpp>
#include "CIntrospectionAdaptor.h"

CIntrospectionEventHandler::CIntrospectionEventHandler(QObject *parent) : QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    connectSignals();
}

CIntrospectionEventHandler::~CIntrospectionEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
}

void CIntrospectionEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    CIntrospectionStubResource* pIntroResource = ResourceFactory::getIntrospectionStubResource();
    if (pIntroResource)
    {
        // make the signal and slot connection
        CIntrospectionEventProvider* pIntrospectEventProvider = pIntroResource->getIntrospectionStubEventProvider();
        if(pIntrospectEventProvider)
        {
            connect(pIntrospectEventProvider, SIGNAL(sigGetIntrospectionData(int, QString)), this, SLOT(sltGetIntrospectionData(int, QString)), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION," %s pIntrospectEventProvider is null",__FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION," %s Resource returned as null from ResourceFactory",__FUNCTION__);
    }
}

void CIntrospectionEventHandler::sltGetIntrospectionData(int iItemType, QString itemName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    CIntrospectionAdaptor::getInstance()->getIntrospectionData(iItemType, itemName);
}

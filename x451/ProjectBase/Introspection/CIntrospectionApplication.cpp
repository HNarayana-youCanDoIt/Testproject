/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionApplication.cpp
* @ingroup      HMIComponent
* @author       Gaurav Garg
 * CIntrospectionApplication, an Application for introspection module,
 * CIntrospectionApplication act as creator calls for the adaptor
*/

#include "CIntrospectionApplication.h"
#include "CIntrospectionAdaptor.h"
#include "CIntrospectionEventHandler.h"

CIntrospectionApplication::CIntrospectionApplication(QObject* parent): QObject(parent)
  ,m_pIntrospectionAdaptor(CIntrospectionAdaptor::getInstance())
  ,m_pIntrospectionEventHandler(new CIntrospectionEventHandler())
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION, __FUNCTION__);
}


CIntrospectionApplication::~CIntrospectionApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION, __FUNCTION__);
    if (m_pIntrospectionEventHandler)
    {
        delete m_pIntrospectionEventHandler;
    }
}

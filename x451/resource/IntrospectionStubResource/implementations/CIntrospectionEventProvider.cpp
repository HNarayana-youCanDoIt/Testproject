/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionEventProvider.cpp
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionEventProvider, class to propogate events from resource layer
*/

#include "CIntrospectionEventProvider.h"
#include "logging.h"

CIntrospectionEventProvider::CIntrospectionEventProvider(QObject *parent) : QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
}

CIntrospectionEventProvider::~CIntrospectionEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
}

void CIntrospectionEventProvider::getIntrospectionData(int iItemType, std::string itemName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    emit sigGetIntrospectionData(iItemType, QString::fromStdString(itemName));
}

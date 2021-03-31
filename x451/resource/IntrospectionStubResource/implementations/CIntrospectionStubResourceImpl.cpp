/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionStubResourceImpl.cpp
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionStubResourceImpl, Stub Resource Implementation for the Introspection Service module.
*/

#include "CIntrospectionStubResourceImpl.h"
#include "logging.h"

CIntrospectionStubResourceImpl::CIntrospectionStubResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    m_pIntroEventProvider = new CIntrospectionEventProvider();
    m_pInspectReplyVar = nullptr;
}

CIntrospectionStubResourceImpl::~CIntrospectionStubResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    if (m_pIntroEventProvider)
    {
        delete m_pIntroEventProvider;
        m_pIntroEventProvider = nullptr;
    }

    if (m_pInspectReplyVar)
    {
        m_pInspectReplyVar = nullptr;
    }
}

CIntrospectionEventProvider* CIntrospectionStubResourceImpl::getIntrospectionEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    return m_pIntroEventProvider;
}

void  CIntrospectionStubResourceImpl::inspectScreen(const std::shared_ptr<CommonAPI::ClientId> pClient, ::v0::com::harman::dcif::HMIIntrospectionTypes::ScreenItemType screenItemType, std::string itemName, inspectScreenReply_t pReply)
{
    CPP_UNUSED(pClient);
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    m_pInspectReplyVar = pReply;

    if(m_pIntroEventProvider)
    {
        m_pIntroEventProvider->getIntrospectionData(screenItemType.value_, itemName);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION," %s Introspection event provider is NULL", __FUNCTION__);
    }
}

void CIntrospectionStubResourceImpl::sendScreenInfo(const string& strScreenInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);

    HMIIntrospectionTypes::InspectionResponseCode m_InspectionStatus= HMIIntrospectionTypes::InspectionResponseCode::SUCCESS;


    if(m_pInspectReplyVar != nullptr)
    {
        m_pInspectReplyVar(m_InspectionStatus,strScreenInfo);
        m_pInspectReplyVar = nullptr;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION," %s Callback inspect failed",__FUNCTION__);
    }

}

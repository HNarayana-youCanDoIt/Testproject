/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CIntrospectionStubResource.cpp
* @ingroup      HMIComponent
* @author       Gaurav Garg
* CIntrospectionStubResource, Resource for the Introspection Service module.
*/

#include "CIntrospectionStubResource.h"

#include "logging.h"
#include <CommonAPI/CommonAPI.hpp>


CIntrospectionStubResource::CIntrospectionStubResource()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    /*
     * create the runtime
     */
    shared_ptr<CommonAPI::Runtime> pRunTime = CommonAPI::Runtime::get();

    if(pRunTime)
    {
        string strDomain = "local";
        string strConnectionInstance = "dbusConnection";
        string strInstanceName = "HMIServiceComponent.introspectionInstance";

        m_pIntrospectionStubResourceImpl = make_shared<CIntrospectionStubResourceImpl>();

        if(m_pIntrospectionStubResourceImpl)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION," %s stub loaded successfully" ,__FUNCTION__);
            pRunTime->registerService(strDomain, strInstanceName, m_pIntrospectionStubResourceImpl, strConnectionInstance);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION," %s Error: could not load stub",__FUNCTION__);

        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION," %s Error: could not load runtime",__FUNCTION__);
    }
}

CIntrospectionStubResource::~CIntrospectionStubResource()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
}

void CIntrospectionStubResource::setScreenChange(const string& strScreenName, EItemType eItemType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s setScreenChange: %s, eItemType:%d",__FUNCTION__,strScreenName.c_str(), static_cast<int>(eItemType));

    if(m_pIntrospectionStubResourceImpl)
    {

#if !defined(USE_SIMULATION_INTROSPECTION)
        switch(eItemType)
        {
        case EItemType::EN_ITEM_TYPE_SCREEN:
        {
            m_pIntrospectionStubResourceImpl->fireScreenChangeEvent(strScreenName);
            m_pIntrospectionStubResourceImpl->setTopScreenAttribute(strScreenName);
        }
            break;

        case EItemType::EN_ITEM_TYPE_DRAWER:
        {
            m_pIntrospectionStubResourceImpl->fireDrawerScreenChangeEvent(strScreenName);
            m_pIntrospectionStubResourceImpl->setDrawerTopScreenAttribute(strScreenName);
        }
            break;

        case EItemType::EN_ITEM_TYPE_POPUP:
        {
            m_pIntrospectionStubResourceImpl->firePopupScreenChangeEvent(strScreenName);
            m_pIntrospectionStubResourceImpl->setPopupTopScreenAttribute(strScreenName);
        }
            break;

        case EItemType::EN_ITEM_TYPE_OVERLAYS:
        {
            m_pIntrospectionStubResourceImpl->fireOverlayScreenChangeEvent(strScreenName);
            m_pIntrospectionStubResourceImpl->setOverlayTopScreenAttribute(strScreenName);
        }
            break;

        default:
            LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION, "%s Invalid value received", __FUNCTION__);
            break;
        }
#else
        //do nothing
#endif // defined(USE_SIMULATION_INTROSPECTION)

    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION," %s Error: m_pIntrospectionStubResourceImpl is null" ,__FUNCTION__);
    }
}

void CIntrospectionStubResource::sendScreenInfo(const string& strScreenInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    if(m_pIntrospectionStubResourceImpl)
    {
        m_pIntrospectionStubResourceImpl->sendScreenInfo(strScreenInfo);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s m_pIntroStubEventProvider is null ",__FUNCTION__);
    }
}

CIntrospectionEventProvider *CIntrospectionStubResource::getIntrospectionStubEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_INTROSPECTION,"%s",__FUNCTION__);
    CIntrospectionEventProvider* m_pIntroStubEventProvider = nullptr;
    if(m_pIntrospectionStubResourceImpl)
    {
        m_pIntroStubEventProvider =  m_pIntrospectionStubResourceImpl->getIntrospectionEventProvider();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_INTROSPECTION, " %s Error: could not find stub", __FUNCTION__);
    }
    return m_pIntroStubEventProvider;
}

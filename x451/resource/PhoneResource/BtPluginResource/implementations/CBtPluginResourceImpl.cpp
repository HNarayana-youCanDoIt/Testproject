/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CBtPluginResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CBtPluginResourceImpl class
 */

#include <ResourceDeploymentConfig.h>
#include <ResourceMaster.h>
#include "CBtPluginResourceImpl.h"
#include "logging.h"

CBtPluginResourceImpl::CBtPluginResourceImpl()
    : m_pBtPluginEventProvider(new CBtPluginEventProvider()),
      m_objBtPluginProxy(ResourceDeploymentConfig::getConfig().m_BtPressPlugin_Proxy.domain,
                         ResourceDeploymentConfig::getConfig().m_BtPressPlugin_Proxy.instance),
      m_bIsBtPluginProxyAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    subscribeBtPluginCb();
}

CBtPluginResourceImpl::~CBtPluginResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if (m_pBtPluginEventProvider)
    {
        delete m_pBtPluginEventProvider;
        m_pBtPluginEventProvider = NULL;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Bt plugin event provider is NULL", __FUNCTION__);
    }
}

CBtPluginEventProvider *CBtPluginResourceImpl::getBtPluginEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_pBtPluginEventProvider;
}

void CBtPluginResourceImpl::startTTSPlayAsyncReq(uint32_t uiPropmtId, string strMessageText)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: prompt id is: %d, message text is: %s", __FUNCTION__, uiPropmtId, strMessageText.c_str());
    if(m_bIsBtPluginProxyAvailable)
    {
        m_objBtPluginProxy->startTTSplayAsync(uiPropmtId, strMessageText,
                                              std::bind(&CBtPluginResourceImpl::startTTSPlayAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"bt plugin proxy not available");
    }
}

void CBtPluginResourceImpl::stopTTSPlayAsyncReq(uint32_t uiPropmtId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: prompt id is: %d", __FUNCTION__, uiPropmtId);
    if(m_bIsBtPluginProxyAvailable)
    {
        m_objBtPluginProxy->stopTTSplayAsync(uiPropmtId, std::bind(&CBtPluginResourceImpl::stopTTSPlayAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"bt plugin proxy not available");
    }
}

void CBtPluginResourceImpl::btPluginStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(eStatus == CommonAPI::AvailabilityStatus::AVAILABLE)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: proxy is available", __FUNCTION__);
        m_bIsBtPluginProxyAvailable = true;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: proxy is not available", __FUNCTION__);
        m_bIsBtPluginProxyAvailable = false;
    }
}

void CBtPluginResourceImpl::ttsPlayStateCb(UISSTypes::ePlayState eTTSPlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: TTS play state is: %d", __FUNCTION__, eTTSPlayState.value_);
    // Propagate the information to the phone application layer
    if (m_pBtPluginEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"update tts playstate status to upper layer");
        m_pBtPluginEventProvider->updateTTSPlayStateStatus(eTTSPlayState.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

void CBtPluginResourceImpl::startTTSPlayAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: CallStatus: %d, ErrorType: %d",
             __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);
}

void CBtPluginResourceImpl::stopTTSPlayAsyncCb(const CallStatus &eCallStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: CallStatus: %d, ErrorType: %d",
             __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);
}

void CBtPluginResourceImpl::subscribeBtPluginCb()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    SUBSCRIBE(m_objBtPluginProxy, getProxyStatusEvent(),                        &CBtPluginResourceImpl::btPluginStatusCb,   _1);
    SUBSCRIBE(m_objBtPluginProxy, getTtsPlayStateAttribute().getChangedEvent(), &CBtPluginResourceImpl::ttsPlayStateCb,     _1);
}

EMethodCallStatus CBtPluginResourceImpl::getMethodCallStatus(CallStatus eCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    EMethodCallStatus eMethodCallStatus = METHOD_CALL_STATUS_DEFAULT;
    switch(eCallStatus)
    {
    case CallStatus::SUCCESS:
        eMethodCallStatus = METHOD_CALL_STATUS_SUCCESS;
        break;
    case CallStatus::OUT_OF_MEMORY:
        eMethodCallStatus = METHOD_CALL_STATUS_OUT_OF_MEMORY;
        break;
    case CallStatus::NOT_AVAILABLE:
        eMethodCallStatus = METHOD_CALL_STATUS_NOT_AVAILABLE;
        break;
    case CallStatus::CONNECTION_FAILED:
        eMethodCallStatus = METHOD_CALL_STATUS_CONNECTION_FAILED;
        break;
    case CallStatus::REMOTE_ERROR:
        eMethodCallStatus = METHOD_CALL_STATUS_REMOTE_ERROR;
        break;
    case CallStatus::UNKNOWN:
        eMethodCallStatus = METHOD_CALL_STATUS_UNKNOWN;
        break;
    case CallStatus::INVALID_VALUE:
        eMethodCallStatus = METHOD_CALL_STATUS_INVALID_VALUE;
        break;
    case CallStatus::SUBSCRIPTION_REFUSED:
        eMethodCallStatus = METHOD_CALL_STATUS_SUBSCRIPTION_REFUSED;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value (%d) for call status passed",static_cast<int>(eCallStatus));
        break;
    }
    return eMethodCallStatus;
}

EMethodCallErrorType CBtPluginResourceImpl::getMethodCallErrorType(int iErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    EMethodCallErrorType eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_DEFAULT;
    switch(iErrorType)
    {
    case BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_SUCCESS;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_PENDING:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_PENDING;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_API_NOT_SUPPORTED:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_API_NOT_SUPPORTED;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_BAD_PARAMETER:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_BAD_PARAMETER;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_DEVICE_REMOVED:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_DEVICE_REMOVED;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_SYNC_NOT_COMPLETED:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_SYNC_NOT_COMPLETED;
        break;
    case BTPresTypes::eErrorType::ERROR_TYPE_FAILURE:
        eMethodCallErrorType = METHOD_CALL_ERROR_TYPE_FAILURE;
        break;
    case BTPresTypes::eErrorType::ERROR_EXCEEDED_MAX_ENTRY_LIMIT:
        eMethodCallErrorType = METHOD_CALL_ERROR_EXCEEDED_MAX_ENTRY_LIMIT;
        break;
    case BTPresTypes::eErrorType::ERROR_EXCEEDED_MAX_CHARACTER_LIMIT:
        eMethodCallErrorType = METHOD_CALL_ERROR_EXCEEDED_MAX_CHARACTER_LIMIT;
        break;
    case BTPresTypes::eErrorType::ERROR_REASON_NO_NETWORK_SERVICE:
        eMethodCallErrorType = METHOD_CALL_ERROR_REASON_NO_NETWORK_SERVICE;
        break;
    case BTPresTypes::eErrorType::ERROR_REASON_NETWORK_NOT_ALLOWED:
        eMethodCallErrorType = METHOD_CALL_ERROR_REASON_NETWORK_NOT_ALLOWED;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "wrong value (%d) for method call error type passed", iErrorType);
        break;
    }
    return eMethodCallErrorType;
}

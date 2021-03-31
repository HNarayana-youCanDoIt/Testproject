/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRStubResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CVRStubResourceImpl class
 */

#include "CVRStubResourceImpl.h"
#include "logging.h"

CVRStubResourceImpl::CVRStubResourceImpl()
    : m_pVREventProvider(new CVRStubEventProvider()),
      m_objSetScreenReply(nullptr),
      m_objShowContactReply(nullptr),
      m_objMediaFilterListShowReply(nullptr)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    setRequestState(EN_NO_REQUEST);
    m_vectPickList.clear();
    m_vectTeleprompterList.clear();
}

CVRStubResourceImpl::~CVRStubResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(m_pVREventProvider)
    {
        delete m_pVREventProvider;
        m_pVREventProvider = nullptr;
    }
}

CVRStubEventProvider *CVRStubResourceImpl::getVRStubEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    return m_pVREventProvider;
}

void CVRStubResourceImpl::sendVRResponse(EResponseType eResponseType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: response type is: %d, current request state is: %d", __FUNCTION__, static_cast<int>(eResponseType), m_eVRRequestState);
    switch(m_eVRRequestState)
    {
    case EN_REQUEST_SET_SCREEN:
    {
        if(m_objSetScreenReply != nullptr)
        {
            m_objSetScreenReply(getResponseType(eResponseType));
            setRequestState(EN_NO_REQUEST);
            m_objSetScreenReply = nullptr;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: set screen reply is null", __FUNCTION__);
        }
    }
        break;

    case EN_REQUEST_SHOW_CONTACT:
    {
        if(m_objShowContactReply != nullptr)
        {
            m_objShowContactReply(getResponseType(eResponseType));
            setRequestState(EN_NO_REQUEST);
            m_objShowContactReply   = nullptr;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: show contact reply is null", __FUNCTION__);
        }
    }
        break;

    case EN_REQUEST_MEDIA_FILTER_LIST_SHOW:
    {
        if(m_objMediaFilterListShowReply != nullptr)
        {
            m_objMediaFilterListShowReply(getResponseType(eResponseType));
            setRequestState(EN_NO_REQUEST);
            m_objMediaFilterListShowReply   = nullptr;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: media filter list show reply is null", __FUNCTION__);
        }
    }
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR request state not handled: %d", __FUNCTION__, static_cast<int>(m_eVRRequestState));
        break;
    }
}

void CVRStubResourceImpl::setScreen(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _strScreenName, setScreenReply_t _reply)
{
    int iHashCode = 0;
    if(_client)
    {
        iHashCode = static_cast<int>(_client->hashCode());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: _client is NULL", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: client hash code: %d, screen name: %s", __FUNCTION__, iHashCode, _strScreenName.c_str());

    m_objSetScreenReply = _reply;
    setRequestState(EN_REQUEST_SET_SCREEN);

    if (m_pVREventProvider)
    {
        m_pVREventProvider->setScreenRequest(_strScreenName);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s: VR event provider not created", __FUNCTION__);
    }
}

void CVRStubResourceImpl::showContact(const std::shared_ptr<CommonAPI::ClientId> _client, string _strDatabaseType, int32_t _iContactId, hmiVRStub::showContactReply_t _reply)
{
    int iHashCode = 0;
    if(_client)
    {
        iHashCode = static_cast<int>(_client->hashCode());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: _client is NULL", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: client hash code: %d, database type is: %s, contact id is: %d", __FUNCTION__, iHashCode, _strDatabaseType.c_str(), _iContactId);

    m_objShowContactReply   = _reply;
    setRequestState(EN_REQUEST_SHOW_CONTACT);

    if (m_pVREventProvider)
    {
        m_pVREventProvider->showContact(_strDatabaseType, _iContactId);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s: VR event provider not created", __FUNCTION__);
    }
}

void CVRStubResourceImpl::showTelePrompterList(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector<string> _strAryTelePrompterlist, hmiVRStub::showTelePrompterListReply_t _reply)
{
    int iHashCode = 0;
    if(_client)
    {
        iHashCode = static_cast<int>(_client->hashCode());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: _client is NULL", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: client hash code: %d", __FUNCTION__, iHashCode);

    m_vectTeleprompterList.clear();
    for(uint iIndex = 0; iIndex < _strAryTelePrompterlist.size(); iIndex++)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: teleprompter list item at index %d is: %s", __FUNCTION__, iIndex, _strAryTelePrompterlist.at(iIndex).c_str());
        m_vectTeleprompterList.push_back(_strAryTelePrompterlist.at(iIndex));
    }

    if (m_pVREventProvider)
    {
        m_pVREventProvider->showTeleprompterList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s: VR event provider not created", __FUNCTION__);
    }

    _reply(hmiVRTypes::EResponseType::EN_SUCCESS);
}

void CVRStubResourceImpl::showPickList(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector<string> _strAryPicklist, string _strContextTitle, hmiVRStub::showPickListReply_t _reply){
    CPP_UNUSED(_strContextTitle);
    int iHashCode = 0;
    if(_client)
    {
        iHashCode = static_cast<int>(_client->hashCode());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: _client is NULL", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: client hash code: %d", __FUNCTION__, iHashCode);

    m_vectPickList.clear();
    for(uint iIndex = 0; iIndex < _strAryPicklist.size(); iIndex++)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: picklist item at index %d is: %s", __FUNCTION__, iIndex, _strAryPicklist.at(iIndex).c_str());
        m_vectPickList.push_back(_strAryPicklist.at(iIndex));
    }

    if (m_pVREventProvider)
    {
        m_pVREventProvider->showPickList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s: VR event provider not created", __FUNCTION__);
    }

    _reply(hmiVRTypes::EResponseType::EN_SUCCESS);
}

void CVRStubResourceImpl::hidePickList(const std::shared_ptr<CommonAPI::ClientId> _client, hmiVRStub::hidePickListReply_t _reply)
{
    int iHashCode = 0;
    if(_client)
    {
        iHashCode = static_cast<int>(_client->hashCode());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: _client is NULL", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: client hash code: %d", __FUNCTION__, iHashCode);

    if (m_pVREventProvider)
    {
        m_pVREventProvider->hidePickList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s: VR event provider not created", __FUNCTION__);
    }

    _reply(hmiVRTypes::EResponseType::EN_SUCCESS);
}

void CVRStubResourceImpl::setFocusedItem(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _iLineNo, hmiVRStub::setFocusedItemReply_t _reply)
{
    int iHashCode = 0;
    if(_client)
    {
        iHashCode = static_cast<int>(_client->hashCode());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: _client is NULL", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: client hash code: %d, line number: %d", __FUNCTION__, iHashCode, _iLineNo);

    if (m_pVREventProvider)
    {
        m_pVREventProvider->setFocusedItem(_iLineNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s: VR event provider not created", __FUNCTION__);
    }

    _reply(hmiVRTypes::EResponseType::EN_SUCCESS);
}

void CVRStubResourceImpl::focusSelectedCategory(const std::shared_ptr<CommonAPI::ClientId> _client, string _strCategory, hmiVRStub::focusSelectedCategoryReply_t _reply)
{
    int iHashCode = 0;
    if(_client)
    {
        iHashCode = static_cast<int>(_client->hashCode());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: _client is NULL", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: client hash code: %d, category is: %s", __FUNCTION__, iHashCode, _strCategory.c_str());

    if (m_pVREventProvider)
    {
        m_pVREventProvider->focusSelectedCategory(_strCategory);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s: VR event provider not created", __FUNCTION__);
    }

    _reply(hmiVRTypes::EResponseType::EN_SUCCESS);
}

void CVRStubResourceImpl::mediaFilterListShow(const std::shared_ptr<CommonAPI::ClientId> _client, hmiVRTypes::EFilterIDType _eFilterType, int64_t _iFilterId, hmiVRStub::mediaFilterListShowReply_t _reply)
{
    int iHashCode = 0;
    if(_client)
    {
        iHashCode = static_cast<int>(_client->hashCode());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: _client is NULL", __FUNCTION__);
    }
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: client hash code: %d, _eFilterType is: %d, _iFilterId is: %lld", __FUNCTION__, iHashCode, _eFilterType.value_, _iFilterId);

    m_objMediaFilterListShowReply   = _reply;
    setRequestState(EN_REQUEST_MEDIA_FILTER_LIST_SHOW);

    if (m_pVREventProvider)
    {
        m_pVREventProvider->mediaFilterListShow(_eFilterType.value_, _iFilterId);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR,"%s: VR event provider not created", __FUNCTION__);
    }
}

void CVRStubResourceImpl::setRequestState(EVRRequestState eVRRequestState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: Current VR request state is: %d, Incoming VR request state is: %d", __FUNCTION__, m_eVRRequestState, eVRRequestState);
    m_eVRRequestState = eVRRequestState;
}

hmiVRTypes::EResponseType CVRStubResourceImpl::getResponseType(EResponseType eResponseType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: HMI response type is: %d", __FUNCTION__, eResponseType);
    hmiVRTypes::EResponseType eVRResponseType = hmiVRTypes::EResponseType::EN_INVALID;
    switch(eResponseType)
    {
    case EN_RESPONSE_TYPE_SUCCESS:
        eVRResponseType = hmiVRTypes::EResponseType::EN_SUCCESS;
        break;

    case EN_RESPONSE_TYPE_FAILURE:
        eVRResponseType = hmiVRTypes::EResponseType::EN_FAILURE;
        break;

    case EN_RESPONSE_TYPE_PROJECTION_MODE:
        eVRResponseType = hmiVRTypes::EResponseType::EN_PROJECTIONMODE;
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: HMI response type not handled", __FUNCTION__);
        break;
    }

    return eVRResponseType;
}


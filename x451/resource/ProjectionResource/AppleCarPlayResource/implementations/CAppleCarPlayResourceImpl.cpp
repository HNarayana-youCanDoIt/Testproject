/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlayResourceImpl.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CAppleCarPlayResourceImpl, Resource Implementation for AppleCarPlay.
*/

#include "CAppleCarPlayResourceImpl.h"
#include "logging.h"
#include "ResourceMaster.h"
#include "ResourceDeploymentConfig.h"
#include "CAppleCarPlayEventProvider.h"

CAppleCarPlayResourceImpl::CAppleCarPlayResourceImpl():
    m_pAppleCarPlayEventProvider(new CAppleCarPlayEventProvider()),
    m_objAppleCarPlayProxy(ResourceDeploymentConfig::getConfig().m_AppleCarPlay_Proxy.domain,
                           ResourceDeploymentConfig::getConfig().m_AppleCarPlay_Proxy.instance),
    m_objAppleCarPlayPluginProxy(ResourceDeploymentConfig::getConfig().m_AppleCarPlayPlugin_Proxy.domain,
                                 ResourceDeploymentConfig::getConfig().m_AppleCarPlayPlugin_Proxy.instance),
    m_bIsAppleCarPlayProxyAvailable(false),
    m_bIsAppleCarPlayPluginProxyAvailable(false)

{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    SUBSCRIBE(m_objAppleCarPlayProxy, getProxyStatusEvent(),
              &CAppleCarPlayResourceImpl::appleCarPlaySeriveStatusCb, _1);

    SUBSCRIBE(m_objAppleCarPlayPluginProxy, getProxyStatusEvent(),
              &CAppleCarPlayResourceImpl::appleCarPlayPluginSeriveStatusCb, _1);

   subscribe();
   subscribeAppleCarPlayPlugin();
}

CAppleCarPlayResourceImpl::~CAppleCarPlayResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(m_pAppleCarPlayEventProvider)
    {
        delete m_pAppleCarPlayEventProvider;
        m_pAppleCarPlayEventProvider = nullptr;
    }
}

CAppleCarPlayEventProvider* CAppleCarPlayResourceImpl::getAppleCarPlayEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    return m_pAppleCarPlayEventProvider;
}

void CAppleCarPlayResourceImpl::requestProjection(const string &appURL)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: with appURL:%s", __FUNCTION__,appURL.c_str());

    CallStatus objCallStatus;

    if(m_bIsAppleCarPlayProxyAvailable)
    {
        m_objAppleCarPlayProxy->requestProjection(appURL, objCallStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlay Proxy not available", __FUNCTION__);
    }

}

void CAppleCarPlayResourceImpl::requestNative()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    CallStatus objCallStatus;

    if(m_bIsAppleCarPlayProxyAvailable)
    {
        m_objAppleCarPlayProxy->requestNative(cpprestypes::eScreenSwitchReason::USER_SWITCH, objCallStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlay Proxy not available", __FUNCTION__);
    }
}

void CAppleCarPlayResourceImpl::reportKeyEvent(const uint32_t &uiKeyCode, const uint32_t &uiKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_bIsAppleCarPlayPluginProxyAvailable)
    {
        m_objAppleCarPlayPluginProxy->reportKeyEventAsync(uiKeyCode, uiKeyState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: CarPlayPlugin Proxy not available", __FUNCTION__);
    }
}

void CAppleCarPlayResourceImpl::setSmartFanState(bool bSmartFanState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Request - setSmartFanState: %d", __FUNCTION__, bSmartFanState);

    if (m_bIsAppleCarPlayPluginProxyAvailable)
    {
        m_objAppleCarPlayPluginProxy->setSmartFanstateAsync(bSmartFanState, std::bind(&CAppleCarPlayResourceImpl::onSetSmartFanStateAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: CarPlayPlugin Proxy not available", __FUNCTION__);
    }
}

void CAppleCarPlayResourceImpl::onSetSmartFanStateAsyncCb(const CallStatus &status, bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: CallStatus: %d bValue : %d", __FUNCTION__, static_cast<int>(status), bValue);

    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        if (m_pAppleCarPlayEventProvider)
        {
            m_pAppleCarPlayEventProvider->updateSmartFanState(bValue);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAppleCarPlayEventProvider is NULL.", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION,"CarPlay onSetSmartFanStateAsyncCb callback is not successful");
    }
}

void CAppleCarPlayResourceImpl::updateCPProxyStatus(bool bCPProxyStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bCPProxyStatus: %d", __FUNCTION__, bCPProxyStatus);

    if (m_pAppleCarPlayEventProvider)
    {
        m_pAppleCarPlayEventProvider->updateCPProxyStatus(bCPProxyStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAppleCarPlayEventProvider is NULL.", __FUNCTION__);
    }
}

/*********************************************************
 *  @category   INTERNAL METHODS
 *********************************************************/

void CAppleCarPlayResourceImpl::subscribe()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    SUBSCRIBE(m_objAppleCarPlayProxy, getSessionAttribute().getChangedEvent(), &CAppleCarPlayResourceImpl::onSessionAttributeDetailsCb, _1);
    SUBSCRIBE(m_objAppleCarPlayProxy, getDeviceInfoAttribute().getChangedEvent(), &CAppleCarPlayResourceImpl::onDeviceDetailsCb, _1);
}

void CAppleCarPlayResourceImpl::subscribeAppleCarPlayPlugin()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    SUBSCRIBE(m_objAppleCarPlayPluginProxy, getScreenOwnerAttribute().getChangedEvent(), &CAppleCarPlayResourceImpl::onScreenOwnerCb, _1);
    SUBSCRIBE(m_objAppleCarPlayPluginProxy, getPhoneOwnerAttribute().getChangedEvent(), &CAppleCarPlayResourceImpl::onPhoneOwnerCb, _1);
    SUBSCRIBE(m_objAppleCarPlayPluginProxy, getNowPlayingDataAttribute().getChangedEvent(), &CAppleCarPlayResourceImpl::onNowPlayingDataAttributeCb, _1);
    SUBSCRIBE(m_objAppleCarPlayPluginProxy, getSpeechOwnerAttribute().getChangedEvent(), &CAppleCarPlayResourceImpl::onSpeechOwnerCb, _1);
}

/*********************************************************
 *  @category   CALLBACK METHODS
 *********************************************************/

void CAppleCarPlayResourceImpl::appleCarPlaySeriveStatusCb(AvailabilityStatus eAvailabilityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(AvailabilityStatus::AVAILABLE == eAvailabilityStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlay Proxy available", __FUNCTION__);

        m_bIsAppleCarPlayProxyAvailable = true;
    }
    else
    {
        m_bIsAppleCarPlayProxyAvailable = false;

        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlay Proxy not available", __FUNCTION__);

    }
}

void CAppleCarPlayResourceImpl::appleCarPlayPluginSeriveStatusCb(AvailabilityStatus eAvailabilityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(AvailabilityStatus::AVAILABLE == eAvailabilityStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlayPlugin Proxy available", __FUNCTION__);

        m_bIsAppleCarPlayPluginProxyAvailable = true;
    }
    else
    {
        m_bIsAppleCarPlayPluginProxyAvailable = false;

        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlayPlugin Proxy not available", __FUNCTION__);

    }

    updateCPProxyStatus(m_bIsAppleCarPlayPluginProxyAvailable);
}

void CAppleCarPlayResourceImpl::onSessionAttributeDetailsCb(pprestypes::sSessionDetails sSessionDetails)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_pAppleCarPlayEventProvider)
    {
        m_pAppleCarPlayEventProvider->updateAppleCarPlayRemoteUIStatus(sSessionDetails.getRemoteUI());

        if(pprestypes::eSessionStatus::SESSION_ACTIVATED == sSessionDetails.getStatus())
        {
            m_pAppleCarPlayEventProvider->updateAppleCarPlayConnectionStatus(true);
        }
        else
        {
            m_pAppleCarPlayEventProvider->updateAppleCarPlayConnectionStatus(false);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAppleCarPlayEventProvider is NULL.", __FUNCTION__);
    }
}

void CAppleCarPlayResourceImpl::onDeviceDetailsCb(const vector<pprestypes::sDevDetails> &vectSDeviceDetails)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (!vectSDeviceDetails.empty())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,"%s: AppleCarPlay Device Name: %s", __FUNCTION__, vectSDeviceDetails[0].getDevName().c_str());

        if (m_pAppleCarPlayEventProvider)
        {
            m_pAppleCarPlayEventProvider->updateAppleCarPlayDeviceName(vectSDeviceDetails[0].getDevName());
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAppleCarPlayEventProvider is NULL.", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: vectSDeviceDetails is empty.", __FUNCTION__);
    }
}

void CAppleCarPlayResourceImpl::onScreenOwnerCb(const TataCarPlayPresPlugin::OwnerType &ownerType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s CarPlay::onScreenOwner", __FUNCTION__);
    if (m_pAppleCarPlayEventProvider)
    {
        /*
         * Gets screenOwner and update CarPlay projection status accordingly.
         */
        m_pAppleCarPlayEventProvider->updateAppleCarPlayProjectionStatus(TataCarPlayPresPlugin::OwnerType::iDevice == ownerType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAppleCarPlayEventProvider is NULL.", __FUNCTION__);
    }
}

void CAppleCarPlayResourceImpl::onPhoneOwnerCb(const TataCarPlayPresPlugin::OwnerType &ownerType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s CarPlay::onPhoneOwnerCb", __FUNCTION__);
    if (m_pAppleCarPlayEventProvider)
    {
        /*
         * Gets PhoneOwner and update CarPlay Phone status accordingly.
         */
        m_pAppleCarPlayEventProvider->updateAppleCarPlayPhoneStatus(TataCarPlayPresPlugin::OwnerType::iDevice == ownerType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAppleCarPlayEventProvider is NULL.", __FUNCTION__);
    }
}

void CAppleCarPlayResourceImpl::onNowPlayingDataAttributeCb(const TataCarPlayPresPlugin::sPluginNowPlayingInfo &objsNowPlayingInfo)
{
    /*
     * Get the CPMedia Meta Data from pres and save it in member object
     * of structure NowPlayingInfo, for further use.
     */
    m_objNowPlayingInfo.mStrTitle = objsNowPlayingInfo.getTitle();
    m_objNowPlayingInfo.mStrArtist = objsNowPlayingInfo.getArtist();

    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: songName: %s,"
                                            " songArtistName: %s", __FUNCTION__,
             m_objNowPlayingInfo.mStrTitle.c_str(),
             m_objNowPlayingInfo.mStrArtist.c_str());

    if (m_pAppleCarPlayEventProvider)
    {
        /*
         * Update CPNowPlayingInfo to upper layer.
         */
        m_pAppleCarPlayEventProvider->updateCPNowPlayingInfo();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pCarPlayEventProvider is NULL.", __FUNCTION__);
    }
}

void CAppleCarPlayResourceImpl::onSpeechOwnerCb(const TataCarPlayPresPlugin::OwnerType &ownerType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s Speech Owner: %d", __FUNCTION__, ownerType.value_);
    if (m_pAppleCarPlayEventProvider)
    {
        /*
         * Gets Speech Owner and update CarPlay Siri status accordingly.
         */
        m_pAppleCarPlayEventProvider->updateCarPlaySiriStatus(TataCarPlayPresPlugin::OwnerType::iDevice == ownerType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAppleCarPlayEventProvider is NULL.", __FUNCTION__);
    }
}


/*********************************************************//**
 *  @category   REQUEST METHODS
 *********************************************************/

/*********************************************************//**
 *  @category   RESPONSE CALLBACK METHODS
 *********************************************************/


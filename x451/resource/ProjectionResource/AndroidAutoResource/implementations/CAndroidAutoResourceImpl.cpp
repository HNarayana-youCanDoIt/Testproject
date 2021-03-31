/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoResourceImpl.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CAndroidAutoResourceImpl, Resource Implementation for AndroidAuto.
*/

#include "CAndroidAutoResourceImpl.h"
#include "logging.h"
#include "ResourceMaster.h"
#include "ResourceDeploymentConfig.h"
#include "CAndroidAutoEventProvider.h"

CAndroidAutoResourceImpl::CAndroidAutoResourceImpl():
    m_pAndroidAutoEventProvider(new CAndroidAutoEventProvider()),
    m_objAndroidAutoProxy(ResourceDeploymentConfig::getConfig().m_AndroidAuto_Proxy.domain,
                          ResourceDeploymentConfig::getConfig().m_AndroidAuto_Proxy.instance),
    m_objAndroidAutoPluginProxy(ResourceDeploymentConfig::getConfig().m_AndroidAutoPlugin_Proxy.domain,
                                ResourceDeploymentConfig::getConfig().m_AndroidAutoPlugin_Proxy.instance),
    m_bIsAndroidAutoProxyAvailable(false),
    m_bIsAndroidAutoPluginProxyAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    SUBSCRIBE(m_objAndroidAutoProxy, getProxyStatusEvent(),
              &CAndroidAutoResourceImpl::androidAutoSeriveStatusCb, _1);
    SUBSCRIBE(m_objAndroidAutoPluginProxy, getProxyStatusEvent(),
              &CAndroidAutoResourceImpl::androidAutoPluginSeriveStatusCb, _1);

    subscribe();
    subscribeAAPlugin();
}

CAndroidAutoResourceImpl::~CAndroidAutoResourceImpl()
{
    if(m_pAndroidAutoEventProvider)
    {
        delete m_pAndroidAutoEventProvider;
        m_pAndroidAutoEventProvider = nullptr;
    }
}

CAndroidAutoEventProvider* CAndroidAutoResourceImpl::getAndroidAutoEventProvider()
{
    return m_pAndroidAutoEventProvider;
}


/*********************************************************//**
 *  @category   INTERNAL METHODS
 *********************************************************/

void CAndroidAutoResourceImpl::subscribe()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    SUBSCRIBE(m_objAndroidAutoProxy, getPlaybackStatusAttribute().getChangedEvent(), &CAndroidAutoResourceImpl::onPlaybackStatusAttributeCb, _1);
    SUBSCRIBE(m_objAndroidAutoProxy, getMetadataAttribute().getChangedEvent(), &CAndroidAutoResourceImpl::onMetadataAttributeCb, _1);
    SUBSCRIBE(m_objAndroidAutoProxy, getNavStatusTypeAttribute().getChangedEvent(), &CAndroidAutoResourceImpl::onGetNavStatusTypeAttributeCb, _1);
    SUBSCRIBE(m_objAndroidAutoProxy, getSessionAttribute().getChangedEvent(), &CAndroidAutoResourceImpl::onGetSessionAttributeCb, _1);
    SUBSCRIBE(m_objAndroidAutoProxy, getTurnInfoAttribute().getChangedEvent(), &CAndroidAutoResourceImpl::onNavTurnInfoAttributeCb, _1);
    SUBSCRIBE(m_objAndroidAutoProxy, getTurnDistInfoAttribute().getChangedEvent(), &CAndroidAutoResourceImpl::onNavTurnDistInfoAttributeCb, _1);
}

void CAndroidAutoResourceImpl::subscribeAAPlugin()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    SUBSCRIBE(m_objAndroidAutoPluginProxy, getFirstConnShowPopupEvent(), &CAndroidAutoResourceImpl::onFirstConnectionCb, _1);
    SUBSCRIBE(m_objAndroidAutoPluginProxy, getFunctionOwnerAttribute().getChangedEvent(), &CAndroidAutoResourceImpl::onFunctionOwnerCb, _1);
    SUBSCRIBE(m_objAndroidAutoPluginProxy, getScreenOwnerAttribute().getChangedEvent(), &CAndroidAutoResourceImpl::onScreenOwnerCb, _1);
    SUBSCRIBE(m_objAndroidAutoPluginProxy, getSpeechOwnerAttribute().getChangedEvent(), &CAndroidAutoResourceImpl::onSpeechOwnerCb, _1);
}

/*********************************************************//**
 *  @category   CALLBACK METHODS
 *********************************************************/

void CAndroidAutoResourceImpl::androidAutoSeriveStatusCb(AvailabilityStatus eAvailabilityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(AvailabilityStatus::AVAILABLE == eAvailabilityStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAuto Proxy available", __FUNCTION__);

        m_bIsAndroidAutoProxyAvailable = true;
    }
    else
    {
        m_bIsAndroidAutoProxyAvailable = false;

        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAuto Proxy not available", __FUNCTION__);

    }
}

void CAndroidAutoResourceImpl::androidAutoPluginSeriveStatusCb(AvailabilityStatus eAvailabilityStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(AvailabilityStatus::AVAILABLE == eAvailabilityStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoPlugin Proxy available", __FUNCTION__);

        m_bIsAndroidAutoPluginProxyAvailable = true;
    }
    else
    {
        m_bIsAndroidAutoPluginProxyAvailable = false;

        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoPlugin Proxy not available", __FUNCTION__);

    }
}

void CAndroidAutoResourceImpl::onFirstConnectionCb(uint8_t ucFirstRunParam)
{
    CPP_UNUSED(ucFirstRunParam);

    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_pAndroidAutoEventProvider)
    {
        m_pAndroidAutoEventProvider->updateAAFirstRunConnectionStatus();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAndroidAutoEventProvider is NULL.", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::onFunctionOwnerCb(const TataAndroidAutoPresPlugin::HuFunctions &objSHuFunctions)
{
    CPP_UNUSED(objSHuFunctions);
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
}

void CAndroidAutoResourceImpl::onScreenOwnerCb(
        const TataAndroidAutoPresPlugin::OwnerType &ownerType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    if (m_pAndroidAutoEventProvider)
    {
        /*
         * Gets screenOwner and update Android Auto projection status
         * accordingly.
         */
        m_pAndroidAutoEventProvider->updateAAProjectionStatus(
                    TataAndroidAutoPresPlugin::OwnerType::Phone == ownerType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAndroidAutoEventProvider is NULL.", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::onGetNavStatusTypeAttributeCb(
        const pprestypes::navigationStatusType &naviStatus
        )
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_pAndroidAutoEventProvider)
    {
        /*
         * Update AANavi status to upper layer.
         */
        m_pAndroidAutoEventProvider->updateAANaviStatus(
                    ( pprestypes::navigationStatusType::NavigationStatus_Active
                      == naviStatus )
                    );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAndroidAutoEventProvider is NULL.", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::onPlaybackStatusAttributeCb(const pprestypes::sMediaPlaybackStatusUpdate &objsMediaPlaybackStatusUpdate)
{
    pprestypes::sMediaPlayState objsMediaPlayState = objsMediaPlaybackStatusUpdate.getPlayState();

    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: aaMediaPlayState: %u", __FUNCTION__,
             static_cast<ushort> (objsMediaPlayState.value_));

    if (m_pAndroidAutoEventProvider)
    {
        /*
         * Update AAMediaPlayState to upper layer.
         */
        m_pAndroidAutoEventProvider->updateAAMediaPlayState(objsMediaPlayState.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAndroidAutoEventProvider is NULL.", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::onMetadataAttributeCb(const pprestypes::sMetaDataUpdate &objsMetaDataUpdate)
{
    /*
     * Get the AAMedia Meta Data from pres and save it in member object
     * of structure SAAMediaMetaData, for further use.
     */
    m_objAAMediaMetaData.m_strArtistName = objsMetaDataUpdate.getArtistName();
    m_objAAMediaMetaData.m_strSongName = objsMetaDataUpdate.getSongName();
    m_objAAMediaMetaData.m_strAlbumName = objsMetaDataUpdate.getAlbumName();
    m_objAAMediaMetaData.m_strPlaylist = objsMetaDataUpdate.getPlaylist();
    m_objAAMediaMetaData.m_strSongAlbumArt = objsMetaDataUpdate.getSongAlbumArt();
    m_objAAMediaMetaData.m_uiTime = objsMetaDataUpdate.getTime();
    m_objAAMediaMetaData.m_iSongRating = objsMetaDataUpdate.getSongRating();

    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: songName: %s,"
                                            " songArtistName: %s", __FUNCTION__,
             m_objAAMediaMetaData.m_strSongName.c_str(),
             m_objAAMediaMetaData.m_strArtistName.c_str());

    if ( m_pAndroidAutoEventProvider )
    {
        /*
         * Update AAMediaMetaData to upper layer.
         */
        m_pAndroidAutoEventProvider->updateAAMediaMetaData();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAndroidAutoEventProvider is NULL.", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::onGetSessionAttributeCb(const pprestypes::sSessionDetails &objsSessionDetails)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    m_objAASessionDetails.m_strDeviceName = objsSessionDetails.getDevName();
    m_objAASessionDetails.m_strBtAddress = objsSessionDetails.getBtAddress();
    m_objAASessionDetails.m_strUSBSerialNo = objsSessionDetails.getUsbSerialNo();
    m_objAASessionDetails.m_bIsConnected = objsSessionDetails.getIsConnected();
    m_objAASessionDetails.m_bRemoteUi = objsSessionDetails.getRemoteUI();
    m_objAASessionDetails.m_iSessionStatus = objsSessionDetails.getStatus();
    m_objAASessionDetails.m_iTransportType = objsSessionDetails.getTransport();

    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: DeviceName: %s,"
                                            " BtAddress: %s", __FUNCTION__,
             m_objAASessionDetails.m_strDeviceName.c_str(),
             m_objAASessionDetails.m_strBtAddress.c_str());


    if ( m_pAndroidAutoEventProvider )
    {
        /*
         * Update AASessionDetails to upper layer.
         */
        m_pAndroidAutoEventProvider->updateAASessionDetails();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAndroidAutoEventProvider is NULL.", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::onNavTurnInfoAttributeCb(const pprestypes::sNaviNextTurnInfo &objsNaviNextTurnInfo)
{
    m_objSAANaviNextTurnInfo.m_strRoadName = objsNaviNextTurnInfo.getRoadName();
    m_objSAANaviNextTurnInfo.m_iNextTurnEvent = objsNaviNextTurnInfo.getTurnEvent();
    m_objSAANaviNextTurnInfo.m_iNextTurnSide = objsNaviNextTurnInfo.getSideType();
    m_objSAANaviNextTurnInfo.m_strImage = objsNaviNextTurnInfo.getImage();
    m_objSAANaviNextTurnInfo.m_iTurnAngle = objsNaviNextTurnInfo.getTurnAngle();
    m_objSAANaviNextTurnInfo.m_iTurnNumber = objsNaviNextTurnInfo.getTurnNo();

    /*
    * Update AANavigationTurnEventDetails to upper layer.
    */
    m_pAndroidAutoEventProvider->updateAANaviTurnEventDetails();

    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_strImage: %s, m_iNextTurnSide: %d, m_iNextTurnEvent: %d, m_iTurnAngle: %d",
             __FUNCTION__, m_objSAANaviNextTurnInfo.m_strImage.c_str(), m_objSAANaviNextTurnInfo.m_iNextTurnSide, m_objSAANaviNextTurnInfo.m_iNextTurnEvent, m_objSAANaviNextTurnInfo.m_iTurnAngle);
}

void CAndroidAutoResourceImpl::onNavTurnDistInfoAttributeCb(const pprestypes::sNaviNextTurnDistInfo &objsNaviNextTurnDistInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    m_objSAANaviNextTurnDistInfo.m_iDistance = objsNaviNextTurnDistInfo.getDist();
    m_objSAANaviNextTurnDistInfo.m_iTimeDuration = objsNaviNextTurnDistInfo.getTimeDuration();
    m_objSAANaviNextTurnDistInfo.m_iDisplayDistance = objsNaviNextTurnDistInfo.getDisplayDist();
    m_objSAANaviNextTurnDistInfo.m_iDistanceUnit = objsNaviNextTurnDistInfo.getUnitType();

    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_iDistance: %d, m_iTimeDuration: %d, m_iDisplayDistance: %d, m_iDistanceUnit: %d",
             __FUNCTION__, m_objSAANaviNextTurnDistInfo.m_iDistance, m_objSAANaviNextTurnDistInfo.m_iTimeDuration, m_objSAANaviNextTurnDistInfo.m_iDisplayDistance, m_objSAANaviNextTurnDistInfo.m_iDistanceUnit);

    if ( m_pAndroidAutoEventProvider)
    {
        /*
        * Update AANavigationTurnDistanceDetails to upper layer.
        */
        m_pAndroidAutoEventProvider->updateAANaviTurnDistanceDetails();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAndroidAutoEventProvider is NULL.", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::onSpeechOwnerCb(
        const TataAndroidAutoPresPlugin::OwnerType &ownerType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    if (m_pAndroidAutoEventProvider)
    {
        /*
         * Gets speechOwner and update Android Auto Ok Google status
         * accordingly.
         */
        m_pAndroidAutoEventProvider->updateOKGoogleStatus(
                    TataAndroidAutoPresPlugin::OwnerType::Phone == ownerType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: m_pAndroidAutoEventProvider is NULL.", __FUNCTION__);
    }
}


/*********************************************************//**
 *  @category   REQUEST METHODS
 *********************************************************/

void CAndroidAutoResourceImpl::requestProjection()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    CallStatus objCallStatus;

    if (m_bIsAndroidAutoProxyAvailable)
    {
        m_objAndroidAutoProxy->requestProjection("", objCallStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAuto Proxy not available", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::requestNative()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    CallStatus objCallStatus;

    if (m_bIsAndroidAutoProxyAvailable)
    {
        m_objAndroidAutoProxy->requestNative(aaprestypes::eScreenSwitchReason::USER_SWITCH, objCallStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAuto Proxy not available", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::reportKeyEvent(const uint32_t &uiKeyCode, const uint32_t &uiKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_bIsAndroidAutoPluginProxyAvailable)
    {
        m_objAndroidAutoPluginProxy->reportKeyEventAsync(uiKeyCode, uiKeyState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoPlugin Proxy not available", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::toggleAapMediaAsync()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_bIsAndroidAutoPluginProxyAvailable)
    {
        m_objAndroidAutoPluginProxy->toggleAapMediaAsync();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoPlugin Proxy not available", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::pauseAapMediaAsync()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_bIsAndroidAutoPluginProxyAvailable)
    {
        m_objAndroidAutoPluginProxy->pauseAapMediaAsync();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoPlugin Proxy not available", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::playAapMediaAsync()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_bIsAndroidAutoPluginProxyAvailable)
    {
        m_objAndroidAutoPluginProxy->playAapMediaAsync();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoPlugin Proxy not available", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::aapMediaNextAsync()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_bIsAndroidAutoPluginProxyAvailable)
    {
        m_objAndroidAutoPluginProxy->AapMediaNextAsync();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoPlugin Proxy not available", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::aapMediaPreviousAsync()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_bIsAndroidAutoPluginProxyAvailable)
    {
        m_objAndroidAutoPluginProxy->AapMediaPreviousAsync();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoPlugin Proxy not available", __FUNCTION__);
    }
}

void CAndroidAutoResourceImpl::aapShowAaMediaAsync()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (m_bIsAndroidAutoPluginProxyAvailable)
    {
        m_objAndroidAutoPluginProxy->AapShowAaMediaAsync();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAutoPlugin"
                                                   " Proxy not available",
                    __FUNCTION__);
    }
}

/*********************************************************//**
 *  @category   RESPONSE CALLBACK METHODS
 *********************************************************/


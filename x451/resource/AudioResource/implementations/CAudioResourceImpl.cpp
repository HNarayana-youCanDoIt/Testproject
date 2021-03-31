/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CAudioResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CAudioResourceImpl, Resource Implementation for Audio.
 */
#include "CAudioResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"
#include "CAudioResourceEnums.h"

CAudioResourceImpl::CAudioResourceImpl():
    m_pAudioEventProvider(new CAudioEventProvider()),
    m_pAudioControlProxy(ResourceDeploymentConfig::getConfig().m_Audio_Control.domain,ResourceDeploymentConfig::getConfig().m_Audio_Control.instance),
    m_pAudioSettingsProxy(ResourceDeploymentConfig::getConfig().m_Audio_Settings.domain, ResourceDeploymentConfig::getConfig().m_Audio_Settings.instance),
    m_pAudioPluginProxy(ResourceDeploymentConfig::getConfig().m_Audio_Plugin.domain, ResourceDeploymentConfig::getConfig().m_Audio_Plugin.instance),
    m_bAudioSettingAvailable(false),
    m_bAudioControlAvailable(false),
    m_bTunerAvailable(false),
    m_bMediaAvailable(false),
    m_bBTAvailable(false),
    m_bAUXAvailable(false),
    m_bUSBAvailable(false),
    m_bIPodAvailable(false),
    m_iBass(0),
    m_iMid(0),
    m_iTreble(0),
    m_iBalance(0),
    m_iFade(0),
    m_bFMSrcStatus(false),
    m_bAMSrcStatus(false),
    m_bUSBSrcStatus(false),
    m_bIPODSrcStatus(false),
    m_bAUXSrcStatus(false),
    m_bBTSrcStatus(false),
    m_iActEntSourceVolume(0),
    m_bMuteActive(false),
    m_bIsVolumeUpdatedByUser(false),
    m_iVolumeGroup(0),
    m_iSourceId(0),
    m_bSpeedDependantVolume(false),
    m_iStartUpVolume(0),
    m_strActiveAudioPreset(""),
    m_bMicMuteStatus(false),
    m_iAuxGainValue(-1),
    m_eActiveEntSrc(CAudioEnums::SRC_ENT_UNKNOWN),
    m_strAuxConnectionStatus(""),
    m_strIpodConnectionStatus(""),
    m_strUsbConnectionStatus(""),
    m_bPdcMixModeStatus(true)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,__FUNCTION__);
    SUBSCRIBE(m_pAudioControlProxy,getProxyStatusEvent(),&CAudioResourceImpl::statusEventListnerControler,_1);
    SUBSCRIBE(m_pAudioSettingsProxy,getProxyStatusEvent(),&CAudioResourceImpl::statusEventListnerSettings,_1);
    SUBSCRIBE(m_pAudioPluginProxy,getProxyStatusEvent(),&CAudioResourceImpl::statusEventListnerAudioplugin,_1);
}

CAudioResourceImpl::~CAudioResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(m_pAudioEventProvider)
        delete m_pAudioEventProvider;
}

void CAudioResourceImpl::subscribeControlProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :",  __FUNCTION__);
    SUBSCRIBE(m_pAudioControlProxy,getActiveEntSourceAttribute().getChangedEvent(),&CAudioResourceImpl::onActiveEntSourceAttributeCb,_1);
    SUBSCRIBE(m_pAudioControlProxy,getEntSourceListAttribute().getChangedEvent(),&CAudioResourceImpl::onEntSourceListAttributeCb,_1);
    SUBSCRIBE(m_pAudioControlProxy,getActiveAudioSourcesAttribute().getChangedEvent(),&CAudioResourceImpl::onActiveAudioSourcesAttributeCb,_1);
}

void CAudioResourceImpl::subscribeSettingsProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :",  __FUNCTION__);
    SUBSCRIBE(m_pAudioSettingsProxy,getBassAttribute().getChangedEvent(),&CAudioResourceImpl::onBassAttributeCb,_1);
    SUBSCRIBE(m_pAudioSettingsProxy,getMidAttribute().getChangedEvent(),&CAudioResourceImpl::onMidAttributeCb,_1);
    SUBSCRIBE(m_pAudioSettingsProxy,getTrebleAttribute().getChangedEvent(),&CAudioResourceImpl::onTrebleAttributeCb,_1);
    SUBSCRIBE(m_pAudioSettingsProxy,getBalanceAttribute().getChangedEvent(),&CAudioResourceImpl::onBalanceAttributeCb,_1);
    SUBSCRIBE(m_pAudioSettingsProxy,getFadeAttribute().getChangedEvent(),&CAudioResourceImpl::onFadeAttributeCb,_1);
    SUBSCRIBE(m_pAudioSettingsProxy,getEqualizerAttribute().getChangedEvent(),&CAudioResourceImpl::onAudioPresetAttributeCb,_1);
    SUBSCRIBE(m_pAudioSettingsProxy,getVolumeUpdateEvent(),&CAudioResourceImpl::onVolumeUpdateEventCb,_1,_2,_3);
    SUBSCRIBE(m_pAudioSettingsProxy,getActiveSrcMuteAttribute().getChangedEvent(),&CAudioResourceImpl::onActiveSrcMuteAttributeCb,_1);
    SUBSCRIBE(m_pAudioSettingsProxy,getMicMuteStatusAttribute().getChangedEvent(),&CAudioResourceImpl::onMicMuteStatusCb,_1);
}

void CAudioResourceImpl::subscribeAudioPluginProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s", __FUNCTION__);
    SUBSCRIBE(m_pAudioPluginProxy, getStartupVolumeAttribute().getChangedEvent(), &CAudioResourceImpl::onStartupVolumeAttributeCb, _1);
    SUBSCRIBE(m_pAudioPluginProxy, getSdvcStateAttribute().getChangedEvent(), &CAudioResourceImpl::onSdvcStateAttributeCb, _1);
    SUBSCRIBE(m_pAudioPluginProxy, getPdcMixModeAttribute().getChangedEvent(), &CAudioResourceImpl::onPdcMixModeAttributeCb, _1);
    SUBSCRIBE(m_pAudioPluginProxy, getAuxInGainAttribute().getChangedEvent(), &CAudioResourceImpl::onAuxOffsetGainAttributeCb, _1);
    SUBSCRIBE(m_pAudioPluginProxy, getAuxConnectionStateAttribute().getChangedEvent(), &CAudioResourceImpl::onAuxConnectionStateAttribute, _1);
    SUBSCRIBE(m_pAudioPluginProxy, getUsbConnectionStateAttribute().getChangedEvent(), &CAudioResourceImpl::onUSBConnectionStateAttribute, _1);
    SUBSCRIBE(m_pAudioPluginProxy, getIpodConnectionStateAttribute().getChangedEvent(), &CAudioResourceImpl::onIPODConnectionStateAttribute, _1);
    SUBSCRIBE(m_pAudioPluginProxy, getSourceStateEvent(), &CAudioResourceImpl::onSourceStateEventCb, _1, _2);
}

void CAudioResourceImpl::statusEventListnerSettings(CommonAPI::AvailabilityStatus eStatus)
{
    if(CommonAPI::AvailabilityStatus::AVAILABLE ==  eStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, :true", __FUNCTION__);
        subscribeSettingsProxy();
        m_bAudioSettingAvailable = true;
        // Getting Phone Audio Volume
        getSourceVolume(SRC_TEL_HANDSFREE);

        // Getting Voice Alert Volume
        getSourceVolume(SRC_WARNING);

        // Getting Park Assist Volume
        getSourceVolume(SRC_INDICATION);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s, :false", __FUNCTION__);
        m_bAudioSettingAvailable = false;
    }
}

void CAudioResourceImpl::statusEventListnerControler(CommonAPI::AvailabilityStatus eStatus)
{
    if(eStatus == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, :true", __FUNCTION__);
        subscribeControlProxy();
        m_bAudioControlAvailable = true;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s, :false", __FUNCTION__);
        m_bAudioControlAvailable = false;
    }
}

void CAudioResourceImpl::statusEventListnerAudioplugin(AvailabilityStatus eStatus)
{
    if(eStatus == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, :true", __FUNCTION__);
        subscribeAudioPluginProxy();
        m_bAudioPluginAvailable = true;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s, :false", __FUNCTION__);
        m_bAudioPluginAvailable = false;
    }

    if(m_pAudioEventProvider)
        m_pAudioEventProvider->updateAudioPluginProxyAvailability(m_bAudioPluginAvailable);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioEventProvider is null");
}

CAudioEventProvider *CAudioResourceImpl::getAudioDataEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    return m_pAudioEventProvider;
}

void CAudioResourceImpl::setAudioOff(bool bAudioState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Request - audioState : %d ", __FUNCTION__, bAudioState);
    if(m_bAudioPluginAvailable)
    {
        m_pAudioPluginProxy->SetAudioOffAsync(bAudioState,std::bind(&CAudioResourceImpl::onSetAudioOffCb,this,_1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: Audio press plugin is not available", __FUNCTION__);
    }
}

void CAudioResourceImpl::switchToPreviousEntSource()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ",__FUNCTION__);

    if(m_bAudioPluginAvailable)
    {
        m_pAudioPluginProxy->SwitchToPreviousEntSourceAsync(std::bind(&CAudioResourceImpl::switchToPreviousEntSourceCb,this,_1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: Audio plugin proxy is not available", __FUNCTION__);
    }
}

void CAudioResourceImpl::playFromSourceGroup(int iSourceGroup)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s iSourceGroup is: %d", __FUNCTION__, iSourceGroup);

    if(m_bAudioPluginAvailable)
    {
        m_pAudioPluginProxy->PlayFromSourceGroupAsync(getSourceGroup(iSourceGroup), std::bind(&CAudioResourceImpl::playFromSourceGroupAsyncCb, this, _1, _2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: Audio plugin proxy is not available", __FUNCTION__);
    }
}

void CAudioResourceImpl::onSourceStateEventCb(uint16_t uiSourceId, audioPresPluginTypes::ConnectionState_e eSourceState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s source id is: %d, source state is: %d", __FUNCTION__, uiSourceId, eSourceState.value_);

    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateSourceState(uiSourceId, eSourceState.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
    }
}

void CAudioResourceImpl::setBass(int16_t iBass)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s: Request - bass: %d", __FUNCTION__, iBass);
    std::pair<audioPresCtrlTypes::eAudioAttribute,int16_t> data(audioPresCtrlTypes::eAudioAttribute::BASS,iBass);
    audioPresCtrlTypes::mAttribute attributesmap;
    attributesmap.insert(data);

    CommonAPI::CallStatus eInternalCallStatus;
    /*
     * Note: setAudioAttribute method is a fire and forget method, ie., here the request method is send to LB
     * and HMI doesnt wait for the response and then free to disappear(Forget), HMI wont be in blocking state.
     * In this requester doesnt wait for response, but it is like async call.
     */
    m_pAudioSettingsProxy->setAudioAttribute(attributesmap,eInternalCallStatus);
}

void CAudioResourceImpl::setMid(int16_t iMid)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s: Request - mid: %d", __FUNCTION__, iMid);
    std::pair<audioPresCtrlTypes::eAudioAttribute,int16_t> data(audioPresCtrlTypes::eAudioAttribute::MID,iMid);
    audioPresCtrlTypes::mAttribute attributesmap;
    attributesmap.insert(data);

    CommonAPI::CallStatus eInternalCallStatus;
    /*
     * Note: setAudioAttribute method is a fire and forget method, ie., here the request method is send to LB
     * and HMI doesnt wait for the response and then free to disappear(Forget), HMI wont be in blocking state.
     * In this requester doesnt wait for response, but it is like async call.
     */
    m_pAudioSettingsProxy->setAudioAttribute(attributesmap,eInternalCallStatus);
}

void CAudioResourceImpl::setTreble(int16_t iTreble)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s: Request - treble: %d", __FUNCTION__, iTreble);
    std::pair<audioPresCtrlTypes::eAudioAttribute,int16_t> data(audioPresCtrlTypes::eAudioAttribute::TREBLE,iTreble);
    audioPresCtrlTypes::mAttribute attributesmap;
    attributesmap.insert(data);

    CommonAPI::CallStatus eInternalCallStatus;
    /*
     * Note: setAudioAttribute method is a fire and forget method, ie., here the request method is send to LB
     * and HMI doesnt wait for the response and then free to disappear(Forget), HMI wont be in blocking state.
     * In this requester doesnt wait for response, but it is like async call.
     */
    m_pAudioSettingsProxy->setAudioAttribute(attributesmap,eInternalCallStatus);
}

void CAudioResourceImpl::setFaderBalance(int16_t iFader, int16_t iBalance)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s: Request - fader: %d, balance: %d",__FUNCTION__, iFader, iBalance);
    std::pair<audioPresCtrlTypes::eAudioAttribute,int16_t> faderData(audioPresCtrlTypes::eAudioAttribute::FADE,iFader);
    std::pair<audioPresCtrlTypes::eAudioAttribute,int16_t> balanceData(audioPresCtrlTypes::eAudioAttribute::BALANCE,iBalance);
    audioPresCtrlTypes::mAttribute attributesmap;
    attributesmap.clear();
    attributesmap.insert(faderData);
    attributesmap.insert(balanceData);

    CommonAPI::CallStatus eInternalCallStatus;
    /*
     * Note: setAudioAttribute method is a fire and forget method, ie., here the request method is send to LB
     * and HMI doesnt wait for the response and then free to disappear(Forget), HMI wont be in blocking state.
     * In this requester doesnt wait for response, but it is like async call.
     */
    m_pAudioSettingsProxy->setAudioAttribute(attributesmap,eInternalCallStatus);
}

void CAudioResourceImpl::onBassAttributeCb(int16_t iBass)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Response - bass : %d", __FUNCTION__, iBass);
    m_iBass = iBass;
    if(m_pAudioEventProvider)
        m_pAudioEventProvider->updateBassData(iBass);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
}

int CAudioResourceImpl::getBassValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return  m_iBass;
}

void CAudioResourceImpl::onMidAttributeCb(int16_t iMid)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Response - mid : %d", __FUNCTION__, iMid);
    m_iMid = iMid;
    if(m_pAudioEventProvider)
        m_pAudioEventProvider->updateMidData(iMid);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
}

int CAudioResourceImpl::getMidValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return  m_iMid;
}

void CAudioResourceImpl::onTrebleAttributeCb(int16_t iTreble)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Response - treble : %d", __FUNCTION__, iTreble);
    if(m_pAudioEventProvider)
        m_pAudioEventProvider->updateTrebleData(iTreble);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
}

int CAudioResourceImpl::getTrebleValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return  m_iTreble;
}

void CAudioResourceImpl::onBalanceAttributeCb(int16_t iBalance)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Response - balance : %d", __FUNCTION__, iBalance);
    m_iBalance = iBalance;
    if(m_pAudioEventProvider)
        m_pAudioEventProvider->updateBalanceData(iBalance);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
}

int CAudioResourceImpl::getBalanceValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return  m_iBalance;
}

void CAudioResourceImpl::onFadeAttributeCb(int16_t iFade)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Response - fade : %d", __FUNCTION__, iFade);
    m_iFade = iFade;
    if(m_pAudioEventProvider)
        m_pAudioEventProvider->updateFadeData(iFade);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
}

int CAudioResourceImpl::getFadeValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return  m_iFade;
}

void CAudioResourceImpl::onActiveEntSourceAttributeCb(audioPresCtrlTypes::sSourceInfo objEntSrcInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Response - sEntSrcInfo : %d ", __FUNCTION__, objEntSrcInfo.getSourceID().value_);
    CAudioEnums::EAudioEntertainmentSrcs eActivesource = static_cast<CAudioEnums::EAudioEntertainmentSrcs> (objEntSrcInfo.getSourceID().value_);

    m_eActiveEntSrc = eActivesource;
    /*
     *Note: Here this logic is implemented because when on IPOD or USB connection, audio manager service sends active entertainment source value as 55.
     *So to diferentiate the connection type HMI explicitly set the active source to IPOD to show IPOD as active source on HMI.
     *Hence Here the condition is that when active entertainment source value is USB and source type is IPOD
     *then set the active entertainment source to IPOD, so HMI will know the connected source is IPOD.
     *As in vehicle we have only one port either USB connected or IPOD connected so service sends same value for USB and IPOD.
    */
    if(eActivesource == CAudioEnums::SRC_USB1 && objEntSrcInfo.getSourceType().value_ == SOURCE_TYPE_IPOD)
    {
        eActivesource = CAudioEnums::SRC_IPOD;
    }

    /*
     * This switch case is added to print the KPI Marker logs.
     */
    switch (eActivesource)
    {
    case CAudioEnums::SRC_CARPLAY_MEDIA:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ CarPlay Media source activated ]");
        break;
    case CAudioEnums::SRC_GAL_MEDIA:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Android Media source activated ]");
        break;
    case CAudioEnums::SRC_CARLIFE_MEDIA:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ CarLife Media source activated ]");
        break;
    case CAudioEnums::SRC_APPLINK_MEDIA:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ APPLINK Media source activated ]");
        break;
    case CAudioEnums::SRC_SAL_MEDIA:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ SAL Media source activated ]");
        break;
    case CAudioEnums::SRC_USB1:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ USB source activated ]");
        break;
    case CAudioEnums::SRC_BT_A2DP2:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ BT AUDIO source activated ]");
        break;
    case CAudioEnums::SRC_BT_A2DP1:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ BT AUDIO source activated ]");
        break;
    case CAudioEnums::SRC_AUDIO_AUX:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ AUX source activated ]");
        break;
    case CAudioEnums::SRC_IPOD:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ IPOD source activated ]");
        break;
    case CAudioEnums::SRC_TUNER_FM:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Tuner FM source activated ]");
        break;
    case CAudioEnums::SRC_TUNER_AM:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Tuner AM source activated ]");
        break;
    case CAudioEnums::SRC_TUNER_DRM:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Tuner DRM source activated ]");
        break;
    default:
        break;
    }

    if(m_pAudioEventProvider)
        m_pAudioEventProvider->activeEntSource(eActivesource);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
}

CAudioEnums::EAudioEntertainmentSrcs CAudioResourceImpl::getActiveEntSrc()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return  m_eActiveEntSrc;
}

void CAudioResourceImpl::onEntSourceListAttributeCb(audioPresCtrlTypes::mEntSrcsInfo mapEntSrcInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    m_bTunerAvailable = false;
    m_bMediaAvailable= false;
    m_bBTAvailable = false;
    m_bAUXAvailable = false;
    m_bUSBAvailable = false;
    m_bIPodAvailable = false;

    audioPresCtrlTypes::mEntSrcsInfo::iterator it;
    int index=0;
    for(it = mapEntSrcInfo.begin();it!=mapEntSrcInfo.end();it++,index++)
    {
        audioPresCtrlTypes::sSourceInfo srcinfo =  it->second;
        AudioSourceItem* audioDevice= new AudioSourceItem();
        audioDevice->id = index;
        audioDevice->appId = srcinfo.getSourceID();
        audioDevice->available = (srcinfo.getAvailability() == audioPresCtrlTypes::eSourceAvailablity::A_AVAILABLE) ? true : false;
        audioDevice->type =  (SourceType)static_cast<int>(srcinfo.getSourceType());

        switch(it->first)
        {
        case SRC_TUNER_FM :
        {
            LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Tuner FM source available ]");
            m_bTunerAvailable = audioDevice->available ? audioDevice->available:m_bTunerAvailable;
            m_bFMSrcStatus = m_bTunerAvailable;
            if(m_pAudioEventProvider)
                m_pAudioEventProvider->updateFMstatus(m_bTunerAvailable);
            else
                LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
            break;
        }
        case SRC_TUNER_AM :
        {
            LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Tuner AM source available ]");
            m_bTunerAvailable = audioDevice->available ? audioDevice->available:m_bTunerAvailable;
            m_bAMSrcStatus = m_bTunerAvailable;
            if(m_pAudioEventProvider)
                m_pAudioEventProvider->updateAMstatus(m_bTunerAvailable);
            else
                LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
            break;
        }

        case SRC_TUNER_DRM :
        {
            LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Tuner DRM source available ]");
            m_bTunerAvailable = audioDevice->available ? audioDevice->available:m_bTunerAvailable;
            if(m_pAudioEventProvider)
                m_pAudioEventProvider->updateDRMstatus(m_bTunerAvailable);
            else
                LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
            break;
        }
        case SRC_USB1 :
        {
            m_bMediaAvailable = audioDevice->available ? audioDevice->available:m_bMediaAvailable;
            if(SOURCE_TYPE_IPOD == audioDevice->type)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ IPOD source available ]");
                m_bIPodAvailable= audioDevice->available;
                m_bIPODSrcStatus = m_bIPodAvailable;

                if(m_pAudioEventProvider)
                    m_pAudioEventProvider->updateIPODstatus(m_bIPodAvailable);
                else
                    LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ USB source available ]");
                m_bUSBAvailable= audioDevice->available;
                m_bUSBSrcStatus = m_bUSBAvailable;
                if(m_pAudioEventProvider)
                    m_pAudioEventProvider->updateUSBstatus(m_bUSBAvailable);
                else
                    LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
            }
            break;
        }
        case SRC_BT_A2DP1:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ BT Audio source available ]");
            m_bBTAvailable = audioDevice->available ? audioDevice->available:m_bBTAvailable;
            m_bBTSrcStatus = m_bBTAvailable;
            if(m_pAudioEventProvider)
                m_pAudioEventProvider->updateBTstatus(m_bBTAvailable);
            else
                LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
            break;
        }
        case SRC_AUDIO_AUX:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ AUX source available ]");
            m_bAUXAvailable = audioDevice->available ? audioDevice->available:m_bAUXAvailable;
            m_bAUXSrcStatus = m_bAUXAvailable;
            if(m_pAudioEventProvider)
                m_pAudioEventProvider->updateAUXstatus(m_bAUXAvailable);
            else
                LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
            break;
        }

        default:
            LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"onActiveAudioSourceAttribute :Default Invalid!" );
            break;
        }
    }
}

bool CAudioResourceImpl::getAMSrcStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_bAMSrcStatus;
}

bool CAudioResourceImpl::getFMSrcStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_bFMSrcStatus;
}

bool CAudioResourceImpl::getUSBSrcStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_bUSBSrcStatus;
}

bool CAudioResourceImpl::getIPODSrcStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_bIPODSrcStatus;
}

bool CAudioResourceImpl::getAUXSrcStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_bAUXSrcStatus;
}

bool CAudioResourceImpl::getBTSrcStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_bBTSrcStatus;
}

void CAudioResourceImpl::setActiveSourceID(CAudioEnums::EAudioEntertainmentSrcs eSrcID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Request - eSrcID %d ", __FUNCTION__, eSrcID);

    /*
     * This switch case is added to print the KPI Marker logs.
     */
    switch (eSrcID)
    {
    case CAudioEnums::SRC_CARPLAY_MEDIA:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ CarPlay Media source switch requested ]");
        break;
    case CAudioEnums::SRC_GAL_MEDIA:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Android Media source switch requested ]");
        break;
    case CAudioEnums::SRC_CARLIFE_MEDIA:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ CarLife Media source switch requested ]");
        break;
    case CAudioEnums::SRC_APPLINK_MEDIA:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ APPLINK Media source switch requested ]");
        break;
    case CAudioEnums::SRC_SAL_MEDIA:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ SAL Media source switch requested ]");
        break;
    case CAudioEnums::SRC_USB1:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ USB source switch requested ]");
        break;
    case CAudioEnums::SRC_BT_A2DP2:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ BT AUDIO source switch requested ]");
        break;
    case CAudioEnums::SRC_BT_A2DP1:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ BT AUDIO source switch requested ]");
        break;
    case CAudioEnums::SRC_AUDIO_AUX:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ AUX source switch requested ]");
        break;
    case CAudioEnums::SRC_IPOD:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ IPOD source switch requested ]");
        break;
    case CAudioEnums::SRC_TUNER_FM:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Tuner FM source switch requested ]");
        break;
    case CAudioEnums::SRC_TUNER_AM:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Tuner AM source switch requested ]");
        break;
    case CAudioEnums::SRC_TUNER_DRM:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"[KPI_MARKER][HMI][ Tuner DRM source switch requested ]");
        break;
    default:
        break;
    }

    if(eSrcID == CAudioEnums::SRC_IPOD)
    {
        eSrcID = CAudioEnums::SRC_USB1;
    }
    if(m_bAudioControlAvailable)
    {
        audioPresCtrlTypes::eEntertainmentSrcs _srcID = static_cast<audioPresCtrlTypes::eEntertainmentSrcs::Literal>(eSrcID);
        m_pAudioControlProxy->SetEntertainmentSrcAsync(_srcID, std::bind(&CAudioResourceImpl::SetEntertainmentSrcAsyncCb,this, _1,_2));
    }
}

void CAudioResourceImpl::SetEntertainmentSrcAsyncCb(const CallStatus &status, const audioPresCtrlTypes::eAudioPresErrors &)
{
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, false", __FUNCTION__);
    }
}

void CAudioResourceImpl::setAudioPreset(const string &strPreset)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s : %s ",__FUNCTION__, strPreset.c_str());
    std::pair<audioPresCtrlTypes::eAudioAttribute,string> data(audioPresCtrlTypes::eAudioAttribute::EQUALIZER,strPreset);
    audioPresCtrlTypes::mAttribute attributesmap;
    attributesmap.insert(data);

    CommonAPI::CallStatus eInternalCallStatus;
    /*
     * Note: setAudioAttribute method is a fire and forget method, ie., here the request method is send to LB
     * and HMI doesnt wait for the response and then free to disappear(Forget), HMI wont be in blocking state.
     * In this requester doesnt wait for response, but it is like async call.
     */
    m_pAudioSettingsProxy->setAudioAttribute(attributesmap,eInternalCallStatus);
}

void CAudioResourceImpl::ToggleSystemMute()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Toggle Mute ", __FUNCTION__);
    if(m_bAudioSettingAvailable)
    {
        CommonAPI::CallStatus _internalCallStatus;
        /*
         * Note: ToggleSystemMute method is a fire and forget method, ie., here the request method is send to LB
         * and HMI doesnt wait for the response and then free to disappear(Forget), HMI wont be in blocking state.
         * In this requester doesnt wait for response, but it is like async call.
         */
        m_pAudioPluginProxy->ToggleSystemMute(_internalCallStatus);
    }
}

void CAudioResourceImpl::toggleMute(const bool &bUserInitiated)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s: bUserInitiated = %d", __FUNCTION__, bUserInitiated);
    if(m_bAudioPluginAvailable)
    {
        CommonAPI::CallStatus _internalCallStatus;
        m_pAudioPluginProxy->ToggleMute(bUserInitiated, _internalCallStatus);
    }
    else
    {
        //Do nothing
    }
}

void CAudioResourceImpl::playBeep(CAudioEnums::EBeepType eBeepType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Request - beep Type : %d ", __FUNCTION__, eBeepType);
    if(m_bAudioPluginAvailable)
    {
        audioPresPluginTypes::eBeepTypes ebeepType = static_cast<audioPresPluginTypes::eBeepTypes::Literal>(eBeepType);
        m_pAudioPluginProxy->PlayBeepAsync(ebeepType, std::bind(&CAudioResourceImpl::onPlayBeepAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: Audio plugin is not available", __FUNCTION__);
    }
}

void CAudioResourceImpl::setStartUpVolume(int16_t iStartUpVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s start Up Volume : %d ", __FUNCTION__, iStartUpVolume);
    if(m_bAudioPluginAvailable)
    {
        m_pAudioPluginProxy->SetStartupVolumeAsync(iStartUpVolume, std::bind(&CAudioResourceImpl::onStartUpVolumeCb,this, _1,_2));
    }
}

void CAudioResourceImpl::setSDVCState(bool bSdvcState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s SDVC state: %d ", __FUNCTION__, bSdvcState);
    if(m_bAudioPluginAvailable)
    {
        m_pAudioPluginProxy->SetSDVCStateAsync(bSdvcState, std::bind(&CAudioResourceImpl::onSdvcStateCb,this, _1,_2));
    }
}

void  CAudioResourceImpl::setPhoneSourceVolume(const uint16_t &iAabsoluteVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Phone Source Volume: %d ", __FUNCTION__, iAabsoluteVolume);
    setSourceVolume(SRC_TEL_HANDSFREE,iAabsoluteVolume);
}

void CAudioResourceImpl::setVoiceAlertVolume(const uint16_t &iAbsoluteVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Voice Alert Volume: %d ", __FUNCTION__, iAbsoluteVolume);
    setSourceVolume(SRC_VR_SMS_READOUT,iAbsoluteVolume);
}

void CAudioResourceImpl::setNotificationVolume(const uint16_t &iAbsoluteVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Notification Volume: %d ", __FUNCTION__, iAbsoluteVolume);
    setSourceVolume(SRC_GAL_NAVI,iAbsoluteVolume);
}

void CAudioResourceImpl::setAuxInGain(CAudioEnums::EAuxInGain eAuxInGain)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Aux In Gain: ", __FUNCTION__);
    if(m_bAudioPluginAvailable)
    {
        audioPresPluginTypes::eAuxInGains _eAuxInGains = static_cast<audioPresPluginTypes::eAuxInGains::Literal>(eAuxInGain);
        m_pAudioPluginProxy->SetAuxInGainAsync(_eAuxInGains, std::bind(&CAudioResourceImpl::onAuxInGainCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: Audio plugin is not available", __FUNCTION__);
    }
}

void CAudioResourceImpl::setSourceVolume(const int &iSourceID, const uint16_t &iAbsoluteVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s,sourceID =  %d ,absoluteVolume=  %d", __FUNCTION__, iSourceID,iAbsoluteVolume);
    if(m_bAudioSettingAvailable)
    {
        audioPresCtrlTypes::sSourceVolume objSrcVolume(iAbsoluteVolume,iSourceID);
        m_pAudioSettingsProxy->SetSourceVolumeAsync(objSrcVolume,std::bind(&CAudioResourceImpl::onSourceVolumeAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: Audio plugin is not available", __FUNCTION__);
    }
}

void CAudioResourceImpl::toggleSource(CAudioEnums::EToggleDirection edirection)
{
    if(m_bAudioControlAvailable)
    {
        audioPresPluginTypes::eToggleEntSrcDirection etoggleDirection = static_cast<audioPresPluginTypes::eToggleEntSrcDirection::Literal>(edirection);
        m_pAudioPluginProxy->ToggleEntertainmentSourceAsync(etoggleDirection, std::bind(&CAudioResourceImpl::onToggleSourceAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: Audio plugin is not available", __FUNCTION__);
    }
}

void CAudioResourceImpl::toggleMicMute()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, __FUNCTION__);
    if(m_bAudioControlAvailable)
    {
        CommonAPI::CallStatus eCallStatus;
        m_pAudioSettingsProxy->ToggleMicMute(eCallStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"Audio setting proxy not available");
    }
}

void CAudioResourceImpl::setPdcMixModeState(bool bPdcMixModeState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Pdc Mix mode state: %d", __FUNCTION__, bPdcMixModeState);
    if(m_bAudioPluginAvailable)
    {
        m_pAudioPluginProxy->SetPdcMixModeAsync(bPdcMixModeState, std::bind(&CAudioResourceImpl::onPdcMixModeStatusCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: Audio plugin is not available", __FUNCTION__);
    }
}

void CAudioResourceImpl::setParkAssistVolume(const uint16_t &iParkAssistVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Request - Park assist volume: %d ", __FUNCTION__, iParkAssistVolume);
    setSourceVolume(SRC_INDICATION,iParkAssistVolume);
}

void CAudioResourceImpl::onStartUpVolumeCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors&)
{
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, false", __FUNCTION__);
    }
}

void CAudioResourceImpl::onSdvcStateCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors &)
{
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, false", __FUNCTION__);
    }
}

void CAudioResourceImpl::onSourceVolumeAsyncCb(const CallStatus &status, const audioPresCtrlTypes::eAudioPresErrors &)
{
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, false", __FUNCTION__);
    }
}

void CAudioResourceImpl::onStartupVolumeAttributeCb(int16_t iStartUpVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s startup Volume: %d ", __FUNCTION__, iStartUpVolume);

    m_iStartUpVolume = iStartUpVolume;
    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateStartUpVolume(iStartUpVolume);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
    }
}

int CAudioResourceImpl::getStartupVolume()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_iStartUpVolume;
}


void CAudioResourceImpl::onSdvcStateAttributeCb(bool bSdvcState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Sdvc State : %d ", __FUNCTION__, bSdvcState);
    m_bSpeedDependantVolume = bSdvcState;
    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateSpeedDependantVolume(bSdvcState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
    }
}

bool CAudioResourceImpl::getSpeedDependantVolumeStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return  m_bSpeedDependantVolume;
}

void CAudioResourceImpl::onPdcMixModeAttributeCb(bool bPdcMixModeState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Pdc Mix mode State : %d ", __FUNCTION__, bPdcMixModeState);
    m_bPdcMixModeStatus = bPdcMixModeState;
    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updatePdcMixMode(bPdcMixModeState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
    }
}

bool CAudioResourceImpl::getPdcMixModeStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s PdcMixMode : %d ", __FUNCTION__, m_bPdcMixModeStatus);
    return m_bPdcMixModeStatus;
}

void CAudioResourceImpl::onAuxOffsetGainAttributeCb(int16_t iAuxOffsetGain)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s : Response - AUX gain: %d ",__FUNCTION__, iAuxOffsetGain);

    m_iAuxGainValue = iAuxOffsetGain;

    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateAuxGainValue(iAuxOffsetGain);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: AudioDataEventProvider is null", __FUNCTION__);
    }
}

int CAudioResourceImpl::getAuxGainValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ",__FUNCTION__);
    return m_iAuxGainValue;
}

audioPresPluginTypes::eSourceGroup CAudioResourceImpl::getSourceGroup(int iSourceCategory)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, iSourceGroup is: %d", __FUNCTION__, iSourceCategory);
    EAudioSourceCategory eSourceCategory = static_cast<EAudioSourceCategory>(iSourceCategory);
    audioPresPluginTypes::eSourceGroup eAudioPressSourceGroup = audioPresPluginTypes::eSourceGroup::MEDIA;

    switch(eSourceCategory)
    {
    case SOURCE_CATEGORY_TUNER:
        eAudioPressSourceGroup = audioPresPluginTypes::eSourceGroup::TUNER;
        break;

    case SOURCE_CATEGORY_AUX:
        eAudioPressSourceGroup = audioPresPluginTypes::eSourceGroup::AUX;
        break;

    case SOURCE_CATEGORY_PROJECTION:
        eAudioPressSourceGroup = audioPresPluginTypes::eSourceGroup::PROJECTION;
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Media source group passed", __FUNCTION__);
        break;
    }
    return eAudioPressSourceGroup;
}

void CAudioResourceImpl::onAuxInGainCb(const CallStatus &callStatus, const audioPresPluginTypes::eAudioPresPluginErrors &audioPresStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, CallStatus: %d, audioPresStatus: %d", __FUNCTION__, static_cast<int>(callStatus), static_cast<int>(audioPresStatus));
}

void CAudioResourceImpl::onToggleSourceAsyncCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors &)
{
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, false", __FUNCTION__);
    }
}

void CAudioResourceImpl::onMicMuteStatusCb(bool bMicMuteStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s mic mute status : %d ", __FUNCTION__, bMicMuteStatus);

    m_bMicMuteStatus = bMicMuteStatus;
    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateMicMuteStatus(bMicMuteStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
    }
}

bool CAudioResourceImpl::getMicMuteStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_bMicMuteStatus;
}

void CAudioResourceImpl::onPlayBeepAsyncCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors& audioPresStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, CallStatus: %d, audioPresStatus: %d", __FUNCTION__, static_cast<int>(status), static_cast<int>(audioPresStatus));
}

void CAudioResourceImpl::onPdcMixModeStatusCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors &)
{
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, false", __FUNCTION__);
    }
}

void CAudioResourceImpl::onAudioPresetAttributeCb(string strPreset)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Response - preset %s ", __FUNCTION__, strPreset.c_str());
    m_strActiveAudioPreset = strPreset.c_str();

    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateAudioPresetSelection(strPreset);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
    }
}

const string &CAudioResourceImpl::getActiveAudioPreset()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_strActiveAudioPreset;
}

void CAudioResourceImpl::onVolumeUpdateEventCb(audioPresCtrlTypes::sSourceVolume objSrcVolume,
                                               bool bEventTriggeredByUser, audioPresCtrlTypes::eVolumeGroup eVolumeGroup)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s AbsoluteVolume: %d, SrcID: %d", __FUNCTION__,
             objSrcVolume.getAbsoluteVolume(), objSrcVolume.getSourceID());
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Event triggered by User: %d, VolumeGroup: %d", __FUNCTION__,
             bEventTriggeredByUser, static_cast<int> (eVolumeGroup));

    m_iActEntSourceVolume = objSrcVolume.getAbsoluteVolume();
    m_bIsVolumeUpdatedByUser = bEventTriggeredByUser;
    m_iVolumeGroup  = static_cast<int> (eVolumeGroup);
    m_iSourceId     = objSrcVolume.getSourceID();

    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateVolume(objSrcVolume.getAbsoluteVolume(), bEventTriggeredByUser,
                                            eVolumeGroup, objSrcVolume.getSourceID());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: m_pAudioEventProvider is NULL", __FUNCTION__);
    }
}

int CAudioResourceImpl::getVolumeGroup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_iVolumeGroup;
}

int CAudioResourceImpl::getSourceId()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_iSourceId;
}

int CAudioResourceImpl::getActiveEntSrcVolume()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_iActEntSourceVolume;
}

bool CAudioResourceImpl::getVolumeUpdatedByUserStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_bIsVolumeUpdatedByUser;
}

void CAudioResourceImpl::onActiveSrcMuteAttributeCb(bool  bActiveSourceMute)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Mute status: %d", __FUNCTION__, bActiveSourceMute);

    m_bMuteActive = bActiveSourceMute;

    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateSourceMuteState(bActiveSourceMute);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
    }
}

bool CAudioResourceImpl::getMuteStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_bMuteActive;
}

void CAudioResourceImpl::getSourceVolume(const int &iSourceID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s : sourceID: %d", __FUNCTION__, iSourceID);
    if(m_bAudioSettingAvailable)
    {
        audioPresCtrlTypes::eEntertainmentSrcs _srcID = (audioPresCtrlTypes::eEntertainmentSrcs::Literal) iSourceID;
        m_pAudioSettingsProxy->GetSourceVolumeAsync(_srcID,std::bind(&CAudioResourceImpl::onGetSourceVolumeAsyncCb,this, _1,_2,_3));
    }
}

void CAudioResourceImpl::onGetSourceVolumeAsyncCb(const CommonAPI::CallStatus& status, const audioPresCtrlTypes::eAudioPresErrors&, const audioPresCtrlTypes::sSourceVolume& volume)
{
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Success, source: %d, Volume: %d", __FUNCTION__, volume.getSourceID(), volume.getAbsoluteVolume());
        if((SRC_TEL_HANDSFREE == volume.getSourceID())) /** Phone volume **/
        {
            onVolumeUpdateEventCb(volume, false, audioPresCtrlTypes::eVolumeGroup::VU_PHONE_UPDATE);
        }
        else if(SRC_INDICATION == volume.getSourceID()) /** Park assist volume **/
        {
            onVolumeUpdateEventCb(volume, false, audioPresCtrlTypes::eVolumeGroup::VU_PROMPT_UPDATE);
        }
        else if(SRC_WARNING == volume.getSourceID())
        {
            onVolumeUpdateEventCb(volume, false, audioPresCtrlTypes::eVolumeGroup::VU_PROMPT_UPDATE);
        }
        else if(m_pAudioEventProvider)
        {
            m_pAudioEventProvider->updateVolume(
                        volume.getAbsoluteVolume(),
                        false,
                        audioPresCtrlTypes::eVolumeGroup::VU_NOUPDATE,
                        volume.getSourceID()
                        );
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: m_pAudioEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, CallStatus: %d", __FUNCTION__, static_cast<int>(status));
    }
}

void CAudioResourceImpl::onActiveAudioSourcesAttributeCb(
        const std::vector<audioPresCtrlTypes::SourceId> &vectSourceId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);

    m_vectActiveAudioSource.clear();

    if (!vectSourceId.empty() && m_pAudioEventProvider)
    {
        std::vector<uint16_t>::const_iterator itActiveSource =
                vectSourceId.begin();

        while(itActiveSource != vectSourceId.end())
        {
            m_vectActiveAudioSource.push_back(*itActiveSource);
            ++itActiveSource;
        }

        m_pAudioEventProvider->updateActiveAudioSourceList();

        //Get all available audio source current volume levels at 1st call for current session.
        for(uint i = 0; i < m_vectActiveAudioSource.size(); i++)
        {
            getSourceVolume(m_vectActiveAudioSource[i]);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "%s: Active Source Vector"
                                              " is empty. or m_pAudioEventProvider"
                                              " is NULL", __FUNCTION__);
    }

}

void CAudioResourceImpl::onSetAudioOffCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors& audioPresStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, CallStatus: %d, audioPresStatus: %d", __FUNCTION__, static_cast<int>(status), static_cast<int>(audioPresStatus));
}

void CAudioResourceImpl::switchToPreviousEntSourceCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors &audioPresStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, CallStatus: %d, audioPresStatus: %d", __FUNCTION__, static_cast<int>(status),static_cast<int>(audioPresStatus));
}

void CAudioResourceImpl::onAuxConnectionStateAttribute(const std::string &strAuxConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s - strAuxConnectionState: %s ", __FUNCTION__, strAuxConnectionState.c_str());

    m_strAuxConnectionStatus = strAuxConnectionState.c_str();
    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateAuxConnectionState(strAuxConnectionState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
    }
}

const string &CAudioResourceImpl::getAuxConnectionStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_strAuxConnectionStatus;
}

void CAudioResourceImpl::onUSBConnectionStateAttribute(const std::string &strUSBConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s - strUSBConnectionState: %s ", __FUNCTION__, strUSBConnectionState.c_str());

    m_strUsbConnectionStatus = strUSBConnectionState.c_str();

    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateUSBConnectionState(strUSBConnectionState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
    }
}

const string &CAudioResourceImpl::getUsbConnectionStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return m_strUsbConnectionStatus;
}

void CAudioResourceImpl::onIPODConnectionStateAttribute(const std::string &strIPODConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s - strIPODConnectionState: %s ", __FUNCTION__, strIPODConnectionState.c_str());

    m_strIpodConnectionStatus = strIPODConnectionState.c_str();
    if(m_pAudioEventProvider)
    {
        m_pAudioEventProvider->updateIPODConnectionState(strIPODConnectionState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioDataEventProvider is null");
    }
}

const string &CAudioResourceImpl::getIpodConnectionStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ", __FUNCTION__);
    return  m_strIpodConnectionStatus;
}

void CAudioResourceImpl::playFromSourceGroupAsyncCb(const CallStatus &eCallStatus, const audioPresPluginTypes::eAudioPresPluginErrors &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, eCallStatus: %d, eErrorType: %d", __FUNCTION__, static_cast<int>(eCallStatus), eErrorType.value_);
}


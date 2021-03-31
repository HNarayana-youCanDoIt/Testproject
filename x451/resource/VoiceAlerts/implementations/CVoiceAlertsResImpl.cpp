/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
***************************************************************
*/
/**
* @file         CVoiceAlertsResImpl.cpp
* @ingroup       HMIComponent
* @author        Guru Alingal
* CVoiceAlertsResImpl will be an interface to communicate to voice alert service
* and to pass on the information to upper layers.
*/

#include <VoiceAlerts/implementations/CVoiceAlertsResImpl.h>
#include <ResourceMaster.h>

CVoiceAlertsResImpl::CVoiceAlertsResImpl()
    : m_ePresence(VoiceAlertType::HuInfoFeaturePresence_enum::En_Not_Present),
      m_eAlert(VoiceAlertType::HuAlertState_enum::En_No_Warning),
      m_eMceAlert(VoiceAlertType::HuAlertStateMce_enum::En_No_Warning),
      m_eAlertStatus(VoiceAlertType::HuAlertStatus_enum::En_STATE_NO_ALERT),
      m_eHMISelection(VoiceAlertType::HuHMISelection_enum::En_Reserved),
      m_eDriveMode(VoiceAlertType::CurDriveModeSig_enum::En_Reserved),
      m_objVoiceAlertProxy(ResourceDeploymentConfig::getConfig().m_VoiceAlertProxy.domain,
                       ResourceDeploymentConfig::getConfig().m_VoiceAlertProxy.instance),
      m_pEventProvider(new CVoiceAlertsEventProvider()),
      m_bIsVoiceAlertAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s", __FUNCTION__);
    SUBSCRIBE(m_objVoiceAlertProxy,getProxyStatusEvent(),&CVoiceAlertsResImpl::VAProxyAvailabilityCb,_1 );
}

CVoiceAlertsResImpl::~CVoiceAlertsResImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s", __FUNCTION__);
    delete m_pEventProvider;
    m_pEventProvider = nullptr;
}

void CVoiceAlertsResImpl::VAProxyAvailabilityCb(AvailabilityStatus eStatus)
{
    if( CommonAPI::AvailabilityStatus::AVAILABLE== eStatus )
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, :true", __FUNCTION__);
        m_bIsVoiceAlertAvailable = true;

        SUBSCRIBE(m_objVoiceAlertProxy, getVasStatusAttribute().getChangedEvent(), &CVoiceAlertsResImpl::onVasStatusAttributeCb, _1 );
        SUBSCRIBE(m_objVoiceAlertProxy, getHuAlertStatusAttribute().getChangedEvent(), &CVoiceAlertsResImpl::onHuAlertStatusAttributeCb, _1 );
        SUBSCRIBE(m_objVoiceAlertProxy, getHuInfoFeaturePresenceAttribute().getChangedEvent(), &CVoiceAlertsResImpl::onHuInfoFeaturePresenceAttributeCb, _1 );
        SUBSCRIBE(m_objVoiceAlertProxy, getHuAlertHMISelectionAttribute().getChangedEvent(), &CVoiceAlertsResImpl::onHuAlertHMISelectionAttributeCb, _1 );
        SUBSCRIBE(m_objVoiceAlertProxy, getCurDriveModeSigAttribute().getChangedEvent(), &CVoiceAlertsResImpl::onCurDriveModeSigAttributeCb, _1 );
        SUBSCRIBE(m_objVoiceAlertProxy, getHuAlertStateAttribute().getChangedEvent(), &CVoiceAlertsResImpl::onGetHuAlertStateAttributeCb, _1);
        SUBSCRIBE(m_objVoiceAlertProxy, getHuAlertStateMceAttribute().getChangedEvent(), &CVoiceAlertsResImpl::onGetHuAlertStateMceAttribute, _1);
    }
    else
    {
        m_bIsVoiceAlertAvailable = false;
        LOG_WARNING(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, :false", __FUNCTION__);
    }
}

void CVoiceAlertsResImpl::onVasStatusAttributeCb(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: %d", __FUNCTION__, bStatus);
    if(NULL != m_pEventProvider)
    {
        m_pEventProvider->updateVasStatus(bStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, Event provider not created", __FUNCTION__);
    }
}

void CVoiceAlertsResImpl::onHuAlertStatusAttributeCb(VoiceAlertType::HuAlertStatus_enum eAlertStaus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: %d", __FUNCTION__, eAlertStaus.value_);
    if(NULL != m_pEventProvider)
    {
        m_eAlertStatus = eAlertStaus;
        m_pEventProvider->updateHuAlertStatus(eAlertStaus.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, Event provider not created", __FUNCTION__);
    }
}

void CVoiceAlertsResImpl::onGetHuAlertStateAttributeCb(VoiceAlertType::HuAlertState_enum eAlert)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: %d", __FUNCTION__, eAlert.value_);
    if(NULL != m_pEventProvider)
    {
        m_eAlert = eAlert;
        m_pEventProvider->updateHuAlertState(eAlert.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, Event provider not created", __FUNCTION__);
    }
}

void CVoiceAlertsResImpl::onGetHuAlertStateMceAttribute(VoiceAlertType::HuAlertStateMce_enum eMceAlert)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: %d", __FUNCTION__, eMceAlert.value_);
    if(m_pEventProvider)
    {
        m_eMceAlert = eMceAlert;
        m_pEventProvider->updateHuAlertMceState(m_eMceAlert.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, Event provider not created", __FUNCTION__);
    }
}

void CVoiceAlertsResImpl::onHuInfoFeaturePresenceAttributeCb(VoiceAlertType::HuInfoFeaturePresence_enum ePresence)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: Voice Alert Presence : %d", __FUNCTION__, ePresence.value_);
    if(NULL != m_pEventProvider)
    {
        m_ePresence = ePresence;
        m_pEventProvider->updateHuInfoFeaturePresence(ePresence.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, Event provider not created", __FUNCTION__);
    }
}

void CVoiceAlertsResImpl::onHuAlertHMISelectionAttributeCb(VoiceAlertType::HuHMISelection_enum eHMISelection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: Voice Alert Selection : %d", __FUNCTION__, eHMISelection.value_);
    if(NULL != m_pEventProvider)
    {
        m_eHMISelection = eHMISelection;
        m_pEventProvider->updateHuAlertHMISelection(eHMISelection.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, Event provider not created", __FUNCTION__);
    }
}

void CVoiceAlertsResImpl::onCurDriveModeSigAttributeCb(VoiceAlertType::CurDriveModeSig_enum eDriveMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: %d", __FUNCTION__, eDriveMode.value_);
    if(NULL != m_pEventProvider)
    {
        m_eDriveMode = eDriveMode;
        m_pEventProvider->updateCurDriveMode(eDriveMode.value_);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, Event provider not created", __FUNCTION__);
    }
}

CVoiceAlertsEventProvider *CVoiceAlertsResImpl::getEventProvider() const
{
    return m_pEventProvider;
}

void CVoiceAlertsResImpl::setVoiceAlertSelection(bool bVoiceAlertSelection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: VoiceAlertSelection %d", __FUNCTION__, bVoiceAlertSelection);
    if(m_bIsVoiceAlertAvailable)
    {
        m_objVoiceAlertProxy->setHuHMISelectionAsync(VoiceAlertType::HuHMISelection_enum::En_Voice_Alert, bVoiceAlertSelection, std::bind(&CVoiceAlertsResImpl::onHuHMISelectionAsyncCb,this, _1,_2));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VOICE_ALERTS," Voice alert Proxy not available");
    }
}

void CVoiceAlertsResImpl::onHuHMISelectionAsyncCb(const CallStatus &status, const VoiceAlertType::HuHMISelection_enum& )
{
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s ", __FUNCTION__);
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, true", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS,"%s, false", __FUNCTION__);
    }
}


int CVoiceAlertsResImpl::getVoiceAlertPresence()
{
    return static_cast<int>(m_ePresence);
}

int CVoiceAlertsResImpl::getCurrentVoiceAlert()
{
    return static_cast<int>(m_eAlert);
}

int CVoiceAlertsResImpl::getCurrentMceVoiceAlert()
{
    return m_eMceAlert;
}

int CVoiceAlertsResImpl::getCurrentState()
{
    return static_cast<int>(m_eAlertStatus);
}

int CVoiceAlertsResImpl::getHMISelectionState()
{
    return static_cast<int>(m_eHMISelection);
}

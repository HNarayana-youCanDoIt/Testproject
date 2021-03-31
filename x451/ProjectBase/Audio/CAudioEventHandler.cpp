/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CAudioEventHandler.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * This class is to handle Audio settings and Audio Controls events.
 */
#include "CAudioEventHandler.h"
#include "CAudioAdaptor.h"
#include "AudioResource/implementations/CAudioResourceImpl.h"
#include <ResourceFactory.hpp>
#include "CHMIMain.h"
#include "CDisplayManagerAdaptor.h"
#include "CMediaAdaptor.h"
#include "CAppleCarPlayAdaptor.h"
#include <PowerMode/CPowerModeAdaptor.h>

CAudioEventHandler::CAudioEventHandler(QObject *parent):
    QObject(parent),
    m_pAudioAdaptor(CAudioAdaptor::getInstance()),
    m_eAudioEntertainmentSrc(CAudioEnums::SRC_ENT_UNKNOWN)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    connectSignals();
}

CAudioEventHandler::~CAudioEventHandler()
{

}

void CAudioEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    CAudioResourceImpl* audioResource = static_cast<CAudioResourceImpl*>(ResourceFactory::getAudioResource());
    if(audioResource)
    {
        CAudioEventProvider* pAudioEventProvider = audioResource->getAudioDataEventProvider();

        if (pAudioEventProvider)
        {
            connect(pAudioEventProvider, SIGNAL(sigUpdateAudioPluginProxyAvailability(bool)), this, SLOT(sltUpdateAudioPluginProxyAvailability(bool)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigUpdateBassDataType(int)), this, SLOT(sltUpdateBassData(int)));
            connect(pAudioEventProvider, SIGNAL(sigUpdateMidDataType(int)), this, SLOT(sltUpdateMidData(int)));
            connect(pAudioEventProvider, SIGNAL(sigUpdateTrebleDataType(int)), this, SLOT(sltUpdateTrebleData(int)));
            connect(pAudioEventProvider, SIGNAL(sigUpdateBalanceDataType(int)), this, SLOT(sltUpdateBalanceData(int)));
            connect(pAudioEventProvider, SIGNAL(sigUpdateFadeDataType(int)), this, SLOT(sltUpdateFadeData(int)));
            connect(pAudioEventProvider, SIGNAL(sigActiveEntSource(CAudioEnums::EAudioEntertainmentSrcs)), this, SLOT(sltActiveEntSource(CAudioEnums::EAudioEntertainmentSrcs)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigTunerFMSrcStatus(bool)), this, SLOT(sltTunerFMSrcStatus(bool)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigTunerAMSrcStatus(bool)), this, SLOT(sltTunerAMSrcStatus(bool)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigMediaUSBSrcStatus(bool)), this, SLOT(sltMediaUSBSrcStatus(bool)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigMediaIPODSrcStatus(bool)), this, SLOT(sltMediaIPODSrcStatus(bool)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigMediaAUXSrcStatus(bool)), this, SLOT(sltMediaAUXSrcStatus(bool)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigMediaBTSrcStatus(bool)), this, SLOT(sltMediaBTSrcStatus(bool)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigUpdateAudioPresetChanged(string)), this, SLOT(sltUpdateAudioPresetChanged(string)));
            connect(pAudioEventProvider, SIGNAL(sigAUXConnectionStateChanged(string)), this, SLOT(sltUpdateAUXConnectionState(string)));
            connect(pAudioEventProvider, SIGNAL(sigUSBConnectionStateChanged(string)), this, SLOT(sltUpdateUSBConnectionState(string)));
            connect(pAudioEventProvider, SIGNAL(sigIPODConnectionStateChanged(string)), this, SLOT(sltUpdateIPODConnectionState(string)));
            connect(pAudioEventProvider, SIGNAL(sigUpdateSourceMuteState(bool)), this, SLOT(sltUpdateSourceMuteState(bool)));
            connect(pAudioEventProvider, SIGNAL(sigUpdateSpeedDependantVolume(bool)), this, SLOT(sltUpdateSpeedDependantVolume(bool)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigUpdateStartUpVolume(int)), this, SLOT(sltUpdateStartUpVolume(int)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigUpdateVoiceAlertVolume(int)), this, SLOT(sltUpdateVoiceAlertVolume(int)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigUpdateMicMuteStatus(bool)), this, SLOT(sltMicMuteStatusUpdated(bool)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigUpdatePdcMixModeState(bool)), this, SLOT(sltUpdatePdcMixModeState(bool)));
            connect(pAudioEventProvider, SIGNAL(sigUpdateActiveAudioSourceList()), this, SLOT(sltUpdateActiveAudioSourceList()), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigUpdateAuxGainValue(int)), this, SLOT(sltUpdateAuxGainValue(int)));
            connect(pAudioEventProvider, SIGNAL(sigUpdateVolume(ushort, bool, ushort, ushort)), this, SLOT(sltUpdateVolume(ushort, bool, ushort, ushort)), Qt::QueuedConnection);
            connect(pAudioEventProvider, SIGNAL(sigSourceStateUpdated(int,int)), this, SLOT(sltSourceStateUpdated(int, int)), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"pAudioEventProvider is NULL.");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"Resource returns as null from ResourceFactory");
    }
}

void CAudioEventHandler::sltUpdateAudioPluginProxyAvailability(bool bAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s", __FUNCTION__);
    if(m_pAudioAdaptor)
        m_pAudioAdaptor->updateAudioPluginProxyAvailability(bAvailability);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltUpdateBassData(int iBass)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(m_pAudioAdaptor)
        m_pAudioAdaptor->setBass(iBass);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltUpdateMidData(int iMid)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(m_pAudioAdaptor)
        m_pAudioAdaptor->setMid(iMid);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltUpdateTrebleData(int iTreble)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(m_pAudioAdaptor)
        m_pAudioAdaptor->setTreble(iTreble);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltUpdateBalanceData(int iBalance)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->setBalance(iBalance);
        m_pAudioAdaptor->setBalancePos(iBalance);
    }
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltUpdateFadeData(int iFade)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->setFader(iFade);
        m_pAudioAdaptor->setFaderPos(iFade);
    }
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltActiveEntSource(CAudioEnums::EAudioEntertainmentSrcs eActiveEntSource)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s eActiveEntSource : %d", __FUNCTION__ , eActiveEntSource);

    m_eAudioEntertainmentSrc = eActiveEntSource;

    /*
     * Fix for issue: 2580280: When CarPlay Media is active and user Change the source to
     * AM/FM from source drawer, the source drawer gets stuck and seen as empty.
     * The issue is happening becuase Tuner screen is very heavy and it takes more CPU
     * to create and at the same time Drawer Minimize animation also running, So for some
     * time Source drawer get stuck. So we put 150 milliseconds delay, to update the source
     * info, if last enetrtainment source was carplay media, and new source gets activated.
     *
     * Note: This code can be remove, If we optimize the tuner screen, so that it's creation will be light.
     */
    /* Whenever MediaOff and source change then need to delay the call for takeAction
     * else perform the regular checks
     */
    int iDrawersAnimWaitTime = 0;
    if(CPowerModeEnums::VPM_MEDIA_OFF == CPowerModeAdaptor::getInstance().getPowerModeStatus())
    {
        iDrawersAnimWaitTime = 250;
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s Coming out of mediaOff on source change", __FUNCTION__);

    }
    else if ((CAudioEnums::SRC_CARPLAY_MEDIA == CAudioAdaptor::getInstance()->activeEntSrc())
             || ((CAudioEnums::SRC_ENT_UNKNOWN == CAudioAdaptor::getInstance()->activeEntSrc())
                 && (CAudioEnums::SRC_CARPLAY_MEDIA == CAudioAdaptor::getInstance()->prevActiveEntSrc()))
             )
    {
        iDrawersAnimWaitTime = 150;
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s Carplay media was previous source", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s Carplay media was not previous source, So not adding any delay.", __FUNCTION__);
    }

    if (iDrawersAnimWaitTime > 0)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s Adding iDrawersAnimWaitTime:%d milisecond delay for switching entertainment source on HMI", __FUNCTION__, iDrawersAnimWaitTime);
        QTimer::singleShot(iDrawersAnimWaitTime, this, SLOT(sltTakeActionOnEntSourceActivation()));
    }
    else
    {
        sltTakeActionOnEntSourceActivation();
    }
}

void CAudioEventHandler::sltTunerFMSrcStatus(bool bFmStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s fmStatus: %d",__FUNCTION__, bFmStatus);
    if(m_pAudioAdaptor)
        m_pAudioAdaptor->updateFMSrcStatus(bFmStatus);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltTunerAMSrcStatus(bool bAmStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s amStatus: %d" ,__FUNCTION__, bAmStatus);
    if(m_pAudioAdaptor)
        m_pAudioAdaptor->updateAMSrcStatus(bAmStatus);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltMediaUSBSrcStatus(bool bUsbStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s usbStatus: %d" ,__FUNCTION__, bUsbStatus);
    if(m_pAudioAdaptor)
        m_pAudioAdaptor->updateUSBSrcStatus(bUsbStatus);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltMediaIPODSrcStatus(bool bIpodStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s ipodStatus: %d" ,__FUNCTION__, bIpodStatus);
    if(m_pAudioAdaptor)
        m_pAudioAdaptor->updateIPODSrcStatus(bIpodStatus);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");

}

void CAudioEventHandler::sltMediaAUXSrcStatus(bool bAuxStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s auxStatus: %d" ,__FUNCTION__, bAuxStatus);
    if(m_pAudioAdaptor)
        m_pAudioAdaptor->updateAUXSrcStatus(bAuxStatus);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltMediaBTSrcStatus(bool bBTStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s btStatus: %d" ,__FUNCTION__, bBTStatus);
    if(m_pAudioAdaptor)
        m_pAudioAdaptor->updateBTSrcStatus(bBTStatus);
    else
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
}

void CAudioEventHandler::sltUpdateAudioPresetChanged(string strPresetName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->updateAudioPreset(QString::fromStdString(strPresetName));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdateAUXConnectionState(const string &strAUXConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s", __FUNCTION__);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->updateAUXConnectionState(QString::fromStdString(strAUXConnectionState));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdateUSBConnectionState(const string &strUSBConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s", __FUNCTION__);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->updateUSBConnectionState(QString::fromStdString(strUSBConnectionState));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdateIPODConnectionState(const string &strIPODConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s", __FUNCTION__);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->updateIPODConnectionState(QString::fromStdString(strIPODConnectionState));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdateSourceMuteState(bool bMuteStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Mute Active %d" ,__FUNCTION__, bMuteStatus);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->updateMuteState(bMuteStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdateSpeedDependantVolume(bool bSpeedDependantVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Speed Dependant volume %d" ,__FUNCTION__, bSpeedDependantVolume);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->setSpeedDependantVolume(bSpeedDependantVolume);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdateStartUpVolume(int iStartUpVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Start up volume %d" ,__FUNCTION__, iStartUpVolume);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->setStartUpVolume(iStartUpVolume);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdateVoiceAlertVolume(int iVoiceAlertVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Voice Alert volume %d" ,__FUNCTION__, iVoiceAlertVolume);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->setVoiceAlertVolume(iVoiceAlertVolume);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltMicMuteStatusUpdated(bool bMicMuteStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s mic mute status %d" ,__FUNCTION__, bMicMuteStatus);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->micMuteStatusUpdated(bMicMuteStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdatePdcMixModeState(bool bPdcMixModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s pdc mix mode status %d" ,__FUNCTION__, bPdcMixModeStatus);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->setPdcMixModeStatus(bPdcMixModeStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdateAuxGainValue(int iAuxGainValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, AUX gain value: %d" ,__FUNCTION__, iAuxGainValue);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->setAuxGainValue(iAuxGainValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdateActiveAudioSourceList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);

    if( m_pAudioAdaptor )
    {
        emit m_pAudioAdaptor->sigActiveAudioSourceListUpdated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor is NULL ");
    }
}

void CAudioEventHandler::sltUpdateVolume(
        ushort usActiveSourceVolume,
        bool bIsVolumeUpdatedByUser,
        ushort usActiveSourceVolumeUpdateGroup,
        ushort  usSourceId
        )
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s: usActiveSourceVolume: %d,"
                                       " bIsVolumeUpdatedByUser:"
                                       " %d, usActiveSourceVolumeUpdateGroup:"
                                       " %d, usSourceId: %d", __FUNCTION__,
             usActiveSourceVolume, bIsVolumeUpdatedByUser,
             usActiveSourceVolumeUpdateGroup, usSourceId);

    if (CAudioAdaptor::getInstance())
    {
        CAudioAdaptor::getInstance()->updateVolume(
                    usActiveSourceVolume,
                    bIsVolumeUpdatedByUser,
                    static_cast<CAudioEnums::EVolumeUpdateGroup>
                    (usActiveSourceVolumeUpdateGroup),
                    usSourceId
                    );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"%s: AudioAdaptor is NULL.",
                    __FUNCTION__);
    }
}

void CAudioEventHandler::sltSourceStateUpdated(int iSourceId, int iSourceState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s", __FUNCTION__);
    if(m_pAudioAdaptor)
    {
        m_pAudioAdaptor->sourceStateInfoUpdated(iSourceId, iSourceState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO," audioAdaptor not available");
    }
}

void CAudioEventHandler::sltTakeActionOnEntSourceActivation()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s m_eAudioEntertainmentSrc : %d", __FUNCTION__ , m_eAudioEntertainmentSrc);

    bool bIsSourceChangeRequestedByUser = CAudioAdaptor::getInstance()->isSourceChangeRequestedByUser();

    CAudioAdaptor::getInstance()->updateActiveEntSrc(m_eAudioEntertainmentSrc);
    CHMIMain::getSM()->getSCI_Audio()->set_currentActiveSrc(m_eAudioEntertainmentSrc);

    //Fix me: This needs to be revisit as to notify the state machine as signal raise_evEntSourceChanged(iActiveEntSource);

    switch (m_eAudioEntertainmentSrc)
    {
    case SRC_TUNER_FM:
    case SRC_TUNER_AM:
    case SRC_TUNER_DRM:
    {
        // Wakeup the display.
        CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);

        CHMIMain::getSM()->getSCI_Audio()->set_activeSrcCategory(CAudioEnums::SOURCE_CATEGORY_TUNER);

        /*
         * If source change is requested by user or Audio state is active and Tuner
         * category source gets activated, then only screen/state transition
         * should happen to active source screen/state.
         */
        if (bIsSourceChangeRequestedByUser || CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio))
        {
            CHMIMain::getSM()->raise_evTunerActivated();
            CAudioAdaptor::getInstance()->setIsSourceChangeRequestedByUser(false);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s: Source chnage is not requested by user, No screen"
                                               " transition will happen. " , __FUNCTION__);
        }
    }
        break;
    case SRC_USB1:
    case SRC_BT_A2DP2:
    case SRC_BT_A2DP1:
    case SRC_AUDIO_AUX:
    case CAudioEnums::SRC_IPOD:
    {
        // Wakeup the display.
        CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);
        CHMIMain::getSM()->getSCI_Audio()->set_activeSrcCategory(CAudioEnums::SOURCE_CATEGORY_MEDIA);

        /*
         * If source change is requested by user or Audio state is
         * active and Meida category source gets activated, then only screen/state transition
         * should happen to active source screen/state.
         */
        if (bIsSourceChangeRequestedByUser || CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio))
        {
            CMediaAdaptor::getInstance().requestMediaActivation(true);
            CAudioAdaptor::getInstance()->setIsSourceChangeRequestedByUser(false);
        }
        else
        {
            CMediaAdaptor::getInstance().requestMediaActivation(false);
            LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s: Source chnage is not requested by user, No screen"
                                               " transition will happen. " , __FUNCTION__);
        }
    }
        break;
    case SRC_CARPLAY_MEDIA:
    case SRC_GAL_MEDIA:
    case SRC_CARLIFE_MEDIA:
    case SRC_APPLINK_MEDIA:
    case SRC_SAL_MEDIA:
    {
        // Wakeup the display.
        CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);
    }
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s In default case, m_eAudioEntertainmentSrcs: %d" , __FUNCTION__, m_eAudioEntertainmentSrc);
        CHMIMain::getSM()->getSCI_Audio()->set_activeSrcCategory(CAudioEnums::SOURCE_CATEGORY_UNKNOWN);
    }
        break;
    }
}

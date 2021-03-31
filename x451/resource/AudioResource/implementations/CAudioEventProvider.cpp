/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CAudioEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CAudioEventProvider, Class to send signals to Audio Application layer on Audio Resource events
 */
#include "CAudioEventProvider.h"
#include "logging.h"

CAudioEventProvider::CAudioEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
}

CAudioEventProvider::~CAudioEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s", __FUNCTION__);
}

void CAudioEventProvider::updateAudioPluginProxyAvailability(bool bAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s", __FUNCTION__);
    emit sigUpdateAudioPluginProxyAvailability(bAvailability);
}

void CAudioEventProvider::updateBassData(int iBass)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigUpdateBassDataType(iBass);
}

void CAudioEventProvider::updateMidData(int iMid)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigUpdateMidDataType(iMid);
}

void CAudioEventProvider::updateTrebleData(int iTreble)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigUpdateTrebleDataType(iTreble);
}

void CAudioEventProvider::updateBalanceData(int iBalance)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigUpdateBalanceDataType(iBalance);
}

void CAudioEventProvider::updateFadeData(int iFade)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigUpdateFadeDataType(iFade);
}

void CAudioEventProvider::activeEntSource(CAudioEnums::EAudioEntertainmentSrcs eActiveEntSourceID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigActiveEntSource(eActiveEntSourceID);
}

void CAudioEventProvider::updateFMstatus(bool bFmstatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigTunerFMSrcStatus(bFmstatus);
}

void CAudioEventProvider::updateAMstatus(bool bAmstatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigTunerAMSrcStatus(bAmstatus);
}

void CAudioEventProvider::updateUSBstatus(bool bUsbstatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigMediaUSBSrcStatus(bUsbstatus);
}

void CAudioEventProvider::updateIPODstatus(bool bIpodstatus)
{
   LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
   emit sigMediaIPODSrcStatus(bIpodstatus);
}

void CAudioEventProvider::updateDRMstatus(bool bDrmstatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigTunerDRMSrcStatus(bDrmstatus);
}

void CAudioEventProvider::updateBTstatus(bool bBTstatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigMediaBTSrcStatus(bBTstatus);
}

void CAudioEventProvider::updateAUXstatus(bool bAuxstatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigMediaAUXSrcStatus(bAuxstatus);
}

void CAudioEventProvider::updateAudioPresetSelection(string strPresetName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigUpdateAudioPresetChanged(strPresetName);
}

void CAudioEventProvider::updateAuxConnectionState(const string &strAUXConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s", __FUNCTION__);
    emit sigAUXConnectionStateChanged(strAUXConnectionState);
}

void CAudioEventProvider::updateUSBConnectionState(const string &strUSBConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s", __FUNCTION__);
    emit sigUSBConnectionStateChanged(strUSBConnectionState);
}

void CAudioEventProvider::updateIPODConnectionState(const string &strIPODConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s", __FUNCTION__);
    emit sigIPODConnectionStateChanged(strIPODConnectionState);
}

void CAudioEventProvider::updateSourceMuteState(bool bMuteStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigUpdateSourceMuteState(bMuteStatus);
}

void CAudioEventProvider::updateSpeedDependantVolume(bool bSpeeddepandantVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigUpdateSpeedDependantVolume(bSpeeddepandantVolume);
}

void CAudioEventProvider::updateStartUpVolume(int iStartUpVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, startUp Volume : %d", __FUNCTION__, iStartUpVolume);
    emit sigUpdateStartUpVolume(iStartUpVolume);
}

void CAudioEventProvider::updateVolume(ushort usActiveSourceVolume, bool bIsVolumeUpdatedByUser,
                                       ushort usActiveSourceVolumeUpdateGroup, ushort  usSourceId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);

    emit sigUpdateVolume(usActiveSourceVolume, bIsVolumeUpdatedByUser, usActiveSourceVolumeUpdateGroup, usSourceId);
}

void CAudioEventProvider::updateVoiceAlertVolume(int iVoiceAlertVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, voice alert Volume : %d", __FUNCTION__, iVoiceAlertVolume);
    emit sigUpdateVoiceAlertVolume(iVoiceAlertVolume);
}

void CAudioEventProvider::updateMicMuteStatus(bool bMicMuteStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, mic mute status : %d", __FUNCTION__, bMicMuteStatus);
    emit sigUpdateMicMuteStatus(bMicMuteStatus);
}

void CAudioEventProvider::updateAuxGainValue(int iAuxGainValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, AuxGainStatus : %d", __FUNCTION__, iAuxGainValue);
    emit sigUpdateAuxGainValue(iAuxGainValue);
}

void CAudioEventProvider::updatePdcMixMode(bool bPdcMixModeState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, PDC Mix mode state : %d", __FUNCTION__, bPdcMixModeState);
    emit sigUpdatePdcMixModeState(bPdcMixModeState);
}

void CAudioEventProvider::updateActiveAudioSourceList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    emit sigUpdateActiveAudioSourceList();
}

void CAudioEventProvider::updateSourceState(uint uiSourceId, int iSourceState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s", __FUNCTION__);
    emit sigSourceStateUpdated(uiSourceId, iSourceState);
}

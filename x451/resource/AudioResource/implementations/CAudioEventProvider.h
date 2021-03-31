/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CAudioEventProvider.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CAudioEventProvider, Class to send signals to Audio Application layer on Audio Resource events
 */

#ifndef CAUDIOEVENTPROVIDER_H
#define CAUDIOEVENTPROVIDER_H

#include <QObject>
#include <string>
#include "Audio/CAudioEnums.h"
using namespace std;

class CAudioEventProvider: public QObject
{
    Q_OBJECT

public:
    CAudioEventProvider(QObject* pParent = 0);
    ~CAudioEventProvider();

signals:

    /**
     * @brief sigUpdateAudioPluginProxyAvailability This function is called internally when proxy availability value changed and
     *           consumed by the application layer.
     * @param bAvailability
     * @return void
     */
    void sigUpdateAudioPluginProxyAvailability(bool bAvailability);

    /**
    * @brief	This function is called internally when bass value changed and
    *           consumed by the application layer.
    * @param	iBass: bass value.
    * @return	void.
    */
    void sigUpdateBassDataType(int iBass);

    /**
    * @brief	This function is called internally when mid value changed and
    *           consumed by the application layer.
    * @param	iMid: mid value.
    * @return	void.
    */
    void sigUpdateMidDataType(int iMid);

    /**
    * @brief	This function is called internally when treble value changed and
    *           consumed by the upper layer.
    * @param	iTreble: treble value.
    * @return	void.
    */
    void sigUpdateTrebleDataType(int iTreble);

    /**
    * @brief	This function is called internally when balance value changed and
    *           consumed by the application layer.
    * @param	ibalance: balance value.
    * @return	void.
    */
    void sigUpdateBalanceDataType(int ibalance);

    /**
    * @brief	This function is called internally when fade value changed and
    *           consumed by the application layer.
    * @param	ifade: fade value.
    * @return	void.
    */
    void sigUpdateFadeDataType(int ifade);

    /**
    * @brief	This function is called internally when active entertainment source value changed and
    *           consumed by the application layer.
    * @param	eActiveEntSourceID: iActiveEntSourceID will get the active source ID.
    * @return	void.
    */
    void sigActiveEntSource(CAudioEnums::EAudioEntertainmentSrcs eActiveEntSourceID);

    /**
    * @brief	This function is called internally when Tuner FM source value changed and
    *           consumed by the application layer.
    * @param	m_bTunerFMActive: m_bTunerFMActive will get the active FM status.
    * @return	void.
    */
    void sigTunerFMSrcStatus(bool bTunerFMActive);

    /**
    * @brief	This function is called internally when Tuner AM source value changed and
    *           consumed by the application layer.
    * @param	m_bTunerAMActive: m_bTunerFMActive will get the active AM status.
    * @return	void.
    */
    void sigTunerAMSrcStatus(bool bTunerAMActive);

    /**
    * @brief	This function is called internally when Tuner DRM source value changed and
    *           consumed by the application layer.
    * @param	m_bTunerDRMActive: m_bTunerDRMActive will get the active DRM status.
    * @return	void.
    */
    void sigTunerDRMSrcStatus(bool bTunerDRMActive);

    /**
    * @brief	This function is called internally when USB source value changed and
    *           consumed by the application layer.
    * @param	m_bMediaUSB1Active: m_bMediaUSB1Active will get the active USB status.
    * @return	void.
    */
    void sigMediaUSBSrcStatus(bool bMediaUSB1Active);

    /**
    * @brief	This function is called internally when IPOD source value changed and
    *           consumed by the application layer.
    * @param	bMediaIPODActive: bMediaIPODActive will get the active IPOD status.
    * @return	void.
    */
    void sigMediaIPODSrcStatus(bool bMediaIPODActive);

    /**
    * @brief	This function is called internally when BT source value changed and
    *           consumed by the application layer.
    * @param	m_bMediaBTActive: m_bMediaBTActive will get the active BT status.
    * @return	void.
    */
    void sigMediaBTSrcStatus(bool bMediaBTActive);

    /**
    * @brief	This function is called internally when AUX source value changed and
    *           consumed by the application layer.
    * @param	m_bMediaAUXActive: m_bMediaAUXActive will get the active AUX status.
    * @return	void.
    */

    void sigMediaAUXSrcStatus(bool bMediaAUXActive);

    /**
     * @brief sigUpdateAudioPresetChanged : This signal gets emitted on audio preset change
     * @param strPresetName is passed as an argument
     * @return	void.
     */
    void sigUpdateAudioPresetChanged(string strPresetName);

    /**
     * @brief sigAUXConnectionStateChanged : This signal gets emitted on AUX connection state change
     * @param strAUXConnectionState : String connection state
     * @return	void
     */
    void sigAUXConnectionStateChanged(string strAUXConnectionState);

    /**
     * @brief sigUSBConnectionStateChanged : This signal gets emitted on USB connection state change
     * @param strUSBConnectionState : String connection state
     * @return	void
     */
    void sigUSBConnectionStateChanged(string strUSBConnectionState);

    /**
     * @brief sigIPODConnectionStateChanged : This signal gets emitted on IPOD connection state change
     * @param strIPODConnectionState : String connection state
     * @return	void
     */
    void sigIPODConnectionStateChanged(string strIPODConnectionState);

    /**
     * @brief   sigUpdateVolume : This signal gets emitted on active source volume
     *          change.
     * @param   usActiveSourceVolume: Active source volume.
     * @param   bIsVolumeUpdatedByUser:  bIsVolumeUpdatedByUser will be true if
     *          volume is updated by user else false.
     * @param   usActiveSourceVolumeUpdateGroup: Volume update source group, for
     *          which volume gets changed.
     * @param   usSourceId: sourceId for which volume gets updated.
     * @return	void.
     */
    void sigUpdateVolume(ushort usActiveSourceVolume,
                         bool bIsVolumeUpdatedByUser,
                         ushort usActiveSourceVolumeUpdateGroup,
                         ushort usSourceId
                         );

    /**
     * @brief sigUpdateSourceMuteState : This signal gets emitted on active source mute change
     * @param bMuteStatus: bMuteStatus will get active source mute status.
     * @return	void.
     */
    void sigUpdateSourceMuteState(bool bMuteStatus);

    /**
     * @brief sigUpdateSpeedDependantVolume : This signal gets emitted on speed depandant volume change
     * @param bSpeeddepandantVolume: bSpeeddepandantVolume will get speed depandant volume status.
     * @return	void.
     */
    void sigUpdateSpeedDependantVolume(bool bSpeeddepandantVolume);

    /**
     * @brief sigUpdateStartUpVolume : This signal gets emitted on start up volume change
     * @param iStartUpVolume: iStartUpVolume will get startup volume status.
     * @return	void.
     */
    void sigUpdateStartUpVolume(int iStartUpVolume);

    /**
     * @brief sigUpdateVoiceAlertVolume : This signal gets emitted on voice alert volume change
     * @param iVoiceAlertVolume: iVoiceAlertVolume will get voice alert volume status.
     * @return	void.
     */
    void sigUpdateVoiceAlertVolume(int iVoiceAlertVolume);

    /**
     * @brief   Signal that shall be emited to notify mic mute status is received.
     * @param   bMicMuteStatus   - mic mute status, TRUE if mic is muted, false otherwise.
     * @return	void.
     */
    void sigUpdateMicMuteStatus(bool bMicMuteStatus);

    /**
     * @brief sigUpdatePdcMixModeState : This signal gets emitted on pdc mix mode status change
     * @param bPdcMixMode: bPdcMixMode will get pdc mix mode status.
     * @return	void.
     */
    void sigUpdatePdcMixModeState(bool bPdcMixMode);

    /**
     * @brief sigUpdateAuxGainValue : This signal gets emitted on AUX gain value change
     * @param iAuxGainValue: will get AUX gain value.
     * @return	void.
     */
    void sigUpdateAuxGainValue(int iAuxGainValue);

    /**
     * @brief   sigUpdateActiveAudioSourceList : This signal gets emitted to
     *          inform the Adaptor layer that the ActiveAudioSource List is
     *          updated.
     * @param   void.
     * @return  void.
     */
    void sigUpdateActiveAudioSourceList();

    /**
     * @brief   sigSourceStateUpdated : This signal gets emitted to
     *          inform the Adaptor layer that the source state information is received.
     * @param   iSourceId : source id for which state information is received.
     * @param   iSourceState : current state of the source.
     * @return  void.
     */
    void sigSourceStateUpdated(int iSourceId, int iSourceState);

public:

    /**
     * @brief updateAudioPluginProxyAvailability update the status of the audio plugin proxy available/ unavailable
     * @param bAvailability status true / false
     * @return	void
     */
    void updateAudioPluginProxyAvailability(bool bAvailability);

    /**
    * @brief	This function is called from resource layer when bass data has updated.
    * @param	iBass: bass value.
    * @return	void.
    */
    void updateBassData(int iBass);

    /**
    * @brief	This function is called from resource layer when mid data has updated.
    * @param	iMid: mid value.
    * @return	void.
    */
    void updateMidData(int iMid);

    /**
    * @brief	This function is called from resource layer when treble data has updated.
    * @param	iTreble: treble value.
    * @return	void.
    */
    void updateTrebleData(int iTreble);

    /**
    * @brief	This function is called from resource layer when balance data has updated.
    * @param	iBalance: balance value.
    * @return	void.
    */
    void updateBalanceData(int iBalance);

    /**
    * @brief	This function is called from resource layer when fade data has updated.
    * @param	iFade: fade value.
    * @return	void.
    */
    void updateFadeData(int iFade);

    /**
    * @brief	This function is called from resource layer when active entertainment source has updated.
    * @param	eActiveEntSourceID: activeEntSourceID will get the active entertainment source ID.
    * @return	void.
    */
    void activeEntSource(CAudioEnums::EAudioEntertainmentSrcs eActiveEntSourceID);

    /**
    * @brief	This function is called from resource layer when FM status has updated.
    * @param	bFmstatus: fmstatus will have fm value.
    * @return	void.
    */
    void updateFMstatus(bool bFmstatus);

    /**
    * @brief	This function is called from resource layer when AM status has updated.
    * @param	bAmstatus: amstatus will have am value.
    * @return	void.
    */
    void updateAMstatus(bool bAmstatus);

    /**
    * @brief	This function is called from resource layer when DRM status has updated.
    * @param	bDrmstatus: drmstatus will have drm value.
    * @return	void.
    */
    void updateDRMstatus(bool bDrmstatus);

    /**
    * @brief	This function is called from resource layer when USB status has updated.
    * @param	bUsbstatus: usbstatus will have am value.
    * @return	void.
    */
    void updateUSBstatus(bool bUsbstatus);

    /**
    * @brief	This function is called from resource layer when IPOD status has updated.
    * @param	bIpodstatus: bIpodstatus will have am value.
    * @return	void.
    */
    void updateIPODstatus(bool bIpodstatus);

    /**
    * @brief	This function is called from resource layer when BT status has updated.
    * @param	bBTstatus: btstatus will have bt value.
    * @return	void.
    */
    void updateBTstatus(bool bBTstatus);

    /**
    * @brief	This function is called from resource layer when AUX status has updated.
    * @param	bAuxstatus: auxstatus will have aux value.
    * @return	void.
    */
    void updateAUXstatus(bool bAuxstatus);

    /**
    * @brief	This function is called from resource layer when audio preset is changed.
    * @param	presetName: Name of the preset to be updated
    * @return	void.
    */
    void updateAudioPresetSelection(string strPresetName);

    /**
    * @brief	updateAuxConnectionState - This function is called from resource layer when AUX connection state is changed.
    * @param	strAUXConnectionState: Connection state
    * @return	void
    */
    void updateAuxConnectionState(const string &strAUXConnectionState);

    /**
    * @brief	updateUSBConnectionState - This function is called from resource layer when USB connection state is changed.
    * @param	strUSBConnectionState: Connection state
    * @return	void
    */
    void updateUSBConnectionState(const string &strUSBConnectionState);

    /**
    * @brief	updateIPODConnectionState - This function is called from resource layer when IPOD connection state is changed.
    * @param	strIPODConnectionState: Connection state
    * @return	void
    */
    void updateIPODConnectionState(const string &strIPODConnectionState);

    /**
    * @brief	updateVolume: This function is called from resource layer when
    *           volume update happens for any source.
    * @param	usActiveSourceVolume: usActiveSourceVolume will hold active
    *           source volume.
    * @param    bIsVolumeUpdatedByUser: bIsVolumeUpdatedByUser will be true if
    *           user updates the volume else false.
    * @param    usActiveSourceVolumeUpdateGroup: This param holds the source
    *           group, for which the volume gets updated.
    * @param    usSourceId: sourceId for which volume gets updated.
    * @return	void.
    */
    void updateVolume(
            ushort  usActiveSourceVolume,
            bool    bIsVolumeUpdatedByUser,
            ushort  usActiveSourceVolumeUpdateGroup,
            ushort  usSourceId
            );

    /**
    * @brief	This function is called from resource layer when active source mute is changed.
    * @param	bMuteStatus: bMuteStatus will have activate source mute state value.
    * @return	void.
    */
    void updateSourceMuteState(bool bMuteStatus);

    /**
    * @brief	This function is called from resource layer when speed depandant volume status is changed.
    * @param	iSpeeddepandantVolume: iSpeeddepandantVolume will have speed dependant volume status.
    * @return	void.
    */
    void updateSpeedDependantVolume(bool bSpeeddepandantVolume);

    /**
    * @brief	This function is called from resource layer when start up volume is changed.
    * @param	iStartUpVolume: iStartUpVolume will have start up volume value.
    * @return	void.
    */
    void updateStartUpVolume(int iStartUpVolume);

    /**
    * @brief	This function is called from resource layer when voice alert volume is changed.
    * @param	iVoiceAlertVolume: iVoiceAlertVolume will have voice alert volume value.
    * @return	void.
    */
    void updateVoiceAlertVolume(int iVoiceAlertVolume);

    /**
    * @brief	Method to inform audio adapter layer regarding mic mute status.
    * @param	bMicMuteStatus   - mic mute status, TRUE if mic is muted, false otherwise.
    * @return	void.
    */
    void updateMicMuteStatus(bool bMicMuteStatus);

    /**
    * @brief	This function is called from resource layer when AUX gain value is changed.
    * @param	iAuxGainValue - will have AUX gain status.
    * @return	void.
    */
    void updateAuxGainValue(int iAuxGainValue);

    /**
    * @brief	This function is called from resource layer when voice alert volume is changed.
    * @param	bPdcMixModeState: bPdcMixModeState will have pdc mix mode state.
    * @return	void.
    */
    void updatePdcMixMode(bool bPdcMixModeState);

    /**
     * @brief   updateActiveAudioSource: his function is used to emit the
     *          signal to Adaptor layer to update the active audio source.
     * @param   void
     * @return  void.
     */
    void updateActiveAudioSource();

    /**
     * @brief   updateActiveAudioSourceList: This function is used to emit the
     *          signal to Adaptor layer to update the active audio source list.
     * @param   void
     * @return  void.
     */
    void updateActiveAudioSourceList();

    /**
     * @brief   updateSourceState: This function is used to emit the
     *          signal to adaptor layer to update the source state information.
     * @param   uiSourceId : source id for which state information is received.
     * @param   iSourceState : current state of the source
     * @return  void.
     */
    void updateSourceState(uint uiSourceId, int iSourceState);
};

#endif // CAUDIOEVENTPROVIDER_H

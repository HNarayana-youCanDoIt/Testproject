/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CAudioEventHandler.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * This class is to handle Audio settings and Audio Control events.
 */
#ifndef CAUDIOEVENTHANDLER_H
#define CAUDIOEVENTHANDLER_H

#include <QObject>
#include "CAudioAdaptor.h"
#include "StateMachine_TML_HMI_SM.h"
#include "AudioResource/implementations/CDataAudioManger.h"

/**
 * @brief The CAudioEventHandler class: This class is to handle Audio settings events.
 *          Audio resource event provider will emit signals and those will be handled here.
 */
class CAudioEventHandler: public QObject
{
    Q_OBJECT

public:
    CAudioEventHandler(QObject* parent = 0);
    ~CAudioEventHandler();

public slots:

    /**
    * @brief	sltUpdateAudioPluginProxyAvailability This function will update proxy availability data received from Audio Resource layer.
    * @param	bAvailablility: proxy availability true /false
    * @return	void
    */
    void sltUpdateAudioPluginProxyAvailability(bool bAvailability);

    /**
    * @brief	This function will update bass data received from Audio Resource layer.
    * @param	iBass: bass value from audioPresCtrl.
    * @return	void
    */
    void sltUpdateBassData(int iBass);

    /**
    * @brief	This function will update mid data received from Audio Resource layer.
    * @param	iMid: mid value from audioPresCtrl.
    * @return	void
    */
    void sltUpdateMidData(int iMid);

    /**
    * @brief	This function will update treble data received from Audio Resource layer.
    * @param	iTreble: treble value from audioPresCtrl.
    * @return	void
    */
    void sltUpdateTrebleData(int iTreble);

    /**
    * @brief	This function will update balance data received from Audio Resource layer.
    * @param	iBalance: balance value from audioPresCtrl.
    * @return	void
    */
    void sltUpdateBalanceData(int iBalance);

    /**
    * @brief	This function will update fade data received from Audio Resource layer.
    * @param	iFade: fade value from audioPresCtrl.
    * @return	void
    */
    void sltUpdateFadeData(int iFade);

    /**
    * @brief	This function will update active entertainment source received from Audio Resource layer.
    * @param	eActiveEntSource: eActiveEntSource value from audioPresCtrl.
    * @return	void
    */
    void sltActiveEntSource(CAudioEnums::EAudioEntertainmentSrcs eActiveEntSource);

    /**
    * @brief	This function will update FM status received from Audio Resource layer.
    * @param	bFmStatus: fmStatus value from audioPresCtrl.
    * @return	void
    */
    void sltTunerFMSrcStatus(bool bFmStatus);

    /**
    * @brief	This function will update AM status received from Audio Resource layer.
    * @param	bAmStatus: amStatus value from audioPresCtrl.
    * @return	void
    */
    void sltTunerAMSrcStatus(bool bAmStatus);

    /**
    * @brief	This function will update USB status received from Audio Resource layer.
    * @param	bUsbStatus: usbStatus value from audioPresCtrl
    * @return	void
    */
    void sltMediaUSBSrcStatus(bool bUsbStatus);

    /**
    * @brief	This function will update IPOD status received from Audio Resource layer.
    * @param	bIpodStatus: bIpodStatus value from audioPresCtrl
    * @return	void
    */
    void sltMediaIPODSrcStatus(bool bIpodStatus);

    /**
    * @brief	This function will update AUX status received from Audio Resource layer.
    * @param	bAuxStatus: AuxStatus value from audioPresCtrl
    * @return	void
    */
    void sltMediaAUXSrcStatus(bool bAuxStatus);

    /**
    * @brief	This function will update BT status received from Audio Resource layer.
    * @param	bBTStatus: bBTStatus value from audioPresCtrl
    * @return	void
    */
    void sltMediaBTSrcStatus(bool bBTStatus);

    /**
    * @brief	This function will update audio preset data received from Audio Resource layer.
    * @param	strPresetName: presetName from audioPresCtrl.
    * @return	void
    */
    void sltUpdateAudioPresetChanged(string strPresetName);

    /**
    * @brief	sltUpdateAUXConnectionState: This function will update AUX connection received from Audio Resource layer.
    * @param	strAUXConnectionState: Connection state
    * @return	void
    */
    void sltUpdateAUXConnectionState(const string &strAUXConnectionState);

    /**
    * @brief	sltUpdateUSBConnectionState: This function will update USB connection received from Audio Resource layer.
    * @param	strUSBConnectionState: Connection state
    * @return	void
    */
    void sltUpdateUSBConnectionState(const string &strUSBConnectionState);

    /**
    * @brief	sltUpdateIPODConnectionState: This function will update IPOD connection received from Audio Resource layer.
    * @param	strIPODConnectionState: Connection state
    * @return	void
    */
    void sltUpdateIPODConnectionState(const string &strIPODConnectionState);

    /**
    * @brief	This function will update active source mute status received from Audio Resource layer.
    * @param	bMuteStatus: bMuteStatus value from audioPresCtrl.
    * @return	void
    */
    void sltUpdateSourceMuteState(bool bMuteStatus);

    /**
    * @brief	This function will update speed depandant volume status received from Audio Resource layer.
    * @param	bSpeedDependantVolume: bSpeedDependantVolume value from audioPresCtrl.
    * @return	void
    */
    void sltUpdateSpeedDependantVolume(bool bSpeedDependantVolume);

    /**
    * @brief	This function will update start up volume status received from Audio Resource layer.
    * @param	iStartUpVolume: iStartUpVolume value from audioPresCtrl.
    * @return	void
    */
    void sltUpdateStartUpVolume(int iStartUpVolume);

    /**
    * @brief	This function will update voice alert volume status received from Audio Resource layer.
    * @param	iVoiceAlertVolume: iVoiceAlertVolume value from audioPresCtrl.
    * @return	void
    */
    void sltUpdateVoiceAlertVolume(int iVoiceAlertVolume);

    /*!
     * @brief   Method to notify audio adaptor regarding updated mic mute status.
     * @param   bMicMuteStatus   - mic mute status, TRUE if mic is muted, false otherwise.
     * @return  void.
     */
    void sltMicMuteStatusUpdated(bool bMicMuteStatus);

    /**
    * @brief	This function will update pdc mix mode status received from Audio Resource layer.
    * @param	bPdcMixModeStatus: bPdcMixModeStatus value from audioPresCtrl.
    * @return	void
    */
    void sltUpdatePdcMixModeState(bool bPdcMixModeStatus);

    /**
    * @brief	This function will update AUX gain value received from Audio Resource layer.
    * @param	iAuxGainValue: value from service.
    * @return	void
    */
    void sltUpdateAuxGainValue(int iAuxGainValue);

    /**
     * @brief   sltUpdateActiveAudioSourceList: This function is used tp update
     *          ActiveAudio SourceList.
     * @param   void.
     * return   void.
     */
    void sltUpdateActiveAudioSourceList();

    /**
     * @brief   sltUpdateVolume: This function is used to update
     *          ActiveAudio Source volume.
     * @param   usActiveSourceVolume: Active source volume.
     * @param   bIsVolumeUpdatedByUser:  bIsVolumeUpdatedByUser will be true if
     *          volume is updated by user else false.
     * @param   usActiveSourceVolumeUpdateGroup: Volume update source group, for which volume
     *          gets changed.
     * @param    usSourceId: sourceId for which volume gets updated.
     * return   void.
     */
    void sltUpdateVolume(
            ushort usActiveSourceVolume,
            bool bIsVolumeUpdatedByUser,
            ushort usActiveSourceVolumeUpdateGroup,
            ushort  usSourceId
            );

    /**
     * @brief   sltSourceStateUpdated - slot used to handle source changed information
     * @param   iSourceId : Source id for which source state information is received
     * @param   iSourceState : current state of the source
     * @return  void
     */
    void sltSourceStateUpdated(int iSourceId, int iSourceState);

    /**
     * @brief   sltTakeActionOnSourceActivation: This slot is used to take the action,
     *          when Audio entertainment source gets change. this is also used as a slot
     *          for SingleShot timer.
     * @param   void.
     * @return  void.
     */
    void sltTakeActionOnEntSourceActivation();

private:
    /**
    * @brief	This function will connect signals and slots.
    * @param	void
    * @return	void
    */
    void connectSignals();

    CAudioAdaptor *m_pAudioAdaptor;


    /**
     * @brief m_eAudioEntertainmentSrc: This variable hold the current active source.
     */
    CAudioEnums::EAudioEntertainmentSrcs m_eAudioEntertainmentSrc;
};

#endif // CAudioEventHandler_H

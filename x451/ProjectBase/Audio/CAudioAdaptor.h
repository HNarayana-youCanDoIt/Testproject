/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CAudioAdaptor.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * This class is to handle Audio settings and Audio Controls functionality.
 */
#ifndef CAUDIOADAPTOR_H
#define CAUDIOADAPTOR_H

#include "QObject"
#include "logging.h"
#include "CFramework.h"
#include "AudioResource/interfaces/IAudioResource.h"
#include "AudioResource/implementations/CAudioResourceImpl.h"
#include "Setup/CSetupEnums.h"
#include "CAudioEnums.h"
#include "MediaResource/interfaces/IMediaResource.h"
#include <QMap>

/**
 * @brief The CAudioAdaptor class: This class contains methods to handle Audio related functionality
 *          like Bass, Middle, Treble, Balance & Fader etc.
 */
class CAudioAdaptor : public QObject
{
    Q_OBJECT

    // to get current bass value
    Q_PROPERTY(int bass     READ bass    WRITE setBass    NOTIFY sigBassChanged)

    // to get current mid value.
    Q_PROPERTY(int mid      READ mid     WRITE setMid     NOTIFY sigMidChanged)

    // to get current treble value.
    Q_PROPERTY(int treble   READ treble  WRITE setTreble  NOTIFY sigTrebleChanged)

    // to get current balance value.
    Q_PROPERTY(int balance  READ balance WRITE setBalance NOTIFY sigBalanceChanged)

    //to get current fade value.
    Q_PROPERTY(int fader    READ fader   WRITE setFader   NOTIFY sigFadeChanged)

    // To get value of fader position
    Q_PROPERTY(int faderPos   READ faderPos   NOTIFY sigFaderPosChanged)

    // To get value of balance position
    Q_PROPERTY(int balancePos READ balancePos NOTIFY sigBalancePosChanged)

    // To get value of fm status
    Q_PROPERTY(bool fmSrcStatus     READ fmSrcStatus    NOTIFY sigFMSrcStatuschanged)

    // To get value of am status
    Q_PROPERTY(bool amSrcStatus     READ amSrcStatus    NOTIFY sigAMSrcStatuschanged)

    // To get value of USB status
    Q_PROPERTY(bool usbSrcStatus     READ usbSrcStatus   NOTIFY sigUSBSrcStatuschanged)

    // To get value of AUX status
    Q_PROPERTY(bool auxSrcStatus     READ auxSrcStatus   NOTIFY sigAUXSrcStatuschanged)

    // To get value of BT status
    Q_PROPERTY(bool btSrcStatus     READ btSrcStatus   NOTIFY sigBTSrcStatuschanged)

    // To get value of iPod status
    Q_PROPERTY(bool ipodSrcStatus     READ ipodSrcStatus   NOTIFY sigIPODSrcStatuschanged)

    // To get value of AUX connection status
    Q_PROPERTY(CAudioEnums::EAuxConnectionStatus auxConnectionStatus    READ auxConnectionStatus   NOTIFY sigAUXConnectionStatuschanged)

    // To get value of USB connection status
    Q_PROPERTY(CAudioEnums::EUsbConnectionStatus usbConnectionStatus    READ usbConnectionStatus   NOTIFY sigUSBConnectionStatuschanged)

    // To get value of AUX connection status
    Q_PROPERTY(CAudioEnums::EIpodConnectionStatus ipodConnectionStatus    READ ipodConnectionStatus   NOTIFY sigIPODConnectionStatuschanged)

    // To get current active source volume
    Q_PROPERTY(int  actEntSourceVolume READ actEntSourceVolume NOTIFY sigActEntSourceVolumeChanged)

    // To get the active source mute state
    Q_PROPERTY(bool muteActive READ muteActive NOTIFY sigMuteStateChanged)

    // To get the active source mute state
    Q_PROPERTY(bool volumeUpdatedByUser READ volumeUpdatedByUser NOTIFY sigVolumeUpdatedByUserChanged)

    // To get value of active entertainment source
    Q_PROPERTY(int activeEntSrc     READ activeEntSrc   NOTIFY sigActiveEntSrcChanged)

    // To get value of previous active entertainment source
    Q_PROPERTY(int prevActiveEntSrc READ prevActiveEntSrc NOTIFY sigActiveEntSrcChanged)

    // To get value of active audio preset
    Q_PROPERTY(CAudioEnums::EAudioPresets activeAudioPreset READ activeAudioPreset NOTIFY sigActiveAudioPresetChanged)

    // To get value of speed depandant volume status
    Q_PROPERTY(bool speedDependantVolume   READ speedDependantVolume   NOTIFY sigSpeedDependantVolumeChanged)

    // To get value of phone call volume status
    Q_PROPERTY(int phoneCallVolume   READ phoneCallVolume   NOTIFY sigPhoneCallVolumeChanged)

    // To get value of start up volume status
    Q_PROPERTY(int startUpVolume  READ startUpVolume   NOTIFY sigStartUpVolumeChanged)

    // To get value of voice alert volume status
    Q_PROPERTY(int voiceAlertVolume  READ voiceAlertVolume  NOTIFY sigVoiceAlertVolumeChanged)

    //! property for qml to get updated mic mute status
    Q_PROPERTY(bool micMuteStatus     READ micMuteStatus    NOTIFY sigMicMuteStatusUpdated)

    // To get value of voice alert volume status
    Q_PROPERTY(bool pdcMixModeStatus  READ pdcMixModeStatus  NOTIFY sigPdcMixModeStatusChanged)

    // To get the value of AUX gain volume
    Q_PROPERTY(int auxGainValue READ auxGainValue NOTIFY sigAuxGainValueChanged)

    // Property for Voulme update group.
    Q_PROPERTY(CAudioEnums::EVolumeUpdateGroup volumeUpdateGroup READ volumeUpdateGroup NOTIFY sigVolumeUpdateGroupChanged)

    // Property for Active source volume.
    Q_PROPERTY(ushort activeSourceVolume READ activeSourceVolume NOTIFY sigActiveSourceVolumeChanged)

    //Property for Configured audio preset.
    Q_PROPERTY(CAudioEnums::EAudioPresets configuredAudioPreset READ configuredAudioPreset  NOTIFY sigConfiguredAudioPresetChanged)

    // Property for Active Audio Preset Name.
    Q_PROPERTY(QString activeAudioPresetName READ activeAudioPresetName NOTIFY sigActiveAudioPresetNameChanged)

public:
    static const u_short BASE_10 = 10;
    static const u_short FORMATTED_STR_LEN_2 = 2;
    static const u_short FORMATTED_STR_LEN_3 = 3;

public:
    ~CAudioAdaptor();

    /**
     * @brief	sourceStateInfoUpdated: Method shall be invoked when ever any source's current state
     *          information is updated.
     * @param	iSourceId: source id for which the state has changed.
     * @param   iSourceState: current state of the source.
     * @return	void
     */
    void sourceStateInfoUpdated(int iSourceId, int iSourceState);

    /**
     * @brief   playFromSourceGroup: Method to be invoked to play a source group.
     * @param   eSourceCategory: Source category to be played.
     * @param   bScreenSwitchReq: Falg to indicate whether screen switch is required or not.
     * @return  void
     */
    void playFromSourceGroup(CAudioEnums::EAudioSourceCategory eSourceCategory, bool bScreenSwitchReq = false);

    /**
     * @brief	sourceStateInfoUpdated: Method shall be invoked to get the source state of the particular source.
     * @param	eSourceId: source id for which the state has to be fetched.
     * @return	current state of the source.
     */
    CAudioEnums::ESourceState getSourceState(CAudioEnums::ESourceId eSourceId);

    /**
     * @brief updateAudioPluginProxyAvailability update the status of the audio plugin proxy available/ unavailable
     * @param bAvailability status true / false
     * @return	void
     */
    void updateAudioPluginProxyAvailability(bool bAvailability);

    /**
     * @brief   getSourceCategory: Method to get the category of the passed source.
     * @param   iSourceId: id of the source.
     * @return  category of the source.
     */
    CAudioEnums::EAudioSourceCategory getSourceCategory(int iSourceId);

    /**
    * @brief	This function will return bass value.
    * @param	void.
    * @return	bass: bass value
    */
    int bass();

    /**
    * @brief	This function will return mid value.
    * @param	void.
    * @return	mid: mid value
    */
    int mid();

    /**
    * @brief	This function will return treble value.
    * @param	void.
    * @return	treble: treble value
    */
    int treble();

    /**
    * @brief	This function will return balance value.
    * @param	void.
    * @return	balance: balance value
    */
    int balance();

    /**
    * @brief	This function will return fade value.
    * @param	void.
    * @return	fade: fade value
    */
    int fader();

    /**
    * @brief	This function get the instance of adaptor class.
    * @param	void.
    * @return   pointer
    */
    static CAudioAdaptor *getInstance();

    /**
    * @brief	This function will set bass value.
    * @param	iBass: iBass will set bass value.
    * @return	void
    */
    void setBass(int iBass);

    /**
    * @brief	This function will set mid value.
    * @param	iMid: iMid will set mid value..
    * @return	void
    */
    void setMid(int iMid);

    /**
    * @brief	This function will set treble value.
    * @param	iTreble: iTreble will set treble value.
    * @return	void
    */
    void setTreble(int iTreble);

    /**
    * @brief	This function will set balance value.
    * @param	iBalance: iBalance will set balance value.
    * @return	void
    */
    void setBalance(int iBalance);

    /**
    * @brief	This function will set fade value.
    * @param	iFade: iFade will set fade value.
    * @return	void
    */
    void setFader(int iFade);

    /**
     * @brief   faderPos - To get the fader position
     * @param   void
     * @return	fader - fader position is returned.
     */
    int faderPos();

    /**
     * @brief   setFaderPos - To set the fader position
     * @param   fFaderPos: faderPos will set fader position
     * @return	void
     */
    void setFaderPos(float fFaderPos);

    /**
     * @brief   balancePos - To get the balance position
     * @param   void
     * @return	balance - balance position is returned.
     */
    int balancePos();

    /**
     * @brief   setBalancePos - To set the balance position
     * @param   fBalancePos: balancePos will set balance position
     * @return	void
     */
    void setBalancePos(float fBalancePos);

    /**
    * @brief	This function return FM status.
    * @param	void.
    * @return	true: FM source is available
    *           false: FM source is not available
    */
    bool fmSrcStatus();

    /**
    * @brief	This function is to update FM Source.
    * @param	bFMSrcStatus: bFMSrcStatus
    * @return   void
    */
    void updateFMSrcStatus(bool bFMSrcStatus);

    /**
    * @brief	This function return AM status.
    * @param	void.
    * @return	true: AM source is available
    *           false: AM source is not available
    */
    bool amSrcStatus();

    /**
    * @brief	This function to update AM status.
    * @param	bAMSrcStatus: bAMSrcStatus will hold AM status.
    * @return	void
    */
    void updateAMSrcStatus(bool bAMSrcStatus);

    /**
    * @brief	This function return USB status.
    * @param	void.
    * @return	true: USB source is available
    *           false: USB source is not available
    */
    bool usbSrcStatus();

    /**
    * @brief	This function to update USB status.
    * @param	bUSBSrcStatus: bUSBSrcStatus will hold USB status.
    * @return	void
    */
    void updateUSBSrcStatus(bool bUSBSrcStatus);

    /**
    * @brief	This function return IPOD status.
    * @param	void.
    * @return	true: IPOD source is available
    *           false: IPOD source is not available
    */
    bool ipodSrcStatus();

    /**
    * @brief	This function to update IPOD status.
    * @param	bIPODSrcStatus: bIPODSrcStatus will hold IPOD status.
    * @return	void
    */
    void updateIPODSrcStatus(bool bIPODSrcStatus);

    /**
    * @brief	This function return AUX status.
    * @param	void.
    * @return	true: AUX source is available
    *           false: AUX source is not available
    */
    bool auxSrcStatus();

    /**
    * @brief	This function to update AUX status.
    * @param	bAUXScStatus: bAUXScStatus will hold AUX status.
    * @return	void
    */
    void updateAUXSrcStatus(bool bAUXSrcStatus);

    /**
    * @brief	This function return BT status.
    * @param	void.
    * @return	true: BT source is available
    *           false: BT source is not available
    */
    bool btSrcStatus();

    /**
    * @brief	This function to update BT status.
    * @param	bBTSrcStatus: bBTSrcStatus will hold BT status.
    * @return	void
    */
    void updateBTSrcStatus(bool bBTSrcStatus);

    /**
     * @brief Method to get the active audio preset
     * @param void.
     * @return m_eActiveAudioPreset - value of the active audio preset
     */
    CAudioEnums::EAudioPresets activeAudioPreset();

    /**
     * @brief Method to Update Audio preset value
     * @param strPresetName: Name of currently active audio preset
     * @return void
     */
    void updateAudioPreset(const QString& strPresetName);

    /**
     * @brief updateAUXConnectionState: Method to Update AUX connection state
     * @param strAUXConnectionState: Connection state
     * @return void
     */
    void updateAUXConnectionState(const QString& strAUXConnectionState);

    /**
     * @brief updateUSBConnectionState: Method to Update USB connection state
     * @param strUSBConnectionState: Connection state
     * @return void
     */
    void updateUSBConnectionState(const QString& strUSBConnectionState);

    /**
     * @brief updateIPODConnectionState: Method to Update IPOD connection state
     * @param strIPODConnectionState: Connection state
     * @return void
     */
    void updateIPODConnectionState(const QString& strIPODConnectionState);

    /** @brief actEntSourceVolume - To get the active entertainment source volume
     * @param void
     * @return actEntSourceVolume: volume of active entertainment source
     */
    int actEntSourceVolume();

    /**
    * @brief	setActiveEntSrcVolume: Setter function for Active entertainment
    *           source volume value.
    * @param	iActiveEntSrcVol: Active entertainment source volume value.
    * @return	void
    */
    void setActiveEntSrcVolume(int iActiveEntSrcVol);

    /** @brief muteActive - To get the mute status.
     * @param void
     * @return true: mute is active.
     *         false: mute is not active.
     */
    bool muteActive();

    /** @brief volumeUpdatedByUser - To get the status of user interaction on volume update
     * @param void
     * @return true: updated by user
     *         false: not updated by user
     */
    bool volumeUpdatedByUser() { return m_bIsVolumeUpdatedByUser; }

    /**
     * @brief updateMuteState -  This function will update on mute state changed.
     * @param bMuteActive: bMuteActive status will be true when user request for mute change and false on unmute.
     * @return void
     */
    void updateMuteState(bool bMuteActive);

    /**
     * @brief   volumeUpdateGroup: Getter function for
     *          volumeUpdateGroup property.
     * @param   void.
     * @return  Current Volume Update Group
     */
    CAudioEnums::EVolumeUpdateGroup volumeUpdateGroup() const
    {
        return m_eVolumeUpdateGroup;
    }

    /**
     * @brief   setVolumeUpdateGroup: Setter function for volumeUpdateGroup
     *          property.
     * @param   eVolumeUpdateGroup: Volume Update group for which volume
     *          is changing.
     * @return  void.
     */
    void setVolumeUpdateGroup(CAudioEnums::EVolumeUpdateGroup eVolumeUpdateGroup);

    /**
     * @brief   activeSourceVolume: This function is getter for activeSourceVolume
     *          property.
     * @param   void.
     * @return  Active source volume.
     */
    ushort activeSourceVolume() const
    {
        return m_usActiveSourceVolume;
    }

    /**
     * @brief   setActiveSourceVolume: Setter for property activeSourceVolume.
     * @param   usActiveSourceVolume: Active source volume.
     * @return  void.
     */
    void setActiveSourceVolume(ushort usActiveSourceVolume);

    /**
     * @brief   updateVolume: This function is used to update the active source
     *          volume and active source group, So that Source group Icon can be
     *          show on Volume Bar.
     * @param   usActiveSourceVolume: Active source volume.
     * @param   bIsVolumeUpdatedByUser:  bIsVolumeUpdatedByUser will be true if
     *          volume is updated by user else false.
     * @param   eVolumeUpdateGroup: Volume update source group, for which volume
     *          gets changed.
     * @param   usSourceId: sourceId for which volume gets updated.
     * @return  void.
     */
    void updateVolume(
            ushort usActiveSourceVolume,
            bool bIsVolumeUpdatedByUser,
            CAudioEnums::EVolumeUpdateGroup eVolumeUpdateGroup,
            ushort usSourceId
            );

    /**
    * @brief	This function will return active entertainment source.
    * @param	void
    * @return	enum
    */
    CAudioEnums::EAudioEntertainmentSrcs activeEntSrc();

    /**
    * @brief	This function will return previous active entertainment source.
    * @param	void
    * @return	enum
    */
    CAudioEnums::EAudioEntertainmentSrcs prevActiveEntSrc();

    /**
    * @brief	This function will update active entertainment source value.
    * @param	eActiveEntSrc : eActiveEntSrc will have active entertainment sourceId.
    * @return	void
    */
    void updateActiveEntSrc(CAudioEnums::EAudioEntertainmentSrcs eActiveEntSrc);

    /**
     * @brief activeAudioPresetName Method to get the active audio preset name
     * @param void.
     * @return QString - Name of the active audio preset
     */
     QString activeAudioPresetName();

    /**
    * @brief	This function will be called from qml file to set bass,mid and treble as per index.
    * @param	iValue: val of bass,mid & treble which are going to set from qml
    * @param    iIndex:iIndex will hold the index of list model.
    * @return	void
    */
    Q_INVOKABLE void setBMTValues(int iValue, int iIndex);

    /** @brief speedDependantVolume - To get the speed dependent volume status.
     * @param void
     * @return true: speeddependant volume is active.
     *         false: speeddependant volume not active.
     */
    bool speedDependantVolume();

    /**
     * @brief This function will update on speed dependant volume state changed.
     * @param bSpeedDependantVol: bSpeedDependantVol status will be true when user request for speed depandant volume and false when not set speed depandant volume.
     * @return void
     */
    void setSpeedDependantVolume(bool bSpeedDependantVol);

    /** @brief phoneCallVolume - To get the phone call volume
     * @param void
     * @return phoneCallVolume: volume of phone call
     */
    int phoneCallVolume();

    /**
    * @brief	This function will set phone call volume value.
    * @param	iPhoneCallVol: iPhoneCallVol will set phone call volume value.
    * @return	void
    */
    void setPhoneCallVolume(int iPhoneCallVol);

    /** @brief startUpVolume - To get the start up volume
     * @param void
     * @return startUpVolume: volume of start up
     */
    int startUpVolume();

    /**
    * @brief	This function will set start up volume value.
    * @param	iStartUpVol: iStartUpVol will set start up volume value.
    * @return	void
    */
    void setStartUpVolume(int iStartUpVol);

    /** @brief voiceAlertVolume - To get the voice alert volume
     * @param void
     * @return voiceAlertVolume: volume of voice alert
     */
    int voiceAlertVolume();

    /**
    * @brief	This function will set voice alert volume value.
    * @param	iVoiceAlertVol: iVoiceAlertVol will have voice alert volume value.
    * @return	void
    */
    void setVoiceAlertVolume(int iVoiceAlertVol);

    /** @brief pdcMixModeStatus - To get the pdc mix mode status
     * @param void
     * @return pdcMixModeStatus: pdc mix mode status
     */
    inline bool pdcMixModeStatus() {return m_bPdcMixModeStatus;}

    /**
     * @brief   auxConnectionStatus - To get the AUX connection status
     * @param   void
     * @return  m_eAuxConnectionStatus: AUX connection status
     */
    CAudioEnums::EAuxConnectionStatus auxConnectionStatus() {return m_eAuxConnectionStatus;}

    /**
     * @brief   usbConnectionStatus - To get the USB connection status
     * @param   void
     * @return  m_eUsbConnectionStatus: USB connection status
     */
    CAudioEnums::EUsbConnectionStatus usbConnectionStatus() {return m_eUsbConnectionStatus;}

    /**
     * @brief  ipodConnectionStatus - To get the IPOD connection status
     * @param  void
     * @return m_eIpodConnectionStatus: IPOD connection status
     */
     CAudioEnums::EIpodConnectionStatus ipodConnectionStatus() {return m_eIpodConnectionStatus;}

    /**
     * @brief auxGainValue - To get the aux gain value
     * @param void
     * @return int: aux gain value
     */
    int auxGainValue() {return m_iAuxGainValue;}

    /**
    * @brief	This function will set pdc mix mode status.
    * @param	bPdcMixModeStatus: bPdcMixModeStatus will have pdc mix mode status.
    * @return	void
    */
    void setPdcMixModeStatus(bool bPdcMixModeStatus);

    /**
    * @brief	setAuxGainValue() - This function will set aux gain value.
    * @param	int iAuxGainValue: aux gain value from service.
    * @return	void
    */
    void setAuxGainValue(int iAuxGainValue);

    /**
    * @brief	This method shall be invoked when ever mic mute status is updated.
    * @param	bMicMuteStatus   - mic mute status, TRUE if mic is muted, false otherwise.
    * @return	void
    */
    void micMuteStatusUpdated(bool bMicMuteStatus);

    /*!
     * @brief   Method to get mic mute status.
     * @param   void.
     * @return  true - Mic is muted.
     *          false - Mic is unmuted.
     */
    bool micMuteStatus() { return m_bMicMuteStatus; }

    /**
    * @brief	Method to be called to toggle mic mute.
    * @param	void.
    * @return	void
    */
    void toggleMicMute();

    /**
     * @brief	This function will call playBeep function from resource.
     * @param	CAudioEnums::EBeepType eBeepType: contains beep type to be played from resource.
     * @return	void
     */
    void playBeep(CAudioEnums::EBeepType eBeepType);

    /**
     * @brief setAudioOff This method is to set the audio off state on the audio resource
     * @param audioState state to set On-Off (true, false)
     */
    void setAudioOff(bool bAudioState);

    /**
     * @brief   isAudioInterruptSourceActive: This function is used to know that
     *          a particular audio interrupt source is active.
     * @param   eAudioInterruptSource: sourceId which needs to be check that
     *          active or not.
     * @return  bool: true if active else false.
     */
    bool isAudioInterruptSourceActive( CAudioEnums::EAudioInterruptSources eAudioInterruptSource);

    /**
     * @brief   setIsSourceChangeRequestedByUser: This function is used to set the
     *          m_bIsSourceChangeRequestedByUser variable, this needs to be set true
     *          if source change is initiated by user, otherwise it should be false.
     * @param   isRequestedByUser: true if source change is requested by user, otherwise
     *          false.
     * @return  void.
     */
    void setIsSourceChangeRequestedByUser(bool bIsSrcChangeRequestedByUser);

    /**
     * @brief isSourceChangeRequestedByUser: Function to know that the source
     *        change is requested by user or not.
     * @return bool: true if source change is requested by user, otherwise false.
     */
    bool isSourceChangeRequestedByUser() const
    {
        return m_bIsSourceChangeRequestedByUser;
    }    

public:

    /**
    * @brief	This function will be called from qml file to set bass,mid and treble as per index.
    * @param	iValue: val of bass,mid & treble which are going to set from qml
    * @param    iIndex:iIndex will hold the index of list model.
    * @return	void
    */
    Q_INVOKABLE void setVolumeSettingsValues(int iValue, int iIndex);

    /**
     * @brief   calculateBalanceFader - Method is called from qml to calculate the balance & fader from positions
     * @param   fFaderPos - Fader position value is received from qml
     * @param   fBalancePos - Balance position value is received from qml
     * @return	void.
     */
    Q_INVOKABLE void calculateBalanceFader(float fFaderPos, float fBalancePos);

    /**
     * @brief   setActiveEntSrc - Method is called from qml to set active entertainment source.
     * @param   eEntertainmentSrc - src source value recieved from qml.
     * @return	void.
     */
    Q_INVOKABLE void setActiveEntSrc(CAudioEnums::EAudioEntertainmentSrcs eEntertainmentSrc);

    /**
     * @brief   setAudioPresetAttribute - Method is called from qml to set the audio preset
     * @param   iAudioPreset - preset Index is received from qml, same is sent in API call
     * @return	void.
     */
    Q_INVOKABLE void setAudioPresetAttribute(int iAudioPreset);

    /**
     * @brief   updateBalanceFaderPositions - Method is called from qml,
     *          to update the balance & fader position's when the user is dragged the balance & fader pointer
     * @param   faderPos - Fader position value is received from qml
     * @param   balancePos - Balance position value is received from qml
     * @return	void.
     */
    Q_INVOKABLE void updateBalanceFaderPositions(float fFaderPos, float fBalancePos);

    /**
     * @brief   switchToActiveEntertainmentSource - Funtion is used to go to
     *          Active entertainment source.
     * @param   void
     * @return	void.
     */
    Q_INVOKABLE void switchToActiveEntertainmentSourceScreen();

    /**
     * @brief   Method is called from qml to set currently configured audio preset.
     * @param   iIndex - index of audio preset
     * @return	void.
     */
    Q_INVOKABLE void setConfiguredAudioPreset(int iIndex);

    /**
     * @brief   Method will inform the configured audio preset value
     * @param   iIndex - index of audio preset
     * @return	void.
     */
    Q_INVOKABLE CAudioEnums::EAudioPresets configuredAudioPreset();

    /**
     * @brief   toggleMute - Method is called from qml to toggle mute for the current active entertainment source.
     * @param   bUserInitiated: set this flag to true if it is a user triggerred mute event.
     * @return	void.
     */
    Q_INVOKABLE void toggleMute(bool bUserInitiated = false);

    /**
    * @brief   convertIntValueFormat - Method is called from qml,
    *          to convert the values as formatted string
    * @param   value - value is received from qml
    * @return	QString - Formatted string
    *          Ex: 1 converted as +01, -1 converted as -01, 0 converted as 00,
    *              10 converted as +10, -10 converted as -10
    */
    Q_INVOKABLE QString convertIntValueFormat(int value);

    /**
    * @brief	This function will request speed depandant value to LB.
    * @param	bSpeedDependantValue: bSpeedDependantValue will set speed dependant value.
    * @return	void
    */
    Q_INVOKABLE void setSpeedDependantVolumeAttribute(bool bSpeedDependantVolume);

    /**
    * @brief	toggleEntSrc - This function will request AudioManager to toggle source (next or previos)
    * @param	eToggleDirection - Toggle Source Direction
    *           TOGGLE_NEXT - To switch to next source (default)
    *           TOGGLE_PREVIOUS - To switch to previous source
    * @return	void
    */
    Q_INVOKABLE void toggleEntSrc(CAudioEnums::EToggleDirection eToggleDirection = CAudioEnums::TOGGLE_NEXT);


    /**
    * @brief	This function will request audio service to set pdc mix mode state.
    * @param	bPdcMixModeStatus- bPdcMixModeStatus will set pdc mix mode status value.
    * @return	void
    */
    Q_INVOKABLE void setPdcMixModeStateAttribute(bool bPdcMixModeStatus);

    /**
    * @brief	This function will request audio service to set aux in gain settings to eAuxinGain.
    * @param	eAuxInGain- Value to set as aux gain. Possible values are AUXINGAIN_LOW, AUXINGAIN_MID, AUXINGAIN_HIGH
    * @return	void
    */
    Q_INVOKABLE void  setAuxInGainAttribute(int iAuxInGain);

    /**
    * @brief	switchToPreviousEntSource: This function will request Audio service to switch to previously active Ent. source
    * @param	void
    * @return	void
    */
    Q_INVOKABLE void switchToPreviousEntSource();

    /**
    * @brief	This function will request bass value to LB.
    * @param	iBassval: bassval will set bass value.
    * @return	void
    */
    void setBassAttribute(int iBassval);

    /**
    * @brief	This function will request mid value to LB.
    * @param	iMidval: midval will set mid value.
    * @return	void
    */
    void setMidAttribute(int iMidval);

    /**
    * @brief	This function will request treble value to LB.
    * @param	iTrebleval: trebleval will set treble value.
    * @return	void
    */
    void setTrebleAttribute(int iTrebleval);

    /**
    * @brief	This function will request balance & fader value to LB.
    * @param	iFader: fader value to be sent.
    * @param	iBalance: balance value to be sent.
    * @return	void
    */
    void setFaderBalance(int iFader, int iBalance);

    /**
    * @brief	This function will request phone call volume to LB.
    * @param	iPhoneCallVol: iPhoneCallVol will set phone call volume value.
    * @return	void
    */
    void setPhoneCallVolumeAttribute(int iPhoneCallVol);

    /**
    * @brief	This function will request start up volume to LB.
    * @param	iStartUpVol: iStartUpVol will set start up volume value.
    * @return	void
    */
    void setStartUpVolumeAttribute(int iStartUpVol);

    /**
    * @brief	This function will request voice alert volume to LB.
    * @param	iVoiceAlertVol: iVoiceAlertVol will set voice alert volume value.
    * @return	void
    */
    void setVoiceAlertVolumeAttribute(int iVoiceAlertVol);

    /**
    * @brief	This function will request notification volume to LB.
    * @param	iNotificationVol: iNotificationVol will set notification volume value.
    * @return	void
    */
    Q_INVOKABLE void setNotificationVolumeAttribute(int iNotificationVol);

    /**
    * @brief	invParkAssistVolume: This function will request park assist volume to audio service.
    * @param	int iParkAssistVolume: contains park assist volume to be set.
    * @return	void
    */
    Q_INVOKABLE void invParkAssistVolume(int iParkAssistVolume);

    /**
    * @brief	getIsVolumeUpdatedByUser: This function will return vvalue of m_bIsVolumeUpdatedByUser
    * @param	void
    * @return	m_bIsVolumeUpdatedByUser - bool indicating if user request
    */
    Q_INVOKABLE bool getIsVolumeUpdatedByUser() { return m_bIsVolumeUpdatedByUser; }

signals:

    /**
     * @brief sigActiveAudioPresetNameChanged This signal is emitted when audio preset name is changed
     * @param void
     * @return void
     */
    void sigActiveAudioPresetNameChanged();

    /**
     * @brief sigUpdateAudioPluginProxyAvailability This signal is emitted when proxy availability value changed
     * @param bAvailability
     * @return void
     */
    void sigUpdateAudioPluginProxyAvailability(bool bAvailability);
 
   /**
    * @brief	This signal will emit bass value whenever bass gets changed.
    * @param	void.
    * @return	void
    */
    void sigBassChanged();

    /**
    * @brief	This signal will emit mid value whenever mid gets changed.
    * @param	void.
    * @return	void
    */
    void sigMidChanged();

    /**
    * @brief	This signal will emit treble value whenever treble gets changed.
    * @param	void.
    * @return	void
    */
    void sigTrebleChanged();

    /**
    * @brief	This signal will emit balance value whenever balance gets changed.
    * @param	void.
    * @return	void
    */
    void sigBalanceChanged();

    /**
    * @brief	This signal will emit fade value whenever fade gets changed.
    * @param	void.
    * @return	void
    */
    void sigFadeChanged();

    /**
    * @brief	This signal will emit fader position value whenever fader position gets changed.
    * @param	void.
    * @return	void
    */
    void sigFaderPosChanged();

    /**
    * @brief	This signal will emit balance position value whenever balance position gets changed.
    * @param	void.
    * @return	void
    */
    void sigBalancePosChanged();

    /**
    * @brief	This signal will emit FM status whenever FM status gets changed.
    * @param	void.
    * @return	void
    */
    void sigFMSrcStatuschanged();

    /**
    * @brief	This signal will emit AM status whenever AM status gets changed.
    * @param	void.
    * @return	void
    */
    void sigAMSrcStatuschanged();

    /**
    * @brief	This signal will emit USB status whenever USB status gets changed.
    * @param	void.
    * @return	void
    */
    void sigUSBSrcStatuschanged();

    /**
    * @brief	This signal will emit IPOD status whenever IPOD status gets changed.
    * @param	void.
    * @return	void
    */
    void sigIPODSrcStatuschanged();

    /**
    * @brief	This signal will emit AUX status whenever AUX status gets changed.
    * @param	void.
    * @return	void
    */
    void sigAUXSrcStatuschanged();

    /**
    * @brief	This signal will emit BT status whenever BT status gets changed.
    * @param	void.
    * @return	void
    */
    void sigBTSrcStatuschanged();

    /**
    * @brief	This signal will emit AUX connection status whenever it is updated.
    * @param	void.
    * @return	void
    */
    void sigAUXConnectionStatuschanged();

    /**
    * @brief	This signal will emit USB connection status whenever it is updated.
    * @param	void.
    * @return	void
    */
    void sigUSBConnectionStatuschanged();

    /**
    * @brief	This signal will emit IPOD connection status whenever it is updated.
    * @param	void.
    * @return	void.
    */
    void sigIPODConnectionStatuschanged();

    /**
    * @brief	This signal gets emitted, whenever active source volume changed.
    * @param	void.
    * @return	void
    */
    void sigActEntSourceVolumeChanged();

    /**
     * @brief   sigActiveSourceVolumeChanged: This signal will emit when volume
     *          gets changed for any source.
     * @param   void.
     * @return  void.
     */
    void sigActiveSourceVolumeChanged();

    /**
     * @brief   sigVolumeUpdateGroupChanged: This signal will be emitted, Whenever
     *          volumeUpdateGroupChanged property gets changed.
     * @param   void.
     * @return  void.
     */
    void sigVolumeUpdateGroupChanged();

    /**
    * @brief	This signal gets emitted, whenever active source mute status changed.
    * @param	void.
    * @return	void
    */
    void sigMuteStateChanged();

    /**
    * @brief	This signal gets emitted, whenever value of m_bIsVolumeUpdatedByUser changes.
    * @param	void.
    * @return	void
    */
    void sigVolumeUpdatedByUserChanged();

    /**
    * @brief	This signal will emit active entertainment source value whenever active entertainment source status gets changed.
    * @param	void.
    * @return	void
    */
    void sigActiveEntSrcChanged();

    /**
    * @brief	This signal will emit active audio preset on updated.
    * @param	void.
    * @return	void
    */
    void sigActiveAudioPresetChanged();

    /**
    * @brief	This signal will emit speed dependant volume on changed.
    * @param	void.
    * @return	void
    */
    void sigSpeedDependantVolumeChanged();

    /**
    * @brief	This signal will emit phone call volume on changed.
    * @param	void.
    * @return	void
    */
    void sigPhoneCallVolumeChanged();

    /**
    * @brief	This signal will emit start up volume on changed.
    * @param	void.
    * @return	void
    */
    void sigStartUpVolumeChanged();

    /**
    * @brief	This signal will emit voice alert volume on changed.
    * @param	void.
    * @return	void
    */
    void sigVoiceAlertVolumeChanged();

    /*!
     * @brief   Signal emitted whenever mic mute status is updated.
     * @param   void.
     * @return  void.
     */
    void sigMicMuteStatusUpdated();

    /**
    * @brief	This signal will emit aux gain value on changed.
    * @param	void.
    * @return	void
    */
    void sigAuxGainValueChanged();

    /**
    * @brief	This signal will emit pdc mix mode status on changed.
    * @param	void.
    * @return	void
    */
    void sigPdcMixModeStatusChanged();

    /**
     * @brief sigActiveAudioSourceListUpdated: This siganl is emitted, whenever
     *        Active Audio Source List is updated.
     */
    void sigActiveAudioSourceListUpdated();

    /**
     * @brief   sigSourceStateInfoUpdated: Signal shall be broadcasted when ever any source's current state
     *          information is updated.
     * @param	iSourceId: source id for which the state has changed.
     * @param   iSourceState: current state of the source.
     * @return  void.
     */
    void sigSourceStateInfoUpdated(int iSourceId, int iSourceState);

    /**
     * @brief sigConfiguredAudioPresetChanged : This signal is emitted, whenever
     *        configured audio preset is updated
     * @param   void.
     * @return  void.
     */
    void sigConfiguredAudioPresetChanged();

private:
    //private methods to be declared here

    /**
    * @brief	This method will status of audio resource pointer.
    * @param	void.
    * @return	bool - status of audio resource pointer, null or not.
    */
    bool isAudioResourceNull();

    /**
    * @brief	setIsVolumeUpdatedByUser: This method shall set the value of m_bIsVolumeUpdatedByUser
    * @param	bIsVolumeUpdatedByUser - bool value
    * @return	void
    */
    void setIsVolumeUpdatedByUser(bool bIsVolumeUpdatedByUser);

    /**
     * @brief   getAuxConnectionInEnums - Method to get Aux connection status Enum value corresponding to the
     *          string received from Service.
     * @param   strAuxConnectionState - Aux connection status string
     * @return  CAudioEnums::EAuxConnectionStatus - Aux Connection status enum
     */
    CAudioEnums::EAuxConnectionStatus getAuxConnectionInEnums(const QString &strAuxConnectionState);

    /**
     * @brief   getIpodConnectionInEnums - Method to get Ipod connection status Enum value corresponding to the
     *          string received from Service.
     * @param   strIpodConnectionState - Ipod connection status string
     * @return  CAudioEnums::EIpodConnectionStatus - Ipod Connection status enum
     */
    CAudioEnums::EIpodConnectionStatus getIpodConnectionInEnums(const QString &strIpodConnectionState);

    /**
     * @brief   getUsbConnectionInEnums - Method to get USB connection status Enum value corresponding to the
     *          string received from Service.
     * @param   strUsbConnectionState - Usb connection status string
     * @return  CAudioEnums::EUsbConnectionStatus - Usb Connection status enum
     */
    CAudioEnums::EUsbConnectionStatus getUsbConnectionInEnums(const QString &strUsbConnectionState);

private:

    /**
     * @brief CAudioAdaptor class Constructor
     * @param pParent
     * @return void
     */
    explicit CAudioAdaptor(QObject *parent = nullptr);

    /* Instance of class CAudioAdaptor */
    static CAudioAdaptor* m_pAudioAdaptor;

    /* Instance of class IAudioResource */
    IAudioResource* m_pAudioResource;

    /* Pointer of CAudioResourceImpl class to communicate with
     * audio manager resource layer.
     */
    CAudioResourceImpl* m_pAudioResourceImpl;

    /* Instance of media resource */
    IMediaResource* m_pMediaResource;

    /* This variable holds the bass value */
    int m_iBass;

    /* This variable holds the mid value */
    int m_iMid;

    /* This variable holds the treble value */
    int m_iTreble;

    /* This variable holds the balance value */
    int m_iBalance;

    /* This variable holds the fade value */
    int m_iFade;

    /* This variable holds the balance position value */
    int m_iBalancePos;

    /* This variable holds the fader position value */
    int m_iFaderPos;

    /* This variable holds the fm availability status */
    bool m_bFMSrcStatus;

    /* This variable holds the am availability status */
    bool m_bAMSrcStatus;

    /* This variable holds the usb availability status */
    bool m_bUSBSrcStatus;

    /* This variable holds the ipod availability status */
    bool m_bIPODSrcStatus;

    /* This variable holds the aux availability status */
    bool m_bAUXSrcStatus;

    /* This variable holds the bt availability status */
    bool m_bBTSrcStatus;

    /**
     * @brief This holds the value of current connection status of Aux
     *        Possible Values: AUX_STATE_UNKNOWN, AUX_CONNECTED, AUX_ALREADY_CONNECTED, AUX_REMOVED
     */
    CAudioEnums::EAuxConnectionStatus m_eAuxConnectionStatus;

    /**
     * @brief This holds the value of current connection status of Ipod
     *        Possible Values: IPOD_STATE_UNKNOWN, IPOD_CONNECTED, IPOD_ALREADY_CONNECTED, IPOD_DISCONNECTED
     */
    CAudioEnums::EIpodConnectionStatus m_eIpodConnectionStatus;

    /**
     * @brief This holds the value of current connection status of Usb
     *        Possible Values: USB_STATE_UNKNOWN, USB_CONNECTED, USB_ALREADY_CONNECTED, USB_DISCONNECTED
     */
    CAudioEnums::EUsbConnectionStatus m_eUsbConnectionStatus;

    /* This variable holds the active entertainment source volume */
    int m_iActEntSourceVolume;

    /* This variable holds the active source mute status*/
    bool m_bMuteActive;

    /* This variable holds the speed depandant volume status*/
    bool m_bSpeedDependantVolume;

    /* This variable holds the phone call volume status*/
    int m_iPhoneCallVolume;

    /* This variable holds the start up volume status*/
    int m_iStartUpVolume;

    /* This variable holds the voice alert volume status*/
    int m_iVoiceAlertVolume;

    /* This variable holds the aux gain value */
    int m_iAuxGainValue;

    /* This variable holds the pdc mix mode status*/
    bool m_bPdcMixModeStatus;

    /* This variable holds the previous active entertainment source */
    CAudioEnums::EAudioEntertainmentSrcs m_ePrevActiveEntSrc;

    /* This variable holds the active entertainment source */
    CAudioEnums::EAudioEntertainmentSrcs m_eActiveEntSrc;

    /* This variable holds the configured Audio Preset */
    CAudioEnums::EAudioPresets m_eConfiguredAudioPreset;

    /* This variable holds the active Audio Preset */
    CAudioEnums::EAudioPresets m_eActiveAudioPreset;

    /* This variable holds the mapping of audio preset values */
    QMap<CAudioEnums::EAudioPresets,QString> m_mapAudioPreset;

    /* This variable holds the mapping of audio preset values */
    QVector<QString> m_vecAudioPresetName;

    //! Flag to hold mic mute status
    bool    m_bMicMuteStatus;

    /**
     * @brief m_bUserInitiatedSrcSwitch - Flag to check if source switch was initiated by user action
     *        on receiving source activated signal.
     */
    bool    m_bUserInitiatedSrcSwitch;

    /**
     * @brief m_eVolumeUpdateGroup: Variable to hold the Volume Update group.
     *        This is updated whenever, volume update happens for any source.
     *        We will get the Volume update group for which volume is changing.
     */
    CAudioEnums::EVolumeUpdateGroup m_eVolumeUpdateGroup;

    /**
     * @brief m_uSActiveSourceVolume: Variable is used to hold the volume of
     *        Active source.
     */
    ushort m_usActiveSourceVolume;

    /**
     * @brief m_bIsSourceChangeRequestedByUser: This variable stores the status
     *        of source change requested by user or not. true if source change is
     *        requested by user, otherwise false.
     */
    bool m_bIsSourceChangeRequestedByUser;

    /**
     * @brief m_bIsVolumeUpdatedByUser: Variable is used to hold value of user interaction
     * when volume update is received
     */
    bool m_bIsVolumeUpdatedByUser;

    /* Map for audio source id and audio source state */
    QMap<CAudioEnums::ESourceId, CAudioEnums::ESourceState> m_mapAudioSourceInfo;
};

#endif // CAUDIOADAPTOR_H

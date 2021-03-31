/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CAudioResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CAudioResourceImpl, Resource Implementation for Audio.
 */

#ifndef CAUDIORESOURCEIMPL_H
#define CAUDIORESOURCEIMPL_H

#include "resource/AudioResource/interfaces/IAudioResource.h"
#include "v2/com/harman/audio/audioPresCtrl/audioPresCtrlControlsProxy.hpp"
#include "v3/com/harman/audio/audioPresCtrl/audioPresCtrlSettingsProxy.hpp"
#include "v3/com/harman/audio/audioPresCtrl/audioPresCtrlTypes.hpp"
#include "v0/com/harman/audiopres/plugin/TataAudioPresPluginProxy.hpp"
#include "v0/com/harman/audiopres/plugin/audioPresPluginTypes.hpp"
#include "v0/com/harman/audiopres/plugin/TataAudioPresPlugin.hpp"
#include "v0/com/harman/audiopres/plugin/TataAudioPresPluginProxyBase.hpp"

#include "CAudioEventProvider.h"
#include <capi/CAPIClientAbstraction.hpp>
#include "Audio/CAudioEnums.h"

using namespace std;
using namespace v3::com::harman::audio::audioPresCtrl;
using namespace v2::com::harman::audio::audioPresCtrl;
using namespace v0::com::harman::audiopres::plugin;

/**
*   @brief The AudioResourceImpl class
*   This class implements the AudioResourceImpl interface.
*/

class CAudioResourceImpl: public IAudioResource
{
public:

    virtual ~CAudioResourceImpl();

public:

    CAudioEventProvider* getAudioDataEventProvider();

    /**
    * @brief	This function is going to set bass level.
    *           which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param	iBass: bass is integer holding the bass value set from audio adaptor.
    * @return	void.
    */
    virtual void setBass(int16_t iBass) override;

    /**
    * @brief	This function is going to set mid level.
    *           which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param	iMid: mid is integer holding the mid value set from audio adaptor.
    * @return	void.
    */
    virtual void setMid(int16_t iMid) override;

    /**
    * @brief	This function is going to set treble level.
    *           which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    iTreble: treble is integer holding the treble value set from audio adaptor.
    * @return	void.
    */
    virtual void setTreble(int16_t iTreble) override;

    /**
    * @brief	This function is going to set fader & balance level.
    *           which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    iFader: The fader value sent from audio adaptor.
    * @param    iBalance: The balance value sent from audio adaptor.
    * @return	void.
    */
    virtual void setFaderBalance(int16_t iFader, int16_t iBalance) override;

    /**
    * @brief	This function is to set active entertainment audio source.
    * @param    eSrcID: srcID will have enums of entertainemnt sources.
    * @return	void.
    */
    void setActiveSourceID(CAudioEnums::EAudioEntertainmentSrcs eSrcID) override;


    /**
    * @brief	This method is to set the audio preset, which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    strPreset: preset will set the Audio preset string.
    * @return	void.
    */
    virtual void setAudioPreset(const string &strPreset) override;

    /**
    * @brief	This method is used to toggle system mute, which is going to call TataAudioPresPluginProxy(service) API.
    * @param    void
    * @return	void.
    */
    virtual void ToggleSystemMute() override;

    /**
     * @brief	This method is used to toggle mute status of currently playing sources as per TML mute strategy
     * @param   bUserInitiated: set this flag to true if it is a user triggerred mute event.
     * @return	void.
     */
    virtual void toggleMute(const bool &bUserInitiated) override;

    /**
    * @brief	This method is to set the start up volume, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    iStartUpVolume: startupvolume will set the startup volume.
    * @return	void.
    */
    virtual void setStartUpVolume(int16_t iStartUpVolume) override;

    /**
    * @brief	This method is to set the SDVC state, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    bSdvcState: bSdvcState will set the speed dependant volume state.
    * @return	void.
    */
    virtual void setSDVCState(bool bSdvcState) override;

    /**
    * @brief	This method is to set the phone call volume, which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    iAabsoluteVolume: iAabsoluteVolume will set the phone call volume.
    * @return	void.
    */
    virtual void setPhoneSourceVolume(const uint16_t &iAabsoluteVolume) override;

    /**
    * @brief	This method is to set the voice alert volume, which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    iAabsoluteVolume: iAabsoluteVolume will set the voice alert volume.
    * @return	void.
    */
    virtual void setVoiceAlertVolume(const uint16_t &iAbsoluteVolume) override;

    /**
    * @brief	This method is to set the notification volume, which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    iAabsoluteVolume: iAabsoluteVolume will set the notification volume.
    * @return	void.
    */
    virtual void setNotificationVolume(const uint16_t &iAbsoluteVolume) override;

    /**
    * @brief	This method is to set the Aux in gain, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    eAuxInGain: eAuxInGain will set the Aux in Gain.
    * @return	void.
    */
    virtual void setAuxInGain(CAudioEnums::EAuxInGain eAuxInGain) override;

    /**
    * @brief	This method is to set the source volume, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    iSourceID: iSourceID will hold the source ID.
    * @param    iAbsoluteVolume: iAbsoluteVolume will hold volume.
    * @return	void.
    */
    virtual void setSourceVolume(const int &iSourceID, const uint16_t &iAbsoluteVolume) override;

    /**
    * @brief	This method is to set the toggle source, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    edirection: edirection will hold direction in which source will toggle.
    * @return	void.
    */
    virtual void toggleSource(CAudioEnums::EToggleDirection edirection);

    /**
     * @brief   This method is used to toggle MIC mute status.
     * @param   void.
     * @return  void.
     */
    void toggleMicMute() override;

    /**
    * @brief	This method is to set the pdc mix mode state, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    bPdcMixModeState: bPdcMixModeState will hold pdc mix mode state.
    * @return	void.
    */
    virtual void setPdcMixModeState(bool bPdcMixModeState) override;

    /**
    * @brief	This method is to set the park assist volume, which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    iParkAssistVolume: iParkAssistVolume contains the park assist volume.
    * @return	void.
    */
    virtual void setParkAssistVolume(const uint16_t &iParkAssistVolume) override;

    /**
     * @brief   getActiveAudioSourceList: Method to get Active Audio
     *          Source List.
     * @param   void.
     * @return  void.
     */
    const vector<uint16_t>&  getActiveAudioSourceList() const
    {
        return m_vectActiveAudioSource;
    }

    /**
     * @brief setAudioOff This method is used to make Sink audio ON-OFF
     * @param audioState state to set On-Off (true, false)
     */
    void setAudioOff(bool bAudioState) override;

    /**
     * @brief switchToPreviousEntSource: This method is used to switch to previous Ent. source
     * @param void
     * @return void
     */
    void switchToPreviousEntSource() override;

    /**
     * @brief   playFromSourceGroup: Method to be invoked to play a source group. Audo service shall
     *          take care of playing the source from the group.
     * @param   iSourceGroup: Source group to be played.
     * @return  void
     */
    void playFromSourceGroup(int iSourceGroup) override;

    /*****  CALL BACK METHODS  ****************************/

    /**
    * @brief    onSourceStateEventCb: Callback to get notified about source state information.
    * @param    uiSourceId: holds the source id for which source state info is received.
    * @param    eSourceState: holds the current state of the source.
    * @return	void.
    */
    void onSourceStateEventCb(uint16_t uiSourceId, audioPresPluginTypes::ConnectionState_e eSourceState);

    /**
    * @brief	This function is to get bass value on event subscription and
    *           and update the value to audiodataeventprovider class.
    * @param    iBass: bass holding the bass value on response.
    * @return	void.
    */
    void onBassAttributeCb(int16_t iBass) override;

    /**
    * @brief	This function is to get mid value on event subscription and
    *           and update the value to audiodataeventprovider class.
    * @param    iMid: mid holding the updated mid value on response.
    * @return	void.
    */
    void onMidAttributeCb(int16_t iMid) override;

    /**
    * @brief	This function is to get treble value on event subscription and
    *           and update the value to audiodataeventprovider class.
    * @param    iTreble: treble holding the updated treble value on response.
    * @return	void.
    */
    void onTrebleAttributeCb(int16_t iTreble) override;

    /**
    * @brief	This function is to get balance value on event subscription and
    *           and update the value to audiodataeventprovider class.
    * @param    iBalance: balance holding the updated balance value on response.
    * @return	void.
    */
    void onBalanceAttributeCb(int16_t iBalance) override;

    /**
    * @brief	This function is to get fade value on event subscription and
    *           and update the value to audiodataeventprovider class.
    * @param    iFade: fade holding the updated fade value on response.
    * @return	void.
    */
    void onFadeAttributeCb(int16_t iFade) override;

    /**
    * @brief	This function is to get active entertainment source value on event subscription and
    *           and update the value to audioeventprovider class.
    * @param    objEntSrcInfo: objEntSrcInfo is a data structure holding information of an entertainment source
    * @return	void.
    */
    void onActiveEntSourceAttributeCb(audioPresCtrlTypes::sSourceInfo objEntSrcInfo) override;

    /**
    * @brief	This function is to get available entertainment sources list value on event subscription and
    *           and update the value to audioeventprovider class.
    * @param    mapEntSrcInfo: mapEntSrcInfo is a map holding information of an entertainment sources.
    * @return	void.
    */
    void onEntSourceListAttributeCb(audioPresCtrlTypes::mEntSrcsInfo mapEntSrcInfo) override;

    /**
    * @brief	This function is to check the API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    void SetEntertainmentSrcAsyncCb(const CommonAPI::CallStatus &status, const audioPresCtrlTypes::eAudioPresErrors&) override;

    /**
    * @brief	This function is to check the availability of audio settings proxy.
    * @param    eStatus: status will have API availability status.
    * @return	void.
    */
    void statusEventListnerSettings(CommonAPI::AvailabilityStatus eStatus);

    /**
    * @brief	This function is to check the availability of audio controls proxy.
    * @param    eStatus: status will have API availability status.
    * @return	void.
    */
    void statusEventListnerControler(CommonAPI::AvailabilityStatus eStatus);

    /**
    * @brief	This function is to check the availability of audio plugin proxy.
    * @param    eStatus: status will have API availability status.
    * @return	void.
    */
    void statusEventListnerAudioplugin(CommonAPI::AvailabilityStatus eStatus);

    /**
    * @brief	This function is to get audio preset value on event subscription and update the value to audiodataeventprovider class.
    * @param    strPreset : Preset to be updated in UI.
    * @return	void.
    */
    virtual void onAudioPresetAttributeCb(string strPreset) override;

    /**
    * @brief	This function is to get active entertainment source volume value on event subscription and update the value to audiodataeventprovider class.
    * @param    objSrcVolume : objSrcVolume is structure which will hold absolute volume of active source and sourceID.
    * @param    bEventTriggeredByUser: eventTriggered By User or system, (true)volume triggered by user or (false) system triggered.
    * @param    eVolumeGroup: volume group will have group of entertainment sources, interrupt sources.
    * @return	void.
    */
    virtual void onVolumeUpdateEventCb(audioPresCtrlTypes::sSourceVolume objSrcVolume, bool bEventTriggeredByUser, audioPresCtrlTypes::eVolumeGroup eVolumeGroup) override;

    /**
    * @brief	This function is to get active source mute value on event subscription and update the value to audiodataeventprovider class.
    * @param    bActiveSourceMute: bActiveSourceMute will hold mute state of a source.
    * @return	void.
    */
    virtual void onActiveSrcMuteAttributeCb(bool bActiveSourceMute) override;

    /**
    * @brief	This function is to check the Start Up Volume API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onStartUpVolumeCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors&) override;

    /**
    * @brief	This function is to check the SDVC state API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onSdvcStateCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors&) override;

    /**
    * @brief	This method is to set the beep type, which is going to call PlayBeepAsync(service) API.
    * @param    CAudioEnums::EBeepType eBeepType: beep type to be played.
    * @return	void.
    */
    virtual void playBeep(CAudioEnums::EBeepType eBeepType) override;

    /**
    * @brief	This function is to check the source volume API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onSourceVolumeAsyncCb(const CallStatus &status, const audioPresCtrlTypes::eAudioPresErrors &) override;

    /**
    * @brief	This function is to get start up volume value on event subscription and update the value to audiodataeventprovider class.
    * @param    iStartUpVolume: iStartUpVolume holding the start up volume.
    * @return	void.
    */
    virtual void onStartupVolumeAttributeCb(int16_t iStartUpVolume) override;

    /**
    * @brief	This function is to get SDVC state on event subscription and update the value to audiodataeventprovider class.
    * @param    bSdvcState: bSdvcState holding the SDVC state.
    * @return	void.
    */
    virtual void onSdvcStateAttributeCb(bool bSdvcState) override;

    /**
    * @brief	This function is to get PDC Mix Mode state on event subscription and update the value to audiodataeventprovider class.
    * @param    bPdcMixModeState: bPdcMixModeState holding the Pdc mix mode state.
    * @return	void.
    */
    virtual void onPdcMixModeAttributeCb(bool bPdcMixModeState) override;

    /**
    * @brief	This function is to check the play beep API call status.
    * @param    status: callstatus holding the API call status.
    * @param    audioPresPluginTypes::eAudioPresPluginErrors&: holds the status of audioPresStatus
    * @return	void.
    */
    void onPlayBeepAsyncCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors& audioPresStatus);

    /**
    * @brief	This function is to check the Aux in gain API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onAuxInGainCb(const CallStatus &callStatus, const audioPresPluginTypes::eAudioPresPluginErrors &audioPresStatus) override;

    /**
    * @brief	This function is to check the toggle source API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onToggleSourceAsyncCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors &) override;

    /*!
     * @brief   Callback to get notified about the mic mute status.
     * @param   bMicMuteStatus   - mic mute status, TRUE if mic is muted, false otherwise.
     * @return  void.
     */
    void onMicMuteStatusCb(bool bMicMuteStatus) override;

    /**
    * @brief	This function is to check the pdc mix mode API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onPdcMixModeStatusCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors &) override;

    /**
    * @brief	This method is to get the Volume of any source
    * @param    sourceID: Source id is to be passed.
    * @return	void.
    */
    virtual void getSourceVolume(const int &iSourceID) override;

    /**
    * @brief	This method is a call back method to GetSourceVolumeAsync.
    * @param    status: This holds the status of call
    * @param    audioPresError: This holds the status of audioPresCtrlType
    * @param    volume: Volume of requested source
    * @return	void.
    */
    void onGetSourceVolumeAsyncCb(const CommonAPI::CallStatus& status, const audioPresCtrlTypes::eAudioPresErrors&, const audioPresCtrlTypes::sSourceVolume& volume);

    /**
     * @brief   onActiveAudioSourcesAttributeCb
     * @param   vectSourceId: Vector of Active SourceID.
     * @return  void.
     */
    void onActiveAudioSourcesAttributeCb(
            const std::vector<audioPresCtrlTypes::SourceId> &vectSourceId) override;

    /**
    * @brief    Callback to get notified about audio off
    * @param    status: callstatus holding the API call status.
    * @param    audioPresPluginTypes::eAudioPresPluginErrors&: holds the status of audioPresStatus
    * @return	void.
    */
    void onSetAudioOffCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors& audioPresStatus) override;

    /**
    * @brief    Callback to get notified about SwitchToPreviousEntSourceAsync method response
    * @param    status: callstatus holding the API call status.
    * @param    audioPresPluginTypes::eAudioPresPluginErrors&: holds the status of audioPresStatus
    * @return	void.
    */
    void switchToPreviousEntSourceCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors& audioPresStatus) override;

    /**
    * @brief	onAuxConnectionStateAttribute: This function is to get connection state type value on connection/disconnection of AUX source.
    * @param    strAuxConnectionState: String value holding the connection state type
    * @return	void.
    */
    virtual void onAuxConnectionStateAttribute(const std::string &strAuxConnectionState);

    /**
    * @brief	onUSBConnectionStateAttribute: This function is to get connection state type value on connection/disconnection of USB source.
    * @param    strUSBConnectionState: String value holding the connection state type
    * @return	void.
    */
    virtual void onUSBConnectionStateAttribute(const std::string &strUSBConnectionState);

    /**
    * @brief	onIPODConnectionStateAttribute: This function is to get connection state type value on connection/disconnection of IPOD source.
    * @param    strIPODConnectionState: String value holding the connection state type
    * @return	void.
    */
    virtual void onIPODConnectionStateAttribute(const std::string &strIPODConnectionState);

    /*!
     * @brief   playFromSourceGroupAsyncCb: Callback to get notified about playFromSourceGroupAsync method response.
     * @param   eCallStatus: Call status of the playFromSourceGroupAsync method, whether success or not.
     * @param   eErrorType: Type of the error received after invoking playFromSourceGroupAsync method.
     * @return  void.
     */
    void playFromSourceGroupAsyncCb(const CommonAPI::CallStatus& eCallStatus, const audioPresPluginTypes::eAudioPresPluginErrors& eErrorType);

    /**
     * @brief getBassValue : This function is used to get the bass value.
     * @param   void.
     * @return  int: bass value.
     */
    int getBassValue();

    /**
     * @brief getMidValue : This function is used to get the mid value.
     * @param   void.
     * @return  int: mid value.
     */
    int getMidValue();

    /**
     * @brief getTrebleValue : This function is used to get the treble value.
     * @param   void.
     * @return  int: treble value.
     */
    int getTrebleValue();

    /**
     * @brief getBalanceValue : This function is used to get the balance value.
     * @param   void.
     * @return  int : balance value.
     */
    int getBalanceValue();

    /**
     * @brief getFadeValue : This function is used to get the fade value.
     * @param   void.
     * @return  int : fade value.
     */
    int getFadeValue();

    /**
     * @brief getFMSrcStatus : This function is used to get the FM source status.
     * @param   void.
     * @return  bool : FM source status.
     */
    bool getFMSrcStatus();

    /**
     * @brief getAMSrcStatus : This function is used to get the fade AM source status.
     * @param   void.
     * @return  bool : AM source status.
     */
    bool getAMSrcStatus();

    /**
     * @brief getUSBSrcStatus : This function is used to get the USB source status.
     * @param   void.
     * @return  bool : Usb source status.
     */
    bool getUSBSrcStatus();

    /**
     * @brief getIPODSrcStatus : This function is used to get the IPOD source status.
     * @param   void.
     * @return  bool : Ipod source status.
     */
    bool getIPODSrcStatus();

    /**
     * @brief getAUXSrcStatus : This function is used to get the AUX source status.
     * @param   void.
     * @return  bool : Aux source status.
     */
    bool getAUXSrcStatus();

    /**
     * @brief getBTSrcStatus : This function is used to get the BT source status.
     * @param   void.
     * @return  bool : Bt source status.
     */
    bool getBTSrcStatus();

    /**
     * @brief getActiveEntSrcVolume : This function is used to get the active entertainment source volume.
     * @param   void.
     * @return  int : Active entertainment source volume.
     */
    int getActiveEntSrcVolume();

    /**
     * @brief getVolumeGroup : This function is used to get the volume source group.
     * @param   void.
     * @return int : Volume source group.
     */
    int getVolumeGroup();

    /**
     * @brief getMuteStatus : This function is used to get the mute status.
     * @param   void.
     * @return  bool : mute status
     */
    bool getMuteStatus();

    /**
     * @brief getVolumeUpdatedByUserStatus : This function is used to get the volume update by user status.
     * @param   void.
     * @return  bool : Volume updated by user status.
     */
    bool getVolumeUpdatedByUserStatus();

    /**
     * @brief getSpeedDependantVolumeStatus : This function is used to get the speed dependant volume status.
     * @param   void.
     * @return  bool : speed dependant volume status.
     */
    bool getSpeedDependantVolumeStatus();

    /**
     * @brief getStartupVolume : This function is used to get the phone call volume.
     * @param   void.
     * @return  int : start up volume
     */
    int getStartupVolume();

    /**
     * @brief activeAudioPreset : This function is used to get the active audio preset
     * @param void.
     * @return string &: reference of active audio preset
     */
    const string &getActiveAudioPreset();

    /**
     * @brief getMicMuteStatus : This function is used to get the mic mute status.
     * @param   void.
     * @return  bool : mic mute status.
     */
    bool getMicMuteStatus();

    /**
     * @brief getAuxGainValue : This function is used to get the aux gain value.
     * @param   void.
     * @return  int : Aux gain value.
     */
    int getAuxGainValue();

    /**
     * @brief getActiveEntSrc : This function is used to get the active entartainment source.
     * @param   void.
     * @return  CAudioEnums::EAudioEntertainmentSrcs : Active entertainment source.
     */
    CAudioEnums::EAudioEntertainmentSrcs getActiveEntSrc();

    /**
     * @brief getSourceId : This function is used to get the active source id.
     * @param   void.
     * @return int : active source id value.
     */
    int getSourceId();

    /**
     * @brief getAuxConnectionStatus : This function is used to get the aux connection status.
     * @param   void.
     * @return  string &: reference of Aux connection status.
     */
    const string &getAuxConnectionStatus();

    /**
     * @brief getIpodConnectionStatus : This function is used to get the ipod connection status.
     * @param   void.
     * @return  string &: reference of Ipod connection status.
     */
    const string &getIpodConnectionStatus();

    /**
     * @brief getUsbConnectionStatus : This function is used to get the usb connection status.
     * @param   void.
     * @return  string &: reference of  Usb connection status.
     */
    const string &getUsbConnectionStatus();

    /**
     * @brief getPdcMixModeStatus : This function is used to get the pdc mix mode status.
     * @param   void.
     * @return  bool : pdc mix mode status.
     */
    bool getPdcMixModeStatus();

private:
    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    CAudioResourceImpl();

    /**
    * @brief	This function is to subscribe the audio settings events
    *           provided by audiopresctrlsettings proxy.
    * @param    void.
    * @return	void.
    */
    void subscribeSettingsProxy();

    /**
    * @brief	This function is to subscribe the audio sources events
    *           provided by audioPresCtrlControls proxy.
    * @param    void.
    * @return	void.
    */
    void subscribeControlProxy();

    /**
    * @brief	This function is to subscribe the audio plugin events
    *           provided by audioPresCtrlPlugin proxy.
    * @param    void.
    * @return	void.
    */
    void subscribeAudioPluginProxy();

    /**
    * @brief	This function is to get the Aux gain value.
    * @param    iAuxOffsetGain: This holds Aux gain value.
    * @return	void.
    */
    void onAuxOffsetGainAttributeCb(int16_t iAuxOffsetGain);

    /*!
     * @brief   getSourceGroup: Internal method to map audio resource's supported source category enums
     *          to Audio service source group enums. The mapped enums shall be used by the class itself.
     * @param   iSourceCategory - Audio resource's source category enum value.
     * @return  Audio service source group enum value.
     */
    audioPresPluginTypes::eSourceGroup getSourceGroup(int iSourceCategory);

    /* Create an instance of the CAudioDataEventProvider to emit signals to the upper layer **/
    CAudioEventProvider* m_pAudioEventProvider;

    /* audiopresctrlcontrolsproxy class object to call audio proxy methods **/
    CAPIClientAbstraction<audioPresCtrlControlsProxy> m_pAudioControlProxy;

    /* audiopresctrlsettingssproxy class object to call audio proxy methods **/
    CAPIClientAbstraction<audioPresCtrlSettingsProxy> m_pAudioSettingsProxy;

    /* audiopresctrlpluginproxy class object to call audio proxy methods **/
    CAPIClientAbstraction<TataAudioPresPluginProxy> m_pAudioPluginProxy;

    /* This variable holds the API availability status, TRUE if available else FALSE **/
    bool m_bAudioSettingAvailable;

    /* This variable holds the API availability status, TRUE if available else FALSE **/
    bool m_bAudioControlAvailable;

    /* This variable holds the API availability status, TRUE if available else FALSE **/
    bool m_bAudioPluginAvailable;

    /* This variable holds the Tuner source availability status **/
    bool m_bTunerAvailable;

    /* This variable holds the Media source availability status **/
    bool m_bMediaAvailable;

    /* This variable holds the BT source availability status **/
    bool m_bBTAvailable;

    /* This variable holds the AUX source availability status **/
    bool m_bAUXAvailable;

    /* This variable holds the USB source availability status **/
    bool m_bUSBAvailable;

    /* This variable holds the IPOD source availability status **/
    bool m_bIPodAvailable;

    /**
     * @brief vectActiveAudioSource: Vector of Active Audio Sources.
     */
    std::vector<uint16_t> m_vectActiveAudioSource;

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

    /* This variable holds the active entertainment source volume */
    int m_iActEntSourceVolume;

    /* This variable holds the active source mute status*/
    bool m_bMuteActive;

    /* This Variable is used to hold value of user interaction
     * when volume update is received*/
    bool m_bIsVolumeUpdatedByUser;

    /* This variable holds the volume group */
    int m_iVolumeGroup;

    /* This variable holds the active source id*/
    int m_iSourceId;

    /* This variable holds the speed depandant volume status*/
    bool m_bSpeedDependantVolume;

    /* This variable holds the start up volume status*/
    int m_iStartUpVolume;

    /* This variable holds the active Audio Preset */
    std::string m_strActiveAudioPreset;

    /* This variable holds the  mic mute status */
    bool m_bMicMuteStatus;

    /* This variable holds the aux gain value */
    int m_iAuxGainValue;

    /* This variable holds the active entertainment source */
    CAudioEnums::EAudioEntertainmentSrcs m_eActiveEntSrc;

    /*This variable holds the value of current connection status of Aux
     * Possible Values: AUX_STATE_UNKNOWN, AUX_CONNECTED, AUX_ALREADY_CONNECTED, AUX_REMOVED */
    std::string m_strAuxConnectionStatus;

    /*This variable holds the value of current connection status of Ipod
     *        Possible Values: IPOD_STATE_UNKNOWN, IPOD_CONNECTED, IPOD_ALREADY_CONNECTED, IPOD_DISCONNECTED */
    std::string m_strIpodConnectionStatus;

    /*This variable holds the value of current connection status of Usb
     *        Possible Values: USB_STATE_UNKNOWN, USB_CONNECTED, USB_ALREADY_CONNECTED, USB_DISCONNECTED */
     std::string m_strUsbConnectionStatus;

    /* This variable holds the pdc mix mode status */
    bool m_bPdcMixModeStatus;

};
#endif // CAUDIORESOURCEIMPL_H

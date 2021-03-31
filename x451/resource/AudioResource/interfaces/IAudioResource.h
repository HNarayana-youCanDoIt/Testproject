/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          IAudioResource.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 *  IAudioResource, an interface for Audio Resource Implementaion in HMI.
 */


#ifndef IAUDIORESOURCE_H
#define IAUDIORESOURCE_H

#include "v3/com/harman/audio/audioPresCtrl/audioPresCtrlTypes.hpp"
#include <capi/CAPIClientAbstraction.hpp>
#include "resource/AudioResource/implementations/CDataAudioManger.h"
#include "Audio/CAudioEnums.h"
#include "v0/com/harman/audiopres/plugin/audioPresPluginTypes.hpp"

using namespace std;
using namespace v3::com::harman::audio::audioPresCtrl;
using namespace v0::com::harman::audiopres::plugin;

/*!
 * @interface IAudioResource
 * @brief This interfaces provides abstract methods to communicate with the
 * AudioPresCtrl proxy directly which shall be implemented by resource
 * implementation class.
 */

class IAudioResource
{
public:
    virtual ~IAudioResource(){}

    /*****  Request METHODS  ****************************/

    /**
    * @brief	This pure virtual function is to set bass value, API call to be made with this method.
    * @param    iBass: bass is integer holding the bass value set from audio adaptor.
    * @return	void.
    */
    virtual void setBass(int16_t iBass) = 0;

    /**
    * @brief	This pure virtual function is to set mid value, API call to be made with this method.
    * @param    iMid: mid is integer holding the mid value set from audio adaptor.
    * @return	void.
    */
    virtual void setMid(int16_t iMid) = 0;

    /**
    * @brief	This pure virtual function is to set treble value, API call to be made with this method.
    * @param    iTreble: treble is integer holding the treble value set from audio adaptor.
    * @return	void.
    */
    virtual void setTreble(int16_t iTreble) = 0;

    /**
    * @brief	This pure virtual function is to set fader & balance value, API call to be made with this method.
    * @param    iFader: fader value to be sent to LB
    * @param    iBalance: balance value to be sent to LB
    * @return	void.
    */
    virtual void setFaderBalance(int16_t iFader, int16_t iBalance) = 0;

    /**
    * @brief	This function is going to call the audiopress control API to activate audio source.
    * @param    eSrcID: srcId will hold the entertainment source ID.
    * @return	void.
    */
    virtual void setActiveSourceID(CAudioEnums::EAudioEntertainmentSrcs eSrcID) = 0;

    /**
    * @brief	This pure virtual function is to set the audio preset, API call to be made with this method.
    * @param    strPreset: preset will set the Audio Preset.
    * @return	void.
    */
    virtual void setAudioPreset(const string &strPreset) = 0;

    /**
    * @brief	This method is used to toggle system mute, which is going to call TataAudioPresPluginProxy(service) API.
    * @param    void
    * @return	void.
    */
    virtual void ToggleSystemMute() = 0;

    /**
     * @brief	This method is used to toggle mute status of currently playing sources as per TML mute strategy
     * @param   bUserInitiated: set this flag to true if it is a user triggerred mute event.
     * @return	void.
     */
    virtual void toggleMute(const bool &bUserInitiated) = 0;

    /**
    * @brief	This method is used to play the beep.
    * @param    CAudioEnums::EBeepType eBeepType: beep type to be played.
    * @return	void.
    */
    virtual void playBeep(CAudioEnums::EBeepType eBeepType) = 0;

    /**
    * @brief	This method is to set the start up volume, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    iStartUpVolume: startupvolume will set the startup volume.
    * @return	void.
    */
    virtual void setStartUpVolume(int16_t iStartUpVolume) = 0;

    /**
    * @brief	This method is to set the SDVC state, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    bSdvcState: bSdvcState will set the speed dependant volume state.
    * @return	void.
    */
    virtual void setSDVCState(bool bSdvcState) = 0;

    /**
    * @brief	This method is to set the phone call volume, which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    iAabsoluteVolume: iAabsoluteVolume will set the phone call volume.
    * @return	void.
    */
    virtual void setPhoneSourceVolume(const uint16_t &iAbsoluteVolume) = 0;

    /**
    * @brief	This method is to set the park assist volume, which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    iAbsoluteVolume: iAbsoluteVolume contains the park assist volume.
    * @return	void.
    */
    virtual void setParkAssistVolume(const uint16_t &iAbsoluteVolume) = 0;

    /**
    * @brief	This method is to set the voice alert volume, which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    iAabsoluteVolume: iAabsoluteVolume will set the voice alert volume.
    * @return	void.
    */
    virtual void setVoiceAlertVolume(const uint16_t &iAbsoluteVolume) = 0;

    /**
    * @brief	This method is to set the notifiaction volume, which is going to call audioPresCtrlSettingsProxy(service) API.
    * @param    iAabsoluteVolume: iAabsoluteVolume will set the notification volume.
    * @return	void.
    */
    virtual void setNotificationVolume(const uint16_t &iAbsoluteVolume) = 0;

    /**
    * @brief	This method is to set the Aux in gain, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    eAuxInGain: eAuxInGain will set the Aux in Gain.
    * @return	void.
    */
    virtual void setAuxInGain(CAudioEnums::EAuxInGain eAuxInGain) = 0;

    /**
    * @brief	This method is to set the source volume, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    iSourceID: iSourceID will hold the source ID.
    * @param    iAbsoluteVolume: iAbsoluteVolume will hold volume.
    * @return	void.
    */
    virtual void setSourceVolume(const int &iSourceID, const uint16_t &iAbsoluteVolume) = 0;

    /**
    * @brief	This method is to set the toggle source, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    edirection: edirection will hold direction in which source will toggle.
    * @return	void.
    */
    virtual void toggleSource(CAudioEnums::EToggleDirection edirection) = 0;

    /**
     * @brief   This method is used to toggle MIC mute status.
     * @param   void.
     * @return  void.
     */
    virtual void toggleMicMute() = 0;

    /**
    * @brief	This method is to set the pdc mix mode state, which is going to call audioPresCtrlPluginProxy(service) API.
    * @param    bPdcMixModeState: bPdcMixModeState will hold pdc mix mode status.
    * @return	void.
    */
    virtual void setPdcMixModeState(bool bPdcMixModeState) = 0;

    /**
    * @brief	This method is to get the Volume of any source
    * @param    sourceID: Source id is to be passed.
    * @return	void.
    */
    virtual void getSourceVolume(const int &sourceID) = 0;
	
    /**
     * @brief   getActiveAudioSourceList: Method to get Active Audio
     *          Source List.
     * @param   void.
     * @return  void.
     */
    virtual const vector<uint16_t>&  getActiveAudioSourceList() const = 0;

    /**
     * @brief setAudioOff This method is used to make Sink audio ON-OFF
     * @param bAudioState state to set On-Off (true, false)
     */
    virtual void setAudioOff(bool bAudioState) = 0;

    /**
     * @brief switchToPreviousEntSource-  This method is used to switch to previous Ent. source
     * @param void
     * @return void
     */
    virtual void switchToPreviousEntSource() = 0;

    /**
     * @brief   playFromSourceGroup: Method to be implemented to play a source group. Audo service shall
     *          take care of playing the source from the group.
     * @param   iSourceGroup: Source group to be played.
     * @return  void
     */
    virtual void playFromSourceGroup(int iSourceGroup) = 0;

    /*****  CALL BACK METHODS  ****************************/

    /**
    * @brief	This function is call back method to get bass value, response from audiopresctrlproxy received here.
    * @param    iBass: bass holding the bass value on response.
    * @return	void.
    */
    virtual void onBassAttributeCb(int16_t iBass) = 0;

    /**
    * @brief	This function is call back method to get mid value, response from audiopresctrlproxy received here.
    * @param    iMid: mid holding the updated mid value on response.
    * @return	void.
    */
    virtual void onMidAttributeCb(int16_t iMid) = 0;

    /**
    * @brief	This function is call back method to get treble value, response from audiopresctrlproxy received here.
    * @param    iTreble: treble holding the updated treble value on response.
    * @return	void.
    */
    virtual void onTrebleAttributeCb(int16_t iTreble) = 0;

    /**
    * @brief	This function is call back method to get balance value, response from audiopresctrlproxy received here.
    * @param    iBalance: balance holding the updated balance value on response.
    * @return	void.
    */
    virtual void onBalanceAttributeCb(int16_t iBalance) = 0;

    /**
    * @brief	This function is call back method to get fade value, response from audiopresctrlproxy received here.
    * @param    iFade: fade holding the updated fade value on response.
    * @return	void.
    */
    virtual void onFadeAttributeCb(int16_t iFade) = 0;

    /**
    * @brief	This function is call back method to get active entertainment source value, response from audiopresctrlproxy received here.
    * @param    objEntSrcInfo: objEntSrcInfo is a data structure holding information of an entertainment source
    * @return	void.
    */
    virtual void onActiveEntSourceAttributeCb(audioPresCtrlTypes::sSourceInfo objEntSrcInfo) = 0;

    /**
    * @brief	This function is call back method to get active entertainment source list, response from audiopresctrlproxy received here.
    * @param    mapEntSrcInfo: mapEntSrcInfo is a data structure holding information of an entertainment source list.
    * @return	void.
    */
    virtual void onEntSourceListAttributeCb(audioPresCtrlTypes::mEntSrcsInfo mapEntSrcInfo) = 0;

    /**
    * @brief	This function is call back method to get the Common API call status as Sucess or failure.
    * @param    status: callstatus will hold the event status on subscription.
    * @return	void.
    */
    virtual void SetEntertainmentSrcAsyncCb(const CommonAPI::CallStatus &status, const audioPresCtrlTypes::eAudioPresErrors&) = 0;

    /**
    * @brief	This pure virtual function is to get audio preset value, response from audiopresctrlproxy received here.
    * @param    strPreset : Preset to be updated in UI.
    * @return	void.
    */
    virtual void onAudioPresetAttributeCb(string strPreset) = 0;

    /**
    * @brief	This function is to get active entertainment source volume value on event subscription and update the value to audiodataeventprovider class.
    * @param    objSrcVolume : objSrcVolume is structure which will hold absolute volume of active source and sourceID.
    * @param    bEventTriggeredByUser: eventTriggered By User or system, (true)volume triggered by user or (false) system triggered.
    * @param    eVolumeGroup: volume group will have group of entertainment sources, interrupt sources.
    * @return	void.
    */
    virtual void onVolumeUpdateEventCb(audioPresCtrlTypes::sSourceVolume objSrcVolume, bool bEventTriggered, audioPresCtrlTypes::eVolumeGroup eVolumeGroup) = 0;

    /**
    * @brief	This function is call back method to get active source mute, response from audiopresctrlproxy received here.
    * @param    bActiveSourceMute: bActiveSourceMute will hold mute status.
    * @return	void.
    */
    virtual void onActiveSrcMuteAttributeCb(bool bActiveSourceMute) = 0;

    /**
    * @brief	This function is to check the Start Up Volume API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onStartUpVolumeCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors&) = 0;

    /**
    * @brief	This function is to check the SDVC state API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onSdvcStateCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors&) = 0;

    /**
    * @brief	This function is to check the source volume API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onSourceVolumeAsyncCb(const CallStatus &status, const audioPresCtrlTypes::eAudioPresErrors&) = 0;

    /**
    * @brief	This function is to get start up volume value on event subscription and update the value to audiodataeventprovider class.
    * @param    iStartUpVolume: iStartUpVolume holding the start up volume.
    * @return	void.
    */
    virtual void onStartupVolumeAttributeCb(int16_t iStartUpVolume) = 0;

    /**
    * @brief	This function is to get SDVC state on event subscription and update the value to audiodataeventprovider class.
    * @param    bSdvcState: bSdvcState holding the SDVC state.
    * @return	void.
    */
    virtual void onSdvcStateAttributeCb(bool bSdvcState) = 0;

    /**
    * @brief	This function is to get PDC Mix Mode state on event subscription and update the value to audiodataeventprovider class.
    * @param    bPdcMixModeState: bPdcMixModeState holding the Pdc mix mode state.
    * @return	void.
    */
    virtual void onPdcMixModeAttributeCb(bool bPdcMixModeState) = 0;

    /**
    * @brief	This function is to check the Aux in gain API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onAuxInGainCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors&) = 0;

    /**
    * @brief	This function is to check the toggle source API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onToggleSourceAsyncCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors &) = 0;

    /*!
     * @brief   Callback to get notified about the mic mute status.
     * @param   bMicMuteStatus   - mic mute status, TRUE if mic is muted, false otherwise.
     * @return  void.
     */
    virtual void onMicMuteStatusCb(bool bMicMuteStatus) = 0;

    /**
    * @brief	This function is to check the pdc mix mode API call status.
    * @param    status: callstatus holding the API call status.
    * @return	void.
    */
    virtual void onPdcMixModeStatusCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors &) = 0;

    /**
     * @brief   onActiveAudioSourcesAttributeCb
     * @param   vectSourceId: Vector of Active SourceID.
     * @return  void.
     */
     virtual void onActiveAudioSourcesAttributeCb(
            const std::vector<audioPresCtrlTypes::SourceId> &vectSourceId) = 0;

    /**
    * @brief    Callback to get notified about audio off
    * @param    status: callstatus holding the API call status.
    * @param    audioPresPluginTypes::eAudioPresPluginErrors&: holds the status of audioPresStatus
    * @return	void.
    */
    virtual void onSetAudioOffCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors& audioPresStatus) = 0;

    /**
    * @brief    Callback to get notified about SwitchToPreviousEntSourceAsync method response
    * @param    status: callstatus holding the API call status.
    * @param    audioPresStatus: holds the status of audioPresStatus
    * @return	void.
    */
    virtual void switchToPreviousEntSourceCb(const CallStatus &status, const audioPresPluginTypes::eAudioPresPluginErrors& audioPresStatus) = 0;

    /**
    * @brief	This function is to get connection state type value on connection/disconnection of AUX source.
    * @param    strAuxConnectionState: String value holding the connection state type
    * @return	void.
    */
    virtual void onAuxConnectionStateAttribute(const std::string &strAuxConnectionState) = 0;

    /**
    * @brief	This function is to get connection state type value on connection/disconnection of USB source.
    * @param    strUSBConnectionState: String value holding the connection state type
    * @return	void.
    */
    virtual void onUSBConnectionStateAttribute(const std::string &strUSBConnectionState) = 0;

    /**
    * @brief	This function is to get connection state type value on connection/disconnection of IPOD source.
    * @param    strIPODConnectionState: String value holding the connection state type
    * @return	void.
    */
    virtual void onIPODConnectionStateAttribute(const std::string &strIPODConnectionState) = 0;

};

#endif // IAUDIORESOURCE_H



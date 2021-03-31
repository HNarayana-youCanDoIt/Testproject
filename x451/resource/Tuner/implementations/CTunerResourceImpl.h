/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CTunerResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Manali Patil
 * CTunerResourceImpl, The class includes resource layer implementation
**/

#ifndef CTUNERRESOURCEIMPL_H
#define CTUNERRESOURCEIMPL_H

#include <QVariant>
#include <memory>
#include "resource/Tuner/interfaces/ITunerResource.h"
#include "resource/Tuner/interfaces/ITunerTypes.h"
#include "CTunerEventProvider.h"
#include <capi/CAPIClientAbstraction.hpp>

using namespace std;
using namespace v3::com::harman::tuner;

/** The class includes resource layer implementation */
class CTunerResourceImpl : public ITunerResource
{
public:
    CTunerResourceImpl();
    virtual ~CTunerResourceImpl();
    CTunerEventProvider* getTunerDataEventProvider();

    /**
    * @brief tunerProxyAvailability - subscribe to the tunerservice proxy
    * @param status - void
    * @return - void
    */
    virtual void init();

    /**
    * @brief tunerProxyAvailability - status for the availability change of tuner proxy
    * @param status - AvailabilityStatus
    * @return - void
    */
    virtual void tunerProxyAvailability(CommonAPI::AvailabilityStatus status);

    /**
    * @brief tunerIntrospectionProxyAvailabilityCb - status for the availability change of tuner introspection proxy
    * @param status - AvailabilityStatus
    * @return - void
    */
    virtual void tunerIntrospectionProxyAvailabilityCb(CommonAPI::AvailabilityStatus status);

    /**
     * @brief startSeekUp - start the seek up functionality
     * @param  - void
     * @return - void
     */
    virtual void startSeekUp();

    /**
     * @brief startSeekDown - start the seek down functionality
     * @param  - void
     * @return - void
     */
    virtual void startSeekDown();

    /**
     * @brief startScan - start the scan functionality
     * @param  - void
     * @return - void
     */
    virtual void startScan();

    /**
     * @brief startManualSeekUp - start the manual seek up functionality
     * @param  - void
     * @return - void
     */
    virtual void startManualSeekUp();

    /**
     * @brief startManualSeekDown - start the manual seek down functionality
     * @param  - void
     * @return - void
     */
    virtual void startManualSeekDown();

    /**
     * @brief startAutoStore - start the autostore functionality
     * @param  - void
     * @return - void
     */
    virtual void startAutoStore();

    /**
     * @brief stopSeek - stop the seek functionality
     * @param type - void
     * @return - void
     */
    virtual void stopSeek();

    /**
     * @brief stopSeekOnScanAndAutostore - stop seek for scan or autostore is active
     * @param type - void
     * @return - void
     */
    virtual void stopSeekOnScanAndAutostore();

    /**
     * @brief setFrequency - set a given frequency
     * @param type - frequency to be set
     * @return - void
     */
    virtual void setFrequency(int iFrequency);

    /**
    * @brief addToPreset -add current frequency to the given preset
    * @param type -preset number
    * @return - void
    */
    virtual void addToPreset(int preset);

    /**
    * @brief selectPreset -select the given preset
    * @param type -preset number
    * @return - void
    */
    virtual void selectPreset(int preset);

    /**
    * @brief enableQualityMonitor - control if the quality monitor should be on/off
    * @param bMonitorFlag - true if quality monitor is to be enabled else false
    * @return - void
    */
    virtual void enableQualityMonitor(bool bMonitorFlag);

    /**
    * @brief getPresetList-get the preset frequency and preset index of all the available presets
    * @param type -void
    * @return - mapPresetList: QMap of Preset frequencies and preset index as key value
    */
    map<uint, uint> getPresetList();

    /**
     * @brief callStationSelectStationAsync - asyc call to select the station
     * @param  - StationSelector struct (tag, frequency, prrset, seekMode, genre), handle, callback, callinfo
     * @return - void
     */
    void callStationSelectStationAsync(const OrinocoTunerTypes::StationSelector &stationSelector, const uint32_t &handle, OrinocoTunerProxyBase::StationSelectStationAsyncCallback callback = nullptr, const CommonAPI::CallInfo *info = nullptr);

    /** Signals */
    /**
     * @brief onCurrentStation () : signal for any change in station information.
     * @param - AudioCurrentStation
     * @return - current frequency, Band, SeekMode
     */
    void onCurrentStation(const OrinocoTunerTypes::AudioCurrentStation &currStation);

    /**
     * @brief onQualityAmFmChangeCb () : signal for any change in multipath value.
     * @param - QualityAmFms: AM specific quality parameters, QualityDabs: DAB specific quality parameters , QualityDrms: DRM specific quality parameters
     * @return - void
     */
    void onQualityAmFmChangeCb(const OrinocoTunerIntrospectionTypes::QualityAmFms &qualityamfmlist, const OrinocoTunerIntrospectionTypes::QualityDabs &qualitydablist, const OrinocoTunerIntrospectionTypes::QualityDrms &qualitydrmlist);

    /**
     * @brief onReceiveStationList () : signal for station list after autostore.
     * @param -AudioStationList(frequency and preset number used)
     * @return - void
     */
    void onReceiveStationList(const OrinocoTunerTypes::AudioStationList &audioStationList);

    /**
     * @brief onPresetListChange() : signal for any change in station list after preset.
     * @param -StationList(contains preset and the frequency to be stored in the corresponding preset)
     * @return - void
     */
    void onPresetListChange(const OrinocoTunerTypes::StationList &stationList);

    /**
     * @brief onReceiveStationList () : stores station list returned after autostore in map and expose list to adaptor.
     * @param -sList: list returned after autostore operation
     * @return - void
     */
    void storePresetList(std::vector<OrinocoTunerTypes::ListStation> sList);


    /** Callbacks */

    /**
     * @brief asyncStationSelectStationcb(): call status callback for any tunerApp aync calls
     * @param - callstatus
     * @return - void
     */
    void asyncStationSelectStationcb(const CommonAPI::CallStatus&);

    /**
     * @brief disableQualityMonitor(): call status to disable quality monitor for multipath.
     * @param - void.
     * @return - void.
     */
    void disableQualityMonitor() override;

private:

    /**
     * @brief subscribeTunerProxyEvents() : Method to subscribe CallBack methods to events,attributes provided by TunerProxy
     * @param - void
     * @return - void
     */
    void subscribeTunerProxyEvents();

protected:

    /** Map for Preset data structure */
    map< uint, uint> mapPresetList;

private:

    /**
     * @brief Adding ResourceFactory class as friend class so that
     * ResourceFactory shall be able to create the instance of this class.
     */
    friend class ResourceFactory;

    /**
     * @brief m_pTunerEventProvider Create an instance of the CTunerEventProvider to emit signals to the upper layer
     */
    CTunerEventProvider* m_pTunerEventProvider;

    CAPIClientAbstraction<OrinocoTunerProxy> m_Tuner_Proxy;

    CAPIClientAbstraction<OrinocoTunerIntrospectionProxy> m_Tuner_Introspection_Proxy;

    /** variable for seek Type */
    uint m_uiSeekType;

    /**
     * @brief m_iCurrentFrequency variable for current station frequency
     */
    int m_iCurrentFrequency;

    /**
     * @brief m_iLastPlayedFrequency variable holds frequency value that was playing before start of autostore and scan
     */
    int m_iLastPlayedFrequency;

    /**
     * @brief m_iBand variable for Band (AM, FM, DRM etc.)
     */
    int m_iBand;

    /**
     * @brief m_iFieldStrength variable for field strength of selected station
     */
    int m_iFieldStrength;

    /**
     * @brief m_strStationName string variable for station name
     */
    string m_strStationName;

    /**
     * @brief m_uiTagId variable for tag id of selected station
     */
    uint m_uiTagId;

    /**
     * @brief m_ucMultipath variable for multipath value of selected station
     */
    uint8_t m_ucMultipath;

    /**
     * @brief m_currStation variable to store current information
     */
    OrinocoTunerTypes::StationSelector m_currStation;

    /**
     * @brief m_bIsTunerProxyAvailable Flag to maintain tuner proxy availability status
     */
    bool m_bIsTunerProxyAvailable;

    /**
     * @brief m_bIsTunerIntrospectionProxyAvailable Flag to maintain tuner introspection proxy availability status
     */
    bool m_bIsTunerIntrospectionProxyAvailable;

};
#endif // TUNERRESOURCEIMPL_H

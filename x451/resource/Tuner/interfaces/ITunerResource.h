/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         ITunerResource.h
* @ingroup       HMIComponent
* @author        Manali Patil
* ITunerResource, the base class of TunerResourceImpl
* It is an interface for tuner service
*/

#ifndef ITUNERRESOURCE_H
#define ITUNERRESOURCE_H

#include <string>
#include <QString>
#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <capi/CAPIClientAbstraction.hpp>
#include "resource/Tuner/interfaces/ITunerTypes.h"
#include <v3/com/harman/tuner/OrinocoTunerProxy.hpp>
#include <v3/com/harman/tuner/OrinocoTunerTypes.hpp>
#include <v1/com/harman/tuner/OrinocoTunerIntrospectionTypes.hpp>
#include <v1/com/harman/tuner/OrinocoTunerIntrospectionProxy.hpp>

using namespace std;
using namespace v1::com::harman::tuner;

class ITunerResource
{

public:

    /** The base class of TunerResourceImpl */
    virtual ~ITunerResource() {}

    /** Request Methods */

    /**
    * @brief startSeekUp - start the seek up functionality
    * @param  - void
    * @return - void
    */
    virtual void startSeekUp() = 0;

    /**
    * @brief startSeekDown - start the seek down functionality
    * @param  - void
    * @return - void
    */
    virtual void startSeekDown() = 0;

    /**
    * @brief startScan - start the scan functionality
    * @param  - void
    * @return - void
    */
    virtual void startScan() = 0;

    /**
    * @brief startManualSeekUp - start the manual seek up functionality
    * @param  - void
    * @return - void
    */
    virtual void startManualSeekUp() = 0;

    /**
    * @brief startManualSeekDown - start the manual seek down functionality
    * @param  - void
    * @return - void
    */
    virtual void startManualSeekDown() = 0;

    /**
    * @brief startAutoStore - start the autostore functionality
    * @param  - void
    * @return - void
    */
    virtual void startAutoStore() = 0;

    /**
    * @brief stopSeek - stop the seek functionality
    * @param type - void
    * @return - void
    */
    virtual void stopSeek() = 0;

    /**
    * @brief stopSeekOnScanAndAutostore - stop seek when scan or autostore is active
    * @param type - void
    * @return - void
    */
    virtual void stopSeekOnScanAndAutostore() = 0;
    /**
    * @brief setFrequency - set a given frequency
    * @param type - frequency to be set
    * @return - void
    */
    virtual void setFrequency(int ifrequency) = 0;

    /**
    * @brief addToPreset -add current frequency to the given preset
    * @param type -preset number
    * @return - void
    */
    virtual void addToPreset(int preset) = 0;

    /**
    * @brief selectPreset -select the given preset
    * @param type -preset number
    * @return - void
    */
    virtual void selectPreset(int preset) = 0;

    /**
    * @brief getPresetList-get the frequency and preset number of all the available presets
    * @param type -void
    * @return - mapPresetList: QMap for Preset data structure
    */
    virtual map< uint, uint> getPresetList() = 0;

    /**
    * @brief tunerProxyAvailability - callback for the availability change of tuner proxy
    * @param status - AvailabilityStatus
    * @return - void
    */
    virtual void tunerProxyAvailability(CommonAPI::AvailabilityStatus status) = 0;

    /**
    * @brief enableQualityMonitor - control if the quality monitor should be on/off
    * @param bMonitorFlag - true if quality monitor is to be enabled else false
    * @return - void
    */
    virtual void enableQualityMonitor(bool bMonitorFlag) = 0;

    /**
     * @brief disableQualityMonitor(): call status to disable quality monitor for multipath.
     * @param - void.
     * @return - void.
     */
    virtual void disableQualityMonitor() = 0 ;

    /**
    * @brief tunerIntrospectionProxyAvailabilityCb - callback for the availability change of tuner introspection proxy
    * @param status - AvailabilityStatus
    * @return - void
    */
    virtual void tunerIntrospectionProxyAvailabilityCb(CommonAPI::AvailabilityStatus status) = 0;


};

#endif // ITUNERRESOURCE_H

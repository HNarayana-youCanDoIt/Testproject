/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CTunerEventProvider.h
 * @ingroup       HMIComponent
 * @author        Manali Patil
 * CTunerEventProvider, The class sends signals raised to the event handler class
 * It has the implementation of the signals
**/

#ifndef CTunerEventProvider_H
#define CTunerEventProvider_H

#include <QObject>

using namespace std;

/**
 * @brief The class sends signals raised to the event handler class
 */
class CTunerEventProvider: public QObject
{
    Q_OBJECT

public:
    CTunerEventProvider(QObject* parent = 0);
    ~CTunerEventProvider();

signals:    
    /**
    *All events  received from the below layers are propagated to the upper layers.
    **/
    /**
     * @brief sigUpdateSeekType Signal to update seek Type
     * @param uiSeekType
     */
    void sigUpdateSeekType(uint uiSeekType);

    /**
     * @brief sigUpdateFrequency Signal to update frequency
     * @param uiFrequency
     */
    void sigUpdateFrequency(uint uiFrequency);

    /**
     * @brief sigUpdateBand Signal to update band
     * @param iBand
     */
    void sigUpdateBand(int iBand);

    /**
     * @brief sigManualSeekStatus Signal to update manual seek status
     */
    void sigManualSeekStatus();

    /**
     * @brief sigUpdateStationName Signal to update station name
     * @param objStrStationName
     */
    void sigUpdateStationName(const string &objStrStationName);

    /**
     * @brief sigPresetListResponseReceived Signal to update preset response status
     */
    void sigPresetListResponseReceived();

    /**
     * @brief sigActivePresetResponseReceived Signal to update active preset response status
     */
    void sigActivePresetResponseReceived();

    /**
     * @brief sigUpdateFieldStrength Signal to update field strength value of currently tuned station
     * @param iFieldStrength
     */
    void sigUpdateFieldStrength(int iFieldStrength);

    /**
     * @brief sigUpdateTagId Signal to update tag id of currently tuned station
     * @param uiTagId
     */
    void sigUpdateTagId(uint uiTagId);

    /**
     * @brief sigValidStationFoundUpdated Signal to update valid station found status
     * @param bStatus
     */
    void sigValidStationFoundUpdated(bool bStatus);


    /**
     * @brief sigUpdateMultipath Signal to update multipath value
     * @param ucMultipathValue
    */
    void sigUpdateMultipath(unsigned char ucMultipathValue);

    /**
     * @brief Signal to update the quaity Monitor
    */
    void sigIntrospectionProxyAvailable();

    /**
     * @brief sigUpdateTunerStatus Signal to update tuner proxy availabity status
     * @param bIsTunerAvailable
     */
    void sigUpdateTunerStatus(bool bIsTunerAvailable);

public:
    /**
    * Functions used by the Resource layer to indirectly emit signals to the upper layers
    **/

    /**
     * @brief updateSeekType - Function used by Resource layer to emit seek Type
     * @param uint - uiSeekType
     * @return - void
     */
    void updateSeekType(uint uiSeekType);

    /**
     * @brief updateFrequency - Function used by Resource layer to emit frequency
     * @param uint - uiFrequency
     * @return - void
     */
    void updateFrequency(uint uiFrequency);

    /**
     * @brief updateBand - Function used by Resource layer to emit band
     * @param int - iBand
     * @return - void
     */
    void updateBand(int iBand);

    /**
     * @brief manualTuningStatus - Function used by Resource layer to emit manual seek status
     * @param - void
     * @return - void
     */
    void manualTuningStatus();

    /**
     * @brief updateStationName - Function used by Resource layer to emit station name
     * @param - void
     * @return - void
     */
    void updateStationName(const string &objStrStationName);

    /**
     * @brief PresetListResponseReceived - Function used by Resource layer to emit preset list response status
     * @param - void
     * @return - void
     */
    void presetListResponseReceived();

    /**
     * @brief ActivePresetResponseReceived - Function used by Resource layer to emit active preset response status
     * @param - void
     * @return - void
     */
    void activePresetResponseReceived();


    /**
     * @brief updateFieldStrength- Function used by Resource layer to emit signal strength
     * @param - iFieldStrength : field strength or signal strength of Tuner.
     * @return - void
     */
    void updateFieldStrength(int iFieldStrength);

    /**
     * @brief updateTag- Function used by Resource layer to emit Tag of current station
     * @param uiTagId - tag id of current frequency
     * @return - void
     */
    void updateTagId(uint uiTagId);

    /**
     * @brief validStationFoundStatus- Function used by Resource layer to emit the valid station found status
     * @param - bStatus
     * @return - void
     */
    void validStationFoundStatus(bool bStatus);

    /**
     * @brief updateMultipath- Function used by Resource layer to emit multipath value
     * @param - ucMultipath - multipath value
     * @return - void
     */
    void updateMultipath(uint8_t ucMultipath);

    /**
     * @brief introspectionProxyAvailable- Function to update  the quality monitor.
     * @param - void.
     * @return - void.
     */
    void introspectionProxyAvailable();

    /**
     * @brief updateTunerStatus- Function used by Resource layer to emit tunerservice proxy status
     * @param bIsTunerAvailable
     * @return void
     */
    void updateTunerStatus(bool bIsTunerAvailable);
};

#endif // CTunerEventProvider_H


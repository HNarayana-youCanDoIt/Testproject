/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
* @file          CTunerEventHandler.h
* @ingroup       HMIComponent
* @author        Rahul Balyan
* CTunerEventHandler, The class listens for the signals raised by the resource layer provider class
* It has the implementation of the corresponding slots
**/

#ifndef CTunerEventHandler_H
#define CTunerEventHandler_H

#include <QObject>
#include "CTunerAdaptor.h"

/**
 * @brief The CTunerEventHandler class
 * The class listens for the signals raised by the resource layer provider class
 * It has the implementation of the corresponding slots
**/

class CTunerEventHandler: public QObject
{
    Q_OBJECT
public:
    CTunerEventHandler(QObject* parent = 0);
    ~CTunerEventHandler();

public slots:
    // slots that would be invoked on the resource layer events signals

    /*!
     * @brief   Method to notify Tuner adaptor regarding update of tuner seek type.
     * @param   uiSeekState: uint
     * @return  void.
     */
    void sltUpdateSeekType(uint uiSeekState);

    /*!
     * @brief   Method to notify Tuner adaptor regarding update of tuner current frequency.
     * @param   uiFrequency: uint
     * @return  void.
     */
    void sltUpdateFrequency(uint uiFrequency);

    /*!
     * @brief   Method to notify Tuner adaptor regarding update of tuner current band.
     * @param   iBand: uint
     * @return  void.
     */
    void sltUpdateBand(int iBand);

    /*!
     * @brief   Method to notify Tuner adaptor regarding update of manual seek status.
     * @param   void
     * @return  void.
     */
    void sltManualSeekStatus();

    /*!
     * @brief   Method to notify Tuner adaptor regarding update of tuner station name.
     * @param   objStrStationName : station name
     * @return  void.
     */
    void sltUpdateStationName(const string &objStrStationName);

    /**
     * @brief sltUpdatePresetList - Slot for preset list update signal
     * @param void
     * @return void
     */
    void sltUpdatePresetList();

    /**
     * @brief sltActivePresetResponseReceived - Slot for active preset response received update
     * @param void
     * @return void
     */
    void sltActivePresetResponseReceived();

    /**
     * @brief sltUpdateFieldStrength - Slot for field strength update signal
     * @param int -iFieldStrength: variable to store signal strength
     * @return void
     */
    void sltUpdateFieldStrength(int iFieldStrength);

    /**
     * @brief sltValidStationFoundUpdated - Slot for Valid Station Found Update signal
     * @param bool - bStatus : variable to store empty status, true when empty
     * @return void
     */
    void sltValidStationFoundUpdated(bool bStatus);

    /**
     * @brief sltTagIdUpdated - Slot for tag id update signal
     * @param uint - uiTagId
     * @return void
     */
    void sltTagIdUpdated(uint uiTagId);

    /**
     * @brief sltUpdateMultipath - Slot for multipath update signal
     * @param unsigned char ucMultipath: variable to store multipath value
     * @return void
     */
    void sltUpdateMultipath(unsigned char ucMultipath);
    /**
     * @brief sltIntrospectionProxyAvailable - Slot to update quality monitor status
     * @param void.
     * @return void
     */
    void sltIntrospectionProxyAvailable();

    /**
     * @brief sltUpdateTunerStatus - Slot for tuner availability status
     * @param bool bIsTunerAvailable: tuner proxy availability status
     * @return void
     */
    void sltUpdateTunerStatus(bool bIsTunerAvailable);

private:
    void connectSignals();
};

#endif // CTunerEventHandler_H

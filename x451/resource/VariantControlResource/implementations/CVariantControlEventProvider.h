/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CVariantControlEventProvider.h
 * @ingroup       HMIComponent
 * @author        Manali Patil
 * CVariantControlEventProvider, Class to send signals to VariantControl Application layer on VariantControl Resource events
 */

#ifndef CVARIANTCONTROLEVENTPROVIDER_H
#define CVARIANTCONTROLEVENTPROVIDER_H

#include <QObject>

/**
 * @brief The CVariantControlEventProvider class send signals to VariantControl Application layer on VariantControl Resource events
 */
class CVariantControlEventProvider: public QObject
{
    Q_OBJECT

public:
    /**
    * @brief	CVariantControlEventProvider: Constructor
    * @param	pParent* : parent pointer.
    * @return	void
    */
    CVariantControlEventProvider(QObject* pParent = 0);

    /**
    * @brief	~CVariantControlEventProvider: Destructor
    * @param	void
    * @return	void.
    */
    ~CVariantControlEventProvider();

signals:

    /**
     * @brief sigAntennaTypeReceived: Signal to notify Am/Fm Antenna type has been updated
     * @param iAntennaType: Antenna type whether AM/FM.
     * @return void
     */
    void sigAntennaTypeReceived(int iAntennaType);

    /**
     * @brief sigEolAndroidAutoChanged: Signal to notify EOL for AndroidAuto has been updated
     * @param  bEolAndroidAutoStatus: enabled status of Android Auto.
     * @return void
     */
    void sigEolAndroidAutoChanged(bool bEolAndroidAutoStatus);

    /**
     * @brief sigEolAppleCarPlayChanged: Signal to notify EOL for AppleCarPlay has been updated
     * @param bEolAppleCarPlayStatus: enabled status of Apple carplay.
     * @return void
     */
    void sigEolAppleCarPlayChanged(bool bEolAppleCarPlayStatus);

    /**
     * @brief sigEolDriveModeStatusDataChanged: Signal to notify EOL for drive mode status data updated
     * @param  iEolDriveModeStatusStatus: drive mode status data.
     * @return void
     */
    void sigEolDriveModeStatusDataChanged(int iEolDriveModeStatusStatus);

    /**
     * @brief sigEolICCastStatusChanged: Signal to notify EOL for IC cast enabled status has been updated
     * @param  iEolICCastEnabledStatus: enabled status of IC cast.
     * @return void
     */
    void sigEolICCastStatusChanged(int iEolICCastEnabledStatus);

    /**
     * @brief sigSensorCountChanged: Signal to notify the change in the PDC sensor count
     * @param iSensorCount: No of PDC sensors.
     * @return void.
     */
    void sigEOLSensorCountChanged(int iSensorCount);

    /**
     * @brief sigEOLVIP_DIDChanged: Signal to notify the change in the VIP DID
     * @param iVIP_DID, vehicle infotaiment platform information
     * @return void.
     */
    void sigEOLVIP_DIDChanged(int iVIP_DID);

    /**
     * @brief sigEOLAppsDIDChanged: Signal to notify the change in the Apps DID
     * @param iAppsDID, Apps / features disable enable information
     * @return void.
     */
    void sigEOLAppsDIDChanged(int iAppsDID);

public:

    /**
    * @brief	antennaTypeStatusReceived: This method will inform variant control event handler, that Am/Fm antenna type is received.
    * @param	iAntennaTypeStatus : Antenna Type status whether it is AM/FM.
    * @return	void.
    */
    void antennaTypeStatusReceived(int iAntennaTypeStatus);

    /*!
     * @brief   eolAndroidAutoStatusReceived: Method to inform HMI abdout EOL change for AndroidAuto.
     * @param   bEolAndroidAutoStatus: enabled satus of Android Auto.
     * @return  void.
     */
    void eolAndroidAutoStatusReceived(bool bEolAndroidAutoStatus);

    /*!
     * @brief   eolAppleCarPlayStatusReceived: Method to inform HMI abdout EOL change for AppleCarPlay.
     * @param   bEolAppleCarPlayStatus: enabled status of Apple carplay.
     * @return  void.
     */
    void eolAppleCarPlayStatusReceived(bool bEolAppleCarPlayStatus);

    /*!
     * @brief   eolDriveModeStatusReceived: Method to inform HMI abdout EOL change for drive mode status data.
     * @param   iEolDriveModeStatus: drive mode status data.
     * @return  void.
     */
    void eolDriveModeStatusReceived(int iEolDriveModeStatus);

    /*!
     * @brief   eolDriveModeStatusReceived: Method to inform HMI about EOL change for IC cast enabled status.
     * @param   iEolICCastEnabledStatus: IC cast enabled status data.
     * @return  void.
     */
    void eolICCastEnabledStatusReceived(int iEolICCastEnabledStatus);

    /**
     * @brief eolSensorCountReceived: Method to inform application layer about sensor count update.
     * @param iSensorCount: Sensor count data.
     * @return void
     */
    void eolSensorCountReceived(int iSensorCount);

    /**
     * @brief eolVIP_DIDReceived: Method to inform application layer about VIP DID update
     * @param iVIP_DID, vehicle infotaiment platform information
     * @return void
     */
    void eolVIP_DIDReceived(int iVIP_DID);

    /**
     * @brief eolAppsDIDReceived: Method to inform application layer about Apps DID update
     * @param iAppsDID, Apps / features disable enable information
     * @return void
     */
    void eolAppsDIDReceived(int iAppsDID);

};

#endif // CVARIANTCONTROLEVENTPROVIDER_H

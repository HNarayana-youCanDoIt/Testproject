/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CVariantControlAdaptor.h
 * @ingroup         HMIComponent
 * @author          Manali Patil
 * CVariantControlAdaptor, an Adaptor for VariantControl module,
 * CVariantControlAdaptor used to communicate between QML and Resource Layer.
 */

#ifndef CVARIANTCONTROLADAPTOR_H
#define CVARIANTCONTROLADAPTOR_H

#include <QObject>
#include "CVariantControlEnum.h"

class IVariantControlResource;

/**
 * @brief The CVariantControlAdaptor class: This singleton class contains methods to handle VariantControl related functionality
 */
class CVariantControlAdaptor : public QObject
{
    Q_OBJECT

    /**
     * @brief FIRST_BIT constant to read the IC cast data's first bit.
     */
    const int FIRST_BIT;

    //Properties
    /* To get AmFm antenna type information */
    Q_PROPERTY(CVariantControlEnum::EAntennaType antennaType READ antennaType NOTIFY sigAntennaTypeChanged)

    /* To get Android Auto Enabled information */
    Q_PROPERTY(bool eolAndroidAutoEnabled READ eolAndroidAutoEnabled NOTIFY sigEOLAndroidAutoEnabledChanged)

    /* To get Apple Carplay Enabled information */
    Q_PROPERTY(bool eolAppleCarPlayEnabled READ eolAppleCarPlayEnabled NOTIFY sigEOLAppleCarPlayEnabledChanged)

    /* To get IC Cast enabled status */
    Q_PROPERTY(bool eolICCastEnabledStatus READ eolICCastEnabledStatus NOTIFY sigEOLICCastEnabledStatusChanged)

    /* To get VIP DID value */
    Q_PROPERTY(CVariantControlEnum::EVIP_DID eolVIP_DID READ eolVIP_DID NOTIFY sigEOLVIP_DIDChanged)

    /* To get DriveNext enabled by eol value */
    Q_PROPERTY(bool eolDriveNextEnabled READ eolDriveNextEnabled NOTIFY sigEOLDriveNextEnabledChanged)

    /* To get HMI Doodle enabled by eol value */
    Q_PROPERTY(bool eolHMIDoodleEnabled READ eolHMIDoodleEnabled NOTIFY sigEOLHMIDoodleEnabledChanged)

    /* To get W3W enabled by eol value */
    Q_PROPERTY(bool eolW3WEnabled READ eolW3WEnabled NOTIFY sigEOLW3WEnabledChanged)

public:
    /**
    * @brief	This function get the instance of adaptor class.
    * @param	void
    * @return   pointer to CVariantControlAdaptor
    */
    static CVariantControlAdaptor* getInstance();

    /**
    * @brief	~CVariantControlAdaptor: Destructor
    * @param	void.
    * @return   void.
    */
    ~CVariantControlAdaptor();

    /**
     * @brief Method to get the value of m_eAntennaType
     * @param void.
     * @return m_eAntennaType - Value of antenna type
     */
    CVariantControlEnum::EAntennaType antennaType() { return m_eAntennaType; }

    /**
     * @brief eolAndroidAutoEnabled: Method to get the value of m_bEOLAndroidAutoEnabled
     * @param void.
     * @return m_bEOLAndroidAutoEnabled - Value of android auto enabled status.
     */
    bool eolAndroidAutoEnabled() { return m_bEOLAndroidAutoEnabled; }

    /**
     * @brief eolAppleCarPlayEnabled: Method to get the value of m_bEOLAppleCarplayEnabled
     * @param void.
     * @return m_bEOLAppleCarplayEnabled - Value of apple car play enabled status.
     */
    bool eolAppleCarPlayEnabled() { return m_bEOLAppleCarplayEnabled; }

    /**
     * @brief eolDriveModeStatusData: Method to get the value of m_iEOLDriveModeStatusData
     * @param void.
     * @return m_iEOLDriveModeStatusData - Value of Drive mode status data.
     */
    int eolDriveModeStatusData() { return m_iEOLDriveModeStatusData; }

    /**
     * @brief eolICCastEnabledStatus: Method to get the value of m_iEOLICCastEnabledStatus
     * @param void.
     * @return m_iEOLICCastEnabledStatus - Value of IC cast enabled status.
     */
    bool eolICCastEnabledStatus() { return m_bEOLICCastEnabledStatus; }

    /**
     * @brief eolVIP_DID: Method to get the value of VIP DID
     * @param void.
     * @return m_eEOLVIP_DID - Value of vechile infotainment platform DID
     */
    CVariantControlEnum::EVIP_DID eolVIP_DID() { return m_eVIP_DID; }

    /**
     * @brief eolAppsDID: Method to get the value of Apps DID
     * @param void.
     * @return m_iAppsDID - Value of Apps / features disable enable information
     */
    int eolAppsDID() { return m_iAppsDID; }

    /**
     * @brief eolDriveNextEnabled: Method to get whether drive next has been enabled by EOL
     * @param void.
     * @return m_bIsDriveNextEnabled - Value of drive next feature disable enable information
     */
    bool eolDriveNextEnabled() { return m_bIsDriveNextEnabled; }

    /**
     * @brief eolHMIDoodleEnabled: Method to get whether HMI doodle has been enabled by EOL
     * @param void.
     * @return m_bIsHMIDoodleEnabled - Value of HMI doodle feature disable enable information
     */
    bool eolHMIDoodleEnabled() { return m_bIsHMIDoodleEnabled; }

    /**
     * @brief eolW3WEnabled: Method to get whether W3W has been enabled by EOL
     * @param void.
     * @return m_bIsW3WEnabled - Value of W3W feature disable enable information
     */
    bool eolW3WEnabled() { return m_bIsW3WEnabled; }

    /**
     * @brief setAntennaType: Method to set the AmFm antenna connection type
     * @param eAntennaType- Value of Antenna Type from variant control service
     * @return void
     */
    void setAntennaType(CVariantControlEnum::EAntennaType eAntennaType);

    /**
     * @brief setEOLAndroidAutoEnabled: Method to set the EOL AndroidAuto Enable state
     * @param bEolAndroidAutoStatus: contains status of Android Auto.
     * @return void
     */
    void setEOLAndroidAutoEnabled(bool bEolAndroidAutoStatus);

    /**
     * @brief setEOLAppleCarPlayEnabled: Method to set the EOL AppleCarPlay Enable state
     * @param bEolAppleCarPlayStatus: contains status of Apple carplay.
     * @return void
     */
    void setEOLAppleCarPlayEnabled(bool bEolAppleCarPlayStatus);

    /**
     * @brief setEOLDriveModeStatus: Method to set the EOL drive mode status data
     * @param iEolDriveModeStatus: contains drive mode status data.
     * @return void
     */
    void setEOLDriveModeStatus(int iEolDriveModeStatus);

    /**
     * @brief setEOLICCastEnabledStatus: Method to set the EOL IC cast Enable status
     * @param iICCastEnabledStatus: contains status of IC cast.
     * @return void
     */
    void setEOLICCastEnabledStatus(int iICCastEnabledStatus);

    /**
     * @brief setEOLVIP_DID: Method to set the EOL VIP DID value
     * @param iVIP_DID: contains value of the vehicle infotainment platform
     * @return void
     */
    void setEOLVIP_DID(int iVIP_DID);

    /**
     * @brief setEOLVIP_DID: Method to set the EOL Apps DID value
     * @param iAppsDID: Apps / features disable enable information
     * @return void
     */
    void setEOLAppsDID(int iAppsDID);

    /**
     * @brief getESensorCount: To get the sonsor count.
     * @param void
     * @return sensor count.
     */
    CVariantControlEnum::EPDCSensorCount  getESensorCount() const;

    /**
     * @brief setESensorCount: To set the no of sensors in vehicle.
     * @param iSensorCount: sensor count
     * @return void
     */
    void setESensorCount(int iSensorCount);

signals:

    /**
    * @brief	sigAntennaTypeChanged: This signal will emit antenna type information
    * @param	void
    * @return	void
    */
    void sigAntennaTypeChanged();

    /**
    * @brief	sigEOLAndroidAutoEnabledChanged: This signal will emit when EOL AndroidAuto Enable Changes
    * @param	void
    * @return	void
    */
    void sigEOLAndroidAutoEnabledChanged();

    /**
    * @brief	sigEOLAppleCarPlayEnabledChanged: This signal will emit when EOL AppleCarPlay Enable Changes
    * @param	void
    * @return	void
    */
    void sigEOLAppleCarPlayEnabledChanged();

    /**
    * @brief	sigEOLDriveModeStatusChanged: This signal will emit when EOL drive mode status data Changes
    * @param	void
    * @return	void
    */
    void sigEOLDriveModeStatusChanged();

    /**
    * @brief	sigICCastEnabledStatusChanged: This signal will emit when EOL IC cast enabled Changes
    * @param	void
    * @return	void
    */
    void sigEOLICCastEnabledStatusChanged();

    /**
     * @brief sigEOLSensorCountChanged: Signal to indicate the changes in sensor count.
     * @param void
     * @return void
     */
    void sigEOLSensorCountChanged();

    /**
     * @brief sigEOLVIP_DIDChanged: Signal to indicate the changes in VIP DID
     * @param void
     * @return void
     */
    void sigEOLVIP_DIDChanged();

    /**
     * @brief sigEOLDriveNextEnabledChanged: Signal to indicate the changes in drive next app feature enable value
     * @param void
     * @return void
     */
    void sigEOLDriveNextEnabledChanged();

    /**
     * @brief sigEOLHMIDoodleEnabledChanged: Signal to indicate the changes in HMI doodle app feature enable value
     * @param void
     * @return void
     */
    void sigEOLHMIDoodleEnabledChanged();

    /**
     * @brief sigEOLW3WEnabledChanged: Signal to indicate the changes in W3W app feature enable value
     * @param void
     * @return void
     */
    void sigEOLW3WEnabledChanged();

private:
    /**
    * @brief	Constructor
    * @param	QObject *parent : Parent class instance
    * @return   None
    */
    explicit CVariantControlAdaptor(QObject *pParent = nullptr);

    /**
     * @brief m_pVariantControlAdaptor: Static pointer for CVariantControlAdaptor instance
     */
    static CVariantControlAdaptor* m_pVariantControlAdaptor;

    /**
     * @brief m_eAntennaType: This variable holds the AmFm antenna type details
     */
    CVariantControlEnum::EAntennaType m_eAntennaType;

    /**
     * @brief m_bEOLAndroidAutoEnabled: This variable holds the EOL Android auto Enabled Status
     */
    bool m_bEOLAndroidAutoEnabled;

    /**
     * @brief m_bEOLAppleCarplayEnabled: This variable holds the EOL Apply carplay Enabled Status
     */
    bool m_bEOLAppleCarplayEnabled;

    /**
     * @brief m_iEOLDriveModeStatusData: used to maintain EOL value for drive mode status data
     */
    int m_iEOLDriveModeStatusData;

    /**
     * @brief m_iEOLICCastEnabledStatus: used to maintain EOL value for IC cast enabled status
     */
    bool m_bEOLICCastEnabledStatus;

    /**
     * @brief m_eSensorCount: No. of PDC sensors available in the vehicle.
     */
    CVariantControlEnum::EPDCSensorCount m_eSensorCount;

    /**
     * @brief m_eVIP_DID: vehicle infotainment platform value
     */
    CVariantControlEnum::EVIP_DID m_eVIP_DID;

    /**
     * @brief m_iAppsDID: Apps / features disable enable information
     */
    short m_iAppsDID;

    /**
     * @brief Apps Enable Disable - DriveNext
     */
    bool m_bIsDriveNextEnabled;

    /**
     * @brief Apps Enable Disable - HMI Doodle
     */
    bool m_bIsHMIDoodleEnabled;

    /**
     * @brief Apps Enable Disable - W3W
     */
    bool m_bIsW3WEnabled;

};

#endif // CVARIANTCONTROLADAPTOR_H

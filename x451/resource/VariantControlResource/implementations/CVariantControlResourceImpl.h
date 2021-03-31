/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVariantControlResourceImpl.h
* @ingroup      HMIComponent
* @author       Manali Patil
* CVariantControlResourceImpl, Resource Implementation for VariantControl
*/
#ifndef CVARIANTCONTROLRESOURCEIMPL_H
#define CVARIANTCONTROLRESOURCEIMPL_H

#include "resource/VariantControlResource/interfaces/IVariantControlResource.h"

class CVariantControlEventProvider;

/**
 * @brief The CVariantControlResourceImpl class is Resource Implementation for VariantControl
 */
class CVariantControlResourceImpl: public IVariantControlResource
{
public:

    /**
    * @brief	~CVariantControlResourceImpl: Destructor.
    * @param	void.
    * @return	void.
    */
    virtual ~CVariantControlResourceImpl();

    /**
    * @brief	getVariantControlEventProvider: This function returns the pointer of CVariantControlEventProvider class.
    * @param    void.
    * @return	CVariantControlEventProvider* : Pointer to CVariantControlEventProvider instance.
    */
    CVariantControlEventProvider* getVariantControlEventProvider();

    /**
    * @brief	CVariantControlResourceImpl: Constructor
    * @param	void.
    * @return	void.
    */
    CVariantControlResourceImpl();

    /**
    * @brief	readEolParameters: request to read EOL Parameters.
    * @param	void.
    * @return	void.
    */
    void readEolParameters() override;

    /**
    * @brief	getEOLAntennaType: get current status for EOL Antenna Type
    * @param	void.
    * @return	m_iAntennaType: status of Antenna type.
    */
    int getEOLAntennaType() override { return m_iAntennaType; }

    /**
    * @brief	getEOLAndroidAutoEnabled: get current status for EOL AndroidAuto
    * @param	void.
    * @return	m_bAndroidAutoEnabled: enabled status of Android Auto.
    */
    bool getEOLAndroidAutoEnabled() override { return m_bAndroidAutoEnabled; }

    /**
    * @brief	getEOLAppleCarPlayEnabled: get current status for EOL AppleCarPlay.
    * @param	void.
    * @return	m_bAppleCarPlayEnabled: enabled status of Apple carplay.
    */
    bool getEOLAppleCarPlayEnabled() override { return m_bAppleCarPlayEnabled; }

    /**
    * @brief	getEOLDriveModeStatusData: get current drive mode status data.
    * @param	void.
    * @return	m_iDriveModeStatusData: drive mode status data.
    */
    int getEOLDriveModeStatusData() override { return m_iDriveModeStatusData; }

    /**
    * @brief	getEOLICCastEnabledStatus: get current IC cast enabled status.
    * @param	void.
    * @return	m_iICCastEnabledStatus: enabled status of IC cast.
    */
    int getEOLICCastEnabledStatus() override { return m_iICCastEnabledStatus; }

    /**
    * @brief getEOLSensorCount: Get the no of PDC sensors available in the system
     * @param void
     * @return no of sensors
     */
    int getEOLSensorCount() override;

    /**
    * @brief	getEOL_VIP_DID: get the VIP (Vehicle infotainment platform information from EOL
    * @param	void.
    * @return	int : VIP DID received from EOL
    */
    int getEOL_VIP_DID() override { return m_iVIP_DID; }

    /**
    * @brief	getEOLAppsDID: get the Apps / features enable disable information from EOL
    * @param	void.
    * @return	int : Apps DID received from EOL
    */
    int getEOLAppsDID() override { return m_iAppsDID; }
	
private:

    /**
     * @brief validateVIP_DID: To validate if the received value is handled else return a predefined default value
     * @param iDID
     * @return VIP DID value
     */
    int validateVIP_DID(int iDID);

private:

    friend class ResourceFactory;

    /**
     * @brief m_pVariantControlEventProvider: Instance of the CVariantControlEventProvider to emit signals to the upper layer
     */
    CVariantControlEventProvider* m_pVariantControlEventProvider;

    /**
     * @brief m_iAntennaType: variable for connected AmFm antenna type
     */
    int m_iAntennaType;

    /**
     * @brief m_bAndroidAutoEnabled: used to maintain EOL value for AndroidAuto
     */
    bool m_bAndroidAutoEnabled;

    /**
     * @brief m_bAppleCarPlayEnabled: used to maintain EOL value for AppleCarPlay
     */
    bool m_bAppleCarPlayEnabled;

    /**
     * @brief m_iDriveModeStatusData: used to maintain EOL value for drive mode status data
     */
    int m_iDriveModeStatusData;

    /**
     * @brief m_iICCastEnabledStatus: used to maintain EOL value for IC cast enabled status
     */
    int m_iICCastEnabledStatus;

    /**
     * @brief m_iSensorCount: used to maintain EOL value for No of sensors
     */
    int m_iSensorCount;

    /**
     * @brief m_iVIP_DID: used to maintain EOL value for VIP (Vechicle Infotainment Platform) DID
     */
    int m_iVIP_DID;

    /**
     * @brief m_iAppsDID: used to maintain EOL value for Apps / features that have been enabled/disabled
     */
    int m_iAppsDID;
};

#endif //CVARIANTCONTROLRESOURCEIMPL_H


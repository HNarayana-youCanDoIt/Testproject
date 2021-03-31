/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         IVariantControlResource.h
* @ingroup      HMIComponent
* @author       Manali Patil
* IVariantControlResource, an interface for VariantControl Resource Implementaion in HMI
*/

#ifndef IVARIANTCONTROLRESOURCE_H
#define IVARIANTCONTROLRESOURCE_H

#include <string>
#include <capi/CAPIClientAbstraction.hpp>


using namespace std;


/**
*   @brief The IVariantControlResource class
*   This interfaces provides functionality of EOL reading.(DID reading)
*/
class IVariantControlResource
{
public:
    virtual ~IVariantControlResource(){}

    /*****  Request METHODS  ****************************/

    /**
     * @brief readEolParameters: request to read EOL Parameters.
     * @param void.
     * @return void.
     */
    virtual void readEolParameters() = 0;

    /**
    * @brief	getEOLAntennaType: get current status for EOL Antenna Type
    * @param	void.
    * @return	Antenna type status.
    */
    virtual int getEOLAntennaType() = 0;

    /**
    * @brief	getEOLAndroidAutoEnabled: get current status for EOL AndroidAuto
    * @param	void.
    * @return	enabled status of Android auto from EOL.
    */
    virtual bool getEOLAndroidAutoEnabled() = 0;

    /**
    * @brief	getEOLAppleCarPlayEnabled: get current status for EOL AppleCarPlay.
    * @param	void.
    * @return	enabled status of Apple Carplay from EOL.
    */
    virtual bool getEOLAppleCarPlayEnabled() = 0;

    /**
    * @brief	getEOLDriveModeStatusData: get current drive mode status data.
    * @param	void.
    * @return	int : drive mode status data.
    */
    virtual int getEOLDriveModeStatusData() = 0;

    /**
    * @brief	getEOLICCastEnabledStatus: get IC cast enabled status.
    * @param	void.
    * @return	int : IC cast enabled status.
    */
    virtual int getEOLICCastEnabledStatus() = 0;

    /**
    * @brief	getEOLSensorCount: get the PDC sensor count information read from EOL
    * @param	void.
    * @return	int : sensor count
    */
    virtual int getEOLSensorCount() = 0;

    /**
    * @brief	getEOL_VIP_DID: get the VIP (Vehicle infotainment platform) information from EOL
    * @param	void.
    * @return	int : VIP DID received from EOL
    */
    virtual int getEOL_VIP_DID() = 0;

    /**
    * @brief	getEOLAppsDID: get the Apps / features enable disable information from EOL
    * @param	void.
    * @return	int : Apps DID received from EOL
    */
    virtual int getEOLAppsDID() = 0;

    //    /*****  CALL BACK METHODS  ****************************/


};

#endif // IVARIANTCONTROLRESOURCE_H

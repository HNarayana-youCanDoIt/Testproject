/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDriveNextModerator.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* @brief        CDriveNextModerator Static Class to contain all validation and conversion methods for DriveNext.
*/

#ifndef CDRIVENEXTMODERATOR_H
#define CDRIVENEXTMODERATOR_H


#include <capi/CAPIClientAbstraction.hpp>
#include "v0/com/harman/drivepro/drivepropresProxy.hpp"
#include "CDriveNextResourceData.h"

using namespace v0::com::harman::drivepro;

/**
* @brief    Static class CDriveNextModerator.
* @param    gives validation and conversion methods for DriveNext.
*/
class CDriveNextModerator
{
private:
    /**
    * @brief    constructor for CDriveNextModerator.
    * @param    private constructor to avoide object creation.
    * @return   NA.
    */
    CDriveNextModerator();

public:
    /**
    * @brief    validateDNProxyEnumValue: This function validate all Dn Proxy signal enum values with HMI enum values
    * @param    void.
    * @return   bool. true when all DN proxy enum values match with HMI enum values
    */
    static bool validateDNProxyEnumValue();

    /**
    * @brief    convertToDNProxySignalEnumValue: This convert HMI Signal Enum value to Proxy Signal Enum Value
    * @param    EDriveNextSignalTypes eHmiValue signal type value in HMI enum.
    * @return   driveProTypeCollection::eSignalNames::Literal signal type value in Proxy enum.
    */
    static driveProTypeCollection::eSignalNames::Literal convertToDNProxySignalEnumValue(EDriveNextSignalTypes eHmiValue);

    /**
    * @brief    convertToDNHmiSignalEnumValue: This convert Proxy Signal Enum value to HMI Signal Enum Value
    * @param    driveProTypeCollection::eSignalNames::Literal eProxyValue signal type value in Proxy enum.
    * @return   EDriveNextSignalTypes signal type value in HMI enum.
    */
    static EDriveNextSignalTypes convertToDNHmiSignalEnumValue(driveProTypeCollection::eSignalNames::Literal eProxyValue);

    /**
    * @brief    convertDriveNextTripType: This function is to convert service trip type to HMI trip type.
    * @param    eTripType: trip type recieved from DriveNext service.
    * @return   EDriveNextTripType: converted trip type.
    */
    static EDriveNextTripType convertDriveNextTripType(driveProTypeCollection::eTripType eTripType);

    /**
    * @brief    convertDriveNextProxyTripType: This function is to convert HMI trip type to service trip type.
    * @param    EDriveNextTripType type recieved from HMI.
    * @param    driveProTypeCollection::eTripType ref to return converted value.
    * @return   bool conversion success status
    */
    static bool convertDriveNextProxyTripType(EDriveNextTripType eTripType, driveProTypeCollection::eTripType &eProxyTripType);

    /**
    * @brief    convertDriveNextLogLevel: This function is to convert service log level to HMI log level.
    * @param    uint32_t: log level recieved from DriveNext service.
    * @return   EDriveNextLogLevel: converted log level.
    */
    static EDriveNextLogLevel convertDriveNextLogLevel(uint32_t uiLogLevel);

    /**
    * @brief    convertDriveNextProxyLogLevel: This function is to convert HMI log level to service log level.
    * @param    EDriveNextLogLevel log level recieved from HMI.
    * @param    uint32_t ref to return converted value.
    * @return   bool conversion success status
    */
    static bool convertDriveNextProxyLogLevel(EDriveNextLogLevel eDriveNextLogLevel, uint32_t &uiLogLevel);

    /**
    * @brief    convertDriveNextLoggingType: This function is to convert service logging type to HMI logging type.
    * @param    driveProTypeCollection::eLoggingType: logging type recieved from DriveNext service.
    * @return   EDriveNextLoggingType: converted logging type.
    */
    static EDriveNextLoggingType convertDriveNextLoggingType(driveProTypeCollection::eLoggingType eLoggingType);

    /**
    * @brief    convertDriveNextProxyLoggingType: This function is to convert HMI logging type to service logging type.
    * @param    EDriveNextLoggingType logging type recieved from HMI.
    * @param    driveProTypeCollection::eLoggingType ref to return converted value.
    * @return   bool conversion success status
    */
    static bool convertDriveNextProxyLoggingType(EDriveNextLoggingType eLoggingType, driveProTypeCollection::eLoggingType &eProxtLoggingType);

    /**
    * @brief    convertDriveNextDistUnitType: This function is to convert service distance unit type to HMI distance unit type.
    * @param    driveProTypeCollection::eDistUnit: distance unit type recieved from DriveNext service.
    * @return   EDriveNextDistanceUnitType: converted distance unit type.
    */
    static EDriveNextDistanceUnitType convertDriveNextDistUnitType(driveProTypeCollection::eDistUnit eProxtDistUnitType);

    /**
    * @brief    convertDriveNextProxyDistUnitType: This function is to convert HMI distance unit type to service distance unit type.
    * @param    EDriveNextDistanceUnitType distance unit type recieved from HMI.
    * @param    driveProTypeCollection::eDistUnit ref to return converted value.
    * @return   bool conversion success status
    */
    static bool convertDriveNextProxyDistUnitType(EDriveNextDistanceUnitType eDistUnitType, driveProTypeCollection::eDistUnit &eProxtDistUnitType);

    /**
    * @brief    convertDriveNextFuelUnitType: This function is to convert service fuel unit type to HMI fuel unit type.
    * @param    driveProTypeCollection::eFuelUnit: fuel unit type recieved from DriveNext service.
    * @return   EDriveNextFuelUnitType: converted fuel unit type.
    */
    static EDriveNextFuelUnitType convertDriveNextFuelUnitType(driveProTypeCollection::eFuelUnit eProxtFuelUnitType);

    /**
    * @brief    convertDriveNextProxyFuelUnitType: This function is to convert HMI fuel unit type to service fuel unit type.
    * @param    EDriveNextFuelUnitType fuel unit type recieved from HMI.
    * @param    driveProTypeCollection::eFuelUnit ref to return converted value.
    * @return   bool conversion success status
    */
    static bool convertDriveNextProxyFuelUnitType(EDriveNextFuelUnitType eFuelUnitType, driveProTypeCollection::eFuelUnit &eProxtFuelUnitType);

    /**
    * @brief    convertDriveNextSignalErrorType: This function is to convert service signal error type to HMI signal error type.
    * @param    driveProTypeCollection::eDpErrorCode: signal error type recieved from DriveNext service.
    * @return   EDriveNextSignalErrorTypes: converted signal error type.
    */
    static EDriveNextSignalErrorTypes convertDriveNextSignalErrorType(driveProTypeCollection::eDpErrorCode eProxySignalErrorType);

    /**
    * @brief    convertDriveNextProxySignalErrorType: This function is to convert HMI signal error type to service signal error type.
    * @param    EDriveNextSignalErrorTypes: signal error type recieved from HMI.
    * @param    driveProTypeCollection::eDpErrorCode: proxy signal error type ref to return converted value.
    * @return   bool conversion success status
    */
    static bool convertDriveNextProxySignalErrorType(EDriveNextSignalErrorTypes eSignalErrorType, driveProTypeCollection::eDpErrorCode &eProxySignalErrorType);

private:
    //variable to hold enum validation result status,
    static CallStatus sm_eProxyEnumValidationStatus;
};

#endif // CDRIVENEXTMODERATOR_H

/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDriveNextData.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextData.h, DriveNext module data header file, responsible for initializing different static models
 */

#ifndef CDRIVENEXTDATA_H
#define CDRIVENEXTDATA_H

#include <QString>
#include "logging.h"
#include "CDriveNextEnum.h"
#include "implementations/CDriveNextResourceData.h"

/**
 * @brief The SDriveNextTripData struct: Responsible for initializing DriveNext trips model
 */
struct SDriveNextTripData
{

    /// SDriveNextTripData: default constructor for structure SDriveNextTripData,
    /// used to init data with default values.
    SDriveNextTripData ();

    /// SDriveNextTripData: parameterized constructor for structure SDriveNextTripData,
    /// used to init data values.
    SDriveNextTripData (CDriveNextEnum::EDNTripType eTripType, QString strName, QString strLeftIcon, QString strMidIcon, QString strRightIcon);

    /// m_eTripType: DriveNext trip type gets stored in this var
    CDriveNextEnum::EDNTripType m_eTripType;

    /// m_strName: DriveNext trip name string gets stored in this var
    QString m_strName;

    /// m_strLeftIcon: DriveNext trip left image path gets stored in this var
    QString m_strLeftIcon;

    /// m_strMidIcon: DriveNext trip mid image path gets stored in this var
    QString m_strMidIcon;

    /// m_strRightIcon: DriveNext trip right image path gets stored in this var
    QString m_strRightIcon;
};

/**
 * @brief The SDriveNextSignalSubInformation: Responsible holding DriveNext signal data sub information
 */
struct SDriveNextSignalSubInformation
{
    /// SDriveNextSignalSubInformation: default constructor for structure SDriveNextSignalSubInformation,
    /// used to init data with default values.
    SDriveNextSignalSubInformation ();

    /// SDriveNextSignalSubInformation: parameterized constructor for structure SDriveNextSignalSubInformation,
    /// used to init data values.
    SDriveNextSignalSubInformation (QString strTitle, CDriveNextEnum::EDNSigFormatType eValueFormatType, CDriveNextEnum::EDNSigUnitType eUnitType, CDriveNextEnum::EDNSigStringType eStringType);

    /// m_strTitle: DriveNext signal title gets stored in this var
    QString m_strTitle;

    /// m_eDNValueFormatType: DriveNext signal format type gets stored in this var
    CDriveNextEnum::EDNSigFormatType m_eValueFormatType;

    /// m_eDNUnitType: DriveNext signal unit type gets stored in this var
    CDriveNextEnum::EDNSigUnitType m_eUnitType;

    /// m_eDNStringType: DriveNext signal string type gets stored in this var
    CDriveNextEnum::EDNSigStringType m_eStringType;
};

/**
 * @brief The SDriveNextSignalInformation: Responsible holding DriveNext signal data information
 */
struct SDriveNextSignalInformation
{
    /// SDriveNextSignalInformation: default constructor for structure SDriveNextSignalInformation,
    /// used to init data with default values.
    SDriveNextSignalInformation ();

    /// SDriveNextSignalInformation: parameterized constructor for structure SDriveNextSignalInformation,
    /// used to init data only with engg values.
    SDriveNextSignalInformation (EDriveNextSignalTypes eSignalType,
                                 QString strEnggTitle, CDriveNextEnum::EDNSigFormatType eEnggValueFormatType, CDriveNextEnum::EDNSigUnitType eEnggUnitType, CDriveNextEnum::EDNSigStringType eEnggStringType);

    /// SDriveNextSignalInformation: parameterized constructor for structure SDriveNextSignalInformation,
    /// used to init data with all values.
    SDriveNextSignalInformation (EDriveNextSignalTypes eSignalType,
                                 QString strEnggTitle, CDriveNextEnum::EDNSigFormatType eEnggValueFormatType, CDriveNextEnum::EDNSigUnitType eEnggUnitType, CDriveNextEnum::EDNSigStringType eEnggStringType,
                                 QString strDNTitle, CDriveNextEnum::EDNSigFormatType eDNValueFormatType, CDriveNextEnum::EDNSigUnitType eDNUnitType, CDriveNextEnum::EDNSigStringType eDNStringType);

    /// m_eSignalType: DriveNext signal type gets stored in this var
    EDriveNextSignalTypes m_eSignalType;

    /// m_EnggInfo: DriveNext Engg signal info gets stored in this object
    SDriveNextSignalSubInformation m_EnggInfo;

    /// m_DNInfo: DriveNext signal info gets stored in this object
    SDriveNextSignalSubInformation m_DNInfo;
};

#endif // CDRIVENEXTDATA_H

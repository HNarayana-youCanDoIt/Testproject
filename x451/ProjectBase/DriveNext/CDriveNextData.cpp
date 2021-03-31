/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDriveNextData.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextData.cpp, DriveNext module data class, responsible for initializing different data models
 */

#include "CDriveNextData.h"
#include "CDDriveNextSignalInformation.h"

SDriveNextSignalSubInformation::SDriveNextSignalSubInformation()
{
    m_strTitle          = "UNKNOWN";
    m_eValueFormatType  = CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_UNKNOWN;
    m_eUnitType         = CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN;
    m_eStringType       = CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN;
}

SDriveNextSignalSubInformation::SDriveNextSignalSubInformation(QString strTitle, CDriveNextEnum::EDNSigFormatType eValueFormatType, CDriveNextEnum::EDNSigUnitType eUnitType, CDriveNextEnum::EDNSigStringType eStringType)
{
    m_strTitle          = strTitle;
    m_eValueFormatType  = eValueFormatType;
    m_eUnitType         = eUnitType;
    m_eStringType       = eStringType;
}

SDriveNextSignalInformation::SDriveNextSignalInformation()
{
    m_eSignalType                   = EDriveNextSignalTypes::DRIVENEXT_SIG_UNKNOWN;

    m_EnggInfo.m_strTitle           = "UNKNOWN";
    m_EnggInfo.m_eValueFormatType   = CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_UNKNOWN;
    m_EnggInfo.m_eUnitType          = CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN;
    m_EnggInfo.m_eStringType        = CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN;

    m_DNInfo.m_strTitle             = QT_TR_NOOP("TEXT_DN_SIG_UNKNOWN");
    m_DNInfo.m_eValueFormatType     = CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_UNKNOWN;
    m_DNInfo.m_eUnitType            = CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN;
    m_DNInfo.m_eStringType          = CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN;
}

SDriveNextSignalInformation::SDriveNextSignalInformation(EDriveNextSignalTypes eSignalType, QString strEnggTitle, CDriveNextEnum::EDNSigFormatType eEnggValueFormatType, CDriveNextEnum::EDNSigUnitType eEnggUnitType, CDriveNextEnum::EDNSigStringType eEnggStringType)
{
    m_eSignalType                   = eSignalType;

    m_EnggInfo.m_strTitle           = strEnggTitle;
    m_EnggInfo.m_eValueFormatType   = eEnggValueFormatType;
    m_EnggInfo.m_eUnitType          = eEnggUnitType;
    m_EnggInfo.m_eStringType        = eEnggStringType;

    m_DNInfo.m_strTitle             = QT_TR_NOOP("TEXT_DN_SIG_UNKNOWN");
    m_DNInfo.m_eValueFormatType     = CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_UNKNOWN;
    m_DNInfo.m_eUnitType            = CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN;
    m_DNInfo.m_eStringType          = CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN;
}

SDriveNextSignalInformation::SDriveNextSignalInformation(EDriveNextSignalTypes eSignalType,
                                                         QString strEnggTitle, CDriveNextEnum::EDNSigFormatType eEnggValueFormatType, CDriveNextEnum::EDNSigUnitType eEnggUnitType, CDriveNextEnum::EDNSigStringType eEnggStringType,
                                                         QString strDNTitle, CDriveNextEnum::EDNSigFormatType eDNValueFormatType, CDriveNextEnum::EDNSigUnitType eDNUnitType, CDriveNextEnum::EDNSigStringType eDNStringType)
{
    m_eSignalType                   = eSignalType;

    m_EnggInfo.m_strTitle           = strEnggTitle;
    m_EnggInfo.m_eValueFormatType   = eEnggValueFormatType;
    m_EnggInfo.m_eUnitType          = eEnggUnitType;
    m_EnggInfo.m_eStringType        = eEnggStringType;

    m_DNInfo.m_strTitle             = strDNTitle;
    m_DNInfo.m_eValueFormatType     = eDNValueFormatType;
    m_DNInfo.m_eUnitType            = eDNUnitType;
    m_DNInfo.m_eStringType          = eDNStringType;
}


SDriveNextTripData::SDriveNextTripData ()
{
    m_eTripType     = CDriveNextEnum::EDNTripType::DRIVENEXT_TRIP_UNKNOWN;
    m_strName       = "";
    m_strLeftIcon   = "";
    m_strMidIcon    = "";
    m_strRightIcon  = "";
}

SDriveNextTripData::SDriveNextTripData (CDriveNextEnum::EDNTripType eTripType, QString strName, QString strLeftIcon, QString strMidIcon, QString strRightIcon)
{
    m_eTripType     = eTripType;
    m_strName       = strName;
    m_strLeftIcon   = strLeftIcon;
    m_strMidIcon    = strMidIcon;
    m_strRightIcon  = strRightIcon;
}

/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDDriveNextSignalInformation.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDDriveNextSignalInformation, static data class for DriveNext signal data element information.
 */

#include "CDDriveNextSignalInformation.h"
#include "logging.h"
#include "math.h"

const int CDDriveNextSignalInformation::TRIPS_COUNT = 6;
const int CDDriveNextSignalInformation::SCORE_RANGE = 5;
const int CDDriveNextSignalInformation::SIGNALS_PER_TRIP_COUNT = EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_FUELECOINSTRATING;

const int CDDriveNextSignalInformation::TRIP_SIGNAL_LIST[CDriveNextEnum::EDNTripElements::DN_TRIP_ELEMENT_TOTAL_COUNT] =
{
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OVERALLCUMURATING,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOCUMRATING,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DRIVECUMURATING,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SAFETYCUMRATING,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDIST,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGFUELECO,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDURATION,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_IDLETIME,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGSPEED,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOPSPEED,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMECORRECTGEARPER,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESNOPER,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MOSTTIMEGEAR,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PERTIMEWITHSEATBELT,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEHIGHSPEEDPER,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCHARSHCOUNT,
    EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HARSHBRK
};

/** Add signals data information here by signal type order
    contains TEXT,  Value Format type,  Unit Type,  Additional Text String Type **/
const SDriveNextSignalInformation CDDriveNextSignalInformation::SIGNALS_DATA_INFO[CDDriveNextSignalInformation::SIGNALS_PER_TRIP_COUNT] =
{
    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOINSTRATING, "FuelEcoInstRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_FUELECOCUMRATING, "FuelEcoCumRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_EFFICIENCY"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_ENGINEIDLE, "TotalTime",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_IDLETIME, "IdleTime",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_ENG_IDLE_TIME"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_HHHH_MM_SS,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_IDLETIMEPER, "IdleTimePer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALFUELIDLE, "TotalFuelIdle",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_MILI_LTR,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_RPMEFFINFO, "TotalTime",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDIST, "TotalDist",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEAMBER, "Eff_rpmTimeAmber",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEAMBERPER, "Eff_rpmTimeAmberPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEGREEN, "Eff_rpmTimeGreen",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEGREENPER, "Eff_rpmTimeGreenPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMERED, "Eff_rpmTimeRed",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMTIMEREDPER, "Eff_rpmTimeRedPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTAMBER, "Eff_rpmDistAmber",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTAMBERPER, "Eff_rpmDistAmberPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTGREEN, "Eff_rpmDistGreen",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTGREENPER, "Eff_rpmDistGreenPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTRED, "Eff_rpmDistRed",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_EFF_RPMDISTREDPER, "Eff_rpmDistRedPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGENG_RPM, "AvgEng_rpm",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_RPM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_ACON, "TotalTime",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AC_ONTIME, "AC_OnTime",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AC_ONTIMEPER, "AC_OnTimePer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIME_CLT_ACC, "TotalTime",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_CLT_ACCTIME, "Clt_accTime",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_CLT_ACCTIMEPER, "Clt_accTimePer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKINSTRATING, "BrkInstRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCLN, "Accln",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_MTR_PER_SEC_SQR,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFBRKCYCLE, "NoOfBrkCycle",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKCUMRATING, "BrkCumRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALBRK, "TotalBrk",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NORMALBRK, "NormalBrk",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NORMALBRKPER, "NormalBrkPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MODERATEBRK, "ModerateBrk",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MODERATEBRKPER, "ModerateBrkPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HEAVYBRK, "HeavyBrk",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HEAVYBRKPER, "HeavyBrkPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PANICBRK, "PanicBrk",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PANICBRKPER, "PanicBrkPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HARSHBRK, "HarshBrk",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_HARSH_BREAK"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_HARSHBRKPER, "HarshBrkPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGBRKCOUNT, "AvgBrkCount",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ODODISTPERTRIP_BRAKING, "OdoDistPerTrip",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCINSTRATING, "AccInstRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCCUMRATING, "AccCumRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTRAVELTIME, "TotalTravelTime",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALACCPEDALPRESSTIME, "TotalAccPedalPressTime",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE1, "AccPedalPressRange1",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE1PER, "AccPedalPressRange1Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE2, "AccPedalPressRange2",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE2PER, "AccPedalPressRange2Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE3, "AccPedalPressRange3",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE3PER, "AccPedalPressRange3Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE4, "AccPedalPressRange4",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSRANGE4PER, "AccPedalPressRange4Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESSNO, "AccPedalPressNo",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCPEDALPRESNOPER, "AccPedalPresNoPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_AVG_ACCEL_PEDAL_TRIVAL"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGACCPEDALPOS, "AvgAccPedalPos",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ACCHARSHCOUNT, "AccHarshCount",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_HARSH_ACCEL"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_VEHICLE_TXMNVARIANT, "Vehicle_TxmnVariant",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_GSINSTRATING, "GSInstRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_GSCUMRATING, "GSCumRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTVALIDGEAR_GEARSHIFT, "TotalDistValidGear",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEVALIDGEAR_GEARSHIFT, "TotalTimeValidGear",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR1, "TimeGear1",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR1, "DistGear1",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR1PER, "TimeGear1Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR1PER, "DistGear1Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR2, "TimeGear2",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR2, "DistGear2",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR2PER, "TimeGear2Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR2PER, "DistGear2Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR3, "TimeGear3",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR3, "DistGear3",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR3PER, "TimeGear3Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR3PER, "DistGear3Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR4, "TimeGear4",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR4, "DistGear4",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR4PER, "TimeGear4Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR4PER, "DistGear4Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR5, "TimeGear5",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR5, "DistGear5",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR5PER, "TimeGear5Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR5PER, "DistGear5Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR6, "TimeGear6",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR6, "DistGear6",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEGEAR6PER, "TimeGear6Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DISTGEAR6PER, "DistGear6Per",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_MOSTTIMEGEAR, "MostTimeGear",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_MOST_USED_GEAR"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_TEXT_VAL,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_GEAR),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTVALIDGEAR, "TotalDistValidGear",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTWRONGGEAR, "TotalDistWrongGear",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTDOWNINDI, "TotalDistDownIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTUPINDI, "TotalDistUpIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTWRONGINDI, "AvgDistWrongIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTDOWNINDI, "AvgDistDownIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGDISTUPINDI, "AvgDistUpIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTWRONGGEARPER, "TotalDistWrongGearPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTDOWNINDIPER, "TotalDistDownIndiPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALDISTUPINDIPER, "TotalDistUpIndiPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEVALIDGEAR, "TotalTimeValidGear",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEWRONGGEAR, "TotalTimeWrongGear",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEDOWNINDI, "TotalTimeDownIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEUPINDI, "TotalTimeUpIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEWRONGGEARPER, "TotalTimeWrongGearPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEDOWNINDIPER, "TotalTimeDownIndiPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEUPINDIPER, "TotalTimeUpIndiPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTWRONGGEAR, "TotalCountWrongGear",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTDOWNINDI, "TotalCountDownIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTUPINDI, "TotalCountUpIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTDOWNINDIPER, "TotalCountDownIndiPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALCOUNTUPINDIPER, "TotalCountUpIndiPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGCOUNTUPINDI, "AvgCountUpIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGCOUNTDOWNINDI, "AvgCountDownIndi",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMECORRECTGEARPER, "TotalTimeCorrectGearPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_PROPER_GEAR_UTIL"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGGEARSHIFT, "AvgGearShift",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFGEARSHIFT, "NoOfGearShift",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_HRS,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_ODODISTPERTRIP, "OdoDistPerTrip",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOPSPEED, "TopSpeed",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_HR,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_TOP_SPEED"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_HR,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DRIVEINSTRATING, "DriveInstRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DRIVECUMURATING, "DriveCumuRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_DRIVING"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND1TIME, "SpeedBand1Time",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND1TIMEPER, "SpeedBand1TimePer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND2TIME, "SpeedBand2Time",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND2TIMEPER, "SpeedBand2TimePer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND3TIME, "SpeedBand3Time",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND3TIMEPER, "SpeedBand3TimePer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND4TIME, "SpeedBand4Time",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SPEEDBAND4TIMEPER, "SpeedBand4TimePer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDIST, "TripDistCurrentTrip",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_DISTANCE_TRAVELLED"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),/*PLEASE NOTE: DRIVENEXT_SIG_XXXX_TRIPDIST engg menu title text is different as per trip types */

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDURATION, "TripDurationCurrentTrip",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SEC,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_TRIP_DURATION"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_HHHH_MM,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),/*PLEASE NOTE: DRIVENEXT_SIG_XXXX_TRIPDURATION engg menu title text is different as per trip types */

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGSPEED, "AvgSpeedCurrentTripxxx km",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_HR,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_AVG_SPEED"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_HR,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),/*PLEASE NOTE: DRIVENEXT_SIG_XXXX_AVGSPEED engg menu title text is different as per trip types */

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGFUELECO, "AvgFuelEcoCurrentTrip",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_LITRE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_FUEL_ECONOMY"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_KM_PER_LTR,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),/*PLEASE NOTE: DRIVENEXT_SIG_XXXX_AVGFUELECO engg menu title text is different as per trip types */

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OVERALLINSTRATING, "OverallInstRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OVERALLCUMURATING, "OverallCumuRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_OVERALL_SCORE"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PERTIMEWITHOUTSEATBELT, "PerTimeWithoutSeatbelt",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_PERTIMEWITHSEATBELT, "PerTimeWithSeatbelt",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_SEATBELT_UTIL"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SEATBELTFACTOR, "SeatBeltFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHOUTSEATBELT, "NoOfTimeWithoutSeatbelt",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHSEATBELT, "NoOfTimeWithSeatbelt",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_NOOFTIMEWITHOUTSEATBELTPER, "NoOfTimeWithoutSeatbeltPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DOORCLOSETIMEPER, "DoorCloseTimePer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_DOOROPENTIMEPER, "DoorOpenTimePer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TIMEHIGHSPEEDCLTBRKPRESSEDPER, "TimeHighSpeedCltBrkPressedPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TOTALTIMEHIGHSPEEDPER, "TotalTimeHighSpeedPer",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_OVER_SPEEDING"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_PERCENTAGE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SRSFACTOR, "SRSFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TEABREAKFACTOR, "TeaBreakFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRLFACTOR, "TRLFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TLLFACTOR, "TLLFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TBLFACTOR, "TBLFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TFLFACTOR, "TFLFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TPLFACTOR, "TPLFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRVLFACTOR, "TRvLFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_BRKFLDFACTOR, "BrkFldFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_OILPRFACTOR, "OilPrFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_WIFFACTOR, "WIFFactor",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_VEHICLEHEALTH, "VehicleHealth",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_UNKNOWN,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SAFETYINSTRATING, "SafetyInstRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN),

    SDriveNextSignalInformation(EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_SAFETYCUMRATING, "SafetyCumRating",
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN,
    QT_TR_NOOP("TEXT_DN_SAFETY"),
    CDriveNextEnum::EDNSigFormatType::DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
    CDriveNextEnum::EDNSigUnitType::DRIVENEXT_SIG_UNIT_SCORE,
    CDriveNextEnum::EDNSigStringType::DRIVENEXT_SIG_STR_UNKNOWN)
};

std::vector<SDriveNextSignalInformation> CDDriveNextSignalInformation::sm_vectSignalsInfo;

void CDDriveNextSignalInformation::initSignalsData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s", __FUNCTION__);

    for (int iTrip = 0; iTrip < TRIPS_COUNT; iTrip++)
    {
        for (int iSignal = 0; iSignal < SIGNALS_PER_TRIP_COUNT; iSignal++)
        {
            SDriveNextSignalInformation sInfo = SDriveNextSignalInformation(
                        static_cast<EDriveNextSignalTypes>(SIGNALS_DATA_INFO[iSignal].m_eSignalType + (SIGNALS_PER_TRIP_COUNT*iTrip)),
                        SIGNALS_DATA_INFO[iSignal].m_EnggInfo.m_strTitle,
                        SIGNALS_DATA_INFO[iSignal].m_EnggInfo.m_eValueFormatType,
                        SIGNALS_DATA_INFO[iSignal].m_EnggInfo.m_eUnitType,
                        SIGNALS_DATA_INFO[iSignal].m_EnggInfo.m_eStringType,
                        SIGNALS_DATA_INFO[iSignal].m_DNInfo.m_strTitle,
                        SIGNALS_DATA_INFO[iSignal].m_DNInfo.m_eValueFormatType,
                        SIGNALS_DATA_INFO[iSignal].m_DNInfo.m_eUnitType,
                        SIGNALS_DATA_INFO[iSignal].m_DNInfo.m_eStringType);

            sInfo.m_DNInfo.m_strTitle = tr(SIGNALS_DATA_INFO[iSignal].m_DNInfo.m_strTitle.toStdString().data());

            sm_vectSignalsInfo.push_back(sInfo);
        }
    }

    //As some signals have engg menu title text as per trip types, Updateing text here,
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDIST].m_EnggInfo.m_strTitle = "TripDistCurrentTrip";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRIPDIST].m_EnggInfo.m_strTitle = "TripDistTripA";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRIPDIST].m_EnggInfo.m_strTitle = "TripDistTripB";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRIPDIST].m_EnggInfo.m_strTitle = "TripDistTripOverallTrip";

    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_TRIPDURATION].m_EnggInfo.m_strTitle = "TripDurationCurrentTrip";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_TRIPDURATION].m_EnggInfo.m_strTitle = "TripDurationTripA";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_TRIPDURATION].m_EnggInfo.m_strTitle = "TripDurationTripB";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_TRIPDURATION].m_EnggInfo.m_strTitle = "TripDurationTripOverallTrip";

    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGSPEED].m_EnggInfo.m_strTitle = "AvgSpeedCurrentTripxxx km";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGSPEED].m_EnggInfo.m_strTitle = "AvgSpeedTripAxxx km";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGSPEED].m_EnggInfo.m_strTitle = "AvgSpeedTripBxxx km";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGSPEED].m_EnggInfo.m_strTitle = "AvgSpeedOverallTripxxx km";

    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_CURRENTTRIP_AVGFUELECO].m_EnggInfo.m_strTitle = "AvgFuelEcoCurrentTrip";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPA_AVGFUELECO].m_EnggInfo.m_strTitle = "AvgFuelEcoTripA";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_TRIPB_AVGFUELECO].m_EnggInfo.m_strTitle = "AvgFuelEcoTripB";
    sm_vectSignalsInfo[EDriveNextSignalTypes::DRIVENEXT_SIG_OVERALLTRIP_AVGFUELECO].m_EnggInfo.m_strTitle = "AvgFuelEcoOverallTrip";
}

void CDDriveNextSignalInformation::resetSignalsData()
{
    sm_vectSignalsInfo.clear();
}

SDriveNextSignalInformation CDDriveNextSignalInformation::getSignalData(int index)
{
    SDriveNextSignalInformation sInfo;
    if ((static_cast<int>(sm_vectSignalsInfo.size()) > index) && (index >= 0))
    {
        sInfo = sm_vectSignalsInfo.at(index);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Type Not Found:%d", __FUNCTION__, index);
    }
    return sInfo;
}

double CDDriveNextSignalInformation::roundDoubleWithDecimals(double dValue, uint uiPlaces)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s dValue:%lf, iPlaces:%u", __FUNCTION__, dValue, uiPlaces);
    double dFactor = pow(10, uiPlaces);
    return roundl(dValue * dFactor)/dFactor;
}

CDDriveNextSignalInformation::CDDriveNextSignalInformation(QObject *parent) :
    QObject(parent)
{
}

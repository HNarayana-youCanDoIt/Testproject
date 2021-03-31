/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDriveNextResourceData.cpp
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* @brief        File to contain all the Structure Data that shall be used by DriveNext module
*/

#include "CDriveNextResourceData.h"
#include "logging.h"

SAverageFuelEconomy::SAverageFuelEconomy()
    : eTripType(DRIVENEXT_TRIP_UNKNOWN),
      dAverageFuelEconomy(0.0)
{
}

SRpmBandInfo::SRpmBandInfo()
    : dTotalTime(0.0),
      dTotalDistance(0.0),
      dEffRpmTimeAmber(0.0),
      dEffRpmTimeAmberPer(0.0),
      dEffRpmTimeGreen(0.0),
      dEffRpmTimeGreenPer(0.0),
      dEffRpmTimeRed(0.0),
      dEffRpmTimeRedPer(0.0),
      dEffRpmDistAmber(0.0),
      dEffRpmDistAmberPer(0.0),
      dEffRpmDistGreen(0.0),
      dEffRpmDistGreenPer(0.0),
      dEffRpmDistRed(0.0),
      dEffRpmDistRedPer(0.0)
{
}

SEffciencyInfo::SEffciencyInfo()
    : eTripType(DRIVENEXT_TRIP_UNKNOWN),
      dFuelEcoInstRating(0.0),
      dFuelEcoCumulativeRating(0.0),
      dEngineIdleTime(0.0),
      dAverageSpeed(0.0),
      sAverageFuelEconomy(),
      sRpmBandInfo()
{
}

void SEffciencyInfo::setAverageFuelEconomy(EDriveNextTripType tripType, double averageFuelEconomy)
{
    sAverageFuelEconomy.eTripType = tripType;
    sAverageFuelEconomy.dAverageFuelEconomy = averageFuelEconomy;

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Trip Type : %d, Average Fuel Economy : %lf", __FUNCTION__,
             static_cast<int>(sAverageFuelEconomy.eTripType), sAverageFuelEconomy.dAverageFuelEconomy);
}

void SEffciencyInfo::setRpmBandInfo(double totalTime, double totalDistance, double effRpmTimeAmber, double effRpmTimeAmberPer,
                                    double effRpmTimeGreen, double effRpmTimeGreenPer, double effRpmTimeRed, double effRpmTimeRedPer,
                                    double effRpmDistAmber, double effRpmDistAmberPer, double effRpmDistGreen, double effRpmDistGreenPer,
                                    double effRpmDistRed, double effRpmDistRedPer)
{
    sRpmBandInfo.dTotalTime = totalTime;
    sRpmBandInfo.dTotalDistance = totalDistance;
    sRpmBandInfo.dEffRpmTimeAmber = effRpmTimeAmber;
    sRpmBandInfo.dEffRpmTimeAmberPer = effRpmTimeAmberPer;
    sRpmBandInfo.dEffRpmTimeGreen = effRpmTimeGreen;
    sRpmBandInfo.dEffRpmTimeGreenPer = effRpmTimeGreenPer;
    sRpmBandInfo.dEffRpmTimeRed = effRpmTimeRed;
    sRpmBandInfo.dEffRpmTimeRedPer = effRpmTimeRedPer;
    sRpmBandInfo.dEffRpmDistAmber = effRpmDistAmber;
    sRpmBandInfo.dEffRpmDistAmberPer = effRpmDistAmberPer;
    sRpmBandInfo.dEffRpmDistGreen = effRpmDistGreen;
    sRpmBandInfo.dEffRpmDistGreenPer = effRpmDistGreenPer;
    sRpmBandInfo.dEffRpmDistRed = effRpmDistRed;
    sRpmBandInfo.dEffRpmDistRedPer = effRpmDistRedPer;

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s Total time : %lf, Total distance : %lf", __FUNCTION__, totalTime, totalDistance);

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "Eff Rpm Time Amber : %lf, Eff Rpm Timer Amber Per : %lf, Eff Rpm Time Green : %lf, Eff Rpm Time Green Per : %lf, Eff Rpm Time Red : %lf, Eff Rpm Time Red Per : %lf",
             effRpmTimeAmber, effRpmTimeAmberPer, effRpmTimeGreen, effRpmTimeGreenPer, effRpmTimeRed, effRpmTimeRedPer);

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "Eff Rpm Dist Amber : %lf, Eff Rpm Dist Amber Per : %lf, Eff Rpm Dist Green : %lf, Eff Rpm Dist Green Per : %lf, Eff Rpm Dist Red : %lf, Eff Rpm Dist Red Per : %lf",
             effRpmDistAmber, effRpmDistAmberPer, effRpmDistGreen, effRpmDistGreenPer, effRpmDistRed, effRpmDistRedPer);
}

STimeinDifferentSpeedBands::STimeinDifferentSpeedBands()
    : eTripType(DRIVENEXT_TRIP_UNKNOWN),
      dSpeedBand1TimePer(0.0),
      dSpeedBand2TimePer(0.0),
      dSpeedBand3TimePer(0.0),
      dSpeedBand4TimePer(0.0),
      dSpeedBand1Time(0.0),
      dSpeedBand2Time(0.0),
      dSpeedBand3Time(0.0),
      dSpeedBand4Time(0.0)
{
}

SDrivingInfo::SDrivingInfo()
    : eTripType(DRIVENEXT_TRIP_UNKNOWN),
      dTopSpeed(0.0),
      dCorrectGearPerTime(0.0),
      dAverageAccPedalTravelPosition(0.0),
      dMostUsedGear(0.0),
      dCumulativeRatingofAvgAcc(0.0),
      dCumulativeRatingofAvgBrake(0.0),
      dCumulativeRatingofAvgGear(0.0),
      dInstRatingofAvgAcc(0.0),
      dInstRatingofAvgBrake(0.0),
      dInstRatingofAvgGear(0.0),
      dBrakingCountPer10Km(0.0),
      sDiffSpeedBandsPerTime()
{
}

void SDrivingInfo::setDiffSpeedBandsPerTime(EDriveNextTripType tripType,
                                            double speedBand1TimePer, double speedBand2TimePer, double speedBand3TimePer, double speedBand4TimePer,
                                            double speedBand1Time, double speedBand2Time, double speedBand3Time, double speedBand4Time)
{
    sDiffSpeedBandsPerTime.eTripType = tripType;
    sDiffSpeedBandsPerTime.dSpeedBand1TimePer = speedBand1TimePer;
    sDiffSpeedBandsPerTime.dSpeedBand2TimePer = speedBand2TimePer;
    sDiffSpeedBandsPerTime.dSpeedBand3TimePer = speedBand3TimePer;
    sDiffSpeedBandsPerTime.dSpeedBand4TimePer = speedBand4TimePer;
    sDiffSpeedBandsPerTime.dSpeedBand1Time = speedBand1Time;
    sDiffSpeedBandsPerTime.dSpeedBand2Time = speedBand2Time;
    sDiffSpeedBandsPerTime.dSpeedBand3Time = speedBand3Time;
    sDiffSpeedBandsPerTime.dSpeedBand4Time = speedBand4Time;

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, Trip Type : %d, SpeedBand1TimePer : %lf, SpeedBand2TimePer : %lf, SpeedBand3TimePer : %lf, SpeedBand4TimePer : %lf", __FUNCTION__,
             static_cast<int>(tripType), speedBand1TimePer, speedBand2TimePer, speedBand3TimePer, speedBand4TimePer);

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, SpeedBand1Time : %lf, SpeedBand2Time : %lf, SpeedBand3Time : %lf, SpeedBand4Time : %lf", __FUNCTION__,
             speedBand1Time, speedBand2Time, speedBand3Time, speedBand4Time);
}

SSeatBeltPerTime::SSeatBeltPerTime()
    : eTripType(DRIVENEXT_TRIP_UNKNOWN),
      dPerTimeWithoutSeatbelt(0.0),
      dPerTimeWithSeatbelt(0.0),
      dSeatBeltFactor(0.0)
{
}

SBrakingTypeInfo::SBrakingTypeInfo()
    : eTripType(DRIVENEXT_TRIP_UNKNOWN),
      dTotalBrk(0.0),
      dNormalBrk(0.0),
      dNormalBrkPer(0.0),
      dModerateBrk(0.0),
      dModerateBrkPer(0.0),
      dHeavyBrk(0.0),
      dHeavyBrkPer(0.0),
      dPanicBrk(0.0),
      dPanicBrkPer(0.0),
      dHarshBrk(0.0),
      dHarshBrkPer(0.0)
{
}

SSafetyInfo::SSafetyInfo()
    : dSafetyInstRating(0.0),
      dAverageSpeed(0.0),
      sSeatBeltPerTime(),
      sBreakingtypeInfo()
{
}

void SSafetyInfo::setSeatBeltPerTime(EDriveNextTripType tripType,
                                     double perTimeWithoutSeatbelt, double perTimeWithSeatbelt, double seatBeltFactor)
{
    sSeatBeltPerTime.eTripType = tripType;
    sSeatBeltPerTime.dPerTimeWithoutSeatbelt = perTimeWithoutSeatbelt;
    sSeatBeltPerTime.dPerTimeWithSeatbelt = perTimeWithSeatbelt;
    sSeatBeltPerTime.dSeatBeltFactor = seatBeltFactor;

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, Trip Type : %d, perTimeWithoutSeatbelt : %lf, perTimeWithSeatbelt : %lf, seatBeltFactor : %lf",
             __FUNCTION__, static_cast<int>(tripType), perTimeWithoutSeatbelt, perTimeWithSeatbelt, seatBeltFactor);
}

void SSafetyInfo::setBrakingTypeInfo( EDriveNextTripType tripType, double totalBrk,
                                      double normalBrk, double normalBrkPer, double moderateBrk, double moderateBrkPer,
                                      double heavyBrk, double heavyBrkPer, double panicBrk, double panicBrkPer,
                                      double harshBrk, double harshBrkPer )
{
    sBreakingtypeInfo.eTripType = tripType;
    sBreakingtypeInfo.dTotalBrk = totalBrk;
    sBreakingtypeInfo.dNormalBrk = normalBrk;
    sBreakingtypeInfo.dNormalBrkPer = normalBrkPer;
    sBreakingtypeInfo.dModerateBrk = moderateBrk;
    sBreakingtypeInfo.dModerateBrkPer = moderateBrkPer;
    sBreakingtypeInfo.dHeavyBrk = heavyBrk;
    sBreakingtypeInfo.dHeavyBrkPer = heavyBrkPer;
    sBreakingtypeInfo.dPanicBrk = panicBrk;
    sBreakingtypeInfo.dPanicBrkPer = panicBrkPer;
    sBreakingtypeInfo.dHarshBrk = harshBrk;
    sBreakingtypeInfo.dHarshBrkPer = harshBrkPer;

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "%s, Trip Type : %d, totalBrk : %lf, normalBrk : %lf, normalBrkPer : %lf, moderateBrk : %lf, moderateBrkPer : %lf",
             __FUNCTION__, static_cast<int>(tripType), totalBrk, normalBrk, normalBrkPer, moderateBrk, moderateBrkPer);

    LOG_INFO(Log::e_LOG_CONTEXT_DRIVENEXT, "heavyBrk : %lf, heavyBrkPer : %lf, panicBrk : %lf, panicBrkPer : %lf, harshBrk : %lf, harshBrkPer : %lf",
             heavyBrk, heavyBrkPer, panicBrk, panicBrkPer, harshBrk, harshBrkPer);
}

SDistanceUnitInfo::SDistanceUnitInfo()
    : m_eUnitType(EDriveNextDistanceUnitType::DRIVENEXT_DIST_TYPE_UNKNOWN),
      m_dUnitScale(0)
{
}

SFuelUnitInfo::SFuelUnitInfo()
    : m_eUnitType(EDriveNextFuelUnitType::DRIVENEXT_FUEL_TYPE_UNKNOWN),
      m_dUnitScale(0)
{
}

SSignalDataStructure::SSignalDataStructure():
    m_eErrorType(EDriveNextSignalErrorTypes::DRIVENEXT_SIG_ERROR_UNKNOWN),
    m_dValue(0)
{
}

double SSignalDataStructure::getValue()
{
    return m_dValue;
}

void SSignalDataStructure::setValue(double dValue)
{
    m_dValue = dValue;
}

EDriveNextSignalErrorTypes SSignalDataStructure::getErrorType()
{
    return m_eErrorType;
}

void SSignalDataStructure::setErrorType(EDriveNextSignalErrorTypes eErrorType)
{
    m_eErrorType = eErrorType;
}

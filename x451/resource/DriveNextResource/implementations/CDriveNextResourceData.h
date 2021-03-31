/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2019
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDriveNextResourceData.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* @brief        File to contain all the Structure Data that shall be used by DriveNext module
*/

#ifndef CDRIVENEXTRESOURCEDATA_H
#define CDRIVENEXTRESOURCEDATA_H

#include "CDriveNextResourceEnum.h"

/**
 * @struct SSignalDataStructure
 * @brief This structure shall hold the data for signal responce
 */
struct SSignalDataStructure
{
    /**
    * @brief    constructor for SSignalDataStructure.
    */
    SSignalDataStructure();

    /**
    * @brief    getValue get function for signal value.
    * @param    void.
    * @return   double signal value.
    */
    double getValue();

    /**
    * @brief    getValue get function for signal value.
    * @param    double signal value.
    * @return   void.
    */
    void setValue(double dValue);

    /**
    * @brief    getErrorType get function for signal error type.
    * @param    void.
    * @return   EDriveNextSignalErrorTypes signal error type.
    */
    EDriveNextSignalErrorTypes getErrorType();

    /**
    * @brief    getValue get function for signal value.
    * @param    EDriveNextSignalErrorTypes signal error type.
    * @return   void.
    */
    void setErrorType(EDriveNextSignalErrorTypes eErrorType);

private:
    /* Holds the DriveNext signal error type */
    EDriveNextSignalErrorTypes m_eErrorType;

    /* Holds the DriveNext signal value */
    double m_dValue;
};

/**
 * @struct SAverageFuelEconomy
 * @brief This structure shall hold the data for Average Fuel Economy
 */
struct SAverageFuelEconomy
{
    /**
    * @brief    constructor for SAverageFuelEconomy.
    */
    SAverageFuelEconomy();

    /* Holds the DriveNext trip type */
    EDriveNextTripType eTripType;

    /* Holds the average fuel economy */
    double dAverageFuelEconomy;
};

/**
 * @struct SRpmBandInfo
 * @brief This structure shall hold the data for RPM band information
 */
struct SRpmBandInfo
{
    /**
    * @brief    constructor for SRpmBandInfo.
    */
    SRpmBandInfo();

    /* Holds the total time for RPM band information */
    double dTotalTime;

    /* Holds the total distance for RPM band information */
    double dTotalDistance;

    /* Holds the EffRpmTimeAmber for RPM band information */
    double dEffRpmTimeAmber;

    /* Holds the EffRpmTimeAmberPer for RPM band information */
    double dEffRpmTimeAmberPer;

    /* Holds the EffRpmTimeGreen for RPM band information */
    double dEffRpmTimeGreen;

    /* Holds the EffRpmTimeGreenPer for RPM band information */
    double dEffRpmTimeGreenPer;

    /* Holds the EffRpmTimeRed for RPM band information */
    double dEffRpmTimeRed;

    /* Holds the EffRpmTimeRedPer for RPM band information */
    double dEffRpmTimeRedPer;

    /* Holds the EffRpmDistAmber for RPM band information */
    double dEffRpmDistAmber;

    /* Holds the EffRpmDistAmberPer for RPM band information */
    double dEffRpmDistAmberPer;

    /* Holds the EffRpmDistGreen for RPM band information */
    double dEffRpmDistGreen;

    /* Holds the EffRpmDistGreenPer for RPM band information */
    double dEffRpmDistGreenPer;

    /* Holds the EffRpmDistRed for RPM band information */
    double dEffRpmDistRed;

    /* Holds the EffRpmDistRedPer for RPM band information */
    double dEffRpmDistRedPer;
};

/**
 * @struct SEffciencyInfo
 * @brief This structure shall hold the data for Effciency Information
 */
struct SEffciencyInfo
{
    /**
    * @brief    constructor for SEffciencyInfo.
    */
    SEffciencyInfo();

    /**
    * @brief    This function sets the average fuel economy.
    * @param    tripType: trip type recieved from DriveNext service.
    *           averageFuelEconomy: average fuel economy recieved from DriveNext service
    * @return   void.
    */
    void setAverageFuelEconomy(EDriveNextTripType tripType, double averageFuelEconomy);

    /**
    * @brief    This function sets the Rpm band information.
    * @param    totalTime: total time.
    *           totalDistance: total distance.
    *           Rpm time: Rpm time for amber, green and red and their percentage
    *           Rpm distance: Rpm distance for amber, green and red and their percentage
    * @return   void.
    */
    void setRpmBandInfo(double totalTime, double totalDistance, double effRpmTimeAmber, double effRpmTimeAmberPer,
                        double effRpmTimeGreen, double effRpmTimeGreenPer, double effRpmTimeRed, double effRpmTimeRedPer,
                        double effRpmDistAmber, double effRpmDistAmberPer, double effRpmDistGreen, double effRpmDistGreenPer,
                        double effRpmDistRed, double effRpmDistRedPer);

    /* Holds the DriveNext trip type for Effciency Information */
    EDriveNextTripType eTripType;

    /* Holds the trip type for Effciency Information */
    double dFuelEcoInstRating;

    /* Holds the trip type for Effciency Information */
    double dFuelEcoCumulativeRating;

    /* Holds the Engine Idle Time for Effciency Information */
    double dEngineIdleTime;

    /* Holds the Average Speed for Effciency Information */
    double dAverageSpeed;

    /* Holds the Average Fuel Economy for Effciency Information */
    SAverageFuelEconomy sAverageFuelEconomy;

    /* Holds the Rpm Band Info for Effciency Information */
    SRpmBandInfo sRpmBandInfo;
};

/**
 * @struct STimeinDifferentSpeedBands
 * @brief This structure shall hold the data for Driving Information
 */
struct STimeinDifferentSpeedBands
{
    /**
    * @brief    constructor for STimeinDifferentSpeedBands.
    */
    STimeinDifferentSpeedBands();

    /* Holds the DriveNext trip type for Driving Information for different speed bands */
    EDriveNextTripType eTripType;

    /* Holds the speed band 1 time percentage for Driving Information */
    double dSpeedBand1TimePer;

    /* Holds the speed band 2 time percentage for Driving Information */
    double dSpeedBand2TimePer;

    /* Holds the speed band 3 time percentage for Driving Information */
    double dSpeedBand3TimePer;

    /* Holds the speed band 4 time percentage for Driving Information */
    double dSpeedBand4TimePer;

    /* Holds the speed band 1 time for Driving Information */
    double dSpeedBand1Time;

    /* Holds the speed band 2 time for Driving Information */
    double dSpeedBand2Time;

    /* Holds the speed band 3 time for Driving Information */
    double dSpeedBand3Time;

    /* Holds the speed band 4 time for Driving Information */
    double dSpeedBand4Time;
};

/**
 * @struct SDrivingInfo
 * @brief This structure shall hold the data for Driving Information
 */
struct SDrivingInfo
{
    /**
    * @brief    constructor for SDrivingInfo.
    */
    SDrivingInfo();

    /**
    * @brief    This function sets the different speed bands per time.
    * @param    tripType: trip type recieved from DriveNext service.
    *           SpeedBandTimePer: percentage for time for different speedbands
    *           SpeedBandTime: time for different speedbands
    * @return   void.
    */
    void setDiffSpeedBandsPerTime(EDriveNextTripType tripType,
                                  double speedBand1TimePer, double speedBand2TimePer, double speedBand3TimePer, double speedBand4TimePer,
                                  double speedBand1Time, double speedBand2Time, double speedBand3Time, double speedBand4Time);

    /* Holds the DriveNext trip type for Driving Information */
    EDriveNextTripType eTripType;

    /* Holds the top speed for Driving Information */
    double dTopSpeed;

    /* Holds the Correct Gear Per Time for Driving Information */
    double dCorrectGearPerTime;

    /* Holds the Average Acc Pedal Travel Position for Driving Information */
    double dAverageAccPedalTravelPosition;

    /* Holds the Most Used Gear for Driving Information */
    double dMostUsedGear;

    /* Holds the Cumulative Rating of Avg Acc for Driving Information */
    double dCumulativeRatingofAvgAcc;

    /* Holds the Cumulative Rating of Avg Brake for Driving Information */
    double dCumulativeRatingofAvgBrake;

    /* Holds the Cumulative Rating of Avg Gear for Driving Information */
    double dCumulativeRatingofAvgGear;

    /* Holds the Inst Rating of Avg Acc for Driving Information */
    double dInstRatingofAvgAcc;

    /* Holds the Inst Rating of Avg Brake for Driving Information */
    double dInstRatingofAvgBrake;

    /* Holds the Inst Rating of Avg Gear for Driving Information */
    double dInstRatingofAvgGear;

    /* Holds the Braking Count Per 10Km for Driving Information */
    double dBrakingCountPer10Km;

    /* Holds the Time in Different Speed Bands for Driving Information */
    STimeinDifferentSpeedBands sDiffSpeedBandsPerTime;
};

/**
 * @struct SSeatBeltPerTime
 * @brief This structure shall hold the data for Seat belt per time
 */
struct SSeatBeltPerTime
{
    /**
    * @brief    constructor for SSeatBeltPerTime.
    */
    SSeatBeltPerTime();

    /* Holds the DriveNext trip type for Seat Belt Per Time Information */
    EDriveNextTripType eTripType;

    /* Holds the Per Time Without Seatbelt for Seat Belt Per Time Information */
    double dPerTimeWithoutSeatbelt;

    /* Holds the Per Time With Seatbelt for Seat Belt Per Time Information */
    double dPerTimeWithSeatbelt;

    /* Holds the Seat Belt Factor for Seat Belt Per Time Information */
    double dSeatBeltFactor;
};

/**
 * @struct SBrakingTypeInfo
 * @brief This structure shall hold the data for Braking Type Information
 */
struct SBrakingTypeInfo
{
    /**
    * @brief    constructor for SBrakingTypeInfo.
    */
    SBrakingTypeInfo();

    /* Holds the DriveNext trip type for Braking Type Information */
    EDriveNextTripType eTripType;

    /* Holds the Total break for Braking Type Information */
    double dTotalBrk;

    /* Holds the Normal break for Braking Type Information */
    double dNormalBrk;

    /* Holds the Normal break percentage for Braking Type Information */
    double dNormalBrkPer;

    /* Holds the Moderate break for Braking Type Information */
    double dModerateBrk;

    /* Holds the Moderate break percentage for Braking Type Information */
    double dModerateBrkPer;

    /* Holds the Heavy break for Braking Type Information */
    double dHeavyBrk;

    /* Holds the Heavy break percentage for Braking Type Information */
    double dHeavyBrkPer;

    /* Holds the Panic break for Braking Type Information */
    double dPanicBrk;

    /* Holds the Panic break percentage for Braking Type Information */
    double dPanicBrkPer;

    /* Holds the Harsh break for Braking Type Information */
    double dHarshBrk;

    /* Holds the Harsh break percentage for Braking Type Information */
    double dHarshBrkPer;
};

/**
 * @struct SSafetyInfo
 * @brief This structure shall hold the data for Safety Information
 */
struct SSafetyInfo
{
    /**
    * @brief    constructor for SSafetyInfo.
    */
    SSafetyInfo();

    /**
    * @brief    This function sets the Seat Belt Per Time for Safety information.
    * @param    tripType: trip type recieved from DriveNext service.
    *           perTimeWithoutSeatbelt: percentage Time Without Seatbelt.
    *           perTimeWithSeatbelt: percentage Time With Seatbelt.
    *           seatBeltFactor: Seat belt factor.
    * @return   void.
    */
    void setSeatBeltPerTime(EDriveNextTripType tripType,
                            double perTimeWithoutSeatbelt, double perTimeWithSeatbelt, double seatBeltFactor);

    /**
    * @brief    This function sets the Braking Type Info for Safety information.
    * @param    tripType: trip type recieved from DriveNext service.
    *           totalBrk: Total break count.
    *           normalBrk: Normal break count.
    *           moderateBrk: Moderate break count.
    *           moderateBrkPer: Moderate break percentage.
    *           heavyBrk: Heavy break count.
    *           heavyBrkPer: Heavy break percentage.
    *           panicBrk: Panic break count.
    *           panicBrkPer: Panic break percentage.
    *           harshBrk: Harsh break count.
    *           harshBrkPer: Harsh break percentage.
    * @return   void.
    */
    void setBrakingTypeInfo( EDriveNextTripType tripType, double totalBrk,
                             double normalBrk, double normalBrkPer, double moderateBrk, double moderateBrkPer,
                             double heavyBrk, double heavyBrkPer, double panicBrk, double panicBrkPer,
                             double harshBrk, double harshBrkPer );

    /* Holds the Safety Inst Rating for Safety Information */
    double dSafetyInstRating;

    /* Holds the Average Speed for Safety Information */
    double dAverageSpeed;

    /* Holds the Seat Belt Per Time for Safety Information */
    SSeatBeltPerTime sSeatBeltPerTime;

    /* Holds the Braking Type Info for Safety Information */
    SBrakingTypeInfo sBreakingtypeInfo;
};

/**
 * @struct SDistanceUnitInfo
 * @brief This structure shall hold the data for distance unit Information
 */
struct SDistanceUnitInfo
{
    /**
    * @brief    constructor for SDistanceUnitInfo.
    */
    SDistanceUnitInfo();

    /* Holds the distance unit Type */
    EDriveNextDistanceUnitType m_eUnitType;

    /* Holds the distance unit scale factor */
    double m_dUnitScale;
};

/**
 * @struct SFuelUnitInfo
 * @brief This structure shall hold the data for fuel unit Information
 */
struct SFuelUnitInfo
{
    /**
    * @brief    constructor for SFuelUnitInfo.
    */
    SFuelUnitInfo();

    /* Holds the fuel unit Type */
    EDriveNextFuelUnitType m_eUnitType;

    /* Holds the Fuel unit scale factor */
    double m_dUnitScale;
};

#endif // CDRIVENEXTRESOURCEDATA_H

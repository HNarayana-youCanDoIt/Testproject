/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file    CVoiceAlertsEnums.h
 * @ingroup HMIComponent
 * @author  Guru Alingal
 * @brief   This class contains declarations for enums to be used in voice alerts
 *          domain.
 **/

#ifndef VOICEALERTSENUMS_H
#define VOICEALERTSENUMS_H

#include <QObject>
#include <QtQml>

class CVoiceAlertsEnums : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief The EVoiceAlerts enum is the enumeration of all the possible voice
     *        alerts in the system.
     */
    enum EVoiceAlerts
    {
        //// TATA_X104_High_VAVE specific code
        EN_VA_NOALERT = 0                                       ,
        EN_VA_AUTO_MODE                                         ,
        EN_VA_COMFORT_MODE                                      ,
        EN_VA_DYNAMIC_MODE                                      ,
        EN_VA_ROUGH_ROAD_MODE                                   ,
        EN_VA_CITY_MODE                                         ,
        EN_VA_SPORT_MODE                                        ,
        EN_VA_ECONOMY_MODE                                      ,
        EN_VA_DOOR_OPEN_GENERAL_WARNING                         ,
        EN_VA_DRIVER_DOOR_OPEN                                  ,
        EN_VA_CO_DRIVER_DOOR_OPEN                               ,
        EN_VA_REAR_RIGHT_DOOR_OPEN                              ,
        EN_VA_REAR_LEFT_DOOR_OPEN                               ,
        EN_VA_TAIL_GATE_OPEN                                    ,
        EN_VA_FASTEN_SEAT_BELT_DRIVER                           ,
        EN_VA_PARK_BRAKE_ENGAGED                                ,
        EN_VA_LOW_TIRE_PRESSURE_ALERT_FR                        ,
        EN_VA_LOW_TIRE_PRESSURE_ALERT_FL                        ,
        EN_VA_LOW_TIRE_PRESSURE_ALERT_RR                        ,
        EN_VA_LOW_TIRE_PRESSURE_ALERT_RL                        ,
        EN_VA_FUEL_LEVEL_LOW_STATE                              ,
        EN_VA_LOW_BRAKE_FLUID                                   ,
        EN_VA_ENGINE_OIL_PRESSURE_LOW_STATE                     ,
        EN_VA_WATER_IN_FUEL                                     ,
        EN_VA_KEY_SERVICE_REMINDER                              ,
        EN_VA_KEY_FOB_BATTERY_LOW                               ,
        EN_VA_SMART_KEY_OUT_OF_RANGE                            ,
    };

    /**
     * @brief The EMceVoiceAlerts enum is the enumeration of all the possible voice
     *        alerts in the Mce system.
     */
    enum EMceVoiceAlerts
    {
        EN_MCE_VA_NOALERT = 0                                       ,
        EN_MCE_VA_AUTO_MODE                                         ,
        EN_MCE_VA_COMFORT_MODE                                      ,
        EN_MCE_VA_DYNAMIC_MODE                                      ,
        EN_MCE_VA_ROUGH_ROAD_MODE                                   ,
        EN_MCE_VA_CITY_MODE                                         ,
        EN_MCE_VA_SPORT_MODE                                        ,
        EN_MCE_VA_ECONOMY_MODE                                      ,
        EN_MCE_VA_WET_MODE                                          ,
        EN_MCE_VA_MUD                                               ,
        EN_MCE_VA_SAND                                              ,
        EN_MCE_VA_GRASS                                             ,
        EN_MCE_VA_DOOR_OPEN_GENERAL_WARNING                         ,
        EN_MCE_VA_DRIVER_DOOR_OPEN                                  ,
        EN_MCE_VA_CO_DRIVER_DOOR_OPEN                               ,
        EN_MCE_VA_REAR_RIGHT_DOOR_OPEN                              ,
        EN_MCE_VA_REAR_LEFT_DOOR_OPEN                               ,
        EN_MCE_VA_TAIL_GATE_OPEN                                    ,
        EN_MCE_VA_FASTEN_SEAT_BELT_DRIVER                           ,
        EN_MCE_VA_HDC_DEACTIVATION_DUE_TO_SPEED_ABOVE_SET_VALUE     ,
        EN_MCE_VA_HDC_ACTIVATED                                     ,
        EN_MCE_VA_PARK_BRAKE_ENGAGED                                ,
        EN_MCE_VA_LOW_BRAKE_FLUID                                   ,
        EN_MCE_VA_LOW_SOC_INDICATION                                ,
        EN_MCE_VA_TPMS_GENERAL_WARNING                              ,
        EN_MCE_VA_LOW_TIRE_PRESSURE_ALERT_FL                        ,
        EN_MCE_VA_LOW_TIRE_PRESSURE_ALERT_FR                        ,
        EN_MCE_VA_LOW_TIRE_PRESSURE_ALERT_RL                        ,
        EN_MCE_VA_LOW_TIRE_PRESSURE_ALERT_RR                        ,
        EN_MCE_VA_LOW_TIRE_PRESSURE_ALERT_SPARE                     ,
        EN_MCE_VA_HIGH_TIRE_PRESSURE_ALERT_FL                       ,
        EN_MCE_VA_HIGH_TIRE_PRESSURE_ALERT_FR                       ,
        EN_MCE_VA_HIGH_TIRE_PRESSURE_ALERT_RL                       ,
        EN_MCE_VA_HIGH_TIRE_PRESSURE_ALERT_RR_                      ,
        EN_MCE_VA_HIGH_TIRE_PRESSURE_ALERT_SPARE                    ,
        EN_MCE_VA_HIGH_TIRE_TEMP_ALERT_FL                           ,
        EN_MCE_VA_HIGH_TIRE_TEMP_ALERT_FR                           ,
        EN_MCE_VA_HIGH_TIRE_TEMP_ALERT_RL                           ,
        EN_MCE_VA_HIGH_TIRE_TEMP_ALERT_RR                           ,
        EN_MCE_VA_HIGH_TIRE_TEMP_ALERT_SPARE                        ,
        EN_MCE_VA_PRESSURE_LEAKAGE_ALERT_FL                         ,
        EN_MCE_VA_PRESSURE_LEAKAGE_ALERT_FR                         ,
        EN_MCE_VA_PRESSURE_LEAKAGE_ALERT_RL                         ,
        EN_MCE_VA_PRESSURE_LEAKAGE_ALERT_RR                         ,
        EN_MCE_VA_PRESSURE_LEAKAGE_ALERT_SPARE_                     ,
        EN_MCE_VA_FORWARD_COLLISION_WARNING_INDICATION              ,
        EN_MCE_VA_CRUISE_ACTIVATED                                  ,
        EN_MCE_VA_SERVICE_REMINDER_DAYS                             ,
        EN_MCE_VA_SERVICE_REMINDER_KMS                              ,
        EN_MCE_VA_FUEL_FILTER_CLOGGING                              ,
        EN_MCE_VA_ENGINE_OIL_PRESSURE_LOW_STATE                     ,
        EN_MCE_VA_FUEL_LEVEL_LOW_STATE                              ,
        EN_MCE_VA_DRIVE_ALERT1_TEA_BREAK                            ,
        EN_MCE_VA_WATER_IN_FUEL                                     ,
        EN_MCE_VA_KEY_FOB_BATTERY_LOW                               ,
        EN_MCE_VA_FASTEN_SEAT_BELT_CO_DRIVER                        ,
        EN_MCE_VA_CRUISE_ON                                         ,
        EN_MCE_VA_KEY_NOT_FOUND                                     ,
        EN_MCE_VA_EXPRESS_COOLING_ON                                ,
        EN_MCE_VA_EXPRESS_COOLING_OFF                               ,
        EN_MCE_VA_EXPRESS_COOLING_ON_WINDOWS_ROLL_DOWN              ,
        EN_MCE_VA_EXPRESS_COOLING_OFF_WINDOWS_ROLL_UP               ,
        EN_MCE_VA_ROLL_UP_WINDOWS                                   ,
        EN_MCE_VA_LOW_AMBIENT_TEMPERATURE                           ,
    };

    /**
     * @brief The EVoiceAlertsState enum is the enumeration of all the possible
     *         states of a voice alert.
     */
    enum EVoiceAlertsState
    {
        EN_VA_STATE_NO_ALERT = 0,
        EN_VA_STATE_RECEIVED,
        EN_VA_STATE_IN_QUEQUE,
        EN_VA_STATE_IN_PROCESS,
        EN_VA_STATE_DELIVERED,
        EN_VA_STATE_ABORTED,
        EN_VA_STATE_IGNORED,
        EN_VA_STATE_IN_ERROR,
        EN_VA_STATE_IN_RESERVED,
    };

    /**
     * @brief The EDriveModes enum holds all the available drive modes.
     */
    enum EDriveModes
    {
        DRIVE_MODE_INVALID = -1,
        DRIVE_MODE_CITY_MANUAL,
        DRIVE_MODE_SPORT_MANUAL,
        DRIVE_MODE_ECONOMY_MANUAL,
        DRIVE_MODE_CITY_AUTO,
        DRIVE_MODE_SPORT_AUTO,
        DRIVE_MODE_ECONOMY_AUTO,
        DRIVE_MODE_CITY_TIPTRONIC,
        DRIVE_MODE_SPORT_TIPTRONIC,
        DRIVE_MODE_ECONOMY_TIPTRONIC,
    };

    /**
     * @brief The EDriveModesStates enum holds availability value for all drive mode.
     */
    enum EDriveModesStates
    {
        DRIVE_MODE_STATE_INVALID = -1,

        DRIVE_MODE_ENABLE_STATE = 1,

        DRIVE_MODE_CITY_MANUAL_STATE		=33,
        DRIVE_MODE_SPORT_MANUAL_STATE		=65,
        DRIVE_MODE_ECONOMY_MANUAL_STATE     =129,

        DRIVE_MODE_CITY_AUTO_STATE          = 513,
        DRIVE_MODE_SPORT_AUTO_STATE         = 1025,
        DRIVE_MODE_ECONOMY_AUTO_STATE		= 2049,

        DRIVE_MODE_CITY_TIPTRONIC_STATE     = 4097,
        DRIVE_MODE_SPORT_TIPTRONIC_STATE	= 8193,
        DRIVE_MODE_ECONOMY_TIPTRONIC_STATE  = 16385,
    };

};
#endif // VOICEALERTSENUM_H

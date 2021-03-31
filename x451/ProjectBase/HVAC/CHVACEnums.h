/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHVACEnums.h
* @ingroup      HMIComponent
* @author       Mohit Rajani
* CHVACEnum     Class that would contain all the Enums related to HVAC
*               that would also be registered as a QML type so that these can be used in QML too
*/

#ifndef CHVACENUMS_H
#define CHVACENUMS_H

#include <QObject>
#include <QtQml>

// const literals
const float TEMPERATURE_STEP_SIZE = 0.5;
const int TEMPERATURE_DIVISOR_MULTI = 10;
const int FAN_SPEED_STEP_SIZE = 1;
const int DISTRIBUTION_MODE_STEP_SIZE = 1;

/**
 * @class CHVACEnums
 * @brief Class that would contain all the Enums related to HVAC
 *        that would also be registered as a QML type so that these can be used in QML too
 */
class CHVACEnums : public QObject
{
    Q_OBJECT

public:

    /**
     * @enum EHVACParamEnums
     * @brief Enum for HVAC related parameters
     */
    enum EHVACParamEnums
    {
        HUCCM_AIRCON_CTRL = 1,
        HUCCM_ECON_MODE = 2,
        HUCCM_AUTO_MODE = 3,
        HUCCM_HVAC_CTRL = 4,
        HUCCM_MAX_DEFRST = 5,
        HUCCM_FRESHAIR_RECIRC = 6,
        HUCCM_DISTRIB_MODE = 7,
        HUCCM_TEMP_PASS = 8,
        HUCCM_TEMP_DRVR = 9,
        HUCCM_FAN_SPEED = 10,
        HUCCM_DUAL_MODE = 11,
        HUCCM_TEMP_CHANGE = 12,
        HUCCM_REAR_DEFOG = 13,
        CCM_ERR_STATUS = 14,
        CCM_VARIANT_TYPE = 15,
        CCM_PRESENCE = 16,
        CCM_SWITCH_STUCKWARN = 17,
        CCM_LOWFANSPD_CONFIG = 18,
        CCM_HIFANSPD_CONFIG = 19,
        CCM_LOWTEMP_CONFIG = 20,
        CCM_HITEMP_CONFIG = 21,
        CCM_ECON_CONFIG = 22,
        CCM_EXPCOOL_CONFIG = 23,
        HUCCM_EXPCOOL_STATUS = 24
    };
    Q_ENUM(EHVACParamEnums)

    enum EHVACModeStates
    {
        HVAC_MODE_STATE_OFF = 0,
        HVAC_MODE_STATE_ON,
    };
    Q_ENUM(EHVACModeStates)

    enum EHVACDistributionMode
    {
        HVAC_DM_MIN_LIMIT = 0,
        HVAC_DM_CHEST_MODE = 1,
        HVAC_DM_CHESTLEG_MODE,
        HVAC_DM_LEG_MODE,
        HVAC_DM_LEGDEFROST_MODE,
        HVAC_DM_DEFROST_MODE,
        HVAC_DM_MAX_LIMIT,
    };
    Q_ENUM(EHVACDistributionMode)

    enum EHVACAirCirculationModes
    {
        HVAC_AIRCIRCULATION_UNKNOWN = -1,
        HVAC_AIRCIRCULATION_RECIRCULATION_ON = 0,
        HVAC_AIRCIRCULATION_FRESHIR_ON = 2,
    };
    Q_ENUM(EHVACAirCirculationModes)

    /**
     * @enum EHVACErrorValue
     * @brief Enum for HVAC related error
     */
    enum EHVACErrorValue
    {
        HVAC_NOERROR = 0,
        HVAC_ERROR = 1,
        HVAC_ERROR_SETTING_NOT_UPDATED = 2,
    };
    Q_ENUM(EHVACErrorValue)

    /**
     * @enum EHVACCCMPresence
     * @brief Enum for HVAC CCM presence status
     */
    enum EHVACCCMPresence
    {
        HVAC_CCM_UNKNOWN = -1,
        HVAC_CCM_PRESENT = 0,
        HVAC_CCM_RESERVED = 1,
        HVAC_CCM_MAX = 2,
    };
    Q_ENUM(EHVACCCMPresence)

    /**
     * @enum EHVACZoneType
     * @brief Enum for HVAC zone type
     */
    enum EHVACZoneType
    {
        HVAC_UNKNOWN_ZONE = -1,
        HVAC_SINGLE_ZONE = 0,
        HVAC_DUAL_ZONE = 1,
        HVAC_ETC_ZONE = 2,
        HVAC_RESERVED_ZONE = 3
    };
    Q_ENUM(EHVACZoneType)

    /**
     * @enum EHVACContainerType
     * @brief Enum for HVAC container type
     */
    enum EHVACContainerType
    {
        EN_CONTAINER_TYPE_DUAL_ZONE,
        EN_CONTAINER_TYPE_SINGLE_ZONE,
        EN_CONTAINER_TYPE_SINGLE_ZONE_WITH_XPRESS_COOLING,
        EN_CONTAINER_TYPE_NONE
    };
    Q_ENUM(EHVACContainerType)

    /**
     * @brief registerHVACEnumsToQML Method to register CHVACEnum as a QML type
     */
    static void registerHVACEnumsToQML()
    {
        qmlRegisterType<CHVACEnums>("com.harman.qml.hvacenums",1,0,"HVACEnums");
    }
};

Q_DECLARE_METATYPE(CHVACEnums::EHVACParamEnums)
Q_DECLARE_METATYPE(CHVACEnums::EHVACModeStates)
Q_DECLARE_METATYPE(CHVACEnums::EHVACDistributionMode)
Q_DECLARE_METATYPE(CHVACEnums::EHVACAirCirculationModes)
Q_DECLARE_METATYPE(CHVACEnums::EHVACErrorValue)
Q_DECLARE_METATYPE(CHVACEnums::EHVACCCMPresence)
Q_DECLARE_METATYPE(CHVACEnums::EHVACZoneType)
Q_DECLARE_METATYPE(CHVACEnums::EHVACContainerType)

#endif // CHVACENUM_H

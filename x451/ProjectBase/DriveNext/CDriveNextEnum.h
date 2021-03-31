/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDriveNextEnum.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextEnum, file that contain enums that will be used in DriveNext.
 */

#ifndef CDRIVENEXTENUM_H
#define CDRIVENEXTENUM_H

#include <QObject>
#include <QtQml>

class CDriveNextEnum: public QObject
{
    Q_OBJECT
public:

    //________________________________________________________________________________________________
    /**
     * @enum EDNSignalErrorTypes
     * @brief Enums for DriveNext Signal Error Types
     */
    enum EDNSignalErrorTypes
    {
        DRIVENEXT_SIG_ERROR_CONFIGURATION_FILE_PATH_NOT_FOUND = 8001,
        DRIVENEXT_SIG_ERROR_TRIP_HISTORY_FILE_PATHIN_VALID = 8002,
        DRIVENEXT_SIG_ERROR_CONFIGURATION_FILE_INVALID = 8003,
        DRIVENEXT_SIG_ERROR_TRIP_HISTORY_FILE_INVALID = 8004,
        DRIVENEXT_SIG_ERROR_VALUE_NOT_IN_RANGE = 8200,
        DRIVENEXT_SIG_ERROR_VALUE_ABOVE_RANGE = 8201,
        DRIVENEXT_SIG_ERROR_VALUE_BELOW_RANGE = 8202,
        DRIVENEXT_SIG_ERROR_SIGNAL_VALUE_NOT_SET = 8203,
        DRIVENEXT_SIG_ERROR_SIGNAL_VALUE_NOT_AVAILABLE = 8204,
        DRIVENEXT_SIG_ERROR_DIVIDEBYZERO = 8301,
        DRIVENEXT_SIG_ERROR_OVERFLOW = 8302,
        DRIVENEXT_SIG_ERROR_JSON_INVALID = 8501,
        DRIVENEXT_SIG_ERROR_DATA_INCOMPLETE = 8801,
        DRIVENEXT_SIG_ERROR_OTHER = 8601,
        DRIVENEXT_SIG_ERROR_TRIPID_NOT_FOUND = 8602,
        DRIVENEXT_SIG_ERROR_STATE_PERMISSION_DENIED = 8700,
        DRIVENEXT_SIG_ERROR_CANNOT_CREATE_USER_DIRECTORY = 8701,
        DRIVENEXT_SIG_ERROR_EXCEPTION = 8000,
        DRIVENEXT_SIG_ERROR_TRIP_NOT_RUNNING = 9001,
        DRIVENEXT_SIG_ERROR_TRIP_DISTANCE_THRESH = 9002,
        DRIVENEXT_SIG_ERROR_LIBRARY_NOT_INITIALIZED = 10001,
        DRIVENEXT_SIG_ERROR_AMT_VEHICLE = 11001,
        DRIVENEXT_SIG_ERROR_SUCCESS = 0,
        DRIVENEXT_SIG_ERROR_UNKNOWN = -1,
    };
    Q_ENUMS(EDNSignalErrorTypes)

    //________________________________________________________________________________________________
    /**
     * @enum EDNTripType
     * @brief Enums for DriveNext Trip Type
     */
    enum EDNTripType
    {
        DRIVENEXT_TRIP_UNKNOWN    = -1,
        DRIVENEXT_TRIP_A          = 0,
        DRIVENEXT_TRIP_B          = 1,
        DRIVENEXT_OVERALL_TRIP    = 2,
        DRIVENEXT_CURRENT_TRIP    = 3,
        DRIVENEXT_LAST_TRIP       = 4,
        DRIVENEXT_BEST_TRIP       = 5,
        DRIVENEXT_ALL_TRIP        = 6
    };
    Q_ENUMS(EDNTripType)

    //________________________________________________________________________________________________
    /**
     * @enum EDNTripElements
     * @brief Enums for DriveNext Trip Data Elements
     */
    enum EDNTripElements
    {
        DN_TRIP_ELEMENT_UNKNOWN             = -1,
        DN_TRIP_ELEMENT_OVERALL_SCORE,
        DN_TRIP_ELEMENT_EFFICIENCY_SCORE,
        DN_TRIP_ELEMENT_DRIVING_SCORE,
        DN_TRIP_ELEMENT_SAFETY_SCORE,
        DN_TRIP_ELEMENT_DISTANCE_TRAVELLED,
        DN_TRIP_ELEMENT_FUEL_ECONOMY,
        DN_TRIP_ELEMENT_TRIP_DURATION,
        DN_TRIP_ELEMENT_ENG_IDLE_TIME,
        DN_TRIP_ELEMENT_AVG_SPEED,
        DN_TRIP_ELEMENT_TOP_SPEED,
        DN_TRIP_ELEMENT_PROPER_GEAR_UTIL,
        DN_TRIP_ELEMENT_AVG_ACCEL_PEDAL_TRIVAL,
        DN_TRIP_ELEMENT_MOST_USED_GEAR,
        DN_TRIP_ELEMENT_SEATBELT_UTIL,
        DN_TRIP_ELEMENT_OVER_SPEEDING,
        DN_TRIP_ELEMENT_HARSH_ACCEL,
        DN_TRIP_ELEMENT_HARSH_BREAK,
        DN_TRIP_ELEMENT_TOTAL_COUNT
    };
    Q_ENUMS(EDNTripElements)

    /**
     * @enum EDNLogLevel
     * @brief Enums for DriveNext Log Level
     */
    enum EDNLogLevel
    {
        DRIVENEXT_LOG_LEVEL_UNKNOWN = -1,
        DRIVENEXT_LOG_LEVEL_0   = 0,
        DRIVENEXT_LOG_LEVEL_1   = 1,
        DRIVENEXT_LOG_LEVEL_2   = 2,
        DRIVENEXT_LOG_LEVEL_3   = 3
    };
    Q_ENUMS(EDNLogLevel)

    /**
     * @enum EDNLoggingType
     * @brief Enums for DriveNext Logging type
     */
    enum EDNLoggingType
    {
        DRIVENEXT_LOG_TYPE_UNKNOWN  = -1,
        DRIVENEXT_LOG_TYPE_INTERNAL = 0,
        DRIVENEXT_LOG_TYPE_USB      = 1
    };
    Q_ENUMS(EDNLoggingType)

    /**
     * @enum EDNSigUnitType
     * @brief Enums for DriveNext Signal unit type
     */
    enum EDNSigUnitType
    {
        DRIVENEXT_SIG_UNIT_UNKNOWN = -1,
        DRIVENEXT_SIG_UNIT_PERCENTAGE,
        DRIVENEXT_SIG_UNIT_MILI_LTR,
        DRIVENEXT_SIG_UNIT_RPM,
        DRIVENEXT_SIG_UNIT_SEC,
        DRIVENEXT_SIG_UNIT_HRS,
        DRIVENEXT_SIG_UNIT_MTR_PER_SEC_SQR,
        DRIVENEXT_SIG_UNIT_KM,
        DRIVENEXT_SIG_UNIT_KM_PER_HR,
        DRIVENEXT_SIG_UNIT_KM_PER_LITRE,
        DRIVENEXT_SIG_UNIT_SCORE,
        DRIVENEXT_SIG_UNIT_KM_PER_LTR,
        DRIVENEXT_SIG_UNIT_TOTAL_COUNT
    };

    /**
     * @enum EDNSigFormatType
     * @brief Enums for DriveNext signal value format type
     */
    enum EDNSigFormatType
    {
        DRIVENEXT_SIG_FORMAT_UNKNOWN = -1,
        DRIVENEXT_SIG_FORMAT_VALUE,
        DRIVENEXT_SIG_FORMAT_VALUE_UNIT,
        DRIVENEXT_SIG_FORMAT_TEXT_VAL,
        DRIVENEXT_SIG_FORMAT_HHHH_MM_SS,
        DRIVENEXT_SIG_FORMAT_HHHH_MM,
        DRIVENEXT_SIG_FORMAT_TOTAL_COUNT
    };

    /**
     * @enum EDNSigStringType
     * @brief Enums for DriveNext Signal string type
     */
    enum EDNSigStringType
    {
        DRIVENEXT_SIG_STR_UNKNOWN = -1,
        DRIVENEXT_SIG_STR_GEAR,
        DRIVENEXT_SIG_STR_TOTAL_COUNT
    };

    //________________________________________________________________________________________________

    static void registerDriveNextEnumsToQML()
    {
        qmlRegisterType<CDriveNextEnum>("com.harman.qml.driveNextenums",1,0,"DriveNextEnums");
    }
};

Q_DECLARE_METATYPE(CDriveNextEnum::EDNSignalErrorTypes)
Q_DECLARE_METATYPE(CDriveNextEnum::EDNTripType)
Q_DECLARE_METATYPE(CDriveNextEnum::EDNTripElements)
Q_DECLARE_METATYPE(CDriveNextEnum::EDNLogLevel)
Q_DECLARE_METATYPE(CDriveNextEnum::EDNLoggingType)

#endif // CDRIVENEXTENUM_H

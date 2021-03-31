/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file                CParkAssistEnums.h
 * @ingroup             HMIComponent
 * @author              Santosh Chakala
 * CParkAssistEnums     Class that would contain all the Enums related to ParkAssist
 *                      that would also be registered as a QML type so that these could be used in QML too
 */

#ifndef CPARKASSISTENUMS_H
#define CPARKASSISTENUMS_H

#include <QObject>
#include <QtQml>

/**
 * @class CParkAssistEnum
 * @brief Class that would contain all the Enums related to parkAssist
 *        that would also be registered as a QML type so that these could be used in QML too
 */
class CParkAssistEnum : public QObject{

    Q_OBJECT
public:

    /**
     * @enum EPDcRearTones
     * @brief Enum for Park Assist Tones
     */
    enum EPDcRearTones
    {
        PARKASSIST_TONE_1 = 0,
        PARKASSIST_TONE_2 = 1,
        PARKASSIST_TONE_3 = 2,
    };
    Q_ENUM(EPDcRearTones)

    /**
     * @brief The EParkAssistDelayTimer enum: This enum contains delay timer indexe's
     */
    enum EParkAssistDelayTimer
    {
        PARK_ASSIST_DELAY_TIMER_DEFAULT_INDEX = -1,
        PARK_ASSIST_DELAY_TIMER_ZERO_INDEX,
        PARK_ASSIST_DELAY_TIMER_ONE_INDEX,
        PARK_ASSIST_DELAY_TIMER_TWO_INDEX,
        PARK_ASSIST_DELAY_TIMER_MAX_INDEX,
    };
    Q_ENUM(EParkAssistDelayTimer)

    /**
     * @brief The EParkAssistDelayTimerValues enum: This enum contains delay timer value's
     */
    enum EParkAssistDelayTimerValues
    {
        PARK_ASSIST_DELAY_TIMER_DEFAULT_VALUE    = -1,
        PARK_ASSIST_DELAY_TIMER_ZERO_INDEX_VALUE = 0,
        PARK_ASSIST_DELAY_TIMER_ONE_INDEX_VALUE  = 5,
        PARK_ASSIST_DELAY_TIMER_TWO_INDEX_VALUE  = 10,
        PARK_ASSIST_DELAY_TIMER_MAX_INDEX_VALUE,
    };
    Q_ENUM(EParkAssistDelayTimerValues)

    /**
     * @brief The EParkAssistVariantType enum: This enum contains park assist variant types
     */
    enum EParkAssistVariantType
    {
        PARK_ASSIST_VARIANT_DEFAULT = 0,
        PARK_ASSIST_VARIANT_PDC = 1,
        PARK_ASSIST_VARIANT_RVC = 2,
        PARK_ASSIST_VARIANT_PDC_RVC = 3
    };
    Q_ENUM(EParkAssistVariantType)

    /**
     * @brief The EPdcFaults enum: This enum contains PDC faults
     */
    enum EPdcFaults
    {
        PDC_FAULT_NO_FAULT = 0,
        PDC_FAULT_CRITICAL_FAULT = 1,
        PDC_FAULT_TRAILER_CONNECTED = 2,
        PDC_FAULT_VEHICLE_SPEED_TOO_HIGH = 3,
        PDC_FAULT_TOO_MUCH_NOISY_ENVIRONMENT = 4,
        PDC_FAULT_MINOR_FAULT = 5,
        PDC_FAULT_TAILGATE_OPEN = 6,
        PDC_FAULT_PARK_BRAKE_ENGAGED = 7
    };
    Q_ENUM(EPdcFaults)

    /**
     * @brief The ERvcFaults enum: This enum contains RVC faults
     */
    enum ERvcFaults
    {
        RVC_FAULT_NO_FAULT = 0,
        RVC_FAULT_TAILGATE_OPEN = 1,
        RVC_FAULT_RVC_VIDEO_STG = 2,
        RVC_FAULT_RVC_VIDEO_SIGNAL_FAULT = 3
    };
    Q_ENUM(ERvcFaults)

    /**
     * @brief The EPdcRvcFaults enum: This enum contains PDC+RVC faults
     */
    enum EPdcRvcFaults
    {
        PDC_RVC_FAULT_NO_FAULT = 0,
        PDC_RVC_FAULT_PDC_OK_RVC_VIDEO_FAULT = 1,
        PDC_RVC_FAULT_PDC_CRITICAL_FAULT_RVC_VIDEO_FAULT = 2,
        PDC_RVC_FAULT_PDC_NOISY_ENV_RVC_VIDEO_FAULT = 3,
        PDC_RVC_FAULT_PDC_TRAILER_CONNECTED_RVC_VIDEO_FAULT = 4,
        PDC_RVC_FAULT_PDC_OVERSPEED_RVC_VIDEO_FAULT = 5,
        PDC_RVC_FAULT_PDC_TAILGATE_OPEN_RVC_VIDEO_FAULT = 6,
        PDC_RVC_FAULT_PDC_PARK_BRAKE_RVC_VIDEO_FAULT = 7,
        PDC_RVC_FAULT_PDC_MINOR_FAULT_RVC_VIDEO_FAULT = 8,
        PDC_RVC_FAULT_PDC_CRITICAL_FAULT_RVC_OK = 9,
        PDC_RVC_FAULT_PDC_NOISY_ENV_RVC_OK = 10,
        PDC_RVC_FAULT_PDC_TRAILER_RVC_OK = 11,
        PDC_RVC_FAULT_PDC_OVERSPEED_RVC_OK = 12,
        PDC_RVC_FAULT_PDC_TAILGATE_RVC_OK = 13,
        PDC_RVC_FAULT_PDC_PARK_BRAKE_RVC_OK = 14,
        PDC_RVC_FAULT_PDC_MINOR_FAULT_RVC_OK = 15
    };
    Q_ENUM(EPdcRvcFaults)

    /**
     * @brief The ERvcOverlays enum: This enum contains RVC overlay types
     */
    enum ERvcOverlays
    {
        RVC_OVERLAY_DEFAULT = -1,
        RVC_OVERLAY_STATIC = 0,
        RVC_OVERLAY_DYNAMIC = 1
    };
    Q_ENUM(ERvcOverlays)

    /**
     * @brief The ERvcOverlayDirection enum: This enum contains RVC overlay direction
     */
    enum ERvcOverlayDirection
    {
        RVC_OVERLAY_DEFAULT_DIRECTION = -1,
        RVC_OVERLAY_CLOCKWISE_DIRECTION = 0,    /** Steering wheel turned in clockwise direction */
        RVC_OVERLAY_COUNTER_CLOCKWISE_DIRECTION = 1    /** Steering wheel turned in counter-clockwise direction */
    };
    Q_ENUM(ERvcOverlayDirection)

    /**
     * @brief The ERvcZones enum: This enum contains RVC zones
     */
    enum ERvcZones
    {
        RVC_ZONE_DEFAULT = -1,
        RVC_ZONE_GREEN = 0,
        RVC_ZONE_YELLOW = 1,
        RVC_ZONE_RED = 2
    };
    Q_ENUM(ERvcZones)

    /**
     * @brief The EPdcLeftZone enum: This enum contains left zones of PDC screen
     */
    enum EPdcLeftZone
    {
        PDC_LEFT_ZONE_NO_OBSTACLE = 0,
        PDC_LEFT_ZONE_RED_LEVEL_1 = 1,
        PDC_LEFT_ZONE_RED_LEVEL_2 = 2,
        PDC_LEFT_ZONE_YELLOW_LEVEL_3 = 3,
        PDC_LEFT_ZONE_YELLOW_LEVEL_4 = 4,
        PDC_LEFT_ZONE_GREEN_LEVEL_5 = 5,
        PDC_LEFT_ZONE_GREEN_LEVEL_6 = 6
    };
    Q_ENUM(EPdcLeftZone)

    /**
     * @brief The EPdcMidLeftZone enum: This enum contains mid left zones of PDC screen
     */
    enum EPdcMidLeftZone
    {
        PDC_MID_LEFT_ZONE_NO_OBSTACLE = 0,
        PDC_MID_LEFT_ZONE_RED_LEVEL_1 = 1,
        PDC_MID_LEFT_ZONE_RED_LEVEL_2 = 2,
        PDC_MID_LEFT_ZONE_YELLOW_LEVEL_3 = 3,
        PDC_MID_LEFT_ZONE_YELLOW_LEVEL_4 = 4,
        PDC_MID_LEFT_ZONE_GREEN_LEVEL_5 = 5,
        PDC_MID_LEFT_ZONE_GREEN_LEVEL_6 = 6
    };
    Q_ENUM(EPdcMidLeftZone)

    /**
     * @brief The EPdcMidRightZone enum: This enum contains mid right zones of PDC screen
     */
    enum EPdcMidRightZone
    {
        PDC_MID_RIGHT_ZONE_NO_OBSTACLE = 0,
        PDC_MID_RIGHT_ZONE_RED_LEVEL_1 = 1,
        PDC_MID_RIGHT_ZONE_RED_LEVEL_2 = 2,
        PDC_MID_RIGHT_ZONE_YELLOW_LEVEL_3 = 3,
        PDC_MID_RIGHT_ZONE_YELLOW_LEVEL_4 = 4,
        PDC_MID_RIGHT_ZONE_GREEN_LEVEL_5 = 5,
        PDC_MID_RIGHT_ZONE_GREEN_LEVEL_6 = 6
    };
    Q_ENUM(EPdcMidRightZone)

    /**
     * @brief The EPdcRightZone enum: This enum contains right zones of PDC screen
     */
    enum EPdcRightZone
    {
        PDC_RIGHT_ZONE_NO_OBSTACLE = 0,
        PDC_RIGHT_ZONE_RED_LEVEL_1 = 1,
        PDC_RIGHT_ZONE_RED_LEVEL_2 = 2,
        PDC_RIGHT_ZONE_YELLOW_LEVEL_3 = 3,
        PDC_RIGHT_ZONE_YELLOW_LEVEL_4 = 4,
        PDC_RIGHT_ZONE_GREEN_LEVEL_5 = 5,
        PDC_RIGHT_ZONE_GREEN_LEVEL_6 = 6
    };
    Q_ENUM(EPdcRightZone)

    /**
     * @brief Method to register CParkAssistEnum as a QML type
     * @param void
     * @return void
     */
    static void registerParkAssistEnumsToQML()
    {
        qmlRegisterType<CParkAssistEnum>("com.harman.qml.parkassistenum",1,0,"ParkAssistEnum");
    }
};

Q_DECLARE_METATYPE(CParkAssistEnum::EParkAssistDelayTimer)
Q_DECLARE_METATYPE(CParkAssistEnum::EParkAssistDelayTimerValues)
Q_DECLARE_METATYPE(CParkAssistEnum::EParkAssistVariantType)
Q_DECLARE_METATYPE(CParkAssistEnum::EPdcFaults)
Q_DECLARE_METATYPE(CParkAssistEnum::ERvcFaults)
Q_DECLARE_METATYPE(CParkAssistEnum::EPdcRvcFaults)
Q_DECLARE_METATYPE(CParkAssistEnum::ERvcOverlays)
Q_DECLARE_METATYPE(CParkAssistEnum::ERvcOverlayDirection)
Q_DECLARE_METATYPE(CParkAssistEnum::ERvcZones)
Q_DECLARE_METATYPE(CParkAssistEnum::EPdcLeftZone)
Q_DECLARE_METATYPE(CParkAssistEnum::EPdcMidLeftZone)
Q_DECLARE_METATYPE(CParkAssistEnum::EPdcMidRightZone)
Q_DECLARE_METATYPE(CParkAssistEnum::EPdcRightZone)
#endif // CPARKASSISTENUMS_H

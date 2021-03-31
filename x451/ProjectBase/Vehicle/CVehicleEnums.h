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
 * CParkAssistEnums     Class that would contain all the Enums related to Vehicle
 *                      that would also be registered as a QML type so that these could be used in QML too
 */

#ifndef CVEHICLEENUMS_H
#define CVEHICLEENUMS_H

#include <QObject>
#include <QtQml>

/**
 * @class CVehicleEnums
 * @brief Class that would contain all the Enums related to vehicle
 *        that would also be registered as a QML type so that these could be used in QML too
 */
class CVehicleEnums :public QObject
{
    Q_OBJECT
public:
    /**
     * @brief The EParkAssistDelayTimer enum: This enum contains delay timer indexe's
     */
    enum EVehicleApproachLampsIndex
    {
        VEHICLE_APPROACH_LAMPS_DEFAULT_INDEX = -1,
        VEHICLE_APPROACH_LAMPS_ZERO_INDEX,
        VEHICLE_APPROACH_LAMPS_ONE_INDEX,
        VEHICLE_APPROACH_LAMPS_TWO_INDEX,
        VEHICLE_APPROACH_LAMPS_MAX_INDEX,
    };
    Q_ENUM(EVehicleApproachLampsIndex)

    /**
     * @brief The EParkAssistDelayTimerValues enum: This enum contains delay timer value's
     */
    enum EVehicleApproachLampsValues
    {
        VEHICLE_APPROACH_LAMPS_DEFAULT_VALUE    = -1,
        VEHICLE_APPROACH_LAMPS_ZERO_INDEX_VALUE = 30,
        VEHICLE_APPROACH_LAMPS_ONE_INDEX_VALUE  = 60,
        VEHICLE_APPROACH_LAMPS_TWO_INDEX_VALUE  = 90,
        VEHICLE_APPROACH_LAMPS_MAX_INDEX_VALUE,
    };
    Q_ENUM(EVehicleApproachLampsValues)


    /**
     * @brief The EAmbientLightMode enum: This enum conatins ambient light mode values
     */
    enum EAmbientLightMode
    {
        AMBIENT_LIGHT_DEFAULT_VALUE = -1,
        AMBIENT_LIGHT_AUTO_MODE,
        AMBIENT_LIGHT_OFF_MODE,
        AMBIENT_LIGHT_ON_MODE,
        AMBIENT_LIGHT_RESERVED,
    };
    Q_ENUM(EAmbientLightMode)

    /**
     * @brief The EParkLampAvailability enum : This enum conatins park light availablity status
     */
    enum EParkLampAvailability {
        PARK_LAMP_DEFAULT_VALUE = -1,
        PARK_LAMP_AVAILABLE,
        PARK_LAMP_NOT_AVAILBLE,
        PARK_LAMP_NOT_SUPPORTED,
        PARK_LAMP_NOT_SUPPORTED_SECURITY_POLICY,
    };
    Q_ENUM(EParkLampAvailability)

    static void registerVehicleEnumsToQML()
    {
        qmlRegisterType<CVehicleEnums>("com.harman.qml.vehicleenums", 1, 0, "VehicleEnums");
    }
};
Q_DECLARE_METATYPE(CVehicleEnums::EVehicleApproachLampsIndex)
Q_DECLARE_METATYPE(CVehicleEnums::EVehicleApproachLampsValues)
Q_DECLARE_METATYPE(CVehicleEnums::EAmbientLightMode)
Q_DECLARE_METATYPE(CVehicleEnums::EParkLampAvailability)

#endif // CVEHICLEENUMS_H

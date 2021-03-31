/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CPowerModeEnums.h
 * @ingroup         HMIComponent
 * @author          Prashantkumar Raut
 * CPowerEnums - a class to handle Power mode functionality.
 */

#ifndef CPOWERMODEENUMS_H
#define CPOWERMODEENUMS_H

#include <QObject>
#include <QtQml>

/**
 * @brief The CPowerModeEnums class: This class contains all the enums related to Power mode
 */
class CPowerModeEnums : public QObject
{
    Q_OBJECT
public:

    /**
    * @brief Enum for Vehicle Power modes.
    **/
    enum eVehiclePowerModes
    {
        VPM_UNKNOWN = 0,
        VPM_SWITCH_OFF,
        VPM_EARLY_WAKEUP,
        VPM_MEDIA_OFF,
        VPM_ACTIVE,
        VPM_ONE_HOUR,
    };

    //make eVehiclePowerModes as qml enum
    Q_ENUM(eVehiclePowerModes)

    enum eNSMNodeStates
    {
        NsmNodeState_NotSet = 0,
        NsmNodeState_StartUp = 1,
        NsmNodeState_BaseRunning = 2,
        NsmNodeState_LucRunning = 3,
        NsmNodeState_FullyRunning = 4,
        NsmNodeState_FullyOperational = 5,
        NsmNodeState_ShuttingDown = 6,
        NsmNodeState_ShutdownDelay = 7,
        NsmNodeState_FastShutdown = 8,
        NsmNodeState_DegradedPower = 9,
        NsmNodeState_Shutdown = 10,
        NsmNodeState_Last = 11
    };

    //make eNSMNodeStates as qml enum
    Q_ENUM(eNSMNodeStates)

    /**
    * @brief register PowerEnum class with QML
    **/
    static void registerPowerEnumsToQML()
    {
        qmlRegisterType<CPowerModeEnums>("com.harman.qml.powerenums",1,0,"PowerModeEnums");
    }
};

/**
* @brief  declare PowerEnum class enums in QML matatype
**/
Q_DECLARE_METATYPE(CPowerModeEnums::eVehiclePowerModes)
Q_DECLARE_METATYPE(CPowerModeEnums::eNSMNodeStates)

#endif // CPOWERMODEENUMS_H

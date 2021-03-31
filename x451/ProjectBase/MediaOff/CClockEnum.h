/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CClockEnum.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         CClockEnum class that contains all the Clock related enums.
 */

#ifndef CCLOCKENUM_H
#define CCLOCKENUM_H

#include <QObject>
#include <QtQml>

class CClockEnum: public QObject
{
    Q_OBJECT
public:

    /**
     * @enum    EClockLayoutTypes
     * @brief   Defines clock layout types.
     */
    enum EClockLayoutTypes
    {
        LAYOUT_UNDEFINED = 0,
        LAYOUT_ANALOG,
        LAYOUT_DIGITAL,
    };
    Q_ENUM(EClockLayoutTypes)

    /**
     * @enum    EClockMotionTypes
     * @brief   Defines clock hand motion types.
     */
    enum EClockMotionTypes
    {
        MOTION_UNDEFINED = 0,
        MOTION_SWITCH,
        MOTION_JUMP,
        MOTION_SMOOTH,
        MOTION_ELASTIC,
    };
    Q_ENUM(EClockMotionTypes)

    static void registerClockEnumsToQML()
    {
        qmlRegisterType<CClockEnum>("com.harman.qml.clockenum", 1, 0, "ClockEnum");
    }
};

Q_DECLARE_METATYPE(CClockEnum::EClockLayoutTypes)
Q_DECLARE_METATYPE(CClockEnum::EClockMotionTypes)

#endif // CCLOCKENUM_H

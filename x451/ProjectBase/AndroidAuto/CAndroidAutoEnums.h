/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAndroidAutoEnums.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition for Enums class of AndroidAuto,
* This declares all the enums related to AndroidAuto and register all enums to
* qt meta system to use in qml.
*/

#ifndef CANDROIDAUTOENUMS_H
#define CANDROIDAUTOENUMS_H

#include <QObject>
#include <QtQml>

/**
 * @class CAndroidAutoEnums
 * @brief The CAndroidAutoEnums class declares all the enums related to
 *        AndroidAuto and register all enums to qt meta system to use in qml.
 */
class CAndroidAutoEnums: public QObject
{
    Q_OBJECT
public:

    /**
     * @brief The EAAMediaPlayState enum: This enum holds the constants for
     *        Android Auto Media Play State.
     */
    enum EAAMediaPlayState
    {
        EN_AA_MEDIA_PLAY_STATE_UNKNOWN,
        EN_AA_MEDIA_PLAY_STATE_STOPPED,
        EN_AA_MEDIA_PLAY_STATE_PLAYING,
        EN_AA_MEDIA_PLAY_STATE_PAUSED,
    };
    Q_ENUM(EAAMediaPlayState)

    /**
     * @brief The EAANaviNextTurnSideType enum: This enum holds the Android Auto Navigation
     * Next Turn side type.
     */
    enum EAANaviNextTurnSideType
    {
        EN_AA_NEXT_TURN_SIDE_TYPE_LEFT = 1,
        EN_AA_NEXT_TURN_SIDE_TYPE_RIGHT,
        EN_AA_NEXT_TURN_SIDE_TYPE_UNSPECIFIED,
    };
    Q_ENUM(EAANaviNextTurnSideType)

    /**
     * @brief The EAANaviNextTurnEvent enum: This enum holds the Android Auto Navigation
     * Next Turn Event type.
     */
    enum EAANaviNextTurnEvent
    {
        EN_AA_NEXT_TURN_EVENT_UNKNOWN=0,
        EN_AA_NEXT_TURN_EVENT_DEPART = 1,
        EN_AA_NEXT_TURN_EVENT_NAME_CHANGE = 2,
        EN_AA_NEXT_TURN_EVENT_SLIGHT_TURN = 3,
        EN_AA_NEXT_TURN_EVENT_TURN = 4,
        EN_AA_NEXT_TURN_EVENT_SHARP_TURN = 5,
        EN_AA_NEXT_TURN_EVENT_U_TURN = 6,
        EN_AA_NEXT_TURN_EVENT_ON_TURN = 7,
        EN_AA_NEXT_TURN_EVENT_OFF_RAMP = 8,
        EN_AA_NEXT_TURN_EVENT_FORK = 9,
        EN_AA_NEXT_TURN_EVENT_MERGE = 10,
        EN_AA_NEXT_TURN_EVENT_ROUND_ABOUT_ENTER = 11,
        EN_AA_NEXT_TURN_EVENT_ROUND_ABOUT_EXIT = 12,
        EN_AA_NEXT_TURN_EVENT_ENTER_AND_EXIT = 13,
        EN_AA_NEXT_TURN_EVENT_STRAIGHT = 14,
        EN_AA_NEXT_TURN_EVENT_FERRY_BOAT = 16,
        EN_AA_NEXT_TURN_EVENT_FERRY_TRAIN = 17,
        EN_AA_NEXT_TURN_EVENT_DESTINATION = 19,
    };
    Q_ENUM(EAANaviNextTurnEvent)

    /**
     * @brief The EAANaviNextTurnDistanceUnit enum: This enum holds the Android Auto Navigation
     * Distnace Unit type.
     */
    enum EAANaviNextTurnDistanceUnit
    {
        EN_AA_NEXT_TURN_DISTANCE_UNIT_UNKNOWN=0,
        EN_AA_NEXT_TURN_DISTANCE_UNIT_METERS,
        EN_AA_NEXT_TURN_DISTANCE_UNIT_KILOMETERS,
        EN_AA_NEXT_TURN_DISTANCE_UNIT_KILOMETERS_P1,
        EN_AA_NEXT_TURN_DISTANCE_UNIT_MILES,
        EN_AA_NEXT_TURN_DISTANCE_UNIT_MILES_P1,
        EN_AA_NEXT_TURN_DISTANCE_UNIT_FEET,
        EN_AA_NEXT_TURN_DISTANCE_UNIT_YARDS,
    };
    Q_ENUM(EAANaviNextTurnDistanceUnit)

    /**
     * @brief The EAANaviRoundAboutTurnNumber enum: This enum holds the Android Auto Navigation
     * Round About turn number.
     */
    enum EAANaviRoundAboutTurnNumber
    {
        EN_AA_ROUND_ABOUT_TURN_NUMBER_UNKNOWN=0,
        EN_AA_ROUND_ABOUT_TURN_NUMBER_ONE,
        EN_AA_ROUND_ABOUT_TURN_NUMBER_TWO,
        EN_AA_ROUND_ABOUT_TURN_NUMBER_THREE,
        EN_AA_ROUND_ABOUT_TURN_NUMBER_FOUR,
        EN_AA_ROUND_ABOUT_TURN_NUMBER_FIVE,
        EN_AA_ROUND_ABOUT_TURN_NUMBER_SIX,
        EN_AA_ROUND_ABOUT_TURN_NUMBER_SEVEN,
        EN_AA_ROUND_ABOUT_TURN_NUMBER_EIGHT,
    };
    Q_ENUM(EAANaviRoundAboutTurnNumber)

    /**
     * @brief The EAANaviRoundAboutTurnAngle enum: This enum holds the Android Auto Navigation
     * Round About turn Angle.
     */
    enum EAANaviRoundAboutTurnAngle
    {
        EN_AA_ROUND_ABOUT_TURN_ANGLE_UNKNOWN = 0,
        EN_AA_ROUND_ABOUT_TURN_ANGLE_45 = 45,
        EN_AA_ROUND_ABOUT_TURN_ANGLE_90 = 90,
        EN_AA_ROUND_ABOUT_TURN_ANGLE_135 = 135,
        EN_AA_ROUND_ABOUT_TURN_ANGLE_180 = 180,
        EN_AA_ROUND_ABOUT_TURN_ANGLE_225 = 225,
        EN_AA_ROUND_ABOUT_TURN_ANGLE_270 = 270,
        EN_AA_ROUND_ABOUT_TURN_ANGLE_315 = 315,
        EN_AA_ROUND_ABOUT_TURN_ANGLE_360 = 360,
    };
    Q_ENUM(EAANaviRoundAboutTurnAngle)

    /**
     * @brief registerAndroidAutoEnumsToQML function to register enums to QML.
     */
    static void registerAndroidAutoEnumsToQML()
    {
        qmlRegisterType<CAndroidAutoEnums>("com.harman.qml.androidautoenums",1,0,"AndroidAutoEnums");
    }
};

Q_DECLARE_METATYPE(CAndroidAutoEnums::EAAMediaPlayState)
Q_DECLARE_METATYPE(CAndroidAutoEnums::EAANaviNextTurnSideType)
Q_DECLARE_METATYPE(CAndroidAutoEnums::EAANaviNextTurnEvent)
Q_DECLARE_METATYPE(CAndroidAutoEnums::EAANaviNextTurnDistanceUnit)
Q_DECLARE_METATYPE(CAndroidAutoEnums::EAANaviRoundAboutTurnNumber)
Q_DECLARE_METATYPE(CAndroidAutoEnums::EAANaviRoundAboutTurnAngle)

#endif // CANDROIDAUTOENUMS_H

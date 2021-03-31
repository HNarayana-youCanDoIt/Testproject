/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CTunerEnums.h
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * CTunerEnums,   This enum class will be used to declare all required ENUM for tuner Application layer and QML layer also.
 **/

#ifndef CTUNERENUMS_H
#define CTUNERENUMS_H

#include <QObject>
#include <QtQml>

/**
 * @brief The CTunerEnums class
 * The class will be used to declare all required ENUM for tuner Application layer and QML layer also.
**/

class CTunerEnums: public QObject
{
    Q_OBJECT
public:

    /**
     * @enum    ETunerSeekType
     * @brief   Enum for type of tuner seek(Autoseek, Scan and Autostore) and will be used to set
     *          the seek type when user request seek.
     */
    enum ETunerSeekType
    {
        SEEK_INVALID            = -1,
        SEEK_NONE,
        SEEK_MANUAL_UP,
        SEEK_MANUAL_DOWN,
        SEEK_AUTOSEEK_UP,
        SEEK_AUTOSEEK_DOWN,
        SEEK_ENDLESS_UP,
        SEEK_ENDLESS_DOWN,
        SEEK_SCAN_UP,
        SEEK_SCAN_SKIP_UP,
        SEEK_SCAN_DOWN,
        SEEK_SCAN_SKIP_DOWN,
        SEEK_FULL_AUTOSTORE,
        SEEK_FULL_BACKGROUND,
        SEEK_MANUAL,
    };
    Q_ENUMS(ETunerSeekType)

    /**
     * @enum    ETunerBand
     * @brief   Enum for type of band(AM/FM) will be used to check Band Type.
     */
    enum ETunerBand
    {
        BAND_INVALID            = 0,
        BAND_FM                 = 1,
        BAND_AM                 = 4,
    };
    Q_ENUMS(ETunerBand)


    /**
     * @enum    ETunerOptionListIndex
     * @brief   Enum for tuner option screen's available options.
     */
    enum ETunerOptionListIndex
    {
        TUNER_OPTION_INVALID_INDEX = -1,
        TUNER_OPTION_AUTOSTORE_INDEX,
        TUNER_OPTION_SCAN_INDEX,
    };
    Q_ENUMS(ETunerOptionListIndex)

    /**
     * @enum    ETunerScreens
     * @brief   Enum for tuner module's screen
     */
    enum ETunerScreens
    {
        TUNER_SCREEN_INVALID = -1,
        TUNER_SCREEN_OPTION,
        TUNER_SCREEN_PRESET_LIST,
    };
    Q_ENUMS(ETunerScreens)

    /**
     * @enum    EManualSeekChangeType
     * @brief   Enum for manual seek change type
     */
    enum EManualSeekChangeType
    {
        CHANGE_INVALID = -1,
        CHANGE_BY_DRAG,
        CHANGE_BY_CLICK,
        CHANGE_BY_ROTARY,
    };
    Q_ENUMS(EManualSeekChangeType)

    /**
     * @enum    ETunerSCTState
     * @brief   Enum for Tuner SCT states
     */
    enum ETunerSCTState
    {
        TUNER_SCT_STATE_INVALID     = -1,
        TUNER_SCT_STATE_DEFAULT,
        TUNER_SCT_STATE_AUTOSEEK_UP,
        TUNER_SCT_STATE_AUTOSEEK_DOWN,
        TUNER_SCT_STATE_AUTOSTORE,
        TUNER_SCT_STATE_SCAN
    };
    Q_ENUMS(ETunerSCTState)

    /**
     * @brief registerTunerEnumsToQML function to register enums to QML.
     */
    static void registerTunerEnumsToQML()
    {
        qmlRegisterType<CTunerEnums>("com.harman.qml.tunerenums",1,0,"TunerEnums");
    }
};

Q_DECLARE_METATYPE(CTunerEnums::ETunerSeekType)
Q_DECLARE_METATYPE(CTunerEnums::ETunerBand)
Q_DECLARE_METATYPE(CTunerEnums::ETunerOptionListIndex)
Q_DECLARE_METATYPE(CTunerEnums::ETunerScreens)
Q_DECLARE_METATYPE(CTunerEnums::ETunerSCTState)
Q_DECLARE_METATYPE(CTunerEnums::EManualSeekChangeType)

#endif // CTUNERENUMS_H



/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CRCAEnums.h
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* CHVACEnum     Class that would contain all the Enums related to RCA
*               that would also be registered as a QML type so that these can be used in QML too
*/

#ifndef CRCAENUMS_H
#define CRCAENUMS_H

#include <QObject>
#include <QtQml>

// const literals

/**
 * @class CRCAEnums
 * @brief Class that would contain all the Enums related to RCA
 *        that would also be registered as a QML type so that these can be used in QML too
 */
class CRCAEnums : public QObject
{
    Q_OBJECT

public:

    /**
     * @enum ERCAActionInitiated
     * @brief Enum for RCA actions initiated from app
     */
    enum ERCAActionInitiated
    {
        RCA_NO_ACTION               = -1,
        RCA_BASS_UPDATED            = 0,
        RCA_MIDDLE_UPDATED          = 1,
        RCA_TREBLE_UPDATED          = 2,
        RCA_PRESET_UPDATED          = 3,
        RCA_BALANCEFADER_UPDATED    = 4,
        RCA_VIDEO_PLAYED            = 5,
        RCA_PICTURE_SELECTED        = 6,
        RCA_AUX_GAIN_UPDATED        = 7
    };
    Q_ENUM(ERCAActionInitiated)

    /**
     * @brief registerRCAEnumsToQML: Method to register CRCAEnum as a QML type
     */
    static void registerRCAEnumsToQML()
    {
        qmlRegisterType<CRCAEnums>("com.harman.qml.rcaenums",1,0,"RCAEnums");
    }
};

Q_DECLARE_METATYPE(CRCAEnums::ERCAActionInitiated)

#endif // CRCAENUM_H

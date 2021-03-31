/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CDoodleEnum.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleEnum, file that contain enums that will be used in Doodle.
 * Enums defined in this class are accessible in QML.
 */
//________________________________________________________________________________________________
#ifndef CDOODLEENUM_H
#define CDOODLEENUM_H

#include <QObject>
#include <QtQml>

//________________________________________________________________________________________________
/**
 * @brief   CDoodleEnum: Class to maintain all enums required for Doodle module.
 * Enums defined in this class are accessible in QML.
 */
class CDoodleEnum: public QObject
{
    Q_OBJECT
public:

    //________________________________________________________________________________________________
    /**
     * @enum    EDoodleSetupElementTypes
     * @brief   Enums for doodle setup list element types
     */
    enum EDoodleSetupElementTypes
    {
        DOODLE_SETUP_UNKNOWN = -1,
        DOODLE_SETUP_MY_STICKER,
        DOODLE_SETUP_MY_STICKER_ACTIVATE,
        DOODLE_SETUP_MY_STICKER_PREVIEW,
        DOODLE_SETUP_MY_STICKER_CLEAR,
        DOODLE_SETUP_STARTUP_IMAGE,
        DOODLE_SETUP_STARTUP_IMAGE_ACTIVATE,
        DOODLE_SETUP_STARTUP_IMAGE_PREVIEW,
        DOODLE_SETUP_STARTUP_IMAGE_CLEAR,
        DOODLE_SETUP_TOTAL_COUNT
    };
    Q_ENUMS(EDoodleSetupElementTypes)

    //________________________________________________________________________________________________
    /**
     * @brief   registerDoodleEnumsToQML: static method to register enums with QML.
     */
    static void registerDoodleEnumsToQML()
    {
        qmlRegisterType<CDoodleEnum>("com.harman.qml.doodleenums",1,0,"DoodleEnums");
    }

    //________________________________________________________________________________________________
};

//________________________________________________________________________________________________
/**
 * @brief   to declare enums with QML.
 */
Q_DECLARE_METATYPE(CDoodleEnum::EDoodleSetupElementTypes)
//________________________________________________________________________________________________

#endif // CDOODLEENUM_H

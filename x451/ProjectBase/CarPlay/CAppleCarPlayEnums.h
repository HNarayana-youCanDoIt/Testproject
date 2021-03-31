/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlayEnums.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition for Enums class of AppleCarPlay,
* This declares all the enums related to AppleCarPlay and register all enums to
* qt meta system to use in qml.
*/

#ifndef CAPPLECARPLAYENUMS_H
#define CAPPLECARPLAYENUMS_H

#include <QObject>
#include <QtQml>

/**
 * @class CAppleCarPlayEnums
 * @brief The CAppleCarPlayEnums class declares all the enums related to
 *        AppleCarPlay and register all enums to qt meta system to use in qml.
 */
class CAppleCarPlayEnums: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief registerAppleCarPlayEnumsToQML function to register enums to QML.
     */
    static void registerAppleCarPlayEnumsToQML()
    {
        qmlRegisterType<CAppleCarPlayEnums>("com.harman.qml.carplayenums", 1, 0, "AppleCarPlayEnums");
    }
};

#endif // CAPPLECARPLAYENUMS_H

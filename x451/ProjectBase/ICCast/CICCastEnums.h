/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CICCastEnum.h
* @ingroup      HMIComponent
* @author       Rajat Gupta
* CICCastEnum   Class that would contain all the Enums related to IC Cast
*               that would also be registered as a QML type so that these can be used in QML too
**/

#ifndef CICCASTENUMS_H
#define CICCASTENUMS_H

#include <QObject>
#include <QtQml>

class CICCastEnums : public QObject
{
    Q_OBJECT

public:

    /**
     * @enum EICCastFeature
     * @brief Enum for IC Cast Component that needs to be casted.
     */
    enum EICCastFeature
    {
        ICRENDER_CAST_MASTER = 1,
        ICRENDER_CAST_RADIO = 2,
        ICRENDER_CAST_MEDIA = 3,
    };
    Q_ENUM(EICCastFeature)

    enum  EICCastCallStatus {
        SUCCESS = 0,
        OUT_OF_MEMORY,
        NOT_AVAILABLE,
        CONNECTION_FAILED,
        REMOTE_ERROR,
        UNKNOWN,
        INVALID_VALUE,
        SUBSCRIPTION_REFUSED
    };
    Q_ENUM(EICCastCallStatus)

    /**
     * @brief registerICCastEnumsToQML Method to register CICCastEnum as a QML type
     */
    static void registerICCastEnumToQML()
    {
        qmlRegisterType<CICCastEnums>("com.harman.qml.iccastenums",1,0,"ICCastEnum");
    }
};

Q_DECLARE_METATYPE(CICCastEnums::EICCastFeature)
Q_DECLARE_METATYPE(CICCastEnums::EICCastCallStatus)

#endif // CICCASTENUMS_H

/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDateAndTimeEnums.h
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CDateAndTimeEnums, file that contain enums that will be used in Date And Time.
 */
#ifndef CDATEANDTIMEENUMS_H
#define CDATEANDTIMEENUMS_H

#include <QObject>
#include <QtQml>

class CDateAndTimeEnums: public QObject
{
    Q_OBJECT
public:


    /**
     * @brief The ETimeFormat enum: Contains the time format types.
     */
    enum ETimeFormat {
        TIME_FORMAT_DEFAULT = 0,
        TIME_FORMAT_12_HR = 1,
        TIME_FORMAT_24_HR = 2
    };
    Q_ENUMS(ETimeFormat)

    enum ECallStatus {
        SUCCESS,
        OUT_OF_MEMORY,
        NOT_AVAILABLE,
        CONNECTION_FAILED,
        REMOTE_ERROR,
        UNKNOWN,
        INVALID_VALUE,
        SUBSCRIPTION_REFUSED
    };
    Q_ENUMS(ECallStatus)

    //________________________________________________________________________________________________

    static void registerDateAndTimeEnumsToQML()
    {
        qmlRegisterType<CDateAndTimeEnums>("com.harman.qml.dateandtimeenums",1,0,"DateAndTimeEnums");
    }
};

Q_DECLARE_METATYPE(CDateAndTimeEnums::ETimeFormat)
Q_DECLARE_METATYPE(CDateAndTimeEnums::ECallStatus)

#endif // CDATEANDTIMEENUMS_H

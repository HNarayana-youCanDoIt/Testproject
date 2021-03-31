/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDiagnosticEnum.h
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CDiagnosticEnum, file that contain enums that will be used in Diagnostic.
 */

#ifndef CDIAGNOSTICENUM_H
#define CDIAGNOSTICENUM_H

#include <QObject>
#include <QtQml>

class CDiagnosticEnum: public QObject
{
    Q_OBJECT
public:

    /**
     * @enum EConnectionStatus
     * @brief Enum to check the connection status for parameters related to Diagnostic
     */
    enum EConnectionStatus
    {
        INVALID = -1,
        DISCONNECTED = 0,
        CONNECTED = 1,
        UNKNOWN = 2,
    };
    Q_ENUMS(EConnectionStatus)
    //________________________________________________________________________________________________

    static void registerDiagnosticEnumsToQML()
    {
        qmlRegisterType<CDiagnosticEnum>("com.harman.qml.diagnosticenums",1,0,"DiagnosticEnums");
    }
};

Q_DECLARE_METATYPE(CDiagnosticEnum::EConnectionStatus)

#endif // CDIAGNOSTICENUM_H

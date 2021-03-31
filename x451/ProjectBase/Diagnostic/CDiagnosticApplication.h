/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDiagnosticApplication.h
 * @ingroup         HMIComponent
 * @author          Manali Patil
 * CDiagnosticApplication, an Application for Diagnostic module,
 * CDiagnosticApplication act as mediator between QML and Statemachine.
 */

#ifndef CDIAGNOSTICAPPLICATION_H
#define CDIAGNOSTICAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"

class CDiagnosticAdaptor;
class CDiagnosticEventHandler;

/**
 * @brief The CDiagnosticApplication class: This class contains all the functionality related to Diagnostic module
 *          creates instances for CDiagnosticEventHandler and CDiagnosticAdaptor
 */
class CDiagnosticApplication : public QObject
{
public:
    /**
    * @brief	CDiagnosticApplication - Constructor for application class CDiagnosticApplication
    * @param	pParent: Parent class pointer
    * @return	void.
    **/
    CDiagnosticApplication(QObject* pParent = nullptr);

    /**
    * @brief	~CDiagnosticApplication - Destructor for application class CDiagnosticApplication
    * @param	void.
    * @return	void.
    **/
    ~CDiagnosticApplication();

private:
    /**
     * @brief m_pDiagnosticEventHandler: Instance of CDiagnosticEventHandler class
     */
    CDiagnosticEventHandler* m_pDiagnosticEventHandler;
};

#endif // CDIAGNOSTICAPPLICATION_H

/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CVersionManagerApplication.h
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CVersionManagerApplication, an Application for Version Manager module,
 * CVersionManagerApplication act as mediator between QML and Statemachine.
 */

#ifndef CVERSIONMANAGERAPPLICATION_H
#define CVERSIONMANAGERAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"

class CVersionManagerAdaptor;
class CVersionManagerEventHandler;

/**
 * @brief The CVersionManagerApplication class: This class contains all the functionality related to Version Manager module
 *          creates instances for CVersionManagerEventHandler and CVersionManagerAdaptor
 */
class CVersionManagerApplication : public QObject
{
public:
    /**
    * @brief	CVersionManagerApplication - Constructor for application class CVersionManagerApplication
    * @param	QObject
    * @return	void.
    **/
    CVersionManagerApplication(QObject* parent = nullptr);

    /**
    * @brief	~CVersionManagerApplication - Destructor for application class CVersionManagerApplication
    * @param	void.
    * @return	void.
    **/
    ~CVersionManagerApplication();

private:
    /**
     * @brief m_pVersionManagerEventHandler, Instance of CVersionManagerEventHandler class
    **/

    CVersionManagerEventHandler* m_pVersionManagerEventHandler;

};

#endif // CVERSIONMANAGERAPPLICATION_H

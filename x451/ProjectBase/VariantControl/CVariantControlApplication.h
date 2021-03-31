/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CVariantControlApplication.h
 * @ingroup         HMIComponent
 * @author          Manali Patil
 * CVariantControlApplication, an Application for VariantControl module,
 * CVariantControlApplication act as mediator between QML and Statemachine.
 */

#ifndef CVARIANTCONTROLAPPLICATION_H
#define CVARIANTCONTROLAPPLICATION_H

#include <QObject>
#include "HMIIncludes.h"

class CVariantControlAdaptor;
class CVariantControlEventHandler;

/**
 * @brief The CVariantControlApplication class: This class contains all the functionality related to VariantControl module
 *          creates instances for CVariantControlEventHandler and CVariantControlAdaptor
 */
class CVariantControlApplication : public QObject
{
public:
    /**
    * @brief	CVariantControlApplication - Constructor for application class CVariantControlApplication
    * @param	pParent: parent class pointer.
    * @return	void.
    **/
    CVariantControlApplication(QObject* pParent = nullptr);

    /**
    * @brief	~CVariantControlApplication - Destructor for application class CVariantControlApplication
    * @param	void.
    * @return	void.
    **/
    ~CVariantControlApplication();

private:

    /**
     * @brief m_pVariantControlEventHandler: Instance of CVariantControlEventHandler class
     */
    CVariantControlEventHandler* m_pVariantControlEventHandler;
};

#endif // CVARIANTCONTROLAPPLICATION_H

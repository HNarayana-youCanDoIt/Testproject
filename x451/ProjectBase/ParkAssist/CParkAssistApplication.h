/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CParkAssistApplication.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CParkAssistApplication.h, park assist module application header file, contains all the functionality related to park assist module
 *          creates instances for CParkAssistEventHandler & CParkAssistSM and raises events SM
 */

#ifndef CPARKASSISTAPPLICATION_H
#define CPARKASSISTAPPLICATION_H

#include <QObject>
#include "CBaseApplication.h"
#include "StateMachine_TML_HMI_SM.h"
#include "CParkAssistEnums.h"

class CParkAssistSM;
class CParkAssistAdaptor;
class CParkAssistEventHandler;

/**
 * @brief The CParkAssistApplication class: This class contains all the functionality related to park assist module
 *          creates instances for CAudioEventHandler & CParkAssistSM and raises events SM
 */
class CParkAssistApplication : public CBaseApplication
{
    Q_OBJECT

public:

    /**
    * @brief	CParkAssistApplication - Constructor for application class CParkAssistApplication.
    * @param	QQuickItem.
    * @return	NA.
    **/
    CParkAssistApplication(QQuickItem* parent = nullptr);

    /**
    * @brief	~CParkAssistApplication - Destructor for application class CParkAssistApplication.
    * @param	NA.
    * @return	NA.
    **/
    ~CParkAssistApplication();

    /**
    * @brief	onCreated - Method is called when the QML is loaded successfully, this is CBaseApplication method
    * @param	QQuickItem.
    * @return	void.
    **/
    virtual void onCreated(QQuickItem* rootObject);

    /**
     * @brief	displayScreenPdcRvc: This method displays park assist screen based on park assist variant.
     * @param	void.
     * @return	void.
     **/
    void displayScreenPdcRvc();

private slots:

    /**
     * @brief sltSetHMINotification slot is called to propagate the setHMINotification to the resource layer
     * @param void
     * @return void
     */
    void sltSetHMINotification();

private:

    /* Instance of CParkAssistSM class */
    CParkAssistSM* m_pParkAssistSM;

    /* Instance of CParkAssistAdaptor class */
    CParkAssistAdaptor *m_pParkAssistAdaptor;

    /* Instance of CParkAssistEventHandler class */
    CParkAssistEventHandler *m_pParkAssistEventHandler;
};

#endif // CPARKASSISTAPPLICATION_H

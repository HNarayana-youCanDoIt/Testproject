/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDriveNextApplication.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDriveNextApplication, an Application for DriveNext module,
 * CDriveNextApplication act as mediator between QML and State-machine.
 */

#ifndef CDRIVENEXTAPPLICATION_H
#define CDRIVENEXTAPPLICATION_H

#include <QObject>
#include "CBaseApplication.h"

class CDriveNextAdaptor;
class CDriveNextEventHandler;
class CDriveNextSM;

class CDriveNextApplication : public CBaseApplication
{
public:
    /**
    * @brief	CDriveNextApplication::CDriveNextApplication constructor for application class CDriveNextApplication.
    * @param	QObject.
    * @return	NA.
    **/
    CDriveNextApplication(QQuickItem* parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextApplication::~CDriveNextApplication is destructor of application class CDriveNextApplication
    * @param	NA.
    * @return	NA.
    **/
    ~CDriveNextApplication();
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextApplication::onCreated is CDriveNextApplication method
    * @param	QQuickItem.
    * @return	void.
    **/
    virtual void onCreated(QQuickItem* rootObject);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextApplication::raiseSMEvent is CDriveNextApplication method
    * @param	QString, QVariant.
    * @return	void.
    **/
    void raiseSMEvent(const QString & name,const QVariant & data);
    //________________________________________________________________________________________________
    /**
    * @brief	CDriveNextApplication::getDriveNextAdaptor is function to get shared pointer of CDriveNextAdaptor
    * @param	void.
    * @return	CDriveNextAdaptor*. shared pointer for CDriveNextAdaptor class
    **/
    static CDriveNextAdaptor* getDriveNextAdaptor();
    //________________________________________________________________________________________________
private:
    static CDriveNextApplication* m_pInstance;                  // used to hold current object of CDriveNextApplication class
    QSharedPointer<CDriveNextAdaptor> m_spDriveNextAdaptor;     //Qt Shared poilter for CDriveNextAdaptor class
    CDriveNextEventHandler* mpDriveNextDataEventHandler;        // Refrence to DriveNext data handler instance
    CDriveNextSM* mpDriveNextSM;                                // Refrence to DriveNext state machine instance
    //________________________________________________________________________________________________
};

#endif // CDRIVENEXTAPPLICATION_H

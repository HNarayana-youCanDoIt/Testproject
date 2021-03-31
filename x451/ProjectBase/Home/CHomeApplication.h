/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHomeApplication.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CHomeApplication, an Application for Home module,
 * CHomeApplication act as mediator between QML and Statemachine.
 */

#ifndef CHOMEAPPLICATION_H
#define CHOMEAPPLICATION_H

#include <QObject>
#include "CBaseApplication.h"

class CHomeAdaptor;
class CHomeEventHandler;
class CHomeSM;

/**
 * @brief CHomeApplication, an Application for Home module,
 * It act as mediator between QML and Statemachine.
 */
class CHomeApplication : public CBaseApplication
{
public:
    /**
    * @brief	CHomeApplication::CHomeApplication constructor for application class CHomeApplication.
    * @param	QObject.
    * @return	NA.
    **/
    CHomeApplication(QQuickItem* parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeApplication::~CHomeApplication is destructor of application class CHomeApplication
    * @param	NA.
    * @return	NA.
    **/
    ~CHomeApplication();
    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::onCreated is CBaseApplication method
    * @param	QQuickItem.
    * @return	void.
    **/
    virtual void onCreated(QQuickItem* rootObject);
    //________________________________________________________________________________________________
    /**
    * @brief	CDHomeShortcut::raiseSMEvent is CBaseApplication method
    * @param	QString, QVariant.
    * @return	void.
    **/
    void raiseSMEvent(const QString & name,const QVariant & data);
    //________________________________________________________________________________________________
private:
    CHomeAdaptor& mHomeAdaptor;                     // refrence to home adaptor instance
    CHomeEventHandler* mpHomeDataEventHandler;      // refrence to home data handler instance
    CHomeSM* mpHomeSM;                              // refrence to home state machine instance
    //________________________________________________________________________________________________
};

#endif // CHOMEAPPLICATION_H

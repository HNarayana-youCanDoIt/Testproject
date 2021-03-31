/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CW3WApplication.h
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CW3WApplication, an Application for W3W module,
 * CW3WApplication act as mediator between QML and State-machine.
 */

#ifndef CW3WAPPLICATION_H
#define CW3WAPPLICATION_H

#include <QObject>
#include "CBaseApplication.h"

class CW3WAdaptor;
class CW3WEventHandler;
class CW3WSM;

class CW3WApplication : public CBaseApplication
{
public:
    /**
    * @brief	CW3WApplication::CW3WApplication constructor for application class CW3WApplication.
    * @param	QObject.
    * @return	NA.
    **/
    CW3WApplication(QQuickItem* parent = nullptr);

    /**
    * @brief	CW3WApplication::~CW3WApplication is destructor of application class CW3WApplication
    * @param	NA.
    * @return	NA.
    **/
    ~CW3WApplication();

    /**
    * @brief	CW3WApplication::onCreated is CW3WApplication method
    * @param	QQuickItem.
    * @return	void.
    **/
    virtual void onCreated(QQuickItem* rootObject);

    /**
    * @brief	CW3WApplication::raiseSMEvent is CW3WApplication method
    * @param	QString, QVariant.
    * @return	void.
    **/
    void raiseSMEvent(const QString & name,const QVariant & data);

    /**
    * @brief	CW3WApplication::getW3WAdaptor is function to get shared pointer of CW3WAdaptor
    * @param	void.
    * @return	CW3WAdaptor*. shared pointer for CW3WAdaptor class
    **/
    static CW3WAdaptor* getW3WAdaptor();

private:
    /* used to hold current object of CW3WApplication class */
    static CW3WApplication* m_pInstance;
    /* Qt Shared poilter for CW3WAdaptor class */
    QSharedPointer<CW3WAdaptor> m_spW3WAdaptor;
    /* Pointer to W3W data handler instance */
    CW3WEventHandler* mpW3WDataEventHandler;
    /* Pointer to W3W state machine instance */
    CW3WSM* mpW3WSM;
};

#endif // CW3WAPPLICATION_H

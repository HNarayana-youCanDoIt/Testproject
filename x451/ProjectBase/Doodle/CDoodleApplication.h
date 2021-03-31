/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDoodleApplication.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleApplication, an Application for Doodle module,
 * This class act as mediator between QML and State-machine.
 */
//________________________________________________________________________________________________
#ifndef CDOODLEAPPLICATION_H
#define CDOODLEAPPLICATION_H

#include <QObject>
#include "CBaseApplication.h"

class CDoodleAdaptor;
class CDoodleEventHandler;
class CDoodleSM;

//________________________________________________________________________________________________
/**
 * @brief CDoodleApplication, an Application class for Doodle module.
 * This class act as mediator between QML and State-machine.
 */
class CDoodleApplication : public CBaseApplication
{

public:

    /**
    * @brief    CDoodleApplication::CDoodleApplication constructor for application class CDoodleApplication.
    * @param    QObject.
    * @return   NA.
    **/
    CDoodleApplication(QQuickItem* parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleApplication::~CDoodleApplication is destructor of application class CDoodleApplication
    * @param    NA.
    * @return   NA.
    **/
    ~CDoodleApplication();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleApplication::onCreated is CDoodleApplication method
    * @param    QQuickItem.
    * @return   void.
    **/
    virtual void onCreated(QQuickItem* rootObject);
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleApplication::raiseSMEvent is CDoodleApplication method
    * @param    QString, QVariant.
    * @return   void.
    **/
    void raiseSMEvent(const QString & name,const QVariant & data);
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleApplication::getDoodleAdaptor is function to get shared pointer of CDoodleAdaptor
    * @param    void.
    * @return   CDoodleAdaptor*. shared pointer for CDoodleAdaptor class
    **/
    static CDoodleAdaptor* getDoodleAdaptor();
    //________________________________________________________________________________________________

private:

    //// m_pInstance: pointer to CDoodleApplication class instance.
    static CDoodleApplication* m_pInstance;

    //// m_spDoodleAdaptor: Qt Shared pointer to CDoodleAdaptor class instance.
    QSharedPointer<CDoodleAdaptor> m_spDoodleAdaptor;

    //// mpDoodleDataEventHandler: pointer to CDoodleEventHandler class instance.
    CDoodleEventHandler* mpDoodleDataEventHandler;

    //// mpDoodleSM: pointer to CDoodleSM class instance.
    CDoodleSM* mpDoodleSM;

    //________________________________________________________________________________________________
};

#endif // CDOODLEAPPLICATION_H

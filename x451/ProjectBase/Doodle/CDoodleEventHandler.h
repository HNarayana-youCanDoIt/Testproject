/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDoodleEventHandler.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDoodleEventHandler, a Resource handler for Doodle module,
 * CDoodleEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */
//________________________________________________________________________________________________
#ifndef CDOODLEEVENTHANDLER_H
#define CDOODLEEVENTHANDLER_H

#include <QObject>

//________________________________________________________________________________________________
/**
 * @brief CDoodleEventHandler, a Resource handler for Doodle module,
 * It act as mediator between adaptor and resource manager,
 * This listens signals raised by the resource layer provider class,
 * It has the implementation of the corresponding slots.
 */
class CDoodleEventHandler: public QObject
{
    Q_OBJECT

public:

    /**
    * @brief    CDoodleEventHandler::CDoodleEventHandler constructor for data handler class CDoodleEventHandler.
    * @param    QObject.
    * @return   NA.
    **/
    CDoodleEventHandler(QObject* parent = 0);
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleEventHandler::~CDoodleEventHandler is destructor of data handler class CDoodleEventHandler
    * @param    NA.
    * @return   NA.
    **/
    ~CDoodleEventHandler();
    //________________________________________________________________________________________________

private slots:

    /**
    * @brief    slotProxyStatusChanged slot catch by HMI module
    * to handle Proxy availability status
    * @param    void.
    * @return   void.
    */
    void slotProxyStatusChanged();
    //________________________________________________________________________________________________

private:

    /**
    * @brief    CDoodleEventHandler::connectSignals used to create connection for class CDoodleEventHandler
    * @param    void.
    * @return   void.
    **/
    void connectSignals();
    //________________________________________________________________________________________________
    /**
    * @brief    CDoodleEventHandler::disconnectSignals used to release connection for class CDoodleEventHandler
    * @param    void.
    * @return   void.
    **/
    void disconnectSignals();

    //________________________________________________________________________________________________
};

#endif // CDOODLEEVENTHANDLER_H

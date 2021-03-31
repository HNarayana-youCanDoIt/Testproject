/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CMediaOffEventHandler.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CMediaOffEventHandler, a Resource handler for Media Off module,
 * CMediaOffEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#ifndef CMEDIAOFFEVENTHANDLER_H
#define CMEDIAOFFEVENTHANDLER_H

#include <QObject>

class CMediaOffApplication;
class CMediaOffAdaptor;
class CMediaOffSM;

/**
 * @brief CMediaOffEventHandler, a Resource handler for Media Off module,
 * It act as mediator between adaptor and resource manager,
 * This listens signals raised by the resource layer provider class,
 * It has the implementation of the corresponding slots.
 */
class CMediaOffEventHandler: public QObject
{
    Q_OBJECT
public:
    /**
    * @brief	CMediaOffEventHandler::CMediaOffEventHandler constructor for data handler class CMediaOffEventHandler.
    * @param	QObject.
    * @return	NA.
    **/
    CMediaOffEventHandler(QObject* parent = 0);
    //________________________________________________________________________________________________
    /**
    * @brief	CMediaOffEventHandler::~CMediaOffEventHandler is destructor of data handler class CMediaOffEventHandler
    * @param	NA.
    * @return	NA.
    **/
    ~CMediaOffEventHandler();
    //________________________________________________________________________________________________
public slots:

    //________________________________________________________________________________________________
protected:

    //________________________________________________________________________________________________
private:
    void connectSignals();
    //________________________________________________________________________________________________
};

#endif // CMEDIAOFFEVENTHANDLER_H
/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHomeEventHandler.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CHomeEventHandler, a Resource handler for Home module,
 * CHomeEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#ifndef CHOMEEVENTHANDLER_H
#define CHOMEEVENTHANDLER_H

#include <QObject>

class CHomeApplication;
class CHomeAdaptor;
class CHomeSM;

/**
 * @brief CHomeEventHandler, a Resource handler for Home module,
 * It act as mediator between adaptor and resource manager,
 * This listens signals raised by the resource layer provider class,
 * It has the implementation of the corresponding slots.
 */
class CHomeEventHandler: public QObject
{
    Q_OBJECT
public:
    /**
    * @brief	CHomeEventHandler::CHomeEventHandler constructor for data handler class CHomeEventHandler.
    * @param	QObject.
    * @return	NA.
    **/
    CHomeEventHandler(QObject* parent = 0);
    //________________________________________________________________________________________________
    /**
    * @brief	CHomeEventHandler::~CHomeEventHandler is destructor of data handler class CHomeEventHandler
    * @param	NA.
    * @return	NA.
    **/
    ~CHomeEventHandler();
    //________________________________________________________________________________________________
public slots:
    // Declare the slots that would be invoked on the resource layer events signals
    // void sltHardKeyEvent(int eventType);
    // void sltUpdateDataType(int type);
    //________________________________________________________________________________________________
private:
    void connectSignals();
    //________________________________________________________________________________________________
};

#endif // CHOMEEVENTHANDLER_H
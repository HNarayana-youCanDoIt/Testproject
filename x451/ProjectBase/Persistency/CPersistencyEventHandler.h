/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CPersistencyEventHandler.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CPersistencyEventHandler, a Resource handler for Persistency service,
 * CPersistencyEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#ifndef CPERSISTENCYEVENTHANDLER_H
#define CPERSISTENCYEVENTHANDLER_H

#include <QObject>
#include <QSettings>
#include "PersistencyDef.h"

/**
 * @brief CPersistencyEventHandler, a Resource handler for Power System,
 * CPersistencyEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */
class CPersistencyEventHandler: public QObject
{
    Q_OBJECT
public:
    /**
    * @brief	CPersistencyEventHandler::CPersistencyEventHandler constructor for data handler class CPersistencyEventHandler.
    * @param	QObject.
    * @return	NA.
    **/
    CPersistencyEventHandler(QObject* parent = 0);
    //________________________________________________________________________________________________
    /**
    * @brief	CPersistencyEventHandler::~CPersistencyEventHandler is destructor of data handler class CPersistencyEventHandler
    * @param	NA.
    * @return	NA.
    **/
    ~CPersistencyEventHandler();
    //________________________________________________________________________________________________
private:
    /**
    * @brief	CPersistencyEventHandler::connectSignals is used to connect slot(s) with respective signals from resource
    * @param	void.
    * @return	void.
    **/
    void connectSignals();
    //________________________________________________________________________________________________
public:
    /**
    * @brief	CPersistencyEventHandler::readIntFromEarlyDataPersistency is used to read early data from Persistency
    * @param	unsigned long (unique id for data).
    * @return	QString (value for data).
    **/
    const QString readDataFromEarlyDataPersistency(unsigned long ubootID);
    //________________________________________________________________________________________________
    /**
    * @brief	CPersistencyEventHandler::readDataFromPersistency is used to read regular data from Persistency
    * @param	QString (Key for data).
    * @return	QString (value for data).
    **/
    QString readDataFromPersistency(QString qstrKey);
    //________________________________________________________________________________________________
    /**
    * @brief	CPersistencyEventHandler::WriteDataToPersistency is used to write data to Persistency
    * @param	QString (Key for data), QString (value for data)
    * @return	bool (write task successful status).
    **/
    bool WriteDataToPersistency(QString qstrKey, QString value);
    //________________________________________________________________________________________________
private:
#if defined(USE_SIMULATION_PERSISTENCY)
    QSettings* m_pSimulationPersistency;    // QT Simulation Persistency object
#endif // defined(USE_SIMULATION_PERSISTENCY)
};

#endif // CPERSISTENCYEVENTHANDLER_H

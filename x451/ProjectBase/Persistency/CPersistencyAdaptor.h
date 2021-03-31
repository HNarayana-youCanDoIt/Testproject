/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CPersistencyAdaptor.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CPersistencyAdaptor, an Adaptor for Persistency service,
 * CPersistencyAdaptor is singleton class used to read/write data information with persistency service.
 */

#ifndef CPERSISTENCYADAPTOR_H
#define CPERSISTENCYADAPTOR_H

#include "CPersistencyEventHandler.h"

class CDPersistencyKeyValue;

/**
 * @brief CPersistencyAdaptor, an Adaptor for Persistency module,
 * CPersistencyAdaptor is singleton class used to read/write data information with persistency module.
 */
class CPersistencyAdaptor : public QObject
{
    Q_OBJECT

public:
    // Adaptor related functions //
    /**
    * @brief	CPersistencyAdaptor::getInstance is static method used to get instance of singleton class CPersistencyAdaptor
    * @param	void.
    * @return	CPersistencyAdaptor.
    **/
    static CPersistencyAdaptor &getInstance();
    //________________________________________________________________________________________________
    /**
    * @brief	CPersistencyAdaptor::~CPersistencyAdaptor is destructor of singleton class CPersistencyAdaptor
    * @param	NA.
    * @return	NA.
    **/
    ~CPersistencyAdaptor();
    //________________________________________________________________________________________________
private:
    /**
    * @brief	CPersistencyAdaptor::CPersistencyAdaptor private constructor for singleton class CPersistencyAdaptor.
    * @param	QObject.
    * @return	NA.
    **/
    explicit CPersistencyAdaptor(QObject *parent = nullptr);
    //________________________________________________________________________________________________
    /**
    * @brief	CPersistencyAdaptor::validateDefaultPersistencyKeyValues is method used to Validate Default Persistency Key Values.
    * @param	void.
    * @return	void.
    **/
    void validateDefaultPersistencyKeyValues();
    //________________________________________________________________________________________________
public:
    // Persistency Service related functions //
    /**
    * @brief	CPersistencyAdaptor::readIntData is method used to read Int from Persistency data for given key.
    * @param	ePersistencyKeys (eKey for data).
    * @return	int (value for data).
    **/
    int readIntData(EPersistencyKeys eKey);
    //________________________________________________________________________________________________
    /**
    * @brief	CPersistencyAdaptor::writeIntData is method used to write Int to Persistency data for given key
    * @param	ePersistencyKeys (eKey for data), int (iValue for data).
    * @return	bool (write task successful status).
    **/
    bool writeIntData(EPersistencyKeys eKey, int iValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CPersistencyAdaptor::readFloatData is method used to read Float from Persistency data for given key.
    * @param	ePersistencyKeys (eKey for data).
    * @return	float (value for data).
    **/
    float readFloatData(EPersistencyKeys eKey);
    //________________________________________________________________________________________________
    /**
     * @brief CPersistencyAdaptor::writeFloatData is method used to write Float from Persistency data for given key.
     * @param ePersistencyKeys (eKey for data).
     * @param float (fValue for data).
     * @return bool (write task successful status).
     */
    bool writeFloatData(EPersistencyKeys eKey, float fValue);
    //________________________________________________________________________________________________
    /**
    * @brief	CPersistencyAdaptor::readStringData is method used to read String from Persistency data for given key.
    * @param	ePersistencyKeys (eKey for data).
    * @return	QString (value for data).
    **/
    QString readStringData(EPersistencyKeys eKey);
    //________________________________________________________________________________________________
    /**
    * @brief	CPersistencyAdaptor::writeStringData is method used to write String to Persistency data for given key
    * @param	ePersistencyKeys (eKey for data), QString (strValue for data).
    * @return	bool (write task successful status).
    **/
    bool writeStringData(EPersistencyKeys eKey, const QString &strValue);
    //________________________________________________________________________________________________
private:
    static CPersistencyAdaptor* m_pPersistencyAdaptor;      // used to maintain singleton class instance
    CPersistencyEventHandler* m_pCPersistencyEventHandler;  // used to communicate with PCL

    //map to hold Persistency Key Value and Types
    std::map<EPersistencyKeys, CDPersistencyKeyValue> m_mapKeyValueTypes;
};

#endif // CPERSISTENCYADAPTOR_H

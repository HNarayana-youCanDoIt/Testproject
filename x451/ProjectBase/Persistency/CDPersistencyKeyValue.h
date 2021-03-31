/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDPersistencyKeyValue.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDPersistencyKeyValue, a Data structure for Persistency module,
 * CDPersistencyKeyValue maintains key, value and updated-Date data information.
 */

#ifndef CDPERSISTENCYKEYVALUE_H
#define CDPERSISTENCYKEYVALUE_H

#include <QString>
#include "PersistencyDef.h"
#include "CHomeEnum.h"

/**
 * @brief CDPersistencyKeyValue, an data class for Persistency module,
 * CDPersistencyKeyValue is data class used to hold key value and types for Persistency.
 */
class CDPersistencyKeyValue
{
public:
    //____________________________________________________________________________
    /**
    * @brief    CDPersistencyKeyValue default constructor for CDPersistencyKeyValue class.
    * @param    void.
    * @return   NA.
    **/
    CDPersistencyKeyValue();
    //____________________________________________________________________________
    /**
    * @brief    CDPersistencyKeyValue parameterized constructor for CDPersistencyKeyValue class.
    * @param    enum Type,              EPersistencyKeys enum value for key.
    * @param    QString Key,            text for key.
    * @param    QString Default Value,  text for value.
    * @param    QString Update Version, text for last updated verdion.
    * @return   NA.
    **/
    CDPersistencyKeyValue(EPersistencyKeys eType, QString strKey, QString strDefValue, QString strUpdateVersion);
    //____________________________________________________________________________
    /**
    * @brief    getType getter for Persistency Key Value type.
    * @param    void.
    * @return   eType.
    **/
    EPersistencyKeys getType();
    //____________________________________________________________________________
    /**
    * @brief    getKey getter for Persistency Key Value key.
    * @param    void.
    * @return   string Key.
    **/
    QString getKey();
    //____________________________________________________________________________
    /**
    * @brief    getDefaultValue getter for Persistency Key Value default value.
    * @param    void.
    * @return   string Default Value.
    **/
    QString getDefaultValue();
    //____________________________________________________________________________
    /**
    * @brief    getUpdateVersion getter for Persistency Key Value update version.
    * @param    void.
    * @return   string last updated version.
    **/
    QString getUpdateVersion();
    //____________________________________________________________________________
private:
    //member variable to hold Persistency Key Value type
    EPersistencyKeys m_eType;

    //member variable to hold Persistency Key Value key
    QString m_strKey;

    //member variable to hold Persistency Key Value default value
    QString m_strDefValue;

    //member variable to hold Persistency Key Value last updated version value.
    QString m_strUpdateVersion;
};

#endif // CDPERSISTENCYKEYVALUE_H

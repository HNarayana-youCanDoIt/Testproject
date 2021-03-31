/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDPersistencyKeyValue.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDPersistencyKeyValue, a Data structure for Persistency module,
 * CDPersistencyKeyValue maintains key, value and updated-Date data information.
 */

#include "CDPersistencyKeyValue.h"
#include "logging.h"

//____________________________________________________________________________
CDPersistencyKeyValue::CDPersistencyKeyValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s", __FUNCTION__);
    m_eType = EPersistencyKeys::TOTAL_KEYS;
    m_strKey = "UNKNOWN";
    m_strDefValue = "UNKNOWN";
    m_strUpdateVersion = "UNKNOWN";
}
//____________________________________________________________________________
CDPersistencyKeyValue::CDPersistencyKeyValue(EPersistencyKeys eType, QString strKey, QString strDefValue, QString strUpdateVersion)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, eType:%d, strKey:%s, strDefValue:%s, strUpdateVersion:%s", __FUNCTION__, eType, strKey.toStdString().data(), strDefValue.toStdString().data(), strUpdateVersion.toStdString().data());
    m_eType = eType;
    m_strKey = strKey;
    m_strDefValue = strDefValue;
    m_strUpdateVersion = strUpdateVersion;
}
//____________________________________________________________________________
EPersistencyKeys CDPersistencyKeyValue::getType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, %d", __FUNCTION__, static_cast<int>(m_eType));
    return m_eType;
}
//____________________________________________________________________________
QString CDPersistencyKeyValue::getKey()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, %s", __FUNCTION__, m_strKey.toStdString().data());
    return m_strKey;
}
//____________________________________________________________________________
QString CDPersistencyKeyValue::getDefaultValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, %s", __FUNCTION__, m_strDefValue.toStdString().data());
    return m_strDefValue;
}
//____________________________________________________________________________
QString CDPersistencyKeyValue::getUpdateVersion()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, %s", __FUNCTION__, m_strUpdateVersion.toStdString().data());
    return m_strUpdateVersion;
}
//____________________________________________________________________________

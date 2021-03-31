/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CPersistencyEventHandler.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CPersistencyEventHandler, a Resource handler for Persistency service,
 * CPersistencyEventHandler act as mediator between adaptor and resource manager.
 * The class listens for the signals raised by the resource layer provider class.
 * It has the implementation of the corresponding slots.
 */

#include "CPersistencyEventHandler.h"
#include "logging.h"
#include "CFramework.h"
#include "CPersistencyAdaptor.h"
#include "VariantControl/CVariantControlAdaptor.h"

#if !defined(USE_SIMULATION_PERSISTENCY)
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <persistence_client_library_file.h>
#include <persistence_client_library_key.h>
#include <persistence_client_library.h>
#include <persistence_client_library_error_def.h>
#include <persistence_client_library_utils.h>

#include <algorithm>
#include <iostream>
#include <Uboot.h>
#endif // !defined(USE_SIMULATION_PERSISTENCY)

///////////////////////////////////////////////////////////////////////////////
// Event Handler related functions
///////////////////////////////////////////////////////////////////////////////
CPersistencyEventHandler::CPersistencyEventHandler(QObject *parent) : QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s", __FUNCTION__);

    connectSignals();

#if defined(USE_SIMULATION_PERSISTENCY)
    m_pSimulationPersistency = new QSettings ("Harman", HMI_PCL_APP_NAME);
#else
    pclInitLibrary(HMI_PCL_APP_NAME.toStdString().c_str(), PCL_SHUTDOWN_TYPE_NORMAL);
#endif // defined(USE_SIMULATION_PERSISTENCY)
}
//____________________________________________________________________________
CPersistencyEventHandler::~CPersistencyEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s", __FUNCTION__);

#if defined(USE_SIMULATION_PERSISTENCY)
    if (m_pSimulationPersistency != nullptr)
    {
        delete m_pSimulationPersistency;
        m_pSimulationPersistency = nullptr;
    }
#else
    pclDeinitLibrary();
#endif // defined(USE_SIMULATION_PERSISTENCY)
}

///////////////////////////////////////////////////////////////////////////////
// Event related functions
///////////////////////////////////////////////////////////////////////////////
void CPersistencyEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s", __FUNCTION__);
}

///////////////////////////////////////////////////////////////////////////////
// Persistency related functions
///////////////////////////////////////////////////////////////////////////////
const QString CPersistencyEventHandler::readDataFromEarlyDataPersistency(unsigned long ubootID)
{
    // FixMe: [NK] [PERSISTENCY] Early Data Persistency is under devlopment and need refactoring
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, ubootID:%ld", __FUNCTION__, ubootID);
    QString qstrValue = "";

#if defined(USE_SIMULATION_PERSISTENCY)
    qstrValue = m_pSimulationPersistency->value("Early_" + QString::number(ubootID)).toString();
#else
    unsigned char sValue[100] = "";
    int sizetoRead = 1;
    if (pclKeyReadData(PCL_LDBID_EARLY,(const char *)&ubootID,PCL_USER_NUMBER,PCL_SEAT_NUMBER,sValue,sizetoRead) >= 0)
    {
        qstrValue = QString::fromUtf8((char*)sValue);
        LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, Read Successful BootID:%ld Value:%s", __FUNCTION__, ubootID, (char*)sValue);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, Read Fail BootID:%ld", __FUNCTION__, ubootID);
    }
#endif // defined(USE_SIMULATION_PERSISTENCY)
    return qstrValue;
}
//____________________________________________________________________________
QString CPersistencyEventHandler::readDataFromPersistency(QString qstrKey)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, qstrKey:%s", __FUNCTION__, qstrKey.toStdString().data());

    std::string sKey = qstrKey.toStdString();
    QString qstrValue = "";

#if defined(USE_SIMULATION_PERSISTENCY)
    qstrValue = m_pSimulationPersistency->value(qstrKey).toString();
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, Read From Simulation Key:%s Value:%s", __FUNCTION__, sKey.c_str(), qstrValue.toStdString().c_str());
#else
    unsigned char sValue[100];
    int sizetoRead = pclKeyGetSize(PCL_LDBID_LOCAL, sKey.c_str(), PCL_USER_NUMBER,PCL_SEAT_NUMBER);
    memset((unsigned char *)&sValue,0,100);
    if (pclKeyReadData(PCL_LDBID_LOCAL,sKey.c_str(),PCL_USER_NUMBER,PCL_SEAT_NUMBER,sValue,sizetoRead) >= 0)
    {
        qstrValue = QString::fromUtf8((char*)sValue);
        LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, Read Successful Key:%s Value:%s", __FUNCTION__, sKey.c_str(), (char*)sValue);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, Read Fail Key:%s", __FUNCTION__, sKey.c_str());
    }
#endif // defined(USE_SIMULATION_PERSISTENCY)
    return qstrValue;
}
//____________________________________________________________________________
bool CPersistencyEventHandler::WriteDataToPersistency(QString qstrKey, QString qstrValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, qstrKey:%s, qstrValue:%s", __FUNCTION__, qstrKey.toStdString().data(), qstrValue.toStdString().data());

    std::string sKey = qstrKey.toStdString();
    std::string sValue = qstrValue.toStdString();
    bool bStatus = false;

#if defined(USE_SIMULATION_PERSISTENCY)
    m_pSimulationPersistency->setValue(qstrKey, qstrValue);
    bStatus = true;
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, Write to Simulation Key:%s Value:%s", __FUNCTION__, sKey.c_str(), sValue.c_str());
#else
    unsigned char buf[100];
    copy( sValue.begin(), sValue.end(), buf );
    buf[sValue.length()] = 0;
    if (pclKeyWriteData(PCL_LDBID_LOCAL, sKey.c_str(), PCL_USER_NUMBER, PCL_SEAT_NUMBER, (unsigned char*)buf, sValue.size()) >= 0)
    {
        bStatus = true;
        LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, Write Successful Key:%s Value:%s", __FUNCTION__, sKey.c_str(), sValue.c_str());
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, Write Fail Key:%s Value:%s", __FUNCTION__, sKey.c_str(), sValue.c_str());
    }
#endif // defined(USE_SIMULATION_PERSISTENCY)
    return bStatus;
}
//____________________________________________________________________________

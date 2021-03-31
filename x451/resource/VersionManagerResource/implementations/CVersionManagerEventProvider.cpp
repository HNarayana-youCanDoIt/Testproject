/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVersionManagerEventProvider.cpp
* @ingroup      HMIComponent
* @author       Rajat Gupta
* CVersionManagerEventProvider, Class to send signals to VersionManagerHandler on Version Manager Resource events
*/


#include "CVersionManagerEventProvider.h"
#include "logging.h"

CVersionManagerEventProvider::CVersionManagerEventProvider(QObject *parent):
    QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
}

CVersionManagerEventProvider::~CVersionManagerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
}

void CVersionManagerEventProvider::vcInfoNumberReceived(const QString &strVCInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    emit sigVCInfoUpdateReceived(strVCInfo);
}

void CVersionManagerEventProvider::vinPartNumberReceived(const QString& strVinInfo)
{

    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigVINInfoUpdateReceived (strVinInfo);
}

void CVersionManagerEventProvider::containerPartNoReceived(const QString& strContainerPartNo)
{

    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigContainerPartNoUpdateReceived (strContainerPartNo);
}

void CVersionManagerEventProvider::silverBoxPartNoReceived(const QString& strSilverBoxPartNo)
{

    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigSilverBoxPartNoUpdateReceived (strSilverBoxPartNo);
}

void CVersionManagerEventProvider::displayHWPartNoReceived(const QString& strDisplayHWPartNo)
{

    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigDisplayHWPartNoUpdateReceived (strDisplayHWPartNo);
}

void CVersionManagerEventProvider::parameterizationPartNoReceived(const QString& strParameterizationPartNo)
{

    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigParameterizationPartNoUpdateReceived (strParameterizationPartNo);
}

void CVersionManagerEventProvider::buttonPanelPartNoReceived(const QString& strButtonPanelPartNo)
{

    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigButtonPanelPartNoUpdateReceived (strButtonPanelPartNo);
}

void CVersionManagerEventProvider::socSofVersionNoUpdateReceived(const QString& strSOCSoftVersionNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigSOCSofVersionNoUpdateReceived (strSOCSoftVersionNo);

}

void CVersionManagerEventProvider::buttonPanelSofVersionNoUpdateReceived(const QString& strbuttonPanelSoftVersionNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigButtonPanelSofVersionNoUpdateReceived (strbuttonPanelSoftVersionNo);

}

void CVersionManagerEventProvider::displayManagerSofVersionNoUpdateReceived(const QString& strDisplayManagerSoftVersionNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigDisplayManagerSofVersionNoUpdateReceived (strDisplayManagerSoftVersionNo);

}

void CVersionManagerEventProvider::powerModeCfgTypeReceived(const string &strPowerMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigPowerModeCfgTypeReceived(QString::fromStdString(strPowerMode));
}

void CVersionManagerEventProvider::versionMismatchEventReceived(uint uiMismacthValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    emit sigVersionMismatchEventReceived(uiMismacthValue);
}

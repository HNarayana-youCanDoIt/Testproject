/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVersionManagerEventHandler.cpp
* @ingroup      HMIComponent
* @author       Rajat Gupta
* @class        CVersionManagerEventHandler: Class has the slots for all the Signals sent by CVersionManagerEventHandler
*                                   which informs Version Manager Adaptor about Version Manager Resource Events
*/

#include "CVersionManagerEventHandler.h"
#include "CVersionManagerAdaptor.h"
#include "HMIIncludes.h"
#include "VersionManagerResource/implementations/CVersionManagerResourceImpl.h"
#include <ResourceFactory.hpp>
#include "CPowerModeAdaptor.h"
#include <QObject>

CVersionManagerEventHandler::CVersionManagerEventHandler(QObject *parent) : QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    CVersionManagerAdaptor::getInstance();
    m_bReducedCanStatus = false;
    connectSignals();
}

CVersionManagerEventHandler::~CVersionManagerEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
}

void CVersionManagerEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    CVersionManagerResourceImpl* m_pVersionManagerResource =
            static_cast<CVersionManagerResourceImpl*>(ResourceFactory::getVersionManagerResource());

    if (m_pVersionManagerResource)
    {
        CVersionManagerEventProvider* m_pVersionManagerEventProvider = m_pVersionManagerResource->getVersionManagerEventProvider();

        // Connect signal and slot connection of Part Numbers
        if(m_pVersionManagerEventProvider)

        {
            connect(m_pVersionManagerEventProvider, SIGNAL(sigVCInfoUpdateReceived(const QString&)),
                    this, SLOT(sltVCInfoUpdateReceived(const QString&)),Qt::QueuedConnection);

            connect(m_pVersionManagerEventProvider, SIGNAL(sigVINInfoUpdateReceived(const QString&)),
                    this, SLOT(sltVINInfoUpdateReceived(const QString&)),Qt::QueuedConnection);

            connect(m_pVersionManagerEventProvider, SIGNAL(sigContainerPartNoUpdateReceived(const QString&))
                    , this, SLOT(sltContainerPartNoUpdateReceived(const QString&)),Qt::QueuedConnection);

            connect(m_pVersionManagerEventProvider, SIGNAL(sigSilverBoxPartNoUpdateReceived(const QString&))
                    , this, SLOT(sltSilverBoxPartNoUpdateReceived(const QString&)),Qt::QueuedConnection);

            connect(m_pVersionManagerEventProvider, SIGNAL(sigDisplayHWPartNoUpdateReceived(const QString&))
                    , this, SLOT(sltDisplayHWPartNoUpdateReceived(const QString&)),Qt::QueuedConnection);

            connect(m_pVersionManagerEventProvider, SIGNAL(sigParameterizationPartNoUpdateReceived(const QString&))
                    , this, SLOT(sltParameterizationPartNoUpdateReceived(const QString&)),Qt::QueuedConnection);

            connect(m_pVersionManagerEventProvider, SIGNAL(sigButtonPanelPartNoUpdateReceived(const QString&))
                    , this, SLOT(sltButtonPanelPartNoUpdateReceived(const QString&)),Qt::QueuedConnection);


            // Connect signal and slot connection of Software Version Part number.
            connect(m_pVersionManagerEventProvider, SIGNAL(sigSOCSofVersionNoUpdateReceived(const QString&))
                    , this, SLOT(sltSOCSofVersionNoUpdateReceived(const QString&)),Qt::QueuedConnection);
            connect(m_pVersionManagerEventProvider, SIGNAL(sigButtonPanelSofVersionNoUpdateReceived(const QString&))
                    , this, SLOT(sltButtonPanelSofVersionNoUpdateReceived(const QString&)),Qt::QueuedConnection);
            connect(m_pVersionManagerEventProvider, SIGNAL(sigDisplayManagerSofVersionNoUpdateReceived(const QString&))
                    , this, SLOT(sltDisplayManagerSofVersionNoUpdateReceived(const QString&)),Qt::QueuedConnection);
            connect(m_pVersionManagerEventProvider, SIGNAL(sigPowerModeCfgTypeReceived(const QString& ))
                    , this, SLOT(sltPowerModeCfgTypeReceived(const QString& )),Qt::QueuedConnection);
            connect(m_pVersionManagerEventProvider, SIGNAL(sigVersionMismatchEventReceived(uint))
                    , this, SLOT(sltVersionMismatchEventReceived(uint)),Qt::QueuedConnection);

            //connect signal for getting power mode change update
            connect(&(CPowerModeAdaptor::getInstance()), SIGNAL(sigPowerModeChanged()), this, SLOT(sltPowerModeChanged()));

        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"Resource returns as null from ResourceFactory");
    }
}

void CVersionManagerEventHandler::sltVCInfoUpdateReceived(const QString &strVCInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: strVCInfo: %s", __FUNCTION__, strVCInfo.toStdString().data());
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setVCInfo(strVCInfo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: VersionManagerAdaptor object not created.",__FUNCTION__);
    }

}
void CVersionManagerEventHandler::sltVINInfoUpdateReceived(const QString& strVinInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setVINInfo(strVinInfo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: VersionManagerAdaptor object not created.",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltContainerPartNoUpdateReceived(const QString& strContainerPartNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setContainerPartNo(strContainerPartNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: VersionManagerAdaptor object not created.",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltSilverBoxPartNoUpdateReceived(const QString& strSilverBoxPartNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setSilverBoxPartNo(strSilverBoxPartNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: VersionManagerAdaptor object not created.",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltDisplayHWPartNoUpdateReceived(const QString& strDisplayHWPartNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setDisplayHWPartNo(strDisplayHWPartNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: VersionManagerAdaptor object not created.",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltParameterizationPartNoUpdateReceived(const QString& strParameterizationPartNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setParameterizationPartNo(strParameterizationPartNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: VersionManagerAdaptor object not created.",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltButtonPanelPartNoUpdateReceived(const QString& strButtonPanelPartNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setButtonPanelPartNo(strButtonPanelPartNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: VersionManagerAdaptor object not created.",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltSOCSofVersionNoUpdateReceived(const QString& strSOCSoftVersionNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setSOCSoftVersionNo(strSOCSoftVersionNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: VersionManagerAdaptor object not created.",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltButtonPanelSofVersionNoUpdateReceived(const QString& strBtnPanelSoftVersionNo )
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setBtnPanelSoftVersionNo(strBtnPanelSoftVersionNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: VersionManagerAdaptor object not created.",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltDisplayManagerSofVersionNoUpdateReceived(const QString& strDisplayManagerSoftVersionNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);

    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setDisplayManagerSoftVersionNo(strDisplayManagerSoftVersionNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: VersionManagerAdaptor object not created.",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltPowerModeCfgTypeReceived(const QString& strPowerMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s", __FUNCTION__);
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->setPowerMode(strPowerMode);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: m_pVersionManagerAdaptor is NULL",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltVersionMismatchEventReceived(uint uiVerMismatchValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s", __FUNCTION__);
    if(CVersionManagerAdaptor::getInstance())
    {
        CVersionManagerAdaptor::getInstance()->versionMisMatchValueReceived(uiVerMismatchValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: m_pVersionManagerAdaptor is NULL",__FUNCTION__);
    }
}

void CVersionManagerEventHandler::sltPowerModeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s", __FUNCTION__);
    if(CPowerModeEnums::VPM_EARLY_WAKEUP == CPowerModeAdaptor::getInstance().getPowerModeStatus())
        {
                m_bReducedCanStatus = true;
        }

    if(CPowerModeEnums::VPM_ACTIVE == CPowerModeAdaptor::getInstance().getPowerModeStatus() && m_bReducedCanStatus)
    {
         CVersionManagerAdaptor::getInstance()->versionMismatchEvent();
         m_bReducedCanStatus = false;

    }
}

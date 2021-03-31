/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CAppleCarPlayEventHandler.cpp
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         Contain implementation of all the slots and methods declared in
 *                CAppleCarPlayEventHandler class
 */

#include "CAppleCarPlayEventHandler.h"
#include "ResourceFactory.hpp"
#include "logging.h"
#include "CAppleCarPlayAdaptor.h"
#include "implementations/CDeviceModeHandlerResourceImpl.h"
#include "implementations/CAppleCarPlayResourceImpl.h"
#include "implementations/CAppleCarPlayEventProvider.h"

CAppleCarPlayEventHandler::CAppleCarPlayEventHandler(QObject* pParent): QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    connectAppleCarPlayEventProviderSignals();
}

CAppleCarPlayEventHandler::~CAppleCarPlayEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    disconnectAppleCarPlayEventProviderSignals();
}

/******************************************************
 * @category    APPLECARPLAY SLOTS
 *******************************************************/

void CAppleCarPlayEventHandler::sltUpdateAppleCarPlayConnectionStatus(bool bAppleCarPlayConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(CAppleCarPlayAdaptor::getInstance())
    {
        CAppleCarPlayAdaptor::getInstance()->setAppleCarPlayConnectionStatus(bAppleCarPlayConnectionStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AppleCarPlay adaptor object not created.");
    }
}

void CAppleCarPlayEventHandler::sltUpdateAppleCarPlayProjectionStatus(bool bAppleCarPlayProjectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(CAppleCarPlayAdaptor::getInstance())
    {
        CAppleCarPlayAdaptor::getInstance()->setAppleCarPlayProjectionStatus(bAppleCarPlayProjectionStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AppleCarPlay adaptor object not created.");
    }
}

void CAppleCarPlayEventHandler::sltUpdateAppleCarPlayPhoneStatus(bool bAppleCarPlayPhoneStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(CAppleCarPlayAdaptor::getInstance())
    {
        CAppleCarPlayAdaptor::getInstance()->setAppleCarPlayPhoneStatus(bAppleCarPlayPhoneStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AppleCarPlay adaptor object not created.");
    }
}

void CAppleCarPlayEventHandler::sltUpdateCarPlaySiriStatus(bool bCarPlaySiriStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(CAppleCarPlayAdaptor::getInstance())
    {
        CAppleCarPlayAdaptor::getInstance()->setCarPlaySiriStatus(bCarPlaySiriStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AppleCarPlay adaptor object not created.");
    }
}

void CAppleCarPlayEventHandler::sltUpdateAppleCarPlayDeviceName(const QString &strAppleCarPlayDeviceName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(CAppleCarPlayAdaptor::getInstance())
    {
        CAppleCarPlayAdaptor::getInstance()->setAppleCarPlayDeviceName(strAppleCarPlayDeviceName);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AppleCarPlay adaptor object not created.");
    }
}

void CAppleCarPlayEventHandler::sltUpdateAppleCarPlayRemoteUIStatus(bool bAppleCarPlayRemoteUIStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(CAppleCarPlayAdaptor::getInstance())
    {
        CAppleCarPlayAdaptor::getInstance()->setAppleCarPlayRemoteUIStatus(bAppleCarPlayRemoteUIStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AppleCarPlay adaptor object not created.");
    }
}

void CAppleCarPlayEventHandler::sltUpdateCPMediaNowPlayingInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if( CAppleCarPlayAdaptor::getInstance() )
    {
        CAppleCarPlayAdaptor::getInstance()->updateCPNowPlayingInfo();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AppleCarPlay adaptor object not created.");
    }
}

void CAppleCarPlayEventHandler::sltUpdateSmartFanState(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Smart Fan state: %d", __FUNCTION__, bValue);

    CAppleCarPlayAdaptor::getInstance()->updateSmartFanState(bValue);
}

void CAppleCarPlayEventHandler::sltUpdateCPProxyStatus(bool bCPProxyStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bCPProxyStatus: %d", __FUNCTION__, bCPProxyStatus);

    CAppleCarPlayAdaptor::getInstance()->updateCPProxyStatus(bCPProxyStatus);
}

/******************************************************
 * @category    INTERNAL METHODS
 *******************************************************/

void CAppleCarPlayEventHandler::connectAppleCarPlayEventProviderSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    /*****************************************************
     * Connecting signals of DeviceMode Handler's Event provider
     *****************************************************/

    CDeviceModeHandlerResourceImpl* pDeviceModeHandlerResource = dynamic_cast<CDeviceModeHandlerResourceImpl*>(ResourceFactory::getDeviceModeHandlerResource());

    if(pDeviceModeHandlerResource)
    {
        CDeviceModeHandlerEventProvider* pDeviceModeHandlerEventProvider = pDeviceModeHandlerResource->getDeviceModeHandlerEventProvider();

        if (pDeviceModeHandlerEventProvider)
        {
            connect(pDeviceModeHandlerEventProvider, SIGNAL(sigUpdateCarPlayConnectionStatus(bool)), this, SLOT(sltUpdateAppleCarPlayConnectionStatus(bool)), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: pDeviceModeHandlerEventProvider is NULL.", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: Device Mode Handler resource not created", __FUNCTION__);
    }

    /*****************************************************
     * Connecting signals of AppleCarPlay Event provider.
     *****************************************************/

    CAppleCarPlayResourceImpl* pAppleCarPlayResource = dynamic_cast<CAppleCarPlayResourceImpl*>(ResourceFactory::getAppleCarPlayResource());

    if(pAppleCarPlayResource)
    {
        CAppleCarPlayEventProvider* pAppleCarPlayEventProvider = pAppleCarPlayResource->getAppleCarPlayEventProvider();

        if (pAppleCarPlayEventProvider)
        {
            connect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateAppleCarPlayConnectionStatus(bool)), this, SLOT(sltUpdateAppleCarPlayConnectionStatus(bool)), Qt::QueuedConnection);
            connect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateAppleCarPlayProjectionStatus(bool)), this, SLOT(sltUpdateAppleCarPlayProjectionStatus(bool)), Qt::QueuedConnection);
            connect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateAppleCarPlayPhoneStatus(bool)), this, SLOT(sltUpdateAppleCarPlayPhoneStatus(bool)), Qt::QueuedConnection);
            connect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateAppleCarPlayDeviceName(const QString &)), this, SLOT(sltUpdateAppleCarPlayDeviceName(const QString &)), Qt::QueuedConnection);
            connect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateAppleCarPlayRemoteUIStatus(bool)), this, SLOT(sltUpdateAppleCarPlayRemoteUIStatus(bool)), Qt::QueuedConnection);
            connect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateCPMediaNowPlayingInfo()), this, SLOT(sltUpdateCPMediaNowPlayingInfo()), Qt::QueuedConnection);
            connect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateSmartFanState(bool)), this, SLOT(sltUpdateSmartFanState(bool)), Qt::QueuedConnection);
            connect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateCPProxyStatus(bool)), this, SLOT(sltUpdateCPProxyStatus(bool)), Qt::QueuedConnection);
            connect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateCarPlaySiriStatus(bool)), this, SLOT(sltUpdateCarPlaySiriStatus(bool)), Qt::QueuedConnection);

        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: pAppleCarPlayEventProvide is NULL.", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlay resource not created.", __FUNCTION__);
    }
}

void CAppleCarPlayEventHandler::disconnectAppleCarPlayEventProviderSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    /************************************************************
     * Disconnecting signals of DeviceMode Handler's Event provider.
     ************************************************************/

    CDeviceModeHandlerResourceImpl* pDeviceModeHandlerResource = dynamic_cast<CDeviceModeHandlerResourceImpl*>(ResourceFactory::getDeviceModeHandlerResource());

    if(pDeviceModeHandlerResource)
    {
        CDeviceModeHandlerEventProvider* pDeviceModeHandlerEventProvider = pDeviceModeHandlerResource->getDeviceModeHandlerEventProvider();

        if (pDeviceModeHandlerEventProvider)
        {
            disconnect(pDeviceModeHandlerEventProvider, SIGNAL(sigUpdateCarPlayConnectionStatus(bool)), this, SLOT(sltUpdateAppleCarPlayConnectionStatus(bool)));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: pDeviceModeHandlerEventProvider is NULL.", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: Device Mode Handler resource not created", __FUNCTION__);
    }

    /*****************************************************
     * Disconnecting signals of AppleCarPlay Event provider.
     *****************************************************/

    CAppleCarPlayResourceImpl* pAppleCarPlayResource = dynamic_cast<CAppleCarPlayResourceImpl*>(ResourceFactory::getAppleCarPlayResource());

    if(pAppleCarPlayResource)
    {
        CAppleCarPlayEventProvider* pAppleCarPlayEventProvider = pAppleCarPlayResource->getAppleCarPlayEventProvider();

        if (pAppleCarPlayEventProvider)
        {
            disconnect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateAppleCarPlayConnectionStatus(bool)), this, SLOT(sltUpdateAppleCarPlayConnectionStatus(bool)));
            disconnect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateAppleCarPlayProjectionStatus(bool)), this, SLOT(sltUpdateAppleCarPlayProjectionStatus(bool)));
            disconnect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateAppleCarPlayPhoneStatus(bool)), this, SLOT(sltUpdateAppleCarPlayPhoneStatus(bool)));
            disconnect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateAppleCarPlayDeviceName(const QString &)), this, SLOT(sltUpdateAppleCarPlayDeviceName(const QString &)));
            disconnect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateAppleCarPlayRemoteUIStatus(bool)), this, SLOT(sltUpdateAppleCarPlayRemoteUIStatus(bool)));
            disconnect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateCPMediaNowPlayingInfo()), this, SLOT(sltUpdateCPMediaNowPlayingInfo()));
            disconnect(pAppleCarPlayEventProvider, SIGNAL(sigUpdateCarPlaySiriStatus(bool)), this, SLOT(sltUpdateCarPlaySiriStatus(bool)));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: pAppleCarPlayEventProvide is NULL.", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlay resource not created.", __FUNCTION__);
    }
}

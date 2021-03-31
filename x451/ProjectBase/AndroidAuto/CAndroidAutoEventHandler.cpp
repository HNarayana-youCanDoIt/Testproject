/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CAndroidAutoEventHandler.cpp
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         Contain implementation of all the slots and methods declared in
 *                CAndroidAutoEventHandler class
 */

#include "CAndroidAutoEventHandler.h"
#include "ResourceFactory.hpp"
#include "logging.h"
#include "CAndroidAutoAdaptor.h"
#include "CAndroidAutoEnums.h"
#include "implementations/CDeviceModeHandlerResourceImpl.h"
#include "implementations/CAndroidAutoResourceImpl.h"
#include "implementations/CAndroidAutoEventProvider.h"

CAndroidAutoEventHandler::CAndroidAutoEventHandler(QObject* pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    connectAndroidAutoEventProviderSignals();
    connectDeviceModeHandlerEventProviderSignals();
}

CAndroidAutoEventHandler::~CAndroidAutoEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    disconnectAndroidAutoEventProviderSignals();
    disconnectDeviceModeHandlerEventProviderSignals();
}

/******************************************************//**
 * @category    ANDROIDAUTO SLOTS
 *******************************************************/

void CAndroidAutoEventHandler::sltUpdateAndroidAutoConnectionStatus(bool bAAConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bAAConnectionStatus: %d", __FUNCTION__, bAAConnectionStatus);

    if(CAndroidAutoAdaptor::getInstance())
    {
        CAndroidAutoAdaptor::getInstance()->setAndroidAutoConnectionStatus(bAAConnectionStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AndroidAuto adaptor object not created.");
    }
}

void CAndroidAutoEventHandler::sltUpdateAndroidAutoBondReqStatus(bool bAABondReqStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: sltUpdateAndroidAutoBondReqStatus: %d", __FUNCTION__, bAABondReqStatus);

    if(CAndroidAutoAdaptor::getInstance())
    {
        CAndroidAutoAdaptor::getInstance()->setAndroidAutoBondReqStatus(bAABondReqStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AndroidAuto adaptor object not created.");
    }
}

void CAndroidAutoEventHandler::sltShowFirstRunPopup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_AA_FIRST_RUN);
}

void CAndroidAutoEventHandler::sltUpdateAAMediaMetaData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if( CAndroidAutoAdaptor::getInstance() )
    {
        CAndroidAutoAdaptor::getInstance()->updateAAMediaMetaData();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AndroidAuto adaptor object not created.");
    }
}

void CAndroidAutoEventHandler::sltUpdateAAMediaPlayState(ushort usAAMediaPlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: usAAMediaPlayState: %d",
             __FUNCTION__, usAAMediaPlayState);

    if(CAndroidAutoAdaptor::getInstance())
    {
        CAndroidAutoAdaptor::getInstance()->setAAMediaPlayState(
                    static_cast<CAndroidAutoEnums::EAAMediaPlayState>
                    (usAAMediaPlayState));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AndroidAuto adaptor object not created.");
    }
}

void CAndroidAutoEventHandler::sltUpdateAAProjectionStatus(bool bAAProjectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bAAProjectionStatus: %d", __FUNCTION__, bAAProjectionStatus);

    if(CAndroidAutoAdaptor::getInstance())
    {
        CAndroidAutoAdaptor::getInstance()->setAndroidAutoProjectionStatus(bAAProjectionStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AndroidAuto adaptor object not created.");
    }
}

void CAndroidAutoEventHandler::sltUpdateOKGoogleStatus(bool bOKGoogleStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bOKGoogleStatus: %d", __FUNCTION__, bOKGoogleStatus);

    if(CAndroidAutoAdaptor::getInstance())
    {
        CAndroidAutoAdaptor::getInstance()->setOKGoogleStatus(bOKGoogleStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AndroidAuto adaptor object not created.");
    }
}

void CAndroidAutoEventHandler::sltUpdateAANaviStatus(bool bAANaviStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bAANaviStatus: %d", __FUNCTION__, bAANaviStatus);

    if(CAndroidAutoAdaptor::getInstance())
    {
        CAndroidAutoAdaptor::getInstance()->setAANaviStatus(bAANaviStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AndroidAuto adaptor object not created.");
    }
}

void CAndroidAutoEventHandler::sltUpdateAASessionDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if(CAndroidAutoAdaptor::getInstance())
    {
        CAndroidAutoAdaptor::getInstance()->updateAASessionDetails();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AndroidAuto adaptor object not created.");
    }
}

void CAndroidAutoEventHandler::sltUpdateAANaviTurnEventDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    CAndroidAutoAdaptor::getInstance()->updateAANaviTurnEventDetails();
}

void CAndroidAutoEventHandler::sltUpdateAANaviDistanceDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    CAndroidAutoAdaptor::getInstance()->updateAANaviDistanceDetails();
}


/******************************************************//**
 * @category    INTERNAL METHODS
 *******************************************************/

void CAndroidAutoEventHandler::connectDeviceModeHandlerEventProviderSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    CDeviceModeHandlerResourceImpl* pDeviceModeHandlerResource = dynamic_cast<CDeviceModeHandlerResourceImpl*>(ResourceFactory::getDeviceModeHandlerResource());

    if(pDeviceModeHandlerResource)
    {
        CDeviceModeHandlerEventProvider* pDeviceModeHandlerEventProvider = pDeviceModeHandlerResource->getDeviceModeHandlerEventProvider();

        if (pDeviceModeHandlerEventProvider)
        {
            connect(pDeviceModeHandlerEventProvider, SIGNAL(sigUpdateAAConnectionStatus(bool)), this, SLOT(sltUpdateAndroidAutoConnectionStatus(bool)), Qt::QueuedConnection);
            connect(pDeviceModeHandlerEventProvider, SIGNAL(sigUpdateAABondingReqStatus(bool)), this, SLOT(sltUpdateAndroidAutoBondReqStatus(bool)), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: pDeviceModeHandlerEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: Device Mode Handler resource not created.", __FUNCTION__);
    }
}

void CAndroidAutoEventHandler::disconnectDeviceModeHandlerEventProviderSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    CDeviceModeHandlerResourceImpl* pDeviceModeHandlerResource = dynamic_cast<CDeviceModeHandlerResourceImpl*>(ResourceFactory::getDeviceModeHandlerResource());

    if(pDeviceModeHandlerResource)
    {
        CDeviceModeHandlerEventProvider* pDeviceModeHandlerEventProvider = pDeviceModeHandlerResource->getDeviceModeHandlerEventProvider();

        if (pDeviceModeHandlerEventProvider)
        {
            disconnect(pDeviceModeHandlerEventProvider, SIGNAL(sigUpdateAAConnectionStatus(bool)), this, SLOT(sltUpdateAndroidAutoConnectionStatus(bool)));
            disconnect(pDeviceModeHandlerEventProvider, SIGNAL(sigUpdateAABondingReqStatus(bool)), this, SLOT(sltUpdateAndroidAutoBondReqStatus(bool)));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: pDeviceModeHandlerEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: Device Mode Handler resource not created", __FUNCTION__);
    }
}

void CAndroidAutoEventHandler::connectAndroidAutoEventProviderSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    CAndroidAutoResourceImpl* pAndroidAutoResource = dynamic_cast<CAndroidAutoResourceImpl*>(ResourceFactory::getAndroidAutoResource());

    if(pAndroidAutoResource)
    {
        CAndroidAutoEventProvider* pAndroidAutoEventProvider = pAndroidAutoResource->getAndroidAutoEventProvider();

        if (pAndroidAutoEventProvider)
        {
            connect(pAndroidAutoEventProvider, SIGNAL(sigShowFirstRunPopup()), this, SLOT(sltShowFirstRunPopup()), Qt::QueuedConnection);
            connect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAAMediaMetaData()), this, SLOT(sltUpdateAAMediaMetaData()), Qt::QueuedConnection);
            connect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAAMediaPlayState(ushort)), this, SLOT(sltUpdateAAMediaPlayState(ushort)), Qt::QueuedConnection);
            connect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAAProjectionStatus(bool)), this, SLOT(sltUpdateAAProjectionStatus(bool)), Qt::QueuedConnection);
            connect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAANaviStatus(bool)), this, SLOT(sltUpdateAANaviStatus(bool)), Qt::QueuedConnection);
            connect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAASessionDetails()), this, SLOT(sltUpdateAASessionDetails()), Qt::QueuedConnection);
            connect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAANaviTurnEventDetails()), this, SLOT(sltUpdateAANaviTurnEventDetails()), Qt::QueuedConnection);
            connect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAANaviDistanceDetails()), this, SLOT(sltUpdateAANaviDistanceDetails()), Qt::QueuedConnection);
            connect(pAndroidAutoEventProvider, SIGNAL(sigUpdateOKGoogleStatus(bool)), this, SLOT(sltUpdateOKGoogleStatus(bool)), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: pAndroidAutoEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAuto resource not created.", __FUNCTION__);
    }
}

void CAndroidAutoEventHandler::disconnectAndroidAutoEventProviderSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    CAndroidAutoResourceImpl* pAndroidAutoResource = dynamic_cast<CAndroidAutoResourceImpl*>(ResourceFactory::getAndroidAutoResource());

    if(pAndroidAutoResource)
    {
        CAndroidAutoEventProvider* pAndroidAutoEventProvider = pAndroidAutoResource->getAndroidAutoEventProvider();

        if (pAndroidAutoEventProvider)
        {
            disconnect(pAndroidAutoEventProvider, SIGNAL(sigShowFirstRunPopup()), this, SLOT(sltShowFirstRunPopup()));
            disconnect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAAMediaMetaData()), this, SLOT(sltUpdateAAMediaMetaData()));
            disconnect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAAMediaPlayState(ushort)), this, SLOT(sltUpdateAAMediaPlayState(ushort)));
            disconnect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAAProjectionStatus(bool)), this, SLOT(sltUpdateAAProjectionStatus(bool)));
            disconnect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAANaviStatus(bool)), this, SLOT(sltUpdateAANaviStatus(bool)));
			disconnect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAASessionDetails()), this, SLOT(sltUpdateAASessionDetails()));
            disconnect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAANaviTurnEventDetails()), this, SLOT(sltUpdateAANaviTurnEventDetails()));
            disconnect(pAndroidAutoEventProvider, SIGNAL(sigUpdateAANaviDistanceDetails()), this, SLOT(sltUpdateAANaviDistanceDetails()));
            disconnect(pAndroidAutoEventProvider, SIGNAL(sigUpdateOKGoogleStatus(bool)), this, SLOT(sltUpdateOKGoogleStatus(bool)));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: pAndroidAutoEventProvider is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AndroidAuto resource not created.", __FUNCTION__);
    }
}

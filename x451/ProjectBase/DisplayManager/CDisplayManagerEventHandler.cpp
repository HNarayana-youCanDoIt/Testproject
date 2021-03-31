/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDisplayManagerEventHandler.cpp
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         Contain implementation of all the slots and methods declared in
 *                CDisplayManagerEventHandler class
 */

#include "CDisplayManagerEventHandler.h"
#include "ResourceFactory.hpp"
#include "logging.h"
#include "CDisplayManagerAdaptor.h"
#include "implementations/CDisplayManagerResourceImpl.h"
#include "CPopupManager.h"

CDisplayManagerEventHandler::CDisplayManagerEventHandler(QObject* pParent): QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    connectDisplayManagerSignals();
}

CDisplayManagerEventHandler::~CDisplayManagerEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    disconnectDisplayManagerSignals();
}

void CDisplayManagerEventHandler::sltBrightnessLevelRespRecv()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    CDisplayManagerAdaptor::getInstance()->setBrightnessLevelRespRecv();
}

void CDisplayManagerEventHandler::sltButtonPanelBrightnessLevelRespRecv()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    CDisplayManagerAdaptor::getInstance()->setButtonPanelBrightnessLevelRespRecv ();
}

void CDisplayManagerEventHandler::sltUpdateBrightnessLevel(short iBrightnessLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    CDisplayManagerAdaptor::getInstance()->setBrightnessLevel(iBrightnessLevel);
}

void CDisplayManagerEventHandler::sltUpdateButtonPanelBrightnessLevel(short iBrightnessLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    CDisplayManagerAdaptor::getInstance()->setButtonPanelBrightnessLevel(iBrightnessLevel);
}

void CDisplayManagerEventHandler::sltUpdateDisplayOnOffFeatureStatus(qint32 iDisplayOnOffFeatureStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: "
                                                 "iDisplayOnOffFeatureStatus:"
                                                 " %d", __FUNCTION__,
             iDisplayOnOffFeatureStatus);

    if (0 == iDisplayOnOffFeatureStatus)
    {
        CDisplayManagerAdaptor::getInstance()->setDisplayOnOffFeatureStatus(false);
        CPopupManager::getInstance()->closePopup(
                    CPopupEnum::EN_POPUPID_DISPLAY_OFF_TRANSPARENT);
    }
    else if (1 == iDisplayOnOffFeatureStatus)
    {
        CDisplayManagerAdaptor::getInstance()->setDisplayOnOffFeatureStatus(true);
        CPopupManager::getInstance()->showPopup(
                    CPopupEnum::EN_POPUPID_DISPLAY_OFF_TRANSPARENT);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: Wrong status "
                                                        "recieved for Display "
                                                        "ON/OFF feature status."
                    , __FUNCTION__);
    }
}

void CDisplayManagerEventHandler::sltUpdateNightModeStatus(qint32 iNightModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iNightModeStatus: %d", __FUNCTION__, iNightModeStatus);

    if (0 == iNightModeStatus)
    {
        CDisplayManagerAdaptor::getInstance()->setNightModeStatus(false);
    }
    else if (1 == iNightModeStatus)
    {
        CDisplayManagerAdaptor::getInstance()->setNightModeStatus(true);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: Wrong status recieved for Display status.", __FUNCTION__);
    }
}

/******************************************************//**
 * @category    Display MANAGER SLOTS
 *******************************************************/


/******************************************************//**
 * @category    INTERNAL METHODS
 *******************************************************/
void CDisplayManagerEventHandler::connectDisplayManagerSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    CDisplayManagerResourceImpl* pDisplayMgrResource = dynamic_cast<CDisplayManagerResourceImpl*>(ResourceFactory::getDisplayManagerResource());

    if (pDisplayMgrResource)
    {
        CDisplayManagerEventProvider* pDisplayMgrEventProvider = pDisplayMgrResource->getDisplayManagerEventProvider();

        if (pDisplayMgrEventProvider)
        {
            connect(pDisplayMgrEventProvider, SIGNAL(sigBrightnessLevelRespRecv()), this, SLOT(sltBrightnessLevelRespRecv()), Qt::QueuedConnection);

            connect(pDisplayMgrEventProvider, SIGNAL(sigButtonPanelBrightnessLevelRespRecv()), this, SLOT(sltButtonPanelBrightnessLevelRespRecv()), Qt::QueuedConnection);
            connect(pDisplayMgrEventProvider, SIGNAL(sigUpdateBrightnessLevel(short)), this, SLOT(sltUpdateBrightnessLevel(short)), Qt::QueuedConnection);
             connect(pDisplayMgrEventProvider, SIGNAL(sigUpdateButtonPanelBrightnessLevel(short)), this, SLOT(sltUpdateButtonPanelBrightnessLevel(short)), Qt::QueuedConnection);
            connect(pDisplayMgrEventProvider, SIGNAL(sigUpdateDisplayOnOffFeatureStatus(qint32)), this, SLOT(sltUpdateDisplayOnOffFeatureStatus(qint32)), Qt::QueuedConnection);
            connect(pDisplayMgrEventProvider, SIGNAL(sigUpdateNightModeStatus(qint32)), this, SLOT(sltUpdateNightModeStatus(qint32)), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "pDisplayMgrEventProvider is NULL.");
        }

    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "Display manager resource not created.");
    }
}

void CDisplayManagerEventHandler::disconnectDisplayManagerSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    CDisplayManagerResourceImpl* pDisplayMgrResource = dynamic_cast<CDisplayManagerResourceImpl*>(ResourceFactory::getDisplayManagerResource());

    if(pDisplayMgrResource)
    {
        CDisplayManagerEventProvider* pDisplayMgrEventProvider = pDisplayMgrResource->getDisplayManagerEventProvider();

        if (pDisplayMgrEventProvider)
        {
            disconnect(pDisplayMgrEventProvider, SIGNAL(sigBrightnessLevelRespRecv()), this, SLOT(sltBrightnessLevelRespRecv()));
            disconnect(pDisplayMgrEventProvider, SIGNAL(sigButtonPanelBrightnessLevelRespRecv()), this, SLOT(sltButtonPanelBrightnessLevelRespRecv()));
            disconnect(pDisplayMgrEventProvider, SIGNAL(sigUpdateBrightnessLevel(short)), this, SLOT(sltUpdateBrightnessLevel(short)));
            disconnect(pDisplayMgrEventProvider, SIGNAL(sigUpdateButtonPanelBrightnessLevel(short)), this, SLOT(sltUpdateButtonPanelBrightnessLevel(short)));
            disconnect(pDisplayMgrEventProvider, SIGNAL(sigUpdateDisplayOnOffFeatureStatus(qint32)), this, SLOT(sltUpdateDisplayOnOffFeatureStatus(qint32)));
            disconnect(pDisplayMgrEventProvider, SIGNAL(sigUpdateNightModeStatus(qint32)), this, SLOT(sltUpdateNightModeStatus(qint32)));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "pDisplayMgrEventProvider is NULL.");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "Display manager resource not created.");
    }
}

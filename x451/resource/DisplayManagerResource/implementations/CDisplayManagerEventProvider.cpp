/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CDisplayManagerDataEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         Contain implementation of all the methods declared in
 *                CDisplayManagerDataEventProvider class
 */

#include "CDisplayManagerEventProvider.h"
#include "logging.h"

CDisplayManagerEventProvider::CDisplayManagerEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
}

CDisplayManagerEventProvider::~CDisplayManagerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
}

void CDisplayManagerEventProvider::updateBrightnessLevelResponse()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    emit sigBrightnessLevelRespRecv();
}

void CDisplayManagerEventProvider::updateButtonPanelBrightnessLevelResponse()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    emit sigButtonPanelBrightnessLevelRespRecv();
}

void CDisplayManagerEventProvider::updateBrightnessLevel(short iBrightnessLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iBrightnessLevel: %d", __FUNCTION__, iBrightnessLevel);
    emit sigUpdateBrightnessLevel(iBrightnessLevel);
}

void CDisplayManagerEventProvider::updateButtonPanelBrightnessLevel(short iBrightnessLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iBrightnessLevel: %d", __FUNCTION__, iBrightnessLevel);
    emit sigUpdateButtonPanelBrightnessLevel (iBrightnessLevel);
}

void CDisplayManagerEventProvider::updateDisplayOnOffFeatureStatus(qint32 iDisplayOnOffFeatureStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iDisplayOnOffFeatureStatus: %d", __FUNCTION__, iDisplayOnOffFeatureStatus);
    emit sigUpdateDisplayOnOffFeatureStatus(iDisplayOnOffFeatureStatus);
}

void CDisplayManagerEventProvider::updateNightModeStatus(qint32 iNightModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iNightModeStatus: %d", __FUNCTION__, iNightModeStatus);
    emit sigUpdateNightModeStatus(iNightModeStatus);
}

/************************************************************************//**
 * @category    METHODS
 ************************************************************************/

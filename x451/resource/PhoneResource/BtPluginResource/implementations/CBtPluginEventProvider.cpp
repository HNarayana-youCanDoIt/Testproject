/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CBtPluginEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CBtPluginEventProvider class
 */

#include "CBtPluginEventProvider.h"
#include "logging.h"

CBtPluginEventProvider::CBtPluginEventProvider(QObject *pParent)
    : QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}

CBtPluginEventProvider::~CBtPluginEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}

/************************************************************************//**
 * @category    METHODS
 ************************************************************************/
void CBtPluginEventProvider::updateTTSPlayStateStatus(int iTTSPlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigTTSPlayStateStatus(iTTSPlayState);
}

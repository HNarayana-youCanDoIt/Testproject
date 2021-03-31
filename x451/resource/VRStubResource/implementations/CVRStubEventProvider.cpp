/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRStubEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 * CVRStubEventProvider class
 */

#include "CVRStubEventProvider.h"
#include "logging.h"

CVRStubEventProvider::CVRStubEventProvider(QObject *pParent) : QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
}

CVRStubEventProvider::~CVRStubEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
}

void CVRStubEventProvider::setScreenRequest(const string &strScreenName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigSetScreenRequest(QString::fromStdString(strScreenName));
}

void CVRStubEventProvider::showContact(const string &strDatabaseType, int iContactId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigShowContact(QString::fromStdString(strDatabaseType), iContactId);
}

void CVRStubEventProvider::showTeleprompterList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigShowTeleprompterList();
}

void CVRStubEventProvider::showPickList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigShowPickList();
}

void CVRStubEventProvider::hidePickList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigHidePickList();
}

void CVRStubEventProvider::setFocusedItem(int iLineNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigSetFocusedItem(iLineNo);
}

void CVRStubEventProvider::focusSelectedCategory(const string &strCategory)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigFocusSelectedCategory(QString::fromStdString(strCategory));
}

void CVRStubEventProvider::mediaFilterListShow(int32_t iMediaFilterType, int64_t iMediaFilterId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    emit sigMediaFilterListShow(iMediaFilterType, iMediaFilterId);
}

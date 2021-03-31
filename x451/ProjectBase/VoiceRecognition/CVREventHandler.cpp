/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVREventHandler.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the slots declared in CVREventHandler class
 */

#include "CVREventHandler.h"
#include "implementations/CVRStubResourceImpl.h"
#include "implementations/CVRProxyResImpl.h"
#include "ResourceFactory.hpp"
#include "CVRAdaptor.h"
#include "logging.h"

CVREventHandler::CVREventHandler(QObject *pParent) : QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    connectVRStubSignals();
    connectVRProxySignals();
}

CVREventHandler::~CVREventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    disconnectVRStubSignals();
    disconnectVRProxySignals();
}

void CVREventHandler::sltSetScreenRequest(QString strScreenName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->setScreen(strScreenName);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::sltShowContact(QString strDatabaseType, int iContactId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->showContact(strDatabaseType, iContactId);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::sltShowTeleprompterList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->showTeleprompterList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::sltShowPickList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->showPickList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::sltHidePickList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->hidePickList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::sltSetFocusedItem(int iLineNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->setFocusedItem(iLineNo);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::sltFocusSelectedCategory(QString strCategory)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->focusSelectedCategory(strCategory);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::sltMediaFilterListShow(qint32 iMediaFilterType, qint64 iMediaFilterId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->mediaFilterListShow(iMediaFilterType, iMediaFilterId);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}


void CVREventHandler::sltVRStateChange(int iVRState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->onVRStateChange(iVRState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::sltVRDialogStateChange(int iVRDialogState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->onVRDialogStateChange(iVRDialogState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::sltVRAvailableStatus(bool bVRAvailableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->onVRAvailableStatus(bVRAvailableStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::sltVRProxyAvailableStatus(bool bVRProxyAvailableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    if(CVRAdaptor::getInstance())
    {
        CVRAdaptor::getInstance()->onVRProxyAvailableStatus(bVRProxyAvailableStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR adaptor object not created");
    }
}

void CVREventHandler::connectVRStubSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);

    if(ResourceFactory::getVRStubResource() && ResourceFactory::getVRStubResource()->getVRStubResourceImpl())
    {
        CVRStubEventProvider* pVRStubEventProvider = ResourceFactory::getVRStubResource()->getVRStubResourceImpl()->getVRStubEventProvider();
        connect(pVRStubEventProvider, SIGNAL(sigSetScreenRequest(QString)),             this, SLOT(sltSetScreenRequest(QString)),           Qt::QueuedConnection);
        connect(pVRStubEventProvider, SIGNAL(sigShowContact(QString, int)),             this, SLOT(sltShowContact(QString, int)),           Qt::QueuedConnection);
        connect(pVRStubEventProvider, SIGNAL(sigShowTeleprompterList()),                this, SLOT(sltShowTeleprompterList()),              Qt::QueuedConnection);
        connect(pVRStubEventProvider, SIGNAL(sigShowPickList()),                        this, SLOT(sltShowPickList()),                      Qt::QueuedConnection);
        connect(pVRStubEventProvider, SIGNAL(sigHidePickList()),                        this, SLOT(sltHidePickList()),                      Qt::QueuedConnection);
        connect(pVRStubEventProvider, SIGNAL(sigSetFocusedItem(int)),                   this, SLOT(sltSetFocusedItem(int)),                 Qt::QueuedConnection);
        connect(pVRStubEventProvider, SIGNAL(sigFocusSelectedCategory(QString)),        this, SLOT(sltFocusSelectedCategory(QString)),      Qt::QueuedConnection);
        connect(pVRStubEventProvider, SIGNAL(sigMediaFilterListShow(qint32,qint64)),    this, SLOT(sltMediaFilterListShow(qint32,qint64)),  Qt::QueuedConnection);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR stub resource not created");
    }
}

void CVREventHandler::connectVRProxySignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);

    CVRProxyResImpl* pVRProxyResImpl = dynamic_cast<CVRProxyResImpl*>(ResourceFactory::getVRProxyResource());
    if(pVRProxyResImpl)
    {
        CVRProxyEventProvider* pVRProxyEventProvider = pVRProxyResImpl->getVRProxyEventProvider();
        connect(pVRProxyEventProvider, SIGNAL(sigVRStateChange(int)),           this, SLOT(sltVRStateChange(int)),          Qt::QueuedConnection);
        connect(pVRProxyEventProvider, SIGNAL(sigVRDialogStateChange(int)),     this, SLOT(sltVRDialogStateChange(int)),    Qt::QueuedConnection);
        connect(pVRProxyEventProvider, SIGNAL(sigVRAvailableStatus(bool)),      this, SLOT(sltVRAvailableStatus(bool)),     Qt::QueuedConnection);
        connect(pVRProxyEventProvider, SIGNAL(sigVRProxyAvailableStatus(bool)), this, SLOT(sltVRProxyAvailableStatus(bool)));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR stub resource not created");
    }
}

void CVREventHandler::disconnectVRStubSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);

    if(ResourceFactory::getVRStubResource() && ResourceFactory::getVRStubResource()->getVRStubResourceImpl())
    {
        CVRStubEventProvider* pVRStubEventProvider = ResourceFactory::getVRStubResource()->getVRStubResourceImpl()->getVRStubEventProvider();
        disconnect(pVRStubEventProvider, SIGNAL(sigSetScreenRequest(QString)),              this, SLOT(sltSetScreenRequest(QString)));
        disconnect(pVRStubEventProvider, SIGNAL(sigShowContact(QString,int32_t)),           this, SLOT(sltShowContact(QString,int32_t)));
        disconnect(pVRStubEventProvider, SIGNAL(sigShowTeleprompterList()),                 this, SLOT(sltShowTeleprompterList()));
        disconnect(pVRStubEventProvider, SIGNAL(sigShowPickList()),                         this, SLOT(sltShowPickList()));
        disconnect(pVRStubEventProvider, SIGNAL(sigHidePickList()),                         this, SLOT(sltHidePickList()));
        disconnect(pVRStubEventProvider, SIGNAL(sigSetFocusedItem(int)),                    this, SLOT(sltSetFocusedItem(int)));
        disconnect(pVRStubEventProvider, SIGNAL(sigFocusSelectedCategory(QString)),         this, SLOT(sltFocusSelectedCategory(QString)));
        disconnect(pVRStubEventProvider, SIGNAL(sigMediaFilterListShow(qint32,qint64)),     this, SLOT(sltMediaFilterListShow(qint32,qint64)));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR proxy resource not created");
    }
}

void CVREventHandler::disconnectVRProxySignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);

    CVRProxyResImpl* pVRProxyResImpl = dynamic_cast<CVRProxyResImpl*>(ResourceFactory::getVRProxyResource());
    if(pVRProxyResImpl)
    {
        CVRProxyEventProvider* pVRProxyEventProvider = pVRProxyResImpl->getVRProxyEventProvider();
        disconnect(pVRProxyEventProvider, SIGNAL(sigVRStateChange(int)),            this, SLOT(sltVRStateChange(int)));
        disconnect(pVRProxyEventProvider, SIGNAL(sigVRDialogStateChange(int)),      this, SLOT(sltVRDialogStateChange(int)));
        disconnect(pVRProxyEventProvider, SIGNAL(sigVRAvailableStatus(bool)),       this, SLOT(sltVRAvailableStatus(bool)));
        disconnect(pVRProxyEventProvider, SIGNAL(sigVRProxyAvailableStatus(bool)),  this, SLOT(sltVRProxyAvailableStatus(bool)));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "VR proxy resource not created");
    }
}

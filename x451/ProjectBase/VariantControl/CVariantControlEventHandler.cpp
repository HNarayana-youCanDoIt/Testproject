/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVariantControlEventHandler.cpp
* @ingroup      HMIComponent
* @author       Manali Patil
* @class        CVariantControlEventHandler: Class has the slots for all the Signals sent by CVariantControlEventHandler
*                                   which informs VariantControl Adaptor about VariantControl Resource Events
*/

#include "CVariantControlEventHandler.h"
#include "CVariantControlAdaptor.h"
#include "HMIIncludes.h"
#include "VariantControlResource/implementations/CVariantControlResourceImpl.h"
#include <ResourceFactory.hpp>
#include <VariantControlResource/implementations/CVariantControlEventProvider.h>

CVariantControlEventHandler::CVariantControlEventHandler(QObject *pParent) : QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, __FUNCTION__);
    connectSignals();
}

CVariantControlEventHandler::~CVariantControlEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, __FUNCTION__);
}

void CVariantControlEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, __FUNCTION__);

    CVariantControlResourceImpl* pVariantControlResource = static_cast<CVariantControlResourceImpl*>(ResourceFactory::getVariantControlResource());

    if (pVariantControlResource)
    {
        CVariantControlEventProvider* pVariantControlEventProvider = pVariantControlResource->getVariantControlEventProvider();

        if(pVariantControlEventProvider)
        {
            // make the signal and slot connection
            connect(pVariantControlEventProvider, SIGNAL(sigAntennaTypeReceived(int)), this, SLOT(sltAntennaTypeReceived(int)), Qt::QueuedConnection);
            connect(pVariantControlEventProvider, SIGNAL(sigEolAndroidAutoChanged(bool)), this, SLOT(sltEolAndroidAutoChangeReceived(bool)), Qt::QueuedConnection);
            connect(pVariantControlEventProvider, SIGNAL(sigEolAppleCarPlayChanged(bool)), this, SLOT(sltEolAppleCarPlayChangeReceived(bool)), Qt::QueuedConnection);
            connect(pVariantControlEventProvider, SIGNAL(sigEolDriveModeStatusDataChanged(int)), this, SLOT(sltEolDriveModeStatusReceived(int)), Qt::QueuedConnection);
            connect(pVariantControlEventProvider, SIGNAL(sigEolICCastStatusChanged(int)), this, SLOT(sltEolICCastEnabledStatusReceived(int)), Qt::QueuedConnection);
            connect(pVariantControlEventProvider, SIGNAL(sigEOLSensorCountChanged(int)), this, SLOT(sltEOLSensorCountUpdate(int)), Qt::QueuedConnection);
            connect(pVariantControlEventProvider, SIGNAL(sigEOLVIP_DIDChanged(int)), this, SLOT(sltEOLVIP_DIDUpdate(int)), Qt::QueuedConnection);
            connect(pVariantControlEventProvider, SIGNAL(sigEOLAppsDIDChanged(int)), this, SLOT(sltEOLAppsDIDUpdate(int)), Qt::QueuedConnection);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL,"pVariantControlEventProvider is null");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL,"pVariantControlResource is null");
    }
}

void CVariantControlEventHandler::sltAntennaTypeReceived(int iAntennaType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);

    if(CVariantControlAdaptor::getInstance())
    {
        CVariantControlAdaptor::getInstance()->setAntennaType(static_cast<CVariantControlEnum::EAntennaType> (iAntennaType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: CVariantControlAdaptor is NULL", __FUNCTION__);
    }
}

void CVariantControlEventHandler::sltEolAndroidAutoChangeReceived(bool bEolAndroidAutoStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);

    if(CVariantControlAdaptor::getInstance())
    {
        CVariantControlAdaptor::getInstance()->setEOLAndroidAutoEnabled(bEolAndroidAutoStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: CVariantControlAdaptor is NULL", __FUNCTION__);
    }
}

void CVariantControlEventHandler::sltEolAppleCarPlayChangeReceived(bool bEolAppleCarPlayStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);

    if(CVariantControlAdaptor::getInstance())
    {
        CVariantControlAdaptor::getInstance()->setEOLAppleCarPlayEnabled(bEolAppleCarPlayStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: CVariantControlAdaptor is NULL", __FUNCTION__);
    }
}

void CVariantControlEventHandler::sltEolDriveModeStatusReceived(int iEolDriveModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);

    if(CVariantControlAdaptor::getInstance())
    {
        CVariantControlAdaptor::getInstance()->setEOLDriveModeStatus(iEolDriveModeStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: CVariantControlAdaptor is NULL", __FUNCTION__);
    }
}

void CVariantControlEventHandler::sltEolICCastEnabledStatusReceived(int iEolICCastEnabledStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);

    if(CVariantControlAdaptor::getInstance())
    {
        CVariantControlAdaptor::getInstance()->setEOLICCastEnabledStatus(iEolICCastEnabledStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: CVariantControlAdaptor is NULL", __FUNCTION__);
    }
}

void CVariantControlEventHandler::sltEOLSensorCountUpdate(int iSensorCount)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s iSensorCount: %d", __FUNCTION__, iSensorCount);

    if(CVariantControlAdaptor::getInstance())
    {
        CVariantControlAdaptor::getInstance()->setESensorCount(iSensorCount);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: CVariantControlAdaptor is NULL", __FUNCTION__);
    }    
}

void CVariantControlEventHandler::sltEOLVIP_DIDUpdate(int iVIP_DID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s iVIP_DID: %d", __FUNCTION__, iVIP_DID);

    if(CVariantControlAdaptor::getInstance())
    {
        CVariantControlAdaptor::getInstance()->setEOLVIP_DID(iVIP_DID);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: CVariantControlAdaptor is NULL", __FUNCTION__);
    }
}

void CVariantControlEventHandler::sltEOLAppsDIDUpdate(int iAppsDID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s iAppsDID: %d", __FUNCTION__, iAppsDID);

    if(CVariantControlAdaptor::getInstance())
    {
        CVariantControlAdaptor::getInstance()->setEOLAppsDID(iAppsDID);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: CVariantControlAdaptor is NULL", __FUNCTION__);
    }
}

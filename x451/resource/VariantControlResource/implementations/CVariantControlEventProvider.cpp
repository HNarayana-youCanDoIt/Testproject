/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVariantControlEventProvider.cpp
* @ingroup      HMIComponent
* @author       Manali Patil
* CVariantControlEventProvider, Class to send signals to VariantControlHandler on VariantControl Resource events
*/


#include "CVariantControlEventProvider.h"
#include "logging.h"

CVariantControlEventProvider::CVariantControlEventProvider(QObject *pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
}

CVariantControlEventProvider::~CVariantControlEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
}

void CVariantControlEventProvider::antennaTypeStatusReceived(int iAntennaTypeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: iAntennaTypeStatus: %d", __FUNCTION__, iAntennaTypeStatus);
    emit sigAntennaTypeReceived(iAntennaTypeStatus);
}

void CVariantControlEventProvider::eolAndroidAutoStatusReceived(bool bEolAndroidAutoStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: iEolAndroidAutoStatus: %d", __FUNCTION__, bEolAndroidAutoStatus);
    emit sigEolAndroidAutoChanged(bEolAndroidAutoStatus);
}

void CVariantControlEventProvider::eolAppleCarPlayStatusReceived(bool bEolAppleCarPlayStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: iEolAppleCarPlayStatus: %d", __FUNCTION__, bEolAppleCarPlayStatus);
    emit sigEolAppleCarPlayChanged(bEolAppleCarPlayStatus);
}

void CVariantControlEventProvider::eolDriveModeStatusReceived(int iEolDriveModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: iEolDriveModeStatusOne: %d", __FUNCTION__, iEolDriveModeStatus);
    emit sigEolDriveModeStatusDataChanged(iEolDriveModeStatus);
}

void CVariantControlEventProvider::eolICCastEnabledStatusReceived(int iEolICCastEnabledStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: iEolICCastEnabledStatus: %d", __FUNCTION__, iEolICCastEnabledStatus);
    emit sigEolICCastStatusChanged(iEolICCastEnabledStatus);
}

void CVariantControlEventProvider::eolSensorCountReceived(int iSensorCount)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: iSensorCount: %d", __FUNCTION__, iSensorCount);
    emit sigEOLSensorCountChanged(iSensorCount);
}

void CVariantControlEventProvider::eolVIP_DIDReceived(int iVIP_DID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: iVIP_DID: %d", __FUNCTION__, iVIP_DID);
    emit sigEOLVIP_DIDChanged(iVIP_DID);
}

void CVariantControlEventProvider::eolAppsDIDReceived(int iAppsDID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s: iAppsDID: %d", __FUNCTION__, iAppsDID);
    emit sigEOLAppsDIDChanged(iAppsDID);
}

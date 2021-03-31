/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CVariantControlAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Manali Patil
 * CVariantControlAdaptor, an Adaptor for VariantControl module,
 * CVariantControlAdaptor used to communicate between QML and Resource Layer.
 */

#include "CVariantControlAdaptor.h"
#include "ResourceFactory.hpp"
#include "VariantControlResource/interfaces/IVariantControlResource.h"
#include "HMIIncludes.h"
#include <CFramework.h>

CVariantControlAdaptor* CVariantControlAdaptor::m_pVariantControlAdaptor = nullptr;

// Macro to check if apps is enabled within the APP_DID EOL
#define CHECK_APP_ENABLED(appDID, position) ((appDID >> position) & 1u)

CVariantControlAdaptor::CVariantControlAdaptor(QObject *pParent) : QObject(pParent),
    FIRST_BIT(1),
    m_eAntennaType(CVariantControlEnum::ANTENNA_TYPE_INVALID),
    m_bEOLAndroidAutoEnabled(false),
    m_bEOLAppleCarplayEnabled(false),
    m_iEOLDriveModeStatusData(-1),
    m_bEOLICCastEnabledStatus(false),
    m_eSensorCount(CVariantControlEnum::EN_TWO_SENSORS),
    m_eVIP_DID(CVariantControlEnum::VIP_DID_HU_HIGH_X445),
    m_iAppsDID(255), // All apps / features enable
    m_bIsDriveNextEnabled(false),
    m_bIsHMIDoodleEnabled(false),
    m_bIsW3WEnabled(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
    CVariantControlEnum::registerVariantControlEnumsToQML();
    CFramework::getFramework().setContextProperty("cppVariantControlAdaptor", this);
    if(ResourceFactory::getVariantControlResource())
    {
        setAntennaType(static_cast<CVariantControlEnum::EAntennaType>(ResourceFactory::getVariantControlResource()->getEOLAntennaType()));
        setEOLAndroidAutoEnabled(ResourceFactory::getVariantControlResource()->getEOLAndroidAutoEnabled());
        setEOLAppleCarPlayEnabled(ResourceFactory::getVariantControlResource()->getEOLAppleCarPlayEnabled());
        setEOLDriveModeStatus(ResourceFactory::getVariantControlResource()->getEOLDriveModeStatusData());
        setEOLICCastEnabledStatus(ResourceFactory::getVariantControlResource()->getEOLICCastEnabledStatus());
        setESensorCount(ResourceFactory::getVariantControlResource()->getEOLSensorCount());
        setEOLVIP_DID(ResourceFactory::getVariantControlResource()->getEOL_VIP_DID());
        setEOLAppsDID(ResourceFactory::getVariantControlResource()->getEOLAppsDID());
    }
}

CVariantControlEnum::EPDCSensorCount CVariantControlAdaptor::getESensorCount() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, m_eSensorCount: %d ", __FUNCTION__, m_eSensorCount );
    return m_eSensorCount;
}

void CVariantControlAdaptor::setESensorCount(int iSensorCount)
{

    if((iSensorCount >= CVariantControlEnum::EN_TWO_SENSORS) &&
            (iSensorCount < CVariantControlEnum::EN_TOTAL_SENSORS))
    {
        m_eSensorCount = static_cast<CVariantControlEnum::EPDCSensorCount>(iSensorCount);
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s iSensorCount: %d, ", __FUNCTION__, m_eSensorCount);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s Invalid data received from service: %d ", __FUNCTION__, iSensorCount);
    }
}

CVariantControlAdaptor::~CVariantControlAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);

    if(m_pVariantControlAdaptor)
    {
        delete m_pVariantControlAdaptor;
        m_pVariantControlAdaptor = nullptr;
    }
}

CVariantControlAdaptor* CVariantControlAdaptor::getInstance()
{
    if(!m_pVariantControlAdaptor)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
        m_pVariantControlAdaptor = new CVariantControlAdaptor();
    }
    return m_pVariantControlAdaptor;
}

void CVariantControlAdaptor::setAntennaType(CVariantControlEnum::EAntennaType eAntennaType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
    if(m_eAntennaType != eAntennaType)
    {
        m_eAntennaType = eAntennaType;
        emit sigAntennaTypeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL,"m_eAntennaType unchanged");
    }
}

void CVariantControlAdaptor::setEOLAndroidAutoEnabled(bool bEolAndroidAutoStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
    if(m_bEOLAndroidAutoEnabled != bEolAndroidAutoStatus)
    {
        m_bEOLAndroidAutoEnabled = bEolAndroidAutoStatus;
        emit sigEOLAndroidAutoEnabledChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL,"m_bEOLAndroidAutoEnabled unchanged");
    }
}

void CVariantControlAdaptor::setEOLAppleCarPlayEnabled(bool bEolAppleCarPlayStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
    if(m_bEOLAppleCarplayEnabled != bEolAppleCarPlayStatus)
    {
        m_bEOLAppleCarplayEnabled = bEolAppleCarPlayStatus;
        emit sigEOLAppleCarPlayEnabledChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL,"m_bEOLAppleCarplayEnabled unchanged");
    }
}

void CVariantControlAdaptor::setEOLDriveModeStatus(int iEolDriveModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, iEolDriveModeStatus : %d", __FUNCTION__, iEolDriveModeStatus);
    if(iEolDriveModeStatus != m_iEOLDriveModeStatusData)
    {
        m_iEOLDriveModeStatusData = iEolDriveModeStatus;
        emit sigEOLDriveModeStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL,"m_iEOLDriveModeStatusData unchanged");
    }
}

void CVariantControlAdaptor::setEOLICCastEnabledStatus(int iICCastEnabledStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, iICCastEnabledStatus : %d", __FUNCTION__, iICCastEnabledStatus);

    bool bStatus = ((iICCastEnabledStatus & FIRST_BIT) == FIRST_BIT);

    if(bStatus != m_bEOLICCastEnabledStatus)
    {
        m_bEOLICCastEnabledStatus = bStatus;
        emit sigEOLICCastEnabledStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL,"m_iEOLICCastEnabledStatus unchanged");
    }
}

void CVariantControlAdaptor::setEOLVIP_DID(int iVIP_DID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, iVIP_DID : %d", __FUNCTION__, iVIP_DID);
    if(iVIP_DID != m_eVIP_DID)
    {
        m_eVIP_DID = static_cast<CVariantControlEnum::EVIP_DID>(iVIP_DID);
        emit sigEOLVIP_DIDChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL,"iVIP_DID unchanged");
    }
}

void CVariantControlAdaptor::setEOLAppsDID(int iAppsDID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, iAppsDID : %d", __FUNCTION__, iAppsDID);
    if(iAppsDID != m_iAppsDID)
    {
        m_iAppsDID = iAppsDID;
        // Extract drive next feature enabled or not
        bool bIsDriveNextEnabled = CHECK_APP_ENABLED(iAppsDID,CVariantControlEnum::APPS_POSITION_DRIVENEXT);
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, DriveNext Enabled: %d", __FUNCTION__, bIsDriveNextEnabled);
        if (bIsDriveNextEnabled != m_bIsDriveNextEnabled)
        {
            m_bIsDriveNextEnabled = bIsDriveNextEnabled;
            emit sigEOLDriveNextEnabledChanged();
        }

        // Extract HMI doodle feature enabled or not
        bool bIsHMIDoodleEnabled = CHECK_APP_ENABLED(iAppsDID,CVariantControlEnum::APPS_POSITION_HMI_DOODLE);
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, HMIDoodle Enabled: %d", __FUNCTION__, bIsHMIDoodleEnabled);
        if (bIsHMIDoodleEnabled != m_bIsHMIDoodleEnabled)
        {
            m_bIsHMIDoodleEnabled = bIsHMIDoodleEnabled;
            emit sigEOLHMIDoodleEnabledChanged();
        }

        // Extract W3W feature enabled or not
        bool bIsW3WEnabled = CHECK_APP_ENABLED(iAppsDID,CVariantControlEnum::APPS_POSITION_W3W);
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, W3W Enabled: %d", __FUNCTION__, bIsW3WEnabled);
        if (bIsW3WEnabled != m_bIsW3WEnabled)
        {
            m_bIsW3WEnabled = bIsW3WEnabled;
            emit sigEOLW3WEnabledChanged();
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL,"iAppsDID unchanged");
    }
}

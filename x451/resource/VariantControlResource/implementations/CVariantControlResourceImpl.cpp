/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVariantControlResourceImpl.cpp
* @ingroup      HMIComponent
* @author       Manali Patil
* CVariantControlResourceImpl, Resource Implementation for VariantControlHandler
*/

#include "CVariantControlResourceEnums.h"
#include "CVariantControlResourceImpl.h"
#include "CVariantControlEventProvider.h"
#include <ResourceMaster.h>
#include "logging.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ResourceDeploymentConfig.h"
#ifndef PLATFORM_WIN32
#include <unistd.h>
#endif

#define BOOTINFOSIZE 			64
#define BOOTINFOPATH 			"/proc/bootinfo"

#define EOL_INDEX_ANTENNA_TYPE          33
#define EOL_INDEX_ANDROID_AUTO          22
#define EOL_INDEX_CAR_PLAY              24
#define EOL_INDEX_DRIVE_MODE_ONE        43
#define EOL_INDEX_DRIVE_MODE_TWO        44
#define EOL_INDEX_IC_CAST               30
#define EOL_PDC_SENSOR_COUNT            50      /* EOL byte starts from 21 and the parameters for sensor count is at 29 */
#define EOL_APPS_DID                    51      /* EOL byte starts from 21 and the parameters for Apps DID is at 30-31 */
#define EOL_VIP_DID                     53      /* EOL byte starts from 21 and the parameters for VIP DID is at 32 */

CVariantControlResourceImpl::CVariantControlResourceImpl():
    m_pVariantControlEventProvider(new CVariantControlEventProvider()),
    m_iAntennaType(-1),
    m_bAndroidAutoEnabled(false),
    m_bAppleCarPlayEnabled(false),
    m_iDriveModeStatusData(-1),
    m_iICCastEnabledStatus(-1),
    m_iSensorCount(0),
    m_iVIP_DID(EVehicleInfotainmentPlatform::VIP_DID_HU_HIGH_X445), // Need to get the correct value from TML. Currently setting it as x445
    m_iAppsDID(255) // Need to get the correct defautl value from TML. Currently setting it as all features enabled hence 255
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
    readEolParameters();
}

CVariantControlResourceImpl::~CVariantControlResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
    if (m_pVariantControlEventProvider)
    {
        delete m_pVariantControlEventProvider;
        m_pVariantControlEventProvider = nullptr;
    }
}

CVariantControlEventProvider* CVariantControlResourceImpl::getVariantControlEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);
    return m_pVariantControlEventProvider;
}

void CVariantControlResourceImpl::readEolParameters()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s", __FUNCTION__);

    int iDriveModeStatusOne = 0;
    int iDriveModeStatusTwo = 0;

    int iAntennaType = m_iAntennaType;
    bool bAndroidAutoEnabled = m_bAndroidAutoEnabled;
    bool bAppleCarPlayEnabled = m_bAppleCarPlayEnabled;
    int iDriveModeStatusData = m_iDriveModeStatusData;
    int iICCastEnabledStatus = m_iICCastEnabledStatus;
    int iSensorCount         = m_iSensorCount;
    int iVIP_DID = m_iVIP_DID;
    int iAppsDID = m_iAppsDID;

#if (defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86))
    iAntennaType = -1;
    bAndroidAutoEnabled = true;
    bAppleCarPlayEnabled = true;
    iDriveModeStatusData = -1;
    iICCastEnabledStatus = -1;
    iAppsDID = 70;// Enabling W3W(64), HMIDoodle(4), DrivePro(2) Setting X445 as app for simulation.
#else
    int iFileDescriptor = 0;
    iFileDescriptor = open(BOOTINFOPATH, O_RDONLY);

    if (iFileDescriptor < 0)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Opening /proc/bootinfo file failed", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Opening /proc/bootinfo file succeded", __FUNCTION__);

        char Earlybuf[BOOTINFOSIZE];
        int ret = read(iFileDescriptor, static_cast<char *>(Earlybuf), BOOTINFOSIZE);

        if (ret < 0)
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Reading /proc/bootinfo file failed", __FUNCTION__);
        }
        else
        {
            iAntennaType = Earlybuf[EOL_INDEX_ANTENNA_TYPE];
            LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Reading /proc/bootinfo file succeded EOL_INDEX_ANTENNA_TYPE : %d", __FUNCTION__,iAntennaType);

            bAndroidAutoEnabled = (Earlybuf[EOL_INDEX_ANDROID_AUTO] == 1);
            LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Reading /proc/bootinfo file succeded EOL_INDEX_ANDROID_AUTO : %d", __FUNCTION__, bAndroidAutoEnabled);

            bAppleCarPlayEnabled = (Earlybuf[EOL_INDEX_CAR_PLAY ] == 1);
            LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Reading /proc/bootinfo file succeded EOL_INDEX_CAR_PLAY  : %d", __FUNCTION__, bAppleCarPlayEnabled);

            iDriveModeStatusOne = Earlybuf[EOL_INDEX_DRIVE_MODE_ONE];
            LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Reading /proc/bootinfo file succeded EOL_INDEX_DRIVE_MODE_ONE  : %d", __FUNCTION__, iDriveModeStatusOne);

            iDriveModeStatusTwo = Earlybuf[EOL_INDEX_DRIVE_MODE_TWO];
            LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Reading /proc/bootinfo file succeded EOL_INDEX_DRIVE_MODE_TWO  : %d", __FUNCTION__, iDriveModeStatusTwo);

            iICCastEnabledStatus = Earlybuf[EOL_INDEX_IC_CAST];
            LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Reading /proc/bootinfo file succeded EOL_INDEX_IC_CAST  : %d", __FUNCTION__, iICCastEnabledStatus);

            iSensorCount = Earlybuf[EOL_PDC_SENSOR_COUNT];
            LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Reading /proc/bootinfo file succeded EOL_PDC_SENSOR_COUNT  : %d", __FUNCTION__, iSensorCount);

            iVIP_DID = Earlybuf[EOL_VIP_DID];
            LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Reading /proc/bootinfo file succeded EOL_VIP_DID  : %d", __FUNCTION__, iVIP_DID);

            iAppsDID = Earlybuf[EOL_APPS_DID];
            LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s, Reading /proc/bootinfo file succeded EOL_APPS_DID  : %d", __FUNCTION__, iAppsDID);
        }
        close(iFileDescriptor);
    }
#endif

    if(m_pVariantControlEventProvider)
    {
        if(iAntennaType != m_iAntennaType)
        {
            m_iAntennaType = iAntennaType;
            m_pVariantControlEventProvider->antennaTypeStatusReceived(m_iAntennaType);
        }

        if(bAndroidAutoEnabled != m_bAndroidAutoEnabled)
        {
            m_bAndroidAutoEnabled = bAndroidAutoEnabled;
            m_pVariantControlEventProvider->eolAndroidAutoStatusReceived(m_bAndroidAutoEnabled);
        }
        if(bAppleCarPlayEnabled != m_bAppleCarPlayEnabled)
        {
            m_bAppleCarPlayEnabled = bAppleCarPlayEnabled;
            m_pVariantControlEventProvider->eolAppleCarPlayStatusReceived(m_bAppleCarPlayEnabled);
        }

        iDriveModeStatusData = ((iDriveModeStatusTwo << 8) | iDriveModeStatusOne);

        if(iDriveModeStatusData != m_iDriveModeStatusData)
        {
            m_iDriveModeStatusData = iDriveModeStatusData;
            m_pVariantControlEventProvider->eolDriveModeStatusReceived(m_iDriveModeStatusData);
        }
        if(iICCastEnabledStatus != m_iICCastEnabledStatus)
        {
            m_iICCastEnabledStatus = iICCastEnabledStatus;
            m_pVariantControlEventProvider->eolICCastEnabledStatusReceived(m_iICCastEnabledStatus);
        }

        if(iSensorCount != m_iSensorCount)
        {
            m_iSensorCount = iSensorCount;
            m_pVariantControlEventProvider->eolSensorCountReceived(m_iSensorCount);
        }

        if ((iVIP_DID != 0) && (iVIP_DID != 255) && (iVIP_DID != m_iVIP_DID))
        {
            m_iVIP_DID = validateVIP_DID(iVIP_DID);
            m_pVariantControlEventProvider->eolVIP_DIDReceived(m_iVIP_DID);
        }

        if (iAppsDID != m_iAppsDID)
        {
            m_iAppsDID = iAppsDID;
            m_pVariantControlEventProvider->eolAppsDIDReceived(m_iAppsDID);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER,"m_pVariantControlEventProvider is null");
    }
}

int CVariantControlResourceImpl::getEOLSensorCount()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VARIANT_CONTROL, "%s SensorCount: %d ", __FUNCTION__, m_iSensorCount);
    return m_iSensorCount;
}

int CVariantControlResourceImpl::validateVIP_DID(int iDID)
{
    int validValue = static_cast<int>(EVehicleInfotainmentPlatform::VIP_DID_HU_HIGH_X445);

    switch(iDID)
    {
    case EVehicleInfotainmentPlatform::VIP_DID_HU_HIGH_X451:
    case EVehicleInfotainmentPlatform::VIP_DID_HU_NEXON_LEVEL_B_VAVE:
    case EVehicleInfotainmentPlatform::VIP_DID_HU_NEXON_EV_HIGH:
    case EVehicleInfotainmentPlatform::VIP_DID_HU_NEXON_MCE:
	case EVehicleInfotainmentPlatform::VIP_DID_HU_HIGH_X445:
        validValue = iDID;
        break;
    default:
        //Do Nothing
        break;
    }

    return validValue;
}

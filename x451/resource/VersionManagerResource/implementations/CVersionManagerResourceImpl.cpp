/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CVersionManagerResourceImpl.cpp
* @ingroup      HMIComponent
* @author       Rajat Gupta
* CVersionManagerResourceImpl, Resource Implementation for VersionManagerHandler
*/

#include "CVersionManagerResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"

CVersionManagerResourceImpl::CVersionManagerResourceImpl():
    m_pVersionManagerEventProvider(new CVersionManagerEventProvider()),
    m_VersionManagerProxy(ResourceDeploymentConfig::getConfig().m_VersionManager_Proxy.domain
                         ,ResourceDeploymentConfig::getConfig().m_VersionManager_Proxy.instance),
    VEHICLE_ID_NUMBER("VEHICLE_ID_NUMBER"),
    VEHICLE_CFG_INFO_NUMBER("VEHICLE_CFG_INFO"),
    BUTTON_PANEL_16R_NUMBER_ECU_HW("BUTTON_PANEL_16R_NUMBER_ECU_HW"),
    DISPLAY_16R_NUMBER_ECU_HW("DISPLAY_16R_NUMBER_ECU_HW"),
    PARAMETERIZATION_PART_NUMBER("PARAMETERIZATION_PART_NUMBER"),
    SILVERBOX_HARDWARE_PART_NUMBER("SILVERBOX_HARDWARE_PART_NUMBER"),
    CONTAINER_PART_NUMBER("CONTAINER_PART_NUMBER"),
    SOC("SOC"),
    BUTTON_PANEL("BUTTON_PANEL"),
    DISPLAY("DISPLAY"),
    VERSION_DETAILS_TIMEOUT(15000)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    subscribeVersionManagerProxy();
}

void CVersionManagerResourceImpl::subscribeVersionManagerProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    SUBSCRIBE(m_VersionManagerProxy,getProxyStatusEvent(), &CVersionManagerResourceImpl::versionManagerStatusCb, _1);
}

CVersionManagerResourceImpl::~CVersionManagerResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    if (m_pVersionManagerEventProvider)
    {
        delete m_pVersionManagerEventProvider;
    }
}

CVersionManagerEventProvider* CVersionManagerResourceImpl::getVersionManagerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    return m_pVersionManagerEventProvider;
}

void CVersionManagerResourceImpl::versionManagerStatusCb(CommonAPI::AvailabilityStatus status)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s", __FUNCTION__);

    if (CommonAPI::AvailabilityStatus::AVAILABLE == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: Version manager status is available.", __FUNCTION__);
        // APIs call to 16R part numbers
        m_VersionManagerProxy->get16RPartNumberInAsciiAsync(versionmanagertypes_tata::_16RPartName_e::VEHICLE_CFG_INFO_NUMBER, std::bind(&CVersionManagerResourceImpl::get16RPartNumberAsyncCb, this, _1, _2));
        m_VersionManagerProxy->get16RPartNumberInAsciiAsync(versionmanagertypes_tata::_16RPartName_e::VEHICLE_ID_NUMBER, std::bind(&CVersionManagerResourceImpl::get16RPartNumberAsyncCb, this, _1, _2));
        m_VersionManagerProxy->get16RPartNumberInAsciiAsync(versionmanagertypes_tata::_16RPartName_e::CONTAINER_PART_NUMBER, std::bind(&CVersionManagerResourceImpl::get16RPartNumberAsyncCb, this, _1, _2));
        m_VersionManagerProxy->get16RPartNumberInAsciiAsync(versionmanagertypes_tata::_16RPartName_e::SILVERBOX_HARDWARE_PART_NUMBER, std::bind(&CVersionManagerResourceImpl::get16RPartNumberAsyncCb, this, _1, _2));
        m_VersionManagerProxy->get16RPartNumberInAsciiAsync(versionmanagertypes_tata::_16RPartName_e::DISPLAY_16R_NUMBER_ECU_HW, std::bind(&CVersionManagerResourceImpl::get16RPartNumberAsyncCb, this, _1, _2));
        m_VersionManagerProxy->get16RPartNumberInAsciiAsync(versionmanagertypes_tata::_16RPartName_e::PARAMETERIZATION_PART_NUMBER, std::bind(&CVersionManagerResourceImpl::get16RPartNumberAsyncCb, this, _1, _2));
        m_VersionManagerProxy->get16RPartNumberInAsciiAsync(versionmanagertypes_tata::_16RPartName_e::BUTTON_PANEL_16R_NUMBER_ECU_HW, std::bind(&CVersionManagerResourceImpl::get16RPartNumberAsyncCb, this, _1, _2));
        m_VersionManagerProxy->getPowerModeCfgTypeAsync(std::bind(&CVersionManagerResourceImpl::getPowerModeCfgTypeAsyncCb, this, _1, _2));

        //API's Call to Software Version Number
        CallInfo objCallInfoData(VERSION_DETAILS_TIMEOUT);
        m_VersionManagerProxy->getVersionDetailsAsync(versionmanagertypes_tata::VersionName_e::SOC, std::bind(&CVersionManagerResourceImpl::getVersionDetailsAsyncCb, this, _1, _2), &objCallInfoData);
        m_VersionManagerProxy->getVersionDetailsAsync(versionmanagertypes_tata::VersionName_e::BUTTON_PANEL, std::bind(&CVersionManagerResourceImpl::getVersionDetailsAsyncCb, this, _1, _2), &objCallInfoData);
        m_VersionManagerProxy->getVersionDetailsAsync(versionmanagertypes_tata::VersionName_e::DISPLAY, std::bind(&CVersionManagerResourceImpl::getVersionDetailsAsyncCb, this, _1, _2), &objCallInfoData);

        SUBSCRIBE(m_VersionManagerProxy,getVersionMismatchAttribute().getChangedEvent(),&CVersionManagerResourceImpl::onVersionMismatchEventStatusCb,_1);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: Version manager status is not available: %d", __FUNCTION__, static_cast<int>(status));
    }
}

CVersionManagerEnums::SVersionInformation CVersionManagerResourceImpl::fetchVersionInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SYSTEM,"%s", __FUNCTION__);
    return m_sVersionInfo;
}

void CVersionManagerResourceImpl::onVersionMismatchEventStatusCb(versionmanagertypes_tata::VersionMismatchDetails_e eMismatchType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s %d",__FUNCTION__, eMismatchType.value_);
    m_pVersionManagerEventProvider->versionMismatchEventReceived(eMismatchType);
}

void CVersionManagerResourceImpl::get16RPartNumberAsyncCb(const CommonAPI::CallStatus& status, const versionmanagertypes_tata::_16RPartDetails_t& t_16RpartInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: get16RPartNumberAsyncCb call status: %d", __FUNCTION__, static_cast<int>(status));

    if (CommonAPI::CallStatus::SUCCESS == status)
    {
        if (NULL != m_pVersionManagerEventProvider)
        {
            string str16RPartNo = t_16RpartInfo.getS_16RPartName();

            if (VEHICLE_ID_NUMBER == str16RPartNo)
            {
                m_pVersionManagerEventProvider->vinPartNumberReceived(t_16RpartInfo.getS_16RPartData().c_str ());
            }
            else if (VEHICLE_CFG_INFO_NUMBER == str16RPartNo)
            {
                m_pVersionManagerEventProvider->vcInfoNumberReceived(t_16RpartInfo.getS_16RPartData().c_str ());
            }
            else if (CONTAINER_PART_NUMBER == str16RPartNo)
            {
                m_pVersionManagerEventProvider->containerPartNoReceived(t_16RpartInfo.getS_16RPartData().c_str ());
            }
            else if (SILVERBOX_HARDWARE_PART_NUMBER == str16RPartNo)
            {
                m_pVersionManagerEventProvider->silverBoxPartNoReceived(t_16RpartInfo.getS_16RPartData().c_str ());
            }
            else if (DISPLAY_16R_NUMBER_ECU_HW == str16RPartNo)
            {
                m_pVersionManagerEventProvider->displayHWPartNoReceived(t_16RpartInfo.getS_16RPartData().c_str ());
            }
            else if (PARAMETERIZATION_PART_NUMBER == str16RPartNo)
            {
                m_pVersionManagerEventProvider->parameterizationPartNoReceived(t_16RpartInfo.getS_16RPartData().c_str ());
            }
            else if (BUTTON_PANEL_16R_NUMBER_ECU_HW == str16RPartNo)
            {
                m_pVersionManagerEventProvider->buttonPanelPartNoReceived(t_16RpartInfo.getS_16RPartData().c_str ());
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: 16R Part Name is not valid", __FUNCTION__);
            }

        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: m_pVersionManagerEventProvider is null.", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s:get16RPartNumberAsyncCb call status is not success.", __FUNCTION__ );
    }
}

void CVersionManagerResourceImpl::getVersionDetailsAsyncCb(const CallStatus &status, const versionmanagertypes_tata::versionInfo_t &t_versionInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: getVersionDetailsAsyncCb call status: %d", __FUNCTION__, static_cast<int>(status));

    if (CommonAPI::CallStatus::SUCCESS == status)
    {
        if (NULL != m_pVersionManagerEventProvider)
        {
            if (SOC == t_versionInfo.getS_versionName())
            {
                m_sVersionInfo.versionData = t_versionInfo.getS_versionData();
                m_sVersionInfo.versionName = t_versionInfo.getS_versionName();
                m_sVersionInfo.versionReleasedDate = t_versionInfo.getS_versionReleasedDate();
                m_pVersionManagerEventProvider->socSofVersionNoUpdateReceived(t_versionInfo.getS_versionData().c_str ());
            }
            else if (BUTTON_PANEL == t_versionInfo.getS_versionName ())
            {
                m_pVersionManagerEventProvider->buttonPanelSofVersionNoUpdateReceived(t_versionInfo.getS_versionData().c_str ());
            }

            else if (DISPLAY == t_versionInfo.getS_versionName ())
            {
                m_pVersionManagerEventProvider->displayManagerSofVersionNoUpdateReceived(t_versionInfo.getS_versionData().c_str ());
            }

            else
                LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: Software Version Info is not valid", __FUNCTION__);
        }

        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: m_pVersionManagerEventProvider is null.", __FUNCTION__);
        }
    }

    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s:getVersionDetailsAsyncCb call status is not success.", __FUNCTION__ );
    }
}


void CVersionManagerResourceImpl::getPowerModeCfgTypeAsyncCb(const CommonAPI::CallStatus& status, const versionmanagertypes_tata::_16RPartDetails_t& t_powerModeConfigInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: getPowerModeCfgTypeAsyncCb call status: %d, Power Mode Type: %s", __FUNCTION__, static_cast<int>(status), t_powerModeConfigInfo.getS_16RPartData().c_str());
    m_pVersionManagerEventProvider->powerModeCfgTypeReceived(t_powerModeConfigInfo.getS_16RPartData());
}

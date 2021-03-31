/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CSoftwareUpdateResourceImpl.cpp
* @ingroup      HMIComponent
* @author       Nishant Khandagale
* CSoftwareUpdateResourceImpl, Resource Implementation for SoftwareUpdateHandler
*/

#include "CSoftwareUpdateResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"

const char* CSoftwareUpdateResourceImpl::SBX_VERSION = "SbxVersion";

CSoftwareUpdateResourceImpl::CSoftwareUpdateResourceImpl():
    m_pSoftwareUpdateEventProvider(new CSoftwareUpdateEventProvider()),
    m_SoftwareUpdateProxy(ResourceDeploymentConfig::getConfig().m_SoftwareUpdate_Proxy.domain,ResourceDeploymentConfig::getConfig().m_SoftwareUpdate_Proxy.instance),
    m_bSoftwareUpdateAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    mSWImageList.clear();
    m_updateDetailsList.clear();
    subscribeSoftwareUpdateProxy();
}

void CSoftwareUpdateResourceImpl::subscribeSoftwareUpdateProxy()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);

    // Software update proxy subscriptions
    SUBSCRIBE(m_SoftwareUpdateProxy,getProxyStatusEvent(),&CSoftwareUpdateResourceImpl::statusEventListnerSoftwareUpdate,_1);
    SUBSCRIBE(m_SoftwareUpdateProxy,getSoftwareAvailableForInstallAttrAttribute().getChangedEvent(),&CSoftwareUpdateResourceImpl::onSWAvailable,_1);
    SUBSCRIBE(m_SoftwareUpdateProxy,getSoftwareUpdateStatusEvent(),&CSoftwareUpdateResourceImpl::onSoftwareUpdateStatus,_1,_2);
}

CSoftwareUpdateResourceImpl::~CSoftwareUpdateResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    mSWImageList.clear();
    m_updateDetailsList.clear();
    if (m_pSoftwareUpdateEventProvider)
    {
        delete m_pSoftwareUpdateEventProvider;
    }
}


void CSoftwareUpdateResourceImpl::statusEventListnerSoftwareUpdate(AvailabilityStatus status)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
    if(CommonAPI::AvailabilityStatus::AVAILABLE == status)
    {
        m_bSoftwareUpdateAvailable = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s, Software settings NOT AVAILABLE ", __FUNCTION__);
        m_bSoftwareUpdateAvailable = false;
    }
    m_pSoftwareUpdateEventProvider->updateSwAvailabilityStatus(m_bSoftwareUpdateAvailable);
}


CSoftwareUpdateEventProvider* CSoftwareUpdateResourceImpl::getSoftwareUpdateEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    return m_pSoftwareUpdateEventProvider;
}


void CSoftwareUpdateResourceImpl::checkForUpdate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s value %d" ,__FUNCTION__, m_bSoftwareUpdateAvailable);
    if(m_bSoftwareUpdateAvailable)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "%s, Check for update requested", __FUNCTION__);
        CallInfo objCallInfoData(SW_CHECKFORUPDATE_CAPI_TIMEOUT);
        m_SoftwareUpdateProxy->CheckForUpdatesAsync(std::bind(&CSoftwareUpdateResourceImpl::asyncCbCheckForUpdate,this, _1,_2, _3)
                                                    , &objCallInfoData);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "%s, Service not available", __FUNCTION__);
    }
}

void CSoftwareUpdateResourceImpl::asyncCbCheckForUpdate(const CommonAPI::CallStatus& status, const SoftwareUpdateTypes::eMethodResult& mResult, const SoftwareUpdateTypes::tUpdateSearchResult& searchResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"SoftwareUpdateResourceImpl::asyncCbCheckForUpdate: %d %d %d", static_cast<int>(searchResult.getUpdateAvailability().value_) ,
             static_cast<int>(status),static_cast<int>(mResult));
    if((CommonAPI::CallStatus::SUCCESS == status) && (SoftwareUpdateTypes::eMethodResult::REQ_OK == mResult))
    {
        if (m_pSoftwareUpdateEventProvider)
        {
            if(NO_UPDATE_AVAILABLE == searchResult.getUpdateAvailability().value_)
            {
                m_pSoftwareUpdateEventProvider->updateSwAvailability(NO_UPDATE_AVAILABLE);
            }
            else if(UPDATE_ALREADY_IN_PROGRESS == searchResult.getUpdateAvailability().value_)
            {
                m_pSoftwareUpdateEventProvider->updateSwAvailability(UPDATE_ALREADY_IN_PROGRESS);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "%s, updateAvailability: %d", __FUNCTION__, static_cast<int>(searchResult.getUpdateAvailability().value_));
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "%s, m_pSoftwareUpdateEventProvider is null", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "%s, status and result not successful ", __FUNCTION__);
        if (m_pSoftwareUpdateEventProvider)
        {
            m_pSoftwareUpdateEventProvider->updateSwAvailability(NO_UPDATE_AVAILABLE);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "%s, m_pSoftwareUpdateEventProvider is null", __FUNCTION__);
        }
    }
}

void CSoftwareUpdateResourceImpl::CancelUpdateAsyncCb(const CallStatus &eCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    if(CommonAPI::CallStatus::SUCCESS == eCallStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"CancelUpdateAsyncCb succeeded ");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"CancelUpdateAsyncCb failed ");
    }
}

void CSoftwareUpdateResourceImpl::DeclineUpdateAsyncCb(const CallStatus &eCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    if(CommonAPI::CallStatus::SUCCESS == eCallStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"DeclineUpdateAsyncCb succeeded ");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"DeclineUpdateAsyncCb failed ");
    }
}


void CSoftwareUpdateResourceImpl::onSWAvailable(SoftwareUpdateTypes::tPackageList packageList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    fillDetails(packageList);
}

void CSoftwareUpdateResourceImpl::onSoftwareUpdateStatus(SoftwareUpdateTypes::tStatus status, SoftwareUpdateTypes::eUpdateSource eUpdateSource)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    Q_UNUSED(eUpdateSource);
    SoftwareUpdateTypes::tErrorInfo  errorInfo = status.getErrorInfo();
    if(ESoftwareUpdateError::PACKAGE_VALIDATION_FAILED == errorInfo.getErrorCode())
    {
        m_pSoftwareUpdateEventProvider->updateError(ESoftwareUpdateError::PACKAGE_VALIDATION_FAILED);
    }
    else if(MSD_DISCONNECTED == errorInfo.getErrorCode())
    {
        m_pSoftwareUpdateEventProvider->updateError(ESoftwareUpdateError::MSD_DISCONNECTED);
    }
    else
    {
        //do nothing for other errors
    }
}

void CSoftwareUpdateResourceImpl::fillDetails(SoftwareUpdateTypes::tPackageList packageList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);

    bool bSwAvailableForInstall = false;
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s, list size: %zd",__FUNCTION__, packageList.size());
    mSWImageList.clear();
    m_updateDetailsList.clear();
    mSWImageList = packageList;

    for (SoftwareUpdateTypes::tPackageList::iterator it = packageList.begin(); it != packageList.end(); ++it)
    {
        SUpdateSearchResult updateDetails;
        updateDetails._packageDetails.eSource = (ESoftwareUpdateSource)it->getSource().value_;
        updateDetails._packageDetails.strPackageName = it->getPackageName();
        updateDetails._packageDetails.strVersion = it->getVersion();
        updateDetails._packageDetails.uiPackageSize = it->getPackageSize();
        m_updateDetailsList.push_back(updateDetails);
        bSwAvailableForInstall = true;
    }

    if(m_pSoftwareUpdateEventProvider)
    {
        if (true == bSwAvailableForInstall)
        {
            m_pSoftwareUpdateEventProvider->updateSoftware();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "SW not available for install");
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s, Event provider is NULL",__FUNCTION__);
    }
    /* Signal EventProvider, update list information received from below layer.
     * Do not send any structure to the above layers. On receiving this signal the Adaptor will call the getPackageDetails
     * on the resources
     */
}

void CSoftwareUpdateResourceImpl::requestSWUpdate(int index)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s index: %d", __FUNCTION__, index );
    if(m_bSoftwareUpdateAvailable)
    {
        int iSWImageListSize = static_cast<int>(mSWImageList.size());//cast the unsigned int to an int since it may store a -1 value
        if ((index >=0) && (index < iSWImageListSize))
        {
            SoftwareUpdateTypes::tPackageDetails installPackage = mSWImageList[index];
            LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s name: %s", __FUNCTION__, installPackage.getPackageName().c_str() );
            m_SoftwareUpdateProxy->RequestInstallPackageAsync(installPackage);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "index out of bound");
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "Service not available");
    }
}

std::list<SUpdateSearchResult> CSoftwareUpdateResourceImpl::getPackageDetails()
{
    return m_updateDetailsList;
}

void CSoftwareUpdateResourceImpl::cancelUpdate(ESoftwareUpdateCancelType eCancelType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    if(m_bSoftwareUpdateAvailable)
    {
        if(ESoftwareUpdateCancelType::CANCEL_INSTALL  == eCancelType )
        {
            m_SoftwareUpdateProxy->RequestInstallAsync(SoftwareUpdateTypes::eRequestInstall::CANCEL_INSTALLATION,std::bind(&CSoftwareUpdateResourceImpl::CancelUpdateAsyncCb,this, _1));
        }
        else if(ESoftwareUpdateCancelType::DECLINE_INSTALL == eCancelType )
        {
            m_SoftwareUpdateProxy->RequestInstallAsync(SoftwareUpdateTypes::eRequestInstall::DECLINE_INSTALLATION,std::bind(&CSoftwareUpdateResourceImpl::DeclineUpdateAsyncCb,this, _1));
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "Service not available");
    }

}

void CSoftwareUpdateResourceImpl::reqInstallVerMismatch(uint uiMismatchType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);

    if(m_bSoftwareUpdateAvailable)
    {
        SoftwareUpdateTypes::tPackageDetails objPackageDetails;
        objPackageDetails.setSource(SoftwareUpdateTypes::eUpdateSource::UPDATE_SOURCE_ALL);
        objPackageDetails.setDescription("");
        objPackageDetails.setVersion("");
        objPackageDetails.setPackageSize(0);
        objPackageDetails.setEstimatedInstallTime(0);
        if(versionMismatchType::BP_DM_VERSION_MISMATCH == uiMismatchType)
        {
            objPackageDetails.setPackageName(m_strBP_DM_VerMismatchFileName);
            objPackageDetails.setPackageLocation(m_strBP_DM_VerMismatchFilePath);
            m_SoftwareUpdateProxy->RequestInstallPackageAsync(objPackageDetails,std::bind(&CSoftwareUpdateResourceImpl::InstallPackageVerMismatchAsyncCb,this, _1));
        }
        else if(versionMismatchType::BUTTON_PANEL_VERSION_MISMATCH == uiMismatchType)
        {
            objPackageDetails.setPackageName(m_strBP_VerMismatchFileName);
            objPackageDetails.setPackageLocation(m_strBP_VerMismatchFilePath);
            m_SoftwareUpdateProxy->RequestInstallPackageAsync(objPackageDetails,std::bind(&CSoftwareUpdateResourceImpl::InstallPackageVerMismatchAsyncCb,this, _1));
        }
        else if(versionMismatchType::DISPLAY_VERSION_MISMATCH == uiMismatchType)
        {
            objPackageDetails.setPackageName(m_strDM_VerMismatchFileName);
            objPackageDetails.setPackageLocation(m_strDM_VerMismatchFilePath);
            m_SoftwareUpdateProxy->RequestInstallPackageAsync(objPackageDetails,std::bind(&CSoftwareUpdateResourceImpl::InstallPackageVerMismatchAsyncCb,this, _1));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s -- There is no version mismatch", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE, "Service not available");
    }
}

void CSoftwareUpdateResourceImpl::InstallPackageVerMismatchAsyncCb(const CallStatus &status)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    if(CommonAPI::CallStatus::SUCCESS == status)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"InstallPackageVerMismatchAsyncCb succeeded ");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"InstallPackageVerMismatchAsyncCb failed ");
    }
}

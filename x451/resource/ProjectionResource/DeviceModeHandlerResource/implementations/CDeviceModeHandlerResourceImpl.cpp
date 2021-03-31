/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDeviceModeHandlerResourceImpl.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* CDeviceModeHandlerResourceImpl, Resource Implementation for DeviceModeHandler.
*/

#include "CDeviceModeHandlerResourceImpl.h"
#include "logging.h"
#include "ResourceMaster.h"
#include "ResourceDeploymentConfig.h"

using namespace std;
using namespace v1::com::harman::pres;

CDeviceModeHandlerResourceImpl::CDeviceModeHandlerResourceImpl():
    m_pDeviceModeHandlerEventProvider(new CDeviceModeHandlerEventProvider()),
    m_objDeviceModeHandlerProxy(ResourceDeploymentConfig::getConfig().m_DeviceModeHandler_Proxy.domain,
                                ResourceDeploymentConfig::getConfig().m_DeviceModeHandler_Proxy.instance),
    m_bIsDeviceModeHandlerAvailable(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    SUBSCRIBE(m_objDeviceModeHandlerProxy, getProxyStatusEvent(),
              &CDeviceModeHandlerResourceImpl::deviceModeHandlerServiceStatusCb, _1);
    subscribe();
}

CDeviceModeHandlerResourceImpl::~CDeviceModeHandlerResourceImpl()
{
    if(m_pDeviceModeHandlerEventProvider)
    {
        delete m_pDeviceModeHandlerEventProvider;
        m_pDeviceModeHandlerEventProvider = NULL;
    }
}

CDeviceModeHandlerEventProvider* CDeviceModeHandlerResourceImpl::getDeviceModeHandlerEventProvider()
{
    return m_pDeviceModeHandlerEventProvider;
}

/******************************************************//**
 * @category INTERNAL METHODS
 *******************************************************/

void CDeviceModeHandlerResourceImpl::subscribe()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    SUBSCRIBE(m_objDeviceModeHandlerProxy, getDeviceInsertedEvent(), &CDeviceModeHandlerResourceImpl::deviceInsertedCb, _1);
    SUBSCRIBE(m_objDeviceModeHandlerProxy, getDeviceRemovedEvent(), &CDeviceModeHandlerResourceImpl::deviceRemovedCb, _1);
    SUBSCRIBE(m_objDeviceModeHandlerProxy, getModeStatusEvent(), &CDeviceModeHandlerResourceImpl::modeStatusCb, _1, _2, _3, _4, _5);

    /* Function to get the Device inserted info when Dev press proxy gets available. */
    m_objDeviceModeHandlerProxy->getinserteddeviceinfoAsync(std::bind(&CDeviceModeHandlerResourceImpl::getInsertedDeviceInfoAsyncCb, this, _1, _2));

}

EDeviceType CDeviceModeHandlerResourceImpl::getDeviceTypeEnum(const devprestypes::eDeviceType &eDeviceTypeRcv)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Recieved Device Type: %d ", __FUNCTION__, eDeviceTypeRcv.value_);

    EDeviceType eDeviceType = DEVICE_TYPE_UNKNOWN;

    switch(eDeviceTypeRcv.value_)
    {
    case devprestypes::eDeviceType::USB_MSD:
        eDeviceType = DEVICE_TYPE_USB_MSD;
        break;
    case devprestypes::eDeviceType::IPHONE:
        eDeviceType = DEVICE_TYPE_IPHONE;
        break;
    case devprestypes::eDeviceType::ANDROID_PHONE:
        eDeviceType = DEVICE_TYPE_ANDROID_PHONE;
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Wrong value for Device Type passed.", __FUNCTION__);
        break;
    }

    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Converted Device Type is: %d", __FUNCTION__, eDeviceType);

    return eDeviceType;
}

void CDeviceModeHandlerResourceImpl::startModeReq(const devprestypes::eModeName &eModeName, uint8_t uiDeviceID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: , eModeName: %d", __FUNCTION__, eModeName.value_);

    if (m_bIsDeviceModeHandlerAvailable)
    {
        switch(eModeName)
        {
        case devprestypes::eModeName::USB_ANDROID_ANDROIDAUTO:
            m_objDeviceModeHandlerProxy->startModeAsync(uiDeviceID, eModeName, true, std::bind(&CDeviceModeHandlerResourceImpl::startModeAsyncCb, this, _1, _2));
            break;
        case devprestypes::eModeName::USB_ANDROID_SAL:
            break;
        case devprestypes::eModeName::USB_IPHONE_CARPLAY:
            m_objDeviceModeHandlerProxy->startModeAsync(uiDeviceID, eModeName, true, std::bind(&CDeviceModeHandlerResourceImpl::startModeAsyncCb, this, _1, _2));
            break;
        case devprestypes::eModeName::USB_IPHONE_IPOD:
            break;
        case devprestypes::eModeName::USB_IPHONE_SAL:
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Mode Name not handled.", __FUNCTION__);
            break;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION,"Device Mode Handler proxy not available");
    }
}

void CDeviceModeHandlerResourceImpl::setProjectionConnectionStatus(const devprestypes::sModeInfo &objModeInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: ModeName: %d, ModeStatus: %d",__FUNCTION__, objModeInfo.getModeName().value_, objModeInfo.getModeStatus().value_);

    bool bConnectionStatus = false;

    bool bAndroidAutoBondingReq = false;

    if((devprestypes::eModeStatus::ACTIVATING == objModeInfo.getModeStatus() ||
        devprestypes::eModeStatus::ACTIVE == objModeInfo.getModeStatus()) &&
           devprestypes::eModeName::USB_ANDROID_ANDROIDAUTO == objModeInfo.getModeName())
        {
            bAndroidAutoBondingReq = true;
        }

    if (devprestypes::eModeStatus::ACTIVE == objModeInfo.getModeStatus())
    {
        bConnectionStatus = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Mode Status is not recieved as ACTIVE.", __FUNCTION__);
    }

    if (m_pDeviceModeHandlerEventProvider)
    {
        if( devprestypes::eModeStatus::ACTIVE == objModeInfo.getModeStatus()
              || devprestypes::eModeStatus::DEACTIVATING == objModeInfo.getModeStatus()
              ||
          #ifdef PLATFORM_WIN32
              devprestypes::eModeStatus::ERROR_1 == objModeInfo.getModeStatus()
          #else
              devprestypes::eModeStatus::ERROR == objModeInfo.getModeStatus()
          #endif
              )

    {
        switch(objModeInfo.getModeName())
        {
        case devprestypes::eModeName::USB_ANDROID_ANDROIDAUTO:
            m_pDeviceModeHandlerEventProvider->updateAAConnectionStatus(bConnectionStatus);
            break;
        case devprestypes::eModeName::USB_IPHONE_CARPLAY:
            m_pDeviceModeHandlerEventProvider->updateCarPlayConnectionStatus(bConnectionStatus);
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Mode Name not handled.", __FUNCTION__);
            break;
        }
    }
		else
		{
			LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Mode Status is neither recieved as ACTIVE nor as DEACTIVATING", __FUNCTION__);
		}
    m_pDeviceModeHandlerEventProvider->updateAABondingReqStatus(bAndroidAutoBondingReq);
    }
    else
    {
       LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION,"%s: m_pDeviceModeHandlerEventProvider is NULL.", __FUNCTION__);
    }
}

/*********************************************************//**
                    * @category  CALLBACK METHODS
                     *********************************************************/

void CDeviceModeHandlerResourceImpl::deviceModeHandlerServiceStatusCb(CommonAPI::AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,__FUNCTION__);

    if(CommonAPI::AvailabilityStatus::AVAILABLE == eStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,"%s: Proxy available", __FUNCTION__);
        m_bIsDeviceModeHandlerAvailable = true;
    }
    else
    {
        m_bIsDeviceModeHandlerAvailable = false;
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,"%s:  Proxy not available", __FUNCTION__);

    }
}

void CDeviceModeHandlerResourceImpl::deviceInsertedCb(const devprestypes::sDeviceInfo  &objDeviceInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,__FUNCTION__);

    const vector<devprestypes::sModeInfo> &vectModeInfo = objDeviceInfo.getHUSupportedModes();

    size_t ulSize = vectModeInfo.size();

    m_objDeviceInfo.m_uiDeviceID = objDeviceInfo.getId();
    m_objDeviceInfo.m_strDeviceName = objDeviceInfo.getDeviceName();
    m_objDeviceInfo.m_eDeviceType = getDeviceTypeEnum(objDeviceInfo.getDevType());

    for(size_t ulIndex = 0; ulIndex < ulSize; ++ulIndex)
    {
        startModeReq(vectModeInfo.at(ulIndex).getModeName(), m_objDeviceInfo.m_uiDeviceID);
    }

}

void CDeviceModeHandlerResourceImpl::deviceRemovedCb(uint8_t uiRemovalStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,"%s: uiRemovalStatus: %d", __FUNCTION__, uiRemovalStatus);

    if (m_pDeviceModeHandlerEventProvider)
    {
        m_pDeviceModeHandlerEventProvider->updateAAConnectionStatus(false);
        m_pDeviceModeHandlerEventProvider->updateCarPlayConnectionStatus(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION,"%s: m_pDeviceModeHandlerEventProvider is NULL.", __FUNCTION__);
    }

}

void CDeviceModeHandlerResourceImpl::modeStatusCb(uint8_t uiDeviceID,
                                                  bool bReinsertedNeeded,
                                                  bool bHasConflictsMode,
                                                  const vector<devprestypes::sConflictMode> &vectSConflictMode,
                                                  const devprestypes::sModeInfo &objModeInfo
                                                  )
{
    Q_UNUSED(uiDeviceID);
    Q_UNUSED(bReinsertedNeeded);
    Q_UNUSED(bHasConflictsMode);
    Q_UNUSED(vectSConflictMode);
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    setProjectionConnectionStatus(objModeInfo);


}

/********************************************//**
 * @category RESPONSE CALLBACK METHODS
 ************************************************/

void CDeviceModeHandlerResourceImpl::startModeAsyncCb(const CallStatus &eCallStatus, const devprestypes::eAcknowledgement &eAcknowledgement)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,"%s: eCallStatus: %d, eAcknowledgement: %d", __FUNCTION__, static_cast<int>(eCallStatus), static_cast<int>(eAcknowledgement.value_));
}

void CDeviceModeHandlerResourceImpl::getInsertedDeviceInfoAsyncCb(const CallStatus &eCallStatus, const devprestypes::vDeviceInfo &objvDeviceInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,"%s: eCallStatus: %d", __FUNCTION__, static_cast<int>(eCallStatus));

    if (!objvDeviceInfo.empty())
    {
        deviceInsertedCb(objvDeviceInfo.at(0));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,"%s: Device Info vector is empty", __FUNCTION__);
    }
}


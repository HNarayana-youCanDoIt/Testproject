/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CSoftwareUpdateAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CSoftwareUpdateAdaptor, an Adaptor for Software Update module,
 * CSoftwareUpdateAdaptor used to communicate between QML and Resource Layer.
 */

#include "CSoftwareUpdateAdaptor.h"
#include "ResourceFactory.hpp"
#include "SoftwareUpdateResource/interfaces/ISoftwareUpdateResource.h"
#include "HMIIncludes.h"
#include "CPopupManager.h"
#include "CAudioAdaptor.h"
#include "CPowerModeAdaptor.h"
#include <CFramework.h>
#include <list>

CSoftwareUpdateAdaptor* CSoftwareUpdateAdaptor::m_pSoftwareUpdateAdaptor = nullptr;


CSoftwareUpdateAdaptor::CSoftwareUpdateAdaptor(QObject *parent) : QObject(parent)
  , m_pSoftwareUpdateResource(ResourceFactory::getSoftwareUpdateResource())
  , m_strSelectedISOName("")
  , m_iSelectedISOIndex(-1)
  , m_bSwUpdateAvailability(false)
  , m_bBusyIndicatorVisibility(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppSoftwareUpdateAdaptor", this);
}

CSoftwareUpdateAdaptor::~CSoftwareUpdateAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);

    if(m_pSoftwareUpdateAdaptor)
    {
	   //Todo::Changed for Unit Test to keep the instance alive when it is destucted, then also.
//        delete m_pSoftwareUpdateAdaptor;
        m_pSoftwareUpdateAdaptor = nullptr;
    }
}

CSoftwareUpdateAdaptor* CSoftwareUpdateAdaptor::getInstance()
{
    if(nullptr == m_pSoftwareUpdateAdaptor)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s", __FUNCTION__);
        m_pSoftwareUpdateAdaptor = new CSoftwareUpdateAdaptor();
    }
    return m_pSoftwareUpdateAdaptor;
}
void CSoftwareUpdateAdaptor::releaseInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);

    delete m_pSoftwareUpdateAdaptor;
    m_pSoftwareUpdateAdaptor = nullptr;

}


bool CSoftwareUpdateAdaptor::swUpdateAvailability()
{
    return m_bSwUpdateAvailability;
}

void CSoftwareUpdateAdaptor::setSwUpdateAvailability(bool availability)
{
    if (m_bSwUpdateAvailability != availability)
    {
        m_bSwUpdateAvailability = availability;
        emit sigSwUpdateAvailabilityChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_bSwUpdateAvailability unchanged");
    }
}

bool CSoftwareUpdateAdaptor::busyIndicatorVisibility()
{
    return m_bBusyIndicatorVisibility;
}

void CSoftwareUpdateAdaptor::setBusyIndicatorVisibility(bool visibility)
{
    if(m_bBusyIndicatorVisibility != visibility)
    {
        m_bBusyIndicatorVisibility = visibility;
        emit sigBusyIndicatorVisibilityChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_bBusyIndicatorVisibility unchanged");
    }
}


QStringList CSoftwareUpdateAdaptor::swISOList()
{
    return m_SWISOList;
}
void CSoftwareUpdateAdaptor::setSWISOList(QStringList val)
{
    if (m_SWISOList != val)
    {
        m_SWISOList = val;
        emit sigSWISOListChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_SWISOList unchanged");
    }
}

void CSoftwareUpdateAdaptor::swISOListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    if(m_pSoftwareUpdateResource)
    {
        QStringList packageList;
        //FixMe: Ideally we should get is list from below and append all the entries of the list
        std::list<SUpdateSearchResult>tmpList = m_pSoftwareUpdateResource->getPackageDetails();
        for (std::list<SUpdateSearchResult>::iterator it = tmpList.begin(); it != tmpList.end(); ++it)
        {
            packageList.append(QString::fromStdString(it->_packageDetails.strPackageName));
        }
        setSWISOList(packageList);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_pSoftwareUpdateResource is null");
    }
}

QString CSoftwareUpdateAdaptor::selectedISOName()
{
    return m_strSelectedISOName;
}

void CSoftwareUpdateAdaptor::setSelectedISOName(QString selectedISOName)
{
    if(0 < selectedISOName.length())
    {
        m_strSelectedISOName = selectedISOName;
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s : %s selected",__FUNCTION__,m_strSelectedISOName.toStdString().c_str());
        emit sigISONameSelected();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s : Length %d",__FUNCTION__,selectedISOName.length());
    }
}

int CSoftwareUpdateAdaptor::selectedISOIndex()
{
    return m_iSelectedISOIndex;
}

void CSoftwareUpdateAdaptor::setSelectedISOIndex(int selectedISOIndex)
{
    if (selectedISOIndex != m_iSelectedISOIndex)
    {
        m_iSelectedISOIndex = selectedISOIndex;
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s : %d selected",__FUNCTION__,selectedISOIndex);
        emit sigSelectedISOIndexChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"selectedISO index unchanged");
    }
}

void CSoftwareUpdateAdaptor::showISOFileConfirmPopup(int index, QString strPackageName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);

    /* One hour mode & low battery precondition check for Software Update */
    if(CPowerModeEnums::VPM_ONE_HOUR != CPowerModeAdaptor::getInstance().getPowerModeStatus())
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_TURN_IGN_OFF);
    }
    else if (CPowerModeEnums::NsmNodeState_DegradedPower == CPowerModeAdaptor::getInstance().getNSMNodeState())
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_LOW_BATTERY);
    }
    else
    {
        setSelectedISOIndex(index);
        setSelectedISOName(strPackageName);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_IMAGE_CONFIRMATION);
    }
}


int CSoftwareUpdateAdaptor::invErrorVerMismatchUpdate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    int iErrorValue = -1;
    if(CPowerModeEnums::VPM_ONE_HOUR != CPowerModeAdaptor::getInstance().getPowerModeStatus())
    {
       LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s IGN IS ON",__FUNCTION__);
       iErrorValue = 0;
    }
    else if(CPowerModeEnums::NsmNodeState_DegradedPower == CPowerModeAdaptor::getInstance().getNSMNodeState())
    {
       LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s LOW BATTERY VOLTAGE ERROR",__FUNCTION__);
       iErrorValue = 1;
    }
    else
    {
      LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s NO ERROR",__FUNCTION__);
    }
    return iErrorValue;
}

void CSoftwareUpdateAdaptor::cancelUpdateOnError(ESoftwareUpdateCancelType eCancelType)
{
    if(m_pSoftwareUpdateResource)
    {
        if(ESoftwareUpdateCancelType::CANCEL_INSTALL == eCancelType)
        {
            m_pSoftwareUpdateResource->cancelUpdate(eCancelType);
        }
        else if(ESoftwareUpdateCancelType::DECLINE_INSTALL == eCancelType)
        {
            m_pSoftwareUpdateResource->cancelUpdate(eCancelType);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_pSoftwareUpdateResource is null");
    }
}

void CSoftwareUpdateAdaptor::invShowErrorMessage(uint type)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);

    if(CPopupManager::getInstance()->isPopupAlive() && CPopupManager::getInstance()->getCurrentDisplayedPopup() == CPopupEnum::EN_POPUPID_VALIDATION_IN_PROGRESS)
    {
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_VALIDATION_IN_PROGRESS);
    }
    if(CPopupManager::getInstance()->isPopupAlive() && CPopupManager::getInstance()->getCurrentDisplayedPopup() == CPopupEnum::EN_POPUPID_IMAGE_CONFIRMATION)
    {
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_IMAGE_CONFIRMATION);
    }


    cancelUpdateOnError(ESoftwareUpdateCancelType::CANCEL_INSTALL);
    cancelUpdateOnError(ESoftwareUpdateCancelType::DECLINE_INSTALL);

    if(ESoftwareUpdateError::PACKAGE_VALIDATION_FAILED == type)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_PACKAGE_VALIDATION_FAILED);
    }
    else if(ESoftwareUpdateError::MSD_DISCONNECTED == type)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_MSD_DISCONNECTED);
    }
    else
    {
        //do nothing
    }
}

void CSoftwareUpdateAdaptor::showAvailabilityErrorMessage(uint uiSwAvailabilityErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    /* FixMe: Workaround for the current list API provided by SWUP. We do not get the updateAvailability of each
       detected package */
    if( ESoftwareUpdateAvailability::NO_UPDATE_AVAILABLE == uiSwAvailabilityErrorType)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_IMAGE_NOT_FOUND);
        cancelUpdateOnError(ESoftwareUpdateCancelType::CANCEL_INSTALL);
    }
    else if (ESoftwareUpdateAvailability::UPDATE_ALREADY_IN_PROGRESS  == uiSwAvailabilityErrorType)
    {
        setBusyIndicatorVisibility(false);
		cancelUpdateOnError(ESoftwareUpdateCancelType::CANCEL_INSTALL);
    }
    else
    {
        // Do nothing
    }
}

void CSoftwareUpdateAdaptor::checkForUpdateAttribute()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);

    /* USB connected precondition check for Software Update */
    if(false == CAudioAdaptor::getInstance()->usbSrcStatus())
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_NO_USB_CONNECTED);
    }
    else
    {
        /* One hour precondition check for Software Update */
        if(CPowerModeEnums::VPM_ONE_HOUR != CPowerModeAdaptor::getInstance().getPowerModeStatus())
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_TURN_IGN_OFF);
        }
        else if (CPowerModeEnums::NsmNodeState_DegradedPower == CPowerModeAdaptor::getInstance().getNSMNodeState())
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_LOW_BATTERY);
        }
        else
        {
            if(m_pSoftwareUpdateResource)
            {
                m_pSoftwareUpdateResource->checkForUpdate();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_pSoftwareUpdateResource is null");
            }
        }
    }
}

void CSoftwareUpdateAdaptor::requestInstallPackageAttribute(int index)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s, install index: %d",__FUNCTION__,index);
    if(m_pSoftwareUpdateResource)
    {
        m_pSoftwareUpdateResource->requestSWUpdate(index);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"m_pSoftwareUpdateResource is null");
    }
}

void CSoftwareUpdateAdaptor::requestInstallOnVerMismatch(uint uiTypeVersionMismatch)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s",__FUNCTION__);
    if(nullptr != m_pSoftwareUpdateResource)
    {
        m_pSoftwareUpdateResource->reqInstallVerMismatch(uiTypeVersionMismatch);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SOFTWARE_UPDATE,"%s: m_pSoftwareUpdateResource is NULL.",__FUNCTION__);
    }

}

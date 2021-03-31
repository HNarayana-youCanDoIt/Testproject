/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CVersionManagerAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CVersionManagerAdaptor, an Adaptor for Version Manager module,
 * CVersionManagerAdaptor used to communicate between QML and Resource Layer.
 */

#include "CVersionManagerAdaptor.h"
#include "ResourceFactory.hpp"
#include "VersionManagerResource/interfaces/IVersionManagerResource.h"
#include "HMIIncludes.h"
#include "CSoftwareUpdateAdaptor.h"
#include <CFramework.h>

CVersionManagerAdaptor* CVersionManagerAdaptor::m_pVersionManagerAdaptor = NULL;


CVersionManagerAdaptor::CVersionManagerAdaptor(QObject *parent) : QObject(parent)
  , m_pVersionManagerResource(ResourceFactory::getVersionManagerResource())
  , m_strVIN("")
  , m_strContainerPartNo("")
  , m_strSilverBoxPartNo("")
  , m_strDisplayHWPartNo("")
  , m_strParameterizationPartNo("")
  , m_strButtonPanelPartNo("")
  , m_strBtnPanelSoftVersionNo("")
  , m_strDisplayManagerVersionNo("")
  , m_strSOCVersionNo("")
  , m_uiVersionMismatchValue (0)
  , m_SwVersion("")
  , m_SwReleaseDate("")
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppVersionManagerAdaptor", this);
    fetchVersionInfo();
}

CVersionManagerAdaptor::~CVersionManagerAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);

    if(m_pVersionManagerAdaptor)
    {
	   //Todo::Changed for Unit Test to keep the instance alive when it is destucted, then also.
      //  delete m_pVersionManagerAdaptor;
        m_pVersionManagerAdaptor = nullptr;
    }
}
void CVersionManagerAdaptor::releaseInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    delete m_pVersionManagerAdaptor;
    m_pVersionManagerAdaptor = nullptr;
}

CVersionManagerAdaptor* CVersionManagerAdaptor::getInstance()
{
    if(nullptr == m_pVersionManagerAdaptor)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
        m_pVersionManagerAdaptor = new CVersionManagerAdaptor();
    }
    return m_pVersionManagerAdaptor;
}

QString CVersionManagerAdaptor::swVersion()
{
    return m_SwVersion;
}

void CVersionManagerAdaptor::setSwVersion(QString val)
{
    if (m_SwVersion != val)
    {
        m_SwVersion = val;
        emit sigSwVersionChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_SwVersion unchanged");
    }
}

QString CVersionManagerAdaptor::swReleaseDate()
{
    return m_SwReleaseDate;
}

void CVersionManagerAdaptor::setSwReleaseDate(QString val)
{
    if (m_SwReleaseDate != val)
    {
        m_SwReleaseDate = val;
        emit sigSwReleaseDateChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_SwReleaseDate unchanged");
    }
}

void CVersionManagerAdaptor::setVCInfo(const QString &strVCInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, strVCInfo: %s", __FUNCTION__, strVCInfo.toStdString().c_str ());
     if(m_strVCInfo != strVCInfo)
     {
         m_strVCInfo = strVCInfo;
         emit sigVCInfoChanged();
     }
     else
     {
         LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strVCInfo unchanged");
     }

}

void CVersionManagerAdaptor:: setVINInfo(const QString &strVin)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, strVin: %s", __FUNCTION__, strVin.toStdString().c_str ());
    if(m_strVIN != strVin)
    {
        m_strVIN = strVin;
        emit sigVINInfoChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strVIN unchanged");
    }
}

void CVersionManagerAdaptor::setContainerPartNo(const QString &strContainerPartNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, strContainerPartNo: %s", __FUNCTION__, strContainerPartNo.toStdString().c_str ());
    if(m_strContainerPartNo != strContainerPartNo)
    {
        m_strContainerPartNo = strContainerPartNo;
        emit sigContainerPartNoChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strContainerPartNo unchanged");
    }
}

void CVersionManagerAdaptor::setSilverBoxPartNo(const QString &strSilverBoxPartNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, strSilverBoxPartNo: %s", __FUNCTION__, strSilverBoxPartNo.toStdString().c_str ());
    if(m_strSilverBoxPartNo != strSilverBoxPartNo)
    {
        m_strSilverBoxPartNo = strSilverBoxPartNo;
        emit sigSilverBoxPartChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strSilverBoxPartNo unchanged");
    }
}

void CVersionManagerAdaptor::setDisplayHWPartNo(const QString &strDisplayHWPartNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, strDisplayHWPartNo: %s", __FUNCTION__, strDisplayHWPartNo.toStdString().c_str ());
    if(m_strDisplayHWPartNo != strDisplayHWPartNo)
    {
        m_strDisplayHWPartNo = strDisplayHWPartNo;
        emit sigDisplayHWPartNoChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strDisplayHWPartNo unchanged");
    }
}

void CVersionManagerAdaptor::setParameterizationPartNo(const QString &strParameterizationPartNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, strParameterizationPartNo: %s", __FUNCTION__, strParameterizationPartNo.toStdString().c_str ());
    if(m_strParameterizationPartNo != strParameterizationPartNo)
    {
        m_strParameterizationPartNo = strParameterizationPartNo;
        emit sigParameterizationPartNoChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strParameterizationPartNo unchanged");
    }
}

void CVersionManagerAdaptor::setButtonPanelPartNo(const QString &strButtonPanelPartNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, strButtonPanelPartNo: %s", __FUNCTION__, strButtonPanelPartNo.toStdString().c_str ());
    if(m_strButtonPanelPartNo != strButtonPanelPartNo)
    {
        m_strButtonPanelPartNo = strButtonPanelPartNo;
        emit sigButtonPanelPartNoChanged ();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strButtonPanelPartNo unchanged");
    }
}

void CVersionManagerAdaptor::setBtnPanelSoftVersionNo(const QString &strBtnPanelSoftVersionNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, strBtnPanelSoftVersionNo: %s", __FUNCTION__, strBtnPanelSoftVersionNo.toStdString().c_str ());
    if(m_strBtnPanelSoftVersionNo != strBtnPanelSoftVersionNo)
    {
        m_strBtnPanelSoftVersionNo = strBtnPanelSoftVersionNo;
        emit sigBtnPanelSoftVersionNoChanged ();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strBtnPanelSoftVersionNo unchanged");
    }
}

void CVersionManagerAdaptor::setDisplayManagerSoftVersionNo(const QString &strDisplayManagerSoftVersionNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, strDisplayManagerSoftVersionNo: %s", __FUNCTION__, strDisplayManagerSoftVersionNo.toStdString().c_str ());
    if(m_strDisplayManagerVersionNo != strDisplayManagerSoftVersionNo)
    {
        m_strDisplayManagerVersionNo = strDisplayManagerSoftVersionNo;
        emit sigDisplayManagerSoftVersionNoChanged ();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strDisplayManagerVersionNo unchanged");
    }
}

void CVersionManagerAdaptor::setSOCSoftVersionNo(const QString &strSOCSoftVersionNo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, strSOCSoftVersionNo: %s", __FUNCTION__, strSOCSoftVersionNo.toStdString().c_str ());
    if(m_strSOCVersionNo != strSOCSoftVersionNo)
    {
        m_strSOCVersionNo = strSOCSoftVersionNo;
        emit sigSOCSoftVersionNoChanged ();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strSOCVersionNo unchanged");
    }

    fetchVersionInfo();
}

void CVersionManagerAdaptor::fetchVersionInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s",__FUNCTION__);
    if(nullptr != m_pVersionManagerResource)
    {
        CVersionManagerEnums::SVersionInformation objVersionInformation = m_pVersionManagerResource->fetchVersionInfo();
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: Version:%s, ReleaseDate:%s",__FUNCTION__, objVersionInformation.versionData.c_str() ,objVersionInformation.versionReleasedDate.c_str());
        setSwVersion(QString::fromStdString(objVersionInformation.versionData));
        setSwReleaseDate(QString::fromStdString(objVersionInformation.versionReleasedDate));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s: m_pVersionManagerResource is NULL.",__FUNCTION__);
    }
}

void CVersionManagerAdaptor::versionMisMatchValueReceived(uint uiVerMismatchValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s", __FUNCTION__);
    m_uiVersionMismatchValue = uiVerMismatchValue;
    versionMismatchEvent();
}

void CVersionManagerAdaptor::versionMismatchEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s", __FUNCTION__);
    if(versionmanagertypes_tata::VersionMismatchDetails_e::NO_VERSION_MISMATCH != m_uiVersionMismatchValue)
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_VERSION_MISMATCH);
    }
    else
    {
        //do nothing
    }
}

void CVersionManagerAdaptor::callSwUpdateOnVerMismatch()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    if(versionmanagertypes_tata::VersionMismatchDetails_e::NO_VERSION_MISMATCH != m_uiVersionMismatchValue)
    {
        CSoftwareUpdateAdaptor::getInstance()->requestInstallOnVerMismatch(m_uiVersionMismatchValue );
    }
    else
    {
        //do nothing
    }
}

void CVersionManagerAdaptor::setPowerMode(const QString &strPowerMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER, "%s", __FUNCTION__);
    if(m_strPowerMode != strPowerMode)
    {
        if("00" == strPowerMode){
            m_ePowerModeType = CVersionManagerEnums::TYPE_POWER_MODE_IGN_ON;
        }
        else if("01" == strPowerMode){
            m_ePowerModeType = CVersionManagerEnums::TYPE_POWER_MODE_PEPS;
        }
        else{
            LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"%s, Not Valid PowerMode", __FUNCTION__);
        }
        m_strPowerMode = strPowerMode;
        emit sigPowerModeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VERSION_MANAGER,"m_strPowerMode unchanged");
    }
}

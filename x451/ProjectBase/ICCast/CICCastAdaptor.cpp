/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CICCastAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CICCastAdaptor, an adaptor for IC Cast module,
 * CICCastAdaptor is singleton class used to communicate with qml,resources of IC cast module.
 */

#include "ResourceFactory.hpp"
#include "HMIIncludes.h"
#include "logging.h"
#include "CFramework.h"
#include "CICCastAdaptor.h"
#include "CICCastEventHandler.h"
#include "CPersistencyAdaptor.h"
#include "CThemeManager.h"

CICCastAdaptor* CICCastAdaptor::m_pICCastAdaptor = nullptr;

CICCastAdaptor::CICCastAdaptor(QObject *pParent) : QObject(pParent),
    m_bICCastStatus(false),
    m_bICCastEnableStatus(true),
    m_pICCastResource(ResourceFactory::getICCastResource()),
    m_bICCastValueToBeUpdated(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppICCastAdaptor",this);
    CICCastEnums::registerICCastEnumToQML();
    connect(&CThemeManager::getThemeManager(), SIGNAL(sigCurrentThemeTypeChanged()), this, SLOT(sltCurrentThemeChangedForICCast()), Qt::QueuedConnection);
    setICCastEnableStatus(m_pICCastResource->isICCastProxyAvailable());
    sendICCastStatus(static_cast<bool>(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_HMI_IC_CAST_STATE)));
    updateOnThemeChanged();
    m_pICCastEventHandler = new CICCastEventHandler();
}

///////////////////////////////////////////////////////////////////////////////
// Adaptor related functions
///////////////////////////////////////////////////////////////////////////////
CICCastAdaptor* CICCastAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);
    if (nullptr == m_pICCastAdaptor)
    {
        m_pICCastAdaptor = new CICCastAdaptor();
    }
    return m_pICCastAdaptor;
}

CICCastAdaptor::~CICCastAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);

    if(m_pICCastAdaptor)
    {
        delete m_pICCastAdaptor;
        m_pICCastAdaptor = nullptr;
    }
    if (m_pICCastEventHandler)
    {
        delete m_pICCastEventHandler;
        m_pICCastEventHandler = nullptr;
    }
}

///////////////////////////////////////////////////////////////////////////////
// property related functions
///////////////////////////////////////////////////////////////////////////////


void CICCastAdaptor::setICCastStatus(bool bICCastStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: bICCastStatus: %d", __FUNCTION__, bICCastStatus);
    if(bICCastStatus != m_bICCastStatus)
    {
        m_bICCastStatus = bICCastStatus;
        emit sigICCastStatusChanged();
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HMI_IC_CAST_STATE, static_cast<int> (bICCastStatus));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s| Value not changed.", __FUNCTION__);
    }
}

void CICCastAdaptor::setICCastEnableStatus(bool bICCastEnableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: bICCastEnableStatus: %d", __FUNCTION__, bICCastEnableStatus);
    if(bICCastEnableStatus != m_bICCastEnableStatus)
    {
        m_bICCastEnableStatus = bICCastEnableStatus;
        emit sigICCastEnableStatusChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s| Value not changed.", __FUNCTION__);
    }

}

void CICCastAdaptor::updateICCastStatus(int iCallbackStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: iCallbackStatus: %d", __FUNCTION__, iCallbackStatus);

    if(CICCastEnums::SUCCESS == iCallbackStatus)
    {
        setICCastStatus(m_bICCastValueToBeUpdated);
    }
    // Enable  the Cast Option whatever be the cast callback status be.
    setICCastEnableStatus(true);
}

void CICCastAdaptor::sendICCastStatus(bool bICCastStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: bICCastStatus: %d", __FUNCTION__, bICCastStatus);
    m_bICCastValueToBeUpdated = bICCastStatus;
    m_pICCastResource->setIcRenderCastAsyncReq(CICCastEnums::ICRENDER_CAST_MASTER, bICCastStatus);
    setICCastEnableStatus(false);
}

void CICCastAdaptor::updateOnProxyAvailability(bool bICCastProxyStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: bICCastProxyStatus: %d", __FUNCTION__, bICCastProxyStatus);

    if(bICCastProxyStatus)
    {
        sendICCastStatus(static_cast<bool>(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_HMI_IC_CAST_STATE)));
        updateOnThemeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: IC Cast Proxy Not Available", __FUNCTION__);
    }
}

int CICCastAdaptor::mapIcCastThemeValue(int iIcCastTheme)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: iIcCastTheme: %d", __FUNCTION__, iIcCastTheme);
    int iRetIcCastThemeValue = -1;
    switch(iIcCastTheme)
    {
    case CThemeManagerEnums::THEME_TYPE_1:
        iRetIcCastThemeValue = 0;
        break;
    case CThemeManagerEnums::THEME_TYPE_2:
        iRetIcCastThemeValue = 2;
        break;
//As per TML, green colour theme should be removed
//    case CThemeManagerEnums::THEME_TYPE_3:
//        iRetIcCastThemeValue = 1;
//        break;
    case CThemeManagerEnums::THEME_TYPE_4:
        iRetIcCastThemeValue = 4;
        break;
    case CThemeManagerEnums::THEME_TYPE_5:
        iRetIcCastThemeValue = 3;
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: Default Case", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: iRetIcCastThemeValue: %d", __FUNCTION__, iRetIcCastThemeValue);
    return iRetIcCastThemeValue;
}

void CICCastAdaptor::updateOnThemeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);
    int iCurrentThemeType = mapIcCastThemeValue(static_cast<int> (CThemeManager::getThemeManager().currentThemeType()));
    if(m_pICCastResource)
    {
        m_pICCastResource->setIcColorTheme(iCurrentThemeType);
    }
    else {
        LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s: m_pICCastResource is NULL", __FUNCTION__);
    }

}

void CICCastAdaptor::sltCurrentThemeChangedForICCast()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ICCAST, "%s", __FUNCTION__);
    updateOnThemeChanged();
}

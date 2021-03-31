/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDisplayManagerAdaptor.cpp
 * @ingroup       HMIComponent
 * @author        Vishal Chaudhary
 * @brief         Contain implementation of all the methods declared in
 *                CDisplayManagerAdaptor class
 */

#include "CDisplayManagerAdaptor.h"
#include "CDisplayManagerEventHandler.h"
#include "logging.h"
#include "ResourceFactory.hpp"
#include "implementations/CDisplayManagerResourceImpl.h"
#include "CParkAssistAdaptor.h"
#include "CAppleCarPlayAdaptor.h"
#include "CAndroidAutoAdaptor.h"
#include "CPhoneAdaptor.h"

CDisplayManagerAdaptor* CDisplayManagerAdaptor::m_pDisplayManagerAdaptor = NULL;

CDisplayManagerAdaptor::CDisplayManagerAdaptor(QObject *pParent) :
    QObject(pParent),
    m_pDisplayManagerResource(dynamic_cast<CDisplayManagerResourceImpl*>(ResourceFactory::getDisplayManagerResource())),
    m_pDisplayManagerEventHandler(new CDisplayManagerEventHandler()),
    m_bDisplayOnOffFeatureStatus(false),
    m_bNightModeStatus(false),
    m_iBrightnessLevel(20),
    m_iButtonPanelBrightnessLevel(20),
    m_bIsBrightnessLevelRespRecv(true),
    m_bIsButtonPanelBrightnessLevelRespRecv(true)

{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppDisplayManagerAdaptor", this);

    connect(CParkAssistAdaptor::getInstance(), SIGNAL(sigReverseGearStatusChanged()), this, SLOT(sltReverseGearStatusChanged()), Qt::QueuedConnection);
}

bool CDisplayManagerAdaptor::isDisplayNeedstoBeOn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: ", __FUNCTION__);

    return (CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()
            || CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus()
            || CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus()
            || CPhoneAdaptor::getInstance()->doesCallExist());
}

void CDisplayManagerAdaptor::sltReverseGearStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: ", __FUNCTION__);

    /*
     * This is done here for the issue, Popup timeouts and  reverse gear engaged,
     * Becuase we do not recieved the response of previous request for displyOff
     * So the variable m_bDisplayOnOffFeatureStatus is having previous value,
     * which is like display is ON, So on revrese gear enaged
     * we call the adaptor's reqDisplay function to ON the display, Adaptor ignores
     * that request becuase it thinks like diplay is already ON. So now always
     * we request display ON on PDC enagage.
     */
    if (m_pDisplayManagerResource && CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus())
    {
        m_pDisplayManagerResource->setDisplayOnOffFeatureAsyncReq(true);
    }
}

CDisplayManagerAdaptor::~CDisplayManagerAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    if (m_pDisplayManagerAdaptor)
    {
        delete m_pDisplayManagerAdaptor;
        m_pDisplayManagerAdaptor = nullptr;
    }

    if (m_pDisplayManagerEventHandler)
    {
        delete m_pDisplayManagerEventHandler;
        m_pDisplayManagerEventHandler = nullptr;
    }
}

void CDisplayManagerAdaptor::setDisplayOnOffFeatureStatus(const bool bDisplayOnOffFeatureStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: bDisplayOnOffFeatureStatus: %d", __FUNCTION__, bDisplayOnOffFeatureStatus);

    if (bDisplayOnOffFeatureStatus != m_bDisplayOnOffFeatureStatus)
    {
        m_bDisplayOnOffFeatureStatus = bDisplayOnOffFeatureStatus;
        emit sigDisplayOnOffFeatureStatusChanged();

        /*
         * If HMI recieves the display feature status as true (means display is off),
         * and HMI is in any such state in which display must be on then, request
         * the display manager to switch ON the display.
         */
        if (m_bDisplayOnOffFeatureStatus && isDisplayNeedstoBeOn())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: Display must be ON, so Switching ON the display.", __FUNCTION__);
            reqDisplayOnOffFeature(false);
        }
        else
        {
            // Do nothing.
        }
    }
    else
    {
        //Do nothing
    }
}

void CDisplayManagerAdaptor::setNightModeStatus(const bool bNightModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: bNightModeStatus: %d", __FUNCTION__, bNightModeStatus);

    if (bNightModeStatus != m_bNightModeStatus)
    {
        m_bNightModeStatus = bNightModeStatus;
        emit sigNightModeStatusChanged();
    }
    else
    {
        //Do nothing
    }
}

void CDisplayManagerAdaptor::setBrightnessLevel(const short iBrightnessLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iBrightnessLevel: %d", __FUNCTION__, iBrightnessLevel);

    if (iBrightnessLevel != m_iBrightnessLevel)
    {
        m_iBrightnessLevel = iBrightnessLevel;
        emit sigBrightnessLevelChanged();
    }
    else
    {
        //Do nothing
    }

}

void CDisplayManagerAdaptor::setButtonPanelBrightnessLevel(const short iBrightnessLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iBrightnessLevel: %d", __FUNCTION__, iBrightnessLevel);

    if (iBrightnessLevel != m_iButtonPanelBrightnessLevel)
    {
        m_iButtonPanelBrightnessLevel = iBrightnessLevel;
        emit sigButtonPanelBrightnessLevelChanged();
    }
    else
    {
        //Do nothing
    }
}

/************************************************************************//**
 * @category    METHODS
 ************************************************************************/

CDisplayManagerAdaptor* CDisplayManagerAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL,__FUNCTION__);

    if (!m_pDisplayManagerAdaptor)
    {
        m_pDisplayManagerAdaptor = new CDisplayManagerAdaptor();
    }

    return m_pDisplayManagerAdaptor;
}

void CDisplayManagerAdaptor::setBrightnessLevelRespRecv()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    m_bIsBrightnessLevelRespRecv = true;
}

void CDisplayManagerAdaptor::setButtonPanelBrightnessLevelRespRecv()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, __FUNCTION__);
    m_bIsButtonPanelBrightnessLevelRespRecv = true;
}

/************************************************************************//**
 * @category    RESOURCE LAYER METHODS
 * @brief       API's can be called directly from QML or from other
 *              Adaptor's
 ************************************************************************/

void CDisplayManagerAdaptor::reqDisplayOnOffFeature(bool bDisplayOnOffFeatureStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: bDisplayOnOffFeatureStatus: %d", __FUNCTION__, bDisplayOnOffFeatureStatus);

    /*
     * If Request recieved for DisplayOff and HMI is in any such state in Which
     * display must be ON, then No action.
     */
    if ( bDisplayOnOffFeatureStatus && isDisplayNeedstoBeOn())
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: Display must remain ON, So No Action.", __FUNCTION__);
    }
    else if(m_pDisplayManagerResource)
    {
        /*
         * m_bDisplayOnOffFeatureStatus will be true if Display is Off
         * and false if display is ON, but to Off display HMI has to send
         * as false. and to ON HMI has to send true.
         */
        m_pDisplayManagerResource->setDisplayOnOffFeatureAsyncReq(!bDisplayOnOffFeatureStatus);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: Display manager resource object not created", __FUNCTION__);
    }
}

void CDisplayManagerAdaptor::reqDisplayBrightnessLevel(short iBrightnessLevel, bool bIsReleased)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iBrightnessLevel: %d, bIsReleased: %d, m_bIsBrightnessLevelRespRecv: %d", __FUNCTION__, iBrightnessLevel, bIsReleased, m_bIsBrightnessLevelRespRecv);

    if(m_pDisplayManagerResource)
    {
        if (bIsReleased)
        {
            setBrightnessLevel(iBrightnessLevel);
            m_pDisplayManagerResource->setDisplayBrightnessLevelAsyncReq(iBrightnessLevel);
        }
        else if (m_bIsBrightnessLevelRespRecv)
        {
            setBrightnessLevel(iBrightnessLevel);
            m_bIsBrightnessLevelRespRecv = false;
            m_pDisplayManagerResource->setDisplayBrightnessLevelAsyncReq(iBrightnessLevel);
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: Display manager resource object not created. m_bIsBrightnessLevelRespRecv: %d", __FUNCTION__, m_bIsBrightnessLevelRespRecv);
    }
}

//[Todo:] The debouncing logic has to be modified
void CDisplayManagerAdaptor::reqButtonPanelBrightnessLevel(short iBrightnessLevel, bool bIsReleased)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: iBrightnessLevel: %d, bIsReleased: %d, m_bIsButtonPanelBrightnessLevelRespRecv: %d", __FUNCTION__, iBrightnessLevel, bIsReleased, m_bIsButtonPanelBrightnessLevelRespRecv);

    if(m_pDisplayManagerResource)
    {
        if (bIsReleased)
        {
            setButtonPanelBrightnessLevel(iBrightnessLevel);
            m_pDisplayManagerResource->setButtonPanelBrightnessLevelAsyncReq(iBrightnessLevel);
        }
        else if (m_bIsButtonPanelBrightnessLevelRespRecv)
        {
            setButtonPanelBrightnessLevel(iBrightnessLevel);
            m_bIsButtonPanelBrightnessLevelRespRecv = false;
            m_pDisplayManagerResource->setButtonPanelBrightnessLevelAsyncReq(iBrightnessLevel);
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DISPLAY_CONTROL, "%s: Display manager resource object not created. m_bIsButtonPanelBrightnessLevelRespRecv: %d", __FUNCTION__, m_bIsButtonPanelBrightnessLevelRespRecv);
    }
}

/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CPopupManagerSM.cpp
* @ingroup      HMIComponent
* @author       Rahul Madan
* CPopupManagerSM  Class to implement Popup SCT Interface
*/
#include "CPopupManagerSM.h"
#include "CPopupManager.h"
#include <CFramework.h>

CPopupManagerSM::CPopupManagerSM():m_pPopupPropertyHandler(new CPopupPropertyHandler())
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
}

CPopupManagerSM::~CPopupManagerSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    if(m_pPopupPropertyHandler)
    {
        delete m_pPopupPropertyHandler;
        m_pPopupPropertyHandler = NULL;
    }
}

void CPopupManagerSM::enterNoNotification()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);

    // ToDo: add description for logic
    emit CPopupManager::getInstance()->sigEnterNoNotificationState();
}

void CPopupManagerSM::exitNoNotification()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    if(m_pPopupPropertyHandler)
    {
        CHMIMain::getSM()->getSCI_Popup()->set_minNotificationTimeout(m_pPopupPropertyHandler->getPopupMap().value(CPopupManager::getInstance()->m_eCurrentRequestedNotification).m_iMinTimeout);
        CHMIMain::getSM()->getSCI_Popup()->set_maxNotificationTimeout(m_pPopupPropertyHandler->getPopupMap().value(CPopupManager::getInstance()->m_eCurrentRequestedNotification).m_iMaxTimeout);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupPropertyHandler is NULL",__FUNCTION__);
    }
}

void CPopupManagerSM::enterNotificationActive()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    CPopupManager::getInstance()->loadPopup(CPopupManager::getInstance()->getCurrentRequestedNotification());
}

void CPopupManagerSM::exitNotificationActive()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    CPopupManager::getInstance()->unloadPopup(CPopupManager::getInstance()->getCurrentDisplayedNotification());
    //Setting min. Timeout to 0
    CHMIMain::getSM()->getSCI_Popup()->set_minNotificationTimeout(0);
    //Setting max. Timeout to 0
    CHMIMain::getSM()->getSCI_Popup()->set_maxNotificationTimeout(0);

    // Setting isCloseOnMinTimeoutNotification to false when notification gets closed
    if(CHMIMain::getSM()->getSCI_Popup()->get_isCloseOnMinTimeoutNotification())
    {
        CHMIMain::getSM()->getSCI_Popup()->set_isCloseOnMinTimeoutNotification(false);
    }
}

void CPopupManagerSM::enterNoPopup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    emit CPopupManager::getInstance()->sigEnterNoPopupState();
}

void CPopupManagerSM::exitNoPopup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    /** Setting Timeouts here because, as soon as we enter the PopupActive State, the Timers start and if we do not set
     *  set the min. and max. timeouts here, The Timer would take default values as time
     */
    if(m_pPopupPropertyHandler)
    {
        CHMIMain::getSM()->getSCI_Popup()->set_minPopupTimeout(m_pPopupPropertyHandler->getPopupMap().value(CPopupManager::getInstance()->m_eCurrentRequestedPopup).m_iMinTimeout);
        CHMIMain::getSM()->getSCI_Popup()->set_maxPopupTimeout(m_pPopupPropertyHandler->getPopupMap().value(CPopupManager::getInstance()->m_eCurrentRequestedPopup).m_iMaxTimeout);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupPropertyHandler is NULL",__FUNCTION__);
    }
}

void CPopupManagerSM::enterPopupActive()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    // Pause/stop the timer for the current screen when a popup is shown
    CFramework::getFramework().stopScreenTimer();

    CPopupManager::getInstance()->loadPopup(CPopupManager::getInstance()->getCurrentRequestedPopup());
}

void CPopupManagerSM::exitPopupActive()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    CPopupManager::getInstance()->unloadPopup(CPopupManager::getInstance()->getCurrentDisplayedPopup());
    //Setting min. Timeout to 0
    CHMIMain::getSM()->getSCI_Popup()->set_minPopupTimeout(0);
    //Setting max. Timeout to 0
    CHMIMain::getSM()->getSCI_Popup()->set_maxPopupTimeout(0);

    // Setting isCloseOnMinTimeoutPopup to false when popup gets closed
    if(CHMIMain::getSM()->getSCI_Popup()->get_isCloseOnMinTimeoutPopup())
    {
        CHMIMain::getSM()->getSCI_Popup()->set_isCloseOnMinTimeoutPopup(false);
    }
    // Restart the screen timeout timer
    CFramework::getFramework().restartScreenTimer();
}

void CPopupManagerSM::handleNotificationPriority()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    CPopupManager::getInstance()->handlePriority(CPopupManager::getInstance()->getCurrentRequestedNotification());
}

void CPopupManagerSM::handlePopupPriority()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);

    // ToDo: add description for logic
    CPopupManager::getInstance()->handlePriority(CPopupManager::getInstance()->getCurrentRequestedPopup());
}

bool CPopupManagerSM::isPopupAllowed()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    return CPopupManager::getInstance()->isPopupAllowed(CPopupManager::getInstance()->getCurrentRequestedPopup());
}

bool CPopupManagerSM::isNotificationAllowed()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    return CPopupManager::getInstance()->isPopupAllowed(CPopupManager::getInstance()->getCurrentRequestedNotification());
}

void CPopupManagerSM::checkPopupContext()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, __FUNCTION__);
    CPopupManager::getInstance()->checkPopupContext();
}


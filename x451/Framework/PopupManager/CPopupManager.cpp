/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CPopupManager.cpp
* @ingroup      HMIComponent
* @author       Rahul Madan
* CPopupManager Class implementation which shall be used by all the HMI Modules to
*               show, close and request any inforrmation about the Popups
*/

#include "CPopupManager.h"
#include "CFramework.h"
#include "CPopupPropertyHandler.h"
#include "CPopupManagerSM.h"
#include "CPowerModeAdaptor.h"
#include "CDisplayManagerAdaptor.h"
#include "LayerManager/CLayerManagerAdaptor.h"

#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"

//TODO: Following Features will be implemented in future changes:
// * Result Signals for methods : showPopup and closePopup
// * closeOnTouch
CPopupManager* CPopupManager::m_pInstance = nullptr;
CPopupManager::CPopupManager() :m_pPopupProperty(new CPopupPropertyHandler()),
    m_pPopupManagerSM(new CPopupManagerSM()),
    m_eCurrentRequestedPopup(CPopupEnum::EN_POPUPID_UNKNOWN),
    m_eCurrentRequestedNotification(CPopupEnum::EN_POPUPID_UNKNOWN),
    m_eCurrentDisplayedPopup(CPopupEnum::EN_POPUPID_UNKNOWN),
    m_eCurrentDisplayedNotification(CPopupEnum::EN_POPUPID_UNKNOWN),
    m_bIsHKHandledCompletely(true),
    m_ePopupResult(CPopupEnum::EN_POPUP_RESULT_INVALID),
    m_eNotificationResult(CPopupEnum::EN_POPUP_RESULT_INVALID),
    m_eHardKeyHandled(CHardKeyEnum::KEYCODEHK_INVALID),
    m_bStartPopupQueueing(false),
    m_bNotificationVisible(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    CPopupEnum::registerPopupEnumToQML();
    CHMIMain::getSM()->setSCI_Popup_OCB(m_pPopupManagerSM);
    connect(this, SIGNAL(sigEnterNoPopupState()), this, SLOT(sltEnterNoPopupState()),Qt::QueuedConnection);
    connect(this, SIGNAL(sigEnterNoNotificationState()), this, SLOT(sltEnterNoNotificationState()),Qt::QueuedConnection);
}

CPopupManager::~CPopupManager()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    if(m_pPopupProperty)
    {
        delete m_pPopupProperty;
        m_pPopupProperty = nullptr;
    }
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
    if(m_pPopupManagerSM)
    {
        delete m_pPopupManagerSM;
        m_pPopupManagerSM = nullptr;
    }
}

CPopupManager* CPopupManager::getInstance()
{
    if(nullptr == m_pInstance)
    {
        m_pInstance = new CPopupManager();
    }
    return m_pInstance;
}

void CPopupManager::showPopup(CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : ePopupId: %d", __FUNCTION__, ePopupId);
    if(!(CPowerModeEnums::VPM_EARLY_WAKEUP == CPowerModeAdaptor::getInstance().getPowerModeStatus()))
    {
        if(m_pPopupProperty)
        {
            if(CPopupEnum::EN_POPUP_ZONE_FOUR == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
            {
                if(m_eCurrentDisplayedPopup != ePopupId)
                {
                    handlePopupsWithNoTimeOut(ePopupId);
                    setCurrentRequestedPopup(ePopupId);
                    CHMIMain::getSM()->getSCI_Popup()->raise_evShowPopup();
                }
                else if(m_pPopupProperty->getPopupMap().value(ePopupId).m_bResetPopupTimer)
                {
                    CHMIMain::getSM()->getSCI_Popup()->raise_evResetPopupTimer();
                }
                else
                {
                    // do nothing
                }

            }
            else if(CPopupEnum::EN_POPUP_ZONE_TWO == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
            {
                if(m_eCurrentDisplayedNotification != ePopupId)
                {
                    setCurrentRequestedNotification(ePopupId);
                    CHMIMain::getSM()->getSCI_Popup()->raise_evShowNotification();
                }
                else if(m_pPopupProperty->getPopupMap().value(ePopupId).m_bResetPopupTimer)
                {
                    CHMIMain::getSM()->getSCI_Popup()->raise_evResetNotificationTimer();
                }
                else
                {
                    // do nothing
                }
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Popup Zone not defined | %d",__FUNCTION__,ePopupId);
            }

        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupProperty is NULL ",__FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : ePopupId: %d Ignored as System is in EarlyWakeup PowerMode", __FUNCTION__, ePopupId);
    }
}

//FixMe : Adding different methods to load, unload Notification Popups
void CPopupManager::closePopup(CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : ePopupId: %d", __FUNCTION__, ePopupId);
    if(m_pPopupProperty)
    {
        if(CPopupEnum::EN_POPUP_ZONE_FOUR == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            if(m_eCurrentDisplayedPopup == ePopupId)
            {
                //Check if Min. Timer is over for currently displayed popup, close the popup
                if(CHMIMain::getSM()->getSCI_Popup()->get_isMinPopupTimeoutOver())
                {
                    if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS != m_ePopupResult)
                    {
                        setPopupResult(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CLOSE_REQUEST);
                    }
                    CHMIMain::getSM()->getSCI_Popup()->raise_evClosePopup();
                }
                //Else If Min. Timer is till running for currently displayed popup, set isCloseOnMinTimeout to true to close popup after it's min. timer is over
                else
                {
                    CHMIMain::getSM()->getSCI_Popup()->set_isCloseOnMinTimeoutPopup(true);
                }
            }
            else
            {
                m_lPendingPopups.remove(m_pPopupProperty->getPopupMap().value(ePopupId));
            }
        }
        else if(CPopupEnum::EN_POPUP_ZONE_TWO == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            if(m_eCurrentDisplayedNotification == ePopupId)
            {
                //Check if Min. Timer is over for currently displayed notification, close the popup
                if(CHMIMain::getSM()->getSCI_Popup()->get_isMinNotificationTimeoutOver())
                {
                    m_eNotificationResult = CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CLOSE_REQUEST;
                    CHMIMain::getSM()->getSCI_Popup()->raise_evCloseNotification();
                }
                //Else If Min. Timer is till running for currently displayed notification, set isCloseOnMinTimeout to true to close notification after it's min. timer is over
                else
                {
                    CHMIMain::getSM()->getSCI_Popup()->set_isCloseOnMinTimeoutNotification(true);
                }
            }
            else
            {
                m_lPendingNotification.remove(m_pPopupProperty->getPopupMap().value(ePopupId));
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Popup Zone not defined | %d",__FUNCTION__,ePopupId);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupProperty is NULL ",__FUNCTION__);
    }
}

bool CPopupManager::isPopupAlive()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    return CHMIMain::getSM()->getSCI_Popup()->get_isPopupDisplayed();
}

void CPopupManager::invResetPopupTimer()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    CHMIMain::getSM()->getSCI_Popup()->raise_evResetPopupTimer();
}

bool CPopupManager::isNotificationAlive()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    return CHMIMain::getSM()->getSCI_Popup()->get_isNotificationDisplayed();
}

void CPopupManager::closeAllPopups()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    if(isPopupAlive())
    {
        setPopupResult(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CLOSE_ALL_POPUPS);
        CHMIMain::getSM()->getSCI_Popup()->raise_evForceClosePopup();
    }
    if(isNotificationAlive())
    {
        m_eNotificationResult = CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CLOSE_ALL_POPUPS;
        CHMIMain::getSM()->getSCI_Popup()->raise_evForceCloseNotification();
    }

    if(getCurrentRequestedPopup() != CPopupEnum::EN_POPUPID_UNKNOWN)
    {
        setCurrentRequestedPopup(CPopupEnum::EN_POPUPID_UNKNOWN);
    }
    if(getCurrentRequestedNotification() != CPopupEnum::EN_POPUPID_UNKNOWN)
    {
        setCurrentRequestedNotification(CPopupEnum::EN_POPUPID_UNKNOWN);
    }

    m_lPendingPopups.clear();
    m_lPendingNotification.clear();
}

void CPopupManager::forceClosePopup(const CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : %d",__FUNCTION__, ePopupId);
    if(m_pPopupProperty)
    {
        if(CPopupEnum::EN_POPUP_ZONE_FOUR == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            if(m_eCurrentDisplayedPopup == ePopupId)
            {
                if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS != m_ePopupResult)
                {
                    setPopupResult(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_FORCE_CLOSE_REQUEST);
                }
                CHMIMain::getSM()->getSCI_Popup()->raise_evForceClosePopup();
            }
            else
            {
                m_lPendingPopups.remove(m_pPopupProperty->getPopupMap().value(ePopupId));
            }
        }
        else if(CPopupEnum::EN_POPUP_ZONE_TWO == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            if(m_eCurrentDisplayedNotification == ePopupId)
            {
                m_eNotificationResult = CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_FORCE_CLOSE_REQUEST;
                CHMIMain::getSM()->getSCI_Popup()->raise_evForceCloseNotification();
            }
            else
            {
                m_lPendingNotification.remove(m_pPopupProperty->getPopupMap().value(ePopupId));
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Popup Zone not defined | %d",__FUNCTION__,ePopupId);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupProperty is NULL ",__FUNCTION__);
    }
}

void CPopupManager::closeOnHardKey()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    if(m_pPopupProperty)
    {
        if(CPopupEnum::EN_POPUP_ZONE_FOUR == m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedPopup).m_ePopupZone)
        {
            if(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedPopup).m_bCloseOnHK)
            {
                setPopupResult(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_HK);
                CHMIMain::getSM()->getSCI_Popup()->raise_evForceClosePopup();
            }
        }

        // As per the current implementation notification will not get closed on hardkey press.
        // Commenting this code for future use if closeOnHardkey requirement changes for notification
        // we can easily use this.
        //        if(CPopupEnum::EN_POPUP_ZONE_TWO == m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedNotification).m_ePopupZone)
        //        {
        //            if(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedNotification).m_bCloseOnHK)
        //            {
        //                CHMIMain::getSM()->getSCI_Popup()->raise_evForceCloseNotification();
        //            }
        //        }

        /*
        * On hard key press popup will get close and if there is any pending popup in pending popup list, it will get displayed
        * immediately if we will not remove the pending popups from pending popup list.
        * From user point of view he wants to close the popup but new popup is getting displayed from pending popup list.
        * Which is not user expectation that's why removing all pending popups from pending popup list, if closeOnHardKey is true.
        */
        for(std::list<CPopupPropertyHandler::CPopupProperties>::iterator iter = m_lPendingPopups.begin(); iter != m_lPendingPopups.end();  )
        {
            if(iter->m_bCloseOnHK)
            {
                iter = m_lPendingPopups.erase(iter);
            }
            else
            {
                ++iter;
            }
        }

        // As per the current implementation notification will not get closed on hardkey press.
        // Commenting this code for future use if closeOnHardkey requirement changes for notification
        // we can easily use this.
        /*
        * On hard key press notification will get close and if there is any pending notification in pending notification list, it will get displayed
        * immediately if we will not remove the pending notifications from pending notification list.
        * From user point of view he wants to close the popup but new notification is getting displayed from pending notification list.
        * Which is not user expectation that's why removing all pending notifications from pending notification list if the closeOnHardKey is true.
        */
        //        for(CPopupPropertyHandler::CPopupProperties const& objPopupProperties : m_lPendingNotification )
        //        {
        //            if(objPopupProperties.m_bCloseOnHK)
        //            {
        //                m_lPendingNotification.remove(m_pPopupProperty->getPopupMap().value(objPopupProperties.m_eId));
        //            }
        //        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupProperty is NULL",__FUNCTION__);
    }
}

void CPopupManager::broadcastPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupresult, QString strAdditionalInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, "%s: PopupId is: %d, Popup result is: %d", __FUNCTION__, ePopupId, ePopupresult);

    if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_HK == ePopupresult)
    {
        strAdditionalInfo = QString::number(m_eHardKeyHandled);
    }
    else
    {
        //Do nothing
    }
    emit sigPopupResult(ePopupId, ePopupresult, strAdditionalInfo);
}

void CPopupManager::setStartPopupQueueing(bool bStartPopupQueuing)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, "%s: bStartPopupQueuing: %d", __FUNCTION__, bStartPopupQueuing);

    if(m_bStartPopupQueueing != bStartPopupQueuing)
    {
        m_bStartPopupQueueing = bStartPopupQueuing;
    }
}

bool CPopupManager::getBNotificationVisible() const
{
    return m_bNotificationVisible;
}

void CPopupManager::setBNotificationVisible(bool bNotificationVisible)
{
    if(m_bNotificationVisible != bNotificationVisible)
    {
        m_bNotificationVisible = bNotificationVisible;
        emit sigNotificationVisibilityChanged();
    }
}

bool CPopupManager::handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, "%s: key is: %d, key state is: %d", __FUNCTION__, eKey, eKeyState);
    m_bIsHKHandledCompletely = false;
    m_eHardKeyHandled = eKey;
    switch(eKey)
    {
    case CHardKeyEnum::KEYCODEHK_BACK:
    {
        m_bIsHKHandledCompletely = true;
        if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) ||
                (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
        {
            //If popup is alive then close the popup based on close on hard key property of popup.
            if(isPopupAlive())
            {
                closeOnHardKey();
                if(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedPopup).m_bCloseOnHK)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, "%s: close on HK is true", __FUNCTION__);
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, "%s: close on HK is false, emit the signal", __FUNCTION__);
                    /*
                     * Emit the signal so that the current popup on screen can handle it and process it,
                     * if it needs to do some operation on HK.
                     */
                    emit sigProcessHKOnPopup(static_cast<int>(eKey), static_cast<int>(eKeyState));
                }
            }
        }
        else
        {
            //Do Nothing
        }
    }
        break;

    case CHardKeyEnum::KEYCODEHK_MENUROTARY:
    case CHardKeyEnum::KEYCODEHK_MENUROTARY_KNOB:
    {
        if(isPopupAlive())
        {
            m_bIsHKHandledCompletely = true;
            handleRotary(eKey, eKeyState);
        }

    }
        break;

    case CHardKeyEnum::KEYCODEHK_VOLROTARY:
    case CHardKeyEnum::KEYCODEHK_ENGGMENU:
    case CHardKeyEnum::KEYCODEHK_FAVORITE:
    case CHardKeyEnum::KEYCODEHK_HOME:
    case CHardKeyEnum::KEYCODEHK_PHONE:
    case CHardKeyEnum::KEYCODEHK_SEEKDOWN:
    case CHardKeyEnum::KEYCODEHK_SEEKUP:
    case CHardKeyEnum::KEYCODEHK_SOFTWARE_UPDATE:
    case CHardKeyEnum::KEYCODESWC_ACCEPT_VR:
    case CHardKeyEnum::KEYCODESWC_DOWN:
    case CHardKeyEnum::KEYCODESWC_NEXT:
    case CHardKeyEnum::KEYCODESWC_PREV:
    case CHardKeyEnum::KEYCODESWC_REJECT_MUTE:
    case CHardKeyEnum::KEYCODESWC_SOURCE:
    case CHardKeyEnum::KEYCODESWC_UP:
    {        
        //If popup is alive then close the popup based on close on hard key property of popup.
        if(isPopupAlive())
        {
            if (CDoodleApplication::getDoodleAdaptor() && CDoodleApplication::getDoodleAdaptor()->isDoodleStickerOnScreen())
            {
                //Do Nothing!
                //while doodle sticker is on screen HardKEys events handled by DoodleAdaptor.
            }
            else if(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedPopup).m_bCloseOnHK)
            {
                if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) ||
                        (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, "%s: close on HK is true", __FUNCTION__);
                    closeOnHardKey();
                }
                else
                {
                    //do nothing
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_POPUP, "%s: close on HK is false, emit the signal", __FUNCTION__);
                m_bIsHKHandledCompletely = true;
                /*
                 * Emit the signal so that the current popup on screen can handle it and process it,
                 * if it needs to do some operation on HK.
                 */
                emit sigProcessHKOnPopup(static_cast<int>(eKey), static_cast<int>(eKeyState));
            }
        }

    }
        break;
    default:
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP, "%s Invalid data received key: %d state: %d ", __FUNCTION__, static_cast<int>(eKey), static_cast<int>(eKeyState));
    }
    return m_bIsHKHandledCompletely;
}

void CPopupManager::handleRotary(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    if(CHardKeyEnum::EHardKeys::KEYCODEHK_MENUROTARY == eKey)
    {
        emit sigRotaryPressedPopup(static_cast<int>(eKey), static_cast<int>(eKeyState));
    }
    else if(CHardKeyEnum::EHardKeys::KEYCODEHK_MENUROTARY_KNOB == eKey)
    {
        emit sigRotaryUpdatePopup(static_cast<int>(eKey), static_cast<int>(eKeyState));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s, invalid rotary event", __FUNCTION__);
    }
}

void CPopupManager::loadPopup(CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s popup:  %d", __FUNCTION__,ePopupId);
    bool retVal = false;
    if(m_pPopupProperty)
    {
        setPopupResult(CPopupEnum::EN_POPUP_RESULT_INVALID);

        //If popup to be loaded is not EN_POPUPID_DISPLAY_OFF_TRANSPARENT then only turn on the display otherwise do nothing
        if(CPopupEnum::EN_POPUPID_DISPLAY_OFF_TRANSPARENT != ePopupId)
        {
            CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);
        }
        else
        {
            //do nothing
        }

        if(CPopupEnum::EN_POPUP_ZONE_FOUR == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            CScreen* pScreen = CFramework::getFramework().getQMLScreen(m_pPopupProperty->getPopupMap().value(ePopupId).m_sQmlFilePath,NULL);
            if((pScreen) && (pScreen->component()))
            {
                retVal = QMetaObject::invokeMethod(CFramework::getFramework().getRootObject(),"loadPopup",
                                                   Q_ARG(QVariant, QVariant::fromValue(pScreen->component())) ,Q_ARG(QVariant,QVariant::fromValue(pScreen->screenName())));

                setCurrentDisplayedPopup(getCurrentRequestedPopup());
                setCurrentRequestedPopup(CPopupEnum::EN_POPUPID_UNKNOWN);
                broadcastPopupResult(ePopupId, CPopupEnum::EN_POPUP_RESULT_DISPLAYED);
                if(!retVal)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"loadPopup: invokeMethod failed retVal %d", retVal);
                }
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : screen or screen->component are NULL",__FUNCTION__);
            }
        }
        else if(CPopupEnum::EN_POPUP_ZONE_TWO == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            CScreen* pScreen = CFramework::getFramework().getQMLScreen(m_pPopupProperty->getPopupMap().value(ePopupId).m_sQmlFilePath,NULL);

            if(pScreen)
            {
                emit sigShowNotificationPopup(m_pPopupProperty->getPopupMap().value(ePopupId).m_sQmlFilePath, QVariant::fromValue(pScreen->screenName()), getCurrentRequestedNotification());
                CLayerManagerAdaptor::getInstance()->showScene(CLayerManagerEnums::SURFACE_HVAC_NOTIFICATIONS);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : screen or screen->component are NULL",__FUNCTION__);
            }

            setCurrentDisplayedNotification(getCurrentRequestedNotification());
            setCurrentRequestedNotification(CPopupEnum::EN_POPUPID_UNKNOWN);
            broadcastPopupResult(ePopupId, CPopupEnum::EN_POPUP_RESULT_DISPLAYED);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Popup Zone not defined | %d",__FUNCTION__,ePopupId);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupProperty is NULL ",__FUNCTION__);
    }

}

void CPopupManager::unloadPopup(CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    bool retVal = false;

    if(m_pPopupProperty)
    {
        if(CPopupEnum::EN_POPUP_ZONE_FOUR == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            if(CPopupEnum::EN_POPUP_RESULT_INVALID == m_ePopupResult)
            {
                setPopupResult(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT);
            }

            retVal = QMetaObject::invokeMethod(CFramework::getFramework().getRootObject(),"unloadPopup");
            if(!retVal)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"closePopup: invokeMethod failed retVal %d", retVal);
            }
            else
            {
                broadcastPopupResult(ePopupId, m_ePopupResult);
            }
            setCurrentDisplayedPopup(CPopupEnum::EN_POPUPID_UNKNOWN);
        }
        else if(CPopupEnum::EN_POPUP_ZONE_TWO == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            if(CPopupEnum::EN_POPUP_RESULT_INVALID == m_eNotificationResult)
            {
                m_eNotificationResult = CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT;
            }
            emit sigCloseNotificationPopup();

            CLayerManagerAdaptor::getInstance()->hideScene(CLayerManagerEnums::SURFACE_HVAC_NOTIFICATIONS);
            broadcastPopupResult(ePopupId, m_eNotificationResult);
            m_eNotificationResult = CPopupEnum::EN_POPUP_RESULT_INVALID;
            setCurrentDisplayedNotification(CPopupEnum::EN_POPUPID_UNKNOWN);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Popup Zone not defined | %d",__FUNCTION__,ePopupId);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupProperty is NULL ",__FUNCTION__);
    }

}

void CPopupManager::closeOnTouch()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    if(m_pPopupProperty)
    {
        if(isPopupAlive())
        {
            if(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedPopup).m_bCloseOnTouch)
            {
                setPopupResult(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TOUCH);
                CHMIMain::getSM()->getSCI_Popup()->raise_evForceClosePopup();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : close on touch is false for popup",__FUNCTION__);
            }
        }
        else if(isNotificationAlive())
        {
            if(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedNotification).m_bCloseOnTouch)
            {
                m_eNotificationResult = CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TOUCH;
                CHMIMain::getSM()->getSCI_Popup()->raise_evForceCloseNotification();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : close on touch is false for notification",__FUNCTION__);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : No popup or notification is alive",__FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupProperty is NULL",__FUNCTION__);
    }
}

void CPopupManager::setPopupResult(CPopupEnum::EPopupResult ePopupresult)
{
    LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : ePopupresult: %d",__FUNCTION__, ePopupresult);
    if(ePopupresult != m_ePopupResult)
    {
        m_ePopupResult = ePopupresult;
        emit sigPopupResultChanged();
    }
}

void CPopupManager::enqueuePopup(CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    if(!isExist(ePopupId))
    {
        if(m_pPopupProperty)
        {
            if(CPopupEnum::EN_POPUP_ZONE_FOUR == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s, zone 4 enqueue completed, popupId: %d", __FUNCTION__, ePopupId);
                //Adding the popup at the end of the list
                m_lPendingPopups.push_back(m_pPopupProperty->getPopupMap().value(ePopupId));
                //Sorting the list on the basis of Popup Priority
                m_lPendingPopups.sort(comparePriority());
            }
            else if(CPopupEnum::EN_POPUP_ZONE_TWO == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
            {
                //Adding the popup at the end of the list
                m_lPendingNotification.push_back(m_pPopupProperty->getPopupMap().value(ePopupId));
                //Sorting the list on the basis of Popup Priority
                m_lPendingNotification.sort(comparePriority());
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Popup Zone not defined ",__FUNCTION__);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupProperty is NULL ",__FUNCTION__);
        }
    }
}

CPopupEnum::EPopupID CPopupManager::dequeuePopup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);

    CPopupPropertyHandler::CPopupProperties pProp = CPopupManager::getInstance()->m_lPendingPopups.front();
    CPopupManager::getInstance()->m_lPendingPopups.pop_front();
    return pProp.m_eId;
}

void CPopupManager::handlePriority(CPopupEnum::EPopupID ePopupId)
{
    /** NOTE : The popup priority is in reverse ordered, lesser the value higher the priority */

    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    if(m_pPopupProperty)
    {
        if(CPopupEnum::EN_POPUP_ZONE_FOUR == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            //Check if Priority of requested popup is more than or equal to that of already displayed popup
            if(m_pPopupProperty->getPopupMap().value(ePopupId).m_ePriority <= m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedPopup).m_ePriority)
            {
                //Check if Min. Timer of the popup is still running
                if(!(CHMIMain::getSM()->getSCI_Popup()->get_isMinPopupTimeoutOver()))
                {
                    //Enqueue the requested popup
                    enqueuePopup(ePopupId);
                    setCurrentRequestedPopup(CPopupEnum::EN_POPUPID_UNKNOWN);

                    //set set_isCloseOnMinTimeoutPopup to true, to close the popup after it's min. timeout get's over
                    CHMIMain::getSM()->getSCI_Popup()->set_isCloseOnMinTimeoutPopup(true);
                    return;
                }

                //Check if closeOnSupersede of currently Displayed popup is false
                if(!(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedPopup).m_bCloseOnSupersede))
                {
                    //Check if Max. Timer is still running for currently Displayed Popup
                    if(!(CHMIMain::getSM()->getSCI_Popup()->get_isMaxPopupTimeoutOver()))
                    {
                        //Enqueue currently displayed Popup
                        enqueuePopup(m_eCurrentDisplayedPopup);
                        setCurrentDisplayedPopup(CPopupEnum::EN_POPUPID_UNKNOWN);
                    }
                    else
                    {
                        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Popup Max Timeout Over ",__FUNCTION__);
                    }
                }
                else
                {
                    setPopupResult(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_SUPERSEDE);
                }
                //Force close the currently Displayed popup
                CHMIMain::getSM()->getSCI_Popup()->raise_evForceClosePopup();
            }
            else
            {
                //Check if closeOnSupersede property of requested popup is false
                if(!(m_pPopupProperty->getPopupMap().value(ePopupId).m_bCloseOnSupersede))
                {
                    //Enqueue the requested popup
                    enqueuePopup(ePopupId);
                    setCurrentRequestedPopup(CPopupEnum::EN_POPUPID_UNKNOWN);
                }
                else
                {
                    // Sent out signal to ignore the popup.
                    broadcastPopupResult(ePopupId, CPopupEnum::EN_POPUP_RESULT_IGNORED);
                    setCurrentRequestedPopup(CPopupEnum::EN_POPUPID_UNKNOWN);
                }
            }
        }
        else if(CPopupEnum::EN_POPUP_ZONE_TWO == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            //Check if Priority of requested notification is more than or equal to that of already displayed notification
            if(m_pPopupProperty->getPopupMap().value(ePopupId).m_ePriority <= m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedNotification).m_ePriority)
            {
                //Check if Min. Timer of the notification is still running
                if(!(CHMIMain::getSM()->getSCI_Popup()->get_isMinNotificationTimeoutOver()))
                {
                    //FixMe : Current Notification shall get closed after it's min. timeout is over
                    enqueuePopup(ePopupId);
                    setCurrentRequestedNotification(CPopupEnum::EN_POPUPID_UNKNOWN);

                    //set set_isCloseOnMinTimeoutNotification to true, to close the notification after it's min. timeout get's over
                    CHMIMain::getSM()->getSCI_Popup()->set_isCloseOnMinTimeoutNotification(true);
                    return;
                }

                //Check if closeOnSupersede of currently Displayed notification is false
                if(!(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedNotification).m_bCloseOnSupersede))
                {
                    //Check if Max. Timer is still running for currently Displayed notification
                    if(!(CHMIMain::getSM()->getSCI_Popup()->get_isMaxNotificationTimeoutOver()))
                    {
                        //Enqueue currently displayed notification
                        enqueuePopup(m_eCurrentDisplayedNotification);
                        setCurrentDisplayedNotification(CPopupEnum::EN_POPUPID_UNKNOWN);
                    }
                    else
                    {
                        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Notification Max Timeout not Over ",__FUNCTION__);
                    }
                }
                else
                {
                    m_eNotificationResult = CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_SUPERSEDE;
                }
                //Force close the currently Displayed notification
                CHMIMain::getSM()->getSCI_Popup()->raise_evForceCloseNotification();
            }
            else
            {
                //Check if closeOnSupersede property of requested notification is false
                if(!(m_pPopupProperty->getPopupMap().value(ePopupId).m_bCloseOnSupersede))
                {
                    //Enqueue the requested notification
                    enqueuePopup(ePopupId);
                    setCurrentRequestedNotification(CPopupEnum::EN_POPUPID_UNKNOWN);
                }
                else
                {
                    // emitting notification result signal with status ignored
                    broadcastPopupResult(ePopupId, CPopupEnum::EN_POPUP_RESULT_IGNORED);
                    setCurrentRequestedNotification(CPopupEnum::EN_POPUPID_UNKNOWN);
                }
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Popup Zone not defined ",__FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupProperty is NULL ",__FUNCTION__);
    }
}

void CPopupManager::handlePopupsWithNoTimeOut(CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, "%s, ePopupId:%d", __FUNCTION__, static_cast<int>(ePopupId));
    if (m_eCurrentDisplayedPopup != ePopupId)
    {
        if (CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON == m_eCurrentDisplayedPopup)
        {
            forceClosePopup(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON);
        }
        else if (CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON_PREVIEW == m_eCurrentDisplayedPopup)
        {
            forceClosePopup(CPopupEnum::EN_POPUPID_DOODLE_MYSTICKER_ICON_PREVIEW);
        }
        else if (CPopupEnum::EN_POPUPID_DOODLE_STARTUP_IMAGE_PREVIEW == m_eCurrentDisplayedPopup)
        {
            forceClosePopup(CPopupEnum::EN_POPUPID_DOODLE_STARTUP_IMAGE_PREVIEW);
        }
        else
        {
            //Do Nothing!
        }
    }
}

void CPopupManager::showPendingNotification()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);

    /**
     * Check if m_lPendingNotification is not empty and m_eCurrentRequestedNotification is also set to EN_POPUPID_UNKNOWN,
     * Pop the first notification in the list and show it over the screen
     */
    if(!(m_lPendingNotification.empty()) && (m_eCurrentRequestedNotification == CPopupEnum::EN_POPUPID_UNKNOWN))
    {
        setCurrentRequestedNotification(m_lPendingNotification.front().m_eId);
        CHMIMain::getSM()->getSCI_Popup()->raise_evShowNotification();
        m_lPendingNotification.pop_front();
    }
    /**
     * If m_eCurrentRequestedNotification is not EN_POPUPID_UNKNOWN, that means the requested notification needs to be shown
     */
    else if(m_eCurrentRequestedNotification != CPopupEnum::EN_POPUPID_UNKNOWN)
    {
        CHMIMain::getSM()->getSCI_Popup()->raise_evShowNotification();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : No Pending Notification",__FUNCTION__);
    }
}

void CPopupManager::showPendingPopup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s, m_lPendingPopups.empty() : %d, m_eCurrentRequestedPopup: %d", __FUNCTION__, m_lPendingPopups.empty(), m_eCurrentRequestedPopup);

//    if(!getPopupQueuingStatus())
//    {
        /**
         * Check if m_lPendingPopups is not empty and m_eCurrentRequestedPopup is also set to EN_POPUPID_UNKNOWN,
         * Pop the first popup in the list and show it over the screen
         */
        if(!(m_lPendingPopups.empty()) && (m_eCurrentRequestedPopup == CPopupEnum::EN_POPUPID_UNKNOWN))
        {
            setCurrentRequestedPopup(m_lPendingPopups.front().m_eId);
            m_lPendingPopups.pop_front();
            CHMIMain::getSM()->getSCI_Popup()->raise_evShowPopup();
        }
        /**
         * If m_eCurrentRequestedPopup is not EN_POPUPID_UNKNOWN, that means the requested popup needs to be shown
         */
        else if(m_eCurrentRequestedPopup != CPopupEnum::EN_POPUPID_UNKNOWN)
        {
            CHMIMain::getSM()->getSCI_Popup()->raise_evShowPopup();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : No Pending Popups",__FUNCTION__);
        }
//    }
//    else
//    {
//        LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : m_bStartPopupQueueing is true. Hence, showPendingPopup is skipped",__FUNCTION__);
//    }

}

bool CPopupManager::isPopupAllowed(CPopupEnum::EPopupID ePopupId)
{
    CPopupEnum::EPopupApplicableContext eCurrentHMIContext = static_cast<CPopupEnum::EPopupApplicableContext>(CHMIMain::getSM()->getDefaultSCI()->get_iCurrentHMIContext());

    LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Current Context : %d popupID : %d",__FUNCTION__, eCurrentHMIContext, ePopupId);

    bool bRet = false;
    if(m_pPopupProperty)
    {
        if(CPopupPropertyHandler::CPopupProperties::m_vecInvalidContext.contains(eCurrentHMIContext))
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : CPopupEnum::EN_HMI_INVALID_CONTEXT", __FUNCTION__);
            if(m_pPopupProperty->getPopupMap().value(ePopupId).m_bEnqueue)
            {
                enqueuePopup(ePopupId);
            }
            setCurrentRequestedPopup(CPopupEnum::EN_POPUPID_UNKNOWN);
            setCurrentRequestedNotification(CPopupEnum::EN_POPUPID_UNKNOWN);
            bRet = false;
        }
        else
        {
            if(m_pPopupProperty->getPopupMap().value(ePopupId).m_vecApplicableContext.contains(eCurrentHMIContext))
            {
                bRet = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : Popup is not applicable in %d context", __FUNCTION__, eCurrentHMIContext);
                if(m_pPopupProperty->getPopupMap().value(ePopupId).m_bEnqueue)
                {
                    enqueuePopup(ePopupId);
                }
                else
                {
                    broadcastPopupResult(ePopupId,CPopupEnum::EN_POPUP_RESULT_IGNORED);
                }
                setCurrentRequestedPopup(CPopupEnum::EN_POPUPID_UNKNOWN);
                setCurrentRequestedNotification(CPopupEnum::EN_POPUPID_UNKNOWN);
            }
        }
    }
    return bRet;
}

void CPopupManager::checkPopupContext()
{
    CPopupEnum::EPopupApplicableContext eCurrentHMIContext = static_cast<CPopupEnum::EPopupApplicableContext>(CHMIMain::getSM()->getDefaultSCI()->get_iCurrentHMIContext());
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP, "%s, Current HMI context : %d",__FUNCTION__, eCurrentHMIContext);

    /**
     * @note m_bStartPopupQueueing is set to TRUE when HMI enters contexts like PDC_RVC_CONTEXT & PHONE_CALL_CONTEXT.
     *       This would ensure that after entering these states, showPending method is skipped.
     */
    if(eCurrentHMIContext == CPopupEnum::EPopupApplicableContext::EN_HMI_PDC_RVC_CONTEXT
            || eCurrentHMIContext == CPopupEnum::EPopupApplicableContext::EN_HMI_PHONE_CALL_CONTEXT)
    {
        setStartPopupQueueing(true);
    }
    else
    {
        if(getPopupQueuingStatus())
        {
            setStartPopupQueueing(false);
        }
    }

    if(m_pPopupProperty)
    {
        // This check has no effect on HMI but can be used in future, when popup needs to be enqueued in invalid context
        if(CPopupPropertyHandler::CPopupProperties::m_vecInvalidContext.contains(eCurrentHMIContext))
        {
            if(CPopupEnum::EN_POPUPID_UNKNOWN != m_eCurrentDisplayedNotification)
            {
                if(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedNotification).m_bEnqueue)
                {
                    enqueuePopup(m_eCurrentDisplayedNotification);
                }
                m_eNotificationResult = CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CONTEXT_CHANGE;
                CHMIMain::getSM()->getSCI_Popup()->raise_evForceCloseNotification();
            }
            if(CPopupEnum::EN_POPUPID_UNKNOWN != m_eCurrentDisplayedPopup)
            {
                if(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedPopup).m_bEnqueue)
                {
                    enqueuePopup(m_eCurrentDisplayedPopup);
                }
                setPopupResult(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CONTEXT_CHANGE);
                CHMIMain::getSM()->getSCI_Popup()->raise_evForceClosePopup();
            }
        }
        else
        {
            if(m_eCurrentDisplayedPopup == CPopupEnum::EN_POPUPID_UNKNOWN)
            {
                showPendingPopup();
            }
            else
            {
                if(!m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedPopup).m_vecApplicableContext.contains(eCurrentHMIContext))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : Popup is not applicable in %d context", __FUNCTION__, eCurrentHMIContext);
                    if(m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedPopup).m_bEnqueue)
                    {
                        enqueuePopup(m_eCurrentDisplayedPopup);
                    }
                    setPopupResult(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CONTEXT_CHANGE);
                    CHMIMain::getSM()->getSCI_Popup()->raise_evForceClosePopup();
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : Popup is applicable in %d context", __FUNCTION__, eCurrentHMIContext);
                }
            }



            if(m_eCurrentDisplayedNotification == CPopupEnum::EN_POPUPID_UNKNOWN )
            {
                showPendingNotification();
            }
            else
            {
                if(!m_pPopupProperty->getPopupMap().value(m_eCurrentDisplayedNotification).m_vecApplicableContext.contains(eCurrentHMIContext))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : Notification is not applicable in %d context", __FUNCTION__, eCurrentHMIContext);
                    m_eNotificationResult = CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_CONTEXT_CHANGE;
                    CHMIMain::getSM()->getSCI_Popup()->raise_evForceCloseNotification();
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s : Notification is applicable in %d context", __FUNCTION__, eCurrentHMIContext);
                }
            }
        }
    }
}

void CPopupManager::sltEnterNoPopupState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    showPendingPopup();
}

void CPopupManager::sltEnterNoNotificationState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    showPendingNotification();
}

bool CPopupManager::isExist(CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,__FUNCTION__);
    bool bRet = false;

    if(m_pPopupProperty)
    {
        if(CPopupEnum::EN_POPUP_ZONE_FOUR == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            //Iterating through the list
            for(CPopupPropertyHandler::CPopupProperties const& objPopupProperties : m_lPendingPopups )
            {
                if(ePopupId == objPopupProperties.m_eId)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s, Popup already exist in list, popupId: %d", __FUNCTION__, ePopupId);
                    bRet = true;
                    return bRet;
                }
            }
        }
        else if(CPopupEnum::EN_POPUP_ZONE_TWO == m_pPopupProperty->getPopupMap().value(ePopupId).m_ePopupZone)
        {
            //Iterating through the list
            for(CPopupPropertyHandler::CPopupProperties const& objPopupProperties : m_lPendingNotification )
            {
                if(ePopupId == objPopupProperties.m_eId)
                {
                    bRet = true;
                    return bRet;
                }
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : Popup Zone not defined | %d",__FUNCTION__,ePopupId);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_POPUP,"%s : m_pPopupProperty is NULL ",__FUNCTION__);
    }
    return bRet;
}

void CPopupManager::setCurrentDisplayedPopup(CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s Current Displayed Popup:%d",__FUNCTION__,ePopupId);
    m_eCurrentDisplayedPopup = ePopupId;
}

void CPopupManager::setCurrentRequestedPopup(CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s Current Requested Popup:%d",__FUNCTION__,ePopupId);
    m_eCurrentRequestedPopup = ePopupId;
}

void CPopupManager::setCurrentRequestedNotification(CPopupEnum::EPopupID ePopupId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_POPUP,"%s Current Requested Notification:%d",__FUNCTION__,ePopupId);
    m_eCurrentRequestedNotification = ePopupId;
}

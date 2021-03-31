/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDrawersAdaptor.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition of all functions of Adaptor class of
* Drawers, This is used by QML files to get the information needs to show on view.
*/

#include "CDrawersAdaptor.h"
#include "CLayerManagerAdaptor.h"
#include "CAudioAdaptor.h"
#include "CAndroidAutoAdaptor.h"
#include "CAppleCarPlayAdaptor.h"

CDrawersAdaptor	*CDrawersAdaptor::m_pDrawersAdaptor	= nullptr;

CDrawersAdaptor::CDrawersAdaptor(QObject *pParent) : QObject(pParent),
    m_strDrawersState(DRAWERS_STATE_HIDDEN_STRING),
    m_strSrcDrawerState(DRAWERS_STATE_HIDDEN_STRING),
    m_strShortcutDrawerState(DRAWERS_STATE_HIDDEN_STRING),
    m_bEnableHomeButton(true),
    m_bEnableSettingsButton(true),
    m_strHvacDrawerState(DRAWERS_STATE_HIDDEN_STRING),
    m_strQadDrawerState(DRAWERS_STATE_HIDDEN_STRING),
    m_iDrawersMaximizeMinimizeAnimationDuration(100),
    m_iDrawersShowHideAnimationDuration(100),
    m_bShowMuteStatus(false),
    m_bAllowStatusBarOnScreen(false),
    m_strNotificationOverlayState(""),
    m_eActiveNotification(CDrawersEnums::EN_NOTIFICATION_TYPE_NONE)
{
    CFramework::getFramework().setContextProperty("cppDrawersAdaptor",this);
    CDrawersEnums::registerDrawersEnumsToQML();
    connect(&m_objDateTimeTimer, SIGNAL(timeout()),this,SLOT(sltDateTimeTimeout()));
    m_objDateTimeTimer.start(100);
    connectSignals();
}

void CDrawersAdaptor::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s", __FUNCTION__);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigMuteStateChanged()),
            this, SLOT(sltMuteStatusChanged()), Qt::QueuedConnection);
    connect(CLayerManagerAdaptor::getInstance(), &CLayerManagerAdaptor::sigNotificationLayerVisibilityState,
            this, &CDrawersAdaptor::sltNotificationLayerVisibilityState);

    connect(this, SIGNAL(sigChangeMuteStatusOnScreenExit()), this, SLOT(sltChangeMuteStatusOnScreenExit()), Qt::QueuedConnection);
    connect(this, SIGNAL(sigHideNotificationOverlay()), this, SLOT(sltHideNotificationOverlay()), Qt::QueuedConnection);
}

void CDrawersAdaptor::disconnectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s", __FUNCTION__);
    disconnect(CAudioAdaptor::getInstance(), SIGNAL(sigMuteStateChanged()),
               this, SLOT(sltMuteStatusChanged()));
    disconnect(CLayerManagerAdaptor::getInstance(), &CLayerManagerAdaptor::sigNotificationLayerVisibilityState,
               this, &CDrawersAdaptor::sltNotificationLayerVisibilityState);

    disconnect(this, SIGNAL(sigChangeMuteStatusOnScreenExit()), this, SLOT(sltChangeMuteStatusOnScreenExit()));
    disconnect(this, SIGNAL(sigHideNotificationOverlay()), this, SLOT(sltHideNotificationOverlay()));
}

void CDrawersAdaptor::sltMuteStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s - Mute status: %d", __FUNCTION__, CAudioAdaptor::getInstance()->muteActive());

    /**
     * If AA/Carplay projection status is true, Mute bar slide in only when mute is active
     */
    if ((m_bShowMuteStatus) && (CAudioAdaptor::getInstance()->muteActive()))
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evShowVolOverlay();
    }
    /**
     * Else on HMI, VolumeBar shall slide out if Mute status is received as true,
     * As we have Mute symbole on Native HMI.
     */
    else if(CAudioAdaptor::getInstance()->muteActive())
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evHideVolOverlay();
    }
    else
    {
        //Do Nothing
    }
}

void CDrawersAdaptor::sltNotificationLayerVisibilityState(bool bVisibilityState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: notification layer visibility state: %d", __FUNCTION__, static_cast<int>(bVisibilityState));

    if (false == bVisibilityState)
    {
        sltHideNotificationOverlay();
    }
    else
    {
        // Do nothing
    }
}

void CDrawersAdaptor::sltChangeMuteStatusOnScreenExit()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s", __FUNCTION__);
    setShowMuteStatus(false);
}

void CDrawersAdaptor::setEnableHomeButton(const bool &bEnableHomeButton)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS,  "%s, : bEnableHomeButton: %d",
             __FUNCTION__, bEnableHomeButton);

    if (m_bEnableHomeButton != bEnableHomeButton)
    {
        m_bEnableHomeButton = bEnableHomeButton;
        emit sigEnableHomeButtonChanged();
    }
}

void CDrawersAdaptor::setEnableSettingsButton(const bool &bEnableSettingsButton)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s, bEnableSettingsButton: %d",
             __FUNCTION__, bEnableSettingsButton);

    if (m_bEnableSettingsButton != bEnableSettingsButton)
    {
        m_bEnableSettingsButton = bEnableSettingsButton;
        emit sigEnableSettingsButtonChanged();
    }
}

void CDrawersAdaptor::setHvacDrawerState(const QString &strHvacDrawerState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s, strHvacDrawerState: %s",
             __FUNCTION__, strHvacDrawerState.toStdString().c_str());

    if (m_strHvacDrawerState != strHvacDrawerState)
    {
        m_strHvacDrawerState = strHvacDrawerState;
        emit sigHvacDrawerStateChanged();
        setShortcutDrawerState(strHvacDrawerState);
    }
}

void CDrawersAdaptor::setQadDrawerState(const QString &strQadDrawerState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: strQadDrawerState: %s",
             __FUNCTION__, strQadDrawerState.toStdString().c_str());

    if ( m_strQadDrawerState != strQadDrawerState)
    {
        m_strQadDrawerState = strQadDrawerState;
        emit sigQadDrawerStateChanged();
    }
}

void CDrawersAdaptor::setDrawersMaximizeMinimizeAnimationDuration(const int &iMaximizedMinimizedAnimationDuration)
{
    if (m_iDrawersMaximizeMinimizeAnimationDuration != iMaximizedMinimizedAnimationDuration)
    {
        m_iDrawersMaximizeMinimizeAnimationDuration = iMaximizedMinimizedAnimationDuration;
        emit sigDrawersMaximizeMinimizeAnimationDurationChanged();
    }
}

void CDrawersAdaptor::setDrawersShowHideAnimationDuration(const int &iShowHideAnimationDuration)
{
    if (m_iDrawersShowHideAnimationDuration != iShowHideAnimationDuration)
    {
        m_iDrawersShowHideAnimationDuration = iShowHideAnimationDuration;
        emit sigDrawersShowHideAnimationDurationChanged();
    }
}

bool CDrawersAdaptor::handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: eKey: %d, eKeyState: %d", __FUNCTION__, eKey, eKeyState);

    bool bRes = false;
    switch(eKey)
    {
    case CHardKeyEnum::KEYCODEHK_VOLROTARY:
    case CHardKeyEnum::KEYCODEHK_MENUROTARY:
    case CHardKeyEnum::KEYCODEHK_BACK:
    {
        if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) ||
                (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
        {
            //If drawer is in maximized state then back key will only close the drawer hence setting the bRes to true.
            bRes = closeDrawers();
        }
        else
        {
            //Do Nothing
        }
    }
        break;
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

        if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) ||
                (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
        {
            closeDrawers();
        }
        else
        {
            //Do Nothing
        }
    }
        break;

    case CHardKeyEnum::KEYCODEHK_MENUROTARY_KNOB:
        bRes = isDrawerMaximized();
        break;

    default:
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s Invalid data received key: %d state: %d ", __FUNCTION__, static_cast<int>(eKey), static_cast<int>(eKeyState));
    }

    return bRes;
}

bool CDrawersAdaptor::closeDrawers()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);

    bool bRes = false;

    if((m_strShortcutDrawerState.compare(DRAWERS_STATE_MAXIMIZED_STRING) == 0 ))
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evMinimizeShortcutDrawer();
        bRes = true;
    }
    else if (m_strQadDrawerState.compare(DRAWERS_STATE_MAXIMIZED_STRING) == 0 )
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evMinimizeQadDrawer();
        bRes = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s No drawers open", __FUNCTION__);
    }

    return bRes;
}

void CDrawersAdaptor::sltHideNotificationOverlay()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);

    CHMIMain::getSM()->getSCI_Drawers()->raise_evHideVolOverlay();

    CHMIMain::getSM()->getSCI_Drawers()->raise_evHideHvacOverlay();
}

void CDrawersAdaptor::setNotificationOverlayState(const QString &strNotificationOverlayState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : strNotificationOverlayState: %s", __FUNCTION__, strNotificationOverlayState.toStdString().c_str());

    if (m_strNotificationOverlayState != strNotificationOverlayState)
    {
        m_strNotificationOverlayState = strNotificationOverlayState;

        emit sigNotificationOverlayStateChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s : Values are same.", __FUNCTION__);
    }
}

void CDrawersAdaptor::setActiveNotification(CDrawersEnums::ENotificationTypes eActiveNotification)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : eActiveNotification: %d", __FUNCTION__, eActiveNotification);

    if (m_eActiveNotification != eActiveNotification)
    {
        m_eActiveNotification = eActiveNotification;

        emit sigActiveNotificationChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s : Values are same.", __FUNCTION__);
    }
}

bool CDrawersAdaptor::allowStatusBarOnScreen()
{
    return m_bAllowStatusBarOnScreen;
}

void CDrawersAdaptor::setAllowStatusBarOnScreen(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : bStatus: %d", __FUNCTION__, bStatus);
    if (m_bAllowStatusBarOnScreen != bStatus)
    {
        m_bAllowStatusBarOnScreen = bStatus;
        emit sigAllowStatusBarOnScreenChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : no change in m_bAllowStatusBarOnScreen", __FUNCTION__);
    }
}

void CDrawersAdaptor::setShowMuteStatus(bool bShowMuteStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : bShowMuteStatus: %d", __FUNCTION__, bShowMuteStatus);

    if (m_bShowMuteStatus != bShowMuteStatus)
    {
        m_bShowMuteStatus = bShowMuteStatus;
        /*
         * If Show mute status gets false, then hide the slide bar immidiately
         */
        if (!m_bShowMuteStatus)
        {
            emit sigHideNotificationOverlay();
        }
        else
        {
            // Do nothing.
        }

        emit sigShowMuteStateChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s : Values are same.", __FUNCTION__);
    }
}

CDrawersAdaptor::~CDrawersAdaptor()
{

}

CDrawersAdaptor *CDrawersAdaptor::getInstance()
{
    if (!m_pDrawersAdaptor)
    {
        m_pDrawersAdaptor = new CDrawersAdaptor();
    }
    return m_pDrawersAdaptor;
}

bool CDrawersAdaptor::isDrawerMaximized()
{
    bool bStatus = ((m_strShortcutDrawerState.compare(DRAWERS_STATE_MAXIMIZED_STRING) == 0 ) ||
                    (m_strQadDrawerState.compare(DRAWERS_STATE_MAXIMIZED_STRING) == 0 ));

    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : bStatus: %d", __FUNCTION__, bStatus);
    return bStatus;
}

void CDrawersAdaptor::setDrawersState(const QString &strDrawersState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : strSrcDrawerState: %s",
             __FUNCTION__, strDrawersState.toStdString().c_str());

    if (m_strDrawersState != strDrawersState)
    {
        m_strDrawersState = strDrawersState;
        emit sigDrawersStateChanged();
    }
}

void CDrawersAdaptor::setSrcDrawerState(const QString &strSrcDrawerState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : strSrcDrawerState: %s", __FUNCTION__, strSrcDrawerState.toStdString().c_str());
    if (m_strSrcDrawerState != strSrcDrawerState)
    {
        m_strSrcDrawerState = strSrcDrawerState;
        emit sigSrcDrawerStateChanged();
        setShortcutDrawerState(strSrcDrawerState);
    }
}

void CDrawersAdaptor::setShortcutDrawerState(const QString &strShortcutDrawerState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : strShortcutDrawerState: %s", __FUNCTION__, strShortcutDrawerState.toStdString().c_str());
    if (m_strShortcutDrawerState!= strShortcutDrawerState)
    {
        m_strShortcutDrawerState = strShortcutDrawerState;
        emit sigShortcutDrawerStateChanged();
    }
}

void CDrawersAdaptor::sltDateTimeTimeout()
{
    //LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s:", __FUNCTION__);
    emit sigDateTimeRefresh();
}


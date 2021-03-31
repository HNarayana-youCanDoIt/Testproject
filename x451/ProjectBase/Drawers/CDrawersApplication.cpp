/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDrawersApplication.cpp
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition of all functions of CDrawersApplication class of
* Drawers.
*/

#include "CDrawersApplication.h"
#include "CDrawersSM.h"
#include "CHomeAdaptor.h"
#include "CDrawersAdaptor.h"
#include "CAudioAdaptor.h"
#include "CHVACAdaptor.h"
#include "CDisplayManagerAdaptor.h"
#include "CParkAssistAdaptor.h"
#include "CPowerModeAdaptor.h"
#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"

CDrawersApplication::CDrawersApplication(QQuickItem *pParent)
    : CBaseApplication(pParent),
      m_pDrawersSM(new CDrawersSM(*this))
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, __FUNCTION__);

    mfw.setContextProperty("cppDrawersApp",this);
    connectSignals();
}

CDrawersApplication::~CDrawersApplication()
{
    if (m_pDrawersSM)
    {
        delete m_pDrawersSM;
        m_pDrawersSM = nullptr;
    }

    disconnectSignals();
}

void CDrawersApplication::onCreated(QQuickItem *pRootObject)
{
    Q_UNUSED(pRootObject)
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);
}

void CDrawersApplication::raiseSMEvent(const QString &name, const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: name: %s , data: %d", __FUNCTION__, name.toStdString().c_str(), data.toInt());

    if(DRAWERS_NAME_STRING == name)
    {
        raiseCommonSMEventsForDrawers(static_cast<CDrawersEnums::ECommonEventsForDrawers> (data.toInt()));
    }
    else if (SHORTCUT_DRAWER_NAME_STRING == name)
    {
        raiseSMEventFromShortcutDrawer(static_cast<CDrawersEnums::EShortcutDrawerButtonID> (data.toInt()));
    }
    else if (QAD_DRAWER_NAME_STRING == name)
    {
        raiseSMEventFromQADDrawer(static_cast<CDrawersEnums::EQadDrawerButtonID> (data.toInt()));
    }
    else if (SOURCE_DRAWER_NAME_STRING == name)
    {
        raiseSMEventFromSourceDrawer(static_cast<CDrawersEnums::ESourceDrawerButtonID> (data.toInt()));
    }
    else{
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: In else", __FUNCTION__);
    }

}

void CDrawersApplication::raiseSMEventFromShortcutDrawer(const CDrawersEnums::EShortcutDrawerButtonID &eShortcutDrawerButtonID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: eShortcutDrawerButtonID: %d", __FUNCTION__, eShortcutDrawerButtonID);
    switch(eShortcutDrawerButtonID)
    {
    case CDrawersEnums::SHORTCUT_DRAWER_BUTTON_CLIMATE_ID:
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evMaximizeHVACDrawer();
    }
        break;
    case CDrawersEnums::SHORTCUT_DRAWER_BUTTON_PARKASSIST_ID:
    {
        CParkAssistAdaptor::getInstance()->activatePdcRvc(true);
    }
        break;
    case CDrawersEnums::SHORTCUT_DRAWER_BUTTON_SOURCE_ID:
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evMaximizeSourceDrawer();
    }
        break;
    case CDrawersEnums::SHORTCUT_DRAWER_BUTTON_HOME_ID:
    {
        //As per TML requirement for doodle,
        //this flow is added to handle doodle flow when
        //
        //Doodle is displayed and user goes in doodle setup screen by touching doodle
        //inside doodle screen if user tries to come out by pressing home button present on drawer
        //the doodle should not resume and it will come as per time out conditions
        //
        //If user comes out of setup screen using back button without changing any settings or accessing drawers
        //Doodle shall resume on screen imediatly!
        if(CDoodleApplication::getDoodleAdaptor())
        {
            CDoodleApplication::getDoodleAdaptor()->setForceShowDoodleOnScreen(false);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s: CDoodleAdaptor object not available", __FUNCTION__);
        }

        CHomeAdaptor::getInstance().setCurrentPageIndex(0);
        CHMIMain::getSM()->raise_evHomeActivated();
    }
        break;
    case CDrawersEnums::SHORTCUT_DRAWER_BUTTON_MEDIAOFF_ID:
    {
        //Todo : Switch to Media Off mode
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: In Default case", __FUNCTION__);
    }
        break;
    }
}

void CDrawersApplication::raiseSMEventFromQADDrawer(const CDrawersEnums::EQadDrawerButtonID &eQadDrawerButtonID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: eQadDrawerButtonID: %d", __FUNCTION__, eQadDrawerButtonID);
    switch(eQadDrawerButtonID)
    {
    case CDrawersEnums::QAD_DRAWER_OPEN_BUTTON_ID:
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evMaximizeQadDrawer();
    }
        break;
    case CDrawersEnums::QAD_DRAWER_CLOSE_BUTTON_ID:
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evMinimizeQadDrawer();
    }
        break;
    case CDrawersEnums::QAD_DRAWER_SETTINGS_BUTTON_ID:
    {
        CHMIMain::getSM()->raise_evSetupActivated();
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: In Default case", __FUNCTION__);
    }
        break;
    }
}

void CDrawersApplication::raiseSMEventFromSourceDrawer(const CDrawersEnums::ESourceDrawerButtonID &eSourceDrawerButtonID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: eSourceDrawerButtonID: %d", __FUNCTION__, eSourceDrawerButtonID);

    switch (eSourceDrawerButtonID)
    {
    case CDrawersEnums::SOURCE_DRAWER_CLOSE_BUTTON_ID:
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evMinimizeShortcutDrawer();
    }
        break;

    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: In Default case", __FUNCTION__);
    }

    }
}

void CDrawersApplication::raiseCommonSMEventsForDrawers(CDrawersEnums::ECommonEventsForDrawers eCommonEvent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: eCommonEvent: %d", __FUNCTION__, eCommonEvent);

    switch (eCommonEvent)
    {
    case CDrawersEnums::DRAWER_COMMON_EVENT_CLOSE_TIMER_RESET:
    {
        CHMIMain::getSM()->getSCI_Drawers()->raise_evResetCloseDrawerTimer();
    }
        break;

    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: In Default case", __FUNCTION__);
    }

    }
}

void CDrawersApplication::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);

    if(CHVACAdaptor::getInstance())
    {
        connect(CHVACAdaptor::getInstance(), SIGNAL(sigCcmUserInterventionParamChanged(int)), this, SLOT(sltCcmUserInterventionParamChanged(int)));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: HVAC Adaptor instance not created.", __FUNCTION__);
    }

    if(CPopupManager::getInstance())
    {
        connect(CPopupManager::getInstance(), SIGNAL(sigPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)), this, SLOT(sltPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: Popup Adaptor instance not created.", __FUNCTION__);
    }
}

void CDrawersApplication::disconnectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);

    if(CHVACAdaptor::getInstance())
    {
        disconnect(CHVACAdaptor::getInstance(), SIGNAL(sigCcmUserInterventionParamChanged(int)), this, SLOT(sltCcmUserInterventionParamChanged(int)));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: HVAC Adaptor instance not created.", __FUNCTION__);
    }

    if(CPopupManager::getInstance())
    {
        disconnect(CPopupManager::getInstance(), SIGNAL(sigPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)), this, SLOT(sltPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: Popup Adaptor instance not created.", __FUNCTION__);
    }
}

bool CDrawersApplication::isHvacOverlayCanBeShown()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ccmPresenceState: %d, powerModeStatus: %d, control panel mode is: %d, HVAC drawer maximised state is: %d",
             __FUNCTION__, CHVACAdaptor::getInstance()->ccmPresence(), CPowerModeAdaptor::getInstance().getPowerModeStatus(),
             CHVACAdaptor::getInstance()->ctrlPanelMode(),
             CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState));

    return ((CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT)
            && (CPowerModeAdaptor::getInstance().getPowerModeStatus() != CPowerModeEnums::VPM_ONE_HOUR)
            && (CHVACAdaptor::getInstance()->ctrlPanelMode())
            && (!CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState))
            && (!CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_PDC_active_pdc_region_UI_PDC)));
}

CDrawersEnums::ENotificationTypes CDrawersApplication::getNotificationType(CHVACEnums::EHVACParamEnums eHVACParam)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: HVAC param is: %d", __FUNCTION__, eHVACParam);

    CDrawersEnums::ENotificationTypes eHVACNotificationType = CDrawersEnums::EN_NOTIFICATION_TYPE_NONE;

    switch(eHVACParam)
    {
    case CHVACEnums::HUCCM_AIRCON_CTRL:
        eHVACNotificationType = CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_AC_MODE_STATUS;
        break;
    case CHVACEnums::HUCCM_ECON_MODE:
        eHVACNotificationType = CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_ECON_MODE_STATUS;
        break;
    case CHVACEnums::HUCCM_AUTO_MODE:
        eHVACNotificationType = CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_AUTO_MODE_STATUS;
        break;
    case CHVACEnums::HUCCM_HVAC_CTRL:
        eHVACNotificationType = CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_CLIMATE_MODE_STATUS;
        break;
    case CHVACEnums::HUCCM_MAX_DEFRST:
        eHVACNotificationType = CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_MAX_DEFROST_MODE_STATUS;
        break;
    case CHVACEnums::HUCCM_FRESHAIR_RECIRC:
        eHVACNotificationType = CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_AIR_CIRCULATION_MODE_STATUS;
        break;
    case CHVACEnums::HUCCM_DISTRIB_MODE:
        eHVACNotificationType = CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_DISTRIBUTION_MODE_STATUS;
        break;
    case CHVACEnums::HUCCM_FAN_SPEED:
        eHVACNotificationType = CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_FAN;
        break;
    case CHVACEnums::HUCCM_TEMP_CHANGE:
        eHVACNotificationType = CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_TEMPERATURE;
        break;
    default:
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"%s: unhandled HVAC parameter",__FUNCTION__);
        break;
    }

    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: HVAC notification type is: %d", __FUNCTION__, eHVACNotificationType);
    return eHVACNotificationType;
}

void CDrawersApplication::displayHVACNotificationOverlay(CDrawersEnums::ENotificationTypes eHVACNotificationType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: HVAC notification type is: %d", __FUNCTION__, eHVACNotificationType);

    CDrawersEnums::ENotificationTypes eActiveOverlay = CDrawersAdaptor::getInstance()->activeNotification();

    if (isHvacOverlayCanBeShown())
    {
        if (CDrawersEnums::EN_NOTIFICATION_TYPE_NONE != eActiveOverlay)
        {
            if (eHVACNotificationType == eActiveOverlay)
            {
                CHMIMain::getSM()->getSCI_Drawers()->raise_evResetHvacOverlayHideTimer();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s: Some other HVAC overlay is visible, so no action.", __FUNCTION__);
            }
        }
        else
        {
            CDrawersAdaptor::getInstance()->setActiveNotification(eHVACNotificationType);
            CHMIMain::getSM()->getSCI_Drawers()->raise_evShowHvacOverlay();
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s: HVAC overlay cannot be shown", __FUNCTION__);
    }
}

void CDrawersApplication::displayCtrlPanelModeOverlay()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s", __FUNCTION__);

    if((CPowerModeAdaptor::getInstance().getPowerModeStatus() != CPowerModeEnums::VPM_ONE_HOUR) &&
            (CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT))
    {
        CDrawersEnums::ENotificationTypes eActiveOverlay = CDrawersAdaptor::getInstance()->activeNotification();

        if (!CHVACAdaptor::getInstance()->ctrlPanelMode()
                && !CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_drawer_DrawerManager_drawers_main_region_DrawersVisibleState_shortcut_drawer_region_HVACDrawerMaximizedState))
        {
            CDrawersAdaptor::getInstance()->setActiveNotification(CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_CLIMATE_MODE_STATUS);

            if (CDrawersEnums::EN_NOTIFICATION_TYPE_NONE != eActiveOverlay)
            {
                CHMIMain::getSM()->getSCI_Drawers()->raise_evResetHvacOverlayHideTimer();
            }
            else
            {
                CHMIMain::getSM()->getSCI_Drawers()->raise_evShowHvacOverlay();
            }
        }
        else
        {
            if (CDrawersEnums::EN_NOTIFICATION_TYPE_NONE != eActiveOverlay)
            {
                if (CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_CLIMATE_MODE_STATUS == eActiveOverlay)
                {
                    CHMIMain::getSM()->getSCI_Drawers()->raise_evHideHvacOverlay();
                }
                else
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s: Some other overlay is visible, So no action. ", __FUNCTION__);
                }
            }
            else
            {
                // Do nothing.
            }
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HVAC,"%s: CCM is not preset or system is in ONE_HOUR mode, powerModeStatus: %d, ccmState: %d", __FUNCTION__, CPowerModeAdaptor::getInstance().getPowerModeStatus(), CHVACAdaptor::getInstance()->ccmPresence());
    }
}

void CDrawersApplication::sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo)
{
    Q_UNUSED(strAdditionalInfo);
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ePopupId: %d, ePopupResult: %d", __FUNCTION__, ePopupId, ePopupResult);

    switch(ePopupId)
    {
    case CPopupEnum::EPopupID::EN_POPUPID_DISPLAY_OFF_CONFIRMATION:
    {
        if(CPopupEnum::EN_POPUP_RESULT_CLOSED_ON_TIMEOUT == ePopupResult)
        {
            CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(true);
            CHMIMain::getSM()->getSCI_Drawers()->raise_evMinimizeQadDrawer();
        }
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s: In Default case.", __FUNCTION__);
    }
        break;
    }
}

void CDrawersApplication::sltCcmUserInterventionParamChanged(int iHuCcmParam)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: CCM param is: %d", __FUNCTION__, iHuCcmParam);
    CDrawersEnums::ENotificationTypes eHVACNotificationType = getNotificationType(static_cast<CHVACEnums::EHVACParamEnums>(iHuCcmParam));
    if(!CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_PDC_active_pdc_region_UI_PDC))
    {
        if(CDrawersEnums::EN_NOTIFICATION_TYPE_HVAC_CLIMATE_MODE_STATUS == eHVACNotificationType)
        {
            displayCtrlPanelModeOverlay();
        }
        else
        {
            displayHVACNotificationOverlay(eHVACNotificationType);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s Do Not update anything for climate in PDC/RVC State", __FUNCTION__);
    }
}

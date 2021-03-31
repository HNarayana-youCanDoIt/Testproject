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
* This file is having the definition of all functions of CDrawersSM class of
* Drawers.
*/

#include "CDrawersSM.h"
#include "CDrawersAdaptor.h"
#include "LayerManager/CLayerManagerAdaptor.h"
#include "ParkAssist/CParkAssistAdaptor.h"

CDrawersSM::CDrawersSM(CDrawersApplication& drawersApp):
    m_objDrawersApp(drawersApp)
{
    CHMIMain::getSM()->setSCI_Drawers_OCB(this);
}

CDrawersSM::~CDrawersSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enterDrawers()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
    m_objDrawersApp.loadDrawers("qrc:/QML/Drawers/Drawers.qml");

    // Inform RVCApp hmi is up and running
    CParkAssistAdaptor::getInstance()->setHmiNotificationAttribute(true);
}

void CDrawersSM::exitDrawers()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);

    if (CDrawersAdaptor::getInstance())
    {
        CDrawersAdaptor::getInstance()->setDrawersState(DRAWERS_STATE_HIDE_WITHOUT_ANIMATION_STRING);
        CDrawersAdaptor::getInstance()->setNotificationOverlayState("Hide");
        CDrawersAdaptor::getInstance()->setActiveNotification(CDrawersEnums::EN_NOTIFICATION_TYPE_NONE);

        //Request to hide the notification surface
        CLayerManagerAdaptor::getInstance()->hideScene(CLayerManagerEnums::SURFACE_VOL_NOTIFICATION);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s: Drawers Adaptor is NULL", __FUNCTION__);
    }
}

void CDrawersSM::enterDrawersHiddenState(sc_boolean bPlayAnimation)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : bPlayAnimation: %d", __FUNCTION__, bPlayAnimation);

    if (CDrawersAdaptor::getInstance())
    {

        if (bPlayAnimation)
        {
            CDrawersAdaptor::getInstance()->setQadDrawerState(DRAWERS_STATE_MINIMIZED_STRING);
            CDrawersAdaptor::getInstance()->setShortcutDrawerState(DRAWERS_STATE_MINIMIZED_STRING);
            CDrawersAdaptor::getInstance()->setDrawersState(DRAWERS_STATE_HIDE_WITH_ANIMATION_STRING);
        }
        else
        {
            CDrawersAdaptor::getInstance()->setDrawersState(DRAWERS_STATE_HIDE_WITHOUT_ANIMATION_STRING);
            CDrawersAdaptor::getInstance()->setQadDrawerState(DRAWERS_STATE_MINIMIZED_STRING);
            CDrawersAdaptor::getInstance()->setShortcutDrawerState(DRAWERS_STATE_MINIMIZED_STRING);
        }

        emit CDrawersAdaptor::getInstance()->sigHideNotificationOverlay();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s: Drawers Adaptor is NULL", __FUNCTION__);
    }
}

void CDrawersSM::exitDrawersHiddenState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enterDrawersVisibleState(sc_boolean bPlayAnimation)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s : bPlayAnimation: %d",
             __FUNCTION__, bPlayAnimation);

    if (CDrawersAdaptor::getInstance())
    {
        if (bPlayAnimation)
        {
            CDrawersAdaptor::getInstance()->setDrawersState(
                        DRAWERS_STATE_SHOW_WITH_ANIMATION_STRING);
        }
        else
        {
            CDrawersAdaptor::getInstance()->setDrawersState(
                        DRAWERS_STATE_SHOW_WITHOUT_ANIMATION_STRING);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: Drawers Adaptor is NULL",
                 __FUNCTION__);
    }
}

void CDrawersSM::exitDrawersVisibleState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enterStatusBarState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::exitStatusBarState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enterShortcutDrawerMinimizedState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);

    if (CDrawersAdaptor::getInstance())
    {
        CDrawersAdaptor::getInstance()->setSrcDrawerState(
                    DRAWERS_STATE_MINIMIZED_STRING );
        CDrawersAdaptor::getInstance()->setHvacDrawerState(
                    DRAWERS_STATE_MINIMIZED_STRING );
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: Drawers Adaptor is NULL",
                 __FUNCTION__);
    }
}

void CDrawersSM::exitShortcutDrawerMinimizedState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enterHvacDrawerMaximizedState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);

    if (CDrawersAdaptor::getInstance())
    {
        CDrawersAdaptor::getInstance()->setHvacDrawerState(DRAWERS_STATE_MAXIMIZED_STRING);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: Drawers Adaptor is NULL",
                 __FUNCTION__);
    }
}

void CDrawersSM::exitHvacDrawerMaximizedState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enterSourceDrawerMaximizedState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);

    if (CDrawersAdaptor::getInstance())
    {
        CDrawersAdaptor::getInstance()->setSrcDrawerState(
                    DRAWERS_STATE_MAXIMIZED_STRING);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: Drawers Adaptor is NULL",
                 __FUNCTION__);
    }
}

void CDrawersSM::exitSourceDrawerMaximizedState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enterQadDrawerMaximizedState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);

    if (CDrawersAdaptor::getInstance())
    {
        CDrawersAdaptor::getInstance()->setQadDrawerState(
                    DRAWERS_STATE_MAXIMIZED_STRING);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: Drawers Adaptor is NULL",
                 __FUNCTION__);
    }
}


void CDrawersSM::exitQadDrawerMaximizedState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enterQadDrawerMinimizedState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);

    if (CDrawersAdaptor::getInstance())
    {
        CDrawersAdaptor::getInstance()->setQadDrawerState(
                    DRAWERS_STATE_MINIMIZED_STRING );
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: Drawers Adaptor is NULL",
                 __FUNCTION__);
    }
}

void CDrawersSM::exitQadDrawerMinimizedState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::disableQadDrawer()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enableQadDrawer()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::disableShortcutDrawer()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enableShortcutDrawer()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, __FUNCTION__);
}

void CDrawersSM::enableShortcutDrawerButtons(sc_integer iButtonID,
                                             sc_boolean bEnable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: iButtonID: %d, bEnable: %d",
             __FUNCTION__, iButtonID, bEnable);

    switch(iButtonID)
    {
    case CDrawersEnums::SHORTCUT_DRAWER_BUTTON_HOME_ID:
    {
        if (CDrawersAdaptor::getInstance())
        {
            CDrawersAdaptor::getInstance()->setEnableHomeButton(bEnable);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: Drawers Adaptor is NULL",
                     __FUNCTION__);
        }
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: In Default case.",
                 __FUNCTION__);
    }
        break;
    }
}
void CDrawersSM::enterVolOverlayShowState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);

    CDrawersAdaptor::getInstance()->setActiveNotification(CDrawersEnums::EN_NOTIFICATION_TYPE_VOLUME);
    CDrawersAdaptor::getInstance()->setNotificationOverlayState("Show");

    //Request showing the notification surface
    CLayerManagerAdaptor::getInstance()->showScene(CLayerManagerEnums::SURFACE_VOL_NOTIFICATION);
}

void CDrawersSM::exitVolOverlayShowState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);
}

void CDrawersSM::enterVolOverlayHideState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);

    CDrawersAdaptor::getInstance()->setNotificationOverlayState("Hide");
    CDrawersAdaptor::getInstance()->setActiveNotification(CDrawersEnums::EN_NOTIFICATION_TYPE_NONE);

    //Request to hide the notification surface
    CLayerManagerAdaptor::getInstance()->hideScene(CLayerManagerEnums::SURFACE_VOL_NOTIFICATION);
}

void CDrawersSM::exitVolOverlayHideState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);
}

void CDrawersSM::enterHvacOverlayShowState()
{
   LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);

   CDrawersAdaptor::getInstance()->setNotificationOverlayState("Show");

   //Request showing the notification surface
   CLayerManagerAdaptor::getInstance()->showScene(CLayerManagerEnums::SURFACE_VOL_NOTIFICATION);
}

void CDrawersSM::exitHvacOverlayShowState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);
}

void CDrawersSM::enterHvacOverlayHideState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);

    CDrawersAdaptor::getInstance()->setNotificationOverlayState("Hide");
    CDrawersAdaptor::getInstance()->setActiveNotification(CDrawersEnums::EN_NOTIFICATION_TYPE_NONE);

    //Request to hide the notification surface
    CLayerManagerAdaptor::getInstance()->hideScene(CLayerManagerEnums::SURFACE_VOL_NOTIFICATION);
}

void CDrawersSM::exitHvacOverlayHideState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: ", __FUNCTION__);
}

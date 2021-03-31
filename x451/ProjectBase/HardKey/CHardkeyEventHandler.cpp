/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardkeyEventHandler.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CMediaDataEventHandler, Class has the slots for all the Signals sent by CHardkeyEventProvider
*                         which informs Media Adaptor about Media Resource Events
*/

#include "CHardkeyEventHandler.h"
#include "CHMIMain.h"
#include "CHardkeyAdaptor.h"
#include "implementations/CHardkeyResourceImpl.h"
#include "CPopupEnum.h"
#include "ResourceFactory.hpp"
#include "HMIIncludes.h"
#include "CDisplayManagerAdaptor.h"
#include "CMediaAdaptor.h"
#include <CFramework.h>

#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"

CHardkeyEventHandler::CHardkeyEventHandler(QObject *parent)
    :QObject(parent),
      m_HardkeyAdaptor(*CHardkeyAdaptor::getInstance())
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
    connectSignals();
}

CHardkeyEventHandler::~CHardkeyEventHandler()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
}

void CHardkeyEventHandler::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
    CHardkeyResourceImpl* pHardkeyResource = dynamic_cast<CHardkeyResourceImpl*>(ResourceFactory::getHardkeyResource());

    if(pHardkeyResource)
    {
        CHardkeyEventProvider* pHardkeyEventProvider = pHardkeyResource->getHardkeyDataEventProvider();
        connect(pHardkeyEventProvider,SIGNAL(sigHardKeyEvent(EHardKeys,EHardKeyState)),this,SLOT(sltHardKeyEvent(EHardKeys,EHardKeyState)));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HARDKEYS, "%s | Hardkey Resource is returned NULL from Resource Factory",__FUNCTION__);
    }
}

bool CHardkeyEventHandler::isRotary(EHardKeys eKeyCode)
{
    return ((eKeyCode == KEYCODEHK_MENUROTARY ) ||
            (eKeyCode == KEYCODEHK_MENUROTARY_KNOB ));
}

void CHardkeyEventHandler::sltHardKeyEvent(EHardKeys eKey, EHardKeyState eState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
    CHMIMain::getSM()->getSCI_HardKey()->set_iKeyCode(eKey);
    CHMIMain::getSM()->getSCI_HardKey()->set_iKeyState(eState);

    bool bIsHardKeyHandled = false;

    /* If display is off and any HK event is reveived, Display must be woken up */
    CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);

    // Need to send the hardkey event to Fwk to restart the screen timer
    CFramework::getFramework().restartScreenTimer();
    CFramework::getFramework().monitorUserInteraction();

    /** hardkey event shall be passed to doodle module **/
    CDoodleApplication::getDoodleAdaptor()->handleHardKeys(static_cast<CHardKeyEnum::EHardKeys>(eKey), static_cast<CHardKeyEnum::EHardKeyState>(eState));

    /** hardkey event shall be passed to overlay, if any overlay is displayed then the action shall be taken. **/
     bIsHardKeyHandled = CHardkeyAdaptor::getInstance()->passHardkeyToOverlay(static_cast<CHardKeyEnum::EHardKeys>(eKey), static_cast<CHardKeyEnum::EHardKeyState>(eState));

    /*
     * hardkey events shall be passed to screens only if it is not handled by popup and drawers since
     * popup and drawers are displayed above screens.
     * */
    if(CPopupManager::getInstance()->isPopupAlive())
    {
        bIsHardKeyHandled = CPopupManager::getInstance()->handleHardKeys(static_cast<CHardKeyEnum::EHardKeys>(eKey), static_cast<CHardKeyEnum::EHardKeyState>(eState));
    }

    if(!bIsHardKeyHandled)
    {
        bIsHardKeyHandled = CDrawersAdaptor::getInstance()->handleHardKeys(static_cast<CHardKeyEnum::EHardKeys>(eKey), static_cast<CHardKeyEnum::EHardKeyState>(eState));
    }

    if(!bIsHardKeyHandled)
    {
        if(isRotary(eKey))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s - Rotary event received.", __FUNCTION__);
            CHardkeyAdaptor::getInstance()->passRREToScreens(static_cast<CHardKeyEnum::EHardKeys>(eKey), static_cast<CHardKeyEnum::EHardKeyState>(eState));
        }
        else
        {
            if(CHardkeyAdaptor::getInstance()->IsSWUpdateActive() && eKey == KEYCODEHK_SOFTWARE_UPDATE)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "KeyCode : %d , software update in progress",eKey);
            }
            else
            {
                if((EHardKeys::KEYCODEHK_VOLROTARY_KNOB != eKey) && (EHardKeys::KEYCODEHK_MENUROTARY_KNOB != eKey)
                        && (EHardKeys::KEYCODEHK_VOLROTARY != eKey) && (EHardKeys::KEYCODEHK_MENUROTARY != eKey)
                        && (EHardKeys::KEYCODESWC_REJECT_MUTE != eKey))
                {
                    CMediaAdaptor::getInstance().cancelFastForward();
                }

                CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_USB_CONNECTED);                
                CHMIMain::getSM()->getSCI_HardKey()->raise_evHardKeyStateUpdate();
            }
        }
    }
}


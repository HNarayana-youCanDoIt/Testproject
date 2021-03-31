/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardkeyResourceImpl.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CHardkeyResourceImpl, Resource Implementation for HardKeyHandler.
*/

#include "CHardkeyResourceImpl.h"
#include <ResourceMaster.h>
#include "logging.h"
#include "ResourceDeploymentConfig.h"
#include "implementations/CHardkeyEnums.h"


CHardkeyResourceImpl::CHardkeyResourceImpl():
    KEY_PRESS("press"),
    KEY_LONGPRESS("longpress"),
    KEY_RELEASE("release"),
    KEY_ROTATE_RIGHT("right"),
    KEY_ROTATE_LEFT("left"),
    KEY_STUCK("stuck"),
    m_pHardkeyEventProvider(new CHardkeyEventProvider()),
    m_objHardKeyProxy(ResourceDeploymentConfig::getConfig().m_Hardkey_Proxy.domain,ResourceDeploymentConfig::getConfig().m_Hardkey_Proxy.instance),
    m_objHardKeyPluginProxy(ResourceDeploymentConfig::getConfig().m_HardkeyPlugin_Proxy.domain,ResourceDeploymentConfig::getConfig().m_HardkeyPlugin_Proxy.instance)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
    subscribe();
    m_listLongPressedKeys.clear();
}

void CHardkeyResourceImpl::keyPressServiceStatusCb(AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);

    if(CommonAPI::AvailabilityStatus::AVAILABLE == eStatus)
    {
        //m_bHKAvailable = true;
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"available");

        SUBSCRIBE(m_objHardKeyProxy,getKeyEventSelectiveEvent(),&CHardkeyResourceImpl::keyCtrlEventCb,_1)

        CommonAPI::CallStatus status;

        std::vector<keyprestypes::tKeyStates> keys;

        //key SWC ModeChange
        keyprestypes::tKeyStates key;
        std::vector<std::string> keystates;
        keystates.clear();
        keystates.push_back(KEY_PRESS);
        keystates.push_back(KEY_LONGPRESS);
        keystates.push_back(KEY_RELEASE);
        keystates.push_back(KEY_STUCK);

        /* Subscribing for keycodes for x451 high
        -------------------------------------------------*/

        for(int eKeyIndex= KEYCODEHK_VOLROTARY; eKeyIndex <= KEYCODEHK_ENGGMENU; eKeyIndex++)
        {
            key.setId(eKeyIndex);
            if((KEYCODEHK_MENUROTARY_KNOB == eKeyIndex) ||
                    (KEYCODEHK_VOLROTARY_KNOB == eKeyIndex))
            {
                std::vector<std::string> keystatesRotary;
                keystatesRotary.clear();
                keystatesRotary.push_back(KEY_PRESS);
                keystatesRotary.push_back(KEY_LONGPRESS);
                keystatesRotary.push_back(KEY_RELEASE);
                keystatesRotary.push_back(KEY_ROTATE_RIGHT);
                keystatesRotary.push_back(KEY_ROTATE_LEFT);
                key.setKeyStates(keystatesRotary);
                keys.push_back(key);
            }
            else
            {
                key.setKeyStates(keystates);
                keys.push_back(key);

            }
        }

        /* Subscribing for keycodes for x0 high
        -------------------------------------------------*/

        for(int eKeyIndex= KEYCODETOUCH_POWER; eKeyIndex <= KEYCODETOUCH_ENGGMENU; eKeyIndex++)
        {
            key.setId(eKeyIndex);
            key.setKeyStates(keystates);
            keys.push_back(key);
        }

        /* Subscribing SWC keycodes
        -------------------------------------------------*/

        for(int eKeyIndex= KEYCODESWC_PREV; eKeyIndex <= KEYCODESWC_ACCEPT_VR; eKeyIndex++)
        {
            key.setId(eKeyIndex);
            key.setKeyStates(keystates);
            keys.push_back(key);
        }

        m_objHardKeyProxy->subscribeKeys(std::move(keys), status);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HARDKEYS,"keyPress service not available");
    }
}

void CHardkeyResourceImpl::subscribe()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
    SUBSCRIBE(m_objHardKeyProxy,getProxyStatusEvent(),&CHardkeyResourceImpl::keyPressServiceStatusCb,_1)
}

void CHardkeyResourceImpl::keyCtrlEventCb(const std::shared_ptr<keyprestypes::tKey> &key)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);

    EHardKeyState eKeyState = HKEY_STATE_INVALID;

    string strKeyState = key->getKeyState();
    int iKeyCode = key->getId();

    if(0 == strKeyState.compare(KEY_RELEASE))
    {
        auto result = std::find(m_listLongPressedKeys.begin(), m_listLongPressedKeys.end(), iKeyCode);
        if(result != m_listLongPressedKeys.end())
        {
            eKeyState = HKEY_STATE_LONGRELEASED;
            /* Removing the ikeyCode from logpressed list so that the long press state that particular
             * key is updated propoerly.
              */
            m_listLongPressedKeys.remove(iKeyCode);
        }
         else
        {
            eKeyState = HKEY_STATE_RELEASED;
        }
    }
    else if(0 == strKeyState.compare(KEY_LONGPRESS))
    {
        eKeyState = HKEY_STATE_LONGPRESSED;
        /**
          *@todo need to clear the list in case of special keys like engg menu and sw update.
          */
        m_listLongPressedKeys.push_front(iKeyCode);
    }
    // FixMe: Need to remove this condition, When the issue from service side resolved.
    else if(0 == strKeyState.compare(KEY_PRESS) && KEYCODEHK_SOFTWARE_UPDATE == iKeyCode)
    {
        eKeyState = HKEY_STATE_PRESSED;
         /*
          * Clearing the m_listLongPressedKeys here, becuase from service side
          * we are not getting release of software update key.
          */
        m_listLongPressedKeys.clear();
    }
    else if(0 == strKeyState.compare(KEY_PRESS))
    {
       eKeyState = HKEY_STATE_PRESSED;
    }
    else if(0 == strKeyState.compare(KEY_ROTATE_RIGHT))
    {
       eKeyState = HKEY_STATE_ROTATE_RIGHT;
    }
    else if(0 == strKeyState.compare(KEY_ROTATE_LEFT))
    {
        eKeyState = HKEY_STATE_ROTATE_LEFT;
    }
    else if(0 == strKeyState.compare(KEY_STUCK))
    {
        eKeyState = HKEY_STATE_STUCK;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"wrong key state received");
    }

    if (m_pHardkeyEventProvider)
    {
        m_pHardkeyEventProvider->onKeyEvent(static_cast<EHardKeys>(iKeyCode), eKeyState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HARDKEYS,"m_pHardkeyDataEventProvider null");
    }
}

CHardkeyResourceImpl::~CHardkeyResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
    if (m_pHardkeyEventProvider)
    {
        delete m_pHardkeyEventProvider;
        m_pHardkeyEventProvider = NULL;
    }
}

CHardkeyEventProvider* CHardkeyResourceImpl::getHardkeyDataEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
    return m_pHardkeyEventProvider;
}

void CHardkeyResourceImpl::sendKeyCodeToKeyPresPluginProxy(const KeyPresPlugin::eKeyCodeId _keyCode, const KeyPresPlugin::eKeyState _keystate, CallStatus _internalCallStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s, _keyCode:%d, _keystate:%d, _internalCallStatus:%d", __FUNCTION__, static_cast<int>(_keyCode), static_cast<int>(_keystate), static_cast<int>(_internalCallStatus));
    m_objHardKeyPluginProxy->sendKeyCode(_keyCode, _keystate, _internalCallStatus);
}

void CHardkeyResourceImpl::sendSliderStateAsyncToKeyPresPluginProxy(const KeyPresPlugin::eKeyCodeId _keyCode, const KeyPresPlugin::eKeyState _keystate, const int _steps)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s, _keyCode:%d, _keystate:%d, _steps:%d", __FUNCTION__, static_cast<int>(_keyCode), static_cast<int>(_keystate), _steps);
    m_objHardKeyPluginProxy->sendSliderStateAsync(_keyCode, _keystate, _steps, std::bind(&CHardkeyResourceImpl::sendSliderStateAsyncCb,this, _1,_2));
}

void CHardkeyResourceImpl::sendSliderStateAsyncCb(const CommonAPI::CallStatus& eCallStatus, const KeyPresPlugin::eCallResult& eCallResult)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s CallStatus: %d CallResult:%d",__FUNCTION__, static_cast<int>(eCallStatus), static_cast<int>(eCallResult));
}

/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardkeyAdaptor.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CHardkeyAdaptor Adaptor class for Hardkey - It is a singleton class used to communicate with qml and SM on HardKey events.
*/

#include "CHardkeyAdaptor.h"
#include "logging.h"
#include "ResourceFactory.hpp"
#include "CHMIMain.h"
#include "CHardkeySM.h"
#include "CHardKeyEnum.h"

#include "implementations/CHardkeyResourceImpl.h"

CHardkeyAdaptor* CHardkeyAdaptor::m_pHardkeyAdaptor = nullptr;

CHardkeyAdaptor::CHardkeyAdaptor(QObject* parent) : QObject(parent),
    m_eCurrentHardkey(CHardKeyEnum::KEYCODEHK_INVALID),
    m_bIsSWUpdateActive(false),
    m_bHardKeyHandledByOverlay(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
    CHardKeyEnum::registerHardKeyEnumToQML();
    CFramework::getFramework().setContextProperty("cppHardkeyAdaptor", this);

}

CHardkeyAdaptor::~CHardkeyAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,__FUNCTION__);
    if(m_pHardkeyAdaptor)
        delete m_pHardkeyAdaptor;
}

CHardkeyAdaptor* CHardkeyAdaptor::getInstance()
{
    if(nullptr == m_pHardkeyAdaptor)
    {
        m_pHardkeyAdaptor = new CHardkeyAdaptor();
    }
    return m_pHardkeyAdaptor;
}

void CHardkeyAdaptor::processHardKey(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s, eKey:%d, eKeyState:%d", __FUNCTION__, eKey, eKeyState);
    //    switch(eKey)
    //    {
    //    case KEYCODETOUCH_HOME:
    //        CHMIMain::getSM()->raise_evHomeActivated();
    //        break;

    //    default:
    //        break;
    //    }
}

bool CHardkeyAdaptor::passHardkeyToOverlay(CHardKeyEnum::EHardKeys eKeyCode, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s: ", __FUNCTION__);
    m_bHardKeyHandledByOverlay = false;

    emit sigPassHardkeyToOverlay(static_cast<int>(eKeyCode), static_cast<int>(eKeyState));

    return m_bHardKeyHandledByOverlay;
}

bool CHardkeyAdaptor::passRREToScreens(CHardKeyEnum::EHardKeys eKeyCode, CHardKeyEnum::EHardKeyState eKeyState)
{
    if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) || (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState) ||
       (CHardKeyEnum::HKEY_STATE_PRESSED == eKeyState)  || (CHardKeyEnum::HKEY_STATE_LONGRELEASED == eKeyState) ||
       (CHardKeyEnum::HKEY_STATE_STUCK == eKeyState))
    {
        emit sigRotaryPressed(static_cast<int>(eKeyCode), static_cast<int>(eKeyState));
    }
    else
    {
        emit sigRotaryUpdate(static_cast<int>(eKeyCode), static_cast<int>(eKeyState));
    }
    return true;
}

int CHardkeyAdaptor::getKeyCodeForPlugin(CHardKeyEnum::EHardKeys _eKeyCode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s, _keyCode:%d", __FUNCTION__, static_cast<int>(_eKeyCode));
    int _iKeyCodeId = -1;
    switch (_eKeyCode)
    {
    case CHardKeyEnum::KEYCODETOUCH_POWER:
    {
        _iKeyCodeId = KeyPresPlugin::eKeyCodeId::KEYCODEHMI_MEDIAOFF;
    }
        break;
    case CHardKeyEnum::KEYCODETOUCH_VOLUME_UP:
    {
        _iKeyCodeId = KeyPresPlugin::eKeyCodeId::KEYCODEHMI_VOLUMEUP;
    }
        break;
    case CHardKeyEnum::KEYCODETOUCH_VOLUME_DOWN:
    {
        _iKeyCodeId = KeyPresPlugin::eKeyCodeId::KEYCODEHMI_VOLUMEDOWN;
    }
        break;
    case CHardKeyEnum::KEYCODETOUCH_MUTE:
    {
        _iKeyCodeId = KeyPresPlugin::eKeyCodeId::KEYCODEHMI_MUTE;
    }
        break;
    case CHardKeyEnum::KEYCODEHK_VOLROTARY_KNOB:
    {
        _iKeyCodeId = KeyPresPlugin::eKeyCodeId::KEYCODEHMI_VOLUME_SLIDER;
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s, INVALID value", __FUNCTION__);
    }
        break;
    }
    return _iKeyCodeId;
}

int CHardkeyAdaptor::getKeyStateForPlugin(CHardKeyEnum::EHardKeyState _eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s, _keyState:%d", __FUNCTION__, static_cast<int>(_eKeyState));
    int _iKeyStatePlugin = -1;
    switch (_eKeyState)
    {
    case CHardKeyEnum::HKEY_STATE_PRESSED:
    {
        _iKeyStatePlugin = KeyPresPlugin::eKeyState::KEYSTATEHMI_PRESS;
    }
        break;
    case CHardKeyEnum::HKEY_STATE_LONGPRESSED:
    {
        _iKeyStatePlugin = KeyPresPlugin::eKeyState::KEYSTATEHMI_LONGPRESS;
    }
        break;
    case CHardKeyEnum::HKEY_STATE_RELEASED:
    {
        _iKeyStatePlugin = KeyPresPlugin::eKeyState::KEYSTATEHMI_RELEASE;
    }
        break;
    case CHardKeyEnum::HKEY_STATE_LONGRELEASED:
    {
        _iKeyStatePlugin = KeyPresPlugin::eKeyState::KEYSTATEHMI_RELEASE;
    }
        break;
    case CHardKeyEnum::HKEY_STATE_ROTATE_LEFT:
    {
        _iKeyStatePlugin = KeyPresPlugin::eKeyState::KEYSTATEHMI_LEFT;
    }
        break;
    case CHardKeyEnum::HKEY_STATE_ROTATE_RIGHT:
    {
        _iKeyStatePlugin = KeyPresPlugin::eKeyState::KEYSTATEHMI_RIGHT;
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s, INVALID value", __FUNCTION__);
    }
        break;
    }
    return _iKeyStatePlugin;
}
void CHardkeyAdaptor::invSendKeyCodeEvent(CHardKeyEnum::EHardKeys _eKeyCode, CHardKeyEnum::EHardKeyState _eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s, _keyCode:%d, _keyState:%d", __FUNCTION__, static_cast<int>(_eKeyCode), static_cast<int>(_eKeyState));

    KeyPresPlugin::eKeyState::Literal _eKeyStatePlugin = static_cast<KeyPresPlugin::eKeyState::Literal>(getKeyStateForPlugin(_eKeyState));
    KeyPresPlugin::eKeyCodeId::Literal _eKeyCodeId = static_cast<KeyPresPlugin::eKeyCodeId::Literal>(getKeyCodeForPlugin(_eKeyCode));

    if ((_eKeyStatePlugin >= 0) && (_eKeyCodeId >= 0))
    {
        CHardkeyResourceImpl* pHardkeyResource = dynamic_cast<CHardkeyResourceImpl*>(ResourceFactory::getHardkeyResource());
        if (pHardkeyResource)
        {
            pHardkeyResource->sendKeyCodeToKeyPresPluginProxy(_eKeyCodeId, _eKeyStatePlugin, CommonAPI::CallStatus::SUCCESS);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s, pHardkeyResource not found", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s, Unhandled key State", __FUNCTION__);
    }
}

void CHardkeyAdaptor::invSendSliderStateEvent(CHardKeyEnum::EHardKeys _eKeyCode, CHardKeyEnum::EHardKeyState _eKeyState, int _iSteps)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s, _keyCode:%d, _keyState:%d _uiSteps:%d", __FUNCTION__, static_cast<int>(_eKeyCode), static_cast<int>(_eKeyState), _iSteps);

    KeyPresPlugin::eKeyState::Literal _eKeyStatePlugin = static_cast<KeyPresPlugin::eKeyState::Literal>(getKeyStateForPlugin(_eKeyState));
    KeyPresPlugin::eKeyCodeId::Literal _eKeyCodeId = static_cast<KeyPresPlugin::eKeyCodeId::Literal>(getKeyCodeForPlugin(_eKeyCode));

    if ((_eKeyStatePlugin >= 0) && (_eKeyCodeId >= 0))
    {
        CHardkeyResourceImpl* pHardkeyResource = dynamic_cast<CHardkeyResourceImpl*>(ResourceFactory::getHardkeyResource());
        if (pHardkeyResource)
        {
            pHardkeyResource->sendSliderStateAsyncToKeyPresPluginProxy(_eKeyCodeId, _eKeyStatePlugin, _iSteps);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s, pHardkeyResource not found", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_DRAWERS, "%s, Unhandled key State", __FUNCTION__);
    }
}


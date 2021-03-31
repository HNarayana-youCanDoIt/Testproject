/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CAppleCarPlayAdaptor.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition of all functions of Adaptor class of
* AppleCarPlay, This is used by QML files to get the information needs to show
* on view.
*/

#include "CAppleCarPlayAdaptor.h"
#include "ResourceFactory.hpp"
#include "CPopupManager.h"
#include "CHomeAdaptor.h"
#include "CAudioAdaptor.h"
#include "CDrawersAdaptor.h"
#include "ProjectionResource/AppleCarPlayResource/implementations/CAppleCarPlayResourceImpl.h"
#include "CLayerManagerAdaptor.h"
#include "CDisplayManagerAdaptor.h"
#include "CDiagnosticAdaptor.h"
#include "CDiagnosticEnum.h"
#include "CParkAssistAdaptor.h"
#include "CPhoneAdaptor.h"

CAppleCarPlayAdaptor	*CAppleCarPlayAdaptor::m_pAppleCarPlayAdaptor	= nullptr;

CAppleCarPlayAdaptor::CAppleCarPlayAdaptor(QObject *pParent) : QObject(pParent),
    m_pAppleCarPlayResource(dynamic_cast<CAppleCarPlayResourceImpl*>(ResourceFactory::getAppleCarPlayResource())),
    m_bAppleCarPlayConnectionStatus(false),
    m_bAppleCarPlayProjectionStatus(false),
    m_bAppleCarPlayPhoneStatus(false),
    m_strAppleCarPlayDeviceName(""),
    m_bIsCPSwitchable(false),
    m_bAppleCarPlayRemoteUIStatus(false),
    m_bSmartFanState(false),
    m_bCarPlaySiriStatus(false),
    DEVICE_NAME_LENGTH_LIMIT(27)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    m_bSmartFanState = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_CP_SMART_FAN_STATE);

    CFramework::getFramework().setContextProperty("cppAppleCarPlayAdaptor",this);
    CAppleCarPlayEnums::registerAppleCarPlayEnumsToQML();
    connectSignals();
}

bool CAppleCarPlayAdaptor::handleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    bool bReturn = false;

    if (m_bAppleCarPlayConnectionStatus)
    {
        /**
          @todo- Add logic for KEYCODETOUCH_POWER & KEYCODETOUCH_MUTE if required as per CarPlay requirements
          */
        switch(eKey)
        {
        case CHardKeyEnum::KEYCODETOUCH_SOFTWARE_UPDATE:
        case CHardKeyEnum::KEYCODETOUCH_FAVOURITE:
        case CHardKeyEnum::KEYCODETOUCH_ENGGMENU:
        case CHardKeyEnum::KEYCODETOUCH_HOME:
        case CHardKeyEnum::KEYCODEHK_SOFTWARE_UPDATE:
        case CHardKeyEnum::KEYCODEHK_FAVORITE:
        case CHardKeyEnum::KEYCODEHK_ENGGMENU:
        case CHardKeyEnum::KEYCODEHK_HOME:
        {
            requestNative();
            bReturn = true;
        }
            break;
        case CHardKeyEnum::KEYCODEHK_PHONE:
        {
            /*
             * If CarPlay is connected and if phone status is true means carplay
             * call is going on, then HMI has to report key to cp pres plugin,
             * else HMI has to cal=l request projection of cp pres with appURL
             * "mobilePhone:" to launch carplay phone app.
             */
            if(m_bAppleCarPlayConnectionStatus)
            {
                if (getAppleCarPlayPhoneStatus())
                {
                    reportKeyEventToResource( eKey, eKeyState );
                    bReturn = true;
                }
                else if ((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState)
                         || (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState))
                {
                    requestCarPlayProjection(CP_URL_MOBILEPHONE);
                    bReturn = true;
                }
                else
                {
                    //Do nothing.
                }
            }
        }
            break;
        case CHardKeyEnum::KEYCODEHK_SEEKDOWN:
        case CHardKeyEnum::KEYCODEHK_SEEKUP:
        {
            reportKeyEventToResource( eKey, eKeyState );
            bReturn = true;
        }
            break;
        case CHardKeyEnum::KEYCODEHK_BACK:
        {
            /*
             * If CPProjection is active
             * HMI has to report key events to CarPlay Pres.
             */
            if ( m_bAppleCarPlayProjectionStatus )
            {
                reportKeyEventToResource( eKey, eKeyState );
                bReturn = true;
            }
            else
            {
                // Do nothing.
            }
        }
            break;
        case CHardKeyEnum::KEYCODESWC_ACCEPT_VR:
        {
            if((CDiagnosticAdaptor::getInstance()) && (CDiagnosticAdaptor::getInstance()->micConnectionStatus() != CDiagnosticEnum::CONNECTED))
            {
                //Mic is not connected
                CAudioAdaptor::getInstance()->playBeep(CAudioEnums::BEEP_TYPE_CONFIRM);
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_MIC_NOT_AVAILABLE_POPUP);
            }
            else
            {
                //Mic is connected
            }
            reportKeyEventToResource( eKey, eKeyState );

            if( (!m_bCarPlaySiriStatus) && (CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState) )
            {
                /* To forward this event to start the Native VR, as per Native VR + Carplay Siri use case */
                bReturn = false;
            }
            else
            {
                bReturn = true;
            }
        }
            break;
        case CHardKeyEnum::KEYCODESWC_DOWN:
        case CHardKeyEnum::KEYCODESWC_NEXT:
        case CHardKeyEnum::KEYCODESWC_PREV:
        case CHardKeyEnum::KEYCODESWC_UP:
        {
            reportKeyEventToResource( eKey, eKeyState );
            bReturn = true;
        }
            break;
        case CHardKeyEnum::KEYCODESWC_REJECT_MUTE:
        {
            if(m_bAppleCarPlayPhoneStatus)
            {
                reportKeyEventToResource( eKey, eKeyState );
                bReturn = true;
            }
            else
            {
                //do nothing.
            }
        }
            break;
        default:
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s Invalid data received key: %d state: %d ", __FUNCTION__, eKey, eKeyState);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: "
                                                "m_bCarPlayConnectionStatus:"
                                                " %d ", __FUNCTION__,
                 m_bAppleCarPlayConnectionStatus);
    }

    return bReturn;
}

void CAppleCarPlayAdaptor::updateCPNowPlayingInfo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if ( m_pAppleCarPlayResource )
    {
        const CarPlayNowPlayingInfo& objsNowPlayingInfo = m_pAppleCarPlayResource->getNowPlayingData();
        setCPMediaSongTitle(objsNowPlayingInfo.mStrTitle.c_str());
        setCPMediaSongArtist(objsNowPlayingInfo.mStrArtist.c_str());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "AppleCarPlayResource is NULL.");
    }
}

void CAppleCarPlayAdaptor::updateSmartFanState(bool bValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Smart fan state: %d", __FUNCTION__, bValue);
    if(bValue != m_bSmartFanState)
    {
        m_bSmartFanState = bValue;
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_CP_SMART_FAN_STATE, m_bSmartFanState);
        emit sigSmartFanStateChanged(m_bSmartFanState);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s Values are same", __FUNCTION__);
    }
}

void CAppleCarPlayAdaptor::setSmartFanState()
{
    int iSmartFanStateFromPersistence = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_CP_SMART_FAN_STATE);

    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Smart fan state in persistence is %d, requesting opposite state.", __FUNCTION__, iSmartFanStateFromPersistence);

    if (nullptr != m_pAppleCarPlayResource)
    {
        m_pAppleCarPlayResource->setSmartFanState(!iSmartFanStateFromPersistence);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlayResource is NULL", __FUNCTION__);
    }
}

void CAppleCarPlayAdaptor::updateCPProxyStatus(bool bCPProxyStatus)
{
    if(true == bCPProxyStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: CarPlay proxy status: %d, smart fan state from persistence: %d",
                 __FUNCTION__, bCPProxyStatus, m_bSmartFanState);

        if (nullptr != m_pAppleCarPlayResource)
        {
            m_pAppleCarPlayResource->setSmartFanState(m_bSmartFanState);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlayResource is NULL", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlay proxy is not available : %d", __FUNCTION__, bCPProxyStatus);
    }
}

void CAppleCarPlayAdaptor::requestCarPlayProjection(const string &appURL)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: with appURL:%s", __FUNCTION__, appURL.c_str());

    if (NULL != m_pAppleCarPlayResource)
    {
        m_pAppleCarPlayResource->requestProjection(appURL);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlayResource is NULL", __FUNCTION__);
    }
}

void CAppleCarPlayAdaptor::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveAudioSourceListUpdated()),
            this, SLOT(slotActiveAudioSourceListUpdated()), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveEntSrcChanged()),
            this, SLOT(slotActiveEntSourceChanged()), Qt::QueuedConnection);
    connect(&CFramework::getFramework(),SIGNAL(sigBroadcastUserInteractionDetected()),
            this, SLOT(slotBroadcastUserInteractionDetected()), Qt::QueuedConnection);

}

void CAppleCarPlayAdaptor::disconnectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    disconnect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveAudioSourceListUpdated()),
               this, SLOT(slotActiveAudioSourceListUpdated()));
    disconnect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveEntSrcChanged()),
               this, SLOT(slotActiveEntSourceChanged()));
}

void CAppleCarPlayAdaptor::reportKeyEventToResource(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: eKey: %d, eKeyState: %d",
             __FUNCTION__, eKey, eKeyState);

    if (m_pAppleCarPlayResource)
    {
        m_pAppleCarPlayResource->reportKeyEvent(eKey, eKeyState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: "
                                                   "CarPlayResource"
                                                   " is NULL",
                    __FUNCTION__);
    }
}

void CAppleCarPlayAdaptor::resetData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    setAppleCarPlayProjectionStatus(false);
    setAppleCarPlayPhoneStatus(false);
    setCPMediaSongArtist("");
    setCPMediaSongTitle("");
    setIsCPSwitchable(false);
    setAppleCarPlayRemoteUIStatus(false);
}

void CAppleCarPlayAdaptor::requestNative()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (NULL != m_pAppleCarPlayResource)
    {
        m_pAppleCarPlayResource->requestNative();
        // Calling layer manager adaptor to show/set the HMI surface as top surface
        CLayerManagerAdaptor::getInstance()->showScene(CLayerManagerEnums::SURFACE_HMI);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlayResource is NULL", __FUNCTION__);
    }
}

void CAppleCarPlayAdaptor::showCPMusicScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    /*
     * if m_bIsCPSwitchable is true or Any Audio Screen is active, like FM, AM, Media
     * screen and CP Media gets activated. HMI should switch to CP Media screen.
     */
    if (m_pAppleCarPlayResource && (m_bIsCPSwitchable ||
                                    CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio)))
    {
        if (!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus())
        {
            m_pAppleCarPlayResource->requestProjection(CP_URL_NOWPLAYING);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: Rverse Gear is active so no action.", __FUNCTION__);
        }
        setIsCPSwitchable(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: CarPlayResource"
                                                   " is NULL", __FUNCTION__);
    }
}

void CAppleCarPlayAdaptor::setIsCPSwitchable(bool bIsCPSwitchable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s: bIsCPSwitchable: %d",
             __FUNCTION__, bIsCPSwitchable);

    if (m_bIsCPSwitchable != bIsCPSwitchable &&
            m_bAppleCarPlayConnectionStatus)
    {
        m_bIsCPSwitchable = bIsCPSwitchable;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: Values are same.",
                    __FUNCTION__);
    }
}

void CAppleCarPlayAdaptor::slotActiveAudioSourceListUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
}

void CAppleCarPlayAdaptor::slotActiveEntSourceChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if ( m_bAppleCarPlayConnectionStatus &&
         (CAudioEnums::SRC_CARPLAY_MEDIA ==
          CAudioAdaptor::getInstance()->activeEntSrc()) )
    {
        showCPMusicScreen();
    }
    else if ( m_bIsCPSwitchable && m_bAppleCarPlayProjectionStatus )
    {
        requestNative();
        setIsCPSwitchable(false);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: Active Source is not "
                                                   "SRC_CARPLAY_MEDIA", __FUNCTION__);
        setIsCPSwitchable(false);
    }
}

void CAppleCarPlayAdaptor::slotBroadcastUserInteractionDetected()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
    if (NULL != m_pAppleCarPlayResource)
    {
        m_pAppleCarPlayResource->requestNative();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION, "%s: AppleCarPlayResource is NULL", __FUNCTION__);
    }
}

CAppleCarPlayAdaptor::~CAppleCarPlayAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);
}

CAppleCarPlayAdaptor *CAppleCarPlayAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if (!m_pAppleCarPlayAdaptor)
    {
        m_pAppleCarPlayAdaptor = new CAppleCarPlayAdaptor();
    }
    else
    {
        // Do nothing.
    }

    return m_pAppleCarPlayAdaptor;
}

void CAppleCarPlayAdaptor::setAppleCarPlayConnectionStatus(const bool bAppleCarPlayConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : bAppleCarPlayConnectionStatus: %d", __FUNCTION__, bAppleCarPlayConnectionStatus);

    if (m_bAppleCarPlayConnectionStatus != bAppleCarPlayConnectionStatus)
    {
        m_bAppleCarPlayConnectionStatus = bAppleCarPlayConnectionStatus;
        emit sigAppleCarPlayConnectionStatusChanged(m_bAppleCarPlayConnectionStatus);

        /*
         * If Display is Off, Do display ON
         */
        CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);

        if (m_bAppleCarPlayConnectionStatus)
        {
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_CONNECT_YOUR_PHONE);

            CFramework::getFramework().setBEnableUserInteractionDetection(false);

            if(CPhoneAdaptor::getInstance()->doesCallExist())
            {
                /** @note: This implementation makes sure when iPhone is connected for CarPlay
                 *         then QAD is closed and then is disabled in it's minimzed state.
                 */
                CDrawersAdaptor::getInstance()->closeDrawers();
            }
            else
            {
                //Do Nothing
            }

            if(!m_bAppleCarPlayRemoteUIStatus
                    && DRAWERS_STATE_MAXIMIZED_STRING != CDrawersAdaptor::getInstance()->qadDrawerState()
                    && !CHomeAdaptor::getInstance().isShortcutOnDisplayScreen(CHomeEnum::SHORTCUT_APPLE_CAR_PLAY_ID))
            {
                CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_CONNECTION);
            }
            else
            {
                //do nothing.
            }
        }
        else if (!m_bAppleCarPlayConnectionStatus)
        {
            CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_CONNECTION);
            resetData();
            CFramework::getFramework().setBEnableUserInteractionDetection(true);
        }
        else
        {
            resetData();
        }
    }
    else
    {
        // Do nothing.
    }
}

void CAppleCarPlayAdaptor::launchAppleCarPlay(const string &appURL)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION, "%s", __FUNCTION__);

    if ( !m_bAppleCarPlayConnectionStatus )
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_CONNECT_YOUR_PHONE);
    }
    else if ( !m_bAppleCarPlayProjectionStatus )
    {
        requestCarPlayProjection(appURL);
    }
}

void CAppleCarPlayAdaptor::setAppleCarPlayProjectionStatus(const bool bAppleCarPlayProjectionStatus)
{

    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : bAppleCarPlayProjectionStatus: %d", __FUNCTION__, bAppleCarPlayProjectionStatus);

    if (m_bAppleCarPlayProjectionStatus != bAppleCarPlayProjectionStatus)
    {
        m_bAppleCarPlayProjectionStatus = bAppleCarPlayProjectionStatus;

        emit sigAppleCarPlayProjectionStatusChanged(m_bAppleCarPlayProjectionStatus);
        CHMIMain::getSM()->getSCI_CarPlay()->set_bAppleCarPlayProjStatus(m_bAppleCarPlayProjectionStatus);

        if (m_bAppleCarPlayProjectionStatus)
        {
            /*
+             * If Display is Off, Do display ON
+             */
            CDisplayManagerAdaptor::getInstance()->reqDisplayOnOffFeature(false);

            CPopupManager::getInstance()->closePopup(CPopupEnum::EN_POPUPID_APPLE_CARPLAY_CONNECTION);
            /*
             * raise evCarPlayProjectionStatusChanged to switch to projection state from native
             */
            CHMIMain::getSM()->raise_evCarPlayProjectionStatusChanged();
        }
        else
        {
            if(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_CarPlay))
            {
                /*
                 * raise evCarPlayProjectionStatusChanged to perform exit from projection state to native
                 */
                CHMIMain::getSM()->raise_evCarPlayProjectionStatusChanged();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : CarPlay Projection is not active state ", __FUNCTION__);
            }
        }
    }
    else
    {
        // Do nothing.
    }
}

void CAppleCarPlayAdaptor::setAppleCarPlayPhoneStatus(const bool bAppleCarPlayPhoneStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : bAppleCarPlayPhoneStatus: %d", __FUNCTION__, bAppleCarPlayPhoneStatus);

    if (m_bAppleCarPlayPhoneStatus != bAppleCarPlayPhoneStatus)
    {
        m_bAppleCarPlayPhoneStatus = bAppleCarPlayPhoneStatus;
    }
    else
    {
        // Do nothing.
    }
}

void CAppleCarPlayAdaptor::setCarPlaySiriStatus(const bool bCarPlaySiriStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : bCarPlaySiriStatus: %d", __FUNCTION__, bCarPlaySiriStatus);

    if (m_bCarPlaySiriStatus != bCarPlaySiriStatus)
    {
        m_bCarPlaySiriStatus = bCarPlaySiriStatus;
    }
    else
    {
        // Do nothing.
    }
}

void CAppleCarPlayAdaptor::setCPMediaSongTitle(const QString &strCPMediaSongTitle)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : strCPMediaSongTitle: %s",
             __FUNCTION__, strCPMediaSongTitle.toStdString().c_str());

    if (m_strCPMediaSongTitle != strCPMediaSongTitle)
    {
        m_strCPMediaSongTitle = strCPMediaSongTitle;
        emit sigCPMediaSongTitleChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.",
                 __FUNCTION__);
    }
}

void CAppleCarPlayAdaptor::setCPMediaSongArtist(const QString &strCPMediaSongArtist)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : strCPMediaSongArtist: %s",
             __FUNCTION__, strCPMediaSongArtist.toStdString().c_str());

    if (m_strCPMediaSongArtist != strCPMediaSongArtist)
    {
        m_strCPMediaSongArtist = strCPMediaSongArtist;
        emit sigCPMediaSongArtistChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : Values are same.",
                 __FUNCTION__);
    }
}

void CAppleCarPlayAdaptor::setAppleCarPlayDeviceName(const QString &strAppleCarPlayDeviceName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, : strAppleCarPlayDeviceName: %s: ", __FUNCTION__, strAppleCarPlayDeviceName.toStdString().c_str());

    if (strAppleCarPlayDeviceName != m_strAppleCarPlayDeviceName)
    {
        m_strAppleCarPlayDeviceName = strAppleCarPlayDeviceName;

        if ( m_strAppleCarPlayDeviceName.length() > DEVICE_NAME_LENGTH_LIMIT )
        {
            m_strAppleCarPlayDeviceName.remove((DEVICE_NAME_LENGTH_LIMIT - 3),  (m_strAppleCarPlayDeviceName.length() - (DEVICE_NAME_LENGTH_LIMIT - 3)));
            m_strAppleCarPlayDeviceName.append("...");
        }

        emit sigAppleCarPlayDeviceNameChanged();
    }
    else
    {
        //Do nothing.
    }
}

void CAppleCarPlayAdaptor::setAppleCarPlayRemoteUIStatus(bool bAppleCarPlayRemoteUIStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PROJECTION,  "%s, :bAppleCarPlayRemoteUIStatus: %d", __FUNCTION__, bAppleCarPlayRemoteUIStatus);

    if (bAppleCarPlayRemoteUIStatus != m_bAppleCarPlayRemoteUIStatus)
    {
        m_bAppleCarPlayRemoteUIStatus = bAppleCarPlayRemoteUIStatus;
    }
    else
    {
        //Do nothing.
    }
}

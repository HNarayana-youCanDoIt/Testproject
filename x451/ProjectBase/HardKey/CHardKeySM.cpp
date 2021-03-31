/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardkeySM.cpp
* @ingroup      HMIComponent
* @author       Guru Alingal
* CHardKeySM class implements TML_HMI_SM::SCI_HardKey_OCB. This class is used to handle hardkey operations.
* This class is responsible for passing on hard key events to respective modules.
*/

#include "CHardkeySM.h"
#include "logging.h"
#include "CHMIMain.h"
#include "CMediaAdaptor.h"
#include "CTunerAdaptor.h"
#include "CPhoneAdaptor.h"
#include "CAndroidAutoAdaptor.h"
#include "CAppleCarPlayAdaptor.h"
#include "CHomeAdaptor.h"
#include "CHardKeyEnum.h"
#include "CAudioAdaptor.h"
#include "CVoiceAlertsAdaptor.h"
#include "CVRAdaptor.h"
#include "ResourceFactory.hpp"
#include "CParkAssistAdaptor.h"

/**
 * @todo: This is just basic implementation considering audio sources only. Need to handle scenarios wich involves
 * different HMI states, audio sources. We need to prepare a design for handling common functionalities that does not fall
 * in the direct responsibility any modules but is critical for the system and which requires complete awareness of the
 * system state.
 */

CHardkeySM::CHardkeySM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_HardKey_OCB(this);
    initKeyHandlerMap();
}

CHardkeySM::~CHardkeySM()
{

}

void CHardkeySM::handleHomeHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, __FUNCTION__);

    //If phone call exists and projection is not with AA then do not process home HK
    if((CPhoneAdaptor::getInstance()) &&
            (CPhoneAdaptor::getInstance()->doesCallExist()) &&
            (!CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call exist and projection is not with AA, do not process home hk");
    }
    //If Apple CarPlay call exists in CP projection, then do not process home HK
    else if(CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus() &&
            CAppleCarPlayAdaptor::getInstance()->getAppleCarPlayPhoneStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Apple Car Play Phone call exists, do not process home hk");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call does not exist, process home HK");
        CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState> (CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());
        handleHardKeysInRadio(CHardKeyEnum::KEYCODEHK_HOME,eKeyState);
        switch(eKeyState)
        {
        case HKEY_STATE_RELEASED:
        case HKEY_STATE_LONGPRESSED:
        {
            handleHardKeysInProjection(CHardKeyEnum::KEYCODEHK_HOME, eKeyState);
            CHomeAdaptor::getInstance().setCurrentPageIndex(0);
            CHMIMain::getSM()->raise_evHomeActivated();
        }
            break;
        case HKEY_STATE_PRESSED:
            //No Action is expected.
            break;
        default:
            LOG_WARNING(Log::e_LOG_CONTEXT_HARDKEYS, "%s Invalid key state %d recived hence ignored.",__FUNCTION__, eKeyState);
            break;
        }
    }
}

void CHardkeySM::handleFavHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s", __FUNCTION__);

    //If phone call exists and projection is not with AA then do not process home HK
    if((CPhoneAdaptor::getInstance()) &&
            (CPhoneAdaptor::getInstance()->doesCallExist()) &&
            (!CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call exist and projection is not with AA, do not process fav hk");
    }
    //If Apple CarPlay call exists in CP projection, then do not process fav HK
    else if(CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus() &&
            CAppleCarPlayAdaptor::getInstance()->getAppleCarPlayPhoneStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Apple Car Play Phone call exists, do not process fav hk");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call does not exist, process favorite HK");
        CHardKeyEnum::EFavKeyCode eKeyCode = CHomeAdaptor::getInstance().eCurrentFavKeyCode();

        CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());

        handleHardKeysInRadio(CHardKeyEnum::KEYCODEHK_FAVORITE,eKeyState);

        /*
         * If OK Google is active, then HMI has to report the key to AA pres to deactivate OK Google.
         */
        if (CAndroidAutoAdaptor::getInstance()->okGoogleStatus())
        {
            CAndroidAutoAdaptor::getInstance()->handleHardKeys(CHardKeyEnum::KEYCODEHK_FAVORITE, eKeyState);
        }

        if(CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState )
        {
            if (CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus())
            {
                CAppleCarPlayAdaptor::getInstance()->requestNative();
            }
            else if (CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus())
            {
                CAndroidAutoAdaptor::getInstance()->requestNative();
            }
            //FixMe : need to display fav hard key screen after confirmation from android/carplay requestNative method.
            //TO DO: Display a list of configurable options.
            CHMIMain::getSM()->getSCI_Home()->set_bIsConfigureFavHKSelection(true);
            CHMIMain::getSM()->raise_evHomeActivated();
        }
        else if (CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState)
        {
            switch(eKeyCode)
            {
            case FAV_HK_SOURCE:
            {
                LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"[KPI_MARKER][HMI][ Toggling source using SOURCE favourite key]");
                CAndroidAutoAdaptor::getInstance()->setCanSwitchMode(true);
                CAppleCarPlayAdaptor::getInstance()->setIsCPSwitchable(true);
                if((CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()) && (!CAudioAdaptor::getInstance()->pdcMixModeStatus()))
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s: Reverse gear engaged and mix mode is FALSE, pdcRvcStatus: %d, mixModeStatus: %d", __FUNCTION__, CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus(), CAudioAdaptor::getInstance()->pdcMixModeStatus());
                }
                else
                {
                    CAudioAdaptor::getInstance()->toggleEntSrc();
                }
            }
                break;
            case CHardKeyEnum::FAV_HK_AUDIO_SETUP:
            {
                if (CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus())
                {
                    CAppleCarPlayAdaptor::getInstance()->requestNative();
                }
                else if (CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus())
                {
                    CAndroidAutoAdaptor::getInstance()->requestNative();
                }
                CHMIMain::getSM()->getSCI_Setup()->raise_evAudioSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_AUDIO_NAMED_ENTRY());

            }
                break;
            case CHardKeyEnum::FAV_HK_ANDROIDAUTO:
            {
                CAndroidAutoAdaptor::getInstance()->launchAndroidAuto();
            }
                break;
            case CHardKeyEnum::FAV_HK_CARPLAY:
            {
                CAppleCarPlayAdaptor::getInstance()->launchAppleCarPlay();
            }
                break;
            case CHardKeyEnum::FAV_HK_PARK_ASSIST:
                CParkAssistAdaptor::getInstance()->activatePdcRvc(true);
                break;
            case CHardKeyEnum::FAV_HK_CONTACTS:
            {
                CPhoneAdaptor::getInstance()->invSwitchToPhoneBrowse(CPhoneEnum::PHONE_BROWSE_TYPE_CONTACTS);
            }
                break;
            case CHardKeyEnum::FAV_HK_FAVOURITES:
            {
                if (CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus())
                {
                    CAppleCarPlayAdaptor::getInstance()->requestNative();
                }
                else if (CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus())
                {
                    CAndroidAutoAdaptor::getInstance()->requestNative();
                }
                CPhoneAdaptor::getInstance()->invSwitchToPhoneBrowse(CPhoneEnum::PHONE_BROWSE_TYPE_FAVORITES);
            }
                break;
            case CHardKeyEnum::FAV_HK_MOODLIGHTING:
                //TODO: activate Navigation.
                break;
            case CHardKeyEnum::FAV_HK_VOICE_COMMAND:
            {
                if ((!CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus()) &&
                        (!CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus()))
                {
                    if((CVRAdaptor::getInstance()) && (!CVRAdaptor::getInstance()->invGetVRSessionStatus()))
                    {
                        CVRAdaptor::getInstance()->activateVRSession(eKeyState);
                    }
                    else
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s: VR session is active", __FUNCTION__);
                    }
                }
                else
                {
                    //Do nothing
                }
            }
                break;
            case CHardKeyEnum::FAV_HK_NAVIGATION:
                //TODO: activate Navigation.
                break;
            case CHardKeyEnum::FAV_HK:
            {
                if (CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus())
                {
                    CAppleCarPlayAdaptor::getInstance()->requestNative();
                }
                else if (CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus())
                {
                    CAndroidAutoAdaptor::getInstance()->requestNative();
                }
                CHMIMain::getSM()->getSCI_Home()->set_bIsConfigureFavHKSelection(true);
                CHMIMain::getSM()->raise_evHomeActivated();
            }
                break;
            default:
                LOG_WARNING(Log::e_LOG_CONTEXT_HARDKEYS,"%s Fav key set to invalid option. %d",__FUNCTION__, static_cast<int>(eKeyCode));

            }
        }
        else if(CHardKeyEnum::HKEY_STATE_PRESSED == eKeyState)
        {
            //Do Nothing
        }
        else{
            //Do Nothing
        }
    }
}

void CHardkeySM::handleNextHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s", __FUNCTION__);

    if((CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()) && (!CAudioAdaptor::getInstance()->pdcMixModeStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s: Reverse gear engaged and mix mode is FALSE, pdcRvcStatus: %d, mixModeStatus: %d", __FUNCTION__, CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus(), CAudioAdaptor::getInstance()->pdcMixModeStatus());
    }
    else if(CPhoneAdaptor::getInstance()->doesCallExist())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call exist, do not process next hk");
    }
    else if(CVRAdaptor::getInstance()->invGetVRSessionStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "VR session active, do not process next hk");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call do not exist, process next hk");
        CAudioEnums::EAudioEntertainmentSrcs eActiveEntSource = static_cast<CAudioEnums::EAudioEntertainmentSrcs>(CHMIMain::getSM()->getSCI_Audio()->get_currentActiveSrc());

        CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());
        CHardKeyEnum::EHardKeys eKeyCode = static_cast<CHardKeyEnum::EHardKeys>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyCode());

        switch (eActiveEntSource)
        {
        case SRC_TUNER_FM:
        case SRC_TUNER_AM:
        case SRC_TUNER_DRM:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s Passing control to Tuner",__FUNCTION__);
            CTunerAdaptor::getInstance()->handleHardKeys(eKeyCode,eKeyState);
        }
            break;
        case SRC_USB1:
        case SRC_BT_A2DP2:
        case SRC_BT_A2DP1:
        case SRC_IPOD:
            //case SRC_AUDIO_AUX:
        {
            CMediaAdaptor::getInstance().handleHardKeys(eKeyCode, eKeyState);
        }
            break;
            // Android Auto Media Source
        case SRC_GAL_MEDIA:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s Passing control to AndroidAuto",__FUNCTION__);
            CAndroidAutoAdaptor::getInstance()->handleHardKeys(eKeyCode, eKeyState);
        }
            break;
        case SRC_CARPLAY_MEDIA:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s Passing control to AppleCarPlay",__FUNCTION__);
            CAppleCarPlayAdaptor::getInstance()->handleHardKeys(eKeyCode, eKeyState);
        }
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s No entertainment source found to handle this key." ,__FUNCTION__);
            break;
        }
    }
}

void CHardkeySM::handlePrevHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s", __FUNCTION__);

    if((CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()) && (!CAudioAdaptor::getInstance()->pdcMixModeStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s: Reverse gear engaged and mix mode is FALSE, pdcRvcStatus: %d, mixModeStatus: %d", __FUNCTION__, CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus(), CAudioAdaptor::getInstance()->pdcMixModeStatus());
    }
    else if(CPhoneAdaptor::getInstance()->doesCallExist())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call exist, do not process previous hk");
    }
    else if(CVRAdaptor::getInstance()->invGetVRSessionStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "VR session active, do not process previous hk");
    }
    else
    {
        CAudioEnums::EAudioEntertainmentSrcs eActiveEntSource = static_cast<CAudioEnums::EAudioEntertainmentSrcs>(CHMIMain::getSM()->getSCI_Audio()->get_currentActiveSrc());
        CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());
        CHardKeyEnum::EHardKeys eKeyCode = static_cast<CHardKeyEnum::EHardKeys>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyCode());

        switch (eActiveEntSource)
        {
        case SRC_TUNER_FM:
        case SRC_TUNER_AM:
        case SRC_TUNER_DRM:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s Passing control to Tuner",__FUNCTION__);
            CTunerAdaptor::getInstance()->handleHardKeys(eKeyCode, eKeyState);
        }
            break;
        case SRC_USB1:
        case SRC_BT_A2DP2:
        case SRC_BT_A2DP1:
        case SRC_IPOD:
            //case SRC_AUDIO_AUX:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s Passing control to Media",__FUNCTION__);
            CMediaAdaptor::getInstance().handleHardKeys(eKeyCode, eKeyState);
        }
            break;
            // Android Auto Media Source
        case SRC_GAL_MEDIA:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s Passing control to AndroidAuto",__FUNCTION__);
            CAndroidAutoAdaptor::getInstance()->handleHardKeys(eKeyCode, eKeyState);
        }
            break;
        case SRC_CARPLAY_MEDIA:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s Passing control to AppleCarPlay",__FUNCTION__);
            CAppleCarPlayAdaptor::getInstance()->handleHardKeys(eKeyCode, eKeyState);
        }
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s No entertainment source found to handle this key." ,__FUNCTION__);
            break;
        }
    }
}

void CHardkeySM::handlePhoneHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s", __FUNCTION__);
    CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());

    handleHardKeysInRadio(CHardKeyEnum::KEYCODEHK_PHONE,eKeyState);

    //If phone call is incoming then the phone hard key should be handled by phone adaptor
    if((CPhoneAdaptor::getInstance()) &&
            (CPhoneAdaptor::getInstance()->isCallIncoming()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s: Phone call incoming, passing control to Phone",__FUNCTION__);
        CPhoneAdaptor::getInstance()->invHandleHardKeys(CHardKeyEnum::KEYCODEHK_PHONE, eKeyState);
        /*
         * We need to switch to phone screen if AA projection is active.
         * Use case - User is in AA music screen. Incoming call is received and
         * user selects PHONE HK, incoming call should be accepted and AA screen
         * should also swicth to AA phone screen, therefore the handleHardKeysInProjection
         * method is being called here.
         */
        handleHardKeysInProjection(CHardKeyEnum::KEYCODEHK_PHONE, eKeyState);
    }
    /*
     * Projection need all KeyEvents like press, release, long press.
     */
    else if(handleHardKeysInProjection(CHardKeyEnum::KEYCODEHK_PHONE, eKeyState))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "KEYCODEHK_PHONE is handled in projection.");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s Passing control to Phone",__FUNCTION__);

        if (CPhoneAdaptor::getInstance())
        {
            CPhoneAdaptor::getInstance()->invHandleHardKeys(CHardKeyEnum::KEYCODEHK_PHONE, eKeyState);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_HARDKEYS, "Phone Adaptor object is not created");
        }
    }
}

void CHardkeySM::handleBackHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s", __FUNCTION__);
    CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());

    // TODO: Need to handle scenarios while popup or drawers is actve.
	
    /*
    * Projection need all KeyEvents like press, release, long press.
    */
    if (handleHardKeysInProjection(CHardKeyEnum::KEYCODEHK_BACK, eKeyState))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s: KEYCODEHK_BACK is handled in Projection.", __FUNCTION__);
    }
    else if(handleHardKeysInRadio(CHardKeyEnum::KEYCODEHK_BACK,eKeyState))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s: KEYCODEHK_BACK is handled in Radio.", __FUNCTION__);
    }
    else if(handleHardKeysInParkAssist(CHardKeyEnum::KEYCODEHK_BACK, eKeyState))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s: KEYCODEHK_BACK is handled in Park Assist.", __FUNCTION__);
    }
    else if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState ) ||
            (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState ))
    {
        CFramework::getFramework().doBack();
    }
    else
    {
        //Do Nothing
    }
}

void CHardkeySM::handleEnggMenuHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s", __FUNCTION__);

    //If phone call exists and projection is not with AA then do not process engg menu HK
    if((CPhoneAdaptor::getInstance()) &&
            (CPhoneAdaptor::getInstance()->doesCallExist()) &&
            (!CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call exist and projection is not with AA, do not process engg menu HK");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call does not exist, process engg menu HK");
        handleHardKeysInRadio(CHardKeyEnum::KEYCODEHK_ENGGMENU,m_eKeyState);
        /** Need to revisit the below conditions. It is possible that key press only emits key pressed for
         * special keys like engg menu and s/w update.
          */
        // ToDo : Need to update hardKeySM design
//        if((HKEY_STATE_PRESSED == m_eKeyState ) ||
//                (HKEY_STATE_LONGPRESSED == m_eKeyState ))
//        {
            handleHardKeysInProjection(CHardKeyEnum::KEYCODEHK_ENGGMENU, m_eKeyState);
            CHMIMain::getSM()->raise_evEnggMenuActivated();
//        }
//        else
//        {
//            //Do Nothing
//        }
    }
}

void CHardkeySM::handleSwUpdateHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s", __FUNCTION__);

    //If phone call exists and projection is not with AA then do not process s/w update HK
    if((CPhoneAdaptor::getInstance()) &&
            (CPhoneAdaptor::getInstance()->doesCallExist()) &&
            (!CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call exist and projection is not with AA, do not process s/w update HK");
    }
    else if(CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus() &&
            CAppleCarPlayAdaptor::getInstance()->getAppleCarPlayPhoneStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Apple Car Play Phone call exists, do not process s/w update HK");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call does not exist, process s/w updae HK");
        CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());
        handleHardKeysInRadio(CHardKeyEnum::KEYCODEHK_SOFTWARE_UPDATE,eKeyState);
        /** Need to revisit the below conditions. It is possible that key press only emits key pressed for
         * special keys like engg menu and s/w update.
          */
        if(CHardKeyEnum::HKEY_STATE_PRESSED == eKeyState)
        {
            handleHardKeysInProjection(CHardKeyEnum::KEYCODEHK_SOFTWARE_UPDATE, eKeyState);
            CHMIMain::getSM()->raise_evSoftwareUpdateActivated();
        }
        else
        {
            //Do Nothing
        }
    }
}

void CHardkeySM::handleVolRotaryHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s", __FUNCTION__);
}

void CHardkeySM::handleUpSWCK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s ", __FUNCTION__);

    CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());

    handleHardKeysInRadio(CHardKeyEnum::KEYCODESWC_UP,eKeyState);
}

void CHardkeySM::handleDownSWCK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s ", __FUNCTION__);

    CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());

    handleHardKeysInRadio(CHardKeyEnum::KEYCODESWC_DOWN,eKeyState);
}

void CHardkeySM::handleRejectMuteSWCK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s ", __FUNCTION__);

    CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());

    //If Apple CarPlay call exists in CP projection, then process RejectMute HK with all the keystates
    if(CAppleCarPlayAdaptor::getInstance()->getAppleCarPlayPhoneStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Apple Car Play Phone call exists, process RejectMute hk");
        CAppleCarPlayAdaptor::getInstance()->handleHardKeys(CHardKeyEnum::KEYCODESWC_REJECT_MUTE, eKeyState);
    }
    else if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState ) ||
            (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState ))
    {
        //If phone call exists then the phone hard key should be handled by phone adaptor
        if((CPhoneAdaptor::getInstance()) &&
                (CPhoneAdaptor::getInstance()->doesCallExist()))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s: Phone call case, passing control to Phone",__FUNCTION__);
            CPhoneAdaptor::getInstance()->invHandleHardKeys(CHardKeyEnum::KEYCODESWC_REJECT_MUTE, eKeyState);
        }
        else
        {
            CAudioAdaptor::getInstance()->toggleMute(true);
        }
    }
    else
    {
        //Do Nothing
    }
}

void CHardkeySM::handleAcceptVRSWCK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s ", __FUNCTION__);

    CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());

    handleHardKeysInRadio(CHardKeyEnum::KEYCODESWC_ACCEPT_VR,eKeyState);

    //If phone call exists then the phone hard key should be handled by phone adaptor
    if((CPhoneAdaptor::getInstance()) &&
            (CPhoneAdaptor::getInstance()->doesCallExist()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s: Phone call case, passing control to Phone",__FUNCTION__);
        CPhoneAdaptor::getInstance()->invHandleHardKeys(CHardKeyEnum::KEYCODESWC_ACCEPT_VR, eKeyState);
        /*
         * We need to switch to phone screen if AA projection is active.
         * Use case - User is in AA music screen. Incoming call is received and
         * user selects ACCEPT_VR HK, incoming call should be accepted and AA screen
         * should also swicth to AA phone screen, therefore the handleHardKeysInProjection
         * method is being called here.
         */
        handleHardKeysInProjection(CHardKeyEnum::KEYCODEHK_PHONE, eKeyState);
    }
    else if(CAppleCarPlayAdaptor::getInstance()->getAppleCarPlayPhoneStatus())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s: Carplay Phone call case, passing control to Projection",__FUNCTION__);
        handleHardKeysInProjection(CHardKeyEnum::KEYCODESWC_ACCEPT_VR, eKeyState);
    }
    else if ( (!CVRAdaptor::getInstance()->invGetVRSessionStatus()) &&
             handleHardKeysInProjection(CHardKeyEnum::KEYCODESWC_ACCEPT_VR, eKeyState))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s: KEYCODESWC_ACCEPT_VR is handled in Projection.", __FUNCTION__);
    }
    else
    {
        if((CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState) &&
                (!CVRAdaptor::getInstance()->invGetVRSessionStatus()))
        {
            //If VR session is not active and PTT long press then activate phone bt vr
            CPhoneAdaptor::getInstance()->reqPhoneBtVrActivation();
        }
        else
        {
            CVRAdaptor::getInstance()->activateVRSession(eKeyState);
        }
    }
}

void CHardkeySM::handleSourceSWCK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s ", __FUNCTION__);

    CHardKeyEnum::EHardKeyState eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());

    /*
     *  If OKGoogle is going on and user press swc source key, HMI has to report key to AA pres to deactivate the OK Google.
     */
    if (CAndroidAutoAdaptor::getInstance()->okGoogleStatus())
    {
        CAndroidAutoAdaptor::getInstance()->handleHardKeys(CHardKeyEnum::KEYCODESWC_SOURCE, eKeyState);
    }

    if((CHardKeyEnum::HKEY_STATE_RELEASED == eKeyState ) ||
            (CHardKeyEnum::HKEY_STATE_LONGPRESSED == eKeyState ))
    {
        //If phone call exists then do not process source SWC HK
        if((CPhoneAdaptor::getInstance()) &&
                (CPhoneAdaptor::getInstance()->doesCallExist()))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call exist, do not process source SWC HK");
        }
        //If Apple CarPlay call exists in CP projection, then do not process SourceSWCK
        else if(CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus() &&
                CAppleCarPlayAdaptor::getInstance()->getAppleCarPlayPhoneStatus())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Apple Car Play Phone call exists, do not process SourceSWCK");
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "Phone call does not exist, process source SWC HK");
            handleHardKeysInRadio(CHardKeyEnum::KEYCODESWC_SOURCE,eKeyState);
            LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"[KPI_MARKER][HMI][ Toggling source using SOURCE SWC key]");
            CAndroidAutoAdaptor::getInstance()->setCanSwitchMode(true);
            CAppleCarPlayAdaptor::getInstance()->setIsCPSwitchable(true);
            if((CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()) && (!CAudioAdaptor::getInstance()->pdcMixModeStatus()))
            {
                LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s: Reverse gear engaged and mix mode is FALSE, pdcRvcStatus: %d, mixModeStatus: %d", __FUNCTION__, CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus(), CAudioAdaptor::getInstance()->pdcMixModeStatus());
            }
            else
            {
                CAudioAdaptor::getInstance()->toggleEntSrc();
            }
        }
    }
    else
    {
        // do nothing
    }
}

void CHardkeySM::handleHardkeys(int iKeyCode, int iKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s, Current hardkey keyCode : %d, keyState : %d", __FUNCTION__, iKeyCode, iKeyState);

    m_eKeyState = static_cast<CHardKeyEnum::EHardKeyState>(iKeyState);
    m_eKeyCode = static_cast<CHardKeyEnum::EHardKeys>(iKeyCode);

    emit sigHardKeyStateUpdated(iKeyCode, iKeyState);
}

void CHardkeySM::initKeyHandlerMap()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s", __FUNCTION__);

    m_mapHardKeyHandler.clear();

    CFunctor<CHardkeySM> funct(this, &CHardkeySM::handleHomeHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODEHK_HOME, funct);

    funct.update(this, &CHardkeySM::handleFavHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODEHK_FAVORITE, funct);

    funct.update(this, &CHardkeySM::handleNextHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODEHK_SEEKUP, funct);

    funct.update(this, &CHardkeySM::handlePrevHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODEHK_SEEKDOWN, funct);

    funct.update(this, &CHardkeySM::handlePhoneHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODEHK_PHONE, funct);

    funct.update(this, &CHardkeySM::handleBackHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODEHK_BACK, funct);

    funct.update(this, &CHardkeySM::handleSwUpdateHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODEHK_SOFTWARE_UPDATE, funct);

    funct.update(this, &CHardkeySM::handleEnggMenuHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODEHK_ENGGMENU, funct);

    funct.update(this, &CHardkeySM::handleVolRotaryHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODEHK_VOLROTARY, funct);

    funct.update(this, &CHardkeySM::handleNextHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODESWC_NEXT, funct);

    funct.update(this, &CHardkeySM::handlePrevHK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODESWC_PREV, funct);

    funct.update(this, &CHardkeySM::handleSourceSWCK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODESWC_SOURCE, funct);

    funct.update(this, &CHardkeySM::handleAcceptVRSWCK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODESWC_ACCEPT_VR, funct);

    funct.update(this, &CHardkeySM::handleRejectMuteSWCK);
    m_mapHardKeyHandler.insert(CHardKeyEnum::KEYCODESWC_REJECT_MUTE, funct);

    connect(this, SIGNAL(sigHardKeyStateUpdated(int, int)), this, SLOT(sltOnHardKeyStateUpdated(int, int)), Qt::QueuedConnection);

}

void CHardkeySM::sltOnHardKeyStateUpdated(int iKeyCode, int iKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s, Current hardKey eKeyCode: %d", __FUNCTION__, iKeyCode);
    Q_UNUSED(iKeyState);
    CHardKeyEnum::EHardKeys eKeyCode = static_cast<CHardKeyEnum::EHardKeys>(iKeyCode);
    QMap<CHardKeyEnum::EHardKeys, CFunctor<CHardkeySM>>::iterator iter = m_mapHardKeyHandler.find(eKeyCode);

    if(iter != m_mapHardKeyHandler.end())
    {
        (iter.value())();
    }
}

bool CHardkeySM::handleHardKeysInProjection(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s: eHardKey: %d, eHardKeyState: %d", __FUNCTION__, eKey, eKeyState);

    bool bReturn = false;

    if (CHardKeyEnum::KEYCODESWC_ACCEPT_VR == eKey)
    {
        if (CAndroidAutoAdaptor::getInstance()->androidAutoConnectionStatus())
        {
            bReturn = CAndroidAutoAdaptor::getInstance()->handleHardKeys(eKey, eKeyState);
        }
        else if (CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus())
        {
            bReturn = CAppleCarPlayAdaptor::getInstance()->handleHardKeys(eKey, eKeyState);
        }
        else
        {
            // Do nothing.
        }
    }
    else if(CHardKeyEnum::KEYCODEHK_PHONE == eKey && CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus())
    {
        bReturn = CAppleCarPlayAdaptor::getInstance()->handleHardKeys(eKey, eKeyState);
    }
    else if (CAndroidAutoAdaptor::getInstance()->androidAutoProjectionStatus())
    {
        bReturn = CAndroidAutoAdaptor::getInstance()->handleHardKeys(eKey, eKeyState);
    }
    else if(CAppleCarPlayAdaptor::getInstance()->appleCarPlayProjectionStatus())
    {
        bReturn = CAppleCarPlayAdaptor::getInstance()->handleHardKeys(eKey, eKeyState);
    }

    return bReturn;
}

bool CHardkeySM::handleHardKeysInRadio(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    bool bRes = false;
    CAudioEnums::EAudioEntertainmentSrcs eActiveEntSource = CAudioAdaptor::getInstance()->activeEntSrc();
    /** Passing control to Tuner if active src is tuner to stop active seek */
    if(CAudioEnums::SRC_TUNER_FM == eActiveEntSource || CAudioEnums::SRC_TUNER_DRM == eActiveEntSource || CAudioEnums::SRC_TUNER_AM == eActiveEntSource)
    {
        bRes = CTunerAdaptor::getInstance()->handleHardKeys(eKey,eKeyState);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_TUNER,"%s, Tuner is not activated", __FUNCTION__);
    }
    return bRes;
}

bool CHardkeySM::handleHardKeysInParkAssist(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS,"%s: eKey: %d, eKeyState: %d", __FUNCTION__, eKey, eKeyState);
    bool bRes = false;

    if((CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus()) && (CParkAssistAdaptor::getInstance()->isPdcRvcActivatedFromHmi()))
    {
        bRes = CParkAssistAdaptor::getInstance()->handleHardKeys(eKey,eKeyState);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HARDKEYS, "%s: PDC is not activated by HMI", __FUNCTION__);
    }
    return bRes;

}

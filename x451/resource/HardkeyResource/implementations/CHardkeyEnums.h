/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CHardkeyEnums.h
* @ingroup      HMIComponent
* @author       Prashantkumar Raut
* CHardkeyEnums, Enum for HardkeyHandler.
*/
#ifndef CHARDKEYENUMS_H
#define CHARDKEYENUMS_H


/**
 * Enum for different hard key states
 */
enum EHardKeyState
{
    HKEY_STATE_INVALID = 0u,
    HKEY_STATE_PRESSED,
    HKEY_STATE_LONGPRESSED,
    HKEY_STATE_RELEASED,
    HKEY_STATE_LONGRELEASED,
    HKEY_STATE_ROTATE_LEFT,
    HKEY_STATE_ROTATE_RIGHT,
    HKEY_STATE_STUCK
};

/**
 * Enum for different hard key code
 */
enum EHardKeys
{
    KEYCODEHK_INVALID=0u,

    //Hard keys used in X451 board
    KEYCODEHK_VOLROTARY=20,
    KEYCODEHK_MENUROTARY,
    KEYCODEHK_HOME,
    KEYCODEHK_FAVORITE,
    KEYCODEHK_SEEKDOWN,
    KEYCODEHK_SEEKUP,
    KEYCODEHK_PHONE,
    KEYCODEHK_BACK,
    KEYCODEHK_VOLROTARY_KNOB,
    KEYCODEHK_MENUROTARY_KNOB,
    KEYCODEHK_SOFTWARE_UPDATE,
    KEYCODEHK_ENGGMENU,

    //Touch keys used in X0_7" board
    KEYCODETOUCH_POWER=60,
    KEYCODETOUCH_HOME,
    KEYCODETOUCH_FAVOURITE,
    KEYCODETOUCH_MUTE,
    KEYCODETOUCH_VOLUME_UP,
    KEYCODETOUCH_VOLUME_DOWN,
    KEYCODETOUCH_SOFTWARE_UPDATE,
    KEYCODETOUCH_ENGGMENU,

    //SWC keys used in both X0_7" and X451 boards
    KEYCODESWC_PREV=40,
    KEYCODESWC_SOURCE,
    KEYCODESWC_NEXT,
    KEYCODESWC_REJECT_MUTE,
    KEYCODESWC_UP,
    KEYCODESWC_DOWN,
    KEYCODESWC_ACCEPT_VR
};

/**
 * @brief The EFavKeyCode enum to create enmerations for all possible fav key configuration.
 */
enum EFavKeyCode{

    FAV_HK						= 0,
    FAV_HK_SOURCE,
    FAV_HK_AUDIO_SETUP,
    FAV_HK_FAVOURITES_CONTACTS,
    FAV_HK_VOICE_COMMAND,
    FAV_HK_NAVIGATION,
    FAV_HK_ANDROIDAUTO,
    FAV_HK_CARPLAY,
};

#endif // CHARDKEYENUMS_H

/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            PersistencyDef.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * PersistencyDef, holds Definations and Enums for Persistency service.
 */

#ifndef PERSISTENCYDEF_H
#define PERSISTENCYDEF_H

#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)
#define USE_SIMULATION_PERSISTENCY
#endif // defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX_X86)

//____________________________________________________________________________
/** ldbid : logical database ID
 * for group data it will be group ID (should be in HEX)
 */
const unsigned int PCL_LDBID_LOCAL  = 0xFF;         //used for all application
const unsigned int PCL_LDBID_PUBLIC = 0x00;         //used for public data
const unsigned int PCL_LDBID_EOL    = 0x71;         //used for EOL data
const unsigned int PCL_LDBID_EARLY  = 0x72;         //used for early boot info

/** user_no, seat_no
 * the User ID and Seat no
 */
const unsigned int PCL_USER_NUMBER = 0x01;          //used to define user for PCL (set to 1 as no profile save used)
const unsigned int PCL_SEAT_NUMBER = 0x01;          //used to define seat for PCL (set to 1 as no profile save used)
const unsigned int PCL_DEFAULT_USER_NO = 0x00;      //used to define DEFAULT user for PCL
const unsigned int PCL_DEFAULT_SEAT_NO = 0x00;      //used to define DEFAULT seat for PCL

const QString HMI_PCL_APP_NAME = "APP_HMI";         //used to define Application for PCL
//____________________________________________________________________________
/**
 * EPersistencyKeys enum used to read write persistency
 * this enum should hold all keys present in Elina persistency json files
 **/
enum EPersistencyKeys
{
    HMI_DATA_AVAILABLE = 0,                         // used as simulation persistancy available flag

    //EOL Status changes
    HMI_PCL_I_EOL_ANDROID_AUTO_ON,                  // Used to hold current EOL status for Android Auto
    HMI_PCL_I_EOL_APPLE_CAR_PLAY_ON,                // Used to hold current EOL status for Apple Car Play
    HMI_PCL_I_EOL_DOODLE_ON,                        // Used to hold current EOL status for Doodle
    HMI_PCL_I_EOL_DRIVE_NEXT_ON,                    // Used to hold current EOL status for DriveNext
    HMI_PCL_I_EOL_W3W_ON,                           // Used to hold current EOL status for W3W
    HMI_PCL_I_EOL_AUX_ON,                           // Used to hold current source status for AUX

    //HMI HOME DATA PERSISTANCY KEYS
    HMI_PCL_I_HOME_SLOT_01,                         // used for home screen home page slot 1 shortcut id
    HMI_PCL_I_HOME_SLOT_02,                         // used for home screen home page slot 2 shortcut id
    HMI_PCL_I_HOME_SLOT_03,                         // used for home screen home page slot 3 shortcut id
    HMI_PCL_I_HOME_SLOT_04,                         // used for home screen home page slot 4 shortcut id
    HMI_PCL_I_HOME_SLOT_05,                         // used for home screen home page slot 5 shortcut id
    HMI_PCL_I_HOME_SLOT_06,                         // used for home screen home page slot 6 shortcut id

    //HMI SETUP PERSISTENCY KEYS
    HMI_PCL_I_SETUP_SMS_NOTIFY_TYPE,                // used for SMS notification type
    HMI_PCL_I_SETUP_SMS_CONFIGURE_SELECTION,        // used for SMS configure selection

    //HMI ENGG MENU DATA PERSISTANCY KEYS
    HMI_PCL_I_ENGG_MENU_TEST_AUTOMATION,            //used for EnggMenu Test Automation Option

    //HMI FAVORITE SCREEN PERSISTENCY KEYS
    HMI_PCL_I_FAVORITE_SCREEN_OPTION_SELECTION,     // used for favorite screen option selection

    //HMI AUDIO SETUP PRESET
    HMI_PCL_I_SETUP_AUDIO_PRESET,

    //HMI THEME SETUP PRESET
    HMI_PCL_I_SETUP_THEME_PRESET,

    //HMI SETUP CUSTOM SMS
    HMI_PCL_S_SETUP_CUSTOM_SMS_01,                  // used for setup custom SMS text 01
    HMI_PCL_S_SETUP_CUSTOM_SMS_02,                  // used for setup custom SMS text 02
    HMI_PCL_S_SETUP_CUSTOM_SMS_03,                  // used for setup custom SMS text 03
    HMI_PCL_S_SETUP_CUSTOM_SMS_04,                  // used for setup custom SMS text 04
    HMI_PCL_S_SETUP_CUSTOM_SMS_05,                  // used for setup custom SMS text 05
    HMI_PCL_S_SETUP_CUSTOM_SMS_06,                  // used for setup custom SMS text 06
    HMI_PCL_S_SETUP_CUSTOM_SMS_07,                  // used for setup custom SMS text 07

    //HMI ENGG MENU KEYS
    HMI_PCL_I_ENGG_STATIC_IP_SELECTION,             // used for storing the static ip option selection status
    HMI_PCL_I_ENGG_CPU_MEASUREMENT_SELECTION,       // used for storing the CPU measurement option selection status
    HMI_PCL_I_ENGG_RAM_MEASUREMENT_SELECTION,       // used for storing the RAM measurement option selection status
    HMI_PCL_I_ENGG_DEBUG_LOGS_SELECTION,            // used for storing the debug logs option selection status
    HMI_PCL_I_ENGG_IPC_LOGS_SELECTION,              // used for storing the IPC logs option selection status

    //HMI SMART FAN STATE(CP)
    HMI_PCL_I_CP_SMART_FAN_STATE,                   // used for storing the state of the smart fan

    //HMI THEME SETUP PRESET
    HMI_PCL_I_THEME_CUSTOM_FANSPEED,                // used for storing custom fan speed
    HMI_PCL_I_THEME_CUSTOM_TEMPERATURE,             // used for storing custom temperature
    HMI_PCL_I_THEME_CUSTOM_COLOR,                   // used for storing custom color
    HMI_PCL_I_THEME_CUSTOM_BRIGHTNESS,              // used for storing custom brightness
    HMI_PCL_I_THEME_CUSTOM_AMBIENTLIGHT,            // used for storing custom ambientlight
    HMI_PCL_I_THEME_CUSTOM_NOTIFICATION,            // used for storing custom notification
    HMI_PCL_I_THEME_CUSTOM_AUDIOPRESET,             // used for storing custom audiopreset

    // HMI THEME WITH DRIVE MODE DATA
    HMI_PCL_I_CHANGE_THEME_WITH_DRIVE_MODE_STATUS,  // used for storing flag for change theme with drive mode status
    HMI_PCL_I_HMI_THEME_SELECTION,                  // used for storing flag for hmi theme selection

    //HMI IC CAST ON/OFF DATA
    HMI_PCL_I_HMI_IC_CAST_STATE,                    // used for storing IC cast state

    //HMI MEDIA OFF
    HMI_PCL_I_SELECTED_CLOCK_ID,                    // used for storing selected clock layout

    //HMI DOODLE
    HMI_PCL_I_DOODLE_STICKER_ACTIVATED,             // used for storing Doodle activate status
    HMI_PCL_I_DOODLE_STICKER_POS_X,                 // used for storing Doodle sticker X position
    HMI_PCL_I_DOODLE_STICKER_POS_Y,                 // used for storing Doodle sticker Y position

    //HMI W3W AUTO LAUNCH PERMISSIONS
    HMI_PCL_I_W3W_AUTOLAUNCH_ANDROID_AUTO,          // used for W3W Auto Launch Permission for Android Auto
    HMI_PCL_I_W3W_AUTOLAUNCH_APPLE_CARPLAY,         // used for W3W Auto Launch Permission for Apple Carplay

    //HMI W3W WALKTHROUGH ON STARTUP
    HMI_PCL_I_W3W_STARTUP_WALKTHROUGH,              // used for W3W Walkthrough On Startup setting

    /**
      * Add your hmi module specific persistancy keys
      * Add respective Key, default value and updateVersion in CPersistencyAdaptor::m_mapKeyValueTypes
      * using CPersistencyAdaptor::validateDefaultPersistencyKeyValues function
      */

    TOTAL_KEYS,                                     // used to get total persistancy key count
};
//____________________________________________________________________________

#endif // PERSISTENCYDEF_H

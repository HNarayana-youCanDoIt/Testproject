/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupEnums.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupEnums.h, setup module enums is present here
 */
#ifndef CSETUPENUMS_H
#define CSETUPENUMS_H

#include <QObject>
#include <QtQml>

/**
 * @brief The CSetupEnums class: This class contains all the enums related to setup module
 */
class CSetupEnums: public QObject
{
    Q_OBJECT
public:

    /**
     * @brief The ESetup enum: This enum contains all the options of main setup screen
     */
    enum ESetup
    {
        SETUP_INVALID          = -1,
        SETUP_VEHICLE          = 0,
        SETUP_AUDIO            = 1,
        SETUP_BLUETOOTH        = 2,
        SETUP_VOLUME           = 3,
        SETUP_GENERAL          = 4,
        SETUP_THEMES           = 5,
        SETUP_SOFTWARE_DETAILS = 6,
        SETUP_ABOUT            = 7,
    };
    Q_ENUM(ESetup)


    /**
     * @brief The EAudioSetupCurrentScreen enum: This enum contains all the audio setup screens
     */
    enum EAudioSetupCurrentScreen
    {
        AUDIOSETUP_NONE             = -1,
        AUDIOSETUP_BMT_AUDIO_PRESET_SCREEN = 0,
        AUDIOSETUP_BALANCE_FADER_SCREEN    = 1,
    };
    Q_ENUM(EAudioSetupCurrentScreen)

    /**
     * @brief The EAudioSetupPathViewCurrIndex enum: This enum contains all the indices of pathview used in audio setup screens
     * Dummy enums are created here to avoid the path distortion in pathview used in HBTabBar for Two Items Path. It facilitates the path to rotate in circular motion.
     */
    enum EAudioSetupPathViewCurrIndex
    {
        AUDIOSETUP_BMT_AUDIO_PRESET_INDEX = 0,
        AUDIOSETUP_BALANCE_FADER_INDEX    = 1,
        AUDIOSETUP_BMT_AUDIO_PRESET_INDEX_DUMMY = 2,
        AUDIOSETUP_BALANCE_FADER_INDEX_DUMMY    = 3
    };
    Q_ENUM(EAudioSetupPathViewCurrIndex)

    /**
     * @brief The EBassMiddleTreble enum: This enum contains all the options of Bass, Middle & Treble screen
     */
    enum EBassMiddleTreble
    {
        BMT_INVALID = -1,
        BMT_BASS    = 0,
        BMT_MIDDLE  = 1,
        BMT_TREBLE  = 2
    };
    Q_ENUM(EBassMiddleTreble)

    /**
     * @brief The EVolumeSettings enum: This enum contains all the options of volume setup screen used for validation handling.
     */
    enum EVolumeSettings
    {
        VOLUME_INVALID = -1,
        VOLUME_SPEED_DEPENDENT,
        VOLUME_START_UP,
        VOLUME_PHONE_CALL,
        VOLUME_VOICE_ALERTS
    };

    /**
     * @brief The EGeneralSetup enum: This enum contains all the options of general setup screen
     */
    enum EGeneralSetup
    {
        GENERALSETUP_INVALID         = -1,
        GENERALSETUP_SET_DATE_AND_TIME = 0,
        GENERALSETUP_RESET_TO_FACTORY_DEFAULT = 1,
        GENERALSETUP_ANDROID_AUTO   = 2
    };
    Q_ENUM(EGeneralSetup)

    /**
     * @brief The EVehicleSetup enum: This enum contains all the options of vehicle setup screen used for validation handling
     */
    enum EVehicleSetup
    {
        VEHICLESETUP_INVALID    = -1,
        VEHICLESETUP_VEHICLE_AUTO_RELOCK,
        VEHICLESETUP_PARK_ASSIST,
        VEHICLESETUP_AMBIENT_LIGHT,
        VEHICLESETUP_APPROACH_LAMPS,
        VEHICLESETUP_VOICE_ALERT
    };

    /**
     * @enum    EThemeSetupWithDriveModeItems
     * @brief   It contains the items in theme setup with drive modes screen.
     */
    enum EThemeSetupWithDriveModeItems
    {
        THEME_SETUP_WITH_DRIVE_MODE_INVALID         = -1,
        THEME_SETUP_WITH_DRIVE_MODE_CHANGE_THEME_WITH_DRIVE_MODE = 0,
        THEME_SETUP_WITH_DRIVE_MODE_THEMES,
    };
    Q_ENUM(EThemeSetupWithDriveModeItems)

    /**
     * @enum    EThemesItem
     * @brief   It contains the items in themes dropdown
     */
    enum EThemesItem
    {
        THEME_INVALID         = -1,
        THEME_ONE,
        THEME_TWO,
        THEME_THREE,
        THEME_FOUR,
        THEME_FIVE
    };
    Q_ENUM(EThemesItem)

    /**
     * @enum   EDriveModes
     * @brief  This enum contains all thtype of drive modes available
     */
    enum EDriveModes
    {
        DRIVE_MODE_INVALID = -1,
        DRIVE_MODE_CITY,
        DRIVE_MODE_SPORT,
        DRIVE_MODE_ECO,
    };
    Q_ENUM(EDriveModes)

    /**
     * @brief The ESetupScreens enum: This enum contains all the possible screens in the setup module
     */
    enum ESetupScreens
    {
        SETUP_SCREEN_INVALID = -1,
        SETUP_SCREEN_MAIN = 0,
        SETUP_SCREEN_VEHICLE = 1,
        SETUP_SCREEN_PARK_ASSIST = 2,
        SETUP_SCREEN_MOOD_LIGHTING = 3,
        SETUP_SCREEN_AUDIO = 4,
        SETUP_SCREEN_BASS_MIDDLE_TREBLE = 5,
        SETUP_SCREEN_BALANCE_FADER = 6,
        SETUP_SCREEN_AUDIO_PRESETS = 7,
        SETUP_SCREEN_BLUETOOTH = 8,
        SETUP_SCREEN_PAIRED_DEVICES = 9,
        SETUP_SCREEN_PAIR_NEW_DEVICE = 10,
        SETUP_SCREEN_DELETE_DEVICE = 11,
        SETUP_SCREEN_PHONE = 12,
        SETUP_SCREEN_SMS_ALERT_NOTIFICATION = 13,
        SETUP_SCREEN_CONFIGURE_AUTO_SMS = 14,
        SETUP_SCREEN_KEYBOARD = 15,
        SETUP_SCREEN_VOLUME = 16,
        SETUP_SCREEN_AUX_IN_GAIN = 17,
        SETUP_SCREEN_VOICE_ALERTS = 18,
        SETUP_SCREEN_GENERAL = 19,
        SETUP_SCREEN_SET_DATE = 20,
        SETUP_SCREEN_SET_TIME = 21,
        SETUP_SCREEN_SOFTWARE_DETAILS = 22,
        SETUP_SCREEN_DISPLAY = 23,
        SETUP_SCREEN_THEMES = 24,
        SETUP_SCREEN_THEME_PRESETS = 25,
        SETUP_OPTION_VEHICLE_AUTO_RELOCK = 26,
        SETUP_OPTION_VOICE_ALERT = 27,
        SETUP_OPTION_PARK_ASSIST_TONE_TYPE = 28,
        SETUP_OPTION_PARK_ASSIST_DELAY_TIMER = 29,
        SETUP_SCREEN_LIGHTING = 30,
        SETUP_OPTION_APPROACH_LAMPS = 31,
        SETUP_SCREEN_SMART_FAN = 32,
        SETUP_OPTION_DRL = 33,
        SETUP_SCREEN_ABOUT_MENU = 34,
        SETUP_SCREEN_SOFTWARE_UPDATE = 35,
        SETUP_SCREEN_DRIVENEXT = 36,
        SETUP_SCREEN_DRIVENEXT_RESET_ALL = 37,
    };
    Q_ENUM(ESetupScreens)

    /**
     * @brief The ESetupListItemTypes enum: This enum contains all the possible list item types
     */
    enum ESetupListItemTypes
    {
        SETUP_LIST_ITEM_INVALID_TYPE = -1,
        SETUP_LIST_ITEM_LABEL = 0,
        SETUP_LIST_ITEM_CHECK_BOX = 1,
        SETUP_LIST_ITEM_RADIO_BUTTON = 2,
        SETUP_LIST_ITEM_DROP_DOWN = 3,
        SETUP_LIST_ITEM_TOGGLE_BUTTON = 4,
        SETUP_LIST_ITEM_SLIDER = 5,
        SETUP_LIST_ITEM_ICON_SLIDER = 6,
        SETUP_LIST_ITEM_THEME_CLIMATE = 7,
        SETUP_LIST_ITEM_THEME_COLOR = 8,
        SETUP_LIST_ITEM_THEME_LIGHTING = 9,
        SETUP_LIST_ITEM_THEME_SOUND = 10,
        SETUP_LIST_ITEM_THEME_RADIO_BUTTON = 11,
    };
    Q_ENUM(ESetupListItemTypes)

    /**
     * @brief The ESetupRoles enum: This enum contains all the possible roles for setup module
     */
    enum ESetupRoles
    {
        SETUP_LIST_ITEM_INVALID_ROLE = 255,
        SETUP_LIST_ITEM_INDEX_ROLE = 256,
        SETUP_LIST_ITEM_NAME_ROLE = 257,
        SETUP_LIST_ITEM_DEFAULT_IMAGE_ROLE = 258,
        SETUP_LIST_ITEM_SELECTED_IMAGE_ROLE = 259,
        SETUP_LIST_ITEM_TYPE_ROLE = 260,
        SETUP_LIST_ITEM_ENABLED_ROLE = 261,
        SETUP_LIST_ITEM_COLLAPSED_ROLE = 262,
        SETUP_LIST_ITEM_CHECKED_ROLE = 263,
        SETUP_LIST_ITEM_VALUE_ROLE = 264,
        SETUP_lIST_ITEM_DISTRIBUTIONMODE_ROLE = 267,
        SETUP_lIST_ITEM_FANSPEED_ROLE = 269,
        SETUP_lIST_ITEM_TEMPERATURE_ROLE = 270,
        SETUP_lIST_ITEM_LOADING_ROLE = 271,
    };
    Q_ENUM(ESetupRoles)

    /**
     * @brief The ESetupRoles enum: This enum contains all the possible air flow distribution modes
     */
    enum EAirFlowDistributionModes
    {
        SETUP_THEME_PRESETS_HVAC_DM_CHEST_MODE = 1,
        SETUP_THEME_PRESETS_HVAC_DM_CHESTLEG_MODE,
        SETUP_THEME_PRESETS_HVAC_DM_LEG_MODE,
        SETUP_THEME_PRESETS_HVAC_DM_LEGDEFROST_MODE,
        SETUP_THEME_PRESETS_HVAC_DM_DEFROST_MODE,
    };
    Q_ENUM(EAirFlowDistributionModes)

    /**
     * @brief The EDateTimeComponent enum: This enum contains component present in Date and time screen
     */
    enum EDateTimeComponent
    {
        SETUP_COMPONENT_DATE = 0,
        SETUP_COMPONENT_TIME_12_HR,
        SETUP_COMPONENT_TIME_24_HR,
    };
    Q_ENUM(EDateTimeComponent)

    /**
     * @brief The EThemePreset enum : This enum contains theme presets
     */
    enum EThemePreset
    {
        THEME_PRESET_INVALID = -1,
        THEME_PRESET_ZEN,
        THEME_PRESET_ZING,
        THEME_PRESET_ZEEL,
        THEME_PRESET_USER,
        THEME_PRESET_MAX,
    };
    Q_ENUM(EThemePreset)

    /**
     * @brief The EThemePresetColor enum : This enum contains theme preset colors
     */
    enum EThemePresetColor
    {
        THEME_PRESET_COLOR_INVALID = -1,
        THEME_PRESET_COLOR_0,
        THEME_PRESET_COLOR_1,
        THEME_PRESET_COLOR_2,
        THEME_PRESET_COLOR_3,
        THEME_PRESET_COLOR_4,
    };
    Q_ENUM(EThemePresetColor)

    /**
     * @brief The EParkAssist enum : This enum contains all options inside park assist screen used for validation.
     */
    enum EParkAssist
    {
        PARK_ASSIST_MIX_WITH_AUDIO = 0,
        PARK_ASSIST_TONE_VOLUME,
        PARK_ASSIST_DELAY_TIMER,
    };
    Q_ENUM(EParkAssist)

    /**
     * @brief The EParkAssist enum : This enum contains all options park assist tone type used for validation.
     */
    enum EParkAssistToneTypeItemId
    {
        PARK_ASSIST_TONE_1_ID   = 0,
        PARK_ASSIST_TONE_2_ID,
        PARK_ASSIST_TONE_3_ID,
    };
    Q_ENUM(EParkAssistToneTypeItemId)

    /**
     * @brief The EParkAssist enum : This enum contains all options park assist delay timer type used for validation.
     */
    enum EParkAssistDelayTimerItemId
    {
        PARK_ASSIST_DELAY_TIMER_SEC_0   = 0,
        PARK_ASSIST_DELAY_TIMER_SEC_5,
        PARK_ASSIST_DELAY_TIMER_SEC_10,
    };
    Q_ENUM(EParkAssistDelayTimerItemId)

    /**
     * @brief The EThemeSetup enum : This enum contains all options inside theme setup screen used for validation.
     */
    enum EThemeSetup
    {
        THEMESETUP_INVALID      = -1,
        THEMESETUP_CLIMATE,
        THEMESETUP_COLOR,
        THEMESETUP_LIGHTING,
        THEMESETUP_SOUND
    };
    Q_ENUM(EThemeSetup)

    /**
     * @brief The EParkAssist enum : This enum contains all options park assist delay timer type used for validation.
     */
    enum EApproachLampItemId
    {
        APPROACH_LAMP_SEC_30   = 0,
        APPROACH_LAMP_SEC_60,
        APPROACH_LAMP_SEC_90,
    };
    Q_ENUM(EApproachLampItemId)

    static void registerSetupEnumsToQML()
    {
        qmlRegisterType<CSetupEnums>("com.harman.qml.setupenums",1,0,"SetupEnums");
    }
};

/**
 * @brief ERequestState enum : This enum contains all necessary state of theme presets apply states used for validation.
 */
enum ERequestState
{
    EN_REQ_STATE_INVALID    =-1,
    EN_REQ_STATE_SENT          ,
    EN_REQ_STATE_ERROR         ,
    EN_REQ_STATE_IGNORED       ,
    EN_REQ_STATE_PROCESSED     ,
    EN_REQ_STATE_HOLD          ,
};

/**
 * @brief ERequestIndex enum : This enum contains indexes of all possible setttings in theme presets used for validation.
 */
enum ERequestIndex
{
    EN_REQ_INDEX_FANSPEED           =  0,
    EN_REQ_INDEX_TEMPERATURE            ,
    EN_REQ_INDEX_COLOR                  ,
    EN_REQ_INDEX_AMBIENTLIGHT           ,
    EN_REQ_INDEX_NOTIFICATION_VOLUME    ,
    EN_REQ_INDEX_AUDIO_PRESET           ,
    EN_REQ_INDEX_END                    ,
};


Q_DECLARE_METATYPE(CSetupEnums::ESetup)
Q_DECLARE_METATYPE(CSetupEnums::EBassMiddleTreble)
Q_DECLARE_METATYPE(CSetupEnums::EGeneralSetup)
Q_DECLARE_METATYPE(CSetupEnums::ESetupScreens)
Q_DECLARE_METATYPE(CSetupEnums::ESetupListItemTypes)
Q_DECLARE_METATYPE(CSetupEnums::EAirFlowDistributionModes)
Q_DECLARE_METATYPE(CSetupEnums::EDateTimeComponent)
Q_DECLARE_METATYPE(CSetupEnums::EThemePreset)
Q_DECLARE_METATYPE(CSetupEnums::EThemePresetColor)
Q_DECLARE_METATYPE(CSetupEnums::EParkAssist)
Q_DECLARE_METATYPE(CSetupEnums::EParkAssistToneTypeItemId)
Q_DECLARE_METATYPE(CSetupEnums::EParkAssistDelayTimerItemId)
Q_DECLARE_METATYPE(CSetupEnums::EThemeSetup)
Q_DECLARE_METATYPE(CSetupEnums::EApproachLampItemId)
Q_DECLARE_METATYPE(CSetupEnums::EAudioSetupCurrentScreen)
Q_DECLARE_METATYPE(CSetupEnums::EThemeSetupWithDriveModeItems)
Q_DECLARE_METATYPE(CSetupEnums::EThemesItem)
Q_DECLARE_METATYPE(CSetupEnums::EDriveModes)
Q_DECLARE_METATYPE(CSetupEnums::EAudioSetupPathViewCurrIndex)

#endif // CSETUPENUMS_H

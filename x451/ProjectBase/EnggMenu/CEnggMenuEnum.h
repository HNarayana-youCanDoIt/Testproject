/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggEventHandler.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande, Rajat Gupta
 * CEnggMenuEnum, file that contain enums that will be used in EnggMenu.
 */
#ifndef CENGGMENUENUM_H
#define CENGGMENUENUM_H

#include <QObject>
#include <QtQml>

class CEnggMenuEnum: public QObject
{
    Q_OBJECT
public:

    /**
     * @enum ELogResponse
     * @brief It contains response from service side i.e successful or failure.
     */
    enum ELogResponse
    {
        LOG_RESPONSE_SUCCESS = 0,
        LOG_RESPONSE_FAILURE = -1,
        LOG_RESPONSE_FILE_NOT_FOUND = 1
    };
    //________________________________________________________________________________________________


    /**
     * @enum EIpType
     * @brief Enum to check the type of IP
     */
    enum EIpType
    {
        IP_INVALID = -1,
        IP_STATIC = 1,
        IP_DYNAMIC = 2,
    };
    //________________________________________________________________________________________________
    /**
     * @enum EEnggMenuScreen
     * @brief It contains all the screens that will be shown in an EnggMenu Module
     */
    enum EEnggMenuScreen
    {
        ENGG_MENU_SCREEN_MAIN ,
        ENGG_MENU_SCREEN_TEST_MODE,

        ENGG_MENU_SCREEN_DRIVE_NEXT,
        ENGG_MENU_SCREEN_DRIVE_NEXT_LIB_UPDATE,
        ENGG_MENU_SCREEN_DRIVE_NEXT_CONFIG_UPDATE,
        ENGG_MENU_SCREEN_DRIVE_NEXT_DEBUG,
        ENGG_MENU_SCREEN_DRIVE_NEXT_LOG,
        ENGG_MENU_SCREEN_DRIVE_NEXT_LOGGING,
        ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS,
        ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_EFFICIENCY,
        ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_BRAKING,
        ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_ACCELERATION,
        ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GEAR_SHIFT,
        ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GENERIC,
        ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_SAFETY,

        ENGG_MENU_SCREEN_BUTTON_PANEL,
        ENGG_MENU_SCREEN_DEBUG_LOG,
        ENGG_MENU_SCREEN_ILLUMINATION,
        ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION,
        ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION,

        ENGG_MENU_SCREEN_SYSTEM_CONFIG,
        ENGG_MENU_SCREEN_SYSTEM_CONFIG_VIN,
        ENGG_MENU_SCREEN_SYSTEM_CONFIG_VC_NUMBER,
        ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R,
        ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_BUTTON_PANEL,
        ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_CONTAINER_PART,
        ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_DISPLAY_PART,
        ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_PARAM_PART,
        ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SILVERBOX_PART,
        ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SOFT_PART,

        ENGG_MENU_SCREEN_W3W_LAST_NAVIGATED,

        ENGG_MENU_SCREEN_PICTURE_VIEWER,
    };
    Q_ENUMS(EEnggMenuScreen)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggScreenType
     * @brief It contains diff screen types that will loaded accordingly.
     */
    enum EEnggScreenType
    {
        ENGG_MENU_SCREEN_TYPE_NULL = 0,
        ENGG_MENU_SCREEN_TYPE_LIST,
        ENGG_MENU_SCREEN_TYPE_PART_NO,
        ENGG_MENU_SCREEN_TYPE_ILLUMINATION_ADJUST,
        ENGG_MENU_SCREEN_TYPE_BUTTON_PANEL,
        ENGG_MENU_SCREEN_TYPE_PICTURE_VIEWER,
        ENGG_MENU_SCREEN_TYPE_DRIVENEXT_LIB_UPDATE,
        ENGG_MENU_SCREEN_TYPE_DRIVENEXT_CONFIG_UPDATE,
        ENGG_MENU_SCREEN_TYPE_LIST_5_ROWS,
        ENGG_MENU_SCREEN_TYPE_W3W_LAST_NAVIGATED,
    };
    Q_ENUMS(EEnggScreenType)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuItemType
     * @brief It contains diff types of List Component present in Engg Menu List which will change as per requirement.
     */
    enum EEnggMenuItemType
    {
        ENGG_MENU_ITEM_TYPE_NONE = -1,
        ENGG_MENU_ITEM_TYPE_LABEL ,
        ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL,
        ENGG_MENU_ITEM_TYPE_LABEL_WITH_SLIDER,
        ENGG_MENU_ITEM_TYPE_LABEL_WITH_CHECKBOX,
        ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON,
        ENGG_MENU_ITEM_TYPE_SYS_CONFIG,
        ENGG_MENU_ITEM_TYPE_TRACK_NAME,
        ENGG_MENU_ITEM_TYPE_DRIVE_NEXT_KEY_VALUE,
    };
    Q_ENUMS(EEnggMenuItemType)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuIdMainPage
     * @brief Contains ID of each List item present in EnggMenu Main Screen.
     */
    enum EEnggMenuIdMainPage
    {
        ENGG_MENU_ID_VIP_DID,
        ENGG_MENU_ID_TEST_MODE,
        ENGG_MENU_ID_DRIVE_NEXT,
        ENGG_MENU_ID_ILLUMINATION,
        ENGG_MENU_ID_BUTTON_PANEL,
        ENGG_MENU_ID_DEBUG_LOGS,
        ENGG_MENU_ID_SYSTEM_CONFIG,
        ENGG_MENU_ID_W3W_LAST_NAVIGATED,
        //Todo: needs to be removed
        ENGG_MENU_ID_PICTURE_VIEWER,
    };
    Q_ENUMS(EEnggMenuIdMainPage)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuIdIllumination
     * @brief Contains ID of each List item present in EnggMenu Illumination Screen.
     */
    enum EEnggMenuIdIllumination
    {
        ENGG_MENU_ID_DISPLAY_ILLUMINATION    ,
        ENGG_MENU_ID_BUTTON_PANEL_ILLUMINATION   ,

    };
    Q_ENUMS(EEnggMenuIdIllumination)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuIdSysConfig
     * @brief Contains ID of each List item present in EnggMenu System Configuration Screen.
     */
    enum EEnggMenuIdSysConfig
    {
        ENGG_MENU_ID_STEERING_WHEEL_CONTROLS   ,
        ENGG_MENU_ID_CURRENT_POWER_MODE_TYPES     ,
        ENGG_MENU_ID_AM_FM_ANTENNA_TYPES          ,
        ENGG_MENU_ID_MICROPHONE                   ,
        ENGG_MENU_ID_VIN                          ,
        ENGG_MENU_ID_VC_NUMBER                    ,
        ENGG_MENU_ID_ALL_16R_PART_NUMBERS
    };
    Q_ENUMS(EEnggMenuIdSysConfig)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuId16RPartNumber
     * @brief Contains ID of each List item present in EnggMenu 16R Part Number Screen.
     */

    enum EEnggMenuId16RPartNumber
    {

        ENGG_MENU_ID_CONTAINER_PART_NUMBER   ,
        ENGG_MENU_ID_SILVERBOX_PART_NUMER        ,
        ENGG_MENU_ID_DISPLAYHW_PART_NUMBER       ,
        ENGG_MENU_ID_BUTTON_PANEL_PART_NUMBER    ,
        ENGG_MENU_ID_SOFTWARE_PART_NUMBER        ,
        ENGG_MENU_ID_PARAMETERIZATION_PART_NUMBER,
    };
    Q_ENUMS(EEnggMenuId16RPartNumber)
    //________________________________________________________________________________________________


    /**
     * @enum EEnggMenuIdDebugLogs
     * @brief Contains ID of each List item present in EnggMenu Debug Logs Screen.
     */

    enum EEnggMenuIdDebugLogs
    {


        ENGG_MENU_ID_INVALID_LOG = -1,
        ENGG_MENU_ID_TEST_AUTOMATION ,
        ENGG_MENU_ID_STATIC_IP ,
        ENGG_MENU_ID_DEBUGS_LOG,
        ENGG_MENU_ID_EXTRACT_LOG ,
        ENGG_MENU_ID_DEVICE_MODE,

    };
    Q_ENUMS(EEnggMenuIdDebugLogs)


    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuIdTestMode
     * @brief Contains ID of each List item present in EnggMenu Test Mode.
     */
    enum EEnggMenuIdTestMode
    {
        ENGG_MENU_TEST_MODE,
        ENGG_MENU_TEST_MODE_TUNER,
        ENGG_MENU_TEST_MODE_AUDIO_MEDIA,
        ENGG_MENU_TEST_MODE_VIDEO_MEDIA,
    };
    Q_ENUMS(EEnggMenuIdTestMode)
    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuIdTestModeTuner
     * @brief Contains ID of each List item present in EnggMenu Test Mode - Tuner Screen.
     */

    enum EEnggMenuIdTestModeTuner
    {
        ENGG_MENU_ID_TUNER_STATION_NAME ,
        ENGG_MENU_ID_TUNER_FREQUENCY,
        ENGG_MENU_ID_TUNER_SIGNAL_STRENGTH,
        ENGG_MENU_ID_TUNER_MULTI_PATH,
        ENGG_MENU_ID_TUNER_VEHICLE_SPEED,
        ENGG_MENU_ID_TUNER_CURRENT_VOLUME_LEVEL,

    };
    Q_ENUMS(EEnggMenuIdTestModeTuner)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuIdTestModeAudioMedia
     * @brief Enums of the parameters present in Audio Media list.
     */
    enum EEnggMenuIdTestModeAudioMedia
    {
        ENGG_MENU_ID_AUDIO_TRACK_NAME ,
        ENGG_MENU_ID_AUDIO_BIT_RATE,
        ENGG_MENU_ID_AUDIO_SAMPLING_RATE,
        ENGG_MENU_ID_AUDIO_VEHICLE_SPEED,
        ENGG_MENU_ID_AUDIO_CURRENT_VOLUME_LEVEL,
    };
    Q_ENUMS(EEnggMenuIdTestModeAudioMedia)
    //________________________________________________________________________________________________
    /**
     * @enum EAppTestAutomationStatus
     * @brief Enum to check the status of test Automation i.e enable/disable
     */
    enum EAppTestAutomationStatus
    {
        TEST_AUTOMATION_INVALID = -1,
        TEST_AUTOMATION_DISABLE,
        TEST_AUTOMATION_ENABLE,
    };

    /**
     * @enum EEnggMenuIdTestModeVideoMedia
     * @brief Enums of the parameters present in Video Media list.
     */
    enum EEnggMenuIdTestModeVideoMedia
    {
        ENGG_MENU_ID_VIDEO_TRACK_NAME ,
        ENGG_MENU_ID_VIDEO_VIDEO_FORMAT,
        ENGG_MENU_ID_VIDEO_VIDEO_CODEC,
        ENGG_MENU_ID_VIDEO_VIDEO_RESOLUTION,
        ENGG_MENU_ID_VIDEO_VIDEO_FRAME_RATE,
        ENGG_MENU_ID_VIDEO_AUDIO_CODEC,
        ENGG_MENU_ID_VIDEO_AUDIO_SAMPLING_RATE,
        ENGG_MENU_ID_VIDEO_VEHICLE_SPEED,
        ENGG_MENU_ID_VIDEO_CURRENT_VOLUME_LEVEL,
    };
    Q_ENUMS(EEnggMenuIdTestModeVideoMedia)
    //________________________________________________________________________________________________

    /**
      * @enum EEnggMenuDeviceMode
      * @brief Device Mode can be in two states  1. Device Mode 2.Host Mode
      */
    enum EEnggMenuDeviceMode
    {
        DEVICE_MODE = 0,
        HOST_MODE = 1
    };
    Q_ENUMS(EEnggMenuDeviceMode)
    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuExtractLogsStatus
     * @brief Enum to check the return status of extract logs
     */
    enum EEnggMenuExtractLogsStatus
    {
        LOGS_SUCCESS = 0,
        USB_NOT_CONNECTED = 1,
        LOGGING_NOT_ENABLED = 2,
        USB_DEVICE_FULL = 3
    };

    Q_ENUMS(EEnggMenuExtractLogsStatus)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuDriveNextMenu
     * @brief Contains ID of each List item present in EnggMenu DriveNext Menu Selection Screen.
     */

    enum EEnggMenuDriveNextMenu
    {
        ENGG_MENU_ID_DRIVE_NEXT_LIB_UPDATE = 0,
        ENGG_MENU_ID_DRIVE_NEXT_CONFIG_UPDATE,
        ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL,
        ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP,
        ENGG_MENU_ID_DRIVE_NEXT_LOGGING,
        ENGG_MENU_ID_DRIVE_NEXT_EXPORT_LOG,
        ENGG_MENU_ID_DRIVE_NEXT_TRIP
    };
    Q_ENUMS(EEnggMenuDriveNextMenu)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuDriveNextDebugLevel
     * @brief Contains ID of each List item present in EnggMenu DriveNext Debug Level Selection Screen.
     */

    enum EEnggMenuDriveNextDebugLevel
    {
        ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_UNKNOWN = -1,
        ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_0,
        ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_1,
        ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_2,
        ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_3,
        ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_TOTAL_COUNT
    };
    Q_ENUMS(EEnggMenuDriveNextDebugLevel)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuDriveNextLogTrip
     * @brief Contains ID of each List item present in EnggMenu DriveNext Trip Selection for Log Screen.
     */

    enum EEnggMenuDriveNextLogTrip
    {
        ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_UNKNOWN = -1,
        ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_OVERALL,
        ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_CURRENT,
        ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_A,
        ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_B,
        ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_ALL,
        ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_TOTAL_COUNT
    };
    Q_ENUMS(EEnggMenuDriveNextLogTrip)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuDriveNextLoggingLocation
     * @brief Contains ID of each List item present in EnggMenu DriveNext Trip Logging Location Selection Screen.
     */

    enum EEnggMenuDriveNextLoggingLocation
    {
        ENGG_MENU_ID_DRIVE_NEXT_LOGGING_UNKNOWN = -1,
        ENGG_MENU_ID_DRIVE_NEXT_LOGGING_INTERNAL,
        ENGG_MENU_ID_DRIVE_NEXT_LOGGING_USB,
        ENGG_MENU_ID_DRIVE_NEXT_LOGGING_TOTAL_COUNT
    };
    Q_ENUMS(EEnggMenuDriveNextLoggingLocation)

    //________________________________________________________________________________________________

    /**
     * @enum EEnggMenuDriveNextDetails
     * @brief Contains ID of each List item present in EnggMenu DriveNext Trips Selection Screen.
     */

    enum EEnggMenuDriveNextDetails
    {
        ENGG_MENU_ID_DRIVE_NEXT_DETAILS_UNKNOWN = -1,
        ENGG_MENU_ID_DRIVE_NEXT_DETAILS_EFFICIENCY,
        ENGG_MENU_ID_DRIVE_NEXT_DETAILS_BRAKING,
        ENGG_MENU_ID_DRIVE_NEXT_DETAILS_ACCELERATION,
        ENGG_MENU_ID_DRIVE_NEXT_DETAILS_GEAR_SHIFT,
        ENGG_MENU_ID_DRIVE_NEXT_DETAILS_GENERIC,
        ENGG_MENU_ID_DRIVE_NEXT_DETAILS_SAFETY,
        ENGG_MENU_ID_DRIVE_NEXT_DETAILS_TOTAL_COUNT
    };
    Q_ENUMS(EEnggMenuDriveNextDetails)

    //________________________________________________________________________________________________

    static void registerEnggMenuEnumsToQML()
    {
        qmlRegisterType<CEnggMenuEnum>("com.harman.qml.enggMenuenums",1,0,"EnggMenuEnums");
    }
};

Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuScreen)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggScreenType)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuItemType)

Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuIdMainPage)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuIdIllumination)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuIdSysConfig)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuId16RPartNumber)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuIdDebugLogs)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuIdTestModeTuner)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuIdTestModeAudioMedia)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuIdTestModeVideoMedia)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuDeviceMode)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuExtractLogsStatus)

Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuDriveNextMenu)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuDriveNextDebugLevel)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuDriveNextLogTrip)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuDriveNextLoggingLocation)
Q_DECLARE_METATYPE(CEnggMenuEnum::EEnggMenuDriveNextDetails)

#endif // CENGGMENUENUM_H

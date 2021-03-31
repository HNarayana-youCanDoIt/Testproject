/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CPopupEnum.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* CPopupEnum    Class that would contain all the Enums related to Popup Manager
*               that would be registered as a QML Type so that these could be used in QML too.
*/

#ifndef CPOPUPENUM_H
#define CPOPUPENUM_H

#include <QObject>
#include <QtQml>
#include "CPopupEnum.h"
/**
 * @class CPopupEnum
 * @brief Class that would contain all the Enums related to Popup Manager
 *        that would be registered as a QML Type so that these could be used in QML too.
 */
class CPopupEnum : public QObject
{
    Q_OBJECT
public:
    // Enums to be added for all the Popups here
    /**
     * Enums of all the popup Ids
     */
    enum EPopupID{
        EN_POPUPID_UNKNOWN = 0,

        EN_POPUPID_USB_CONNECTED,
        EN_POPUPID_USB_DISCONNECTED,
        EN_POPUPID_NO_USB_CONNECTED,
        EN_POPUPID_IPOD_CONNECTED,
        EN_POPUPID_IPOD_DISCONNECTED,
        EN_POPUPID_AUX_CONNECTED,
        EN_POPUPID_AUX_DISCONNECTED,
        EN_POPUPID_BTAUDIO_CONNECTED,
        EN_POPUPID_BTAUDIO_DISCONNECTED,
        EN_POPUPID_MEDIA_EMPTY_CATEGORY,
        EN_POPUPID_MEDIA_EMPTY_DEVICE_CONNECTED,
        EN_POPUPID_USB_DEVICE_ERROR_CONNECTED,
        EN_POPUPID_USB_ONLY_VIDEO_CONFIRMATION,
        EN_POPUPID_USB_ONLY_IMAGE_CONFIRMATION,
        EN_POPUPID_USB_SPEED_LOCKOUT_VIDEO,
        EN_POPUPID_USB_SPEED_LOCKOUT_IMAGES,
        EN_POPUPID_USB_CORRUPT_VIDEO,

        EN_POPUPID_IMAGE_NOT_FOUND,
        EN_POPUPID_IMAGE_CONFIRMATION,
        EN_POPUPID_TURN_IGN_OFF,
        EN_POPUPID_LOW_BATTERY,
        EN_POPUPID_PACKAGE_VALIDATION_FAILED,
        EN_POPUPID_VALIDATION_IN_PROGRESS,
        EN_POPUPID_MSD_DISCONNECTED,
        EN_POPUPID_HOME_EDIT_SHORTCUT,
        EN_POPUPID_AUDIO_PRESETS_LIST,
        EN_POPUPID_VERSION_MISMATCH,
        /****************************
         * Phone Setup Popups
        ****************************/
        EN_POPUPID_PHONE_SETUP_DEVICE_LIMIT_REACHED,
        EN_POPUPID_PHONE_SETUP_TURN_ON_BLUETOOTH,
        EN_POPUPID_PHONE_SETUP_BT_DEVICES_NOT_FOUND,
        EN_POPUPID_PHONE_SETUP_PREVIOUS_DEVICE_DISCONNECTION,
        EN_POPUPID_PHONE_SETUP_PASSKEY,
        EN_POPUPID_PHONE_SETUP_EXTERNAL_PAIRING_REQUEST,
        EN_POPUPID_PHONE_SETUP_PAIRING_FAILED,
        EN_POPUPID_PHONE_SETUP_DETERMINING_BT_SERVICES,
        EN_POPUPID_PHONE_SETUP_CONNECTING,
        EN_POPUPID_PHONE_SETUP_CONNECTED,
        EN_POPUPID_PHONE_SETUP_CONNECTION_FAILED,
        EN_POPUPID_PHONE_SETUP_DISCONNECTING,
        EN_POPUPID_PHONE_SETUP_DISCONNECTED,
        EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_CONFIRMATION,
        EN_POPUPID_PHONE_SETUP_DELETING_DEVICE,
        EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_SUCCESS,
        EN_POPUPID_PHONE_SETUP_DELETE_DEVICE_FAILED,
        EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_CONFIRMATION,
        EN_POPUPID_PHONE_SETUP_DELETING_ALL_DEVICES,
        EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_SUCCESS,
        EN_POPUPID_PHONE_SETUP_DELETE_ALL_DEVICES_FAILED,
        EN_POPUPID_PHONE_SETUP_ONLY_A2DP_CONNECTED,
        EN_POPUPID_PHONE_SETUP_DEVICE_BATTERY_LOW,

        /****************************
         * Android Auto Popups
         ****************************/
        EN_POPUPID_AA_FIRST_RUN,
        EN_POPUPID_AA_SESSION_CLOSED,
        EN_POPUPID_AA_CONNECT_YOUR_PHONE,
        EN_POPUPID_AA_MAX_DEVICES_PAIRED,
        EN_POPUPID_AA_NAVIGATION_DETAILS,
        EN_POPUPID_PROJECTION_ERROR,

        /****************************
         * Phone Call Popups
        ****************************/
        EN_POPUPID_PHONE_INCOMING_CALL_POPUP,
        EN_NO_NETWORK_AVAILABLE,
        EN_POPUPID_LOW_PRIORITY_CALL_POPUP,

        /****************************
         * Phone SMS Popups
        ****************************/
        EN_POPUPID_PHONE_INCOMING_SMS_POPUP,
        EN_POPUPID_PHONE_SMS_READING_POPUP,
        EN_POPUPID_PHONE_SMS_READING_COMPLETE_POPUP,
        EN_POPUPID_LOW_PRIORITY_SMS_POPUP,
        EN_POPUPID_PHONE_SENDING_SMS,
        EN_POPUPID_PHONE_SMS_SENT,

        /**********************************
         * Display Off confirmation Popup
         *********************************/
        EN_POPUPID_DISPLAY_OFF_CONFIRMATION,
        EN_POPUPID_DISPLAY_OFF_TRANSPARENT,

        /****************************
         * Setup Popups
        ****************************/

        EN_POPUPID_SETUP_FACTORY_RESET_CONFIRMATION_STATUS,
        EN_POPUPID_SETUP_FACTORY_RESET_IGNITION_ON_STATUS,
        EN_POPUPID_SETUP_FACTORY_RESET_WAITING_STATUS,
        EN_POPUPID_SETUP_FACTORY_RESET_SUCCESSFUL_STATUS,
        EN_POPUPID_SETUP_FACTORY_RESET_DISABLE,
        EN_POPUPID_SETUP_THEME_ACTIVATED_SUCCESSFUL_STATUS,
        EN_POPUPID_SETUP_VEHICLE_SETTING_CANNOT_UPDATE_POPUP,
        EN_POPUPID_SETUP_PARK_LAMP_TURN_ON_STATUS,
        EN_POPUPID_SETUP_CLIMATE_TURN_ON_STATUS,

        /****************************
         * AppleCarPlay Popups
         ****************************/
        EN_POPUPID_APPLE_CARPLAY_SESSION_CLOSED,
        EN_POPUPID_APPLE_CARPLAY_CONNECTION,
        EN_POPUPID_APPLE_CARPLAY_CONNECT_YOUR_PHONE,

        /****************************
         * Phone Browse Popups
        ****************************/
        EN_POPUPID_PHONE_BROWSE_FAVORITE_ADDED,
        EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVED,
        EN_POPUPID_PHONE_BROWSE_FAVORITE_REMOVE_CONFIRMATION,
        EN_POPUPID_PHONE_BROWSE_FAVORITE_LIST_FULL,
        EN_POPUPID_PHONE_BROWSE_ADD_FAVORITE_FAILED,
        EN_POPUPID_PHONE_BROWSE_REMOVE_FAVORITE_FAILED,

        /**************************************
         * Voice Alert Notification
         * ***********************************/
        EN_POPUPID_VOICE_ALERT_NOTIFICATION,

        /**********************************
         * Tuner Popups
         *********************************/
        EN_POPUPID_NO_VALID_STATION_FOUND_POPUP,
        EN_POPUPID_TUNER_ANTENNA_NOT_CONNECTED_POPUP,

        /****************************
         * One Hour Mode Popups
        ****************************/
        EN_POPUPID_ONE_HOUR_MODE_ENTRY_POPUP,

        /****************************
         * VR Popups
         ****************************/
        EN_MIC_NOT_AVAILABLE_POPUP,
        EN_VR_NOT_AVAILABLE_POPUP,

        /****************************
        * PowerMode Popups
        ****************************/
       EN_POPUPID_POWERMODE_ONE_HOUR_MODE_EXPIRY,

        /****************************
         * RCA Popups
         ****************************/
        EN_POPUPID_RCA_AUX_GAIN,
        EN_POPUPID_RCA_AUDIO_PRESET,
        EN_POPUPID_RCA_BMT,
        EN_POPUPID_RCA_BALANCE_FADER,

        /****************************
         * EnggMenu Popups
         ****************************/
        EN_POPUPID_ENGGMENU_USB_NOT_CONNECTED,
        EN_POPUPID_ENGGMENU_LOGGING_NOT_ENABLED,
        EN_POPUPID_ENGGMENU_USB_DEVICE_FULL,

        /****************************
         * AntiTheft Popup
         ****************************/
        EN_POPUPID_VEHICLE_ANTITHEFT_AUTHENTICATION_FAILED_POPUP,

        /****************************
         * Phone Bt VR Popup
         ****************************/
        EN_BT_VR_NOT_AVAILABLE_POPUP,

        /****************************
         * DriveNext Popup
         ****************************/
        EN_POPUPID_DN_FILE_UPDATE_FAILED,
        EN_POPUPID_DN_FILE_UPDATE_SUCCESS,
        EN_POPUPID_DN_CAN_NOT_RESET,
        EN_POPUPID_DN_RESET_ALL_CONFIRMATION,
        EN_POPUPID_DN_RESET_ALL_FAILED,
        EN_POPUPID_DN_RESET_ALL_SUCCESS,
        EN_POPUPID_DN_RESET_TRIP_A_CONFIRMATION,
        EN_POPUPID_DN_RESET_TRIP_B_CONFIRMATION,
        EN_POPUPID_DN_RESET_TRIP_FAILED,
        EN_POPUPID_DN_RESET_TRIP_SUCCESS,

        /****************************
         * Phone W3W Popups
         ****************************/
        EN_POPUPID_W3W_SHARE_ADDRESS,
        EN_POPUPID_W3W_ADDRESS_SHARED,
        EN_POPUPID_W3W_SET_FAVORITE,
        EN_POPUPID_W3W_FAVORITE_SAVED,
        EN_POPUPID_W3W_AA_CP_NOT_CONNECTED,
		EN_POPUPID_W3W_CONNECTNEXT_NOT_CONNECTED,
        EN_POPUPID_W3W_DELETE_FAVORITE,
        EN_POPUPID_W3W_DELETE_RECENT,
        EN_POPUPID_W3W_ADDRESS_DELETED,
        EN_POPUPID_W3W_FAVORITE_MAX_LIMIT,
        EN_POPUPID_W3W_FAVORITE_ALREADY_SAVED,
        EN_POPUPID_W3W_INVALID_ADDRESS,
        EN_POPUPID_W3W_HFP_NOT_CONNECTED,
        EN_POPUPID_W3W_SMS_NOT_SUPPORTED,
        EN_POPUPID_W3W_ALLOW_AUTOLAUNCH_AA,
        EN_POPUPID_W3W_ALLOW_AUTOLAUNCH_CP,

        /****************************
         * Doodle Popups
         ****************************/
        EN_POPUPID_DOODLE_MYSTICKER_ICON,
        EN_POPUPID_DOODLE_MYSTICKER_ICON_PREVIEW,
        EN_POPUPID_DOODLE_STARTUP_IMAGE_PREVIEW,
        EN_POPUPID_DOODLE_MYSTICKER_NOT_CONFIGURED,
        EN_POPUPID_DOODLE_MYSTICKER_ACTIVATED,
        EN_POPUPID_DOODLE_MYSTICKER_CLEAR_POPUP,
        EN_POPUPID_DOODLE_MYSTICKER_UPDATE,
        EN_POPUPID_DOODLE_STARTUPIMAGE_NOT_CONFIGURED,
        EN_POPUPID_DOODLE_STARTUPIMAGE_ACTIVATED,
        EN_POPUPID_DOODLE_STARTUPIMAGE_CLEAR_POPUP,
        EN_POPUPID_DOODLE_STARTUPIMAGE_UPDATE
    };
    Q_ENUMS(EPopupID)

    /**
     * Enums for popup display zone
     */
    enum EPopupZone{
        EN_POPUP_ZONE_NONE = 0,
        EN_POPUP_ZONE_TWO = 2,
        EN_POPUP_ZONE_FOUR = 4,
    };
    Q_ENUMS(EPopupZone)

    /**
     * Enums for popup priority
     */
    enum EPopupPriority{
        EN_POPUP_PRIORITY_NONE = 0,
        EN_POPUP_PRIORITY_ONE,
        EN_POPUP_PRIORITY_TWO,
        EN_POPUP_PRIORITY_THREE,
        EN_POPUP_PRIORITY_FOUR,
        EN_POPUP_PRIORITY_FIVE,
        EN_POPUP_PRIORITY_SIX,
        EN_POPUP_PRIORITY_SEVEN,
        EN_POPUP_PRIORITY_EIGHT,
    };
    Q_ENUMS(EPopupPriority)

    /**
     * Enums for popup applicable contexts
     */
    enum EPopupApplicableContext{
        EN_HMI_INVALID_CONTEXT = 0,
        EN_HMI_MEDIA_CONTEXT,
        EN_HMI_TUNER_CONTEXT,
        EN_HMI_PHONE_CONTEXT,
        EN_HMI_PHONE_CALL_CONTEXT,
        EN_HMI_SETUP_CONTEXT,
        EN_HMI_HOME_CONTEXT,
        EN_HMI_MEDIA_OFF_CONTEXT,
        EN_HMI_ENGG_MENU_CONTEXT,
        EN_HMI_SOFTWARE_UPDATE_CONTEXT,
        EN_HMI_PDC_RVC_CONTEXT,
        EN_HMI_ANDROID_AUTO_CONTEXT,
        EN_HMI_APPLE_CARPLAY_CONTEXT,
        EN_HMI_SAL_CONTEXT,
        EN_HMI_EARLY_WAKEUP_CONTEXT,
        EN_HMI_STARTUP_ANIMATION_CONTEXT,
        EN_HMI_VR_PICKLIST_CONTEXT,
        EN_HMI_VR_HELP_CONTEXT,
        EN_HMI_DRIVE_NEXT_CONTEXT,
        EN_HMI_PHONE_SETUP_CONTEXT,
        EN_HMI_W3W_CONTEXT,
        EN_HMI_DOODLE_SETUP_CONTEXT,
        HMI_SOUNDDEMO_CONTEXT
    };
    Q_ENUMS(EPopupApplicableContext)

    /**
     * Enums for popup result
     */
    enum EPopupResult{
        EN_POPUP_RESULT_INVALID = -1,
        EN_POPUP_RESULT_DISPLAYED,
        EN_POPUP_RESULT_IGNORED,
        EN_POPUP_RESULT_CLOSED_ON_TIMEOUT,
        EN_POPUP_RESULT_CLOSED_ON_TOUCH,
        EN_POPUP_RESULT_CLOSED_ON_HK,
        EN_POPUP_RESULT_CLOSED_ON_SUPERSEDE,
        EN_POPUP_RESULT_CLOSED_ON_CONTEXT_CHANGE,
        EN_POPUP_RESULT_CLOSED_ON_CLOSE_REQUEST,
        EN_POPUP_RESULT_CLOSED_ON_FORCE_CLOSE_REQUEST,
        EN_POPUP_RESULT_CLOSED_ON_POPUP_BTN_PRESS,
        EN_POPUP_RESULT_CLOSED_ON_CLOSE_ALL_POPUPS,
    };
    Q_ENUMS(EPopupResult)

    /**
     * @brief Method to register CPopupEnum as a QML Type
     * @param void
     * @return void
     */
    static void registerPopupEnumToQML()
    {
        qmlRegisterType<CPopupEnum>("com.harman.qml.popupenums",1,0,"PopupEnum");
    }
};

Q_DECLARE_METATYPE(CPopupEnum::EPopupID)
Q_DECLARE_METATYPE(CPopupEnum::EPopupZone)
Q_DECLARE_METATYPE(CPopupEnum::EPopupPriority)
Q_DECLARE_METATYPE(CPopupEnum::EPopupResult)
Q_DECLARE_METATYPE(CPopupEnum::EPopupApplicableContext)

#endif // CPOPUPENUM_H

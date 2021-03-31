/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CAudioEnums.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * This class is to handle Audio settings functionality.
 */

#ifndef CAUDIOENUMS_H
#define CAUDIOENUMS_H

#include <QObject>
#include <QtQml>

/**
 * @brief The CAudioEnums class: This class contains all the enums related to Audio module
 */
class CAudioEnums : public QObject
{
    Q_OBJECT
public:


    /**
     * @enum EAudioEntertainmentSrcs
     * @brief Enum for entertainment sources will be used to set active entertainment sources when user request for active source
     */
    enum EAudioEntertainmentSrcs
    {
        SRC_ENT_UNKNOWN = 0,
        SRC_TUNER_FM = 35,
        SRC_TUNER_AM = 36,
        SRC_TUNER_DAB = 37,
        SRC_TUNER_LW = 39,
        SRC_TUNER_MW = 40,
        SRC_TUNER_SW = 41,
        SRC_TUNER_WB = 42,
        SRC_TUNER_SDARS = 43,
        SRC_CDA = 45,
        SRC_DVDA = 48,
        SRC_DVDV = 50,
        SRC_HDD = 54,
        SRC_USB1 = 55,
        SRC_USB2 = 56,
        SRC_SD_CARD = 57,
        SRC_AUDIO_AUX = 60,
        SRC_BT_A2DP1 = 65,
        SRC_BT_A2DP2 = 66,
        SRC_CARPLAY_MEDIA = 76,
        SRC_GAL_MEDIA = 77,
        SRC_CARLIFE_MEDIA = 78,
        SRC_MIRRORLINK_MEDIA = 79,
        SRC_IPOD = 82,
        SRC_APPLINK_MEDIA = 88,
        SRC_AUDIO_OFF = 97,
        SRC_TUNER_DRM = 98,
        SRC_SAL_MEDIA = 100,
    };
    Q_ENUM(EAudioEntertainmentSrcs)

    /**
     * @brief The EVolumeUpdateGroup enum is having the groups of volume update.
     */
    enum EVolumeUpdateGroup
    {
        EN_VOLUME_UPDATE_GROUP_UNKNOWN = 0,
        EN_VOLUME_UPDATE_GROUP_NOUPDATE = 2,
        EN_VOLUME_UPDATE_GROUP_ENT = 3,
        EN_VOLUME_UPDATE_GROUP_VR = 4,
        EN_VOLUME_UPDATE_GROUP_PROMPT = 5,
        EN_VOLUME_UPDATE_GROUP_PHONE = 6,
        EN_VOLUME_UPDATE_GROUP_TA = 7,
        /*
         *  This is not coming from AudioManger, This is created for internal
         *  purpose of HMI.
         */
        EN_VOLUME_UPDATE_GROUP_PDC_RVC = 8,
    };
    Q_ENUM(EVolumeUpdateGroup)

    /**
     * @brief The EAudioInterruptSources enum holds all Interrupt sources.
     */
    enum EAudioInterruptSources
    {
        SRC_SERVICE_CALL = 1,
        SRC_VOICERECORDER = 2,
        SRC_TTS = 4,
        SRC_NAV = 5,
        SRC_ETC_WARNING = 6,
        SRC_ETC_INFO = 7,
        SRC_TEL_HANDSFREE = 8,
        SRC_TEL_RINGING = 9,
        SRC_CARPLAY_PHONE = 10,
        SRC_CARPLAYPHONE_RINGING = 11,
        SRC_CARPLAY_SIRI = 12,
        SRC_CARPLAY_ALT = 13,
        SRC_GAL_VOICE = 16,
        SRC_GAL_NAVI = 17,
        SRC_GAL_UI = 18,
        SRC_GAL_VR = 19,
        SRC_CARLIFE_NAVI = 22,
        SRC_CARLIFE_VR = 23,
        SRC_MIRRORLINK_VR = 24,
        SRC_APPLINK_NAVI = 89,
        SRC_APPLINK_VR = 90,
        SRC_APPLINK_TTS = 99,
        SRC_TUNER_TA = 33,
        SRC_TUNER_DAB_TA = 34,
        SRC_MANUAL_MUTE = 87,
        SRC_KEYPADTOUCH = 30,
        SRC_ECALL_PHONE = 91,
        SRC_ECALL_PROMPT = 92,
        SRC_MIC = 95,
        SRC_TESTTONE = 96,
        SRC_TOUCHBEEP = 31,
        SRC_CONFIRMATION = 27,
        SRC_INDICATION = 28,
        SRC_WARNING = 29,
        SRC_RECORDED_PLAYBACK = 104,
        SRC_TUNER_PTY_NEWS = 106,
        SRC_INTERRUPT_UNKNOWN = 562
    };
    Q_ENUM(EAudioInterruptSources)

    enum EAudioPresets
    {
        AUDIO_PRESET_FLAT,
        AUDIO_PRESET_ROCK,
        AUDIO_PRESET_POP,
        AUDIO_PRESET_JAZZ,
        AUDIO_PRESET_CLASSIC,
        AUDIO_PRESET_HIPHOP,
        AUDIO_PRESET_CUSTOM,
        AUDIO_PRESET_DEFAULT
    };
    Q_ENUM(EAudioPresets)

    enum EAuxInGain
    {
        AUXINGAIN_LOW = 0,
        AUXINGAIN_MID = 1,
        AUXINGAIN_HIGH = 2
    };
    Q_ENUM(EAuxInGain)

    enum EToggleDirection
    {
        TOGGLE_PREVIOUS = 0,
        TOGGLE_NEXT = 1
    };
    Q_ENUM(EToggleDirection)

    /**
      * @enum   EAudioSourceCategory
      * @brief  This enum shall hold the values supported for audio source category.
      */
    enum EAudioSourceCategory
    {
        SOURCE_CATEGORY_UNKNOWN = 0,
        SOURCE_CATEGORY_TUNER,
        SOURCE_CATEGORY_MEDIA,
        SOURCE_CATEGORY_AUX,
        SOURCE_CATEGORY_PROJECTION
    };

    /**
         * @brief eBeepType : enum for type of beep
         */
    enum EBeepType
    {
        BEEP_TYPE_PDC_1 = 0,
        BEEP_TYPE_PDC_2,
        BEEP_TYPE_RINGTONE_1,
        BEEP_TYPE_RINGTONE_2,
        BEEP_TYPE_CONFIRM,
        BEEP_TYPE_CANCEL,
        BEEP_TYPE_TOUCH,
        BEEP_TYPE_TRIGGER,
        BEEP_TYPE_GONG,
        BEEP_TYPE_BEEP_PDC_1
    };
    Q_ENUM(EBeepType)

    /**
     * @enum ESourceId
     * @brief Enum for all the sources including entertainment and interrupt sources
     */
    enum ESourceId
    {
        /* Entertainment sources */
        EN_ENT_SOURCE_UNKNOWN                 = 0,
        EN_ENT_SOURCE_TUNER_FM                = 35,
        EN_ENT_SOURCE_TUNER_AM                = 36,
        EN_ENT_SOURCE_TUNER_DAB               = 37,
        EN_ENT_SOURCE_TUNER_LW                = 39,
        EN_ENT_SOURCE_TUNER_MW                = 40,
        EN_ENT_SOURCE_TUNER_SW                = 41,
        EN_ENT_SOURCE_TUNER_WB                = 42,
        EN_ENT_SOURCE_TUNER_SDARS             = 43,
        EN_ENT_SOURCE_CDA                     = 45,
        EN_ENT_SOURCE_DVDA                    = 48,
        EN_ENT_SOURCE_DVDV                    = 50,
        EN_ENT_SOURCE_USB1                    = 55,
        EN_ENT_SOURCE_USB2                    = 56,
        EN_ENT_SOURCE_SD_CARD                 = 57,
        EN_ENT_SOURCE_AUDIO_AUX               = 60,
        EN_ENT_SOURCE_BT_A2DP1                = 65,
        EN_ENT_SOURCE_BT_A2DP2                = 66,
        EN_ENT_SOURCE_CARPLAY_MEDIA           = 76,
        EN_ENT_SOURCE_GAL_MEDIA               = 77,
        EN_ENT_SOURCE_CARLIFE_MEDIA           = 78,
        EN_ENT_SOURCE_MIRRORLINK_MEDIA        = 79,
        EN_ENT_SOURCE_IPOD                    = 82,
        EN_ENT_SOURCE_APPLINK_MEDIA           = 88,
        EN_ENT_SOURCE_AUDIO_OFF               = 97,
        EN_ENT_SOURCE_TUNER_DRM               = 98,
        EN_ENT_SOURCE_SAL_MEDIA               = 100,
        /* Interrupt sources */
        EN_INT_SOURCE_SERVICE_CALL            = 1,
        EN_INT_SOURCE_VOICERECORDER           = 2,
        EN_INT_SOURCE_TTS                     = 4,
        EN_INT_SOURCE_NAV                     = 5,
        EN_INT_SOURCE_ETC_WARNING             = 6,
        EN_INT_SOURCE_ETC_INFO                = 7,
        EN_INT_SOURCE_TEL_HANDSFREE           = 8,
        EN_INT_SOURCE_TEL_RINGING             = 9,
        EN_INT_SOURCE_CARPLAY_PHONE           = 10,
        EN_INT_SOURCE_CARPLAYPHONE_RINGING    = 11,
        EN_INT_SOURCE_CARPLAY_SIRI            = 12,
        EN_INT_SOURCE_CARPLAY_ALT             = 13,
        EN_INT_SOURCE_GAL_VOICE               = 16,
        EN_INT_SOURCE_GAL_NAVI                = 17,
        EN_INT_SOURCE_GAL_UI                  = 18,
        EN_INT_SOURCE_GAL_VR                  = 19,
        EN_INT_SOURCE_CARLIFE_NAVI            = 22,
        EN_INT_SOURCE_CARLIFE_VR              = 23,
        EN_INT_SOURCE_MIRRORLINK_VR           = 24,
        EN_INT_SOURCE_APPLINK_NAVI            = 89,
        EN_INT_SOURCE_APPLINK_VR              = 90,
        EN_INT_SOURCE_APPLINK_TTS             = 99,
        EN_INT_SOURCE_TUNER_TA                = 33,
        EN_INT_SOURCE_TUNER_DAB_TA            = 34,
        EN_INT_SOURCE_MANUAL_MUTE             = 87,
        EN_INT_SOURCE_KEYPADTOUCH             = 30,
        EN_INT_SOURCE_ECALL_PHONE             = 91,
        EN_INT_SOURCE_ECALL_PROMPT            = 92,
        EN_INT_SOURCE_MIC                     = 95,
        EN_INT_SOURCE_TESTTONE                = 96,
        EN_INT_SOURCE_TOUCHBEEP               = 31,
        EN_INT_SOURCE_CONFIRMATION            = 27,
        EN_INT_SOURCE_INDICATION              = 28,
        EN_INT_SOURCE_WARNING                 = 29,
        EN_INT_SOURCE_RECORDED_PLAYBACK       = 104,
        EN_INT_SOURCE_TUNER_PTY_NEWS          = 106,
        EN_INT_SOURCE_UNKNOWN                 = 562
    };
    Q_ENUM(ESourceId)

    /**
     * @enum ESourceState
     * @brief Enum for source(entertainment and interrupt) state
     */
    enum ESourceState
    {
        EN_SOURCE_STATE_UNKNOWN,
        EN_SOURCE_STATE_CONNECTING,
        EN_SOURCE_STATE_CONNECTED,
        EN_SOURCE_STATE_DISCONNECTING,
        EN_SOURCE_STATE_DISCONNECTED,
        EN_SOURCE_STATE_SUSPENDED,
        EN_SOURCE_STATE_MAX
    };
    Q_ENUM(ESourceState)

    /**
     * @brief The EAuxConnectionStatus enum - Enum for Aux ConnectionStatus
     */
    enum EAuxConnectionStatus
    {
        AUX_STATE_DEFAULT = -1,
        AUX_STATE_UNKNOWN = 0,
        AUX_CONNECTED = 1,
        AUX_ALREADY_CONNECTED = 2,
        AUX_DISCONNECTED = 3
    };
    Q_ENUM(EAuxConnectionStatus)

    /**
     * @brief The EAuxConnectionStatus enum - Enum for Ipod ConnectionStatus
     */
    enum EIpodConnectionStatus
    {
        IPOD_STATE_DEFAULT = -1,
        IPOD_STATE_UNKNOWN = 0,
        IPOD_CONNECTED = 1,
        IPOD_ALREADY_CONNECTED = 2,
        IPOD_DISCONNECTED = 3
    };
    Q_ENUM(EIpodConnectionStatus)

    /**
     * @brief The EAuxConnectionStatus enum - Enum for Usb ConnectionStatus
     */
    enum EUsbConnectionStatus
    {
        USB_STATE_DEFAULT = -1,
        USB_STATE_UNKNOWN = 0,
        USB_CONNECTED = 1,
        USB_ALREADY_CONNECTED = 2,
        USB_DISCONNECTED = 3
    };
    Q_ENUM(EUsbConnectionStatus)

    static void registerAudioEnumsToQML()
    {
        qmlRegisterType<CAudioEnums>("com.harman.qml.audioenums",1,0,"AudioEnums");
        qRegisterMetaType<CAudioEnums::EAudioEntertainmentSrcs>("CAudioEnums::EAudioEntertainmentSrcs");
    }

};

//Q_DECLARE_METATYPE(CAudioEnums::EAudioEntertainmentSrcs)
Q_DECLARE_METATYPE(CAudioEnums::EAudioPresets)
Q_DECLARE_METATYPE(CAudioEnums::EBeepType)
Q_DECLARE_METATYPE(CAudioEnums::EToggleDirection)
Q_DECLARE_METATYPE(CAudioEnums::ESourceId)
Q_DECLARE_METATYPE(CAudioEnums::ESourceState)
Q_DECLARE_METATYPE(CAudioEnums::EAuxConnectionStatus)
Q_DECLARE_METATYPE(CAudioEnums::EIpodConnectionStatus)
Q_DECLARE_METATYPE(CAudioEnums::EUsbConnectionStatus)

#endif // CAUDIOENUMS_H

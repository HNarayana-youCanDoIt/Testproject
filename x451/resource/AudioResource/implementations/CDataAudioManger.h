/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CDataAudioManager.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 *  Audio module enums are present here
 */

#ifndef CDATAAUDIOMANGER_H
#define CDATAAUDIOMANGER_H

/**
 * @brief The eEntertainmentSrcs enum : entertainment sources from audiopresscontrol proxy
 */

enum eEntertainmentSrcs {
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
    SRC_APPLINK_TTS = 99,
    SRC_SAL_MEDIA = 100
};

/**
 * @brief The SourceType : source types from audiopresscontrol proxy
 */
enum SourceType
{
    SOURCE_TYPE_TUNER = 0,
    SOURCE_TYPE_USB_STORAGE = 1,
    SOURCE_TYPE_USB_MTP = 2,
    SOURCE_TYPE_IPOD = 3,
    SOURCE_TYPE_MEDIA = 4,
    SOURCE_TYPE_PROJECTION = 5,
    SOURCE_TYPE_APPS = 6,
    SOURCE_TYPE_UNKNOWN=7
};

/**
 * @brief The eInterruptSrcs : interrupt source types from audiopresscontrol proxy
 */
enum eInterruptSrcs
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
    SRC_VR_SMS_READOUT = 64,
    SRC_VR = 3,
    SRC_INTERRUPT_UNKNOWN = 562
};

/**
 * @struct AudioSourceItem
 * @brief This structure shall hold the data for appId, source availability status and source type
 */
struct AudioSourceItem
{
    int appId = 0;
    bool available = false;
    SourceType type = SOURCE_TYPE_UNKNOWN;
    int id = 0;
};

#endif // CDATAAUDIOMANGER_H

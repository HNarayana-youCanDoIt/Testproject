
/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CPhoneEnum.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPhoneEnum class that contains all the phone UI module related enums.
 */

#ifndef CPHONEENUM_H
#define CPHONEENUM_H

#include <QObject>
#include <QtQml>

/*!
 * @class CPhoneEnum
 * @brief This class contains all the phone UI module related enums.
 */
class CPhoneEnum: public QObject
{
    Q_OBJECT
public:

    /**
     * @enum    EPhoneSetupItems
     * @brief   It contains the items in phone setup screen.
     */
    enum EPhoneSetupItems
    {
        PHONE_SETUP_INVALID         = -1,
        PHONE_SETUP_PAIR_NEW_DEVICE = 0,
        PHONE_SETUP_PAIRED_DEVICES,
        PHONE_SETUP_BLUETOOTH_VISIBILITY,
        PHONE_SETUP_SMS_ALERT_NOTIFICATION,
        PHONE_SETUP_CONFIGURE_AUTO_SMS
    };
    Q_ENUM(EPhoneSetupItems)

    /*!
     * @enum    EPhoneCallState
     * @brief   This enum shall hold the values supported for call state that shall be used by
     * call screen.
     */
    enum EPhoneCallState
    {
        PHONE_CALLSTATE_INCOMING_CALL,
        PHONE_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL,
        PHONE_CALLSTATE_HELD_CALL_AND_INCOMING_CALL,
        PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL,
        PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL,
        PHONE_CALLSTATE_ACTIVE_CALL,
        PHONE_CALLSTATE_ACTIVE_CALL_AND_HELD_CALL,
        PHONE_CALLSTATE_ACTIVE_CALL_AND_CONFERENCE_ONHOLD,
        PHONE_CALLSTATE_HELD_CALL,
        PHONE_CALLSTATE_CONFERENCE_ONHOLD,
        PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE,
        PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_HELD_CALL,
        PHONE_CALLSTATE_DIALING,
        PHONE_CALLSTATE_ALERTING,
        PHONE_CALLSTATE_ACTIVE_CALL_AND_DIALING,
        PHONE_CALLSTATE_ACTIVE_CALL_AND_ALERTING,
        PHONE_CALLSTATE_HELD_CALL_AND_DIALING,
        PHONE_CALLSTATE_HELD_CALL_AND_ALERTING,
        PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_DIALING,
        PHONE_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_ALERTING,
        PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_DIALING,
        PHONE_CALLSTATE_CONFERENCE_ONHOLD_AND_ALERTING,
        PHONE_CALLSTATE_ALL_CALLS_TERMINATED,
        PHONE_CALLSTATE_IDLE
    };
    Q_ENUM(EPhoneCallState)

    /**
     * @enum    EItemType
     * @brief   It contains the type of items to be shown on screen.
     */
    enum EItemType
    {
        ITEM_TYPE_LABEL,
        ITEM_TYPE_ICON_WITH_BUTTON,
        ITEM_TYPE_LABEL_WITH_DROPDOWN,
        ITEM_TYPE_LABEL_WITH_RADIO_BUTTON,
        ITEM_TYPE_LABEL_WITH_CHECKBOX,
        ITEM_TYPE_LABEL_WITH_RADIO_BUTTON_AND_DROPDOWN,
        ITEM_TYPE_LABEL_WITH_EDIT_BUTTON,
        ITEM_TYPE_LABEL_WITH_BUTTON,
        ITEM_TYPE_DEFAULT
    };
    Q_ENUM(EItemType)

    /**
     * @enum    EPhoneBrowseType
     * @brief   It contains the type of browsing screen to be shown.
     */
    enum EPhoneBrowseType
    {
        PHONE_BROWSE_TYPE_UNKNOWN = -1,
        PHONE_BROWSE_TYPE_CALL_LOGS,        
        PHONE_BROWSE_TYPE_DIALPAD,
        PHONE_BROWSE_TYPE_FAVORITES,
        PHONE_BROWSE_TYPE_FREQUENTLY_DIALED,
        PHONE_BROWSE_TYPE_CONTACTS,
        PHONE_BROWSE_TYPE_CONTACT_DETAILS
    };
    Q_ENUM(EPhoneBrowseType)

    /**
     * @enum    ESignalStrengthLevel
     * @brief   It contains the signal strength levels.
     */
    enum ESignalStrengthLevel
    {
        SIGNAL_STRENGTH_UNAVAILABLE = -1,
        SIGNAL_STRENGTH_LEVEL_ZERO,
        SIGNAL_STRENGTH_LEVEL_ONE,
        SIGNAL_STRENGTH_LEVEL_TWO,
        SIGNAL_STRENGTH_LEVEL_THREE,
        SIGNAL_STRENGTH_LEVEL_FOUR,
        SIGNAL_STRENGTH_LEVEL_FIVE,
        SIGNAL_STRENGTH_NO_SIM
    };
    Q_ENUM(ESignalStrengthLevel)

    /**
     * @enum    EBatteryCharge
     * @brief   It contains the battery charge levels.
     */
    enum EBatteryChargeLevel
    {
        BATTERY_CHARGE_UNAVAILABLE = -1,
        BATTERY_CHARGE_LEVEL_ZERO,
        BATTERY_CHARGE_LEVEL_ONE,
        BATTERY_CHARGE_LEVEL_TWO,
        BATTERY_CHARGE_LEVEL_THREE,
        BATTERY_CHARGE_LEVEL_FOUR,
        BATTERY_CHARGE_LEVEL_FIVE
    };
    Q_ENUM(EBatteryChargeLevel)

    /**
     * @enum    ECallerState
     * @brief   It contains the caller state.
     */
    enum ECallerState
    {
        CALLER_ACTIVE,
        CALLER_ON_HOLD,
        CALLER_INACTIVE,
        CALLER_UNAVAILABLE
    };
    Q_ENUM(ECallerState)

    /**
     * @enum    ESmsAlertNotificationItemId
     * @brief   It contains SMS alert Notification options
     */
    enum ESmsAlertNotificationItemId
    {
        NOTIFY_WITH_BEEP_AND_POPUP_ID = 0,
        NOTIFY_WITH_ONLY_POPUP_ID,
        NO_NOTIFICATION_ID
    };
    Q_ENUM(ESmsAlertNotificationItemId)


    /**
     * @enum    EConfigureAutoSMSItemId
     * @brief   It contains EConfigure Auto Sms options
     */
    enum EConfigureAutoSMSItemId
    {
        MESSAGE_1_ID = 0,
        MESSAGE_2_ID ,
        MESSAGE_3_ID ,
        MESSAGE_4_ID ,
        MESSAGE_5_ID ,
        MESSAGE_6_ID ,
        MESSAGE_7_ID ,
        MESSAGE_8_ID ,
        MESSAGE_9_ID ,
        MESSAGE_10_ID
    };
    Q_ENUM(EConfigureAutoSMSItemId)

    /*!
     * @enum    ECallType
     * @brief   This enum shall hold the values supported call types.
     */
    enum ECallType
    {
        CALL_TYPE_UNKNOWN,
        CALL_TYPE_INCOMING,
        CALL_TYPE_OUTGOING,
        CALL_TYPE_MISSED
    };
    Q_ENUM(ECallType)

    /*!
     * @enum    EPhoneSyncStatus
     * @brief   This enum shall hold the values supported phone sync status.
     */
    enum EPhoneSyncStatus
    {
        PHONE_DATA_READ_OFF = 0,
        PHONE_DATA_READ_READY,
        PHONE_DATA_READING,
        PHONE_DATA_READ_DONE,
        PHONE_DATA_READ_UPDATING,
        PHONE_DATA_READ_FAIL,
    };
    Q_ENUM(EPhoneSyncStatus)

    /**
     * @brief The EKeyPadState enum: This enum contains all the possible states of keypad screen
     */
    enum EKeyPadState
    {
        KEYPAD_STATE_INVALID = -1,
        KEYPAD_STATE_CAPITAL,
        KEYPAD_STATE_SMALL,
        KEYPAD_STATE_NUMERIC,
    };
    Q_ENUM(EKeyPadState)

    /**
     * @brief The EKeyPadTextInputState enum: This enum contains all the possible states of text input area
     */
    enum EKeyPadTextInputState
    {
        TEXTINPUT_DEFAULT_TEXT = -1,
        TEXTINPUT_EMPTY_TEXT,
        TEXTINPUT_TYPING_TEXT,
    };
    Q_ENUM(EKeyPadTextInputState)


    /**
     * @brief The ETTSPlayState enum: This enum contains all the possible states of TTS
     */
    enum ETTSPlayState
    {
        EN_PLAY_STATE_NOTPLAYING,
        EN_PLAY_STATE_PLAYSTART,
        EN_PLAY_STATE_PLAYING,
        EN_PLAY_STATE_PLAYEND,
        EN_PLAY_STATE_ABORTED,
        EN_PLAY_STATE_PLAYERROR
    };
    Q_ENUM(ETTSPlayState)

    static void registerPhoneEnumsToQML()
    {
        qmlRegisterType<CPhoneEnum>("com.harman.qml.phoneenum",1,0,"PhoneEnum");
    }
};

Q_DECLARE_METATYPE(CPhoneEnum::EPhoneSetupItems)
Q_DECLARE_METATYPE(CPhoneEnum::EPhoneCallState)
Q_DECLARE_METATYPE(CPhoneEnum::EItemType)
Q_DECLARE_METATYPE(CPhoneEnum::EPhoneBrowseType)
Q_DECLARE_METATYPE(CPhoneEnum::ESignalStrengthLevel)
Q_DECLARE_METATYPE(CPhoneEnum::EBatteryChargeLevel)
Q_DECLARE_METATYPE(CPhoneEnum::ECallerState)
Q_DECLARE_METATYPE(CPhoneEnum::ESmsAlertNotificationItemId)
Q_DECLARE_METATYPE(CPhoneEnum::EConfigureAutoSMSItemId)
Q_DECLARE_METATYPE(CPhoneEnum::ECallType)
Q_DECLARE_METATYPE(CPhoneEnum::EPhoneSyncStatus)
Q_DECLARE_METATYPE(CPhoneEnum::EKeyPadState)
Q_DECLARE_METATYPE(CPhoneEnum::EKeyPadTextInputState)
Q_DECLARE_METATYPE(CPhoneEnum::ETTSPlayState)

#endif // CPHONEENUM_H

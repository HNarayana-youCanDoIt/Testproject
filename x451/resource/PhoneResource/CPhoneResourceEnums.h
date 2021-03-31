/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneResourceEnums.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain all the enums that shall be used by phone resource data structures
 * or by phone resource implementation classes. These enums shall also be used by phone application layer.
 */

#ifndef CPHONERESOURCEENUMS_H
#define CPHONERESOURCEENUMS_H

/*********************************************************************************************//**
 * @category CONNECTION MANAGER RESOURCE ENUMS
 **********************************************************************************************/

/*!
 * @enum    EDeviceClass
 * @brief   This enum shall hold the values supported for device class.
 */
enum EDeviceClass
{
    DEVICE_CLASS_COMPUTER,
    DEVICE_CLASS_PHONE,
    DEVICE_CLASS_AUDIO_VIDEO,
    DEVICE_CLASS_WEARABLE,
    DEVICE_CLASS_OTHERS,
    DEVICE_CLASS_DEFAULT
};

/*!
 * @enum    ESupportedProfile
 * @brief   This enum shall hold the values for all the profiles supported by BT press.
 */
enum ESupportedProfile
{
    PROFILE_TYPE_HFPGW,
    PROFILE_TYPE_A2DP,
    PROFILE_TYPE_AVRCP,
    PROFILE_TYPE_SPP,
    PROFILE_TYPE_PAN,
    PROFILE_TYPE_PBAP,
    PROFILE_TYPE_MAP,
    PROFILE_TYPE_UNKNOWN,
    PROFILE_TYPE_DEFAULT
};

/*!
 * @enum    EConnectionStatus
 * @brief   This enum shall hold the values supported for service connection status.
 */
enum EConnectionStatus
{
    CONNECTION_STATUS_CONNECTED,
    CONNECTION_STATUS_CONNECTING,
    CONNECTION_STATUS_DISCONNECTING,
    CONNECTION_STATUS_DISCONNECTED,
    CONNECTION_STATUS_CONNECTERROR,
    CONNECTION_STATUS_NOT_SUPPORTED,
    CONNECTION_STATUS_DEFAULT
};

/*!
 * @enum    EPairingStatus
 * @brief   This enum shall hold the values supported for device pairing status.
 */
enum EPairingStatus
{
    PAIRING_STATUS_SUCCESS,
    PAIRING_STATUS_FAILURE,
    PAIRING_STATUS_DISCOVERABLE,
    PAIRING_STATUS_NOT_DISCOVERABLE,
    PAIRING_STATUS_FAILED_NO_USER_ACTION_FROM_HU,
    PAIRING_STATUS_INCOMPATIBLE_REMOTE_DEVICE,
    PAIRING_STATUS_UNRESPONSIVE_DEVICE,
    PAIRING_STATUS_DEFAULT
};

/*!
 * @enum    EBondingType
 * @brief   This enum shall hold the values supported for device bonding type.
 */
enum EBondingType
{
    BONDING_TYPE_STANDARD,
    BONDING_TYPE_SECURE,
    BONDING_TYPE_DEAFULT
};

/*!
 * @enum    EServiceConnectDisconnectReason
 * @brief   This enum shall hold the values supported for service connect disconnect reason.
 */
enum EServiceConnectDisconnectReason
{
    SERVICE_CONNECTED_HEADUNIT_INITIATED,
    SERVICE_CONNECTED_PHONE_INITIATED,
    SERVICE_CONNECTED_AUTO_CONNECTION,
    SERVICE_DISCONNECTED_HEADUNIT_INITIATED,
    SERVICE_DISCONNECTED_PHONE_INITIATED,
    SERVICE_DISCONNECTED_LINK_LOSS,
    SERVICE_CONNECT_ERROR_PAGE_TIMEOUT,
    SERVICE_CONNECT_ERROR_USER_REJECTED,
    SERVICE_DISCONNECTED_DEVICE_DISCONNECTED,
    SERVICE_DISCONNECTED_NEW_CONNECTION_REQUEST,
    SERVICE_CONNECT_DISCONNECT_DEFAULT
};

/*!
 * @enum    EDeviceDeletedReason
 * @brief   This enum shall hold the values supported for device deleted reason.
 */
enum EDeviceDeletedReason
{
    DEVICE_DELETED_REASON_MISSING_KEY,
    DEVICE_DELETED_REASON_USER_REQUESTED,
    DEVICE_DELETED_REASON_DEFAULT
};

/*********************************************************************************************//**
 * @category CALL MANAGER RESOURCE ENUMS
 **********************************************************************************************/
/*!
 * @enum    EContactNumTelephoneType
 * @brief   This enum shall hold the values supported for contact number telephone type.
 */
enum EContactNumTeleType
{
    CONTACT_NUM_TELEPHONE_TYPE_MOBILE,
    CONTACT_NUM_TELEPHONE_TYPE_HOME,
    CONTACT_NUM_TELEPHONE_TYPE_WORK,
    CONTACT_NUM_TELEPHONE_TYPE_OTHER,
    CONTACT_NUM_TELEPHONE_TYPE_DEFAULT
};

/*!
 * @enum    EHMICallState
 * @brief   This enum shall hold the values supported for call state that shall be used by
 * phone adaptor layer.
 */
enum EHMICallState
{
    HMI_CALLSTATE_INCOMING_CALL,
    HMI_CALLSTATE_ACTIVE_CALL_AND_INCOMING_CALL,
    HMI_CALLSTATE_HELD_CALL_AND_INCOMING_CALL,
    HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_INCOMING_CALL,
    HMI_CALLSTATE_CONFERENCE_ONHOLD_AND_INCOMING_CALL,
    HMI_CALLSTATE_ACTIVE_CALL,
    HMI_CALLSTATE_ACTIVE_CALL_AND_HELD_CALL,
    HMI_CALLSTATE_ACTIVE_CALL_AND_CONFERENCE_ONHOLD,
    HMI_CALLSTATE_HELD_CALL,
    HMI_CALLSTATE_CONFERENCE_ONHOLD,
    HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE,
    HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_HELD_CALL,
    HMI_CALLSTATE_DIALING,
    HMI_CALLSTATE_ALERTING,
    HMI_CALLSTATE_ACTIVE_CALL_AND_DIALING,
    HMI_CALLSTATE_ACTIVE_CALL_AND_ALERTING,
    HMI_CALLSTATE_HELD_CALL_AND_DIALING,
    HMI_CALLSTATE_HELD_CALL_AND_ALERTING,
    HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_DIALING,
    HMI_CALLSTATE_CONFERENCE_CALL_ACTIVE_AND_ALERTING,
    HMI_CALLSTATE_CONFERENCE_ONHOLD_AND_DIALING,
    HMI_CALLSTATE_CONFERENCE_ONHOLD_AND_ALERTING,
    HMI_CALLSTATE_ALL_CALLS_TERMINATED,
    HMI_CALLSTATE_IDLE
};

/*!
 * @enum    ECallState
 * @brief   This enum shall hold the values supported for call state.
 */
enum ECallState
{
    CALL_STATE_ACTIVE,
    CALL_STATE_ON_HOLD,
    CALL_STATE_TERMINATED,
    CALL_STATE_DIALING,
    CALL_STATE_RINGING,
    CALL_STATE_ALERTING,
    CALL_STATE_WAITING,
    CALL_STATE_IGNORED,
    CALL_STATE_IDLE
};

/*!
 * @enum    ECallDirection
 * @brief   This enum shall hold the values supported for call direction.
 */
enum ECallDirection
{
    CALL_DIRECTION_INCOMING,
    CALL_DIRECTION_OUTGOING,
    CALL_DIRECTION_UNKNOWN
};

/*!
 * @enum    ECallAudioStatus
 * @brief   This enum shall hold the values supported for call audio status.
 */
enum ECallAudioStatus
{
    CALL_AUDIOSTATUS_CONNECTED,
    CALL_AUDIOSTATUS_DISCONNECTED,
    CALL_AUDIOSTATUS_ERROR,
    CALL_AUDIOSTATUS_DEFAULT
};

/*!
 * @enum    ESignalLevel
 * @brief   This enum shall hold the values supported for signal level.
 */
enum ESignalLevel
{
    NO_SIM_SIGNAL_LEVEL,
    SIGNAL_LEVEL_0_PERCENT,
    SIGNAL_LEVEL_10_PERCENT,
    SIGNAL_LEVEL_20_PERCENT,
    SIGNAL_LEVEL_30_PERCENT,
    SIGNAL_LEVEL_40_PERCENT,
    SIGNAL_LEVEL_50_PERCENT,
    SIGNAL_LEVEL_60_PERCENT,
    SIGNAL_LEVEL_70_PERCENT,
    SIGNAL_LEVEL_80_PERCENT,
    SIGNAL_LEVEL_90_PERCENT,
    SIGNAL_LEVEL_100_PERCENT,
    SIGNAL_LEVEL_INVALID
};

/*!
 * @enum    EBatteryChargeLevel
 * @brief   This enum shall hold the values supported for battery charge level.
 */
enum EBatteryChargeLevel
{
    BATTERY_CHARGE_LEVEL_0_PERCENT,
    BATTERY_CHARGE_LEVEL_20_PERCENT,
    BATTERY_CHARGE_LEVEL_40_PERCENT,
    BATTERY_CHARGE_LEVEL_60_PERCENT,
    BATTERY_CHARGE_LEVEL_80_PERCENT,
    BATTERY_CHARGE_LEVEL_100_PERCENT,
    BATTERY_CHARGE_LEVEL_INVALID
};

/*!
 * @enum    EPhoneNetworkRegState
 * @brief   This enum shall hold the values supported for phone network registery state info.
 */
enum EPhoneNetworkRegState
{
    PHONE_NETWORK_REGSTATE_NOT_REGISTERED,
    PHONE_NETWORK_REGSTATE_HOME,
    PHONE_NETWORK_REGSTATE_SEARCHING,
    PHONE_NETWORK_REGSTATE_DENIED,
    PHONE_NETWORK_REGSTATE_ROAMING,
    PHONE_NETWORK_REGSTATE_OPERATOR_DENIED,
    PHONE_NETWORK_REGSTATE_UNKNOWN
};

/*!
 * @enum    EPhoneOperatorMode
 * @brief   This enum shall hold the values supported for phone operator mode info.
 */
enum EPhoneOperatorMode
{
    PHONE_OPERATOR_MODE_AUTO,
    PHONE_OPERATOR_MODE_MANUAL,
    PHONE_OPERATOR_MODE_UNKNOWN
};

/*!
 * @enum    EPhoneSupportedFeatures
 * @brief   This enum shall hold the values supported for phone supported features info.
 */
enum EPhoneSupportedFeatures
{
    PHONE_FEATURE_REJECT,
    PHONE_FEATURE_REPLACE,
    PHONE_FEATURE_SWAP,
    PHONE_FEATURE_HANGUP_ENH,
    PHONE_FEATURE_SELECT,
    PHONE_FEATURE_CONFERENCE,
    PHONE_FEATURE_CALLTRANSFER,
    PHONE_FEATURE_CALLSTATUS_ENH,
    PHONE_FEATURE_RESP_AND_HOLD,
    PHONE_FEATURE_INBAND,
    PHONE_FEATURE_VR,
    PHONE_FEATURE_AUDIO_ENH,
    PHONE_FEATURE_SIRI,
    PHONE_FEATURE_GOOGLE_NOW,
    PHONE_FEATURE_NONE
};

/*********************************************************************************************//**
 * @category PHONE PIMDB RESOURCE ENUMS
 **********************************************************************************************/
/*!
 * @enum    EContactType
 * @brief   This enum shall hold the values supported contact types.
 */
enum EContactType
{
    CONTACT_TYPE_DEFAULT = -1,
    CONTACT_TYPE_MOBILE,
    CONTACT_TYPE_HOME,
    CONTACT_TYPE_WORK,
    CONTACT_TYPE_OTHER
};

/*!
 * @enum    ERemoteDeviceOS
 * @brief   This enum shall hold the values of Remote Device OS
 */
enum ERemoteDeviceOS
{
    OS_UNKNOWN = 0,
    OS_WINDOWS = 1,
    OS_ANDROID = 2,
    OS_IOS = 3
};

/*!
 * @enum    EDataReadState
 * @brief   This enum shall hold data read state type.
 */
enum EDataReadStateType
{
    DATA_READ_OFF,
    DATA_READ_READY,
    DATA_READING,
    DATA_READ_DONE,
    DATA_READ_UPDATING,
    DATA_READ_FAIL,
};

/*********************************************************************************************//**
 * @category PHONE RESOURCE GENERIC ENUMS
 **********************************************************************************************/
/*!
 * @enum    EMethodCallStatus
 * @brief   This enum shall hold the values supported for connection manager proxy method call status.
 */
enum EMethodCallStatus
{
    METHOD_CALL_STATUS_SUCCESS,
    METHOD_CALL_STATUS_OUT_OF_MEMORY,
    METHOD_CALL_STATUS_NOT_AVAILABLE,
    METHOD_CALL_STATUS_CONNECTION_FAILED,
    METHOD_CALL_STATUS_REMOTE_ERROR,
    METHOD_CALL_STATUS_UNKNOWN,
    METHOD_CALL_STATUS_INVALID_VALUE,
    METHOD_CALL_STATUS_SUBSCRIPTION_REFUSED,
    METHOD_CALL_STATUS_DEFAULT
};

/*!
 * @enum    EMethodCallErrorType
 * @brief   This enum shall hold the values supported for connection manager proxy method call status error type.
 */
enum EMethodCallErrorType
{
    METHOD_CALL_ERROR_TYPE_SUCCESS,
    METHOD_CALL_ERROR_TYPE_DEFAULT,
    METHOD_CALL_ERROR_TYPE_PENDING,
    METHOD_CALL_ERROR_TYPE_API_NOT_SUPPORTED,
    METHOD_CALL_ERROR_TYPE_BAD_PARAMETER,
    METHOD_CALL_ERROR_TYPE_DEVICE_REMOVED,
    METHOD_CALL_ERROR_TYPE_SYNC_NOT_COMPLETED,
    METHOD_CALL_ERROR_TYPE_FAILURE,
    METHOD_CALL_ERROR_EXCEEDED_MAX_ENTRY_LIMIT,
    METHOD_CALL_ERROR_EXCEEDED_MAX_CHARACTER_LIMIT,
    METHOD_CALL_ERROR_REASON_NO_NETWORK_SERVICE,
    METHOD_CALL_ERROR_REASON_NETWORK_NOT_ALLOWED
};

#endif // CPHONERESOURCEENUMS_H

/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneResourceData.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain all the structure data that shall be used by phone resource implementation classes.
 */

#ifndef CPHONERESOURCEDATA_H
#define CPHONERESOURCEDATA_H

#include <string>
#include <vector>
#include <unordered_map>
#include "logging.h"
#include "PhoneResource/CPhoneResourceEnums.h"
using namespace std;

/***************************************************************//**
 * @category CONSTANTS
 ***************************************************************/
const int PHONE_API_REQUEST_DEFAULT_TIMEOUT  = 45000;

/*********************************************************************************************//**
 * @category BASE STRUCTURE
 **********************************************************************************************/
/*!
 * @struct  SDeviceInfo
 * @brief   This structure shall hold basic information of the device, all other structures
 * whom so ever need the information shall be derived from it.
 */
struct SDeviceInfo
{
    SDeviceInfo()
        : m_strDeviceBtAddr(""),
          m_strDeviceName(""),
          m_eDeviceClass(DEVICE_CLASS_DEFAULT)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold device bt address
    string       m_strDeviceBtAddr;
    //! Data to hold device name
    string       m_strDeviceName;
    //! Data to hold value of device class
    EDeviceClass m_eDeviceClass;

    //! Method to clear the stored data
    void clear()
    {
        m_strDeviceBtAddr   = "";
        m_strDeviceName     = "";
        m_eDeviceClass      = DEVICE_CLASS_DEFAULT;
    }
};

/*********************************************************************************************//**
 * @category CONNECTION MANAGER RESOURCE STRUCTURES
 **********************************************************************************************/
/*!
 * @struct  SDeviceBondingStatus
 * @brief   This structure shall hold the data for device bonding status
 * received from connection manager proxy.
 */
struct SDeviceBondingStatus : public SDeviceInfo
{
    SDeviceBondingStatus()
        : m_ePairingStatus(PAIRING_STATUS_DEFAULT),
          m_bPairingSuccessful(false)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold value of pairing status
    EPairingStatus  m_ePairingStatus;
    //! Flag to maintain paring status of device
    bool            m_bPairingSuccessful;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_ePairingStatus      = PAIRING_STATUS_DEFAULT;
        m_bPairingSuccessful  = false;
    }
};

/*!
 * @struct  SBondingRequest
 * @brief   This structure shall hold the data for bonding request
 * received from connection manager proxy.
 */
struct SBondingRequest : public SDeviceInfo
{
    SBondingRequest()
        : m_strPasskey(""),
          m_eBondingType(BONDING_TYPE_DEAFULT),
          m_bSecureBonding(false)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold passkey pin
    string       m_strPasskey;
    //! Data to hold value of bonding type
    EBondingType m_eBondingType;
    //! Flag to maintain bonding type is secure bonding or not
    bool         m_bSecureBonding;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_strPasskey      = "";
        m_eBondingType    = BONDING_TYPE_DEAFULT;
        m_bSecureBonding  = false;
    }
};

/*!
 * @struct  SServiceConnectionStatus
 * @brief   This structure shall hold the data for service connection status
 * received from connection manager proxy.
 */
struct SServiceConnectionStatus : public SDeviceInfo
{
    SServiceConnectionStatus()
        : m_eSupportedProfile(PROFILE_TYPE_DEFAULT),
          m_bConnectionSuccessful(false),
          m_bDisconnectionSuccessful(false),
          m_eConnectionStatus(CONNECTION_STATUS_DEFAULT),
          m_eServiceConnectDisconnectReason(SERVICE_CONNECT_DISCONNECT_DEFAULT)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold supported profile value
    ESupportedProfile               m_eSupportedProfile;
    //! Flag to maintain connection status for the profile
    bool                            m_bConnectionSuccessful;
    //! Flag to maintain disconnection status for the profile
    bool                            m_bDisconnectionSuccessful;
    //! Data to hold value of connection status
    EConnectionStatus               m_eConnectionStatus;
    //! Data to hold value of service connect disconnect reason
    EServiceConnectDisconnectReason m_eServiceConnectDisconnectReason;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_eSupportedProfile                 = PROFILE_TYPE_DEFAULT;
        m_bConnectionSuccessful             = false;
        m_bDisconnectionSuccessful          = false;
        m_eConnectionStatus                 = CONNECTION_STATUS_DEFAULT;
        m_eServiceConnectDisconnectReason   = SERVICE_CONNECT_DISCONNECT_DEFAULT;
    }
};

/*!
 * @struct  SDeviceDeleted
 * @brief   This structure shall hold the data for device deleted
 * received from connection manager proxy.
 */
struct SDeviceDeleted : public SDeviceInfo
{
    SDeviceDeleted()
        : m_eDeviceDeleteReason(DEVICE_DELETED_REASON_DEFAULT),
          m_bUserRequested(false)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold value of delete device reason
    EDeviceDeletedReason m_eDeviceDeleteReason;
    //! Flag to maintain device deletion requested from user or not
    bool                 m_bUserRequested;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_eDeviceDeleteReason   = DEVICE_DELETED_REASON_DEFAULT;
        m_bUserRequested        = false;
    }
};

/*!
 * @struct  SSearchDeviceInfo
 * @brief   This structure shall hold the data for search device information
 * received from connection manager proxy.
 */
struct SSearchDeviceInfo : public SDeviceInfo
{
    SSearchDeviceInfo()
        : m_bDeviceConnected(false),
          m_bDevicePaired(false)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Flag to maintain device is connected or not
    bool         m_bDeviceConnected;
    //! Flag to maintain device is paired or not
    bool         m_bDevicePaired;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_bDeviceConnected  = false;
        m_bDevicePaired     = false;
    }
};

/*!
 * @struct  SProfileInfo
 * @brief   This structure shall hold the data for profile information
 * received from connection manager proxy.
 */
struct SProfileInfo
{
    SProfileInfo()
        : m_uiMajorVersion(0),
          m_uiMinorVersion(0),
          m_eConnectionStatus(CONNECTION_STATUS_DEFAULT)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold major version of the profile
    unsigned short      m_uiMajorVersion;
    //! Data to hold minor version of the profile
    unsigned short      m_uiMinorVersion;
    //! Data to hold connection status of the profile
    EConnectionStatus   m_eConnectionStatus;

    //! Method to clear the stored data
    void clear()
    {
        m_uiMajorVersion    = 0;
        m_uiMinorVersion    = 0;
        m_eConnectionStatus = CONNECTION_STATUS_DEFAULT;
    }
};

/*!
 * @struct  SBondedDeviceInfo
 * @brief   This structure shall hold the data for bonded device information
 * received from connection manager proxy.
 */
struct SBondedDeviceInfo : public SDeviceInfo
{
    SBondedDeviceInfo()
        : m_uiIndex(0)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
        m_mapProfileInfoList.clear();
    }
    //! Data to hold index/position of paired device
    unsigned short  m_uiIndex;
    //! Unordered map of connected profile information
    unordered_map<ESupportedProfile, SProfileInfo, std::hash<int>> m_mapProfileInfoList;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_uiIndex           = 0;
        m_mapProfileInfoList.clear();
    }
};

/*********************************************************************************************//**
 * @category CALL MANAGER RESOURCE STRUCTURES
 **********************************************************************************************/
/*!
 * @struct  SCallStateInfo
 * @brief   This structure shall hold the data for call state info
 * received from call manager proxy.
 */
struct SCallStateInfo
{
    SCallStateInfo()
        : m_iCallId(-1),
          m_eCallState(CALL_STATE_IDLE),
          m_strContactNumber(""),
          m_strContactName(""),
          m_strContactImageUrl(""),
          m_eContactNumTeleType(CONTACT_NUM_TELEPHONE_TYPE_DEFAULT),
          m_uiContactId(0),
          m_eCallDirection(CALL_DIRECTION_UNKNOWN)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold value of call id
    int                 m_iCallId;
    //! Data to hold value of call state
    ECallState          m_eCallState;
    //! Data to hold value of contact number
    string              m_strContactNumber;
    //! Data to hold value of contact name
    string              m_strContactName;
    //! Data to hold value of contact image url
    string              m_strContactImageUrl;
    //! Data to hold value of contact number telephone type
    EContactNumTeleType m_eContactNumTeleType;
    //! Data to hold value of contact id
    unsigned int        m_uiContactId;
    //! Data to hold value of call direction
    ECallDirection      m_eCallDirection;

    //! Method to clear the stored data
    void clear()
    {
        m_iCallId               = -1;
        m_eCallState            = CALL_STATE_IDLE;
        m_strContactNumber      = "";
        m_strContactName        = "";
        m_strContactImageUrl    = "";
        m_eContactNumTeleType   = CONTACT_NUM_TELEPHONE_TYPE_DEFAULT;
        m_uiContactId           = 0;
        m_eCallDirection        = CALL_DIRECTION_UNKNOWN;
    }
};

/*!
 * @struct  SCallStateInfoList
 * @brief   This structure shall hold HMI call state info and list of callstate info
 * received from call manager proxy.
 */
struct SCallStateInfoList : public SDeviceInfo
{
    SCallStateInfoList()
        : m_eHMICallState(HMI_CALLSTATE_IDLE)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
        m_vectCallStateInfo.clear();
    }
    //! Data to hold value of call state that shall be generated after decoding call state info received
    EHMICallState           m_eHMICallState;
    //! List of call state info data for connected device
    vector<SCallStateInfo>  m_vectCallStateInfo;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_eHMICallState     = HMI_CALLSTATE_IDLE;
        m_vectCallStateInfo.clear();
    }
};

/*!
 * @struct  SCallDuration
 * @brief   This structure shall hold the data for call duration info
 * received from call manager proxy.
 */
struct SCallDuration : public SDeviceInfo
{
    SCallDuration()
        : m_iCallId(-1),
          m_uiCallDuration(0)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold value of call id
    signed char         m_iCallId;
    //! Data to hold value of contact id
    unsigned int        m_uiCallDuration;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_iCallId           = -1;
        m_uiCallDuration    = 0;
    }
};

/*!
 * @struct  SHfModeStatus
 * @brief   This structure shall hold the data for hf mode status info
 * received from call manager proxy.
 */
struct SHfModeStatus : public SDeviceInfo
{
    SHfModeStatus()
        : m_eCallAudioStatus(CALL_AUDIOSTATUS_DEFAULT)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold value of contact id
    ECallAudioStatus    m_eCallAudioStatus;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_eCallAudioStatus  = CALL_AUDIOSTATUS_DEFAULT;
    }
};



/*!
 * @struct  SSignalChargeInfo
 * @brief   This structure shall hold the data for battery charge and signal strength info
 * received from call manager proxy.
 */
struct SSignalChargeInfo : public SDeviceInfo
{
    SSignalChargeInfo()
        : m_eSignalLevel(SIGNAL_LEVEL_INVALID),
          m_eBatteryChargeLevel(BATTERY_CHARGE_LEVEL_INVALID)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold value of signal level
    ESignalLevel        m_eSignalLevel;
    //! Data to hold value of battery charge level
    EBatteryChargeLevel m_eBatteryChargeLevel;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_eSignalLevel          = SIGNAL_LEVEL_INVALID;
        m_eBatteryChargeLevel   = BATTERY_CHARGE_LEVEL_INVALID;
    }
};

/*!
 * @struct  SNetworkOperatorInfo
 * @brief   This structure shall hold the data for phone network operator info
 * received from call manager proxy.
 */
struct SNetworkOperatorInfo : public SDeviceInfo
{
    SNetworkOperatorInfo()
        : m_ePhoneNetworkRegState(PHONE_NETWORK_REGSTATE_UNKNOWN),
          m_bNetworkAvailability(false),
          m_strSubscriberNumber(""),
          m_strOperatorName(""),
          m_ePhoneOperatorMode(PHONE_OPERATOR_MODE_UNKNOWN)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold value of phone network registry state
    EPhoneNetworkRegState   m_ePhoneNetworkRegState;
    //! Flag to indicate whether network is available or not
    bool                    m_bNetworkAvailability;
    //! Data to hold value of subscriber number
    string                  m_strSubscriberNumber;
    //! Data to hold value of operator name
    string                  m_strOperatorName;
    //! Data to hold value of phone operator mode
    EPhoneOperatorMode      m_ePhoneOperatorMode;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_ePhoneNetworkRegState     = PHONE_NETWORK_REGSTATE_UNKNOWN;
        m_bNetworkAvailability      = false;
        m_strSubscriberNumber       = "";
        m_strOperatorName           = "";
        m_ePhoneOperatorMode        = PHONE_OPERATOR_MODE_UNKNOWN;
    }
};

/*!
 * @struct  SHfpSupportedFeatures
 * @brief   This structure shall hold the data for hfp supported features info
 * received from call manager proxy.
 */
struct SHfpSupportedFeatures : public SDeviceInfo
{
    SHfpSupportedFeatures()
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
        m_mapSupportedFeatures.clear();
    }
    //! Unordered map of phone supported features information
    unordered_map<EPhoneSupportedFeatures, bool, std::hash<int>> m_mapSupportedFeatures;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_mapSupportedFeatures.clear();
    }
};

/*!
 * @struct  SPhoneBTVrModeStatus
 * @brief   This structure shall hold the data for phone bt vr mode status
 * received from call manager proxy.
 */
struct SPhoneBTVrModeStatus : public SDeviceInfo
{
    SPhoneBTVrModeStatus()
        : m_bPhoneBtVrModeStatus(false)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! To hold status of Bt VR.
    bool    m_bPhoneBtVrModeStatus;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_bPhoneBtVrModeStatus = false;
    }
};

/*********************************************************************************************//**
 * @category PHONE PIMDB RESOURCE STRUCTURES
 **********************************************************************************************/
/*!
 * @struct  SCallLogData
 * @brief   This structure shall hold the data for call log info
 * received from phone pimdb proxy.
 */
struct SCallLogData
{
    SCallLogData()
        : m_iCallLogIndex(-1),
          m_iCallType(-1),
          m_strContactName(""),
          m_strContactNumber(""),
          m_strCallStamp("")
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }

    //! Data to hold value of call log index in the db
    int         m_iCallLogIndex;
    //! Data to hold value of call type
    int         m_iCallType;
    //! Data to hold value of contact name
    string      m_strContactName;
    //! Data to hold value of contact number
    string      m_strContactNumber;
    //! Data to hold value of call stamp
    string      m_strCallStamp;

    //! Method to clear the stored data
    void clear()
    {
        m_iCallLogIndex     = -1;
        m_iCallType         = -1;
        m_strContactName    = "";
        m_strContactNumber  = "";
        m_strCallStamp      = "";
    }
};

/*!
 * @struct  SFrequentlyDialledData
 * @brief   This structure shall hold the data for frequently dialled info
 * received from phone pimdb proxy.
 */
struct SFrequentlyDialledData
{
    SFrequentlyDialledData()
        : m_iDialledNumIndex(-1),
          m_iCallType(-1),
          m_strContactName(""),
          m_strContactNumber(""),
          m_strCallStamp("")
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }

    //! Data to hold value of frequently dialled number index in the db
    int         m_iDialledNumIndex;
    //! Data to hold value of call type
    int         m_iCallType;
    //! Data to hold value of contact name
    string      m_strContactName;
    //! Data to hold value of contact number
    string      m_strContactNumber;
    //! Data to hold value of call stamp
    string      m_strCallStamp;

    //! Method to clear the stored data
    void clear()
    {
        m_iDialledNumIndex     = -1;
        m_iCallType         = -1;
        m_strContactName    = "";
        m_strContactNumber  = "";
        m_strCallStamp      = "";
    }
};

/*!
 * @struct  SContactData
 * @brief   This structure shall hold the data for contact info
 * received from phone pimdb proxy.
 */
struct SContactData
{
    SContactData()
        : m_iContactIndex(-1),
          m_iContactID(-1),
          m_iContactType(-1),
          m_iFavIndex(-1),
          m_strContactName(""),
          m_strContactNumber("")
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }

    //! Data to hold value of contact index in the db
    int             m_iContactIndex;
    //! Data to hold value of contact id
    int             m_iContactID;
    //! Data to hold value of contact type
    int             m_iContactType;
    //! Data to hold value of favorite index in the db
    int             m_iFavIndex;
    //! Data to hold value of contact name
    string          m_strContactName;
    //! Data to hold value of contact number
    string          m_strContactNumber;

    //! Method to clear the stored data
    void clear()
    {
        m_iContactIndex     = -1;
        m_iContactID        = -1;
        m_iContactType      = -1;
        m_iFavIndex         = -1;
        m_strContactName    = "";
        m_strContactNumber  = "";
    }
};

/*!
 * @struct  SSmsData
 * @brief   This structure shall hold the data for sms info
 * received from phone pimdb proxy.
 */
struct SSmsData
{
    SSmsData()
        : m_strContactName("")
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold value of contact name
    string  m_strContactName;

    //! Method to clear the stored data
    void clear()
    {
        m_strContactName = "";
    }
};


/*!
 * @struct  SSmsTemplateData
 * @brief   This structure shall hold the data for sms template info
 * received from phone pimdb proxy.
 */
struct SSmsTemplateData
{
    SSmsTemplateData()
        : m_strContactName("")
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    //! Data to hold value of contact name
    string  m_strContactName;

    //! Method to clear the stored data
    void clear()
    {
        m_strContactName = "";
    }
};

/*!
 * @struct  SSmsSupportedFeatureList
 * @brief   This structure shall hold the data for sms supported features info
 * received from call pimdb proxy.
 */
struct SSmsSupportedFeatureList : public SDeviceInfo
{
    SSmsSupportedFeatureList()
        : m_strBtAddress(""),
          m_eRemoteDeviceOS(OS_UNKNOWN),
          m_bSmsSyncSupport(false),
          m_bReadStatusSupport(false),
          m_bSendSupport(false)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);


    }

    //! Data to hold value of Bt Address
        string m_strBtAddress;

        //! Data to hold value of remote device OS
        ERemoteDeviceOS m_eRemoteDeviceOS;

        //! Data to hold value of sms sync support
        bool m_bSmsSyncSupport;

        //! Data to hold value of read status support
        bool m_bReadStatusSupport;

        //! Data to hold value of send Support
        bool m_bSendSupport;

    //! Method to clear the stored data
    void clear()
    {
        SDeviceInfo::clear();
        m_strBtAddress = "";
        m_eRemoteDeviceOS = OS_UNKNOWN;
        m_bSmsSyncSupport = false;
        m_bReadStatusSupport = false;
        m_bSendSupport = false;
    }

};

/*!
 * @struct  SMessageData
 * @brief   This structure shall hold the properties for message data
 * received from phone pimdb proxy.
 */
struct SMessageData
{
    SMessageData()
        : m_strName(""),
          m_strNumber(""),
          m_strBody(""),
          m_strAddress(""),
          m_iId(0)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }
    string m_strName;
    string m_strNumber;
    string m_strBody;
    string m_strAddress;
    int m_iId;

    void clear()
    {
        m_strName = "";
        m_strNumber = "";
        m_strBody = "";
        m_strAddress = "";
        m_iId = 0;
    }
};

/*!
 * @struct  SUnreadMissedCallData
 * @brief   This structure holds basic information of unread Missed Call
 */
struct SUnreadMissedCallData
{
    SUnreadMissedCallData()
        : m_strBTAddress(""),
          m_strContactName(""),
          m_strContactNumber(""),
          m_uiMissedCallCount(0)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    }

    string       m_strBTAddress;
    string       m_strContactName;
    string       m_strContactNumber;
    unsigned int m_uiMissedCallCount;

    //! Method to clear the stored data
    void clear()
    {
        m_strBTAddress      = "";
        m_strContactName    = "";
        m_strContactNumber  = "";
        m_uiMissedCallCount = 0;
    }
};

#endif // CPHONERESOURCEDATA_H

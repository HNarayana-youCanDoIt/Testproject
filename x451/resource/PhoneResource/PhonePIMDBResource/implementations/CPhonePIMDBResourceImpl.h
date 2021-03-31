/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CPhonePIMDBResourceImpl.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         This file contains CPhonePIMDBResourceImpl class that shall implement the
 * PimDbResource interface and is a mediator between lower layer(press control)
 * and upper layer(application).
 */

#ifndef CPHONEPIMDBRESOURCEIMPL_H
#define CPHONEPIMDBRESOURCEIMPL_H

#include "interfaces/IPhonePIMDBResource.h"
#include "CPhonePIMDBEventProvider.h"
#include "PhoneResource/CPhoneResourceData.h"
#include <capi/CAPIClientAbstraction.hpp>

class CPhonePIMDBResourceImpl: public IPhonePIMDBResource
{
public:
    CPhonePIMDBResourceImpl();
    virtual ~CPhonePIMDBResourceImpl();

    /** ****************************************************
     ** @category INTERNAL METHODS
     ** ****************************************************/

    /*!
     * @brief   getPhonePimDbEventProvider: Method to get the instance of CPhonePIMDBEventProvider class.
     * @param   void.
     * @return  pointer to the object of CPhonePIMDBEventProvider class.
     */
    CPhonePIMDBEventProvider* getPhonePimDbEventProvider();

    /*!
     * @brief   getProxyStatusEventCb: Method to get PimDb Proxy Status Event change
     * @param   eStatus: AvailabilityStatus for PimDb Proxy.
     * @return  void.
     */
    void  getProxyStatusEventCb(CommonAPI::AvailabilityStatus eStatus);

    /*!
     * @brief   getPimDbServiceAvailableStatus: Method to get the status of PimDb Service Availability.
     * @param   void.
     * @return  bool status of PimDb Service Availability.
     */
    bool  getPimDbServiceAvailableStatus();

    /*!
     * @brief   subscribePimDbHandlerCb: Internal method to subscribe all the callback methods from PimDbHandler.
     * @param   void.
     * @return  void.
     */
    void subscribePimDbHandlerCb();

    /*!
     * @brief   getContactNamesForCallList: Internal method to convert PimDb Contact Names to Req Format.
     * @param   objBTPresPBEntry: ContactNames from PimDb.
     * @return  string according to Require format
     */
    string getContactNamesForCallList(BTPresTypes::phonebookEntry objBTPresPBEntry);

    /*!
     * @brief   getPhoneNumbersForCallList: Internal method to convert PimDb Phone Numbers to Req Format.
     * @param   objBTPresPBEntry: PhoneNumbers from PimDb.
     * @return  string according to Require format
     */
    string getPhoneNumbersForCallList(BTPresTypes::phonebookEntry objBTPresPBEntry);

    /*!
     * @brief   getPhoneNumberTypeForCallList: Internal method to convert PimDb Phone NumberType to Req Format.
     * @param   objBTPresPBEntry: PhoneNumberTypes from PimDb.
     * @return  EContactType according to Require format
     */
    EContactType getPhoneNumberTypeForCallList(BTPresTypes::phonebookEntry objBTPresPBEntry);

    /*!
     * @brief   getFormatedDateAndTime: Internal method to convert PimDb datetime to Req Format.
     * @param   objBTPresPBEntry: datetime from PimDb.
     * @return  string according to Require format
     */
    string getFormatedDateAndTime(BTPresTypes::phonebookEntry objBTPresPBEntry);

    /*!
     * @brief   getCallLogList: Method to get call log list.
     * @param   void.
     * @return  const reference vector of SCallLogData structure's instance.
     */
    const vector<SCallLogData>&  getCallLogList() { return m_vectCallListData; }

    /*!
     * @brief   getContactList: Method to get Contact list.
     * @param   void.
     * @return  const reference vector of SContactData structure's instance.
     */
    const vector<SContactData>&  getContactList() { return m_vectContactListData; }

    /*!
     * @brief   getSmsSupportedFeatureList: Method to get hfp supported features info of connected devices for hfp profile.
     * @param   void.
     * @return  const reference vector of SHfpSupportedFeatures structure's instance.
     */
    const vector<SSmsSupportedFeatureList>&  getSmsSupportedFeatureList() { return m_vectSmsSupportedFeatureList; }

    /*!
     * @brief   getContactDetailList: Method to get Contact detail list.
     * @param   void.
     * @return  const reference vector of SContactData structure's instance.
     */
    const vector<SContactData>&  getContactDetailList() { return m_vectContactDetailListData; }

    /*!
     * @brief   getFavouriteList: Method to get Favourite Contact list.
     * @param   void.
     * @return  const reference vector of SContactData structure's instance.
     */
    const vector<SContactData>&  getFavouriteList() { return m_vectFavouriteListData; }

    /*!
     * @brief   getFrequentlyDialedList: Method to get frequently dialed list.
     * @param   void.
     * @return  const reference vector of SFrequentlyDialledData structure's instance.
     */
    const vector<SFrequentlyDialledData>&  getFrequentlyDialedList() { return m_vectFrequentlyDialedListData; }

    /*!
     * @brief   getSmsList: Method to get Sms list.
     * @param   void.
     * @return  const reference vector of SSmsData structure's instance.
     */
    const vector<SSmsData>&  getSmsList() { return m_vectSmsListData; }

    /*!
     * @brief   getSMSTemplateList: Method to get SMSTemplate list.
     * @param   void.
     * @return  const reference vector of SSmsTemplateData structure's instance.
     */
    const vector<SSmsTemplateData>&  getSMSTemplateList() { return m_vectSMSTemplateListData; }

    /*!
     * @brief   getMessageData: Method to get incoming message data.
     * @param   void.
     * @return  const reference of SMessageData structure's instance.
     */
    const SMessageData& getMessageData() { return m_objSmsData; }

    /*!
     * @brief   getUnreadMissedCallData: Method to get unread missed call data.
     * @param   void.
     * @return  const reference instance of SUnreadMissedCallData structure.
     */
    const SUnreadMissedCallData& getUnreadMissedCallData(){ return m_objUnreadMissedCallData; }

    /*!
     * @brief   changeIsSendingSMSAllowed: Method to change Can send SMS value
     * @param   bool can send SMS.
     * @return  void
     */
    void changeIsSendingSMSAllowed(bool bIsSendingSMSAllowed);

private:

    /*!
     * @brief   getCallListSyncState: Method to get Call List Sync State
     * @param   void
     * @return  EDataReadStateType: Call List data sync state.
     */
    inline EDataReadStateType getCallListSyncState() { return m_eCallListSyncStatus; }

    /*!
     * @brief   getContactListSyncState: Method to get Contact List Sync State
     * @param   void
     * @return  EDataReadStateType: Contact List data sync state.
     */
    inline EDataReadStateType getContactListSyncState() { return m_eContactListSyncStatus; }

    /*!
     * @brief   getContactDetailListSyncState: Method to get Contact detail List Sync State
     * @param   void
     * @return  EDataReadStateType: Contact detail List data sync state.
     */
    inline EDataReadStateType getContactDetailListSyncState() { return m_eContactDetailListSyncStatus; }

    /*!
     * @brief   getFavouriteListSyncState: Method to get Favourite List Sync State
     * @param   void
     * @return  EDataReadStateType: Favourite List data sync state.
     */
    inline EDataReadStateType getFavouriteListSyncState() { return m_eFavouriteListSyncStatus; }

    /*!
     * @brief   getFrequentlyDialedListSyncState: Method to get rquently dialed list sync state
     * @param   void
     * @return  frequently dialed list sync status.
     */
    EDataReadStateType getFrequentlyDialedListSyncState() { return m_eFrequentlyDialedListSyncStatus; }

    /*!
     * @brief   getSmsListSyncState: Method to get Sms List Sync State
     * @param   void
     * @return  EDataReadStateType: Sms List data sync state.
     */
    inline EDataReadStateType getSmsListSyncState() { return m_eSmsListSyncStatus; }

    /*!
     * @brief   getSmsTemplateListSyncState: Method to get Sms Template List Sync State
     * @param   void
     * @return  EDataReadStateType: Sms Template List data sync state.
     */
    inline EDataReadStateType getSmsTemplateListSyncState() { return m_eSMSTemplateListSyncStatus; }

    /*!
     * @brief   getRemoteDevOS: Internal method to map remote device OS enums to pimdb resource's
     *          remote device OS enums. The mapped enums shall be used by the phone application layer
     *          and the class itself.
     * @param   iRemoteDeviceOS: remote device OS enum value.
     * @return  pimdb resource's remote device OS enum value.
     */
    ERemoteDeviceOS getRemoteDevOS(int iRemoteDeviceOS);

    /*!
     * @brief   changeCallListSyncState: Method to change Call List Sync State
     * @param   eState: new Call List data sync state.
     * @return  void
     */
    void changeCallListSyncState(EDataReadStateType eState);

    /*!
     * @brief   changeContactListSyncState: Method to change Contact List Sync State
     * @param   eState: new Contact List data sync state.
     * @return  void
     */
    void changeContactListSyncState(EDataReadStateType eState);

    /*!
     * @brief   changeContactDetailListSyncState: Method to change Contact Detail List Sync State
     * @param   eState: new Contact Detail List data sync state.
     * @return  void
     */
    void changeContactDetailListSyncState(EDataReadStateType eState);

    /*!
     * @brief   changeFavouriteListSyncState: Method to change Favourite List Sync State
     * @param   eState: new Favourite List data sync state.
     * @return  void
     */
    void changeFavouriteListSyncState(EDataReadStateType eState);

    /*!
     * @brief   changeFrequentlyDialedListSyncState: changeFrequentlyDialedListSyncState: Method to change frquently dialed list sync State
     * @param   eState: new Favourite List data sync state.
     * @return  void
     */
    void changeFrequentlyDialedListSyncState(EDataReadStateType eState);

    /*!
     * @brief   changeSmsListSyncState: Method to change Sms List Sync State
     * @param   eState: new Sms List data sync state.
     * @return  void
     */
    void changeSmsListSyncState(EDataReadStateType eState);

    /*!
     * @brief   changeSmsTemplateListSyncState: Method to change Sms Template List Sync State
     * @param   eState: new Sms Template List data sync state.
     * @return  void
     */
    void changeSmsTemplateListSyncState(EDataReadStateType eState);

    /*!
     * @brief   tryRequestQueryForCallLog: Method to request PimDb query for Call List
     * @param   void
     * @return  void
     */
    void tryRequestQueryForCallLog();

    /*!
     * @brief   tryRequestQueryForContact: Method to request PimDb query for Contact List
     * @param   void
     * @return  void
     */
    void tryRequestQueryForContact();

    /*!
     * @brief   tryRequestQueryForFavorite: Method to request PimDb query for Favorite Contact List
     * @param   void
     * @return  void
     */
    void tryRequestQueryForFavorite();

    /*!
     * @brief   tryRequestQueryForFrequentlyDialed: Method to request PimDb query for freuently dialed list
     * @param   void
     * @return  void
     */
    void tryRequestQueryForFrequentlyDialed();

    /*!
     * @brief   tryRequestQueryForSMS: Method to request PimDb query for SMS List
     * @param   void
     * @return  void
     */
    void tryRequestQueryForSMS();

    /*!
     * @brief   tryRequestQueryForSMSTemplate: Method to request PimDb query for SMS Template List
     * @param   void
     * @return  void
     */
    void tryRequestQueryForSMSTemplate();    

    /*!
     * @brief   closePimDbSession: Internal method to be called to reset Pimdb data.
     * @param   void
     * @return  void
     */
    void closePimDbSession();

public:
    /** ****************************************************
     ** @category SERVICE SIGNALS
     ** ****************************************************/

    /*!
     * @brief   getContactNameOrderAttributeChangedCb: method to get callback for Contact Name Order Attribute Changed
     * @param   eContactNameOrder: contact name order
     * @return  void
     */
    void getContactNameOrderAttributeChangedCb(BTPresTypes::eContactNameOredr eContactNameOrder) override;

    /*!
     * @brief   getDeviceListAttributeChangedCb: method to get callback for Device List Attribute Changed
     * @param   vectPimProperties: list of device properties
     * @return  void
     */
    void getDeviceListAttributeChangedCb(BTPresTypes::pimPropertiesList vectPimProperties) override;

    /*!
     * @brief   getEmergencyContactListAttributeChangedCb: method to get callback for Emergency Contact List Attribute Changed
     * @param   vectPhonebook: list of emergency contacts in the phonebook
     * @return  void
     */
    void getEmergencyContactListAttributeChangedCb(BTPresTypes::phonebook vectPhonebook) override;

    /*!
     * @brief   getMessageNotificationEventCb: method to get callback for Message Notification Event
     * @param   strAddress: Address of the connected device
     * @param   lMessageId: Id for message
     * @param   objSmsInfo: SMS info
     * @param   eMsgNotification: SMS notification type
     * @return  void
     */
    void getMessageNotificationEventCb(string strBtAdddress, int64_t lMessageId, BTPresTypes::smsEntry objSmsInfo, BTPresTypes::eMsgNotification eMsgNotification) override;

    /*!
     * @brief   getNewCallListEventCb: method to get callback for New Call List Event
     * @param   strBtAdddress: address of the connected device
     * @param   objCallLogInfo: new call log information
     * @return  void
     */
    void getNewCallListEventCb(string strBtAdddress, BTPresTypes::callstackEntry objCallLogInfo) override;

    /*!
     * @brief   getSessionClosedSelectiveEventCb: method to get callback for PimDb Session Closed
     * @param   ucSessionID: closed sessionID
     * @param   ucSessionQueryID: sessionQueryID
     * @param   eErrorType: error type
     * @return  void
     */
    void getSessionClosedSelectiveEventCb(uint8_t ucSessionID, uint8_t ucSessionQueryID, BTPresTypes::eErrorType eErrorType) override;

    /*!
     * @brief   getSessionQueryUpdateSelectiveEventCb: method to get callback for Session Query Update Selective Event
     * @param   ucSessionID: sessionID related to callback
     * @param   ucSessionQueryID: sessionQueryID related to callback
     * @param   usCount: count related to query
     * @param   ucReadCount: unread count related to query
     * @param   vectAlphaJumpTable: list of alpha jump table
     * @return  void
     */
    void getSessionQueryUpdateSelectiveEventCb(uint8_t ucSessionID, uint8_t ucSessionQueryID, uint16_t usCount, uint8_t ucReadCount, BTPresTypes::alphaJumpList vectAlphaJumpTable) override;

    /*!
     * @brief   getSessionQueryWindowUpdateSelectiveEventCb: method to get callback for Session Query Window Update Selective Event
     * @param   ucSessionID: sessionID related to callback
     * @param   ucSessionQueryID: sessionQueryID related to callback
     * @param   usStartIndex: start Index related to query
     * @param   ucNumItems: num Items related to query
     * @param   vectPhoneBookEntry: list of phonebook entry
     * @return  void
     */
    void getSessionQueryWindowUpdateSelectiveEventCb(uint8_t ucSessionID, uint8_t ucSessionQueryID, uint16_t usStartIndex, uint8_t ucNumItems, BTPresTypes::phonebook vectPhoneBookEntry) override;

    /*!
     * @brief   getSmsNotificationEventCb: method to get callback for Sms Notification Event
     * @param   strSmsData: SMS data
     * @param   lMessageID: SMS id
     * @param   eMsgNotification: SMS type
     * @return  void
     */
    void getSmsNotificationEventCb(string strSmsData, int64_t lMessageID, BTPresTypes::eMsgNotification eMsgNotification) override;

    /*!
     * @brief   getSmsSupportedFeatureAttributeChangedCb: method to get callback for Sms Supported Feature Attribute Changed
     * @param   vectSmsSupportedFeature: updated sms Supported Feature List
     * @return  void
     */
    void getSmsSupportedFeatureAttributeChangedCb(BTPresTypes::smsSupportedFeatureList vectSmsSupportedFeature) override;

    /*!
     * @brief   getUnreadMissedCallEventCb: method to get callback for Unread Missed Call Event
     * @param   strBtAddress: bt address of the connected device
     * @param   strContactNumber: phone number of the latest missed call
     * @param   strContactName: formatted name of the contact
     * @param   ucUnreadCount: count of the unread missed call
     * @return  void
     */
    void getUnreadMissedCallEventCb(string strBtAddress, string strPhoneNumber, string strContactName, uint8_t ucUnreadCount) override;

    /** ****************************************************
     ** @category SERVICE CALL & CALLBACK METHODS
     ** ****************************************************/

    /*!
     * @brief   openSessionAsyncReq: method to open PimDb session
     * @param   strBtAddress: bt address of connected device
     * @return  void
     */
    void openSessionAsyncReq(string strBtAddress) override;

    /*!
     * @brief   openSessionAsyncReqCb: method to get callback for open PimDb Session Async Req
     * @param   eStatus: Method call status of the request
     * @param   ucSessionID: session id
     * @param   eErrorType: error type of the method call
     * @return  void
     */
    void openSessionAsyncReqCb(const CommonAPI::CallStatus& eStatus, const uint8_t& ucSessionID, const BTPresTypes::eErrorType& eErrorType) override;

    /*!
     * @brief   setSessionQueryAsyncReqCb: method to get callback for PimDb Session Query Async Req
     * @param   eStatus: Method call status of the request
     * @param   eErrorType: error type of the method call
     * @param   uiNumResults: num Results given for query
     * @param   ucSessionQueryID: session query id
     * @param   UcUnreadCount: unread count given for query
     * @param   vectAlphaJumpTable: list of alpha jump table
     * @param   eDatabaseType: data base type related to query
     * @return  void
     */
    void setSessionQueryAsyncReqCb(const CommonAPI::CallStatus& eStatus,
                                   const BTPresTypes::eErrorType& eErrorType,
                                   const uint32_t& uiNumResults,
                                   const uint8_t& ucSessionQueryID,
                                   const uint8_t& ucUnreadCount,
                                   const  BTPresTypes::alphaJumpList& vectAlphaJumpTable,
                                   BTPresTypes::eDatabaseType eDatabaseType) override;

    /*!
     * @brief   closeSessionAsyncReq: method to close PimDb session
     * @param   void
     * @return  void
     */
    void closeSessionAsyncReq() override;

    /*!
     * @brief   closeSessionAsyncReqCb: method to get callback for close Session Async
     * @param   eStatus: Method call status of the request
     * @param   eErrorType: error type of the method call
     * @return  void
     */
    void closeSessionAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType) override;

    /*!
     * @brief   setSessionQueryWindowAsyncReq: method to set PimDb Session Query Window Async
     * @param   ucSessionID: session ID
     * @param   ucSessionQueryID: session Query ID
     * @param   usStartIndex: start Index fro data
     * @param   ucNumItems: total data count requested
     * @return  void
     */
    void setSessionQueryWindowAsyncReq(const uint8_t &ucSessionID, const uint8_t &ucSessionQueryID, const uint16_t &usStartIndex, const uint8_t &ucNumItems) override;

    /*!
     * @brief   setSessionQueryWindowAsyncReqCb: method to get callback for Session Query Window Async
     * @param   eStatus: Method call status of the request
     * @param   eErrorType: error type of the method call
     * @return  void
     */
    void setSessionQueryWindowAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType) override;

    /*!
     * @brief   getContactsByIDAsyncReq: method to get Contacts By ID async
     * @param   lDataBaseType: required data type
     * @param   lContactID: contact id
     * @return  void
     */
    void getContactsByIDAsyncReq(int64_t lDataBaseType, int64_t lContactID) override;

    /*!
     * @brief   getContactsByIDAsyncReqCb: method to get callback for Contacts By ID Async
     * @param   eStatus: Method call status of the request
     * @param   eErrorType: error type of the method call
     * @param   objPhonebookData: phonebook data
     * @return  void
     */
    void getContactsByIDAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType, const BTPresTypes::phonebookEntry &objPhonebookData) override;

    /*!
     * @brief   addContactToFavouriteListAsyncReq: method to add Contact To Favourite List Async
     * @param   lContactID: contact id of the contact
     * @param   strContactNumber: contact number to add in favorite
     * @param   lContactType: contact number type
     * @return  void
     */
    void addContactToFavouriteListAsyncReq(int64_t lContactID, string strContactNumber, int64_t lContactType) override;

    /*!
     * @brief   addContactToFavouriteListAsyncReqCb: method to get callback for add Contact To Favourite List Async
     * @param   eStatus: Method call status of the request
     * @param   eErrorType: error type of the method call
     */
    void addContactToFavouriteListAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType) override;

    /*!
     * @brief   deleteContactFromFavouriteListAsyncReq: method to delete Contact from Favourite List Async
     * @param   lFavoriteIndex: favorite Index to delete
     * @return  void
     */
    void deleteContactFromFavouriteListAsyncReq(int64_t lFavoriteIndex) override;

    /*!
     * @brief   deleteContactFromFavouriteListAsyncReqCb: method to get callback for delete Contact from Favourite List Async
     * @param   eStatus: Method call status of the request
     * @param   eErrorType: error type of the method call
     * @return  void
     */
    void deleteContactFromFavouriteListAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType) override;

    /*!
     * @brief   sendSMSAsyncReq: Method to send SMS to provided number.
     * @param   strBtAddr: bt address of the connected phone.
     * @param   strNumber: phone number to be dialled.
     * @param   strMsgText: name of the contact if available.
     * @return  void.
     */
    void sendSMSAsyncReq(const string& strBtAddr, const string& strNumber, const string& strMsgText) override;

    /*!
     * @brief   sendSMSAsyncReqCb: Method to catch call back from sendSMSAsyncReq.
     * @param   eStatus: Method call status of the request.
     * @param   eErrorType: error type of the method call.
     * @param   strRecieverNumber: reciever Number.
     * @return  void.
     */
    void sendSMSAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType, const std::string& strRecieverNumber) override;

private:
    /*!
     * @brief Pointer of CPhonePIMDBEventProvider class to
     * emit signals to the phone application layer.
     */
    CPhonePIMDBEventProvider* m_pPhonePIMDBEventProvider;

    /*!
     * @brief Instance of PimDbHandlerProxy class to communicate with
     * bt press control layer.
     */
    CAPIClientAbstraction <PimDbHandlerProxy> m_PimDbHandlerProxy;
    bool                        m_bPimDbServiceAvailable;       //! Flag to maintain PimDb proxy availability status
    int                         m_iSessionID;                   //! used to hold session id for PimDb resource
    string                      m_strDeviceBtAddr;              //! used to hold bt address for device whose PimDb session is open

    int                         m_iCallListSessionQueryID;          //! used to hold query id for PimDb resource call logs.
    int                         m_iContactListSessionQueryID;       //! used to hold query id for PimDb resource contacts.
    int                         m_iFavouriteListSessionQueryID;     //! used to hold query id for PimDb resource favourite.
    int                         m_iSmsListSessionQueryID;           //! used to hold query id for PimDb resource SMS.
    int                         m_iSMSTemplateListSessionQueryID;   //! used to hold query id for PimDb resource SMS template.
    int                         m_iFrequentDialedListSessionQueryID;//! used to hold query id for PimDb resource frequently dialed numbers.

    int                         m_iCallListCount;           //! used to hold data count for PimDb resource call logs.
    int                         m_iContactListCount;        //! used to hold data count for PimDb resource contacts.
    int                         m_iFavouriteListCount;      //! used to hold data count for PimDb resource favourite.
    int                         m_iSmsListCount;            //! used to hold data count for PimDb resource SMS.
    int                         m_iSMSTemplateListCount;    //! used to hold data count for PimDb resource SMS template.
    int                         m_iFrequentDialedListCount; //! used to hold data count for PimDb resource frequently dialed numbers.

    bool                        m_bIsCallDataReady;             //! used to hold status for PimDb resource call logs data availability.
    bool                        m_bIsContactDataReady;          //! used to hold status for PimDb resource contacts data availability.
    bool                        m_bIsFavouriteDataReady;        //! used to hold status for PimDb resource favourite data availability.
    bool                        m_bIsSmsDataReady;              //! used to hold status for PimDb resource SMS data availability.
    bool                        m_bIsSMSTemplateDataReady;      //! used to hold status for PimDb resource SMS template data availability.
    bool                        m_bIsFrequentlyDialedDataReady;//! used to hold status for PimDb resource frequently dialed numbers data availability.

    bool                        m_bIsSendingSMSAllowed;      //! used to hold can send SMS permission value.

    vector<SCallLogData>            m_vectCallListData;             //! used to hold data list for PimDb resource call logs.
    vector<SContactData>            m_vectContactListData;          //! used to hold data list for PimDb resource contacts.
    vector<SContactData>            m_vectContactDetailListData;    //! used to hold data list for PimDb resource contact details.
    vector<SContactData>            m_vectFavouriteListData;        //! used to hold data list for PimDb resource favourite.
    vector<SSmsData>                m_vectSmsListData;              //! used to hold data list for PimDb resource SMS.
    vector<SSmsTemplateData>        m_vectSMSTemplateListData;      //! used to hold data list for PimDb resource SMS template.
    vector<SFrequentlyDialledData>  m_vectFrequentlyDialedListData; //! used to hold data list for PimDb resource frequently dialed numbers.

    vector<SSmsSupportedFeatureList>    m_vectSmsSupportedFeatureList; //!List of sms supported featured devices

    EDataReadStateType          m_eCallListSyncStatus;              //! used to hold data sync status type for PimDb resource call logs.
    EDataReadStateType          m_eContactListSyncStatus;           //! used to hold data sync status type for PimDb resource contacts.
    EDataReadStateType          m_eContactDetailListSyncStatus;     //! used to hold data sync status type for PimDb resource contact details.
    EDataReadStateType          m_eFavouriteListSyncStatus;         //! used to hold data sync status type for PimDb resource favourite.
    EDataReadStateType          m_eSmsListSyncStatus;               //! used to hold data sync status type for PimDb resource SMS.
    EDataReadStateType          m_eSMSTemplateListSyncStatus;       //! used to hold data sync status type for PimDb resource SMS template.
    EDataReadStateType          m_eFrequentlyDialedListSyncStatus;  //! used to hold data sync status type for PimDb resource frequently dialed list.

    SMessageData                m_objSmsData;                   //! used to hold sms information
    SUnreadMissedCallData       m_objUnreadMissedCallData;      //! used to hold data for PimDb resource Unread missed call.
};

#endif // CPHONEPIMDBRESOURCEIMPL_H

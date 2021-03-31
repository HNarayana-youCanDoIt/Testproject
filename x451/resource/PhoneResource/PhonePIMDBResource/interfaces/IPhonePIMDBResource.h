/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          IPhonePIMDBResource.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         This file contains IPhonePIMDBResource interface that provides abstract methods to communicate
 * with the PimDbHandler proxy directly which shall be implemented by resource implementation class.
 */

#ifndef PHONEPIMDBRESOURCE_H
#define PHONEPIMDBRESOURCE_H

#include <string>
#include <vector>

//!Include the headers related to PimDbHandlerPressCtrl
#include "v5/com/harman/btpres/PimDbHandlerProxy.hpp"
#include "v7/com/harman/btpres/BTPresTypes.hpp"
#include "PhoneResource/CPhoneResourceEnums.h"

using namespace std;
using namespace v5::com::harman::btpres;
using namespace v7::com::harman::btpres;

/*!
 * @interface IPhonePIMDBResource
 * @brief This interfaces provides abstract methods to communicate with the
 * PimDbHandler proxy directly which shall be implemented by resource
 * implementation class.
 */
class IPhonePIMDBResource
{
public:

    /*!
     * @brief   virtual destructor to allow overriding by child class
     * @param   NA
     * @return  NA
     */
    virtual ~IPhonePIMDBResource(){}

    /*!
     * @brief   method to get callback for Contact Name Order Attribute Changed
     * @param   eContactNameOrder :: contact name order
     * @return  void
     */
    virtual void getContactNameOrderAttributeChangedCb(BTPresTypes::eContactNameOredr eContactNameOrder) = 0;

    /*!
     * @brief   method to get callback for Device List Attribute Changed
     * @param   vectPimProperties :: list of device properties
     * @return  void
     */
    virtual void getDeviceListAttributeChangedCb(BTPresTypes::pimPropertiesList vectPimProperties) = 0;

    /*!
     * @brief   method to get callback for Emergency Contact List Attribute Changed
     * @param   vectPhonebook :: list of emergency contacts in the phonebook
     * @return  void
     */
    virtual void getEmergencyContactListAttributeChangedCb(BTPresTypes::phonebook vectPhonebook) = 0;

    /*!
     * @brief   method to get callback for Message Notification Event
     * @param   strAddress :: Address of the connected device
     * @param   lMessageId :: Id for message
     * @param   objSmsInfo :: SMS info
     * @param   eMsgNotification :: SMS notification type
     * @return  void
     */
    virtual void getMessageNotificationEventCb(string strBtAdddress, int64_t lMessageId, BTPresTypes::smsEntry objSmsInfo, BTPresTypes::eMsgNotification eMsgNotification) = 0;

    /*!
     * @brief   method to get callback for New Call List Event
     * @param   strBtAdddress :: address of the connected device
     * @param   objCallLogInfo :: new call log information
     * @return  void
     */
    virtual void getNewCallListEventCb(string strBtAdddress, BTPresTypes::callstackEntry objCallLogInfo) = 0;

    /*!
     * @brief   method to get callback for PimDb Session Closed
     * @param   ucSessionID :: closed sessionID
     * @param   ucSessionQueryID :: sessionQueryID
     * @param   eErrorType :: error type
     * @return  void
     */
    virtual void getSessionClosedSelectiveEventCb(uint8_t ucSessionID, uint8_t ucSessionQueryID, BTPresTypes::eErrorType eErrorType) = 0;

    /*!
     * @brief   method to get callback for Session Query Update Selective Event
     * @param   ucSessionID :: sessionID related to callback
     * @param   ucSessionQueryID :: sessionQueryID related to callback
     * @param   usCount :: count related to query
     * @param   ucReadCount :: unread count related to query
     * @param   vectAlphaJumpTable :: list of alpha jump table
     * @return  void
     */
    virtual void getSessionQueryUpdateSelectiveEventCb(uint8_t ucSessionID, uint8_t ucSessionQueryID, uint16_t usCount, uint8_t ucReadCount, BTPresTypes::alphaJumpList vectAlphaJumpTable) = 0;

    /*!
     * @brief   method to get callback for Session Query Window Update Selective Event
     * @param   ucSessionID :: sessionID related to callback
     * @param   ucSessionQueryID :: sessionQueryID related to callback
     * @param   usStartIndex :: start Index related to query
     * @param   ucNumItems :: num Items related to query
     * @param   vectPhoneBookEntry :: list of phonebook entry
     * @return  void
     */
    virtual void getSessionQueryWindowUpdateSelectiveEventCb(uint8_t ucSessionID, uint8_t ucSessionQueryID, uint16_t usStartIndex, uint8_t ucNumItems, BTPresTypes::phonebook vectPhoneBookEntry) = 0;

    /*!
     * @brief   method to get callback for Sms Notification Event
     * @param   strSmsData :: SMS data
     * @param   lMessageID :: SMS id
     * @param   eMsgNotification :: SMS type
     * @return  void
     */
    virtual void getSmsNotificationEventCb(string strSmsData, int64_t lMessageID, BTPresTypes::eMsgNotification eMsgNotification) = 0;

    /*!
     * @brief   method to get callback for Sms Supported Feature Attribute Changed
     * @param   vectSmsSupportedFeature :: updated sms Supported Feature List
     * @return  void
     */
    virtual void getSmsSupportedFeatureAttributeChangedCb(BTPresTypes::smsSupportedFeatureList vectSmsSupportedFeature) = 0;

    /*!
     * @brief   method to get callback for Unread Missed Call Event
     * @param   strBtAddress :: bt address of the connected device
     * @param   strContactNumber :: phone number of the latest missed call
     * @param   strContactName :: formatted name of the contact
     * @param   ucUnreadCount :: count of the unread missed call
     * @return  void
     */
    virtual void getUnreadMissedCallEventCb(string strBtAddress, string strPhoneNumber, string strContactName, uint8_t ucUnreadCount) = 0;

    /*!
     * @brief   method to open PimDb session
     * @param   strBtAddress :: bt address of connected device
     * @return  void
     */
    virtual void openSessionAsyncReq(string strBtAddress) = 0;

    /*!
     * @brief   method to get callback for open PimDb Session Async Req
     * @param   eStatus :: Method call status of the request
     * @param   ucSessionID :: session id
     * @param   eErrorType :: error type of the method call
     * @return  void
     */
    virtual void openSessionAsyncReqCb(const CommonAPI::CallStatus& eStatus, const uint8_t& ucSessionID, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   method to get callback for PimDb Session Query Async Req
     * @param   eStatus :: Method call status of the request
     * @param   eErrorType :: error type of the method call
     * @param   uiNumResults :: num Results given for query
     * @param   ucSessionQueryID :: session query id
     * @param   ucUnreadCount :: unread count given for query
     * @param   vectAlphaJumpTable :: list of alpha jump table
     * @param   eDatabaseType :: data base type related to query
     * @return  void
     */
    virtual void setSessionQueryAsyncReqCb(const CommonAPI::CallStatus& eStatus,
                                           const BTPresTypes::eErrorType& eErrorType,
                                           const uint32_t& uiNumResults,
                                           const uint8_t& ucSessionQueryID,
                                           const uint8_t& ucUnreadCount,
                                           const  BTPresTypes::alphaJumpList& vectAlphaJumpTable,
                                           BTPresTypes::eDatabaseType eDatabaseType) = 0;

    /*!
     * @brief   method to close PimDb session
     * @param   void
     * @return  void
     */
    virtual void closeSessionAsyncReq() = 0;

    /*!
     * @brief   method to get callback for close Session Async
     * @param   eStatus :: Method call status of the request
     * @param   eErrorType :: error type of the method call
     * @return  void
     */
    virtual void closeSessionAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   method to set PimDb Session Query Window Async
     * @param   ucSessionID :: session ID
     * @param   ucSessionQueryID :: session Query ID
     * @param   usStartIndex :: start Index fro data
     * @param   ucNumItems :: total data count requested
     * @return  void
     */
    virtual void setSessionQueryWindowAsyncReq(const uint8_t &ucSessionID, const uint8_t &ucSessionQueryID, const uint16_t &usStartIndex, const uint8_t &ucNumItems) = 0;

    /*!
     * @brief   method to get callback for Session Query Window Async
     * @param   eStatus :: Method call status of the request
     * @param   eErrorType :: error type of the method call
     * @return  void
     */
    virtual void setSessionQueryWindowAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   method to get Contacts By ID async
     * @param   lDataBaseType :: required data type
     * @param   lContactID :: contact id
     * @return  void
     */
    virtual void getContactsByIDAsyncReq(int64_t lDataBaseType, int64_t lContactID) = 0;

    /*!
     * @brief   method to get callback for Contacts By ID Async
     * @param   eStatus :: Method call status of the request
     * @param   eErrorType :: error type of the method call
     * @param   objPhonebookData :: phonebook data
     * @return  void
     */
    virtual void getContactsByIDAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType, const BTPresTypes::phonebookEntry &objPhonebookData) = 0;

    /*!
     * @brief   method to add Contact To Favourite List Async
     * @param   lContactID :: contact id of the contact
	 * @param   strContactNumber :: contact number to add in favorite
     * @param   lContactType :: contact number type
     * @return  void
     */
    virtual void addContactToFavouriteListAsyncReq(int64_t lContactID, string strContactNumber, int64_t lContactType) = 0;

    /*!
     * @brief   method to get callback for add Contact To Favourite List Async
     * @param   eStatus :: Method call status of the request
     * @param   eErrorType :: error type of the method call
     */
    virtual void addContactToFavouriteListAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   method to delete Contact from Favourite List Async
     * @param   lFavoriteIndex :: favorite Index to delete
     * @return  void
     */
    virtual void deleteContactFromFavouriteListAsyncReq(int64_t lFavoriteIndex) = 0;

    /*!
     * @brief   method to get callback for delete Contact from Favourite List Async
     * @param   eStatus :: Method call status of the request
     * @param   eErrorType :: error type of the method call
     */
    virtual void deleteContactFromFavouriteListAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType) = 0;

    /*!
     * @brief   Method to send SMS to provided number.
     * @param   strBtAddr       - bt address of the connected phone.
     * @param   strNumber       - phone number to be dialled.
     * @param   strMsgText      - name of the contact if available.
     * @return  void.
     */
    virtual void sendSMSAsyncReq(const string& strBtAddr, const string& strNumber, const string& strMsgText) = 0;

    /*!
     * @brief   Method to catch call back from sendSMSAsyncReq.
     * @param   eStatus             - Method call status of the request.
     * @param   eErrorType          - error type of the method call.
     * @param   strRecieverNumber   - reciever Number.
     * @return  void.
     */
    virtual void sendSMSAsyncReqCb(const CommonAPI::CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType, const std::string& strRecieverNumber) = 0;
};

#endif // PHONEPIMDBRESOURCE_H

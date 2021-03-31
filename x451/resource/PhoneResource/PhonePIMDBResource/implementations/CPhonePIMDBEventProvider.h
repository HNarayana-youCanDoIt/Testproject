/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CPhonePIMDBEventProvider.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         This file contains CPhonePIMDBEventProvider class that shall publish events
 * whenever HMI CPhonePIMDBResource layer receive some response or callbacks from PimDbResource proxy.
 */

#ifndef CPHONEPIMDBEVENTPROVIDER_H
#define CPHONEPIMDBEVENTPROVIDER_H

#include <QObject>
#include "PhoneResource/CPhoneResourceEnums.h"

using namespace std;

class CPhonePIMDBEventProvider: public QObject
{
    Q_OBJECT

public:

    /*!
     * @brief   CPhonePIMDBEventProvider constructor
     * @param   NA
     * @return  NA
     */
    CPhonePIMDBEventProvider(QObject* pParent = 0);

    /*!
     * @brief   CPhonePIMDBEventProvider destructor
     * @param   NA
     * @return  NA
     */
    ~CPhonePIMDBEventProvider();

public:
    /*!
     * @brief   method to get PimDb service callback for PimDb Service Availability Status update
     * @param   bool PimDb Service Availability Status
     * @return  void
     */
    void updatePimDbServiceAvailableStatus(bool bPimDbServiceAvailableStatus);

    /*!
     * @brief   method to get PimDb service callback for Contact Name Order Attribute Changed
     * @param   void
     * @return  void
     */
    void onContactNameOrderAttributeChanged();

    /*!
     * @brief   method to get PimDb service callback for Device List Attribute Changed
     * @param   void
     * @return  void
     */
    void onDeviceListAttributeChanged();

    /*!
     * @brief   method to get PimDb service callback for Emergency Contact List Attribute Changed
     * @param   void
     * @return  void
     */
    void onEmergencyContactListAttributeChanged();

    /*!
     * @brief   method to get PimDb service callback for Message Notification Event
     * @param   void
     * @return  void
     */
    void onMessageNotificationEvent();

    /*!
     * @brief   method to get PimDb service callback for New Call List Event
     * @param   void
     * @return  void
     */
    void onNewCallListEvent();

    /*!
     * @brief   method to get PimDb service callback for Session Closed Selective Event
     * @param   void
     * @return  void
     */
    void onSessionClosedSelectiveEvent();

    /*!
     * @brief   method to get PimDb service callback for Session Query Update Selective Event
     * @param   void
     * @return  void
     */
    void onSessionQueryUpdateSelectiveEvent();

    /*!
     * @brief   method to get PimDb service callback for Session Query Window Update Selective Event
     * @param   void
     * @return  void
     */
    void onSessionQueryWindowUpdateSelectiveEvent();

    /*!
     * @brief   method to get PimDb service callback for Sms Notification Event
     * @param   void
     * @return  void
     */
    void onSmsNotificationEvent();

    /*!
     * @brief   method to get PimDb service callback for Sms Supported Feature Attribute Changed
     * @param   void
     * @return  void
     */
    void onSmsSupportedFeatureAttributeChanged();

    /*!
     * @brief   method to get PimDb service callback for Can Send SMS Attribute Changed
     * @param   bool Can Send SMS
     * @return  void
     */
    void onIsSendingSMSAllowedAttributeChanged(bool bIsSendingSMSAllowed);

    /*!
     * @brief   method to get PimDb service callback for Unread Missed Call Event
     * @param   void
     * @return  void
     */
    void onUnreadMissedCallEvent();

    /*!
     * @brief   method to get sms dupported featured list
     * @param   void
     * @return  void
     */
    void onGetSmsSupportedFeatureAttributeChanged();

    /*!
     * @brief   method to get PimDb service callback for Open Session Async Method Call Status
     * @param   void
     * @return  void
     */
    void onOpenSessionAsyncMethodCallStatus();

    /*!
     * @brief   method to get PimDb service callback for Set Session Query Async Method Call Status
     * @param   void
     * @return  void
     */
    void onSetSessionQueryAsyncMethodCallStatus();

    /*!
     * @brief   method to get PimDb service callback for Close Session Async Method Call Status
     * @param   void
     * @return  void
     */
    void onCloseSessionAsyncMethodCallStatus();

    /*!
     * @brief   method to get PimDb service callback for Set Session Query Window Async Method Call Status
     * @param   void
     * @return  void
     */
    void onSetSessionQueryWindowAsyncMethodCallStatus();

    /*!
     * @brief   method to get PimDb service callback for Get Contacts By ID Async Method Call Status
     * @param   void
     * @return  void
     */
    void onGetContactsByIDAsyncMethodCallStatus();

    /*!
     * @brief   method to get PimDb service callback for Add Contact To Favourite List Async Method Call Status
     * @param   void
     * @return  void
     */
    void onAddContactToFavouriteListAsyncMethodCallStatus();

    /*!
     * @brief   method to get PimDb service callback for Delete Contact From Favourite List Async Method Call Status
     * @param   void
     * @return  void
     */
    void onDeleteContactFromFavouriteListAsyncMethodCallStatus();

    /*!
     * @brief   method to get PimDb service callback for Call Log Status Changed
     * @param   iStatus - changed call log sync status
     * @return  void
     */
    void onCallLogStatusChanged(int iStatus);

    /*!
     * @brief   method to get PimDb service callback for Contact Status Changed
     * @param   iStatus - changed contact sync status
     * @return  void
     */
    void onContactStatusChanged(int iStatus);

    /*!
     * @brief   method to get PimDb service callback for Contact detail Status Changed
     * @param   iStatus - changed contact detail sync status
     * @return  void
     */
    void onContactDetailStatusChanged(int iStatus);

    /*!
     * @brief   method to get PimDb service callback for Favorite Status Changed
     * @param   iStatus - changed favorite log sync status
     * @return  void
     */
    void onFavoriteStatusChanged(int iStatus);

    /*!
     * @brief   onFrequentlyDialedStatusChanged: method to get PimDb service callback for frequently dialed status changed.
     * @param   iStatus: changed frequently dialed sync status
     * @return  void.
     */
    void onFrequentlyDialedStatusChanged(int iStatus);

    /*!
     * @brief   method to get PimDb service callback for SMS Status Changed
     * @param   iStatus - changed sms log sync status
     * @return  void
     */
    void onSMSStatusChanged(int iStatus);

    /*!
     * @brief   method to get PimDb service callback for SMS Template Status Changed
     * @param   iStatus - changed sms template log sync status
     * @return  void
     */
    void onSMSTemplateStatusChanged(int iStatus);

    /*!
     * @brief   method to get PimDb service callback for Call Log Updated
     * @param   void
     * @return  void
     */
    void onCallLogUpdated();

    /*!
     * @brief   onFrequentlyDialedListUpdated: method to get PimDb service callback for frequently dialed list update.
     * @param   void
     * @return  void
     */
    void onFrequentlyDialedListUpdated();

    /*!
     * @brief   method to get PimDb service callback for Contact Updated
     * @param   usStartIndex: start index of the contact data list received.
     * @return  void
     */
    void onContactUpdated(unsigned short usStartIndex);

    /*!
     * @brief   method to get PimDb service callback for Contact Detail Updated
     * @param   void
     * @return  void
     */
    void onContactDetailUpdated();

    /*!
     * @brief   method to get PimDb service callback for Favorite Updated
     * @param   void
     * @return  void
     */
    void onFavoriteUpdated();

    /*!
     * @brief   method to get PimDb service callback for SMS Updated
     * @param   void
     * @return  void
     */
    void onSMSUpdated();

    /*!
     * @brief   method to get PimDb service callback for SMS Template Updated
     * @param   void
     * @return  void
     */
    void onSMSTemplateUpdated();

    /*!
     * @brief   method to get result of add contact to favorite
     * @param   bool is operation callback successful
     * @return  void
     */
    void onAddContactToFavouriteComplete(bool bIsSuccess);

    /*!
     * @brief   method to get result of remove contact from favorite
     * @param   bool is operation callback successful
     * @return  void
     */
    void onRemoveContactFromFavouriteComplete(bool bIsSuccess);

    /*!
     * @brief   method to get result of send SMS async request
     * @param   bool is operation callback successful
     * @return  void
     */
    void onSendSMSComplete(bool bIsSuccess);

signals:

    /*!
     * @brief   method to emit Qml signal for Service Availability Status Changed
     * @param   bool PimDb Service Availability Status
     * @return  void
     */
    void sigPimDbServiceAvailableStatusChanged(bool bPimDbServiceAvailableStatus);

    /*!
     * @brief   method to emit Qml signal for Contact Name Order Attribute Changed
     * @param   void
     * @return  void
     */
    void sigContactNameOrderAttributeChanged();

    /*!
     * @brief   method to emit Qml signal for Device List Attribute Changed
     * @param   void
     * @return  void
     */
    void sigDeviceListAttributeChanged();

    /*!
     * @brief   method to emit Qml signal for Emergency Contact List Attribute Changed
     * @param   void
     * @return  void
     */
    void sigEmergencyContactListAttributeChanged();

    /*!
     * @brief   method to emit Qml signal for Message Notification Event
     * @param   void
     * @return  void
     */
    void sigMessageNotificationEvent();

    /*!
     * @brief   method to emit Qml signal for New Call List Event
     * @param   void
     * @return  void
     */
    void sigNewCallListEvent();

    /*!
     * @brief   method to emit Qml signal for PimDb Session Closed Selective Event
     * @param   void
     * @return  void
     */
    void sigSessionClosedSelectiveEvent();

    /*!
     * @brief   method to emit Qml signal for Session Query Update Selective Event
     * @param   void
     * @return  void
     */
    void sigSessionQueryUpdateSelectiveEvent();

    /*!
     * @brief   method to emit Qml signal for Session Query Window Update Selective Event
     * @param   void
     * @return  void
     */
    void sigSessionQueryWindowUpdateSelectiveEvent();

    /*!
     * @brief   method to emit Qml signal for Sms Notification Event
     * @param   void
     * @return  void
     */
    void sigSmsNotificationEvent();

    /*!
     * @brief   method to emit Qml signal for Sms Supported Feature Attribute Changed
     * @param   void
     * @return  void
     */
    void sigSmsSupportedFeatureAttributeChanged();

    /*!
     * @brief   method to emit Qml signal for SMS send permission Changed
     * @param   bool can send SMS
     * @return  void
     */
    void sigIsSendingSMSAllowedAttributeChanged(bool bIsSendingSMSAllowed);

    /*!
     * @brief   method to emit Qml signal for Unread Missed Call Event
     * @param   void
     * @return  void
     */
    void sigUnreadMissedCallEvent();

    /*!
     * @brief   method to emit Qml signal for getting sms supported feature attribute changed Event
     * @param   void
     * @return  void
     */
    void sigGetSmsSupportedFeature();

    /*!
     * @brief   method to emit Qml signal for Open Session Async Method Call Status
     * @param   void
     * @return  void
     */
    void sigOpenSessionAsyncMethodCallStatus();

    /*!
     * @brief   method to emit Qml signal for Set Session Query Async Method Call Status
     * @param   void
     * @return  void
     */
    void sigSetSessionQueryAsyncMethodCallStatus();

    /*!
     * @brief   method to emit Qml signal for Close Session Async Method Call Status
     * @param   void
     * @return  void
     */
    void sigCloseSessionAsyncMethodCallStatus();

    /*!
     * @brief   method to emit Qml signal for Set Session Query Window Async Method Call Status
     * @param   void
     * @return  void
     */
    void sigSetSessionQueryWindowAsyncMethodCallStatus();

    /*!
     * @brief   method to emit Qml signal for Get Contacts By ID Async Method Call Status
     * @param   void
     * @return  void
     */
    void sigGetContactsByIDAsyncMethodCallStatus();

    /*!
     * @brief   method to emit Qml signal for Add Contact To Favourite List Async Method Call Status
     * @param   void
     * @return  void
     */
    void sigAddContactToFavouriteListAsyncMethodCallStatus();

    /*!
     * @brief   method to emit Qml signal for Delete Contact From Favourite List Async Method Call Status
     * @param   void
     * @return  void
     */
    void sigDeleteContactFromFavouriteListAsyncMethodCallStatus();

    /*!
     * @brief   method to emit Qml signal for Call Log Status Changed
     * @param   iStatus -  Call Log sync status
     * @return  void
     */
    void sigCallLogStatusChanged(int iStatus);

    /*!
     * @brief   method to emit Qml signal for Contact Status Changed
     * @param   iStatus - Contact sync Status
     * @return  void
     */
    void sigContactStatusChanged(int iStatus);

    /*!
     * @brief   method to emit Qml signal for Contact Detail Status Changed
     * @param   iStatus - Contact Detail sync Status
     * @return  void
     */
    void sigContactDetailStatusChanged(int iStatus);


    /*!
     * @brief   method to emit Qml signal for Favorite Status Changed
     * @param   iStatus - Favorite sync Status
     * @return  void
     */
    void sigFavoriteStatusChanged(int iStatus);

    /*!
     * @brief   sigFrequenltDialedStatusChanged: method to emit Qml signal for frequently dialed status changed.
     * @param   iStatus: frequently dialed status
     * @return  void
     */
    void sigFrequenltDialedStatusChanged(int iStatus);

    /*!
     * @brief   method to emit Qml signal for SMS Status Changed
     * @param   iStatus - SMS sync Status
     * @return  void
     */
    void sigSMSStatusChanged(int iStatus);

    /*!
     * @brief   method to emit Qml signal for SMS Template Status Changed
     * @param   iStatus - SMS Template sync Status
     * @return  void
     */
    void sigSMSTemplateStatusChanged(int iStatus);

    /*!
     * @brief   method to emit Qml signal for Call Log Updated
     * @param   void
     * @return  void
     */
    void sigCallLogUpdated();

    /*!
     * @brief   sigFrequentlyDialedListUpdated: method to emit Qml signal for frequently dialed list updated.
     * @param   void
     * @return  void
     */
    void sigFrequentlyDialedListUpdated();

    /*!
     * @brief   method to emit Qml signal for Contact Updated
     * @param   usStartIndex: start index of the contact data list received.
     * @return  void
     */
    void sigContactUpdated(unsigned short usStartIndex);

    /*!
     * @brief   method to emit Qml signal for Contact Detail Updated
     * @param   void
     * @return  void
     */
    void sigContactDetailUpdated();

    /*!
     * @brief   method to emit Qml signal for Favorite Updated
     * @param   void
     * @return  void
     */
    void sigFavoriteUpdated();

    /*!
     * @brief   method to emit Qml signal for SMS Updated
     * @param   void
     * @return  void
     */
    void sigSMSUpdated();

    /*!
     * @brief   method to emit Qml signal for SMS Template Updated
     * @param   void
     * @return  void
     */
    void sigSMSTemplateUpdated();

    /*!
     * @brief   method to emit Qml signal for Add Contact to Favourite Complete callback
     * @param   bool is operation callback successful
     * @return  void
     */
    void sigAddContactToFavouriteComplete(bool);

    /*!
     * @brief   method to emit Qml signal for Remove Contact From Favourite Complete callback
     * @param   bool is operation callback successful
     * @return  void
     */
    void sigRemoveContactFromFavouriteComplete(bool);

    /*!
     * @brief   method to emit Qml signal for send SMS callback
     * @param   bool is operation callback successful
     * @return  void.
     */
    void sigSendSMSAsyncMethodCallStatus(bool);
};

#endif // CPHONEPIMDBEVENTPROVIDER_H

/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CPhoneAdaptor.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPhoneAdaptor class that stores all the data needed by QMl screens or
 * other adaptor module. It also communicates with QML and Phone resource layer.
 */

#ifndef CPHONEADAPTOR_H
#define CPHONEADAPTOR_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <string>
#include "HMIIncludes.h"
#include "CFramework.h"
#include "CDeviceSearchListModel.h"
#include "CPairedDeviceListModel.h"
#include "CPhoneSetupListModel.h"
#include "CConfParticipantsListModel.h"
#include "CPhoneEnum.h"
#include "CCallLogListModel.h"
#include "CContactDetailListModel.h"
#include "CPhoneBrowseTabBarModel.h"

#include "PhoneResource/CPhoneResourceData.h"

//! @category FORWARD DECLERATIONS
class CPhoneConnectionManagerResourceImpl;
class CPhoneCallManagerResourceImpl;
class CPhonePIMDBResourceImpl;

using namespace std;

//===========================================================================================================
/*
 * TODO
 * 1. In phone browse screen or phone call screen and phone got disconnected then switch to home screen
 * 2. Reset call info data for active, held, incoming call when device gets disconnected for hfp
 * 3. Clear call info data in hfp disconnection
 * 4. Check for MISRA code standard changes like if condition should have default else, etc.
 * 5. Call state parsing related optimisation
 * 6. need to change the API signature, instead of bool the API needs to take enum as a param and pass it to connection
 * manager resource. From QML we should pass the appropriate profile enum for which serviceConnection should happen.
 * 7. Clearing the list first and then updating the list again results in reseting of the scrollbar, if
 * currently we are in third page of the list and list is created again then the list jumps to first page again
 * resulting in scrollbar jump. We need to check list property where we can make a backup of list
 * property(top item, focused item) and shall be able to restore thopse properties again after we create the list.
 * 8. Add HfModeReqStatus to disable the HfMode button till the response/status is not received as success or faliure.
 * 9. Add Network not available popup. This shall be shown if network is not available and user try to dial a number.
 * 10. Check for LOG_INFO warnings in complete phone module
 */
//============================================================================================================

/*!
 * @class CPhoneAdaptor
 * @brief This is a singletone class that stores all the data needed by QMl screens or
 * other adaptor module. It also communicates with QML and Phone resource layer.
 */
class CPhoneAdaptor: public QObject
{
    Q_OBJECT
    /************************************************************************//**
     * @category   BT CONNECTION RELATED Q_PROPERTY
     ************************************************************************/
    //! property for qml to get updated passkey pin
    Q_PROPERTY(QString passKeyPin                               READ passKeyPin             NOTIFY sigPassKeyPinUpdated)
    //! property for qml to get updated device name connected for HFP/A2DP profile
    Q_PROPERTY(QString connectedDeviceName                      READ connectedDeviceName    NOTIFY sigConnectedDeviceNameUpdated)
    //! property for qml to get update whether ay device is connected for HFP/A2DP profile
    Q_PROPERTY(bool deviceConnected                             READ deviceConnected        NOTIFY sigDeviceConnectionUpdated)
    //! property for qml to get updated HU bluetooth status
    Q_PROPERTY(bool bluetoothStatus                             READ bluetoothStatus        NOTIFY sigBluetoothStatusUpdated)
    //! property for qml to get updated device search status
    Q_PROPERTY(bool deviceSearchStatus                          READ deviceSearchStatus     NOTIFY sigDeviceSearchStatus)
    //! property for qml to get updated about the visibility request status change
    Q_PROPERTY(bool btVisibilityReqStatus                       READ btVisibilityReqStatus  NOTIFY sigBtVisibilityReqStatusUpdated)
    /*** The below properties shall not be used for dynamic updates hence notify property is not added ***/
    //! property for qml to get updated device name disconnected for HFP/A2DP profile
    Q_PROPERTY(QString disconnectedDeviceName                   READ disconnectedDeviceName CONSTANT)
    //! property for qml to get the name of the deleted device
    Q_PROPERTY(QString deletedDeviceName                        READ deletedDeviceName      CONSTANT)
    //! property for qml to get updated selected item name
    Q_PROPERTY(QString selItemName                              READ selItemName            CONSTANT)
    //! property for qml to get updated selected item bt address
    Q_PROPERTY(QString selItemBtAddr                            READ selItemBtAddr          CONSTANT)
    //! property for qml to get updated hfp connection status
    Q_PROPERTY(bool hfpConnectionStatus                         READ hfpConnectionStatus    NOTIFY sigHFPConnectionStatus)
    //! property for qml to get device search list model
    Q_PROPERTY(QAbstractListModel* deviceSearchListModel        READ deviceSearchListModel  CONSTANT)
    //! property for qml to get device search list model
    Q_PROPERTY(QAbstractListModel* pairedDeviceListModel        READ pairedDeviceListModel  CONSTANT)
    //! property for qml to get bt setup list model
    Q_PROPERTY(QAbstractListModel* phoneSetupListModel          READ phoneSetupListModel    CONSTANT)

    /************************************************************************//**
     * @category   PHONE CALL RELATED Q_PROPERTY
     ************************************************************************/
    //! property for qml to get incoming caller information
    Q_PROPERTY(CCallInfo* incomingCallInfo                          READ incomingCallInfo               CONSTANT)
    //! property for qml to get first caller information
    Q_PROPERTY(CCallInfo* firstCallerInfo                           READ firstCallerInfo                CONSTANT)
    //! property for qml to get second caller information
    Q_PROPERTY(CCallInfo* secondCallerInfo                          READ secondCallerInfo               CONSTANT)
    //! property for qml to get accept call request status
    Q_PROPERTY(bool acceptCallReqStatus                             READ acceptCallReqStatus            NOTIFY sigAcceptCallReqStatusUpdated)
    //! property for qml to get reject call request status
    Q_PROPERTY(bool rejectCallReqStatus                             READ rejectCallReqStatus            NOTIFY sigRejectCallReqStatusUpdated)
    //! property for qml to get sending SMS status
    Q_PROPERTY(bool sendSMSReqStatus                                READ sendSMSReqStatus               NOTIFY sigSendSMSReqStatusUpdated)
    //! property for qml to get dial request status
    Q_PROPERTY(bool dialReqStatus                                   READ dialReqStatus                  NOTIFY sigDialReqStatusUpdated)
    //! property for qml to get merge call request status
    Q_PROPERTY(bool mergeCallsReqStatus                             READ mergeCallsReqStatus            NOTIFY sigMergeCallsReqStatusUpdated)
    //! property for qml to get swap call request status
    Q_PROPERTY(bool swapCallsReqStatus                              READ swapCallsReqStatus             NOTIFY sigSwapCallsReqStatusUpdated)
    //! property for qml to get resume call request status
    Q_PROPERTY(bool resumeCallReqStatus                             READ resumeCallReqStatus            NOTIFY sigResumeCallReqStatusUpdated)
    //! property for qml to get hold call request status
    Q_PROPERTY(bool holdCallReqStatus                               READ holdCallReqStatus              NOTIFY sigHoldCallReqStatusUpdated)
    //! property for qml to get end call request status
    Q_PROPERTY(bool endCallReqStatus                                READ endCallReqStatus               NOTIFY sigEndCallReqStatusUpdated)
    //! property for qml to get hf mode request status
    Q_PROPERTY(bool hfModeReqStatus                                 READ hfModeReqStatus                NOTIFY sigHFModeReqStatusUpdated)
    //! property for qml to get handsfree mode status
    Q_PROPERTY(bool handsFreeModeStatus                             READ handsFreeModeStatus            NOTIFY sigHandsFreeModeStatusUpdated)
    //! property for qml to get signal strength level
    Q_PROPERTY(CPhoneEnum::ESignalStrengthLevel signalStrengthLevel READ signalStrengthLevel            NOTIFY sigSignalStrengthLevelUpdated)
    //! property for qml to get battery charge level
    Q_PROPERTY(CPhoneEnum::EBatteryChargeLevel batteryChargeLevel   READ batteryChargeLevel             NOTIFY sigBatteryChargeLevelUpdated)
    //! property for qml to get current phone call state
    Q_PROPERTY(CPhoneEnum::EPhoneCallState phoneCallState           READ phoneCallState                 NOTIFY sigPhoneCallStateUpdated)
    //! property for qml to get conference participants list model
    Q_PROPERTY(QAbstractListModel* confParticipantsListModel        READ confParticipantsListModel      CONSTANT)
    //! property for qml to get DTMF Number pad on status
    Q_PROPERTY(bool isInDTMFNumberPad                               READ isInDTMFNumberPad              NOTIFY sigDTMFNumberPadStatusUpdated)

    /************************************************************************//**
     * @category   PHONE BROWSE RELATED Q_PROPERTY
     ************************************************************************/
    /** Property hold model for phone browse tab bar */
    Q_PROPERTY(CPhoneBrowseTabBarModel* pPhoneBrowseTabBarModel         READ pPhoneBrowseTabBarModel    CONSTANT)
    /** Property hold current phone browse screen enum */
    Q_PROPERTY(CPhoneEnum::EPhoneBrowseType eCurrentPhoneBrowseScreen   READ eCurrentPhoneBrowseScreen  NOTIFY sigCurrentPhoneBrowseScreenChanged)

    /************************************************************************//**
     * @category   PHONE PIMDB RELATED Q_PROPERTY
     ************************************************************************/
    //! property for qml to get call Logs List Model
    Q_PROPERTY(CCallLogListModel* callLogListModel                                 READ callLogListModel                       NOTIFY sigCallLogListModelUpdated)
    //! property for qml to get frequently dialed List Model
    Q_PROPERTY(CCallLogListModel* frequentlyDialedListModel                        READ frequentlyDialedListModel              NOTIFY sigFrequentlyDialedListModelUpdated)
    //! property for qml to get contacts List Model
    Q_PROPERTY(CContactDetailListModel* contactListModel                           READ contactListModel                       NOTIFY sigContactListModelUpdated)
    //! property for qml to get contact Details List Model
    Q_PROPERTY(CContactDetailListModel* contactDetailListModel                     READ contactDetailListModel                 NOTIFY sigContactDetailListModelUpdated)
    //! property for qml to get favorite Contacts List Model
    Q_PROPERTY(CContactDetailListModel* favoriteContactListModel                   READ favoriteContactListModel               NOTIFY sigFavoriteContactListModelUpdated)
    //! property for qml to get call Logs Sync Status
    Q_PROPERTY(CPhoneEnum::EPhoneSyncStatus pimDbCallListSyncStatus                READ pimDbCallListSyncStatus                NOTIFY sigPimDbCallListSyncUpdated)
    //! property for qml to get contacts Sync Status
    Q_PROPERTY(CPhoneEnum::EPhoneSyncStatus pimDbContactListSyncStatus             READ pimDbContactListSyncStatus             NOTIFY sigPimDbContactListSyncUpdated)
    //! property for qml to get contact Details Sync Status
    Q_PROPERTY(CPhoneEnum::EPhoneSyncStatus pimDbContactDetailSyncStatus           READ pimDbContactDetailSyncStatus           NOTIFY sigPimDbContactDetailSyncUpdated)
    //! property for qml to get favorite Contacts Sync Status
    Q_PROPERTY(CPhoneEnum::EPhoneSyncStatus pimDbFavouriteListSyncStatus           READ pimDbFavouriteListSyncStatus           NOTIFY sigPimDbFavouriteListSyncUpdated)
    //! property for qml to get favorite Contacts Sync Status
    Q_PROPERTY(CPhoneEnum::EPhoneSyncStatus pimDbFrequentlyDialedListSyncStatus    READ pimDbFrequentlyDialedListSyncStatus    NOTIFY sigPimDbFrequentlyDialedListSyncUpdated)

    /************************************************************************//**
     * @category   Keypad Related Property
     ************************************************************************/
    //! property for qml which holds the input text when user has clicked edit button to edit the corresponding text message.
    Q_PROPERTY(QString textInputMessage                                     READ textInputMessage                       NOTIFY sigTextInputMessageChanged)
    //! property for qml to get New SMS Sender name
    Q_PROPERTY(QString smsSenderName                                        READ smsSenderName                          NOTIFY sigSMSSenderNameChanged)
    //! property for qml to get New SMS Sender number
    Q_PROPERTY(QString smsSenderNumber                                      READ smsSenderNumber                        NOTIFY sigSMSSenderNumberChanged)
    //! property for qml to get New SMS data
    Q_PROPERTY(QString smsData                                              READ smsData                                NOTIFY sigSMSDataChanged)
    //! property for qml to get Reading SMS Sender name
    Q_PROPERTY(QString readingSMSSenderName                                 READ readingSMSSenderName                   NOTIFY sigReadingSMSSenderNameChanged)
    //! property for qml to get Reading SMS Sender number
    Q_PROPERTY(QString readingSMSSenderNumber                               READ readingSMSSenderNumber                 NOTIFY sigReadingSMSSenderNumberChanged)
    //! property for qml to get Reading SMS data
    Q_PROPERTY(QString readingSMSData                                       READ readingSMSData                         NOTIFY sigReadingSMSDataChanged)
    //! property for qml to get favorite toggling process status
    Q_PROPERTY(bool isFavoriteToggling                                      READ isFavoriteToggling                     NOTIFY sigIsFavoriteTogglingUpdated)
    //! property for qml to get which contact name is toggling for favorite
    Q_PROPERTY(QString favoriteTogglingContactName                          READ favoriteTogglingContactName            CONSTANT)
    //! property for qml to get which contact number is toggling for favorite
    Q_PROPERTY(QString favoriteTogglingContactNumber                        READ favoriteTogglingContactNumber          CONSTANT)
    //! property for qml to get last contact list top index
    Q_PROPERTY(int contactListCurrentTopIndex                               READ contactListCurrentTopIndex             WRITE setContactListCurrentTopIndex     NOTIFY sigContactListCurrentTopIndexUpdated)
    //! property for qml to get value of is Sending SMS Allowed permission
    Q_PROPERTY(int isSendingSMSAllowed                                      READ isSendingSMSAllowed                    NOTIFY sigIsSendingSMSAllowedChanged)
    //! property for qml to get unread missed call count
    Q_PROPERTY(QString phoneNotificationText                                READ phoneNotificationText                  NOTIFY sigPhoneNotificationTextChanged)
    //! property for qml to check if a call exists or not
    Q_PROPERTY(bool doesCallExist                                           READ doesCallExist                          NOTIFY sigPhoneCallStateUpdated)

    //! property for qml to check if a Low priority phone related popup is active
    Q_PROPERTY(bool lowPriorityPopupActive                                  READ lowPriorityPopupActive                 WRITE invSetLowPriorityPopupActiveStatus         NOTIFY sigLowPriorityPopupActiveUpdated)

public:
    ~CPhoneAdaptor();

    /************************************************************************//**
     * @category    METHODS
     ************************************************************************/

    /*!
     * @brief   Method to create and get singleton instance of CPhoneAdaptor class.
     * @param   void.
     * @return  pointer to the object of CPhoneAdaptor class.
     */
    static CPhoneAdaptor *getInstance();

    /*!
     * @brief   resetPimdbProperties - Method to reset pimdb related properties.
     * @param   void.
     * @return  void.
     */
    void resetPimdbProperties();
	
	/**
     * @brief   showHidePhoneBtVROverlay: This function is used to show or hide the phone bt VR Overlay.
     * @param   bShowPhoneBtVROverLay: true if need to show the phone bt VR overlay, false to hide.
     * @return  void.
     */
    void showHidePhoneBtVROverlay(bool bShowPhoneBtVROverLay);

    /*!
     * @brief   Method to create phone related data models.
     * @param   void.
     * @return  void.
     */
    void initPhoneDataModels();

    /*!
     * @brief   reqPhoneBtVrActivation: Method to be invoked to request activation of phone bt vr.
     * @param   void.
     * @return  void.
     */
    void reqPhoneBtVrActivation();

    /*!
     * @brief   invReqPhoneBtVrDeactivation: Method to be invoked to request deactivation of phone bt vr.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invReqPhoneBtVrDeactivation();

    /**
     * @brief   isPhoneBtVROverlayVisible: This function is used to know that the phone bt VR Overlay
     *          is currently visible or not.
     * @param   void.
     * @return  bool: true if phone bt VR overlay is visible, otherwise false
     */
    bool isPhoneBtVROverlayVisible();

    /**
    * @brief    getProjPhConnectionStatus: Method to get the projection(Android Auto or
    *           Carplay) connection status whether the projection(Android Auto or Carplay)
    *           phone is connected or not.
    * @param    void.
    * @return   TRUE if projection(Android Auto or Carplay) phone is connected, FALSE otherwise.
    */
    bool getProjPhConnectionStatus();

    /**
    * @brief    Method to handle hardkey as per phone specifications.
    * @param    eKey        - key on which the action is triggered.
    * @param    eKeyState   - state of the key on which the action is triggered.
    * @return   true if the action was taken otherwise false.
    */
    Q_INVOKABLE bool invHandleHardKeys(CHardKeyEnum::EHardKeys eKey, CHardKeyEnum::EHardKeyState eKeyState);

    /**
    * @brief    invGetLastDialedNumber: Method to be invoked to get the last dialed number.
    * @param    void.
    * @return   value of last dialled number.
    */
    Q_INVOKABLE QString invGetLastDialedNumber();

    /**
    * @brief	invGetBrowseType: Method to get browse type of the tab bar item.
    * @param	iItemIndex: Tab bar item index.
    * @return	Browse type of the tab bar item.
    **/
    Q_INVOKABLE int invGetBrowseType(int iItemIndex);

    /**
    * @brief	invGetBrowseItemIndex: Method to get tab bar browse item index.
    * @param	iPhoneBrowseType: Tab bar item browse type.
    * @return	tab bar browse itme index.
    **/
    Q_INVOKABLE int invGetBrowseItemIndex(int iPhoneBrowseType);

    /*!
     * @brief   invResetSelectedItemInfo: Method to reset selected item information.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invResetSelectedItemInfo();


    /*!
     * @brief   invSetLowPriorityPopupActiveStatus: Method to set the low priority sms/call popup status.
     * @param   bLPPhonePopupStatus: low priority phone popup status that has to be set.
     * @return  void.
     */
    Q_INVOKABLE void invSetLowPriorityPopupActiveStatus(bool bLPPhonePopupStatus);

    /**
      @brief    invGetPreviousListCount: Method to get the last saved paired list count
      @param    void.
      @return   m_iPreviousPairedListCount: Prvious Paired List count.
      **/
    Q_INVOKABLE int invGetPreviousListCount() { return m_iPreviousPairedListCount; }

    /**
      @brief    invGetCurrentListCount: Method to get the current saved paired list count
      @param    void.
      @return   m_iCurrentPairedListCount: Current Paired List count.
      **/
    Q_INVOKABLE int invGetCurrentListCount() { return m_iCurrentPairedListCount; }


    /**
     * @brief   selectContactDetailsCategory: Method to be invoked to set focus on the passed category.
     * @param   strCategory: category to be highlighted.
     * @return  TRUE if the category is valid, FALSE otherwise.
     */
    bool selectContactDetailsCategory(const QString& strCategory);

    /**
    * @brief    Method to get whether the current call is active/outgoing or not.
    * @param    void.
    * @return   true if the call is active/outgoing, false otherwise.
    */
    bool isCallActive();

    /**
    * @brief    isCallIncoming: Method to get whether the current call is incoming or not.
    * @param    void.
    * @return   true if the call is incoming, false otherwise.
    */
    bool isCallIncoming();

    /**
    * @brief    Method to get whether the call exist, i.e. call can be incoming/outgoing/active.
    * @param    void.
    * @return   true if the call exist, false otherwise.
    */
    bool doesCallExist();

    /**
    * @brief    lowPriorityPopupActive: Method to get the low Priority popup active status.
    * @param    void.
    * @return   true if the low priority popup is active whether its sms or call , false otherwise.
    */
    bool lowPriorityPopupActive();

    /**
     * @brief   switchToContactDetails: Method to be invoked to switch to contact details screen.
     * @param   iContactId: Contact Id of the contact.
     * @return  void.
     */
    void switchToContactDetails(int iContactId);

    /**
     * @brief   updateCallInPdcRvc: Internal method to be invoked to take necessary action for call
     *          on transition to PDC/RVC state.
     * @param   void.
     * @return  void.
     */
    void updateCallInPdcRvc();

    /**
     * @brief   updateCallInNative: Internal method to be invoked to take necessary action for call
     *          on transition to Native state.
     * @param   void.
     * @return  void.
     */
    void updateCallInNative();

    /**
     * @brief   updateSmsInPdcRvc: Internal method to be invoked to take necessary action for sms
     *          on transition to PDC/RVC state.
     * @param   void.
     * @return  void.
     */
    void updateSmsInPdcRvc();

    /**
     * @brief   updateSmsInNative: Internal method to be invoked to take necessary action for sms
     *          on transition to Native state.
     * @param   void.
     * @return  void.
     */
    void updateSmsInNative();

    /**
     * @brief   takeActionForPhoneInterrupts: Method to be invoked to update take appropriate actions for
     *          phone interrupts.
     * @param   void.
     * @return  void.
     */
    void takeActionForPhoneInterrupts();

    /**
     * @brief   setIncomingSmsPopupStatus: Method to reset the incoming sms popup state to default(false)
     * @param   void.
     * @return  void.
     */
    void resetIncomingSmsPopupState();

    /**
     * @brief   resetDeleteAllDevicesSelStatus: Method to reset delte all devices selection status.
     * @param   void.
     * @return  void.
     */
    void resetDeleteAllDevicesSelStatus();

    /**
     * @brief   showSmsSentPopup: Method to be invoked to show sms sent popup.
     * @param   void.
     * @return  void.
     */
    void showSmsSentPopup();

    /**
     * @brief   getDeleteAllDevicesStatus: Method to be invoked to get delete all devices status.
     * @param   void.
     * @return  TRUE if delete all devices is success, FALSE otherwise.
     */
    bool getDeleteAllDevicesStatus() { return m_bDeleteAllDevicesStatus; }

    /**
     * @brief   getDeleteDeviceStatus: Method to be invoked to get delete device status.
     * @param   void.
     * @return  TRUE if delete device is success, FALSE otherwise.
     */
    bool getDeleteDeviceStatus() { return m_bDeleteDeviceStatus; }

    /************************************************************************//**
     * @category   BT CONNECTION METHODS
     ************************************************************************/
    /*!
     * @brief   Method to inform connection manager resource to start device search.
     * @param   void.
     * @return  void.
     */
    void startDeviceSearch();

    /*!
     * @brief   Method to inform connection manager resource to stop device search.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invStopDeviceSearch();

    /*!
     * @brief   Method to set bluetooth status.
     * @param   bBtStatus - status of the bluetooth whether enable or not.
     * @return  void.
     */
    void updateBluetoothStatus(bool bBtStatus);

    /*!
     * @brief   Method to set pass key pin.
     * @param   strPassKey - passkey generated at time of pairing with a new device.
     * @return  void.
     */
    void updatePassKey(const string& strPassKey);

    /*!
     * @brief   Method to set device search status.
     * @param   bDeviceSearchStatus - Device search status whether started or stopped.
     * @return  void.
     */
    void updateDeviceSearchStatus(bool bDeviceSearchStatus);

    /*!
     * @brief   Method to set HU discoverable status.
     * @param   bDiscoverableStatus - HU discoverable status whether discoverable or not.
     * @return  void.
     */
    void updateHUDiscoverableStatus(bool bDiscoverableStatus);

    /*!
     * @brief   Method to update device search result.
     * @param   void.
     * @return  void.
     */
    void updateDeviceSearchResult();

    /*!
     * @brief   Method to update bonded device list.
     * @param   void.
     * @return  void.
     */
    void updateBondedDeviceList();

    /*!
     * @brief   updateConnectedDeviceList: Method to update connected device list.
     * @param   void.
     * @return  void.
     */
    void updateConnectedDeviceList();

    /*!
     * @brief   Method to update bonding status.
     * @param   void.
     * @return  void.
     */
    void updateBondingStatus();

    /*!
     * @brief   Method to update bonding request.
     * @param   void.
     * @return  void.
     */
    void updateBondingRequest();

    /*!
     * @brief   Method to update service connection status.
     * @param   void.
     * @return  void.
     */
    void updateServiceConnectionStatus();

    /*!
     * @brief   Method to update device deleted status.
     * @param   void.
     * @return  void.
     */
    void updateDeviceDeletedStatus();

    /*!
     * @brief   Method to update hfp connection status.
     * @param   TRUE if HFP profile is connected, FALSE otherwise.
     * @return  void.
     */
    void updateHFPConnectionStatus(bool bIsHfpConnected);

    /*!
     * @brief   Method to update setDiscoverableMode method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateSetDiscoverableModeMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                   EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update startDeviceSearch method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateStartDeviceSearchMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                 EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update stopDeviceSearch method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateStopDeviceSearchMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update startAllServiceConnection method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateStartAllServiceConnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                         EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update startServiceConnectionMethod method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateStartServiceConnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                      EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update bondingReply method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateBondingReplyMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                            EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update deleteDevice method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateDeleteDeviceMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                            EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update deleteAllDevices method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateDeleteAllDevicesMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update startAllServiceDisconnection method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateStartAllServiceDisconnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                            EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update startServiceDisconnection method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateStartServiceDisconnectionMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                         EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update setBluetoothStatus method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateSetBluetoothStatusMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                  EMethodCallErrorType eMethodCallErrorType);


    /************************************************************************//**
     * @category   PHONE CALL METHODS
     ************************************************************************/
    /*!
     * @brief   Method to update call state info.
     * @param   void.
     * @return  void.
     */
    void callStateInfoUpdated();

    /*!
     * @brief   Method to update HF feature.
     * @param   void.
     * @return  void.
     */
    void updateHfFeatures();

    /*!
     * @brief   Method to update operator info.
     * @param   void.
     * @return  void.
     */
    void updateOperatorInfoList();

    /*!
     * @brief   Method to update rssi charge info.
     * @param   void.
     * @return  void.
     */
    void updateRssiChargeInfo();

    /*!
     * @brief   Method to update hf mode status.
     * @param   void.
     * @return  void.
     */
    void updateHfModeStatus();

    /*!
     * @brief   Method to update call duration.
     * @param   void.
     * @return  void.
     */
    void updateCallDuration();

    /*!
     * @brief   updatePhoneBtVrModeStatus: Method to update phone bt vr mode status.
     * @param   void.
     * @return  void.
     */
    void updatePhoneBtVrModeStatus();

    /*!
     * @brief   Method to update acceptIncomingCallAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateAcceptIncomingCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                       EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update rejectIncomingCallAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateRejectIncomingCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                       EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update sendSMSAsyncReq method call status.
     * @param   bIsSucessful - request completed sucessfully
     * @return  void.
     */
    void updateSendSMSAsyncMethodCallStatus(bool bIsSucessful);

    /*!
     * @brief   Method to update dialAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateDialAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                         EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update conferenceCallAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateConferenceCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                   EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update swapCallsAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateSwapCallsAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                              EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update resumeHeldCallAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateResumeHeldCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                   EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update holdActiveCallAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateHoldActiveCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                   EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update endCallAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateEndCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                            EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update endActiveCallAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateEndActiveCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                  EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update endAllCallsAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateEndAllCallsAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update sendDtmfToneAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateSendDtmfToneAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                 EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update setHfModeAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateSetHfModeAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                              EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to update setVRModeAsync method call status.
     * @param   eMethodCallStatus    - call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType - type of the error received after invoking the method.
     * @return  void.
     */
    void updateSetVRModeAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                              EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   Method to inform connection manager resource to end the current active call.
     * @param   void.
     * @return  void.
     */
    void endActiveCall();

    /*!
     * @brief   Method to inform connection manager resource to end all available calls from HU.
     * @param   void.
     * @return  void.
     */
    void endAllCalls();

    /************************************************************************//**
     * @category   PHONE PIMDB METHODS
     ************************************************************************/
    /*!
     * @brief   pimDbServiceAvailableStatusChanged: Method to update pimDb Service Available Status.
     * @param   bPimDbServiceAvailableStatus: PimDb Service Availability Status
     * @return  void
     */
    void pimDbServiceAvailableStatusChanged(bool bPimDbServiceAvailableStatus);

    /*!
     * @brief   Method to update call list sync state.
     * @param   eStatus - call log sync state
     * @return  void
     */
    void changePimDbCallListSyncState(CPhoneEnum::EPhoneSyncStatus eStatus);

    /*!
     * @brief   Method to update contact list sync state.
     * @param   eStatus - contact sync state
     * @return  void
     */
    void changePimDbContactListSyncState(CPhoneEnum::EPhoneSyncStatus eStatus);

    /*!
     * @brief   Method to update contact detail list sync state.
     * @param   eStatus - contact details sync state
     * @return  void
     */
    void changePimDbContactDetailSyncState(CPhoneEnum::EPhoneSyncStatus eStatus);

    /*!
     * @brief   Method to update favorite list sync state.
     * @param   eStatus - favorite sync state
     * @return  void
     */
    void changePimDbFavouriteListSyncState(CPhoneEnum::EPhoneSyncStatus eStatus);

    /*!
     * @brief   changePimDbFrequentlyDialedListSyncState: Method to update frequently dialed list sync state.
     * @param   eStatus: frequently dialed list sync state
     * @return  void
     */
    void changePimDbFrequentlyDialedListSyncState(CPhoneEnum::EPhoneSyncStatus eStatus);

    /*!
     * @brief   Method to update call list data.
     * @param   void.
     * @return  void.
     */
    void pimDbCallListUpdated();

    /*!
     * @brief   Method to update contact list data.
     * @param   usStartIndex: start index of the contact data list received.
     * @return  void.
     */
    void pimDbContactListUpdated(unsigned short usStartIndex);

    /*!
     * @brief   Method to update contact detail list data.
     * @param   void.
     * @return  void.
     */
    void pimDbContactDetailListUpdated();

    /*!
     * @brief   Method to update favorite list data.
     * @param   void.
     * @return  void.
     */
    void pimDbFavouriteListUpdated();

    /*!
     * @brief   pimDbFrequentlyDialedListUpdated: Method to update frequently dialed list data.
     * @param   void.
     * @return  void.
     */
    void pimDbFrequentlyDialedListUpdated();

    /*!
     * @brief   Method to sync contact details list with favorite list data.
     * @param   void.
     * @return  void.
     */
    void syncFavouriteListWithContactDetails();

    /*!
     * @brief   Method to change DTMF Number Pad Status(DTMF or Dial).
     * @param   bStatus - TRUE if in DTMF mode,
     *                    FALSE if in Dial mode.
     * @return  void.
     */
    Q_INVOKABLE void invChangeDTMFNumberPadStatus(bool bStatus);

    /*!
     * @brief   Method to get set favorite operation result.
     * @param   bIsSuccess -  true if favorite is added, false otherwise Success.
     * @return  void.
     */
    void pimDbSetAsFavoriteOperationResult(bool bIsSuccess);

    /*!
     * @brief   Method to get Remove favorite operation result.
     * @param   bIsSuccess -  true if favorite is removed, false otherwise Success.
     * @return  void.
     */
    void pimDbRemoveAsFavoriteOperationResult(bool bIsSuccess);

    /*!
     * @brief   Method to update unread missed call status.
     * @param   void.
     * @return  void.
     */
    void updateUnreadMissedCallStatus();

    /*!
     * @brief   Method to update sms supported feature.
     * @param   void.
     * @return  void.
     */
    void updateGetSmsSupportedFeature();

    /**
     * @brief   updateTTSPlayStateStatus - Method shall be invoked when ever TTS playstate
     *          status is updated.
     * @param   iTTSPlayState - current playstate of TTS.
     * @return  void.
     */
    void updateTTSPlayStateStatus(int iTTSPlayState);


    /************************************************************************//**
     * @category    BT CONNECTION RELATED GETTERS
     ************************************************************************/
    /*!
     * @brief   Method to get hu discoverable status.
     * @param   void.
     * @return  m_bHUDiscoverableStatus - hu discoverable status whether visible or not.
     */
    bool getHUDiscoverableStatus(){ return m_bHUDiscoverableStatus; }

    /************************************************************************//**
     * @category    BT CONNECTION PROPERTY RELATED GETTERS
     ************************************************************************/

    /*!
     * @brief   Method to get the passkey pin.
     * @param   void.
     * @return  refernce of passkey pin object.
     */
    QString passKeyPin(){ return m_strPassKeyPin; }

    /*!
     * @brief   Method to get device name connected for HFP/A2DP profile.
     * @param   void.
     * @return  reference of device name connected for HFP/A2DP profile object.
     */
    QString connectedDeviceName(){ return m_strConnectedDeviceName; }

    /*!
     * @brief   Method to get device name disconnected for HFP/A2DP profile.
     * @param   void.
     * @return  reference of device name disconnected for HFP/A2DP profile object.
     */
    QString disconnectedDeviceName(){ return m_strDisconnectedDeviceName; }

    /*!
     * @brief   Method to get name of the deleted device.
     * @param   void.
     * @return  reference of name of the deleted device object.
     */
    QString deletedDeviceName(){ return m_strDeletedDeviceName; }

    /*!
     * @brief   Method to get whether a device is connected for HFP/A2DP profile.
     * @param   void.
     * @return  true - device connected for HFP/A2DP profile.
     *          false - no device connected for HFP and A2DP profile.
     */
    bool deviceConnected(){ return m_bIsDeviceConnected; }

    /*!
     * @brief   Method to get HU bluetooth status.
     * @param   void.
     * @return  true - HU bluetooth is enabled.
     *          false - HU bluetooth is disabled.
     */
    bool bluetoothStatus(){ return m_bIsBluetoothEnabled; }

    /*!
     * @brief   Method to get device search status.
     * @param   void.
     * @return  true - device search initiated.
     *          false - device search finished.
     */
    bool deviceSearchStatus(){ return m_bDeviceSearchStatus; }

    /*!
     * @brief   Method to get bt visibility request update.
     * @param   void.
     * @return  true - bt visibility request sent to connection manager resource.
     *          false - bt status update received from connection manager resource.
     */
    bool btVisibilityReqStatus(){ return m_bBtVisibilityReqStatus; }

    /*!
     * @brief   Method to get updated selected item name.
     * @param   void.
     * @return  reference of selected item name object.
     */
    QString selItemName(){ return m_strSelItemName; }

    /*!
     * @brief   Method to get updated selected item bt address.
     * @param   void.
     * @return  reference of selected item bt address object.
     */
    QString selItemBtAddr(){ return m_strSelItemBtAddr; }

    /*!
     * @brief   Method to get updated hfp connection status.
     * @param   void.
     * @return  TRUE if hfp profile is connected, FALSE otherwise.
     */
    bool hfpConnectionStatus(){ return m_bIsHFPConnected; }


    /*!
     * @brief   Method to get Contact List Current Top Index
     * @param   void.
     * @return  int Contact Current Top Index value.
     */
    int contactListCurrentTopIndex() {return m_iContactListCurrentTopIndex; }

    /*!
     * @brief   Method to set Contact List Current Top Index
     * @param   iValue: Contact Current Top Index value.
     * @return  void.
     */
    void setContactListCurrentTopIndex(int iValue);

    /*!
     * @brief   Method to get device search list model.
     * @param   void.
     * @return  pointer to the object of class CDeviceSearchListModel
     */
    QAbstractListModel* deviceSearchListModel(){ return m_pDeviceSearchListModel; }

    /*!
     * @brief   Method to get paired device list model.
     * @param   void.
     * @return  pointer to the object of class CPairedDeviceListModel
     */
    QAbstractListModel* pairedDeviceListModel(){ return m_pPairedDeviceListModel; }

    /*!
     * @brief   Method to get phone setup list model.
     * @param   void.
     * @return  pointer to the object of class CPhoneSetupListModel
     */
    QAbstractListModel* phoneSetupListModel(){ return m_pPhoneSetupListModel; }
    /*!
     * @brief   Method to get status of favorite toggling.
     * @param   void.
     * @return  true : favorite toggling is in process, false : favorite toggling is not in process
     */
    bool isFavoriteToggling(){ return m_bIsFavoriteToggling; }

    /*!
     * @brief   favoriteTogglingContactName: Method to get name of favorite toggling contact.
     * @param   void.
     * @return  Contact name for favorite toggling contact
     */
    QString favoriteTogglingContactName(){ return m_objFavoriteTogglingInfo.m_strName; }

    /*!
     * @brief   favoriteTogglingContactNumber: Method to get number of favorite toggling contact.
     * @param   void.
     * @return  Contact number for favorite toggling contact
     */
    QString favoriteTogglingContactNumber(){ return m_objFavoriteTogglingInfo.m_strNumber; }

    /*!
     * @brief   Method get notify Can Send SMS permission changes
     * @param   bool can send SMS
     * @return  void.
     */
    void setIsSendingSMSAllowed(bool bIsSendingSMSAllowed);

    /*!
     * @brief   Method get notify new message recieved
     * @param   void
     * @return  void.
     */
    void newMessageNotification();

    /*!
     * @brief   resetContactDetailList: Method to reset contact detail data list.
     * @param   void.
     * @return  void.
     */
    void resetContactDetailList();

    /************************************************************************//**
     * @category    PHONE CALL PROPERTY RELATED GETTERS
     ************************************************************************/
    /*!
     * @brief   Method to get incoming call info.
     * @param   void.
     * @return  refernce of incoming call info object.
     */
    CCallInfo* incomingCallInfo() { return &m_objIncomingCallInfo; }

    /*!
     * @brief   Method to get second caller info.
     * @param   void.
     * @return  refernce of first caller info object.
     */
    CCallInfo* firstCallerInfo() { return &m_objFirstCallerInfo; }

    /*!
     * @brief   Method to get second caller info.
     * @param   void.
     * @return  refernce of second caller info object.
     */
    CCallInfo* secondCallerInfo() { return &m_objSecondCallerInfo; }

    /*!
     * @brief   Method to get accept incoming call request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    bool acceptCallReqStatus() { return m_bAcceptCallRequestStatus; }

    /*!
     * @brief   Method to get reject incoming call request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    bool rejectCallReqStatus() { return m_bRejectCallRequestStatus; }

    /*!
     * @brief   Method to get send SMS request status.
     * @param   void.
     * @return  TRUE is the sending SMS
     *          FALSE if the no SMS sending in progress
     */
    bool sendSMSReqStatus() { return m_bSendSMSRequestStatus; }

    /*!
     * @brief   Method to get dial request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    bool dialReqStatus() { return m_bDialRequestStatus; }

    /*!
     * @brief   Method to get merge calls request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    bool mergeCallsReqStatus() { return m_bMergeCallsRequestStatus; }

    /*!
     * @brief   Method to get swap calls request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    bool swapCallsReqStatus() { return m_bSwapCallRequestStatus; }

    /*!
     * @brief   Method to get resume call request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    bool resumeCallReqStatus() { return m_bResumeCallRequestStatus; }

    /*!
     * @brief   Method to get hold call request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    bool holdCallReqStatus() { return m_bHoldCallRequestStatus; }

    /*!
     * @brief   Method to get end call request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    bool endCallReqStatus() { return m_bEndCallRequestStatus; }

    /*!
     * @brief   Method to get hf mode request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    bool hfModeReqStatus() { return m_bHFModeRequestStatus; }

    /*!
     * @brief   Method to get handsfree mode status.
     * @param   void.
     * @return  TRUE if handsfree mode
     *          FALSE if handset mode.
     */
    bool handsFreeModeStatus() { return m_bIsHandsFreeMode; }

    /*!
     * @brief   Method to get signal strength level.
     * @param   void.
     * @return  level of signal strength.
     */
    CPhoneEnum::ESignalStrengthLevel signalStrengthLevel() { return m_eSignalStrengthLevel; }

    /*!
     * @brief   Method to get battery charge level.
     * @param   void.
     * @return  level of battery charge.
     */
    CPhoneEnum::EBatteryChargeLevel batteryChargeLevel() { return m_eBatteryChargeLevel; }

    /*!
     * @brief   Method to get current phone call state
     * @param   void.
     * @return  current phone call state.
     */
    CPhoneEnum::EPhoneCallState phoneCallState() { return m_ePhoneCallState; }

    /*!
     * @brief   Method to get conference participant list model
     * @param   void.
     * @return  refernce of conference participant list model object.
     */
    CConfParticipantsListModel* confParticipantsListModel() { return &m_objConfParticipantsListModel; }

    /************************************************************************//**
     * @category    PHONE PIMDB PROPERTY RELATED GETTERS
     ************************************************************************/
    /*!
     * @brief   Method to get call logs list model.
     * @param   void.
     * @return  pointer of class CCallLogListModel
     */
    CCallLogListModel* callLogListModel(){ return m_pCallLogListModel; }

    /*!
     * @brief   frequentlyDialedListModel: Method to get frequently dialed list list model.
     * @param   void.
     * @return  list of frequently dialed numbers
     */
    CCallLogListModel* frequentlyDialedListModel(){ return m_pFrequentlyDialedListModel; }

    /*!
     * @brief   Method to get contacts list model.
     * @param   void.
     * @return  pointer of class CContactDetailListModel
     */
    CContactDetailListModel* contactListModel(){ return m_pContactListModel; }

    /*!
     * @brief   Method to get contact details list model.
     * @param   void.
     * @return  pointer of class CContactDetailListModel
     */
    CContactDetailListModel* contactDetailListModel(){ return m_pContactDetailListModel; }

    /*!
     * @brief   Method to get favorite contacts list model.
     * @param   void.
     * @return  pointer of class CContactDetailListModel
     */
    CContactDetailListModel* favoriteContactListModel(){ return m_pFavoriteContactListModel; }


    /*!
     * @brief   Method to get value of can send SMS permission
     * @param   void.
     * @return  bool is Sending SMS Allowed
     */
    bool isSendingSMSAllowed() { return m_bIsSendingSMSAllowed; }

    /*!
     * @brief   Method to get call List sync completed or not.
     * @param   void.
     * @return  sync state of call logs.
     */
    CPhoneEnum::EPhoneSyncStatus pimDbCallListSyncStatus();

    /*!
     * @brief   Method to get contact List sync completed or not.
     * @param   void.
     * @return  sync state of contacts.
     */
    CPhoneEnum::EPhoneSyncStatus pimDbContactListSyncStatus();

    /*!
     * @brief   Method to get ContactDetail List sync completed or not.
     * @param   void.
     * @return  sync state of contact details.
     */
    CPhoneEnum::EPhoneSyncStatus pimDbContactDetailSyncStatus();

    /*!
     * @brief   Method to get Favourite List sync completed or not.
     * @param   void.
     * @return  sync state of favorites.
     */
    CPhoneEnum::EPhoneSyncStatus pimDbFavouriteListSyncStatus();

    /*!
     * @brief   pimDbFrequentlyDialedListSyncStatus: Method to get frequently dialed list sync completed or not.
     * @param   void.
     * @return  sync state of frequetly dialed list.
     */
    CPhoneEnum::EPhoneSyncStatus pimDbFrequentlyDialedListSyncStatus();

    /*!
     * @brief   Method to get phone notification text
     * @param   void.
     * @return  phone notification text
     */
    QString phoneNotificationText() { return m_strPhoneNotificationText; }


    /************************************************************************//**
     * @category    PHONE BROWSE PROPERTY RELATED GETTERS
     ************************************************************************/

    /*!
     * @brief   Method to get hf mode request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    CPhoneBrowseTabBarModel* pPhoneBrowseTabBarModel() { return &m_objPhoneBrowseTabBarModel; }

    /*!
     * @brief   Method to get hf mode request status.
     * @param   void.
     * @return  TRUE is the request has been sent to call manager proxy and
     *          FALSE if the request is successfully received by the call manager proxy.
     */
    CPhoneEnum::EPhoneBrowseType eCurrentPhoneBrowseScreen() { return m_eCurrentPhoneBrowseScreen; }

    /*!
     * @brief   Method to get Number pad type.
     * @param   void.
     * @return  bool true when DTMF mode, false when Dial mode.
     */
    bool isInDTMFNumberPad() { return m_bIsInDTMFNumberPad; }

    /*!
     * @brief   Method to get New SMS Sender Name
     * @param   void.
     * @return  SMS sender name
     */
    QString smsSenderName();

    /*!
     * @brief   Method to get New SMS Sender Number
     * @param   void.
     * @return  SMS sender number
     */
    QString smsSenderNumber();

    /*!
     * @brief   Method to get New SMS Data
     * @param   void.
     * @return  SMS data
     */
    QString smsData();

    /*!
     * @brief   readingSMSSenderName: Method to get reading SMS Sender Name
     * @param   void.
     * @return  SMS sender name
     */
    QString readingSMSSenderName();

    /*!
     * @brief   readingSMSSenderNumber: Method to get reading SMS Sender Number
     * @param   void.
     * @return  SMS sender number
     */
    QString readingSMSSenderNumber();

    /*!
     * @brief   readingSMSData: Method to get reading SMS Data
     * @param   void.
     * @return  SMS data
     */
    QString readingSMSData();

    /*!
     * @brief   Method to set New SMS Details
     * @param   objSMSData - new sms details.
     * @return  void
     */
    void setSMSDetails(SMessageData& objSMSData);

    /*!
     * @brief   setReadingSMSDetails: Method to set reading SMS Details
     * @param   objSmsData: reading sms details.
     * @return  void
     */
    void setReadingSMSDetails(SMessageData& objSmsData);

    /*!
     * @brief   Method to reset new SMS Details
     * @param   void
     * @return  void
     */
    void resetSMSDetails();

    /*!
     * @brief   resetReadingSMSDetails: Method to reset reading SMS Details
     * @param   void
     * @return  void
     */
    void resetReadingSMSDetails();

    /**
     * @brief   isMaxDeviceLimitReached: This function is used to know that the
     *          maximum number of devices already paired or not.
     * @param   void.
     * @return  true if Maximum Number of devices are already paired otherwise false.
     */
    bool isMaxDeviceLimitReached();

    /**
     * @brief   isDeviceAlreadyPaired: This function is used to know that the
     *          the passed btAddress device already paired or not.
     * @param   strBtAddress: Bt Address of the device, which pairing status needs to check.
     * @return  true if device is already paired otherwise false.
     */
    bool isDeviceAlreadyPaired(const QString &strBtAddress);

    /**
     * @brief   deleteOldestConnectedDevice: This function is used to delete the
     *          oldest connected device.
     * @param   void.
     * @return  void.
     */
    void deleteOldestConnectedDevice();

    /**
     * @brief   updateOldestConnectedDeviceInfo: This function is used to update the
     *          oldest connected device info.
     * @param   strDeviceName: Device Name.
     * @param   strDeviceAddress: Device Address.
     * @return  void.
     */
    void updateOldestConnectedDeviceInfo(const QString &strDeviceName, const QString &strDeviceAddress);

    /*!
     * @brief   Method to reset contact detail data list
     * @param   void.
     * @return  void
     */
    Q_INVOKABLE void invResetContactDetailList();

    /************************************************************************//**
     * @category    PHONE BROWSE RELATED SETTERS
     ************************************************************************/

    /*!
     * @brief   Method to set the deleted device name.
     * @param   strDeletedDeviceName - name of the deleted device.
     * @return  void.
     */
    void setCurrentPhoneBrowseScreen(CPhoneEnum::EPhoneBrowseType eCurrentScreen);

    /************************************************************************//**
     * @category    CONNECTION MANAGER RESOURCE LAYER METHODS
     * @brief       API's can be called directly from QML or from other
     *              Adaptor's
     ************************************************************************/

    /*!
     * @brief   Method to inform connection manager resource to enable (or) disable
     *          discoverable mode.
     * @param   bEnable - value can be true(enable) or false(disable).
     * @return  void.
     */
    Q_INVOKABLE void invSetDiscoverableMode(bool bEnable);

    /*!
     * @brief   Method to inform connection manager resource to start service connection
     *          of all supported profiles for a device.
     * @param   strBtAddr - bt address of the device for which service connection
     *                      needs to be started.
     * @return  void.
     */
    Q_INVOKABLE void invStartAllServiceConnection(const QString strBtAddr);

    /*!
     * @brief   Method to inform connection manager resource to start service connection
     *          of a specific profile for a device.
     * @param   strBtAddr - bt address of the device.
     * @param   bStartHFPConnection - flag to determine whether to connect HFP or A2DP profile.
     * @return  void.
     */
    Q_INVOKABLE void invStartServiceConnection(const QString strBtAddr, bool bStartHFPConnection);

    /*!
     * @brief   Method to inform connection manager resource to start (or) stop bonding process.
     * @param   bAccepted - authentication request accepted or declined.
     * @param   bSecureBonding - secure bonding or not, true(secure) or false(standard).
     * @return  void.
     */
    Q_INVOKABLE void invBondingReply(bool bAccepted, bool bSecureBonding);

    /*!
     * @brief   Method to inform connection manager resource to delete the paired device.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invDeleteDevice();

    /*!
     * @brief   Method to inform connection manager resource to delete all the paired devices.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invDeleteAllDevices();

    /*!
     * @brief   Method to inform connection manager resource to start service disconnection
     *          of all supported profiles for a device.
     * @param   strBtAddr - bt address of the device for which service disconnection
     *                      needs to be started.
     * @return  void.
     */
    Q_INVOKABLE void invStartAllServiceDisconnection(const QString strBtAddr);

    /*!
     * @brief   Method to inform connection manager resource to start service disconnection
     *          of a specific profile for a device.
     * @param   strBtAddr - bt address of the device.
     * @param   bStartHFPDisconnection - flag to determine whether to disconnect HFP or A2DP profile.
     * @return  void.
     */
    Q_INVOKABLE void invStartServiceDisconnection(const QString strBtAddr, bool bStartHFPDisconnection);

    /*!
     * @brief   Method to set item infomation selected from QML via touch or RRE.
     * @param   strName - name of the selected item.
     * @param   strBtAddr - bt address of the selected item.
     * @return  void.
     */
    Q_INVOKABLE void invSetSelectedItemInfo(const QString strName, const QString strBtAddr);

    /*!
     * @brief   Method to inform adapter layer that external pairing has been cancelled from user
     *          and to reset the stored pairing information.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invExternalPairingRejected();

    /*!
     * @brief   Method to switch to phone browse screen.
     * @param   ePhoneBrowseType - type of phone browse screen to switch.
     * @return  void.
     */
    Q_INVOKABLE void invSwitchToPhoneBrowse(CPhoneEnum::EPhoneBrowseType ePhoneBrowseType);

    /*!
     * @brief   Method to switch to paired device screen.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invSwitchToPairedDevices();

    /*!
     * @brief   invSwitchToPairNewDevice: Method to switch to pair new device screen.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invSwitchToPairNewDevice();

    /*!
     * @brief   Method to get device address connected for HFP/A2DP profile.
     * @param   void.
     * @return  m_strConnectedDeviceAddr - device address connected for HFP/A2DP profile.
     */
    Q_INVOKABLE QString invGetConnectedDeviceAddress(){ return m_strConnectedDeviceAddr; }

    /************************************************************************//**
     * @category    Phone Setup SMS related invokable methods
     * @brief       API's can be called directly from QML or from other
     *              Adaptor's
     ************************************************************************/
    /*!
     * @brief   Method to update the SMS Alert Notification selected option into persistency.
     * @param   iItemId , This parameter contains the selected Item Id.
     * @return  void.
     */
    Q_INVOKABLE void invUpdateSMSAlertNotification(int iItemId);

    /*!
     * @brief   Method to update the Configure Auto model selected option into persistency.
     * @param   iItemId , This parameter contains the selected item id.
     * @return  void.
     */
    Q_INVOKABLE void invUpdateConfigureAutoSms(int iItemId);

    /*!
     * @brief   invShowPopupNoDeviceFound: Method to be invoked to show no device found popup.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invShowPopupNoDeviceFound();

    /*!
     * @brief   Method to clear device search list.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invClearDeviceSearchList();

    /************************************************************************//**
     * @category    CALL MANAGER RESOURCE LAYER METHODS
     * @brief       API's can be called directly from QML or from other
     *              Adaptor's
     ************************************************************************/
    /*!
     * @brief   Method to inform connection manager resource to accept the incoming call.
     * @param   bAcceptInHandsetMode - flag indicates whether the call has to be transferred to handset mode.
     * @return  void.
     */
    Q_INVOKABLE void invAcceptIncomingCall(bool bAcceptInHandsetMode = false);

    /*!
     * @brief   Method to inform connection manager resource to reject the incoming call.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invRejectIncomingCall();

    /*!
     * @brief   Method to inform connection manager resource to reject the incoming call by sending SMS.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invRejectIncomingCallWithSMS();

    /*!
     * @brief   Method to send the SMS to the specified number using specified text.
     * @param   number : The number to which the SMS is to be sent.
     *          SMSText : SMS text to be sent.
     * @return  void.
     */
    void sendSMS(const QString number, const QString SMSText);

    /*!
     * @brief   invDial: Method to inform connection manager resource to initate a call.
     * @param   strNumber: phone number to be dialled.
     * @param   strName: name of the contact to dial.
     * @return  void.
     */
    Q_INVOKABLE void invDial(QString strNumber, QString strName = "");

    /*!
     * @brief   Method to inform connection manager resource to put the calls in conference/merge two calls.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invConferenceCall();

    /*!
     * @brief   Method to inform connection manager resource to swap the active call with held call.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invSwapCalls();

    /*!
     * @brief   Method to inform connection manager resource to activate/resume the held call.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invResumeHeldCall();

    /*!
     * @brief   Method to inform connection manager resource to put the current active call on hold.
     * @param   void.
     * @return  void.
     */
    Q_INVOKABLE void invHoldActiveCall();

    /*!
     * @brief   Method to toggle mic mute.
     * @param   bToggleMicMute: Flag to check whether to toggle mic mute or not, TRUE to
     *          toggle mic mute.
     * @return  void.
     */
    Q_INVOKABLE void invToggleMicMute(bool bToggleMicMute = true);

    /*!
     * @brief   Method to inform phone adaptor to end the phone call.
     * @param   void
     * @return  void.
     */
    Q_INVOKABLE void invEndPhoneCall();

    /*!
     * @brief   Method to inform connection manager resource to end the call for passed call id.
     * @param   iCallId     - call id of the phone call to be ended.
     * @return  void.
     */
    Q_INVOKABLE void invEndCall(int iCallId);

    /*!
     * @brief   Method to inform connection manager resource to send DTMF tone from HU to phone.
     * @param   strDtmfTone - dtmf tone to be sent to phone.
     * @return  void.
     */
    Q_INVOKABLE void invSendDtmfTone(const QString strDtmfTone);

    /*!
     * @brief   Method to inform connection manager resource to transfer call audio from handsfree to handset mode
     * @param   bHfMode - mode requested from HMI whether to set handset mode or handsfree mode .
     * @return  void.
     */
    Q_INVOKABLE void invSetHfMode(bool bHfMode);


    /************************************************************************//**
     * @category    PHONE PIMDB MANAGER RESOURCE LAYER METHODS
     * @brief       API's can be called directly from QML or from other
     *              Adaptor's
     ************************************************************************/
    /*!
     * @brief   Method to request contact details to pimDb resource for given contact ID
     * @param   int - contact ID value to request details
     * @return  void.
     */
    Q_INVOKABLE void invGetContactDetails(int iContactId);

    /*!
     * @brief   Method to add contact details to favorite list
     * @param   QString contact name.
     * @param   int contact id.
     * @param   QString contact number.
     * @param   int contact number type.
     * @param   int favorite index of contact number.
     * @return  void.
     */
    Q_INVOKABLE void invAddContactToFavorite(QString strContactName, int iContactId, QString strContactNumber, int iContactType, int iFavoriteIndex);

    /*!
     * @brief   Method to remove contact details from favorite list
     * @param   QString contact name.
     * @param   int contact id.
     * @param   QString contact number.
     * @param   int contact number type.
     * @param   int favorite index of contact number.
     * @return  void.
     */
    Q_INVOKABLE void invRemoveContactFromFavorite(QString strContactName, int iContactId, QString strContactNumber, int iContactType, int iFavoriteIndex);

    /*!
     * @brief   Method to get contact type in text fromat.
     * @param   int iContactType - contact type value
     * @return  QString - contact type in HMI text fromat.
     */
    Q_INVOKABLE QString invGetContactTypeText(int iContactType);

    /*!
     * @brief   Method to remove contact number as favorite.
     * @param   bRemoveFav - TRUE: remove contact number as favorite, FALSE: reset the info stored
     * @return  void.
     */
    Q_INVOKABLE void invRemoveFavorite(bool bRemoveFav);

    /*!
     * @brief   Method called to clear the unread missed call info
     * @param   void
     * @return  void.
     */
    Q_INVOKABLE void invResetUnreadMissedCallInfo();

    /************************************************************************//**
     * @category    Keypad Related Functions
     ************************************************************************/
    /*!
     * @brief getClickedCharacter: Sets the current active model of setup based on screen transition
     * @param eKeypadState - capital, small, Keypad state - passed from qml
     * @param iCharIndex - clicked character index - passed from qml
     * @return QChar: character which is clicked
     */
    Q_INVOKABLE QChar getClickedCharacter(CPhoneEnum::EKeyPadState eKeypadState, int iCharIndex);

    /**
     * @brief saveButtonClicked: Method gets called on Save button click, to update the keypad text to the model and persistency
     * @param const QString - Message in the text input field
     * @return void
     */
    Q_INVOKABLE void saveButtonClicked(const QString &strMessage);

    /**
     * @brief editButtonClicked: Method gets called on Edit button click, to update the keypad text area with the corresponding text
     * @param QString - Corresponding message at that particular index.
     * @param int - Index for which message to be changed.
     * @return void
     */
    Q_INVOKABLE void editButtonClicked(const QString &strMessage, int iIndex);

    /**
     * @brief textInputMessage: Returns the current selected theme mask image path
     * @param void
     * @return QString: Message to be updated on the text input of keypad
     */
    QString textInputMessage();

    /*!
     * @brief   Method called to get missed call count
     * @param   void
     * @return  void.
     */
    Q_INVOKABLE unsigned int invGetMissedCallCount() { return m_uiUnreadMissedCallCount; }

    /*!
     * @brief   startSmsReadout - Method to start sms readout
     * @param   void
     * @return  void.
     */
    Q_INVOKABLE void invStartSmsReadout();

    /*!
     * @brief  stopSmsReadout - Method to stop sms readout
     * @param   void
     * @return  void.
     */
    Q_INVOKABLE void invStopSmsReadout();

    /**
     * @brief	getKeyButtonDefaultImageCapital: This function returns the path of default state capital images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonDefaultImageCapital(int iKeyIndex);

    /**
     * @brief	getKeyButtonDefaultImageSmall: This function returns the path of default state small images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonDefaultImageSmall(int iKeyIndex);

    /**
     * @brief	getKeyButtonDefaultImageNumeric: This function returns the path of default state numeric images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonDefaultImageNumeric(int iKeyIndex);

    /**
     * @brief	getKeyButtonPressedImageCapital: This function returns the path of pressed state capital images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonPressedImageCapital(int iKeyIndex);

    /**
     * @brief	getKeyButtonPressedImageSmall: This function returns the path of pressed state small images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonPressedImageSmall(int iKeyIndex);

    /**
     * @brief	getKeyButtonPressedImageNumeric: This function returns the path of pressed state numeric images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonPressedImageNumeric(int iKeyIndex);

    /**
     * @brief	getKeyButtonDisabledImageCapital: This function returns the path of disabled state capital images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonDisabledImageCapital(int iKeyIndex);

    /**
     * @brief	getKeyButtonDisabledImageSmall: This function returns the path of disabled state small images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonDisabledImageSmall(int iKeyIndex);

    /**
     * @brief	getKeyButtonDisabledImageNumeric: This function returns the path of disabled state numeric images.
     * @param	iKeyIndex: Received from qml, based on index corresponding image path is returned.
     * @return	QString: Path of the image.
     */
    Q_INVOKABLE QString getKeyButtonDisabledImageNumeric(int iKeyIndex);

signals:
    /************************************************************************//**
     * @category    BT CONNECTION PROPERTY RELATED SIGNALS
     ************************************************************************/

    /*!
     * @brief   Signal emitted whenever pass key pin is updated.
     * @param   void.
     * @return  void.
     */
    void sigPassKeyPinUpdated();

    /*!
     * @brief   Signal emitted whenever device name is changed for HFP/A2DP profile
     *          (device connected/disconnected for HFP/A2DP profile).
     * @param   void.
     * @return  void.
     */
    void sigConnectedDeviceNameUpdated();

    /*!
     * @brief   Signal emitted whenever device gets connected for HFP/A2DP profile.
     * @param   void.
     * @return  void.
     */
    void sigDeviceConnectionUpdated();

    /*!
     * @brief   Signal emitted whenever bluetooth status is updated(HU bluetooth enabled/disabled).
     * @param   void.
     * @return  void.
     */
    void sigBluetoothStatusUpdated();

    /*!
     * @brief   Signal emitted whenever device search status is updated(HU device search start/finished).
     * @param   void.
     * @return  void.
     */
    void sigDeviceSearchStatus();

    /*!
     * @brief   Signal emitted whenever bt visibility request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigBtVisibilityReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever hfp connection status is changed.
     * @param   void.
     * @return  void.
     */
    void sigHFPConnectionStatus();

    /*!
     * @brief   sigExitPairNewDeviceScreen: Signal emitted whenever HMI has to exit from pair new evice screen.
     *          Pair new device screen will listen this signal and if the screen is alive it shall
     *          raise sm event to switch to phone setup screen.
     * @param   void.
     * @return  void.
     */
    void sigExitPairNewDeviceScreen();

    /************************************************************************//**
     * @category    PHONE BROWSE PROPERTY RELATED SIGNALS
     ************************************************************************/
    /*!
     * @brief   Signal emitted whenever accept incoming call request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigCurrentPhoneBrowseScreenChanged();

    /*!
     * @brief   Signal emitted whenever Contact List Current Top Index is updated.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigContactListCurrentTopIndexUpdated();

    /*!
     * @brief   Signal emitted whenever favorite toggling status is updated.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigIsFavoriteTogglingUpdated();

    /*!
     * @brief   Signal emitted whenever new details gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigSMSSenderNameChanged();

    /*!
     * @brief   Signal emitted whenever new details gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigSMSSenderNumberChanged();

    /*!
     * @brief   Signal emitted whenever new details gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigSMSDataChanged();

    /*!
     * @brief   sigReadingSMSSenderNameChanged: Signal emitted whenever Reading SMS details gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigReadingSMSSenderNameChanged();

    /*!
     * @brief   sigReadingSMSSenderNumberChanged: Signal emitted whenever Reading SMS details gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigReadingSMSSenderNumberChanged();

    /*!
     * @brief   sigReadingSMSDataChanged: Signal emitted whenever Reading SMS details gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigReadingSMSDataChanged();

    /**
     * @brief   sigHighlightContactCategory: Signal that shall be emitted to highlight the category
     *          from the contact details list.
     * @param   iLineNo: Line number to be highligted.
     * @return  void.
     */
    Q_SIGNAL void sigHighlightContactCategory(int iLineNo);

    /************************************************************************//**
     * @category    PHONE CALL PROPERTY RELATED SIGNALS
     ************************************************************************/
    /*!
     * @brief   Signal emitted whenever accept incoming call request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigAcceptCallReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever reject incoming call request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigRejectCallReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever sending SMS request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigSendSMSReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever dial request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigDialReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever merge calls request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigMergeCallsReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever swap calls request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigSwapCallsReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever resume call request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigResumeCallReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever hold call request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigHoldCallReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever end call request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigEndCallReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever hf mode request status is updated.
     * @param   void.
     * @return  void.
     */
    void sigHFModeReqStatusUpdated();

    /*!
     * @brief   Signal emitted whenever handsfree mode status is updated.
     * @param   void.
     * @return  void.
     */
    void sigHandsFreeModeStatusUpdated();

    /*!
     * @brief   Signal emitted whenever signal strength level is updated.
     * @param   void.
     * @return  void.
     */
    void sigSignalStrengthLevelUpdated();

    /*!
     * @brief   Signal emitted whenever battery charge level is updated.
     * @param   void.
     * @return  void.
     */
    void sigBatteryChargeLevelUpdated();

    /*!
     * @brief   Signal emitted whenever phone call state is updated.
     * @param   void.
     * @return  void.
     */
    void sigPhoneCallStateUpdated();

    /**
     * @brief   sigShowHidePhoneBtVROverlay: Signal emitted to show or hide phone bt VR overlay.
     * @param   bShowPhoneBtVROverLay: Flag which indicate whether to show or hide phone bt VR overlay
     *          TRUE - show phone bt VR overlay, FALSE - hide phone bt VR overlay.
     * @return  void.
     */
    void sigShowHidePhoneBtVROverlay(bool bShowPhoneBtVROverLay);

    /************************************************************************//**
     * @category    KeyPad Related Signals
     ************************************************************************/
    /*!
     * @brief sigTextInputMessageChanged: Signal gets emitted on text input message changed
     * @param void
     * @return void
     */
    void sigTextInputMessageChanged();


    /************************************************************************//**
     * @category    PHONE PIMDB PROPERTY RELATED SIGNALS
     ************************************************************************/
    /*!
     * @brief   Signal emitted whenever call logs list model request status is updated.
     * @param   void.
     * @return  void.
     */

    Q_SIGNAL void sigCallLogListModelUpdated();

    /*!
     * @brief   sigFrequentlyDialedListModelUpdated: Signal emitted whenever frequently dialed list model
     *          is updated.
     * @param   void.
     * @return  void.
     */

    Q_SIGNAL void sigFrequentlyDialedListModelUpdated();

    /*!
     * @brief   Signal emitted whenever contacts list model request status is updated.
     * @param   void.
     * @return  void.
     */

    Q_SIGNAL void sigContactListModelUpdated();

    /*!
     * @brief   Signal emitted whenever contact details list model request status is updated.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigContactDetailListModelUpdated();

    /*!
     * @brief   Signal emitted whenever favorite list model request status is updated.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigFavoriteContactListModelUpdated();

    /*!
     * @brief   Signal emitted whenever calllog sync state gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigPimDbCallListSyncUpdated();
    /*!
     * @brief   Signal emitted whenever contact sync state gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigPimDbContactListSyncUpdated();

    /*!
     * @brief   Signal emitted whenever contact detail sync state gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigPimDbContactDetailSyncUpdated();

    /*!
     * @brief   Signal emitted whenever favorite sync state gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigPimDbFavouriteListSyncUpdated();

    /*!
     * @brief   sigPimDbFrequentlyDialedListSyncUpdated: Signal emitted whenever frequently dialed list sync state gets change.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigPimDbFrequentlyDialedListSyncUpdated();

    /*!
     * @brief   Signal emitted whenever DTMF mode status is updated.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigDTMFNumberPadStatusUpdated();

    /*!
     * @brief   Signal emitted whenever phone notification text changes.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigPhoneNotificationTextChanged();

    /*!
     * @brief   Signal emitted whenever can send SMS permission value changes.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigIsSendingSMSAllowedChanged();

    /*!
     * @brief   Signal emitted whenever any low priority phone popup status gets changed.
     * @param   void.
     * @return  void.
     */
    Q_SIGNAL void sigLowPriorityPopupActiveUpdated();

private slots:

    /**
     * @brief   sltReverseGearStatusChanged : slot of the reverse gear status received from park assist
     * @param   void.
     * @return  void.
     */
    void sltReverseGearStatusChanged();

    /**
     * @brief   sltSourceStateInfoUpdated - slot of the source state update received from audio adaptor
     * @param   iSourceId: source id for which the state has changed.
     * @param   iSourceState: current state of the source.
     * @return  void
     */
    void sltSourceStateInfoUpdated(int iSourceId, int iSourceState);

    /**
     * @brief   sltDeactivatePhoneCall - slot of the end call screen timer timeout to deactivate phone
     *          call if hfp source is deactivated.
     * @param   void.
     * @return  void
     */
    void sltDeactivatePhoneCall();

    /**
     * @brief   sltPrjPhConnectionStatus - slot of the projection(Android Auto or Carplay) phone connection
     *          status.
     * @param   bPrjPhConnectionState - projection phone connection status, TRUE - projection phone is
     *          connected, FALSE - projection phone is not connected.
     * @return  void
     */
    void sltPrjPhConnectionStatus(bool bPrjPhConnectionState);

private:

    /*!
    * @brief	private constructor for CPhoneAdaptor to get singleton behaviour
    * @param	QObject
    * @return	NULL
    */
    explicit CPhoneAdaptor(QObject *pParent = nullptr);

    /*!
    * @brief	Internal method to force close all the connecting/disconnecting/connected/disconnected
    *			bt popups displayed or in the queue
    * @param	NULL
    * @return	NULL
    */
    void closeAllPhoneBtPopups();

    /************************************************************************//**
     * @category    BT CONNECTION RELATED SETTERS
     ************************************************************************/

    /*!
     * @brief   Method to set device name connected for HFP/A2DP profile.
     * @param   strConnectedDeviceName - device name connected for HFP/A2DP profile.
     * @return  void.
     */
    void setConnectedDeviceName(const QString& strConnectedDeviceName);

    /*!
     * @brief   Method to set device connection status for HFP/A2DP profile.
     * @param   bDeviceConnectionStatus - connection status for HFP/A2DP profile.
     * @return  void.
     */
    void setDeviceConnectionStatus(bool bDeviceConnectionStatus);

    /*!
     * @brief   Method to set bt visibility request updates.
     * @param   bBtVisibilityReqStatus - bt visisbility request update which indicates whether
     *          a request to change bluetooth status has been sent to connection manager resource
     *          and the update of bluetooth status has been recived from connection manager resource.
     * @return  void.
     */
    void setBtVisibilityReqStatus(bool bBtVisibilityReqStatus);

    /*!
     * @brief   Method to set device name disconnected for HFP/A2DP profile.
     * @param   strDisonnectedDeviceName - device name disconnected for HFP/A2DP profile.
     * @return  void.
     */
    void setDisconnectedDeviceName(const QString &strDisonnectedDeviceName);

    /*!
     * @brief   Method to set the deleted device name.
     * @param   strDeletedDeviceName - name of the deleted device.
     * @return  void.
     */
    void setDeletedDeviceName(const QString &strDeletedDeviceName);

    /************************************************************************//**
     * @category    PHONE CALL RELATED SETTERS
     ************************************************************************/
    /*!
     * @brief   Method to set the incoming call information.
     * @param   iCallId                     - Call id of the call.
     * @param   stIncomingrCallerName       - incoming caller name
     * @param   strIncomingCallerNumber     - incoming caller name
     * @param   strIncomingCallerProfileImg - incoming caller number
     * @param   eIncomingCallerState        - incoming caller state
     * @param   bShowOverlayImage           - whether to show overlay image or transparent image
     * @return  void.
     */
    void setIncomingCallInfo(uint8_t iCallId, const QString& strIncomingrCallerName, const QString& strIncomingCallerNumber,
                             const QString& strIncomingCallerProfileImg, CPhoneEnum::ECallerState eIncomingCallerState,
                             bool bShowOverlayImage = false);

    /*!
     * @brief   Method to set the first caller information.
     * @param   iCallId                     - Call id of the call.
     * @param   strFirstCallerName          - first caller name
     * @param   strFirstCallerNumber        - first caller name
     * @param   strFirstCallerProfileImg    - first caller number
     * @param   eFirstCallerState           - first caller state
     * @param   bShowOverlayImage           - whether to show overlay image or transparent image
     * @param   bIsSingleCallActive         - indicates whether single call is active or not
     * @return  void.
     */
    void setFirstCallerInfo(uint8_t iCallId, const QString& strFirstCallerName, const QString& strFirstCallerNumber,
                            const QString& strFirstCallerProfileImg, CPhoneEnum::ECallerState eFirstCallerState,
                            bool bShowOverlayImage = true, bool bIsSingleCallActive = false);

    /*!
     * @brief   Method to set the second caller information.
     * @param   iCallId                     - Call id of the call.
     * @param   strSecondCallerName         - second caller name
     * @param   strSecondCallerNumber       - second caller name
     * @param   strSecondCallerProfileImg   - second caller number
     * @param   eSecondCallerState          - second caller state
     * @param   bShowOverlayImage           - whether to show overlay image or transparent image
     * @param   bIsSingleCallActive         - indicates whether single call is active or not
     * @return  void.
     */
    void setSecondCallerInfo(uint8_t iCallId, const QString& strSecondCallerName, const QString& strSecondCallerNumber,
                             const QString& strSecondCallerProfileImg, CPhoneEnum::ECallerState eSecondCallerState,
                             bool bShowOverlayImage = false, bool bIsSingleCallActive = false);

    /************************************************************************//**
     * @category    INTERNAL METHODS
     ************************************************************************/
    /*!
     * @brief   Internal method to set selected favorite item information.
     * @param   QString contact name.
     * @param   int contact id.
     * @param   QString contact number.
     * @param   int contact number type.
     * @param   int favorite index of contact number.
     * @return  void.
     */
    void setFavoriteToggleInfo(QString strContactName, int iContactId, QString strContactNumber, int iContactType, int iFavoriteIndex);

    /*!
     * @brief   Internal method to reset selected favorite item information.
     * @param   void.
     * @return  void.
     */
    void resetFavoriteToggleInfo();

    /*!
     * @brief   setFavoriteToggling: Internal method to set favorite toggling state.
     * @param   bIsToggling: flag to maintain the status of favorite toggling.
     * @return  void.
     */
    void setFavoriteToggling(const bool bIsToggling);

    /*!
     * @brief   Internal method to reset active, held and incoming call info data.
     * @param   void.
     * @return  void.
     */
    void resetCallInfo();

    /*!
     * @brief   Internal method to reset phone related information.
     * @param   void.
     * @return  void.
     */
    void resetPhoneInformation();

    /*!
     * @brief   resetPhoneAdaptor: Internal method to reset all phone adaptor information whenever bluetooth status is received as false or
     *          bt service crashes.
     * @param   void.
     * @return  void.
     */
    void resetPhoneAdaptor();

    /*!
     * @brief   resetPhoneConnectionData: Internal method to reset all phone connection proxy related data whenever
     *          bluetooth status is received as false or bt service crashes.
     * @param   void.
     * @return  void.
     */
    void resetPhoneConnectionData();

    /*!
     * @brief   resetPhoneCallData: Internal method to reset all phone call proxy related data whenever bluetooth
     *          status is received as false or bt service crashes.
     * @param   void.
     * @return  void.
     */
    void resetPhoneCallData();

    /*!
     * @brief   resetPhonePimDbData: Internal method to reset all phone pimDb proxy related data whenever bluetooth
     *          status is received as false or bt service crashes.
     * @param   void.
     * @return  void.
     */
    void resetPhonePimDbData();

    /*!
     * @brief   Method to get the call info based upon the callstate.
     * @param   vectCallStateInfo - call state info list.
     * @param   eCallState        - call state of the call.
     * @return  void.
     */
    const SCallStateInfo* getCallInfo(const vector<SCallStateInfo>& vectCallStateInfo, ECallState eCallState);

    /*!
     * @brief   Method to reset call related request properties whenever call state info is received.
     * @param   void.
     * @return  void.
     */
    void resetRequestStatusProperties();

    /*!
     * @brief   resetHFPData: Method to reset phone data when Hfp is disconnected.
     * @param   void.
     * @return  void.
     */
    void resetHFPData();

    //TODO: This needs to be move to call manager resource
    /*!
     * @brief   Method to get the participant count in conference call.
     * @param   vectCallStateInfo - call state info list.
     * @param   eCallState        - call state of the call.
     * @return  void.
     */
    int getConferenceParicipantsCount(const vector<SCallStateInfo>& vectCallStateInfo, ECallState eCallState);

    /*!
     * @brief   Method to set accpet incoming call request status.
     * @param   bStatus - TRUE if the request has been sent to call manager proxy,
     *                    FALSE if the response of the request is received as success.
     * @return  void.
     */
    void setAcceptCallReqStatus(bool bStatus);

    /*!
     * @brief   Method to set reject incoming call request status.
     * @param   bStatus - TRUE if the request has been sent to call manager proxy,
     *                    FALSE if the response of the request is received as success.
     * @return  void.
     */
    void setRejectCallReqStatus(bool bStatus);

    /*!
     * @brief   Method to set sending SMS request status.
     * @param   bStatus - TRUE sending SMS
     *                    FALSE no SMS sending in progress
     * @return  void.
     */
    void setSendSMSReqStatus(bool bStatus);

    /*!
     * @brief   Method to set dial request status.
     * @param   bStatus - TRUE if the request has been sent to call manager proxy,
     *                    FALSE if the response of the request is received as success.
     * @return  void.
     */
    void setDialReqStatus(bool bStatus);

    /*!
     * @brief   Method to set merge calls request status.
     * @param   bStatus - TRUE if the request has been sent to call manager proxy,
     *                    FALSE if the response of the request is received as success.
     * @return  void.
     */
    void setMergeCallsReqStatus(bool bStatus);

    /*!
     * @brief   Method to set swap calls request status.
     * @param   bStatus - TRUE if the request has been sent to call manager proxy,
     *                    FALSE if the response of the request is received as success.
     * @return  void.
     */
    void setSwapCallsReqStatus(bool bStatus);

    /*!
     * @brief   Method to set resume call request status.
     * @param   bStatus - TRUE if the request has been sent to call manager proxy,
     *                    FALSE if the response of the request is received as success.
     * @return  void.
     */
    void setResumeCallReqStatus(bool bStatus);

    /*!
     * @brief   Method to set hold call call request status.
     * @param   bStatus - TRUE if the request has been sent to call manager proxy,
     *                    FALSE if the response of the request is received as success.
     * @return  void.
     */
    void setHoldCallReqStatus(bool bStatus);

    /*!
     * @brief   Method to set end call request status.
     * @param   bStatus - TRUE if the request has been sent to call manager proxy,
     *                    FALSE if the response of the request is received as success.
     * @return  void.
     */
    void setEndCallReqStatus(bool bStatus);

    /*!
     * @brief   Method to set hf mode request status.
     * @param   bStatus - TRUE if the request has been sent to call manager proxy,
     *                    FALSE if the response of the request is received as success.
     * @return  void.
     */
    void setHFModeReqStatus(bool bStatus);

    /*!
     * @brief   Method to set handsfree mode(handsfree or handset).
     * @param   bStatus - TRUE if in handsfree mode,
     *                    FALSE if in handset mode.
     * @return  void.
     */
    void setHandsFreeModeStatus(bool bStatus);

    /*!
     * @brief   Method to set signal strength.
     * @param   eSignalStrength - level of signal strength.
     * @return  void.
     */
    void setSignalStrength(ESignalLevel eSignalStrength);

    /*!
     * @brief   Method to set battery charge.
     * @param   eBatteryCharge - level of battery charge.
     * @return  void.
     */
    void setBatteryCharge(EBatteryChargeLevel eBatteryCharge);

    /*!
     * @brief   Method to set the phone current call state.
     * @param   ePhoneCallState - phone current call call state.
     * @return  void.
     */
    void setPhoneCallState(CPhoneEnum::EPhoneCallState ePhoneCallState);

    /*!
     * @brief   Method to get contact type in text fromat.
     * @param   int - call type value as per PimDb
     * @return  int  - contact type as per HMI
     */
    int getCallType(int iPimDbCallType);

    /*!
     * @brief   Method to get contact type in text fromat.
     * @param   int iContactType - contact type value
     * @return  QString - contact type in HMI text fromat.
     */
    QString getContactTypeText(int iContactType);

    /**
     * @brief activateSMCallState - TO invoke the call state of state machine and also to update any
     *        additional information required by state machine.
     * @param void
     * @return void
     */
    void inline activateSMCallState();

    /*!
     * @brief   Method to increment unread missed call count on unread missed call event from service
     * @param   int Unread missed call count
     * @return  void.
     */
    void incrementUnreadMissedCallCount(unsigned int uiMissedCallCount);

private:

    /**
     * @brief getHFPConnectionStatusType - get methode for HFP connection status type
     * @param void
     * @return EConnectionStatus: current HFP connection status type
     */
    EConnectionStatus getHFPConnectionStatusType();

    /**
     * @brief setHFPConnectionStatusType - set methode for HFP connection status type
     * @param EConnectionStatus: new HFP connection status type
     * @return void
     */
    void setHFPConnectionStatusType(EConnectionStatus eStatus);

    /**
     * @brief getA2DPConnectionStatusType - get methode for A2DP connection status type
     * @param void
     * @return EConnectionStatus: current A2DP connection status type
     */
    EConnectionStatus getA2DPConnectionStatusType();

    /**
     * @brief setA2DPConnectionStatusType - set methode for A2DP connection status type
     * @param EConnectionStatus: new A2DP connection status type
     * @return void
     */
    void setA2DPConnectionStatusType(EConnectionStatus eStatus);

    /**
     * @brief   getPhoneResourceInfo: Method to get updated information from phone resource at startup.
     * @param   void.
     * @return  void.
     */
    void getPhoneResourceInfo();

    /**
     * @brief   ringtoneSourceDeactivated: Method to get invoked when first incoming call is terminated or when ringtone
     *          source is disconnected.
     * @param   void.
     * @return  void.
     */
    void ringtoneSourceDeactivated();

    /**
     * @brief   hfpSourceDeactivated: Method to get invoked when hfp source is disconnected or when end call screen timer is
     *          timeout.
     * @param   void.
     * @return  void.
     */
    void hfpSourceDeactivated();

    /**
     * @brief   updateIncomingCallInfo: Method to get invoked when first incoming call information is to be updated.
     * @param   void.
     * @return  void.
     */
    void updateIncomingCallInfo();

    /**
     * @brief   updateSingleCallInfo: Method to get invoked when single call information is to be updated.
     * @param   bIsCallActive: Indicate whether the single call is active or on hold. TRUE if single
     *          call is active, false otherwise.
     * @return  void.
     */
    void updateSingleCallInfo(bool bIsCallActive);

    /**
     * @brief   updateConferenceCallInfo: Method to get invoked when conference call information is to be updated.
     * @param   bIsConferenceCallActive: Indicate whether the conference call is active or on hold. TRUE if conference
     *          call is active, false otherwise.
     * @return  void.
     */
    void updateConferenceCallInfo(bool bIsConferenceCallActive);

    /**
     * @brief   updateOutgoingCallInfo: Method to get invoked when outgoing call information is to be updated.
     * @param   bIsCallDialing: Indicate whether the outgoing call is in dialing or in alerting state. TRUE if
     *          ougoing call is isn dialing state, false otherwise.
     * @return  void.
     */
    void updateOutgoingCallInfo(bool bIsCallDialing);

    /**
     * @brief   updateSingleAndIncomingCallInfo: Method to get invoked when single call with incoming call information
     *          is to be updated.
     * @param   bIsCallActive: Indicate whether the single call is active or on hold. TRUE if single
     *          call is active, false otherwise.
     * @return  void.
     */
    void updateSingleAndIncomingCallInfo(bool bIsCallActive);

    /**
     * @brief   updateConferenceAndIncomingCallInfo: Method to get invoked when conference call with incoming call information
     *          is to be updated.
     * @param   bIsConferenceCallActive: Indicate whether the conference call is active or on hold. TRUE if conference
     *          call is active, false otherwise.
     * @return  void.
     */
    void updateConferenceAndIncomingCallInfo(bool bIsConferenceCallActive);

    /**
     * @brief   updateActiveAndHeldCallInfo: Method to get invoked when multiparty(active and held) call information
     *          is to be updated.
     * @param   void.
     * @return  void.
     */
    void updateActiveAndHeldCallInfo();

    /**
     * @brief   updateSingleAndConferenceCallInfo: Method to get invoked when multiparty(single and conference) information
     *          is to be updated.
     * @param   bIsConferenceCallActive: Indicate whether the conference call is active or on hold. TRUE if conference
     *          call is active, false otherwise.
     * @return  void.
     */
    void updateSingleAndConferenceCallInfo(bool bIsConferenceCallActive);

    /**
     * @brief   updateSingleAndOutgoingCallInfo: Method to get invoked when multiparty(single and outgoing) information
     *          is to be updated.
     * @param   bIsSingleCallActive: Indicate whether the single call is active or on hold. TRUE if single
     *          call is active, false otherwise.
     * @param   bIsCallDialing: Indicate whether the outgoing call is in dialing or in alerting state. TRUE if
     *          ougoing call is isn dialing state, false otherwise.
     * @return  void.
     */
    void updateSingleAndOutgoingCallInfo(bool bIsSingleCallActive, bool bIsCallDialing);

    /**
     * @brief   updateConferenceAndOutgoingCallInfo: Method to get invoked when multiparty(conference and outgoing) information
     *          is to be updated.
     * @param   bIsConferenceCallActive: Indicate whether the conference call is active or on hold. TRUE if conference
     *          call is active, false otherwise.
     * @param   bIsCallDialing: Indicate whether the outgoing call is in dialing or in alerting state. TRUE if
     *          ougoing call is isn dialing state, false otherwise.
     * @return  void.
     */
    void updateConferenceAndOutgoingCallInfo(bool bIsConferenceCallActive, bool bIsCallDialing);

    /**
     * @brief   updateAllCallsTerminatedCallInfo: Method to get invoked when all calls terminated call information
     *          is to be updated.
     * @param   void.
     * @return  void.
     */
    void updateAllCallsTerminatedCallInfo();

    /**
     * @brief   showPhoneCallScreen: Method to get invoked when call screen/low priority call popup(PDC/RVC)
     *          needs to be displayed.
     * @param   void.
     * @return  TRUE if call screen is displayed, FALSE otherwise.
     */
    bool showPhoneCallScreen();

    /**
     * @brief   showCallScreenWithIncomingCallPopup: Method to get invoked when call screen with incoming call popup
     *          or low priority call popup(PDC/RVC) needs to be displayed.
     * @param   void.
     * @return  TRUE if call screen with incoming call popup is displayed, FALSE otherwise.
     */
    bool showCallScreenWithIncomingCallPopup();

    /**
     * @brief   showMicNotConnectedPopup: Method to get invoked to display mic not connected popup.
     * @param   void.
     * @return  TRUE if mic not connected popup is displayed, FALSE otherwise.
     */
    bool showMicNotConnectedPopup();

    /**
     * @brief   updateBTItemEnableState: Method to update the enable state of bluetooth setup
     *          list items.
     * @param   void.
     * @return  void.
     */
    void updateBTItemEnableState();

    /**
     * @brief   getOnGoingCallIndex: Method to search on active/held call index from call state info list.
     * @param   callStateInfoList: list of call state info.
     * @param   iIndex: index from where search will start.
     * @return  active/held call index from the list.
     */
    int getOnGoingCallIndex(const vector<SCallStateInfoList> &callStateInfoList, int iIndex);
    

    /******************************************************//**
     * @category GENERIC PROPERTIES
     *******************************************************/

    //! Pointer of CPhoneAdaptor class for creating singleton instance.
    static CPhoneAdaptor*                   m_pPhoneAdaptor;
    //! Framework class's object reference
    CFramework&                             m_objFramework;

    /******************************************************//**
     * @category BT CONNECTION RELATED PROPERTIES
     *******************************************************/
    /*!
     * Pointer of CPhoneConnectionManagerResourceImpl class to communicate with
     * phone connection manager resource layer.
     */
    CPhoneConnectionManagerResourceImpl*    m_pPhConnMgrResource;
    //! Pointer of CDeviceSearchListModel class
    CDeviceSearchListModel*                 m_pDeviceSearchListModel;
    //! Pointer of CPairedDeviceListModel class
    CPairedDeviceListModel*                 m_pPairedDeviceListModel;
    //! Pointer of CPhoneSetupListModel class
    CPhoneSetupListModel*                   m_pPhoneSetupListModel;
    //! Variable to hold passkey pin data.
    QString                                 m_strPassKeyPin;
    //! Variable to hold device name disconnected for HFP/A2DP profile.
    QString                                 m_strDisconnectedDeviceName;
    //! Variable to hold name of the deleted device.
    QString                                 m_strDeletedDeviceName;
    //! Flag to maintain whether bluetooth is enabled or not.
    bool                                    m_bIsBluetoothEnabled;
    //! Flag to maintain device search status
    bool                                    m_bDeviceSearchStatus;
    //! Flag to maintain bt visibility request status
    bool                                    m_bBtVisibilityReqStatus;
    //! Flag to maintain hu discoverable status
    bool                                    m_bHUDiscoverableStatus;
    //! Variable to hold selected item name
    QString                                 m_strSelItemName;
    //! Variable to hold selected item bt address
    QString                                 m_strSelItemBtAddr;
    //!Flag to maintain whether delete all option is selected
    bool                                    m_bIsDeleteAllSelected;

    //! Variable to hold device address connected for HFP/A2DP profile.
    QString                                 m_strConnectedDeviceAddr;
    //! Variable to hold device name connected for HFP/A2DP profile.
    QString                                 m_strConnectedDeviceName;
    //! Enum to hold device HFP profile connection status to show connected/disconnected popup
    EConnectionStatus                       m_eHFPConnectionStatus;
    //! Enum to hold device A2DP profile connection status to show connected/disconnected popup
    EConnectionStatus                       m_eA2DPConnectionStatus;
    //! Flag to maintain whether any device is connected for HFP profile or not.
    bool                                    m_bIsHFPConnected;
    //! Flag to maintain whether any device is connected for A2DP profile or not.
    bool                                    m_bIsA2DPConnected;
    //! Flag to maintain whether any device is connected for HFP/A2DP profile or not.
    bool                                    m_bIsDeviceConnected;

    /******************************************************//**
     * @category BT CALL RELATED PROPERTIES
     *******************************************************/
    /*!
     * Pointer of CPhoneCallManagerResourceImpl class to communicate with
     * phone call manager resource layer.
     */
    CPhoneCallManagerResourceImpl*          m_pPhCallMgrResource;
    //! Object of conference participant list model
    CConfParticipantsListModel              m_objConfParticipantsListModel;
    //! Variable to hold current call state
    CPhoneEnum::EPhoneCallState             m_ePhoneCallState;
    //! Object of call info to store incoming call info data
    CCallInfo                               m_objIncomingCallInfo;
    //! Object of call info to store first caller info data
    CCallInfo                               m_objFirstCallerInfo;
    //! Object of call info to store second caller info data
    CCallInfo                               m_objSecondCallerInfo;
    //! Flag to maintain status of accept incoming call request status
    bool                                    m_bAcceptCallRequestStatus;
    //! Flag to maintain status of reject incoming call request status
    bool                                    m_bRejectCallRequestStatus;
    //! Flag to maintain status of reject incoming call with SMS request status
    bool                                    m_bSendSMSRequestStatus;
    //! Flag to maintain status of dial request status
    bool                                    m_bDialRequestStatus;
    //! Flag to maintain status of merge calls request status
    bool                                    m_bMergeCallsRequestStatus;
    //! Flag to maintain status of swap calls request status
    bool                                    m_bSwapCallRequestStatus;
    //! Flag to maintain status of resume call request status
    bool                                    m_bResumeCallRequestStatus;
    //! Flag to maintain status of hold call request status
    bool                                    m_bHoldCallRequestStatus;
    //! Flag to maintain status of end call request status
    bool                                    m_bEndCallRequestStatus;
    //! Flag to maintain status of hf mode request status
    bool                                    m_bHFModeRequestStatus;
    //! Flag to maintain handsfree mode status whether in handsfree mode or handset mode
    bool                                    m_bIsHandsFreeMode;
    //! Flag to maintain status of network available
    bool                                    m_bIsNetworkAvailable;
    //! Enum to hold signal strength level
    CPhoneEnum::ESignalStrengthLevel        m_eSignalStrengthLevel;
    //! Enum to hold battery charge level
    CPhoneEnum::EBatteryChargeLevel         m_eBatteryChargeLevel;

    /******************************************************//**
     * @category PHONE BROWSE RELATED PROPERTIES
     *******************************************************/

    /** CTunerManualScaleListModel class object to store manual scale data.*/
    CPhoneBrowseTabBarModel m_objPhoneBrowseTabBarModel;
    /** CTunerManualScaleListModel class object to store manual scale data.*/
    CPhoneEnum::EPhoneBrowseType m_eCurrentPhoneBrowseScreen;

    /******************************************************//**
     * @category PHONE PIMDB RELATED PROPERTIES
     *******************************************************/
    /*!
     * Pointer of CPhonePIMDBResourceImpl class to communicate with
     * phone PimDb resource layer.
     */
    CPhonePIMDBResourceImpl*        m_pPhPimDbResource;
    //! Pointer of CCallLogListModel class for calllogs list
    CCallLogListModel*              m_pCallLogListModel;
    //! Pointer of CCallLogListModel class for frequently dialed list
    CCallLogListModel*              m_pFrequentlyDialedListModel;
    //! Pointer of CContactDetailListModel class for contact list
    CContactDetailListModel*        m_pContactListModel;
    //! Pointer of CContactDetailListModel class for contact detail list
    CContactDetailListModel*        m_pContactDetailListModel;
    //! Pointer of CContactDetailListModel class for favorite contact list
    CContactDetailListModel*        m_pFavoriteContactListModel;
    //! enum to maintain whether call log sync status.
    CPhoneEnum::EPhoneSyncStatus    m_ePimDbCallListSyncState;
    //! enum to maintain whether contact sync status.
    CPhoneEnum::EPhoneSyncStatus    m_ePimDbContactListSyncState;
    //! enum to maintain whether contact detail sync status.
    CPhoneEnum::EPhoneSyncStatus    m_ePimDbContactDetailListSyncState;
    //! enum to maintain whether favorite contact sync status.
    CPhoneEnum::EPhoneSyncStatus    m_ePimDbFavouriteListSyncState;
    //! enum to maintain whether frequently dialed list sync status.
    CPhoneEnum::EPhoneSyncStatus    m_ePimDbFrequentlyDialedListSyncState;
    //! enum to maintain the network RegState.
    EPhoneNetworkRegState  m_ePhoneNetworkRegState;

    //! Flag to maintain status of number pad is DTMF or dial Pad
    bool                            m_bIsInDTMFNumberPad;


    /* Index of the phone setup list for which the text message has to be changed for configure auto sms when user click edit button.*/
    int m_iCurrentMessageIndex;

    /* The text message of the phone setup list for which user has clicked edit button and needs to be changed */
    QString m_strCurrentMessageText;

    /**
     * @brief KEYPAD_CHAR_ARRAY_ROWS: Total Number of Rows.
     */
    const static int KEYPAD_CHAR_ARRAY_ROWS = 3;

    /**
     * @brief KEYPAD_CHAR_ARRAY_COLUMNS: Total Number of Columns.
     */
    const static int KEYPAD_CHAR_ARRAY_COLUMNS = 31;

    /* char array to store all the characters of keyboard */
    QChar m_aKeypadCharacters[KEYPAD_CHAR_ARRAY_ROWS][KEYPAD_CHAR_ARRAY_COLUMNS] = {
        {'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','~','Z','X','C', 'V','B','N','M',',','.',' ','~'},
        {'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','~','z','x','c', 'v','b','n','m',',','.',' ','~'},
        {'1','2','3','4','5','6','7','8','9','0','@','#','$','%','&','-','+','(',')','~','*','"','\'',':',';','!','?',',','.',' ','~'}};

    //!Used to hold SMS available to show or not
    bool                            m_bSMSAvailable;
    //!Used to hlod incoming SMS details
    SMessageData                    m_objMessageData;
    //!Used to hlod reading SMS details
    SMessageData                    m_objReadingMessageData;
    //! Used to hold value for can send SMS permission
    bool                            m_bIsSendingSMSAllowed;
    //! Flag to maintain whether favorite change is processing
    bool                            m_bIsFavoriteToggling;
    //! Used to hold contact info which is about to toggle in favorite list
    CPhoneData::SContactDetailInfo  m_objFavoriteTogglingInfo;
    //!Used to hold unread missed call count
    unsigned int                    m_uiUnreadMissedCallCount;
    //! Variable to hold phone notification text to be displayed in QAD
    QString                         m_strPhoneNotificationText;
    //! Enum to maintain TTS playstate
    CPhoneEnum::ETTSPlayState       m_eTTSPlayState;
    //! Flag to maintain whether to start new sms readout or not
    bool                            m_bStartNewSmsReadout;
    /**
     * @brief m_bIsOldestConnDeviceDeletionRequested: This variable holds the status
     *        of Oldest Device deletion, true if requested otherwise false.
     */
    bool                            m_bIsOldestConnDeviceDeletionRequested;
    //! Use to hold last top index of Contact list
    int                             m_iContactListCurrentTopIndex;
    //! Flag to hold whether to show incoming sms popup or not
    bool                            m_bShowIncomingSmsPopup;
    //! Timer for end call screen
    QTimer                          m_objEndCallScreenTimer;
    //!Flag to maintain whether delete all devices is success or not
    bool                            m_bDeleteAllDevicesStatus;
    //!Flag to maintain whether delete device is success or not
    bool                            m_bDeleteDeviceStatus;

    //!variable to hold the current status of low priority phone popup.
    bool                            m_bLPPhonePopupStatus;

    //!variable to hold the previous saved paired list count.
    int                            m_iPreviousPairedListCount;

    //!variable to hold the current paired list count.
    int                            m_iCurrentPairedListCount;
    //!variable holds current status of bt vr.
    bool                           m_bPhoneBtVrModeStatus;
    //!variable holds visible status of phone bt vr overlay.
    bool                           m_bIsPhoneBtVROverlayVisible;
    //!data to hold BT VR feature support value
    bool                           m_bBtVrSupported;
    //!data to hold whether connected phone is iPhone or not
    bool                           m_bApplePhoneConnected;
};

#endif // CPHONEADAPTOR_H

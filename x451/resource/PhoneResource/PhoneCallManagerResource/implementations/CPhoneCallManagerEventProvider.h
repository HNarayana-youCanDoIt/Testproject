/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneCallManagerEventProvider.h
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         This file contains CPhoneCallManagerEventProvider class that shall publish events
 * whenever HMI PhoneCallManagerResource layer receive some response or callbacks from CallManager proxy.
 */

#ifndef CPHONECALLMANAGEREVENTPROVIDER_H
#define CPHONECALLMANAGEREVENTPROVIDER_H

#include <QObject>
#include "PhoneResource/CPhoneResourceEnums.h"

/*!
 * @class CPhoneCallManagerEventProvider
 * @brief This class shall publish events whenever HMI PhoneCallManagerResource layer receive
 * some response or callbacks from CallManager proxy.
 */
class CPhoneCallManagerEventProvider: public QObject
{
    Q_OBJECT

public:
    CPhoneCallManagerEventProvider(QObject* pParent = 0);
    ~CPhoneCallManagerEventProvider();

    /************************************************************************//**
     * @category    METHODS
     * @brief       Methods that would be used by the PhoneCallManagerResource
     * layer to indirectly emit signals to the phone application layer
     ************************************************************************/

    /*!
     * @brief   callStateInfoReceived: Method to inform phone application layer regarding call state info.
     * @param   void.
     * @return  void.
     */
    void callStateInfoReceived();

    /*!
     * @brief   hfFeaturesListReceived: Method to inform phone application layer regarding hf feature list.
     * @param   void.
     * @return  void.
     */
    void hfFeaturesListReceived();

    /*!
     * @brief   operatorInfoListReceived: Method to inform phone application layer regarding operator info list.
     * @param   void.
     * @return  void.
     */
    void operatorInfoListReceived();

    /*!
     * @brief   rssiChargeInfoListReceived: Method to inform phone application layer regarding rssi charge info list.
     * @param   void.
     * @return  void.
     */
    void rssiChargeInfoListReceived();

    /*!
     * @brief   hfModeStatusReceived: Method to inform phone application layer regarding hf mode status.
     * @param   void.
     * @return  void.
     */
    void hfModeStatusReceived();

    /*!
     * @brief   callDurationReceived: Method to inform phone application layer regarding call duration.
     * @param   void.
     * @return  void.
     */
    void callDurationReceived();

    /*!
     * @brief   phoneBtVrModeStatusReceived: Method to inform phone application layer regarding phone bt vr mode status.
     * @param   void.
     * @return  void.
     */
    void phoneBtVrModeStatusReceived();

    /*!
     * @brief   acceptIncomingCallAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of acceptIncomingCallAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void acceptIncomingCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                 EMethodCallErrorType eMethodCallErrorType);

   /*!
     * @brief   rejectIncomingCallAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of rejectIncomingCallAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void rejectIncomingCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                 EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   dialAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of dialAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void dialAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                   EMethodCallErrorType eMethodCallErrorType);
    /*!
     * @brief   conferenceCallAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of conferenceCallAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void conferenceCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                             EMethodCallErrorType eMethodCallErrorType);
    /*!
     * @brief   swapCallsAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of swapCallsAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void swapCallsAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                        EMethodCallErrorType eMethodCallErrorType);
    /*!
     * @brief   resumeHeldCallAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of resumeHeldCallAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void resumeHeldCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                             EMethodCallErrorType eMethodCallErrorType);
    /*!
     * @brief   holdActiveCallAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of holdActiveCallAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void holdActiveCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                             EMethodCallErrorType eMethodCallErrorType);
    /*!
     * @brief   endCallAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of endCallAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void endCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                      EMethodCallErrorType eMethodCallErrorType);
    /*!
     * @brief   endActiveCallAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of endActiveCallAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void endActiveCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                            EMethodCallErrorType eMethodCallErrorType);
    /*!
     * @brief   endAllCallsAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of endAllCallsAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void endAllCallsAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                          EMethodCallErrorType eMethodCallErrorType);
    /*!
     * @brief   sendDtmfToneAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of sendDtmfToneAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sendDtmfToneAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                           EMethodCallErrorType eMethodCallErrorType);
    /*!
     * @brief   setHfModeAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of setHfModeAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void setHfModeAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                        EMethodCallErrorType eMethodCallErrorType);

    /*!
     * @brief   setVrModeAsyncMethodCallStatus: Method to inform phone application layer regarding method call status
     *          of setVrModeAsync.
     * @param   eMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   eMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void setVrModeAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                        EMethodCallErrorType eMethodCallErrorType);

signals:
    /******************************************************//**
     * @category    SIGNALS
     * @brief       Signals that shall be emitted to the phone
     * application layer
     *******************************************************/

    /*!
     * @brief   sigCallStateInfoReceived: Signal that shall be emited to notify call state info is received.
     * @param   void.
     * @return  void.
     */
    void sigCallStateInfoReceived();

    /*!
     * @brief   sigHfFeaturesListReceived: Signal that shall be emited to notify HF feature list is received.
     * @param   void.
     * @return  void.
     */
    void sigHfFeaturesListReceived();

    /*!
     * @brief   sigOperatorInfoListReceived: Signal that shall be emited to notify operator info list is received.
     * @param   void.
     * @return  void.
     */
    void sigOperatorInfoListReceived();

    /*!
     * @brief   sigRssiChargeInfoListReceived: Signal that shall be emited to notify Rssi charge info list is received.
     * @param   void.
     * @return  void.
     */
    void sigRssiChargeInfoListReceived();

    /*!
     * @brief   sigHfModeStatusReceived: Signal that shall be emited to notify HF mode status is received.
     * @param   void.
     * @return  void.
     */
    void sigHfModeStatusReceived();

    /*!
     * @brief   sigCallDurationReceived: Signal that shall be emited to notify call duration is received.
     * @param   void.
     * @return  void.
     */
    void sigCallDurationReceived();

    /*!
     * @brief   sigPhoneBtVrModeStatusReceived: sigPhoneBtVrModeStatusReceived: Signal that shall be emited to notify phone bt vr mode status is received.
     * @param   void.
     * @return  void.
     */
    void sigPhoneBtVrModeStatusReceived();

    /*!
     * @brief   sigAcceptIncomingCallAsyncMethodCallStatus: Signal that shall be emited to notify acceptIncomingCallAsync method call
     *          status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigAcceptIncomingCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigRejectIncomingCallAsyncMethodCallStatus: Signal that shall be emited to notify rejectIncomingCallAsync method call
     *          status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigRejectIncomingCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigDialAsyncMethodCallStatus: Signal that shall be emited to notify dialAsync method call status is received.
     * @param   iMethodCallStatus:  call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType:  type of the error received after invoking the method.
     * @return  void.
     */
    void sigDialAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigConferenceCallAsyncMethodCallStatus: Signal that shall be emited to notify conferenceCallAsync method call status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigConferenceCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigSwapCallsAsyncMethodCallStatus: Signal that shall be emited to notify swapCallsAsync method call status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigSwapCallsAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigResumeHeldCallAsyncMethodCallStatus: Signal that shall be emited to notify resumeHeldCallAsync method call status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigResumeHeldCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigHoldActiveCallAsyncMethodCallStatus: Signal that shall be emited to notify holdActiveCallAsync method call status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigHoldActiveCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigEndCallAsyncMethodCallStatus: Signal that shall be emited to notify endCallAsync method call status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigEndCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigEndActiveCallAsyncMethodCallStatus: Signal that shall be emited to notify endActiveCallAsync method call status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigEndActiveCallAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigEndAllCallsAsyncMethodCallStatus: Signal that shall be emited to notify endAllCallsAsync method call status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigEndAllCallsAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigSendDtmfToneAsyncMethodCallStatus: Signal that shall be emited to notify sendDtmfToneAsync method call status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigSendDtmfToneAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigSetHfModeAsyncMethodCallStatus: Signal that shall be emited to notify setHfModeAsync method call status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigSetHfModeAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);

    /*!
     * @brief   sigSetVrModeAsyncMethodCallStatus: Signal that shall be emited to notify setVrModeAsync method call status is received.
     * @param   iMethodCallStatus: call status of the method invoked, whether success or not.
     * @param   iMethodCallErrorType: type of the error received after invoking the method.
     * @return  void.
     */
    void sigSetVrModeAsyncMethodCallStatus(int iMethodCallStatus, int iMethodCallErrorType);
};

#endif // CPHONECALLMANAGEREVENTPROVIDER_H

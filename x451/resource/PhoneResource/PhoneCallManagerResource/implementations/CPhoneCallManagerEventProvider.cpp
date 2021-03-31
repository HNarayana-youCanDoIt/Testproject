/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneCallManagerEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 * CPhoneCallManagerEventProvider class
 */

#include "CPhoneCallManagerEventProvider.h"
#include "logging.h"

CPhoneCallManagerEventProvider::CPhoneCallManagerEventProvider(QObject* pParent)
    : QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}

CPhoneCallManagerEventProvider::~CPhoneCallManagerEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}

/************************************************************************//**
 * @category    METHODS
 ************************************************************************/
void CPhoneCallManagerEventProvider::callStateInfoReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigCallStateInfoReceived();
}

void CPhoneCallManagerEventProvider::hfFeaturesListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigHfFeaturesListReceived();
}

void CPhoneCallManagerEventProvider::operatorInfoListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigOperatorInfoListReceived();
}

void CPhoneCallManagerEventProvider::rssiChargeInfoListReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigRssiChargeInfoListReceived();
}

void CPhoneCallManagerEventProvider::hfModeStatusReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigHfModeStatusReceived();
}

void CPhoneCallManagerEventProvider::callDurationReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigCallDurationReceived();
}

void CPhoneCallManagerEventProvider::phoneBtVrModeStatusReceived()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigPhoneBtVrModeStatusReceived();
}

void CPhoneCallManagerEventProvider::acceptIncomingCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                             EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigAcceptIncomingCallAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::rejectIncomingCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                             EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigRejectIncomingCallAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::dialAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                               EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigDialAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::conferenceCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                         EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigConferenceCallAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::swapCallsAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                    EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigSwapCallsAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::resumeHeldCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                         EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigResumeHeldCallAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::holdActiveCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                         EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigHoldActiveCallAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::endCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                  EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigEndCallAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::endActiveCallAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                        EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigEndActiveCallAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::endAllCallsAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                      EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigEndAllCallsAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::sendDtmfToneAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                       EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigSendDtmfToneAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}
void CPhoneCallManagerEventProvider::setHfModeAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus,
                                                                    EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigSetHfModeAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

void CPhoneCallManagerEventProvider::setVrModeAsyncMethodCallStatus(EMethodCallStatus eMethodCallStatus, EMethodCallErrorType eMethodCallErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigSetVrModeAsyncMethodCallStatus(eMethodCallStatus, eMethodCallErrorType);
}

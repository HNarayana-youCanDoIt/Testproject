/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhonePIMDBEventProvider.cpp
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         This file contains CPhonePIMDBEventProvider class that shall publish events
 * whenever HMI CPhonePIMDBResource layer receive some response or callbacks from PimDbResource proxy.
 */

#include "CPhonePIMDBEventProvider.h"
#include "logging.h"

CPhonePIMDBEventProvider::CPhonePIMDBEventProvider(QObject* pParent):
    QObject(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
}

CPhonePIMDBEventProvider::~CPhonePIMDBEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
}

void CPhonePIMDBEventProvider::updatePimDbServiceAvailableStatus(bool bPimDbServiceAvailableStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, bPimDbServiceAvailableStatus = %d", __FUNCTION__, bPimDbServiceAvailableStatus);
    emit sigPimDbServiceAvailableStatusChanged(bPimDbServiceAvailableStatus);
}

void CPhonePIMDBEventProvider::onContactNameOrderAttributeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigContactNameOrderAttributeChanged();
}

void CPhonePIMDBEventProvider::onDeviceListAttributeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigDeviceListAttributeChanged();
}

void CPhonePIMDBEventProvider::onEmergencyContactListAttributeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigEmergencyContactListAttributeChanged();
}

void CPhonePIMDBEventProvider::onMessageNotificationEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigMessageNotificationEvent();
}

void CPhonePIMDBEventProvider::onNewCallListEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigNewCallListEvent();
}

void CPhonePIMDBEventProvider::onSessionClosedSelectiveEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSessionClosedSelectiveEvent();
}

void CPhonePIMDBEventProvider::onSessionQueryUpdateSelectiveEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSessionQueryUpdateSelectiveEvent();
}

void CPhonePIMDBEventProvider::onSessionQueryWindowUpdateSelectiveEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSessionQueryWindowUpdateSelectiveEvent();
}

void CPhonePIMDBEventProvider::onSmsNotificationEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSmsNotificationEvent();
}

void CPhonePIMDBEventProvider::onSmsSupportedFeatureAttributeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSmsSupportedFeatureAttributeChanged();
}

void CPhonePIMDBEventProvider::onIsSendingSMSAllowedAttributeChanged(bool bIsSendingSMSAllowed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigIsSendingSMSAllowedAttributeChanged(bIsSendingSMSAllowed);
}

void CPhonePIMDBEventProvider::onUnreadMissedCallEvent()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigUnreadMissedCallEvent();
}

void CPhonePIMDBEventProvider::onGetSmsSupportedFeatureAttributeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    emit sigGetSmsSupportedFeature();
}

void CPhonePIMDBEventProvider::onOpenSessionAsyncMethodCallStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigOpenSessionAsyncMethodCallStatus();
}

void CPhonePIMDBEventProvider::onSetSessionQueryAsyncMethodCallStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSetSessionQueryAsyncMethodCallStatus();
}

void CPhonePIMDBEventProvider::onCloseSessionAsyncMethodCallStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigCloseSessionAsyncMethodCallStatus();
}

void CPhonePIMDBEventProvider::onSetSessionQueryWindowAsyncMethodCallStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSetSessionQueryWindowAsyncMethodCallStatus();
}

void CPhonePIMDBEventProvider::onGetContactsByIDAsyncMethodCallStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigGetContactsByIDAsyncMethodCallStatus();
}

void CPhonePIMDBEventProvider::onAddContactToFavouriteListAsyncMethodCallStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigAddContactToFavouriteListAsyncMethodCallStatus();
}

void CPhonePIMDBEventProvider::onDeleteContactFromFavouriteListAsyncMethodCallStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigDeleteContactFromFavouriteListAsyncMethodCallStatus();
}

void CPhonePIMDBEventProvider::onCallLogStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigCallLogStatusChanged(iStatus);
}

void CPhonePIMDBEventProvider::onContactStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigContactStatusChanged(iStatus);
}

void CPhonePIMDBEventProvider::onContactDetailStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigContactDetailStatusChanged(iStatus);
}

void CPhonePIMDBEventProvider::onFavoriteStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigFavoriteStatusChanged(iStatus);
}

void CPhonePIMDBEventProvider::onFrequentlyDialedStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigFrequenltDialedStatusChanged(iStatus);
}

void CPhonePIMDBEventProvider::onSMSStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSMSStatusChanged(iStatus);
}

void CPhonePIMDBEventProvider::onSMSTemplateStatusChanged(int iStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSMSTemplateStatusChanged(iStatus);
}

void CPhonePIMDBEventProvider::onCallLogUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigCallLogUpdated();
}

void CPhonePIMDBEventProvider::onFrequentlyDialedListUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigFrequentlyDialedListUpdated();
}

void CPhonePIMDBEventProvider::onContactUpdated(unsigned short usStartIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigContactUpdated(usStartIndex);
}

void CPhonePIMDBEventProvider::onContactDetailUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigContactDetailUpdated();
}

void CPhonePIMDBEventProvider::onFavoriteUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigFavoriteUpdated();
}

void CPhonePIMDBEventProvider::onSMSUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSMSUpdated();
}

void CPhonePIMDBEventProvider::onSMSTemplateUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSMSTemplateUpdated();
}

void CPhonePIMDBEventProvider::onAddContactToFavouriteComplete(bool bIsSuccess)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigAddContactToFavouriteComplete(bIsSuccess);
}

void CPhonePIMDBEventProvider::onRemoveContactFromFavouriteComplete(bool bIsSuccess)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigRemoveContactFromFavouriteComplete(bIsSuccess);
}

void CPhonePIMDBEventProvider::onSendSMSComplete(bool bIsSuccess)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    emit sigSendSMSAsyncMethodCallStatus(bIsSuccess);
}

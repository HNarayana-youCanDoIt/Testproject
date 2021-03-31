/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CPhonePIMDBResourceImpl.cpp
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         This file contains CPhonePIMDBResourceImpl class that shall implement the
 * PimDbResource interface and is a mediator between lower layer(press control)
 * and upper layer(application).
 */

#include "CPhonePIMDBResourceImpl.h"
#include <capi/CAPIClientAbstraction.hpp>
#include <ResourceDeploymentConfig.h>
#include <ResourceMaster.h>
#include "logging.h"

//______________________________________________________________________________________________________
CPhonePIMDBResourceImpl::CPhonePIMDBResourceImpl()
    : m_pPhonePIMDBEventProvider(new CPhonePIMDBEventProvider()),
      m_PimDbHandlerProxy(ResourceDeploymentConfig::getConfig().m_Phone_PimDb_Proxy.domain,
                          ResourceDeploymentConfig::getConfig().m_Phone_PimDb_Proxy.instance),
      m_bPimDbServiceAvailable(false),
      m_iSessionID(-1),
      m_strDeviceBtAddr(""),
      m_iCallListSessionQueryID(-1),
      m_iContactListSessionQueryID(-1),
      m_iFavouriteListSessionQueryID(-1),
      m_iSmsListSessionQueryID(-1),
      m_iSMSTemplateListSessionQueryID(-1),
      m_iFrequentDialedListSessionQueryID(-1),
      m_iCallListCount(-1),
      m_iContactListCount(-1),
      m_iFavouriteListCount(-1),
      m_iSmsListCount(-1),
      m_iSMSTemplateListCount(-1),
      m_iFrequentDialedListCount(-1),
      m_bIsCallDataReady(false),
      m_bIsContactDataReady(false),
      m_bIsFavouriteDataReady(false),
      m_bIsSmsDataReady(false),
      m_bIsSMSTemplateDataReady(false),
      m_bIsFrequentlyDialedDataReady(false),
      m_bIsSendingSMSAllowed(false),      
      m_eCallListSyncStatus(EDataReadStateType::DATA_READ_OFF),
      m_eContactListSyncStatus(EDataReadStateType::DATA_READ_OFF),
      m_eContactDetailListSyncStatus(EDataReadStateType::DATA_READ_OFF),
      m_eFavouriteListSyncStatus(EDataReadStateType::DATA_READ_OFF),
      m_eSmsListSyncStatus(EDataReadStateType::DATA_READ_OFF),
      m_eSMSTemplateListSyncStatus(EDataReadStateType::DATA_READ_OFF),
      m_eFrequentlyDialedListSyncStatus(EDataReadStateType::DATA_READ_OFF)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectCallListData.clear();
    m_vectContactListData.clear();
    m_vectContactDetailListData.clear();
    m_vectFavouriteListData.clear();
    m_vectSmsListData.clear();
    m_vectSMSTemplateListData.clear();
    m_objSmsData.clear();
    m_vectSmsSupportedFeatureList.clear();
    m_vectFrequentlyDialedListData.clear();
    subscribePimDbHandlerCb();
}
//______________________________________________________________________________________________________
CPhonePIMDBResourceImpl::~CPhonePIMDBResourceImpl()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);//TODO:Will be Implemented as per need
}

//______________________________________________________________________________________________________
CPhonePIMDBEventProvider *CPhonePIMDBResourceImpl::getPhonePimDbEventProvider()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_pPhonePIMDBEventProvider;
}
//______________________________________________________________________________________________________
void CPhonePIMDBResourceImpl::getProxyStatusEventCb(CommonAPI::AvailabilityStatus eStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, status = %d", __FUNCTION__, static_cast<int>(eStatus));
    if(CommonAPI::AvailabilityStatus::AVAILABLE == eStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s Phone PIMD controler available", __FUNCTION__);
        m_bPimDbServiceAvailable = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s Phone PIMD controler NOT available", __FUNCTION__);
        m_bPimDbServiceAvailable = false;
        closePimDbSession();
    }

    // Propagate the information to the phone application layer
    if (m_pPhonePIMDBEventProvider)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"update bluetooth service available status to upper layer");
        m_pPhonePIMDBEventProvider->updatePimDbServiceAvailableStatus(getPimDbServiceAvailableStatus());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"data event provider object not created");
    }
}

bool CPhonePIMDBResourceImpl::getPimDbServiceAvailableStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    return m_bPimDbServiceAvailable;
}
//______________________________________________________________________________________________________
void CPhonePIMDBResourceImpl::subscribePimDbHandlerCb()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    /*PIM DB HANDLER 'm_PimDbHandlerProxy' SIGNALS*/
    SUBSCRIBE(m_PimDbHandlerProxy,getProxyStatusEvent(),& CPhonePIMDBResourceImpl::getProxyStatusEventCb,_1);
    SUBSCRIBE(m_PimDbHandlerProxy,getContactNameOrderAttribute().getChangedEvent(),&CPhonePIMDBResourceImpl::getContactNameOrderAttributeChangedCb,_1);
    SUBSCRIBE(m_PimDbHandlerProxy,getDeviceListAttribute().getChangedEvent(),&CPhonePIMDBResourceImpl::getDeviceListAttributeChangedCb,_1);
    SUBSCRIBE(m_PimDbHandlerProxy,getEmergencyContactListAttribute().getChangedEvent(),&CPhonePIMDBResourceImpl::getEmergencyContactListAttributeChangedCb,_1);
    SUBSCRIBE(m_PimDbHandlerProxy,getMessageNotificationEvent(),&CPhonePIMDBResourceImpl::getMessageNotificationEventCb,_1,_2,_3,_4);
    SUBSCRIBE(m_PimDbHandlerProxy,getNewCallListEvent(),&CPhonePIMDBResourceImpl::getNewCallListEventCb,_1,_2);
    SUBSCRIBE(m_PimDbHandlerProxy,getSessionClosedSelectiveEvent(),&CPhonePIMDBResourceImpl::getSessionClosedSelectiveEventCb,_1,_2,_3);
    SUBSCRIBE(m_PimDbHandlerProxy,getSessionQueryUpdateSelectiveEvent(),&CPhonePIMDBResourceImpl::getSessionQueryUpdateSelectiveEventCb,_1,_2,_3,_4,_5);
    SUBSCRIBE(m_PimDbHandlerProxy,getSessionQueryWindowUpdateSelectiveEvent(),&CPhonePIMDBResourceImpl::getSessionQueryWindowUpdateSelectiveEventCb,_1,_2,_3,_4,_5);
    SUBSCRIBE(m_PimDbHandlerProxy,getSmsSupportedFeatureAttribute().getChangedEvent(),&CPhonePIMDBResourceImpl::getSmsSupportedFeatureAttributeChangedCb,_1);
    SUBSCRIBE(m_PimDbHandlerProxy,getSMSNotificationEvent(),&CPhonePIMDBResourceImpl::getSmsNotificationEventCb,_1,_2,_3);
    SUBSCRIBE(m_PimDbHandlerProxy,getUnreadMissedCallEvent(),&CPhonePIMDBResourceImpl::getUnreadMissedCallEventCb,_1,_2,_3,_4);
}
//______________________________________________________________________________________________________
string CPhonePIMDBResourceImpl::getContactNamesForCallList(BTPresTypes::phonebookEntry objBTPresPBEntry)
{
    string strFormattedName;
    if(objBTPresPBEntry.getNameList().end() != objBTPresPBEntry.getNameList().find(BTPresTypes::eContactNameField::CONTACT_FIELD_FORMATTED_NAME))
    {
        strFormattedName = objBTPresPBEntry.getNameList().at(BTPresTypes::eContactNameField::CONTACT_FIELD_FORMATTED_NAME);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s Contact name not found in contact data", __FUNCTION__);
    }
    return strFormattedName;
}
//______________________________________________________________________________________________________
string CPhonePIMDBResourceImpl::getPhoneNumbersForCallList(BTPresTypes::phonebookEntry objBTPresPBEntry)
{
    string strFormattedName;
    if(objBTPresPBEntry.getPhoneNumberList().end() != objBTPresPBEntry.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_CELL))
    {
        BTPresTypes::arString phoneNumberList = objBTPresPBEntry.getPhoneNumberList().at(BTPresTypes::eTelType::CONTACT_TEL_TYPE_CELL);
        for(auto it = phoneNumberList.begin(); it != phoneNumberList.end(); ++it)
        {
            strFormattedName = *it;
        }
    }
    else if(objBTPresPBEntry.getPhoneNumberList().end() != objBTPresPBEntry.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_HOME))
    {
        BTPresTypes::arString phoneNumberList = objBTPresPBEntry.getPhoneNumberList().at(BTPresTypes::eTelType::CONTACT_TEL_TYPE_HOME);
        for(auto it = phoneNumberList.begin(); it != phoneNumberList.end(); ++it)
        {
            strFormattedName = *it;
        }
    }
    else if(objBTPresPBEntry.getPhoneNumberList().end() != objBTPresPBEntry.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_OTHER))
    {
        BTPresTypes::arString phoneNumberList = objBTPresPBEntry.getPhoneNumberList().at(BTPresTypes::eTelType::CONTACT_TEL_TYPE_OTHER);
        for(auto it = phoneNumberList.begin(); it != phoneNumberList.end(); ++it)
        {
            strFormattedName = *it;
        }
    }
    else if(objBTPresPBEntry.getPhoneNumberList().end() != objBTPresPBEntry.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_WORK))
    {
        BTPresTypes::arString phoneNumberList = objBTPresPBEntry.getPhoneNumberList().at(BTPresTypes::eTelType::CONTACT_TEL_TYPE_WORK);
        for(auto it = phoneNumberList.begin(); it != phoneNumberList.end(); ++it)
        {
            strFormattedName = *it;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s Contact number not found in contact data", __FUNCTION__);
    }
    return strFormattedName;
}

//______________________________________________________________________________________________________
EContactType CPhonePIMDBResourceImpl::getPhoneNumberTypeForCallList(BTPresTypes::phonebookEntry objBTPresPBEntry)
{
    EContactType eFormattedNumberType = EContactType::CONTACT_TYPE_DEFAULT;
    if(objBTPresPBEntry.getPhoneNumberList().end() != objBTPresPBEntry.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_CELL))
    {
        eFormattedNumberType = EContactType::CONTACT_TYPE_MOBILE;
    }
    else if(objBTPresPBEntry.getPhoneNumberList().end() != objBTPresPBEntry.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_HOME))
    {
        eFormattedNumberType = EContactType::CONTACT_TYPE_HOME;
    }
    else if(objBTPresPBEntry.getPhoneNumberList().end() != objBTPresPBEntry.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_OTHER))
    {
        eFormattedNumberType = EContactType::CONTACT_TYPE_OTHER;
    }
    else if(objBTPresPBEntry.getPhoneNumberList().end() != objBTPresPBEntry.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_WORK))
    {
        eFormattedNumberType = EContactType::CONTACT_TYPE_WORK;
    }
    else
    {
        ////Nothing To Do
    }
    return eFormattedNumberType;
}

//______________________________________________________________________________________________________
string CPhonePIMDBResourceImpl::getFormatedDateAndTime(BTPresTypes::phonebookEntry objBTPresPBEntry)
{
    string strFormattedDayTime="";
    string strYear = "";
    string strMonth = "";
    string strDate = "";
    string strHour = "";
    string strMinute = "";
    string strSecond = "";
    BTPresTypes::mDaytoDateTime dayToDateTimeMap = objBTPresPBEntry.getDaytoDateTimeMap();
    if(1 == dayToDateTimeMap.size())
    {
        auto iter = dayToDateTimeMap.begin();
        BTPresTypes::eDay day = iter->first;
        BTPresTypes::mDateTime dateTime = iter->second;

        auto iter2 = dateTime.find(BTPresTypes::eDateTime::YEAR);
        // For Ford, the year is in 2-digit format, if what we receive is 4-digits, then use the lower 2 digits only.
        strYear = (iter2 != dateTime.end()) ? (2 == iter2->second.size()) ? iter2->second : iter2->second.substr(2,2) : std::string();
        iter2 = dateTime.find(BTPresTypes::eDateTime::MONTH);
        strMonth = (iter2 != dateTime.end()) ? iter2->second : std::string();
        iter2 = dateTime.find(BTPresTypes::eDateTime::DATE);
        strDate = (iter2 != dateTime.end()) ? iter2->second : std::string();
        iter2 = dateTime.find(BTPresTypes::eDateTime::HOUR);
        strHour = (iter2 != dateTime.end()) ? iter2->second : std::string();
        iter2 = dateTime.find(BTPresTypes::eDateTime::MINUTE);
        strMinute = (iter2 != dateTime.end()) ? iter2->second : std::string();
        iter2 = dateTime.find(BTPresTypes::eDateTime::SECOND);
        strSecond = (iter2 != dateTime.end()) ? iter2->second : std::string();

        switch(day)
        {
        case BTPresTypes::eDay::TODAY:
            strFormattedDayTime = "Today";
            break;

        case BTPresTypes::eDay::YESTERDAY:
            strFormattedDayTime = "Yesterday";
            break;

        case BTPresTypes::eDay::SUNDAY:
            strFormattedDayTime = "Sun";
            break;

        case BTPresTypes::eDay::MONDAY:
            strFormattedDayTime = "Mon";
            break;

        case BTPresTypes::eDay::TUESDAY:
            strFormattedDayTime = "Tue";
            break;

        case BTPresTypes::eDay::WEDNESDAY:
            strFormattedDayTime = "Wed";
            break;

        case BTPresTypes::eDay::THURSDAY:
            strFormattedDayTime = "Thu";
            break;

        case BTPresTypes::eDay::FRIDAY:
            strFormattedDayTime = "Fri";
            break;

        case BTPresTypes::eDay::SATURDAY:
            strFormattedDayTime = "Sat";
            break;
        case BTPresTypes::eDay::DISPLAY_CALENDER_DATE:
            strFormattedDayTime = strDate + "/" + strMonth;
            break;

        default:
            strFormattedDayTime = strDate + "/" + strMonth + "/" + strYear;
            break;
        }
        strFormattedDayTime = strFormattedDayTime + ", " + strHour + ":" + strMinute;
    }
    return strFormattedDayTime;
}

ERemoteDeviceOS CPhonePIMDBResourceImpl::getRemoteDevOS(int iRemoteDeviceOS)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    ERemoteDeviceOS eRemoteDeviceOS = OS_UNKNOWN;
    switch(iRemoteDeviceOS)
    {
    case BTPresTypes::eRemoteDeviceOS::OS_WINDOWS:
        eRemoteDeviceOS = OS_WINDOWS;
        break;
    case BTPresTypes::eRemoteDeviceOS::OS_ANDROID:
        eRemoteDeviceOS = OS_ANDROID;
        break;
    case BTPresTypes::eRemoteDeviceOS::OS_IOS:
        eRemoteDeviceOS = OS_IOS;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, " %s wrong value for remote device OS passed", __FUNCTION__);
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, " %s remote device OS is: %d", __FUNCTION__, eRemoteDeviceOS);
    return eRemoteDeviceOS;
}
//______________________________________________________________________________________________________

void CPhonePIMDBResourceImpl::changeCallListSyncState(EDataReadStateType eState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_eCallListSyncStatus = eState;
    if (m_pPhonePIMDBEventProvider)
    {
		LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, EDataReadStateType:%d", __FUNCTION__, static_cast<int>(eState));
        m_pPhonePIMDBEventProvider->onCallLogStatusChanged(eState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::changeContactListSyncState(EDataReadStateType eState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_eContactListSyncStatus = eState;
    if (m_pPhonePIMDBEventProvider)
    {
		LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, EDataReadStateType:%d", __FUNCTION__, static_cast<int>(eState));
        m_pPhonePIMDBEventProvider->onContactStatusChanged(eState);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::changeContactDetailListSyncState(EDataReadStateType eState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_eContactDetailListSyncStatus = eState;
    if (m_pPhonePIMDBEventProvider)
    {
		LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, EDataReadStateType:%d", __FUNCTION__, static_cast<int>(eState));
        m_pPhonePIMDBEventProvider->onContactDetailStatusChanged(static_cast<int>(eState));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::changeFavouriteListSyncState(EDataReadStateType eState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_eFavouriteListSyncStatus = eState;
    if (m_pPhonePIMDBEventProvider)
    {
		LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, EDataReadStateType:%d", __FUNCTION__, static_cast<int>(eState));
        m_pPhonePIMDBEventProvider->onFavoriteStatusChanged(static_cast<int>(eState));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::changeFrequentlyDialedListSyncState(EDataReadStateType eState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: EDataReadStateType: %d", __FUNCTION__, static_cast<int>(eState));
    m_eFrequentlyDialedListSyncStatus = eState;
    if (m_pPhonePIMDBEventProvider)
    {
        m_pPhonePIMDBEventProvider->onFrequentlyDialedStatusChanged(static_cast<int>(eState));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::changeSmsListSyncState(EDataReadStateType eState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_eSmsListSyncStatus = eState;
    if (m_pPhonePIMDBEventProvider)
    {
		LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, EDataReadStateType:%d", __FUNCTION__, static_cast<int>(eState));
        m_pPhonePIMDBEventProvider->onSMSStatusChanged(static_cast<int>(eState));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::changeSmsTemplateListSyncState(EDataReadStateType eState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_eSMSTemplateListSyncStatus = eState;
    if (m_pPhonePIMDBEventProvider)
    {
		LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s, EDataReadStateType:%d", __FUNCTION__, static_cast<int>(eState));
        m_pPhonePIMDBEventProvider->onSMSTemplateStatusChanged(static_cast<int>(eState));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::changeIsSendingSMSAllowed(bool bIsSendingSMSAllowed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, bIsSendingSMSAllowed %d", __FUNCTION__, bIsSendingSMSAllowed);
    m_bIsSendingSMSAllowed = bIsSendingSMSAllowed;
    if (m_pPhonePIMDBEventProvider)
    {
        m_pPhonePIMDBEventProvider->onIsSendingSMSAllowedAttributeChanged(m_bIsSendingSMSAllowed);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}
//______________________________________________________________________________________________________
void CPhonePIMDBResourceImpl::tryRequestQueryForCallLog()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: m_iSessionID: %d, m_bIsCallDataReady: %d, callListSyncState: %d",
             __FUNCTION__, m_iSessionID, m_bIsCallDataReady, static_cast<int>(getCallListSyncState()));
    if ((0 < m_iSessionID) && (m_bIsCallDataReady))
    {
        if ((EDataReadStateType::DATA_READ_READY == getCallListSyncState()) || (EDataReadStateType::DATA_READ_FAIL == getCallListSyncState()))
        {
            if(getPimDbServiceAvailableStatus())
            {
                changeCallListSyncState(EDataReadStateType::DATA_READING);

                auto internalCallback_CallStack = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryAsyncReqCb,
                                                            this,
                                                            _1,
                                                            _2,
                                                            _3,
                                                            _4,
                                                            _5,
                                                            _6,
                                                            BTPresTypes::eDatabaseType::DB_TYPE_COMBINED_CALLSTACK
                                                            );
                CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);
                m_PimDbHandlerProxy->setSessionQueryAsync(m_iSessionID,
                                                          BTPresTypes::eDatabaseType::DB_TYPE_COMBINED_CALLSTACK,
                                                          BTPresTypes::phonebookResultMap(), // Not needed (for now)
                                                          BTPresTypes::filterMap(), // Not needed (for now)
                                                          BTPresTypes::requiredFieldMap(), // Not needed (for now)
                                                          false, // reset Previous
                                                          true, // AutoUpdateEnabled
                                                          false, // AlphaJumpTable
                                                          internalCallback_CallStack, //callback
                                                          &objCallInfoData //call info data with default timeout value
                                                          );
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
    }
}

void CPhonePIMDBResourceImpl::tryRequestQueryForContact()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: m_iSessionID: %d, m_bIsContactDataReady: %d, contactListSyncState: %d",
             __FUNCTION__, m_iSessionID, m_bIsContactDataReady, static_cast<int>(getContactListSyncState()));
    if ((0 < m_iSessionID) && (m_bIsContactDataReady))
    {
        if ((EDataReadStateType::DATA_READ_READY == getContactListSyncState()) || (EDataReadStateType::DATA_READ_FAIL == getContactListSyncState()))
        {
            if(getPimDbServiceAvailableStatus())
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"[KPI_MARKER][HMI][ Contact sync start -> state is DATA_READING]");
                changeContactListSyncState(EDataReadStateType::DATA_READING);

                auto internalCallback_PhoneBook = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryAsyncReqCb,
                                                            this,
                                                            _1,
                                                            _2,
                                                            _3,
                                                            _4,
                                                            _5,
                                                            _6,
                                                            BTPresTypes::eDatabaseType::DB_TYPE_PHONEBOOK
                                                            );

                CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);
                m_PimDbHandlerProxy->setSessionQueryAsync(m_iSessionID,
                                                          BTPresTypes::eDatabaseType::DB_TYPE_PHONEBOOK,
                                                          BTPresTypes::phonebookResultMap(), // Not needed (for now)
                                                          BTPresTypes::filterMap(), // Not needed (for now)
                                                          BTPresTypes::requiredFieldMap(), // Not needed (for now)
                                                          false, // reset Previous
                                                          true, // AutoUpdateEnabled
                                                          false, // AlphaJumpTable
                                                          internalCallback_PhoneBook, //callback
                                                          &objCallInfoData //call info data with default timeout value
                                                          );
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
    }
}

void CPhonePIMDBResourceImpl::tryRequestQueryForFavorite()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: m_iSessionID: %d, m_bIsFavouriteDataReady: %d, favouriteListSyncState: %d",
             __FUNCTION__, m_iSessionID, m_bIsFavouriteDataReady, static_cast<int>(getFavouriteListSyncState()));
    if ((0 < m_iSessionID) && (m_bIsFavouriteDataReady))
    {
        if ((EDataReadStateType::DATA_READ_READY == getFavouriteListSyncState()) || (EDataReadStateType::DATA_READ_FAIL == getFavouriteListSyncState()))
        {
            if(getPimDbServiceAvailableStatus())
            {
                changeFavouriteListSyncState(EDataReadStateType::DATA_READING);

                auto internalCallback_Fav = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryAsyncReqCb,
                                                      this,
                                                      _1,
                                                      _2,
                                                      _3,
                                                      _4,
                                                      _5,
                                                      _6,
                                                      BTPresTypes::eDatabaseType::DB_TYPE_FAVOURITE
                                                      );

                CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);
                m_PimDbHandlerProxy->setSessionQueryAsync(m_iSessionID,
                                                          BTPresTypes::eDatabaseType::DB_TYPE_FAVOURITE,
                                                          BTPresTypes::phonebookResultMap(), // Not needed (for now)
                                                          BTPresTypes::filterMap(), // Not needed (for now)
                                                          BTPresTypes::requiredFieldMap(), // Not needed (for now)
                                                          false, // reset Previous
                                                          true, // AutoUpdateEnabled
                                                          false, // AlphaJumpTable
                                                          internalCallback_Fav, //callback
                                                          &objCallInfoData //call info data with default timeout value
                                                          );
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
    }
}

void CPhonePIMDBResourceImpl::tryRequestQueryForFrequentlyDialed()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: m_iSessionID: %d, m_bIsFrequentlyDialedDataReady: %d, frequentlydialedListSyncState: %d",
             __FUNCTION__, m_iSessionID, m_bIsFrequentlyDialedDataReady, static_cast<int>(getFrequentlyDialedListSyncState()));
    if ((0 < m_iSessionID) && (m_bIsFrequentlyDialedDataReady))
    {
        if (EDataReadStateType::DATA_READ_READY == getFrequentlyDialedListSyncState())
        {
            if(getPimDbServiceAvailableStatus())
            {
                changeFrequentlyDialedListSyncState(EDataReadStateType::DATA_READING);

                auto internalCallback_Fav = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryAsyncReqCb,
                                                      this,
                                                      _1,
                                                      _2,
                                                      _3,
                                                      _4,
                                                      _5,
                                                      _6,
                                                      BTPresTypes::eDatabaseType::DB_TYPE_FREQUENT_DIALLED_CALLSTACK
                                                      );

                CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);

                m_PimDbHandlerProxy->setSessionQueryAsync(m_iSessionID,
                                                          BTPresTypes::eDatabaseType::DB_TYPE_FREQUENT_DIALLED_CALLSTACK,
                                                          BTPresTypes::phonebookResultMap(), // Not needed (for now)
                                                          BTPresTypes::filterMap(), // Not needed (for now)
                                                          BTPresTypes::requiredFieldMap(), // Not needed (for now)
                                                          false, // reset Previous
                                                          true, // AutoUpdateEnabled
                                                          false, // AlphaJumpTable
                                                          internalCallback_Fav, //callback
                                                          &objCallInfoData //call info data with default timeout value
                                                          );
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        //do nothing
    }
}

void CPhonePIMDBResourceImpl::tryRequestQueryForSMS()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if ((0 < m_iSessionID) && (m_bIsSmsDataReady))
    {
        if ((EDataReadStateType::DATA_READ_READY == getSmsListSyncState()) || (EDataReadStateType::DATA_READ_FAIL == getSmsListSyncState()))
        {
            if(getPimDbServiceAvailableStatus())
            {
                changeSmsListSyncState(EDataReadStateType::DATA_READING);

                auto internalCallback_Sms = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryAsyncReqCb,
                                                      this,
                                                      _1,
                                                      _2,
                                                      _3,
                                                      _4,
                                                      _5,
                                                      _6,
                                                      BTPresTypes::eDatabaseType::DB_TYPE_SMS
                                                      );

                CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);
                m_PimDbHandlerProxy->setSessionQueryAsync(m_iSessionID,
                                                          BTPresTypes::eDatabaseType::DB_TYPE_SMS,
                                                          BTPresTypes::phonebookResultMap(), // Not needed (for now)
                                                          BTPresTypes::filterMap(), // Not needed (for now)
                                                          BTPresTypes::requiredFieldMap(), // Not needed (for now)
                                                          false, // reset Previous
                                                          true, // AutoUpdateEnabled
                                                          false, // AlphaJumpTable
                                                          internalCallback_Sms, //callback
                                                          &objCallInfoData //call info data with default timeout value
                                                          );
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
    }
}

void CPhonePIMDBResourceImpl::tryRequestQueryForSMSTemplate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if ((0 < m_iSessionID) && (m_bIsSMSTemplateDataReady))
    {
        if ((EDataReadStateType::DATA_READ_READY == getSmsTemplateListSyncState()) || (EDataReadStateType::DATA_READ_FAIL == getSmsTemplateListSyncState()))
        {
            if(getPimDbServiceAvailableStatus())
            {
                changeSmsTemplateListSyncState(EDataReadStateType::DATA_READING);

                auto internalCallback_SmsTemp = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryAsyncReqCb,
                                                          this,
                                                          _1,
                                                          _2,
                                                          _3,
                                                          _4,
                                                          _5,
                                                          _6,
                                                          BTPresTypes::eDatabaseType::DB_TYPE_SMS_TEMPLATE
                                                          );

                CallInfo objCallInfoData(PHONE_API_REQUEST_DEFAULT_TIMEOUT);
                m_PimDbHandlerProxy->setSessionQueryAsync(m_iSessionID,
                                                          BTPresTypes::eDatabaseType::DB_TYPE_SMS_TEMPLATE,
                                                          BTPresTypes::phonebookResultMap(), // Not needed (for now)
                                                          BTPresTypes::filterMap(), // Not needed (for now)
                                                          BTPresTypes::requiredFieldMap(), // Not needed (for now)
                                                          false, // reset Previous
                                                          true, // AutoUpdateEnabled
                                                          false, // AlphaJumpTable
                                                          internalCallback_SmsTemp, //callback
                                                          &objCallInfoData //call info data with default timeout value
                                                          );
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
    }
}

//______________________________________________________________________________________________________
void CPhonePIMDBResourceImpl::getContactNameOrderAttributeChangedCb(BTPresTypes::eContactNameOredr eContactNameOrder)
{
    CPP_UNUSED(eContactNameOrder);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);//TODO:Will be Implemented as per need
}

void CPhonePIMDBResourceImpl::getDeviceListAttributeChangedCb(BTPresTypes::pimPropertiesList vectPimProperties)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    BTPresTypes::pimPropertiesList::iterator it;
    int iCombinedCallStackSyncStatus;
    int iPhonebookSyncStatus;
    int iSmsSyncStatus;
    int iSmsTempSyncStatus;

    for(it = vectPimProperties.begin(); it != vectPimProperties.end(); it++)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s btAddress:%s", __FUNCTION__, m_strDeviceBtAddr.c_str());

        if(("" != m_strDeviceBtAddr) && (it->getBtAddress() == m_strDeviceBtAddr))
        {
            BTPresTypes::dBSyncStateMap mapDevSyncState;
            mapDevSyncState = it->getDbSyncState();
            /////////////////////////////////////////////////////////////////////////////////////////////
            auto eCombinedCallStackSyncStatus = mapDevSyncState.find(BTPresTypes::eDatabaseType::DB_TYPE_COMBINED_CALLSTACK);
            if (mapDevSyncState.count(BTPresTypes::eDatabaseType::DB_TYPE_COMBINED_CALLSTACK) > 0)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s DB_TYPE_COMBINED_CALLSTACK data available", __FUNCTION__);
                iCombinedCallStackSyncStatus = eCombinedCallStackSyncStatus->second;

                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s PimDB CallStack read state %d", __FUNCTION__, iCombinedCallStackSyncStatus);
                switch(iCombinedCallStackSyncStatus)
                {
                //Not needed to check these as hmi is not taking any actions on it, hence default case shall be executed
//                case BTPresTypes::eSyncState::SYNC_STATUS_DEFAULT:
//                case BTPresTypes::eSyncState::SYNC_STATUS_START:
//                case BTPresTypes::eSyncState::SYNC_STATUS_INPROGRESS:
//                case BTPresTypes::eSyncState::SYNC_STATUS_PARTIALLY_COMPLETED:
//                case BTPresTypes::eSyncState::SYNC_STATUS_DELTA_SYNC:
//                {
//                    //No work to do here
//                }
//                    break;
                case BTPresTypes::eSyncState::SYNC_STATUS_COMPLETED:
                {
                    m_bIsCallDataReady = true;
                    tryRequestQueryForCallLog();
                    if(m_bIsContactDataReady && !m_bIsFrequentlyDialedDataReady)
                    {
                        m_bIsFrequentlyDialedDataReady = true;
                        tryRequestQueryForFrequentlyDialed();
                    }
                    else
                    {
                        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Phonebook sync not completed or m_bIsFrequentlyDialedDataReady is ready: m_bIsContactDataReady: %d, m_bIsFrequentlyDialedDataReady: %d", __FUNCTION__, m_bIsContactDataReady, m_bIsFrequentlyDialedDataReady);
                    }
                }
                    break;
                case BTPresTypes::eSyncState::SYNC_STATUS_ABORTED:
                case BTPresTypes::eSyncState::SYNC_STATUS_ERROR:
                case BTPresTypes::eSyncState::SYNC_STATUS_ACCESS_DENIED:
                {
                    m_bIsCallDataReady = false;
                    changeCallListSyncState(EDataReadStateType::DATA_READ_FAIL);
                    m_bIsFrequentlyDialedDataReady = false;
                    changeFrequentlyDialedListSyncState(EDataReadStateType::DATA_READ_FAIL);
                }
                    break;
                default:
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s Un-handled PimDB CallStack read state %d", __FUNCTION__, iCombinedCallStackSyncStatus);
                }
                    break;
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s DB_TYPE_COMBINED_CALLSTACK data not available", __FUNCTION__);
            }
            /////////////////////////////////////////////////////////////////////////////////////////////
            auto ePhonebookSyncStatus  = mapDevSyncState.find(BTPresTypes::eDatabaseType::DB_TYPE_PHONEBOOK);
            if (mapDevSyncState.count(BTPresTypes::eDatabaseType::DB_TYPE_PHONEBOOK) > 0)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s DB_TYPE_PHONEBOOK data available", __FUNCTION__);
                iPhonebookSyncStatus = ePhonebookSyncStatus->second;

                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s PimDB Phonebook read state %d", __FUNCTION__, iPhonebookSyncStatus);
                switch(iPhonebookSyncStatus)
                {
                //Not needed to check these as hmi is not taking any actions on it, hence default case shall be executed
//                case BTPresTypes::eSyncState::SYNC_STATUS_DEFAULT:
//                case BTPresTypes::eSyncState::SYNC_STATUS_START:
//                case BTPresTypes::eSyncState::SYNC_STATUS_INPROGRESS:
//                case BTPresTypes::eSyncState::SYNC_STATUS_PARTIALLY_COMPLETED:
//                case BTPresTypes::eSyncState::SYNC_STATUS_DELTA_SYNC:
//                {
//                    //No work to do here
//                }
//                    break;
                case BTPresTypes::eSyncState::SYNC_STATUS_COMPLETED:
                {
                    m_bIsContactDataReady = true;
                    tryRequestQueryForContact();
                    m_bIsFavouriteDataReady = true;
                    tryRequestQueryForFavorite();
                    if(m_bIsCallDataReady && !m_bIsFrequentlyDialedDataReady)
                    {
                        m_bIsFrequentlyDialedDataReady = true;
                        tryRequestQueryForFrequentlyDialed();
                    }
                    else
                    {
                        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Calllogs sync not completed or m_bIsFrequentlyDialedDataReady is ready: m_bIsCallDataReady: %d, m_bIsFrequentlyDialedDataReady: %d", __FUNCTION__, m_bIsCallDataReady, m_bIsFrequentlyDialedDataReady);
                    }
                }
                    break;
                case BTPresTypes::eSyncState::SYNC_STATUS_ABORTED:
                case BTPresTypes::eSyncState::SYNC_STATUS_ERROR:
                case BTPresTypes::eSyncState::SYNC_STATUS_ACCESS_DENIED:
                {
                    m_bIsContactDataReady = false;
                    changeContactListSyncState(EDataReadStateType::DATA_READ_FAIL);
                    m_bIsFavouriteDataReady = false;
                    changeFavouriteListSyncState(EDataReadStateType::DATA_READ_FAIL);
                    m_bIsFrequentlyDialedDataReady = false;
                    changeFrequentlyDialedListSyncState(EDataReadStateType::DATA_READ_FAIL);
                }
                    break;
                default:
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s Un-handled PimDB Phonebook read state %d", __FUNCTION__, iPhonebookSyncStatus);
                }
                    break;
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s DB_TYPE_PHONEBOOK data not available", __FUNCTION__);
            }
            /////////////////////////////////////////////////////////////////////////////////////////////
            auto eSmsSyncStatus  = mapDevSyncState.find(BTPresTypes::eDatabaseType::DB_TYPE_SMS);
            if (mapDevSyncState.count(BTPresTypes::eDatabaseType::DB_TYPE_SMS) > 0)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s DB_TYPE_SMS data available", __FUNCTION__);
                iSmsSyncStatus = eSmsSyncStatus->second;

                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s PimDB SMS read state %d", __FUNCTION__, iSmsSyncStatus);
                switch(iSmsSyncStatus)
                {
                //Not needed to check these as hmi is not taking any actions on it, hence default case shall be executed
//                case BTPresTypes::eSyncState::SYNC_STATUS_DEFAULT:
//                case BTPresTypes::eSyncState::SYNC_STATUS_START:
//                case BTPresTypes::eSyncState::SYNC_STATUS_INPROGRESS:
//                case BTPresTypes::eSyncState::SYNC_STATUS_PARTIALLY_COMPLETED:
//                case BTPresTypes::eSyncState::SYNC_STATUS_DELTA_SYNC:
//                {
//                    //No work to do here
//                }
//                    break;
                case BTPresTypes::eSyncState::SYNC_STATUS_COMPLETED:
                {
                    m_bIsSmsDataReady = true;
                    tryRequestQueryForSMS();
                }
                    break;
                case BTPresTypes::eSyncState::SYNC_STATUS_ABORTED:
                case BTPresTypes::eSyncState::SYNC_STATUS_ERROR:
                case BTPresTypes::eSyncState::SYNC_STATUS_ACCESS_DENIED:
                {
                    m_bIsSmsDataReady = false;
                    changeSmsListSyncState(EDataReadStateType::DATA_READ_FAIL);
                }
                    break;
                default:
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s Un-handled PimDB SMS read state %d", __FUNCTION__, iSmsSyncStatus);
                }
                    break;
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s DB_TYPE_SMS data not available", __FUNCTION__);
            }
            /////////////////////////////////////////////////////////////////////////////////////////////
            auto eSmsTempSyncStatus  = mapDevSyncState.find(BTPresTypes::eDatabaseType::DB_TYPE_SMS_TEMPLATE);
            if (mapDevSyncState.count(BTPresTypes::eDatabaseType::DB_TYPE_SMS_TEMPLATE) > 0)
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s DB_TYPE_SMS_TEMPLATE data available", __FUNCTION__);
                iSmsTempSyncStatus = eSmsTempSyncStatus->second;

                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s PimDB SMS Template read state %d", __FUNCTION__, iSmsTempSyncStatus);
                switch(iSmsTempSyncStatus)
                {
                //Not needed to check these as hmi is not taking any actions on it, hence default case shall be executed
//                case BTPresTypes::eSyncState::SYNC_STATUS_DEFAULT:
//                case BTPresTypes::eSyncState::SYNC_STATUS_START:
//                case BTPresTypes::eSyncState::SYNC_STATUS_INPROGRESS:
//                case BTPresTypes::eSyncState::SYNC_STATUS_PARTIALLY_COMPLETED:
//                case BTPresTypes::eSyncState::SYNC_STATUS_DELTA_SYNC:
//                {
//                    //No work to do here
//                }
//                    break;
                case BTPresTypes::eSyncState::SYNC_STATUS_COMPLETED:
                {
                    m_bIsSMSTemplateDataReady = true;
                    tryRequestQueryForSMSTemplate();
                }
                    break;
                case BTPresTypes::eSyncState::SYNC_STATUS_ABORTED:
                case BTPresTypes::eSyncState::SYNC_STATUS_ERROR:
                case BTPresTypes::eSyncState::SYNC_STATUS_ACCESS_DENIED:
                {
                    m_bIsSMSTemplateDataReady = false;
                    changeSmsTemplateListSyncState(EDataReadStateType::DATA_READ_FAIL);
                }
                    break;
                default:
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s Un-handled PimDB SMS Template read state %d", __FUNCTION__, iSmsTempSyncStatus);
                }
                    break;
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s DB_TYPE_SMS_TEMPLATE data not available", __FUNCTION__);
            }
            /////////////////////////////////////////////////////////////////////////////////////////////
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s requested BTAddress %s not same as connected BTAddress %s", __FUNCTION__, it->getBtAddress().c_str(), m_strDeviceBtAddr.c_str());
        }
    }
}

void CPhonePIMDBResourceImpl::getEmergencyContactListAttributeChangedCb(BTPresTypes::phonebook vectPhonebook)
{
    CPP_UNUSED(vectPhonebook);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);//TODO:Will be Implemented as per need
}

void CPhonePIMDBResourceImpl::getMessageNotificationEventCb(string strBtAdddress, int64_t lMessageId, BTPresTypes::smsEntry objSmsInfo, BTPresTypes::eMsgNotification eMsgNotification)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, address:%s, messageId:%lld, msgNotification:%d", __FUNCTION__, strBtAdddress.c_str(), lMessageId, static_cast<int>(eMsgNotification));

    if(eMsgNotification == BTPresTypes::eMsgNotification::MSG_NOTIFICATION_NEW_SMS_RECEIVED)
    {
        m_objSmsData.clear();        
        m_objSmsData.m_strName      = objSmsInfo.getSmsName();
        m_objSmsData.m_strNumber 	= objSmsInfo.getSmsFrom();
        m_objSmsData.m_strBody 		= objSmsInfo.getSmsBody();
        m_objSmsData.m_strAddress 	= strBtAdddress;
        m_objSmsData.m_iId 			= lMessageId;

        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, SmsData m_iId:%d, m_strAddress:%s, m_strBody:%s, m_strName:%s, m_strNumber:%s",
                 __FUNCTION__, m_objSmsData.m_iId, m_objSmsData.m_strAddress.c_str(), m_objSmsData.m_strBody.c_str(), m_objSmsData.m_strName.c_str(), m_objSmsData.m_strNumber.c_str());

        if (m_pPhonePIMDBEventProvider)
        {
            m_pPhonePIMDBEventProvider->onMessageNotificationEvent();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
        }
    }
}

void CPhonePIMDBResourceImpl::getNewCallListEventCb(string strBtAdddress, BTPresTypes::callstackEntry objCallLogInfo)
{
    CPP_UNUSED(strBtAdddress);
    CPP_UNUSED(objCallLogInfo);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);//TODO:Will be Implemented as per need
}

void CPhonePIMDBResourceImpl::getSessionClosedSelectiveEventCb(uint8_t ucSessionID, uint8_t ucSessionQueryID, BTPresTypes::eErrorType eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, ucSessionID:%d, ucSessionQueryID:%d, eErrorType:%d", __FUNCTION__, static_cast<int>(ucSessionID), static_cast<int>(ucSessionQueryID), static_cast<int>(eErrorType));
    if(static_cast<int>(ucSessionID) == m_iSessionID)
    {
        closePimDbSession();
        if (m_pPhonePIMDBEventProvider)
        {
            m_pPhonePIMDBEventProvider->onSessionClosedSelectiveEvent();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, ucSessionID:%d, not matching with current SessionID:%d", __FUNCTION__, static_cast<int>(ucSessionID), m_iSessionID);
    }
}

void CPhonePIMDBResourceImpl::getSessionQueryUpdateSelectiveEventCb(uint8_t ucSessionID, uint8_t ucSessionQueryID, uint16_t usCount, uint8_t ucReadCount, BTPresTypes::alphaJumpList vectAlphaJumpTable)
{
    CPP_UNUSED(vectAlphaJumpTable);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s sessionID:%d, sessionQueryID:%d, count:%d, unReadCount:%d", __FUNCTION__, ucSessionID, ucSessionQueryID, usCount, ucReadCount);
    if(ucSessionID == m_iSessionID)
    {
        if(ucSessionQueryID == m_iCallListSessionQueryID)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s Call Log Count updated to %d",__FUNCTION__, usCount);
            m_iCallListCount = usCount;

            if(getPimDbServiceAvailableStatus())
            {
                auto callback = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryWindowAsyncReqCb, this, _1, _2);
                m_PimDbHandlerProxy->setSessionQueryWindowAsync(m_iSessionID, m_iCallListSessionQueryID, 0, m_iCallListCount, callback);
                changeCallListSyncState(EDataReadStateType::DATA_READ_UPDATING);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
        else if(ucSessionQueryID == m_iFrequentDialedListSessionQueryID)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s Frequently Dialed Count updated to %d",__FUNCTION__, usCount);
            m_iFrequentDialedListCount = usCount;

            if(getPimDbServiceAvailableStatus())
            {
                auto callback = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryWindowAsyncReqCb, this, _1, _2);
                m_PimDbHandlerProxy->setSessionQueryWindowAsync(m_iSessionID, m_iFrequentDialedListSessionQueryID, 0, m_iFrequentDialedListCount, callback);
                changeFrequentlyDialedListSyncState(EDataReadStateType::DATA_READ_UPDATING);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
        else if(ucSessionQueryID == m_iContactListSessionQueryID)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s contact Count updated to %d",__FUNCTION__, usCount);
            m_iContactListCount = usCount;
            if(getPimDbServiceAvailableStatus())
            {
                int iWindowSize = 200;
                if (iWindowSize > m_iContactListCount)
                {
                    iWindowSize = m_iContactListCount;
                }
                auto callback = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryWindowAsyncReqCb, this, _1, _2);
                m_PimDbHandlerProxy->setSessionQueryWindowAsync(m_iSessionID, m_iContactListSessionQueryID, 0, iWindowSize, callback);
                changeContactListSyncState(EDataReadStateType::DATA_READ_UPDATING);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
        else if(ucSessionQueryID == m_iFavouriteListSessionQueryID)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s favorite contact Count updated to %d",__FUNCTION__, usCount);
            m_iFavouriteListCount = usCount;
            if(getPimDbServiceAvailableStatus())
            {
                auto callback = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryWindowAsyncReqCb, this, _1, _2);
                m_PimDbHandlerProxy->setSessionQueryWindowAsync(m_iSessionID, m_iFavouriteListSessionQueryID, 0, m_iFavouriteListCount, callback);
                changeFavouriteListSyncState(EDataReadStateType::DATA_READ_UPDATING);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
        else if(ucSessionQueryID == m_iSmsListSessionQueryID)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s SMS Count updated to %d",__FUNCTION__, usCount);
            m_iSmsListCount = usCount;
            if(getPimDbServiceAvailableStatus())
            {
                auto callback = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryWindowAsyncReqCb, this, _1, _2);
                m_PimDbHandlerProxy->setSessionQueryWindowAsync(m_iSessionID, m_iSmsListSessionQueryID, 0, m_iSmsListCount, callback);
                changeSmsListSyncState(EDataReadStateType::DATA_READ_UPDATING);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s [INVALID SESSION QUERY] with sessionQueryID:%d",__FUNCTION__, ucSessionQueryID);
        }
    }
}

void CPhonePIMDBResourceImpl::getSessionQueryWindowUpdateSelectiveEventCb(uint8_t ucSessionID, uint8_t ucSessionQueryID, uint16_t usStartIndex, uint8_t ucNumItems, BTPresTypes::phonebook vectPhoneBookEntry)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s sessionID:%d sessionQueryID:%d startIndex:%d numItems:%d phonebook.size = %d", __FUNCTION__, (int)ucSessionID, (int)ucSessionQueryID, (int)usStartIndex, (int)ucNumItems, (int)vectPhoneBookEntry.size());
    if(ucSessionID == m_iSessionID)
    {
        if (ucSessionQueryID == m_iCallListSessionQueryID)
        {
            m_vectCallListData.clear();
            for(auto iter = vectPhoneBookEntry.begin(); iter != vectPhoneBookEntry.end(); ++iter)
            {
                BTPresTypes::phonebookEntry BTPresPBEntry = *iter;

                SCallLogData objData;

                objData.m_iCallLogIndex    = BTPresPBEntry.getIndex();
                objData.m_iCallType        = BTPresPBEntry.getDatabaseType();
                objData.m_strContactName   = getContactNamesForCallList(BTPresPBEntry);
                objData.m_strContactNumber = getPhoneNumbersForCallList(BTPresPBEntry);
                objData.m_strCallStamp     = getFormatedDateAndTime(BTPresPBEntry);

                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, CallLog, CallLogIndex:%d, CallType:%d, ContactName:%s, ContactNumber:%s, CallStamp:%s", __FUNCTION__,
                         objData.m_iCallLogIndex,
                         objData.m_iCallType,
                         objData.m_strContactName.c_str(),
                         objData.m_strContactNumber.c_str(),
                         objData.m_strCallStamp.c_str());

                m_vectCallListData.push_back(objData);
            }
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s call logs count:%d", __FUNCTION__, static_cast<int>(m_vectCallListData.size()));

            changeCallListSyncState(EDataReadStateType::DATA_READ_DONE);
            if (m_pPhonePIMDBEventProvider)
            {
                m_pPhonePIMDBEventProvider->onCallLogUpdated();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
        else if (ucSessionQueryID == m_iFrequentDialedListSessionQueryID)
        {
            m_vectFrequentlyDialedListData.clear();
            for(auto iter = vectPhoneBookEntry.begin(); iter != vectPhoneBookEntry.end(); ++iter)
            {
                BTPresTypes::phonebookEntry BTPresPBEntry = *iter;

                SFrequentlyDialledData objData;

                objData.m_iDialledNumIndex  = BTPresPBEntry.getIndex();
                objData.m_iCallType         = BTPresPBEntry.getDatabaseType();
                objData.m_strContactName    = getContactNamesForCallList(BTPresPBEntry);
                objData.m_strContactNumber  = getPhoneNumbersForCallList(BTPresPBEntry);
                objData.m_strCallStamp      = getFormatedDateAndTime(BTPresPBEntry);

                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, FrequentlyDialedList: DialledNumIndex:%d, CallType:%d, ContactName:%s, ContactNumber:%s, CallStamp:%s", __FUNCTION__,
                         objData.m_iDialledNumIndex,
                         objData.m_iCallType,
                         objData.m_strContactName.c_str(),
                         objData.m_strContactNumber.c_str(),
                         objData.m_strCallStamp.c_str());

                m_vectFrequentlyDialedListData.push_back(objData);
            }
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s frequently dialed list count:%d", __FUNCTION__, static_cast<int>(m_vectFrequentlyDialedListData.size()));

            changeFrequentlyDialedListSyncState(EDataReadStateType::DATA_READ_DONE);
            if (m_pPhonePIMDBEventProvider)
            {
                m_pPhonePIMDBEventProvider->onFrequentlyDialedListUpdated();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
        else if (ucSessionQueryID == m_iContactListSessionQueryID)
        {
            m_vectContactListData.clear();
            for(auto iter = vectPhoneBookEntry.begin(); iter != vectPhoneBookEntry.end(); ++iter)
            {
                BTPresTypes::phonebookEntry BTPresPBEntry = *iter;

                SContactData objData;

                objData.m_iContactIndex     = BTPresPBEntry.getIndex();
                objData.m_iContactID        = BTPresPBEntry.getContactID();
                objData.m_iFavIndex         = BTPresPBEntry.getFavIndex();
                objData.m_strContactName    = getContactNamesForCallList(BTPresPBEntry);
                objData.m_strContactNumber  = getPhoneNumbersForCallList(BTPresPBEntry);
                objData.m_iContactType      = getPhoneNumberTypeForCallList(BTPresPBEntry);

                LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, ContactList, ContactIndex:%d, ContactID:%d, FavIndex:%d, ContactName:%s, ContactNumber:%s, ContactType:%d", __FUNCTION__,
                         objData.m_iContactIndex,
                         objData.m_iContactID,
                         objData.m_iFavIndex,
                         objData.m_strContactName.c_str(),
                         objData.m_strContactNumber.c_str(),
                         objData.m_iContactType);

                m_vectContactListData.push_back(objData);
            }
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s contacts count:%d", __FUNCTION__, static_cast<int>(m_vectContactListData.size()));

            int iDownloadedCount = (ucNumItems + usStartIndex);
            int iRemainingCount = (m_iContactListCount - iDownloadedCount);
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%sContact window status::: Downloaded:%d, Remaining:%d, total:%d", __FUNCTION__, iDownloadedCount, iRemainingCount, m_iContactListCount);

            if (iRemainingCount > 0)
            {
                int iWindowSize = 200;
                if (iWindowSize > iRemainingCount)
                {
                    iWindowSize = iRemainingCount;
                }
                if(getPimDbServiceAvailableStatus())
                {
                    auto callback = std::bind(&CPhonePIMDBResourceImpl::setSessionQueryWindowAsyncReqCb, this, _1, _2);
                    m_PimDbHandlerProxy->setSessionQueryWindowAsync(m_iSessionID, m_iContactListSessionQueryID, iDownloadedCount, iWindowSize, callback);
                    changeContactListSyncState(EDataReadStateType::DATA_READ_UPDATING);
                }
                else
                {
                    LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"[KPI_MARKER][HMI][ Contact sync done -> state - DATA_READ_DONE]");
                changeContactListSyncState(EDataReadStateType::DATA_READ_DONE);
            }

            if (m_pPhonePIMDBEventProvider)
            {
                m_pPhonePIMDBEventProvider->onContactUpdated(usStartIndex);
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
        else if (ucSessionQueryID == m_iFavouriteListSessionQueryID)
        {
            m_vectFavouriteListData.clear();
            for(auto iter = vectPhoneBookEntry.begin(); iter != vectPhoneBookEntry.end(); ++iter)
            {
                BTPresTypes::phonebookEntry BTPresPBEntry = *iter;
                //if (0 < BTPresPBEntry.getFavIndex())
                {
                    SContactData objData;
                    // FixMe: [NK] [PHONE] service issue contact and fav id data values switched
                    objData.m_iContactIndex     = BTPresPBEntry.getIndex();
                    objData.m_iFavIndex         = BTPresPBEntry.getContactID();
                    objData.m_iContactID        = BTPresPBEntry.getFavIndex();
                    objData.m_strContactName    = getContactNamesForCallList(BTPresPBEntry);
                    objData.m_strContactNumber  = getPhoneNumbersForCallList(BTPresPBEntry);
                    objData.m_iContactType      = getPhoneNumberTypeForCallList(BTPresPBEntry);

                    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, FavouriteList, ContactIndex:%d, ContactID:%d, FavIndex:%d, ContactName:%s, ContactNumber:%s, ContactType:%d", __FUNCTION__,
                             objData.m_iContactIndex,
                             objData.m_iContactID,
                             objData.m_iFavIndex,
                             objData.m_strContactName.c_str(),
                             objData.m_strContactNumber.c_str(),
                             objData.m_iContactType);

                    m_vectFavouriteListData.push_back(objData);
                }
            }
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s favourites count:%d", __FUNCTION__, static_cast<int>(m_vectFavouriteListData.size()));

            changeFavouriteListSyncState(EDataReadStateType::DATA_READ_DONE);
            if (m_pPhonePIMDBEventProvider)
            {
                m_pPhonePIMDBEventProvider->onFavoriteUpdated();
            }
            else
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
            }
        }
        else //if (sessionQueryID == m_nSmsListSessionQueryID)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, %d sessionQueryID not handled", __FUNCTION__, ucSessionQueryID);
        }
    }
}

void CPhonePIMDBResourceImpl::getSmsNotificationEventCb(string strSmsData, int64_t lMessageID, BTPresTypes::eMsgNotification eMsgNotification)
{
    CPP_UNUSED(strSmsData);
    CPP_UNUSED(lMessageID);
    CPP_UNUSED(eMsgNotification);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);//TODO:Will be Implemented as per need
}

void CPhonePIMDBResourceImpl::getSmsSupportedFeatureAttributeChangedCb(BTPresTypes::smsSupportedFeatureList vectSmsSupportedFeature)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_vectSmsSupportedFeatureList.clear();

    unsigned int uiSize = static_cast<unsigned int>(vectSmsSupportedFeature.size());
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"hf mode status info list size: %d", uiSize);
    for(unsigned int uiIndex = 0; uiIndex < uiSize; uiIndex++)
    {
        SSmsSupportedFeatureList objSmsModeStatus;
        objSmsModeStatus.m_strBtAddress   = vectSmsSupportedFeature.at(uiIndex).getBtAddress();
        objSmsModeStatus.m_eRemoteDeviceOS  = getRemoteDevOS(vectSmsSupportedFeature.at(uiIndex).getRemoteDeviceOS().value_);
        objSmsModeStatus.m_bSmsSyncSupport = vectSmsSupportedFeature.at(uiIndex).getSyncSupport();
        objSmsModeStatus.m_bReadStatusSupport = vectSmsSupportedFeature.at(uiIndex).getSetReadStatusSupport();
        objSmsModeStatus.m_bSendSupport = vectSmsSupportedFeature.at(uiIndex).getSendSupport();
        m_vectSmsSupportedFeatureList.push_back(objSmsModeStatus);
    }

    if (m_pPhonePIMDBEventProvider)
    {
        m_pPhonePIMDBEventProvider->onGetSmsSupportedFeatureAttributeChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"PimDb event provider NOT Available");
    }
}

void CPhonePIMDBResourceImpl::getUnreadMissedCallEventCb(string strBtAddress, string strPhoneNumber, string strContactName, uint8_t ucUnreadCount)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Bt Address - %s, Phone Number - %s, Contact Name - %s, Unread Count - %d",
             __FUNCTION__, strBtAddress.c_str(), strPhoneNumber.c_str(), strContactName.c_str(), ucUnreadCount);

    m_objUnreadMissedCallData.clear();
    m_objUnreadMissedCallData.m_strBTAddress        = strBtAddress;
    m_objUnreadMissedCallData.m_strContactNumber    = strPhoneNumber;
    m_objUnreadMissedCallData.m_strContactName      = strContactName;
    m_objUnreadMissedCallData.m_uiMissedCallCount   = ucUnreadCount;

    if (m_pPhonePIMDBEventProvider)
    {
        m_pPhonePIMDBEventProvider->onUnreadMissedCallEvent();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"PimDb event provider NOT Available");
    }
}

//______________________________________________________________________________________________________
void CPhonePIMDBResourceImpl::openSessionAsyncReq(string strBtAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(getPimDbServiceAvailableStatus())
    {
        closePimDbSession();

        m_strDeviceBtAddr = strBtAddress;
        m_PimDbHandlerProxy->openSessionAsync(m_strDeviceBtAddr,std::bind(&CPhonePIMDBResourceImpl::openSessionAsyncReqCb, this, _1, _2, _3));

        changeCallListSyncState(EDataReadStateType::DATA_READ_READY);
        changeContactListSyncState(EDataReadStateType::DATA_READ_READY);
        changeFavouriteListSyncState(EDataReadStateType::DATA_READ_READY);
        changeFavouriteListSyncState(EDataReadStateType::DATA_READ_READY);
        changeSmsListSyncState(EDataReadStateType::DATA_READ_READY);
        changeFrequentlyDialedListSyncState(EDataReadStateType::DATA_READ_READY);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::openSessionAsyncReqCb(const CallStatus & eStatus, const uint8_t & ucSessionID, const BTPresTypes::eErrorType & eErrorType)
{
    CPP_UNUSED(eErrorType);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s sessionID %d", __FUNCTION__, ucSessionID);

    if((CommonAPI::CallStatus::SUCCESS == eStatus) && (BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS == eErrorType))
    {
        m_iSessionID = ucSessionID;
        tryRequestQueryForCallLog();
        tryRequestQueryForContact();
        tryRequestQueryForFavorite();
        tryRequestQueryForSMS();
        tryRequestQueryForSMSTemplate();
        tryRequestQueryForFrequentlyDialed();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s open Session Req failed with status %d", __FUNCTION__, static_cast<int>(eStatus));
        m_strDeviceBtAddr = "";
    }
}

void CPhonePIMDBResourceImpl::setSessionQueryAsyncReqCb(const CallStatus &eStatus,
                                                        const BTPresTypes::eErrorType &eErrorType,
                                                        const uint32_t &uiNumResults,
                                                        const uint8_t &ucSessionQueryID,
                                                        const uint8_t &ucUnreadCount,
                                                        const BTPresTypes::alphaJumpList &vectAlphaJumpTable,
                                                        BTPresTypes::eDatabaseType eDatabaseType)
{
    CPP_UNUSED(uiNumResults);
    CPP_UNUSED(ucUnreadCount);
    CPP_UNUSED(vectAlphaJumpTable);

    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s databaseType : %d, status : %d, errorType : %d, sessionQueryID %d", __FUNCTION__, static_cast<int>(eDatabaseType), static_cast<int>(eStatus), static_cast<int>(eErrorType), static_cast<int>(ucSessionQueryID));

    bool bValidResult = false;
    if ((CommonAPI::CallStatus::SUCCESS == eStatus) && (BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS == eErrorType) && (0 < ucSessionQueryID))
    {
        bValidResult = true;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s [INVALID SECTION QUERY] with databaseType : %d, status : %d, errorType : %d, sessionQueryID %d", __FUNCTION__, static_cast<int>(eDatabaseType), static_cast<int>(eStatus), static_cast<int>(eErrorType), static_cast<int>(ucSessionQueryID));
    }

    switch(eDatabaseType)
    {
    case BTPresTypes::eDatabaseType::DB_TYPE_COMBINED_CALLSTACK:
    {
        if(bValidResult)
        {
            m_iCallListSessionQueryID = ucSessionQueryID;
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s m_iCallListSessionQueryID : %d ", __FUNCTION__, m_iCallListSessionQueryID);
        }
        else
        {
            changeCallListSyncState(EDataReadStateType::DATA_READ_FAIL);
        }
    }
        break;
    case BTPresTypes::eDatabaseType::DB_TYPE_FREQUENT_DIALLED_CALLSTACK:
    {
        if(bValidResult)
        {
            m_iFrequentDialedListSessionQueryID = ucSessionQueryID;
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s m_iFrequentDialedListSessionQueryID : %d ", __FUNCTION__, m_iFrequentDialedListSessionQueryID);
        }
        else
        {
            changeFrequentlyDialedListSyncState(EDataReadStateType::DATA_READ_FAIL);
        }
    }
        break;
    case BTPresTypes::eDatabaseType::DB_TYPE_PHONEBOOK:
    {
        if(bValidResult)
        {
            m_iContactListSessionQueryID = ucSessionQueryID;
            m_iContactListCount = uiNumResults;
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s m_iContactListSessionQueryID : %d, m_iContactListCount : %d ", __FUNCTION__, m_iContactListSessionQueryID, m_iContactListCount);
        }
        else
        {
            changeContactListSyncState(EDataReadStateType::DATA_READ_FAIL);
        }
    }
        break;
    case BTPresTypes::eDatabaseType::DB_TYPE_SMS:
    {
        if(bValidResult)
        {
            m_iSmsListSessionQueryID = ucSessionQueryID;
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s m_iSmsListSessionQueryID : %d ", __FUNCTION__, m_iSmsListSessionQueryID);
        }
        else
        {
            changeSmsListSyncState(EDataReadStateType::DATA_READ_FAIL);
        }
    }
        break;
    case BTPresTypes::eDatabaseType::DB_TYPE_FAVOURITE:
    {
        if(bValidResult)
        {
            m_iFavouriteListSessionQueryID = ucSessionQueryID;
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE,"%s m_iFavouriteListSessionQueryID : %d ", __FUNCTION__, m_iFavouriteListSessionQueryID);
        }
        else
        {
            changeFavouriteListSyncState(EDataReadStateType::DATA_READ_FAIL);
        }
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s [INVALID DATABASE TYPE] with databaseType : %d, status : %d sessionQueryID %d", __FUNCTION__, static_cast<int>(eDatabaseType), static_cast<int>(eStatus), static_cast<int>(ucSessionQueryID));
    }
        break;
    }
}

void CPhonePIMDBResourceImpl::closePimDbSession()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_strDeviceBtAddr   = "";
    m_iSessionID        = -1;
    m_iCallListSessionQueryID           = -1;
    m_iContactListSessionQueryID        = -1;
    m_iSmsListSessionQueryID            = -1;
    m_iFavouriteListSessionQueryID      = -1;
    m_iFrequentDialedListSessionQueryID = -1;

    m_bIsCallDataReady              = false;
    m_bIsContactDataReady           = false;
    m_bIsFavouriteDataReady         = false;
    m_bIsSmsDataReady               = false;
    m_bIsSMSTemplateDataReady       = false;
    m_bIsFrequentlyDialedDataReady 	= false;

    m_iCallListCount            = -1;
    m_iContactListCount         = -1;
    m_iFavouriteListCount       = -1;
    m_iSmsListCount             = -1;
    m_iSMSTemplateListCount     = -1;
    m_iFrequentDialedListCount  = -1;

    changeCallListSyncState(EDataReadStateType::DATA_READ_OFF);
    changeContactListSyncState(EDataReadStateType::DATA_READ_OFF);
    changeFavouriteListSyncState(EDataReadStateType::DATA_READ_OFF);
    changeSmsListSyncState(EDataReadStateType::DATA_READ_OFF);
    changeFavouriteListSyncState(EDataReadStateType::DATA_READ_OFF);
    changeContactDetailListSyncState(EDataReadStateType::DATA_READ_OFF);
    changeFrequentlyDialedListSyncState(EDataReadStateType::DATA_READ_OFF);

    m_vectCallListData.clear();
    m_vectContactListData.clear();
    m_vectContactDetailListData.clear();
    m_vectFavouriteListData.clear();
    m_vectSmsListData.clear();
    m_vectSMSTemplateListData.clear();
    m_objSmsData.clear();
    m_vectFrequentlyDialedListData.clear();
}

void CPhonePIMDBResourceImpl::closeSessionAsyncReq()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if(getPimDbServiceAvailableStatus())
    {
        if (m_iSessionID >= 0)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, closing Pimdb SessionID : %d", __FUNCTION__, m_iSessionID);
            m_PimDbHandlerProxy->closeSessionAsync(m_iSessionID, std::bind(&CPhonePIMDBResourceImpl::closeSessionAsyncReqCb,this,_1,_2));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Pimdb session already closed SessionID : %d", __FUNCTION__, m_iSessionID);
        }

        closePimDbSession();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::closeSessionAsyncReqCb(const CallStatus &eStatus, const BTPresTypes::eErrorType &eErrorType)
{
    CPP_UNUSED(eErrorType);
    CPP_UNUSED(eStatus);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}

void CPhonePIMDBResourceImpl::setSessionQueryWindowAsyncReq(const uint8_t &ucSessionID, const uint8_t &ucSessionQueryID, const uint16_t &usStartIndex, const uint8_t &ucNumItems)
{
    CPP_UNUSED(ucSessionID);
    CPP_UNUSED(ucSessionQueryID);
    CPP_UNUSED(usStartIndex);
    CPP_UNUSED(ucNumItems);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);//TODO:Will be Implemented as per need
}

void CPhonePIMDBResourceImpl::setSessionQueryWindowAsyncReqCb(const CallStatus &eStatus, const BTPresTypes::eErrorType &eErrorType)
{
    CPP_UNUSED(eErrorType);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s CallStatus:%d", __FUNCTION__, static_cast<int>(eStatus));
}

void CPhonePIMDBResourceImpl::getContactsByIDAsyncReq(int64_t lDataBaseType, int64_t lContactID)
{
    CPP_UNUSED(lDataBaseType);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    BTPresTypes::phonebookResultMap FieldList;
    if(getPimDbServiceAvailableStatus())
    {
        if("" != m_strDeviceBtAddr)
        {

            changeContactDetailListSyncState(EDataReadStateType::DATA_READING);
            m_PimDbHandlerProxy->getContactsByIDAsync(m_strDeviceBtAddr, BTPresTypes::eDatabaseType::DB_TYPE_PHONEBOOK,lContactID,
                                                      FieldList,std::bind(&CPhonePIMDBResourceImpl::getContactsByIDAsyncReqCb, this, _1, _2,_3));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s BT address is invalid, CALL FAILED", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::getContactsByIDAsyncReqCb(const CallStatus &eStatus, const BTPresTypes::eErrorType &eErrorType, const BTPresTypes::phonebookEntry &objPhonebookData)
{
    CPP_UNUSED(eStatus);
    CPP_UNUSED(eErrorType);
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    string strImageURL = "";
    if(objPhonebookData.getExtendeFeatureList().end() != objPhonebookData.getExtendeFeatureList().find(BTPresTypes::eExtraFeature::IMAGE))
    {
        strImageURL = objPhonebookData.getExtendeFeatureList().at(BTPresTypes::eExtraFeature::IMAGE).c_str();
    }

    if(!m_vectContactDetailListData.empty())
    {
        m_vectContactDetailListData.clear();
    }

    int iContactId = objPhonebookData.getContactID();
    int iFavIndex = objPhonebookData.getFavIndex();
    string strName = getContactNamesForCallList(objPhonebookData);

    if(objPhonebookData.getPhoneNumberList().end() != objPhonebookData.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_CELL))
    {
        BTPresTypes::arString phoneNumberList = objPhonebookData.getPhoneNumberList().at(BTPresTypes::eTelType::CONTACT_TEL_TYPE_CELL);
        for(auto it = phoneNumberList.begin(); it != phoneNumberList.end(); ++it)
        {
            string strNumber = *it;

            SContactData objData;
            objData.m_iContactID        = iContactId;
            objData.m_strContactName    = strName;
            objData.m_strContactNumber  = strNumber;
            objData.m_iContactType      = EContactType::CONTACT_TYPE_MOBILE;
            objData.m_iFavIndex         = iFavIndex;

            m_vectContactDetailListData.push_back(objData);
        }
    }

    if(objPhonebookData.getPhoneNumberList().end() != objPhonebookData.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_HOME))
    {
        BTPresTypes::arString phoneNumberList = objPhonebookData.getPhoneNumberList().at(BTPresTypes::eTelType::CONTACT_TEL_TYPE_HOME);
        for(auto it = phoneNumberList.begin(); it != phoneNumberList.end(); ++it)
        {
            string strNumber = *it;

            SContactData objData;
            objData.m_iContactID        = iContactId;
            objData.m_strContactName    = strName;
            objData.m_strContactNumber  = strNumber;
            objData.m_iContactType      = EContactType::CONTACT_TYPE_HOME;
            objData.m_iFavIndex         = iFavIndex;

            m_vectContactDetailListData.push_back(objData);
        }
    }

    if(objPhonebookData.getPhoneNumberList().end() != objPhonebookData.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_WORK))
    {
        BTPresTypes::arString phoneNumberList = objPhonebookData.getPhoneNumberList().at(BTPresTypes::eTelType::CONTACT_TEL_TYPE_WORK);
        for(auto it = phoneNumberList.begin(); it != phoneNumberList.end(); ++it)
        {
            string strNumber = *it;

            SContactData objData;
            objData.m_iContactID = iContactId;
            objData.m_strContactName = strName;
            objData.m_strContactNumber = strNumber;
            objData.m_iContactType = EContactType::CONTACT_TYPE_WORK;
            objData.m_iFavIndex = iFavIndex;

            m_vectContactDetailListData.push_back(objData);
        }
    }

    if(objPhonebookData.getPhoneNumberList().end() != objPhonebookData.getPhoneNumberList().find(BTPresTypes::eTelType::CONTACT_TEL_TYPE_OTHER))
    {
        BTPresTypes::arString phoneNumberList = objPhonebookData.getPhoneNumberList().at(BTPresTypes::eTelType::CONTACT_TEL_TYPE_OTHER);
        for(auto it = phoneNumberList.begin(); it != phoneNumberList.end(); ++it)
        {
            string strNumber = *it;

            SContactData objData;
            objData.m_iContactID        = iContactId;
            objData.m_strContactName    = strName;
            objData.m_strContactNumber  = strNumber;
            objData.m_iContactType      = EContactType::CONTACT_TYPE_OTHER;
            objData.m_iFavIndex         = iFavIndex;

            m_vectContactDetailListData.push_back(objData);
        }
    }

    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s contacts detail count:%d", __FUNCTION__, static_cast<int>(m_vectContactDetailListData.size()));

    changeContactDetailListSyncState(EDataReadStateType::DATA_READ_DONE);
    if (m_pPhonePIMDBEventProvider)
    {
        m_pPhonePIMDBEventProvider->onContactDetailUpdated();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::addContactToFavouriteListAsyncReq(int64_t lContactID, string strContactNumber, int64_t lContactType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    bool bInvalidData = false;
    if (0 > lContactID)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, Incorrect contactID", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, contactID [%lld]", __FUNCTION__, lContactID);
    }

    if ((strContactNumber.empty()) || ("" == strContactNumber))
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, Incorrect contactNumber", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, contactNumber [%s]", __FUNCTION__, strContactNumber.c_str());
    }

    if (0 > lContactType)
    {
        bInvalidData = true;
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, Incorrect contactType", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, contactType [%lld]", __FUNCTION__, lContactType);
    }

    if ((m_strDeviceBtAddr.empty()) || ("" == m_strDeviceBtAddr))
    {
        bInvalidData = true;
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, Incorrect DeviceBtAddr", __FUNCTION__);
    }

    if (!bInvalidData)
    {
        if (getPimDbServiceAvailableStatus())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Adding with Contact number", __FUNCTION__);
            BTPresTypes::arString vectNumberList;
            vectNumberList.push_back(strContactNumber);

            BTPresTypes::eTelType eContactType;
            switch(lContactType)
            {
            case EContactType::CONTACT_TYPE_MOBILE:
                eContactType = BTPresTypes::eTelType::CONTACT_TEL_TYPE_CELL;
                break;
            case EContactType::CONTACT_TYPE_HOME:
                eContactType = BTPresTypes::eTelType::CONTACT_TEL_TYPE_HOME;
                break;
            case EContactType::CONTACT_TYPE_WORK:
                eContactType = BTPresTypes::eTelType::CONTACT_TEL_TYPE_WORK;
                break;
            case EContactType::CONTACT_TYPE_OTHER:
                eContactType = BTPresTypes::eTelType::CONTACT_TEL_TYPE_OTHER;
                break;
            default:
                eContactType = BTPresTypes::eTelType::CONTACT_TEL_TYPE_OTHER;
                break;
            }

            BTPresTypes::phoneNumberMap mapPhnmber;
            mapPhnmber.insert(std::make_pair(eContactType, vectNumberList));

            BTPresTypes::phonebookEntry objPhEntry;
            objPhEntry.setBtAddress(m_strDeviceBtAddr);
            objPhEntry.setContactID(lContactID);
            objPhEntry.setPhoneNumberList(mapPhnmber);

            BTPresTypes::InsertItems objInsertItems;
            objInsertItems.setContactInfo(objPhEntry);

            m_PimDbHandlerProxy->dbOperationAsync(m_strDeviceBtAddr, BTPresTypes::BTPresTypes::eDatabaseType::DB_TYPE_FAVOURITE, BTPresTypes::eDbOperationId::INSERT_NEW,
                                                  objInsertItems, std::bind(&CPhonePIMDBResourceImpl::addContactToFavouriteListAsyncReqCb, this, _1, _2));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            addContactToFavouriteListAsyncReqCb(CallStatus::SUBSCRIPTION_REFUSED, BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, Failed due to incorrect data", __FUNCTION__);
        addContactToFavouriteListAsyncReqCb(CallStatus::INVALID_VALUE, BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS);
    }
}

void CPhonePIMDBResourceImpl::addContactToFavouriteListAsyncReqCb(const CallStatus &eStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, status:%d, errorType:%d", __FUNCTION__, static_cast<int>(eStatus), static_cast<int>(eErrorType));

    if (m_pPhonePIMDBEventProvider)
    {
        m_pPhonePIMDBEventProvider->onAddContactToFavouriteComplete((CommonAPI::CallStatus::SUCCESS == eStatus) && (BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS == eErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::deleteContactFromFavouriteListAsyncReq(int64_t lFavoriteIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    bool bInvalidData = false;
    if (0 > lFavoriteIndex)
    {
        bInvalidData = true;
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, Incorrect favoriteIndex", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, favoriteIndex [%lld]", __FUNCTION__, lFavoriteIndex);
    }

    if ((m_strDeviceBtAddr.empty()) || ("" == m_strDeviceBtAddr))
    {
        bInvalidData = true;
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, Incorrect DeviceBtAddr", __FUNCTION__);
    }

    if (!bInvalidData)
    {
        if (getPimDbServiceAvailableStatus())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, Deleting with Contact ID", __FUNCTION__);
            std::vector<uint32_t> vectContactIDList;
            std::vector<uint32_t>::iterator it = vectContactIDList.begin();
            vectContactIDList.insert(it,lFavoriteIndex);
            BTPresTypes::InsertItems objInsertItems;
            objInsertItems.setContactIdList(vectContactIDList);

            m_PimDbHandlerProxy->dbOperationAsync(m_strDeviceBtAddr, BTPresTypes::BTPresTypes::eDatabaseType::DB_TYPE_FAVOURITE, BTPresTypes::eDbOperationId::DELETE_FROM_DB,
                                                  objInsertItems, std::bind(&CPhonePIMDBResourceImpl::deleteContactFromFavouriteListAsyncReqCb, this, _1, _2));
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb Service NOT Available, CALL FAILED", __FUNCTION__);
            deleteContactFromFavouriteListAsyncReqCb(CallStatus::SUBSCRIPTION_REFUSED, BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s, Failed due to incorrect data", __FUNCTION__);
        deleteContactFromFavouriteListAsyncReqCb(CallStatus::INVALID_VALUE, BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS);
    }
}

void CPhonePIMDBResourceImpl::deleteContactFromFavouriteListAsyncReqCb(const CallStatus &eStatus, const BTPresTypes::eErrorType &eErrorType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    if (m_pPhonePIMDBEventProvider)
    {
        m_pPhonePIMDBEventProvider->onRemoveContactFromFavouriteComplete((CommonAPI::CallStatus::SUCCESS == eStatus) && (BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS == eErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}

void CPhonePIMDBResourceImpl::sendSMSAsyncReq(const string& strBtAddr, const string& strNumber, const string& strMsgText)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, strBtAddr:%s, strNumber:%s, strMsgText:%s", __FUNCTION__, strBtAddr.c_str(), strNumber.c_str(), strMsgText.c_str());
    if (getPimDbServiceAvailableStatus())
    {
        m_PimDbHandlerProxy->sendSMSByTemplateIDAsync(strBtAddr, strNumber, 0, strMsgText,
                                                      std::bind(&CPhonePIMDBResourceImpl::sendSMSAsyncReqCb, this, _1, _2,_3));
    }
}

void CPhonePIMDBResourceImpl::sendSMSAsyncReqCb(const CallStatus& eStatus, const BTPresTypes::eErrorType& eErrorType, const std::string& strRecieverNumber)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s, status:%d, errorType:%d, recieverNumber:%s", __FUNCTION__, static_cast<int>(eStatus), static_cast<int>(eErrorType), strRecieverNumber.c_str());

    if (m_pPhonePIMDBEventProvider)
    {
        m_pPhonePIMDBEventProvider->onSendSMSComplete((CommonAPI::CallStatus::SUCCESS == eStatus) && (BTPresTypes::eErrorType::ERROR_TYPE_SUCCESS == eErrorType));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE,"%s PimDb event provider NOT Available, CALL FAILED", __FUNCTION__);
    }
}
//______________________________________________________________________________________________________

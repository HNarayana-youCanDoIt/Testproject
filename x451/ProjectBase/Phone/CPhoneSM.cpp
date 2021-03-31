/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CPhoneSM.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CPhoneSM class
 */

#include "CPhoneApplication.h"
#include "CPhoneSM.h"
#include "CPhoneAdaptor.h"
#include "logging.h"

CPhoneSM::CPhoneSM(CPhoneApplication& objPhoneApp):
    m_objPhoneApp(objPhoneApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}

CPhoneSM::~CPhoneSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}

void CPhoneSM::enterPhone()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}
void CPhoneSM::exitPhone()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}
void CPhoneSM::enterPhoneBrowse()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_objPhoneApp.loadScreen("qrc:/QML/PhoneBrowse/PhoneBrowse.qml");
}
void CPhoneSM::exitPhoneBrowse()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_CALL_LOGS);

    /* Reset the current top index of Contact List */
    CPhoneAdaptor::getInstance()->setContactListCurrentTopIndex(0);
    CFramework::getFramework().clearScreenHistoryStack();
}
void CPhoneSM::enterPhoneCall()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    /*
     * If drawers is opened, then close the drawers.
     */
    CDrawersAdaptor::getInstance()->closeDrawers();
}
void CPhoneSM::exitPhoneCall()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CFramework::getFramework().clearScreenHistoryStack();
}
void CPhoneSM::enterCallLogs()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_CALL_LOGS);
}
void CPhoneSM::exitCallLogs()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}
void CPhoneSM::enterContacts()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_CONTACTS);
}
void CPhoneSM::exitContacts()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}
void CPhoneSM::enterFavorites()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_FAVORITES);
}
void CPhoneSM::exitFavorites()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}
void CPhoneSM::enterNumPad()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_DIALPAD);
}
void CPhoneSM::exitNumPad()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    //Reset the DTMF numberpad status to false when exiting from the state
    CPhoneAdaptor::getInstance()->invChangeDTMFNumberPadStatus(false);
}
void CPhoneSM::enterPhoneCallScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_objPhoneApp.loadScreen("qrc:/QML/PhoneCall/PhoneCallScreen.qml");
}
void CPhoneSM::exitPhoneCallScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}
void CPhoneSM::enterParticipantsScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    m_objPhoneApp.loadScreen("qrc:/QML/PhoneCall/ConferenceParticipantsScreen.qml");
}
void CPhoneSM::exitParticipantsScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}

void CPhoneSM::enterContactDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_CONTACT_DETAILS);
}

void CPhoneSM::exitContactDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    /* Clear the Contact Detail data once this screen is exited */
    CPhoneAdaptor::getInstance()->invResetContactDetailList();
}

void CPhoneSM::enterFrequentlyDialed()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_FREQUENTLY_DIALED);
}

void CPhoneSM::exitFrequentlyDialed()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
}

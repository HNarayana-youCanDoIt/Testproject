/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CW3WSM.cpp
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CW3WSM, a State machine handler for W3W module,
 * CW3WSM inherits SCI_W3W_OCB to handle state-machine events.
 */

#include "HMIIncludes.h"

#include "CW3WApplication.h"
#include "CW3WAdaptor.h"
#include "CW3WSM.h"
#include "CW3WEventHandler.h"
#include "CPhoneAdaptor.h"
#include "CMediaAdaptor.h"

CW3WSM::CW3WSM(CW3WApplication& W3WApp):
    mW3WApp(W3WApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_W3w_OCB(this);
}

CW3WSM::~CW3WSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
}

void CW3WSM::enterW3W()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);

    if(CW3WApplication::getW3WAdaptor()->startupWalkthroughStatus())
    {
        CHMIMain::getSM()->getSCI_W3w()->set_bIsW3WStartupNeeded(true);
    }
    else
    {
        CHMIMain::getSM()->getSCI_W3w()->set_bIsW3WStartupNeeded(false);
    }
}

void CW3WSM::exitW3W()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    /* Clear the selected W3W address once W3W app is exited */
    CW3WApplication::getW3WAdaptor()->setSelectedW3WAddressItem(CW3WData::SW3WAddressData());
}

void CW3WSM::enterW3WStartupScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CDrawersAdaptor::getInstance()->setAllowStatusBarOnScreen(false);
    mW3WApp.loadScreen("qrc:/QML/W3W/W3WStartupScreen.qml");
}

void CW3WSM::exitW3WStartupScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CDrawersAdaptor::getInstance()->setAllowStatusBarOnScreen(true);
}

void CW3WSM::enterW3WMainScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    mW3WApp.loadScreen("qrc:/QML/W3W/W3WMainScreen.qml");
}

void CW3WSM::exitW3WMainScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
}

void CW3WSM::enterW3WAddressSuggestionScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CW3WApplication::getW3WAdaptor()->createW3WAutoSuggestionListModel();
    CDrawersAdaptor::getInstance()->setAllowStatusBarOnScreen(false);
    mW3WApp.loadScreen("qrc:/QML/W3W/W3WAddressSuggestionScreen.qml");
}

void CW3WSM::exitW3WAddressSuggestionScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CDrawersAdaptor::getInstance()->setAllowStatusBarOnScreen(true);
    CW3WApplication::getW3WAdaptor()->deleteW3WAutoSuggestionListModel();
    CW3WApplication::getW3WAdaptor()->setAutoSuggestionRecievedStatus(false);
}

void CW3WSM::enterW3WPhoneBrowse()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    mW3WApp.loadScreen("qrc:/QML/W3W/W3WPhoneBrowse.qml");
}

void CW3WSM::exitW3WPhoneBrowse()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_CALL_LOGS);

    /* Reset the current top index of Contact List */
    CPhoneAdaptor::getInstance()->setContactListCurrentTopIndex(0);
}

void CW3WSM::enterContacts()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_CONTACTS);
}

void CW3WSM::exitContacts()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
}

void CW3WSM::enterContactDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CPhoneAdaptor::getInstance()->setCurrentPhoneBrowseScreen(CPhoneEnum::PHONE_BROWSE_TYPE_CONTACT_DETAILS);
}

void CW3WSM::exitContactDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    /* Clear the Contact Detail data once this screen is exited */
    CPhoneAdaptor::getInstance()->invResetContactDetailList();
}

void CW3WSM::enterW3WFavoritesScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    mW3WApp.loadScreen("qrc:/QML/W3W/W3WFavoritesScreen.qml");
}

void CW3WSM::exitW3WFavoritesScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
}

void CW3WSM::enterW3WRecentScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    mW3WApp.loadScreen("qrc:/QML/W3W/W3WRecentScreen.qml");
}

void CW3WSM::exitW3WRecentScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
}

void CW3WSM::enterW3WSetupScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    /* Update the Setup List model before entering into Setup list screen */
    CW3WApplication::getW3WAdaptor()->updateSetupListModel();
    mW3WApp.loadScreen("qrc:/QML/W3W/W3WSetupScreen.qml");
}

void CW3WSM::exitW3WSetupScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
}

void CW3WSM::enterW3WAboutScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CW3WApplication::getW3WAdaptor()->createW3WAboutListModel();
    mW3WApp.loadScreen("qrc:/QML/W3W/W3WAboutScreen.qml");
}

void CW3WSM::exitW3WAboutScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CW3WApplication::getW3WAdaptor()->deleteW3WAboutListModel();
}

void CW3WSM::enterW3WEditLabel()
{
    if(mW3WApp.loadKeypadOverlay("qrc:/QML/W3W/W3WEditLabelKeypad.qml"))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: Keypad overlay loaded", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: Unable to load keypad overlay", __FUNCTION__);
    }
}

void CW3WSM::exitW3WEditLabel()
{
    if(mW3WApp.unloadKeypadOverlay())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: Keypad overlay unloaded", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: Unable to unload keypad overlay", __FUNCTION__);
    }
}

void CW3WSM::enterW3WVideoViewerScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    CDrawersAdaptor::getInstance()->setShowMuteStatus(true);
    mW3WApp.loadScreen("qrc:/QML/W3W/W3WVideoViewerScreen.qml");
    CMediaAdaptor::getInstance().handleVideoSurface(true);
}

void CW3WSM::exitW3WVideoViewerScn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    emit CDrawersAdaptor::getInstance()->sigChangeMuteStatusOnScreenExit();
    CMediaAdaptor::getInstance().handleVideoSurface(false);
}

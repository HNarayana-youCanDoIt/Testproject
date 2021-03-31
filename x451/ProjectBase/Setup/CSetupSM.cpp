/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupSM.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupSM.cpp, setup module state machine cpp file, contains all the state machine callbacks of the module setup.
 */
#include "CSetupSM.h"
#include "CPhoneAdaptor.h"

//TODO: Update state machine to use only one state for both phone setup and bluetooth setup

CSetupSM::CSetupSM(CSetupApplication &setupApp):
    mSetupApp(setupApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    CHMIMain::getSM()->setSCI_Setup_OCB(this);
}

CSetupSM::~CSetupSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::enterSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_MAIN);
    mSetupApp.loadScreen("qrc:/QML/Setup/SetupScreen.qml");
}

void CSetupSM::enterVehicleSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_VEHICLE);
    mSetupApp.loadScreen("qrc:/QML/Setup/VehicleSettings.qml");
}

void CSetupSM::enterAudioSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_AUDIO_PRESETS);
    mSetupApp.loadScreen("qrc:/QML/Setup/AudioSettings.qml");
}

void CSetupSM::enterBluetoothSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.loadScreen("qrc:/QML/PhoneSetup/PhoneSetup.qml");
}

void CSetupSM::enterVolumeSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_VOLUME);
    mSetupApp.loadScreen("qrc:/QML/Setup/VolumeSettingsScreen.qml");
}

void CSetupSM::enterVoiceAlerts()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::enterGeneralSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_GENERAL);
    mSetupApp.loadScreen("qrc:/QML/Setup/GeneralSetupScreen.qml");
}

void CSetupSM::enterSoftwareDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.loadScreen("qrc:/QML/Setup/SoftwareDetails.qml");
}

void CSetupSM::enterDisplaySetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_THEMES);

    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID || CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID)
    {
        // TATA_X104_High_VAVE specific code
        mSetupApp.loadScreen("qrc:/QML/Setup/ThemeSetupWithDriveModeScreen.qml");
    }
    else
    {
        // TATA_X445 specific code, default
        mSetupApp.loadScreen("qrc:/QML/Setup/ThemeSetupScreen.qml");
    }

}

void CSetupSM::enterParkAssist()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_PARK_ASSIST);
    mSetupApp.loadScreen("qrc:/QML/Setup/ParkAssistScreen.qml");
}

void CSetupSM::enterMoodLighting()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_MOOD_LIGHTING);
    mSetupApp.loadScreen("qrc:/QML/Setup/AmbientLightingScreen.qml");
}

void CSetupSM::enterBalanceFader()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    CSetupAdaptor::getInstance()->setCurrentAudioSetupScreen(CSetupEnums::AUDIOSETUP_BALANCE_FADER_SCREEN);
}

void CSetupSM::enterAudioPresets()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_AUDIO_PRESETS);
    CSetupAdaptor::getInstance()->setCurrentAudioSetupScreen(CSetupEnums::AUDIOSETUP_BMT_AUDIO_PRESET_SCREEN);
}

void CSetupSM::enterEditSMSLightbox()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    if(mSetupApp.loadKeypadOverlay("qrc:/QML/Common/Keypad.qml"))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Keypad overlay loaded", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Unable to load keypad overlay", __FUNCTION__);
    }
}

void CSetupSM::enterAUXInGain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::enterSetDate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_SET_DATE);
    mSetupApp.loadScreen("qrc:/QML/Setup/GeneralSetupSetDateAndTime.qml");
}

void CSetupSM::enterSetTime()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::enterPairedDevices()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.loadScreen("qrc:/QML/PhoneSetup/PhonePairedDevices.qml");
}

void CSetupSM::enterPairNewDevice()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.loadScreen("qrc:/QML/PhoneSetup/PhonePairNewDevice.qml");
    if(CPhoneAdaptor::getInstance())
    {
        //Start device search
        CPhoneAdaptor::getInstance()->startDeviceSearch();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS, "Phone adaptor object not created");
    }
}

void CSetupSM::enterDeleteDevice()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::enterLighting()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_LIGHTING);
    mSetupApp.loadScreen("qrc:/QML/Setup/LightingSetupScreen.qml");
}

void CSetupSM::enterAboutMenu()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    mSetupApp.loadScreen("qrc:/QML/Setup/AboutScreen.qml");
}

void CSetupSM::exitSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitVehicleSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitAudioSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitBluetoothSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitVolumeSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitVoiceAlerts()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitGeneralSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitSoftwareDetails()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitDisplaySetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitParkAssist()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitMoodLighting()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitBalanceFader()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitAudioPresets()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitEditSMSLightbox()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    if(mSetupApp.unloadKeypadOverlay())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Keypad overlay unloaded", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Unable to unload keypad overlay", __FUNCTION__);
    }
}

void CSetupSM::exitAUXInGain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitSetDate()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitSetTime()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitPairedDevices()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitPairNewDevice()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitDeleteDevice()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
}

void CSetupSM::exitLighting()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
}

void CSetupSM::exitAboutMenu()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
}

void CSetupSM::exitSetupState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    CFramework::getFramework().clearScreenHistoryStack();
}

void CSetupSM::enterDriveNextSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    CSetupAdaptor::getInstance()->initDriveNextListModel();
    mSetupApp.setCurrentListModel(CSetupEnums::SETUP_SCREEN_DRIVENEXT);
    mSetupApp.loadScreen("qrc:/QML/Setup/DriveNextSetupScreen.qml");
}

void CSetupSM::exitDriveNextSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    CSetupAdaptor::getInstance()->resetDriveNextListModel();
}

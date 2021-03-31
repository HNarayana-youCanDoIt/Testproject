/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupApplication.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupApplication.cpp, setup module application cpp file, contains all the functionality related to setup module
 *          creates instances for CAudioEventHandler & CSetupSM and raises events SM
 */

#include "CSetupApplication.h"
#include "HMIIncludes.h"
#include "logging.h"
#include "Audio/CAudioAdaptor.h"
#include "ParkAssist/CParkAssistAdaptor.h"
#include "Vehicle/CVehicleSettingsAdaptor.h"
#include "Audio/CAudioEventHandler.h"
#include "DateAndTime/CDateAndTimeEventHandler.h"
#include "ParkAssist/CParkAssistEventHandler.h"
#include "Vehicle/CVehicleSettingsEventHandler.h"
#include "CSetupSM.h"

#include "CDriveNextApplication.h"
#include "CDriveNextAdaptor.h"

CSetupApplication::CSetupApplication(QQuickItem* parent)
    :CBaseApplication(parent),
      m_pAudioAdaptor(CAudioAdaptor::getInstance()),
      m_pVehicleAdaptor(CVehicleSettingsAdaptor::getInstance()),
      m_pVehicleEventHandler(new CVehicleSettingsEventHandler),
      m_pDateAndTimeEventHandler(new CDateAndTimeEventHandler()),
      m_pSetupSM(new CSetupSM(*this)),
      m_pSetupAdaptor(CSetupAdaptor::getInstance()),
      CONST_STRING_KEYPAD("Keypad")
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    mfw.setContextProperty("cppSetupApp",this);
    CSetupEnums::registerSetupEnumsToQML();
}

CSetupApplication::~CSetupApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);

    if (m_pDateAndTimeEventHandler)
    {
        delete m_pDateAndTimeEventHandler;
        m_pDateAndTimeEventHandler = NULL;
    }
    if (m_pVehicleEventHandler)
    {
        delete m_pVehicleEventHandler;
        m_pVehicleEventHandler = NULL;
    }
    if (m_pSetupSM)
    {
        delete m_pSetupSM;
        m_pSetupSM = NULL;
    }
}

void CSetupApplication::onCreated(QQuickItem *rootObject)
{
    Q_UNUSED(rootObject);
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
}

void CSetupApplication::loadScreen(QString qmlFilePath)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    CBaseApplication::loadScreen(qmlFilePath);
}

//ToDo: This needs to changed as param should be passed with screenId enum
void CSetupApplication::setCurrentListModel(int screenId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    if(NULL != m_pSetupAdaptor)
    {
        m_pSetupAdaptor->setCurrentListModel(screenId);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "m_pSetupAdaptor is NULL");
    }
}

void CSetupApplication::switchScreenToMainSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS," %s, Switch screen to Main Setup ", __FUNCTION__);
    CHMIMain::getSM()->raise_evSetupActivated();
}

void CSetupApplication::switchScreenToVehicleSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS," %s, Switch screen to vehicle Setup ", __FUNCTION__);
    CHMIMain::getSM()->getSCI_Setup()->raise_evVehicleSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_VEHICLE_NAMED_ENTRY());
}

void CSetupApplication::jumpToPreviousScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);

    CHMIMain::getSM()->raise_evBackPressed();
}

void CSetupApplication::switchScreenToThemeSetup()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS," %s, Switch screen to Theme Setup ", __FUNCTION__);
    /*FixME: Here we need to change the named entry call to direct call */
    CHMIMain::getSM()->getSCI_Setup()->raise_evDisplaySetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_DISPLAY_SETUP_NAMED_ENTRY());
}

void CSetupApplication::raiseSMEvent(const QString & name,const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS," %s, Index received from qml :%d, Screen name :%s", __FUNCTION__, data.toInt(),name.toStdString().c_str());
    if("Back" == data)
    {
        CHMIMain::getSM()->raise_evBackPressed();
        return;
    }

    if("Setup" == name)
    {
        raiseSMEventForMainSetup(static_cast<CSetupEnums::ESetupScreens>(data.toInt()));
    }
    else if("AudioSetup" == name)
    {
        raiseSMEventForAudioSetup(static_cast<CSetupEnums::EAudioSetupPathViewCurrIndex>(data.toInt()));
    }
    else if("GeneralSetup" == name)
    {
        raiseSMEventForGeneralSetup(static_cast<CSetupEnums::EGeneralSetup>(data.toInt()));
    }
    else if("LightingSetup" == name)
    {
        raiseSMEventForLightingSetup(static_cast<CSetupEnums::ESetupScreens>(data.toInt()));
    }
    else if("DriveNextSetup" == name)
    {
        raiseSMEventForDriveNextSetup(static_cast<CSetupEnums::ESetupScreens>(data.toInt()));
    }
    else if("VehicleSetup" == name)
    {
        raiseSMEventForVehicleSetup(static_cast<CSetupEnums::ESetupScreens>(data.toInt()));
    }
    else if(CONST_STRING_KEYPAD == name)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : KeypadIndex: %d", __FUNCTION__, data.toInt());
        CSetupEnums::ESetupScreens eKeypadIndex = static_cast<CSetupEnums::ESetupScreens>(data.toInt());
        if(CSetupEnums::SETUP_SCREEN_KEYBOARD == eKeypadIndex)
        {
            CHMIMain::getSM()->getSCI_Setup()->raise_evKeypadActivated ();
        }
        else
        {
            //Do nothing
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"data received from qml :%s", name.toStdString().c_str());
    }
}

void CSetupApplication::raiseSMEventForMainSetup(CSetupEnums::ESetupScreens setupIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : setupIndex: %d", __FUNCTION__, setupIndex);
    /* Uncomment the cases whenever required */
    switch(setupIndex)
    {
    case CSetupEnums::SETUP_SCREEN_VEHICLE:
        /*Here as it is a special case, we are calling adaptor method to launch vehicle settings where logic
         *to launch vehicle settings will be handled and can call launchVehicleSettings outside setup application also like from
         *home application. */

        CSetupAdaptor::getInstance()->launchVehicleSettings();
        break;

    case CSetupEnums::SETUP_SCREEN_AUDIO:
        CHMIMain::getSM()->getSCI_Setup()->raise_evAudioSetupActivated(SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_AUDIOSETUP);
        break;

        //TODO: Update state machine to use only one state for both phone setup and bluetooth setup
    case CSetupEnums::SETUP_SCREEN_BLUETOOTH:
        CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_BT_NAMED_ENTRY());
        break;
    case CSetupEnums::SETUP_SCREEN_VOLUME:
        CHMIMain::getSM()->getSCI_Setup()->raise_evVolumeSetupActivated(SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_VOLUMESETUP);
        break;

    case CSetupEnums::SETUP_SCREEN_GENERAL:
        CHMIMain::getSM()->getSCI_Setup()->raise_evGeneralSetupActivated(SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_GENERALSETUP);
        break;

    case CSetupEnums::SETUP_SCREEN_SOFTWARE_DETAILS:
        CHMIMain::getSM()->getSCI_Setup()->raise_evSoftwareDetailsActivated(SCVI_STARTUP_REGION_UI_HOME_MAIN_MAIN_SETUP_SETUP_REGION_SOFTWAREDETAILS);
        break;
    case CSetupEnums::SETUP_SCREEN_THEMES:
        /*Here as it is a special case, we are calling adaptor method to launch theme settings where logic
         *to launch theme settings will be handled and can call launchThemeSettings outside setup application also like from
         *home application. */
        CSetupAdaptor::getInstance()->launchThemeSettings();
        break;

    case CSetupEnums::SETUP_SCREEN_ABOUT_MENU:
        CHMIMain::getSM()->getSCI_Setup()->raise_evAboutMenuSetupActivated();
        break;
    case CSetupEnums::SETUP_SCREEN_SOFTWARE_UPDATE:
    {
        CHMIMain::getSM()->raise_evSoftwareUpdateActivatedFromSetup();
        break;
    }
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"raiseSMEventForMainSetup default case :%d", setupIndex);
        break;
    }
}

void CSetupApplication::raiseSMEventForAudioSetup(CSetupEnums::EAudioSetupPathViewCurrIndex eAudioSetupPathViewIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : eAudioSetupPathViewIndex: %d", __FUNCTION__, eAudioSetupPathViewIndex);
    switch(eAudioSetupPathViewIndex)
    {

    case CSetupEnums::AUDIOSETUP_BMT_AUDIO_PRESET_INDEX:
    case CSetupEnums::AUDIOSETUP_BMT_AUDIO_PRESET_INDEX_DUMMY:
        CHMIMain::getSM()->getSCI_Setup()->raise_evAudioSetupActivated(CHMIMain::getSM()->get_sETUP_SCR_AUDIO_PRESETS());
        break;

    case CSetupEnums::AUDIOSETUP_BALANCE_FADER_INDEX:
    case CSetupEnums::AUDIOSETUP_BALANCE_FADER_INDEX_DUMMY:
        CHMIMain::getSM()->getSCI_Setup()->raise_evAudioSetupActivated(CHMIMain::getSM()->get_sETUP_SCR_BALANCE_FADER());
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"raiseSMEventForAudioSetup default case :%d", eAudioSetupPathViewIndex);
        break;
    }
}

void CSetupApplication::raiseSMEventForGeneralSetup(CSetupEnums::EGeneralSetup eGeneralSetupItemIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : eGeneralSetupItemIndex: %d", __FUNCTION__, eGeneralSetupItemIndex);
    switch(eGeneralSetupItemIndex)
    {
    case CSetupEnums::GENERALSETUP_SET_DATE_AND_TIME:
        CHMIMain::getSM()->getSCI_Setup()->raise_evGeneralSetupActivated(CHMIMain::getSM()->get_sETUP_SCR_SET_DATE());
        break;

    case CSetupEnums::GENERALSETUP_RESET_TO_FACTORY_DEFAULT:
        if(CVehicleSettingsAdaptor::getInstance()->speedLockOutStatus())
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_DISABLE);
        }
        else
        {
            CSetupAdaptor::getInstance()->startFactoryResetProcess();
        }
        break;

    case CSetupEnums::GENERALSETUP_ANDROID_AUTO:
        //        [TODO: To be implemented later]
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"raiseSMEventForGeneralSetup default case :%d", eGeneralSetupItemIndex);
        break;
    }
}

void CSetupApplication::raiseSMEventForVehicleSetup(int vehicleSetupIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : vehicleSetupIndex: %d", __FUNCTION__, vehicleSetupIndex);
    switch(vehicleSetupIndex)
    {
    case CSetupEnums::SETUP_SCREEN_PARK_ASSIST:
        CHMIMain::getSM()->getSCI_Setup()->raise_evVehicleSetupActivated(CHMIMain::getSM()->get_sETUP_SCR_PARK_ASSIST());
        break;

    case CSetupEnums::SETUP_SCREEN_LIGHTING:
        CHMIMain::getSM()->getSCI_Setup()->raise_evVehicleSetupActivated(CHMIMain::getSM()->get_sETUP_SCR_LIGHTING_SETUP_NAMED_ENTRY());
        break;

    case CSetupEnums::SETUP_SCREEN_DRIVENEXT:
        CHMIMain::getSM()->getSCI_Setup()->raise_evDriveNextSetupActivated();
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : default case, vehicleSetupIndex: %d", __FUNCTION__, vehicleSetupIndex);
        break;
    }
}

void CSetupApplication::raiseSMEventForLightingSetup(int iLightingSetupIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : LightingSetupIndex: %d", __FUNCTION__, iLightingSetupIndex);
    switch(iLightingSetupIndex)
    {
    case CSetupEnums::SETUP_SCREEN_MOOD_LIGHTING:
        CSetupAdaptor::getInstance()->launchAmbientLightSettings();
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : Invalid case ", __FUNCTION__);
        break;
    }
}

void CSetupApplication::raiseSMEventForDriveNextSetup(int iDriveNextSetupIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : iDriveNextSetupIndex: %d", __FUNCTION__, iDriveNextSetupIndex);
    switch(iDriveNextSetupIndex)
    {
    case CSetupEnums::SETUP_SCREEN_DRIVENEXT_RESET_ALL:
    {
        if (CDriveNextApplication::getDriveNextAdaptor())
        {
            CDriveNextApplication::getDriveNextAdaptor()->tryResetDriveNextTrip(CDriveNextEnum::EDNTripType::DRIVENEXT_ALL_TRIP);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: DriveNextAdaptor not available", __FUNCTION__);
        }
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : Invalid case iDriveNextSetupIndex:%d", __FUNCTION__, iDriveNextSetupIndex);
    }
        break;
    }
}



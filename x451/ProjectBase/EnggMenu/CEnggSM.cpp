/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggSM.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande,Rajat Gupta
 * CEnggSM, a State machine handler for Engineering module,
 * CEnggSM inherits SCI_EnggMenu_OCB to handle statemachine events.
 */

#include "HMIIncludes.h"

#include "CEnggApplication.h"
#include "CEnggAdaptor.h"
#include "CEnggSM.h"
#include "CEnggEventHandler.h"

//________________________________________________________________________________________________
CEnggSM::CEnggSM(CEnggApplication& enggApp):
    m_objEnggApp(enggApp)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CHMIMain::getSM()->setSCI_EnggMenu_OCB(this);
}
CEnggSM::~CEnggSM()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
//////////////////////////////////////////////////////////////////
// StateMachine related functions
//////////////////////////////////////////////////////////////////
void CEnggSM::enterEnggMenu()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
void CEnggSM::exitEnggMenu()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.resetApplication();
#if !defined(TATA_X445)
    CFramework::getFramework().clearScreenHistoryStack();
#endif
}
//________________________________________________________________________________________________
void CEnggSM::enterTestMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_TEST_MODE);
}
void CEnggSM::exitTestMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterIlluminationMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if ((CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_ILLUMINATION);
    }
    else
    {
        m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION);
    }
}
void CEnggSM::exitIlluminationMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterButtonPanelMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_BUTTON_PANEL);
}
void CEnggSM::exitButtonPanelMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterDebugLogMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DEBUG_LOG);
}
void CEnggSM::exitDebugLogMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterSystemConfigMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG);
}
void CEnggSM::exitSystemConfigMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterDisplayIllumination()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION);
}
void CEnggSM::exitDisplayIllumination()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterButtonPanelIllumination()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION);
}
void CEnggSM::exitButtonPanelIllumination()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterVIN()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_VIN);
}
void CEnggSM::exitVIN()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enter16RPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R);
}
void CEnggSM::exit16RPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterDisplayHWPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_DISPLAY_PART);
}
void CEnggSM::exitDisplayHWPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterButtonPanelPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_BUTTON_PANEL);
}
void CEnggSM::exitButtonPanelPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}

void CEnggSM::enterPictureViewerMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_PICTURE_VIEWER);
}

void CEnggSM::exitPictureViewerMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterSoftwarePartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SOFT_PART);
}
void CEnggSM::exitSoftwarePartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterParameterPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_PARAM_PART);
}
void CEnggSM::exitParameterPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterContainerPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_CONTAINER_PART);
}
void CEnggSM::exitContainerPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterSilverBoxPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SILVERBOX_PART);
}
void CEnggSM::exitSilverBoxPartNo()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterGPSCoordinates()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_VC_NUMBER);
}
void CEnggSM::exitGPSCoordinates()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterEnggMenuMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_MAIN);
}
void CEnggSM::exitEnggMenuMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::enterEnggDriveNextMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT);
}

void CEnggSM::exitEnggDriveNextMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextMainMenu();
}

void CEnggSM::enterEnggDriveNextLibUpdateMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LIB_UPDATE);
}

void CEnggSM::exitEnggDriveNextLibUpdateMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}

void CEnggSM::enterEnggDriveNextConfigUpdateMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_CONFIG_UPDATE);
}

void CEnggSM::exitEnggDriveNextConfigUpdateMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}

void CEnggSM::enterEnggDriveNextDebugMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DEBUG);
}

void CEnggSM::exitEnggDriveNextDebugMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextDbgLevel();
}

void CEnggSM::enterEnggDriveNextLogMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LOG);
}

void CEnggSM::exitEnggDriveNextLogMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextDbgTrip();
}

void CEnggSM::enterEnggDriveNextLoggingMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LOGGING);
}

void CEnggSM::exitEnggDriveNextLoggingMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextDbgLocation();
}

void CEnggSM::enterEnggDriveNextTripMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS);
}

void CEnggSM::exitEnggDriveNextTripMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextDetailList();
}

void CEnggSM::enterEnggDriveNextTripDetailsMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}

void CEnggSM::exitEnggDriveNextTripDetailsMode()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);

    switch (CEnggAdaptor::getInstance()->enggMenuCurrentScreen())
    {
    case CEnggMenuEnum::EEnggMenuScreen::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_EFFICIENCY:
    {
        CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextEfficiency();
    }
        break;
    case CEnggMenuEnum::EEnggMenuScreen::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_BRAKING:
    {
        CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextBraking();
    }
        break;
    case CEnggMenuEnum::EEnggMenuScreen::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_ACCELERATION:
    {
        CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextAcceleration();
    }
        break;
    case CEnggMenuEnum::EEnggMenuScreen::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GEAR_SHIFT:
    {
        CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextGearShift();
    }
        break;
    case CEnggMenuEnum::EEnggMenuScreen::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GENERIC:
    {
        CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextGeneric();
    }
        break;
    case CEnggMenuEnum::EEnggMenuScreen::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_SAFETY:
    {
        CEnggAdaptor::getInstance()->resetEnggMenuModelDriveNextSafety();
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s enggMenuCurrentScreen type not handled :%d", __FUNCTION__, static_cast<int>(CEnggAdaptor::getInstance()->enggMenuCurrentScreen()));
    }
        break;
    }
}
//________________________________________________________________________________________________
void CEnggSM::enterW3WLastNavigated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_objEnggApp.setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_W3W_LAST_NAVIGATED);
}
void CEnggSM::exitW3WLastNavigated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}
//________________________________________________________________________________________________
void CEnggSM::handleButtonPanelHK()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CEnggAdaptor::getInstance ()->buttonPanelHkHandling ();
}
//________________________________________________________________________________________________

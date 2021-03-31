/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggApplication.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande,Rajat Gupta
 * CEnggApplication, an application for Engineering module,
 * CEnggApplication act as mediator between QML and Statemachine.
 */

#include "HMIIncludes.h"
#include "logging.h"
#include "ResourceFactory.hpp"
#include "CEnggApplication.h"
#include "CEnggAdaptor.h"
#include "CEnggSM.h"
#include "CEnggEventHandler.h"
#include "EnggDef.h"
#include "CDriveNextApplication.h"
#include "CDriveNextAdaptor.h"

///////////////////////////////////////////////////////////////////////////////
// Engg related functions
///////////////////////////////////////////////////////////////////////////////
CEnggApplication::CEnggApplication(QQuickItem* pParent)
    :CBaseApplication(pParent),
      m_pEnggAdaptor(CEnggAdaptor::getInstance()),
      m_pEnggDataEventHandler(new CEnggEventHandler()),
      m_pEnggSM(new CEnggSM(*this)),
      m_eCurrentScreenType(CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_NULL)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    mfw.setContextProperty("cppEnggApplication",this);
    initApplication();
}
//____________________________________________________________________________
CEnggApplication::~CEnggApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (m_pEnggDataEventHandler)
    {
        delete m_pEnggDataEventHandler;
        m_pEnggDataEventHandler = null;
    }
    if (m_pEnggSM)
    {
        delete m_pEnggSM;
        m_pEnggSM = null;
    }
}
//____________________________________________________________________________
void CEnggApplication::initApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    for (int i =0; i < EnggScreenCount; i++ )
    {
        m_aryEnggScreensInfo[i].ScreenIndex = i;
        m_aryEnggScreensInfo[i].ScreenName = EnggScreenNames[i];
        m_aryEnggScreensInfo[i].ScreenType = EnggScreenTypes[i];
    }

    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_MAIN].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggMain;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_TEST_MODE].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggTestMode;

    ////FixMe need to handle DID presence for DriveNext
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNext;

    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LIB_UPDATE].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextLibUpdate;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_CONFIG_UPDATE].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextConfigUpdate;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DEBUG].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextDebug;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LOG].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextLog;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LOGGING].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextLogging;

    ////FixMe need to handle DID presence for DriveNext
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextDetails;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_EFFICIENCY].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextDetails;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_BRAKING].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextDetails;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_ACCELERATION].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextDetails;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GEAR_SHIFT].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextDetails;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GENERIC].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextDetails;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_SAFETY].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDriveNextDetails;

    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_BUTTON_PANEL].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggButtonPanel;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DEBUG_LOG].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggDbgLog;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_ILLUMINATION].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggIllumination;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggIllumButton;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggIllumDisplay;

    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggSysConfig;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_VIN].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggSysConfigVIN;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_VC_NUMBER].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggSysConfigVC;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggSysConfig16R;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_BUTTON_PANEL].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggSysConfig16RBtn;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_CONTAINER_PART].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggSysConfig16RContain;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_DISPLAY_PART].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggSysConfig16RDisplay;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_PARAM_PART].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggSysConfig16RParam;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SILVERBOX_PART].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggSysConfig16RSilver;
    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SOFT_PART].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggSysConfig16RSoftware;

    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_W3W_LAST_NAVIGATED].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggW3WLastNavigated;

    m_aryEnggScreensInfo[CEnggMenuEnum::ENGG_MENU_SCREEN_PICTURE_VIEWER].raiseSMEventForScreen = &CEnggApplication::raiseSMEventScnEnggPictureViewer;
}

void CEnggApplication::resetApplication()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_eCurrentScreenType = CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_NULL;

}

///////////////////////////////////////////////////////////////////////////////
// CBaseApplication related functions
///////////////////////////////////////////////////////////////////////////////
void CEnggApplication::onCreated(QQuickItem *rootObject)
{
    Q_UNUSED(rootObject);
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}

void CEnggApplication::setAppEnggMenuModel(CEnggMenuEnum::EEnggMenuScreen eEnggMenuScreen)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s: eEnggMenuScreen: %d ", __FUNCTION__, eEnggMenuScreen);
    m_pEnggAdaptor->setEnggMenuCurrentScreen(eEnggMenuScreen);
    m_pEnggAdaptor->setAdaptorEnggMenuModel(eEnggMenuScreen);
    loadEnggMenuScreen(eEnggMenuScreen);
}

void CEnggApplication::loadEnggMenuScreen(CEnggMenuEnum::EEnggMenuScreen eEnggMenuCurrentScreenIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if((eEnggMenuCurrentScreenIndex >= 0) && (eEnggMenuCurrentScreenIndex < EnggScreenCount))
    {
        if (m_eCurrentScreenType != m_aryEnggScreensInfo[eEnggMenuCurrentScreenIndex].ScreenType)
        {
            m_eCurrentScreenType = m_aryEnggScreensInfo[eEnggMenuCurrentScreenIndex].ScreenType;

            switch (m_eCurrentScreenType)
            {
            case CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST:
            {
                loadScreen("qrc:/QML/Engg/ScnEnggList.qml");
            }
                break;
            case CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST_5_ROWS:
            {
                loadScreen("qrc:/QML/Engg/ScnEnggList5Rows.qml");
            }
                break;
            case CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PART_NO:
            {
                loadScreen("qrc:/QML/Engg/ScnEnggPartNo.qml");
            }
                break;
            case CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_ILLUMINATION_ADJUST:
            {
                loadScreen("qrc:/QML/Engg/ScnEnggIllumination.qml");
            }
                break;
            case CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_BUTTON_PANEL:
            {
                loadScreen("qrc:/QML/Engg/ScnEnggButtonPanel.qml");
            }
                break;
            case CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PICTURE_VIEWER:
            {
                loadScreen("qrc:/QML/Engg/ScnEnggPictureViewer.qml");
            }
                break;
            case CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_DRIVENEXT_LIB_UPDATE:
            {
                loadScreen("qrc:/QML/Engg/ScnDriveNextLibUpdate.qml");
            }
                break;
            case CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_DRIVENEXT_CONFIG_UPDATE:
            {
                loadScreen("qrc:/QML/Engg/ScnDriveNextConfigUpdate.qml");
            }
                break;
            case CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_W3W_LAST_NAVIGATED:
            {
                loadScreen("qrc:/QML/Engg/ScnEnggW3WLastNavigated.qml");
            }
                break;
            default:
                LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! eEnggMenuCurrentScreenIndex %d not found", __FUNCTION__, eEnggMenuCurrentScreenIndex);
                break;
            }

        }
    }
}

//____________________________________________________________________________
void CEnggApplication::raiseSMEvent(const QString & strName, const QVariant & varData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: %s, %s",__FUNCTION__, strName.toStdString().data(), varData.toString().toStdString().data());

    int _index = CEnggAdaptor::getInstance()->enggMenuCurrentScreen();
    int iDataVal = varData.toInt();

    if ((_index >= 0) && (_index < EnggScreenCount))
    {
        ((*this).*(m_aryEnggScreensInfo[_index].raiseSMEventForScreen))(iDataVal);
    }
}

void CEnggApplication::raiseSMEventScnEnggMain(const QVariant & varData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, varData.toString().toStdString().data());

    int iDataVal = varData.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_VIP_DID:
    {
        //Do Nothing!
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_TEST_MODE:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evTestModeActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_ILLUMINATION:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evIlluminationActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_PICTURE_VIEWER:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evPictureViewerActivated ();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DEBUG_LOGS:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evDebugLogActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_SYSTEM_CONFIG:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evSystemConfigActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_BUTTON_PANEL:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evButtonPanelActivated ();
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_ID_W3W_LAST_NAVIGATED:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evW3WLastNavigatedActivated();
    }
        break;

    default:

        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! EnggMode Selection  %d not found", __FUNCTION__, iDataVal);
        break;
    }
}

void CEnggApplication::raiseSMEventScnEnggTestMode(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication::raiseSMEventScnEnggDriveNext(const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());

    int iDataVal = data.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LIB_UPDATE:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextLibUpdateActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_CONFIG_UPDATE:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextConfigUpdateActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextDebugActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextLogActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOGGING:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextLoggingActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_EXPORT_LOG:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Exporting DriveNext Debug Logs", __FUNCTION__);
        if (CDriveNextApplication::getDriveNextAdaptor())
        {
            CDriveNextApplication::getDriveNextAdaptor()->exportLogs();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: DriveNextAdaptor not available", __FUNCTION__);
        }
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_TRIP:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextTripActivated();
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! EnggMode Selection %d not found", __FUNCTION__, iDataVal);
    }
        break;
    }
}

void CEnggApplication::raiseSMEventScnEnggDriveNextLibUpdate(const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
    int iDataVal = data.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LIB_UPDATE:
    {
        CDriveNextApplication::getDriveNextAdaptor()->updateLibFile();
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! %d not handled", __FUNCTION__, iDataVal);
    }
        break;
    }
}

void CEnggApplication::raiseSMEventScnEnggDriveNextConfigUpdate(const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
    int iDataVal = data.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_CONFIG_UPDATE:
    {
        CDriveNextApplication::getDriveNextAdaptor()->updateConfigFile();
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! %d not handled", __FUNCTION__, iDataVal);
    }
        break;
    }
}

void CEnggApplication::raiseSMEventScnEnggDriveNextDebug(const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());

    int iDataVal = data.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_0:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log level change
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_1:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log level change
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_2:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log level change
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_3:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log level change
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! EnggMode Selection %d not found", __FUNCTION__, iDataVal);
    }
        break;
    }
}

void CEnggApplication::raiseSMEventScnEnggDriveNextLog(const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());

    int iDataVal = data.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_OVERALL:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log trip selection
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_CURRENT:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log trip selection
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_A:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log trip selection
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_B:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log trip selection
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_ALL:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log trip selection
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! EnggMode Selection %d not found", __FUNCTION__, iDataVal);
    }
        break;
    }
}

void CEnggApplication::raiseSMEventScnEnggDriveNextLogging(const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());

    int iDataVal = data.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_INTERNAL:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log location selection
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_USB:
    {
        // FixMe: [NK] [DriveNext] call flow to update DriveNext Debug Log location selection
    }
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! EnggMode Selection %d not found", __FUNCTION__, iDataVal);
    }
        break;
    }
}

void CEnggApplication::raiseSMEventScnEnggDriveNextDetails(const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());

    int iDataVal = data.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_EFFICIENCY:
    {
        setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_EFFICIENCY);
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextTripDetailsActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_BRAKING:
    {
        setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_BRAKING);
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextTripDetailsActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_ACCELERATION:
    {
        setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_ACCELERATION);
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextTripDetailsActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_GEAR_SHIFT:
    {
        setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GEAR_SHIFT);
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextTripDetailsActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_GENERIC:
    {
        setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GENERIC);
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextTripDetailsActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_SAFETY:
    {
        setAppEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_SAFETY);
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evEnggDriveNextTripDetailsActivated();
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! EnggMode Selection %d not found", __FUNCTION__, iDataVal);
    }
        break;
    }
}

void CEnggApplication::raiseSMEventScnEnggButtonPanel(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}


void CEnggApplication::raiseSMEventScnEnggDbgLog(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication::raiseSMEventScnEnggIllumination(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
    int iDataVal = data.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_BUTTON_PANEL_ILLUMINATION:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evButtonPanelIlluminationActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DISPLAY_ILLUMINATION:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evDisplayIlluminationActivated();
    }
        break;

    default:

        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! EnggMode Illumination  %d not found", __FUNCTION__, iDataVal);
        break;

    }
}

void CEnggApplication::raiseSMEventScnEnggIllumButton(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication::raiseSMEventScnEnggIllumDisplay(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication::raiseSMEventScnEnggSysConfig(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
    int iDataVal = data.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_STEERING_WHEEL_CONTROLS:
    {
        //Non Clickable Items
        break;
    }
    case CEnggMenuEnum::ENGG_MENU_ID_CURRENT_POWER_MODE_TYPES:
    {
        //Non Clickable Items
        break;
    }
    case CEnggMenuEnum::ENGG_MENU_ID_AM_FM_ANTENNA_TYPES:
    {
        //Non Clickable Items
        break;
    }
    case CEnggMenuEnum::ENGG_MENU_ID_MICROPHONE:
    {
        //Non Clickable Items
        break;
    }
    case CEnggMenuEnum::ENGG_MENU_ID_VIN:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evVINActivated();
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_ID_VC_NUMBER:
    {
        //Todo: Name will be renamed in SCT for VC Number.
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evGPSCoordinate();
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_ID_ALL_16R_PART_NUMBERS:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_ev16RPartActivated();
    }
        break;

    default:

        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! Sys Config. Selection  %d not found", __FUNCTION__, iDataVal);
        break;
    }
}

void CEnggApplication::raiseSMEventScnEnggSysConfigVIN(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
    //[FixMe] Do nothing. This function will be removed later.
}

void CEnggApplication::raiseSMEventScnEnggSysConfigVC(const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
    //[FixMe] Do nothing. This function will be removed later.
}

void CEnggApplication::raiseSMEventScnEnggSysConfig16R(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
    int iDataVal = data.toInt();
    switch (iDataVal)
    {
    case CEnggMenuEnum::ENGG_MENU_ID_CONTAINER_PART_NUMBER:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evContainerPartNoActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_SILVERBOX_PART_NUMER:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evSilverBoxPartNoActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DISPLAYHW_PART_NUMBER:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evDisplayHWPartNoActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_BUTTON_PANEL_PART_NUMBER:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evButtonPanelPartNoActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_SOFTWARE_PART_NUMBER:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evSoftwarePartNoActivated();
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_PARAMETERIZATION_PART_NUMBER:
    {
        CHMIMain::getSM()->getSCI_EnggMenu()->raise_evParameterPartNoActivated();
    }
        break;

    default:

        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Error!! 16R Part No. Selection  %d not found", __FUNCTION__, iDataVal);
        break;
    }
}


void CEnggApplication::raiseSMEventScnEnggSysConfig16RBtn(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication::raiseSMEventScnEnggSysConfig16RContain(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication::raiseSMEventScnEnggSysConfig16RDisplay(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication::raiseSMEventScnEnggSysConfig16RParam(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication::raiseSMEventScnEnggSysConfig16RSilver(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication::raiseSMEventScnEnggSysConfig16RSoftware(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication::raiseSMEventScnEnggW3WLastNavigated(const QVariant & data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
}

void CEnggApplication:: raiseSMEventScnEnggPictureViewer(const QVariant &data)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: data: %s", __FUNCTION__, data.toString().toStdString().data());
    CHMIMain::getSM()->getSCI_EnggMenu()->raise_evPictureViewerActivated ();

}

//____________________________________________________________________________

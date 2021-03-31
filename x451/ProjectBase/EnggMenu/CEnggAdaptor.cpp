/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande,Rajat Gupta
 * CEnggAdaptor, an adaptor for Engineering module,
 * CEnggAdaptor is singleton class used to communicate with qml,resources of Engg module.
 */

#include "ResourceFactory.hpp"
#include "HMIIncludes.h"
#include "CEnggApplication.h"
#include "CEnggAdaptor.h"
#include "CEnggSM.h"
#include "CEnggEventHandler.h"
#include "CPersistencyAdaptor.h"
#include "CVersionManagerEnums.h"
#include "CVariantControlEnum.h"
#include "CDriveNextApplication.h"
#include "CDriveNextAdaptor.h"
#include "CW3WApplication.h"
#include "CW3WAdaptor.h"

CEnggAdaptor* CEnggAdaptor::m_pEnggAdaptor = nullptr;

///////////////////////////////////////////////////////////////////////////////
// Adaptor related functions
///////////////////////////////////////////////////////////////////////////////
CEnggAdaptor* CEnggAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr == m_pEnggAdaptor)
    {
        m_pEnggAdaptor = new CEnggAdaptor();
    }
    return m_pEnggAdaptor;
}
//____________________________________________________________________________
CEnggAdaptor::CEnggAdaptor(QObject *pParent) : QObject(pParent),
    m_iActiveSource(0),m_iCurrentTestMode(-1),m_bIsEnggMenuProxyAvailable(false),
    m_pEnggMenuResource(ResourceFactory::getEnggMenuResource())
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelEnggMain           = new CEnggMenuListModel(this);
    m_pEnggModelDebugLog           = new CEnggMenuListModel(this);
    m_pEnggModelIllumination       = new CEnggMenuListModel(this);
    m_pEnggModelSysConfig          = new CEnggMenuListModel(this);
    m_pEnggModelTestModeAudioMedia = new CEnggMenuListModel(this);
    m_pEnggModelTestModeVideoMedia = new CEnggMenuListModel(this);
    m_pEnggModelSysConfig16RPart   = new CEnggMenuListModel(this);
    m_pEnggModelTestModeTuner      = new CEnggMenuListModel(this);

    m_pEnggModelDriveNext           = new CEnggMenuListModel(this);
    m_pEnggModelDriveNextDebug      = new CEnggMenuListModel(this);
    m_pEnggModelDriveNextLog        = new CEnggMenuListModel(this);
    m_pEnggModelDriveNextLogging    = new CEnggMenuListModel(this);
    m_pEnggModelDriveNextDetails    = new CEnggMenuListModel(this);
    m_pEnggModelDriveNextDetailsEfficiency      = new CEnggMenuListModel(this);
    m_pEnggModelDriveNextDetailsBraking         = new CEnggMenuListModel(this);
    m_pEnggModelDriveNextDetailsAcceleration    = new CEnggMenuListModel(this);
    m_pEnggModelDriveNextDetailsGearShift       = new CEnggMenuListModel(this);
    m_pEnggModelDriveNextDetailsGeneric         = new CEnggMenuListModel(this);
    m_pEnggModelDriveNextDetailsSafety          = new CEnggMenuListModel(this);

    CFramework::getFramework().setContextProperty("cppEnggAdaptor",this);
    CEnggMenuEnum::registerEnggMenuEnumsToQML();
    CVersionManagerAdaptor::getInstance();
    initEnggMenuListModels();
    setEnggMenuCurrentListModel(m_pEnggModelEnggMain);
    setEnggMenuCurrentScreen(CEnggMenuEnum::ENGG_MENU_SCREEN_MAIN);
    setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_TITLE"));
    connectSignals();
    updateSysConfigAntennaType();
}

void CEnggAdaptor::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    connect(CAudioAdaptor::getInstance(),SIGNAL(sigUSBSrcStatuschanged()),this,SLOT(sltUpdateDriveNextElements()),Qt::QueuedConnection);
    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigExportingLogsChanged()),this,SLOT(sltUpdateDriveNextElements()),Qt::QueuedConnection);
    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigUpdatingLoggingLocationChanged()),this,SLOT(sltUpdateDriveNextElements()),Qt::QueuedConnection);
    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigDriveNextPresenceChanged()),this,SLOT(sltDriveNextPresenceChanged()),Qt::QueuedConnection);

    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigLogTripTypeChanged()),this,SLOT(sltUpdateLoggingTripList()),Qt::QueuedConnection);
    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigUpdatingLogTripTypeChanged()),this,SLOT(sltUpdateLoggingTripList()),Qt::QueuedConnection);
    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigLogLevelChanged()),this,SLOT(sltUpdateLoggingLevelList()),Qt::QueuedConnection);
    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigUpdatingLogLevelChanged()),this,SLOT(sltUpdateLoggingLevelList()),Qt::QueuedConnection);
    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigLoggingLocationChanged()),this,SLOT(sltUpdateLoggingLocationList()),Qt::QueuedConnection);
    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigUpdatingLoggingLocationChanged()),this,SLOT(sltUpdateLoggingLocationList()),Qt::QueuedConnection);

    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveEntSrcChanged()), this, SLOT(sltActiveEntSrcChanged()),Qt::QueuedConnection);
    connect(CTunerAdaptor::getInstance(), SIGNAL(sigFrequencyChanged()), this, SLOT(sltFrequencyChanged()),Qt::QueuedConnection);
    connect(CTunerAdaptor::getInstance(), SIGNAL(sigStationNameChanged()), this, SLOT(sltStationNameChanged()),Qt::QueuedConnection);
    connect(CTunerAdaptor::getInstance(), SIGNAL(sigFieldStrengthChanged()), this, SLOT(sltFieldStrengthChanged()),Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActEntSourceVolumeChanged()), this, SLOT(sltActEntSourceVolumeChanged()),Qt::QueuedConnection);
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigSongTitleChanged()), this, SLOT(sltSongTitleChanged()),Qt::QueuedConnection);
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigBitRateChanged()), this, SLOT(sltBitRateChanged()),Qt::QueuedConnection);
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigSamplingRateChanged()), this, SLOT(sltSamplingRateChanged()),Qt::QueuedConnection);
    connect(CVersionManagerAdaptor::getInstance(), SIGNAL(sigPowerModeChanged()), this, SLOT(sltPowerModeChanged()),Qt::QueuedConnection);
    connect(CTunerAdaptor::getInstance(), SIGNAL(sigMultipathChanged()), this, SLOT(sltMultipathChanged()),Qt::QueuedConnection);
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigNowPlayingMetadataChanged()), this, SLOT(sltNowPlayingMetadataChanged()),Qt::QueuedConnection);
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigVideoCodecChanged()), this, SLOT(sltVideoCodecChanged()));
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigVideoFrameRateChanged()), this, SLOT(sltVideoFrameRateChanged()));
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigMediaFormatChanged()), this, SLOT(sltMediaFormatChanged()),Qt::QueuedConnection);
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigVideoResolutionChanged()), this, SLOT(sltVideoResolutionChanged()));
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigAudioSamplingRateChanged()), this, SLOT(sltAudioSamplingRateChanged()));
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigAudioCodecChanged()), this, SLOT(sltAudioCodecChanged()));
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigVehicleSpeedChanged()), this, SLOT(sltVehicleSpeedChanged()),Qt::QueuedConnection);
    connect(CDiagnosticAdaptor::getInstance(), SIGNAL(sigSWCConnectionStatusChanged()), this, SLOT(sltSWCConnectionStatusChanged()),Qt::QueuedConnection);
    connect(CDiagnosticAdaptor::getInstance(), SIGNAL(sigMICConnectionStatusChanged()), this, SLOT(sltMICConnectionStatusChanged()),Qt::QueuedConnection);
}

void CEnggAdaptor::initEnggMenuListModels()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    initEnggMenuModelEnggMain();
    initEnggMenuModelIllumination();
    initEnggMenuModel16RPart();
    initEnggMenuModelSysConfig();
    initEnggMenuModelTestModeTuner();
    initEnggMenuModelTestModeAudioMedia();
    initEnggMenuModelDebugLogs();
    initEnggMenuModelTestModeVideoMedia();
}

void CEnggAdaptor::initEnggMenuModelEnggMain()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);

    m_pEnggModelEnggMain->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIP_DID, tr("TEXT_ENGG_MENU_VIP_NAME").arg(getInfotainmentPlatformName()), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL, ""));
    m_pEnggModelEnggMain->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_TEST_MODE, tr("TEXT_ENGG_MENU_TESTMODE"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL, "", false, false));

    if (CVariantControlAdaptor::getInstance()->eolDriveNextEnabled())
    {
        m_pEnggModelEnggMain->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT, tr("TEXT_ENGG_MENU_DN_TESTMODE"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL, "", false, true));
    }
    else
    {
        //EOL disabled for DriveNext
    }

    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if ((CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        m_pEnggModelEnggMain->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_ILLUMINATION, tr("TEXT_ENGG_MENU_ILLUMINATION_CAPTION"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL, "", false, true));
    }
    else
    {
        m_pEnggModelEnggMain->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_ILLUMINATION, tr("TEXT_ENGG_MENU_DISPLAY_ILLUMINATION_CAPTION"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL, "", false, true));
    }

    if ((CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        m_pEnggModelEnggMain->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_BUTTON_PANEL, tr("TEXT_ENGG_MENU_BUTTONPANEL_CAPTION"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL, "", false, true));
    }
	
    m_pEnggModelEnggMain->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DEBUG_LOGS, tr("TEXT_ENGG_MENU_DEBUGLOGS_CAPTION"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL, "", false, false));
    m_pEnggModelEnggMain->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_SYSTEM_CONFIG, tr("TEXT_ENGG_MENU_SYSCONFIG_CAPTION"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL, "", false, true));

    if(CW3WApplication::getW3WAdaptor()->w3wFeatureSupportStatus())
    {
        m_pEnggModelEnggMain->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_W3W_LAST_NAVIGATED, tr("TEXT_ENGG_MENU_W3W_LAST_NAVIGATED"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL, "", false, true));
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextEfficiency()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelDriveNextDetailsEfficiency->resetList();
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggEfficiencyList(true);
        for (uint i = 0; i < CDriveNextApplication::getDriveNextAdaptor()->enggDataEfficiencyList().size(); i++)
        {
            m_pEnggModelDriveNextDetailsEfficiency->addItem(CEnggMenuData(CDriveNextApplication::getDriveNextAdaptor()->enggDataEfficiencyList()[i], "", CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_DRIVE_NEXT_KEY_VALUE));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextEfficiency()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggEfficiencyList(false);
    }
    if (nullptr != m_pEnggModelDriveNextDetailsEfficiency)
    {
        m_pEnggModelDriveNextDetailsEfficiency->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDetailsEfficiency not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextBraking()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelDriveNextDetailsBraking->resetList();
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggBrakingList(true);
        for (uint i = 0; i < CDriveNextApplication::getDriveNextAdaptor()->enggDataBrakingList().size(); i++)
        {
            m_pEnggModelDriveNextDetailsBraking->addItem(CEnggMenuData(CDriveNextApplication::getDriveNextAdaptor()->enggDataBrakingList()[i], "", CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_DRIVE_NEXT_KEY_VALUE));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextBraking()
{
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggBrakingList(false);
    }
    if (nullptr != m_pEnggModelDriveNextDetailsBraking)
    {
        m_pEnggModelDriveNextDetailsBraking->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDetailsBraking not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextAcceleration()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelDriveNextDetailsAcceleration->resetList();
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggAccelerationList(true);
        for (uint i = 0; i < CDriveNextApplication::getDriveNextAdaptor()->enggDataAccelerationList().size(); i++)
        {
            m_pEnggModelDriveNextDetailsAcceleration->addItem(CEnggMenuData(CDriveNextApplication::getDriveNextAdaptor()->enggDataAccelerationList()[i], "", CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_DRIVE_NEXT_KEY_VALUE));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextAcceleration()
{
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggAccelerationList(false);
    }
    if (nullptr != m_pEnggModelDriveNextDetailsAcceleration)
    {
        m_pEnggModelDriveNextDetailsAcceleration->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDetailsAcceleration not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextGearShift()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelDriveNextDetailsGearShift->resetList();
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggGearShiftList(true);
        for (uint i = 0; i < CDriveNextApplication::getDriveNextAdaptor()->enggDataGearShiftList().size(); i++)
        {
            m_pEnggModelDriveNextDetailsGearShift->addItem(CEnggMenuData(CDriveNextApplication::getDriveNextAdaptor()->enggDataGearShiftList()[i], "", CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_DRIVE_NEXT_KEY_VALUE));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextGearShift()
{
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggGearShiftList(false);
    }
    if (nullptr != m_pEnggModelDriveNextDetailsGearShift)
    {
        m_pEnggModelDriveNextDetailsGearShift->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDetailsGearShift not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextGeneric()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelDriveNextDetailsGeneric->resetList();
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggGenericList(true);
        for (uint i = 0; i < CDriveNextApplication::getDriveNextAdaptor()->enggDataGenericList().size(); i++)
        {
            m_pEnggModelDriveNextDetailsGeneric->addItem(CEnggMenuData(CDriveNextApplication::getDriveNextAdaptor()->enggDataGenericList()[i], "", CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_DRIVE_NEXT_KEY_VALUE));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextGeneric()
{
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggGenericList(false);
    }
    if (nullptr != m_pEnggModelDriveNextDetailsGeneric)
    {
        m_pEnggModelDriveNextDetailsGeneric->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDetailsGeneric not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextSafety()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelDriveNextDetailsSafety->resetList();
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggSafetyList(true);
        for (uint i = 0; i < CDriveNextApplication::getDriveNextAdaptor()->enggDataSafetyList().size(); i++)
        {
            m_pEnggModelDriveNextDetailsSafety->addItem(CEnggMenuData(CDriveNextApplication::getDriveNextAdaptor()->enggDataSafetyList()[i], "", CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_DRIVE_NEXT_KEY_VALUE));
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s DriveNextAdaptor not available", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextSafety()
{
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextApplication::getDriveNextAdaptor()->subscribeEnggSafetyList(false);
    }
    if (nullptr != m_pEnggModelDriveNextDetailsSafety)
    {
        m_pEnggModelDriveNextDetailsSafety->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDetailsSafety not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextMainMenu()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr != m_pEnggModelDriveNext)
    {
        m_pEnggModelDriveNext->resetList();
        m_pEnggModelDriveNext->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LIB_UPDATE,     tr("TEXT_ENGG_MENU_DN_LIB_INFO"),           CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNext->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_CONFIG_UPDATE,  tr("TEXT_ENGG_MENU_DN_CONFIG_INFO"),        CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNext->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL,    tr("TEXT_ENGG_MENU_DN_SET_DBG_LEVEL"),      CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNext->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP,       tr("TEXT_ENGG_MENU_DN_SET_DBG_TRIP"),       CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNext->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOGGING,        tr("TEXT_ENGG_MENU_DN_SET_DBG_LOGGING"),    CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNext->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_EXPORT_LOG,     tr("TEXT_ENGG_MENU_DN_SET_EXPORT_LOG"),     CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNext->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_TRIP,           tr("TEXT_ENGG_MENU_DN_DETAILS"),            CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));

        sltDriveNextPresenceChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNext not created", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextMainMenu()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr != m_pEnggModelDriveNext)
    {
        m_pEnggModelDriveNext->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNext not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextDbgLevel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr != m_pEnggModelDriveNextDebug)
    {
        m_pEnggModelDriveNextDebug->resetList();
        m_pEnggModelDriveNextDebug->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_0, tr("TEXT_ENGG_MENU_DN_SET_DBG_LEVEL_0"),  CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));
        m_pEnggModelDriveNextDebug->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_1, tr("TEXT_ENGG_MENU_DN_SET_DBG_LEVEL_1"),  CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));
        m_pEnggModelDriveNextDebug->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_2, tr("TEXT_ENGG_MENU_DN_SET_DBG_LEVEL_2"),  CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));
        m_pEnggModelDriveNextDebug->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_3, tr("TEXT_ENGG_MENU_DN_SET_DBG_LEVEL_3"),  CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));

        sltUpdateLoggingLevelList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDebug not created", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextDbgLevel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr != m_pEnggModelDriveNextDebug)
    {
        m_pEnggModelDriveNextDebug->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDebug not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextDbgTrip()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr != m_pEnggModelDriveNextLog)
    {
        m_pEnggModelDriveNextLog->resetList();
        m_pEnggModelDriveNextLog->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_OVERALL,    tr("TEXT_ENGG_MENU_DN_SET_DBG_TRIP_OVERALL"),   CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));
        m_pEnggModelDriveNextLog->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_CURRENT,    tr("TEXT_ENGG_MENU_DN_SET_DBG_TRIP_CURRENT"),   CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));
        m_pEnggModelDriveNextLog->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_A,          tr("TEXT_ENGG_MENU_DN_SET_DBG_TRIP_A"),         CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));
        m_pEnggModelDriveNextLog->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_B,          tr("TEXT_ENGG_MENU_DN_SET_DBG_TRIP_B"),         CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));
        m_pEnggModelDriveNextLog->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_ALL,        tr("TEXT_ENGG_MENU_DN_SET_DBG_TRIP_ALL"),       CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));

        sltUpdateLoggingTripList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextLog not created", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextDbgTrip()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr != m_pEnggModelDriveNextLog)
    {
        m_pEnggModelDriveNextLog->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextLog not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextDbgLocation()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr != m_pEnggModelDriveNextLogging)
    {
        m_pEnggModelDriveNextLogging->resetList();
        m_pEnggModelDriveNextLogging->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_INTERNAL,    tr("TEXT_ENGG_MENU_DN_SET_DBG_LOGGING_INTERNAL"),   CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));
        m_pEnggModelDriveNextLogging->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_USB,         tr("TEXT_ENGG_MENU_DN_SET_DBG_LOGGING_USB"),        CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_RADIO_BUTTON));

        sltUpdateLoggingLocationList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextLogging not created", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextDbgLocation()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr != m_pEnggModelDriveNextLogging)
    {
        m_pEnggModelDriveNextLogging->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextLogging not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelDriveNextDetailList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr != m_pEnggModelDriveNextDetails)
    {
        m_pEnggModelDriveNextDetails->resetList();
        m_pEnggModelDriveNextDetails->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_EFFICIENCY,    tr("TEXT_ENGG_MENU_DN_DETAIL_EFFICIENCY"),    CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNextDetails->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_BRAKING,       tr("TEXT_ENGG_MENU_DN_DETAIL_BRAKING"),       CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNextDetails->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_ACCELERATION,  tr("TEXT_ENGG_MENU_DN_DETAIL_ACCELERATION"),  CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNextDetails->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_GEAR_SHIFT,    tr("TEXT_ENGG_MENU_DN_DETAIL_GEAR_SHIFT"),    CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNextDetails->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_GENERIC,       tr("TEXT_ENGG_MENU_DN_DETAIL_GENERIC"),       CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelDriveNextDetails->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DRIVE_NEXT_DETAILS_SAFETY,        tr("TEXT_ENGG_MENU_DN_DETAIL_SAFETY"),        CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDetails not created", __FUNCTION__);
    }
}

void CEnggAdaptor::resetEnggMenuModelDriveNextDetailList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (nullptr != m_pEnggModelDriveNextDetails)
    {
        m_pEnggModelDriveNextDetails->resetList();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDetails not created", __FUNCTION__);
    }
}

void CEnggAdaptor::initEnggMenuModelIllumination()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if ((CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        m_pEnggModelIllumination->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DISPLAY_ILLUMINATION      ,  tr("TEXT_ENGG_MENU_DISPLAY_ILLUMINATION_CAPTION")       ,  CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
        m_pEnggModelIllumination->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_BUTTON_PANEL_ILLUMINATION ,  tr("TEXT_ENGG_MENU_BUTTON_PANEL_ILLUMINATION_CAPTION")  ,  CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
    }
}

void CEnggAdaptor::initEnggMenuModelSysConfig()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);

    m_pEnggModelSysConfig->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_STEERING_WHEEL_CONTROLS      ,   tr("TEXT_ENGG_SYS_CONFIG_SWC")                 , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_SYS_CONFIG, "" ));
    m_pEnggModelSysConfig->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_CURRENT_POWER_MODE_TYPES     ,   tr("TEXT_ENGG_SYS_CONFIG_CURR_POWER_MODE")     , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_SYS_CONFIG, "" ));
    m_pEnggModelSysConfig->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_AM_FM_ANTENNA_TYPES          ,   tr("TEXT_ENGG_SYS_CONFIG_FM_AM_ANTENNA_TYPE")  , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_SYS_CONFIG, "" ));
    m_pEnggModelSysConfig->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_MICROPHONE                   ,   tr("TEXT_ENGG_SYS_CONFIG_MIC")                 , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_SYS_CONFIG, "" ));
    m_pEnggModelSysConfig->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIN                          ,   tr("TEXT_ENGG_SYS_CONFIG_VIN")                 , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_SYS_CONFIG, "" ));
    m_pEnggModelSysConfig->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VC_NUMBER                    ,   tr("TEXT_ENGG_SYS_CONFIG_VC_NUMBER")           , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_SYS_CONFIG, "" ));
    m_pEnggModelSysConfig->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_ALL_16R_PART_NUMBERS         ,   tr("TEXT_ENGG_SYS_CONFIG_SIXTEEN_R")           , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_SYS_CONFIG, "" ));

}

void CEnggAdaptor::initEnggMenuModel16RPart()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelSysConfig16RPart->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_CONTAINER_PART_NUMBER          ,  tr("TEXT_ENGG_16R_CONTAINER_PART_NUMBER")          , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
    m_pEnggModelSysConfig16RPart->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_SILVERBOX_PART_NUMER           ,  tr("TEXT_ENGG_16R_SILVERBOX_HW_PART_NUMBER")         , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));

    // Do not show Display HW part number menu in Engg Menu 16R Part Numbers for all projects.
    //m_pEnggModelSysConfig16RPart->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DISPLAYHW_PART_NUMBER          ,  tr("TEXT_ENGG_16R_DISPLAY_HW_PART_NUMBER")         , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));

    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if ((CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
            || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        m_pEnggModelSysConfig16RPart->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_BUTTON_PANEL_PART_NUMBER       ,  tr("TEXT_ENGG_16R_BUTTON_PANNEL_HW_PART_NUMBER")       , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
    }

    m_pEnggModelSysConfig16RPart->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_SOFTWARE_PART_NUMBER           ,  tr("TEXT_ENGG_16R_SOFTWARE_PART_NUMBER")           , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
    m_pEnggModelSysConfig16RPart->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_PARAMETERIZATION_PART_NUMBER   ,  tr("TEXT_ENGG_16R_PARAMETERIZATION_PART_NUMBER")   , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL));
}

void CEnggAdaptor::initEnggMenuModelTestModeTuner()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelTestModeTuner->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_TUNER_STATION_NAME           , tr("TEXT_ENGG_TESTMODE_TUNER_STATION_NAME")       , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeTuner->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_TUNER_FREQUENCY              , tr("TEXT_ENGG_TESTMODE_TUNER_FREQUENCY")          , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeTuner->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_TUNER_SIGNAL_STRENGTH        , tr("TEXT_ENGG_TESTMODE_TUNER_SIGNAL_STRENGTH")    , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeTuner->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_TUNER_MULTI_PATH             , tr("TEXT_ENGG_TESTMODE_TUNER_MULTIPATH")          , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeTuner->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_TUNER_VEHICLE_SPEED          , tr("TEXT_ENGG_TESTMODE_TUNER_VEHICLE_SPEED")      , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeTuner->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_TUNER_CURRENT_VOLUME_LEVEL   , tr("TEXT_ENGG_TESTMODE_TUNER_CURR_VOL_LEVEL")     , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));

}

void CEnggAdaptor::initEnggMenuModelTestModeAudioMedia()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelTestModeAudioMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_AUDIO_TRACK_NAME             , tr("TEXT_ENGG_TESTMODE_AUDIO_TRACK_NAME")    , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_TRACK_NAME, ""));
    m_pEnggModelTestModeAudioMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_AUDIO_BIT_RATE               , tr("TEXT_ENGG_TESTMODE_AUDIO_BIT_RATE")      , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeAudioMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_AUDIO_SAMPLING_RATE          , tr("TEXT_ENGG_TESTMODE_AUDIO_SAMPLING_RATE") , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeAudioMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_AUDIO_VEHICLE_SPEED          , tr("TEXT_ENGG_TESTMODE_AUDIO_VEHICLE_SPEED") , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeAudioMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_AUDIO_CURRENT_VOLUME_LEVEL   , tr("TEXT_ENGG_TESTMODE_AUDIO_CURR_VOL_LEVEL"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
}

void CEnggAdaptor::initEnggMenuModelTestModeVideoMedia()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelTestModeVideoMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_TRACK_NAME           , tr("TEXT_ENGG_TESTMODE_VIDEO_TRACK_NAME")          , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_TRACK_NAME, ""));
    m_pEnggModelTestModeVideoMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_VIDEO_FORMAT         , tr("TEXT_ENGG_TESTMODE_VIDEO_FORMAT")        , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeVideoMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_VIDEO_CODEC          , tr("TEXT_ENGG_TESTMODE_VIDEO_CODEC")         , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeVideoMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_VIDEO_RESOLUTION     , tr("TEXT_ENGG_TESTMODE_VIDEO_RESOLUTION")    , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeVideoMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_VIDEO_FRAME_RATE     , tr("TEXT_ENGG_TESTMODE_VIDEO_FRAME_RATE")    , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeVideoMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_AUDIO_CODEC          , tr("TEXT_ENGG_TESTMODE_VIDEO_AUDIO_CODEC")         , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeVideoMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_AUDIO_SAMPLING_RATE  , tr("TEXT_ENGG_TESTMODE_VIDEO_AUDIO_SAMPLING_RATE") , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeVideoMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_VEHICLE_SPEED        , tr("TEXT_ENGG_TESTMODE_VIDEO_VEHICLE_SPEED")       , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
    m_pEnggModelTestModeVideoMedia->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_CURRENT_VOLUME_LEVEL , tr("TEXT_ENGG_TESTMODE_VIDEO_VOL_LEVEL"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, ""));
}

void CEnggAdaptor::initEnggMenuModelDebugLogs()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelDebugLog->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_TEST_AUTOMATION  , tr("TEXT_ENGG_TEST_AUTOMATION") , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_CHECKBOX  ,"" ,false));
    m_pEnggModelDebugLog->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_STATIC_IP        , tr("TEXT_ENGG_STATIC_IP")       , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_CHECKBOX  ,"" ,false));
    m_pEnggModelDebugLog->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_DEBUGS_LOG       , tr("TEXT_ENGG_DEBUG_LOGS")      , CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_CHECKBOX  ,"" ,false));
    m_pEnggModelDebugLog->addItem(CEnggMenuData(CEnggMenuEnum::ENGG_MENU_ID_EXTRACT_LOG      , tr("TEXT_ENGG_MENU_DEBUGLOGS_EXTRACT_LOGS"), CEnggMenuEnum::ENGG_MENU_ITEM_TYPE_LABEL_WITH_LABEL, "" ,false));
}

//____________________________________________________________________________
CEnggAdaptor::~CEnggAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);

    if(m_pEnggAdaptor)
    {
        delete m_pEnggAdaptor;
        m_pEnggAdaptor = nullptr;
    }
    if(m_pEnggModelDebugLog)
    {
        delete m_pEnggModelDebugLog;
        m_pEnggModelDebugLog = nullptr;
    }
    if(m_pEnggModelIllumination)
    {
        delete m_pEnggModelIllumination;
        m_pEnggModelIllumination = nullptr;
    }
    if(m_pEnggModelSysConfig)
    {
        delete m_pEnggModelSysConfig;
        m_pEnggModelSysConfig = nullptr;
    }
    if(m_pEnggModelSysConfig16RPart)
    {
        delete m_pEnggModelSysConfig16RPart;
        m_pEnggModelSysConfig16RPart = nullptr;
    }
    if(m_pEnggModelTestModeTuner)
    {
        delete m_pEnggModelTestModeTuner;
        m_pEnggModelTestModeTuner = nullptr;
    }
    if(m_pEnggModelTestModeAudioMedia)
    {
        delete m_pEnggModelTestModeAudioMedia;
        m_pEnggModelTestModeAudioMedia = nullptr;
    }
    if(m_pEnggModelTestModeVideoMedia)
    {
        delete m_pEnggModelTestModeVideoMedia;
        m_pEnggModelTestModeVideoMedia = nullptr;
    }
    if(m_pEnggModelEnggMain)
    {
        delete m_pEnggModelEnggMain;
        m_pEnggModelEnggMain = nullptr;
    }
    if(m_pEnggMenuCurrentListModel)
    {
        m_pEnggMenuCurrentListModel = nullptr;
    }
}
//____________________________________________________________________________

///////////////////////////////////////////////////////////////////////////////
// property related functions
///////////////////////////////////////////////////////////////////////////////
CEnggMenuListModel *CEnggAdaptor::enggMenuCurrentListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    return m_pEnggMenuCurrentListModel;
}
CEnggMenuEnum::EEnggMenuScreen CEnggAdaptor::enggMenuCurrentScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    return m_eEnggMenuCurrentScreen;
}

QString CEnggAdaptor::enggMenuScreenTitle()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    return m_strEnggMenuScreenTitle;
}

bool CEnggAdaptor::enggMenuTestAutomationStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    return (CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_ENGG_MENU_TEST_AUTOMATION));
}


void CEnggAdaptor::setEnggMenuCurrentScreen(CEnggMenuEnum::EEnggMenuScreen eEnggMenuCurrentScreenIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: eEnggMenuCurrentScreenIndex: %d", __FUNCTION__, eEnggMenuCurrentScreenIndex);
    if (m_eEnggMenuCurrentScreen != eEnggMenuCurrentScreenIndex)
    {
        m_eEnggMenuCurrentScreen = eEnggMenuCurrentScreenIndex;
        emit sigEnggMenuCurrentScreenChanged();
    }
}

void CEnggAdaptor::setDebugsLogCheckStatus(bool bDebugsLogStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bDebugsLogStatus : %d", __FUNCTION__, bDebugsLogStatus);
    m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_DEBUGS_LOG, true ,CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE );
    m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_DEBUGS_LOG, bDebugsLogStatus ,CEnggMenuListModel::ENGG_MENU_ITEM_STATUS_ROLE );
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_ENGG_DEBUG_LOGS_SELECTION, bDebugsLogStatus);
}

void CEnggAdaptor::setIpTypeStatus(int iIpStatus, int iIpType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_STATIC_IP, true ,CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);

    if (CEnggMenuEnum::LOG_RESPONSE_SUCCESS == iIpStatus)
    {
        switch(iIpType)
        {
        case CEnggMenuEnum::IP_DYNAMIC :
        {
            m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_STATIC_IP,  tr("TEXT_ENGG_STATIC_IP") ,CEnggMenuListModel::ENGG_MENU_ITEM_MAIN_TEXT_ROLE);
            m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_STATIC_IP, false ,CEnggMenuListModel::ENGG_MENU_ITEM_STATUS_ROLE);
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_ENGG_STATIC_IP_SELECTION, 0);
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: using Dynamic IP", __FUNCTION__);
        }
            break;

        case CEnggMenuEnum::IP_STATIC :
        {
            m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_STATIC_IP, tr("TEXT_ENGG_STATIC_IP(192.168.1.1)"), CEnggMenuListModel::ENGG_MENU_ITEM_MAIN_TEXT_ROLE);
            m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_STATIC_IP, true ,CEnggMenuListModel::ENGG_MENU_ITEM_STATUS_ROLE);
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_ENGG_STATIC_IP_SELECTION, 1);
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: using Static IP", __FUNCTION__);
        }
            break;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s:  INVALID RESPONSE: iIpStatus:%d, iIpType:%d", __FUNCTION__, iIpStatus, iIpType);
    }
}

void CEnggAdaptor::setEnggMenuTestAutomationStatus(int iTestAutomationStatusCb, int iTestAutomationValueCb)
{

    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TEST_AUTOMATION, true ,CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE );
    if( CEnggMenuEnum::LOG_RESPONSE_SUCCESS == iTestAutomationStatusCb)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iTestAutomationStatusCb: %d, iTestAutomationValueCb: %d", __FUNCTION__, iTestAutomationStatusCb, iTestAutomationValueCb);
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_ENGG_MENU_TEST_AUTOMATION, iTestAutomationValueCb);
        if(iTestAutomationValueCb == CEnggMenuEnum::TEST_AUTOMATION_ENABLE )
        {
            m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TEST_AUTOMATION, true ,CEnggMenuListModel::ENGG_MENU_ITEM_STATUS_ROLE );
            emit sigEnggMenuTestAutomationStatusChanged();
        }

        else if(iTestAutomationValueCb == CEnggMenuEnum::TEST_AUTOMATION_DISABLE)
        {
            m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TEST_AUTOMATION, false ,CEnggMenuListModel::ENGG_MENU_ITEM_STATUS_ROLE );
            emit sigEnggMenuTestAutomationStatusChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: INVALID TEST AUTOMATION CALLBACK", __FUNCTION__ );
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: CALLBACK FAILURE", __FUNCTION__ );
    }
}

void CEnggAdaptor::setFactoryResetWaitingStatus(bool bFactoryResetWaitingStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bFactoryResetWaitingStatus : %d", __FUNCTION__, bFactoryResetWaitingStatus);
    emit sigFactoryResetWaitingStatusChanged(bFactoryResetWaitingStatus);
}

void CEnggAdaptor::setFactoryResetCompletionStatus(bool bFactoryResetCompletionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bFactoryResetCompletionStatus : %d", __FUNCTION__, bFactoryResetCompletionStatus);
    emit sigFactoryResetCompletionStatusChanged(bFactoryResetCompletionStatus);
}

void CEnggAdaptor::setDeviceModeStatus(int iDeviceModeStatus, int iDeviceType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iDeviceModeStatus: %d, iDeviceType: %d", __FUNCTION__, iDeviceModeStatus, iDeviceType);
    m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_DEVICE_MODE, true , CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE );

    if(CEnggMenuEnum::LOG_RESPONSE_SUCCESS == iDeviceModeStatus)
    {
        if(CEnggMenuEnum::DEVICE_MODE == iDeviceType)
        {
            m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_DEVICE_MODE, true, CEnggMenuListModel::ENGG_MENU_ITEM_STATUS_ROLE );
        }
        else if(CEnggMenuEnum::HOST_MODE == iDeviceType)
        {
            m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_DEVICE_MODE, false, CEnggMenuListModel::ENGG_MENU_ITEM_STATUS_ROLE );
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: CALLBACK FAILURE FOR DEVICE MODE", __FUNCTION__ );
    }
}

void CEnggAdaptor::startFactoryResetProcess()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    m_pEnggMenuResource->startFactoryReset();
}

void CEnggAdaptor::buttonPanelHkHandling()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    int iKeyCode = (CHMIMain::getSM()->getSCI_HardKey()->get_iKeyCode());
    int iKeyState = (CHMIMain::getSM()->getSCI_HardKey()->get_iKeyState());
    emit sigButtonPanelHKPressedChanged(iKeyCode, iKeyState);
}

void CEnggAdaptor::setEnggMenuCurrentListModel(CEnggMenuListModel *pEnggMenuCurrentListModel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (m_pEnggMenuCurrentListModel != pEnggMenuCurrentListModel)
    {
        m_pEnggMenuCurrentListModel = pEnggMenuCurrentListModel;
        emit sigEnggMenuCurrentListModelChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Engg Menu Model Not changed.", __FUNCTION__);
    }
}

void CEnggAdaptor::setEnggMenuCurrentScreenTitle(QString strEnggMenuScreenTitle)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if (m_strEnggMenuScreenTitle != strEnggMenuScreenTitle)
    {
        m_strEnggMenuScreenTitle = strEnggMenuScreenTitle;
        emit sigEnggMenuScreenTitleChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Engg Menu Title Not changed.", __FUNCTION__);
    }
}

void CEnggAdaptor:: toggleEnggCheckbox(bool bCheckboxStatus, int iListItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    switch (m_eEnggMenuCurrentScreen)
    {
    case CEnggMenuEnum::ENGG_MENU_SCREEN_MAIN :
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DEBUG_LOG:
    {
        toggleEnggDebugCheckbox(bCheckboxStatus, iListItemId);
        m_pEnggModelDebugLog->updateEnggMenuModel(iListItemId, false ,CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE );
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_ILLUMINATION:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_TEST_MODE:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LIB_UPDATE:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_CONFIG_UPDATE:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DEBUG:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LOG:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LOGGING:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_EFFICIENCY:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_BRAKING:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_ACCELERATION:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GEAR_SHIFT:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GENERIC:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_SAFETY:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iModelNo %d not found", __FUNCTION__, m_eEnggMenuCurrentScreen);
    }
        break;
    }
}

void CEnggAdaptor::invToggleEnggRadioButton(bool bRadioButton, int iListItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, iListItemId:%d, bRadioButton:%d", __FUNCTION__, iListItemId, bRadioButton);
    switch (m_eEnggMenuCurrentScreen)
    {
    case CEnggMenuEnum::ENGG_MENU_SCREEN_MAIN :
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DEBUG_LOG:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_ILLUMINATION:
    {
        //TODO:Will be Implemented as per need
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG:
    {
        //TODO:Will be Implemented as per need
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_TEST_MODE:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LIB_UPDATE:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_CONFIG_UPDATE:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DEBUG:
    {
        if (bRadioButton)
        {
            changeDriveNextDebugLevel(iListItemId);
        }
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LOG:
    {
        if (bRadioButton)
        {
            changeDriveNextLogType(iListItemId);
        }
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LOGGING:
    {
        if (bRadioButton)
        {
            changeDriveNextLoggingLocation(iListItemId);
        }
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_EFFICIENCY:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_BRAKING:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_ACCELERATION:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GEAR_SHIFT:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GENERIC:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_SAFETY:
    {
        //TODO:Will be Implemented as per need
    }
        break;

    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iModelNo %d not found", __FUNCTION__, m_eEnggMenuCurrentScreen);
    }
        break;
    }
}

void CEnggAdaptor::processEnggMenuItemClick(int iListItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iListItemId :%d", __FUNCTION__, iListItemId);

    switch (enggMenuCurrentScreen())
    {
    case CEnggMenuEnum::ENGG_MENU_SCREEN_DEBUG_LOG:
    {
        if(CEnggMenuEnum::ENGG_MENU_ID_EXTRACT_LOG == iListItemId)
        {
            CEnggAdaptor::getInstance()->startExtractingDebugsLogToUsb();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: List Id is not Extract Logs Id.", __FUNCTION__);
        }

    }
        break;

        //todo: More cases can be added as per requirement in future.
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: List Id is not Extract Logs Id.", __FUNCTION__);
        break;
    }
}

void CEnggAdaptor::toggleEnggDebugCheckbox(bool bCheckboxStatus, int iListItemId)
{

    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bCheckboxStatus : %d ,iListItemId :%d", __FUNCTION__,bCheckboxStatus,iListItemId);
    switch (iListItemId)
    {

    case CEnggMenuEnum::ENGG_MENU_ID_STATIC_IP:
    {
        m_pEnggMenuResource->setSystemIpAddress(bCheckboxStatus);

    }
        break;

    case CEnggMenuEnum::ENGG_MENU_ID_DEBUGS_LOG:
    {
        if(bCheckboxStatus)
        {
            m_pEnggMenuResource->startDebugLogsService();
        }
        else
        {
            m_pEnggMenuResource->stopDebugLogsService();
        }
    }
        break;


    case CEnggMenuEnum::ENGG_MENU_ID_TEST_AUTOMATION:
    {

        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Test Automation Service Starts", __FUNCTION__);
        m_pEnggMenuResource->testAutomationToggleService(bCheckboxStatus);

    }
        break;
    case CEnggMenuEnum::ENGG_MENU_ID_DEVICE_MODE:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Device Mode Changed", __FUNCTION__);
        m_pEnggMenuResource->setDeviceMode(bCheckboxStatus);
    }
        break;
    default:

        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iListItemId: %d not found" , __FUNCTION__, iListItemId);
        break;
    }
}

void CEnggAdaptor::changeDriveNextDebugLevel(int iValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, iValue:%d", __FUNCTION__, iValue);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextEnum::EDNLogLevel eValue = CDriveNextEnum::DRIVENEXT_LOG_LEVEL_UNKNOWN;
        switch(iValue)
        {
        case 0:
        {
            eValue = CDriveNextEnum::DRIVENEXT_LOG_LEVEL_0;
        }
            break;
        case 1:
        {
            eValue = CDriveNextEnum::DRIVENEXT_LOG_LEVEL_1;
        }
            break;
        case 2:
        {
            eValue = CDriveNextEnum::DRIVENEXT_LOG_LEVEL_2;
        }
            break;
        case 3:
        {
            eValue = CDriveNextEnum::DRIVENEXT_LOG_LEVEL_3;
        }
            break;
        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, %d value not handled", __FUNCTION__, iValue);
        }
            break;
        }
        CDriveNextApplication::getDriveNextAdaptor()->updateLogLevel(eValue);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, DriveNext Adaptor not available", __FUNCTION__);
    }
}

void CEnggAdaptor::changeDriveNextLogType(int iValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, iValue:%d", __FUNCTION__, iValue);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextEnum::EDNTripType eValue = CDriveNextEnum::DRIVENEXT_TRIP_UNKNOWN;
        switch(iValue)
        {
        case 0:
        {
            eValue = CDriveNextEnum::DRIVENEXT_OVERALL_TRIP;
        }
            break;
        case 1:
        {
            eValue = CDriveNextEnum::DRIVENEXT_CURRENT_TRIP;
        }
            break;
        case 2:
        {
            eValue = CDriveNextEnum::DRIVENEXT_TRIP_A;
        }
            break;
        case 3:
        {
            eValue = CDriveNextEnum::DRIVENEXT_TRIP_B;
        }
            break;
        case 4:
        {
            eValue = CDriveNextEnum::DRIVENEXT_ALL_TRIP;
        }
            break;
        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, %d value not handled", __FUNCTION__, iValue);
        }
            break;
        }
        CDriveNextApplication::getDriveNextAdaptor()->updateLogTripType(eValue);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, DriveNext Adaptor not available", __FUNCTION__);
    }
}

void CEnggAdaptor::changeDriveNextLoggingLocation(int iValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, iValue:%d", __FUNCTION__, iValue);
    if (CDriveNextApplication::getDriveNextAdaptor())
    {
        CDriveNextEnum::EDNLoggingType eValue = CDriveNextEnum::DRIVENEXT_LOG_TYPE_UNKNOWN;
        switch(iValue)
        {
        case 0:
        {
            eValue = CDriveNextEnum::DRIVENEXT_LOG_TYPE_INTERNAL;
        }
            break;
        case 1:
        {
            eValue = CDriveNextEnum::DRIVENEXT_LOG_TYPE_USB;
        }
            break;
        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, %d value not handled", __FUNCTION__, iValue);
        }
            break;
        }
        CDriveNextApplication::getDriveNextAdaptor()->updateLoggingLocation(eValue);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, DriveNext Adaptor not available", __FUNCTION__);
    }
}

void CEnggAdaptor::setAdaptorEnggMenuModel(CEnggMenuEnum::EEnggMenuScreen eEnggMenuScreen)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    switch (eEnggMenuScreen) {
    case CEnggMenuEnum::ENGG_MENU_SCREEN_MAIN :
        setEnggMenuCurrentListModel(m_pEnggModelEnggMain);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_TITLE"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DEBUG_LOG:
        setEnggMenuCurrentListModel(m_pEnggModelDebugLog);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DEBUGLOGS_CAPTION"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_ILLUMINATION:
    {
        setEnggMenuCurrentListModel(m_pEnggModelIllumination);

        CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
        if ((CVariantControlEnum::VIP_DID_HU_HIGH_X451 == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID)
                || (CVariantControlEnum::VIP_DID_HU_NEXON_EV_HIGH == eVIP_DID) || (CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
        {
            setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_ILLUMINATION_CAPTION"));
        }
        else
        {
            setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DISPLAY_ILLUMINATION_CAPTION"));
        }
    }
        break;
    case CEnggMenuEnum::ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION:
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DISPLAY_ILLUMINATION_CAPTION"));
        break;
    case CEnggMenuEnum::ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION:
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_BUTTON_PANEL_ILLUMINATION_CAPTION"));
        break;
    case CEnggMenuEnum::ENGG_MENU_SCREEN_BUTTON_PANEL:
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_BUTTONPANEL_CAPTION"));
        break;
    case CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG:
        setEnggMenuCurrentListModel(m_pEnggModelSysConfig);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_SYSCONFIG_CAPTION"));
        break;
    case CEnggMenuEnum::ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R:
        setEnggMenuCurrentListModel(m_pEnggModelSysConfig16RPart);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_SYS_CONFIG_SIXTEEN_R"));
        break;
    case CEnggMenuEnum::ENGG_MENU_SCREEN_TEST_MODE:
        m_iActiveSource = CAudioAdaptor::getInstance()->activeEntSrc();
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: active source in screen : %d", __FUNCTION__, m_iActiveSource);
        if((CAudioEnums::SRC_TUNER_FM == m_iActiveSource) || (CAudioEnums::SRC_TUNER_AM == m_iActiveSource))
        {
            setEnggMenuCurrentListModel(m_pEnggModelTestModeTuner);
            setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_TESTMODE_TUNER_TITLE"));

            /*
             * Quality monitor should only be enabled in tuner test mode screen as the corresponding attribute(multipath)
             * keeps changing continuosly so might affect performance and is needed only in this screen
            */
            setEnggMenuCurrentScreenTitle((m_iActiveSource == CAudioEnums::SRC_TUNER_FM) ? tr("TEXT_ENGG_MENU_TESTMODE_TUNER_FM") : tr("TEXT_ENGG_MENU_TESTMODE_TUNER_AM"));

        }
        else if((CAudioEnums::SRC_USB1 == m_iActiveSource) && (CMediaEnum::EMediaBrowseItem::BROWSEITEM_VIDEOS == m_iCurrentTestMode))
        {
            setEnggMenuCurrentListModel(m_pEnggModelTestModeVideoMedia);
            setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_TESTMODE_VIDEO_MEDIA"));
        }
        else if ((CAudioEnums::SRC_AUDIO_AUX == m_iActiveSource) || (CAudioEnums::SRC_BT_A2DP1 == m_iActiveSource)
                 || (CAudioEnums::SRC_USB1 == m_iActiveSource)|| (CAudioEnums::SRC_IPOD == m_iActiveSource))
        {
            setEnggMenuCurrentListModel(m_pEnggModelTestModeAudioMedia);
            switch (m_iActiveSource)
            {
            case CAudioEnums::SRC_AUDIO_AUX :
                setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_TESTMODE_AUDIO_MEDIA_AUX"));
                break;

            case CAudioEnums::SRC_BT_A2DP1 :
                setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_TESTMODE_AUDIO_MEDIA_BT"));
                break;

            case CAudioEnums::SRC_USB1 :
                setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_TESTMODE_AUDIO_MEDIA_USB"));
                break;

            case CAudioEnums::SRC_IPOD :
                setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_TESTMODE_AUDIO_MEDIA_IPOD"));
                break;

            default:
                setEnggMenuCurrentScreenTitle("");
                LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: No appropriate Audio Media Found", __FUNCTION__);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "Unknown source or media off mode");
        }
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT:
        initEnggMenuModelDriveNextMainMenu();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNext);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_TESTMODE_TITLE"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LIB_UPDATE:
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_LIB_INFO_TITLE"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_CONFIG_UPDATE:
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_CONFIG_INFO_TITLE"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DEBUG:
        initEnggMenuModelDriveNextDbgLevel();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNextDebug);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_SET_DBG_LEVEL_TITLE"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LOG:
        initEnggMenuModelDriveNextDbgTrip();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNextLog);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_SET_DBG_TRIP_TITLE"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_LOGGING:
        initEnggMenuModelDriveNextDbgLocation();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNextLogging);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_SET_DBG_LOGGING_TITLE"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS:
        initEnggMenuModelDriveNextDetailList();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNextDetails);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_DETAIL_TITLE"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_EFFICIENCY:
        initEnggMenuModelDriveNextEfficiency();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNextDetailsEfficiency);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_DETAIL_EFFICIENCY"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_BRAKING:
        initEnggMenuModelDriveNextBraking();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNextDetailsBraking);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_DETAIL_BRAKING"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_ACCELERATION:
        initEnggMenuModelDriveNextAcceleration();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNextDetailsAcceleration);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_DETAIL_ACCELERATION"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GEAR_SHIFT:
        initEnggMenuModelDriveNextGearShift();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNextDetailsGearShift);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_DETAIL_GEAR_SHIFT"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GENERIC:
        initEnggMenuModelDriveNextGeneric();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNextDetailsGeneric);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_DETAIL_GENERIC"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_SAFETY:
        initEnggMenuModelDriveNextSafety();
        setEnggMenuCurrentListModel(m_pEnggModelDriveNextDetailsSafety);
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_DN_DETAIL_SAFETY"));
        break;

    case CEnggMenuEnum::ENGG_MENU_SCREEN_W3W_LAST_NAVIGATED:
        setEnggMenuCurrentScreenTitle(tr("TEXT_ENGG_MENU_W3W_LAST_NAVIGATED_TITLE"));
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iModelNo %d not found", __FUNCTION__, m_eEnggMenuCurrentScreen);
        break;
    }

    // These slots are called as whenever the list screen  will change, the slots will fetch the latest value from the other modules
    sltActEntSourceVolumeChanged();
    sltSongTitleChanged();
    sltVehicleSpeedChanged();
}

void CEnggAdaptor::sltUpdateDriveNextElements()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);

    bool bUSBStatus = CAudioAdaptor::getInstance()->usbSrcStatus();
    bool bDNProxyStatus = CDriveNextApplication::getDriveNextAdaptor() && CDriveNextApplication::getDriveNextAdaptor()->driveNextPresence();
    bool bNotExportingLogs = CDriveNextApplication::getDriveNextAdaptor() && (!CDriveNextApplication::getDriveNextAdaptor()->exportingLogs());
    bool bNotUpdatingLoggingLocation = CDriveNextApplication::getDriveNextAdaptor() && (!CDriveNextApplication::getDriveNextAdaptor()->updatingLoggingLocation());

    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, bUSBStatus : %d, bNotExportingLogs : %d, bNotUpdatingLoggingLocation : %d", __FUNCTION__, bUSBStatus, bNotExportingLogs, bNotUpdatingLoggingLocation);

    if ((nullptr != m_pEnggModelDriveNext) && m_pEnggModelDriveNext->rowCount() > 0)
    {
        m_pEnggModelDriveNext->updateEnggMenuModel(CEnggMenuEnum::EEnggMenuDriveNextMenu::ENGG_MENU_ID_DRIVE_NEXT_EXPORT_LOG, (bDNProxyStatus && bUSBStatus && bNotExportingLogs), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNext empty", __FUNCTION__);
    }

    if ((nullptr != m_pEnggModelDriveNextLogging) && (m_pEnggModelDriveNextLogging->rowCount() > 0))
    {
        m_pEnggModelDriveNextLogging->updateEnggMenuModel(CEnggMenuEnum::EEnggMenuDriveNextLoggingLocation::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_USB, (bUSBStatus && bNotUpdatingLoggingLocation), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextLogging empty", __FUNCTION__);
    }
}

void CEnggAdaptor::sltDriveNextPresenceChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    bool bUSBStatus = CAudioAdaptor::getInstance()->usbSrcStatus();
    bool bDNProxyStatus = CDriveNextApplication::getDriveNextAdaptor() && CDriveNextApplication::getDriveNextAdaptor()->driveNextPresence();
    bool bNotExportingLogs = CDriveNextApplication::getDriveNextAdaptor() && (!CDriveNextApplication::getDriveNextAdaptor()->exportingLogs());

    if ((nullptr != m_pEnggModelDriveNext) && m_pEnggModelDriveNext->rowCount() > 0)
    {
        m_pEnggModelDriveNext->updateEnggMenuModel(CEnggMenuEnum::EEnggMenuDriveNextMenu::ENGG_MENU_ID_DRIVE_NEXT_LIB_UPDATE,       (bDNProxyStatus), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
        m_pEnggModelDriveNext->updateEnggMenuModel(CEnggMenuEnum::EEnggMenuDriveNextMenu::ENGG_MENU_ID_DRIVE_NEXT_CONFIG_UPDATE,    (bDNProxyStatus), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
        m_pEnggModelDriveNext->updateEnggMenuModel(CEnggMenuEnum::EEnggMenuDriveNextMenu::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL,      (bDNProxyStatus), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
        m_pEnggModelDriveNext->updateEnggMenuModel(CEnggMenuEnum::EEnggMenuDriveNextMenu::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP,         (bDNProxyStatus), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
        m_pEnggModelDriveNext->updateEnggMenuModel(CEnggMenuEnum::EEnggMenuDriveNextMenu::ENGG_MENU_ID_DRIVE_NEXT_LOGGING,          (bDNProxyStatus), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
        m_pEnggModelDriveNext->updateEnggMenuModel(CEnggMenuEnum::EEnggMenuDriveNextMenu::ENGG_MENU_ID_DRIVE_NEXT_EXPORT_LOG,       (bDNProxyStatus && bUSBStatus && bNotExportingLogs), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
        m_pEnggModelDriveNext->updateEnggMenuModel(CEnggMenuEnum::EEnggMenuDriveNextMenu::ENGG_MENU_ID_DRIVE_NEXT_TRIP,             (bDNProxyStatus), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNext empty", __FUNCTION__);
    }
}

void CEnggAdaptor::sltUpdateLoggingTripList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);

    if ((nullptr != m_pEnggModelDriveNextLog) && (m_pEnggModelDriveNextLog->rowCount() > 0))
    {
        if (CDriveNextApplication::getDriveNextAdaptor())
        {
            bool bUpdating = CDriveNextApplication::getDriveNextAdaptor()->updatingLogTripType();
            CDriveNextEnum::EDNTripType eType = CDriveNextApplication::getDriveNextAdaptor()->logTripType();
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, eType:%d, bUpdating:%d", __FUNCTION__, static_cast<int>(eType), bUpdating);

            CEnggMenuEnum::EEnggMenuDriveNextLogTrip eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextLogTrip::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_UNKNOWN;
            switch(eType)
            {
            case CDriveNextEnum::DRIVENEXT_OVERALL_TRIP:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextLogTrip::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_OVERALL;
            }
                break;
            case CDriveNextEnum::DRIVENEXT_CURRENT_TRIP:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextLogTrip::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_CURRENT;
            }
                break;
            case CDriveNextEnum::DRIVENEXT_TRIP_A:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextLogTrip::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_A;
            }
                break;
            case CDriveNextEnum::DRIVENEXT_TRIP_B:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextLogTrip::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_B;
            }
                break;
            case CDriveNextEnum::DRIVENEXT_ALL_TRIP:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextLogTrip::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_ALL;
            }
                break;
            default:
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, %d value not handled", __FUNCTION__, static_cast<int>(eType));
            }
                break;
            }

            for (int i = CEnggMenuEnum::EEnggMenuDriveNextLogTrip::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_OVERALL; i <= CEnggMenuEnum::EEnggMenuDriveNextLogTrip::ENGG_MENU_ID_DRIVE_NEXT_LOG_TRIP_ALL; i++)
            {
                m_pEnggModelDriveNextLog->updateEnggMenuModel(i, (i == eSelectedId), CEnggMenuListModel::ENGG_MENU_ITEM_STATUS_ROLE);
                m_pEnggModelDriveNextLog->updateEnggMenuModel(i, (!bUpdating), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s DriveNextAdaptor not available", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextLog empty", __FUNCTION__);
    }
}

void CEnggAdaptor::sltUpdateLoggingLevelList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);

    if ((nullptr != m_pEnggModelDriveNextDebug) && m_pEnggModelDriveNextDebug->rowCount() > 0)
    {
        if (CDriveNextApplication::getDriveNextAdaptor())
        {
            bool bUpdating = CDriveNextApplication::getDriveNextAdaptor()->updatingLogLevel();
            CDriveNextEnum::EDNLogLevel eType = CDriveNextApplication::getDriveNextAdaptor()->logLevel();
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, eType:%d, bUpdating:%d", __FUNCTION__, static_cast<int>(eType), bUpdating);

            CEnggMenuEnum::EEnggMenuDriveNextDebugLevel eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextDebugLevel::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_UNKNOWN;
            switch(eType)
            {
            case CDriveNextEnum::EDNLogLevel::DRIVENEXT_LOG_LEVEL_0:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextDebugLevel::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_0;
            }
                break;
            case CDriveNextEnum::EDNLogLevel::DRIVENEXT_LOG_LEVEL_1:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextDebugLevel::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_1;
            }
                break;
            case CDriveNextEnum::EDNLogLevel::DRIVENEXT_LOG_LEVEL_2:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextDebugLevel::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_2;
            }
                break;
            case CDriveNextEnum::EDNLogLevel::DRIVENEXT_LOG_LEVEL_3:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextDebugLevel::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_3;
            }
                break;
            default:
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, %d value not handled", __FUNCTION__, static_cast<int>(eType));
            }
                break;
            }

            for (int i = CEnggMenuEnum::EEnggMenuDriveNextDebugLevel::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_0; i < CEnggMenuEnum::EEnggMenuDriveNextDebugLevel::ENGG_MENU_ID_DRIVE_NEXT_DEBUG_LEVEL_TOTAL_COUNT; i++)
            {
                m_pEnggModelDriveNextDebug->updateEnggMenuModel(i, (i == eSelectedId), CEnggMenuListModel::ENGG_MENU_ITEM_STATUS_ROLE);
                m_pEnggModelDriveNextDebug->updateEnggMenuModel(i, (!bUpdating), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s DriveNextAdaptor not available", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextDebug empty", __FUNCTION__);
    }
}

void CEnggAdaptor::sltUpdateLoggingLocationList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);

    if ((nullptr != m_pEnggModelDriveNextLogging) && (m_pEnggModelDriveNextLogging->rowCount() > 0))
    {
        if (CDriveNextApplication::getDriveNextAdaptor())
        {
            bool bUpdating = CDriveNextApplication::getDriveNextAdaptor()->updatingLoggingLocation();
            bool bUSBStatus = CAudioAdaptor::getInstance()->usbSrcStatus();
            CDriveNextEnum::EDNLoggingType eType = CDriveNextApplication::getDriveNextAdaptor()->loggingLocation();
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, eType:%d, bUpdating:%d, bUSBStatus:%d", __FUNCTION__, static_cast<int>(eType), bUpdating, bUSBStatus);

            CEnggMenuEnum::EEnggMenuDriveNextLoggingLocation eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextLoggingLocation::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_UNKNOWN;
            switch(eType)
            {
            case CDriveNextEnum::EDNLoggingType::DRIVENEXT_LOG_TYPE_INTERNAL:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextLoggingLocation::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_INTERNAL;
            }
                break;
            case CDriveNextEnum::EDNLoggingType::DRIVENEXT_LOG_TYPE_USB:
            {
                eSelectedId = CEnggMenuEnum::EEnggMenuDriveNextLoggingLocation::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_USB;
            }
                break;
            default:
            {
                LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s, %d value not handled", __FUNCTION__, static_cast<int>(eType));
            }
                break;
            }

            for (int i = CEnggMenuEnum::EEnggMenuDriveNextLoggingLocation::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_INTERNAL; i < CEnggMenuEnum::EEnggMenuDriveNextLoggingLocation::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_TOTAL_COUNT; i++)
            {
                m_pEnggModelDriveNextLogging->updateEnggMenuModel(i, (i == eSelectedId), CEnggMenuListModel::ENGG_MENU_ITEM_STATUS_ROLE);
                m_pEnggModelDriveNextLogging->updateEnggMenuModel(i, (!bUpdating), CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
            }

            if (!bUSBStatus)
            {
                m_pEnggModelDriveNextLogging->updateEnggMenuModel(CEnggMenuEnum::EEnggMenuDriveNextLoggingLocation::ENGG_MENU_ID_DRIVE_NEXT_LOGGING_USB, false, CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
            }
            else
            {
                //Do Nothing.
            }
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s DriveNextAdaptor not available", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s m_pEnggModelDriveNextLogging empty", __FUNCTION__);
    }
}

void CEnggAdaptor::sltFrequencyChanged()
{
    QString strFrequency = CTunerAdaptor::getInstance()->strFrequency() + CTunerAdaptor::getInstance()->strFrequencyUnit();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: frequency: %s", __FUNCTION__, (strFrequency.toStdString()).c_str());
    if (m_pEnggModelTestModeTuner)
    {
        m_pEnggModelTestModeTuner->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TUNER_FREQUENCY, strFrequency, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeTuner is null");
    }
}

void CEnggAdaptor::sltStationNameChanged()
{
    QString strStationName = CTunerAdaptor::getInstance()->strStationName();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: station name: %s", __FUNCTION__, (strStationName.toStdString()).c_str());
    if (m_pEnggModelTestModeTuner)
    {
        m_pEnggModelTestModeTuner->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TUNER_STATION_NAME, strStationName, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeTuner is null");
    }
}

void CEnggAdaptor::sltFieldStrengthChanged()
{
    int fieldStrength = CTunerAdaptor::getInstance()->iFieldStrength();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: field strength: %d", __FUNCTION__,fieldStrength);
    if (m_pEnggModelTestModeTuner)
    {
        m_pEnggModelTestModeTuner->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TUNER_SIGNAL_STRENGTH, fieldStrength, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
}

void CEnggAdaptor::sltMultipathChanged()
{
    unsigned char ucMultipathValue = CTunerAdaptor::getInstance()->multiPath();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: ucMultipathValue: %d", __FUNCTION__, ucMultipathValue);
    if (m_pEnggModelTestModeTuner)
    {
        m_pEnggModelTestModeTuner->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TUNER_MULTI_PATH, ucMultipathValue, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
}

void CEnggAdaptor::sltNowPlayingMetadataChanged()
{
    m_iCurrentTestMode = CMediaAdaptor::getInstance().nowPlayingMetadata();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: TestMode : %d", __FUNCTION__, m_iCurrentTestMode);
    sltActiveEntSrcChanged();
}

void CEnggAdaptor::sltActEntSourceVolumeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);

    int iActiveEntSourceVolume = CAudioAdaptor::getInstance()->actEntSourceVolume();

    if((m_pEnggMenuCurrentListModel == m_pEnggModelTestModeTuner) && (m_pEnggModelTestModeTuner))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iActiveEntSourceVolume : %d", __FUNCTION__, iActiveEntSourceVolume);
        m_pEnggModelTestModeTuner->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TUNER_CURRENT_VOLUME_LEVEL, iActiveEntSourceVolume, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else if((m_pEnggMenuCurrentListModel == m_pEnggModelTestModeAudioMedia) && (m_pEnggModelTestModeAudioMedia))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iActiveEntSourceVolume : %d", __FUNCTION__, iActiveEntSourceVolume);
        m_pEnggModelTestModeAudioMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_AUDIO_CURRENT_VOLUME_LEVEL, iActiveEntSourceVolume, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else if((m_pEnggMenuCurrentListModel == m_pEnggModelTestModeVideoMedia) && (m_pEnggModelTestModeVideoMedia))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iActiveEntSourceVolume : %d", __FUNCTION__, iActiveEntSourceVolume);
        m_pEnggModelTestModeVideoMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_CURRENT_VOLUME_LEVEL, iActiveEntSourceVolume, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeTuner or m_pEnggModelTestModeAudioMedia or m_pEnggModelTestModeVideoMedia  is null");
    }
}


void CEnggAdaptor::sltActiveEntSrcChanged()
{
    m_iActiveSource = CAudioAdaptor::getInstance()->activeEntSrc();
    m_pEnggModelEnggMain->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TEST_MODE, true, CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_iActiveSource : %d", __FUNCTION__, m_iActiveSource);

    if((CAudioEnums::SRC_TUNER_FM == m_iActiveSource || CAudioEnums::SRC_TUNER_AM == m_iActiveSource) && (m_pEnggModelTestModeTuner != nullptr))
    {
        QString strTunerMode = ((CAudioEnums::SRC_TUNER_FM == m_iActiveSource) ? tr("TEXT_ENGG_MENU_TESTMODE_TUNER_FM") : tr("TEXT_ENGG_MENU_TESTMODE_TUNER_AM")) ;
        m_pEnggModelEnggMain->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TEST_MODE, strTunerMode, CEnggMenuListModel::ENGG_MENU_ITEM_MAIN_TEXT_ROLE);
    }

    else if((CAudioEnums::SRC_USB1 == m_iActiveSource) && (CMediaEnum::EMediaBrowseItem::BROWSEITEM_VIDEOS == m_iCurrentTestMode) && (m_pEnggModelTestModeVideoMedia != nullptr))
    {
        m_pEnggModelEnggMain->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TEST_MODE, tr("TEXT_ENGG_MENU_TESTMODE_VIDEO_MEDIA"), CEnggMenuListModel::ENGG_MENU_ITEM_MAIN_TEXT_ROLE);
    }

    else if(((CAudioEnums::SRC_AUDIO_AUX == m_iActiveSource) || (CAudioEnums::SRC_BT_A2DP1 == m_iActiveSource)
             || (CAudioEnums::SRC_USB1 == m_iActiveSource)|| (CAudioEnums::SRC_IPOD == m_iActiveSource)) &&
            (m_pEnggModelTestModeAudioMedia != nullptr))
    {
        QString strTestModeTitle;
        switch (m_iActiveSource)
        {
        case CAudioEnums::SRC_AUDIO_AUX :
            strTestModeTitle = tr("TEXT_ENGG_MENU_TESTMODE_AUDIO_MEDIA_AUX");
            break;

        case CAudioEnums::SRC_BT_A2DP1 :
            strTestModeTitle = tr("TEXT_ENGG_MENU_TESTMODE_AUDIO_MEDIA_BT");
            break;

        case CAudioEnums::SRC_USB1 :
            strTestModeTitle = tr("TEXT_ENGG_MENU_TESTMODE_AUDIO_MEDIA_USB");
            break;

        case CAudioEnums::SRC_IPOD :
            strTestModeTitle = tr("TEXT_ENGG_MENU_TESTMODE_AUDIO_MEDIA_IPOD");
            break;

        default:
            strTestModeTitle = "";
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: No appropriate Audio Media Found", __FUNCTION__);
        }

        m_pEnggModelEnggMain->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TEST_MODE, strTestModeTitle, CEnggMenuListModel::ENGG_MENU_ITEM_MAIN_TEXT_ROLE);
    }
    else
    {
        //[todo] This will be modified as per the media off screen discussion
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeTuner or m_pEnggModelTestModeAudioMedia or m_pEnggModelTestModeVideoMedia is null");
        m_pEnggModelEnggMain->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TEST_MODE, false, CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
        m_pEnggModelEnggMain->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TEST_MODE, tr("TEXT_ENGG_MENU_TESTMODE"), CEnggMenuListModel::ENGG_MENU_ITEM_MAIN_TEXT_ROLE);
    }

    /**
      * While on Test Mode screen if the user switches active source, the test mode model shall change as per the active source.
      * Thus refreshing the engg menu model.
     **/
    if(CEnggMenuEnum::ENGG_MENU_SCREEN_TEST_MODE == m_eEnggMenuCurrentScreen)
    {
        setAdaptorEnggMenuModel(CEnggMenuEnum::ENGG_MENU_SCREEN_TEST_MODE);
    }
}

void CEnggAdaptor::sltSongTitleChanged()
{
    const QString &strSongTitle = CMediaAdaptor::getInstance().songTitle();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Track name: %s", __FUNCTION__,(strSongTitle.toStdString()).c_str());
    if ((m_pEnggMenuCurrentListModel == m_pEnggModelTestModeAudioMedia) && (m_pEnggMenuCurrentListModel))
    {
        m_pEnggModelTestModeAudioMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_AUDIO_TRACK_NAME, strSongTitle, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else if((m_pEnggMenuCurrentListModel == m_pEnggModelTestModeVideoMedia) && (m_pEnggMenuCurrentListModel))
    {
        m_pEnggModelTestModeVideoMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_TRACK_NAME, strSongTitle, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeAudioMedia or  m_pEnggModelTestModeVideoMedia is null");
    }
}

void CEnggAdaptor::sltBitRateChanged()
{
    const QString &strBitRate = CMediaAdaptor::getInstance().bitRate();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Bit Rate: %s", __FUNCTION__,(strBitRate.toStdString()).c_str());
    if (m_pEnggModelTestModeAudioMedia)
    {
        m_pEnggModelTestModeAudioMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_AUDIO_BIT_RATE, strBitRate, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeAudioMedia is null");
    }
}

void CEnggAdaptor::sltSamplingRateChanged()
{
    const QString &strSamplingRate = CMediaAdaptor::getInstance().samplingRate();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Sampling Rate: %s", __FUNCTION__,(strSamplingRate.toStdString()).c_str());
    if (m_pEnggModelTestModeAudioMedia)
    {
        m_pEnggModelTestModeAudioMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_AUDIO_SAMPLING_RATE, strSamplingRate, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeAudioMedia is null");
    }
}
//____________________________________________________________________________

void CEnggAdaptor::sltPowerModeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);

    CVersionManagerEnums::EPowerModeType ePowerModeType = CVersionManagerAdaptor::getInstance()->getPowerModeType();
    QString strPowerModeType = "";

    if (CVersionManagerEnums::TYPE_POWER_MODE_IGN_ON == ePowerModeType){
        strPowerModeType = tr("TEXT_ENGG_SYSTEM_CONFIG_POWER_MODE_STATUS_ING");
    }
    else if(CVersionManagerEnums::TYPE_POWER_MODE_PEPS == ePowerModeType){
        strPowerModeType = tr("TEXT_ENGG_SYSTEM_CONFIG_POWER_MODE_STATUS_PEPS");
    }
    else{
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Invalid Power Mode received", __FUNCTION__ );
    }

    if (m_pEnggModelSysConfig)
    {
        m_pEnggModelSysConfig->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_CURRENT_POWER_MODE_TYPES,
                                                   strPowerModeType, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelSysConfig is null");
    }

}

void CEnggAdaptor::sltSWCConnectionStatusChanged()
{
    CDiagnosticEnum::EConnectionStatus eSWCConnectionStatus = CDiagnosticAdaptor::getInstance()->swcConnectionStatus();
    QString strSWCConnectionStatus = "";

    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: SWC connected status: %d", __FUNCTION__, eSWCConnectionStatus);

    switch(eSWCConnectionStatus)
    {
    case(CDiagnosticEnum::CONNECTED):
    {
        strSWCConnectionStatus = tr("TEXT_ENGG_SYSTEM_CONFIG_STATUS_CONNECTED");
    }
        break;
    case(CDiagnosticEnum::DISCONNECTED):
    {
        strSWCConnectionStatus = tr("TEXT_ENGG_SYSTEM_CONFIG_STATUS_DISCONNECTED");
    }
        break;
    case(CDiagnosticEnum::UNKNOWN):
    {
        strSWCConnectionStatus = tr("TEXT_ENGG_SYSTEM_CONFIG_STATUS_NOT_AVAILABLE");
    }
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: No Connection Status found", __FUNCTION__);
        break;
    }

    if (m_pEnggModelSysConfig)
    {
        m_pEnggModelSysConfig->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_STEERING_WHEEL_CONTROLS, strSWCConnectionStatus,
                                                   CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelSysConfig is null");
    }
}



void CEnggAdaptor::sltMICConnectionStatusChanged()
{
    CDiagnosticEnum::EConnectionStatus eMICConnectionStatus =CDiagnosticAdaptor::getInstance()->micConnectionStatus();
    QString strMICConnectionStatus = "";

    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: SWC connected status: %d", __FUNCTION__, eMICConnectionStatus);

    switch(eMICConnectionStatus)
    {
    case(CDiagnosticEnum::CONNECTED):
    {
        strMICConnectionStatus = tr("TEXT_ENGG_SYSTEM_CONFIG_STATUS_CONNECTED");
    }
        break;
    case(CDiagnosticEnum::DISCONNECTED):
    {
        strMICConnectionStatus = tr("TEXT_ENGG_SYSTEM_CONFIG_STATUS_DISCONNECTED");
    }
        break;
    case(CDiagnosticEnum::UNKNOWN):
    {
        strMICConnectionStatus = tr("TEXT_ENGG_SYSTEM_CONFIG_STATUS_NOT_AVAILABLE");
    }
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: No Connection Status found", __FUNCTION__);
        break;
    }


    if (m_pEnggModelSysConfig)
    {
        m_pEnggModelSysConfig->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_MICROPHONE, strMICConnectionStatus, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelSysConfig is null");
    }
}

void CEnggAdaptor::updateSysConfigAntennaType()
{
    QString strAntennaType = "";
    CVariantControlEnum::EAntennaType eAntennaType = CVariantControlEnum::ANTENNA_TYPE_INVALID;
    if(CVariantControlAdaptor::getInstance())
    {
        eAntennaType = CVariantControlAdaptor::getInstance()->antennaType();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: CVariantControlAdaptor is Null", __FUNCTION__);
    }

    if(CVariantControlEnum::ANTENNA_TYPE_ACTIVE == eAntennaType)
    {
        strAntennaType = tr("TEXT_ENGG_SYSTEM_CONFIG_ANTENNA_STATUS_ACTIVE");
    }
    else if(CVariantControlEnum::ANTENNA_TYPE_PASSIVE == eAntennaType)
    {
        strAntennaType = tr("TEXT_ENGG_SYSTEM_CONFIG_ANTENNA_STATUS_PASSIVE");
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Antenna Type Not Valid", __FUNCTION__);
    }

    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Antenna type: %s", __FUNCTION__, strAntennaType.toStdString().c_str());
    if (m_pEnggModelSysConfig)
    {
        m_pEnggModelSysConfig->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_AM_FM_ANTENNA_TYPES, strAntennaType, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelSysConfig is null");
    }
}

void CEnggAdaptor::sltVehicleSpeedChanged()
{
    float fVehicleSpeedValue = CVehicleSettingsAdaptor::getInstance()->fVehicleSpeed ();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Vehicle speed: %f", __FUNCTION__, fVehicleSpeedValue);
    if(m_pEnggMenuCurrentListModel == m_pEnggModelTestModeTuner)
    {
        m_pEnggModelTestModeTuner->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_TUNER_VEHICLE_SPEED, fVehicleSpeedValue, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else if(m_pEnggMenuCurrentListModel == m_pEnggModelTestModeAudioMedia)
    {
        m_pEnggModelTestModeAudioMedia-> updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_AUDIO_VEHICLE_SPEED, fVehicleSpeedValue, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else if(m_pEnggMenuCurrentListModel == m_pEnggModelTestModeVideoMedia)
    {
        m_pEnggModelTestModeVideoMedia-> updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_VEHICLE_SPEED, fVehicleSpeedValue, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "Current model is not m_pEnggModelTestModeAudioMedia or m_pEnggModelTestModeVideoMedia or m_pEnggModelTestModeTuner");
    }
}


void CEnggAdaptor::updateDebugLogsStatusToService()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    // Enable the Debug Logs List Button when Engg menu Service is available.
    m_pEnggModelEnggMain->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_DEBUG_LOGS, true, CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);

    bool bTestAutomationStatus = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_ENGG_MENU_TEST_AUTOMATION);
    toggleEnggDebugCheckbox(bTestAutomationStatus, CEnggMenuEnum::ENGG_MENU_ID_TEST_AUTOMATION);

    bool bStaticIpStatus = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_ENGG_STATIC_IP_SELECTION);
    toggleEnggDebugCheckbox(bStaticIpStatus, CEnggMenuEnum::ENGG_MENU_ID_STATIC_IP);

    bool bDebugLogsStatus = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_ENGG_DEBUG_LOGS_SELECTION);
    toggleEnggDebugCheckbox(bDebugLogsStatus, CEnggMenuEnum::ENGG_MENU_ID_DEBUGS_LOG);

    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bTestAutomationStatus: %d, bStaticIpStatus: %d, bDebugLogsStatus: %d", __FUNCTION__, bTestAutomationStatus, bStaticIpStatus, bDebugLogsStatus);
}

void CEnggAdaptor::updateEnggMenuParametersOnProxyAvailability(bool bIsEnggMenuProxyAvailable)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: bIsEnggMenuProxyAvailable: %d", __FUNCTION__, bIsEnggMenuProxyAvailable);

    if(m_bIsEnggMenuProxyAvailable != bIsEnggMenuProxyAvailable)
    {
        m_bIsEnggMenuProxyAvailable = bIsEnggMenuProxyAvailable;
        emit sigEnggMenuProxyStatusChanged();

        if(m_bIsEnggMenuProxyAvailable)
        {
            updateDebugLogsStatusToService();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: EnggProxy is not available, do not update debug logs status to service.", __FUNCTION__);
            // Disable the Debug Logs List Button when Engg menu Service is not available.
            m_pEnggModelEnggMain->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_DEBUG_LOGS, false, CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);

        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: EnggProxyStatus is same as previous.", __FUNCTION__);
    }
}

void CEnggAdaptor::sltVideoCodecChanged()
{
    QString strVideoCodec =  CMediaAdaptor::getInstance().videoCodec();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s,Video Codec:%s",__FUNCTION__,(strVideoCodec.toStdString()).c_str());
    if (m_pEnggModelTestModeVideoMedia)
    {
        m_pEnggModelTestModeVideoMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_VIDEO_CODEC, strVideoCodec, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeVideoMedia is null");
    }
}

void CEnggAdaptor::sltVideoFrameRateChanged()
{
    QString strVideoFrameRate =  CMediaAdaptor::getInstance().videoFrameRate();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s,Video Frame rate:%s",__FUNCTION__,(strVideoFrameRate.toStdString()).c_str());
    if (m_pEnggModelTestModeVideoMedia)
    {
        m_pEnggModelTestModeVideoMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_VIDEO_FRAME_RATE, strVideoFrameRate, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeVideoMedia is null");
    }
}

void CEnggAdaptor::sltVideoResolutionChanged()
{
    QString strVideoResolution =  CMediaAdaptor::getInstance().videoResolution();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s,Video Resolution:%s",__FUNCTION__,(strVideoResolution.toStdString()).c_str());
    if (m_pEnggModelTestModeVideoMedia)
    {
        m_pEnggModelTestModeVideoMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_VIDEO_RESOLUTION, strVideoResolution, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeVideoMedia is null");
    }
}

void CEnggAdaptor::sltMediaFormatChanged()
{
    QString strMediaFormat =  CMediaAdaptor::getInstance().mediaFormat();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Media Format: %s", __FUNCTION__, (strMediaFormat.toStdString()).c_str());
    if (m_pEnggModelTestModeVideoMedia)
    {
        m_pEnggModelTestModeVideoMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_VIDEO_FORMAT, strMediaFormat, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeVideoMedia is null");
    }
}

void CEnggAdaptor::sltAudioSamplingRateChanged()
{
    QString strAudioSamplingRate =  CMediaAdaptor::getInstance().audioSamplingRate();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s,Audio sampling rate:%s",__FUNCTION__,(strAudioSamplingRate.toStdString()).c_str());
    if (m_pEnggModelTestModeVideoMedia)
    {
        m_pEnggModelTestModeVideoMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_AUDIO_SAMPLING_RATE, strAudioSamplingRate, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeVideoMedia is null");
    }
}

void CEnggAdaptor::sltAudioCodecChanged()
{
    QString strAudioCodec =  CMediaAdaptor::getInstance().audioCodec();
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s,Audio codec:%s",__FUNCTION__,(strAudioCodec.toStdString()).c_str());
    if (m_pEnggModelTestModeVideoMedia)
    {
        m_pEnggModelTestModeVideoMedia->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_VIDEO_AUDIO_CODEC, strAudioCodec, CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE );
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "m_pEnggModelTestModeVideoMedia is null");
    }
}

void CEnggAdaptor::setExtractLogsStatus(CEnggMenuEnum::EEnggMenuExtractLogsStatus eExtractLogsProcessStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: eExtractLogsProcessStatus: %d", __FUNCTION__, eExtractLogsProcessStatus);

    /**
      * Enable the Extract Logs List Button Item when i receives the callback.
     */
    m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_EXTRACT_LOG, true, CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);

    switch(eExtractLogsProcessStatus)
    {

    case CEnggMenuEnum::USB_NOT_CONNECTED:
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_ENGGMENU_USB_NOT_CONNECTED);
        break;

    case CEnggMenuEnum::USB_DEVICE_FULL:
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_ENGGMENU_USB_DEVICE_FULL);
        break;

    case CEnggMenuEnum::LOGGING_NOT_ENABLED:
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_ENGGMENU_LOGGING_NOT_ENABLED);
        break;

    case CEnggMenuEnum::LOGS_SUCCESS:
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Extraction of Logs Successful", __FUNCTION__);
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Invalid extract logs status", __FUNCTION__);
        break;
    }

    //TODO: For time being, Change the value of this Extract Logs button to empty string.
    m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_EXTRACT_LOG, "", CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE);

}

QString CEnggAdaptor::getInfotainmentPlatformName()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    QString strInfotainmentPlatform = "";
    switch(eVIP_DID)
    {
    case CVariantControlEnum::EVIP_DID::VIP_DID_HU_TIAGO_7INCH:
    {
        strInfotainmentPlatform = tr("TEXT_NAME_VIP_DID_TIAGO_7INCH");
    }
        break;
    case CVariantControlEnum::EVIP_DID::VIP_DID_HU_HEXA_7_VAVE:
    {
        strInfotainmentPlatform = tr("TEXT_NAME_VIP_DID_HEXA_HU_7_VAVE");
    }
        break;
    case CVariantControlEnum::EVIP_DID::VIP_DID_HU_NEXON_LEVEL_B_VAVE:
    {
        strInfotainmentPlatform = tr("TEXT_NAME_VIP_DID_NEXON_LEVEL_B_VAVE");
    }
        break;
    case CVariantControlEnum::EVIP_DID::VIP_DID_HU_HIGH_X451:
    {
        strInfotainmentPlatform = tr("TEXT_NAME_VIP_DID_HU_HIGH_X451");
    }
        break;
    case CVariantControlEnum::EVIP_DID::VIP_DID_HU_HIGH_X445:
    {
        strInfotainmentPlatform = tr("TEXT_NAME_VIP_DID_HU_HIGH_X445");
    }
        break;
    case CVariantControlEnum::EVIP_DID::VIP_DID_HU_NEXON_EV_HIGH:
    {
        strInfotainmentPlatform = tr("TEXT_NAME_VIP_DID_HU_NEXON_EV_HIGH");
    }
        break;
    case CVariantControlEnum::EVIP_DID::VIP_DID_HU_TIGOR_7:
    {
        strInfotainmentPlatform = tr("TEXT_NAME_VIP_DID_TIGOR_7INCH");
    }
        break;
    case CVariantControlEnum::EVIP_DID::VIP_DID_HU_NEXON_MCE:
    {
        strInfotainmentPlatform = tr("TEXT_NAME_VIP_DID_NEXON_MCE");
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s Name not defined for eVIP_DID:%d", __FUNCTION__, static_cast<int>(eVIP_DID));
        strInfotainmentPlatform = QString::number(static_cast<int>(eVIP_DID));
    }
        break;
    }
    return strInfotainmentPlatform;
}

void CEnggAdaptor::startExtractingDebugsLogToUsb()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    if(m_pEnggMenuResource)
    {
        if(m_pEnggModelDebugLog)
        {
            m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_EXTRACT_LOG, tr("Extracting..."), CEnggMenuListModel::ENGG_MENU_ITEM_SUB_TEXT_ROLE);
            m_pEnggModelDebugLog->updateEnggMenuModel(CEnggMenuEnum::ENGG_MENU_ID_EXTRACT_LOG, false, CEnggMenuListModel::ENGG_MENU_ITEM_ENABLE_STATUS_ROLE);
            m_pEnggMenuResource->extractDebugLogs();
        }

        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: m_pEnggModelDebugLog is null", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Engineering menu resource not available", __FUNCTION__);
    }
}

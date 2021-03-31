/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupAdaptor.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupAdaptor.cpp, setup module adaptor cpp file, responsible for creating setup
 *                  list model class instances and contains current active model of setup
 */

#include "CSetupAdaptor.h"
#include "CParkAssistAdaptor.h"
#include "CVehicleSettingsAdaptor.h"
#include "CHVACAdaptor.h"
#include "CPersistencyAdaptor.h"
#include "CThemeManager.h"
#include "CThemeManagerEnums.h"
#include "CDisplayManagerAdaptor.h"
#include "CVoiceAlertsAdaptor.h"
#include "CAppleCarPlayAdaptor.h"
#include "CHVACAdaptor.h"
#include "CSetupEnums.h"
#include "CDriveNextApplication.h"
#include "CDriveNextAdaptor.h"

CSetupAdaptor* CSetupAdaptor::m_pSetupAdaptor = nullptr;

CSetupAdaptor::CSetupAdaptor(QObject *parent):
    QObject(parent),
    /*Note: TATA X451 and X104 Vave project */
    m_pCurrentModel(nullptr),
    m_pSetupMainListModel(nullptr),
    m_pSetupAudioListModel(nullptr),
    m_pSetupBMTListModel(nullptr),
    m_pSetupAudioPresetListModel(nullptr),
    m_pSetupGeneralListModel(nullptr),
    m_pSetupVolumeSettingsListModel(nullptr),
    m_pSetupVehicleSettingsListModel(nullptr),
    m_pSetupVehicleListModel(nullptr),
    m_pSetupParkAssistListModel(nullptr),
    m_pSetupLightingListModel(nullptr),
    m_pSetupDriveNextListModel(nullptr),
    m_pSetupDelayTimerModel(nullptr),
    m_pSetupParkAssistToneModel(nullptr),
    m_pSetupAproachLampsModel(nullptr),
    m_pSetupThemeListModel(nullptr),
    m_pThemeSettingsModel(nullptr),
    m_pAudioSettingsModel(nullptr),
    m_pEditModeThemeElement(nullptr),
    m_pThemeElement(nullptr),
    m_bEditModeFlag(false),
    m_iPresetSelected(-1),
    // TATA_X104_High_VAVE specific code
    m_pThemeSetupWithDriveModeListModel(nullptr),
    m_bChangeThemeWithDriveModeStatus(false),
    m_eActiveDriveMode(CSetupEnums::DRIVE_MODE_INVALID),
    // TATA_X104_High_VAVE specific code end
    m_eCurrThemeColor(CSetupEnums::THEME_INVALID),
    m_iCurActiveThemePreset(-1),
    m_bThemeLoadingStatus(false),
    m_strActiveThemePresetText(""),
    m_strActiveThemePresetIcon(""),
    m_bIsThemeItemExpanded(false),
    m_iExpandedThemeItemIndex(-1),
    m_iExpandedParkAssistItemIndex(-1),
    m_iExpandedApproachLampsItemIndex(-1),
    m_bIsCurrentThemeModified(false),
    m_iApproachLampIndex(-1),
    m_eAudioSetupCurrentScreen(CSetupEnums::AUDIOSETUP_NONE),
    m_iVoiceAlertIndex(-1),
    m_iSmartFanIndex(-1),
    m_iDriveNextIndex(-1),
    m_iBcmDrlIndex(-1),
    m_bIsClimatePopupShown(false)
{
    m_pSetupAdaptor = this;
    setCurActiveThemePreset(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SETUP_THEME_PRESET));

    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: eVIP_DID: %d", __FUNCTION__, eVIP_DID);
    if (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID || CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID)
    {
        // TATA_X104_High_VAVE specific code
        setActiveDriveMode(CSetupEnums::DRIVE_MODE_CITY);
        setChangeThemeWithDriveModeStatus(static_cast<bool>(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_CHANGE_THEME_WITH_DRIVE_MODE_STATUS)));
        invApplyThemeColor(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_HMI_THEME_SELECTION));
        m_pThemeSetupWithDriveModeListModel = new CThemeSetupWithDriveModeListModel(this);
    }

    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, " %s, Current Active Theme Preset : %d", __FUNCTION__, m_iCurActiveThemePreset);

    m_iPresetSelected = m_iCurActiveThemePreset;

    m_pSetupMainListModel = new CSetupMainListModel(this);
    /* Main setup model is set as default model */
    m_pCurrentModel = m_pSetupMainListModel;
    m_pSetupAudioListModel = new CSetupAudioListModel(this);
    m_pSetupBMTListModel = new CSetupBMTListModel(this);
    m_pSetupAudioPresetListModel = new CSetupAudioPresetListModel(this);
    m_pSetupGeneralListModel = new CSetupGeneralListModel(this);
    m_pSetupVolumeSettingsListModel = new CSetupVolumeSettingsListModel(this);

    m_pThemeSettingsModel = new CThemeSettingsModel(this);

    m_pAudioSettingsModel = new CAudioSettingsModel(this);

    m_pSetupVehicleSettingsListModel = new CSetupListModel(this);

    m_pSetupLightingListModel  = new CSetupListModel(this);

    m_pSetupDriveNextListModel = new CSetupListModel(this);

    m_pSetupVehicleListModel = new CSetupListModel(this);
    m_pSetupParkAssistListModel = new CSetupListModel(this);
    m_pSetupAproachLampsModel = new CSetupListModel(this);
    m_pSetupDelayTimerModel = new CSetupListModel(this);
    m_pSetupParkAssistToneModel = new CSetupListModel(this);
    m_pSetupThemeListModel = new CSetupListModel(this);

    /* Here theme element is being initialized with default parameters */
    m_pEditModeThemeElement = new CThemeElement(0, 0, 1, 1, 20, 1, 0, 0, 0, 0, 0);

    initSetupListModels();

    CFramework::getFramework().setContextProperty("cppSetupAdaptor", this);
    connectSignals();

    /*Here this method is called to update the current active theme preset and to show that in drawers */
    updateCurActiveThemePreset();

    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Preset value: %d ", __FUNCTION__, m_iPresetSelected);

    clearReqState();
}

CSetupAdaptor::~CSetupAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    if(m_pSetupAdaptor)
    {
        delete m_pSetupAdaptor;
        m_pSetupAdaptor = nullptr;
    }

    if(m_pAudioSettingsModel)
    {
        delete m_pAudioSettingsModel;
        m_pAudioSettingsModel = nullptr;
    }

    if(m_pSetupMainListModel)
    {
        delete m_pSetupMainListModel;
        m_pSetupMainListModel = nullptr;
    }
    if(m_pSetupAudioListModel)
    {
        delete m_pSetupAudioListModel;
        m_pSetupAudioListModel = nullptr;
    }
    if(m_pSetupBMTListModel)
    {
        delete m_pSetupBMTListModel;
        m_pSetupBMTListModel = nullptr;
    }
    if(m_pSetupAudioPresetListModel)
    {
        delete m_pSetupAudioPresetListModel;
        m_pSetupAudioPresetListModel = nullptr;
    }
    if(m_pSetupGeneralListModel)
    {
        delete m_pSetupGeneralListModel;
        m_pSetupGeneralListModel = nullptr;
    }
    if(m_pSetupVehicleSettingsListModel)
    {
        delete m_pSetupVehicleSettingsListModel;
        m_pSetupVehicleSettingsListModel = nullptr;
    }
    if(m_pSetupLightingListModel)
    {
        delete m_pSetupLightingListModel;
        m_pSetupLightingListModel = nullptr;
    }
    if(m_pSetupDriveNextListModel)
    {
        delete m_pSetupDriveNextListModel;
        m_pSetupDriveNextListModel = nullptr;
    }
    if(m_pSetupThemeListModel)
    {
        delete m_pSetupThemeListModel;
        m_pSetupThemeListModel = nullptr;
    }
    if(m_pEditModeThemeElement)
    {
        delete m_pEditModeThemeElement;
        m_pEditModeThemeElement = nullptr;
    }
    if(m_pCurrentModel)
    {
        m_pCurrentModel = nullptr;
    }

    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID || CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID)
    {
        // TATA_X104_High_VAVE specific code
        if(m_pThemeSetupWithDriveModeListModel)
        {
            delete m_pThemeSetupWithDriveModeListModel;
            m_pThemeSetupWithDriveModeListModel = NULL;
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: Theme Setup With Drive Mode list model instance already destroyed", __FUNCTION__);
        }
    }

    qDeleteAll(m_lThemeElementsList.begin(), m_lThemeElementsList.end());
    m_lThemeElementsList.clear();

}

CSetupAdaptor* CSetupAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    if(nullptr == m_pSetupAdaptor)
    {
        new CSetupAdaptor();
    }
    return m_pSetupAdaptor;
}

void CSetupAdaptor::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    connect(CEnggAdaptor::getInstance(), SIGNAL(sigFactoryResetWaitingStatusChanged(bool)), this, SLOT(slotFactoryResetWaitingStatusChanged(bool)), Qt::QueuedConnection);
    connect(CEnggAdaptor::getInstance(), SIGNAL(sigFactoryResetCompletionStatusChanged(bool)), this, SLOT(slotFactoryResetCompletionStatusChanged(bool)), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigPdcMixModeStatusChanged()), this, SLOT(sltPdcMixModeStatusChanged()), Qt::QueuedConnection);
    connect(CParkAssistAdaptor::getInstance(), SIGNAL(sigParkAssistVolumeChanged()), this, SLOT(sltParkAssistVolumeChanged()), Qt::QueuedConnection);
    connect(CParkAssistAdaptor::getInstance(), SIGNAL(sigParkAssistDelayTimerChanged()), this, SLOT(sltParkAssistDelayTimerChanged()), Qt::QueuedConnection);
    connect(CParkAssistAdaptor::getInstance(), SIGNAL(sigParkAssistRearToneChanged()), this, SLOT(sltParkAssistRearToneChanged()), Qt::QueuedConnection);
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigAppraochLampsChanged()), this, SLOT(sltAppraochLampsChanged()),Qt::QueuedConnection);
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigVehicleAutoRelockChanged()), this, SLOT(sltVehicleAutoRelockChanged()), Qt::QueuedConnection);

    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigDriveNextPresenceChanged()),this,SLOT(sltDriveNextElementsChanged()), Qt::QueuedConnection);
    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigDriveNextResetPresenceChanged()),this,SLOT(sltDriveNextElementsChanged()), Qt::QueuedConnection);
    connect(CDriveNextApplication::getDriveNextAdaptor(),SIGNAL(sigResetTripStatusChanged()),this,SLOT(sltDriveNextElementsChanged()), Qt::QueuedConnection);

    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if (!(CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID || CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        connect(&CThemeManager::getThemeManager(), SIGNAL(sigCurrentThemeTypeChanged()), this, SLOT(sltCurrentThemeTypeChanged()), Qt::QueuedConnection);
    }
    connect(CParkAssistAdaptor::getInstance(), SIGNAL(sigPdcPresenceChanged()), this, SLOT(sltPdcPresenceChanged()), Qt::QueuedConnection);
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigBcmUcsStateChanged()), this, SLOT(sltBcmUcsStateChanged()), Qt::QueuedConnection);
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigAppraochLampsPresenceChanged()), this, SLOT(sltAppraochLampsPresenceChanged()), Qt::QueuedConnection);
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigAmbientLightModeIlluOnHuChanged()), this, SLOT(sltAmbientLightModeIlluOnHuChanged()), Qt::QueuedConnection);
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigBCMPresenceChanged()), this, SLOT(sltBCMPresenceChanged()), Qt::QueuedConnection);
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigBcmDrlFeaturePresenceStatusChanged()), this, SLOT(sltBcmDrlFeaturePresenceStatusChanged()), Qt::QueuedConnection);
    connect(&CVoiceAlertsAdaptor::getInstance(), SIGNAL(sigVoiceAlertSelectionChanged()), this, SLOT(sltVoiceAlertSelectionChanged()), Qt::QueuedConnection);
    connect(&CVoiceAlertsAdaptor::getInstance(), SIGNAL(sigVoiceAlertPresenceChanged()), this, SLOT(sltVoiceAlertPresenceChanged()), Qt::QueuedConnection);

    connect(CHVACAdaptor::getInstance(),            SIGNAL(sigFanSpeedChanged           ()), this, SLOT(sltFanSpeedChanged          ()));
    connect(CHVACAdaptor::getInstance(),            SIGNAL(sigTemperatureChanged        ()), this, SLOT(sltTemperatureChanged       ()));
    connect(CHVACAdaptor::getInstance(),            SIGNAL(sigDriverTempChanged         ()), this, SLOT(sltTemperatureChanged       ()));

    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigAmbLightIlluSelLevelChanged ()), this, SLOT(sltAmbLightIllumLevelChanged()));
    connect(CAudioAdaptor::getInstance(),           SIGNAL(sigActiveAudioPresetChanged  ()), this, SLOT(sltActiveAudioPresetChanged ()), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(),           SIGNAL(sigVoiceAlertVolumeChanged   ()), this, SLOT(sltVoiceAlertVolumeChanged  ()), Qt::QueuedConnection);

    connect(CHVACAdaptor::getInstance(), SIGNAL(sigCCMPresenceChanged()), this, SLOT(sltCCMPresenceChanged()), Qt::QueuedConnection);

    connect(CAppleCarPlayAdaptor::getInstance(), SIGNAL(sigSmartFanStateChanged(bool)), this, SLOT(sltSmartFanStateChanged()), Qt::QueuedConnection);
    connect(CAppleCarPlayAdaptor::getInstance(), SIGNAL(sigAppleCarPlayConnectionStatusChanged(bool)), this, SLOT(sltCPConnectionStatusUpdated(bool)), Qt::QueuedConnection);

    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigBcmDrlSelectionStatusChanged()), this, SLOT(sltBcmDrlSelectionStateChanged()), Qt::QueuedConnection);
    connect(CDisplayManagerAdaptor::getInstance(), SIGNAL(sigNightModeStatusChanged()), this, SLOT(sltNightModeStatusChanged()), Qt::QueuedConnection);

    connect(CHVACAdaptor::getInstance(), SIGNAL(sigErrorStatusChanged()), this, SLOT(sltErrorStatusChanged()), Qt::QueuedConnection);

    /*FixMe: Need clarifiaction from TML hence for now this code is commented */
    //connect(CHVACAdaptor::getInstance(), SIGNAL(sigCtrlPanelModeChanged()), this, SLOT(sltCtrlPanelModeChanged()), Qt::QueuedConnection);
    //connect(&(CPowerModeAdaptor::getInstance()), SIGNAL(sigPowerModeChanged()), this, SLOT(sltPowerModeChanged()), Qt::QueuedConnection);
    //connect(CDisplayManagerAdaptor::getInstance(), SIGNAL(sigNightModeStatusChanged()), this, SLOT(sltParkLampStatusChanged()), Qt::QueuedConnection);

    ////connect signals to handle vehicle setup element changed.
    connect(&(CPowerModeAdaptor::getInstance()),    SIGNAL(sigPowerModeChanged()),                          this,   SLOT(sltVehicleSetupElementsChanged()),     Qt::QueuedConnection);
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigBCMPresenceChanged()),                        this,   SLOT(sltVehicleSetupElementsChanged()),     Qt::QueuedConnection);
    connect(CVehicleSettingsAdaptor::getInstance(), SIGNAL(sigBcmUcsStateChanged()),                        this,   SLOT(sltVehicleSetupElementsChanged()),     Qt::QueuedConnection);
    connect(CHVACAdaptor::getInstance(),            SIGNAL(sigCCMPresenceChanged()),                        this,   SLOT(sltVehicleSetupElementsChanged()),     Qt::QueuedConnection);
    connect(&CVoiceAlertsAdaptor::getInstance(),    SIGNAL(sigVoiceAlertPresenceChanged()),                 this,   SLOT(sltVehicleSetupElementsChanged()),     Qt::QueuedConnection);
    connect(CAppleCarPlayAdaptor::getInstance(),    SIGNAL(sigAppleCarPlayConnectionStatusChanged(bool)),   this,   SLOT(sltVehicleSetupElementsChanged(bool)), Qt::QueuedConnection);
}

void CSetupAdaptor::factoryResetConfirmClickProcess()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_CONFIRMATION_STATUS);
    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_WAITING_STATUS);
    CEnggAdaptor::getInstance()->startFactoryResetProcess();
    /*Here this method is called to set the theme type to default(blue) when user initiates factory reset */
    CThemeManager::getThemeManager().setThemeType(CThemeManagerEnums::THEME_TYPE_1);
}

QAbstractListModel* CSetupAdaptor::currentModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_pCurrentModel;
}

//ToDo: This needs to changed as param should be passed with screenId enum
void CSetupAdaptor::setCurrentListModel(int screenId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupAdaptor::setCurrentListModel : %d ", screenId);
    switch (screenId)
    {
    case CSetupEnums::SETUP_SCREEN_MAIN:
        m_pCurrentModel = m_pSetupMainListModel;
        break;

    case CSetupEnums::SETUP_SCREEN_AUDIO:
        m_pCurrentModel = m_pSetupAudioListModel;
        break;

    case CSetupEnums::SETUP_SCREEN_BASS_MIDDLE_TREBLE:
        m_pCurrentModel = m_pSetupBMTListModel;
        break;

    case CSetupEnums::SETUP_SCREEN_AUDIO_PRESETS:
        m_pCurrentModel = m_pSetupAudioPresetListModel;
        break;
    case CSetupEnums::SETUP_SCREEN_GENERAL:
        m_pCurrentModel = m_pSetupGeneralListModel;
        break;

    case CSetupEnums::SETUP_SCREEN_VOLUME:
        m_pCurrentModel = m_pSetupVolumeSettingsListModel;
        break;

    case CSetupEnums::SETUP_SCREEN_VEHICLE:
        m_pCurrentModel = m_pSetupVehicleSettingsListModel;
        break;

    case CSetupEnums::SETUP_SCREEN_PARK_ASSIST:
        m_pCurrentModel = m_pSetupParkAssistListModel;
        break;

    case CSetupEnums::SETUP_SCREEN_THEMES:
        m_pCurrentModel = m_pSetupThemeListModel;
        break;

    case CSetupEnums::SETUP_SCREEN_LIGHTING:
        m_pCurrentModel = m_pSetupLightingListModel;
        break;

    case CSetupEnums::SETUP_SCREEN_DRIVENEXT:
        m_pCurrentModel = m_pSetupDriveNextListModel;
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupAdaptor::setCurrentListModel default case");
        break;
    }

    emit sigCurrentModelChanged();
}

QString CSetupAdaptor::getAudioPresetName(CAudioEnums::EAudioPresets eAudioPresets)
{
    return  m_pSetupAudioPresetListModel->getAudioPresetName(eAudioPresets);
}

bool CSetupAdaptor::isVehicleSettingAvailable()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, BCM Presence: %d, BcmUcs state : %d, pdc presence : %d, eolDriveNextEnabled : %d, Ccm Presence : %d, Carplay Connection : %d, Voice Alert : %d",
             __FUNCTION__,
             CVehicleSettingsAdaptor::getInstance()->bCmPresence(),CVehicleSettingsAdaptor::getInstance()->bcmUcsState(),
             CParkAssistAdaptor::getInstance()->pdcPresence(), CVariantControlAdaptor::getInstance()->eolDriveNextEnabled(), CHVACAdaptor::getInstance()->ccmPresence(),
             CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus(),
             CVoiceAlertsAdaptor::getInstance().voiceAlertPresence());

    return ((CVehicleSettingsAdaptor::getInstance()->bCmPresence() && CVehicleSettingsAdaptor::getInstance()->bcmUcsState()) ||
            CParkAssistAdaptor::getInstance()->pdcPresence() ||
            (CVariantControlAdaptor::getInstance()->eolDriveNextEnabled()) ||
            ((CHVACEnums::HVAC_CCM_PRESENT == CHVACAdaptor::getInstance()->ccmPresence()) && CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus()) ||
            CVoiceAlertsAdaptor::getInstance().voiceAlertPresence());
}

QAbstractListModel* CSetupAdaptor::parkAssistDelayTimerSubModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_pSetupDelayTimerModel;
}

QAbstractListModel* CSetupAdaptor::parkAssistToneSubModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_pSetupParkAssistToneModel;
}

QAbstractListModel* CSetupAdaptor::approachLampsSubModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_pSetupAproachLampsModel;
}

QAbstractListModel *CSetupAdaptor::themepresetModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    return m_pThemeSettingsModel;
}

void CSetupAdaptor::initSetupListModels()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    initCustomThemeValues();
    initThemeElementList();
    initThemeSetupListModel();
    initParkAssistListModel();
    initLightingSetupListModel();
}

void CSetupAdaptor::updateVehicleSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Update Vehicle Setup List ", __FUNCTION__);
    /*Note: Here we are calling this function when ever there is change from service saying feature not available
            then we re-initializing the vehicle setup list */
    initVehicleSetupListModel();
}

void CSetupAdaptor::sltPdcPresenceChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Pdc presence status : %d", __FUNCTION__, CParkAssistAdaptor::getInstance()->pdcPresence());
    updateVehicleSetupListModel();
}

void CSetupAdaptor::sltBcmUcsStateChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, BcmUcs status : %d", __FUNCTION__, CVehicleSettingsAdaptor::getInstance()->bcmUcsState());
    updateVehicleSetupListModel();
    updateThemeSetupListModel();
    updateLightingSetupListModel();
}

void CSetupAdaptor::sltAppraochLampsPresenceChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Approach Lamps presence status : %d", __FUNCTION__,
             CVehicleSettingsAdaptor::getInstance()->appraochLampsPresence());
    updateVehicleSetupListModel();
    updateLightingSetupListModel();
}

void CSetupAdaptor::sltAmbientLightModeIlluOnHuChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Ambient Light presence status : %d", __FUNCTION__,
             CVehicleSettingsAdaptor::getInstance()->ambientLightModeIlluOnHu());
    updateVehicleSetupListModel();
    updateThemeSetupListModel();
    updateLightingSetupListModel();
}

void CSetupAdaptor::sltBCMPresenceChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Bcm presence status : %d", __FUNCTION__, CVehicleSettingsAdaptor::getInstance()->bCmPresence());
    updateThemeSetupListModel();
    updateVehicleSetupListModel();
}

void CSetupAdaptor::sltBcmDrlFeaturePresenceStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, DRL presence status : %d", __FUNCTION__, CVehicleSettingsAdaptor::getInstance()->bcmDrlFeature());
    updateLightingSetupListModel();
}

void CSetupAdaptor::sltVoiceAlertPresenceChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Voice alert presence status : %d", __FUNCTION__, CVoiceAlertsAdaptor::getInstance().voiceAlertPresence());
    updateVehicleSetupListModel();
}

void CSetupAdaptor::sltVehicleSetupElementsChanged(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s bStatus:%d", __FUNCTION__, bStatus);
    sltVehicleSetupElementsChanged();
}

void CSetupAdaptor::sltVehicleSetupElementsChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    bool bSwitchBackToMainSetup = false;
    if ((CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_Setup_setup_region_VehicleSetup))
            || (CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_Setup_setup_region_DriveNextSetup))
            //FixMe Need to handle All below states
            //|| (CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_Setup_setup_region_ParkAssist)) handled in ParkAssistScreen.qml
            //|| (CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_Setup_setup_region_LightingSetup)) handled in LightingSetupScreen.qml, AmbientLightDelegate.qml
            //|| (CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_Setup_setup_region_MoodLighting)) handled in AmbientLightingScreen.qml
            )
    {
        if(CPowerModeEnums::eVehiclePowerModes::VPM_ONE_HOUR == CPowerModeAdaptor::getInstance().getPowerModeStatus())
        {
            bSwitchBackToMainSetup = true;
        }
        else if(!isVehicleSettingAvailable())
        {
            bSwitchBackToMainSetup = true;
        }
        else
        {
            //Do Nothing!
        }
    }
    else
    {
        //Do Nothing!
    }

    if (bSwitchBackToMainSetup)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS," %s, Switch screen to Main Setup", __FUNCTION__);
        CHMIMain::getSM()->raise_evSetupActivated();
    }
    else
    {
        //Do Nothing!
    }
}

void CSetupAdaptor::sltCCMPresenceChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    /*Note : Here we are collapsing the theme item if expanded before inserting an item in the list */
    if(m_bIsThemeItemExpanded)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, m_bIsThemeItemExpanded : %d", __FUNCTION__, m_bIsThemeItemExpanded);
        collapseThemeItem(m_iExpandedThemeItemIndex);
    }

    /** init vehicle setup and theme setup list whenever CCM presence change is received **/
    initVehicleSetupListModel();
    initThemeSetupListModel();
}

void CSetupAdaptor::initVehicleSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, BCM_UCS = %d, Vehi Auto Relock : %d, PDC = %d, AmbLight = %d,"
                                         " Approach Lamps = %d ,voice Alert = %d, Car Play = %d, CCM = %d, DRL = %d, DriveNext = %d",
             __FUNCTION__ ,
             CVehicleSettingsAdaptor::getInstance()->bcmUcsState(),
             CVehicleSettingsAdaptor::getInstance()->vehicleAutoRelockPresence(),
             CParkAssistAdaptor::getInstance()->pdcPresence(),
             CVehicleSettingsAdaptor::getInstance()->ambientLightModeIlluOnHu(),
             CVehicleSettingsAdaptor::getInstance()->appraochLampsPresence(),
             CVoiceAlertsAdaptor::getInstance().voiceAlertPresence(),
             CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus(),
             CHVACAdaptor::getInstance()->ccmPresence(),
             CVehicleSettingsAdaptor::getInstance()->bcmDrlFeature(),
             (CDriveNextApplication::getDriveNextAdaptor() && CDriveNextApplication::getDriveNextAdaptor()->driveNextPresence()));

    if(nullptr != m_pSetupVehicleSettingsListModel)
    {
        /*Note: Here we are calling this method to clear the list before insertion */
        m_pSetupVehicleSettingsListModel->removeRows();

        /*Note: This condition is to check pdc presence status.
                As Pdc feature depends on pdc availabilty in vehicle */
        if(CParkAssistAdaptor::getInstance()->pdcPresence())
        {
            m_pSetupVehicleSettingsListModel->insertElementAt(m_pSetupVehicleSettingsListModel->rowCount(), CSetupData(tr("TEXT_VEHICLE_SETTINGS_PARK_ASSIST"),
                                                                                                                       "", "",CSetupEnums::SETUP_LIST_ITEM_LABEL, /*Enable/Disable*/ true,
                                                                                                                       false, false, -1, -1, -1, CSetupEnums::SETUP_SCREEN_PARK_ASSIST));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s List Item is available ", __FUNCTION__);
        }

        if(CVehicleSettingsAdaptor::getInstance()->bcmUcsState() && CVehicleSettingsAdaptor::getInstance()->bCmPresence())
        {
            if(CVehicleSettingsAdaptor::getInstance()->appraochLampsPresence()
                    || CVehicleSettingsAdaptor::getInstance()->ambientLightModeIlluOnHu()
                    || CVehicleSettingsAdaptor::getInstance()->bcmDrlFeature())
            {
                m_pSetupVehicleSettingsListModel->insertElementAt(m_pSetupVehicleSettingsListModel->rowCount(), CSetupData(tr("TEXT_VEHICLE_SETTINGS_LIGHTING"),
                                                                                                                           "", "", CSetupEnums::SETUP_LIST_ITEM_LABEL, /*Enable/Disable*/ true,
                                                                                                                           false, false, -1, -1, -1, CSetupEnums::SETUP_SCREEN_LIGHTING));
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Appraoch Lamps and Ambient Light both are not available ", __FUNCTION__);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, BCM Presence status : %d, BCM Ucs status : %d", __FUNCTION__,
                     CVehicleSettingsAdaptor::getInstance()->bCmPresence(),
                     CVehicleSettingsAdaptor::getInstance()->bcmUcsState());
        }

        /*Note: This condition is to check voice alert feature presence status.
                As voice alert feature depends on voice alert availabilty in vehicle */
        if(CVoiceAlertsAdaptor::getInstance().voiceAlertPresence())
        {
            m_iVoiceAlertIndex = m_pSetupVehicleSettingsListModel->rowCount();
            m_pSetupVehicleSettingsListModel->insertElementAt(m_pSetupVehicleSettingsListModel->rowCount(), CSetupData(tr("TEXT_SETTINGS_VOICE_ALERTS"),
                                                                                                                       "", "", CSetupEnums::SETUP_LIST_ITEM_CHECK_BOX, /*Enable/Disable*/ true,
                                                                                                                       false, /*Checked/Unchecked*/CVoiceAlertsAdaptor::getInstance().voiceAlertSelection(),
                                                                                                                       -1, -1, -1, CSetupEnums::SETUP_OPTION_VOICE_ALERT));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Voice Alert Feature are not available ", __FUNCTION__);
            m_iVoiceAlertIndex = -1;
        }

        /** To be enabled only if FATC is there and Apple CarPlay device is connected with the system. */
        if((CAppleCarPlayAdaptor::getInstance()->appleCarPlayConnectionStatus() && (CHVACEnums::HVAC_CCM_PRESENT == CHVACAdaptor::getInstance()->ccmPresence())))
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Smart Fan value from persistence during model creation: %d",
                     __FUNCTION__, CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_CP_SMART_FAN_STATE));
            m_iSmartFanIndex = m_pSetupVehicleSettingsListModel->rowCount();
            m_pSetupVehicleSettingsListModel->insertElementAt(m_pSetupVehicleSettingsListModel->rowCount(), CSetupData("Smart Fan","", "", CSetupEnums::SETUP_LIST_ITEM_CHECK_BOX, /*Enable/Disable*/ true,
                                                                                                                       false, /*Checked/Unchecked*/CAppleCarPlayAdaptor::getInstance()->smartFanState(),
                                                                                                                       -1, -1, -1, CSetupEnums::SETUP_SCREEN_SMART_FAN));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Smart Fan option is not added to the list.", __FUNCTION__);
            m_iSmartFanIndex = -1;
        }

        if(CVariantControlAdaptor::getInstance()->eolDriveNextEnabled())
        {
            m_iDriveNextIndex = m_pSetupVehicleSettingsListModel->rowCount();
            m_pSetupVehicleSettingsListModel->insertElementAt(m_iDriveNextIndex, CSetupData(tr("TEXT_HOME_SHORTCUT_TITLE_DriveNext"),"", "", CSetupEnums::SETUP_LIST_ITEM_LABEL,
                                                                                            true, false, false, -1, -1, -1,
                                                                                            CSetupEnums::SETUP_SCREEN_DRIVENEXT));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: DriveNext option is not added to the list.", __FUNCTION__);
            m_iDriveNextIndex = -1;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s Vehicle setup list is Empty ", __FUNCTION__);
    }
}

void CSetupAdaptor::updateLightingSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: ", __FUNCTION__);
    initLightingSetupListModel();
}

void CSetupAdaptor::updateReqState(ERequestIndex eReqIndex, bool bMatch)
{
    if(eReqIndex >= EN_REQ_INDEX_FANSPEED && eReqIndex < EN_REQ_INDEX_END)
    {
        if(m_aryReqStatus[eReqIndex] == EN_REQ_STATE_SENT)
        {
            if(bMatch)
            {
                m_aryReqStatus[eReqIndex] = EN_REQ_STATE_PROCESSED;
            }
            else
            {
                //Do Nothing, since the request is not yet complete.
            }
        }
        else
        {
            m_aryReqStatus[eReqIndex] = EN_REQ_STATE_INVALID;
        }
    }
}

void CSetupAdaptor::initLightingSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: ", __FUNCTION__);

    if(nullptr != m_pSetupLightingListModel)
    {
        /*Note: Here we are calling this method to clear the list before insertion */
        m_pSetupLightingListModel->removeRows();

        /*Note: This condition is to check BCM Ucs state and ambient light availability in Vehicle.
            As ambient light feature depends on both the signals availability in vehicle*/
        if(CVehicleSettingsAdaptor::getInstance()->bcmUcsState() && CVehicleSettingsAdaptor::getInstance()->ambientLightModeIlluOnHu())
        {
            m_pSetupLightingListModel->insertElementAt(m_pSetupLightingListModel->rowCount(), CSetupData(tr("TEXT_VEHICLE_SETTINGS_AMBIENT_LIGHTING"),
                                                                                                         "", "", CSetupEnums::SETUP_LIST_ITEM_LABEL, /*Enable/Disable*/ true,
                                                                                                         false, false, -1, -1, -1, CSetupEnums::SETUP_SCREEN_INVALID,
                                                                                                         CSetupEnums::SETUP_SCREEN_MOOD_LIGHTING));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s List Item is available ", __FUNCTION__);
        }

        /*Note: This condition is to check BCM Ucs state and approach lamps feature availability in Vehicle.
            As approach lamps feature depends on both the signals availability in vehicle*/
        if(CVehicleSettingsAdaptor::getInstance()->bcmUcsState() && CVehicleSettingsAdaptor::getInstance()->appraochLampsPresence())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Approach Lamps is Present ", __FUNCTION__);
            m_iApproachLampIndex = m_pSetupLightingListModel->rowCount();
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_iApproachLampIndex : %d ", __FUNCTION__, m_iApproachLampIndex);
            m_pSetupLightingListModel->insertElementAt(m_pSetupLightingListModel->rowCount(), CSetupData(tr("TEXT_VEHICLE_SETTINGS_APPROACH_LAMPS"),
                                                                                                         "", "", CSetupEnums::SETUP_LIST_ITEM_DROP_DOWN, /*Enable/Disable*/ true,
                                                                                                         false, false, -1, -1, -1, CSetupEnums::SETUP_SCREEN_INVALID,
                                                                                                         CSetupEnums::SETUP_OPTION_APPROACH_LAMPS));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s List Item is available ", __FUNCTION__);
            m_iApproachLampIndex = -1;
        }

        /*Note: This condition is to check BCM Ucs state and DRL feature availability in Vehicle.
            As DRL feature depends on both the signals availability in vehicle*/
        if(CVehicleSettingsAdaptor::getInstance()->bcmUcsState() && CVehicleSettingsAdaptor::getInstance()->bcmDrlFeature())
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s DRL is Present ", __FUNCTION__);
            m_iBcmDrlIndex = m_pSetupLightingListModel->rowCount();
            m_pSetupLightingListModel->insertElementAt(m_pSetupLightingListModel->rowCount(), CSetupData(tr("DRL"),
                                                                                                         "", "", CSetupEnums::SETUP_LIST_ITEM_CHECK_BOX, /*Enable/Disable*/ !CDisplayManagerAdaptor::getInstance()->nightModeStatus(),
                                                                                                         false, CVehicleSettingsAdaptor::getInstance()->bcmDrlSelectionStatus(), -1, -1, -1, CSetupEnums::SETUP_SCREEN_INVALID,
                                                                                                         CSetupEnums::SETUP_OPTION_DRL));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s bcmUcs or bcmDrl is not present. ", __FUNCTION__);
            m_iBcmDrlIndex = -1;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_pSetupLightingListModel is NULL",__FUNCTION__);
    }
}

void CSetupAdaptor::initDriveNextListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: ", __FUNCTION__);

    if(nullptr != m_pSetupDriveNextListModel)
    {
        resetDriveNextListModel();

        m_pSetupDriveNextListModel->addDataToModel(CSetupData(tr("TEXT_SETUP_DRIVENEXT_RESET_ALL"),
                                                              "", "", CSetupEnums::SETUP_LIST_ITEM_LABEL,
                                                              true, false, false, -1, -1, -1,
                                                              CSetupEnums::SETUP_SCREEN_INVALID, CSetupEnums::SETUP_SCREEN_DRIVENEXT_RESET_ALL));

        updateDriveNextListModel();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_pSetupDriveNextListModel is NULL",__FUNCTION__);
    }
}

void CSetupAdaptor::resetDriveNextListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: ", __FUNCTION__);

    if(nullptr != m_pSetupDriveNextListModel)
    {
        m_pSetupDriveNextListModel->removeRows();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_pSetupDriveNextListModel is NULL",__FUNCTION__);
    }
}

void CSetupAdaptor::updateDriveNextListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: ", __FUNCTION__);

    if(nullptr != m_pSetupDriveNextListModel)
    {
        bool bDNProxyStatus = CDriveNextApplication::getDriveNextAdaptor() && CDriveNextApplication::getDriveNextAdaptor()->driveNextPresence();
        bool bDNResetAvailability = CDriveNextApplication::getDriveNextAdaptor() && CDriveNextApplication::getDriveNextAdaptor()->driveNextResetPresence();
        bool bDNResetStatus = CDriveNextApplication::getDriveNextAdaptor() && CDriveNextApplication::getDriveNextAdaptor()->resetTripStatus();

        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: bDNProxyStatus:%d, bDNResetAvailability:%d, bDNResetStatus:%d", __FUNCTION__, bDNProxyStatus, bDNResetAvailability, bDNResetStatus);
        m_pSetupDriveNextListModel->updateData(0, (bDNProxyStatus && (!bDNResetStatus)), CSetupListModel::ESetupRoles::ListItemEnabledRole);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_pSetupDriveNextListModel is NULL",__FUNCTION__);
    }
}

void CSetupAdaptor::initParkAssistListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: ", __FUNCTION__);

    if(nullptr != m_pSetupParkAssistListModel)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: pdcMixModeStatus : %d, parkAssistVolume : %d", __FUNCTION__,
                 CAudioAdaptor::getInstance()->pdcMixModeStatus(), CParkAssistAdaptor::getInstance()->parkAssistVolume());

        m_pSetupParkAssistListModel->addDataToModel(CSetupData(tr("TEXT_SETUP_PARK_ASSIST_AUDIO_MIX"), "", "", CSetupEnums::SETUP_LIST_ITEM_CHECK_BOX, true , false,
                                                               /*Checked/Unchecked*/CAudioAdaptor::getInstance()->pdcMixModeStatus(),
                                                               -1, -1, -1, CSetupEnums::SETUP_SCREEN_INVALID, CSetupEnums::PARK_ASSIST_MIX_WITH_AUDIO));
        m_pSetupParkAssistListModel->addDataToModel(CSetupData(tr("TEXT_SETUP_PARK_ASSIST_VOLUME"), "qrc:/image/Setup/Sts_Ico_Volume_7in_n-assets/Set_Ico_ParkAssist_7in_n-assets/Set_Ico_ParkAssist_7in_n.png",
                                                               "",  CSetupEnums::SETUP_LIST_ITEM_ICON_SLIDER, true, false, true, /*sliderValue*/CParkAssistAdaptor::getInstance()->parkAssistVolume(), /*minVal*/1, /*maxVal*/30,
                                                               CSetupEnums::SETUP_SCREEN_INVALID, CSetupEnums::PARK_ASSIST_TONE_VOLUME));
        m_pSetupParkAssistListModel->addDataToModel(CSetupData(tr("TEXT_SETUP_PARK_ASSIST_DELAY_TIMER"), "", "", CSetupEnums::SETUP_LIST_ITEM_DROP_DOWN, true , true, false,
                                                               -1, -1, -1, CSetupEnums::SETUP_SCREEN_INVALID, CSetupEnums::PARK_ASSIST_DELAY_TIMER));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_pSetupParkAssistListModel is NULL",__FUNCTION__);
    }

    if(nullptr != m_pSetupAproachLampsModel)
    {
        /*FixMe: Appraoch lamp values(30, 60, 90) has to read from vehicle service */
        int iApproachLampsIndex = CVehicleSettingsAdaptor::getInstance()->approachLamps();
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: iApproachLampsIndex : %d ",__FUNCTION__, iApproachLampsIndex);
        m_pSetupAproachLampsModel->addDataToModel(CSetupData(tr("TEXT_SETTING_APPROACH_LAMP_30"),  "", "", CSetupEnums::SETUP_LIST_ITEM_RADIO_BUTTON, true, false,
                                                             /*Checked/Unchecked*/(CVehicleEnums::VEHICLE_APPROACH_LAMPS_ZERO_INDEX == iApproachLampsIndex), -1,
                                                             -1, -1, CSetupEnums::SETUP_OPTION_APPROACH_LAMPS, CSetupEnums::APPROACH_LAMP_SEC_30));
        m_pSetupAproachLampsModel->addDataToModel(CSetupData(tr("TEXT_SETTING_APPROACH_LAMP_60"),  "", "", CSetupEnums::SETUP_LIST_ITEM_RADIO_BUTTON, true, false,
                                                             /*Checked/Unchecked*/(CVehicleEnums::VEHICLE_APPROACH_LAMPS_ONE_INDEX == iApproachLampsIndex), -1,
                                                             -1, -1, CSetupEnums::SETUP_OPTION_APPROACH_LAMPS, CSetupEnums::APPROACH_LAMP_SEC_60));
        m_pSetupAproachLampsModel->addDataToModel(CSetupData(tr("TEXT_SETTING_APPROACH_LAMP_90"),  "", "", CSetupEnums::SETUP_LIST_ITEM_RADIO_BUTTON, true, false,
                                                             /*Checked/Unchecked*/(CVehicleEnums::VEHICLE_APPROACH_LAMPS_TWO_INDEX == iApproachLampsIndex), -1,
                                                             -1, -1, CSetupEnums::SETUP_OPTION_APPROACH_LAMPS, CSetupEnums::APPROACH_LAMP_SEC_90));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_pSetupAproachLampsModel is NULL",__FUNCTION__);
    }

    if(nullptr != m_pSetupDelayTimerModel)
    {
        int iDelayTimerIndex = CParkAssistAdaptor::getInstance()->parkAssistDelayTimer();
        m_pSetupDelayTimerModel->addDataToModel(CSetupData(tr("TEXT_SETUP_PARK_ASSIST_DELAY_OPT_0"), "", "", CSetupEnums::SETUP_LIST_ITEM_RADIO_BUTTON, true, false, true,
                                                           /*Checked/Unchecked*/(CParkAssistEnum::PARK_ASSIST_DELAY_TIMER_ZERO_INDEX == iDelayTimerIndex),
                                                           -1, -1, CSetupEnums::SETUP_OPTION_PARK_ASSIST_DELAY_TIMER, CSetupEnums::PARK_ASSIST_DELAY_TIMER_SEC_0));
        m_pSetupDelayTimerModel->addDataToModel(CSetupData(tr("TEXT_SETUP_PARK_ASSIST_DELAY_OPT_5"), "", "", CSetupEnums::SETUP_LIST_ITEM_RADIO_BUTTON,true, false, true,
                                                           /*Checked/Unchecked*/(CParkAssistEnum::PARK_ASSIST_DELAY_TIMER_ONE_INDEX == iDelayTimerIndex),
                                                           -1, -1, CSetupEnums::SETUP_OPTION_PARK_ASSIST_DELAY_TIMER, CSetupEnums::PARK_ASSIST_DELAY_TIMER_SEC_5));
        m_pSetupDelayTimerModel->addDataToModel(CSetupData(tr("TEXT_SETUP_PARK_ASSIST_DELAY_OPT_10"), "", "", CSetupEnums::SETUP_LIST_ITEM_RADIO_BUTTON, true, false, true,
                                                           /*Checked/Unchecked*/(CParkAssistEnum::PARK_ASSIST_DELAY_TIMER_TWO_INDEX == iDelayTimerIndex),
                                                           -1, -1, CSetupEnums::SETUP_OPTION_PARK_ASSIST_DELAY_TIMER, CSetupEnums::PARK_ASSIST_DELAY_TIMER_SEC_10));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_pSetupDelayTimerModel is NULL",__FUNCTION__);
    }

}

void CSetupAdaptor::setExpandedThemeItemIndex(int iExpandedThemeItemIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Expanded Theme SubItem Index : %d ", __FUNCTION__, iExpandedThemeItemIndex);

    if(iExpandedThemeItemIndex != m_iExpandedThemeItemIndex)
    {
        m_iExpandedThemeItemIndex = iExpandedThemeItemIndex;
        emit sigExpandedThemeItemIndexChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Values are same ", __FUNCTION__);
    }
}

void CSetupAdaptor::expandThemeItem(int iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, " %s iItemId : %d ", __FUNCTION__, iItemId);
    if(m_bIsThemeItemExpanded)
    {
        int iCollapsedItemId = m_iExpandedThemeItemIndex;
        collapseThemeItem(m_iExpandedThemeItemIndex);

        /* If already expanded item is present, then after removing it, insertion index
             * needs to be decreamented by 1, as expanded item has been removed */
        if(iCollapsedItemId < iItemId)
        {
            iItemId--;
        }
    }

    CSetupData expandedThemeItem("", "", "", CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, true, false, 1, -1, -1,
                                 CSetupEnums::SETUP_SCREEN_INVALID, -1);


    switch (m_pSetupThemeListModel->elementAt(iItemId).m_iItemId) {
    case CSetupEnums::THEMESETUP_CLIMATE:
        expandedThemeItem.m_sListItemType = CSetupEnums::SETUP_LIST_ITEM_THEME_CLIMATE;
        break;
    case CSetupEnums::THEMESETUP_COLOR:
        expandedThemeItem.m_sListItemType = CSetupEnums::SETUP_LIST_ITEM_THEME_COLOR;
        break;
    case CSetupEnums::THEMESETUP_LIGHTING:
        expandedThemeItem.m_sListItemType = CSetupEnums::SETUP_LIST_ITEM_THEME_LIGHTING;
        break;
    case CSetupEnums::THEMESETUP_SOUND:
        expandedThemeItem.m_sListItemType = CSetupEnums::SETUP_LIST_ITEM_THEME_SOUND;
        break;
    default:
        expandedThemeItem.m_sListItemType = CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE;
        break;
    }

    /* Insert the expanded theme sub item just after the selected theme sub item */
    m_pSetupThemeListModel->insertElementAt(iItemId + 1, expandedThemeItem);

    m_bIsThemeItemExpanded = true;
    setExpandedThemeItemIndex(iItemId);
}

void CSetupAdaptor::collapseThemeItem(int iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: iItemId %d",__FUNCTION__, iItemId);
    if(m_bIsThemeItemExpanded)
    {
        m_pSetupThemeListModel->removeElementAt(iItemId + 1);
        m_bIsThemeItemExpanded = false;
        setExpandedThemeItemIndex(-1);
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Theme SubItem list removed ", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Theme sub item is already in collapsed State", __FUNCTION__);
    }
}

void CSetupAdaptor::setExpandedParkAssistItemIndex(int iExpandedParkAssistItemIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Expanded Park Assist Item Index : %d ", __FUNCTION__, iExpandedParkAssistItemIndex);

    if(iExpandedParkAssistItemIndex != m_iExpandedParkAssistItemIndex)
    {
        m_iExpandedParkAssistItemIndex = iExpandedParkAssistItemIndex;
        emit sigExpandedParkAssistItemIndexChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Values are same ", __FUNCTION__);
    }
}

void CSetupAdaptor::setExpandedApproachLampsItemIndex(int iExpandedAppraochLampsItemIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Expanded Approach Lamps Item Index : %d ", __FUNCTION__, iExpandedAppraochLampsItemIndex);

    if(iExpandedAppraochLampsItemIndex != m_iExpandedApproachLampsItemIndex)
    {
        m_iExpandedApproachLampsItemIndex = iExpandedAppraochLampsItemIndex;
        emit sigExpandedAppraochLampsItemIndexChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Values are same ", __FUNCTION__);
    }
}

void CSetupAdaptor::toggleExpandState(int iItemIndex, int iListItemType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: iItemId %d, iListItemType %d , m_iExpandedParkAssistItemIndex %d",__FUNCTION__, iItemIndex, iListItemType, m_iExpandedParkAssistItemIndex);

    int iNumItemsRemovedDuringCollapse = 0;

    if(m_iExpandedParkAssistItemIndex != -1 && (iItemIndex >= 0 && iItemIndex < m_pSetupParkAssistListModel->rowCount()))
    {
        /**
           * To check whether Park Assist Item is expanded, if yes then collapse the dropdown.
           */
        if(m_iExpandedParkAssistItemIndex == iItemIndex)
        {
            collapseParkAssistItem(iItemIndex, iListItemType, iNumItemsRemovedDuringCollapse);
            setExpandedParkAssistItemIndex(-1);
        }
        else
        {

            /* Collapse the expanded item */
            collapseParkAssistItem(m_iExpandedParkAssistItemIndex, iListItemType, iNumItemsRemovedDuringCollapse);

            if (m_iExpandedParkAssistItemIndex < iItemIndex)
            {
                iItemIndex = iItemIndex - iNumItemsRemovedDuringCollapse;
            }
            else
            {
                // Do nothing.
            }
            setExpandedParkAssistItemIndex(-1);
            expandParkAssistItem(iItemIndex, iListItemType);
        }
    }
    else
    {
        /* Method to expand the park assist item */
        expandParkAssistItem(iItemIndex, iListItemType);
    }
}

void CSetupAdaptor::expandParkAssistItem(int iItemIndex, int iListItemType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: iItemIndex %d, iListItemType %d", __FUNCTION__, iItemIndex, iListItemType);

    CSetupListModel * pItemModel = nullptr;

    /* Here this logic is to handle the which park assist model to be expanded as per listitem type */
    switch(iListItemType)
    {
    case CSetupEnums::PARK_ASSIST_DELAY_TIMER:
        pItemModel = m_pSetupDelayTimerModel;
        break;
    default:

        break;
    }

    /* Here this logic is to insert the park assist sub model items into the park assist list model */
    if (pItemModel && m_pSetupParkAssistListModel)
    {
        for(int iIndex = 0; iIndex < pItemModel->rowCount(); iIndex++)
        {
            m_pSetupParkAssistListModel->insertElementAt((iItemIndex + 1 + iIndex), pItemModel->elementAt(iIndex));
        }
    }
    else
    {
        //Print error log.
    }

    setExpandedParkAssistItemIndex(iItemIndex);

}

void CSetupAdaptor::collapseParkAssistItem(int iItemIndex, int iListItemType, int &iNumItemsRemoved)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: iItemIndex %d, iListItemType %d",__FUNCTION__, iItemIndex, iListItemType);

    if( iItemIndex != -1 )
    {
        int iRowCount = -1;

        /*Here this logic is to handle the which park assist model to be collpased as per listitem type */
        switch(iListItemType)
        {
        case CSetupEnums::PARK_ASSIST_DELAY_TIMER:
            iRowCount = m_pSetupDelayTimerModel->rowCount();
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Invalid list item type ", __FUNCTION__);
            break;
        }

        /*Here this logic is to remove the expanded items from the park assist list model */
        if (m_pSetupParkAssistListModel && (iRowCount >= 0))
        {
            for(int iIndex = 0; iIndex < iRowCount; iIndex++)
            {
                m_pSetupParkAssistListModel->removeElementAt(iItemIndex + 1);
            }

            iNumItemsRemoved = iRowCount;
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Deletion Successful", __FUNCTION__);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Park Assist Item is in collapsed state ", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Inavlid item index ", __FUNCTION__);
    }
}

void CSetupAdaptor::toggleLightingSetupExpandState(int iItemIndex, int iListItemType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, iItemIndex : %d, iListItemType : %d", __FUNCTION__, iItemIndex, iListItemType);

    if((iItemIndex >= 0 && iItemIndex < m_pSetupLightingListModel->rowCount()))
    {
        /**
           * To check whether Approach lamps Item is expanded, if yes then collapse the dropdown.
           */
        if(m_iExpandedApproachLampsItemIndex == iItemIndex)
        {
            collapseLightingSetupItem(iItemIndex, iListItemType);
        }
        else
        {
            expandLightingSetupItem(iItemIndex, iListItemType);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Invalid Index ", __FUNCTION__);
    }
}

void CSetupAdaptor::expandLightingSetupItem(int iItemIndex, int iListItemType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, ItemId : %d iListItemType : %d ", __FUNCTION__, iItemIndex, iListItemType);

    CSetupListModel * pItemModel = nullptr;

    switch(iListItemType)
    {
    case CSetupEnums::SETUP_OPTION_APPROACH_LAMPS:
        pItemModel = m_pSetupAproachLampsModel;
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Invalid Type ", __FUNCTION__);
        break;
    }

    /* Here this logic is to insert the approach lamps model items into the lighting list model */
    if (pItemModel && m_pSetupLightingListModel)
    {
        for(int iIndex = 0; iIndex < pItemModel->rowCount(); iIndex++)
        {
            m_pSetupLightingListModel->insertElementAt((iItemIndex + 1 + iIndex), pItemModel->elementAt(iIndex));
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, pItemModel or m_pSetupLightingListModel is NULL ", __FUNCTION__);
    }

    setExpandedApproachLampsItemIndex(iItemIndex);
}

void CSetupAdaptor::collapseLightingSetupItem(int iItemIndex, int iListItemType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, ItemId : %d iListItemType : %d ", __FUNCTION__, iItemIndex, iListItemType);

    CSetupListModel * pItemModel = nullptr;

    switch(iListItemType)
    {
    case CSetupEnums::SETUP_OPTION_APPROACH_LAMPS:
        pItemModel = m_pSetupAproachLampsModel;
        break;

    default:
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Invalid Type ", __FUNCTION__);
        break;
    }

    /* Here this logic is to insert the approach lamp model items into the lighting list model */
    if (pItemModel && m_pSetupLightingListModel)
    {
        for(int iIndex = 0; iIndex < pItemModel->rowCount(); iIndex++)
        {
            m_pSetupLightingListModel->removeElementAt(iItemIndex + 1);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, pItemModel or m_pSetupLightingListModel is NULL ", __FUNCTION__);
    }

    setExpandedApproachLampsItemIndex(-1);
}

void CSetupAdaptor::updateThemeSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Update Theme Setup List ", __FUNCTION__);
    /*Note : Here we are collapsing the theme item if expanded before inserting an item in the list */
    if(m_bIsThemeItemExpanded)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, m_bIsThemeItemExpanded : %d", __FUNCTION__, m_bIsThemeItemExpanded);
        collapseThemeItem(m_iExpandedThemeItemIndex);
    }

    /*Note: Here we are calling this function when ever there is change from service saying feature not available
            then we re-initializing the theme setup list */
    initThemeSetupListModel();
}

void CSetupAdaptor::initThemeSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, m_iPresetSelected : %d", __FUNCTION__, m_iPresetSelected);
    if(nullptr != m_pSetupThemeListModel)
    {
        /*Note: Here we are calling this method to clear the list before insertion */
        m_pSetupThemeListModel->removeRows();

        if((m_iPresetSelected < CSetupEnums::THEME_PRESET_MAX) && (m_iPresetSelected > CSetupEnums::THEME_PRESET_INVALID))
        {
            CThemeElement* pThemeElement = static_cast<CThemeElement *>(m_lThemeElementsList[m_iPresetSelected]);

            if(CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT)
            {
                m_pSetupThemeListModel->insertElementAt(m_pSetupThemeListModel->rowCount(), CSetupData(tr("TEXT_THEME_CLIMATE"), "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Ico_Climate_na.png","", "",
                                                                                                       "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Gen_Drawer_Ico_Fan_n.png", pThemeElement->fanspeed()/* fan speed*/, pThemeElement->temperature()/* temperature*/,
                                                                                                       true, true, false, false, false, CSetupEnums::SETUP_LIST_ITEM_DROP_DOWN, CSetupEnums::THEMESETUP_CLIMATE));
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: CCM is not present, ccmPresence: %d", __FUNCTION__, CHVACAdaptor::getInstance()->ccmPresence());
            }

            m_pSetupThemeListModel->insertElementAt(m_pSetupThemeListModel->rowCount(), CSetupData(tr("TEXT_THEME_COLOR"),"qrc:/image/Themes/Set_Ico_sColour_7in_n-assets/Set_Ico_Light_na.png",
                                                                                                   CThemeManager::getThemeManager().getAllThemeColors()[pThemeElement->themeColor()], "","", 0, 0,
                                                    true, false, true, false, false, CSetupEnums::SETUP_LIST_ITEM_DROP_DOWN, CSetupEnums::THEMESETUP_COLOR));

            /*Note: Ambient light availablity depends on feature availabilty in vehicle*/
            if(CVehicleSettingsAdaptor::getInstance()->bCmPresence() &&
                    CVehicleSettingsAdaptor::getInstance()->bcmUcsState() &&
                    CVehicleSettingsAdaptor::getInstance()->ambientLightModeIlluOnHu())
            {
                m_pSetupThemeListModel->insertElementAt(m_pSetupThemeListModel->rowCount(), CSetupData(tr("TEXT_VEHICLE_SETTINGS_LIGHTING"), "qrc:/image/Themes/Set_Ico_sLights_7in_n-assets/Set_Ico_colour_na.png",
                                                                                                       "qrc:/image/Themes/Set_Ico_sLights_7in_n-assets/Set_Ico_sMoodlight_Car_n.png", "","", 0, 0,
                                                                                                       true, false, false, true, false, CSetupEnums::SETUP_LIST_ITEM_DROP_DOWN, CSetupEnums::THEMESETUP_LIGHTING));
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s List Item is available, BCM : %d, BcmUcs: %d, AmbientLight :%d", __FUNCTION__,
                         CVehicleSettingsAdaptor::getInstance()->bCmPresence(),
                         CVehicleSettingsAdaptor::getInstance()->bcmUcsState(),
                         CVehicleSettingsAdaptor::getInstance()->ambientLightModeIlluOnHu());
            }

            m_pSetupThemeListModel->insertElementAt(m_pSetupThemeListModel->rowCount(),CSetupData(tr("TEXT_THEME_SOUND"),"qrc:/image/Themes/Set_Ico_sSound_7in_n-assets/Set_Ico_sound_n.png",
                                                                                                  "qrc:/image/Themes/Set_Ico_sSound_7in_n-assets/Set_Ico_sSound_Car_n.png", "", "", 0, 0,
                                                                                                  true, false, false, true, false, CSetupEnums::SETUP_LIST_ITEM_DROP_DOWN, CSetupEnums::THEMESETUP_SOUND));
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Invalid Preset Index Selected : %d", __FUNCTION__, m_iPresetSelected);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_pSetupThemeListModel is NULL",__FUNCTION__);
    }
}

void CSetupAdaptor::initThemeElementList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    qDeleteAll(m_lThemeElementsList.begin(), m_lThemeElementsList.end());
    m_lThemeElementsList.clear();

    // Here the theme element list data set with default values of theme presets.
    // To Do: Need to change the values of theme element preset values like fanspeed, temperature, air flow mode, color etc.,  as per customer requirements
    // Fan   temp    airflow color   brightness  Notification    audipreset  Bass    Mid Treble  AmbLight*/
    m_lThemeElementsList.append(new CThemeElement(1,    20.0,   0,      0,      50,         15,             0,          -5,     8,   2,      3));//zen
    m_lThemeElementsList.append(new CThemeElement(2,    18.0,   1,      1,      90,         12,             1,           6,     5,  -8,      5));//zing
    m_lThemeElementsList.append(new CThemeElement(1,    22.0,   2,      2,      70,         8,              0,          -8,     4,   3,      1));//zeel
    /*Note : This is commented because this preset may not be there.
      FixMe: Reomove this after confirmation from TML*/
    //    m_lThemeElementsList.append(new CThemeElement(4, 20.0, 4, 3, 70, 9, 4, 10,-3, 4, 6));//harrier

    m_lThemeElementsList.append(&m_objCustomThemeElement);//Custom

    CThemeElement *pTemp = static_cast<CThemeElement *>(m_lThemeElementsList.at(m_iPresetSelected));

    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    if (!(CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID || CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID))
    {
        CThemeManager::getThemeManager().setThemeType(static_cast<CThemeManagerEnums::EThemeTypes>(pTemp->themeColor()));
        /* Updating the anim config after the latest theme is read from persistency */
        CThemeManager::getThemeManager().updateAnimConfig();
    }
    emit sigThemeElementList();
}

void CSetupAdaptor::updateThemeSetupListModelData(int iRole, int iListItemIndex, const QVariant& objValue, CSetupListModel *pThemeSetupListModel, CSetupEnums::ESetupScreens eSetupListOption)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    if (pThemeSetupListModel)
    {
        pThemeSetupListModel->updateThemeSetupModelData(iRole, iListItemIndex, objValue, eSetupListOption);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s : pThemeSetupListModel is NULL", __FUNCTION__);
    }
}

void CSetupAdaptor::updateSetupListModelData(int iRole, int iListItemIndex, const QVariant& value, QAbstractListModel *pCurrentListModel, CSetupEnums::ESetupScreens eSetupListOption)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__);
    CSetupListModel *pSetupListModel = dynamic_cast<CSetupListModel *> (pCurrentListModel);
    if (pSetupListModel)
    {
        pSetupListModel->updateSetupModelData(iRole, iListItemIndex, value, eSetupListOption);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s : pSetupListModel is NULL:", __FUNCTION__);
    }
}

void CSetupAdaptor::updateSetupListModelDataParkAssistVolume(int iRole, int iListItemIndex, const QVariant& value, QAbstractListModel *m_pCurrentListModel, CSetupEnums::ESetupScreens eSetupListOption)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s iRole: %d iListItemIndex: %d eSetupListOption:%d", __FUNCTION__, iRole, iListItemIndex, static_cast<int>(eSetupListOption));
    if(m_pCurrentListModel)
    {
        CSetupListModel *pSetupListModel = dynamic_cast<CSetupListModel *> (m_pCurrentListModel);
        if (pSetupListModel)
        {
            pSetupListModel->updateData(iListItemIndex, value, CSetupListModel::ESetupRoles::ListItemValueRole);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s : pSetupListModel is NULL:", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s : m_pCurrentModel is NULL:", __FUNCTION__);
    }
}

QList<QObject *> CSetupAdaptor::themeElementsList()
{
    return m_lThemeElementsList;
}

QObject *CSetupAdaptor::editModeThemeObject()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, ", __FUNCTION__);

    return m_pEditModeThemeElement;
}


void CSetupAdaptor::setEditModeFlag(bool bEditModeFlag)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, EditModeFlag : %d ", __FUNCTION__, bEditModeFlag);
    m_bEditModeFlag = bEditModeFlag;
    emit sigEditModeFlagChanged();
}

void CSetupAdaptor::setCurrentThemeModified(bool bCurrentThemeModified)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Theme Preset Changed : %d ", __FUNCTION__, bCurrentThemeModified);
    m_bIsCurrentThemeModified = bCurrentThemeModified;
    emit sigCurrentThemeModified();
}

void CSetupAdaptor::setCurrentAudioSetupScreen(CSetupEnums::EAudioSetupCurrentScreen eAudioSetupCurrentScreen)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Audio setup screen Changed : %d ", __FUNCTION__, eAudioSetupCurrentScreen);
    if(eAudioSetupCurrentScreen != m_eAudioSetupCurrentScreen)
    {
        m_eAudioSetupCurrentScreen = eAudioSetupCurrentScreen;
        emit sigCurrentAudioSettingsScreenChanged();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s, m_eAudioSetupCurrentScreen is not changed", __FUNCTION__);
    }
}

void CSetupAdaptor::sltThemeCannotBeUpdated()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Error Status : %d ", __FUNCTION__, CHVACAdaptor::getInstance()->errorStatus());
    m_bThemeLoadingStatus = false;
    updateSetupListModelData(CSetupEnums::SETUP_lIST_ITEM_LOADING_ROLE,  /*index*/0, m_bThemeLoadingStatus, m_pSetupThemeListModel);
}

bool CSetupAdaptor::validateClimateValues()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, ", __FUNCTION__);

    bool bRes = false;

    if(CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT)
    {
        if ((m_iCurActiveThemePreset < CSetupEnums::THEME_PRESET_MAX) && (m_iCurActiveThemePreset > CSetupEnums::THEME_PRESET_INVALID))
        {
            bRes = (static_cast<CThemeElement *>(m_lThemeElementsList[m_iCurActiveThemePreset])->fanspeed() != CHVACAdaptor::getInstance()->fanSpeed());
            if(!bRes)
            {
                /** @todo: This is a temporary implementation to support setting temperature/fanspeed between min and mx range.
                 * To be removed later.
                  */
                if(EN_REQ_STATE_HOLD == m_aryReqStatus[EN_REQ_INDEX_TEMPERATURE])
                {
                    CHVACAdaptor::getInstance()->setHVACParameter(CHVACEnums::HUCCM_TEMP_CHANGE, static_cast<CThemeElement *>(m_lThemeElementsList[m_iCurActiveThemePreset])->temperature()*TEMPERATURE_DIVISOR_MULTI);
                    m_aryReqStatus[EN_REQ_INDEX_TEMPERATURE] = EN_REQ_STATE_SENT;
                }

                float fTemperature = (CHVACAdaptor::getInstance()->zoneType() == CHVACEnums::HVAC_DUAL_ZONE) ? CHVACAdaptor::getInstance()->driverTemperature() : CHVACAdaptor::getInstance()->temperature();
                bRes = (static_cast<CThemeElement *>(m_lThemeElementsList[m_iCurActiveThemePreset])->temperature() != fTemperature);
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Active Theme preset Climate Values are set", __FUNCTION__);
            }
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Invalid ThemePreset Index", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: CCM is not preset, ccmPresenceState: %d", __FUNCTION__, CHVACAdaptor::getInstance()->ccmPresence());
    }
    return bRes;
}

bool CSetupAdaptor::validateColorValues()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, ", __FUNCTION__);

    bool bRes = false;
    if ((m_iCurActiveThemePreset < CSetupEnums::THEME_PRESET_MAX) && (m_iCurActiveThemePreset > CSetupEnums::THEME_PRESET_INVALID))
    {
        bRes = (static_cast<CThemeElement *>(m_lThemeElementsList[m_iCurActiveThemePreset])->themeColor() != CThemeManager::getThemeManager().currentThemeType());
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Invalid ThemePreset Index", __FUNCTION__);
    }
    return bRes;
}

bool CSetupAdaptor::validateLightingValues()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, ", __FUNCTION__);

    bool bRes = false;
    if ((m_iCurActiveThemePreset < CSetupEnums::THEME_PRESET_MAX) && (m_iCurActiveThemePreset > CSetupEnums::THEME_PRESET_INVALID))
    {
        if(CVehicleSettingsAdaptor::getInstance()->ambientLightModeIlluOnHu())
        {
            bRes = (static_cast<CThemeElement *>(m_lThemeElementsList[m_iCurActiveThemePreset])->themeAmbLightIlluLevel() != CVehicleSettingsAdaptor::getInstance()->ambSelIlluminationLevel());
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Active Theme preset lighting Values are set", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Invalid ThemePreset Index", __FUNCTION__);
    }
    return bRes;
}

bool CSetupAdaptor::validateSoundValues()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s,", __FUNCTION__);
    bool bRes = false;

    if ((m_iCurActiveThemePreset < CSetupEnums::THEME_PRESET_MAX) && (m_iCurActiveThemePreset > CSetupEnums::THEME_PRESET_INVALID))
    {
        bRes = (static_cast<CThemeElement *>(m_lThemeElementsList[m_iCurActiveThemePreset])->notificationVolume() != CAudioAdaptor::getInstance()->voiceAlertVolume());
        if(!bRes)
        {
            bRes = (static_cast<CThemeElement *>(m_lThemeElementsList[m_iCurActiveThemePreset])->audioPreset() != CAudioAdaptor::getInstance()->activeAudioPreset());
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Active Theme preset Sound Values are set", __FUNCTION__);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Invalid ThemePreset Index", __FUNCTION__);
    }
    return bRes;
}

void CSetupAdaptor::sltFanSpeedChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s ", __FUNCTION__);
    themeLoadingChanged();
    updateReqState(EN_REQ_INDEX_FANSPEED, !validateClimateValues());
    validateReq();
}

void CSetupAdaptor::sltTemperatureChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    themeLoadingChanged();
    updateReqState(EN_REQ_INDEX_TEMPERATURE, !validateClimateValues());
    validateReq();
}

void CSetupAdaptor::sltCurrentThemeTypeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    updateReqState(EN_REQ_INDEX_COLOR, !validateColorValues());
    validateReq();
}

void CSetupAdaptor::sltAmbLightIllumLevelChanged ()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    updateReqState(EN_REQ_INDEX_AMBIENTLIGHT, !validateLightingValues());
    validateReq();
}

void CSetupAdaptor::sltActiveAudioPresetChanged  ()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    updateReqState(EN_REQ_INDEX_AUDIO_PRESET, !validateSoundValues());
    validateReq();
}

void CSetupAdaptor::sltVoiceAlertVolumeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    updateReqState(EN_REQ_INDEX_NOTIFICATION_VOLUME, !validateSoundValues());
    validateReq();
}

void CSetupAdaptor::sltErrorStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s ", __FUNCTION__);
    validateReq();
    m_aryReqStatus[EN_REQ_INDEX_FANSPEED] = EN_REQ_STATE_ERROR;
    m_aryReqStatus[EN_REQ_INDEX_TEMPERATURE] = EN_REQ_STATE_ERROR;
    sltThemeCannotBeUpdated();
}

void CSetupAdaptor::sltCtrlPanelModeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    updateThemesScreenParam(false);
}

void CSetupAdaptor::sltPowerModeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s ", __FUNCTION__);
    updateThemesScreenParam(false);
}

void CSetupAdaptor::sltParkLampStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s ", __FUNCTION__);
    updateThemesScreenParam(false);
}

void CSetupAdaptor::clearReqState()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s",__FUNCTION__);
    for(int i=EN_REQ_INDEX_FANSPEED; i<EN_REQ_INDEX_END; i++)
    {
        m_aryReqStatus[i] = EN_REQ_STATE_INVALID;
    }
}

void CSetupAdaptor::validateReq()
{
    int iErrorCount = findOccurence(EN_REQ_STATE_ERROR);
    int iReqSentCount = findOccurence(EN_REQ_STATE_SENT);
    int iIgnoreCount = findOccurence(EN_REQ_STATE_IGNORED);
    int iInvalidCount = findOccurence(EN_REQ_STATE_INVALID);
    int iProcessedCount = findOccurence(EN_REQ_STATE_PROCESSED);

    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s iErrorCount: %d, iReqSentCount: %d, iIgnoreCount: %d, iInvalidCount: %d, iProcessedCount: %d",
             __FUNCTION__,iErrorCount, iReqSentCount, iIgnoreCount, iInvalidCount, iProcessedCount);

    /* Note: Here when any of the theme preset values are not sent due
     * to same value of the theme preset then this condition gets true */
    if(EN_REQ_INDEX_END == (iIgnoreCount + iInvalidCount + iProcessedCount))
    {
        /* Note: Here when all the theme preset values are  not set due to
         * similar value of the theme preset then this condition gets true*/
        if(EN_REQ_INDEX_END == iInvalidCount)
        {
            //External updates on theme values.
            updateThemesScreenParam(false);
        }
        else
        {
            updateThemesScreenParam(true);
            clearReqState();
        }
    }

    /* Note: Here when any of the theme preset values(fan speed, temperature, color etc.,) are not available to set then
              this condition gets true and update the theme preset screen. */
    else if(iErrorCount > 0)
    {
        //append *
        CSetupData objSetupData = m_pThemeSettingsModel->getModelData(m_iCurActiveThemePreset);

        if(!objSetupData.m_strName.contains("*"))
        {
            objSetupData.m_strName.append("*");
            m_pThemeSettingsModel->updateModel(m_iCurActiveThemePreset, objSetupData);
        }

        setCurrentThemeModified(true);
        updateCurActiveThemePreset();

        clearReqState();
    }

    /* Note: Here when all the theme preset values(fan speed, temperature, color etc.,) are available then
              this condition gets true and update the theme preset screen. */
    else if(iReqSentCount > 0)
    {
        //Validate all the responses
        //if success then display popup and remove * if any else append *
        //ReqState to be cleared at different validation gates.
        updateThemesScreenParam(true);
    }
    else
    {
        //Should never reach here.
    }

}

int CSetupAdaptor::findOccurence(ERequestState eReqState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s",__FUNCTION__);

    int count=0;
    for(int i=EN_REQ_INDEX_FANSPEED; i< EN_REQ_INDEX_END; i++)
    {
        if(m_aryReqStatus[i] == eReqState)
        {
            count++;
        }
    }

    return count;
}

void CSetupAdaptor::updateThemesScreenParam(bool bUserInitiated)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, bUserInitiated : %d, Fan :%d, temp : %f, themecolor : %d, brightness : %d, Notification : %d, Audio Preset : %d ", __FUNCTION__,
             bUserInitiated,
             CHVACAdaptor::getInstance()->fanSpeed(),
             CHVACAdaptor::getInstance()->temperature(),
             CThemeManager::getThemeManager().currentThemeType(),
             CDisplayManagerAdaptor::getInstance()->brightNessLevel(),
             CAudioAdaptor::getInstance()->voiceAlertVolume(),
             CAudioAdaptor::getInstance()->activeAudioPreset());

    CSetupData objSetupData = m_pThemeSettingsModel->getModelData(m_iCurActiveThemePreset);

    if(!objSetupData.m_strName.contains("*")
            && ((validateClimateValues() || validateColorValues() || validateLightingValues() || validateSoundValues())))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Active theme preset values are not same : validateClimateValues: %d ,"
                                             " validateColorValues : %d, validateLightingValues : %d, validateSoundValues : %d", __FUNCTION__,
                 validateClimateValues(), validateColorValues(), validateLightingValues(), validateSoundValues());

        if(!m_bIsCurrentThemeModified)
        {
            /*FixMe: Better to  change this implementaion to update model data once we get the proper assets */
            /*
            * Add * Theme preset name.
            */
            objSetupData.m_strName.append("*");
            m_pThemeSettingsModel->updateModel(m_iCurActiveThemePreset, objSetupData);

            setCurrentThemeModified(true);
            updateCurActiveThemePreset();

        }
        m_bThemeLoadingStatus = false;
        updateSetupListModelData(CSetupEnums::SETUP_lIST_ITEM_LOADING_ROLE,  /*index*/0, m_bThemeLoadingStatus, m_pSetupThemeListModel);

    }
    else if (!validateClimateValues()   &&
             !validateColorValues()     &&
             !validateLightingValues()  &&
             !validateSoundValues())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s If Active theme preset values Changed ", __FUNCTION__);
        setEditModeFlag(false);
        if(bUserInitiated)
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_THEME_ACTIVATED_SUCCESSFUL_STATUS);
            clearReqState();
        }
        /*
            * Remove * from Previous Theme preset name.
            */
        CSetupData objSetupData = m_pThemeSettingsModel->getModelData(m_iCurActiveThemePreset);
        objSetupData.m_strName.remove("*");
        m_pThemeSettingsModel->updateModel(m_iCurActiveThemePreset, objSetupData);

        setCurrentThemeModified(false);
        updateCurActiveThemePreset();
        m_bThemeLoadingStatus = false;
        updateSetupListModelData(CSetupEnums::SETUP_lIST_ITEM_LOADING_ROLE,  /*index*/0, m_bThemeLoadingStatus, m_pSetupThemeListModel);

    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Applying theme... ", __FUNCTION__);
    }
}

void CSetupAdaptor::applyTheme(bool bEditModeFlag, int iCurrentIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s,  EditModeFlag :%d, CurrentIndex :%d Active Preset : %d", __FUNCTION__, bEditModeFlag, iCurrentIndex, m_iCurActiveThemePreset);

    if(m_iCurActiveThemePreset != iCurrentIndex)
    {
        /*
         * Remove * from Previous Theme preset name.
         */
        CSetupData objSetupData = m_pThemeSettingsModel->getModelData(m_iCurActiveThemePreset);
        objSetupData.m_strName.remove("*");
        m_pThemeSettingsModel->updateModel(m_iCurActiveThemePreset, objSetupData);

        setCurActiveThemePreset(iCurrentIndex);
        setCurrentThemeModified(false);
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_SETUP_THEME_PRESET, m_iCurActiveThemePreset);
    }

    if ((iCurrentIndex < CSetupEnums::THEME_PRESET_MAX) && (iCurrentIndex > CSetupEnums::THEME_PRESET_INVALID))
    {
        requestThemePresetValuesToService(static_cast<CThemeElement *>(m_lThemeElementsList[iCurrentIndex]));
        validateReq();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Invalid Index ", __FUNCTION__);
    }


    /*Here this method is called to update the current active theme preset and to show that in drawers */
    updateCurActiveThemePreset();

    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Set Edited Theme values to Service ", __FUNCTION__);

    //Save data to perisistency
    if(m_iCurActiveThemePreset == CSetupEnums::THEME_PRESET_USER)
    {
        saveCustomThemeValToPersistency();
    }

    //To update values
    if ((iCurrentIndex < CSetupEnums::THEME_PRESET_MAX) && (iCurrentIndex > CSetupEnums::THEME_PRESET_INVALID))
    {
        updateThemeModelData(static_cast<CThemeElement *>(m_lThemeElementsList[iCurrentIndex]));
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Invalid Index ", __FUNCTION__);
    }
}

void CSetupAdaptor::invApplyThemeColor(int iThemeColor)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, iThemeColor : %d", __FUNCTION__, iThemeColor);
    if(iThemeColor != m_eCurrThemeColor)
    {
        m_eCurrThemeColor = static_cast<CSetupEnums::EThemesItem>(iThemeColor);
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HMI_THEME_SELECTION, iThemeColor);
        if(!m_bChangeThemeWithDriveModeStatus)
        {
            if(CSetupEnums::THEME_INVALID != m_eCurrThemeColor)
            {
                CThemeManager::getThemeManager().setThemeType(static_cast<CThemeManagerEnums::EThemeTypes>(m_eCurrThemeColor));
            }
        }
    }
}

void CSetupAdaptor::setChangeThemeWithDriveModeStatus(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, bStatus : %d", __FUNCTION__, bStatus);
    if(bStatus != m_bChangeThemeWithDriveModeStatus)
    {
        m_bChangeThemeWithDriveModeStatus = bStatus;
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_CHANGE_THEME_WITH_DRIVE_MODE_STATUS, m_bChangeThemeWithDriveModeStatus);
        if(m_bChangeThemeWithDriveModeStatus)
        {
            if(CSetupEnums::DRIVE_MODE_INVALID != m_eActiveDriveMode)
            {
                CThemeManager::getThemeManager().setThemeType(static_cast<CThemeManagerEnums::EThemeTypes>(m_eActiveDriveMode));
            }
        }
        else
        {
            if(CSetupEnums::THEME_INVALID != m_eCurrThemeColor)
            {
                CThemeManager::getThemeManager().setThemeType(static_cast<CThemeManagerEnums::EThemeTypes>(m_eCurrThemeColor));
            }
        }
    }
}

void CSetupAdaptor::setActiveDriveMode(CSetupEnums::EDriveModes eDriveMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, eDriveMode : %d", __FUNCTION__, eDriveMode);
    if(eDriveMode != m_eActiveDriveMode)
    {
        m_eActiveDriveMode = eDriveMode;
        if(m_bChangeThemeWithDriveModeStatus)
        {
            if(CSetupEnums::DRIVE_MODE_INVALID != m_eActiveDriveMode)
            {
                CThemeManager::getThemeManager().setThemeType(static_cast<CThemeManagerEnums::EThemeTypes>(m_eActiveDriveMode));
            }
        }
    }
}

void CSetupAdaptor::saveCustomThemeValToPersistency()
{
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_FANSPEED,    m_objCustomThemeElement.fanspeed());
    CPersistencyAdaptor::getInstance().writeFloatData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_TEMPERATURE, m_objCustomThemeElement.temperature());
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_COLOR,       m_objCustomThemeElement.themeColor());
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AMBIENTLIGHT,m_objCustomThemeElement.themeAmbLightIlluLevel());
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_NOTIFICATION,m_objCustomThemeElement.notificationVolume());
    CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AUDIOPRESET, m_objCustomThemeElement.audioPreset());
}

void CSetupAdaptor::initCustomThemeValues()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ", __FUNCTION__);

    int iFanSpeed = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_FANSPEED);
    if ((iFanSpeed <= CHVACAdaptor::getInstance()->fanSpeedLowLimit())
            || (iFanSpeed > CHVACAdaptor::getInstance()->fanSpeedHighLimit()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Invalid Value from persistency : %d", __FUNCTION__,
                 CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_FANSPEED));
        iFanSpeed = 1;
    }
    m_objCustomThemeElement.setFanSpeed(iFanSpeed);

    float fTemperature = CPersistencyAdaptor::getInstance().readFloatData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_TEMPERATURE);
    if((fTemperature < CHVACAdaptor::getInstance()->temperatureLowLimit())
            || (fTemperature > CHVACAdaptor::getInstance()->temperatureHighLimit()))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Invalid Value from persistency : %d", __FUNCTION__,
                 CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_TEMPERATURE));
        fTemperature = 20.0;
    }
    m_objCustomThemeElement.setTemperature(fTemperature);

    int iColorMode = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_COLOR);
    if((iColorMode < 0) || (iColorMode > (CThemeManagerEnums::EThemeTypes::THEME_TYPE_MAX - 1)))
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Invalid Value from persistency : %d", __FUNCTION__,
                 CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_COLOR));
        iColorMode = 0;
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_COLOR, iColorMode);
    }
    m_objCustomThemeElement.setColorMode(iColorMode);

    m_objCustomThemeElement.setThemeDisplayBrightness(20);

    int iAmbLightIlluLevel = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AMBIENTLIGHT);
    if(iAmbLightIlluLevel <= 0 || iAmbLightIlluLevel > CVehicleSettingsAdaptor::getInstance()->ambLightIllumLevel())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Invalid Value from persistency : %d", __FUNCTION__,
                 CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AMBIENTLIGHT));
        iAmbLightIlluLevel = 2;
    }
    m_objCustomThemeElement.setThemeAmbLightIlluLevel(iAmbLightIlluLevel);

    int iNotificationVolume = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_NOTIFICATION);
    if(iNotificationVolume < 0 || iNotificationVolume > 30)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Invalid Value from persistency : %d", __FUNCTION__,
                 CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_NOTIFICATION));
        iNotificationVolume = 10;
    }
    m_objCustomThemeElement.setNotificationVolume(iNotificationVolume);

    int iAudioPreset = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AUDIOPRESET);
    if(iAudioPreset < 0 || iAudioPreset > 6)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Invalid Value from persistency : %d", __FUNCTION__,
                 CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AUDIOPRESET));
        iAudioPreset = 3;
    }
    m_objCustomThemeElement.setThemeAudioPreset(iAudioPreset);
    m_objCustomThemeElement.setAirFlowDistributionMode(4);
    m_objCustomThemeElement.setThemeBassValue(0);
    m_objCustomThemeElement.setThemeMidValue(0);
    m_objCustomThemeElement.setThemeTrebleValue(0);
}

void CSetupAdaptor::copyCurrentThemePresetValues(int iCurrentIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, copyCurrentThemePresetValues,  %d", __FUNCTION__, iCurrentIndex);
    if ((iCurrentIndex < CSetupEnums::THEME_PRESET_MAX) && (iCurrentIndex > CSetupEnums::THEME_PRESET_INVALID))
    {
        m_pEditModeThemeElement->setFanSpeed(static_cast<CThemeElement *>(m_lThemeElementsList[iCurrentIndex])->fanspeed());
        m_pEditModeThemeElement->setTemperature(static_cast<CThemeElement *>(m_lThemeElementsList[iCurrentIndex])->temperature());
        m_pEditModeThemeElement->setColorMode(static_cast<CThemeElement *>(m_lThemeElementsList[iCurrentIndex])->themeColor());
        m_pEditModeThemeElement->setNotificationVolume(static_cast<CThemeElement *>(m_lThemeElementsList[iCurrentIndex])->notificationVolume());
        m_pEditModeThemeElement->setThemeAudioPreset(static_cast<CThemeElement *>(m_lThemeElementsList[iCurrentIndex])->audioPreset());
        m_pEditModeThemeElement->setThemeAmbLightIlluLevel(static_cast<CThemeElement *>(m_lThemeElementsList[iCurrentIndex])->themeAmbLightIlluLevel());
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Invalid Index ", __FUNCTION__);
    }
}

void CSetupAdaptor::setPresetSelection(int iPresetSelected)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,setPresetSelection: %d", __FUNCTION__, iPresetSelected);
    m_iPresetSelected = iPresetSelected;

    if(m_iPresetSelected != CSetupEnums::THEME_PRESET_USER)
    {
        updateThemeModelData(static_cast<CThemeElement *>(m_lThemeElementsList[iPresetSelected]));
    }
    else
    {
        /*Note: Here reading the last saved custom mode values from perisistency */

        m_objCustomThemeElement.setFanSpeed(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_FANSPEED));
        m_objCustomThemeElement.setTemperature(static_cast<float>(CPersistencyAdaptor::getInstance().readStringData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_TEMPERATURE).toFloat()));
        m_objCustomThemeElement.setColorMode(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_COLOR));
        m_objCustomThemeElement.setThemeDisplayBrightness(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_BRIGHTNESS));
        m_objCustomThemeElement.setThemeAmbLightIlluLevel(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AMBIENTLIGHT));
        m_objCustomThemeElement.setNotificationVolume(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_NOTIFICATION));
        m_objCustomThemeElement.setThemeAudioPreset(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AUDIOPRESET));
        m_objCustomThemeElement.setAirFlowDistributionMode(4);
        m_objCustomThemeElement.setThemeBassValue(0);
        m_objCustomThemeElement.setThemeMidValue(0);
        m_objCustomThemeElement.setThemeTrebleValue(0);
        updateThemeModelData(&m_objCustomThemeElement);
    }
    emit sigPresetSelectionChanged();
}

void CSetupAdaptor::setCurActiveThemePreset(int iCurActiveThemePreset)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,Current Active theme preset: %d", __FUNCTION__, iCurActiveThemePreset);
    if((iCurActiveThemePreset != m_iCurActiveThemePreset)
            &&  (iCurActiveThemePreset < CSetupEnums::THEME_PRESET_MAX)
            && (iCurActiveThemePreset > CSetupEnums::THEME_PRESET_INVALID))
    {
        m_iCurActiveThemePreset = iCurActiveThemePreset;
        emit sigCurActiveThemePresetChanged();
    }
    else
    {
        /*Note: Here when the value of theme preset is recieved from persistency which is out of bounds and not a valid
         * theme preset then set the theme preset to default theme preset ie., Zen */
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, " %s, Value read from persistency : %d", __FUNCTION__,
                 CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SETUP_THEME_PRESET));
        m_iCurActiveThemePreset = CSetupEnums::THEME_PRESET_ZEN;
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_SETUP_THEME_PRESET, m_iCurActiveThemePreset);
    }
}

void CSetupAdaptor::updateCurActiveThemePreset()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,Current Active theme preset: %d", __FUNCTION__, m_iCurActiveThemePreset);

    CSetupData objSetupData = m_pThemeSettingsModel->getModelData(m_iCurActiveThemePreset);

    m_strActiveThemePresetIcon = objSetupData.m_strMidIcon;
    /*Here we are getting the substring of a string to be used in qml to invoke image on state change.
        "p.png/d.png" will be removed and shall be appended at the point where it is being used. */
    QString subString = (objSetupData.m_strMidIcon.right(5));
    m_strActiveThemePresetIcon.remove(subString);

    m_strActiveThemePresetText = objSetupData.m_strName;
    emit sigUpdateThemePresetInfo();
}

void CSetupAdaptor::updateThemeModelData(CThemeElement *pThemeElement)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,updateThemeModelData: ", __FUNCTION__);

    /*Note: To update the theme preset values on apply */
    if(nullptr != pThemeElement)
    {
        if(CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT)
        {
            updateThemeSetupListModelData(CSetupEnums::SETUP_lIST_ITEM_FANSPEED_ROLE,  /*index*/0, pThemeElement->fanspeed(), m_pSetupThemeListModel);
            updateThemeSetupListModelData(CSetupEnums::SETUP_lIST_ITEM_TEMPERATURE_ROLE,  /*index*/0, pThemeElement->temperature(), m_pSetupThemeListModel);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HVAC,"%s: CCM is not preset, ccmState: %d", __FUNCTION__, CHVACAdaptor::getInstance()->ccmPresence());
        }

        int iColorItemIndex = m_pSetupThemeListModel->findIndexForRequiredRole(CSetupEnums::SETUP_LIST_ITEM_NAME_ROLE, tr("TEXT_THEME_COLOR"));
        updateThemeSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_SELECTED_IMAGE_ROLE,  iColorItemIndex, pThemeElement->themeColor(), m_pSetupThemeListModel);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: pThemeElement is NULL",__FUNCTION__);
    }
}

void CSetupAdaptor::launchVehicleSettings()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Power mode status : %d ", __FUNCTION__, CPowerModeAdaptor::getInstance().getPowerModeStatus());

    //If power mode is ONE_HOUR mode then show "turn on ignition" popup else switch to vehicle setup screen
    if(CPowerModeEnums::VPM_ONE_HOUR == CPowerModeAdaptor::getInstance().getPowerModeStatus())
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_IGNITION_ON_STATUS);
    }
    else
    {
        initVehicleSetupListModel();
        CHMIMain::getSM()->getSCI_Setup()->raise_evVehicleSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_VEHICLE_NAMED_ENTRY());
    }
}

void CSetupAdaptor::launchThemeSettings()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Power mode status : %d", __FUNCTION__, CPowerModeAdaptor::getInstance().getPowerModeStatus());

    //If power mode is ONE_HOUR mode then show "turn on ignition" popup else switch to theme setup screen
    if(CPowerModeEnums::VPM_ONE_HOUR == CPowerModeAdaptor::getInstance().getPowerModeStatus())
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_IGNITION_ON_STATUS);
    }
    else
    {
        CHMIMain::getSM()->getSCI_Setup()->raise_evDisplaySetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_DISPLAY_SETUP_NAMED_ENTRY());
    }
}

bool CSetupAdaptor::validateParkLamp()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Ambient Light : %d ", __FUNCTION__, CVehicleSettingsAdaptor::getInstance()->ambientLightModeIlluOnHu());

    /*Note: Here we are making this varaible to true by default because
     * as we dont need to check park lamp status if ambient light is not available */
    bool bStatus = true;
    if(CVehicleSettingsAdaptor::getInstance()->ambientLightModeIlluOnHu())
    {
        bStatus = (CVehicleSettingsAdaptor::getInstance()->parkLampStatus());
    }

    return bStatus;
}

void CSetupAdaptor::launchAmbientLightSettings()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Park lamp status : %d ", __FUNCTION__, CVehicleSettingsAdaptor::getInstance()->parkLampStatus());
    if(!CVehicleSettingsAdaptor::getInstance()->parkLampStatus())
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_PARK_LAMP_TURN_ON_STATUS);
    }
    else
    {
        CHMIMain::getSM()->getSCI_Setup()->raise_evVehicleSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_MOODLIGHT_NAMED_ENTRY());
    }
}

void CSetupAdaptor::requestThemePresetValuesToService(CThemeElement *pThemeElement)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, CCM State:  %d ", __FUNCTION__, CHVACAdaptor::getInstance()->ctrlPanelMode());

    /**
     * This is done to show one popup at a time, between Climate and ParkLamp Popup. Climate popup is on high priority. So, in case if both climate and
     * park lamp are off and user clicks button to change the Theme then show only climate popup, no need to show the parkLamp popup and if climate is on and
     * park lamp is off, then no need to show Climate popup show only the parkLamp popup.
    **/
    m_bIsClimatePopupShown = false;

    if(nullptr != pThemeElement)
    {
        m_pThemeElement = pThemeElement;

        /*Note: Request to service only sends when Active state*/
        if(CPowerModeAdaptor::getInstance().getPowerModeStatus() == CPowerModeEnums::VPM_ACTIVE)
        {
            if(CHVACAdaptor::getInstance()->ccmPresence() == CHVACEnums::HVAC_CCM_PRESENT)
            {
                /*Note: Request to service only sends when cliamte is On*/
                if(CHVACAdaptor::getInstance()->ctrlPanelMode())
                {

                    //start loading animation screen after requesting fanspeed and temperature value to service
                    updateSetupListModelData(CSetupEnums::SETUP_lIST_ITEM_LOADING_ROLE,  /*index*/0, m_bThemeLoadingStatus, m_pSetupThemeListModel);

                    /*Note : Here we are requesting fan speed when temperature is low or high
                             because CCM will set fan speed to 7 when temperature is Low or high.
                             So on theme change HMI should request for fanspeed as well to set on requested theme preset.*/
                    if((CHVACAdaptor::getInstance()->fanSpeed() != pThemeElement->fanspeed())
                            || ((pThemeElement->temperature() < CHVACAdaptor::getInstance()->temperatureLowLimit())
                                || (pThemeElement->temperature() > CHVACAdaptor::getInstance()->temperatureHighLimit())) )
                    {
                        // trigger loading
                        m_bThemeLoadingStatus = true;
                        CHVACAdaptor::getInstance()->setHVACParameter(CHVACEnums::HUCCM_FAN_SPEED, pThemeElement->fanspeed());
                        m_aryReqStatus[EN_REQ_INDEX_FANSPEED] = EN_REQ_STATE_SENT;
                    }
                    else
                    {
                        m_aryReqStatus[EN_REQ_INDEX_FANSPEED] = EN_REQ_STATE_IGNORED;
                    }

                    if(CHVACAdaptor::getInstance()->temperature() != pThemeElement->temperature())
                    {
                        // trigger loading
                        m_bThemeLoadingStatus = true;
                        CHVACAdaptor::getInstance()->setHVACParameter(CHVACEnums::HUCCM_TEMP_CHANGE, pThemeElement->temperature()*TEMPERATURE_DIVISOR_MULTI);
                        m_aryReqStatus[EN_REQ_INDEX_TEMPERATURE] = EN_REQ_STATE_HOLD;
                    }
                    else
                    {
                        m_aryReqStatus[EN_REQ_INDEX_TEMPERATURE] = EN_REQ_STATE_IGNORED;
                    }


                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Show popup if Climate is Off ", __FUNCTION__);
                    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_CLIMATE_TURN_ON_STATUS);
                    // Change the value to TRUE to let park lamp popup to not to show its popup.
                    m_bIsClimatePopupShown = true;
                    m_aryReqStatus[EN_REQ_INDEX_FANSPEED] = EN_REQ_STATE_ERROR;
                    m_aryReqStatus[EN_REQ_INDEX_TEMPERATURE] = EN_REQ_STATE_ERROR;
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: CCM is not present, %d: ", __FUNCTION__, CHVACAdaptor::getInstance()->ccmPresence());
            }

            /*Note: Request to service only sends when ambient light is available in vehicle*/
            if(CVehicleSettingsAdaptor::getInstance()->bcmUcsState()
                    && (CVehicleSettingsAdaptor::getInstance()->ambientLightModeIlluOnHu()))
            {
                if(CDisplayManagerAdaptor::getInstance()->nightModeStatus())
                {
                    if(CVehicleSettingsAdaptor::getInstance()->ambSelIlluminationLevel() != pThemeElement->themeAmbLightIlluLevel())
                    {
                        CVehicleSettingsAdaptor::getInstance()->setAmbLightillumLevelAttribute(pThemeElement->themeAmbLightIlluLevel());
                        m_aryReqStatus[EN_REQ_INDEX_AMBIENTLIGHT] = EN_REQ_STATE_SENT;
                    }
                    else
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Ambient Light Illumination values are same ", __FUNCTION__);
                        m_aryReqStatus[EN_REQ_INDEX_AMBIENTLIGHT] = EN_REQ_STATE_IGNORED;
                    }
                }
                else
                {
                    //show popup to turn on park lamp if its off and climate popup is not shown.
                    if(!m_bIsClimatePopupShown)
                    {
                        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_PARK_LAMP_TURN_ON_STATUS);
                    }
                    else
                    {
                        //Do Nothing.
                    }
                    m_aryReqStatus[EN_REQ_INDEX_AMBIENTLIGHT] = EN_REQ_STATE_ERROR;
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Ambient Light is not available ", __FUNCTION__);
            }
        }

        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, Ignition is Off ", __FUNCTION__);
            /*Note : Show popup turn on ignition if ignition is off */
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_IGNITION_ON_STATUS);
            m_aryReqStatus[EN_REQ_INDEX_AMBIENTLIGHT] = EN_REQ_STATE_ERROR;
            m_aryReqStatus[EN_REQ_INDEX_FANSPEED] = EN_REQ_STATE_ERROR;
            m_aryReqStatus[EN_REQ_INDEX_TEMPERATURE] = EN_REQ_STATE_ERROR;
        }

        if(CAudioAdaptor::getInstance()->activeAudioPreset() != pThemeElement->audioPreset())
        {
            CAudioAdaptor::getInstance()->setAudioPresetAttribute(pThemeElement->audioPreset());
            m_aryReqStatus[EN_REQ_INDEX_AUDIO_PRESET] = EN_REQ_STATE_SENT;
        }
        else
        {
            m_aryReqStatus[EN_REQ_INDEX_AUDIO_PRESET] = EN_REQ_STATE_IGNORED;
        }

        if(CAudioAdaptor::getInstance()->voiceAlertVolume() != pThemeElement->notificationVolume())
        {
            CAudioAdaptor::getInstance()->setVoiceAlertVolumeAttribute(pThemeElement->notificationVolume());
            m_aryReqStatus[EN_REQ_INDEX_NOTIFICATION_VOLUME] = EN_REQ_STATE_SENT;
        }
        else
        {
            m_aryReqStatus[EN_REQ_INDEX_NOTIFICATION_VOLUME] = EN_REQ_STATE_IGNORED;
        }

        if(CThemeManager::getThemeManager().currentThemeType() != pThemeElement->themeColor())
        {
            CThemeManager::getThemeManager().setThemeType(static_cast<CThemeManagerEnums::EThemeTypes>(pThemeElement->themeColor()));
            m_aryReqStatus[EN_REQ_INDEX_COLOR] = EN_REQ_STATE_SENT;
        }
        else
        {
            m_aryReqStatus[EN_REQ_INDEX_COLOR] = EN_REQ_STATE_IGNORED;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS, " %s, Theme element object not created", __FUNCTION__);
    }
}

void CSetupAdaptor::startFactoryResetProcess()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);

    if(CPowerModeAdaptor::getInstance().getPowerModeStatus() == CPowerModeEnums::VPM_ONE_HOUR)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s , Machine is in One Hour Mode.",__FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_IGNITION_ON_STATUS);
    }
    else if(CPowerModeAdaptor::getInstance().getPowerModeStatus() == CPowerModeEnums::VPM_ACTIVE)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s , Machine is in Active.",__FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_CONFIRMATION_STATUS);
    }
    else if(CPowerModeAdaptor::getInstance().getPowerModeStatus() == CPowerModeEnums::VPM_MEDIA_OFF)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s , Machine is in Media Off.",__FUNCTION__);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_CONFIRMATION_STATUS);
    }
    else
    {
        //do nothing
    }
}

void CSetupAdaptor::slotFactoryResetWaitingStatusChanged(bool bFactoryResetWaitingStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    if(bFactoryResetWaitingStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,bFactoryResetWaitingStatus: %d",__FUNCTION__,bFactoryResetWaitingStatus);
    }

    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,bFactoryResetWaitingStatus: %d",__FUNCTION__,bFactoryResetWaitingStatus);
    }
}

void CSetupAdaptor::slotFactoryResetCompletionStatusChanged(bool bFactoryResetCompletionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    if(bFactoryResetCompletionStatus)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,bFactoryResetCompletionStatus: SUCCESS %d", __FUNCTION__, bFactoryResetCompletionStatus);
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_WAITING_STATUS);
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_SETUP_FACTORY_RESET_SUCCESSFUL_STATUS);
#if defined(USE_SIMULATION_PERSISTENCY)
        CPersistencyAdaptor::getInstance().writeStringData(EPersistencyKeys::HMI_DATA_AVAILABLE, "");
#endif // defined(USE_SIMULATION_PERSISTENCY)
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,bFactoryResetCompletionStatus: FAILURE %d", __FUNCTION__, bFactoryResetCompletionStatus);
    }

}

void CSetupAdaptor::sltPdcMixModeStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s , pdcMixModeStatus : %d", __FUNCTION__, CAudioAdaptor::getInstance()->pdcMixModeStatus());
    updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE,
                             0, CAudioAdaptor::getInstance()->pdcMixModeStatus(), m_pSetupParkAssistListModel);
}

void CSetupAdaptor::sltParkAssistVolumeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    updateSetupListModelDataParkAssistVolume(CSetupEnums::SETUP_LIST_ITEM_VALUE_ROLE, /*index*/1, CParkAssistAdaptor::getInstance()->parkAssistVolume(), m_pSetupParkAssistListModel);
}

void CSetupAdaptor::sltParkAssistDelayTimerChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS," %s, Park Assist Delay Timer Value : %d ", __FUNCTION__, CParkAssistAdaptor::getInstance()->parkAssistDelayTimer());
    if(m_iExpandedParkAssistItemIndex == -1)
    {
        updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE, CParkAssistAdaptor::getInstance()->parkAssistDelayTimer(), true, m_pSetupDelayTimerModel, CSetupEnums::SETUP_OPTION_PARK_ASSIST_DELAY_TIMER);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS," %s, m_iExpandedParkAssistItemIndex : %d ,  m_pSetupDelayTimerModel->rowcount : %d",
                 __FUNCTION__, m_iExpandedParkAssistItemIndex, m_pSetupDelayTimerModel->rowCount());
        updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE, CParkAssistAdaptor::getInstance()->parkAssistDelayTimer(), true, m_pSetupDelayTimerModel, CSetupEnums::SETUP_OPTION_PARK_ASSIST_DELAY_TIMER);
        updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE, m_iExpandedParkAssistItemIndex + 1 + CParkAssistAdaptor::getInstance()->parkAssistDelayTimer(),
                                 true, m_pSetupParkAssistListModel, CSetupEnums::SETUP_OPTION_PARK_ASSIST_DELAY_TIMER);
    }
}

void CSetupAdaptor::sltParkAssistRearToneChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE, CParkAssistAdaptor::getInstance()->parkAssistRearTone(), true, m_pSetupParkAssistToneModel);
}

void CSetupAdaptor::sltAppraochLampsChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, m_iExpandedApproachLampsItemIndex : %d, CVehicleSettingsAdaptor::getInstance()->approachLamps() : %d , ApproachLampIndex :%d m_pSetupLightingListModel->rowCount() : %d",
             __FUNCTION__, m_iExpandedApproachLampsItemIndex, CVehicleSettingsAdaptor::getInstance()->approachLamps(), m_iApproachLampIndex, m_pSetupLightingListModel->rowCount());

    if(m_iExpandedApproachLampsItemIndex == -1)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, IF NOT EXPANDED ", __FUNCTION__);

        updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE, CVehicleSettingsAdaptor::getInstance()->approachLamps(), true, m_pSetupAproachLampsModel, CSetupEnums::SETUP_OPTION_APPROACH_LAMPS);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, ELSE, m_iApproachLampIndex : %d, m_pSetupAproachLampsModel->rowCount() : %d",
                 __FUNCTION__, m_iApproachLampIndex, m_pSetupAproachLampsModel->rowCount());
        /*Note : Here we have added approach lamp position index as it chagnges dynamically when expanded
          and update both ligting list model and approach lamps model*/
        updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE, CVehicleSettingsAdaptor::getInstance()->approachLamps(),
                                 true, m_pSetupAproachLampsModel, CSetupEnums::SETUP_OPTION_APPROACH_LAMPS);
        updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE,
                                 m_iApproachLampIndex + 1 + CVehicleSettingsAdaptor::getInstance()->approachLamps(),
                                 true, m_pSetupLightingListModel, CSetupEnums::SETUP_OPTION_APPROACH_LAMPS);
    }
}

void CSetupAdaptor::sltVehicleAutoRelockChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE,/*index*/0, CVehicleSettingsAdaptor::getInstance()->vehicleAutoRelock(), m_pSetupVehicleSettingsListModel);
}

void CSetupAdaptor::sltDriveNextElementsChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    updateDriveNextListModel();
}

void CSetupAdaptor::sltVoiceAlertSelectionChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Voice Alert Selection : %d ", __FUNCTION__, CVoiceAlertsAdaptor::getInstance().voiceAlertSelection());
    updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE,/*index*/m_iVoiceAlertIndex, CVoiceAlertsAdaptor::getInstance().voiceAlertSelection(), m_pSetupVehicleSettingsListModel);
}

void CSetupAdaptor::sltBcmDrlSelectionStateChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Bcm Drl Selection : %d ", __FUNCTION__, CVehicleSettingsAdaptor::getInstance()->bcmDrlSelectionStatus());
    int iIndex = m_pSetupLightingListModel->findIndexForRequiredRole(CSetupEnums::SETUP_LIST_ITEM_NAME_ROLE, "DRL");
    updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE,/*index*/iIndex, CVehicleSettingsAdaptor::getInstance()->bcmDrlSelectionStatus(), m_pSetupLightingListModel);
}

void CSetupAdaptor::sltNightModeStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Night Mode status : %d ", __FUNCTION__, CDisplayManagerAdaptor::getInstance()->nightModeStatus());
    int iIndex = m_pSetupLightingListModel->findIndexForRequiredRole(CSetupEnums::SETUP_LIST_ITEM_NAME_ROLE, "DRL");
    updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_ENABLED_ROLE,/*index*/iIndex, !(CDisplayManagerAdaptor::getInstance()->nightModeStatus()), m_pSetupLightingListModel);
}

void CSetupAdaptor::sltDistributionModeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    updateSetupListModelData(CSetupEnums::SETUP_lIST_ITEM_DISTRIBUTIONMODE_ROLE,  /*index*/0, CHVACAdaptor::getInstance()->distributionMode(), m_pSetupThemeListModel);
}

void CSetupAdaptor::themeLoadingChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    if((m_pThemeElement) && (m_pThemeElement->fanspeed() == CHVACAdaptor::getInstance()->fanSpeed())
            && (m_pThemeElement->temperature() == CHVACAdaptor::getInstance()->temperature()))
    {
        m_bThemeLoadingStatus = false;
        updateSetupListModelData(CSetupEnums::SETUP_lIST_ITEM_LOADING_ROLE,  /*index*/0, m_bThemeLoadingStatus, m_pSetupThemeListModel);
    }
}

void CSetupAdaptor::sltCPConnectionStatusUpdated(bool bCPConnectionStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: bCPConnectionStatus: %d", __FUNCTION__, bCPConnectionStatus);
    initVehicleSetupListModel();
}

void CSetupAdaptor::sltSmartFanStateChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: bSmartFanState: ", __FUNCTION__);

    if(SETUP_INVALID_INDEX != m_iSmartFanIndex)
    {
        updateSetupListModelData(CSetupEnums::SETUP_LIST_ITEM_CHECKED_ROLE, m_iSmartFanIndex, CAppleCarPlayAdaptor::getInstance()->smartFanState(), m_pSetupVehicleSettingsListModel);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Cannot update smart fan state into model, model is not created.", __FUNCTION__);
    }
}

/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHomeAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CHomeAdaptor, an Adaptor for Home module,
 * CHomeAdaptor is singleton class used to communicate with qml,resources of Home module.
 */

#include "ResourceFactory.hpp"
#include "HMIIncludes.h"

#include "CHomeApplication.h"
#include "CHomeAdaptor.h"
#include "CHomeSM.h"
#include "CHomeEventHandler.h"
#include "CDHomeShortcut.h"
#include "CAudioAdaptor.h"
#include "CPhoneAdaptor.h"
#include "CPopupManager.h"
#include "CPersistencyAdaptor.h"
#include "CAndroidAutoAdaptor.h"
#include "CHardkeyAdaptor.h"
#include "CAppleCarPlayAdaptor.h"
#include "CParkAssistAdaptor.h"
#include "CSetupAdaptor.h"
#include "CVariantControlAdaptor.h"
#include "CVRAdaptor.h"
#include "CHardKeyEnum.h"
#include "CDriveNextApplication.h"
#include "CDriveNextAdaptor.h"
#include "CDoodleApplication.h"
#include "CDoodleAdaptor.h"
#include "CW3WApplication.h"
#include "CW3WAdaptor.h"
#include "CSoundDemoAdaptor.h"

CHomeAdaptor* CHomeAdaptor::mpHomeAdaptor = nullptr;

///////////////////////////////////////////////////////////////////////////////
// Adaptor related functions
///////////////////////////////////////////////////////////////////////////////
CHomeAdaptor& CHomeAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    if (nullptr == mpHomeAdaptor)
    {
        mpHomeAdaptor = new CHomeAdaptor();
    }
    return *mpHomeAdaptor;
}
//____________________________________________________________________________
CHomeAdaptor::CHomeAdaptor(QObject *parent) :
    QObject(parent),
    m_eFavKeyCode(CHardKeyEnum::FAV_HK),
    m_iShortcutPages(0),
    m_iCurrentPageIndex(0),
    m_iShortcutToEdit(0),
    m_bOnHomeScreen(false),
    m_bIsInitializationInProgress(true)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppHomeAdaptor",this);
    CHomeEnum::registerHomeEnumsToQML();
    CFramework::getFramework().setContextProperty("MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE",CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE);
    initAdaptorProperties();
    initFavKeyModel();

    connect(&(CPowerModeAdaptor::getInstance()), SIGNAL(sigPowerModeChanged()), this, SLOT(sltPowerModeChanged()), Qt::QueuedConnection);

    m_bIsInitializationInProgress = false;
}
//____________________________________________________________________________
CHomeAdaptor::~CHomeAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    if (nullptr != m_pHomeUpdateShortcutModel)
    {
        delete m_pHomeUpdateShortcutModel;
        m_pHomeUpdateShortcutModel = nullptr;
    }

    qDeleteAll(m_lCDHomeShortcuts.begin(), m_lCDHomeShortcuts.end());
    m_lCDHomeShortcuts.clear();

    mpHomeAdaptor = nullptr;
}
//____________________________________________________________________________
void CHomeAdaptor::initAdaptorProperties()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    m_iCurrentPageIndex = 0;
    // initialize Title, Icons, IsActive & IsAvailable values according to shortcuts information
    for (int i = 0; i < CHomeEnum::MAX_SHORTCUTS_AVAILABLE; i++)
    {
        m_lCDHomeShortcuts.append(new CDHomeShortcut(i, this));
    }

    connectSignals();
    linkShortcutCallbackFunctions();

    m_liShortcutsId.clear();

    updateHomeScreenSlots();

    m_pHomeUpdateShortcutModel = new CHomeUpdateShortcutModel(this);
}
//____________________________________________________________________________
void CHomeAdaptor::slotEOLChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    updateHomeScreenSlots();
}
//____________________________________________________________________________
bool CHomeAdaptor::isShortcutAvailable(CHomeEnum::EHomeShortcutsUID eHomeShortcutsUID)
{
    bool bAvailable = false;
    switch (eHomeShortcutsUID)
    {
    case CHomeEnum::SHORTCUT_BLANK_ID:
    case CHomeEnum::SHORTCUT_ADD_SHORTCUT_ID:
    case CHomeEnum::SHORTCUT_AUDIO_SETUP_ID:
    case CHomeEnum::SHORTCUT_BLUETOOTH_ID:
    case CHomeEnum::SHORTCUT_CONTACTS_ID:
    case CHomeEnum::SHORTCUT_FAVOURITE_ID:
    case CHomeEnum::SHORTCUT_IPOD_ID:
    case CHomeEnum::SHORTCUT_PHONE_ID:
    case CHomeEnum::SHORTCUT_PHONE_SETUP_ID:
    case CHomeEnum::SHORTCUT_RADIO_ID:
    case CHomeEnum::SHORTCUT_USB_ID:
    case CHomeEnum::SHORTCUT_VOICE_COMMAND_ID:
    case CHomeEnum::SHORTCUT_THEMES_ID:
    {
        bAvailable = true;
    }
        break;
    case CHomeEnum::SHORTCUT_SOUNDDEMO_ID:
    {
        bAvailable = CSoundDemoAdaptor::getInstance()->demoAvailable();
    }
        break;
    case CHomeEnum::SHORTCUT_AUX_IN_ID:
    {
        if(CAudioEnums::AUX_CONNECTED == CAudioAdaptor::getInstance()->auxConnectionStatus() ||
                CAudioEnums::AUX_ALREADY_CONNECTED == CAudioAdaptor::getInstance()->auxConnectionStatus())
        {
            bAvailable = true;
        }
        else
        {
            bAvailable = false;
        }
    }
        break;
    case CHomeEnum::SHORTCUT_ANDROID_AUTO_ID:
    {
        bAvailable = CVariantControlAdaptor::getInstance()->eolAndroidAutoEnabled();
    }
        break;
    case CHomeEnum::SHORTCUT_APPLE_CAR_PLAY_ID:
    {
        bAvailable = CVariantControlAdaptor::getInstance()->eolAppleCarPlayEnabled();
    }
        break;
    case CHomeEnum::SHORTCUT_AMBIENT_LIGHT_ID:
    {
        bAvailable = CVehicleSettingsAdaptor::getInstance()->bAmbientLightAvailableStatus();
    }
        break;
    case CHomeEnum::SHORTCUT_CONNECT_NEXT_ID:
    case CHomeEnum::SHORTCUT_HELP_ID:
    case CHomeEnum::SHORTCUT_NAVIGATION_ID:
    case CHomeEnum::SHORTCUT_VEHICLE_SETTING_ID:
    case CHomeEnum::SHORTCUT_TOGGLE_SOURCE_ID:
    {
        // Always unavailable
    }
        break;
    case CHomeEnum::SHORTCUT_DRIVENEXT_ID:
    {
        bAvailable = CVariantControlAdaptor::getInstance()->eolDriveNextEnabled();
    }
        break;
    case CHomeEnum::SHORTCUT_DOODLE_ID:
    {
        bAvailable = CVariantControlAdaptor::getInstance()->eolHMIDoodleEnabled();
    }
        break;
    case CHomeEnum::SHORTCUT_SETTINGS_MAIN_ID:
    {
        bAvailable = true; // Always available since default HMI is X445
    }
        break;
    case CHomeEnum::SHORTCUT_PARK_ASSIST_ID:
    {
        bAvailable = true; // Always available since default HMI is X445
    }
        break;
    case CHomeEnum::SHORTCUT_W3W_ID:
    {
        bAvailable = CW3WApplication::getW3WAdaptor()->w3wFeatureSupportStatus();
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HOME, "%s, SHORTCUT_ID:%d Not handled, considering EOL disabled", __FUNCTION__, eHomeShortcutsUID);
    }
        break;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, SHORTCUT_ID:%d, EOL_Enabled:%d", __FUNCTION__, eHomeShortcutsUID, bAvailable);
    return bAvailable;
}
//____________________________________________________________________________
bool CHomeAdaptor::validateHomeSlotIndex(EPersistencyKeys ePersistencyKey)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    int iOldValue = CPersistencyAdaptor::getInstance().readIntData(ePersistencyKey);
    bool bValueChanged = false;

    if (iOldValue >= CHomeEnum::MAX_SHORTCUTS_AVAILABLE)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, Invalid Shortcut Found for key:%d Shortcut:%d", __FUNCTION__, ePersistencyKey, iOldValue);
        iOldValue = 0;
        bValueChanged = true;
    }
    else if(CDHomeShortcut::SHORTCUTS[iOldValue][5] != "Y")
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, Shortcut Removed from code side for key:%d Shortcut:%d", __FUNCTION__, ePersistencyKey, iOldValue);
        iOldValue = 0;
        bValueChanged = true;
    }
    else
    {
        //Everything is OK
    }

    if(iOldValue == CHomeEnum::SHORTCUT_AMBIENT_LIGHT_ID)
    {
        if(!CVehicleSettingsAdaptor::getInstance()->bAmbientLightAvailableStatus())
        {
            iOldValue = 0;
            bValueChanged = true;
        }
    }
    else
    {
        //Do nothing
    }

    if (bValueChanged)
    {
        CPersistencyAdaptor::getInstance().writeIntData(ePersistencyKey, iOldValue);
    }
    else
    {
        //Everything is OK
    }

    return bValueChanged;
}

void CHomeAdaptor::validateHomeWithEOLSettings()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);

    bool bIsEOLChanged = false;

    bool bAAEnabled = (CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_EOL_ANDROID_AUTO_ON) == 1);
    bool bEOLAAEnabled = isShortcutAvailable(CHomeEnum::SHORTCUT_ANDROID_AUTO_ID);

    if (bEOLAAEnabled != bAAEnabled)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, EOL for ANDROID_AUTO changed:%d", __FUNCTION__, bEOLAAEnabled);
        bIsEOLChanged = true;
        if (bEOLAAEnabled)
        {
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_ANDROID_AUTO_ON, 1);
        }
        else
        {
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_ANDROID_AUTO_ON, 0);
        }
    }
    else
    {
        //Do nothing.
    }

    bool bACPEnabled = (CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_EOL_APPLE_CAR_PLAY_ON) == 1);
    bool bEOLACPEnabled = isShortcutAvailable(CHomeEnum::SHORTCUT_APPLE_CAR_PLAY_ID);

    if (bEOLACPEnabled != bACPEnabled)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, EOL for APPLE_CAR_PLAY changed:%d", __FUNCTION__, bEOLACPEnabled);
        bIsEOLChanged = true;
        if (bEOLACPEnabled)
        {
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_APPLE_CAR_PLAY_ON, 1);
        }
        else
        {
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_APPLE_CAR_PLAY_ON, 0);
        }
    }
    else
    {
        //Do nothing.
    }

    bool bDNEnabled = (CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_EOL_DRIVE_NEXT_ON) == 1);
    bool bEOLDNEnabled = isShortcutAvailable(CHomeEnum::SHORTCUT_DRIVENEXT_ID);

    if (bEOLDNEnabled != bDNEnabled)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, EOL for DRIVE_NEXT changed:%d", __FUNCTION__, bEOLDNEnabled);
        bIsEOLChanged = true;
        if (bEOLDNEnabled)
        {
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_DRIVE_NEXT_ON, 1);
        }
        else
        {
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_DRIVE_NEXT_ON, 0);
        }
    }
    else
    {
        //Do nothing.
    }

    bool bW3WEnabled = (CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_EOL_W3W_ON) == 1);
    bool bEOLW3WEnabled = isShortcutAvailable(CHomeEnum::SHORTCUT_W3W_ID);

    if (bEOLW3WEnabled != bW3WEnabled)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, EOL for W3W changed:%d", __FUNCTION__, bEOLW3WEnabled);
        bIsEOLChanged = true;
        if (bEOLW3WEnabled)
        {
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_W3W_ON, 1);
        }
        else
        {
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_W3W_ON, 0);
        }
    }
    else
    {
        //Do nothing.
    }

    bool bDoodleEnabled = (CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_EOL_DOODLE_ON) == 1);
    bool bEOLDoodleEnabled = isShortcutAvailable(CHomeEnum::SHORTCUT_DOODLE_ID);

    if (bEOLDoodleEnabled != bDoodleEnabled)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, EOL for DOODLE changed:%d", __FUNCTION__, bEOLDoodleEnabled);
        bIsEOLChanged = true;
        if (bEOLDoodleEnabled)
        {
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_DOODLE_ON, 1);
        }
        else
        {
            CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_DOODLE_ON, 0);
        }
    }
    else
    {
        //Do nothing.
    }

    if (!m_bIsInitializationInProgress)
    {
        bool bAuxPersistancyStatus = (CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_EOL_AUX_ON) == 1);
        bool bAuxConnectionStatus = isShortcutAvailable(CHomeEnum::SHORTCUT_AUX_IN_ID);

        if (bAuxConnectionStatus != bAuxPersistancyStatus)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, EOL for AUX changed:%d", __FUNCTION__, bAuxConnectionStatus);
            if (bAuxConnectionStatus)
            {
                CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_AUX_ON, 1);
            }
            else
            {
                CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_EOL_AUX_ON, 0);

                for (int i = 0; i < CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE; i++)
                {
                    int _iShortcutId = CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_01 + i));
                    if (CHomeEnum::SHORTCUT_AUX_IN_ID == _iShortcutId)
                    {
                        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, remove SHORTCUT_AUX_IN_ID icon from home page", __FUNCTION__);
                        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_01 + i), 0);
                        break;
                    }
                    else
                    {
                        ////Do Nothing
                    }
                }
            }
        }
        else
        {
            //Do nothing.
        }
    }
    else
    {
        //Do nothing.
    }

    if (bIsEOLChanged)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, As EOL changed reset Home Shortcut values to default", __FUNCTION__);
        int newDefaultShortcuts[CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE] = {0};
        int iCurrentFillIndex = 0;

        for (int i = 0; i < CDHomeShortcut::DEFAULT_SHORTCUTS_AVAILABLE; i++)
        {
            if (isShortcutAvailable(static_cast<CHomeEnum::EHomeShortcutsUID>(CDHomeShortcut::DEFAULT_SHORTCUT_IDS[i])))
            {
                LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, adding default shortcut ID:%d, At index:%d", __FUNCTION__, CDHomeShortcut::DEFAULT_SHORTCUT_IDS[i], iCurrentFillIndex);
                newDefaultShortcuts[iCurrentFillIndex++] = CDHomeShortcut::DEFAULT_SHORTCUT_IDS[i];
                if ((CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE - 1) <= iCurrentFillIndex)
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, All default shortcut found", __FUNCTION__);
                    break;
                }
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, EOL not enabled for shortcut ID:%d, At index:%d", __FUNCTION__, CDHomeShortcut::DEFAULT_SHORTCUT_IDS[i], iCurrentFillIndex);
                //try to add next shortcut
            }
        }

        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_01, newDefaultShortcuts[0]);
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_02, newDefaultShortcuts[1]);
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_03, newDefaultShortcuts[2]);
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_04, newDefaultShortcuts[3]);
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_05, newDefaultShortcuts[4]);
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_06, newDefaultShortcuts[5]);
    }
    else
    {
        //Do nothing.
    }
}
//____________________________________________________________________________
void CHomeAdaptor::updateHomeScreenSlots()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);

    //Validate persistency for home module slots
    validateHomeSlotIndex(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_01);
    validateHomeSlotIndex(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_02);
    validateHomeSlotIndex(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_03);
    validateHomeSlotIndex(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_04);
    validateHomeSlotIndex(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_05);
    validateHomeSlotIndex(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_06);

    validateHomeWithEOLSettings();

    int _iShortcutPages;
    QList<int> _liShortcutsId;

    // add default position for first home page
    _liShortcutsId.append(CHomeEnum::SHORTCUT_ADD_SHORTCUT_ID);//empty info added as slot index starts from 1

    //adding first page slot shortcuts from persistency
    _liShortcutsId.append(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_01));
    _liShortcutsId.append(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_02));
    _liShortcutsId.append(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_03));
    _liShortcutsId.append(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_04));
    _liShortcutsId.append(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_05));
    _liShortcutsId.append(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_06));

    // add remaining shortcuts in title ascending order
    for (int i = 1; i < CHomeEnum::MAX_SHORTCUTS_AVAILABLE; i++)
    {
        //QString y = CDHomeShortcut::SHORTCUTS[i][5];
        if ("Y" == CDHomeShortcut::SHORTCUTS[i][5])
        {
            if (!_liShortcutsId.contains(i))
            {
                if (isShortcutAvailable((CHomeEnum::EHomeShortcutsUID)i))
                {
                    _liShortcutsId.append((CHomeEnum::EHomeShortcutsUID)i);
                }
            }
        }
    }

    // calculate count for page to be display on home screen
    int count = _liShortcutsId.count() - 1;
    _iShortcutPages = (count + (CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE - 1))/CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE;

    // add blank icons values on last page if required
    while ((_iShortcutPages * CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE) >= _liShortcutsId.count())
    {
        _liShortcutsId.append(CHomeEnum::SHORTCUT_BLANK_ID);
    }

    // set updated list and data to properties
    setShortcutsId(_liShortcutsId);
    setShortcutPages(_iShortcutPages);
}
//____________________________________________________________________________
void CHomeAdaptor::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);

    //connect slots to EOL signals
    connect(CVariantControlAdaptor::getInstance(),          SIGNAL(sigEOLAndroidAutoEnabledChanged()),              this,   SLOT(slotEOLChanged()));
    connect(CVariantControlAdaptor::getInstance(),          SIGNAL(sigEOLAppleCarPlayEnabledChanged()),             this,   SLOT(slotEOLChanged()));
    connect(CVehicleSettingsAdaptor::getInstance(),         SIGNAL(sigAmbientLightAvailableStatusChanged()),        this,   SLOT(slotEOLChanged()));
    connect(CVariantControlAdaptor::getInstance(),          SIGNAL(sigEOLDriveNextEnabledChanged()),                this,   SLOT(slotEOLChanged()));
    connect(CVariantControlAdaptor::getInstance(),          SIGNAL(sigEOLHMIDoodleEnabledChanged()),                this,   SLOT(slotEOLChanged()));

    //connect slots to module availability signals
    ////connect(CVehicleSettingsAdaptor::getInstance(),     SIGNAL(sigAmbientLightAvailableStatusChanged()),        this,   SLOT(sltHomeShortcutUpdateOnAmbientLight())); /*for future reference*/
    connect(CAudioAdaptor::getInstance(),                   SIGNAL(sigAUXConnectionStatuschanged()),                this,   SLOT(slotAvailabilityChanged_AuxIn()));
    connect(CAndroidAutoAdaptor::getInstance(),             SIGNAL(sigAndroidAutoConnectionStatusChanged(bool)),    this,   SLOT(slotActiveChanged_AndroidAuto(bool)));
    connect(CAudioAdaptor::getInstance(),                   SIGNAL(sigAUXSrcStatuschanged()),                       this,   SLOT(slotActiveChanged_AuxIn()));
    connect(CAudioAdaptor::getInstance(),                   SIGNAL(sigBTSrcStatuschanged()),                        this,   SLOT(slotActiveChanged_Bluetooth()));
    connect(CAppleCarPlayAdaptor::getInstance(),            SIGNAL(sigAppleCarPlayConnectionStatusChanged(bool)),   this,   SLOT(slotActiveChanged_CarPlay(bool)));
    ////connect(SOME_Adaptor::getInstance(),                SIGNAL(sig_SOMETHING_Changed(bool)),                    this,   SLOT(slotActiveChanged_ConnectNext(bool))); /*for future reference*/
    ////connect(SOME_Adaptor::getInstance(),                SIGNAL(sig_SOMETHING_Changed(bool)),                    this,   SLOT(slotActiveChanged_Contacts(bool))); /*for future reference*/
    connect(CDoodleApplication::getDoodleAdaptor(),         SIGNAL(sigDoodleProxyPresenceChanged()),                this,   SLOT(slotActiveChanged_Doodle()));
    connect(CDriveNextApplication::getDriveNextAdaptor(),   SIGNAL(sigDriveNextPresenceChanged()),                  this,   SLOT(slotActiveChanged_DriveNext()));
    connect(CW3WApplication::getW3WAdaptor(),               SIGNAL(sigW3WCoreProxyAvailability(bool)),              this,   SLOT(slotActiveChanged_W3W(bool)));
    ////connect(SOME_Adaptor::getInstance(),                SIGNAL(sig_SOMETHING_Changed(bool)),                    this,   SLOT(slotActiveChanged_Help(bool))); */for future reference*/
    connect(CAudioAdaptor::getInstance(),                   SIGNAL(sigIPODSrcStatuschanged()),                      this,   SLOT(slotActiveChanged_Ipod()));
    connect(CVehicleSettingsAdaptor::getInstance(),         SIGNAL(sigParkLampStatusChanged()),                     this,   SLOT(slotActiveChanged_AmbientLight()));
    ////connect(SOME_Adaptor::getInstance(),                SIGNAL(sig_SOMETHING_Changed(bool)),                    this,   SLOT(slotActiveChanged_Navigation(bool))); /*for future reference*/
    connect(CParkAssistAdaptor::getInstance(),              SIGNAL(sigParkAssistProxyStatusChanged(bool)),          this,   SLOT(slotActiveChanged_ParkAssist(bool)));
    ////connect(SOME_Adaptor::getInstance(),                SIGNAL(sig_SOMETHING_Changed(bool)),                    this,   SLOT(slotActiveChanged_Phone(bool))); /*for future reference*/
    connect(CAudioAdaptor::getInstance(),                   SIGNAL(sigFMSrcStatuschanged()),                        this,   SLOT(slotActiveChanged_Radio()));
    connect(CAudioAdaptor::getInstance(),                   SIGNAL(sigAMSrcStatuschanged()),                        this,   SLOT(slotActiveChanged_Radio()));
    connect(CAudioAdaptor::getInstance(),                   SIGNAL(sigUSBSrcStatuschanged()),                       this,   SLOT(slotActiveChanged_USB()));
    ////connect(SOME_Adaptor::getInstance(),                SIGNAL(sig_SOMETHING_Changed(bool)),                    this,   SLOT(slotActiveChanged_VoiceCommand(bool))); /*for future reference*/
    ////connect(SOME_Adaptor::getInstance(),                SIGNAL(sig_SOMETHING_Changed(bool)),                    this,   SLOT(slotActiveChanged_AudioSetting(bool))); /*for future reference*/
    ////connect(SOME_Adaptor::getInstance(),                SIGNAL(sig_SOMETHING_Changed(bool)),                    this,   SLOT(slotActiveChanged_VehicleSetting(bool))); /*for future reference*/
    ////connect(SOME_Adaptor::getInstance(),                SIGNAL(sig_SOMETHING_Changed(bool)),                    this,   SLOT(slotActiveChanged_AudioPreset(bool))); /*for future reference*/
    ////connect(SOME_Adaptor::getInstance(),                SIGNAL(sig_SOMETHING_Changed(bool)),                    this,   SLOT(slotActiveChanged_Themes(bool))); /*for future reference*/

    //Call slots to sync with current values
    //slotEOLChanged();
    slotActiveChanged_Doodle();
}
//____________________________________________________________________________
void CHomeAdaptor::linkShortcutCallbackFunctions()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "CHomeAdaptor::linkShortcutCallbackFunctions");
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_ADD_SHORTCUT_ID])->    onButtonClickCBFunction = &CHomeAdaptor::cbAddShortcutClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_ANDROID_AUTO_ID])->    onButtonClickCBFunction = &CHomeAdaptor::cbAndroidAutoClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_AUX_IN_ID])->          onButtonClickCBFunction = &CHomeAdaptor::cbAuxInClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_BLUETOOTH_ID])->       onButtonClickCBFunction = &CHomeAdaptor::cbBluetoothClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_APPLE_CAR_PLAY_ID])->  onButtonClickCBFunction = &CHomeAdaptor::cbCarPlayClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_CONNECT_NEXT_ID])->    onButtonClickCBFunction = &CHomeAdaptor::cbConnectNextClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_CONTACTS_ID])->        onButtonClickCBFunction = &CHomeAdaptor::cbContactsClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_DOODLE_ID])->          onButtonClickCBFunction = &CHomeAdaptor::cbDoodleClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_DRIVENEXT_ID])->       onButtonClickCBFunction = &CHomeAdaptor::cbDriveNextClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_FAVOURITE_ID])->       onButtonClickCBFunction = &CHomeAdaptor::cbFavouriteClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_HELP_ID])->            onButtonClickCBFunction = &CHomeAdaptor::cbHelpClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_IPOD_ID])->            onButtonClickCBFunction = &CHomeAdaptor::cbIpodClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_AMBIENT_LIGHT_ID])->   onButtonClickCBFunction = &CHomeAdaptor::cbAmbientLightClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_NAVIGATION_ID])->      onButtonClickCBFunction = &CHomeAdaptor::cbNavigationClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_PARK_ASSIST_ID])->     onButtonClickCBFunction = &CHomeAdaptor::cbParkAssistClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_PHONE_ID])->           onButtonClickCBFunction = &CHomeAdaptor::cbPhoneClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_PHONE_SETUP_ID])->     onButtonClickCBFunction = &CHomeAdaptor::cbPhoneSetupClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_RADIO_ID])->           onButtonClickCBFunction = &CHomeAdaptor::cbRadioClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_USB_ID])->             onButtonClickCBFunction = &CHomeAdaptor::cbUSBClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_VOICE_COMMAND_ID])->   onButtonClickCBFunction = &CHomeAdaptor::cbVoiceCommandClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_AUDIO_SETUP_ID])->     onButtonClickCBFunction = &CHomeAdaptor::cbAudioSettingClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_VEHICLE_SETTING_ID])-> onButtonClickCBFunction = &CHomeAdaptor::cbVehicleSettingClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_THEMES_ID])->          onButtonClickCBFunction = &CHomeAdaptor::cbThemesClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_SETTINGS_MAIN_ID])->   onButtonClickCBFunction = &CHomeAdaptor::cbSettingsClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_W3W_ID])->             onButtonClickCBFunction = &CHomeAdaptor::cbW3WClicked;
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_SOUNDDEMO_ID])->       onButtonClickCBFunction = &CHomeAdaptor::cbSoundDemoClicked;
}
//____________________________________________________________________________
void CHomeAdaptor::initUnusedShortcutsList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    m_pHomeUpdateShortcutModel->clearList();
    for (int i = (CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE + 1); i < m_liShortcutsId.count(); i++)
    {
        if (0 < m_liShortcutsId[i])
        {
            m_pHomeUpdateShortcutModel->addItem(m_liShortcutsId[i]);
        }
    }
    emit sigUnusedShortcutsChanged();
}

void CHomeAdaptor::initFavKeyModel()
{
    m_eFavKeyCode = static_cast<CHardKeyEnum::EFavKeyCode>(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_FAVORITE_SCREEN_OPTION_SELECTION));

    m_objHomeFavKeyModel.removeRows();
    m_liFavHK.clear();

    /**
     * We are using home shortcut database to fill configure FavHK screen options data, that's why
     * we have added source option as well in home shortcut datatbase(HomeDef.h) with availability(DID)
    * coloumns "N"(NO) so that it will not get added in home shortcut. that's why adding source option directly without checking for DID availability.
    */
    m_objHomeFavKeyModel.insertRows(new SConfigureFavHKData(CHardKeyEnum::FAV_HK_SOURCE, CHomeEnum::SHORTCUT_TOGGLE_SOURCE_ID));
    m_liFavHK.append(CHardKeyEnum::FAV_HK_SOURCE);
    addItemFavKeyModel(CHardKeyEnum::FAV_HK_AUDIO_SETUP, CHomeEnum::SHORTCUT_AUDIO_SETUP_ID);
    addItemFavKeyModel(CHardKeyEnum::FAV_HK_FAVOURITES, CHomeEnum::SHORTCUT_FAVOURITE_ID);
    addItemFavKeyModel(CHardKeyEnum::FAV_HK_VOICE_COMMAND, CHomeEnum::SHORTCUT_VOICE_COMMAND_ID);
    addItemFavKeyModel(CHardKeyEnum::FAV_HK_ANDROIDAUTO, CHomeEnum::SHORTCUT_ANDROID_AUTO_ID);
    addItemFavKeyModel(CHardKeyEnum::FAV_HK_CARPLAY, CHomeEnum::SHORTCUT_APPLE_CAR_PLAY_ID);
    if(!m_liFavHK.contains(m_eFavKeyCode))
    {
        m_eFavKeyCode = CHardKeyEnum::FAV_HK;
    }
}

void CHomeAdaptor::addItemFavKeyModel(CHardKeyEnum::EFavKeyCode eFavHKId, CHomeEnum::EHomeShortcutsUID eShortcutId)
{
    // 5 here represent 5th coloumn which is availability column of shortcuts in HomeDef.
    if(isShortcutAvailable(eShortcutId) && CDHomeShortcut::SHORTCUTS[eShortcutId][5] == "Y")
    {
        m_objHomeFavKeyModel.insertRows(new SConfigureFavHKData(eFavHKId, eShortcutId));
        m_liFavHK.append(eFavHKId);
    }
}
//____________________________________________________________________________
void CHomeAdaptor::cbAddShortcutClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    setShortcutToEdit(iShortcutIndex);
    CHMIMain::getSM()->getSCI_Home()->raise_evHomeScreenUpdateShortcutsActivated();
}
//____________________________________________________________________________
void CHomeAdaptor::cbAndroidAutoClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CAndroidAutoAdaptor::getInstance()->launchAndroidAuto();
}
//____________________________________________________________________________
void CHomeAdaptor::cbAuxInClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CAudioAdaptor::getInstance()->setActiveEntSrc(CAudioEnums::SRC_AUDIO_AUX);
}
//____________________________________________________________________________
void CHomeAdaptor::cbBluetoothClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CAudioAdaptor::getInstance()->setActiveEntSrc(CAudioEnums::SRC_BT_A2DP1);
}
//____________________________________________________________________________
void CHomeAdaptor::cbCarPlayClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CAppleCarPlayAdaptor::getInstance()->launchAppleCarPlay();
}
//____________________________________________________________________________
void CHomeAdaptor::cbConnectNextClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
}
//____________________________________________________________________________
void CHomeAdaptor::cbContactsClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->invSwitchToPhoneBrowse(CPhoneEnum::PHONE_BROWSE_TYPE_CONTACTS);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HOME, "Phone adaptor not available");
    }
}
//____________________________________________________________________________
void CHomeAdaptor::cbDoodleClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CHMIMain::getSM()->raise_evDoodleSetupActivated();
}
//____________________________________________________________________________
void CHomeAdaptor::cbDriveNextClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CHMIMain::getSM()->raise_evDriveNextActivated();
}
//____________________________________________________________________________
void CHomeAdaptor::cbFavouriteClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->invSwitchToPhoneBrowse(CPhoneEnum::PHONE_BROWSE_TYPE_FAVORITES);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HOME, "Phone adaptor not available");
    }
}
//____________________________________________________________________________
void CHomeAdaptor::cbHelpClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
}
//____________________________________________________________________________
void CHomeAdaptor::cbIpodClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CAudioAdaptor::getInstance()->setActiveEntSrc(CAudioEnums::SRC_IPOD);
}
//____________________________________________________________________________
void CHomeAdaptor::cbAmbientLightClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CSetupAdaptor::getInstance()->launchAmbientLightSettings();
}
//____________________________________________________________________________
void CHomeAdaptor::cbNavigationClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
}
//____________________________________________________________________________
void CHomeAdaptor::cbParkAssistClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CParkAssistAdaptor::getInstance()->activatePdcRvc(true);
}
//____________________________________________________________________________
void CHomeAdaptor::cbPhoneClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    if(CPhoneAdaptor::getInstance())
    {
        CPhoneAdaptor::getInstance()->invSwitchToPhoneBrowse(CPhoneEnum::PHONE_BROWSE_TYPE_CALL_LOGS);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HOME, "Phone adaptor not available");
    }
}

void CHomeAdaptor::cbPhoneSetupClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CHMIMain::getSM()->getSCI_Setup()->raise_evBluetoothSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_BT_NAMED_ENTRY());
}
//____________________________________________________________________________
void CHomeAdaptor::cbRadioClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CTunerAdaptor::getInstance()->launchTuner();
}
//____________________________________________________________________________
void CHomeAdaptor::cbUSBClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CAudioAdaptor::getInstance()->setActiveEntSrc(CAudioEnums::SRC_USB1);
}
//____________________________________________________________________________
void CHomeAdaptor::cbVoiceCommandClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CVRAdaptor::getInstance()->activateVRSession(CHardKeyEnum::HKEY_STATE_RELEASED);
}
//____________________________________________________________________________
void CHomeAdaptor::cbAudioSettingClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CHMIMain::getSM()->getSCI_Setup()->raise_evAudioSetupActivated(CHMIMain::getSM()->getDefaultSCI()->get_sETUP_SCR_AUDIO_NAMED_ENTRY());
}
//____________________________________________________________________________
void CHomeAdaptor::cbVehicleSettingClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CSetupAdaptor::getInstance()->launchVehicleSettings();
}
//____________________________________________________________________________

void CHomeAdaptor::cbThemesClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CSetupAdaptor::getInstance()->launchThemeSettings();
}
//____________________________________________________________________________
void CHomeAdaptor::cbAudioPresetClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
}
//____________________________________________________________________________

void CHomeAdaptor::cbSettingsClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CHMIMain::getSM()->raise_evSetupActivated();
}
//____________________________________________________________________________

void CHomeAdaptor::cbW3WClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CHMIMain::getSM()->raise_evW3WActivated();
}
//____________________________________________________________________________

void CHomeAdaptor::cbSoundDemoClicked(int iShortcutIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index: %d", __FUNCTION__, iShortcutIndex);
    CAudioAdaptor::getInstance()->setActiveEntSrc(CAudioEnums::SRC_HDD);

}
//____________________________________________________________________________
///////////////////////////////////////////////////////////////////////////////
// Property related functions
///////////////////////////////////////////////////////////////////////////////
QList<QObject*> CHomeAdaptor::homeShortcutsList()
{
    return m_lCDHomeShortcuts;
}
//____________________________________________________________________________
QList<int> CHomeAdaptor::shortcutsId()
{
    return m_liShortcutsId;
}
void CHomeAdaptor::setShortcutsId(QList<int> liShortcutList)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    if (m_liShortcutsId != liShortcutList)
    {
        m_liShortcutsId = liShortcutList;
        emit sigShortcutsIdChanged();
        emit sigShortcutsLengthChanged();
    }
}
//____________________________________________________________________________
CHardKeyEnum::EFavKeyCode CHomeAdaptor::eCurrentFavKeyCode()
{
    LOG_WARNING(Log::e_LOG_CONTEXT_HOME, "%s, current Fav HK : %d",__FUNCTION__, m_eFavKeyCode);
    return m_eFavKeyCode;
}
void CHomeAdaptor::setCurrentFavKeyCode(CHardKeyEnum::EFavKeyCode eFavKeyCode)
{
    LOG_WARNING(Log::e_LOG_CONTEXT_HOME, "%s, Fav HK : %d",__FUNCTION__, eFavKeyCode);

    if (eFavKeyCode != m_eFavKeyCode)
    {
        m_eFavKeyCode = eFavKeyCode;
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_FAVORITE_SCREEN_OPTION_SELECTION, m_eFavKeyCode);
    }
}
//____________________________________________________________________________
int CHomeAdaptor::shortcutPages()
{
    return m_iShortcutPages;
}
void CHomeAdaptor::setShortcutPages(int iPageCount)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, value:%d", __FUNCTION__, iPageCount);
    if (m_iShortcutPages != iPageCount)
    {
        m_iShortcutPages = iPageCount;
        emit sigShortcutPagesChanged();
    }
}
//____________________________________________________________________________
int CHomeAdaptor::currentPageIndex()
{
    return m_iCurrentPageIndex;
}
void CHomeAdaptor::setCurrentPageIndex(int iCurrentPageIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, index:%d", __FUNCTION__, iCurrentPageIndex);
    if (m_iCurrentPageIndex != iCurrentPageIndex)
    {
        m_iCurrentPageIndex = iCurrentPageIndex;
        updateHomeButtonEnableStatus();
        emit sigCurrentPageIndexChanged();
    }
}
//____________________________________________________________________________
void CHomeAdaptor::updateHomeButtonEnableStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, m_iCurrentPageIndex:%d", __FUNCTION__, m_iCurrentPageIndex);
    bool bStatus = true;
    if (isOnHomeScreen())
    {
        bStatus = (m_iCurrentPageIndex > 0);
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, In Home Screen", __FUNCTION__);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, Out of Home Screen", __FUNCTION__);
        //Do Nothing!
    }
    CDrawersAdaptor::getInstance()->setEnableHomeButton(bStatus);

    //CDrawersAdaptor::getInstance()->setEnableHomeButton((m_iCurrentPageIndex > 0));
}
//____________________________________________________________________________
int CHomeAdaptor::shortcutToEdit()
{
    return m_iShortcutToEdit;
}
void CHomeAdaptor::setShortcutToEdit(int iShortcutId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, value:%d", __FUNCTION__, iShortcutId);
    if (m_iShortcutToEdit != iShortcutId)
    {
        m_iShortcutToEdit = iShortcutId;
        emit sigShortcutToEditChanged();
    }
}
//____________________________________________________________________________
bool CHomeAdaptor::isOnHomeScreen()
{
    return m_bOnHomeScreen;
}
void CHomeAdaptor::setOnHomeScreen(bool bStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus:%d", __FUNCTION__, bStatus);
    m_bOnHomeScreen = bStatus;
    updateHomeButtonEnableStatus();
}
//____________________________________________________________________________
bool CHomeAdaptor::isShortcutOnDisplayScreen(const CHomeEnum::EHomeShortcutsUID eShortcutId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, shortcutId:%d",__FUNCTION__, static_cast<int>(eShortcutId));

    bool bShortcutOnDisplay = false;

    if (CHMIMain::getSM()->isStateActive(CHMIMain::getSM()->startup_region_Ui_home_Main_main_Home_home_HomeScreenMain))
    {
        int iStartSlotIndex = (m_iCurrentPageIndex * CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE) + 1;
        for (int i = iStartSlotIndex; i < (iStartSlotIndex + CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE); i++)
        {
            if (m_liShortcutsId.length() <= i)
            {
                break;//list end
            }
            else if(eShortcutId == m_liShortcutsId[i])
            {
                bShortcutOnDisplay = true;//icon found
                break;
            }
        }
    }
    return bShortcutOnDisplay;
}
//____________________________________________________________________________
int CHomeAdaptor::shortcutsLength()
{
    return m_liShortcutsId.count();
}
//____________________________________________________________________________
CHomeUpdateShortcutModel* CHomeAdaptor::unusedShortcuts()
{
    return m_pHomeUpdateShortcutModel;
}

CHomeConfigureFavHKModel* CHomeAdaptor::objFavKeyListModel()
{
    return &m_objHomeFavKeyModel;
}
///////////////////////////////////////////////////////////////////////////////
// QML related functions
///////////////////////////////////////////////////////////////////////////////
void CHomeAdaptor::invUpdateShortcut(int iShortcutIndex, int iShortcutId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    if (-1 == iShortcutId)
    {
        iShortcutId = m_iShortcutToEdit;
    }
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, update shortcut at %d", __FUNCTION__, iShortcutId);

    switch (iShortcutId)
    {
    case 1:
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_01, iShortcutIndex);
        break;
    case 2:
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_02, iShortcutIndex);
        break;
    case 3:
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_03, iShortcutIndex);
        break;
    case 4:
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_04, iShortcutIndex);
        break;
    case 5:
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_05, iShortcutIndex);
        break;
    case 6:
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_06, iShortcutIndex);
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_HOME,"%s :%s", __FUNCTION__, "invalid shortcut index");
        break;
    }
    updateHomeScreenSlots();
}

void CHomeAdaptor::invShowUpdateHomeShortcutPopup(int iSlotIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, iSlotIndex : %d ", __FUNCTION__, iSlotIndex);
    setShortcutToEdit(iSlotIndex);
    CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_HOME_EDIT_SHORTCUT);
}

QString CHomeAdaptor::invShortcutToEditTitle()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, m_iShortcutToEdit : %d ", __FUNCTION__, m_iShortcutToEdit);
    QString _title = "";
    if((0 < m_iShortcutToEdit) && (CDHomeShortcut::MAX_SHORTCUT_SLOTS_AVAILABLE_PER_PAGE >= m_iShortcutToEdit))
    {
        int shortcutID = m_liShortcutsId[m_iShortcutToEdit];
        _title = static_cast<CDHomeShortcut*>(m_lCDHomeShortcuts.at(shortcutID))->text();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME,"%s , invalid shortcut %d",__FUNCTION__, m_iShortcutToEdit);
    }
    return _title;
}

bool CHomeAdaptor::invIsFixedShortcut(CHomeEnum::EHomeShortcutsUID eShortcutID)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);

    bool bIsFixed = false;
    switch(eShortcutID)
    {
    case CHomeEnum::SHORTCUT_ANDROID_AUTO_ID:
    case CHomeEnum::SHORTCUT_APPLE_CAR_PLAY_ID:
    {
        bIsFixed = true;
    }
        break;
    default:
    {
        // do nothing
    }
        break;
    }

    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, %d is Fix %d", __FUNCTION__, eShortcutID, bIsFixed);
    return bIsFixed;
}

///////////////////////////////////////////////////////////////////////////////
// Functions to propogate calls to other adaptor, resource layer and statemachine
///////////////////////////////////////////////////////////////////////////////
void CHomeAdaptor::slotActiveChanged_AndroidAuto(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_ANDROID_AUTO_ID])->setIsActive(bActiveStatus);
#ifndef TATA_X445
    slotActiveChanged_VoiceCommand(!bActiveStatus);
#endif
}
void CHomeAdaptor::slotActiveChanged_AuxIn()
{
    bool bStatus = CAudioAdaptor::getInstance()->auxSrcStatus();
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_AUX_IN_ID])->setIsActive(bStatus);
}
void CHomeAdaptor::slotActiveChanged_Bluetooth()
{
    bool bStatus = CAudioAdaptor::getInstance()->btSrcStatus();
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_BLUETOOTH_ID])->setIsActive(bStatus);
}
void CHomeAdaptor::slotActiveChanged_CarPlay(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_APPLE_CAR_PLAY_ID])->setIsActive(bActiveStatus);
#ifndef TATA_X445
    slotActiveChanged_VoiceCommand(!bActiveStatus);
#endif
}
void CHomeAdaptor::slotActiveChanged_ConnectNext(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_CONNECT_NEXT_ID])->setIsActive(bActiveStatus);
}
void CHomeAdaptor::slotActiveChanged_Contacts(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_CONTACTS_ID])->setIsActive(bActiveStatus);
}
void CHomeAdaptor::slotActiveChanged_Doodle()
{
    bool bActiveStatus = CDoodleApplication::getDoodleAdaptor() && CDoodleApplication::getDoodleAdaptor()->doodleProxyPresence();
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_DOODLE_ID])->setIsActive(bActiveStatus);
}
void CHomeAdaptor::slotActiveChanged_DriveNext()
{
    bool bActiveStatus = CDriveNextApplication::getDriveNextAdaptor() && CDriveNextApplication::getDriveNextAdaptor()->driveNextPresence();
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_DRIVENEXT_ID])->setIsActive(bActiveStatus);
}
void CHomeAdaptor::slotActiveChanged_Favourite(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_FAVOURITE_ID])->setIsActive(bActiveStatus);
}
void CHomeAdaptor::slotActiveChanged_Help(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_HELP_ID])->setIsActive(bActiveStatus);
}
void CHomeAdaptor::slotActiveChanged_Ipod()
{
    bool bStatus = CAudioAdaptor::getInstance()->ipodSrcStatus();
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_IPOD_ID])->setIsActive(bStatus);
}
void CHomeAdaptor::slotActiveChanged_AmbientLight()
{
    bool bStatus = CVehicleSettingsAdaptor::getInstance()->parkLampStatus();
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_AMBIENT_LIGHT_ID])->setIsActive(bStatus);
}
void CHomeAdaptor::slotActiveChanged_Navigation(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_NAVIGATION_ID])->setIsActive(bActiveStatus);
}
void CHomeAdaptor::slotActiveChanged_ParkAssist(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_PARK_ASSIST_ID])->setIsActive(bActiveStatus);
}
void CHomeAdaptor::slotActiveChanged_Phone(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_PHONE_ID])->setIsActive(bActiveStatus);
}
void CHomeAdaptor::slotActiveChanged_Radio()
{
    bool bStatus = (CAudioAdaptor::getInstance()->fmSrcStatus() || CAudioAdaptor::getInstance()->amSrcStatus()) ;
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_RADIO_ID])->setIsActive(bStatus);
}
void CHomeAdaptor::slotActiveChanged_USB()
{
    bool bStatus = CAudioAdaptor::getInstance()->usbSrcStatus();
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_USB_ID])->setIsActive(bStatus);
}
void CHomeAdaptor::slotActiveChanged_VoiceCommand(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_VOICE_COMMAND_ID])->setIsActive(bActiveStatus);
}

void CHomeAdaptor::slotActiveChanged_VehicleSetting(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_VEHICLE_SETTING_ID])->setIsActive(bActiveStatus);
}

void CHomeAdaptor::slotActiveChanged_AudioSetting(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_AUDIO_SETUP_ID])->setIsActive(bActiveStatus);
}

void CHomeAdaptor::slotActiveChanged_Themes(bool bActiveStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, bStatus : %d ", __FUNCTION__, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_THEMES_ID])->setIsActive(bActiveStatus);
}

void CHomeAdaptor::slotAvailabilityChanged_AuxIn()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, eAuxConnectionStatus : %d ", __FUNCTION__, CAudioAdaptor::getInstance()->auxConnectionStatus());

    slotEOLChanged();
    initUnusedShortcutsList();
}
//____________________________________________________________________________
void CHomeAdaptor::sltPowerModeChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);

    switch (CPowerModeAdaptor::getInstance().getPowerModeStatus())
    {
    case CPowerModeEnums::VPM_EARLY_WAKEUP:
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, reset Home data for VPM_EARLY_WAKEUP", __FUNCTION__);
        setCurrentPageIndex(0);
        break;

    case CPowerModeEnums::VPM_MEDIA_OFF:
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, VPM_MEDIA_OFF : Audio Setup tile inactive", __FUNCTION__);
        ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_AUDIO_SETUP_ID])->setIsActive(false);
        break;

    case CPowerModeEnums::VPM_ACTIVE:
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, VPM_ACTIVE : Park Assist tile active", __FUNCTION__);
        ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_PARK_ASSIST_ID])->setIsActive(true);
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, VPM_ACTIVE : Audio Setup tile active", __FUNCTION__);
        ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_AUDIO_SETUP_ID])->setIsActive(true);
        break;

    case CPowerModeEnums::VPM_ONE_HOUR:
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, VPM_ONE_HOUR : Park Assist tile inactive", __FUNCTION__);
        ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_PARK_ASSIST_ID])->setIsActive(false);
        LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, VPM_ONE_HOUR : Audio Setup tile active", __FUNCTION__);
        ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_AUDIO_SETUP_ID])->setIsActive(true);
        break;

    default:
        // Do Nothing
        break;
    }
}
//____________________________________________________________________________
void CHomeAdaptor::slotActiveChanged_W3W(bool w3wCoreProxyStatus)
{
    bool bActiveStatus = CW3WApplication::getW3WAdaptor() && CW3WApplication::getW3WAdaptor()->w3wFeatureSupportStatus();
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, w3wCoreProxyStatus: %d, bStatus : %d ", __FUNCTION__, w3wCoreProxyStatus, bActiveStatus);
    ((CDHomeShortcut*)m_lCDHomeShortcuts[CHomeEnum::SHORTCUT_W3W_ID])->setIsActive(bActiveStatus);
}
//____________________________________________________________________________

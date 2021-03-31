/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CRCAAdaptor.h
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CRCAAdaptor, an Adaptor for RCA module,
 * CRCAAdaptor used to communicate between QML and Resource Layer.
 */


#include "CRCAAdaptor.h"
#include "ResourceFactory.hpp"
#include "CSetupAdaptor.h"
#include "RCAResource/interfaces/IRCAResource.h"
#include "HMIIncludes.h"
#include <CFramework.h>

CRCAAdaptor* CRCAAdaptor::m_pRCAAdaptor = nullptr;

CRCAAdaptor::CRCAAdaptor(QObject *pParent) : QObject(pParent)
  , m_iRCAActionsInitiated(0)
  , m_strAuxGainText("")
  , m_strAudioPresetText("")
  , m_iBassMidTrebleValue(0)
  , m_strBassMidTrebleName("")
  , m_strBalanceFaderImageSource("")
  , m_bIsHMIInBrowseState(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    CFramework::getFramework().setContextProperty("cppRCAAdaptor", this);
    CRCAEnums::registerRCAEnumsToQML();
    connectSignals();
}

CRCAAdaptor::~CRCAAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    m_pRCAAdaptor = nullptr;
}

CRCAAdaptor* CRCAAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    if(nullptr == m_pRCAAdaptor)
    {
        m_pRCAAdaptor = new CRCAAdaptor();
    }
    return m_pRCAAdaptor;
}

void CRCAAdaptor::connectSignals()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);

    connect(CAudioAdaptor::getInstance(), SIGNAL(sigBassChanged())  , this, SLOT(sltBassChanged()), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigMidChanged())   , this, SLOT(sltMidChanged()), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigTrebleChanged()), this, SLOT(sltTrebleChanged()), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigActiveAudioPresetChanged()), this, SLOT(sltAudioPresetChanged()), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigBalanceChanged()), this, SLOT(sltBalanceFaderChanged()), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigFadeChanged()), this, SLOT(sltBalanceFaderChanged()), Qt::QueuedConnection);
    connect(CAudioAdaptor::getInstance(), SIGNAL(sigAuxGainValueChanged()), this, SLOT(sltAuxGainValueChanged()),Qt::QueuedConnection);
    connect(&CMediaAdaptor::getInstance(), SIGNAL(sigNowPlayingChanged()), this, SLOT(sltNowPlayingChanged()), Qt::QueuedConnection);
    connect(CPopupManager::getInstance(), SIGNAL(sigPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)), this, SLOT(sltPopupResult(CPopupEnum::EPopupID, CPopupEnum::EPopupResult, QString)));
}

void CRCAAdaptor::setRCAActionsInitiated(CRCAEnums::ERCAActionInitiated eRCAActionInitiated, uint uiIntInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s, m_iRCAActionsInitiated %i bit set", __FUNCTION__, static_cast<int>(eRCAActionInitiated));
    /* Set the specific bit for RCA Action initiated */
    m_iRCAActionsInitiated |= ( 1 << static_cast<int>(eRCAActionInitiated) );

    //Invoke RCA related cases from here
    if(isRCAActionSet(CRCAEnums::RCA_PICTURE_SELECTED))
    {
        //Inform Media adaptor to display PV
        CMediaAdaptor::getInstance().processRCARequest(CRCAEnums::RCA_PICTURE_SELECTED, uiIntInfo);
    }
    else
    {
        //Do nothing
    }
}

bool CRCAAdaptor::isRCAActionSet(CRCAEnums::ERCAActionInitiated eRCAAction)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s, m_iRCAActionsInitiated contains %i", __FUNCTION__, m_iRCAActionsInitiated);
    /* If the bit for specified RCA Action is set, then return true, otherwise false */
    return m_iRCAActionsInitiated & ( 1 <<static_cast<int>(eRCAAction) );
}

void CRCAAdaptor::clearRCAAction(CRCAEnums::ERCAActionInitiated eRCAAction)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s, m_iRCAActionsInitiated %i bit cleared", __FUNCTION__, static_cast<int>(eRCAAction));
    /* Clear the specific bit after processing the action */
    m_iRCAActionsInitiated &= ~(1<<eRCAAction);
}

int CRCAAdaptor::iBassMidTrebleValue()
{
    return m_iBassMidTrebleValue;
}

QString CRCAAdaptor::strBassMidTrebleName()
{
    return m_strBassMidTrebleName;
}

QString CRCAAdaptor::strAuxGainText()
{
    return m_strAuxGainText;
}

QString CRCAAdaptor::strAudioPresetText()
{
    return m_strAudioPresetText;
}

QString CRCAAdaptor::strBalanceFaderImageSource()
{
    return m_strBalanceFaderImageSource;
}

void CRCAAdaptor::setBassMidTrebleValue(int iBassMidTrebleValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s set - bass/Mid/Treble Value :%d", __FUNCTION__, iBassMidTrebleValue);
    if(iBassMidTrebleValue != m_iBassMidTrebleValue)
    {
        m_iBassMidTrebleValue = iBassMidTrebleValue;
        emit sigBassMidTrebleValueChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s Values are same", __FUNCTION__);
    }
}

void CRCAAdaptor::setBassMidTrebleName(const QString &strBassMidTrebleName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s set - bassMidTrebleName :%s", __FUNCTION__, strBassMidTrebleName.toStdString().c_str());
    if(strBassMidTrebleName != m_strBassMidTrebleName)
    {
        m_strBassMidTrebleName = strBassMidTrebleName;
        emit sigBassMidTrebleNameChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s Values are same", __FUNCTION__);
    }
}

void CRCAAdaptor::setAuxGainText(const QString &strAuxGainText)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s set - strAuxGainText :%s", __FUNCTION__, strAuxGainText.toStdString().c_str());
    if(strAuxGainText != m_strAuxGainText)
    {
        m_strAuxGainText = strAuxGainText;
        emit sigAuxGainTextChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s Values are same", __FUNCTION__);
    }
}

void CRCAAdaptor::setAudioPresetText(const QString &strAudioPresetText)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s set - strAudioPresetText :%s", __FUNCTION__, strAudioPresetText.toStdString().c_str());
    if(strAudioPresetText != m_strAudioPresetText)
    {
        m_strAudioPresetText = strAudioPresetText;
        emit sigAudioPresetTextChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s Values are same", __FUNCTION__);
    }
}

void CRCAAdaptor::setBalanceFaderImageSource(const QString &strBalanceFaderImageSource)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s set - strBalanceFaderImageSource :%s", __FUNCTION__, strBalanceFaderImageSource.toStdString().c_str());
    if(strBalanceFaderImageSource != m_strBalanceFaderImageSource)
    {
        m_strBalanceFaderImageSource = strBalanceFaderImageSource;
        emit sigBalanceFaderImageSourceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_RCA,"%s Values are same", __FUNCTION__);
    }
}

void CRCAAdaptor::setHMIMediaBrowseStatus(bool bIsHMIInBrowseState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s: HMI Browse State: %d", __FUNCTION__, bIsHMIInBrowseState);
    if(ResourceFactory::getRCAResource())
    {
        /* Mismatch check to avoid sending multiple request to RCA resource for same value */
        if(m_bIsHMIInBrowseState != bIsHMIInBrowseState)
        {
            ResourceFactory::getRCAResource()->setHMIMediaBrowseStatusAsyncReq(bIsHMIInBrowseState);
            m_bIsHMIInBrowseState = bIsHMIInBrowseState;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_RCA,"%s, m_bIsHMIInBrowseState is unchanged",__FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_RCA,"%s, RCA resource is NULL",__FUNCTION__);
    }
}

void CRCAAdaptor::showBassMidTreblePopup()
{
    LOG_WARNING(Log::e_LOG_CONTEXT_RCA,"%s",__FUNCTION__);

//    // Blocking audioPreset update notification when audioPreset screen is displaying.
    if(isAudioSetupStateActive() && (CSetupEnums::AUDIOSETUP_BMT_AUDIO_PRESET_SCREEN == CSetupAdaptor::getInstance()->eCurrentAudioSettingsScreen()))
    {
        // Will close already displayed audioPreset update notification if user tries to update again and screen is displaying.
        CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_RCA_BMT);
    }
    else
    {
        CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_RCA_BMT);
    }
}

bool CRCAAdaptor::isAudioSetupStateActive()
{
    return CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_Setup_setup_region_AudioSetup);
}

void CRCAAdaptor::sltBassChanged()
{
    int iBass = CAudioAdaptor::getInstance()->bass();
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s: Bass: %d", __FUNCTION__, iBass);

    if(isRCAActionSet(CRCAEnums::RCA_BASS_UPDATED))
    {
        setBassMidTrebleValue(iBass);
        setBassMidTrebleName(tr("TEXT_AUDIO_SETTING_BASS"));

        showBassMidTreblePopup();

        /* Clear RCA_BASS_UPDATED RCA Action after processing it */
        clearRCAAction(CRCAEnums::RCA_BASS_UPDATED);
    }
    else
    {
        // do nothing
    }
}

void CRCAAdaptor::sltMidChanged()
{
    int iMid = CAudioAdaptor::getInstance()->mid();
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s: Middle: %d", __FUNCTION__, iMid);

    if(isRCAActionSet(CRCAEnums::RCA_MIDDLE_UPDATED))
    {
        setBassMidTrebleValue(iMid);
        setBassMidTrebleName(tr("TEXT_AUDIO_SETTING_MIDDLE"));

        showBassMidTreblePopup();

        /* Clear RCA_MIDDLE_UPDATED RCA Action after processing it */
        clearRCAAction(CRCAEnums::RCA_MIDDLE_UPDATED);
    }
    else
    {
        // do nothing
    }
}

void CRCAAdaptor::sltTrebleChanged()
{
    int iTreble = CAudioAdaptor::getInstance()->treble();
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s: Treble: %d", __FUNCTION__, iTreble);

    if(isRCAActionSet(CRCAEnums::RCA_TREBLE_UPDATED))
    {
        setBassMidTrebleValue(iTreble);
        setBassMidTrebleName(tr("TEXT_AUDIO_SETTING_TREBLE"));

        showBassMidTreblePopup();

        /* Clear RCA_TREBLE_UPDATED RCA Action after processing it */
        clearRCAAction(CRCAEnums::RCA_TREBLE_UPDATED);
    }
    else
    {
        // do nothing
    }
}

void CRCAAdaptor::sltAudioPresetChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s: Preset: %d", __FUNCTION__, CAudioAdaptor::getInstance()->activeAudioPreset());

    if(isRCAActionSet(CRCAEnums::RCA_PRESET_UPDATED))
    {

        setAudioPresetText(CAudioAdaptor::getInstance()->activeAudioPresetName());

//        // Blocking audioPreset update notification when audioPreset screen is displaying.
        if(isAudioSetupStateActive() && (CSetupEnums::AUDIOSETUP_BMT_AUDIO_PRESET_SCREEN == CSetupAdaptor::getInstance()->eCurrentAudioSettingsScreen()))
        {
            // Will close already displayed audioPreset update notification if user tries to update again and screen is displaying.
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_RCA_AUDIO_PRESET);
        }
        else
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_RCA_AUDIO_PRESET);
        }

        /* Clear RCA_PRESET_UPDATED RCA Action after processing it */
        clearRCAAction(CRCAEnums::RCA_PRESET_UPDATED);
    }
    else
    {
        // do nothing
    }
}

void CRCAAdaptor::sltBalanceFaderChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s: Balance: %d Fader: %d", __FUNCTION__, CAudioAdaptor::getInstance()->balance(), CAudioAdaptor::getInstance()->fader());

    if(isRCAActionSet(CRCAEnums::RCA_BALANCEFADER_UPDATED))
    {
        QString strBalanceFaderImageSource = "";
        int iBalance = CAudioAdaptor::getInstance()->balance();
        int iFader = CAudioAdaptor::getInstance()->fader();

        if (iBalance < 0 && iFader > 0)
        {
            strBalanceFaderImageSource = "qrc:/image/RCA/RCA_Ico_Balance_and_Fader_n/Sts_Ico_Balance_And_fader_2_n.png";
        }
        else if(iBalance > 0 && iFader > 0)
        {
            strBalanceFaderImageSource = "qrc:/image/RCA/RCA_Ico_Balance_and_Fader_n/Sts_Ico_Balance_And_fader_3_n.png";
        }
        else if(iBalance < 0 && iFader < 0)
        {
            strBalanceFaderImageSource = "qrc:/image/RCA/RCA_Ico_Balance_and_Fader_n/Sts_Ico_Balance_And_fader_4_n.png";
        }
        else if(iBalance > 0 && iFader < 0)
        {
            strBalanceFaderImageSource = "qrc:/image/RCA/RCA_Ico_Balance_and_Fader_n/Sts_Ico_Balance_And_fader_5_n.png";
        }
        else
        {
            strBalanceFaderImageSource = "qrc:/image/RCA/RCA_Ico_Balance_and_Fader_n/Sts_Ico_Balance_And_fader_1_n.png";
        }

        setBalanceFaderImageSource(strBalanceFaderImageSource);

//        // Blocking BalanceFader update notification when BalanceFader screen is displaying.
        if(isAudioSetupStateActive() && (CSetupEnums::AUDIOSETUP_BALANCE_FADER_SCREEN == CSetupAdaptor::getInstance()->eCurrentAudioSettingsScreen()))
        {
            // Will close already displayed BalanceFader update notification if user tries to update again and screen is displaying.
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_RCA_BALANCE_FADER);
        }
        else
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_RCA_BALANCE_FADER);
        }
    }
    else
    {
        // do nothing
    }
}

void CRCAAdaptor::sltAuxGainValueChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s: AuxGain: %d", __FUNCTION__, CAudioAdaptor::getInstance()->auxGainValue());
    if(isRCAActionSet(CRCAEnums::RCA_AUX_GAIN_UPDATED))
    {
        switch(CAudioAdaptor::getInstance()->auxGainValue())
        {
        case CAudioEnums::AUXINGAIN_HIGH:
            setAuxGainText(tr("TEXT_AUDIO_SOURCE_AUX_HIGH_GAIN"));
            break;
        case CAudioEnums::AUXINGAIN_MID:
            setAuxGainText(tr("TEXT_AUDIO_SOURCE_AUX_MID_GAIN"));
            break;
        case CAudioEnums::AUXINGAIN_LOW:
            setAuxGainText(tr("TEXT_AUDIO_SOURCE_AUX_LOW_GAIN"));
            break;
        default:
            setAuxGainText(tr("TEXT_TITLE_ERROR"));
            break;
        }

        // Blocking AuxInGain update notification when AuxInGain screen is displaying.
        if(!CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_AUXInGain))
        {
            CPopupManager::getInstance()->showPopup(CPopupEnum::EN_POPUPID_RCA_AUX_GAIN);
        }
        else
        {
            // Will close already displayed AuxInGain update notification if user tries to update again and screen is displaying.
            CPopupManager::getInstance()->forceClosePopup(CPopupEnum::EN_POPUPID_RCA_AUX_GAIN);
        }

        /* Clear RCA_BALANCEFADER_UPDATED RCA Action after processing it */
        clearRCAAction(CRCAEnums::RCA_AUX_GAIN_UPDATED);
    }
    else
    {
        // do nothing
    }
}

void CRCAAdaptor::sltNowPlayingChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s", __FUNCTION__);
    if(isRCAActionSet(CRCAEnums::RCA_VIDEO_PLAYED))
    {
        if(CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaMain)
                || CHMIMain::getSM()->isStateActive(TML_HMI_SM::startup_region_Ui_home_Main_main_ActiveAudio_activeaudio_Media_media_region_MediaVideo))
        {
            // do nothing... screen switch is already handled in CMediaAdaptor::setNowPlayingData()
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s, Transit to Video Player screen on RCA_VIDEO_PLAYED", __FUNCTION__);
            /* On RCA_VIDEO_PLAYED action in RCA, transit to Media screen */
            CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_MAIN);
            CHMIMain::getSM()->raise_evMediaActivated();
        }

        /* Clear RCA_VIDEO_PLAYED RCA Action after processing it */
        clearRCAAction(CRCAEnums::RCA_VIDEO_PLAYED);
    }
    else
    {
        // do nothing
    }
}

void CRCAAdaptor::sltPopupResult(CPopupEnum::EPopupID ePopupId, CPopupEnum::EPopupResult ePopupResult, QString strAdditionalInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_RCA, "%s: ePopupId: %d, ePopupResult: %d, strAdditionalInfo: %s", __FUNCTION__, static_cast<int>(ePopupId), static_cast<int>(ePopupResult), strAdditionalInfo.toStdString().c_str());

    switch(ePopupId)
    {
    case CPopupEnum::EPopupID::EN_POPUPID_RCA_BALANCE_FADER:
    {
        if (CPopupEnum::EN_POPUP_RESULT_DISPLAYED != ePopupResult)
        {
            /* Clear RCA_BALANCEFADER_UPDATED RCA Action after processing it */
            clearRCAAction(CRCAEnums::RCA_BALANCEFADER_UPDATED);
        }
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_RCA, "%s: In Default case.", __FUNCTION__);
    }
        break;
    }
}

/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CAudioAdaptor.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * This class is to handle Audio settings and Audio Controls functionality.
 */
#include "CAudioAdaptor.h"
#include "ResourceFactory.hpp"
#include "Setup/SetupDef.h"
#include "CHMIMain.h"
#include "CPersistencyAdaptor.h"
#include "CParkAssistAdaptor.h"
#include "CMediaAdaptor.h"
#include "implementations/CAudioResourceImpl.h"

CAudioAdaptor* CAudioAdaptor::m_pAudioAdaptor = nullptr;

CAudioAdaptor::CAudioAdaptor(QObject *parent):
    QObject(parent),
    m_pAudioResource(ResourceFactory::getAudioResource()),
    m_pAudioResourceImpl(dynamic_cast<CAudioResourceImpl*>(ResourceFactory::getAudioResource())),
    m_pMediaResource(ResourceFactory::getMediaResource()),
    m_iBalancePos(0),
    m_iFaderPos(0),
    m_iPhoneCallVolume(0),
    m_iVoiceAlertVolume(0),
    m_eConfiguredAudioPreset(static_cast<CAudioEnums::EAudioPresets>(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_SETUP_AUDIO_PRESET))),
    m_bIsSourceChangeRequestedByUser(false)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s: ", __FUNCTION__);

    if(m_pAudioResourceImpl)
    {
        m_iBass                  = m_pAudioResourceImpl->getBassValue();
        m_iMid                   = m_pAudioResourceImpl->getMidValue();
        m_iTreble                = m_pAudioResourceImpl->getTrebleValue();
        m_iBalance               = m_pAudioResourceImpl->getBalanceValue();
        m_iFade                  = m_pAudioResourceImpl->getFadeValue();
        m_bFMSrcStatus           = m_pAudioResourceImpl->getFMSrcStatus();
        m_bAMSrcStatus           = m_pAudioResourceImpl->getAMSrcStatus();
        m_bUSBSrcStatus          = m_pAudioResourceImpl->getUSBSrcStatus();
        m_bIPODSrcStatus         = m_pAudioResourceImpl->getIPODSrcStatus();
        m_bAUXSrcStatus          = m_pAudioResourceImpl->getAUXSrcStatus();
        m_bBTSrcStatus           = m_pAudioResourceImpl->getBTSrcStatus();
        m_iActEntSourceVolume    = m_pAudioResourceImpl->getActiveEntSrcVolume();
        m_bMuteActive            = m_pAudioResourceImpl->getMuteStatus();
        m_bIsVolumeUpdatedByUser = m_pAudioResourceImpl->getVolumeUpdatedByUserStatus();
        m_bSpeedDependantVolume  = m_pAudioResourceImpl->getSpeedDependantVolumeStatus();
        m_iStartUpVolume         = m_pAudioResourceImpl->getStartupVolume();
        m_eActiveAudioPreset     = m_mapAudioPreset.key(m_pAudioResourceImpl->getActiveAudioPreset().c_str(), CAudioEnums::AUDIO_PRESET_DEFAULT);
        m_bMicMuteStatus         = m_pAudioResourceImpl->getMicMuteStatus();
        m_bPdcMixModeStatus      = m_pAudioResourceImpl->getPdcMixModeStatus();
        m_ePrevActiveEntSrc     = CAudioEnums::EAudioEntertainmentSrcs::SRC_ENT_UNKNOWN;
        m_eActiveEntSrc          = m_pAudioResourceImpl->getActiveEntSrc();
        m_iAuxGainValue          = m_pAudioResourceImpl->getAuxGainValue();
        m_eAuxConnectionStatus   = (getAuxConnectionInEnums(m_pAudioResourceImpl->getAuxConnectionStatus().c_str()));
        m_eIpodConnectionStatus  = (getIpodConnectionInEnums(m_pAudioResourceImpl->getIpodConnectionStatus().c_str()));
        m_eUsbConnectionStatus   = (getUsbConnectionInEnums(m_pAudioResourceImpl->getUsbConnectionStatus().c_str()));
        updateVolume(m_pAudioResourceImpl->getActiveEntSrcVolume()
                     , m_pAudioResourceImpl->getVolumeUpdatedByUserStatus()
                     , static_cast<CAudioEnums::EVolumeUpdateGroup>(m_pAudioResourceImpl->getVolumeGroup())
                     , m_pAudioResourceImpl->getSourceId());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO,"AudioResourceImpl is null");
    }

    CFramework::getFramework().setContextProperty("cppAudioAdaptor", this);
    CAudioEnums::registerAudioEnumsToQML();
    m_mapAudioSourceInfo.clear();

    /*Inserting Audio preset index and preset values */
    m_mapAudioPreset.clear();
    m_mapAudioPreset.insert(CAudioEnums::AUDIO_PRESET_FLAT, "NORMAL");
    m_mapAudioPreset.insert(CAudioEnums::AUDIO_PRESET_ROCK, "ROCK");
    m_mapAudioPreset.insert(CAudioEnums::AUDIO_PRESET_POP, "POP");
    m_mapAudioPreset.insert(CAudioEnums::AUDIO_PRESET_JAZZ, "JAZZ");
    m_mapAudioPreset.insert(CAudioEnums::AUDIO_PRESET_CLASSIC, "CLASSIC");
    m_mapAudioPreset.insert(CAudioEnums::AUDIO_PRESET_HIPHOP, "VOCAL");
    m_mapAudioPreset.insert(CAudioEnums::AUDIO_PRESET_CUSTOM, "CUSTOM");
    m_vecAudioPresetName = {tr("TEXT_AUDIO_PRESET_FLAT"), tr("TEXT_AUDIO_PRESET_ROCK"),
                            tr("TEXT_AUDIO_PRESET_POP"), tr("TEXT_AUDIO_PRESET_JAZZ"), tr("TEXT_AUDIO_PRESET_CLASSIC"), tr("TEXT_AUDIO_PRESET_SPEECH"),
                            tr("TEXT_AUDIO_PRESET_USER")};
}

CAudioAdaptor::~CAudioAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(m_pAudioAdaptor)
    {
        delete m_pAudioAdaptor;
        m_pAudioAdaptor = nullptr;
    }
    m_mapAudioPreset.clear();
}

void CAudioAdaptor::sourceStateInfoUpdated(int iSourceId, int iSourceState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s: source id is: %d, source state is: %d ", __FUNCTION__, iSourceId, iSourceState);
    CAudioEnums::ESourceId eSourceId       = static_cast<CAudioEnums::ESourceId>(iSourceId);
    CAudioEnums::ESourceState eSourceState = static_cast<CAudioEnums::ESourceState>(iSourceState);
    m_mapAudioSourceInfo.insert(eSourceId, eSourceState);
    emit sigSourceStateInfoUpdated(iSourceId, iSourceState);
}

void CAudioAdaptor::playFromSourceGroup(CAudioEnums::EAudioSourceCategory eSourceCategory, bool bScreenSwitchReq)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s: requested eSourceCategory is: %d,  bScreenSwitchReq is: %d", __FUNCTION__, eSourceCategory, bScreenSwitchReq);
    if(CAudioAdaptor::getInstance()->getSourceCategory(CAudioAdaptor::getInstance()->activeEntSrc()) == eSourceCategory)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: active source is from the requested group", __FUNCTION__);
        if(bScreenSwitchReq)
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: bScreenSwitchReq is true, switch the screen", __FUNCTION__);
            switchToActiveEntertainmentSourceScreen();
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_VR, "%s: source category is not media", __FUNCTION__);
        //switch the source to media group
        CAudioAdaptor::getInstance()->setIsSourceChangeRequestedByUser(bScreenSwitchReq);
        ResourceFactory::getAudioResource()->playFromSourceGroup(eSourceCategory);
    }
}

CAudioEnums::ESourceState CAudioAdaptor::getSourceState(CAudioEnums::ESourceId eSourceId)
{
    CAudioEnums::ESourceState eSourceState = CAudioEnums::EN_SOURCE_STATE_UNKNOWN;
    if(m_mapAudioSourceInfo.contains(eSourceId))
    {
        eSourceState = m_mapAudioSourceInfo.value(eSourceId);
    }
    return eSourceState;
}

CAudioEnums::EAudioSourceCategory CAudioAdaptor::getSourceCategory(int iSourceId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: source id is: %d", __FUNCTION__, iSourceId);
    CAudioEnums::EAudioSourceCategory eSourceCategory = CAudioEnums::SOURCE_CATEGORY_UNKNOWN;
    switch(iSourceId)
    {
    case CAudioEnums::SRC_TUNER_AM:
    case CAudioEnums::SRC_TUNER_FM:
    case CAudioEnums::SRC_TUNER_DRM:
    {
        eSourceCategory = CAudioEnums::SOURCE_CATEGORY_TUNER;
    }
        break;
    case CAudioEnums::SRC_AUDIO_AUX:
    case CAudioEnums::SRC_BT_A2DP1:
    case CAudioEnums::SRC_BT_A2DP2:
    case CAudioEnums::SRC_USB1:
    case CAudioEnums::SRC_USB2:
    case CAudioEnums::SRC_IPOD:
    {
        eSourceCategory = CAudioEnums::SOURCE_CATEGORY_MEDIA;
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: source id not handled", __FUNCTION__);
    }
        break;
    }

    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: source category is: %d", __FUNCTION__, eSourceCategory);
    return eSourceCategory;
}

CAudioAdaptor* CAudioAdaptor::getInstance()
{
    if(nullptr == m_pAudioAdaptor)
    {
        m_pAudioAdaptor = new CAudioAdaptor();
    }
    return m_pAudioAdaptor;
}

bool CAudioAdaptor::isAudioResourceNull()
{
    bool val = false;
    if (NULL == m_pAudioResource)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :AudioResource is NULL", __FUNCTION__);
        val =true;
    }
    return val;
}

void CAudioAdaptor::setIsVolumeUpdatedByUser(bool bIsVolumeUpdatedByUser)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s m_bIsVolumeUpdatedByUser - %d", __FUNCTION__, bIsVolumeUpdatedByUser);
    if(m_bIsVolumeUpdatedByUser != bIsVolumeUpdatedByUser)
    {
        m_bIsVolumeUpdatedByUser = bIsVolumeUpdatedByUser;
        emit sigVolumeUpdatedByUserChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s m_bIsVolumeUpdatedByUser - Values are same", __FUNCTION__);
    }
}

/* get, set methods - start */

void CAudioAdaptor::updateAudioPluginProxyAvailability(bool bAvailability)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s availability: %d", __FUNCTION__, bAvailability);
    emit sigUpdateAudioPluginProxyAvailability(bAvailability);
}

int CAudioAdaptor::bass()
{
    return m_iBass;
}

void CAudioAdaptor::setBass(int iBass)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set - Bass :%d", __FUNCTION__, iBass);
    if(iBass != m_iBass)
    {
        m_iBass = iBass;
        emit sigBassChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

int CAudioAdaptor::mid()
{
    return m_iMid;
}

void CAudioAdaptor::setMid(int iMid)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set - Mid :%d", __FUNCTION__, iMid);
    if(iMid != m_iMid)
    {
        m_iMid = iMid;
        emit sigMidChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

int CAudioAdaptor::treble()
{
    return m_iTreble;
}

void CAudioAdaptor::setTreble(int iTreble)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set - Treble :%d", __FUNCTION__, iTreble);
    if(iTreble != m_iTreble)
    {
        m_iTreble = iTreble;
        emit sigTrebleChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

int CAudioAdaptor::balance()
{
    return m_iBalance;
}

void CAudioAdaptor::setBalance(int iBalance)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set - Balance :%d", __FUNCTION__, iBalance);
    if(iBalance != m_iBalance)
    {
        m_iBalance = iBalance;
        emit sigBalanceChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

int CAudioAdaptor::fader()
{
    return m_iFade;
}

void CAudioAdaptor::setFader(int iFade)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set - Fade :%d", __FUNCTION__, iFade);
    if(iFade != m_iFade)
    {
        m_iFade = iFade;
        emit sigFadeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

int CAudioAdaptor::faderPos()
{
    return m_iFaderPos;
}

void CAudioAdaptor::setFaderPos(float fFaderPos)
{
    m_iFaderPos = qRound(((-fFaderPos + BALANCE_FADER_SCALE_SHIFT) * BAL_FAD_MAT_HEIGHT) / BALANCE_FADER_RANGE);
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Fader position :%d",__FUNCTION__,  m_iFaderPos);
    emit sigFaderPosChanged();
}

int CAudioAdaptor::balancePos()
{
    return m_iBalancePos;
}

void CAudioAdaptor::setBalancePos(float fBalancePos)
{
    m_iBalancePos = qRound(((fBalancePos + BALANCE_FADER_SCALE_SHIFT) * BAL_FAD_MAT_WIDTH) / BALANCE_FADER_RANGE);
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Balance position :%d", __FUNCTION__,  m_iBalancePos);
    emit sigBalancePosChanged();
}

bool CAudioAdaptor::fmSrcStatus()
{
    return m_bFMSrcStatus;
}

void CAudioAdaptor::updateFMSrcStatus(bool bFMSrcStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s FMSrcStatus : %d",__FUNCTION__, m_bFMSrcStatus);
    if(bFMSrcStatus != m_bFMSrcStatus)
    {
        m_bFMSrcStatus = bFMSrcStatus;
        emit sigFMSrcStatuschanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

bool CAudioAdaptor::amSrcStatus()
{
    return m_bAMSrcStatus;
}

void CAudioAdaptor::updateAMSrcStatus(bool bAMSrcStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s AMSrcStatus : %d",__FUNCTION__,  m_bAMSrcStatus);
    if(bAMSrcStatus != m_bAMSrcStatus)
    {
        m_bAMSrcStatus = bAMSrcStatus;
        emit sigAMSrcStatuschanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

bool CAudioAdaptor::usbSrcStatus()
{
    return m_bUSBSrcStatus;
}

void CAudioAdaptor::updateUSBSrcStatus(bool bUSBSrcStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s USBSrcStatus : %d",__FUNCTION__,  bUSBSrcStatus);
    if(bUSBSrcStatus != m_bUSBSrcStatus)
    {
        m_bUSBSrcStatus = bUSBSrcStatus;
        emit sigUSBSrcStatuschanged();

        if(true == m_bUSBSrcStatus)
        {
            //Do nothing
        }
        else
        {
            //FixME: Raise an event to SCT same as X0
            /* To switch to Software Update screen from ISO List screen on USB Removal */
        }
    }
}

bool CAudioAdaptor::ipodSrcStatus()
{
    return m_bIPODSrcStatus;
}

void CAudioAdaptor::updateIPODSrcStatus(bool bIPODSrcStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s IPOD status : %d", __FUNCTION__, bIPODSrcStatus);
    if(bIPODSrcStatus != m_bIPODSrcStatus)
    {
        m_bIPODSrcStatus = bIPODSrcStatus;
        emit sigIPODSrcStatuschanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}
bool CAudioAdaptor::auxSrcStatus()
{
    return m_bAUXSrcStatus;
}

void CAudioAdaptor::updateAUXSrcStatus(bool bAUXSrcStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Aux status : %d", __FUNCTION__, bAUXSrcStatus);
    if(bAUXSrcStatus != m_bAUXSrcStatus)
    {
        m_bAUXSrcStatus = bAUXSrcStatus;
        emit sigAUXSrcStatuschanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

bool CAudioAdaptor::btSrcStatus()
{
    return m_bBTSrcStatus;
}

void CAudioAdaptor::updateBTSrcStatus(bool bBTSrcStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s BT status : %d", __FUNCTION__, bBTSrcStatus);
    if(bBTSrcStatus != m_bBTSrcStatus)
    {
        m_bBTSrcStatus = bBTSrcStatus;
        emit sigBTSrcStatuschanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

QString CAudioAdaptor::activeAudioPresetName()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO," %s m_eActiveAudioPreset is: %d",__FUNCTION__, m_eActiveAudioPreset);
    QString strActivePresetName = "";
    if((m_eActiveAudioPreset >= 0) && (m_eActiveAudioPreset < m_vecAudioPresetName.size()))
    {
        strActivePresetName =  m_vecAudioPresetName.at(m_eActiveAudioPreset);
    }
    else
    {
        //do nothing
    }
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO," %s activeAudioPresetName: %s",__FUNCTION__, strActivePresetName.toStdString().c_str());
    return strActivePresetName;
}

CAudioEnums::EAudioPresets CAudioAdaptor::activeAudioPreset()
{
    return m_eActiveAudioPreset;
}

void CAudioAdaptor::updateAudioPreset(const QString &strPresetName)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO," %s Audio preset : %s",__FUNCTION__, strPresetName.toStdString().c_str());

    CAudioEnums::EAudioPresets eActiveAudioPreset = m_mapAudioPreset.key(strPresetName, CAudioEnums::AUDIO_PRESET_DEFAULT);

    if((eActiveAudioPreset != CAudioEnums::AUDIO_PRESET_DEFAULT) && (m_eActiveAudioPreset != eActiveAudioPreset))
    {
        m_eActiveAudioPreset = eActiveAudioPreset;
        emit sigActiveAudioPresetChanged();
        emit sigActiveAudioPresetNameChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

CAudioEnums::EAuxConnectionStatus CAudioAdaptor::getAuxConnectionInEnums(const QString &strAuxConnectionState)
{
    CAudioEnums::EAuxConnectionStatus eReturnVal;

    if("AUX_STATE_UNKNOWN" == strAuxConnectionState)
    {
        eReturnVal = CAudioEnums::AUX_STATE_UNKNOWN;
    }
    else if("AUX_CONNECTED" == strAuxConnectionState)
    {
        eReturnVal = CAudioEnums::AUX_CONNECTED;
    }
    else if("AUX_ALREADY_CONNECTED" == strAuxConnectionState)
    {
        eReturnVal = CAudioEnums::AUX_ALREADY_CONNECTED;
    }
    else if("AUX_REMOVED" == strAuxConnectionState)
    {
        eReturnVal = CAudioEnums::AUX_DISCONNECTED;
    }
    else
    {
        eReturnVal = CAudioEnums::AUX_STATE_DEFAULT;
    }

    return eReturnVal;
}

void CAudioAdaptor::updateAUXConnectionState(const QString &strAUXConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s AUX Connection status : %s", __FUNCTION__, strAUXConnectionState.toStdString().c_str());

    CAudioEnums::EAuxConnectionStatus eAuxConnectionStatus = getAuxConnectionInEnums(strAUXConnectionState);

    if(eAuxConnectionStatus != m_eAuxConnectionStatus)
    {
        m_eAuxConnectionStatus = eAuxConnectionStatus;
        emit sigAUXConnectionStatuschanged();
    }
    else
    {
        // Do nothing.
    }
}

CAudioEnums::EUsbConnectionStatus CAudioAdaptor::getUsbConnectionInEnums(const QString &strUsbConnectionState)
{
    CAudioEnums::EUsbConnectionStatus eReturnVal;
    if("USB_STATE_UNKNOWN" == strUsbConnectionState)
    {
        eReturnVal = CAudioEnums::USB_STATE_UNKNOWN;
    }
    else if("USB_CONNECTED" == strUsbConnectionState)
    {
        eReturnVal = CAudioEnums::USB_CONNECTED;
    }
    else if("USB_ALREADY_CONNECTED" == strUsbConnectionState)
    {
        eReturnVal = CAudioEnums::USB_ALREADY_CONNECTED;
    }
    else if("USB_DISCONNECTED" == strUsbConnectionState)
    {
        eReturnVal = CAudioEnums::USB_DISCONNECTED;
    }
    else
    {
        eReturnVal = CAudioEnums::USB_STATE_DEFAULT;
    }

    return eReturnVal;
}

void CAudioAdaptor::updateUSBConnectionState(const QString &strUSBConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s USB Connection status : %s", __FUNCTION__, strUSBConnectionState.toStdString().c_str());

    CAudioEnums::EUsbConnectionStatus eUSBConnectionStatus = getUsbConnectionInEnums(strUSBConnectionState);

    if(eUSBConnectionStatus != m_eUsbConnectionStatus)
    {
        m_eUsbConnectionStatus = eUSBConnectionStatus;
        emit sigUSBConnectionStatuschanged();
    }
    else
    {
        // Do nothing.
    }
}

CAudioEnums::EIpodConnectionStatus CAudioAdaptor::getIpodConnectionInEnums(const QString &strIpodConnectionState)
{
    CAudioEnums::EIpodConnectionStatus eReturnVal;

    if("IPOD_STATE_UNKNOWN" == strIpodConnectionState)
    {
        eReturnVal = CAudioEnums::IPOD_STATE_UNKNOWN;
    }
    else if("IPOD_CONNECTED" == strIpodConnectionState)
    {
        eReturnVal = CAudioEnums::IPOD_CONNECTED;
    }
    else if("IPOD_ALREADY_CONNECTED" == strIpodConnectionState)
    {
        eReturnVal = CAudioEnums::IPOD_ALREADY_CONNECTED;
    }
    else if("IPOD_DISCONNECTED" == strIpodConnectionState)
    {
        eReturnVal = CAudioEnums::IPOD_DISCONNECTED;
    }
    else
    {
        eReturnVal = CAudioEnums::IPOD_STATE_DEFAULT;
    }

    return eReturnVal;
}

void CAudioAdaptor::updateIPODConnectionState(const QString &strIPODConnectionState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s IPOD Connection status : %s", __FUNCTION__, strIPODConnectionState.toStdString().c_str());

    CAudioEnums::EIpodConnectionStatus eIPODConnectionStatus = getIpodConnectionInEnums(strIPODConnectionState);

    if(eIPODConnectionStatus != m_eIpodConnectionStatus)
    {
        m_eIpodConnectionStatus = eIPODConnectionStatus;
        emit sigIPODConnectionStatuschanged();
    }
    else
    {
        // Do nothing.
    }

}

int CAudioAdaptor::actEntSourceVolume()
{
    return m_iActEntSourceVolume;
}

void CAudioAdaptor::setActiveEntSrcVolume(int iActiveEntSrcVol)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, " %s Active EntSource Volume: %d",
             __FUNCTION__, iActiveEntSrcVol);
    if (m_iActEntSourceVolume != iActiveEntSrcVol)
    {
        m_iActEntSourceVolume = iActiveEntSrcVol;
        emit sigActEntSourceVolumeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, " %s Values are same.", __FUNCTION__);
    }
}

void CAudioAdaptor::setVolumeUpdateGroup(CAudioEnums::EVolumeUpdateGroup eVolumeUpdateGroup)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s eVolumeUpdateGroup : %d",
             __FUNCTION__, eVolumeUpdateGroup);

    if(m_eVolumeUpdateGroup != eVolumeUpdateGroup)
    {
        m_eVolumeUpdateGroup = eVolumeUpdateGroup;
        emit sigVolumeUpdateGroupChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

void CAudioAdaptor::setActiveSourceVolume(ushort usActiveSourceVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s usActiveSourceVolume : %u",
             __FUNCTION__, usActiveSourceVolume);

    if(m_usActiveSourceVolume != usActiveSourceVolume)
    {
        m_usActiveSourceVolume = usActiveSourceVolume;
        emit sigActiveSourceVolumeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

void CAudioAdaptor::updateVolume(ushort usActiveSourceVolume, bool bIsVolumeUpdatedByUser,
                                 CAudioEnums::EVolumeUpdateGroup eVolumeUpdateGroup, ushort usSourceId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s: usActiveSourceVolume: %d,"
                                       " bIsVolumeUpdatedByUser:"
                                       " %d, eVolumeUpdateGroup: %d,"
                                       "usSourceId: %d", __FUNCTION__,
             usActiveSourceVolume, bIsVolumeUpdatedByUser,
             eVolumeUpdateGroup, usSourceId);

    bool bIsActionTaken = false;

    setIsVolumeUpdatedByUser(bIsVolumeUpdatedByUser);

    switch(eVolumeUpdateGroup)
    {
    case CAudioEnums::EN_VOLUME_UPDATE_GROUP_ENT:
    {
        setActiveEntSrcVolume(usActiveSourceVolume);
        bIsActionTaken = true;
    }
        break;
    case CAudioEnums::EN_VOLUME_UPDATE_GROUP_PHONE:
    {
        setPhoneCallVolume(usActiveSourceVolume);
        bIsActionTaken = true;
    }
        break;
    case CAudioEnums::EN_VOLUME_UPDATE_GROUP_PROMPT:
    {
        bIsActionTaken = true;
        /*
         * As per AudioManager Team this source is for PDC/RVC Audio Source.
         */
        if (CAudioEnums::SRC_INDICATION == usSourceId)
        {
            CParkAssistAdaptor::getInstance()->setParkAssistVolume(usActiveSourceVolume);
            eVolumeUpdateGroup = CAudioEnums::EN_VOLUME_UPDATE_GROUP_PDC_RVC;
        }
        else
        {
            setVoiceAlertVolume(usActiveSourceVolume);
        }

        /*
         * ToDo: Need to handle Navigation
         */

        bIsActionTaken = true;
    }
        break;
    case CAudioEnums::EN_VOLUME_UPDATE_GROUP_VR:
    {
        /*
         * ToDo: Need to set VR Volume, Please uncommnet below code, when done.
         */
    }
        break;
    case CAudioEnums::EN_VOLUME_UPDATE_GROUP_TA:
    {
        /*
         * ToDo: Need to set Traffic Alert Volume.
         */
        bIsActionTaken = true;
    }
        break;
    case CAudioEnums::EN_VOLUME_UPDATE_GROUP_UNKNOWN:
    {
        // Do nothing.
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "%s: Source Group Unknown"
                                              " recieved.", __FUNCTION__);
    }
        break;
        //FixMe: Remove the below case after audio manager issue is fixed. Audio manager is sending
        //EN_VOLUME_UPDATE_GROUP_NOUPDATE for phone call volume & park assist volume on requesting to set from HMI.
    case CAudioEnums::EN_VOLUME_UPDATE_GROUP_NOUPDATE:
    {
        if(SRC_TEL_HANDSFREE == usSourceId)   /** Phone volume **/
        {
            setPhoneCallVolume(usActiveSourceVolume);
        }
        else if(SRC_INDICATION == usSourceId)   /** Park assist volume **/
        {
            CParkAssistAdaptor::getInstance()->setParkAssistVolume(usActiveSourceVolume);
        }
        else if(SRC_VR_SMS_READOUT == usSourceId || (SRC_VR == usSourceId)) /** Notification Volume **/
        {
            setVoiceAlertVolume(usActiveSourceVolume);
        }
        else if( (SRC_TUNER_FM == usSourceId) || (SRC_TUNER_AM == usSourceId) || (SRC_USB1 == usSourceId) || (SRC_AUDIO_AUX == usSourceId) ||
                 (SRC_BT_A2DP1 == usSourceId) || (SRC_IPOD == usSourceId) )
        {
            setActiveEntSrcVolume(usActiveSourceVolume);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "%s: EN_VOLUME_UPDATE_GROUP_NOUPDATE, usSourceId: %d", __FUNCTION__, usSourceId);
        }
    }
        break;
    default:
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "%s: In default case", __FUNCTION__);
    }
        break;
    }

    if ( bIsActionTaken )
    {
        setVolumeUpdateGroup(eVolumeUpdateGroup);
        setActiveSourceVolume(usActiveSourceVolume);

        if ( bIsVolumeUpdatedByUser )
        {
            CHMIMain::getSM()->getSCI_Audio()->raise_evActiveSrcVolumeChanged();
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "%s: Volume was not updated by user.", __FUNCTION__);
        }
    }
    else
    {
        if( ( activeEntSrc() == static_cast<CAudioEnums::EAudioEntertainmentSrcs>(usSourceId) ) ||
            ( isAudioInterruptSourceActive(static_cast<CAudioEnums::EAudioInterruptSources>(usSourceId)) ) )
        {
            /* To update the QAD volume +/- buttons disabled state properly for current source */
            setActiveSourceVolume(usActiveSourceVolume);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "%s: No Action Taken for Volume update.", __FUNCTION__);
        }
    }
}

bool CAudioAdaptor::muteActive()
{
    return m_bMuteActive;
}

void CAudioAdaptor::updateMuteState(bool bMuteActive)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s Mute Active : %d", __FUNCTION__, bMuteActive);
    if(bMuteActive != m_bMuteActive)
    {
        if (bMuteActive)
            setIsVolumeUpdatedByUser(false);
        m_bMuteActive = bMuteActive;
        emit sigMuteStateChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

CAudioEnums::EAudioEntertainmentSrcs CAudioAdaptor::activeEntSrc()
{
    return m_eActiveEntSrc;
}

CAudioEnums::EAudioEntertainmentSrcs CAudioAdaptor::prevActiveEntSrc()
{
    return m_ePrevActiveEntSrc;
}


void CAudioAdaptor::updateActiveEntSrc(CAudioEnums::EAudioEntertainmentSrcs eActiveEntSrc)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s ActiveEntSrc : %d", __FUNCTION__, eActiveEntSrc);
    if(eActiveEntSrc != m_eActiveEntSrc)
    {
        m_ePrevActiveEntSrc = m_eActiveEntSrc;
        m_eActiveEntSrc = eActiveEntSrc;
        emit sigActiveEntSrcChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}
/* get, set methods - end */

/* Audio resource implementor methods - start */

void CAudioAdaptor::setBassAttribute(int iBassval)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s :", __FUNCTION__);
    if(!isAudioResourceNull())
        m_pAudioResource->setBass(iBassval);
}

void CAudioAdaptor::setMidAttribute(int iMidval)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(!isAudioResourceNull())
        m_pAudioResource->setMid(iMidval);
}

void CAudioAdaptor::setTrebleAttribute(int iTrebleval)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(!isAudioResourceNull())
        m_pAudioResource->setTreble(iTrebleval);
}

void CAudioAdaptor::setFaderBalance(int iFader, int iBalance)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(!isAudioResourceNull())
        m_pAudioResource->setFaderBalance(iFader, iBalance);
}

void CAudioAdaptor::setSpeedDependantVolumeAttribute(bool bSpeedDependantVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, SpeedDependantVolume : %d", __FUNCTION__, bSpeedDependantVolume);
    if(!isAudioResourceNull())
    {
        m_pAudioResource->setSDVCState(bSpeedDependantVolume);
    }
}

void CAudioAdaptor::setPhoneCallVolumeAttribute(int iPhoneCallVol)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO," %s, PhoneCallVolume : %d",__FUNCTION__, iPhoneCallVol);
    if(!isAudioResourceNull())
    {
        m_pAudioResource->setPhoneSourceVolume(iPhoneCallVol);
    }
}

void CAudioAdaptor::setStartUpVolumeAttribute(int iStartUpVol)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO," %s, start up volume : %d", __FUNCTION__, iStartUpVol);
    if(!isAudioResourceNull())
    {
        m_pAudioResource->setStartUpVolume(iStartUpVol);
    }
}

void CAudioAdaptor::setVoiceAlertVolumeAttribute(int iVoiceAlertVol)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Voice alert volume : %d",__FUNCTION__, iVoiceAlertVol);
    if(!isAudioResourceNull())
    {
        m_pAudioResource->setVoiceAlertVolume(iVoiceAlertVol);
    }
}

void CAudioAdaptor::setNotificationVolumeAttribute(int iNotificationVol)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Notification volume : %d",__FUNCTION__, iNotificationVol);
    if(!isAudioResourceNull())
    {
        m_pAudioResource->setNotificationVolume(iNotificationVol);
    }
}

void CAudioAdaptor::setAuxInGainAttribute(int iAuxInGain)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Aux In Gain : %d",__FUNCTION__, iAuxInGain);
    if(!isAudioResourceNull())
    {
        m_pAudioResource->setAuxInGain(static_cast<CAudioEnums::EAuxInGain>(iAuxInGain));
    }

}

void CAudioAdaptor::switchToPreviousEntSource()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s",__FUNCTION__);

    if(!isAudioResourceNull())
    {
        m_pAudioResource->switchToPreviousEntSource();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "%s, Audio resource object not created", __FUNCTION__);
    }
}

void CAudioAdaptor::setPdcMixModeStateAttribute(bool bPdcMixModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, Pdc Mix Mode state : %d",__FUNCTION__, bPdcMixModeStatus);
    if(!isAudioResourceNull())
    {
        m_pAudioResource->setPdcMixModeState(bPdcMixModeStatus);
    }
}

void CAudioAdaptor::toggleEntSrc(CAudioEnums::EToggleDirection eToggleDirection)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s eToggleDirection: %d", __FUNCTION__, eToggleDirection);
    if(!isAudioResourceNull())
    {
        setIsSourceChangeRequestedByUser(true);
        m_pAudioResource->toggleSource(eToggleDirection);
    }
}

void CAudioAdaptor::toggleMicMute()
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(m_pAudioResource)
    {
        m_pAudioResource->toggleMicMute();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "Audio resource object not created");
    }
}

void CAudioAdaptor::playBeep(CAudioEnums::EBeepType eBeepType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    if(m_pAudioResource)
    {
        m_pAudioResource->playBeep(eBeepType);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "Audio resource object not created");
    }
}

bool CAudioAdaptor::speedDependantVolume()
{
    return m_bSpeedDependantVolume;
}

void CAudioAdaptor::setSpeedDependantVolume(bool bSpeedDependantVol)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, " %s, speed volume : %d ", __FUNCTION__, bSpeedDependantVol);
    if( bSpeedDependantVol != m_bSpeedDependantVolume)
    {
        m_bSpeedDependantVolume = bSpeedDependantVol;
        emit sigSpeedDependantVolumeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

int CAudioAdaptor::phoneCallVolume()
{
    return m_iPhoneCallVolume;
}

void CAudioAdaptor::setPhoneCallVolume(int iPhoneCallVol)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s, Phone call volume : %d ", __FUNCTION__, iPhoneCallVol);
    if( iPhoneCallVol != m_iPhoneCallVolume)
    {
        m_iPhoneCallVolume = iPhoneCallVol;
        emit sigPhoneCallVolumeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

int CAudioAdaptor::startUpVolume()
{
    return m_iStartUpVolume;
}

void CAudioAdaptor::setStartUpVolume(int iStartUpVol)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s, start up volume : %d ", __FUNCTION__, iStartUpVol);
    if( iStartUpVol != m_iStartUpVolume)
    {
        m_iStartUpVolume = iStartUpVol;
        emit sigStartUpVolumeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

int CAudioAdaptor::voiceAlertVolume()
{
    return m_iVoiceAlertVolume;
}

void CAudioAdaptor::setVoiceAlertVolume(int iVoiceAlertVol)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s, Voice Alert volume : %d ", __FUNCTION__, iVoiceAlertVol);
    if( iVoiceAlertVol != m_iVoiceAlertVolume)
    {
        m_iVoiceAlertVolume = iVoiceAlertVol;
        emit sigVoiceAlertVolumeChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

void CAudioAdaptor::micMuteStatusUpdated(bool bMicMuteStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s, mic mute status : %d ", __FUNCTION__, bMicMuteStatus);
    if( m_bMicMuteStatus != bMicMuteStatus)
    {
        m_bMicMuteStatus = bMicMuteStatus;
        emit sigMicMuteStatusUpdated();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "mic mute status value unchanged");
    }
}

void CAudioAdaptor::setAuxGainValue(int iAuxGainValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s, aux gain value: %d ", __FUNCTION__, iAuxGainValue);
    if( iAuxGainValue != m_iAuxGainValue)
    {
        m_iAuxGainValue = iAuxGainValue;
        emit sigAuxGainValueChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Values are same", __FUNCTION__);
    }
}

void CAudioAdaptor::setPdcMixModeStatus(bool bPdcMixModeStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s, pdc mix mode status : %d ", __FUNCTION__, bPdcMixModeStatus);

    /*Note : Here similar value check has been removed as there was issue on updating the data of model
             Issue fixed against Elvis ticket : 2610570
             Here temporarily removed the condition.
             Need to find out the proper root cause of the issue.*/
    m_bPdcMixModeStatus = bPdcMixModeStatus;
    emit sigPdcMixModeStatusChanged();
}

void CAudioAdaptor::setAudioOff(bool bAudioState)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s audio state: %d",__FUNCTION__, bAudioState);
    if(!isAudioResourceNull())
    {
        m_pAudioResource->setAudioOff(bAudioState);
    }
}

void CAudioAdaptor::invParkAssistVolume(int iParkAssistVolume)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s: park assist volume: %d", __FUNCTION__, iParkAssistVolume);

    if(!isAudioResourceNull())
    {
        m_pAudioResource->setParkAssistVolume(iParkAssistVolume);
    }
}

/* Audio resource implementor methods - end */

/* Methods invoked from qml - start */
void CAudioAdaptor::setBMTValues(int iValue, int iIndex)
{
    switch (iIndex)
    {
    case CSetupEnums::BMT_BASS:
        setBassAttribute(iValue);
        break;
    case CSetupEnums::BMT_MIDDLE:
        setMidAttribute(iValue);
        break;
    case CSetupEnums::BMT_TREBLE:
        setTrebleAttribute(iValue);
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, default case :%d", __FUNCTION__ , iIndex);
        break;
    }
}


void CAudioAdaptor::setVolumeSettingsValues(int iValue, int iIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Value : %d, Index : %d", __FUNCTION__ ,iValue, iIndex);
    switch (iIndex)
    {
    case CSetupEnums::VOLUME_PHONE_CALL:
        setPhoneCallVolumeAttribute(iValue);
        break;
    case CSetupEnums::VOLUME_START_UP:
        setStartUpVolumeAttribute(iValue);
        break;
    case CSetupEnums::VOLUME_VOICE_ALERTS:
        setVoiceAlertVolumeAttribute(iValue);
        break;
    default:
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s, default case :%d", __FUNCTION__ , iIndex);
        break;
    }
}

void CAudioAdaptor::calculateBalanceFader(float fFaderPos, float fBalancePos)
{
    //Calculating fader value from position
    int fader = -(qRound(((fFaderPos * BALANCE_FADER_RANGE) / BAL_FAD_MAT_HEIGHT) - BALANCE_FADER_SCALE_SHIFT));
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s: Fader position from qml: %f ,Fader value calculated: %d", __FUNCTION__,fFaderPos,fader);

    //Calculating balance value from position
    int balance = qRound(((fBalancePos * BALANCE_FADER_RANGE) / BAL_FAD_MAT_WIDTH) - BALANCE_FADER_SCALE_SHIFT);
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s: Balance position from qml: %f ,Balance value calculated: %d", __FUNCTION__,fBalancePos,balance);

    setFaderBalance(fader,balance);   //API Call
}

void CAudioAdaptor::setActiveEntSrc(CAudioEnums::EAudioEntertainmentSrcs eEntertainmentSrc)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set - ActiveSrc :%d", __FUNCTION__, eEntertainmentSrc);

    if(!isAudioResourceNull())
    {
        if(m_eActiveEntSrc != eEntertainmentSrc)
        {
            setIsSourceChangeRequestedByUser(true);
            m_pAudioResource->setActiveSourceID(eEntertainmentSrc);
        }
        else
        {
            // Here we are calling this function to switch to screen which is already active.
            // To Do: On screen transition if we are already in current active screen again screen transition should not happen.
            switchToActiveEntertainmentSourceScreen();
        }
    }
}

void CAudioAdaptor::setAudioPresetAttribute(int iAudioPreset)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s AudioPreset from qml : %d ", __FUNCTION__, iAudioPreset);
    CAudioEnums::EAudioPresets eAudioPreset = static_cast<CAudioEnums::EAudioPresets>(iAudioPreset);

    if(m_mapAudioPreset.contains(eAudioPreset) && (!isAudioResourceNull()))
    {
        m_pAudioResource->setAudioPreset(m_mapAudioPreset.value(eAudioPreset).toStdString());
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s Map Doesn't contains the preset ", __FUNCTION__);
    }
}

void CAudioAdaptor::updateBalanceFaderPositions(float fFaderPos, float fBalancePos)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s :", __FUNCTION__);
    //Calculating fader value from position
    int fader = -(qRound(((fFaderPos * BALANCE_FADER_RANGE) / BAL_FAD_MAT_HEIGHT) - BALANCE_FADER_SCALE_SHIFT));
    //Calculating balance value from position
    int balance = qRound(((fBalancePos * BALANCE_FADER_RANGE) / BAL_FAD_MAT_WIDTH) - BALANCE_FADER_SCALE_SHIFT);
    //Updating positions of balance & fader vertical, horizontal lines & pointer locally
    setBalancePos(balance);
    setBalance(balance);
    setFaderPos(fader);
    setFader(fader);
}

void CAudioAdaptor::switchToActiveEntertainmentSourceScreen()
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: eActiveEntertainmentSource: %d ", __FUNCTION__, m_eActiveEntSrc);

    switch (m_eActiveEntSrc) {
    case CAudioEnums::SRC_TUNER_AM:
    case CAudioEnums::SRC_TUNER_FM:
    case CAudioEnums::SRC_TUNER_DAB:
    case CAudioEnums::SRC_TUNER_DRM:
    {
        CHMIMain::getSM()->getSCI_Audio()->set_activeSrcCategory(CAudioEnums::SOURCE_CATEGORY_TUNER);
        CHMIMain::getSM()->getDefaultSCI()->raise_evTunerActivated();
    }
        break;
    case CAudioEnums::SRC_AUDIO_AUX:
    case CAudioEnums::SRC_BT_A2DP1:
    case CAudioEnums::SRC_BT_A2DP2:
    case CAudioEnums::SRC_USB1:
    case CAudioEnums::SRC_USB2:
    case CAudioEnums::SRC_IPOD:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: requestMediaActivation() to Media Adaptor", __FUNCTION__);
        CHMIMain::getSM()->getSCI_Audio()->set_activeSrcCategory(CAudioEnums::SOURCE_CATEGORY_MEDIA);
        CMediaAdaptor::getInstance().setMediaDisplayState(CMediaEnum::MEDIA_DISPLAYSTATE_NONE);
        CMediaAdaptor::getInstance().requestMediaActivation(true);
    }
        break;

    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: In Default case", __FUNCTION__);
    }
        break;
    }

}

CAudioEnums::EAudioPresets CAudioAdaptor::configuredAudioPreset()
{
    return m_eConfiguredAudioPreset;
}

void CAudioAdaptor::setConfiguredAudioPreset(int iIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_DRAWERS, "%s: Selected Audio Preset Index : %d", __FUNCTION__, iIndex);
    if(iIndex != CAudioEnums::AUDIO_PRESET_ROCK && iIndex != CAudioEnums::AUDIO_PRESET_POP)
    {
        m_eConfiguredAudioPreset = static_cast<CAudioEnums::EAudioPresets>(iIndex);
        CPersistencyAdaptor::getInstance().writeIntData(EPersistencyKeys::HMI_PCL_I_SETUP_AUDIO_PRESET, m_eConfiguredAudioPreset);
    }
    emit sigConfiguredAudioPresetChanged();
}

void CAudioAdaptor::toggleMute(bool bUserInitiated)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s: bUserInitiated = %d", __FUNCTION__, bUserInitiated);
    if(!isAudioResourceNull())
    {
        m_pAudioResource->toggleMute(bUserInitiated);
    }
    else
    {
        //Do nothing
    }
}

QString CAudioAdaptor::convertIntValueFormat(int value)
{
    QString formattedString = "";
    if(value > 0)
    {
        formattedString = QString("%1").arg(value, CAudioAdaptor::FORMATTED_STR_LEN_2, CAudioAdaptor::BASE_10, QChar('0'));
    }
    else if (value < 0)
    {
        formattedString = QString("%1").arg(value, CAudioAdaptor::FORMATTED_STR_LEN_3, CAudioAdaptor::BASE_10, QChar('0'));
    }
    else
    {
        formattedString = QString("%1").arg(value, CAudioAdaptor::FORMATTED_STR_LEN_2, CAudioAdaptor::BASE_10, QChar('0'));
    }
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s - value :%s", __FUNCTION__, formattedString.toStdString().c_str());
    return formattedString;
}

bool CAudioAdaptor::isAudioInterruptSourceActive(
        CAudioEnums::EAudioInterruptSources eAudioInterruptSource)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s: eAudioInterruptSource: %d",
             __FUNCTION__, eAudioInterruptSource);

    bool bReturnValue = false;

    if ( m_pAudioResource )
    {
        const vector<uint16_t>& vectActiveAudioSource = m_pAudioResource->getActiveAudioSourceList();

        if ( std::find(vectActiveAudioSource.begin(), vectActiveAudioSource.end(), eAudioInterruptSource) != vectActiveAudioSource.end() )
        {
            bReturnValue = true;
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "%s: Audio Interrupt source is not active.", __FUNCTION__);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_AUDIO, "%s: m_pAudioResource is NULL",
                    __FUNCTION__);
    }

    return bReturnValue;
}

void CAudioAdaptor::setIsSourceChangeRequestedByUser(bool bIsSrcChangeRequestedByUser)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s: bIsSrcChangeRequestedByUser: %d", __FUNCTION__, bIsSrcChangeRequestedByUser);

    if (m_bIsSourceChangeRequestedByUser != bIsSrcChangeRequestedByUser)
    {
        /*
         * If PDC/RVC is not active, then only we have to set
         * this variable to true, else we have to set this false, and no action
         * (screen(Active source) transition) should be happen on source activation.
         */
        if (!CParkAssistAdaptor::getInstance()->pdcRvcScreenStatus())
        {

            m_bIsSourceChangeRequestedByUser = bIsSrcChangeRequestedByUser;
        }
        else
        {
            m_bIsSourceChangeRequestedByUser = false;
            LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s: PDC/RVC is active, No Action", __FUNCTION__);
        }
    }
    else
    {

        LOG_INFO(Log::e_LOG_CONTEXT_AUDIO, "%s: Values are same.", __FUNCTION__);
    }

    // Set the information to mediaOff state within statemachine
    CHMIMain::getSM()->getSCI_MediaOff()->set_bIsTransitionAllowed(m_bIsSourceChangeRequestedByUser);
}
/* Methods invoked from qml - end */

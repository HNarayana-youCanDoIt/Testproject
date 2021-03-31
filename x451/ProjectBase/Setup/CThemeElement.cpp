/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CThemeElement.cpp
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CThemeElement.cpp, theme preset class cpp file, responsible for creating theme preset data model
 */
#include "CThemeElement.h"
#include "logging.h"
#include "CHMIMain.h"
#include "CHVACAdaptor.h"

CThemeElement* CThemeElement::m_pThemeElement = nullptr;

CThemeElement::CThemeElement(QObject *parent) : QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);

    mapThemeAudioPreset();
}


CThemeElement::CThemeElement(int iFanSpeed, float fTemeperature, int iDistributionMode, int iColorMode, int iThemeDisplayBrightness, int iNotificationVol,
                             int iThemeAudioPreset, int iThemeBassValue, int iThemeMidValue, int iThemeTrebleValue, int iThemeAmbLightIlluLevel, QObject *parent) : QObject(parent),
    m_iFanSpeed(0),
    m_fTemperature(0),
    m_iAirFlowDistributionMode(0),
    m_iColorMode(0),
    m_iNotificationVol(0),
    m_iThemeAudioPreset(0),
    m_iThemeBass(0),
    m_iThemeMid(0),
    m_iThemeTreble(0),
    m_iThemeAmbLightIlluLevel(0),
    m_iThemeDisplayBrightness(0)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    mapThemeAudioPreset();
    setFanSpeed(iFanSpeed);
    setTemperature(fTemeperature);
    setAirFlowDistributionMode(iDistributionMode);
    setColorMode(iColorMode);
    setThemeDisplayBrightness(iThemeDisplayBrightness);
    setNotificationVolume(iNotificationVol);
    setThemeAudioPreset(iThemeAudioPreset);
    setThemeBassValue(iThemeBassValue);
    setThemeMidValue(iThemeMidValue);
    setThemeTrebleValue(iThemeTrebleValue);
    setThemeAmbLightIlluLevel(iThemeAmbLightIlluLevel);
    CFramework::getFramework().setContextProperty("cppThemeElement", this);

}

CThemeElement::~CThemeElement()
{
    m_pThemeElement = nullptr;
}

CThemeElement* CThemeElement::getInstance()
{
    if(nullptr == m_pThemeElement)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HVAC, __FUNCTION__);
        m_pThemeElement = new CThemeElement();
    }
    return m_pThemeElement;
}

void CThemeElement::mapThemeAudioPreset()
{
    /*Inserting Audio preset index and preset values */
    m_mapAudioPresetTheme.clear();
    m_mapAudioPresetTheme.insert(CAudioEnums::AUDIO_PRESET_FLAT,    "Flat");
    m_mapAudioPresetTheme.insert(CAudioEnums::AUDIO_PRESET_ROCK,    "Rock");
    m_mapAudioPresetTheme.insert(CAudioEnums::AUDIO_PRESET_CLASSIC, "Classic");
    m_mapAudioPresetTheme.insert(CAudioEnums::AUDIO_PRESET_POP,     "Pop");
    m_mapAudioPresetTheme.insert(CAudioEnums::AUDIO_PRESET_JAZZ,    "Jazz");
    m_mapAudioPresetTheme.insert(CAudioEnums::AUDIO_PRESET_HIPHOP,  "Speech");
    m_mapAudioPresetTheme.insert(CAudioEnums::AUDIO_PRESET_CUSTOM,  "User");

}

void CThemeElement::setFanSpeed(int iFanSpeed)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, " %s Set Fan Speed: %d", __FUNCTION__, iFanSpeed);
    if ((iFanSpeed >= CHVACAdaptor::getInstance()->fanSpeedLowLimit())
            && (iFanSpeed <=CHVACAdaptor::getInstance()->fanSpeedHighLimit()))
    {
        if (iFanSpeed != m_iFanSpeed)
        {
            m_iFanSpeed = iFanSpeed;
            emit sigFanSpeedChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
        }
    }
}

void CThemeElement::setTemperature(float fTemperature)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, " %s Set Temperature: %f", __FUNCTION__, fTemperature);
    if (m_fTemperature != fTemperature)
    {
        m_fTemperature = fTemperature;
        emit sigTemperatureChanged();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
    }
}

void CThemeElement::setAirFlowDistributionMode(int iAirFlowDistributionMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, " %s set Distribution Mode %d", __FUNCTION__, iAirFlowDistributionMode);
    if(iAirFlowDistributionMode >= 0)
    {
        if (iAirFlowDistributionMode != m_iAirFlowDistributionMode)
        {
            m_iAirFlowDistributionMode = iAirFlowDistributionMode;
            emit sigAirFlowDistributionModeChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
        }
    }
}

void CThemeElement::setColorMode(int iColorMode)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, " %s set color Mode %d", __FUNCTION__, iColorMode);

    if(iColorMode >= 0)
    {
        if (iColorMode != m_iColorMode)
        {
            m_iColorMode = iColorMode;
            emit sigColorModeChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
        }
    }
}

void CThemeElement::setThemeDisplayBrightness(int iThemeDisplayBrightness)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, " %s set theme display brightness %d", __FUNCTION__, iThemeDisplayBrightness);

    if(iThemeDisplayBrightness >= 0)
    {
        if(iThemeDisplayBrightness != m_iThemeDisplayBrightness)
        {
            m_iThemeDisplayBrightness = iThemeDisplayBrightness;
            emit sigThemeDisplayBrightnessChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
        }
    }
}

void CThemeElement::setNotificationVolume(int iNotifiactionVol)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, " %s set Notification volume %d", __FUNCTION__, iNotifiactionVol);

    if(iNotifiactionVol >= 0)
    {
        if(iNotifiactionVol != m_iNotificationVol)
        {
            m_iNotificationVol = iNotifiactionVol;
            emit sigNotificationVolumeChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
        }
    }
}

void CThemeElement::setThemeAudioPreset(int iThemeAudioPreset)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set theme audio Preset : %d ", __FUNCTION__, iThemeAudioPreset);

    if(iThemeAudioPreset >= 0)
    {
        if(iThemeAudioPreset != m_iThemeAudioPreset)
        {
            m_iThemeAudioPreset = iThemeAudioPreset;
            emit sigThemeAudioPresetChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
        }
    }
}

QString CThemeElement::invGetThemeAudioPresetText(int iThemeAudioPresetIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s iThemeAudioPresetIndex : %d ", __FUNCTION__, iThemeAudioPresetIndex);
    return m_mapAudioPresetTheme.value(static_cast<CAudioEnums::EAudioPresets>(iThemeAudioPresetIndex));
}

void CThemeElement::setThemeBassValue(int iThemeBass)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set theme bass: %d ", __FUNCTION__, iThemeBass);

    if(iThemeBass >= 0)
    {
        if(iThemeBass != m_iThemeBass)
        {
            m_iThemeBass = iThemeBass;
            emit sigThemeBassValueChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
        }
    }
}

void CThemeElement::setThemeMidValue(int iThemeMid)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set theme mid: %d ", __FUNCTION__, iThemeMid);

    if(iThemeMid >= 0)
    {
        if(iThemeMid != m_iThemeMid)
        {
            m_iThemeMid = iThemeMid;
            emit sigThemeMidValueChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
        }
    }
}

void CThemeElement::setThemeTrebleValue(int iThemeTreble)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set theme treble: %d ", __FUNCTION__, iThemeTreble);
    if(iThemeTreble >= 0)
    {
        if(iThemeTreble != m_iThemeTreble)
        {
            m_iThemeTreble = iThemeTreble;
            emit sigThemeTrebleValueChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
        }
    }
}

void CThemeElement::setThemeAmbLightIlluLevel(int iThemeAmbLightIlluLevel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_AUDIO,"%s set theme amb light: %d ", __FUNCTION__, iThemeAmbLightIlluLevel);

    if(iThemeAmbLightIlluLevel >= 0)
    {
        if(iThemeAmbLightIlluLevel != m_iThemeAmbLightIlluLevel)
        {
            m_iThemeAmbLightIlluLevel = iThemeAmbLightIlluLevel;
            emit sigThemeAmbLightIlluLevelChanged();
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s Values are same", __FUNCTION__);
        }
    }
}

/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CPersistencyAdaptor.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CPersistencyAdaptor, an Adaptor for Persistency service,
 * CPersistencyAdaptor is singleton class used to read/write data information with persistency service.
 */

#include "CPersistencyAdaptor.h"
#include "CDPersistencyKeyValue.h"
#include "logging.h"
#include "CFramework.h"

CPersistencyAdaptor* CPersistencyAdaptor::m_pPersistencyAdaptor = nullptr;

///////////////////////////////////////////////////////////////////////////////
// Adaptor related functions
///////////////////////////////////////////////////////////////////////////////
CPersistencyAdaptor &CPersistencyAdaptor::getInstance()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s", __FUNCTION__);

    if (nullptr == m_pPersistencyAdaptor)
    {
        m_pPersistencyAdaptor = new CPersistencyAdaptor();
    }
    return *m_pPersistencyAdaptor;
}
//____________________________________________________________________________
CPersistencyAdaptor::CPersistencyAdaptor(QObject *parent) : QObject(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s", __FUNCTION__);

    CFramework::getFramework().setContextProperty("cppPersistencyAdaptor",this);
    m_pCPersistencyEventHandler = new CPersistencyEventHandler(this);
    validateDefaultPersistencyKeyValues();
}
//____________________________________________________________________________
CPersistencyAdaptor::~CPersistencyAdaptor()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s", __FUNCTION__);
    if (m_pCPersistencyEventHandler)
    {
        delete m_pCPersistencyEventHandler;
        m_pCPersistencyEventHandler = nullptr;
    }
    m_pPersistencyAdaptor = nullptr;
}
//____________________________________________________________________________
void CPersistencyAdaptor::validateDefaultPersistencyKeyValues()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s", __FUNCTION__);
    m_mapKeyValueTypes.clear();
    /** ***** PLEASE NOTE *****
     * After Any Change In Default value Update Date need to change,
     * This will reset value and flow shall run with new value. to avoid problems occurred due to old value.
     * m_mapKeyValueTypes[KEY_ENUM_VALUE] = CDPersistencyKeyValue(KEY_ENUM_VALUE,     Key_String,     Default_Value_String,     Update_Version_String);
     */
    m_mapKeyValueTypes[EPersistencyKeys::HMI_DATA_AVAILABLE]                                = CDPersistencyKeyValue(EPersistencyKeys::HMI_DATA_AVAILABLE,                               "HmiDataAvailable",                     "TATA",                                                         "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_EOL_ANDROID_AUTO_ON]                     = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_EOL_ANDROID_AUTO_ON,                    "HmiEOLAndroidAuto",                    "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_EOL_APPLE_CAR_PLAY_ON]                   = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_EOL_APPLE_CAR_PLAY_ON,                  "HmiEOLAppleCarPlay",                   "1",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_EOL_DOODLE_ON]                           = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_EOL_DOODLE_ON,                          "HmiEOLDoodle",                         "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_EOL_DRIVE_NEXT_ON]                       = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_EOL_DRIVE_NEXT_ON,                      "HmiEOLDriveNext",                      "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_EOL_W3W_ON]                              = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_EOL_W3W_ON,                             "HmiEOLW3W",                            "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_EOL_AUX_ON]                              = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_EOL_AUX_ON,                             "HmiEOLAux",                            "1",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_HOME_SLOT_01]                            = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_01,                           "HmiHomeSlot01",                        QString::number(CHomeEnum::SHORTCUT_ANDROID_AUTO_ID),           "2");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_HOME_SLOT_02]                            = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_02,                           "HmiHomeSlot02",                        QString::number(CHomeEnum::SHORTCUT_APPLE_CAR_PLAY_ID),         "2");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_HOME_SLOT_03]                            = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_03,                           "HmiHomeSlot03",                        QString::number(CHomeEnum::SHORTCUT_RADIO_ID),                  "2");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_HOME_SLOT_04]                            = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_04,                           "HmiHomeSlot04",                        QString::number(CHomeEnum::SHORTCUT_USB_ID),                    "2");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_HOME_SLOT_05]                            = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_05,                           "HmiHomeSlot05",                        QString::number(CHomeEnum::SHORTCUT_PHONE_SETUP_ID),            "2");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_HOME_SLOT_06]                            = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_HOME_SLOT_06,                           "HmiHomeSlot06",                        QString::number(CHomeEnum::SHORTCUT_ADD_SHORTCUT_ID),           "2");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_SETUP_SMS_NOTIFY_TYPE]                   = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_SETUP_SMS_NOTIFY_TYPE,                  "HmiSetupSMSNotifyType",                "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_SETUP_SMS_CONFIGURE_SELECTION]           = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_SETUP_SMS_CONFIGURE_SELECTION,          "HmiSetupSMSConfigSelection",           "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_ENGG_MENU_TEST_AUTOMATION]               = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_ENGG_MENU_TEST_AUTOMATION,              "HmiTestAutomation",                    "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_FAVORITE_SCREEN_OPTION_SELECTION]        = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_FAVORITE_SCREEN_OPTION_SELECTION,       "HmiFavoriteScrOptionSelection",        "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_SETUP_AUDIO_PRESET]                      = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_SETUP_AUDIO_PRESET,                     "HmiSetupAudioPreset",                  "2",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_SETUP_THEME_PRESET]                      = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_SETUP_THEME_PRESET,                     "HmiSetupThemePreset",                  "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_01]                     = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_01,                    "HmiSetupCustomSMS01",                  "I am busy right now, will call later.",                        "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_02]                     = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_02,                    "HmiSetupCustomSMS02",                  "In a meeting.",                                                "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_03]                     = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_03,                    "HmiSetupCustomSMS03",                  "Almost there.",                                                "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_04]                     = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_04,                    "HmiSetupCustomSMS04",                  "Can't talk now, call me later.",                               "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_05]                     = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_05,                    "HmiSetupCustomSMS05",                  "Can't talk, text me.",                                         "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_06]                     = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_06,                    "HmiSetupCustomSMS06",                  "Write your Own.....",                                          "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_07]                     = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_S_SETUP_CUSTOM_SMS_07,                    "HmiSetupCustomSMS07",                  "Write your Own.....",                                          "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_ENGG_STATIC_IP_SELECTION]                = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_ENGG_STATIC_IP_SELECTION,               "HmiEnggStaticIP",                      "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_ENGG_CPU_MEASUREMENT_SELECTION]          = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_ENGG_CPU_MEASUREMENT_SELECTION,         "HmiEnggCPUMeasurement",                "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_ENGG_RAM_MEASUREMENT_SELECTION]          = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_ENGG_RAM_MEASUREMENT_SELECTION,         "HmiEnggRAMMeasurement",                "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_ENGG_DEBUG_LOGS_SELECTION]               = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_ENGG_DEBUG_LOGS_SELECTION,              "HmiDebugLogs",                         "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_ENGG_IPC_LOGS_SELECTION]                 = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_ENGG_IPC_LOGS_SELECTION,                "HmiEnggIPCLogs",                       "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_CP_SMART_FAN_STATE]                      = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_CP_SMART_FAN_STATE,                     "HmiCpSmartFanState",                   "1",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_FANSPEED]                   = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_FANSPEED,                  "HmiThemeCustomFanspeed",               "1",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_TEMPERATURE]                = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_TEMPERATURE,               "HmiThemeCustomTemperature",            "20.0",                                                         "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_COLOR]                      = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_COLOR,                     "HmiThemeCustomColor",                  "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_BRIGHTNESS]                 = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_BRIGHTNESS,                "HmiThemeCustomBrightness",             "60",                                                           "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AMBIENTLIGHT]               = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AMBIENTLIGHT,              "HmiThemeCustomAmbientLight",           "2",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_NOTIFICATION]               = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_NOTIFICATION,              "HmiThemeCustomNotification",           "10",                                                           "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AUDIOPRESET]                = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_THEME_CUSTOM_AUDIOPRESET,               "HmiThemeCustomAudioPreset",            "3",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_CHANGE_THEME_WITH_DRIVE_MODE_STATUS]     = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_CHANGE_THEME_WITH_DRIVE_MODE_STATUS,    "HmiChangeThemeWithDriveModeStatus",    "1",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_HMI_THEME_SELECTION]                     = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_HMI_THEME_SELECTION,                    "HmiThemeSelection",                    "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_HMI_IC_CAST_STATE]                       = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_HMI_IC_CAST_STATE,                      "HmiIcCastState",                       "1",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_SELECTED_CLOCK_ID]                       = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_SELECTED_CLOCK_ID,                      "HmiSelectedClockId",                   "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_ACTIVATED]                = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_ACTIVATED,               "HmiDoodleStickerActivated",            "1",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_POS_X]                    = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_POS_X,                   "HmiDoodleStickerPosX",                 "650",                                                          "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_POS_Y]                    = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_DOODLE_STICKER_POS_Y,                   "HmiDoodleStickerPosY",                 "380",                                                          "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_W3W_AUTOLAUNCH_ANDROID_AUTO]             = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_W3W_AUTOLAUNCH_ANDROID_AUTO,            "HmiW3WAutoLaunchAndroidAuto",          "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_W3W_AUTOLAUNCH_APPLE_CARPLAY]            = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_W3W_AUTOLAUNCH_APPLE_CARPLAY,           "HmiW3WAutoLaunchAppleCarplay",         "0",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::HMI_PCL_I_W3W_STARTUP_WALKTHROUGH]                 = CDPersistencyKeyValue(EPersistencyKeys::HMI_PCL_I_W3W_STARTUP_WALKTHROUGH,                "HmiW3WWalkthroughOnStartup",           "1",                                                            "1");
    m_mapKeyValueTypes[EPersistencyKeys::TOTAL_KEYS]                                        = CDPersistencyKeyValue(EPersistencyKeys::TOTAL_KEYS,                                       "UNKNOWN",                              "UNKNOWN",                                                      "1");

    if (m_pCPersistencyEventHandler)
    {
        QString strUpdateVersionKey = "_U_Ver";

        QString strValue = m_pCPersistencyEventHandler->readDataFromPersistency(m_mapKeyValueTypes[EPersistencyKeys::HMI_DATA_AVAILABLE].getKey());
        QString strDefValue = m_mapKeyValueTypes[EPersistencyKeys::HMI_DATA_AVAILABLE].getDefaultValue();
        bool bResetAllData = (strValue != strDefValue);

        if (bResetAllData)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, Reset all data strValue:%s, strDefValue:%s", __FUNCTION__, strValue.toStdString().data(), strDefValue.toStdString().data());
            m_pCPersistencyEventHandler->WriteDataToPersistency(m_mapKeyValueTypes[EPersistencyKeys::HMI_DATA_AVAILABLE].getKey() + strUpdateVersionKey, m_mapKeyValueTypes[EPersistencyKeys::HMI_DATA_AVAILABLE].getUpdateVersion());
            m_pCPersistencyEventHandler->WriteDataToPersistency(m_mapKeyValueTypes[EPersistencyKeys::HMI_DATA_AVAILABLE].getKey(), m_mapKeyValueTypes[EPersistencyKeys::HMI_DATA_AVAILABLE].getDefaultValue());
        }
        else
        {
            //Do Nothing! Not Reseting All data.
        }

        for (int i = 1; i < EPersistencyKeys::TOTAL_KEYS; i++)
        {
            bool bReset = bResetAllData;
            if (!bResetAllData)
            {
                QString strOldDate = m_pCPersistencyEventHandler->readDataFromPersistency(m_mapKeyValueTypes[static_cast<EPersistencyKeys>(i)].getKey() + strUpdateVersionKey);
                QString strUpdateVersion = m_mapKeyValueTypes[static_cast<EPersistencyKeys>(i)].getUpdateVersion();
                if (strOldDate != strUpdateVersion)
                {
                    bReset = true;
                    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, EPersistencyKeys:%d, strOldDate:%s, strUpdateVersion:%s", __FUNCTION__, i, strOldDate.toStdString().data(), strUpdateVersion.toStdString().data());
                }
                else
                {
                    //Do Nothing! Key value is OK.
                    //LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, EPersistencyKeys:%d, strOldDate:%s, strUpdateVersion:%s", __FUNCTION__, i, strOldDate.toStdString().data(), strUpdateVersion.toStdString().data());
                }
            }
            else
            {
                //Do Nothing! Reseting All data.
            }

            if (bReset)
            {
                m_pCPersistencyEventHandler->WriteDataToPersistency(m_mapKeyValueTypes[static_cast<EPersistencyKeys>(i)].getKey() + strUpdateVersionKey, m_mapKeyValueTypes[static_cast<EPersistencyKeys>(i)].getUpdateVersion());
                m_pCPersistencyEventHandler->WriteDataToPersistency(m_mapKeyValueTypes[static_cast<EPersistencyKeys>(i)].getKey(), m_mapKeyValueTypes[static_cast<EPersistencyKeys>(i)].getDefaultValue());
            }
            else
            {
                //Do Nothing! Key value is OK. with No reset All.
            }
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PERSISTENCY,"%s, m_pCPersistencyEventHandler is null", __FUNCTION__);
    }
}
///////////////////////////////////////////////////////////////////////////////
// Persistency Service related functions
///////////////////////////////////////////////////////////////////////////////
int CPersistencyAdaptor::readIntData(EPersistencyKeys eKey)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, eKey:%d", __FUNCTION__,static_cast<int>(eKey));
    int iValue = -1;
    if (m_pCPersistencyEventHandler)
    {
        QString qstrValue = m_pCPersistencyEventHandler->readDataFromPersistency(m_mapKeyValueTypes[eKey].getKey());
        bool bStatus = false;
        iValue = qstrValue.toInt(&bStatus);
        if (!bStatus)
        {
            iValue = -1;
            LOG_WARNING(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, value for key:%s is '%s' which is not a number", __FUNCTION__, m_mapKeyValueTypes[eKey].getKey().toStdString().c_str(), qstrValue.toStdString().c_str());
        }
        else
        {
            // Do Nothing
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, m_pCPersistencyEventHandler is null", __FUNCTION__);
    }
    return iValue;
}
//____________________________________________________________________________
bool CPersistencyAdaptor::writeIntData(EPersistencyKeys eKey, int iValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, eKey:%d, iValue:%d", __FUNCTION__,static_cast<int>(eKey), iValue);
    bool bResult = false;
    if (m_pCPersistencyEventHandler)
    {
        bResult = m_pCPersistencyEventHandler->WriteDataToPersistency(m_mapKeyValueTypes[eKey].getKey(), QString::number(iValue));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PERSISTENCY,"%s, m_pCPersistencyEventHandler is null", __FUNCTION__);
    }
    return bResult;
}
//____________________________________________________________________________
float CPersistencyAdaptor::readFloatData(EPersistencyKeys eKey)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, eKey:%d", __FUNCTION__,static_cast<int>(eKey));
    float fValue = 0.0;
    if (m_pCPersistencyEventHandler)
    {
        fValue = m_pCPersistencyEventHandler->readDataFromPersistency(m_mapKeyValueTypes[eKey].getKey()).toFloat();
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, m_pCPersistencyEventHandler is null", __FUNCTION__);
    }
    return fValue;
}
//____________________________________________________________________________
bool CPersistencyAdaptor::writeFloatData(EPersistencyKeys eKey, float fValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, eKey:%d, fValue:%f", __FUNCTION__,static_cast<int>(eKey), fValue);
    bool bResult = false;
    if (m_pCPersistencyEventHandler)
    {
        bResult = m_pCPersistencyEventHandler->WriteDataToPersistency(m_mapKeyValueTypes[eKey].getKey(), QString::number(fValue));
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PERSISTENCY,"%s, m_pCPersistencyEventHandler is null", __FUNCTION__);
    }
    return bResult;
}
//____________________________________________________________________________
QString CPersistencyAdaptor::readStringData(EPersistencyKeys eKey)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, eKey:%d", __FUNCTION__,static_cast<int>(eKey));
    QString strValue = "";
    if (m_pCPersistencyEventHandler)
    {
        strValue = m_pCPersistencyEventHandler->readDataFromPersistency(m_mapKeyValueTypes[eKey].getKey());
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, m_pCPersistencyEventHandler is null", __FUNCTION__);
    }
    return strValue;
}
//____________________________________________________________________________
bool CPersistencyAdaptor::writeStringData(EPersistencyKeys eKey, const QString &strValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, eKey:%d, strValue:%s", __FUNCTION__,static_cast<int>(eKey), strValue.toStdString().data());
    bool bResult = false;
    if (m_pCPersistencyEventHandler)
    {
        bResult = m_pCPersistencyEventHandler->WriteDataToPersistency(m_mapKeyValueTypes[eKey].getKey(), strValue);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PERSISTENCY, "%s, m_pCPersistencyEventHandler is null", __FUNCTION__);
    }
    return bResult;
}
//____________________________________________________________________________

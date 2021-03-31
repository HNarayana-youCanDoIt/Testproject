/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CDHomeShortcut.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CDHomeShortcut, a Data structure for Home module,
 * CDHomeShortcut maintains home-shortcut-button data information.
 */

#include "CDHomeShortcut.h"
#include "logging.h"
#include "CHomeAdaptor.h"


/// PLEASE NOTE: AFTER ADDING ANY NEW SHORTCUT PLEASE MAKE SURE TO UPDATE "strUpdateVersion" FOR BELOW ENTRIES
/// EPersistencyKeys::HMI_PCL_I_HOME_SLOT_01
/// EPersistencyKeys::HMI_PCL_I_HOME_SLOT_02
/// EPersistencyKeys::HMI_PCL_I_HOME_SLOT_03
/// EPersistencyKeys::HMI_PCL_I_HOME_SLOT_04
/// EPersistencyKeys::HMI_PCL_I_HOME_SLOT_05
/// EPersistencyKeys::HMI_PCL_I_HOME_SLOT_06
/// in CPersistencyAdaptor::validateDefaultPersistencyKeyValues()
const QString/*char **/ CDHomeShortcut::SHORTCUTS[CHomeEnum::MAX_SHORTCUTS_AVAILABLE][6] =
{ /*Title                                                       Icon path normal                                                Icon path pressed                                               Icon path inactive                                              Active  Available   Index*/
  "",                                                           "Hom_Ico_GridDot/Hom_Ico_GridDot_n.png",                        "Hom_Ico_GridDot/Hom_Ico_GridDot_np.png",                       "",                                                             "Y",    "Y",        /** 00 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_AndroidAuto"),           "Hom_Ico_AndroidAuto/Home_Ico_AndroidAuto_n.png",               "Hom_Ico_AndroidAuto/Home_Ico_AndroidAuto_np.png",              "Hom_Ico_AndroidAuto/Home_Ico_AndroidAuto_nd.png",              "N",    "Y",        /** 01 **/
  QT_TR_NOOP("TEXT_TITLE_CAR_PLAY"),                            "Hom_Ico_CarPlay/Hom_Ico_CarPlay_n.png",                        "Hom_Ico_CarPlay/Hom_Ico_CarPlay_np.png",                       "Hom_Ico_CarPlay/Hom_Ico_CarPlay_nd.png",                       "N",    "Y",        /** 02 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Audio_Setup"),           "Home_Ico_AudioSetup/Hom_Ico_AudioPreset_n.png",                "Home_Ico_AudioSetup/Hom_Ico_AudioPreset_np.png",               "Home_Ico_AudioSetup/Hom_Ico_AudioPreset_nd.png",               "Y",    "Y",        /** 03 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Ambient_Light"),         "Hom_Ico_Ambientlighting/Hom_Ico_Ambientlighting_7in_n.png",    "Hom_Ico_Ambientlighting/Hom_Ico_Ambientlighting_7in_np.png",   "Hom_Ico_Ambientlighting/Hom_Ico_Ambientlighting_7in_nd.png",   "N",    "Y",        /** 04 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_AUX"),                   "Hom_Ico_Aux/Hom_Ico_Aux_n.png",                                "Hom_Ico_Aux/Hom_Ico_Aux_np.png",                               "Hom_Ico_Aux/Hom_Ico_Aux_nd.png",                               "N",    "Y",        /** 05 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Bluetooth_Audio"),       "Hom_Ico_BluetoothMedia/Hom_Ico_BluetoothMedia_n.png",          "Hom_Ico_BluetoothMedia/Hom_Ico_BluetoothMedia_np.png",         "Hom_Ico_BluetoothMedia/Hom_Ico_BluetoothMedia_nd.png",         "N",    "Y",        /** 06 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Connect_Next"),          "Hom_Ico_ConnectNext/Home_Ico_ConnectNext_n.png",               "Hom_Ico_ConnectNext/Home_Ico_ConnectNext_np.png",              "Hom_Ico_ConnectNext/Home_Ico_ConnectNext_nd.png",              "N",    "N",        /** 07 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Contacts"),              "Hom_Ico_Contacts/Home_Ico_Contacts_n.png",                     "Hom_Ico_Contacts/Home_Ico_Contacts_np.png",                    "Hom_Ico_Contacts/Home_Ico_Contacts_nd.png",                    "Y",    "Y",        /** 08 **/
  //FixMe[NK] : Introduce string ID and its translations
  QT_TR_NOOP("*Doodle"),                                        "Hom_Ico_Doodle_7in_n-assets/Hom_Ico_Doodle_7in_n.png",         "Hom_Ico_Doodle_7in_n-assets/Hom_Ico_Doodle_7in_np.png",        "Hom_Ico_Doodle_7in_n-assets/Hom_Ico_Doodle_7in_nd.png",        "N",    "Y",        /** 09 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_DriveNext"),             "Hom_Ico_DriveNext_7in_n-assets/Hom_Ico_DriveNext_n.png",       "Hom_Ico_DriveNext_7in_n-assets/Hom_Ico_DriveNext_np.png",      "Hom_Ico_DriveNext_7in_n-assets/Hom_Ico_DriveNext_nd.png",      "N",    "Y",        /** 10 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Favorites"),             "Hom_Ico_Fav/Hom_Ico_Fav_n.png",                                "Hom_Ico_Fav/Hom_Ico_Fav_np.png",                               "Hom_Ico_Fav/Hom_Ico_Fav_nd.png",                               "Y",    "Y",        /** 11 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Help"),                  "Hom_Ico_Help/Home_Ico_Help_n.png",                             "Hom_Ico_Help/Home_Ico_Help_np.png",                            "Hom_Ico_Help/Home_Ico_Help_nd.png",                            "Y",    "N",        /** 12 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Ipod"),                  "Hom_Ico_Ipod/Hom_Ico_Ipod_n.png",                              "Hom_Ico_Ipod/Hom_Ico_Ipod_np.png",                             "Hom_Ico_Ipod/Hom_Ico_Ipod_nd.png",                             "N",    "Y",        /** 13 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Navigation"),            "Hom_Ico_Navigation/Hom_Ico_Navigation_n.png",                  "Hom_Ico_Navigation/Hom_Ico_Navigation_np.png",                 "Hom_Ico_Navigation/Hom_Ico_Navigation_nd.png",                 "N",    "N",        /** 14 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_ParkAssist"),            "Hom_Ico_ParkAssist_7in-assets/Hom_Ico_ParkAssist_7in_na.png",  "Hom_Ico_ParkAssist_7in-assets/Hom_Ico_ParkAssist_7in_np.png",  "Hom_Ico_ParkAssist_7in-assets/Hom_Ico_ParkAssist_7in_nd.png",  "N",    "Y",        /** 15 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Phone"),                 "Hom_Ico_Phone/Home_Ico_Phone_n.png",                           "Hom_Ico_Phone/Home_Ico_Phone_np.png",                          "Hom_Ico_Phone/Home_Ico_Phone_nd.png",                          "Y",    "Y",        /** 16 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Phone_Setup"),           "Home_Ico_PhoneSetup/Home_Ico_PhoneSetup_X07in_na.png",         "Home_Ico_PhoneSetup/Home_Ico_PhoneSetup_X07in_np.png",         "Home_Ico_PhoneSetup/Home_Ico_PhoneSetup_X07in_nd.png",         "Y",    "Y",        /** 17 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Radio"),                 "Hom_Ico_Tuner/Home_Ico_Radio_n.png",                           "Hom_Ico_Tuner/Home_Ico_Radio_np.png",                          "Hom_Ico_Tuner/Home_Ico_Radio_nd.png",                          "N",    "Y",        /** 18 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Settings"),              "Hom_Ico_Settings_7in_n-assets/Hom_Ico_Settings_7in_na.png",    "Hom_Ico_Settings_7in_n-assets/Hom_Ico_Settings_7in_np.png",    "Hom_Ico_Settings_7in_n-assets/Hom_Ico_Settings_7in_nd.png",    "Y",    "Y",        /** 19 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_SoundDemo"),             "Hom_Ico_SoundDemo_n-assets/Home_Ico_SoundDemo_n.png",          "Hom_Ico_SoundDemo_n-assets/Home_Ico_SoundDemo_np.png",         "Hom_Ico_SoundDemo_n-assets/Home_Ico_SoundDemo_nd.png",         "Y",    "Y",        /** 20 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Source"),                "",                                                             "",                                                             "",                                                             "N",    "N",        /** 21 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Themes"),                "Hom_Ico_Theme/Home_Ico_theme_na.png",                          "Hom_Ico_Theme/Home_Ico_theme_np.png",                          "Hom_Ico_Theme/Home_Ico_theme_nd.png",                          "Y",    "Y",        /** 22 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_USB"),                   "Hom_Ico_USB/Hom_Ico_USB_n.png",                                "Hom_Ico_USB/Hom_Ico_USB_np.png",                               "Hom_Ico_USB/Hom_Ico_USB_nd.png",                               "N",    "Y",        /** 23 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_Vehicle_Settings"),      "",                                                             "",                                                             "",                                                             "N",    "N",        /** 24 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_VoiceCommand"),          "Hom_Ico_VoiceCommand/Home_Ico_VoiceCommand_n.png",             "Hom_Ico_VoiceCommand/Home_Ico_VoiceCommand_np.png",            "Hom_Ico_VoiceCommand/Home_Ico_VoiceCommand_nd.png",            "Y",    "Y",        /** 25 **/
  QT_TR_NOOP("TEXT_HOME_SHORTCUT_TITLE_W3W"),                   "Hom_Ico_W3W_7in_n-assets/Home_Ico_W3W_n.png",                  "Hom_Ico_W3W_7in_n-assets/Home_Ico_W3W_np.png",                 "Hom_Ico_W3W_7in_n-assets/Home_Ico_W3W_nd.png",                 "N",    "Y",        /** 26 **/
};

/**
 * Add default shortcut ID sequence
 **/
const int CDHomeShortcut::DEFAULT_SHORTCUT_IDS[CDHomeShortcut::DEFAULT_SHORTCUTS_AVAILABLE] =
{
    CHomeEnum::SHORTCUT_ANDROID_AUTO_ID,
    CHomeEnum::SHORTCUT_APPLE_CAR_PLAY_ID,
    CHomeEnum::SHORTCUT_RADIO_ID,
    CHomeEnum::SHORTCUT_USB_ID,
    CHomeEnum::SHORTCUT_PHONE_SETUP_ID,
    CHomeEnum::SHORTCUT_THEMES_ID,
    CHomeEnum::SHORTCUT_AUDIO_SETUP_ID,
    //CHomeEnum::SHORTCUT_CONTACTS_ID,
    //CHomeEnum::SHORTCUT_FAVOURITE_ID,
    //CHomeEnum::SHORTCUT_IPOD_ID,
    //CHomeEnum::SHORTCUT_PHONE_ID,
    //CHomeEnum::SHORTCUT_VOICE_COMMAND_ID,
    //CHomeEnum::SHORTCUT_AMBIENT_LIGHT_ID,
};


CDHomeShortcut::CDHomeShortcut(int _uid, QObject *parent) : QObject(parent)
{
    setUId(_uid);
    setText(tr(CDHomeShortcut::SHORTCUTS[_uid][0].toStdString().c_str()));
    setIconNormal(CDHomeShortcut::SHORTCUTS[_uid][1]);
    setIconPressed(CDHomeShortcut::SHORTCUTS[_uid][2]);
    setIconInactive(CDHomeShortcut::SHORTCUTS[_uid][3]);
    setIsActive("Y" == CDHomeShortcut::SHORTCUTS[_uid][4]);
    setIsAvailable("Y" == CDHomeShortcut::SHORTCUTS[_uid][5]);
}
CDHomeShortcut::~CDHomeShortcut()
{

}
//____________________________________________________________________________
int CDHomeShortcut::uId()
{
    return m_UId;
}
void CDHomeShortcut::setUId(int val)
{
    if (m_UId != val)
    {
        m_UId = val;
        emit sigUIdChanged();
    }
}
//____________________________________________________________________________
QString CDHomeShortcut::text()
{
    return m_Text;
}
void CDHomeShortcut::setText(QString val)
{
    if (m_Text != val)
    {
        m_Text = val;
        emit sigTextChanged();
    }
}
//____________________________________________________________________________
QString CDHomeShortcut::iconNormal()
{
    return m_IconNormal;
}
void CDHomeShortcut::setIconNormal(QString val)
{
    if (m_IconNormal != val)
    {
        m_IconNormal = val;
        emit sigIconNormalChanged();
    }
}
//____________________________________________________________________________
QString CDHomeShortcut::iconPressed()
{
    return m_IconPressed;
}
void CDHomeShortcut::setIconPressed(QString val)
{
    if (m_IconPressed != val)
    {
        m_IconPressed = val;
        emit sigIconPressedChanged();
    }
}
//____________________________________________________________________________
QString CDHomeShortcut::iconInactive()
{
    return m_IconInactive;
}
void CDHomeShortcut::setIconInactive(QString val)
{
    if (m_IconInactive != val)
    {
        m_IconInactive = val;
        emit sigIconInactiveChanged();
    }
}
//____________________________________________________________________________
bool CDHomeShortcut::isActive()
{
    return m_IsActive;
}
void CDHomeShortcut::setIsActive(bool val)
{
    if (m_IsActive != val)
    {
        m_IsActive = val;
        emit sigIsActiveChanged();
    }
}
//____________________________________________________________________________
bool CDHomeShortcut::isAvailable()
{
    return m_IsAvailable;
}
void CDHomeShortcut::setIsAvailable(bool val)
{
    if (m_IsAvailable != val)
    {
        m_IsAvailable = val;
        emit sigIsAvailableChanged();
    }
}
//____________________________________________________________________________
void CDHomeShortcut::invShortcutClicked(int _index)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, UID:%d Index:%d", __FUNCTION__, m_UId, _index);
    if (nullptr == onButtonClickCBFunction)
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_HOME, "%s, No onButtonClickCBFunction found for shortcutID %d", __FUNCTION__, m_UId);
        return;
    }
    ((CHomeAdaptor::getInstance()).*onButtonClickCBFunction)(_index);
}
//____________________________________________________________________________

/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CHomeEnum.h
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         This file contains CHomeEnum class that contains all the Home UI module related enums.
 */

#ifndef CHOMEENUM_H
#define CHOMEENUM_H

#include <QObject>
#include <QtQml>

/*!
 * @class CHomeEnum
 * @brief This class contains Home UI module related enums.
 */
class CHomeEnum: public QObject
{
    Q_OBJECT
public:


    /**
     * @enum    EDrawerState
     * @brief   EHomeShortcutsUID : enum for shortcut ID's with same index as SHORTCUTS array
     */
    enum EHomeShortcutsUID
    {
        SHORTCUT_BLANK_ID = -1,             /** dead shortcut used at last page of home screen **/
        SHORTCUT_ADD_SHORTCUT_ID = 0,       /** empty shortcut used at home (1st) page of home screen **/
        SHORTCUT_ANDROID_AUTO_ID,
        SHORTCUT_APPLE_CAR_PLAY_ID,
        SHORTCUT_AUDIO_SETUP_ID,
        SHORTCUT_AMBIENT_LIGHT_ID,
        SHORTCUT_AUX_IN_ID,
        SHORTCUT_BLUETOOTH_ID,
        SHORTCUT_CONNECT_NEXT_ID,
        SHORTCUT_CONTACTS_ID,
        SHORTCUT_DOODLE_ID,
        SHORTCUT_DRIVENEXT_ID,
        SHORTCUT_FAVOURITE_ID,
        SHORTCUT_HELP_ID,
        SHORTCUT_IPOD_ID,
        SHORTCUT_NAVIGATION_ID,
        SHORTCUT_PARK_ASSIST_ID,
        SHORTCUT_PHONE_ID,
        SHORTCUT_PHONE_SETUP_ID,
        SHORTCUT_RADIO_ID,
        SHORTCUT_SETTINGS_MAIN_ID,
        SHORTCUT_SOUNDDEMO_ID,
        SHORTCUT_TOGGLE_SOURCE_ID,
        SHORTCUT_THEMES_ID,
        SHORTCUT_USB_ID,
        SHORTCUT_VEHICLE_SETTING_ID,
        SHORTCUT_VOICE_COMMAND_ID,
        SHORTCUT_W3W_ID,
        MAX_SHORTCUTS_AVAILABLE,            /** total integrated shortcut count **/
    };
    Q_ENUM(EHomeShortcutsUID)

    static void registerHomeEnumsToQML()
    {
        qmlRegisterType<CHomeEnum>("com.harman.qml.homeenum", 1, 0, "HomeEnum");
    }
};

Q_DECLARE_METATYPE(CHomeEnum::EHomeShortcutsUID)

#endif // CHOMEENUM_H

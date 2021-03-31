#ifndef CHARDKEYENUM_H
#define CHARDKEYENUM_H

#include <QObject>
#include <QtQml>

/**
 * @brief The CHardKeyEnum class
 * The class will be used to declare all required ENUM for hardkey Application layer and QML layer also.
**/

class CHardKeyEnum: public QObject
{
    Q_OBJECT
public:

    /**
     * @enum    EHardKeyState
     * @brief   Enum for different hard key states
     */
    enum EHardKeyState
    {
        HKEY_STATE_INVALID = 0u,
        HKEY_STATE_PRESSED,
        HKEY_STATE_LONGPRESSED,
        HKEY_STATE_RELEASED,
        HKEY_STATE_LONGRELEASED,
        HKEY_STATE_ROTATE_LEFT,
        HKEY_STATE_ROTATE_RIGHT,
        HKEY_STATE_STUCK
    };
    Q_ENUMS(EHardKeyState)

    /**
     * @enum    EHardKeys
     * @brief   Enum for different hard key code
     */
    enum EHardKeys
    {
        KEYCODEHK_INVALID=0u,

        //Hard keys used in X451 board
        KEYCODEHK_VOLROTARY=20,
        KEYCODEHK_MENUROTARY,
        KEYCODEHK_HOME,
        KEYCODEHK_FAVORITE,
        KEYCODEHK_SEEKDOWN,
        KEYCODEHK_SEEKUP,
        KEYCODEHK_PHONE,
        KEYCODEHK_BACK,
        KEYCODEHK_VOLROTARY_KNOB,
        KEYCODEHK_MENUROTARY_KNOB,
        KEYCODEHK_SOFTWARE_UPDATE,
        KEYCODEHK_ENGGMENU,

        //Touch keys used in X0_7" board
        KEYCODETOUCH_POWER=60,
        KEYCODETOUCH_HOME,
        KEYCODETOUCH_FAVOURITE,
        KEYCODETOUCH_MUTE,
        KEYCODETOUCH_VOLUME_UP,
        KEYCODETOUCH_VOLUME_DOWN,
        KEYCODETOUCH_SOFTWARE_UPDATE,
        KEYCODETOUCH_ENGGMENU,

        //SWC keys used in both X0_7" and X451 boards
        KEYCODESWC_PREV=40,
        KEYCODESWC_SOURCE,
        KEYCODESWC_NEXT,
        KEYCODESWC_REJECT_MUTE,
        KEYCODESWC_UP,
        KEYCODESWC_DOWN,
        KEYCODESWC_ACCEPT_VR
    };
    Q_ENUMS(EHardKeys)

    /**
     * @brief The EFavKeyCode enum to create enmerations for all possible fav key configuration.
     */
    enum EFavKeyCode{

        FAV_HK = 0,
        FAV_HK_SOURCE,
        FAV_HK_PARK_ASSIST,
        FAV_HK_CONTACTS,
        FAV_HK_AUDIO_SETUP,
        FAV_HK_FAVOURITES,
        FAV_HK_VOICE_COMMAND,
        FAV_HK_NAVIGATION,
        FAV_HK_MOODLIGHTING,
        FAV_HK_ANDROIDAUTO,
        FAV_HK_CARPLAY,
    };
    Q_ENUMS(EFavKeyCode)

    /**
     * @brief registerHardKeyEnumToQML function to register enums to QML.
     */
    static void registerHardKeyEnumToQML()
    {
        qmlRegisterType<CHardKeyEnum>("com.harman.qml.hardkeyenum",1,0,"HardkeyEnum");
    }
};

Q_DECLARE_METATYPE(CHardKeyEnum::EHardKeys)
Q_DECLARE_METATYPE(CHardKeyEnum::EHardKeyState)
Q_DECLARE_METATYPE(CHardKeyEnum::EFavKeyCode)

#endif // CHARDKEYENUM_H


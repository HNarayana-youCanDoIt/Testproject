/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file            CW3WEnum.h
 * @ingroup         HMIComponent
 * @author          Nishant Khandagale
 * CW3WEnum, file that contain enums that will be used in W3W.
 */

#ifndef CW3WENUM_H
#define CW3WENUM_H

#include <QObject>
#include <QtQml>

class CW3WEnum: public QObject
{
    Q_OBJECT
public:

    /**
     * @enum    EW3WAddressType
     * @brief   It contains the type of W3W address.
     */
    enum EW3WAddressType
    {
        W3W_ADDRESS_TYPE_INVALID            = -1,
        W3W_ADDRESS_TYPE_AUTO_SUGGESTION    = 0,
        W3W_ADDRESS_TYPE_SELECTED           = 1,
        W3W_ADDRESS_TYPE_FAVORITE           = 2,
        W3W_ADDRESS_TYPE_RECENT             = 3,
        W3W_ADDRESS_TYPE_MAX_COUNT
    };
    Q_ENUM(EW3WAddressType)

    /**
     * @enum    EW3WFavoriteOperation
     * @brief   It contains the type of operation performed on/for favorite address.
     */
    enum EW3WFavoriteOperation
    {
        W3W_FAVORITE_OPERATION_INVALID      = -1,
        W3W_FAVORITE_OPERATION_ADD          = 0,
        W3W_FAVORITE_OPERATION_EDIT         = 1,
        W3W_FAVORITE_OPERATION_MAX_COUNT
    };
    Q_ENUM(EW3WFavoriteOperation)

    /**
     * @enum    EW3WItemType
     * @brief   It contains the type of W3W items to be shown on screen.
     */
    enum EW3WItemType
    {
        ITEM_TYPE_INVALID                   = -1,
        ITEM_TYPE_LABEL                     = 0,
        ITEM_TYPE_LABEL_WITH_DROPDOWN       = 1,
        ITEM_TYPE_LABEL_WITH_RADIO_BUTTON   = 2,
        ITEM_TYPE_LABEL_WITH_CHECKBOX       = 3,
        ITEM_TYPE_AUTO_SUGGESTION           = 4,
        ITEM_TYPE_W3W_ADDRESS               = 5,
        ITEM_TYPE_MAX_COUNT
    };
    Q_ENUM(EW3WItemType)

    /**
     * @enum    EW3WSetupItems
     * @brief   It contains the items in W3W setup screen.
     */
    enum EW3WSetupItems
    {
        W3W_SETUP_INVALID                   = -1,
        W3W_SETUP_AUTOLAUNCH_PERMISSIONS    = 0,
        W3W_SETUP_AUTOLAUNCH_PERMISSIONS_AA = 1,
        W3W_SETUP_AUTOLAUNCH_PERMISSIONS_CP = 2,
        W3W_SETUP_COUNTRY_PREFERENCE        = 3,
        W3W_SETUP_COUNTRY_PREFERENCE_IN     = 4,
        W3W_SETUP_COUNTRY_PREFERENCE_ALL    = 5,
        W3W_SETUP_STARTUP_WALKTHROUGH       = 6,
        W3W_SETUP_MAX_COUNT
    };
    Q_ENUM(EW3WSetupItems)

    /**
     * @enum    EAutoLaunchPermissionItemId
     * @brief   It contains AutoLaunchPermission options
     */
    enum EAutoLaunchPermissionItemId
    {
        PERMISSION_ID_INVALID           = -1,
        ANDROID_AUTO_PERMISSION_ID      = 0,
        APPLE_CARPLAY_PERMISSION_ID     = 1,
        PERMISSION_ID_MAX_COUNT         = 2,
    };
    Q_ENUM(EAutoLaunchPermissionItemId)

    /**
     * @enum    ECountryPreferenceItemId
     * @brief   It contains Country Preference options
     */
    enum ECountryPreferenceItemId
    {
        COUNTRY_PREFERENCE_INVALID      = -1,
        COUNTRY_PREFERENCE_INDIA_ID     = 0,
        COUNTRY_PREFERENCE_ALL_ID       = 1,
        COUNTRY_PREFERENCE_MAX_COUNT    = 2,
    };
    Q_ENUM(ECountryPreferenceItemId)


    /**
     * @enum    EW3WAboutItems
     * @brief   It contains the items in W3W About screen.
     */
    enum EW3WAboutItems
    {
        W3W_ABOUT_INVALID                   = -1,
        W3W_ABOUT_ITEM_1                    = 0,
        W3W_ABOUT_ITEM_2                    = 1,
        W3W_ABOUT_ITEM_MAX_COUNT            = 2,
    };
    Q_ENUM(EW3WAboutItems)

    static void registerW3WEnumsToQML()
    {
        qmlRegisterType<CW3WEnum>("com.harman.qml.w3wenum",1,0,"W3WEnum");
    }
};

Q_DECLARE_METATYPE(CW3WEnum::EW3WAddressType)
Q_DECLARE_METATYPE(CW3WEnum::EW3WFavoriteOperation)
Q_DECLARE_METATYPE(CW3WEnum::EW3WItemType)
Q_DECLARE_METATYPE(CW3WEnum::EW3WSetupItems)
Q_DECLARE_METATYPE(CW3WEnum::EAutoLaunchPermissionItemId)
Q_DECLARE_METATYPE(CW3WEnum::ECountryPreferenceItemId)
Q_DECLARE_METATYPE(CW3WEnum::EW3WAboutItems)

#endif // CW3WENUM_H

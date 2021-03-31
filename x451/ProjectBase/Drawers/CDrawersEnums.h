/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CDrawersEnums.h
* @ingroup      HMIComponent
* @author       Vishal Chaudhary
* This file is having the definition for Enums class of Drawers,
* This declares all the enums related to Drawers and register all enums to
* qt meta system to use in qml.
*/

#ifndef CDRAWERSENUMS_H
#define CDRAWERSENUMS_H

#include <QObject>
#include <QtQml>

/**
 * @class CDrawersEnums
 * @brief The CDrawersEnums class declares all the enums related to Drawers and register all enums to
 * qt meta system to use in qml.
 */
class CDrawersEnums: public QObject
{
    Q_OBJECT
public:

    /**
     * @enum    EDrawerState
     * @brief   The EDrawerState enum defines all the possible state for drawer.
     */
    enum EDrawerState
    {
        DRAWER_STATE_INVALID = -1,
        DRAWER_STATE_COLLAPSE,
        DRAWER_STATE_EXPAND,
        DRAWER_STATE_MAXIMIZED,
    };
    Q_ENUMS(EDrawerState)

    /**
     * @enum  EDrawerOverlays
     * @brief The EDrawerOverlays enum defines the ID for the 2 types of overlays
     */
    enum EDrawerOverlays
    {
        DRAWER_OVERLAYS_HVAC = 0,
        DRAWER_OVERLAYS_VOLUME
    };
    Q_ENUMS(EDrawerOverlays)

    /**
     * @enum    EDrawer
     * @brief   The EDrawer enum defines the ID of all four drawers.
     */
    enum EDrawer
    {
        DRAWER_HVAC,
        DRAWER_SOURCE,
        DRAWER_QAD,
        DRAWER_SHORTCUT,
    };
    Q_ENUMS(EDrawer)

    /**
     * @enum    EDrawer
     * @brief   The EDrawer enum defines the ID of all four drawers.
     */
    enum EHvacSlideBars
    {
        HVAC_SLIDEBAR_NONE,
        HVAC_FAN_SLIDEBAR,
        HVAC_TEMPERATURE_SLIDEBAR,
        HVAC_AC_MODE_STATUS_SLIDEBAR,
        HVAC_ECON_MODE_STATUS_SLIDEBAR,
        HVAC_AUTO_MODE_STATUS_SLIDEBAR,
        HVAC_DISTRIBUTION_MODE_STATUS_SLIDEBAR,
        HVAC_AIR_CIRCULATION_MODE_STATUS_SLIDEBAR,
        HVAC_CLIMATE_MODE_STATUS_SLIDEBAR,
        HVAC_MAX_DEFROST_MODE_STATUS_SLIDEBAR,
    };
    Q_ENUMS(EHvacSlideBars)

    /**
     * @enum    EShortcutDrawerButtonID
     * @brief   The EShortcutDrawerButtonID enum defines the button IDs which
     *          are present on shortcut drawer.
     */
    enum EShortcutDrawerButtonID
    {
        SHORTCUT_DRAWER_BUTTON_HOME_ID,
        SHORTCUT_DRAWER_BUTTON_CLIMATE_ID,
        SHORTCUT_DRAWER_BUTTON_PARKASSIST_ID,
        SHORTCUT_DRAWER_BUTTON_SOURCE_ID,
        SHORTCUT_DRAWER_BUTTON_MEDIAOFF_ID,
    };
    Q_ENUMS(EShortcutDrawerButtonID)

    /**
     * @enum    EQadDrawerButtonID
     * @brief   The EQadDrawerButtonID enum defines the button IDs which
     *          are present on QAD maximized drawer.
     */
    enum EQadDrawerButtonID
    {
        QAD_DRAWER_SETTINGS_BUTTON_ID,
        QAD_DRAWER_ACTIVE_ENT_SOURCE_INFO_BUTTON_ID,
        QAD_DRAWER_CONNECTED_PHONE_PROFILE_BUTTON_ID,
        QAD_DRAWER_NOTIFICATION_BUTTON_ID,
        QAD_DRAWER_PROJECTION_INFO_BUTTON_ID,
        QAD_DRAWER_OPEN_BUTTON_ID,
        QAD_DRAWER_CLOSE_BUTTON_ID,
    };
    Q_ENUMS(EQadDrawerButtonID)

    /**
     * @enum    ESourceDrawerButtonID
     * @brief   The ESourceDrawerButtonID enum defines the button IDs which
     *          are present on Source maximized drawer.
     */
    enum ESourceDrawerButtonID
    {
        SOURCE_DRAWER_CLOSE_BUTTON_ID
    };
    Q_ENUMS(ESourceDrawerButtonID)

    /**
     * @enum    ECommonEventsForDrawers
     * @brief   The ECommonEventForDrawers enum defines the common events for
     *          all four drawers.
     */
    enum ECommonEventsForDrawers
    {
        DRAWER_COMMON_EVENT_UNKNOWN,
        DRAWER_COMMON_EVENT_CLOSE_TIMER_RESET,
    };
    Q_ENUMS(ECommonEventsForDrawers)

    enum ENotificationTypes
    {
        EN_NOTIFICATION_TYPE_NONE,
        EN_NOTIFICATION_TYPE_HVAC_FAN,
        EN_NOTIFICATION_TYPE_HVAC_TEMPERATURE,
        EN_NOTIFICATION_TYPE_HVAC_AC_MODE_STATUS,
        EN_NOTIFICATION_TYPE_HVAC_ECON_MODE_STATUS,
        EN_NOTIFICATION_TYPE_HVAC_AUTO_MODE_STATUS,
        EN_NOTIFICATION_TYPE_HVAC_DISTRIBUTION_MODE_STATUS,
        EN_NOTIFICATION_TYPE_HVAC_AIR_CIRCULATION_MODE_STATUS,
        EN_NOTIFICATION_TYPE_HVAC_CLIMATE_MODE_STATUS,
        EN_NOTIFICATION_TYPE_HVAC_MAX_DEFROST_MODE_STATUS,
        EN_NOTIFICATION_TYPE_VOLUME,
    };
    Q_ENUMS(ENotificationTypes)

    /**
     * @brief registerDrawersEnumsToQML function to register enums to QML.
     */
    static void registerDrawersEnumsToQML()
    {
        qmlRegisterType<CDrawersEnums>("com.harman.qml.drawersenums",1,0,"DrawersEnums");
    }
};

Q_DECLARE_METATYPE(CDrawersEnums::EDrawerState)
Q_DECLARE_METATYPE(CDrawersEnums::EHvacSlideBars)
Q_DECLARE_METATYPE(CDrawersEnums::EDrawer)
Q_DECLARE_METATYPE(CDrawersEnums::EShortcutDrawerButtonID)
Q_DECLARE_METATYPE(CDrawersEnums::EQadDrawerButtonID)
Q_DECLARE_METATYPE(CDrawersEnums::ESourceDrawerButtonID)
Q_DECLARE_METATYPE(CDrawersEnums::ECommonEventsForDrawers)
Q_DECLARE_METATYPE(CDrawersEnums::EDrawerOverlays)
Q_DECLARE_METATYPE(CDrawersEnums::ENotificationTypes)

#endif // CDRAWERSENUMS_H

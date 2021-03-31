/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CVariantControlEnum.h
 * @ingroup         HMIComponent
 * @author          Rajat Gupta
 * CDiagnosticEnum, file that contain enums that will be used in VariantControl.
 */
#ifndef CVARIANTCONTROLENUM_H
#define CVARIANTCONTROLENUM_H

#include <QObject>
#include <QtQml>

class CVariantControlEnum: public QObject
{
    Q_OBJECT
public:

    /**
     * @enum EVIP_DID
     * @brief Enum for vehcile infotainmentPlatform
     */
    enum EVIP_DID
    {
        VIP_DID_HU_LCIS = 0,
        VIP_DID_HU_TIAGO_7INCH = 1,
        VIP_DID_HU_HEXA_7_VAVE = 2,
        VIP_DID_HU_NEXON_EV_LEVEL_A_VAVE = 3,
        VIP_DID_HU_NEXON_LEVEL_B_VAVE = 4,
        VIP_DID_HU_MID_X451 = 5,
        VIP_DID_HU_HIGH_X451 = 6,
        VIP_DID_HU_MID_X445 = 7,
        VIP_DID_HU_HIGH_X445 = 8,
        VIP_DID_HU_NEXON_EV_MID = 9,
        VIP_DID_HU_NEXON_EV_HIGH = 10,
        VIP_DID_HU_TIGOR_7 = 11,
        VIP_DID_HU_NEXON_MCE = 12
    };
    Q_ENUM(EVIP_DID)


    /* Below are the apps and their bit positions to get information whether the feature is enabled or disabled
     * Apps Enable Disable - ConnectNext                        0
     * Apps Enable Disable - DrivePro                           1
     * Apps Enable Disable - HMI Doodle                         2
     * Apps Enable Disable - Navigation app configuration       3
     * Apps Enable Disable - Vehicle info apps configuration	4
     * Apps Enable Disable - Smart remote app configuration     5
     * Apps Enable Disable - W3W configuration                  6
    */
    enum EAppsPosition
    {
        APPS_POSITION_CONNECTNEXT = 0,
        APPS_POSITION_DRIVENEXT = 1,
        APPS_POSITION_HMI_DOODLE = 2,
        APPS_POSITION_NAVIGATION_APP = 3,
        APPS_POSITION_VEHICLE_INFO_APP = 4,
        APPS_POSITION_SMART_REMOTE_APP = 5,
        APPS_POSITION_W3W = 6,
    };

    /**
     * @enum EAntennaType
     * @brief Enum to check the type of AntennaType
     */
    enum EAntennaType
    {
        ANTENNA_TYPE_INVALID = -1,
        ANTENNA_TYPE_ACTIVE,
        ANTENNA_TYPE_PASSIVE,
    };
    Q_ENUM(EAntennaType)

    /**
     * @brief The EPDCSensorCount enum to identify the number of sensors.
     */
    enum EPDCSensorCount
    {
        EN_TWO_SENSORS = 0,
        EN_THREE_SENSORS,
        EN_FOUR_SENSORS,
        EN_TOTAL_SENSORS
    };
    Q_ENUM(EPDCSensorCount)
    //________________________________________________________________________________________________

    static void registerVariantControlEnumsToQML()
    {
        qmlRegisterType<CVariantControlEnum>("com.harman.qml.variantcontrolenums",1,0,"VariantControlEnum");
    }
};

Q_DECLARE_METATYPE(CVariantControlEnum::EVIP_DID)
Q_DECLARE_METATYPE(CVariantControlEnum::EAppsPosition)
Q_DECLARE_METATYPE(CVariantControlEnum::EAntennaType)
Q_DECLARE_METATYPE(CVariantControlEnum::EPDCSensorCount)

#endif // CVARIANTCONTROLENUM_H

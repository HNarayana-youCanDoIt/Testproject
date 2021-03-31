/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2018
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CEnggEventHandler.h
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande, Rajat Gupta
 * EnggDef.h, file that contain other data structures that will be used in EnggMenu
 */

#ifndef ENGGDEF_H
#define ENGGDEF_H

#include <QObject>
#include <QString>

class CEnggMenuEnum;
class CEnggApplication;

/** Total No of screens present in whole EnggMenu Module **/
const int EnggScreenCount = 32;

/** String Array that contains the name of each screen **/
const QString EnggScreenNames[EnggScreenCount] =
{
    "ENGG_MENU_SCREEN_MAIN",
    "ENGG_MENU_SCREEN_TEST_MODE",
    "ENGG_MENU_SCREEN_DRIVE_NEXT",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_LIB_UPDATE",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_CONFIG_UPDATE",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_DEBUG",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_LOG",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_LOGGING",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_EFFICIENCY",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_BRAKING",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_ACCELERATION",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GEAR_SHIFT",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GENERIC",
    "ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_SAFETY",
    "ENGG_MENU_SCREEN_BUTTON_PANEL",
    "ENGG_MENU_SCREEN_DEBUG_LOG",
    "ENGG_MENU_SCREEN_ILLUMINATION",
    "ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION",
    "ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION",
    "ENGG_MENU_SCREEN_SYSTEM_CONFIG",
    "ENGG_MENU_SCREEN_SYSTEM_CONFIG_VIN",
    "ENGG_MENU_SCREEN_SYSTEM_CONFIG_VC_NUMBER",
    "ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R",
    "ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_BUTTON_PANEL",
    "ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_CONTAINER_PART",
    "ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_DISPLAY_PART",
    "ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_PARAM_PART",
    "ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SILVERBOX_PART",
    "ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SOFT_PART",
    "ENGG_MENU_SCREEN_W3W_LAST_NAVIGATED",
    "ENGG_MENU_SCREEN_PICTURE_VIEWER"
};
/** Enums that contain the information regarding the type of screen **/
const CEnggMenuEnum::EEnggScreenType EnggScreenTypes[EnggScreenCount] =
{
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_MAIN",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_TEST_MODE",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_DRIVE_NEXT",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_DRIVENEXT_LIB_UPDATE,//"ENGG_MENU_SCREEN_DRIVE_NEXT_LIB_UPDATE",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_DRIVENEXT_CONFIG_UPDATE,//"ENGG_MENU_SCREEN_DRIVE_NEXT_CONFIG_UPDATE",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_DRIVE_NEXT_DEBUG",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_DRIVE_NEXT_LOG",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_DRIVE_NEXT_LOGGING",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST_5_ROWS,//"ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_EFFICIENCY",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST_5_ROWS,//"ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_BRAKING",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST_5_ROWS,//"ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_ACCELERATION",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST_5_ROWS,//"ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GEAR_SHIFT",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST_5_ROWS,//"ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_GENERIC",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST_5_ROWS,//"ENGG_MENU_SCREEN_DRIVE_NEXT_DETAILS_SAFETY",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_BUTTON_PANEL,//"ENGG_MENU_SCREEN_BUTTON_PANEL",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_DEBUG_LOG",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_ILLUMINATION",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_ILLUMINATION_ADJUST,//"ENGG_MENU_SCREEN_BUTTON_PANEL_ILLUMINATION",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_ILLUMINATION_ADJUST,//"ENGG_MENU_SCREEN_DISPLAY_ILLUMINATION",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_SYSTEM_CONFIG",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PART_NO,//"ENGG_MENU_SCREEN_SYSTEM_CONFIG_VIN",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PART_NO,//"ENGG_MENU_SCREEN_SYSTEM_CONFIG_VC_NUMBER",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_LIST,//"ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PART_NO,//"ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_BUTTON_PANEL",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PART_NO,//"ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_CONTAINER_PART",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PART_NO,//"ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_DISPLAY_PART",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PART_NO,//"ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_PARAM_PART",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PART_NO,//"ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SILVERBOX_PART",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PART_NO,//"ENGG_MENU_SCREEN_SYSTEM_CONFIG_16R_SOFT_PART",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_W3W_LAST_NAVIGATED,//"ENGG_MENU_SCREEN_W3W_LAST_NAVIGATED",
    CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_PICTURE_VIEWER//"ENGG_MENU_SCREEN_PICTURE_VIEWER"
};

/** Structure containing info regarding each screen i.e its ScreenIndex,Name,Type **/
struct EnggScreenInfo
{
    int ScreenIndex = -1;
    QString ScreenName = "";
    CEnggMenuEnum::EEnggScreenType ScreenType = CEnggMenuEnum::ENGG_MENU_SCREEN_TYPE_NULL;
    void(CEnggApplication::*raiseSMEventForScreen)(const QVariant & data) = NULL;
};

#endif // ENGGDEF_H

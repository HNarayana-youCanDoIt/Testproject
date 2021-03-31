/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2017
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CThemeManagerEnums.h
* @ingroup      HMI Framework
* @author       Mohit Rajani
* CThemeManagerEnums, provides various enumerations related to thememanager. E.g Font types
*/

#ifndef CTHEMEMANAGERENUMS_H
#define CTHEMEMANAGERENUMS_H

#include <QObject>
#include <QtQml>

class CThemeManagerEnums: public QObject
{
    Q_OBJECT
public:
    enum EFontType
    {
        FONTTYPE_T45_C1 = 0,
        FONTTYPE_T45_C1_WHITE,
        FONTTYPE_T45_C1_DISABLED,
        FONTTYPE_T35_C3,
        FONTTYPE_T35_C3_DISABLED,
        FONTTYPE_T35_BK_C2,
        FONTTYPE_T35_BK_C2_DISABLED,
        FONTTYPE_T24_LIGHT_C2,
        FONTTYPE_T24_LIGHT_C2_DISABLED,
        FONTTYPE_T24_LIGHT_C3,
        FONTTYPE_T24_LIGHT_C3_DISABLED,
        FONTTYPE_RVC,
        FONTTYPE_T22_BK_C2_AMBER,
        FONTTYPE_PDC,
        FONTTYPE_T22_LIGHT_C2,
        FONTTYPE_T70_C2_WHITE
    };
    Q_ENUMS(EFontType)

    /**
     * @brief The EThemeTypes enum: This enum contains all the possible theme for the infotainment system
     */
    enum EThemeTypes
    {
        THEME_TYPE_1 = 0,
        THEME_TYPE_2,
        //THEME_TYPE_3, As per TML, green colour theme should be removed
        THEME_TYPE_4,
        THEME_TYPE_5,
        THEME_TYPE_MAX
    };
    Q_ENUM(EThemeTypes)

    static void registerThemeManagerEnumsToQML()
    {
        qmlRegisterType<CThemeManagerEnums>("com.harman.qml.thememanager",1,0,"ThemeMgr");
    }
};

Q_DECLARE_METATYPE(CThemeManagerEnums::EFontType)
Q_DECLARE_METATYPE(CThemeManagerEnums::EThemeTypes)

#endif // CTHEMEMANAGERENUMS_H

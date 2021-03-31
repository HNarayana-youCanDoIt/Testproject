/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupData.h
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupData.h, setup module data class header file, responsible for initializing different static models
 */
#ifndef CSETUPDATA_H
#define CSETUPDATA_H
#include <QString>
#include "logging.h"
#include "CSetupEnums.h"

/**
 * @brief The CSetupData class: Responsible for initializing different static models
 */

//ToDO: This class should be removed we need to have roles locally maintained in structure where ever required
//      In this file that this class should be revisited and unwanted code and logic should be removed

class CSetupData
{
public:
    CSetupData();
    CSetupData(QString listItemName, CSetupEnums::ESetupListItemTypes listItemType = CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, bool listItemChecked = false, int listItemValue = -1,  CSetupEnums::ESetupScreens listItemIndex = CSetupEnums::SETUP_SCREEN_INVALID);
    CSetupData(QString listItemName, CSetupEnums::ESetupListItemTypes listItemType, bool listItemChecked = false, bool islistItemEnabled = false, int iItemId = -1);
    CSetupData(QString listItemName, QString listItemDefaultImage, QString listItemSelectedImage, CSetupEnums::ESetupListItemTypes listItemType = CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, bool islistItemEnabled = false,
               bool isCollapsed = true, bool listItemChecked = false, int listItemValue = -1, int listItemMinValue = -1, int listItemMaxValue = 30, CSetupEnums::ESetupScreens listItemIndex = CSetupEnums::SETUP_SCREEN_INVALID, int iItemId = -1);
    CSetupData(QString listItemName, QString listItemDefaultImage, QString listItemSelectedImage, QString distributionModeImage, QString fanImage, int fanSpeedValue,
               float temperatureValue, bool islistItemEnabled = false, bool climateIconsVisibilityStatus = false, bool themeColorVisibility = false, bool themeSoundVisibility = false,
               bool themeLoadingStatus = false, CSetupEnums::ESetupListItemTypes listItemType = CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, int iItemId = -1, const QString& strName = "", const QString& strLeftIcon = "", const QString& strMidIcon = "", const QString& strRightIcon = "");
    CSetupData(const QString& strName, const QString& strLeftIcon, const QString& strMidIcon, const QString& strRightIcon);

    ~CSetupData();

private:

    /**
     * @brief listItemName : To get the list item name
     * @return : QString
     * @param : void
     */
    QString listItemName();

    /**
     * @brief listItemType : To get the list item type
     * @return : CSetupEnums::ESetupListItemTypes
     * @param : void
     */
    CSetupEnums::ESetupListItemTypes listItemType();

    /**
     * @brief listItemIndex : To get the list item index
     * @return : int
     * @param : void
     */
    CSetupEnums::ESetupScreens listItemIndex();

    /**
     * @brief listChecked : To get the list item is checked or not
     * @return : bool
     * @param : void
     */
    bool listChecked();

    /**
     * @brief listItemValue : To get the list item value
     * @return : int
     * @param : void
     */
    int listItemValue();

    /**
     * @brief listItemDefaultImage : To get the list item default image path
     * @return : QString: Path of the default image
     * @param : void
     */
    QString listItemDefaultImage();

    /**
     * @brief listItemSelectedImage : To get the list item selected image path
     * @return : QString: Path of the selected image
     * @param : void
     */
    QString listItemSelectedImage();

    /**
     * @brief isCollapsed : To get the state of the list item, collapsed or expanded
     * @return : bool: collapsed or expanded
     * @param : void
     */
    bool isCollapsed();

    /**
     * @brief isListItemEnabled : To get the state of the list item, enabled or disabled
     * @return : bool: true or false
     * @param : void
     */
    bool isListItemEnabled();

    /**
     * @brief listItemMinValue : To get the list item min value
     * @return : int
     * @param : void
     */
    int listItemMinValue();

    /**
     * @brief listItemMinValue : To get the list item max value
     * @return : int
     * @param : void
     */
    int listItemMaxValue();

    /**
     * @brief distributionModeImage : To get the distribution mode image
     * @return : QString : Path of the air flow distribution mode image
     * @param : void
     */
    QString distributionModeImage();

    /**
     * @brief fanSpeedImage : To get the fan speed image
     * @return : QString : Path of the fan speed image
     * @param : void
     */
    QString fanSpeedImage();

    /**
     * @brief fanSpeedValue : To get the fan speed value
     * @return : int : value of fan speed
     * @param : void
     */
    int fanSpeedValue();

    /**
     * @brief temperatureValue : To get the temperature value
     * @return : float : value of temperature
     * @param : void
     */
    float temperatureValue();

    /**
      * @brief strName: To get string name
      * @return : QString : name of presets
      * @param : void
      */
     QString strName();

     /**
      * @brief strLeftIcon : To get the theme presets left icon
      * @return : QString : path of theme preset left icon
      * @param : void
      */
     QString strLeftIcon();

     /**
      * @brief strMidIcon : To get the theme presets mid icon
      * @return : QString : path of theme preset mid icon
      * @param : void
      */
     QString strMidIcon();

     /**
      * @brief strRightIcon : To get the theme presets right icon
      * @return : QString : path of theme preset right icon
      * @param : void
      */
     QString strRightIcon();

     /**
      * @brief bClimateIconsVisibilityStatus : To get the climate icon visibility status
      * @return : bool : true or false
      * @param : void
      */
     bool bClimateIconsVisibilityStatus();

     /**
      * @brief bThemeColorVisibility : To get the theme color visibility status
      * @return : bool : true or false
      * @param : void
      */
     bool bThemeColorVisibility();

     /**
      * @brief bThemeSoundVisisbility : To get the theme sound icon visibility status
      * @return : bool : true or false
      * @param : void
      */
     bool bThemeSoundVisisbility();

     /**
      * @brief bThemeLoadingStatus : To get the theme loading status
      * @return : bool : true or false
      * @param : void
      */
     bool bThemeLoadingStatus();

     /**
      * @brief iItemId : To get the list item id
      * @return : int value of list item id
      * @param : void
      */
     int iItemId();

public:

    /* list item index gets stored in this var */
    CSetupEnums::ESetupScreens m_eListItemIndex;

    /* list item name gets stored in this var */
    QString m_sListItemName;

    /* list item type delegate stored in this var */
    CSetupEnums::ESetupListItemTypes m_sListItemType;

    /* list item is checked status stored in this var */
    bool m_bListItemChecked;

    /* list item value gets stored in this var */
    int m_iListItemValue;

    /* list item min value gets stored in this var */
    int m_iListItemMinValue;

    /* list item max value gets stored in this var */
    int m_iListItemMaxValue;

    /* list item default image path gets stored in this var */
    QString m_sListItemDefaultImage;

    /* list item selected image path gets stored in this var */
    QString m_strListItemSelectedImage;

    /* list item collapsed status stored in this var */
    bool m_bIsListItemCollapsed;

    /* list item enabled / disabled status stored in this var */
    bool m_bIsListItemEnabled;

    /* theme presets name gets stored in this var */
    QString m_strName;

    /* theme presets mid image path gets stored in this var */
    QString m_strMidIcon;

    /* theme presets left image path gets stored in this var */
    QString m_strLeftIcon;

    /* theme presets right image path gets stored in this var */
    QString m_strRightIcon;

    /* list item distributed image path gets stored in this var */
    QString m_strDistributionModeImage;

    /* list item fan speed image path gets stored in this var */
    QString m_strFanSpeedImage;

    /* list item fan speed value gets stored in this var */
    int m_iFanSpeedValue;

    /* list item temperature gets stored in this var */
    float m_fTemperatureValue;

    /* list item climate icon visibility gets stored in this var */
    bool m_bClimateIconsVisiblityStatus;

    /* list item theme color visibility gets stored in this var */
    bool m_bThemeColorVisibilty;

    /* list item theme sound icon visibility gets stored in this var */
    bool m_bThemeSoundVisibilty;

    /* list item theme loading visibility gets stored in this var */
    bool m_bThemeLoadingStatus;
    
    /* list item options id gets stored in this var */
    int m_iItemId;
};

#endif // CSETUPDATA_H

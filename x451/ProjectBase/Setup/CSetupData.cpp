/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupData.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupData.cpp, setup module data class cpp file, responsible for initializing different static models
 */

#include "CSetupData.h"

CSetupData::CSetupData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
}

CSetupData::CSetupData(QString listItemName, CSetupEnums::ESetupListItemTypes listItemType, bool listItemChecked, int listItemValue, CSetupEnums::ESetupScreens listItemIndex):
    m_eListItemIndex(listItemIndex),
    m_sListItemName(listItemName),
    m_sListItemType(listItemType),
    m_bListItemChecked(listItemChecked),
    m_iListItemValue(listItemValue)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s ", __FUNCTION__);
}

CSetupData::CSetupData(QString listItemName, CSetupEnums::ESetupListItemTypes listItemType, bool listItemChecked,  bool islistItemEnabled, int iItemId):
    m_sListItemName(listItemName),
    m_sListItemType(listItemType),
    m_bListItemChecked(listItemChecked),
    m_bIsListItemEnabled(islistItemEnabled),
    m_iItemId(iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s ", __FUNCTION__);
}

CSetupData::CSetupData(QString listItemName, QString listItemDefaultImage, QString listItemSelectedImage, CSetupEnums::ESetupListItemTypes listItemType, bool islistItemEnabled, bool isCollapsed, bool listItemChecked, int listItemValue, int listItemMinValue, int listItemMaxValue, CSetupEnums::ESetupScreens listItemIndex, int iItemId):
    m_eListItemIndex(listItemIndex),
    m_sListItemName(listItemName),
    m_sListItemType(listItemType),
    m_bListItemChecked(listItemChecked),
    m_iListItemValue(listItemValue),
    m_iListItemMinValue(listItemMinValue),
    m_iListItemMaxValue(listItemMaxValue),
    m_sListItemDefaultImage(listItemDefaultImage),
    m_strListItemSelectedImage(listItemSelectedImage),
    m_bIsListItemCollapsed(isCollapsed),
    m_bIsListItemEnabled(islistItemEnabled),
    m_iItemId(iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s ",__FUNCTION__);
}

CSetupData::CSetupData(QString listItemName, QString listItemDefaultImage, QString listItemSelectedImage,
                       QString distributionModeImage, QString fanImage, int fanSpeedValue, float temperatureValue, bool islistItemEnabled,
                       bool climateIconsVisibilityStatus, bool themeColorVisibility,
                       bool themeSoundVisibility, bool themeLoadingStatus, CSetupEnums::ESetupListItemTypes listItemType, int iItemId, const QString &strName, const QString &strLeftIcon,
                       const QString& strMidIcon, const QString &strRightIcon):
    m_sListItemName(listItemName),
    m_sListItemType(listItemType),
    m_sListItemDefaultImage(listItemDefaultImage),
    m_strListItemSelectedImage(listItemSelectedImage),
    m_bIsListItemEnabled(islistItemEnabled),
    m_strName(strName),
    m_strMidIcon(strMidIcon),
    m_strLeftIcon(strLeftIcon),
    m_strRightIcon(strRightIcon),
    m_strDistributionModeImage(distributionModeImage),
    m_strFanSpeedImage(fanImage),
    m_iFanSpeedValue(fanSpeedValue),
    m_fTemperatureValue(temperatureValue),
    m_bClimateIconsVisiblityStatus(climateIconsVisibilityStatus),
    m_bThemeColorVisibilty(themeColorVisibility),
    m_bThemeSoundVisibilty(themeSoundVisibility),
    m_bThemeLoadingStatus(themeLoadingStatus),
    m_iItemId(iItemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s ", __FUNCTION__);
}


CSetupData::CSetupData(const QString &strName, const QString &strLeftIcon, const QString &strMidIcon, const QString &strRightIcon):
    m_strName(strName),
    m_strMidIcon(strMidIcon),
    m_strLeftIcon(strLeftIcon),
    m_strRightIcon(strRightIcon)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
}

CSetupData::~CSetupData()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
}

CSetupEnums::ESetupScreens CSetupData::listItemIndex()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_eListItemIndex;
}

bool CSetupData::listChecked()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_bListItemChecked;
}

int CSetupData::listItemValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_iListItemValue;
}

int CSetupData::listItemMinValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_iListItemMinValue;
}

int CSetupData::listItemMaxValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_iListItemMaxValue;
}

QString CSetupData::distributionModeImage()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_strDistributionModeImage;
}

QString CSetupData::fanSpeedImage()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_strFanSpeedImage;
}

int CSetupData::fanSpeedValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_iFanSpeedValue;
}

float CSetupData::temperatureValue()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_fTemperatureValue;
}

QString CSetupData::strName()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_strName;
}

QString CSetupData::strLeftIcon()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_strLeftIcon;
}

QString CSetupData::strMidIcon()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_strMidIcon;
}

QString CSetupData::strRightIcon()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_strRightIcon;
}

bool CSetupData::bClimateIconsVisibilityStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_bClimateIconsVisiblityStatus;
}

bool CSetupData::bThemeColorVisibility()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_bThemeColorVisibilty;
}

bool CSetupData::bThemeSoundVisisbility()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_bThemeSoundVisibilty;
}

bool CSetupData::bThemeLoadingStatus()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_bThemeLoadingStatus;
}

int CSetupData::iItemId()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_iItemId;
}

QString CSetupData::listItemName()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_sListItemName;
}

CSetupEnums::ESetupListItemTypes CSetupData::listItemType()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);
    return m_sListItemType;
}


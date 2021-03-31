/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaData.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* @brief
*/
#ifndef CMEDIADATA_H
#define CMEDIADATA_H

#include <QObject>
#include <QString>
#include "CMediaEnum.h"

/**
 * @struct browseCategoryData
 * @brief  Sructure to hold the Media Browse Category Item Information
 *         that needs to be updated in the Media Browse Category screen
 */
struct SBrowseCategoryData{
    SBrowseCategoryData()
    {
        m_strCategoryImage    = "";
        m_strCategoryItemText = "";
        m_iCategoryItemId     = -1;
        m_eCategoryItemType   = CMediaEnum::BROWSEITEM_UNKNOWN;
        m_bIsActive           = false;
        m_iFSContentType      = 0;
    }
    QString                      m_strCategoryImage;
    QString                      m_strCategoryItemText;
    int                          m_iCategoryItemId;
    CMediaEnum::EMediaBrowseItem m_eCategoryItemType;
    bool                         m_bIsActive;
    int                          m_iFSContentType;
};

/**
 * @struct SBrowseItemData
 * @brief  Sructure to hold the Media Browse List Information
 *         that needs to be updated in the Media Browse screen
 */
struct SBrowseItemData{
    SBrowseItemData()
    {
        m_strBrowseItemImage = "";
        m_strBrowseItemText = "";
        m_eMetadataType = CMediaEnum::BROWSEITEM_UNKNOWN;
    }
    QString m_strBrowseItemImage;
    QString m_strBrowseItemText;
    CMediaEnum::EMediaBrowseItem m_eMetadataType;
};

#endif // CMEDIADATA_H

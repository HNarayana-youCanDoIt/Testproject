/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaBrowseCategoryListModel.cpp
* @ingroup      HMIComponent
* @author       Rahul Madan
* @brief        This file contains CMediaBrowseCategoryListModel class that shall implement the
*               Media Browse Category list data model that shall be used to update all the Category screens in Media Browse
*/
#include "CMediaBrowseCategoryListModel.h"
#include "logging.h"

CMediaBrowseCategoryListModel::CMediaBrowseCategoryListModel(QObject *pParent):
    QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    m_listBrowseCategory.clear();
}

CMediaBrowseCategoryListModel::~CMediaBrowseCategoryListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    m_listBrowseCategory.clear();
}

QHash<int, QByteArray> CMediaBrowseCategoryListModel::roleNames() const
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    QHash<int ,QByteArray> roles;
    roles[ITEM_NAME_ROLE] = "itemNameRole";
    roles[ITEM_IMAGE_ROLE] = "itemImageRole";
    roles[ITEM_ID_ROLE]    = "itemIdRole";
    roles[ITEM_TYPE_ROLE]  = "itemTypeRole";
    roles[ITEM_ACTIVE_ROLE] = "itemActiveRole";
    roles[ITEM_FSCONTENTTYPE_ROLE] = "itemFSContentTypeRole";
    return roles;
}

void CMediaBrowseCategoryListModel::removeRows()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    beginRemoveRows(QModelIndex(), 0, m_listBrowseCategory.count());
    m_listBrowseCategory.clear();
    endRemoveRows();
}

QVariant CMediaBrowseCategoryListModel::data(const QModelIndex &index, int role) const
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    QVariant objRowData;
    int iRowIndex = index.row();

    if(iRowIndex >= 0 && iRowIndex < m_listBrowseCategory.count())
    {
        switch(role)
        {
        case ITEM_IMAGE_ROLE:
            objRowData = m_listBrowseCategory[iRowIndex].m_strCategoryImage;
            break;
        case ITEM_NAME_ROLE:
            objRowData = m_listBrowseCategory[iRowIndex].m_strCategoryItemText;
            break;
        case ITEM_ID_ROLE:
            objRowData = m_listBrowseCategory[iRowIndex].m_iCategoryItemId;
            break;
        case ITEM_TYPE_ROLE:
            objRowData = m_listBrowseCategory[iRowIndex].m_eCategoryItemType;
            break;
        case ITEM_ACTIVE_ROLE:
            objRowData = m_listBrowseCategory[iRowIndex].m_bIsActive;
            break;
        case ITEM_FSCONTENTTYPE_ROLE:
            objRowData = m_listBrowseCategory[iRowIndex].m_iFSContentType;
            break;
        default:
            LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s | Invalid Role received: %d",__FUNCTION__,role);
            break;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s | Model Index out of scope: %d",__FUNCTION__,iRowIndex);
    }
    return objRowData;
}

int CMediaBrowseCategoryListModel::rowCount(const QModelIndex &parent) const
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : count: %d", __FUNCTION__,m_listBrowseCategory.count());
    Q_UNUSED(parent);
    return m_listBrowseCategory.count();
}

void CMediaBrowseCategoryListModel::insertRows(const SBrowseCategoryData &objBrowseCategoryData)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_listBrowseCategory.append(objBrowseCategoryData);

    endInsertRows();
}

void CMediaBrowseCategoryListModel::updateBrowseList(int iIndex, const SBrowseCategoryData &objBrowseCategoryData)
{
    if(iIndex>=0 && iIndex<m_listBrowseCategory.size())
    {
        m_listBrowseCategory[iIndex].m_eCategoryItemType = objBrowseCategoryData.m_eCategoryItemType;
        m_listBrowseCategory[iIndex].m_iCategoryItemId = objBrowseCategoryData.m_iCategoryItemId;
        m_listBrowseCategory[iIndex].m_strCategoryItemText = objBrowseCategoryData.m_strCategoryItemText;
        m_listBrowseCategory[iIndex].m_strCategoryImage = objBrowseCategoryData.m_strCategoryImage;
        m_listBrowseCategory[iIndex].m_iFSContentType = objBrowseCategoryData.m_iFSContentType;
        m_listBrowseCategory[iIndex].m_bIsActive = objBrowseCategoryData.m_bIsActive;
    }

    /* Refreshing the qml's data for the index which is changed */
    const QModelIndex &objLeftIndex = createIndex(iIndex, 0);
    const QModelIndex &objRightIndex = createIndex(iIndex, 0);
    emit dataChanged(objLeftIndex, objRightIndex);
}

SBrowseCategoryData CMediaBrowseCategoryListModel::getBrowseDataFromIndex(int iIndex)
{
    SBrowseCategoryData objBrowseData;
    if ((iIndex >= 0) && (iIndex < m_listBrowseCategory.size()))
    {
        objBrowseData.m_eCategoryItemType = m_listBrowseCategory[iIndex].m_eCategoryItemType;
        objBrowseData.m_iCategoryItemId = m_listBrowseCategory[iIndex].m_iCategoryItemId;
        objBrowseData.m_iFSContentType = m_listBrowseCategory[iIndex].m_iFSContentType;
        objBrowseData.m_strCategoryImage = m_listBrowseCategory[iIndex].m_strCategoryImage;
        objBrowseData.m_strCategoryItemText = m_listBrowseCategory[iIndex].m_strCategoryItemText;
        objBrowseData.m_bIsActive = m_listBrowseCategory[iIndex].m_bIsActive;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iIndex);
    }

    return objBrowseData;

}



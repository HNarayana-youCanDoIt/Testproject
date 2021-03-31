/*****************************************************************
* Project        Harman Car Multimedia System
* (c) copyright  2018
* Company        Harman/Becker Automotive Systems GmbH
*                All rights reserved
* Secrecy Level  STRICTLY CONFIDENTIAL
****************************************************************/
/**
* @file         CMediaBrowseListModel.h
* @ingroup      HMIComponent
* @author       Rahul Madan
* @brief        This file contains CMediaBrowseListModel class that shall implement the
*               Media Browse list data model that shall be used to update the media browse screen for all the sources
*/

#include "CMediaBrowseListModel.h"
#include "logging.h"

CMediaBrowseListModel::CMediaBrowseListModel(QObject *pParent):
    QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    m_listBrowse.clear();
}

CMediaBrowseListModel::~CMediaBrowseListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    m_listBrowse.clear();
}

QHash<int, QByteArray> CMediaBrowseListModel::roleNames() const
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    QHash<int ,QByteArray> roles;
    roles[ITEM_NAME_ROLE] = "itemNameRole";
    roles[ITEM_IMAGE_ROLE] = "itemImageRole";
    roles[ITEM_METADATA_TYPE] = "itemMetadataType";
    return roles;
}

QVariant CMediaBrowseListModel::data(const QModelIndex &index, int role) const
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    QVariant objRowData;
    int iRowIndex = index.row();

    if(iRowIndex >= 0 && iRowIndex < m_listBrowse.count())
    {
        switch(role)
        {
        case ITEM_IMAGE_ROLE:
            objRowData = m_listBrowse[iRowIndex].m_strBrowseItemImage;
            break;
        case ITEM_NAME_ROLE:
            objRowData = m_listBrowse[iRowIndex].m_strBrowseItemText;
            break;
        case ITEM_METADATA_TYPE:
            objRowData = m_listBrowse[iRowIndex].m_eMetadataType;
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

int CMediaBrowseListModel::rowCount(const QModelIndex &parent) const
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MEDIA,"%s : count: %d", __FUNCTION__,m_listBrowse.count());
    Q_UNUSED(parent);
    return m_listBrowse.count();
}

void CMediaBrowseListModel::removeRows()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    beginRemoveRows(QModelIndex(), 0, m_listBrowse.count());
    m_listBrowse.clear();
    endRemoveRows();
}

void CMediaBrowseListModel::insertRows(const QString &strItemText, const QString &strItemImage, const CMediaEnum::EMediaBrowseItem eMetadataType)
{
    //LOG_INFO(Log::e_LOG_CONTEXT_MEDIA, __FUNCTION__);
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    SBrowseItemData objBrowseItemData;
    objBrowseItemData.m_strBrowseItemText = strItemText;
    objBrowseItemData.m_strBrowseItemImage = strItemImage;
    objBrowseItemData.m_eMetadataType = eMetadataType;
    m_listBrowse.append(objBrowseItemData);

    endInsertRows();
}

QString CMediaBrowseListModel::getName(int iIndex)
{
    QString strName= "";

    if(iIndex >= 0 && iIndex < m_listBrowse.count())
    {
        strName = m_listBrowse[iIndex].m_strBrowseItemImage;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MEDIA,"%s | Model Index out of scope: %d",__FUNCTION__,iIndex);
    }
    return strName;
}

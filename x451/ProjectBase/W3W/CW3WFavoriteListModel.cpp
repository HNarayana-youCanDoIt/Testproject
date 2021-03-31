/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CW3WFavoriteListModel.cpp
 * @ingroup       HMIComponent
 * @author        Nishant Khandagale
 * @brief         Contain implementation of all the methods declared in
 * CW3WFavoriteListModel class
 */

#include "CW3WFavoriteListModel.h"
#include "logging.h"
#include "CW3WEnum.h"
#include "CW3WAdaptor.h"
#include "CW3WApplication.h"

CW3WFavoriteListModel::CW3WFavoriteListModel(QObject *pParent) :
    QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_listW3WFavorite.clear();
}

CW3WFavoriteListModel::~CW3WFavoriteListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_listW3WFavorite.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CW3WFavoriteListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[W3W_FAVORITE_ITEM_ADDRESS_ROLE]      = "itemAddressRole";
    roles[W3W_FAVORITE_ITEM_LABEL_ROLE]        = "itemLabelRole";
    roles[W3W_FAVORITE_ITEM_TYPE_ROLE]         = "itemTypeRole";
    roles[W3W_FAVORITE_ITEM_ID_ROLE]           = "itemId";
    return roles;
}

QVariant CW3WFavoriteListModel::data(const QModelIndex &index, int role) const
{
    QVariant rowData;
    int rowIndex = index.row();
    if (index.isValid())
    {
        EW3WFavoriteListRoles w3wFavoriteRole = static_cast<EW3WFavoriteListRoles>(role);
        switch(w3wFavoriteRole)
        {
        case W3W_FAVORITE_ITEM_ADDRESS_ROLE:
            rowData = m_listW3WFavorite.at(rowIndex).m_W3WAddress;
            break;
        case W3W_FAVORITE_ITEM_LABEL_ROLE:
            rowData = m_listW3WFavorite.at(rowIndex).m_W3WAddressLabel;
            break;
        case W3W_FAVORITE_ITEM_TYPE_ROLE:
            rowData = m_listW3WFavorite.at(rowIndex).m_W3WItemType;
            break;
        case W3W_FAVORITE_ITEM_ID_ROLE:
            rowData = m_listW3WFavorite.at(rowIndex).m_ItemId;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "invalid role received: %d", role);
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "model index out of scope: %d", rowIndex);
    }
    return rowData;
}

void CW3WFavoriteListModel::updateW3WFavoriteModelAtIndex(int row, const CW3WData::SW3WAddressData& w3wAddressDataItem)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: row %d", __FUNCTION__, row);

    if((row >= 0) && (row < m_listW3WFavorite.length()))
    {
        /* Update the list item content */
        setData(index(row, 0), w3wAddressDataItem.m_W3WAddress, W3W_FAVORITE_ITEM_ADDRESS_ROLE);
        setData(index(row, 0), w3wAddressDataItem.m_W3WAddressLabel, W3W_FAVORITE_ITEM_LABEL_ROLE);
        setData(index(row, 0), w3wAddressDataItem.m_W3WItemType, W3W_FAVORITE_ITEM_TYPE_ROLE);
        setData(index(row, 0), w3wAddressDataItem.m_ItemId, W3W_FAVORITE_ITEM_ID_ROLE);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s: Index Out of Bound, row: %d", __FUNCTION__, row);
    }
}

void CW3WFavoriteListModel::appendRow(const CW3WData::SW3WAddressData &w3wAddressDataItem)
{
    int rowCount   = m_listW3WFavorite.count();
    beginInsertRows(QModelIndex() , rowCount, rowCount);
    m_listW3WFavorite.append(w3wAddressDataItem);
    endInsertRows();
}

void CW3WFavoriteListModel::removeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    m_listW3WFavorite.removeAt(row);
    endRemoveRows();
}

int CW3WFavoriteListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listW3WFavorite.count();
}

bool CW3WFavoriteListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s : Role:%d, Index:%d ", __FUNCTION__, role, index.row());
    bool returnValue = false;
    if(index.isValid())
    {
        int rowIndex = index.row();
        switch(role)
        {
        case W3W_FAVORITE_ITEM_ADDRESS_ROLE:
        {
            const QString &address = value.toString();
            if(address.compare(m_listW3WFavorite[rowIndex].m_W3WAddress) != 0)
            {
                m_listW3WFavorite[rowIndex].m_W3WAddress = address;
                returnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Favorite Address not changed");
            }
        }
            break;

        case W3W_FAVORITE_ITEM_LABEL_ROLE:
        {
            const QString &addressLabel = value.toString();
            if(addressLabel.compare(m_listW3WFavorite[rowIndex].m_W3WAddressLabel) != 0)
            {
                m_listW3WFavorite[rowIndex].m_W3WAddressLabel = addressLabel;
                returnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Favorite Address Label not changed");
            }
        }
            break;

        case W3W_FAVORITE_ITEM_ID_ROLE:
        {

            int itemId = value.toInt();
            if(itemId != m_listW3WFavorite[rowIndex].m_ItemId)
            {
                m_listW3WFavorite[rowIndex].m_ItemId = itemId;
                returnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Favorite Item Id not changed");
            }
        }
            break;

        default:
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s ,Default Case", __FUNCTION__);
            break;
        }

        if(returnValue)
        {
            QVector<int> roles;
            roles.push_back(role);
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "Model Value Changed");
            emit dataChanged(index, index, roles);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "item role data is not changed");
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s ,Index Out of Scope!", __FUNCTION__);
    }
    return returnValue;
}

CW3WData::SW3WAddressData CW3WFavoriteListModel::getFavoriteData(int itemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, itemId: %d ", __FUNCTION__, itemId);
    CW3WData::SW3WAddressData favoriteDataItem;
    for( int index = 0; index < m_listW3WFavorite.count(); index++ )
    {
        if(itemId == m_listW3WFavorite[index].m_ItemId)
        {
            favoriteDataItem = m_listW3WFavorite[index];
            break;
        }
    }
    return favoriteDataItem;
}

CW3WData::SW3WAddressData CW3WFavoriteListModel::getFavoriteDataAtIndex(int index)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, iIndex: %d ", __FUNCTION__, index);
    CW3WData::SW3WAddressData favoriteDataItem;
    if( (0 <= index) && (m_listW3WFavorite.count() > index) )
    {
        favoriteDataItem = m_listW3WFavorite[index];
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s ,Index Out of Scope!", __FUNCTION__);
    }
    return favoriteDataItem;
}

/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2019
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CW3WAutoSuggestionListModel.cpp
 * @ingroup       HMIComponent
 * @author        Nishant Khandagale
 * @brief         Contain implementation of all the methods declared in
 * CW3WAutoSuggestionListModel class
 */

#include "CW3WAutoSuggestionListModel.h"
#include "logging.h"
#include "CW3WEnum.h"
#include "CW3WAdaptor.h"
#include "CW3WApplication.h"

CW3WAutoSuggestionListModel::CW3WAutoSuggestionListModel(QObject *pParent) :
    QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
}

CW3WAutoSuggestionListModel::~CW3WAutoSuggestionListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_listW3WAutoSuggestion.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CW3WAutoSuggestionListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[W3W_SUGGESTION_ITEM_ADDRESS_ROLE]        = "itemAddressRole";
    roles[W3W_SUGGESTION_ITEM_NEAREST_PLACE_ROLE]  = "itemNearestPlaceRole";
    roles[W3W_SUGGESTION_ITEM_COUNTRY_CODE_ROLE]   = "itemCountryCodeRole";
    roles[W3W_SUGGESTION_ITEM_TYPE_ROLE]           = "itemTypeRole";
    roles[W3W_SUGGESTION_ITEM_ID_ROLE]             = "itemId";
    return roles;
}

QVariant CW3WAutoSuggestionListModel::data(const QModelIndex &index, int role) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    QVariant objRowData;
    int iRowIndex = index.row();
    if (index.isValid())
    {
        EW3WAutoSuggestionListRoles eW3WAutoSuggestionRole = static_cast<EW3WAutoSuggestionListRoles>(role);
        switch(eW3WAutoSuggestionRole)
        {
        case W3W_SUGGESTION_ITEM_ADDRESS_ROLE:
            objRowData = m_listW3WAutoSuggestion.at(iRowIndex).m_W3WAddress;
            break;
        case W3W_SUGGESTION_ITEM_NEAREST_PLACE_ROLE:
            objRowData = m_listW3WAutoSuggestion.at(iRowIndex).m_W3WNearestPlace;
            break;
        case W3W_SUGGESTION_ITEM_COUNTRY_CODE_ROLE:
            objRowData = m_listW3WAutoSuggestion.at(iRowIndex).m_W3WCountryCode;
            break;
        case W3W_SUGGESTION_ITEM_TYPE_ROLE:
            objRowData = m_listW3WAutoSuggestion.at(iRowIndex).m_W3WItemType;
            break;
        case W3W_SUGGESTION_ITEM_ID_ROLE:
            objRowData = m_listW3WAutoSuggestion.at(iRowIndex).m_ItemId;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "invalid role received: %d", role);
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_W3W, "model index out of scope: %d", iRowIndex);
    }
    return objRowData;
}

int CW3WAutoSuggestionListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listW3WAutoSuggestion.count();
}

bool CW3WAutoSuggestionListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s : Role:%d, Index:%d ", __FUNCTION__, role, index.row());
    bool bReturnValue = false;
    if(index.isValid())
    {
        int iRowIndex = index.row();
        switch(role)
        {
        case W3W_SUGGESTION_ITEM_ADDRESS_ROLE:
        {
            const QString &strItemName = value.toString();
            if(strItemName.compare(m_listW3WAutoSuggestion[iRowIndex].m_W3WAddress) != 0)
            {
                m_listW3WAutoSuggestion[iRowIndex].m_W3WAddress = strItemName;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Auto Suggestion Item name not changed");
            }
        }
            break;

        case W3W_SUGGESTION_ITEM_NEAREST_PLACE_ROLE:
        {
            const QString &strItemName = value.toString();
            if(strItemName.compare(m_listW3WAutoSuggestion[iRowIndex].m_W3WNearestPlace) != 0)
            {
                m_listW3WAutoSuggestion[iRowIndex].m_W3WNearestPlace = strItemName;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Auto Suggestion Item name not changed");
            }
        }
            break;

        case W3W_SUGGESTION_ITEM_COUNTRY_CODE_ROLE:
        {
            const QString &strItemName = value.toString();
            if(strItemName.compare(m_listW3WAutoSuggestion[iRowIndex].m_W3WCountryCode) != 0)
            {
                m_listW3WAutoSuggestion[iRowIndex].m_W3WCountryCode = strItemName;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Auto Suggestion Item name not changed");
            }
        }
            break;

        case W3W_SUGGESTION_ITEM_ID_ROLE:
        {

            int iW3WAutoSuggestionId = value.toInt();
            if(iW3WAutoSuggestionId != m_listW3WAutoSuggestion[iRowIndex].m_ItemId)
            {
                m_listW3WAutoSuggestion[iRowIndex].m_ItemId = iW3WAutoSuggestionId;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_W3W, "W3W Auto Suggestion Item name not changed");
            }
        }
            break;

        default:
            LOG_INFO(Log::e_LOG_CONTEXT_W3W,"%s ,Default Case", __FUNCTION__);
            break;
        }
        if(bReturnValue)
        {
            QVector<int> vectRoles;
            vectRoles.push_back(role);
            LOG_INFO(Log::e_LOG_CONTEXT_W3W, "Model Value Changed");
            emit dataChanged(index, index, vectRoles);
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
    return bReturnValue;
}


void CW3WAutoSuggestionListModel::updateW3WAutoSuggestionList(QList<CW3WData::SW3WAddressData> autoSuggestionData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s", __FUNCTION__);
    m_listW3WAutoSuggestion.clear();

    beginResetModel();
    m_listW3WAutoSuggestion = autoSuggestionData;
    endResetModel();
}

CW3WData::SW3WAddressData CW3WAutoSuggestionListModel::getAutoSuggestionData(int itemId)
{
    LOG_INFO(Log::e_LOG_CONTEXT_W3W, "%s, itemID: %d ", __FUNCTION__, itemId);
    CW3WData::SW3WAddressData sAutoSuggestionDataItem;
    for( int index = 0; index < m_listW3WAutoSuggestion.count(); index++ )
    {
        if(itemId == m_listW3WAutoSuggestion[index].m_ItemId)
        {
            sAutoSuggestionDataItem = m_listW3WAutoSuggestion[index];
            break;
        }
    }
    return sAutoSuggestionDataItem;
}


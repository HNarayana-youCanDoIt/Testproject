/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2019
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CGenericListModel.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CGenericListModel, a list generic list model,
 * Used to handle element position and dynamically add remove elements in list,
 */
//____________________________________________________________________________

#include "logging.h"
#include "CGenericListModel.h"

//____________________________________________________________________________
CGenericListModel::CGenericListModel(QObject *pParent)
{
    Q_UNUSED(pParent);
    resetListModel();
}
//____________________________________________________________________________
CGenericListModel::~CGenericListModel()
{
    resetListModel();
}
//____________________________________________________________________________
void CGenericListModel::resetListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, m_listGenericModellist.count:%d", __FUNCTION__, m_listGenericModellist.count());
    m_listGenericModellist.clear();
}
//____________________________________________________________________________
int CGenericListModel::getIndexForElementType(int iListElementType)
{
    int iIndex = 0;

    for(/*this in not needed as veriable unsed in for loop is already defined outside of this for loop*/; iIndex < m_listGenericModellist.count(); iIndex++)
    {
        if (iListElementType == m_listGenericModellist.at(iIndex))
        {
            break;
        }
        else
        {
            //If you are here meand you need to continue your findings.
        }
    }

    if (iIndex >= m_listGenericModellist.count())
    {
        iIndex = -1;
    }
    else
    {
        //If you are here means you found required element.
    }

    return iIndex;
}
//____________________________________________________________________________
int CGenericListModel::tryAddListElementTypeAtStart(int iListElementType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d", __FUNCTION__, iListElementType);
    int iIndex = getIndexForElementType(iListElementType);
    if(iIndex < 0)
    {
        beginInsertRows(QModelIndex(), 0, 0);
        m_listGenericModellist.push_front(iListElementType);
        endInsertRows();
        iIndex = getIndexForElementType(iListElementType);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d already available in list at iIndex:%d", __FUNCTION__, iListElementType, iIndex);
    }
    return iIndex;
}
//____________________________________________________________________________
int CGenericListModel::tryAddListElementTypeAtEnd(int iListElementType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d", __FUNCTION__, iListElementType);
    int iIndex = getIndexForElementType(iListElementType);
    if(iIndex < 0)
    {
        beginInsertRows(QModelIndex(), m_listGenericModellist.count(), m_listGenericModellist.count());
        m_listGenericModellist.push_back(iListElementType);
        endInsertRows();
        iIndex = getIndexForElementType(iListElementType);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d already available in list at iIndex:%d", __FUNCTION__, iListElementType, iIndex);
    }
    return iIndex;
}
//____________________________________________________________________________
int CGenericListModel::tryAddListElementTypeAtIndex(int iListElementType, int iAtIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d", __FUNCTION__, iListElementType);
    int iIndex = getIndexForElementType(iListElementType);
    if(iIndex < 0)
    {
        if ((iAtIndex >= 0) && (iAtIndex < m_listGenericModellist.count()))
        {
            beginInsertRows(QModelIndex(), iAtIndex, iAtIndex);
            m_listGenericModellist.insert(iAtIndex, iListElementType);
            endInsertRows();
            iIndex = getIndexForElementType(iListElementType);
        }
        else if ((iAtIndex >= 0) && (iAtIndex == m_listGenericModellist.count()))
        {
            //Adding at end as iAtIndex given is at end.
            beginInsertRows(QModelIndex(), m_listGenericModellist.count(), m_listGenericModellist.count());
            m_listGenericModellist.push_back(iListElementType);
            endInsertRows();
            iIndex = getIndexForElementType(iListElementType);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d failed to add due to invalid iAtIndex:%d", __FUNCTION__, iListElementType, iAtIndex);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d already available in list at iIndex:%d", __FUNCTION__, iListElementType, iIndex);
    }
    return iIndex;
}
//____________________________________________________________________________
int CGenericListModel::tryAddListElementTypeBeforeElement(int iListElementType, int iListReferanceElementType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d", __FUNCTION__, iListElementType);
    int iIndex = getIndexForElementType(iListElementType);
    if(iIndex < 0)
    {
        int iRefIndex = getIndexForElementType(iListReferanceElementType);
        if (iRefIndex >= 0)
        {
            beginInsertRows(QModelIndex(), iRefIndex, iRefIndex);
            m_listGenericModellist.insert(iRefIndex, iListElementType);
            endInsertRows();
            iIndex = getIndexForElementType(iListElementType);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d failed as iListReferanceElementType:%d not found in list", __FUNCTION__, iListElementType, iListReferanceElementType);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d already available in list at iIndex:%d", __FUNCTION__, iListElementType, iIndex);
    }
    return iIndex;
}
//____________________________________________________________________________
int CGenericListModel::tryAddListElementTypeAfterElement(int iListElementType, int iListReferanceElementType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d", __FUNCTION__, iListElementType);
    int iIndex = getIndexForElementType(iListElementType);
    if(iIndex < 0)
    {
        int iRefIndex = getIndexForElementType(iListReferanceElementType);
        if (iRefIndex >= 0)
        {
            iRefIndex += 1;
            if (iRefIndex == m_listGenericModellist.count())
            {
                //Adding at end as iRefIndex is at end.
                beginInsertRows(QModelIndex(), iRefIndex, iRefIndex);
                m_listGenericModellist.push_back(iListElementType);
                endInsertRows();
            }
            else
            {
                beginInsertRows(QModelIndex(), iRefIndex, iRefIndex);
                m_listGenericModellist.insert(iRefIndex, iListElementType);
                endInsertRows();
            }
            iIndex = getIndexForElementType(iListElementType);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d failed as iListReferanceElementType:%d not found in list", __FUNCTION__, iListElementType, iListReferanceElementType);
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d already available in list at iIndex:%d", __FUNCTION__, iListElementType, iIndex);
    }
    return iIndex;
}
//____________________________________________________________________________
bool CGenericListModel::tryRemoveListElementType(int iListElementType)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d", __FUNCTION__, iListElementType);
    bool bStatus = false;
    int iIndex = getIndexForElementType(iListElementType);
    if(iIndex >= 0)
    {
        beginRemoveRows(QModelIndex(), iIndex, iIndex);
        m_listGenericModellist.removeAt(iIndex);
        endRemoveRows();
        bStatus = true;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, iListElementType:%d not found in list", __FUNCTION__, iListElementType);
    }
    return bStatus;
}
//____________________________________________________________________________
QHash<int, QByteArray> CGenericListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EGenericListModelRoles::LIST_ITEM_TYPE_ROLE] = "genericListItemTypeRole";
    return roles;
}
//____________________________________________________________________________
int CGenericListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listGenericModellist.count();
}
//____________________________________________________________________________
QVariant CGenericListModel::data(const QModelIndex &index, int role) const
{
    QVariant objRowData;
    int iRowIndex = index.row();
    if (index.isValid())
    {
        EGenericListModelRoles eRole = static_cast<EGenericListModelRoles>(role);
        switch(eRole)
        {
        case EGenericListModelRoles::LIST_ITEM_TYPE_ROLE:
        {
            objRowData = m_listGenericModellist.at(iRowIndex);
        }
            break;
        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MAIN, "%s, invalid role received: %d", __FUNCTION__, role);
        }
            break;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN, "%s, model index out of scope: %d", __FUNCTION__, iRowIndex);
    }
    return objRowData;
}
//____________________________________________________________________________
bool CGenericListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, Role:%d, Index:%d ", __FUNCTION__, role, index.row());
    bool bReturnValue = false;

    if(index.isValid())
    {
        int iRowIndex = index.row();
        switch(role)
        {
        case EGenericListModelRoles::LIST_ITEM_TYPE_ROLE:
        {
            int ilistElementType = value.toInt();
            if(ilistElementType != m_listGenericModellist[iRowIndex])
            {
                m_listGenericModellist[iRowIndex] = ilistElementType;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, ilistElementType:%d not changed for iRowIndex:%d", __FUNCTION__, ilistElementType, iRowIndex);
            }
        }
            break;

        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_MAIN, "%s, change fail due to Invalid iRowIndex:%d", __FUNCTION__, iRowIndex);
        }
            break;
        }

        if(bReturnValue)
        {
            QVector<int> vectRoles;
            vectRoles.push_back(role);
            LOG_INFO(Log::e_LOG_CONTEXT_MAIN, "%s, changed for iRowIndex:%d", __FUNCTION__, iRowIndex);
            emit dataChanged(index, index, vectRoles);
        }
        else
        {
            //Do Nothing!
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_MAIN,"%s, Index Out of Scope!", __FUNCTION__);
    }

    return bReturnValue;
}
//____________________________________________________________________________

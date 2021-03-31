/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CContactDetailListModel.cpp
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         This file contains CContactDetailListModel class that shall implement the
 * contact detail list data model that shall be  display on contact detail screen.
 */

#include "CContactDetailListModel.h"
#include "logging.h"

CContactDetailListModel::CContactDetailListModel(QObject* pParent) :
    QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
}

CContactDetailListModel::~CContactDetailListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
}

QHash<int, QByteArray> CContactDetailListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[CONTACT_INDEX_ROLE]          = "contactIndex";
    roles[CONTACT_ID_ROLE]             = "contactID";
    roles[CONTACT_NAME_ROLE]           = "contactName";
    roles[CONTACT_NUMBER_ROLE]         = "contactNumber";
    roles[CONTACT_TYPE_ROLE]           = "contactType";
    roles[CONTACT_IS_FAVORITE_ROLE]    = "contactIsFavorite";
    roles[CONTACT_FAVORITE_INDEX_ROLE] = "contactFavoriteIndex";
    return roles;
}

int CContactDetailListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.count();
}

QVariant CContactDetailListModel::data(const QModelIndex &index, int role) const
{
    QVariant objRowData;
    int iRowIndex = index.row();
    if (index.isValid())
    {
        switch (role)
        {
        case CONTACT_INDEX_ROLE:
        {
            objRowData = m_list[iRowIndex].m_iIndex;
        }
            break;
        case CONTACT_ID_ROLE:
        {
            objRowData = m_list[iRowIndex].m_iContactID;
        }
            break;
        case CONTACT_NAME_ROLE:
        {
            objRowData = m_list[iRowIndex].m_strName;
        }
            break;
        case CONTACT_NUMBER_ROLE:
        {
            objRowData = m_list[iRowIndex].m_strNumber;
        }
            break;
        case CONTACT_TYPE_ROLE:
        {
            objRowData = m_list[iRowIndex].m_iType;
        }
            break;
        case CONTACT_IS_FAVORITE_ROLE:
        {
            objRowData = m_list[iRowIndex].m_bIsFavorite;
        }
            break;
        case CONTACT_FAVORITE_INDEX_ROLE:
        {
            objRowData = m_list[iRowIndex].m_iFavIndex;
        }
            break;
        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "invalid role received: %d", role);
        }
            break;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
    return objRowData;
}

void CContactDetailListModel::insertRows(const CPhoneData::SContactDetailInfo contactDetailInfo)
{
    beginInsertRows(QModelIndex() , rowCount(), rowCount());
    m_list.append(contactDetailInfo);
    endInsertRows();
}

void CContactDetailListModel::removeRows()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_list.clear();
    endRemoveRows();
}

int CContactDetailListModel::getFavoriteIndex(int iRowIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    int _iValue = 0;
    if ((iRowIndex >= 0) && (iRowIndex < m_list.count()))
    {
        _iValue = m_list[iRowIndex].m_iFavIndex;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
    return _iValue;
}

void CContactDetailListModel::setFavoriteIndex(int iRowIndex, int iFavIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    if ((iRowIndex >= 0) && (iRowIndex < m_list.count()))
    {
        m_list[iRowIndex].m_iFavIndex = iFavIndex;
        m_list[iRowIndex].m_bIsFavorite = (iFavIndex > 0);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
}

QString CContactDetailListModel::getNameFromIndex(int iRowIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QString _sValue = "";
    if ((iRowIndex >= 0) && (iRowIndex < m_list.count()))
    {
        _sValue = m_list[iRowIndex].m_strName;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
    return _sValue;
}

QString CContactDetailListModel::getNumberFromIndex(int iRowIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QString _sValue = "";
    if ((iRowIndex >= 0) && (iRowIndex < m_list.count()))
    {
        _sValue = m_list[iRowIndex].m_strNumber;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
    return _sValue;
}

int CContactDetailListModel::getContactIdFromIndex(int iRowIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    int _sValue = 0;
    if ((iRowIndex >= 0) && (iRowIndex < m_list.count()))
    {
        _sValue = m_list[iRowIndex].m_iContactID;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
    return _sValue;
}

int CContactDetailListModel::getContactTypeFromIndex(int iRowIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: iRowIndex is: %d", __FUNCTION__, iRowIndex);
    int iValue = -1;
    if ((iRowIndex >= 0) && (iRowIndex < m_list.count()))
    {
        iValue = m_list[iRowIndex].m_iType;
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: model index out of scope", __FUNCTION__);
    }
    return iValue;
}

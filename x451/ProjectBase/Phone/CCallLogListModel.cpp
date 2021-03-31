/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CCallLogListModel.cpp
 * @ingroup       HMIComponent
 * @author        Nandkishor Lokhande
 * @brief         This file contains CCallLogListModel class that shall implement the
 * call log list data model that shall be  display on call log screen.
 */

#include "CCallLogListModel.h"
#include "logging.h"

CCallLogListModel::CCallLogListModel(QObject* pParent) :
    QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
}

CCallLogListModel::~CCallLogListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
}

QHash<int, QByteArray> CCallLogListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[CALL_LOG_NAME_ROLE]       = "callLogName";
    roles[CALL_LOG_NUMBER_ROLE]     = "callLogNumber";
    roles[CALL_LOG_TYPE_ROLE]       = "callLogType";
    roles[CALL_LOG_TIME_ROLE]       = "callLogTime";
    roles[CALL_LOG_DATE_ROLE]       = "callLogDate";
    return roles;
}

int CCallLogListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.count();
}

QVariant CCallLogListModel::data(const QModelIndex &index, int role) const
{
    QVariant objRowData;
    int iRowIndex = index.row();
    if (index.isValid())
    {
        switch (role)
        {
        case CALL_LOG_NAME_ROLE:
        {
            objRowData = m_list[iRowIndex].m_strName;
        }
            break;
        case CALL_LOG_NUMBER_ROLE:
        {
            objRowData = m_list[iRowIndex].m_strNumber;
        }
            break;
        case CALL_LOG_TYPE_ROLE:
        {
            objRowData = m_list[iRowIndex].m_iCallType;
        }
            break;
        case CALL_LOG_TIME_ROLE:
        {
            objRowData = m_list[iRowIndex].m_strTime;
        }
            break;
        case CALL_LOG_DATE_ROLE:
        {
            objRowData = m_list[iRowIndex].m_strDate;
        }
            break;
        default:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "invalid role received: %d", role);
        }
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
    return objRowData;
}

void CCallLogListModel::insertRows(const CPhoneData::SCallLogInfo callDetailInfo)
{
    beginInsertRows(QModelIndex() , rowCount(), rowCount());
    m_list.append(callDetailInfo);
    endInsertRows();
}

void CCallLogListModel::removeRows()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_list.clear();
    endRemoveRows();
}

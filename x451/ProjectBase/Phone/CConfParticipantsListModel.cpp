/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CConfParticipantsListModel.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CConfParticipantsListModel class
 */

#include "CConfParticipantsListModel.h"
#include "logging.h"

CConfParticipantsListModel::CConfParticipantsListModel(QObject *pParent) :
    QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listConfParticipant.clear();
}

CConfParticipantsListModel::~CConfParticipantsListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listConfParticipant.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CConfParticipantsListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[CONF_PARTICIPANT_NAME_ROLE]   = "participantNameRole";
    roles[CALLER_ID_ROLE]               = "callerIdRole";
    roles[END_PARTICIPANT_CALL_ROLE]    = "endParticpiantCallRole";
    return roles;
}

QVariant CConfParticipantsListModel::data(const QModelIndex &index, int role) const
{
    QVariant objRowData;
    int iRowIndex = index.row();
    if(index.isValid())
    {
        EConfParticipantListRoles eConfParticipantRole = static_cast<EConfParticipantListRoles>(role);
        switch(eConfParticipantRole)
        {
        case CONF_PARTICIPANT_NAME_ROLE:
            objRowData = m_listConfParticipant[iRowIndex].m_strName;
            break;
        case CALLER_ID_ROLE:
            objRowData = m_listConfParticipant[iRowIndex].m_iCalldId;
            break;
        case END_PARTICIPANT_CALL_ROLE:
            objRowData = m_listConfParticipant[iRowIndex].m_bHangupEnhancedStatus;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "invalid role received: %d", role);
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }

    return objRowData;
}

int CConfParticipantsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listConfParticipant.count();
}

/************************************************************************//**
 * @category    EXTERNAL METHODS
 ************************************************************************/
void CConfParticipantsListModel::removeRows()
{
    beginRemoveRows(QModelIndex(), 0, m_listConfParticipant.count());
    m_listConfParticipant.clear();
    endRemoveRows();
}

void CConfParticipantsListModel::insertRows(const CPhoneData::SConfParticipantInfo& objConfParticipantInfo)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE,  "%s, name of participant is: %s, enhanced hangup feature supported: %d",
             __FUNCTION__, objConfParticipantInfo.m_strName.toStdString().c_str(),
             objConfParticipantInfo.m_bHangupEnhancedStatus);
    int iRowCount   = m_listConfParticipant.count();
    beginInsertRows(QModelIndex() , iRowCount, iRowCount);
    m_listConfParticipant.append(objConfParticipantInfo);
    endInsertRows();
}

void CConfParticipantsListModel::updateConfParticipantListItem(int iListIndex , const QVariant& objData, int iRole)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    bool bDataChanged = false;
    if((iListIndex >= 0) && (iListIndex < m_listConfParticipant.size()))
    {
        EConfParticipantListRoles eConfParticipantRole = static_cast<EConfParticipantListRoles>(iRole);
        switch(eConfParticipantRole)
        {
        case CONF_PARTICIPANT_NAME_ROLE:
        {
            m_listConfParticipant[iListIndex].m_strName = objData.toString();
            bDataChanged = true;
        }
            break;
        case CALLER_ID_ROLE:
        {
            m_listConfParticipant[iListIndex].m_iCalldId = objData.toInt();
            bDataChanged = true;
        }
            break;
        case END_PARTICIPANT_CALL_ROLE:
        {
            m_listConfParticipant[iListIndex].m_bHangupEnhancedStatus = objData.toBool();
            bDataChanged = true;
        }
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "invalid role received: %d", iRole);
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "list index out of scope");
    }

    //If role data is changed then only emit the dataChanged signal to update to QML
    if(bDataChanged)
    {
        const QModelIndex &objCurrentIndex = index(iListIndex, 0);
        QVector<int> vectRoles;
        vectRoles.push_back(iRole);
        emit dataChanged(objCurrentIndex, objCurrentIndex, vectRoles);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "item role data is not changed");
    }
}


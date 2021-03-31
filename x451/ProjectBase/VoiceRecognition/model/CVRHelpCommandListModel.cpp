/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRHelpCommandListModel.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CVRHelpCommandListModel class
 */

#include "CVRHelpCommandListModel.h"
#include "logging.h"

CVRHelpCommandListModel::CVRHelpCommandListModel(QObject *pParent)
    : QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    m_listHelpCommand.clear();
}


CVRHelpCommandListModel::~CVRHelpCommandListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    m_listHelpCommand.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CVRHelpCommandListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[VR_HELP_LIST_ITEM_TEXT_ROLE]  = "vrHelpTextRole";
    return roles;
}

QVariant CVRHelpCommandListModel::data(const QModelIndex &objIndex, int iRole) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    QVariant objRowData;
    int iRowIndex = objIndex.row();
    if (objIndex.isValid())
    {
        EVRHelpListRoles eVRHelpCommandListRoles = static_cast<EVRHelpListRoles>(iRole);
        switch(eVRHelpCommandListRoles)
        {
        case VR_HELP_LIST_ITEM_TEXT_ROLE:
        {
            objRowData = m_listHelpCommand[iRowIndex];
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: command text is: %s", __FUNCTION__, objRowData.toString().toStdString().c_str());
        }
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "invalid role received: %d", iRole);
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
    return objRowData;
}

int CVRHelpCommandListModel::rowCount(const QModelIndex &objParent) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s, help command count is: %d", __FUNCTION__, m_listHelpCommand.count());
    Q_UNUSED(objParent);
    return m_listHelpCommand.count();
}

/************************************************************************//**
 * @category    EXTERNAL METHODS
 ************************************************************************/
void CVRHelpCommandListModel::removeRows()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    beginRemoveRows(QModelIndex(), 0, m_listHelpCommand.count());
    m_listHelpCommand.clear();
    endRemoveRows();
}

void CVRHelpCommandListModel::insertRows(const QStringList& listHelpCommand)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    int iSize   = static_cast<int>(listHelpCommand.size());
    if(iSize > 0)
    {
        beginInsertRows(QModelIndex() , 0, (iSize - 1));
        for(int iIndex = 0; iIndex < iSize; iIndex++)
        {
            m_listHelpCommand.append(listHelpCommand.at(iIndex));
        }
        endInsertRows();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: VR help command list size is less then or equal to 0", __FUNCTION__);
    }
}

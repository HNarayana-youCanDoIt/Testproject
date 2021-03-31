/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CVRListModel.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CVRListModel class
 */

#include "CVRListModel.h"
#include "logging.h"

CVRListModel::CVRListModel(QObject *pParent)
    : QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    m_objVRList.clear();
}

CVRListModel::~CVRListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    m_objVRList.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CVRListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[VR_LIST_ITEM_NAME_ROLE]   = "vrListItemNameRole";
    return roles;
}

QVariant CVRListModel::data(const QModelIndex &objIndex, int iRole) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    QVariant objRowData;
    int iRowIndex = objIndex.row();
    if (objIndex.isValid())
    {
        EVRListRoles eVRListRoles = static_cast<EVRListRoles>(iRole);
        switch(eVRListRoles)
        {
        case VR_LIST_ITEM_NAME_ROLE:
            objRowData = m_objVRList[iRowIndex];
            LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: vr item name is: %s", __FUNCTION__, objRowData.toString().toStdString().c_str());
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

int CVRListModel::rowCount(const QModelIndex &objParent) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s, picklist count is: %d", __FUNCTION__, m_objVRList.count());
    Q_UNUSED(objParent);
    return m_objVRList.count();
}

/************************************************************************//**
 * @category    EXTERNAL METHODS
 ************************************************************************/
void CVRListModel::removeRows()
{
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s", __FUNCTION__);
    beginRemoveRows(QModelIndex(), 0, m_objVRList.count());
    m_objVRList.clear();
    endRemoveRows();
}

void CVRListModel::insertRows(const std::vector<std::string>& m_vectVRList)
{    
    int iSize   = static_cast<int>(m_vectVRList.size());
    LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: list size is: %d", __FUNCTION__, iSize);
    if(iSize > 0)
    {
        beginInsertRows(QModelIndex() , 0, (iSize - 1));
        for(int iIndex = 0; iIndex < iSize; iIndex++)
        {
            QString strIndex = QString::number(iIndex + 1) + ". ";
            m_objVRList.append(strIndex + QString::fromStdString(m_vectVRList.at(iIndex)));
        }
        endInsertRows();
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_VR, "%s: vr list size is less then or equal to 0", __FUNCTION__);
    }
}

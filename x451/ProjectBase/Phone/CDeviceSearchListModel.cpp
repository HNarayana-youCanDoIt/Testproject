/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
 /**
 * @file          CDeviceSearchListModel.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CDeviceSearchListModel class
 */

#include "CDeviceSearchListModel.h"
#include "logging.h"

CDeviceSearchListModel::CDeviceSearchListModel(QObject *pParent) :
    QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listSearchDevices.clear();
}

CDeviceSearchListModel::~CDeviceSearchListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listSearchDevices.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CDeviceSearchListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[DEVICE_NAME_ROLE]     = "deviceNameRole";
    roles[DEVICE_ADDRESS_ROLE]  = "deviceAddressRole";
    return roles;
}

QVariant CDeviceSearchListModel::data(const QModelIndex &index, int role) const
{
    QVariant objRowData;
    int iRowIndex = index.row();
    if (index.isValid())
    {
        EDeviceSearchListRoles eDeviceSearchRole = static_cast<EDeviceSearchListRoles>(role);
        switch(eDeviceSearchRole)
        {
        case DEVICE_NAME_ROLE:
            objRowData = m_listSearchDevices[iRowIndex].m_strName;
            break;
        case DEVICE_ADDRESS_ROLE:
            objRowData = m_listSearchDevices[iRowIndex].m_strDeviceBtAddr;
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

int CDeviceSearchListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listSearchDevices.count();
}

/************************************************************************//**
 * @category    EXTERNAL METHODS
 ************************************************************************/
void CDeviceSearchListModel::removeRows()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_listSearchDevices.clear();
    endRemoveRows();
}

QString CDeviceSearchListModel::getNameFromIndex(int iRowIndex)
{
    QString strValue = "";
    if ((iRowIndex >= 0) && (iRowIndex < m_listSearchDevices.count()))
    {
        strValue = m_listSearchDevices[iRowIndex].m_strName;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
    return strValue;
}

QString CDeviceSearchListModel::getAddrFromIndex(int iRowIndex)
{
    QString strValue = "";
    if ((iRowIndex >= 0) && (iRowIndex < m_listSearchDevices.count()))
    {
        strValue = m_listSearchDevices[iRowIndex].m_strDeviceBtAddr;
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "model index out of scope: %d", iRowIndex);
    }
    return strValue;
}

void CDeviceSearchListModel::insertRows(const CPhoneData::SDeviceInfo &objDeviceInfo)
{
    int iRowCount   = m_listSearchDevices.count();
    beginInsertRows(QModelIndex() , iRowCount, iRowCount);
    m_listSearchDevices.append(objDeviceInfo);
    endInsertRows();
}

void CDeviceSearchListModel::removeRow(int iRow)
{
    beginRemoveRows(QModelIndex(), iRow, iRow);
    m_listSearchDevices.removeAt(iRow);
    endRemoveRows();
}

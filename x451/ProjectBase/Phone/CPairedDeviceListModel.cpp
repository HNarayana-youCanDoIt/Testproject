/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CPairedDeviceListModel.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Singh Parihar
 * @brief         Contain implementation of all the methods declared in
 *                CPairedDeviceListModel class
 */

#include "CPairedDeviceListModel.h"
#include "logging.h"

CPairedDeviceListModel::CPairedDeviceListModel(QObject *pParent) :
    QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listPairedDevices.clear();
}

CPairedDeviceListModel::~CPairedDeviceListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listPairedDevices.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CPairedDeviceListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[PAIRED_DEVICE_NAME_ROLE]              = "pairDeviceNameRole";
    roles[PAIRED_DEVICE_ADDRESS_ROLE]           = "pairDeviceAddressRole";
    roles[PAIRED_DEVICE_CONNECTION_STATUS_ROLE] = "connectionStatusRole";
    roles[PAIRED_DEVICE_ITEM_TYPE_ROLE]         = "pairedDeviceItemTypeRole";
    return roles;
}

QVariant CPairedDeviceListModel::data(const QModelIndex &index, int role) const
{
    QVariant objRowData;
    int iRowIndex = index.row();
    if (index.isValid())
    {
        EPairedDeviceListRoles ePairedDeviceRole = static_cast<EPairedDeviceListRoles>(role);
        switch(ePairedDeviceRole)
        {
        case PAIRED_DEVICE_NAME_ROLE:
            objRowData = m_listPairedDevices[iRowIndex].m_strName;
            break;
        case PAIRED_DEVICE_ADDRESS_ROLE:
            objRowData = m_listPairedDevices[iRowIndex].m_strDeviceBtAddr;
            break;
        case PAIRED_DEVICE_CONNECTION_STATUS_ROLE:
            objRowData = m_listPairedDevices[iRowIndex].m_bDeviceConnectionStatus;
            break;
        case PAIRED_DEVICE_ITEM_TYPE_ROLE:
            objRowData = m_listPairedDevices[iRowIndex].m_eItemType;
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

int CPairedDeviceListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listPairedDevices.count();
}

/************************************************************************//**
 * @category    EXTERNAL METHODS
 ************************************************************************/
void CPairedDeviceListModel::removeRows()
{
    LOG_INFO (Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    beginResetModel();
    m_listPairedDevices.clear();
    endResetModel();
}

void CPairedDeviceListModel::insertRows(const QList<CPhoneData::SPairedDeviceInfo>& listPairedDevices)
{
    LOG_INFO (Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);
    beginResetModel();
    m_listPairedDevices = listPairedDevices;
    endResetModel();
}

bool CPairedDeviceListModel::isDeviceAlreadyPaired(const QString &strBtAddress)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s", __FUNCTION__);

    bool bReturn = false;

    if (!m_listPairedDevices.empty())
    {
        for (int index = 0; index < m_listPairedDevices.count(); ++index)
        {
            if (0 == m_listPairedDevices[index].m_strDeviceBtAddr.compare(strBtAddress))
            {
                bReturn = true;
                break;
            }
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_PHONE, "%s: Paired Device List is empty.", __FUNCTION__);
    }

    return bReturn;
}


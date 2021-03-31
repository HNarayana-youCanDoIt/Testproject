/*****************************************************************
* Project           Harman Car Multimedia System
* (c) copyright     2017
* Company           Harman/Becker Automotive Systems GmbH
*                   All rights reserved
* Secrecy Level     STRICTLY CONFIDENTIAL
****************************************************************/
/**
 * @file            CHomeUpdateShortcutModel.cpp
 * @ingroup         HMIComponent
 * @author          Nandkishor Lokhande
 * CHomeUpdateShortcutModel, a model class for Update-Shortcut-List of Home module,
 * CHomeUpdateShortcutModel is QAbstractListModel class used to assign model to ListModel present in Update-Shortcut-List QML of Home module.
 */

#include "CHomeUpdateShortcutModel.h"
#include "logging.h"
//____________________________________________________________________________
CHomeUpdateShortcutModel::CHomeUpdateShortcutModel(QObject *parent)
{
    Q_UNUSED(parent);
}
//____________________________________________________________________________
int CHomeUpdateShortcutModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_liShortcutIDList.count();
}
//____________________________________________________________________________
QVariant CHomeUpdateShortcutModel::data(const QModelIndex &objModelIndex, int iRole) const
{
    QVariant objData = QVariant();
    int iRowIndex = objModelIndex.row();
    if (objModelIndex.isValid())
    {
        switch (iRole)
        {
        case shortcutIdRole:
            objData = m_liShortcutIDList[objModelIndex.row()];
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CHomeUpdateShortcutModel::data, invalid role: %d", iRole);
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME,"%s, invalid row: %d", __FUNCTION__, iRowIndex);
    }
    return objData;
}
//____________________________________________________________________________
void CHomeUpdateShortcutModel::addItem(const int &iShortcutData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    int iRowCount = m_liShortcutIDList.count();
    beginInsertRows(QModelIndex(), iRowCount, iRowCount);
    m_liShortcutIDList << iShortcutData;
    endInsertRows();
}
//____________________________________________________________________________
void CHomeUpdateShortcutModel::clearList()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_liShortcutIDList.clear();
    endRemoveRows();
}
//____________________________________________________________________________
QHash<int, QByteArray> CHomeUpdateShortcutModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[shortcutIdRole] = "shortcutIdRole";
    return roles;
}
//____________________________________________________________________________
QList<int> CHomeUpdateShortcutModel::shortcutDataList() const
{
    return m_liShortcutIDList;
}
//____________________________________________________________________________
void CHomeUpdateShortcutModel::setModeDataList(const QList<int> &liShortcutIDList)
{
    m_liShortcutIDList = liShortcutIDList;
}
//____________________________________________________________________________

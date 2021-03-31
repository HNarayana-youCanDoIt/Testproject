/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupAudioListModel.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupAudioListModel.cpp, audio setup list model class cpp file, responsible for creating audio setup static list model
 */

#include "CSetupAudioListModel.h"

CSetupAudioListModel::CSetupAudioListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);

    m_AudioSetupDataList.clear();
    m_AudioSetupDataList.append(new CSetupData("Bass, Middle & Treble"));
    m_AudioSetupDataList.append(new CSetupData("Balance & Fader"      ));
    m_AudioSetupDataList.append(new CSetupData("Audio Presets"        ));
}

CSetupAudioListModel::~CSetupAudioListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    qDeleteAll(m_AudioSetupDataList.begin(), m_AudioSetupDataList.end());
    m_AudioSetupDataList.clear();
}

int CSetupAudioListModel::rowCount(const QModelIndex &parent) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupAudioListModel::rowCount : %d ", m_AudioSetupDataList.count());
    Q_UNUSED(parent)
    return m_AudioSetupDataList.count();
}

QVariant CSetupAudioListModel::data(const QModelIndex &index, int role) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    QVariant data = QVariant();
    int row = index.row();
    if (row < 0 || row >= rowCount())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupAudioListModel::data, invalid row: %d", row);
    }
    else
    {
        switch(role)
        {
        case ListItemIndexRole:
            data = m_AudioSetupDataList[row]->m_eListItemIndex;
            break;
        case ListItemNameRole:
            data = m_AudioSetupDataList[row]->m_sListItemName;
            break;
        case ListItemTypeRole:
            data = m_AudioSetupDataList[row]->m_sListItemType;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupAudioListModel::data, invalid role: %d", role);
            break;
        }
    }
    return data;
}

QHash<int, QByteArray> CSetupAudioListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[ListItemIndexRole] = "listItemIndexRole";
    roles[ListItemNameRole] = "listItemNameRole";
    roles[ListItemTypeRole] = "listItemTypeRole";
    return roles;
}

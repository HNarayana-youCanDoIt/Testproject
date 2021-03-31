/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupBMTListModel.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupBMTListModel.cpp, BMT list model class cpp file, responsible for creating BMT static list model
 */

#include "CSetupBMTListModel.h"

CSetupBMTListModel::CSetupBMTListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);

    m_pAudioAdaptor = CAudioAdaptor::getInstance();

    m_BMTSetupDataList.clear();
    m_BMTSetupDataList.append(new CSetupData("Bass"  , CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, 0));
    m_BMTSetupDataList.append(new CSetupData("Middle", CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, 0));
    m_BMTSetupDataList.append(new CSetupData("Treble", CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, 0));

    connect(m_pAudioAdaptor, SIGNAL(sigBassChanged())  , this, SLOT(sltBassChanged()));
    connect(m_pAudioAdaptor, SIGNAL(sigMidChanged())   , this, SLOT(sltMidChanged()));
    connect(m_pAudioAdaptor, SIGNAL(sigTrebleChanged()), this, SLOT(sltTrebleChanged()));
}

CSetupBMTListModel::~CSetupBMTListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    qDeleteAll(m_BMTSetupDataList.begin(), m_BMTSetupDataList.end());
    m_BMTSetupDataList.clear();
}

int CSetupBMTListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupBMTListModel::rowCount : %d ", m_BMTSetupDataList.count());
    return m_BMTSetupDataList.count();
}

QVariant CSetupBMTListModel::data(const QModelIndex &index, int role) const
{
    QVariant data = QVariant();
    int row = index.row();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: role: %d, row: %d", __FUNCTION__, role, row);
    if (row < 0 || row >= rowCount())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupBMTListModel::data, invalid row: %d", row);
    }
    else
    {
        switch(role)
        {
        case ListItemIndexRole:
            data = m_BMTSetupDataList[row]->m_eListItemIndex;
            break;
        case ListItemNameRole:
            data = m_BMTSetupDataList[row]->m_sListItemName;
            break;
        case ListItemTypeRole:
            data = m_BMTSetupDataList[row]->m_sListItemType;
            break;
        case ListItemCheckedRole:
            data = m_BMTSetupDataList[row]->m_bListItemChecked;
            break;
        case ListItemValueRole:
            data = m_BMTSetupDataList[row]->m_iListItemValue;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupBMTListModel::data, invalid role: %d", role);
            break;
        }
    }
    return data;
}

QHash<int, QByteArray> CSetupBMTListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[ListItemIndexRole]   = "listItemIndexRole";
    roles[ListItemNameRole]    = "listItemNameRole";
    roles[ListItemTypeRole]    = "listItemTypeRole";
    roles[ListItemCheckedRole] = "listItemCheckedRole";
    roles[ListItemValueRole]   = "listItemValueRole";
    return roles;
}

bool CSetupBMTListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupBMTListModel::setData : %d ", role );
    bool bReturnValue = false;
    switch (role)
    {
    case ListItemCheckedRole:
    {
        m_BMTSetupDataList[index.row()]->m_bListItemChecked = value.toBool();
        emit dataChanged(index, index);
        bReturnValue = true;
    }
        break;
    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupBMTListModel::setData default case" );
    }
        break;
    }
    return bReturnValue;
}

void CSetupBMTListModel::sltBassChanged()
{
    int bass = m_pAudioAdaptor->bass();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupBMTListModel::sltBassChanged : %d ", bass );
    m_BMTSetupDataList[CSetupEnums::BMT_BASS]->m_iListItemValue = bass;
    m_BMTSetupDataList[CSetupEnums::BMT_BASS]->m_bListItemChecked = true;

    /* Refreshing the qml's data for the index which is changed */
    QModelIndex left = createIndex(CSetupEnums::BMT_BASS, 0);
    QModelIndex right = createIndex(CSetupEnums::BMT_BASS, 0);
    emit dataChanged(left, right);

}

void CSetupBMTListModel::sltMidChanged()
{
    int mid = m_pAudioAdaptor->mid();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupBMTListModel::sltMidChanged : %d ", mid );
    m_BMTSetupDataList[CSetupEnums::BMT_MIDDLE]->m_iListItemValue = mid;
    m_BMTSetupDataList[CSetupEnums::BMT_MIDDLE]->m_bListItemChecked = true;

    /* Refreshing the qml's data for the index which is changed */
    QModelIndex left = createIndex(CSetupEnums::BMT_MIDDLE, 0);
    QModelIndex right = createIndex(CSetupEnums::BMT_MIDDLE, 0);
    emit dataChanged(left, right);
}

void CSetupBMTListModel::sltTrebleChanged()
{
    int treble = m_pAudioAdaptor->treble();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupBMTListModel::sltTrebleChanged : %d ", treble );
    m_BMTSetupDataList[CSetupEnums::BMT_TREBLE]->m_iListItemValue = treble;
    m_BMTSetupDataList[CSetupEnums::BMT_TREBLE]->m_bListItemChecked = true;

    /* Refreshing the qml's data for the index which is changed */
    QModelIndex left = createIndex(CSetupEnums::BMT_TREBLE, 0);
    QModelIndex right = createIndex(CSetupEnums::BMT_TREBLE, 0);
    emit dataChanged(left, right);
}

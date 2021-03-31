
/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupGeneralListModel.cpp
 * @ingroup       HMIComponent
 * @author        Rajat Gupta
 * CSetupGeneralListModel.cpp, setup general list model class cpp file, responsible for creating setup general static list model
 */

#include "CSetupGeneralListModel.h"
#include "CEnggAdaptor.h"

CSetupGeneralListModel::CSetupGeneralListModel(QObject *parent):
    QAbstractListModel(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);

    /* Third parameter true/false decides to enable/disable the corresponding setup */
    m_SetupGeneralDataList.clear();

    m_SetupGeneralDataList.append(new CSetupData(tr("TEXT_GENERALSETUP_SET_DATE_AND_TIME_TITLE_LABEL"), "", "", CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, true, false, false, CSetupEnums::GENERALSETUP_SET_DATE_AND_TIME, -1, -1, CSetupEnums::SETUP_SCREEN_GENERAL));
    //Initially it will be disabled, and will be enabled only when the EnggMenu Proxy will be available.
    m_SetupGeneralDataList.append(new CSetupData(tr("TEXT_SETTING_GENERAL_RESET_FACTORY_LABEL"), "", "", CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, false, false, false, CSetupEnums::GENERALSETUP_RESET_TO_FACTORY_DEFAULT, -1, -1, CSetupEnums::SETUP_SCREEN_GENERAL));

    connect(CEnggAdaptor::getInstance(), SIGNAL(sigEnggMenuProxyStatusChanged()), this, SLOT(sltEnggProxyStatusChanged()), Qt::QueuedConnection);
}

CSetupGeneralListModel::~CSetupGeneralListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    qDeleteAll(m_SetupGeneralDataList.begin(), m_SetupGeneralDataList.end());
    m_SetupGeneralDataList.clear();
}

int CSetupGeneralListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupGeneralListModel::rowCount : %d ", m_SetupGeneralDataList.count());
    return m_SetupGeneralDataList.count();
}

QVariant CSetupGeneralListModel::data(const QModelIndex &index, int iRole) const
{
    QVariant objData = QVariant();
    int row = index.row();
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "CSetupGeneralListModel::data : %d %d ", row, rowCount());
    if (row < 0 || row >= rowCount())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupGeneralListModel::data, invalid row: %d", row);
    }
    else
    {
        switch(iRole)
        {
        case ListItemIndexRole:
            objData = m_SetupGeneralDataList[row]->m_eListItemIndex;
            break;
        case ListItemNameRole:
            objData = m_SetupGeneralDataList[row]->m_sListItemName;
            break;
        case ListItemTypeRole:
            objData = m_SetupGeneralDataList[row]->m_sListItemType;
            break;
        case ListItemEnableRole:
            objData = m_SetupGeneralDataList[row]->m_bIsListItemEnabled;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CSetupGeneralListModel::data, invalid role: %d", iRole);
            break;
        }
    }
    return objData;
}

QHash<int, QByteArray> CSetupGeneralListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[ListItemIndexRole] = "listItemIndexRole";
    roles[ListItemNameRole] = "listItemNameRole";
    roles[ListItemTypeRole] = "listItemTypeRole";
    roles[ListItemEnableRole] = "listItemEnableRole";
    return roles;
}

void CSetupGeneralListModel::sltEnggProxyStatusChanged()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    // Enable/Disable according to EnggMenu Proxy Status.
    if(m_SetupGeneralDataList.size() > CSetupEnums::GENERALSETUP_RESET_TO_FACTORY_DEFAULT)
    {
        m_SetupGeneralDataList[CSetupEnums::GENERALSETUP_RESET_TO_FACTORY_DEFAULT]->m_bIsListItemEnabled = CEnggAdaptor::getInstance()->enggMenuProxyStatus();
        /* Refreshing the qml's data for the index which is changed */
        QModelIndex left = createIndex(CSetupEnums::GENERALSETUP_RESET_TO_FACTORY_DEFAULT, 0);
        QModelIndex right = createIndex(CSetupEnums::GENERALSETUP_RESET_TO_FACTORY_DEFAULT, 0);
        emit dataChanged(left, right);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s: Reset Factory Item Not Present in general setup List", __FUNCTION__);
    }
}

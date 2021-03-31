#include "CHomeConfigureFavHKModel.h"
#include "logging.h"

CHomeConfigureFavHKModel::CHomeConfigureFavHKModel(QObject *parent)
    : QAbstractListModel(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
}

CHomeConfigureFavHKModel::~CHomeConfigureFavHKModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    qDeleteAll(m_liConfigureFavHKList.begin(), m_liConfigureFavHKList.end());
    m_liConfigureFavHKList.clear();
}

int CHomeConfigureFavHKModel::rowCount(const QModelIndex &parent) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s, CHomeConfigureFavHKModel::rowCount : %d ", __FUNCTION__, m_liConfigureFavHKList.count());
    Q_UNUSED(parent)
    return m_liConfigureFavHKList.count();
}

QVariant CHomeConfigureFavHKModel::data(const QModelIndex &iIndex, int iRole) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    QVariant objData = QVariant();
    int iRow = iIndex.row();
    if (iRow < 0 || iRow >=  m_liConfigureFavHKList.count())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_HOME,"CHomeConfigureFavHKModel::data, invalid row: %d", iRow);
    }
    else
    {
        switch(iRole)
        {
        case FAV_HK_ID:
            objData = m_liConfigureFavHKList[iRow]->m_eFavHKId;
            break;
        case FAV_HK_SHORTCUT_ID:
            objData = m_liConfigureFavHKList[iRow]->m_eFavHKShortcutId;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_HOME,"CHomeConfigureFavHKModel::data, invalid role: %d", iRole);
            break;
        }
    }
    return objData;
}

QHash<int, QByteArray> CHomeConfigureFavHKModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[FAV_HK_ID] = "FavHKId";
    roles[FAV_HK_SHORTCUT_ID] = "FavHKShortcutId";
    return roles;
}

void CHomeConfigureFavHKModel::removeRows()
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_liConfigureFavHKList.clear();
    endRemoveRows();
}

void CHomeConfigureFavHKModel::insertRows(SConfigureFavHKData *pSConfigureFavHKData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_HOME, "%s", __FUNCTION__);
    beginInsertRows(QModelIndex() , m_liConfigureFavHKList.count(), m_liConfigureFavHKList.count());
    m_liConfigureFavHKList << pSConfigureFavHKData;
    endInsertRows();
}



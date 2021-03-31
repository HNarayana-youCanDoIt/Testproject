#include "CSoundDemoModel.h"
#include "HMIIncludes.h"


CSoundDemoModel::CSoundDemoModel(QObject *pParent)
    :QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    m_listData.clear();
}

CSoundDemoModel::~CSoundDemoModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    m_listData.clear();
}

int CSoundDemoModel::rowCount(const QModelIndex &parent) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    Q_UNUSED(parent);
    return m_listData.count();
}

QVariant CSoundDemoModel::data(const QModelIndex &index, int role) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    QVariant result{};
    int iRowIndex = index.row();

    if(iRowIndex >= 0 && iRowIndex < m_listData.count())
    {
        switch(role)
        {
            case ITEM_ID_ROLE:
                result = m_listData[iRowIndex].m_iId;
                break;
            case ITEM_TRACKID_ROLE:
                result = m_listData[iRowIndex].m_iTrackId;
                break;
            case ITEM_CAPTION_ROLE:
                result = m_listData[iRowIndex].m_strCaption;
                break;
            case ITEM_IMAGE_ROLE:
                result = m_listData[iRowIndex].m_strImagePath;
                break;
            case ITEM_MIN_VAL_ROLE:
                result = m_listData[iRowIndex].m_iMinValue;
                break;
            case ITEM_CURR_VAL_ROLE:
                result = m_listData[iRowIndex].m_iCurrentValue;
                break;
            case ITEM_MAX_VAL_ROLE:
                result = m_listData[iRowIndex].m_iMaxValue;
                break;
            case ITEM_ACTIVE_ROLE:
                result = m_listData[iRowIndex].m_bActive;
                break;
            case ITEM_ENABLED_ROLE:
                result = m_listData[iRowIndex].m_bEnabled;
                break;
            case ITEM_PGBVISIBILITY_ROLE:
                result = m_listData[iRowIndex].m_bPgbVisibility;
                break;
            default:
                LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s: incorrect role %d received.", __FUNCTION__, role);
                break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s: incorrect index %d received.", __FUNCTION__, iRowIndex);
    }
    return result;
}

QHash<int, QByteArray> CSoundDemoModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);

    QHash<int, QByteArray>              roles;
    roles[ITEM_ID_ROLE]                 = "itemIdRole";
    roles[ITEM_TRACKID_ROLE]            = "itemTrackIdRole";
    roles[ITEM_CAPTION_ROLE]            = "itemCaptionRole";
    roles[ITEM_IMAGE_ROLE]              = "itemImageRole";
    roles[ITEM_MIN_VAL_ROLE]            = "itemMinValRole";
    roles[ITEM_CURR_VAL_ROLE]           = "itemCurrValRole";
    roles[ITEM_MAX_VAL_ROLE]            = "itemMaxValRole";
    roles[ITEM_ACTIVE_ROLE]             = "itemActiveRole";
    roles[ITEM_ENABLED_ROLE]            = "itemEnabledRole";
    roles[ITEM_PGBVISIBILITY_ROLE]      = "itemPgbVisibilityRole";

    return roles;
}

void CSoundDemoModel::removeRows()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    beginRemoveRows(QModelIndex(), 0, m_listData.count());
    m_listData.clear();
    endRemoveRows();
}

void CSoundDemoModel::insertRows(const SSoundDemoData &rowData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    SSoundDemoData          data;
    data.m_iId              = rowData.m_iId;
    data.m_iTrackId         = rowData.m_iTrackId;
    data.m_strCaption       = rowData.m_strCaption;
    data.m_strImagePath     = rowData.m_strImagePath;
    data.m_iMinValue        = rowData.m_iMinValue;
    data.m_iCurrentValue    = rowData.m_iCurrentValue;
    data.m_iMaxValue        = rowData.m_iMaxValue;
    data.m_bActive          = rowData.m_bActive;
    data.m_bEnabled         = rowData.m_bEnabled;
    data.m_bPgbVisibility   = rowData.m_bPgbVisibility;

    m_listData.append(data);
    endInsertRows();
}

bool CSoundDemoModel::updateRowData(int index, const QVariant &value, int role)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s", __FUNCTION__);

    bool result= {false};

    if(index >= 0 && index < m_listData.count())
    {
        result = true;
        switch(role)
        {
            case ITEM_CAPTION_ROLE:
                m_listData[index].m_strCaption = value.toString();
                break;
            case ITEM_IMAGE_ROLE:
                m_listData[index].m_strImagePath = value.toString();
                break;
            case ITEM_MIN_VAL_ROLE:
                m_listData[index].m_iMinValue = value.toInt();
                break;
            case ITEM_CURR_VAL_ROLE:
                m_listData[index].m_iCurrentValue = value.toInt();
                break;
            case ITEM_MAX_VAL_ROLE:
                m_listData[index].m_iMaxValue = value.toInt();
                break;
            case ITEM_ACTIVE_ROLE:
                m_listData[index].m_bActive = value.toBool();
                break;
            case ITEM_ENABLED_ROLE:
                m_listData[index].m_bEnabled = value.toBool();
                break;
            case ITEM_PGBVISIBILITY_ROLE:
                m_listData[index].m_bPgbVisibility = value.toBool();
                break;
            default:
                LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s: incorrect role %d received.", __FUNCTION__, role);
                result = false;
                break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SOUNDDEMO, "%s: incorrect index %d received.", __FUNCTION__, index);
    }

    QModelIndex modelIndex = createIndex(index, 0);
    emit dataChanged(modelIndex, modelIndex);
    return result;
}

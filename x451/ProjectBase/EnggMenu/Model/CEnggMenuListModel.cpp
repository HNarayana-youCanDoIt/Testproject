#include "CEnggMenuListModel.h"
#include "logging.h"

CEnggMenuListModel::CEnggMenuListModel(QObject *parent): QAbstractListModel(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
}

CEnggMenuListModel::~CEnggMenuListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s", __FUNCTION__);
    resetList();
}

int CEnggMenuListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s , count: %d", __FUNCTION__, m_listEnggMenuData.count());
    return m_listEnggMenuData.count();
}

QVariant CEnggMenuListModel::data(const QModelIndex &index, int iRole) const
{
    int iModelIndex = index.row();

    QVariant objRowData;
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Index : %d , Role: %d", __FUNCTION__,iModelIndex,iRole);

    if (iModelIndex >= 0 || iModelIndex < m_listEnggMenuData.count())
    {
        switch (iRole)
        {
        case ENGG_MENU_ITEM_MAIN_TEXT_ROLE:
        {
            objRowData = m_listEnggMenuData[iModelIndex].m_strEnggMenuItemMainText;
        }
            break;
        case ENGG_MENU_ITEM_TYPE_ROLE:
        {
            objRowData = m_listEnggMenuData[iModelIndex].m_eEnggMenuItemType;
        }
            break;
        case ENGG_MENU_ITEM_ID_ROLE:
        {
            objRowData = m_listEnggMenuData[iModelIndex].m_iEnggMenuItemId;
        }
            break;
        case ENGG_MENU_ITEM_STATUS_ROLE:
        {
            objRowData = m_listEnggMenuData[iModelIndex].m_bEnggMenuItemStatus;
        }
            break;
        case ENGG_MENU_ITEM_SUB_TEXT_ROLE:
        {
            objRowData = m_listEnggMenuData[iModelIndex].m_strEnggMenuItemSubTitle;
        }
            break;
        case ENGG_MENU_ITEM_ENABLE_STATUS_ROLE:
        {
            objRowData = m_listEnggMenuData[iModelIndex].m_bEnggMenuItemEnableStatus;
        }
            break;
        default:
        {
            LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s ,Role Out of Scope! Role: %d", __FUNCTION__,iRole);
        }
            break;
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iModelIndex:%d Not defined in list", __FUNCTION__, iModelIndex);
    }
    return objRowData;
}

void CEnggMenuListModel::addItem(const CEnggMenuData &objEnggMenuModelData)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Count %d ", __FUNCTION__, m_listEnggMenuData.count());
    if (m_mapEnggMenuDataElementIndex.contains(objEnggMenuModelData.m_iEnggMenuItemId))
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: Element ID:%d already added in list", __FUNCTION__, objEnggMenuModelData.m_iEnggMenuItemId);
    }
    else
    {
        beginInsertRows(QModelIndex(), m_listEnggMenuData.count(), m_listEnggMenuData.count());
        m_listEnggMenuData.append(objEnggMenuModelData);
        endInsertRows();
        m_mapEnggMenuDataElementIndex[objEnggMenuModelData.m_iEnggMenuItemId] = (m_listEnggMenuData.count() - 1);
    }
}

void CEnggMenuListModel::resetList()
{
    beginResetModel();
    m_listEnggMenuData.clear();
    endResetModel();
    m_mapEnggMenuDataElementIndex.clear();
}

QHash<int, QByteArray> CEnggMenuListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: count: %d", __FUNCTION__, m_listEnggMenuData.count());
    QHash<int, QByteArray> roles;
    roles[ENGG_MENU_ITEM_MAIN_TEXT_ROLE] = "enggMenuItemMainTextRole";
    roles[ENGG_MENU_ITEM_TYPE_ROLE] = "enggMenuItemTypeRole";
    roles[ENGG_MENU_ITEM_ID_ROLE]="enggMenuItemIdRole";
    roles[ENGG_MENU_ITEM_STATUS_ROLE]="enggMenuItemStatusRole";
    roles[ENGG_MENU_ITEM_SUB_TEXT_ROLE]="enggMenuItemSubTextRole";
    roles[ENGG_MENU_ITEM_ENABLE_STATUS_ROLE] = "enggMenuItemEnableStatusRole";
    return roles;
}

void CEnggMenuListModel::updateEnggMenuModel(int iListItemID, const QVariant &value, int iRole)
{
    LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iListItemID: %d,role : %d, Value: %s ", __FUNCTION__ , iListItemID ,iRole, value.toString().toStdString().c_str());
    if (m_mapEnggMenuDataElementIndex.contains(iListItemID))
    {
        int iIndex = m_mapEnggMenuDataElementIndex[iListItemID];
        if ((iIndex >= 0) && (iIndex < m_listEnggMenuData.count()))
        {
            switch(iRole)
            {
            case ENGG_MENU_ITEM_STATUS_ROLE:
            {
                m_listEnggMenuData[iIndex].m_bEnggMenuItemStatus = value.toBool();
            }
                break;
            case ENGG_MENU_ITEM_ENABLE_STATUS_ROLE:
            {
                m_listEnggMenuData[iIndex].m_bEnggMenuItemEnableStatus = value.toBool();
            }
                break;
            case ENGG_MENU_ITEM_MAIN_TEXT_ROLE:
            {
                m_listEnggMenuData[iIndex].m_strEnggMenuItemMainText = value.toString();
            }
                break;
            case ENGG_MENU_ITEM_SUB_TEXT_ROLE:
            {
                m_listEnggMenuData[iIndex].m_strEnggMenuItemSubTitle = value.toString();
            }
                break;
            default:
            {
                LOG_INFO(Log::e_LOG_CONTEXT_ENGG_MENU,"%s ,Default Case", __FUNCTION__);
            }
                break;
            }
            /* Refreshing the qml's data for the index which is changed */
            const QModelIndex &objLeftIndex = createIndex(iIndex, 0);
            const QModelIndex &objRightIndex = createIndex(iIndex, 0);
            emit dataChanged(objLeftIndex, objRightIndex);
        }
        else
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iIndex:%d not available in list  for iListItemID:%d", __FUNCTION__, iIndex,iListItemID);
        }
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_ENGG_MENU, "%s: iListItemID:%d not added in list", __FUNCTION__, iListItemID);
    }
}


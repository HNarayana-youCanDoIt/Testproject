/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CSetupListModel.cpp
 * @ingroup       HMIComponent
 * @author        Harish Kunisetty
 * CSetupListModel.cpp, setup list model class source file, responsible for creating generic list of setup screen which has static model.
 */

#include "CSetupListModel.h"
#include "CThemeManagerEnums.h"

CSetupListModel::CSetupListModel(QObject *parent):
    QAbstractListModel(parent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
}

CSetupListModel::~CSetupListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    m_SetupDataList.clear();
}

int CSetupListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_SetupDataList.count();
}

QVariant CSetupListModel::data(const QModelIndex &index, int role) const
{
    QVariant data = QVariant();
    int row = index.row();
    if (row < 0 || row >= rowCount())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, invalid row: %d", __FUNCTION__, row);
    }
    else
    {
        switch(role)
        {
        case ListItemNameRole:
            data = m_SetupDataList[row].m_sListItemName;
            break;
        case ListItemTypeRole:
            data = m_SetupDataList[row].m_sListItemType;
            break;
        case ListItemEnabledRole:
            data = m_SetupDataList[row].m_bIsListItemEnabled;
            break;
        case ListItemDefaultImageRole:
            data = m_SetupDataList[row].m_sListItemDefaultImage;
            break;
        case ListItemSelectedImageRole:
            data = m_SetupDataList[row].m_strListItemSelectedImage;
            break;
        case ListItemCollapsedRole:
            data = m_SetupDataList[row].m_bIsListItemCollapsed;
            break;
        case ListItemCheckedRole:
            data = m_SetupDataList[row].m_bListItemChecked;
            break;
        case ListItemValueRole:
            data = m_SetupDataList[row].m_iListItemValue;
            break;
        case ListItemMinValue:
            data = m_SetupDataList[row].m_iListItemMinValue;
            break;
        case ListItemMaxValue:
            data = m_SetupDataList[row].m_iListItemMaxValue;
            break;
        case ListItemIndexRole:
            data = m_SetupDataList[row].m_eListItemIndex;
            break;
        case ListItemDistributionModeImageRole:
            data = m_SetupDataList[row].m_strDistributionModeImage;
            break;
        case ListItemFanSpeedImageRole:
            data = m_SetupDataList[row].m_strFanSpeedImage;
            break;
        case ListItemFanSpeedValue:
            data = m_SetupDataList[row].m_iFanSpeedValue;
            break;
        case ListItemTemperatureValue:
            data = m_SetupDataList[row].m_fTemperatureValue;
            break;
        case ListItemClimateIconsVisibilityStatus:
            data = m_SetupDataList[row].m_bClimateIconsVisiblityStatus;
            break;
        case ListItemThemeColorVisibility:
            data = m_SetupDataList[row].m_bThemeColorVisibilty;
            break;
        case ListItemThemeSoundVisibility:
            data = m_SetupDataList[row].m_bThemeSoundVisibilty;
            break;
        case ListItemThemeLoadingStatus:
            data = m_SetupDataList[row].m_bThemeLoadingStatus;
            break;
        case ListItemIdRole:
            data = m_SetupDataList[row].m_iItemId;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: role: %d", __FUNCTION__, role);
            break;
        }
    }
    return data;
}

bool CSetupListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : Role:%d, Index:%d ", __FUNCTION__, role, index.row());
    bool bReturnValue = false;
    switch (role)
    {
    case ListItemCollapsedRole:
    {
        m_SetupDataList[index.row()].m_bIsListItemCollapsed = value.toBool();
        emit dataChanged(index, index);
        bReturnValue = true;
    }
        break;
    case ListItemCheckedRole:
    {
        m_SetupDataList[index.row()].m_bListItemChecked = value.toBool();
        emit dataChanged(index, index);
        bReturnValue = true;
    }
        break;

    default:
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s default case", __FUNCTION__ );
    }
        break;
    }
    return bReturnValue;
}

QHash<int, QByteArray> CSetupListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[ListItemIndexRole] = "listItemIndexRole";
    roles[ListItemNameRole] = "listItemNameRole";
    roles[ListItemTypeRole] = "listItemTypeRole";
    roles[ListItemEnabledRole] = "isListItemEnabledRole";
    roles[ListItemSelectedImageRole] = "listItemSelectedImageRole";
    roles[ListItemDefaultImageRole] = "listItemDefaultImageRole";
    roles[ListItemCollapsedRole] = "isListItemCollapsedRole";
    roles[ListItemCheckedRole] = "listItemCheckedRole";
    roles[ListItemValueRole] = "listItemValueRole";
    roles[ListItemMinValue] = "listItemMinValueRole";
    roles[ListItemMaxValue] = "listItemMaxValueRole";
    roles[ListItemDistributionModeImageRole] = "listItemDistributionModeImageRole";
    roles[ListItemFanSpeedImageRole] = "listItemFanSpeedImageRole";
    roles[ListItemFanSpeedValue] = "listItemFanSpeedValue";
    roles[ListItemTemperatureValue] = "listItemTemperatureValue";
    roles[ListItemClimateIconsVisibilityStatus] = "listItemClimateIconsVisibilityStatus";
    roles[ListItemThemeColorVisibility] = "listItemThemeColorVisibility";
    roles[ListItemThemeSoundVisibility] = "listItemThemeSoundVisibility";
    roles[ListItemThemeLoadingStatus] = "listItemThemeLoadingStatus";
    roles[ListItemIdRole] = "listItemIdRole";
    return roles;
}

void CSetupListModel::addDataToModel(const CSetupData& objSetupData)
{
    m_SetupDataList.append(objSetupData);
}

void CSetupListModel::updateThemeColor(const QVariant& objValue, int& iListItemIndex)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s", __FUNCTION__ );
    switch (objValue.toInt())
    {
    case CThemeManagerEnums::THEME_TYPE_1:
        m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#2b74c3";
        break;
    case CThemeManagerEnums::THEME_TYPE_2:
        m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#c32b2b";
        break;
//As per TML, green colour theme should be removed
//            case CThemeManagerEnums::THEME_TYPE_3:
//                m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#2bc393";
//                break;
    case CThemeManagerEnums::THEME_TYPE_4:
        m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#f7913d";
        break;
    case CThemeManagerEnums::THEME_TYPE_5:
        m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#ac245e";
        break;
    default:
        m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#2b74c3";
        break;
    }
}

void CSetupListModel::updateThemeSetupModelData(int iRole, int iListItemIndex, const QVariant& objValue, CSetupEnums::ESetupScreens eSetupListOption)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Index: %d, Role: %d, objValue: %s, eSetupListOption: %d", __FUNCTION__ ,
             iListItemIndex, iRole, objValue.toString().toStdString().c_str(), eSetupListOption);

    if ((iListItemIndex >= 0) && (iListItemIndex < m_SetupDataList.count()))
    {
        switch(iRole)
        {
        case ListItemSelectedImageRole:
            updateThemeColor(objValue, iListItemIndex);
            break;

        case ListItemFanSpeedValue:
            m_SetupDataList[iListItemIndex].m_iFanSpeedValue = objValue.toInt();
            break;

        case ListItemTemperatureValue:
            m_SetupDataList[iListItemIndex].m_fTemperatureValue = objValue.toFloat();
            break;

        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,Default Case", __FUNCTION__);
            break;
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s , Invalid index: %d, list item count: %d", __FUNCTION__, iListItemIndex, m_SetupDataList.count());
    }
}

void CSetupListModel::updateSetupModelData(int iRole, int iListItemIndex, const QVariant& objValue, CSetupEnums::ESetupScreens eSetupListOption)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Index: %d, Role: %d, objValue: %s, eSetupListOption: %d", __FUNCTION__ ,
             iListItemIndex, iRole, objValue.toString().toStdString().c_str(), eSetupListOption);

    if ((iListItemIndex >= 0) && (iListItemIndex < m_SetupDataList.count()))
    {
        switch(iRole)
        {
        case ListItemEnabledRole:
            m_SetupDataList[iListItemIndex].m_bIsListItemEnabled = objValue.toBool();
            break;

        case ListItemCheckedRole:

            for(int row = 0; row < m_SetupDataList.size(); ++row)
            {
                /*Note: Here this condition is used to check for a particular list model where radio buttons are grouped
               *  and refresh the group to false before setting the actual value */
                if( (eSetupListOption != -1) && (m_SetupDataList[row].m_eListItemIndex == eSetupListOption) &&
                        (m_SetupDataList[row].m_sListItemType == CSetupEnums::SETUP_LIST_ITEM_RADIO_BUTTON))
                {
                    m_SetupDataList[row].m_bListItemChecked = false;
                }
                else
                {
                    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s:Do Nothing %d", __FUNCTION__, row)
                }
            }

            m_SetupDataList[iListItemIndex].m_bListItemChecked = objValue.toBool();
            break;

        case ListItemNameRole:
            m_SetupDataList[iListItemIndex].m_sListItemName = objValue.toString();
            break;

        case ListItemValueRole:
            m_SetupDataList[iListItemIndex].m_iListItemValue = objValue.toInt();
            break;

        case ListItemFanSpeedValue:
            m_SetupDataList[iListItemIndex].m_iFanSpeedValue = objValue.toInt();
            break;

        case ListItemTemperatureValue:
            m_SetupDataList[iListItemIndex].m_fTemperatureValue = objValue.toFloat();
            break;

        case ListItemThemeLoadingStatus:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ListItemThemeLoadingStatus", __FUNCTION__);
            m_SetupDataList[iListItemIndex].m_bThemeLoadingStatus = objValue.toBool();
            break;

        case ListItemDistributionModeImageRole:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ListItemDistributionModeImageRole", __FUNCTION__);
            switch(objValue.toInt()) {
            case CSetupEnums::SETUP_THEME_PRESETS_HVAC_DM_CHEST_MODE:
                m_SetupDataList[iListItemIndex].m_strDistributionModeImage = "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Ico_Climate_mod_3_n.png";
                break;
            case CSetupEnums::SETUP_THEME_PRESETS_HVAC_DM_CHESTLEG_MODE:
                m_SetupDataList[iListItemIndex].m_strDistributionModeImage = "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Ico_Climate_mod_1_n.png";
                break;
            case CSetupEnums::SETUP_THEME_PRESETS_HVAC_DM_LEG_MODE:
                m_SetupDataList[iListItemIndex].m_strDistributionModeImage = "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Ico_Climate_mod_2_n.png";
                break;
            case CSetupEnums::SETUP_THEME_PRESETS_HVAC_DM_LEGDEFROST_MODE:
                m_SetupDataList[iListItemIndex].m_strDistributionModeImage = "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Ico_Climate_mod_4_n.png";
                break;
            case CSetupEnums::SETUP_THEME_PRESETS_HVAC_DM_DEFROST_MODE:
                m_SetupDataList[iListItemIndex].m_strDistributionModeImage = "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Ico_Climate_mod_5_n.png";
                break;
            default:
                m_SetupDataList[iListItemIndex].m_strDistributionModeImage = "qrc:/image/Themes/Set_Ico_sClimate_7in_n-assets/Set_Ico_Climate_mod_3_n.png";
                break;
            }
            break;

            /*ToDo: Create one private function and write this code there*/
        case ListItemSelectedImageRole:
            switch (objValue.toInt()) {
            case CThemeManagerEnums::THEME_TYPE_1:
                m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#2b74c3";
                break;
            case CThemeManagerEnums::THEME_TYPE_2:
                m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#c32b2b";
                break;
                //As per TML, green colour theme should be removed
                //            case CThemeManagerEnums::THEME_TYPE_3:
                //                m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#2bc393";
                //                break;
            case CThemeManagerEnums::THEME_TYPE_4:
                m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#f7913d";
                break;
            case CThemeManagerEnums::THEME_TYPE_5:
                m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#ac245e";
                break;
            default:
                m_SetupDataList[iListItemIndex].m_strListItemSelectedImage = "#2b74c3";
                break;
            }
            break;

        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,Default Case", __FUNCTION__);
            break;
        }

        /* Refreshing the qml's data for the index which is changed */
        const QModelIndex& objLeftIndex = createIndex(iListItemIndex, 0);
        const QModelIndex& objRightIndex = createIndex(iListItemIndex, 0);
        emit dataChanged(objLeftIndex, objRightIndex);
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,Invalid index: %d, list item count: %d", __FUNCTION__, iListItemIndex, m_SetupDataList.count());
    }
}

void CSetupListModel::insertElementAt(int iRow, const CSetupData &objSetupListModel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Row : %d", __FUNCTION__, iRow);
    beginInsertRows(QModelIndex(), iRow, iRow);
    m_SetupDataList.insert(iRow, objSetupListModel);
    endInsertRows();
}

void CSetupListModel::removeElementAt(int iRow)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Row : %d", __FUNCTION__, iRow);
    beginRemoveRows(QModelIndex(), iRow, iRow);
    m_SetupDataList.removeAt(iRow);
    endRemoveRows();
}

void CSetupListModel::insertRows(const CSetupData &objSetupListModel)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: ", __FUNCTION__);
    beginInsertRows(QModelIndex() , rowCount(), rowCount());
    m_SetupDataList.append(objSetupListModel);
    endInsertRows();
}

void CSetupListModel::removeRows()
{
    LOG_INFO(Log::e_LOG_CONTEXT_TUNER,__FUNCTION__);
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_SetupDataList.clear();
    endRemoveRows();
}

CSetupData CSetupListModel::elementAt(int iIndex)
{
    CSetupData data;
    if( (0 <= iIndex)  && (iIndex < m_SetupDataList.size()))
    {
        data = m_SetupDataList.at(iIndex);
    }
    else
    {
        LOG_WARNING(Log::e_LOG_CONTEXT_TUNER, "%s, Index out of range iIndex:%d", __FUNCTION__, iIndex);
    }
    return data;
}

int CSetupListModel::findIndexForRequiredRole(int iRole, const QVariant &value)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);
    int iResultIndex = -1;

    if(m_SetupDataList.count() < 1)
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: m_SetupDataList is Empty", __FUNCTION__);
    }
    else
    {
        switch(iRole)
        {
        case ListItemNameRole:
        {
            for(int iIndex = 0; iIndex < m_SetupDataList.count() ; iIndex++)
            {
                if((m_SetupDataList[iIndex].m_sListItemName) == value.toString())
                {
                    iResultIndex = iIndex;
                    break;
                }
            }

            break;
        }
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Default Case: No Role Found", __FUNCTION__);
            break;
        }
    }
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s: Index Returned: %d", __FUNCTION__, iResultIndex);
    return iResultIndex;
}

void CSetupListModel::updateData(int iIndex, const QVariant &value, CSetupListModel::ESetupRoles eRole)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s iIndex:%d, value:%s, eRole:%d", __FUNCTION__, iIndex, value.toString().toStdString().data(), static_cast<int>(eRole));
    if ((iIndex >=0) && (iIndex < m_SetupDataList.count()))
    {
        switch(eRole)
        {
        case CSetupListModel::ESetupRoles::ListItemEnabledRole:
        {
            m_SetupDataList[iIndex].m_bIsListItemEnabled = value.toBool();
        }
            break;
        case CSetupListModel::ESetupRoles::ListItemValueRole:
        {
            m_SetupDataList[iIndex].m_iListItemValue = value.toInt();
        }
            break;
        default:
        {
            LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s: unhandled eRole:%d", __FUNCTION__, static_cast<int>(eRole));
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
        LOG_WARNING(Log::e_LOG_CONTEXT_SETTINGS,"%s: invalid index given iIndex:%d", __FUNCTION__, iIndex);
    }
}

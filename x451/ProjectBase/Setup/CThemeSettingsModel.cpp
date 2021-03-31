/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2017
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file		  CThemeSettingsModel.h
 * @ingroup       HMIComponent
 * @author        Santosh Chakala
 * CThemeSettingsModel.h, theme settings list model file, responsible for creating theme preset static list model
 */
#include "CThemeSettingsModel.h"
#include "logging.h"

CThemeSettingsModel::CThemeSettingsModel(QObject *pParent)
     :QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,__FUNCTION__);

    m_objThemeSetupDataList.clear();
    m_objThemeSetupDataList.append(CSetupData("", "", "", "","", -1, -1, "false", "false", "false", "false", "false", CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, -1, "Zen", "qrc:/image/ZenPresets/Set_Ico_s2Zen_7in_n-assets/Set_Ico_s2Zenn_LeftSide.png", "qrc:/image/ZenPresets/Set_Ico_s2Zen_7in_n-assets/Set_Ico_s2Zen_na.png", "qrc:/image/ZenPresets/Set_Ico_s2Zen_7in_n-assets/Set_Ico_s2Zen_n_RightSide.png" ));
    m_objThemeSetupDataList.append(CSetupData("", "", "", "","", -1, -1, "false", "false", "false", "false", "false", CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, -1, "Zing", "qrc:/image/ZenPresets/Set_Ico_s3Zing_7in_n-assets/Set_Ico_s3Zing_n_LeftSide.png", "qrc:/image/ZenPresets/Set_Ico_s3Zing_7in_n-assets/Set_Ico_s3Zing_na.png", "qrc:/image/ZenPresets/Set_Ico_s3Zing_7in_n-assets/Set_Ico_s3Zing_n_LeftSide.png"));
    m_objThemeSetupDataList.append(CSetupData("", "", "", "","", -1, -1, "false", "false", "false", "false", "false", CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, -1, "Zeal", "qrc:/image/ZenPresets/Set_Ico_s4Zeel_7in_n-assets/Set_Ico_s4Zeel_n_LeftSide.png", "qrc:/image/ZenPresets/Set_Ico_s4Zeel_7in_n-assets/Set_Ico_s4Zeel_na.png", "qrc:/image/ZenPresets/Set_Ico_s4Zeel_7in_n-assets/Set_Ico_s4Zeel_nRightSide.png"));
    /*Note : This is commented because this preset may not be there.
      FixMe: Reomove this after confirmation from TML*/
    //    m_pThemeSetupDataList.append(new CSetupData("", "", "", "","", -1, -1, "false", "false", "false", "false", "false", CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, -1, "Harrier", "qrc:/image/ZenPresets/Set_Ico_s1Harrier_7in_n-assets/Set_Ico_s1Harrier_n_LeftSide.png", "qrc:/image/ZenPresets/Set_Ico_s1Harrier_7in_n-assets/Set_Ico_s1Harrier_na.png", "qrc:/image/ZenPresets/Set_Ico_s1Harrier_7in_n-assets/Set_Ico_s1Harrier_n_RightSide.png"));
    m_objThemeSetupDataList.append(CSetupData("", "", "", "","", -1, -1, "false", "false", "false", "false", "false", CSetupEnums::SETUP_LIST_ITEM_INVALID_TYPE, -1, "User", "qrc:/image/ZenPresets/Set_Ico_s6Custom_7in_n-assets/Set_Ico_s6Custom_n_LeftSide.png", "qrc:/image/ZenPresets/Set_Ico_s6Custom_7in_n-assets/Set_Ico_s6Custom_na.png", "qrc:/image/ZenPresets/Set_Ico_s6Custom_7in_n-assets/Set_Ico_s6Custom_RightSide.png"));
}

CThemeSettingsModel::~CThemeSettingsModel()
{
    m_objThemeSetupDataList.clear();
}

int CThemeSettingsModel::rowCount(const QModelIndex &parent) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, rowCount : %d ",__FUNCTION__, m_objThemeSetupDataList.count());
    Q_UNUSED(parent)
    return m_objThemeSetupDataList.count();
}

QVariant CThemeSettingsModel::data(const QModelIndex &iIndex, int iRole) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    QVariant objData = QVariant();
    int iRow = iIndex.row();
    if (iRow < 0 || iRow >=  m_objThemeSetupDataList.count())
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, invalid row: %d",__FUNCTION__, iRow);
    }
    else
    {
        switch(iRole)
        {
        case TAB_BAR_COMPONENT_NAME_ROLE:
            objData = m_objThemeSetupDataList[iRow].m_strName;
            break;
        case TAB_BAR_COMPONENT_LEFT_ICON_ROLE:
            objData = m_objThemeSetupDataList[iRow].m_strLeftIcon;
            break;
        case TAB_BAR_COMPONENT_MID_ICON_ROLE:
            objData = m_objThemeSetupDataList[iRow].m_strMidIcon;
            break;
        case TAB_BAR_COMPONENT_RIGHT_ICON_ROLE:
            objData = m_objThemeSetupDataList[iRow].m_strRightIcon;
            break;
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"CPhoneBrowseTabBarModel::data, invalid role: %d", iRole);
            break;
        }
    }
    return objData;
}

QHash<int, QByteArray> CThemeSettingsModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[TAB_BAR_COMPONENT_NAME_ROLE] = "name";
    roles[TAB_BAR_COMPONENT_LEFT_ICON_ROLE] = "leftIcon";
    roles[TAB_BAR_COMPONENT_MID_ICON_ROLE] = "midIcon";
    roles[TAB_BAR_COMPONENT_RIGHT_ICON_ROLE] = "rightIcon";
    return roles;
}


void CThemeSettingsModel::updateModel(int iIndex, const CSetupData &objThemeData)
{
    m_objThemeSetupDataList[iIndex].m_strName = objThemeData.m_strName;

    /* Refreshing the qml's data for the index which is changed */
        const QModelIndex &objLeftIndex = createIndex(iIndex, 0);
        const QModelIndex &objRightIndex = createIndex(iIndex, 0);
        emit dataChanged(objLeftIndex, objRightIndex);
}

CSetupData CThemeSettingsModel::getModelData(int iIndex)
{
    return m_objThemeSetupDataList[iIndex];
}

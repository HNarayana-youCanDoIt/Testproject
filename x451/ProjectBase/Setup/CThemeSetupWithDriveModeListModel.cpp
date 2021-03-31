
/*****************************************************************
 * Project        Harman Car Multimedia System
 * (c) copyright  2018
 * Company        Harman/Becker Automotive Systems GmbH
 *                All rights reserved
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/
/**
 * @file          CPhoneSetupListModel.cpp
 * @ingroup       HMIComponent
 * @author        Rahul Balyan
 * @brief         Contain implementation of all the methods declared in
 * CThemeSetupWithDriveModeListModel class
 */

#include "CThemeSetupWithDriveModeListModel.h"
#include "logging.h"
#include "CPersistencyAdaptor.h"
#include "CSetupAdaptor.h"

CThemeSetupWithDriveModeListModel::CThemeSetupWithDriveModeListModel(QObject *pParent) :
    QAbstractListModel(pParent)
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listThemeSetupWithDriveMode.clear();
    m_listThemes.clear();
    initThemeSetupWithDriveModeMainModel();
    initThemesModel();
}

CThemeSetupWithDriveModeListModel::~CThemeSetupWithDriveModeListModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    m_listThemeSetupWithDriveMode.clear();
    m_listThemes.clear();
}

/************************************************************************//**
 * @category    OVERRIDEN METHODS of QAbstractListModel class
 ************************************************************************/
QHash<int, QByteArray> CThemeSetupWithDriveModeListModel::roleNames() const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QHash<int, QByteArray> roles;
    roles[THEME_SETUP_ITEM_TEXT_ROLE]           = "itemTextRole";
    roles[THEME_SETUP_ITEM_ENABLED_ROLE]        = "itemEnabledRole";
    roles[THEME_SETUP_ITEM_CHECKED_ROLE]        = "itemCheckedRole";
    roles[THEME_SETUP_ITEM_TYPE_ROLE]           = "itemTypeRole";
    roles[THEME_SETUP_ITEM_ID_ROLE]             = "itemId";
    return roles;
}

QVariant CThemeSetupWithDriveModeListModel::data(const QModelIndex &index, int role) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, __FUNCTION__);
    QVariant objRowData;
    int iRowIndex = index.row();
    if (index.isValid())
    {
        EThemesSetupListRoles eThemesSetupRole = static_cast<EThemesSetupListRoles>(role);
        switch(eThemesSetupRole)
        {
        case THEME_SETUP_ITEM_TEXT_ROLE:
            objRowData = m_listThemeSetupWithDriveMode.at(iRowIndex).m_sListItemName;
            break;
        case THEME_SETUP_ITEM_ENABLED_ROLE:
            objRowData = m_listThemeSetupWithDriveMode.at(iRowIndex).m_bIsListItemEnabled;
            break;
        case THEME_SETUP_ITEM_CHECKED_ROLE:
            objRowData = m_listThemeSetupWithDriveMode.at(iRowIndex).m_bListItemChecked;
            break;
        case THEME_SETUP_ITEM_TYPE_ROLE:
            objRowData = m_listThemeSetupWithDriveMode.at(iRowIndex).m_sListItemType;
            break;
        case THEME_SETUP_ITEM_ID_ROLE:
            objRowData = m_listThemeSetupWithDriveMode.at(iRowIndex).m_iItemId;
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

int CThemeSetupWithDriveModeListModel::rowCount(const QModelIndex &parent) const
{
    LOG_INFO(Log::e_LOG_CONTEXT_PHONE, "%s: rowCount: %d", __FUNCTION__, m_listThemeSetupWithDriveMode.count());
    Q_UNUSED(parent);
    return m_listThemeSetupWithDriveMode.count();
}

void CThemeSetupWithDriveModeListModel::initThemeSetupWithDriveModeMainModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s",__FUNCTION__);

    bool bChangeThemeWithDriveModeStatus = static_cast<bool>(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_CHANGE_THEME_WITH_DRIVE_MODE_STATUS));

    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, bChangeThemeWithDriveModeStatus : %d", __FUNCTION__, bChangeThemeWithDriveModeStatus);
    m_listThemeSetupWithDriveMode.clear();

    m_listThemeSetupWithDriveMode.append(CSetupData(tr("TEXT_SETTING_DISPLAY_THEME_DRIVE_MODES"), CSetupEnums::SETUP_LIST_ITEM_DROP_DOWN, bChangeThemeWithDriveModeStatus, true, CSetupEnums::THEME_SETUP_WITH_DRIVE_MODE_CHANGE_THEME_WITH_DRIVE_MODE));

    m_listThemeSetupWithDriveMode.append(CSetupData(tr("TEXT_SETTINGS_THEMES"), CSetupEnums::SETUP_LIST_ITEM_DROP_DOWN, false, !bChangeThemeWithDriveModeStatus, CSetupEnums::THEME_SETUP_WITH_DRIVE_MODE_THEMES));

}

void CThemeSetupWithDriveModeListModel::initThemesModel()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, __FUNCTION__);

    CSetupEnums::EThemesItem eThemeSelection = static_cast<CSetupEnums::EThemesItem>(CPersistencyAdaptor::getInstance().readIntData(EPersistencyKeys::HMI_PCL_I_HMI_THEME_SELECTION));

    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, eThemeSelection : %d", __FUNCTION__, eThemeSelection);
    m_listThemes.clear();

    m_listThemes.append(CSetupData(tr("TEXT_SETUP_DISPLAY_THEME_1"), CSetupEnums::SETUP_LIST_ITEM_THEME_RADIO_BUTTON, (eThemeSelection == CSetupEnums::THEME_ONE), true, CSetupEnums::THEME_ONE));

    m_listThemes.append(CSetupData(tr("TEXT_SETUP_DISPLAY_THEME_2"), CSetupEnums::SETUP_LIST_ITEM_THEME_RADIO_BUTTON, (eThemeSelection == CSetupEnums::THEME_TWO), true, CSetupEnums::THEME_TWO));

    m_listThemes.append(CSetupData(tr("TEXT_SETUP_DISPLAY_THEME_3"), CSetupEnums::SETUP_LIST_ITEM_THEME_RADIO_BUTTON, (eThemeSelection == CSetupEnums::THEME_THREE), true, CSetupEnums::THEME_THREE));

    m_listThemes.append(CSetupData(tr("TEXT_SETUP_DISPLAY_THEME_4"), CSetupEnums::SETUP_LIST_ITEM_THEME_RADIO_BUTTON, (eThemeSelection == CSetupEnums::THEME_FOUR), true, CSetupEnums::THEME_FOUR));
    //As per comments from TML only 4 colors are to be supported.
    //m_listThemes.append(CSetupData(tr("TEXT_SETUP_DISPLAY_THEME_5"), CSetupEnums::SETUP_LIST_ITEM_THEME_RADIO_BUTTON, (eThemeSelection == CSetupEnums::THEME_FIVE), true, CSetupEnums::THEME_FIVE));

}

bool CThemeSetupWithDriveModeListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s : Role:%d, Index:%d ", __FUNCTION__, role, index.row());
    bool bReturnValue = false;
    if(index.isValid())
    {
        int iRowIndex = index.row();
        switch(role)
        {
        case THEME_SETUP_ITEM_TEXT_ROLE:
        {
            const QString &strItemText = value.toString();
            if(strItemText.compare(m_listThemeSetupWithDriveMode[iRowIndex].m_sListItemName) != 0)
            {
                m_listThemeSetupWithDriveMode[iRowIndex].m_sListItemName = strItemText;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "Theme Setup Item text not changed");

            }
        }
            break;

        case THEME_SETUP_ITEM_TYPE_ROLE:
        {
            CSetupEnums::ESetupListItemTypes eItemType = static_cast<CSetupEnums::ESetupListItemTypes>(value.toInt());
            if(eItemType != m_listThemeSetupWithDriveMode[iRowIndex].m_sListItemType)
            {
                m_listThemeSetupWithDriveMode[iRowIndex].m_sListItemType = eItemType;
                bReturnValue  = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "Theme Setup Item type not changed");
            }
        }

            break;

        case THEME_SETUP_ITEM_ENABLED_ROLE:
        {
            bool bItemEnabled = value.toBool();
            if(bItemEnabled != m_listThemeSetupWithDriveMode[iRowIndex].m_bIsListItemEnabled)
            {
                m_listThemeSetupWithDriveMode[iRowIndex].m_bIsListItemEnabled = bItemEnabled;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "Theme Setup Item enabled not changed");
            }
        }
            break;

        case THEME_SETUP_ITEM_ID_ROLE:
        {

            int iItemId = value.toInt();
            if(iItemId != m_listThemeSetupWithDriveMode[iRowIndex].m_iItemId)
            {
                m_listThemeSetupWithDriveMode[iRowIndex].m_iItemId = iItemId;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, " Theme Setup Item ID role not changed");

            }
        }
            break;

        case THEME_SETUP_ITEM_CHECKED_ROLE:
        {

            bool bItemChecked = value.toBool();
            if(bItemChecked != m_listThemeSetupWithDriveMode[iRowIndex].m_bListItemChecked)
            {
                m_listThemeSetupWithDriveMode[iRowIndex].m_bListItemChecked = bItemChecked;
                bReturnValue = true;
            }
            else
            {
                LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "Theme Setup Item checked not changed");

            }
        }
        default:
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,Default Case", __FUNCTION__);
            break;
        }

        if(bReturnValue)
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "Model Value Changed");
            emit dataChanged(index, index);
        }
        else
        {
            LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "item role data is not changed");
        }
    }
    else
    {
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s ,Index Out of Scope!", __FUNCTION__);
    }

    return bReturnValue;

}

void CThemeSetupWithDriveModeListModel::invExpandThemesDropdown()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);

    if(!m_listThemeSetupWithDriveMode[CSetupEnums::THEME_SETUP_WITH_DRIVE_MODE_THEMES].m_bListItemChecked)
    {
        updateThemesList();
        beginInsertRows(QModelIndex(), 2,
                        (m_listThemes.count() + 1));

        for (int i = 0; i < m_listThemes.count(); i++)
        {
            m_listThemeSetupWithDriveMode.insert((2 + i), m_listThemes.at(i));
        }

        endInsertRows();
        setData(index(CSetupEnums::THEME_SETUP_WITH_DRIVE_MODE_THEMES, 0), true, EThemesSetupListRoles::THEME_SETUP_ITEM_CHECKED_ROLE);
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, Insertion Successful", __FUNCTION__);
    }
}

void CThemeSetupWithDriveModeListModel::invCollapseThemesDropdown()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s", __FUNCTION__);

    if(m_listThemeSetupWithDriveMode[CSetupEnums::THEME_SETUP_WITH_DRIVE_MODE_THEMES].m_bListItemChecked)
    {
        beginRemoveRows(QModelIndex(), 2,
                        (m_listThemes.count() + 1));

        for (int i = 0; i < m_listThemes.count(); i++)
        {
            m_listThemeSetupWithDriveMode.removeAt(2);
        }

        endRemoveRows();
        setData(index(CSetupEnums::THEME_SETUP_WITH_DRIVE_MODE_THEMES, 0), false, EThemesSetupListRoles::THEME_SETUP_ITEM_CHECKED_ROLE);
        updateThemesList();
        LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS,"%s, theme list Items deletion Successful", __FUNCTION__);
    }
}

void CThemeSetupWithDriveModeListModel::invToggleChangeThemeWithDriveMode(bool bToggleBtnStatus)
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s, bToggleBstnStatus : %d", __FUNCTION__, bToggleBtnStatus);

    setData(index(CSetupEnums::THEME_SETUP_WITH_DRIVE_MODE_THEMES, 0), bToggleBtnStatus, EThemesSetupListRoles::THEME_SETUP_ITEM_ENABLED_ROLE);

    setData(index(CSetupEnums::THEME_SETUP_WITH_DRIVE_MODE_CHANGE_THEME_WITH_DRIVE_MODE, 0), !bToggleBtnStatus, EThemesSetupListRoles::THEME_SETUP_ITEM_CHECKED_ROLE);
    CVariantControlEnum::EVIP_DID eVIP_DID = CVariantControlAdaptor::getInstance()->eolVIP_DID();
    LOG_INFO(Log::e_LOG_CONTEXT_VOICE_ALERTS, "%s: eVIP_DID: %d", __FUNCTION__, eVIP_DID);
    if (CVariantControlEnum::VIP_DID_HU_NEXON_LEVEL_B_VAVE == eVIP_DID || CVariantControlEnum::VIP_DID_HU_NEXON_MCE == eVIP_DID)
    {
        CSetupAdaptor::getInstance()->setChangeThemeWithDriveModeStatus(!bToggleBtnStatus);
    }
}

void CThemeSetupWithDriveModeListModel::updateThemesList()
{
    LOG_INFO(Log::e_LOG_CONTEXT_SETTINGS, "%s current theme color: %d", __FUNCTION__, CSetupAdaptor::getInstance()->getCurrentTheme());
    CSetupEnums::EThemesItem eCurrentTheme = CSetupAdaptor::getInstance()->getCurrentTheme();

    for(int i = 0; i < m_listThemes.count(); i++)
    {
        m_listThemes[i].m_bListItemChecked = false;
    }

    if(CSetupEnums::THEME_INVALID < eCurrentTheme && CSetupEnums::THEME_FIVE >= eCurrentTheme)
    {
        m_listThemes[eCurrentTheme].m_bListItemChecked = true;
    }
}
